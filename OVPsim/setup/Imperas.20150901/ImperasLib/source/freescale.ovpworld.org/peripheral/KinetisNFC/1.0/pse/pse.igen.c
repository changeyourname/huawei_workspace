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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisNFC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CAR_maskWrite) {
    bport1_ab_data.CAR.value = (bport1_ab_data.CAR.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CFG_maskWrite) {
    bport1_ab_data.CFG.value = (bport1_ab_data.CFG.value & 0x40) | (data & 0xffffffbf);
}

static PPM_WRITE_CB(bport1_ab_CMD1_maskWrite) {
    bport1_ab_data.CMD1.value = (bport1_ab_data.CMD1.value & 0xffff) | (data & 0xffff0000);
}

static PPM_WRITE_CB(bport1_ab_CMD2_maskWrite) {
    bport1_ab_data.CMD2.value = (bport1_ab_data.CMD2.value & 0xf8) | (data & 0xffffff07);
}

static PPM_WRITE_CB(bport1_ab_DMA1_maskWrite) {
    bport1_ab_data.DMA1.value = (bport1_ab_data.DMA1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DMA2_maskWrite) {
    bport1_ab_data.DMA2.value = (bport1_ab_data.DMA2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DMACFG_maskWrite) {
    bport1_ab_data.DMACFG.value = (bport1_ab_data.DMACFG.value & 0x1fc) | (data & 0xfffffe03);
}

static PPM_WRITE_CB(bport1_ab_ISR_maskWrite) {
    bport1_ab_data.ISR.value = (bport1_ab_data.ISR.value & 0xff81ffff) | (data & 0x7e0000);
}

static PPM_WRITE_CB(bport1_ab_RAI_maskWrite) {
    bport1_ab_data.RAI.value = (bport1_ab_data.RAI.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_RAR_maskWrite) {
    bport1_ab_data.RAR.value = (bport1_ab_data.RAR.value & 0xcc000000) | (data & 0x33ffffff);
}

static PPM_WRITE_CB(bport1_ab_RPT_maskWrite) {
    bport1_ab_data.RPT.value = (bport1_ab_data.RPT.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_SECSZ_maskWrite) {
    bport1_ab_data.SECSZ.value = (bport1_ab_data.SECSZ.value & 0xffffe000) | (data & 0x1fff);
}

static PPM_WRITE_CB(bport1_ab_SWAP_maskWrite) {
    bport1_ab_data.SWAP.value = (bport1_ab_data.SWAP.value & 0xf000f001) | (data & 0xfff0ffe);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_CMD1",
        "Flash command 1, offset: 0x3F00 ",
        handles.bport1,
        16128,
        4,
        read_32,
        bport1_ab_CMD1_maskWrite,
        view32,
        &(bport1_ab_data.CMD1.value),
        True
    );
    ppmCreateRegister("ab_CMD2",
        "Flash command 2, offset: 0x3F04 ",
        handles.bport1,
        16132,
        4,
        read_32,
        bport1_ab_CMD2_maskWrite,
        view32,
        &(bport1_ab_data.CMD2.value),
        True
    );
    ppmCreateRegister("ab_CAR",
        "Column address, offset: 0x3F08 ",
        handles.bport1,
        16136,
        4,
        read_32,
        bport1_ab_CAR_maskWrite,
        view32,
        &(bport1_ab_data.CAR.value),
        True
    );
    ppmCreateRegister("ab_RAR",
        "Row address, offset: 0x3F0C ",
        handles.bport1,
        16140,
        4,
        read_32,
        bport1_ab_RAR_maskWrite,
        view32,
        &(bport1_ab_data.RAR.value),
        True
    );
    ppmCreateRegister("ab_RPT",
        "Flash command repeat, offset: 0x3F10 ",
        handles.bport1,
        16144,
        4,
        read_32,
        bport1_ab_RPT_maskWrite,
        view32,
        &(bport1_ab_data.RPT.value),
        True
    );
    ppmCreateRegister("ab_RAI",
        "Row address increment, offset: 0x3F14 ",
        handles.bport1,
        16148,
        4,
        read_32,
        bport1_ab_RAI_maskWrite,
        view32,
        &(bport1_ab_data.RAI.value),
        True
    );
    ppmCreateRegister("ab_SR1",
        "Flash status 1, offset: 0x3F18 ",
        handles.bport1,
        16152,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.SR1.value),
        True
    );
    ppmCreateRegister("ab_SR2",
        "Flash status 2, offset: 0x3F1C ",
        handles.bport1,
        16156,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.SR2.value),
        True
    );
    ppmCreateRegister("ab_DMA1",
        "DMA channel 1 address, offset: 0x3F20 ",
        handles.bport1,
        16160,
        4,
        read_32,
        bport1_ab_DMA1_maskWrite,
        view32,
        &(bport1_ab_data.DMA1.value),
        True
    );
    ppmCreateRegister("ab_DMACFG",
        "DMA configuration, offset: 0x3F24 ",
        handles.bport1,
        16164,
        4,
        read_32,
        bport1_ab_DMACFG_maskWrite,
        view32,
        &(bport1_ab_data.DMACFG.value),
        True
    );
    ppmCreateRegister("ab_SWAP",
        "Cach swap, offset: 0x3F28 ",
        handles.bport1,
        16168,
        4,
        read_32,
        bport1_ab_SWAP_maskWrite,
        view32,
        &(bport1_ab_data.SWAP.value),
        True
    );
    ppmCreateRegister("ab_SECSZ",
        "Sector size, offset: 0x3F2C ",
        handles.bport1,
        16172,
        4,
        read_32,
        bport1_ab_SECSZ_maskWrite,
        view32,
        &(bport1_ab_data.SECSZ.value),
        True
    );
    ppmCreateRegister("ab_CFG",
        "Flash configuration, offset: 0x3F30 ",
        handles.bport1,
        16176,
        4,
        read_32,
        bport1_ab_CFG_maskWrite,
        view32,
        &(bport1_ab_data.CFG.value),
        True
    );
    ppmCreateRegister("ab_DMA2",
        "DMA channel 2 address, offset: 0x3F34 ",
        handles.bport1,
        16180,
        4,
        read_32,
        bport1_ab_DMA2_maskWrite,
        view32,
        &(bport1_ab_data.DMA2.value),
        True
    );
    ppmCreateRegister("ab_ISR",
        "Interrupt status, offset: 0x3F38 ",
        handles.bport1,
        16184,
        4,
        read_32,
        bport1_ab_ISR_maskWrite,
        view32,
        &(bport1_ab_data.ISR.value),
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
        bport1_ab_data.ISR.value = 0x60000000;
        bport1_ab_data.DMA2.value = 0x0;
        bport1_ab_data.CFG.value = 0xea631;
        bport1_ab_data.SECSZ.value = 0x420;
        bport1_ab_data.SWAP.value = 0xffe0ffe;
        bport1_ab_data.DMACFG.value = 0x0;
        bport1_ab_data.DMA1.value = 0x0;
        bport1_ab_data.SR2.value = 0x0;
        bport1_ab_data.SR1.value = 0x0;
        bport1_ab_data.RAI.value = 0x0;
        bport1_ab_data.RPT.value = 0x0;
        bport1_ab_data.RAR.value = 0x11000000;
        bport1_ab_data.CAR.value = 0x0;
        bport1_ab_data.CMD2.value = 0x7ee000;
        bport1_ab_data.CMD1.value = 0x30ff0000;
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

