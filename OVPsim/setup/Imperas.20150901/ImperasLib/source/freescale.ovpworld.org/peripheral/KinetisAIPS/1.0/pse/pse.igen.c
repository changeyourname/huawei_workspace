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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisAIPS", "Example");
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

static PPM_WRITE_CB(bport1_ab_MPRA_maskWrite) {
    bport1_ab_data.MPRA.value = (bport1_ab_data.MPRA.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRA_maskWrite) {
    bport1_ab_data.PACRA.value = (bport1_ab_data.PACRA.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRB_maskWrite) {
    bport1_ab_data.PACRB.value = (bport1_ab_data.PACRB.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRC_maskWrite) {
    bport1_ab_data.PACRC.value = (bport1_ab_data.PACRC.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRD_maskWrite) {
    bport1_ab_data.PACRD.value = (bport1_ab_data.PACRD.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRE_maskWrite) {
    bport1_ab_data.PACRE.value = (bport1_ab_data.PACRE.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRF_maskWrite) {
    bport1_ab_data.PACRF.value = (bport1_ab_data.PACRF.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRG_maskWrite) {
    bport1_ab_data.PACRG.value = (bport1_ab_data.PACRG.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRH_maskWrite) {
    bport1_ab_data.PACRH.value = (bport1_ab_data.PACRH.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRI_maskWrite) {
    bport1_ab_data.PACRI.value = (bport1_ab_data.PACRI.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRJ_maskWrite) {
    bport1_ab_data.PACRJ.value = (bport1_ab_data.PACRJ.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRK_maskWrite) {
    bport1_ab_data.PACRK.value = (bport1_ab_data.PACRK.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRL_maskWrite) {
    bport1_ab_data.PACRL.value = (bport1_ab_data.PACRL.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRM_maskWrite) {
    bport1_ab_data.PACRM.value = (bport1_ab_data.PACRM.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRN_maskWrite) {
    bport1_ab_data.PACRN.value = (bport1_ab_data.PACRN.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRO_maskWrite) {
    bport1_ab_data.PACRO.value = (bport1_ab_data.PACRO.value & 0x88888888) | (data & 0x77777777);
}

static PPM_WRITE_CB(bport1_ab_PACRP_maskWrite) {
    bport1_ab_data.PACRP.value = (bport1_ab_data.PACRP.value & 0x88888888) | (data & 0x77777777);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_MPRA",
        "Master Privilege Register A, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_MPRA_maskWrite,
        view32,
        &(bport1_ab_data.MPRA.value),
        True
    );
    ppmCreateRegister("ab_PACRA",
        "Peripheral Access Control Register, offset: 0x20 ",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_PACRA_maskWrite,
        view32,
        &(bport1_ab_data.PACRA.value),
        True
    );
    ppmCreateRegister("ab_PACRB",
        "Peripheral Access Control Register, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_PACRB_maskWrite,
        view32,
        &(bport1_ab_data.PACRB.value),
        True
    );
    ppmCreateRegister("ab_PACRC",
        "Peripheral Access Control Register, offset: 0x28 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_PACRC_maskWrite,
        view32,
        &(bport1_ab_data.PACRC.value),
        True
    );
    ppmCreateRegister("ab_PACRD",
        "Peripheral Access Control Register, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_PACRD_maskWrite,
        view32,
        &(bport1_ab_data.PACRD.value),
        True
    );
    ppmCreateRegister("ab_PACRE",
        "Peripheral Access Control Register, offset: 0x40 ",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_PACRE_maskWrite,
        view32,
        &(bport1_ab_data.PACRE.value),
        True
    );
    ppmCreateRegister("ab_PACRF",
        "Peripheral Access Control Register, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_PACRF_maskWrite,
        view32,
        &(bport1_ab_data.PACRF.value),
        True
    );
    ppmCreateRegister("ab_PACRG",
        "Peripheral Access Control Register, offset: 0x48 ",
        handles.bport1,
        72,
        4,
        read_32,
        bport1_ab_PACRG_maskWrite,
        view32,
        &(bport1_ab_data.PACRG.value),
        True
    );
    ppmCreateRegister("ab_PACRH",
        "Peripheral Access Control Register, offset: 0x4C ",
        handles.bport1,
        76,
        4,
        read_32,
        bport1_ab_PACRH_maskWrite,
        view32,
        &(bport1_ab_data.PACRH.value),
        True
    );
    ppmCreateRegister("ab_PACRI",
        "Peripheral Access Control Register, offset: 0x50 ",
        handles.bport1,
        80,
        4,
        read_32,
        bport1_ab_PACRI_maskWrite,
        view32,
        &(bport1_ab_data.PACRI.value),
        True
    );
    ppmCreateRegister("ab_PACRJ",
        "Peripheral Access Control Register, offset: 0x54 ",
        handles.bport1,
        84,
        4,
        read_32,
        bport1_ab_PACRJ_maskWrite,
        view32,
        &(bport1_ab_data.PACRJ.value),
        True
    );
    ppmCreateRegister("ab_PACRK",
        "Peripheral Access Control Register, offset: 0x58 ",
        handles.bport1,
        88,
        4,
        read_32,
        bport1_ab_PACRK_maskWrite,
        view32,
        &(bport1_ab_data.PACRK.value),
        True
    );
    ppmCreateRegister("ab_PACRL",
        "Peripheral Access Control Register, offset: 0x5C ",
        handles.bport1,
        92,
        4,
        read_32,
        bport1_ab_PACRL_maskWrite,
        view32,
        &(bport1_ab_data.PACRL.value),
        True
    );
    ppmCreateRegister("ab_PACRM",
        "Peripheral Access Control Register, offset: 0x60 ",
        handles.bport1,
        96,
        4,
        read_32,
        bport1_ab_PACRM_maskWrite,
        view32,
        &(bport1_ab_data.PACRM.value),
        True
    );
    ppmCreateRegister("ab_PACRN",
        "Peripheral Access Control Register, offset: 0x64 ",
        handles.bport1,
        100,
        4,
        read_32,
        bport1_ab_PACRN_maskWrite,
        view32,
        &(bport1_ab_data.PACRN.value),
        True
    );
    ppmCreateRegister("ab_PACRO",
        "Peripheral Access Control Register, offset: 0x68 ",
        handles.bport1,
        104,
        4,
        read_32,
        bport1_ab_PACRO_maskWrite,
        view32,
        &(bport1_ab_data.PACRO.value),
        True
    );
    ppmCreateRegister("ab_PACRP",
        "Peripheral Access Control Register, offset: 0x6C ",
        handles.bport1,
        108,
        4,
        read_32,
        bport1_ab_PACRP_maskWrite,
        view32,
        &(bport1_ab_data.PACRP.value),
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
        bport1_ab_data.PACRP.value = 0x0;
        bport1_ab_data.PACRO.value = 0x0;
        bport1_ab_data.PACRN.value = 0x0;
        bport1_ab_data.PACRM.value = 0x0;
        bport1_ab_data.PACRL.value = 0x0;
        bport1_ab_data.PACRK.value = 0x0;
        bport1_ab_data.PACRJ.value = 0x0;
        bport1_ab_data.PACRI.value = 0x0;
        bport1_ab_data.PACRH.value = 0x0;
        bport1_ab_data.PACRG.value = 0x0;
        bport1_ab_data.PACRF.value = 0x0;
        bport1_ab_data.PACRE.value = 0x0;
        bport1_ab_data.PACRD.value = 0x44444444;
        bport1_ab_data.PACRC.value = 0x44444444;
        bport1_ab_data.PACRB.value = 0x44444444;
        bport1_ab_data.PACRA.value = 0x44444444;
        bport1_ab_data.MPRA.value = 0x0;
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

