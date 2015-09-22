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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisI2S", "Example");
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

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & 0xbcffffff) | (data & 0x43000000);
}

static PPM_WRITE_CB(bport1_ab_MDR_maskWrite) {
    bport1_ab_data.MDR.value = (bport1_ab_data.MDR.value & 0xfff00000) | (data & 0xfffff);
}

static PPM_WRITE_CB(bport1_ab_RCR1_maskWrite) {
    bport1_ab_data.RCR1.value = (bport1_ab_data.RCR1.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_RCR2_maskWrite) {
    bport1_ab_data.RCR2.value = (bport1_ab_data.RCR2.value & 0xffff00) | (data & 0xff0000ff);
}

static PPM_WRITE_CB(bport1_ab_RCR3_maskWrite) {
    bport1_ab_data.RCR3.value = (bport1_ab_data.RCR3.value & 0xfffcffe0) | (data & 0x3001f);
}

static PPM_WRITE_CB(bport1_ab_RCR4_maskWrite) {
    bport1_ab_data.RCR4.value = (bport1_ab_data.RCR4.value & 0xffe0e0e4) | (data & 0x1f1f1b);
}

static PPM_WRITE_CB(bport1_ab_RCR5_maskWrite) {
    bport1_ab_data.RCR5.value = (bport1_ab_data.RCR5.value & 0xe0e0e0ff) | (data & 0x1f1f1f00);
}

static PPM_WRITE_CB(bport1_ab_RCSR_maskWrite) {
    bport1_ab_data.RCSR.value = (bport1_ab_data.RCSR.value & 0xce3e0fc) | (data & 0xf31c1f03);
}

static PPM_WRITE_CB(bport1_ab_RMR_maskWrite) {
    bport1_ab_data.RMR.value = (bport1_ab_data.RMR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TCR1_maskWrite) {
    bport1_ab_data.TCR1.value = (bport1_ab_data.TCR1.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_TCR2_maskWrite) {
    bport1_ab_data.TCR2.value = (bport1_ab_data.TCR2.value & 0xffff00) | (data & 0xff0000ff);
}

static PPM_WRITE_CB(bport1_ab_TCR3_maskWrite) {
    bport1_ab_data.TCR3.value = (bport1_ab_data.TCR3.value & 0xfffcffe0) | (data & 0x3001f);
}

static PPM_WRITE_CB(bport1_ab_TCR4_maskWrite) {
    bport1_ab_data.TCR4.value = (bport1_ab_data.TCR4.value & 0xffe0e0e4) | (data & 0x1f1f1b);
}

static PPM_WRITE_CB(bport1_ab_TCR5_maskWrite) {
    bport1_ab_data.TCR5.value = (bport1_ab_data.TCR5.value & 0xe0e0e0ff) | (data & 0x1f1f1f00);
}

static PPM_WRITE_CB(bport1_ab_TCSR_maskWrite) {
    bport1_ab_data.TCSR.value = (bport1_ab_data.TCSR.value & 0xce3e0fc) | (data & 0xf31c1f03);
}

static PPM_WRITE_CB(bport1_ab_TDR0_maskWrite) {
    bport1_ab_data.TDR0.value = (bport1_ab_data.TDR0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TDR1_maskWrite) {
    bport1_ab_data.TDR1.value = (bport1_ab_data.TDR1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TMR_maskWrite) {
    bport1_ab_data.TMR.value = (bport1_ab_data.TMR.value & 0x0) | (data & 0xffffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_TCSR",
        "SAI Transmit Control Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_TCSR_maskWrite,
        view32,
        &(bport1_ab_data.TCSR.value),
        True
    );
    ppmCreateRegister("ab_TCR1",
        "SAI Transmit Configuration 1 Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_TCR1_maskWrite,
        view32,
        &(bport1_ab_data.TCR1.value),
        True
    );
    ppmCreateRegister("ab_TCR2",
        "SAI Transmit Configuration 2 Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_TCR2_maskWrite,
        view32,
        &(bport1_ab_data.TCR2.value),
        True
    );
    ppmCreateRegister("ab_TCR3",
        "SAI Transmit Configuration 3 Register, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_TCR3_maskWrite,
        view32,
        &(bport1_ab_data.TCR3.value),
        True
    );
    ppmCreateRegister("ab_TCR4",
        "SAI Transmit Configuration 4 Register, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_TCR4_maskWrite,
        view32,
        &(bport1_ab_data.TCR4.value),
        True
    );
    ppmCreateRegister("ab_TCR5",
        "SAI Transmit Configuration 5 Register, offset: 0x14 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_TCR5_maskWrite,
        view32,
        &(bport1_ab_data.TCR5.value),
        True
    );
    ppmCreateRegister("ab_TDR0",
        "SAI Transmit Data Register, array offset: 0x20, array step: 0x4 ",
        handles.bport1,
        32,
        4,
        0,
        bport1_ab_TDR0_maskWrite,
        view32,
        &(bport1_ab_data.TDR0.value),
        True
    );
    ppmCreateRegister("ab_TDR1",
        "SAI Transmit Data Register, array offset: 0x20, array step: 0x4 ",
        handles.bport1,
        36,
        4,
        0,
        bport1_ab_TDR1_maskWrite,
        view32,
        &(bport1_ab_data.TDR1.value),
        True
    );
    ppmCreateRegister("ab_TFR0",
        "SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 ",
        handles.bport1,
        64,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TFR0.value),
        True
    );
    ppmCreateRegister("ab_TFR1",
        "SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 ",
        handles.bport1,
        68,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TFR1.value),
        True
    );
    ppmCreateRegister("ab_TMR",
        "SAI Transmit Mask Register, offset: 0x60 ",
        handles.bport1,
        96,
        4,
        read_32,
        bport1_ab_TMR_maskWrite,
        view32,
        &(bport1_ab_data.TMR.value),
        True
    );
    ppmCreateRegister("ab_RCSR",
        "SAI Receive Control Register, offset: 0x80 ",
        handles.bport1,
        128,
        4,
        read_32,
        bport1_ab_RCSR_maskWrite,
        view32,
        &(bport1_ab_data.RCSR.value),
        True
    );
    ppmCreateRegister("ab_RCR1",
        "SAI Receive Configuration 1 Register, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        read_32,
        bport1_ab_RCR1_maskWrite,
        view32,
        &(bport1_ab_data.RCR1.value),
        True
    );
    ppmCreateRegister("ab_RCR2",
        "SAI Receive Configuration 2 Register, offset: 0x88 ",
        handles.bport1,
        136,
        4,
        read_32,
        bport1_ab_RCR2_maskWrite,
        view32,
        &(bport1_ab_data.RCR2.value),
        True
    );
    ppmCreateRegister("ab_RCR3",
        "SAI Receive Configuration 3 Register, offset: 0x8C ",
        handles.bport1,
        140,
        4,
        read_32,
        bport1_ab_RCR3_maskWrite,
        view32,
        &(bport1_ab_data.RCR3.value),
        True
    );
    ppmCreateRegister("ab_RCR4",
        "SAI Receive Configuration 4 Register, offset: 0x90 ",
        handles.bport1,
        144,
        4,
        read_32,
        bport1_ab_RCR4_maskWrite,
        view32,
        &(bport1_ab_data.RCR4.value),
        True
    );
    ppmCreateRegister("ab_RCR5",
        "SAI Receive Configuration 5 Register, offset: 0x94 ",
        handles.bport1,
        148,
        4,
        read_32,
        bport1_ab_RCR5_maskWrite,
        view32,
        &(bport1_ab_data.RCR5.value),
        True
    );
    ppmCreateRegister("ab_RDR0",
        "SAI Receive Data Register, array offset: 0xA0, array step: 0x4 ",
        handles.bport1,
        160,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RDR0.value),
        True
    );
    ppmCreateRegister("ab_RDR1",
        "SAI Receive Data Register, array offset: 0xA0, array step: 0x4 ",
        handles.bport1,
        164,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RDR1.value),
        True
    );
    ppmCreateRegister("ab_RFR0",
        "SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 ",
        handles.bport1,
        192,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RFR0.value),
        True
    );
    ppmCreateRegister("ab_RFR1",
        "SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 ",
        handles.bport1,
        196,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RFR1.value),
        True
    );
    ppmCreateRegister("ab_RMR",
        "SAI Receive Mask Register, offset: 0xE0 ",
        handles.bport1,
        224,
        4,
        read_32,
        bport1_ab_RMR_maskWrite,
        view32,
        &(bport1_ab_data.RMR.value),
        True
    );
    ppmCreateRegister("ab_MCR",
        "SAI MCLK Control Register, offset: 0x100 ",
        handles.bport1,
        256,
        4,
        read_32,
        bport1_ab_MCR_maskWrite,
        view32,
        &(bport1_ab_data.MCR.value),
        True
    );
    ppmCreateRegister("ab_MDR",
        "MCLK Divide Register, offset: 0x104 ",
        handles.bport1,
        260,
        4,
        read_32,
        bport1_ab_MDR_maskWrite,
        view32,
        &(bport1_ab_data.MDR.value),
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
        bport1_ab_data.MDR.value = 0x0;
        bport1_ab_data.MCR.value = 0x0;
        bport1_ab_data.RMR.value = 0x0;
        bport1_ab_data.RFR1.value = 0x0;
        bport1_ab_data.RFR0.value = 0x0;
        bport1_ab_data.RDR1.value = 0x0;
        bport1_ab_data.RDR0.value = 0x0;
        bport1_ab_data.RCR5.value = 0x0;
        bport1_ab_data.RCR4.value = 0x0;
        bport1_ab_data.RCR3.value = 0x0;
        bport1_ab_data.RCR2.value = 0x0;
        bport1_ab_data.RCR1.value = 0x0;
        bport1_ab_data.RCSR.value = 0x0;
        bport1_ab_data.TMR.value = 0x0;
        bport1_ab_data.TFR1.value = 0x0;
        bport1_ab_data.TFR0.value = 0x0;
        bport1_ab_data.TDR1.value = 0x0;
        bport1_ab_data.TDR0.value = 0x0;
        bport1_ab_data.TCR5.value = 0x0;
        bport1_ab_data.TCR4.value = 0x0;
        bport1_ab_data.TCR3.value = 0x0;
        bport1_ab_data.TCR2.value = 0x0;
        bport1_ab_data.TCR1.value = 0x0;
        bport1_ab_data.TCSR.value = 0x0;
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

