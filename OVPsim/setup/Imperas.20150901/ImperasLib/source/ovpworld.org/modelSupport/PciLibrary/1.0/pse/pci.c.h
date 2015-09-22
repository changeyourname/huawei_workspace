/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*
 * This is the common PCI configuration code.
 * Called during start-up by PCI peripherals, it connects to the PCI configuration
 * bus, then calls each peripheral's mapping functions to map them into
 * PCI IO or Memory space.
 */

#include "string.h"

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#include "pci.h"

#define PREFIX               prefixString
#define PCI_SLOT_ATTRIBUTE   "PCIslot"
#define PCI_FN_ATTRIBUTE     "PCIfunction"
#define PCI_PORT_NAME        "PCIconfig"

// each function window is 2^8
// (This card has only one function; the other 7 are unused)
#define PCI_CONFIG_WINDOW   (1 << 8)

// PCI slots are 2^12 wide
#define SLOT_TO_ADDRESS(_s, _f) ((_s) << 11 | ((_f) << 8))

// masks for base address registers
#define ADDRESS_PROBE_MASK   0xFFFFFFFE
#define ADDRESS_PROBE        0xFFFFFFFE
#define MEM_SPACE_MASK       0xFFFFFFF0
#define IO_SPACE_MASK        0xFFFFFFFC
#define EXPANSION_MASK       0xFFFFF800

#define REGION_PREFETCH      0x00000008
#define REGION_4G            0x00000000
#define REGION_1M            0x00000002
#define REGION_64T           0x00000008
#define REGION_IO            0x00000001

// bits in command register
#define CMD_IO_ACCESS        0x0001
#define CMD_MEM_ACCESS       0x0002
#define CMD_MASTER_ENA       0x0004


//
// Areas where writes are allowed
//
typedef struct userRegionS {
    Uns32   regOffset;
    Uns32   bytes;
    writeCB writeFn;
    void    *user;
} userRegion, *userRegionP;

// Window mapped to PCI configuration space
static Uns8 pciConfigWindow[PCI_CONFIG_WINDOW];

// static values of PCI config registers
PCIconfigurationHeader pciConfig;

//
// list of region base registers and their mappings
//
static PCIregion PCIregions[MAX_REGIONS];

//
// List of user-defined writable regions
//
static userRegion userRegions[MAX_REGIONS];
//
// Used in diagnostic output
//
static const char *prefixString;
static Uns32      diag = 0;

//
// Flags for PCI diagnostics
//
//#define DIAG_PCI_LOW   (diag & 0x10)
//#define DIAG_PCI_HIGH  (diag & 0x20)
#define DIAG_PCI_LOW   BHM_DIAG_LOW
#define DIAG_PCI_HIGH  BHM_DIAG_HIGH

// One master port for all DMAs
ppmAddressSpaceHandle masterHandle;

//
// Next free slots
//
static Uns8       freeRegion           = 0;
static Uns8       freeUserRegion       = 0;

//
// Install a PCI region
//     region is the region number (0-5)
//     remap is the function called to remap the region
//
void pciInstallRegion(
    Uns32           regOffset,     // offset of the region baseAddress register
    Uns32           mask,          // see PCI spec
    void            *windowOrUser, // address of local window
    regionInstaller cb,            // optional cb to be called when mapped
    Uns32           size           // window size
)
{
    if (freeRegion >= MAX_REGIONS) {
        bhmMessage("F", PREFIX, "Installing too many address regions");
    }
    PCIregions[freeRegion].regOffset    = regOffset;
    PCIregions[freeRegion].mask         = mask;
    PCIregions[freeRegion].windowOrUser = windowOrUser;
    PCIregions[freeRegion].cb           = cb;
    PCIregions[freeRegion].size         = size;
    freeRegion++;
}

void pciInstallUserWritable(
    Uns32      regOffset,
    Uns32      bytes,
    writeCB    writeFn,
    void       *user
) {
    if (freeUserRegion >= MAX_REGIONS) {
        bhmMessage("F", PREFIX, "Installing too many user regions");
    }
    userRegions[freeUserRegion].regOffset = regOffset;
    userRegions[freeUserRegion].bytes     = bytes;
    userRegions[freeUserRegion].writeFn   = writeFn;
    userRegions[freeUserRegion].user      = user;
    freeUserRegion++;
}

//
// Map the users region to the given place in the PCI IO or memory address space
//
static void installRegisterRegion(const char *port, Uns32 base, Bool io, void *window, Uns32 size)
{
    if (io) {
        ppmCreateDynamicSlavePort(port, base, size, window);
        if (DIAG_PCI_LOW) {
            bhmMessage("I", PREFIX, "Installing IO window 0x%x at 0x%x ", size, base);
        }
    } else {
        if (DIAG_PCI_LOW) {
            bhmMessage("W", PREFIX, "NOT Installing 0x%x byte ROM at 0x%x", size, base);
        }
    }
}

//
// Unmap the users region in the PCI IO or memory address space
//
static void uninstallRegisterRegion(const char *port, Uns32 base, Bool io, Uns32 size)
{
    if(io) {
        ppmDeleteDynamicSlavePort(port, base, size);
        if (DIAG_PCI_LOW) {
            bhmMessage("I", PREFIX, "Removing IO window 0x%x at 0x%x", size, base);
        }
    } else {
        // TODO : expansion ROM (though I don't know what's in it).
        if (DIAG_PCI_LOW) {
            bhmMessage("W", PREFIX, "Not Uninstalling 0x%x byte ROM at 0x%x", size, base);
        }
    }
}

//
// Map or unmap a region
//
static void updateRegionMapping(Uns8 region)
{
    const char *port = BUS_PORT_NAME;
    Uns32 size = PCIregions[region].size;
    if(size) {
        Bool  io     = ((PCIregions[region].mask & REGION_IO) != 0);
        Uns32 offset = PCIregions[region].regOffset;
        Bool  map;
        Uns32 addr;
        if (io) {
            addr = (CONFIG_ACCESS_32(offset) & IO_SPACE_MASK) | PCI_IO_BASE_ADDR;
            map  = ((pciConfig.command & CMD_IO_ACCESS) != 0);
        } else {
            addr = (CONFIG_ACCESS_32(offset) & MEM_SPACE_MASK) | PCI_MM_BASE_ADDR;
            map  = ((pciConfig.command & CMD_MEM_ACCESS) != 0);
        }
        if (PCIregions[region].mapped != map) {
            if(PCIregions[region].cb)
                PCIregions[region].cb(addr, size, map, PCIregions[region].windowOrUser);
            else {
                if (map) {
                    installRegisterRegion(port, addr, io, PCIregions[region].windowOrUser, size);
                } else {
                    uninstallRegisterRegion(port, addr, io, size);
                }
            }
            PCIregions[region].mapped = map;
        }
    }
}

//
// map or unmap all regions
//
static void updateRegionMappings(void)
{
    Uns8 i;
    for(i = 0; i < freeRegion; i++)
        updateRegionMapping(i);
}

//
// Changing the cmmand register might map or unmap all memory or IO
//
static void writeCommandStatus(Uns32 data)
{
    // clear any bits where the written word contains a 1
    pciConfig.status &= ~(data >> 16);

    data &= 0x0000FFFF;
    Uns16 change = (CMD_IO_ACCESS | CMD_MEM_ACCESS) & (data ^ pciConfig.command);
    pciConfig.command = data;
    if(change) {
        updateRegionMappings();
    }
}

static void updateBaseAddress(Uns32 regOffset, Uns32 data)
{
    Uns8 i;
    for(i= 0; i < freeRegion; i++) {
        if(regOffset == PCIregions[i].regOffset) {
            if((data & ADDRESS_PROBE) == ADDRESS_PROBE) {
                CONFIG_ACCESS_32(regOffset) = PCIregions[i].mask;
            } else {
                Uns32 new = data & PCIregions[i].mask;
                CONFIG_ACCESS_32(regOffset) = new;
                updateRegionMapping(i);
            }
            return;
        }
    }
    // No special BAR was installed, therefore it is read-only.
}

static void writeUserDefined(Uns32 regOffset, Uns32 data)
{
    Uns8 i;
    for(i= 0; i < freeUserRegion; i++) {
        Uns32 l = userRegions[i].regOffset;
        Uns32 h = l + userRegions[i].bytes-1;
        if(regOffset >= l && regOffset < h) {
            CONFIG_ACCESS_32(regOffset) = data;
            if(userRegions[i].writeFn) {
                userRegions[i].writeFn(userRegions[i].user, regOffset, data);
            }
            return;
        }
    }
    // no region found
    bhmMessage("E", PREFIX,
        "Write to a read-only  user defined register (0x%x)",
        regOffset
    );
}

//
// The read callback just returns the array values
//
static PPM_READ_CB(pciConfigRead) {
    if (bytes != 4) {
        bhmMessage("E", PREFIX, "Unsupported read");
        return 0;
    }
    Uns32 offset = (Uns32)addr - (Uns32)pciConfigWindow;
    Uns32 data   = CONFIG_ACCESS_32(offset);
    if(DIAG_PCI_LOW) {
        const char *desc = (offset >= 0x40) ?  "Unknown" : pciCfgDesc[offset];
        Uns32 mask = (-1) >> (32 - (8 * bytes));
        bhmMessage("I", PREFIX, "Read PCI config [%s] 0x%04x = 0x%08x", desc, offset, (data & mask));
    }
    return data;
}

//
// The write callback endures the registers have legal values
// and triggers changes to the address map.
//
static PPM_WRITE_CB(pciConfigWrite) {
    if (bytes != 4) {
        bhmMessage("E", PREFIX, "Unsupported write");
        return;
    }
    Uns32 offset = (Uns32)addr - (Uns32)pciConfigWindow;
    if(DIAG_PCI_LOW) {
        const char *desc = (offset >= 0x40) ?  "Unknown" : pciCfgDesc[offset];
        Uns32 mask = (-1) >> (32 - (8 * bytes));
        bhmMessage("I", PREFIX, "Write PCI config [%s] 0x%04x = 0x%08x", desc, offset, (data & mask));
    }

    switch(offset) {
        case 0x04:
            writeCommandStatus(data);
            break;
        // these are where we know base registers can live, there might be more.
        case 0x10 ... 0x24:
        case 0x30:
        case 0x80:
            if(DIAG_PCI_HIGH)
                bhmMessage("I", PREFIX, "Write PCI base 0x%x <= 0x%x", offset, data);
            updateBaseAddress(offset, data);
            break;

        case 0x0C:
        case 0x3C:
            CONFIG_ACCESS_32(offset) = data;
            break;
        case 0x40 ... 0x7C:
        case 0x84 ... 0xFC:
            if(DIAG_PCI_HIGH)
                bhmMessage("I", PREFIX, "Write User Defined 0x%x <= 0x%x", offset, data);
             // user defined
             writeUserDefined(offset, data);
             break;
        default:
            bhmMessage("W", PREFIX, "Attempting write to PCI (Read-only) 0x%x <= 0x%x", offset, data);
            // all other registers are read-only
            break;
    }
}

//
// Initialise and connect the slave to PCI config bus.
// If slavePort is non-null, this override the default name.
//
void pciConnectConfigSlavePort(const char *prefix, const char *slavePort)
{
    if (!slavePort)
        slavePort = PCI_PORT_NAME;

    const char *slotAttributeName  = PCI_SLOT_ATTRIBUTE;
    const char *fnAttributeName    = PCI_FN_ATTRIBUTE;

    Uns32 slotNumber = 0;
    Uns32 fnNumber   = 0;

    prefixString = prefix;
    diag         = bhmGetDiagnosticLevel();

    bhmIntegerAttribute(slotAttributeName, &slotNumber);
    bhmIntegerAttribute(fnAttributeName, &fnNumber);

    Uns32 baseAddress = SLOT_TO_ADDRESS(slotNumber, fnNumber);

    // Wait for PCI controller to get ready
    bhmEventHandle started = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(started);

    if (!ppmCreateDynamicSlavePort(
        slavePort,
        baseAddress,
        sizeof(pciConfigWindow),
        pciConfigWindow
    )) {
        bhmMessage("W", PREFIX,
            "Failed to connect to PCI configuration bus (port %s)",
            slavePort
        );
        return;
    }

    if(DIAG_PCI_LOW) {
        bhmMessage("I", PREFIX,
            "Connected to PCI config bus (%s), slot:%d fn:%d (0x%x - 0x%lx)",
            slavePort,
            slotNumber,
            fnNumber,
            baseAddress,
            baseAddress+sizeof(pciConfigWindow)-1
        );
    }
    ppmInstallWriteCallback(
        pciConfigWrite,
        0,
        pciConfigWindow,
        sizeof(pciConfigWindow)
    );
    ppmInstallReadCallback(
        pciConfigRead,
        0,
        pciConfigWindow,
        sizeof(pciConfigWindow)
    );
}

void pciConnectBusMaster(void)
{
    char *port = "dmaPort";
    masterHandle = ppmOpenAddressSpace(port);

    if(!masterHandle) {
        bhmMessage("F", PREFIX, "Failed to open master port '%s'\n", port);
    }
}

/*************************************************************
 * Byte Swapping Functions
 *************************************************************/

Bool endianBig = False;
ppmNetHandle pciEndianNetHandle;
