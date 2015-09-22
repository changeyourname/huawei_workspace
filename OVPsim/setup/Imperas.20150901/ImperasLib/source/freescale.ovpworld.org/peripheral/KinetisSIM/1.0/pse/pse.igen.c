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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisSIM", "Example");
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

static PPM_WRITE_CB(bport1_ab_CLKDIV1_maskWrite) {
    bport1_ab_data.CLKDIV1.value = (bport1_ab_data.CLKDIV1.value & 0xffff) | (data & 0xffff0000);
}

static PPM_WRITE_CB(bport1_ab_CLKDIV2_maskWrite) {
    bport1_ab_data.CLKDIV2.value = (bport1_ab_data.CLKDIV2.value & 0xfffff0f0) | (data & 0xf0f);
}

static PPM_WRITE_CB(bport1_ab_CLKDIV4_maskWrite) {
    bport1_ab_data.CLKDIV4.value = (bport1_ab_data.CLKDIV4.value & 0xfffff0) | (data & 0xff00000f);
}

static PPM_WRITE_CB(bport1_ab_FCFG1_maskWrite) {
    bport1_ab_data.FCFG1.value = (bport1_ab_data.FCFG1.value & 0xfffffffe) | (data & 0x1);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & 0x1fffffff) | (data & 0xe0000000);
}

static PPM_WRITE_CB(bport1_ab_SCGC1_maskWrite) {
    bport1_ab_data.SCGC1.value = (bport1_ab_data.SCGC1.value & 0xfffff3df) | (data & 0xc20);
}

static PPM_WRITE_CB(bport1_ab_SCGC2_maskWrite) {
    bport1_ab_data.SCGC2.value = (bport1_ab_data.SCGC2.value & 0xffffcffe) | (data & 0x3001);
}

static PPM_WRITE_CB(bport1_ab_SCGC3_maskWrite) {
    bport1_ab_data.SCGC3.value = (bport1_ab_data.SCGC3.value & 0xe4fd6eee) | (data & 0x1b029111);
}

static PPM_WRITE_CB(bport1_ab_SCGC4_maskWrite) {
    bport1_ab_data.SCGC4.value = (bport1_ab_data.SCGC4.value & 0xefe3c339) | (data & 0x101c3cc6);
}

static PPM_WRITE_CB(bport1_ab_SCGC5_maskWrite) {
    bport1_ab_data.SCGC5.value = (bport1_ab_data.SCGC5.value & 0xffff81dc) | (data & 0x7e23);
}

static PPM_WRITE_CB(bport1_ab_SCGC6_maskWrite) {
    bport1_ab_data.SCGC6.value = (bport1_ab_data.SCGC6.value & 0xc40b4fe9) | (data & 0x3bf4b016);
}

static PPM_WRITE_CB(bport1_ab_SCGC7_maskWrite) {
    bport1_ab_data.SCGC7.value = (bport1_ab_data.SCGC7.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_SOPT1CFG_maskWrite) {
    bport1_ab_data.SOPT1CFG.value = (bport1_ab_data.SOPT1CFG.value & 0xf8ffffff) | (data & 0x7000000);
}

static PPM_WRITE_CB(bport1_ab_SOPT1_maskWrite) {
    bport1_ab_data.SOPT1.value = (bport1_ab_data.SOPT1.value & 0x1ff7ffff) | (data & 0xe0080000);
}

static PPM_WRITE_CB(bport1_ab_SOPT2_maskWrite) {
    bport1_ab_data.SOPT2.value = (bport1_ab_data.SOPT2.value & 0xf086403) | (data & 0xf0f79bfc);
}

static PPM_WRITE_CB(bport1_ab_SOPT4_maskWrite) {
    bport1_ab_data.SOPT4.value = (bport1_ab_data.SOPT4.value & 0xc3eee0) | (data & 0xff3c111f);
}

static PPM_WRITE_CB(bport1_ab_SOPT5_maskWrite) {
    bport1_ab_data.SOPT5.value = (bport1_ab_data.SOPT5.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_SOPT6_maskWrite) {
    bport1_ab_data.SOPT6.value = (bport1_ab_data.SOPT6.value & 0xfff00000) | (data & 0xfffff);
}

static PPM_WRITE_CB(bport1_ab_SOPT7_maskWrite) {
    bport1_ab_data.SOPT7.value = (bport1_ab_data.SOPT7.value & 0x60606060) | (data & 0x9f9f9f9f);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 8192);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_SOPT1",
        "System Options Register 1, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_SOPT1_maskWrite,
        view32,
        &(bport1_ab_data.SOPT1.value),
        True
    );
    ppmCreateRegister("ab_SOPT1CFG",
        "SOPT1 Configuration Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_SOPT1CFG_maskWrite,
        view32,
        &(bport1_ab_data.SOPT1CFG.value),
        True
    );
    ppmCreateRegister("ab_SOPT2",
        "System Options Register 2, offset: 0x1004 ",
        handles.bport1,
        4100,
        4,
        read_32,
        bport1_ab_SOPT2_maskWrite,
        view32,
        &(bport1_ab_data.SOPT2.value),
        True
    );
    ppmCreateRegister("ab_SOPT4",
        "System Options Register 4, offset: 0x100C ",
        handles.bport1,
        4108,
        4,
        read_32,
        bport1_ab_SOPT4_maskWrite,
        view32,
        &(bport1_ab_data.SOPT4.value),
        True
    );
    ppmCreateRegister("ab_SOPT5",
        "System Options Register 5, offset: 0x1010 ",
        handles.bport1,
        4112,
        4,
        read_32,
        bport1_ab_SOPT5_maskWrite,
        view32,
        &(bport1_ab_data.SOPT5.value),
        True
    );
    ppmCreateRegister("ab_SOPT6",
        "System Options Register 6, offset: 0x1014 ",
        handles.bport1,
        4116,
        4,
        read_32,
        bport1_ab_SOPT6_maskWrite,
        view32,
        &(bport1_ab_data.SOPT6.value),
        True
    );
    ppmCreateRegister("ab_SOPT7",
        "System Options Register 7, offset: 0x1018 ",
        handles.bport1,
        4120,
        4,
        read_32,
        bport1_ab_SOPT7_maskWrite,
        view32,
        &(bport1_ab_data.SOPT7.value),
        True
    );
    ppmCreateRegister("ab_SDID",
        "System Device Identification Register, offset: 0x1024 ",
        handles.bport1,
        4132,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.SDID.value),
        True
    );
    ppmCreateRegister("ab_SCGC1",
        "System Clock Gating Control Register 1, offset: 0x1028 ",
        handles.bport1,
        4136,
        4,
        read_32,
        bport1_ab_SCGC1_maskWrite,
        view32,
        &(bport1_ab_data.SCGC1.value),
        True
    );
    ppmCreateRegister("ab_SCGC2",
        "System Clock Gating Control Register 2, offset: 0x102C ",
        handles.bport1,
        4140,
        4,
        read_32,
        bport1_ab_SCGC2_maskWrite,
        view32,
        &(bport1_ab_data.SCGC2.value),
        True
    );
    ppmCreateRegister("ab_SCGC3",
        "System Clock Gating Control Register 3, offset: 0x1030 ",
        handles.bport1,
        4144,
        4,
        read_32,
        bport1_ab_SCGC3_maskWrite,
        view32,
        &(bport1_ab_data.SCGC3.value),
        True
    );
    ppmCreateRegister("ab_SCGC4",
        "System Clock Gating Control Register 4, offset: 0x1034 ",
        handles.bport1,
        4148,
        4,
        read_32,
        bport1_ab_SCGC4_maskWrite,
        view32,
        &(bport1_ab_data.SCGC4.value),
        True
    );
    ppmCreateRegister("ab_SCGC5",
        "System Clock Gating Control Register 5, offset: 0x1038 ",
        handles.bport1,
        4152,
        4,
        read_32,
        bport1_ab_SCGC5_maskWrite,
        view32,
        &(bport1_ab_data.SCGC5.value),
        True
    );
    ppmCreateRegister("ab_SCGC6",
        "System Clock Gating Control Register 6, offset: 0x103C ",
        handles.bport1,
        4156,
        4,
        read_32,
        bport1_ab_SCGC6_maskWrite,
        view32,
        &(bport1_ab_data.SCGC6.value),
        True
    );
    ppmCreateRegister("ab_SCGC7",
        "System Clock Gating Control Register 7, offset: 0x1040 ",
        handles.bport1,
        4160,
        4,
        read_32,
        bport1_ab_SCGC7_maskWrite,
        view32,
        &(bport1_ab_data.SCGC7.value),
        True
    );
    ppmCreateRegister("ab_CLKDIV1",
        "System Clock Divider Register 1, offset: 0x1044 ",
        handles.bport1,
        4164,
        4,
        read_32,
        bport1_ab_CLKDIV1_maskWrite,
        view32,
        &(bport1_ab_data.CLKDIV1.value),
        True
    );
    ppmCreateRegister("ab_CLKDIV2",
        "System Clock Divider Register 2, offset: 0x1048 ",
        handles.bport1,
        4168,
        4,
        read_32,
        bport1_ab_CLKDIV2_maskWrite,
        view32,
        &(bport1_ab_data.CLKDIV2.value),
        True
    );
    ppmCreateRegister("ab_FCFG1",
        "Flash Configuration Register 1, offset: 0x104C ",
        handles.bport1,
        4172,
        4,
        read_32,
        bport1_ab_FCFG1_maskWrite,
        view32,
        &(bport1_ab_data.FCFG1.value),
        True
    );
    ppmCreateRegister("ab_FCFG2",
        "Flash Configuration Register 2, offset: 0x1050 ",
        handles.bport1,
        4176,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.FCFG2.value),
        True
    );
    ppmCreateRegister("ab_UIDH",
        "Unique Identification Register High, offset: 0x1054 ",
        handles.bport1,
        4180,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.UIDH.value),
        True
    );
    ppmCreateRegister("ab_UIDMH",
        "Unique Identification Register Mid-High, offset: 0x1058 ",
        handles.bport1,
        4184,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.UIDMH.value),
        True
    );
    ppmCreateRegister("ab_UIDML",
        "Unique Identification Register Mid Low, offset: 0x105C ",
        handles.bport1,
        4188,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.UIDML.value),
        True
    );
    ppmCreateRegister("ab_UIDL",
        "Unique Identification Register Low, offset: 0x1060 ",
        handles.bport1,
        4192,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.UIDL.value),
        True
    );
    ppmCreateRegister("ab_CLKDIV4",
        "System Clock Divider Register 4, offset: 0x1068 ",
        handles.bport1,
        4200,
        4,
        read_32,
        bport1_ab_CLKDIV4_maskWrite,
        view32,
        &(bport1_ab_data.CLKDIV4.value),
        True
    );
    ppmCreateRegister("ab_MCR",
        "Misc Control Register, offset: 0x106C ",
        handles.bport1,
        4204,
        4,
        read_32,
        bport1_ab_MCR_maskWrite,
        view32,
        &(bport1_ab_data.MCR.value),
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
        bport1_ab_data.MCR.value = 0x0;
        bport1_ab_data.CLKDIV4.value = 0x2;
        bport1_ab_data.FCFG2.value = 0x0;
        bport1_ab_data.FCFG1.value = 0x0;
        bport1_ab_data.CLKDIV2.value = 0x0;
        bport1_ab_data.CLKDIV1.value = 0x0;
        bport1_ab_data.SCGC7.value = 0x7;
        bport1_ab_data.SCGC6.value = 0x40000001;
        bport1_ab_data.SCGC5.value = 0x40180;
        bport1_ab_data.SCGC4.value = 0xf0100030;
        bport1_ab_data.SCGC3.value = 0x0;
        bport1_ab_data.SCGC2.value = 0x0;
        bport1_ab_data.SCGC1.value = 0x0;
        bport1_ab_data.SDID.value = 0x180;
        bport1_ab_data.SOPT7.value = 0x0;
        bport1_ab_data.SOPT6.value = 0x0;
        bport1_ab_data.SOPT5.value = 0x0;
        bport1_ab_data.SOPT4.value = 0x0;
        bport1_ab_data.SOPT2.value = 0x44001004;
        bport1_ab_data.SOPT1CFG.value = 0x0;
        bport1_ab_data.SOPT1.value = 0x10009000;
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

