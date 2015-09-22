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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "peripheral/impTypes.h"
#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

#define BUFFERLENGTH 16
#define DEBUG 0
#define PREFIX "FloppyDrive"

//define no inline attribute for intercepted functions
#define NOINLINE  __attribute__((noinline))

Uns32 diag = 0;

#define DIAG_LOW             (diag > 0)
#define DIAG_MED             (diag > 1)
#define DIAG_HIGH            (diag > 2)

#define WINDOW               8

struct {
    Uns8 sra;
    Uns8 srb;
    Uns8 dor;
    Uns8 tdr;
    Uns8 msr;
    Uns8 dsr;
    Uns8 fifo;
    Uns8 reserved;
    Uns8 dir;
    Uns8 ccr;
} device;


///////////////////////////////////////////////////////////////////////////////
// READ
///////////////////////////////////////////////////////////////////////////////
static PPM_REG_READ_CB(readReg) {
    Int32 offset = (Uns32)user - (Uns32)&(device);
    bhmMessage("I", PREFIX, "READ from Peripheral Register %d\n", offset);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////
// WRITE
///////////////////////////////////////////////////////////////////////////////
static PPM_REG_WRITE_CB(writeReg) {
    Int32 offset = (Uns32)user - (Uns32)&(device);
    bhmMessage("I", PREFIX, "Write to Peripheral Register %d value = %x\n", offset, data);
}


void createRegisters(void) {
    Uns32 windowSize = WINDOW;

    void *w = ppmCreateSlaveBusPort("bport1", windowSize);
    //                name    description                      base offset size read     write     view  user data
    ppmCreateRegister("sra", "Status Register A",              w,   0,     1,   readReg, NULL,     NULL, &device.sra,      True);
    ppmCreateRegister("srb", "Status Register B",              w,   1,     1,   readReg, NULL,     NULL, &device.srb,      True);
    ppmCreateRegister("dor", "Digital Out Register",           w,   2,     1,   readReg, writeReg, NULL, &device.dor,      True);
    ppmCreateRegister("tdr", "Tape Drive Register",            w,   3,     1,   readReg, writeReg, NULL, &device.tdr,      True);
    ppmCreateRegister("msr", "Main Status Register",           w,   4,     1,   readReg, NULL,     NULL, &device.msr,      True);
    ppmCreateRegister("dsr", "Data Rate Select Register",      w,   4,     1,   NULL,    writeReg, NULL, &device.dsr,      True);
    ppmCreateRegister("fifo", "Data Fifo",                     w,   5,     1,   readReg, writeReg, NULL, &device.fifo,     True);
    ppmCreateRegister("reserved", "Reserved",                  w,   6,     1,   NULL,    NULL,     NULL, &device.reserved, True);
    ppmCreateRegister("dir", "Digital Input Register",         w,   7,     1,   readReg, NULL,     NULL, &device.dir,      True);
    ppmCreateRegister("ccr", "Configuration Control Register", w,   7,     1,   NULL,    writeReg, NULL, &device.ccr,      True);
}

//
// Set the local diag level
//
static void setDiagLevel(Uns32 d)
{
    diag =d;
}

int main(int argc, char **argv)
{
	// Model Documentation
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Dummy Floppy Disc Controller.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Register stubs only.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "http://www.buchty.net/casio/files/82077.pdf http://www.alldatasheet.com/datesheet-pdf/pdf/167793/INTEL/82077AA.html");
    }

    bhmInstallDiagCB(setDiagLevel);

    createRegisters();

    // now sit and wait for things to happen
    if(DIAG_LOW) bhmMessage("I", PREFIX, "main done\n");
    bhmEventHandle never = bhmCreateEvent();

    bhmWaitEvent(never);
    return 0;
}
