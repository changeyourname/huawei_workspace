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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisPDB", "Example");
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

static PPM_WRITE_CB(bport1_ab_CH0C1_maskWrite) {
    bport1_ab_data.CH0C1.value = (bport1_ab_data.CH0C1.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_CH0DLY0_maskWrite) {
    bport1_ab_data.CH0DLY0.value = (bport1_ab_data.CH0DLY0.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH0DLY1_maskWrite) {
    bport1_ab_data.CH0DLY1.value = (bport1_ab_data.CH0DLY1.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH0S_maskWrite) {
    bport1_ab_data.CH0S.value = (bport1_ab_data.CH0S.value & 0xff00ff00) | (data & 0xff00ff);
}

static PPM_WRITE_CB(bport1_ab_CH1C1_maskWrite) {
    bport1_ab_data.CH1C1.value = (bport1_ab_data.CH1C1.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_CH1DLY0_maskWrite) {
    bport1_ab_data.CH1DLY0.value = (bport1_ab_data.CH1DLY0.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH1DLY1_maskWrite) {
    bport1_ab_data.CH1DLY1.value = (bport1_ab_data.CH1DLY1.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH1S_maskWrite) {
    bport1_ab_data.CH1S.value = (bport1_ab_data.CH1S.value & 0xff00ff00) | (data & 0xff00ff);
}

static PPM_WRITE_CB(bport1_ab_CH2C1_maskWrite) {
    bport1_ab_data.CH2C1.value = (bport1_ab_data.CH2C1.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_CH2DLY0_maskWrite) {
    bport1_ab_data.CH2DLY0.value = (bport1_ab_data.CH2DLY0.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH2DLY1_maskWrite) {
    bport1_ab_data.CH2DLY1.value = (bport1_ab_data.CH2DLY1.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH2S_maskWrite) {
    bport1_ab_data.CH2S.value = (bport1_ab_data.CH2S.value & 0xff00ff00) | (data & 0xff00ff);
}

static PPM_WRITE_CB(bport1_ab_CH3C1_maskWrite) {
    bport1_ab_data.CH3C1.value = (bport1_ab_data.CH3C1.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_CH3DLY0_maskWrite) {
    bport1_ab_data.CH3DLY0.value = (bport1_ab_data.CH3DLY0.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH3DLY1_maskWrite) {
    bport1_ab_data.CH3DLY1.value = (bport1_ab_data.CH3DLY1.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CH3S_maskWrite) {
    bport1_ab_data.CH3S.value = (bport1_ab_data.CH3S.value & 0xff00ff00) | (data & 0xff00ff);
}

static PPM_WRITE_CB(bport1_ab_DACINT0_maskWrite) {
    bport1_ab_data.DACINT0.value = (bport1_ab_data.DACINT0.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_DACINT1_maskWrite) {
    bport1_ab_data.DACINT1.value = (bport1_ab_data.DACINT1.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_DACINTC0_maskWrite) {
    bport1_ab_data.DACINTC0.value = (bport1_ab_data.DACINTC0.value & 0xfffffffc) | (data & 0x3);
}

static PPM_WRITE_CB(bport1_ab_DACINTC1_maskWrite) {
    bport1_ab_data.DACINTC1.value = (bport1_ab_data.DACINTC1.value & 0xfffffffc) | (data & 0x3);
}

static PPM_WRITE_CB(bport1_ab_IDLY_maskWrite) {
    bport1_ab_data.IDLY.value = (bport1_ab_data.IDLY.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_MOD_maskWrite) {
    bport1_ab_data.MOD.value = (bport1_ab_data.MOD.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_PO0DLY_maskWrite) {
    bport1_ab_data.PO0DLY.value = (bport1_ab_data.PO0DLY.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_PO1DLY_maskWrite) {
    bport1_ab_data.PO1DLY.value = (bport1_ab_data.PO1DLY.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_PO2DLY_maskWrite) {
    bport1_ab_data.PO2DLY.value = (bport1_ab_data.PO2DLY.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_PO3DLY_maskWrite) {
    bport1_ab_data.PO3DLY.value = (bport1_ab_data.PO3DLY.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_POEN_maskWrite) {
    bport1_ab_data.POEN.value = (bport1_ab_data.POEN.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_SC_maskWrite) {
    bport1_ab_data.SC.value = (bport1_ab_data.SC.value & 0xfff00010) | (data & 0xfffef);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_SC",
        "Status and Control Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_SC_maskWrite,
        view32,
        &(bport1_ab_data.SC.value),
        True
    );
    ppmCreateRegister("ab_MOD",
        "Modulus Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_MOD_maskWrite,
        view32,
        &(bport1_ab_data.MOD.value),
        True
    );
    ppmCreateRegister("ab_CNT",
        "Counter Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CNT.value),
        True
    );
    ppmCreateRegister("ab_IDLY",
        "Interrupt Delay Register, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_IDLY_maskWrite,
        view32,
        &(bport1_ab_data.IDLY.value),
        True
    );
    ppmCreateRegister("ab_CH0C1",
        "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_CH0C1_maskWrite,
        view32,
        &(bport1_ab_data.CH0C1.value),
        True
    );
    ppmCreateRegister("ab_CH0S",
        "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_CH0S_maskWrite,
        view32,
        &(bport1_ab_data.CH0S.value),
        True
    );
    ppmCreateRegister("ab_CH0DLY0",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_CH0DLY0_maskWrite,
        view32,
        &(bport1_ab_data.CH0DLY0.value),
        True
    );
    ppmCreateRegister("ab_CH0DLY1",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_CH0DLY1_maskWrite,
        view32,
        &(bport1_ab_data.CH0DLY1.value),
        True
    );
    ppmCreateRegister("ab_CH1C1",
        "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_CH1C1_maskWrite,
        view32,
        &(bport1_ab_data.CH1C1.value),
        True
    );
    ppmCreateRegister("ab_CH1S",
        "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
        handles.bport1,
        60,
        4,
        read_32,
        bport1_ab_CH1S_maskWrite,
        view32,
        &(bport1_ab_data.CH1S.value),
        True
    );
    ppmCreateRegister("ab_CH1DLY0",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_CH1DLY0_maskWrite,
        view32,
        &(bport1_ab_data.CH1DLY0.value),
        True
    );
    ppmCreateRegister("ab_CH1DLY1",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_CH1DLY1_maskWrite,
        view32,
        &(bport1_ab_data.CH1DLY1.value),
        True
    );
    ppmCreateRegister("ab_CH2C1",
        "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
        handles.bport1,
        96,
        4,
        read_32,
        bport1_ab_CH2C1_maskWrite,
        view32,
        &(bport1_ab_data.CH2C1.value),
        True
    );
    ppmCreateRegister("ab_CH2S",
        "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
        handles.bport1,
        100,
        4,
        read_32,
        bport1_ab_CH2S_maskWrite,
        view32,
        &(bport1_ab_data.CH2S.value),
        True
    );
    ppmCreateRegister("ab_CH2DLY0",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        104,
        4,
        read_32,
        bport1_ab_CH2DLY0_maskWrite,
        view32,
        &(bport1_ab_data.CH2DLY0.value),
        True
    );
    ppmCreateRegister("ab_CH2DLY1",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        108,
        4,
        read_32,
        bport1_ab_CH2DLY1_maskWrite,
        view32,
        &(bport1_ab_data.CH2DLY1.value),
        True
    );
    ppmCreateRegister("ab_CH3C1",
        "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
        handles.bport1,
        136,
        4,
        read_32,
        bport1_ab_CH3C1_maskWrite,
        view32,
        &(bport1_ab_data.CH3C1.value),
        True
    );
    ppmCreateRegister("ab_CH3S",
        "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
        handles.bport1,
        140,
        4,
        read_32,
        bport1_ab_CH3S_maskWrite,
        view32,
        &(bport1_ab_data.CH3S.value),
        True
    );
    ppmCreateRegister("ab_CH3DLY0",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        144,
        4,
        read_32,
        bport1_ab_CH3DLY0_maskWrite,
        view32,
        &(bport1_ab_data.CH3DLY0.value),
        True
    );
    ppmCreateRegister("ab_CH3DLY1",
        "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
        handles.bport1,
        148,
        4,
        read_32,
        bport1_ab_CH3DLY1_maskWrite,
        view32,
        &(bport1_ab_data.CH3DLY1.value),
        True
    );
    ppmCreateRegister("ab_DACINTC0",
        "DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 ",
        handles.bport1,
        336,
        4,
        read_32,
        bport1_ab_DACINTC0_maskWrite,
        view32,
        &(bport1_ab_data.DACINTC0.value),
        True
    );
    ppmCreateRegister("ab_DACINT0",
        "DAC Interval n Register, array offset: 0x154, array step: 0x8 ",
        handles.bport1,
        340,
        4,
        read_32,
        bport1_ab_DACINT0_maskWrite,
        view32,
        &(bport1_ab_data.DACINT0.value),
        True
    );
    ppmCreateRegister("ab_DACINTC1",
        "DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 ",
        handles.bport1,
        344,
        4,
        read_32,
        bport1_ab_DACINTC1_maskWrite,
        view32,
        &(bport1_ab_data.DACINTC1.value),
        True
    );
    ppmCreateRegister("ab_DACINT1",
        "DAC Interval n Register, array offset: 0x154, array step: 0x8 ",
        handles.bport1,
        348,
        4,
        read_32,
        bport1_ab_DACINT1_maskWrite,
        view32,
        &(bport1_ab_data.DACINT1.value),
        True
    );
    ppmCreateRegister("ab_POEN",
        "Pulse-Out n Enable Register, offset: 0x190 ",
        handles.bport1,
        400,
        4,
        read_32,
        bport1_ab_POEN_maskWrite,
        view32,
        &(bport1_ab_data.POEN.value),
        True
    );
    ppmCreateRegister("ab_PO0DLY",
        "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
        handles.bport1,
        404,
        4,
        read_32,
        bport1_ab_PO0DLY_maskWrite,
        view32,
        &(bport1_ab_data.PO0DLY.value),
        True
    );
    ppmCreateRegister("ab_PO1DLY",
        "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
        handles.bport1,
        408,
        4,
        read_32,
        bport1_ab_PO1DLY_maskWrite,
        view32,
        &(bport1_ab_data.PO1DLY.value),
        True
    );
    ppmCreateRegister("ab_PO2DLY",
        "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
        handles.bport1,
        412,
        4,
        read_32,
        bport1_ab_PO2DLY_maskWrite,
        view32,
        &(bport1_ab_data.PO2DLY.value),
        True
    );
    ppmCreateRegister("ab_PO3DLY",
        "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
        handles.bport1,
        416,
        4,
        read_32,
        bport1_ab_PO3DLY_maskWrite,
        view32,
        &(bport1_ab_data.PO3DLY.value),
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
        bport1_ab_data.PO3DLY.value = 0x0;
        bport1_ab_data.PO2DLY.value = 0x0;
        bport1_ab_data.PO1DLY.value = 0x0;
        bport1_ab_data.PO0DLY.value = 0x0;
        bport1_ab_data.POEN.value = 0x0;
        bport1_ab_data.DACINT1.value = 0x0;
        bport1_ab_data.DACINTC1.value = 0x0;
        bport1_ab_data.DACINT0.value = 0x0;
        bport1_ab_data.DACINTC0.value = 0x0;
        bport1_ab_data.CH3DLY1.value = 0x0;
        bport1_ab_data.CH3DLY0.value = 0x0;
        bport1_ab_data.CH3S.value = 0x0;
        bport1_ab_data.CH3C1.value = 0x0;
        bport1_ab_data.CH2DLY1.value = 0x0;
        bport1_ab_data.CH2DLY0.value = 0x0;
        bport1_ab_data.CH2S.value = 0x0;
        bport1_ab_data.CH2C1.value = 0x0;
        bport1_ab_data.CH1DLY1.value = 0x0;
        bport1_ab_data.CH1DLY0.value = 0x0;
        bport1_ab_data.CH1S.value = 0x0;
        bport1_ab_data.CH1C1.value = 0x0;
        bport1_ab_data.CH0DLY1.value = 0x0;
        bport1_ab_data.CH0DLY0.value = 0x0;
        bport1_ab_data.CH0S.value = 0x0;
        bport1_ab_data.CH0C1.value = 0x0;
        bport1_ab_data.IDLY.value = 0xffff;
        bport1_ab_data.CNT.value = 0x0;
        bport1_ab_data.MOD.value = 0xffff;
        bport1_ab_data.SC.value = 0x0;
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

