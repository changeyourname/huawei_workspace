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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisPIT", "Example");
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

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_MCR",
        "PIT Module Control Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        writeMCR,
        view32,
        &(bport1_ab_data.MCR.value),
        True
    );
    ppmCreateRegister("ab_LDVAL0",
        "Timer Load Value Register, array offset: 0x100, array step: 0x10 ",
        handles.bport1,
        256,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.LDVAL0.value),
        True
    );
    ppmCreateRegister("ab_CVAL0",
        "Current Timer Value Register, array offset: 0x104, array step: 0x10 ",
        handles.bport1,
        260,
        4,
        readCVAL,
        0,
        viewCVAL,
        &(bport1_ab_data.CVAL0.value),
        True
    );
    ppmCreateRegister("ab_TCTRL0",
        "Timer Control Register, array offset: 0x108, array step: 0x10 ",
        handles.bport1,
        264,
        4,
        read_32,
        writeTCTRL,
        view32,
        &(bport1_ab_data.TCTRL0.value),
        True
    );
    ppmCreateRegister("ab_TFLG0",
        "Timer Flag Register, array offset: 0x10C, array step: 0x10 ",
        handles.bport1,
        268,
        4,
        read_32,
        writeTFLG,
        view32,
        &(bport1_ab_data.TFLG0.value),
        True
    );
    ppmCreateRegister("ab_LDVAL1",
        "Timer Load Value Register, array offset: 0x100, array step: 0x10 ",
        handles.bport1,
        272,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.LDVAL1.value),
        True
    );
    ppmCreateRegister("ab_CVAL1",
        "Current Timer Value Register, array offset: 0x104, array step: 0x10 ",
        handles.bport1,
        276,
        4,
        readCVAL,
        0,
        viewCVAL,
        &(bport1_ab_data.CVAL1.value),
        True
    );
    ppmCreateRegister("ab_TCTRL1",
        "Timer Control Register, array offset: 0x108, array step: 0x10 ",
        handles.bport1,
        280,
        4,
        read_32,
        writeTCTRL,
        view32,
        &(bport1_ab_data.TCTRL1.value),
        True
    );
    ppmCreateRegister("ab_TFLG1",
        "Timer Flag Register, array offset: 0x10C, array step: 0x10 ",
        handles.bport1,
        284,
        4,
        read_32,
        writeTFLG,
        view32,
        &(bport1_ab_data.TFLG1.value),
        True
    );
    ppmCreateRegister("ab_LDVAL2",
        "Timer Load Value Register, array offset: 0x100, array step: 0x10 ",
        handles.bport1,
        288,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.LDVAL2.value),
        True
    );
    ppmCreateRegister("ab_CVAL2",
        "Current Timer Value Register, array offset: 0x104, array step: 0x10 ",
        handles.bport1,
        292,
        4,
        readCVAL,
        0,
        viewCVAL,
        &(bport1_ab_data.CVAL2.value),
        True
    );
    ppmCreateRegister("ab_TCTRL2",
        "Timer Control Register, array offset: 0x108, array step: 0x10 ",
        handles.bport1,
        296,
        4,
        read_32,
        writeTCTRL,
        view32,
        &(bport1_ab_data.TCTRL2.value),
        True
    );
    ppmCreateRegister("ab_TFLG2",
        "Timer Flag Register, array offset: 0x10C, array step: 0x10 ",
        handles.bport1,
        300,
        4,
        read_32,
        writeTFLG,
        view32,
        &(bport1_ab_data.TFLG2.value),
        True
    );
    ppmCreateRegister("ab_LDVAL3",
        "Timer Load Value Register, array offset: 0x100, array step: 0x10 ",
        handles.bport1,
        304,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.LDVAL3.value),
        True
    );
    ppmCreateRegister("ab_CVAL3",
        "Current Timer Value Register, array offset: 0x104, array step: 0x10 ",
        handles.bport1,
        308,
        4,
        readCVAL,
        0,
        viewCVAL,
        &(bport1_ab_data.CVAL3.value),
        True
    );
    ppmCreateRegister("ab_TCTRL3",
        "Timer Control Register, array offset: 0x108, array step: 0x10 ",
        handles.bport1,
        312,
        4,
        read_32,
        writeTCTRL,
        view32,
        &(bport1_ab_data.TCTRL3.value),
        True
    );
    ppmCreateRegister("ab_TFLG3",
        "Timer Flag Register, array offset: 0x10C, array step: 0x10 ",
        handles.bport1,
        316,
        4,
        read_32,
        writeTFLG,
        view32,
        &(bport1_ab_data.TFLG3.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, reset_Reset, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.irq0, value);

    handles.irq0 = ppmOpenNetPort("irq0");

// To write to this net, use ppmWriteNet(handles.trg0, value);

    handles.trg0 = ppmOpenNetPort("trg0");

// To write to this net, use ppmWriteNet(handles.irq1, value);

    handles.irq1 = ppmOpenNetPort("irq1");

// To write to this net, use ppmWriteNet(handles.trg1, value);

    handles.trg1 = ppmOpenNetPort("trg1");

// To write to this net, use ppmWriteNet(handles.irq2, value);

    handles.irq2 = ppmOpenNetPort("irq2");

// To write to this net, use ppmWriteNet(handles.trg2, value);

    handles.trg2 = ppmOpenNetPort("trg2");

// To write to this net, use ppmWriteNet(handles.irq3, value);

    handles.irq3 = ppmOpenNetPort("irq3");

// To write to this net, use ppmWriteNet(handles.trg3, value);

    handles.trg3 = ppmOpenNetPort("trg3");

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.TFLG3.value = 0x0;
        bport1_ab_data.TCTRL3.value = 0x0;
        bport1_ab_data.CVAL3.value = 0x0;
        bport1_ab_data.LDVAL3.value = 0x0;
        bport1_ab_data.TFLG2.value = 0x0;
        bport1_ab_data.TCTRL2.value = 0x0;
        bport1_ab_data.CVAL2.value = 0x0;
        bport1_ab_data.LDVAL2.value = 0x0;
        bport1_ab_data.TFLG1.value = 0x0;
        bport1_ab_data.TCTRL1.value = 0x0;
        bport1_ab_data.CVAL1.value = 0x0;
        bport1_ab_data.LDVAL1.value = 0x0;
        bport1_ab_data.TFLG0.value = 0x0;
        bport1_ab_data.TCTRL0.value = 0x0;
        bport1_ab_data.CVAL0.value = 0x0;
        bport1_ab_data.LDVAL0.value = 0x0;
        bport1_ab_data.MCR.value = 0x2;
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

