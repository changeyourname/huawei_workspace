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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisAXBS", "Example");
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

static PPM_WRITE_CB(bport1_ab_CRS0_maskWrite) {
    bport1_ab_data.CRS0.value = (bport1_ab_data.CRS0.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS1_maskWrite) {
    bport1_ab_data.CRS1.value = (bport1_ab_data.CRS1.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS2_maskWrite) {
    bport1_ab_data.CRS2.value = (bport1_ab_data.CRS2.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS3_maskWrite) {
    bport1_ab_data.CRS3.value = (bport1_ab_data.CRS3.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS4_maskWrite) {
    bport1_ab_data.CRS4.value = (bport1_ab_data.CRS4.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS5_maskWrite) {
    bport1_ab_data.CRS5.value = (bport1_ab_data.CRS5.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS6_maskWrite) {
    bport1_ab_data.CRS6.value = (bport1_ab_data.CRS6.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_CRS7_maskWrite) {
    bport1_ab_data.CRS7.value = (bport1_ab_data.CRS7.value & 0xfffffcc8) | (data & 0x337);
}

static PPM_WRITE_CB(bport1_ab_MGPCR0_maskWrite) {
    bport1_ab_data.MGPCR0.value = (bport1_ab_data.MGPCR0.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_MGPCR1_maskWrite) {
    bport1_ab_data.MGPCR1.value = (bport1_ab_data.MGPCR1.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_MGPCR2_maskWrite) {
    bport1_ab_data.MGPCR2.value = (bport1_ab_data.MGPCR2.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_MGPCR3_maskWrite) {
    bport1_ab_data.MGPCR3.value = (bport1_ab_data.MGPCR3.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_MGPCR6_maskWrite) {
    bport1_ab_data.MGPCR6.value = (bport1_ab_data.MGPCR6.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_MGPCR7_maskWrite) {
    bport1_ab_data.MGPCR7.value = (bport1_ab_data.MGPCR7.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_PRS0_maskWrite) {
    bport1_ab_data.PRS0.value = (bport1_ab_data.PRS0.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS1_maskWrite) {
    bport1_ab_data.PRS1.value = (bport1_ab_data.PRS1.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS2_maskWrite) {
    bport1_ab_data.PRS2.value = (bport1_ab_data.PRS2.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS3_maskWrite) {
    bport1_ab_data.PRS3.value = (bport1_ab_data.PRS3.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS4_maskWrite) {
    bport1_ab_data.PRS4.value = (bport1_ab_data.PRS4.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS5_maskWrite) {
    bport1_ab_data.PRS5.value = (bport1_ab_data.PRS5.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS6_maskWrite) {
    bport1_ab_data.PRS6.value = (bport1_ab_data.PRS6.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PRS7_maskWrite) {
    bport1_ab_data.PRS7.value = (bport1_ab_data.PRS7.value & 0x88888888) | (data & 0x77777777);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_PRS0",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_PRS0_maskWrite,
        view32,
        &(bport1_ab_data.PRS0.value),
        True
    );
    ppmCreateRegister("ab_CRS0",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_CRS0_maskWrite,
        view32,
        &(bport1_ab_data.CRS0.value),
        True
    );
    ppmCreateRegister("ab_PRS1",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        256,
        4,
        read_32,
        bport1_ab_PRS1_maskWrite,
        view32,
        &(bport1_ab_data.PRS1.value),
        True
    );
    ppmCreateRegister("ab_CRS1",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        272,
        4,
        read_32,
        bport1_ab_CRS1_maskWrite,
        view32,
        &(bport1_ab_data.CRS1.value),
        True
    );
    ppmCreateRegister("ab_PRS2",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        512,
        4,
        read_32,
        bport1_ab_PRS2_maskWrite,
        view32,
        &(bport1_ab_data.PRS2.value),
        True
    );
    ppmCreateRegister("ab_CRS2",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        528,
        4,
        read_32,
        bport1_ab_CRS2_maskWrite,
        view32,
        &(bport1_ab_data.CRS2.value),
        True
    );
    ppmCreateRegister("ab_PRS3",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        768,
        4,
        read_32,
        bport1_ab_PRS3_maskWrite,
        view32,
        &(bport1_ab_data.PRS3.value),
        True
    );
    ppmCreateRegister("ab_CRS3",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        784,
        4,
        read_32,
        bport1_ab_CRS3_maskWrite,
        view32,
        &(bport1_ab_data.CRS3.value),
        True
    );
    ppmCreateRegister("ab_PRS4",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        1024,
        4,
        read_32,
        bport1_ab_PRS4_maskWrite,
        view32,
        &(bport1_ab_data.PRS4.value),
        True
    );
    ppmCreateRegister("ab_CRS4",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        1040,
        4,
        read_32,
        bport1_ab_CRS4_maskWrite,
        view32,
        &(bport1_ab_data.CRS4.value),
        True
    );
    ppmCreateRegister("ab_PRS5",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        1280,
        4,
        read_32,
        bport1_ab_PRS5_maskWrite,
        view32,
        &(bport1_ab_data.PRS5.value),
        True
    );
    ppmCreateRegister("ab_CRS5",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        1296,
        4,
        read_32,
        bport1_ab_CRS5_maskWrite,
        view32,
        &(bport1_ab_data.CRS5.value),
        True
    );
    ppmCreateRegister("ab_PRS6",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        1536,
        4,
        read_32,
        bport1_ab_PRS6_maskWrite,
        view32,
        &(bport1_ab_data.PRS6.value),
        True
    );
    ppmCreateRegister("ab_CRS6",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        1552,
        4,
        read_32,
        bport1_ab_CRS6_maskWrite,
        view32,
        &(bport1_ab_data.CRS6.value),
        True
    );
    ppmCreateRegister("ab_PRS7",
        "Priority Registers Slave, array offset: 0x0, array step: 0x100 ",
        handles.bport1,
        1792,
        4,
        read_32,
        bport1_ab_PRS7_maskWrite,
        view32,
        &(bport1_ab_data.PRS7.value),
        True
    );
    ppmCreateRegister("ab_CRS7",
        "Control Register, array offset: 0x10, array step: 0x100 ",
        handles.bport1,
        1808,
        4,
        read_32,
        bport1_ab_CRS7_maskWrite,
        view32,
        &(bport1_ab_data.CRS7.value),
        True
    );
    ppmCreateRegister("ab_MGPCR0",
        "Master General Purpose Control Register, offset: 0x800 ",
        handles.bport1,
        2048,
        4,
        read_32,
        bport1_ab_MGPCR0_maskWrite,
        view32,
        &(bport1_ab_data.MGPCR0.value),
        True
    );
    ppmCreateRegister("ab_MGPCR1",
        "Master General Purpose Control Register, offset: 0x900 ",
        handles.bport1,
        2304,
        4,
        read_32,
        bport1_ab_MGPCR1_maskWrite,
        view32,
        &(bport1_ab_data.MGPCR1.value),
        True
    );
    ppmCreateRegister("ab_MGPCR2",
        "Master General Purpose Control Register, offset: 0xA00 ",
        handles.bport1,
        2560,
        4,
        read_32,
        bport1_ab_MGPCR2_maskWrite,
        view32,
        &(bport1_ab_data.MGPCR2.value),
        True
    );
    ppmCreateRegister("ab_MGPCR3",
        "Master General Purpose Control Register, offset: 0xB00 ",
        handles.bport1,
        2816,
        4,
        read_32,
        bport1_ab_MGPCR3_maskWrite,
        view32,
        &(bport1_ab_data.MGPCR3.value),
        True
    );
    ppmCreateRegister("ab_MGPCR6",
        "Master General Purpose Control Register, offset: 0xE00 ",
        handles.bport1,
        3584,
        4,
        read_32,
        bport1_ab_MGPCR6_maskWrite,
        view32,
        &(bport1_ab_data.MGPCR6.value),
        True
    );
    ppmCreateRegister("ab_MGPCR7",
        "Master General Purpose Control Register, offset: 0xF00 ",
        handles.bport1,
        3840,
        4,
        read_32,
        bport1_ab_MGPCR7_maskWrite,
        view32,
        &(bport1_ab_data.MGPCR7.value),
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
        bport1_ab_data.MGPCR7.value = 0x0;
        bport1_ab_data.MGPCR6.value = 0x0;
        bport1_ab_data.MGPCR3.value = 0x0;
        bport1_ab_data.MGPCR2.value = 0x0;
        bport1_ab_data.MGPCR1.value = 0x0;
        bport1_ab_data.MGPCR0.value = 0x0;
        bport1_ab_data.CRS7.value = 0x0;
        bport1_ab_data.PRS7.value = 0x76543210;
        bport1_ab_data.CRS6.value = 0x0;
        bport1_ab_data.PRS6.value = 0x76543210;
        bport1_ab_data.CRS5.value = 0x0;
        bport1_ab_data.PRS5.value = 0x76543210;
        bport1_ab_data.CRS4.value = 0x0;
        bport1_ab_data.PRS4.value = 0x76543210;
        bport1_ab_data.CRS3.value = 0x0;
        bport1_ab_data.PRS3.value = 0x76543210;
        bport1_ab_data.CRS2.value = 0x0;
        bport1_ab_data.PRS2.value = 0x76543210;
        bport1_ab_data.CRS1.value = 0x0;
        bport1_ab_data.PRS1.value = 0x76543210;
        bport1_ab_data.CRS0.value = 0x0;
        bport1_ab_data.PRS0.value = 0x76543210;
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

