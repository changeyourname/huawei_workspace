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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridLCD", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_ENFPR0_maskWrite) {
    bport1_ab_data.ENFPR0.value = (bport1_ab_data.ENFPR0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_ENFPR1_maskWrite) {
    bport1_ab_data.ENFPR1.value = (bport1_ab_data.ENFPR1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDCCR_maskWrite) {
    bport1_ab_data.LCDCCR.value = (bport1_ab_data.LCDCCR.value & 0x7800ffff) | (data & 0x87ff0000);
}

static PPM_WRITE_CB(bport1_ab_LCDCR_maskWrite) {
    bport1_ab_data.LCDCR.value = (bport1_ab_data.LCDCR.value & 0xc8) | (data & 0xffffff37);
}

static PPM_WRITE_CB(bport1_ab_LCDPCR_maskWrite) {
    bport1_ab_data.LCDPCR.value = (bport1_ab_data.LCDPCR.value & 0xf0ffffff) | (data & 0xf000000);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM0_maskWrite) {
    bport1_ab_data.LCDRAM0.value = (bport1_ab_data.LCDRAM0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM10_maskWrite) {
    bport1_ab_data.LCDRAM10.value = (bport1_ab_data.LCDRAM10.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM11_maskWrite) {
    bport1_ab_data.LCDRAM11.value = (bport1_ab_data.LCDRAM11.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM12_maskWrite) {
    bport1_ab_data.LCDRAM12.value = (bport1_ab_data.LCDRAM12.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM13_maskWrite) {
    bport1_ab_data.LCDRAM13.value = (bport1_ab_data.LCDRAM13.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM14_maskWrite) {
    bport1_ab_data.LCDRAM14.value = (bport1_ab_data.LCDRAM14.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM15_maskWrite) {
    bport1_ab_data.LCDRAM15.value = (bport1_ab_data.LCDRAM15.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM1_maskWrite) {
    bport1_ab_data.LCDRAM1.value = (bport1_ab_data.LCDRAM1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM2_maskWrite) {
    bport1_ab_data.LCDRAM2.value = (bport1_ab_data.LCDRAM2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM3_maskWrite) {
    bport1_ab_data.LCDRAM3.value = (bport1_ab_data.LCDRAM3.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM4_maskWrite) {
    bport1_ab_data.LCDRAM4.value = (bport1_ab_data.LCDRAM4.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM5_maskWrite) {
    bport1_ab_data.LCDRAM5.value = (bport1_ab_data.LCDRAM5.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM6_maskWrite) {
    bport1_ab_data.LCDRAM6.value = (bport1_ab_data.LCDRAM6.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM7_maskWrite) {
    bport1_ab_data.LCDRAM7.value = (bport1_ab_data.LCDRAM7.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM8_maskWrite) {
    bport1_ab_data.LCDRAM8.value = (bport1_ab_data.LCDRAM8.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM9_maskWrite) {
    bport1_ab_data.LCDRAM9.value = (bport1_ab_data.LCDRAM9.value & 0x0) | (data & 0xffffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_LCDCR",
        "LCD Control Register, offset: 0x0",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_LCDCR_maskWrite,
        view32,
        &(bport1_ab_data.LCDCR.value),
        True
    );
    ppmCreateRegister("ab_LCDPCR",
        "LCD Prescaler Control Register, offset: 0x4",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_LCDPCR_maskWrite,
        view32,
        &(bport1_ab_data.LCDPCR.value),
        True
    );
    ppmCreateRegister("ab_LCDCCR",
        "LCD Contrast Control Register, offset: 0x8",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_LCDCCR_maskWrite,
        view32,
        &(bport1_ab_data.LCDCCR.value),
        True
    );
    ppmCreateRegister("ab_ENFPR0",
        "LCD Frontplane Enable Register 0, offset: 0x10",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_ENFPR0_maskWrite,
        view32,
        &(bport1_ab_data.ENFPR0.value),
        True
    );
    ppmCreateRegister("ab_ENFPR1",
        "LCD Frontplane Enable Register 1, offset: 0x14",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_ENFPR1_maskWrite,
        view32,
        &(bport1_ab_data.ENFPR1.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM0",
        "LCDRAM, offset: 0x20",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_LCDRAM0_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM0.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM1",
        "LCDRAM, offset: 0x24",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_LCDRAM1_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM1.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM2",
        "LCDRAM, offset: 0x28",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_LCDRAM2_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM2.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM3",
        "LCDRAM, offset: 0x2C",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_LCDRAM3_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM3.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM4",
        "LCDRAM, offset: 0x30",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_LCDRAM4_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM4.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM5",
        "LCDRAM, offset: 0x34",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_LCDRAM5_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM5.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM6",
        "LCDRAM, offset: 0x38",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_LCDRAM6_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM6.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM7",
        "LCDRAM, offset: 0x3C",
        handles.bport1,
        60,
        4,
        read_32,
        bport1_ab_LCDRAM7_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM7.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM8",
        "LCDRAM, offset: 0x40",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_LCDRAM8_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM8.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM9",
        "LCDRAM, offset: 0x44",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_LCDRAM9_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM9.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM10",
        "LCDRAM, offset: 0x48",
        handles.bport1,
        72,
        4,
        read_32,
        bport1_ab_LCDRAM10_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM10.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM11",
        "LCDRAM, offset: 0x4c",
        handles.bport1,
        76,
        4,
        read_32,
        bport1_ab_LCDRAM11_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM11.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM12",
        "LCDRAM, offset: 0x50",
        handles.bport1,
        80,
        4,
        read_32,
        bport1_ab_LCDRAM12_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM12.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM13",
        "LCDRAM, offset: 0x54",
        handles.bport1,
        84,
        4,
        read_32,
        bport1_ab_LCDRAM13_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM13.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM14",
        "LCDRAM, offset: 0x58",
        handles.bport1,
        88,
        4,
        read_32,
        bport1_ab_LCDRAM14_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM14.value),
        True
    );
    ppmCreateRegister("ab_LCDRAM15",
        "LCDRAM, offset: 0x5c",
        handles.bport1,
        92,
        4,
        read_32,
        bport1_ab_LCDRAM15_maskWrite,
        view32,
        &(bport1_ab_data.LCDRAM15.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, reset_Reset, (void*)0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.LCDRAM15.value = 0x0;
        bport1_ab_data.LCDRAM14.value = 0x0;
        bport1_ab_data.LCDRAM13.value = 0x0;
        bport1_ab_data.LCDRAM12.value = 0x0;
        bport1_ab_data.LCDRAM11.value = 0x0;
        bport1_ab_data.LCDRAM10.value = 0x0;
        bport1_ab_data.LCDRAM9.value = 0x0;
        bport1_ab_data.LCDRAM8.value = 0x0;
        bport1_ab_data.LCDRAM7.value = 0x0;
        bport1_ab_data.LCDRAM6.value = 0x0;
        bport1_ab_data.LCDRAM5.value = 0x0;
        bport1_ab_data.LCDRAM4.value = 0x0;
        bport1_ab_data.LCDRAM3.value = 0x0;
        bport1_ab_data.LCDRAM2.value = 0x0;
        bport1_ab_data.LCDRAM1.value = 0x0;
        bport1_ab_data.LCDRAM0.value = 0x0;
        bport1_ab_data.ENFPR1.value = 0x0;
        bport1_ab_data.ENFPR0.value = 0x0;
        bport1_ab_data.LCDCCR.value = 0x0;
        bport1_ab_data.LCDPCR.value = 0x0;
        bport1_ab_data.LCDCR.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, 0);
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, 0);
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

