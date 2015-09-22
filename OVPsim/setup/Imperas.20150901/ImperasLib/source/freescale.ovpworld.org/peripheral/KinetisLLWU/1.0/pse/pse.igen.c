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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisLLWU", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_F1_maskWrite) {
    bport1_ab_data.F1.value = (bport1_ab_data.F1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_F2_maskWrite) {
    bport1_ab_data.F2.value = (bport1_ab_data.F2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FILT1_maskWrite) {
    bport1_ab_data.FILT1.value = (bport1_ab_data.FILT1.value & 0x10) | (data & 0xef);
}

static PPM_WRITE_CB(bport1_ab_FILT2_maskWrite) {
    bport1_ab_data.FILT2.value = (bport1_ab_data.FILT2.value & 0x10) | (data & 0xef);
}

static PPM_WRITE_CB(bport1_ab_ME_maskWrite) {
    bport1_ab_data.ME.value = (bport1_ab_data.ME.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_PE1_maskWrite) {
    bport1_ab_data.PE1.value = (bport1_ab_data.PE1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_PE2_maskWrite) {
    bport1_ab_data.PE2.value = (bport1_ab_data.PE2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_PE3_maskWrite) {
    bport1_ab_data.PE3.value = (bport1_ab_data.PE3.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_PE4_maskWrite) {
    bport1_ab_data.PE4.value = (bport1_ab_data.PE4.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_RST_maskWrite) {
    bport1_ab_data.RST.value = (bport1_ab_data.RST.value & 0xfc) | (data & 0x3);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_PE1",
        "LLWU Pin Enable 1 Register, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_PE1_maskWrite,
        view8,
        &(bport1_ab_data.PE1.value),
        True
    );
    ppmCreateRegister("ab_PE2",
        "LLWU Pin Enable 2 Register, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_PE2_maskWrite,
        view8,
        &(bport1_ab_data.PE2.value),
        True
    );
    ppmCreateRegister("ab_PE3",
        "LLWU Pin Enable 3 Register, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_PE3_maskWrite,
        view8,
        &(bport1_ab_data.PE3.value),
        True
    );
    ppmCreateRegister("ab_PE4",
        "LLWU Pin Enable 4 Register, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        bport1_ab_PE4_maskWrite,
        view8,
        &(bport1_ab_data.PE4.value),
        True
    );
    ppmCreateRegister("ab_ME",
        "LLWU Module Enable Register, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_ME_maskWrite,
        view8,
        &(bport1_ab_data.ME.value),
        True
    );
    ppmCreateRegister("ab_F1",
        "LLWU Flag 1 Register, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_F1_maskWrite,
        view8,
        &(bport1_ab_data.F1.value),
        True
    );
    ppmCreateRegister("ab_F2",
        "LLWU Flag 2 Register, offset: 0x6 ",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_F2_maskWrite,
        view8,
        &(bport1_ab_data.F2.value),
        True
    );
    ppmCreateRegister("ab_F3",
        "LLWU Flag 3 Register, offset: 0x7 ",
        handles.bport1,
        7,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.F3.value),
        True
    );
    ppmCreateRegister("ab_FILT1",
        "LLWU Pin Filter 1 Register, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_FILT1_maskWrite,
        view8,
        &(bport1_ab_data.FILT1.value),
        True
    );
    ppmCreateRegister("ab_FILT2",
        "LLWU Pin Filter 2 Register, offset: 0x9 ",
        handles.bport1,
        9,
        1,
        read_8,
        bport1_ab_FILT2_maskWrite,
        view8,
        &(bport1_ab_data.FILT2.value),
        True
    );
    ppmCreateRegister("ab_RST",
        "LLWU Reset Enable Register, offset: 0xA ",
        handles.bport1,
        10,
        1,
        read_8,
        bport1_ab_RST_maskWrite,
        view8,
        &(bport1_ab_data.RST.value),
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
        bport1_ab_data.RST.value = 0x2;
        bport1_ab_data.FILT2.value = 0x0;
        bport1_ab_data.FILT1.value = 0x0;
        bport1_ab_data.F3.value = 0x0;
        bport1_ab_data.F2.value = 0x0;
        bport1_ab_data.F1.value = 0x0;
        bport1_ab_data.ME.value = 0x0;
        bport1_ab_data.PE4.value = 0x0;
        bport1_ab_data.PE3.value = 0x0;
        bport1_ab_data.PE2.value = 0x0;
        bport1_ab_data.PE1.value = 0x0;
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

