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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisTSI", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_GENCS_maskWrite) {
    bport1_ab_data.GENCS.value = (bport1_ab_data.GENCS.value & 0xe0000e0c) | (data & 0x1ffff1f3);
}

static PPM_WRITE_CB(bport1_ab_PEN_maskWrite) {
    bport1_ab_data.PEN.value = (bport1_ab_data.PEN.value & 0xfff00000) | (data & 0xfffff);
}

static PPM_WRITE_CB(bport1_ab_SCANC_maskWrite) {
    bport1_ab_data.SCANC.value = (bport1_ab_data.SCANC.value & 0xf0f000e0) | (data & 0xf0fff1f);
}

static PPM_WRITE_CB(bport1_ab_THRESHOLD_maskWrite) {
    bport1_ab_data.THRESHOLD.value = (bport1_ab_data.THRESHOLD.value & 0xf0000000) | (data & 0xfffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_GENCS",
        "General Control and Status Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_GENCS_maskWrite,
        view32,
        &(bport1_ab_data.GENCS.value),
        True
    );
    ppmCreateRegister("ab_SCANC",
        "SCAN Control Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_SCANC_maskWrite,
        view32,
        &(bport1_ab_data.SCANC.value),
        True
    );
    ppmCreateRegister("ab_PEN",
        "Pin Enable Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_PEN_maskWrite,
        view32,
        &(bport1_ab_data.PEN.value),
        True
    );
    ppmCreateRegister("ab_WUCNTR",
        "Wake-Up Channel Counter Register, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.WUCNTR.value),
        True
    );
    ppmCreateRegister("ab_CNTR1",
        "Counter Register, offset: 0x100 ",
        handles.bport1,
        256,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR1.value),
        True
    );
    ppmCreateRegister("ab_CNTR3",
        "Counter Register, offset: 0x104 ",
        handles.bport1,
        260,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR3.value),
        True
    );
    ppmCreateRegister("ab_CNTR5",
        "Counter Register, offset: 0x108 ",
        handles.bport1,
        264,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR5.value),
        True
    );
    ppmCreateRegister("ab_CNTR7",
        "Counter Register, offset: 0x10C ",
        handles.bport1,
        268,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR7.value),
        True
    );
    ppmCreateRegister("ab_CNTR9",
        "Counter Register, offset: 0x110 ",
        handles.bport1,
        272,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR9.value),
        True
    );
    ppmCreateRegister("ab_CNTR11",
        "Counter Register, offset: 0x114 ",
        handles.bport1,
        276,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR11.value),
        True
    );
    ppmCreateRegister("ab_CNTR13",
        "Counter Register, offset: 0x118 ",
        handles.bport1,
        280,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR13.value),
        True
    );
    ppmCreateRegister("ab_CNTR15",
        "Counter Register, offset: 0x11C ",
        handles.bport1,
        284,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNTR15.value),
        True
    );
    ppmCreateRegister("ab_THRESHOLD",
        "Low Power Channel Threshold Register, offset: 0x120 ",
        handles.bport1,
        288,
        4,
        read_32,
        bport1_ab_THRESHOLD_maskWrite,
        view32,
        &(bport1_ab_data.THRESHOLD.value),
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
        bport1_ab_data.THRESHOLD.value = 0x0;
        bport1_ab_data.CNTR15.value = 0x0;
        bport1_ab_data.CNTR13.value = 0x0;
        bport1_ab_data.CNTR11.value = 0x0;
        bport1_ab_data.CNTR9.value = 0x0;
        bport1_ab_data.CNTR7.value = 0x0;
        bport1_ab_data.CNTR5.value = 0x0;
        bport1_ab_data.CNTR3.value = 0x0;
        bport1_ab_data.CNTR1.value = 0x0;
        bport1_ab_data.WUCNTR.value = 0x0;
        bport1_ab_data.PEN.value = 0x0;
        bport1_ab_data.SCANC.value = 0x0;
        bport1_ab_data.GENCS.value = 0x0;
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

