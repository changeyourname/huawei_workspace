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

#include "string.h"

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"
#include "pci.h"

#include "cirrus_constants.h"

#define PREFIX              "VGA"

//
// Changing these requires changes to model.xml
//
#define RAM_PORT_NAME         "memory"
#define ISA_PORT_NAME         "config"
#define SCAN_DELAY_ATTRIBUTE  "scanDelay"

// opaque handles that can hold native pointers on both 32-bit and 64-bit hosts
typedef Uns64 vgaStateHandle;
typedef Uns64 displayStateHandle;

static displayStateHandle ds;
static vgaStateHandle     vs;
static Uns32              diagLevel = 0;

// statistics
static Uns32 updates     = 0;
static Uns32 ISAwrites   = 0;
static Uns32 ISAreads    = 0;

//
///////////////////// Intercepted by vga SHL ///////////////////////
//

displayStateHandle displayInit(char * title)
{
    bhmMessage("F", PREFIX, "Failed to intercept : displayInit()");
    return (displayStateHandle){0};
}

vgaStateHandle cirrusInit(Uns32 size, const char *portName, Uns32 id)
{
    bhmMessage("F", PREFIX, "Failed to intercept : cirrusInit()");
    return (vgaStateHandle){0};
}

void vgaDisplay(vgaStateHandle vga, displayStateHandle ds)
{
    bhmMessage("F", PREFIX, "Failed to intercept : vgaDisplay()");
}

void mapDisplay(vgaStateHandle vga, Uns32 base)
{
    bhmMessage("F", PREFIX, "Failed to intercept : %s", __func__);
}

Uns32 ioportRead(vgaStateHandle vgaState, Uns32 address, Uns32 diag)
{
    bhmMessage("F", PREFIX, "Failed to intercept : ioportRead()");
    return 0;
}

void ioportWrite(vgaStateHandle vgaState, Uns32 address, Uns32 bytes, Uns32 diag)
{
    bhmMessage("F", PREFIX, "Failed to intercept : ioportWrite()");
}

static void setupDisplay(Uns32 base, Uns32 size, Bool install, void *user)
{
    if (!install) {
        bhmMessage("F", PREFIX, "model does not support unmapping");
    }
    // TODO : explain why a PCI VGA falls outside the PCI memory mapped region!!
    mapDisplay(vs, base & 0x10000000);
}

static void mapGPIO(Uns32 base, Uns32 size, Bool install, void *user)
{
    if (!install) {
        bhmMessage("F", PREFIX, "model does not support unmapping");
    }
    bhmMessage("I", PREFIX, "Writing PCI config GPIO Base 0x%x - this is unsupported.", base);
}

static void pciInit(void)
{
    pciConfig.vendorID       = PCI_VENDOR_CIRRUS;
    pciConfig.deviceID       = CIRRUS_ID_CLGD5446;
    pciConfig.command        = 0; //PCI_COMMAND_IOACCESS | PCI_COMMAND_MEMACCESS;
    pciConfig.classCode[1]   = PCI_CLASS_SUB_VGA;
    pciConfig.classCode[2]   = PCI_CLASS_BASE_DISPLAY;
    pciConfig.headerType     = PCI_CLASS_HEADERTYPE_00h;
    pciConfig.baseAddress[0] = 0x08;
    pciConnectConfigSlavePort(PREFIX, NULL);
    pciInstallRegion(0x10, 0xfe000008, 0,  setupDisplay,  VGA_RAM_SIZE);
    pciInstallRegion(0x14, 0xfffff000, 0,  mapGPIO, 0x1000);
}

//
// ISA configuration registers
//
static unsigned char ISAconfigWindow [0x30];

static PPM_READ_CB(ISAconfigRead) {
    Uns32 off  = (unsigned char*)addr - &ISAconfigWindow[0x0] + 0x3b0;
    ISAreads++;
    Uns16 res;
    switch(bytes) {
        case 1: {
            res = ioportRead(vs, off, diagLevel);
            break;
        }
        case 2: {
            Uns8 lo = ioportRead(vs, off, diagLevel);
            Uns8 hi = ioportRead(vs, off+1, diagLevel);
            res = lo | (hi<<8);
            break;
        }
        default:
            bhmMessage("E", PREFIX, "Attempting %u byte read", bytes);
            return 0;
    }
    return res;
}

static PPM_WRITE_CB(ISAconfigWrite) {
    Uns32 off  = (unsigned char*)addr - &ISAconfigWindow[0x0] + 0x3b0;

    ISAwrites++;
    switch(bytes) {
        case 1:
            ioportWrite(vs, off, data, diagLevel);
            break;
        case 2:
            ioportWrite(vs, off,   data&0xff, diagLevel);
            ioportWrite(vs, off+1, data>>8,   diagLevel);
            break;
         default:
            bhmMessage("E", PREFIX, "Attempting %u byte write", bytes);
    }
}

static void updateDisplay(void)
{
    vgaDisplay(vs, ds);
}

//
// Connect bus ports
//
static void ISAconfigConnection(const char *portName)
{
    // TODO : this should be set up by the PCI I/O config base register
    // but it doesn't make sense to me.
    if( ppmOpenSlaveBusPort(
        portName,
        ISAconfigWindow,
        sizeof(ISAconfigWindow)
    )) {
        ppmInstallReadCallback(
            ISAconfigRead,
            0,
            &ISAconfigWindow[0x0],
            sizeof(ISAconfigWindow)
        );
        ppmInstallWriteCallback(
            ISAconfigWrite,
            0,
            &ISAconfigWindow[0x0],
            sizeof(ISAconfigWindow)
        );
        if(BHM_DIAG_LOW) {
            bhmMessage("I", PREFIX,
                "Connected ISA configuration port '%s'",
                portName
            );
        }
    } else {
        bhmMessage("F", "Failed to connect to '%s'", portName);
    }
}

void *malloc(int);
//
// This thread waits for the end of simulation
//
static Uns8 endStack[1024*32];
#define STACK_TOP(_s) (&_s[sizeof(_s)-1])

static void endSimulation(void *nu)
{
    bhmEventHandle finished = bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION);
    bhmWaitEvent(finished);
    bhmMessage("I", PREFIX, "Statistics:");
    bhmPrintf("Screen updates :    %d\n", updates);
    bhmPrintf("ISA reads      :    %d\n", ISAreads);
    bhmPrintf("ISA writes     :    %d\n", ISAwrites);
}

Uns32 ImperasTestModeTimeout()
{
    bhmMessage("F", PREFIX, "Failed to intercept : ImperasTestModeTimeout()");
    return (Uns32)NULL;
}

#define TEST_STACK_SIZE  (1024*32)
static  Uns8 testStack[TEST_STACK_SIZE];

double ImperasTestTimeout = 0.0;
static void ImperasTestModeTimeoutThread(void *user) {
    bhmWaitDelay(ImperasTestTimeout*1000000); // timeout in seconds
    bhmFinish();
}

int main(int argc, char **argv) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Graphics card");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform. \n\
           The VGA peripheral utilises memory mapping.\n\
           This requires the use of ICM memory for the frame buffers, which currently may stop its use in SystemC TLM2 platforms.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "cirrus CL GD 5446.pdf Version 2.0 November 1996");
    }

    // diagnostic levels > 3 are passed to the semihost library
    diagLevel = bhmGetDiagnosticLevel();

    if(ImperasTestModeTimeout(&ImperasTestTimeout)) {
        bhmCreateThread(ImperasTestModeTimeoutThread, 0, "ImperasTestModeTimeoutThread", &(testStack[TEST_STACK_SIZE]));
    }

    ISAconfigConnection(ISA_PORT_NAME);

    char title[32];
    char* titleP = 0;
    if (bhmStringAttribute("title", title, sizeof(title))) {
        titleP = title;
    }

    ds = displayInit(titleP);
    vs = cirrusInit( VGA_RAM_SIZE, RAM_PORT_NAME, CIRRUS_ID_CLGD5446);
    vgaDisplay(vs, ds);

    Uns32 delay = 200;
    bhmIntegerAttribute(SCAN_DELAY_ATTRIBUTE, &delay);
    pciInit();

    if (BHM_DIAG_LOW) {
        bhmCreateThread(endSimulation, 0, "end", STACK_TOP(endStack));
        bhmMessage("I", PREFIX, "Starting. Diagnostic level:%d. Scan delay:%d", diagLevel, delay);
    }

    while(1) {
        bhmWaitDelay(delay);
        updateDisplay();
        updates++;
    }
    return 0;
}
