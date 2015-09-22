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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisMCG", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_ATCVH_maskWrite) {
    bport1_ab_data.ATCVH.value = (bport1_ab_data.ATCVH.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_ATCVL_maskWrite) {
    bport1_ab_data.ATCVL.value = (bport1_ab_data.ATCVL.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C10_maskWrite) {
    bport1_ab_data.C10.value = (bport1_ab_data.C10.value & 0x43) | (data & 0xbc);
}

static PPM_WRITE_CB(bport1_ab_C11_maskWrite) {
    bport1_ab_data.C11.value = (bport1_ab_data.C11.value & 0x8) | (data & 0xf7);
}

static PPM_WRITE_CB(bport1_ab_C12_maskWrite) {
    bport1_ab_data.C12.value = (bport1_ab_data.C12.value & 0x40) | (data & 0xbf);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C2_maskWrite) {
    bport1_ab_data.C2.value = (bport1_ab_data.C2.value & 0x40) | (data & 0xbf);
}

static PPM_WRITE_CB(bport1_ab_C3_maskWrite) {
    bport1_ab_data.C3.value = (bport1_ab_data.C3.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C4_maskWrite) {
    bport1_ab_data.C4.value = (bport1_ab_data.C4.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C5_maskWrite) {
    bport1_ab_data.C5.value = (bport1_ab_data.C5.value & 0x18) | (data & 0xe7);
}

static PPM_WRITE_CB(bport1_ab_C6_maskWrite) {
    bport1_ab_data.C6.value = (bport1_ab_data.C6.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C7_maskWrite) {
    bport1_ab_data.C7.value = (bport1_ab_data.C7.value & 0xfe) | (data & 0x1);
}

static PPM_WRITE_CB(bport1_ab_C8_maskWrite) {
    bport1_ab_data.C8.value = (bport1_ab_data.C8.value & 0x5f) | (data & 0xa0);
}

static PPM_WRITE_CB(bport1_ab_SC_maskWrite) {
    bport1_ab_data.SC.value = (bport1_ab_data.SC.value & 0xbf) | (data & 0x40);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_C1",
        "MCG Control 1 Register, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_C1_maskWrite,
        view8,
        &(bport1_ab_data.C1.value),
        True
    );
    ppmCreateRegister("ab_C2",
        "MCG Control 2 Register, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_C2_maskWrite,
        view8,
        &(bport1_ab_data.C2.value),
        True
    );
    ppmCreateRegister("ab_C3",
        "MCG Control 3 Register, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_C3_maskWrite,
        view8,
        &(bport1_ab_data.C3.value),
        True
    );
    ppmCreateRegister("ab_C4",
        "MCG Control 4 Register, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        bport1_ab_C4_maskWrite,
        view8,
        &(bport1_ab_data.C4.value),
        True
    );
    ppmCreateRegister("ab_C5",
        "MCG Control 5 Register, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_C5_maskWrite,
        view8,
        &(bport1_ab_data.C5.value),
        True
    );
    ppmCreateRegister("ab_C6",
        "MCG Control 6 Register, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_C6_maskWrite,
        view8,
        &(bport1_ab_data.C6.value),
        True
    );
    ppmCreateRegister("ab_S",
        "MCG Status Register, offset: 0x6 ",
        handles.bport1,
        6,
        1,
        readS,
        0,
        viewS,
        &(bport1_ab_data.S.value),
        True
    );
    ppmCreateRegister("ab_SC",
        "MCG Status and Control Register, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_SC_maskWrite,
        view8,
        &(bport1_ab_data.SC.value),
        True
    );
    ppmCreateRegister("ab_ATCVH",
        "MCG Auto Trim Compare Value High Register, offset: 0xA ",
        handles.bport1,
        10,
        1,
        read_8,
        bport1_ab_ATCVH_maskWrite,
        view8,
        &(bport1_ab_data.ATCVH.value),
        True
    );
    ppmCreateRegister("ab_ATCVL",
        "MCG Auto Trim Compare Value Low Register, offset: 0xB ",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_ATCVL_maskWrite,
        view8,
        &(bport1_ab_data.ATCVL.value),
        True
    );
    ppmCreateRegister("ab_C7",
        "MCG Control 7 Register, offset: 0xC ",
        handles.bport1,
        12,
        1,
        read_8,
        bport1_ab_C7_maskWrite,
        view8,
        &(bport1_ab_data.C7.value),
        True
    );
    ppmCreateRegister("ab_C8",
        "MCG Control 8 Register, offset: 0xD ",
        handles.bport1,
        13,
        1,
        read_8,
        bport1_ab_C8_maskWrite,
        view8,
        &(bport1_ab_data.C8.value),
        True
    );
    ppmCreateRegister("ab_C10",
        "MCG Control 10 Register, offset: 0xF ",
        handles.bport1,
        15,
        1,
        read_8,
        bport1_ab_C10_maskWrite,
        view8,
        &(bport1_ab_data.C10.value),
        True
    );
    ppmCreateRegister("ab_C11",
        "MCG Control 11 Register, offset: 0x10 ",
        handles.bport1,
        16,
        1,
        read_8,
        bport1_ab_C11_maskWrite,
        view8,
        &(bport1_ab_data.C11.value),
        True
    );
    ppmCreateRegister("ab_C12",
        "MCG Control 12 Register, offset: 0x11 ",
        handles.bport1,
        17,
        1,
        read_8,
        bport1_ab_C12_maskWrite,
        view8,
        &(bport1_ab_data.C12.value),
        True
    );
    ppmCreateRegister("ab_S2",
        "MCG Status 2 Register, offset: 0x12 ",
        handles.bport1,
        18,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.S2.value),
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
        bport1_ab_data.S2.value = 0x0;
        bport1_ab_data.C12.value = 0x0;
        bport1_ab_data.C11.value = 0x0;
        bport1_ab_data.C10.value = 0x80;
        bport1_ab_data.C8.value = 0x0;
        bport1_ab_data.C7.value = 0x0;
        bport1_ab_data.ATCVL.value = 0x0;
        bport1_ab_data.ATCVH.value = 0x0;
        bport1_ab_data.SC.value = 0x0;
        bport1_ab_data.S.value = 0x6a;
        bport1_ab_data.C6.value = 0x0;
        bport1_ab_data.C5.value = 0x0;
        bport1_ab_data.C4.value = 0x0;
        bport1_ab_data.C2.value = 0x80;
        bport1_ab_data.C1.value = 0x4;
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
        ppmDocAddText(doc2_node, "Freescale Multipurpose Clock Generator");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Only models status register reads, based on writes to configuration registers\n\natc register ATME bit is modeled as RAZ/WI");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

