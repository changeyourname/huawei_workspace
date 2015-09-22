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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCRC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CRC_maskWrite) {
    bport1_ab_data.CRC.value = (bport1_ab_data.CRC.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_CTRL_maskWrite) {
    bport1_ab_data.CTRL.value = (bport1_ab_data.CTRL.value & 0x8ffffff) | (data & 0xf7000000);
}

static PPM_WRITE_CB(bport1_ab_GPOLY_maskWrite) {
    bport1_ab_data.GPOLY.value = (bport1_ab_data.GPOLY.value & 0x0) | (data & 0xffffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_CRC",
        "CRC Data Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_CRC_maskWrite,
        view32,
        &(bport1_ab_data.CRC.value),
        True
    );
    ppmCreateRegister("ab_GPOLY",
        "CRC Polynomial Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_GPOLY_maskWrite,
        view32,
        &(bport1_ab_data.GPOLY.value),
        True
    );
    ppmCreateRegister("ab_CTRL",
        "CRC Control Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_CTRL_maskWrite,
        view32,
        &(bport1_ab_data.CTRL.value),
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
        bport1_ab_data.CTRL.value = 0x0;
        bport1_ab_data.GPOLY.value = 0x1021;
        bport1_ab_data.CRC.value = 0xffffffff;
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
