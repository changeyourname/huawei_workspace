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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "LAN9118", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_1) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_1.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_2) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_2.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_3) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_3.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_4) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_4.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_5) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_5.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_6) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_6.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_7) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_7.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_1) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_1.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_2) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_2.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_3) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_3.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_4) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_4.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_5) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_5.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_6) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_6.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_7) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_7.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_STATUS_FIFO) {
    *(Uns32*)data = bport1_ab_data.RX_STATUS_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_STATUS_FIFO_PEEK) {
    *(Uns32*)data = bport1_ab_data.RX_STATUS_FIFO_PEEK.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_STATUS_FIFO) {
    *(Uns32*)data = bport1_ab_data.TX_STATUS_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_STATUS_FIFO_PEEK) {
    *(Uns32*)data = bport1_ab_data.TX_STATUS_FIFO_PEEK.value;
}

static PPM_VIEW_CB(view_bport1_ab_ID_REV) {
    *(Uns32*)data = bport1_ab_data.ID_REV.value;
}

static PPM_VIEW_CB(view_bport1_ab_IRQ_CFG) {
    *(Uns32*)data = bport1_ab_data.IRQ_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_INT_STS) {
    *(Uns32*)data = bport1_ab_data.INT_STS.value;
}

static PPM_VIEW_CB(view_bport1_ab_INT_EN) {
    *(Uns32*)data = bport1_ab_data.INT_EN.value;
}

static PPM_VIEW_CB(view_bport1_ab_BYTE_TEST) {
    *(Uns32*)data = bport1_ab_data.BYTE_TEST.value;
}

static PPM_VIEW_CB(view_bport1_ab_FIFO_INT) {
    *(Uns32*)data = bport1_ab_data.FIFO_INT.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_CFG) {
    *(Uns32*)data = bport1_ab_data.RX_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_CFG) {
    *(Uns32*)data = bport1_ab_data.TX_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_HW_CFG) {
    *(Uns32*)data = bport1_ab_data.HW_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DP_CTRL) {
    *(Uns32*)data = bport1_ab_data.RX_DP_CTRL.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_FIFO_INF) {
    *(Uns32*)data = bport1_ab_data.RX_FIFO_INF.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_FIFO_INF) {
    *(Uns32*)data = bport1_ab_data.TX_FIFO_INF.value;
}

static PPM_VIEW_CB(view_bport1_ab_PMT_CTRL) {
    *(Uns32*)data = bport1_ab_data.PMT_CTRL.value;
}

static PPM_VIEW_CB(view_bport1_ab_GPIO_CFG) {
    *(Uns32*)data = bport1_ab_data.GPIO_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_GPT_CFG) {
    *(Uns32*)data = bport1_ab_data.GPT_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_GPT_CNT) {
    *(Uns32*)data = bport1_ab_data.GPT_CNT.value;
}

static PPM_VIEW_CB(view_bport1_ab_WORD_SWAP) {
    *(Uns32*)data = bport1_ab_data.WORD_SWAP.value;
}

static PPM_VIEW_CB(view_bport1_ab_FREE_RUN) {
    *(Uns32*)data = bport1_ab_data.FREE_RUN.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DROP) {
    *(Uns32*)data = bport1_ab_data.RX_DROP.value;
}

static PPM_VIEW_CB(view_bport1_ab_MAC_CSR_CMD) {
    *(Uns32*)data = bport1_ab_data.MAC_CSR_CMD.value;
}

static PPM_VIEW_CB(view_bport1_ab_MAC_CSR_DATA) {
    *(Uns32*)data = bport1_ab_data.MAC_CSR_DATA.value;
}

static PPM_VIEW_CB(view_bport1_ab_AFC_CFG) {
    *(Uns32*)data = bport1_ab_data.AFC_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_E2P_CMD) {
    *(Uns32*)data = bport1_ab_data.E2P_CMD.value;
}

static PPM_VIEW_CB(view_bport1_ab_E2P_DATA) {
    *(Uns32*)data = bport1_ab_data.E2P_DATA.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_RX_DATA_FIFO",
        0,
        handles.bport1,
        0,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_1",
        0,
        handles.bport1,
        4,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_1,
        (void*)0x4,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_2",
        0,
        handles.bport1,
        8,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_2,
        (void*)0x8,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_3",
        0,
        handles.bport1,
        12,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_3,
        (void*)0xc,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_4",
        0,
        handles.bport1,
        16,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_4,
        (void*)0x10,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_5",
        0,
        handles.bport1,
        20,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_5,
        (void*)0x14,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_6",
        0,
        handles.bport1,
        24,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_6,
        (void*)0x18,
        True
    );
    ppmCreateRegister("ab_RX_DATA_FIFO_7",
        0,
        handles.bport1,
        28,
        4,
        rxFifoRd,
        0,
        view_bport1_ab_RX_DATA_FIFO_7,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO",
        0,
        handles.bport1,
        32,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO,
        (void*)0x20,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_1",
        0,
        handles.bport1,
        36,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_1,
        (void*)0x24,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_2",
        0,
        handles.bport1,
        40,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_2,
        (void*)0x28,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_3",
        0,
        handles.bport1,
        44,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_3,
        (void*)0x2c,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_4",
        0,
        handles.bport1,
        48,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_4,
        (void*)0x30,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_5",
        0,
        handles.bport1,
        52,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_5,
        (void*)0x34,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_6",
        0,
        handles.bport1,
        56,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_6,
        (void*)0x38,
        True
    );
    ppmCreateRegister("ab_TX_DATA_FIFO_7",
        0,
        handles.bport1,
        60,
        4,
        0,
        txFifoWr,
        view_bport1_ab_TX_DATA_FIFO_7,
        (void*)0x3c,
        True
    );
    ppmCreateRegister("ab_RX_STATUS_FIFO",
        0,
        handles.bport1,
        64,
        4,
        rxStatusFifoRd,
        0,
        view_bport1_ab_RX_STATUS_FIFO,
        (void*)0x40,
        True
    );
    ppmCreateRegister("ab_RX_STATUS_FIFO_PEEK",
        0,
        handles.bport1,
        68,
        4,
        rxStatusFifoPeek,
        0,
        view_bport1_ab_RX_STATUS_FIFO_PEEK,
        (void*)0x44,
        True
    );
    ppmCreateRegister("ab_TX_STATUS_FIFO",
        0,
        handles.bport1,
        72,
        4,
        txStatusFifoRd,
        0,
        view_bport1_ab_TX_STATUS_FIFO,
        (void*)0x48,
        True
    );
    ppmCreateRegister("ab_TX_STATUS_FIFO_PEEK",
        0,
        handles.bport1,
        76,
        4,
        txStatusFifoPeek,
        0,
        view_bport1_ab_TX_STATUS_FIFO_PEEK,
        (void*)0x4c,
        True
    );
    ppmCreateRegister("ab_ID_REV",
        0,
        handles.bport1,
        80,
        4,
        idRev,
        0,
        view_bport1_ab_ID_REV,
        (void*)0x50,
        True
    );
    ppmCreateRegister("ab_IRQ_CFG",
        0,
        handles.bport1,
        84,
        4,
        irqCfgRd,
        irqCfgWr,
        view_bport1_ab_IRQ_CFG,
        (void*)0x54,
        True
    );
    ppmCreateRegister("ab_INT_STS",
        0,
        handles.bport1,
        88,
        4,
        intStsRd,
        intStsWr,
        view_bport1_ab_INT_STS,
        (void*)0x58,
        True
    );
    ppmCreateRegister("ab_INT_EN",
        0,
        handles.bport1,
        92,
        4,
        intEnRd,
        intEnWr,
        view_bport1_ab_INT_EN,
        (void*)0x5c,
        True
    );
    ppmCreateRegister("ab_BYTE_TEST",
        0,
        handles.bport1,
        100,
        4,
        byteTest,
        0,
        view_bport1_ab_BYTE_TEST,
        (void*)0x64,
        True
    );
    ppmCreateRegister("ab_FIFO_INT",
        0,
        handles.bport1,
        104,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_FIFO_INT,
        (void*)0x68,
        True
    );
    ppmCreateRegister("ab_RX_CFG",
        0,
        handles.bport1,
        108,
        4,
        rxCfgRd,
        rxCfgWr,
        view_bport1_ab_RX_CFG,
        (void*)0x6c,
        True
    );
    ppmCreateRegister("ab_TX_CFG",
        0,
        handles.bport1,
        112,
        4,
        txCfgRd,
        txCfgWr,
        view_bport1_ab_TX_CFG,
        (void*)0x70,
        True
    );
    ppmCreateRegister("ab_HW_CFG",
        0,
        handles.bport1,
        116,
        4,
        hwCfgRd,
        hwCfgWr,
        view_bport1_ab_HW_CFG,
        (void*)0x74,
        True
    );
    ppmCreateRegister("ab_RX_DP_CTRL",
        0,
        handles.bport1,
        120,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_RX_DP_CTRL,
        (void*)0x78,
        True
    );
    ppmCreateRegister("ab_RX_FIFO_INF",
        0,
        handles.bport1,
        124,
        4,
        rxFifoInfRd,
        0,
        view_bport1_ab_RX_FIFO_INF,
        (void*)0x7c,
        True
    );
    ppmCreateRegister("ab_TX_FIFO_INF",
        0,
        handles.bport1,
        128,
        4,
        txFifoInfRd,
        0,
        view_bport1_ab_TX_FIFO_INF,
        (void*)0x80,
        True
    );
    ppmCreateRegister("ab_PMT_CTRL",
        0,
        handles.bport1,
        132,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_PMT_CTRL,
        (void*)0x84,
        True
    );
    ppmCreateRegister("ab_GPIO_CFG",
        0,
        handles.bport1,
        136,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_GPIO_CFG,
        (void*)0x88,
        True
    );
    ppmCreateRegister("ab_GPT_CFG",
        0,
        handles.bport1,
        140,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_GPT_CFG,
        (void*)0x8c,
        True
    );
    ppmCreateRegister("ab_GPT_CNT",
        0,
        handles.bport1,
        144,
        4,
        defaultRdCB,
        0,
        view_bport1_ab_GPT_CNT,
        (void*)0x90,
        True
    );
    ppmCreateRegister("ab_WORD_SWAP",
        0,
        handles.bport1,
        152,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_WORD_SWAP,
        (void*)0x98,
        True
    );
    ppmCreateRegister("ab_FREE_RUN",
        0,
        handles.bport1,
        156,
        4,
        defaultRdCB,
        0,
        view_bport1_ab_FREE_RUN,
        (void*)0x9c,
        True
    );
    ppmCreateRegister("ab_RX_DROP",
        0,
        handles.bport1,
        160,
        4,
        rxDropRd,
        0,
        view_bport1_ab_RX_DROP,
        (void*)0xa0,
        True
    );
    ppmCreateRegister("ab_MAC_CSR_CMD",
        0,
        handles.bport1,
        164,
        4,
        macCsrCmdRd,
        macCsrCmdWr,
        view_bport1_ab_MAC_CSR_CMD,
        (void*)0xa4,
        True
    );
    ppmCreateRegister("ab_MAC_CSR_DATA",
        0,
        handles.bport1,
        168,
        4,
        macCsrDataRd,
        macCsrDataWr,
        view_bport1_ab_MAC_CSR_DATA,
        (void*)0xa8,
        True
    );
    ppmCreateRegister("ab_AFC_CFG",
        0,
        handles.bport1,
        172,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_AFC_CFG,
        (void*)0xac,
        True
    );
    ppmCreateRegister("ab_E2P_CMD",
        0,
        handles.bport1,
        176,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_E2P_CMD,
        (void*)0xb0,
        True
    );
    ppmCreateRegister("ab_E2P_DATA",
        0,
        handles.bport1,
        180,
        4,
        defaultRdCB,
        defaultWrCB,
        view_bport1_ab_E2P_DATA,
        (void*)0xb4,
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq, value);

    handles.irq = ppmOpenNetPort("irq");

}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Fully functional Model of SMSC LAN9118 for Arm Versatile Express platforms. For full details please consult README-EMAC.txt");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "See README-EMAC.txt");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SMSC LAN9118 High Performance single-chip 10/100 Non-PCI Ethernet Controller Datasheet Revision 1.5 (07-11-08)");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

