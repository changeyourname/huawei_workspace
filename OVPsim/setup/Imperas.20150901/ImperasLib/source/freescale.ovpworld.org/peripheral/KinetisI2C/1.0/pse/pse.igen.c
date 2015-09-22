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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisI2C", "Example");
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

static PPM_WRITE_CB(bport1_ab_A1_maskWrite) {
    bport1_ab_data.A1.value = (bport1_ab_data.A1.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_A2_maskWrite) {
    bport1_ab_data.A2.value = (bport1_ab_data.A2.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C2_maskWrite) {
    bport1_ab_data.C2.value = (bport1_ab_data.C2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_D_maskWrite) {
    bport1_ab_data.D.value = (bport1_ab_data.D.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FLT_maskWrite) {
    bport1_ab_data.FLT.value = (bport1_ab_data.FLT.value & 0xe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_F_maskWrite) {
    bport1_ab_data.F.value = (bport1_ab_data.F.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_RA_maskWrite) {
    bport1_ab_data.RA.value = (bport1_ab_data.RA.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_SLTH_maskWrite) {
    bport1_ab_data.SLTH.value = (bport1_ab_data.SLTH.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_SLTL_maskWrite) {
    bport1_ab_data.SLTL.value = (bport1_ab_data.SLTL.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_SMB_maskWrite) {
    bport1_ab_data.SMB.value = (bport1_ab_data.SMB.value & 0x4) | (data & 0xfb);
}

static PPM_WRITE_CB(bport1_ab_S_maskWrite) {
    bport1_ab_data.S.value = (bport1_ab_data.S.value & 0xa9) | (data & 0x56);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_A1",
        "I2C Address Register 1, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_A1_maskWrite,
        view8,
        &(bport1_ab_data.A1.value),
        True
    );
    ppmCreateRegister("ab_F",
        "I2C Frequency Divider register, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_F_maskWrite,
        view8,
        &(bport1_ab_data.F.value),
        True
    );
    ppmCreateRegister("ab_C1",
        "I2C Control Register 1, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_C1_maskWrite,
        view8,
        &(bport1_ab_data.C1.value),
        True
    );
    ppmCreateRegister("ab_S",
        "I2C Status Register, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        bport1_ab_S_maskWrite,
        view8,
        &(bport1_ab_data.S.value),
        True
    );
    ppmCreateRegister("ab_D",
        "I2C Data I/O register, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_D_maskWrite,
        view8,
        &(bport1_ab_data.D.value),
        True
    );
    ppmCreateRegister("ab_C2",
        "I2C Control Register 2, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_C2_maskWrite,
        view8,
        &(bport1_ab_data.C2.value),
        True
    );
    ppmCreateRegister("ab_FLT",
        "I2C Programmable Input Glitch Filter register, offset: 0x6 ",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_FLT_maskWrite,
        view8,
        &(bport1_ab_data.FLT.value),
        True
    );
    ppmCreateRegister("ab_RA",
        "I2C Range Address register, offset: 0x7 ",
        handles.bport1,
        7,
        1,
        read_8,
        bport1_ab_RA_maskWrite,
        view8,
        &(bport1_ab_data.RA.value),
        True
    );
    ppmCreateRegister("ab_SMB",
        "I2C SMBus Control and Status register, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_SMB_maskWrite,
        view8,
        &(bport1_ab_data.SMB.value),
        True
    );
    ppmCreateRegister("ab_A2",
        "I2C Address Register 2, offset: 0x9 ",
        handles.bport1,
        9,
        1,
        read_8,
        bport1_ab_A2_maskWrite,
        view8,
        &(bport1_ab_data.A2.value),
        True
    );
    ppmCreateRegister("ab_SLTH",
        "I2C SCL Low Timeout Register High, offset: 0xA ",
        handles.bport1,
        10,
        1,
        read_8,
        bport1_ab_SLTH_maskWrite,
        view8,
        &(bport1_ab_data.SLTH.value),
        True
    );
    ppmCreateRegister("ab_SLTL",
        "I2C SCL Low Timeout Register Low, offset: 0xB ",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_SLTL_maskWrite,
        view8,
        &(bport1_ab_data.SLTL.value),
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
        bport1_ab_data.SLTL.value = 0x0;
        bport1_ab_data.SLTH.value = 0x0;
        bport1_ab_data.A2.value = 0xc2;
        bport1_ab_data.SMB.value = 0x0;
        bport1_ab_data.RA.value = 0x0;
        bport1_ab_data.FLT.value = 0x0;
        bport1_ab_data.C2.value = 0x0;
        bport1_ab_data.D.value = 0x0;
        bport1_ab_data.S.value = 0x80;
        bport1_ab_data.C1.value = 0x0;
        bport1_ab_data.F.value = 0x0;
        bport1_ab_data.A1.value = 0x0;
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

