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
 * PCI configuratuion bus interface.
 */

#ifndef PCI_H
#define PCI_H

#include "peripheral/impTypes.h"
#include "peripheral/ppm.h"

//
// temporarily here
//
#define PCI_IO_BASE_ADDR        0x18000000
#define PCI_MM_BASE_ADDR        0x08000000
#define BUS_PORT_NAME           "busPort"

// 32-bit read/write from pciConfig
#define CONFIG_ACCESS_32(_offset)   *(Uns32*)((Uns8*)(&pciConfig) + _offset)
#define CONFIG_ACCESS_16(_offset)   *(Uns16*)((Uns8*)(&pciConfig) + _offset)
#define CONFIG_ACCESS_8(_offset)    *(Uns8*)((Uns8*)(&pciConfig) + _offset)

//
// This maps directly into PCI space
//
typedef struct PCIconfigurationHeaderS {
    Uns16 vendorID;              // 0
    Uns16 deviceID;              // 2

    Uns16 command;               // 4
    Uns16 status;                // 6

    Uns8  revisionID;            // 8
    Uns8  classCode[3];          // 9-B

    Uns8  cacheLineSize;         // C
    Uns8  latencyTimer;          // D
    Uns8  headerType;            // E
    Uns8  BIST;                  // F

    Uns32 baseAddress[6];               // 10-27
    Uns32 cardbusAddress;               // 28-2B

    Uns16 subsystemVendorID;            // 2c
    Uns16 subsystemID;                  // 2E

    Uns32 expansionROMaddress;          // 30

    Uns32 reserved[2];                  // 34

    Uns8  interruptLine;                // 3c
    Uns8  interruptPin;                 // 3D
    Uns8  minGnt;                       // 3E
    Uns8  maxLat;                       // 3F
    union {
        Uns32 words[48];                // 40-FF
        Uns8  bytes[48*4];
    } user;

} PCIconfigurationHeader, *PCIconfigurationHeaderP, *PCIconfigurationHeaderPP;

typedef struct pciCfgInfoS {
    const char *desc;
    Uns8        bytes;
} pciCfgInfo;

static __attribute__((unused)) const char *pciCfgDesc[0x40] = {
        [0x00] = "VendorID",              // 0
        [0x02] = "deviceID",              // 2
        [0x04] = "command",               // 4
        [0x06] = "status",                // 6
        [0x08] = "revisionID",            // 8
        [0x09] = "classCode[3]",          // 9-B
        [0x0c] = "cacheLineSize",         // C
        [0x0d] = "latencyTimer",          // D
        [0x0e] = "headerType",            // E
        [0x0f] = "BIST",                  // F
        [0x10] = "baseAddress[6]",        // 10-27
        [0x28] = "cardbusAddress",        // 28-2B
        [0x2c] = "subsystemVendorID",     // 2c
        [0x2e] = "subsystemID",           // 2E
        [0x30] = "expansionROMaddress",   // 30
        [0x34] = "reserved[2]",           // 34
        [0x3c] = "interruptLine",         // 3c
        [0x3d] = "interruptPin",          // 3D
        [0x3e] = "minGnt",                // 3E
        [0x3f] = "maxLat",                // 3F
};

//
// A PCI device can have this many mappable regions
//
#define MAX_REGIONS     6

//
// Function called to install a PCI region
// install=0 implies uninstall
//
typedef void (*regionInstaller)(Uns32 base, Uns32 bytes, Bool install, void *user);

//
// One of these for each baseAddress
//
typedef struct PCIregionS {
    Uns32           regOffset;     // offset of the region's baseAddress register
    Uns32           mask;          // mask reply to probe request
    Uns32           mapping;       // current base address
    void            *windowOrUser; // ptr to window or user data pased to cb
    regionInstaller cb;
    Uns32           size;       // window size in bytes
    Bool            mapped;     // Has been mapped already
} PCIregion, *PCIregionP, **PCIregionPP;

#define ASSERT(_e,_str)  if(!(_e)) bhmMessage("F", PREFIX, "Assertion Faulure:" _str);

//
// Export to the user
//
extern PCIconfigurationHeader pciConfig;

extern ppmAddressSpaceHandle masterHandle;

//
// Install a PCI region
//     region is the region number (0-5)
//     remap is the function called to remap the region
//     Either window or cb must be specified, not both
//
void pciInstallRegion(
    Uns32           regOffset,     // offset of the region baseAddress register
    Uns32           mask,          // see PCI spec
    void            *windowOrUser, // address of local window
    regionInstaller cb,            // called when a region is mapped
    Uns32           size           // window size
);

//
// Callback when a user-writable register is written
//
typedef void (*writeCB)(void *user, Uns32 offset, Uns32 data);

//
// Tell the PCI implementation it's OK to write to this region
// (and get a callback if required)
//
void pciInstallUserWritable(
    Uns32      regOffset,
    Uns32      bytes,
    writeCB    writeFn,
    void       *user
);

//
// Initialise and connect the slave to PCI config bus.
// If slavePort is non-null, this override the default name.
//
void pciConnectConfigSlavePort(const char *prefix, const char *slavePort);

//
// Initialise and connect master to bus.
//
void pciConnectBusMaster(void);

Bool endianBig;
#define PCIENDIANNET "swapBytes"
ppmNetHandle pciEndianNetHandle;

#endif /*PCI_H*/
