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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCMT", "Example");
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

static PPM_WRITE_CB(bport1_ab_CGH1_maskWrite) {
    bport1_ab_data.CGH1.value = (bport1_ab_data.CGH1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CGH2_maskWrite) {
    bport1_ab_data.CGH2.value = (bport1_ab_data.CGH2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CGL1_maskWrite) {
    bport1_ab_data.CGL1.value = (bport1_ab_data.CGL1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CGL2_maskWrite) {
    bport1_ab_data.CGL2.value = (bport1_ab_data.CGL2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CMD1_maskWrite) {
    bport1_ab_data.CMD1.value = (bport1_ab_data.CMD1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CMD2_maskWrite) {
    bport1_ab_data.CMD2.value = (bport1_ab_data.CMD2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CMD3_maskWrite) {
    bport1_ab_data.CMD3.value = (bport1_ab_data.CMD3.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CMD4_maskWrite) {
    bport1_ab_data.CMD4.value = (bport1_ab_data.CMD4.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DMA_maskWrite) {
    bport1_ab_data.DMA.value = (bport1_ab_data.DMA.value & 0xfe) | (data & 0x1);
}

static PPM_WRITE_CB(bport1_ab_MSC_maskWrite) {
    bport1_ab_data.MSC.value = (bport1_ab_data.MSC.value & 0x80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_OC_maskWrite) {
    bport1_ab_data.OC.value = (bport1_ab_data.OC.value & 0x1f) | (data & 0xe0);
}

static PPM_WRITE_CB(bport1_ab_PPS_maskWrite) {
    bport1_ab_data.PPS.value = (bport1_ab_data.PPS.value & 0xf0) | (data & 0xf);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_CGH1",
        "CMT Carrier Generator High Data Register 1, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_CGH1_maskWrite,
        view8,
        &(bport1_ab_data.CGH1.value),
        True
    );
    ppmCreateRegister("ab_CGL1",
        "CMT Carrier Generator Low Data Register 1, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_CGL1_maskWrite,
        view8,
        &(bport1_ab_data.CGL1.value),
        True
    );
    ppmCreateRegister("ab_CGH2",
        "CMT Carrier Generator High Data Register 2, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_CGH2_maskWrite,
        view8,
        &(bport1_ab_data.CGH2.value),
        True
    );
    ppmCreateRegister("ab_CGL2",
        "CMT Carrier Generator Low Data Register 2, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        bport1_ab_CGL2_maskWrite,
        view8,
        &(bport1_ab_data.CGL2.value),
        True
    );
    ppmCreateRegister("ab_OC",
        "CMT Output Control Register, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_OC_maskWrite,
        view8,
        &(bport1_ab_data.OC.value),
        True
    );
    ppmCreateRegister("ab_MSC",
        "CMT Modulator Status and Control Register, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_MSC_maskWrite,
        view8,
        &(bport1_ab_data.MSC.value),
        True
    );
    ppmCreateRegister("ab_CMD1",
        "CMT Modulator Data Register Mark High, offset: 0x6 ",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_CMD1_maskWrite,
        view8,
        &(bport1_ab_data.CMD1.value),
        True
    );
    ppmCreateRegister("ab_CMD2",
        "CMT Modulator Data Register Mark Low, offset: 0x7 ",
        handles.bport1,
        7,
        1,
        read_8,
        bport1_ab_CMD2_maskWrite,
        view8,
        &(bport1_ab_data.CMD2.value),
        True
    );
    ppmCreateRegister("ab_CMD3",
        "CMT Modulator Data Register Space High, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_CMD3_maskWrite,
        view8,
        &(bport1_ab_data.CMD3.value),
        True
    );
    ppmCreateRegister("ab_CMD4",
        "CMT Modulator Data Register Space Low, offset: 0x9 ",
        handles.bport1,
        9,
        1,
        read_8,
        bport1_ab_CMD4_maskWrite,
        view8,
        &(bport1_ab_data.CMD4.value),
        True
    );
    ppmCreateRegister("ab_PPS",
        "CMT Primary Prescaler Register, offset: 0xA ",
        handles.bport1,
        10,
        1,
        read_8,
        bport1_ab_PPS_maskWrite,
        view8,
        &(bport1_ab_data.PPS.value),
        True
    );
    ppmCreateRegister("ab_DMA",
        "CMT Direct Memory Access, offset: 0xB ",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_DMA_maskWrite,
        view8,
        &(bport1_ab_data.DMA.value),
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
        bport1_ab_data.DMA.value = 0x0;
        bport1_ab_data.PPS.value = 0x0;
        bport1_ab_data.MSC.value = 0x0;
        bport1_ab_data.OC.value = 0x0;
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

