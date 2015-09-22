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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridUART", "Example");
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

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & 0x30) | (data & 0xcf);
}

static PPM_WRITE_CB(bport1_ab_C3_maskWrite) {
    bport1_ab_data.C3.value = (bport1_ab_data.C3.value & 0x80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_C5_maskWrite) {
    bport1_ab_data.C5.value = (bport1_ab_data.C5.value & 0x5f) | (data & 0xa0);
}

static PPM_WRITE_CB(bport1_ab_C7816_maskWrite) {
    bport1_ab_data.C7816.value = (bport1_ab_data.C7816.value & 0xe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_ET7816_maskWrite) {
    bport1_ab_data.ET7816.value = (bport1_ab_data.ET7816.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_IE7816_maskWrite) {
    bport1_ab_data.IE7816.value = (bport1_ab_data.IE7816.value & 0x8) | (data & 0xf7);
}

static PPM_WRITE_CB(bport1_ab_IR_maskWrite) {
    bport1_ab_data.IR.value = (bport1_ab_data.IR.value & 0xf8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_IS7816_maskWrite) {
    bport1_ab_data.IS7816.value = (bport1_ab_data.IS7816.value & 0x8) | (data & 0xf7);
}

static PPM_WRITE_CB(bport1_ab_MA1_maskWrite) {
    bport1_ab_data.MA1.value = (bport1_ab_data.MA1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_MA2_maskWrite) {
    bport1_ab_data.MA2.value = (bport1_ab_data.MA2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_MODEM_maskWrite) {
    bport1_ab_data.MODEM.value = (bport1_ab_data.MODEM.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_PFIFO_maskWrite) {
    bport1_ab_data.PFIFO.value = (bport1_ab_data.PFIFO.value & 0x77) | (data & 0x88);
}

static PPM_WRITE_CB(bport1_ab_S2_maskWrite) {
    bport1_ab_data.S2.value = (bport1_ab_data.S2.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_SFIFO_maskWrite) {
    bport1_ab_data.SFIFO.value = (bport1_ab_data.SFIFO.value & 0xfc) | (data & 0x3);
}

static PPM_WRITE_CB(bport1_ab_TL7816_maskWrite) {
    bport1_ab_data.TL7816.value = (bport1_ab_data.TL7816.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_WF7816_maskWrite) {
    bport1_ab_data.WF7816.value = (bport1_ab_data.WF7816.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_WN7816_maskWrite) {
    bport1_ab_data.WN7816.value = (bport1_ab_data.WN7816.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_WP7816T0_maskWrite) {
    bport1_ab_data.WP7816T0.value = (bport1_ab_data.WP7816T0.value & 0x0) | (data & 0xff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_BDH",
        "UART Baud Rate Registers:High, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        writeBDH,
        view8,
        &(bport1_ab_data.BDH.value),
        True
    );
    ppmCreateRegister("ab_BDL",
        "UART Baud Rate Registers: Low, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        writeBDL,
        view8,
        &(bport1_ab_data.BDL.value),
        True
    );
    ppmCreateRegister("ab_C1",
        "UART Control Register 1, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_C1_maskWrite,
        view8,
        &(bport1_ab_data.C1.value),
        True
    );
    ppmCreateRegister("ab_C2",
        "UART Control Register 2, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        writeC2,
        view8,
        &(bport1_ab_data.C2.value),
        True
    );
    ppmCreateRegister("ab_S1",
        "UART Status Register 1, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        readS1,
        0,
        viewS1,
        &(bport1_ab_data.S1.value),
        True
    );
    ppmCreateRegister("ab_S2",
        "UART Status Register 2, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_S2_maskWrite,
        view8,
        &(bport1_ab_data.S2.value),
        True
    );
    ppmCreateRegister("ab_C3",
        "UART Control Register 3, offset: 0x6 ",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_C3_maskWrite,
        view8,
        &(bport1_ab_data.C3.value),
        True
    );
    ppmCreateRegister("ab_D",
        "UART Data Register, offset: 0x7 ",
        handles.bport1,
        7,
        1,
        readD,
        writeD,
        view8,
        &(bport1_ab_data.D.value),
        True
    );
    ppmCreateRegister("ab_MA1",
        "UART Match Address Registers 1, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_MA1_maskWrite,
        view8,
        &(bport1_ab_data.MA1.value),
        True
    );
    ppmCreateRegister("ab_MA2",
        "UART Match Address Registers 2, offset: 0x9 ",
        handles.bport1,
        9,
        1,
        read_8,
        bport1_ab_MA2_maskWrite,
        view8,
        &(bport1_ab_data.MA2.value),
        True
    );
    ppmCreateRegister("ab_C4",
        "UART Control Register 4, offset: 0xA ",
        handles.bport1,
        10,
        1,
        read_8,
        writeC4,
        view8,
        &(bport1_ab_data.C4.value),
        True
    );
    ppmCreateRegister("ab_C5",
        "UART Control Register 5, offset: 0xB ",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_C5_maskWrite,
        view8,
        &(bport1_ab_data.C5.value),
        True
    );
    ppmCreateRegister("ab_ED",
        "UART Extended Data Register, offset: 0xC ",
        handles.bport1,
        12,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.ED.value),
        True
    );
    ppmCreateRegister("ab_MODEM",
        "UART Modem Register, offset: 0xD ",
        handles.bport1,
        13,
        1,
        read_8,
        bport1_ab_MODEM_maskWrite,
        view8,
        &(bport1_ab_data.MODEM.value),
        True
    );
    ppmCreateRegister("ab_IR",
        "UART Infrared Register, offset: 0xE ",
        handles.bport1,
        14,
        1,
        read_8,
        bport1_ab_IR_maskWrite,
        view8,
        &(bport1_ab_data.IR.value),
        True
    );
    ppmCreateRegister("ab_PFIFO",
        "UART FIFO Parameters, offset: 0x10 ",
        handles.bport1,
        16,
        1,
        read_8,
        bport1_ab_PFIFO_maskWrite,
        view8,
        &(bport1_ab_data.PFIFO.value),
        True
    );
    ppmCreateRegister("ab_CFIFO",
        "UART FIFO Control Register, offset: 0x11 ",
        handles.bport1,
        17,
        1,
        read_8,
        writeCFIFO,
        view8,
        &(bport1_ab_data.CFIFO.value),
        True
    );
    ppmCreateRegister("ab_SFIFO",
        "UART FIFO Status Register, offset: 0x12 ",
        handles.bport1,
        18,
        1,
        read_8,
        bport1_ab_SFIFO_maskWrite,
        view8,
        &(bport1_ab_data.SFIFO.value),
        True
    );
    ppmCreateRegister("ab_TWFIFO",
        "UART FIFO Transmit Watermark, offset: 0x13 ",
        handles.bport1,
        19,
        1,
        read_8,
        writeTWFIFO,
        view8,
        &(bport1_ab_data.TWFIFO.value),
        True
    );
    ppmCreateRegister("ab_TCFIFO",
        "UART FIFO Transmit Count, offset: 0x14 ",
        handles.bport1,
        20,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.TCFIFO.value),
        True
    );
    ppmCreateRegister("ab_RWFIFO",
        "UART FIFO Receive Watermark, offset: 0x15 ",
        handles.bport1,
        21,
        1,
        read_8,
        writeRWFIFO,
        view8,
        &(bport1_ab_data.RWFIFO.value),
        True
    );
    ppmCreateRegister("ab_RCFIFO",
        "UART FIFO Receive Count, offset: 0x16 ",
        handles.bport1,
        22,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.RCFIFO.value),
        True
    );
    ppmCreateRegister("ab_C7816",
        "UART 7816 Control Register, offset: 0x18 ",
        handles.bport1,
        24,
        1,
        read_8,
        bport1_ab_C7816_maskWrite,
        view8,
        &(bport1_ab_data.C7816.value),
        True
    );
    ppmCreateRegister("ab_IE7816",
        "UART 7816 Interrupt Enable Register, offset: 0x19 ",
        handles.bport1,
        25,
        1,
        read_8,
        bport1_ab_IE7816_maskWrite,
        view8,
        &(bport1_ab_data.IE7816.value),
        True
    );
    ppmCreateRegister("ab_IS7816",
        "UART 7816 Interrupt Status Register, offset: 0x1A ",
        handles.bport1,
        26,
        1,
        read_8,
        bport1_ab_IS7816_maskWrite,
        view8,
        &(bport1_ab_data.IS7816.value),
        True
    );
    ppmCreateRegister("ab_WP7816T0",
        "UART 7816 Wait Parameter Register, offset: 0x1B ",
        handles.bport1,
        27,
        1,
        read_8,
        bport1_ab_WP7816T0_maskWrite,
        view8,
        &(bport1_ab_data.WP7816T0.value),
        True
    );
    ppmCreateRegister("ab_WN7816",
        "UART 7816 Wait N Register, offset: 0x1C ",
        handles.bport1,
        28,
        1,
        read_8,
        bport1_ab_WN7816_maskWrite,
        view8,
        &(bport1_ab_data.WN7816.value),
        True
    );
    ppmCreateRegister("ab_WF7816",
        "UART 7816 Wait FD Register, offset: 0x1D ",
        handles.bport1,
        29,
        1,
        read_8,
        bport1_ab_WF7816_maskWrite,
        view8,
        &(bport1_ab_data.WF7816.value),
        True
    );
    ppmCreateRegister("ab_ET7816",
        "UART 7816 Error Threshold Register, offset: 0x1E ",
        handles.bport1,
        30,
        1,
        read_8,
        bport1_ab_ET7816_maskWrite,
        view8,
        &(bport1_ab_data.ET7816.value),
        True
    );
    ppmCreateRegister("ab_TL7816",
        "UART 7816 Transmit Length Register, offset: 0x1F ",
        handles.bport1,
        31,
        1,
        read_8,
        bport1_ab_TL7816_maskWrite,
        view8,
        &(bport1_ab_data.TL7816.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.DirectWrite, value);

    handles.DirectWrite = ppmOpenNetPort("DirectWrite");

    handles.DirectRead = ppmOpenNetPort("DirectRead");
    if (handles.DirectRead) {
        ppmInstallNetCallback(handles.DirectRead, directReadCB, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.Interrupt, value);

    handles.Interrupt = ppmOpenNetPort("Interrupt");

    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, resetCB, (void*)0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.TL7816.value = 0x0;
        bport1_ab_data.ET7816.value = 0x0;
        bport1_ab_data.WF7816.value = 0x1;
        bport1_ab_data.WN7816.value = 0x0;
        bport1_ab_data.WP7816T0.value = 0xa;
        bport1_ab_data.IS7816.value = 0x0;
        bport1_ab_data.IE7816.value = 0x0;
        bport1_ab_data.C7816.value = 0x0;
        bport1_ab_data.RCFIFO.value = 0x0;
        bport1_ab_data.RWFIFO.value = 0x1;
        bport1_ab_data.TCFIFO.value = 0x0;
        bport1_ab_data.TWFIFO.value = 0x0;
        bport1_ab_data.SFIFO.value = 0xc0;
        bport1_ab_data.CFIFO.value = 0x0;
        bport1_ab_data.PFIFO.value = 0x0;
        bport1_ab_data.IR.value = 0x0;
        bport1_ab_data.MODEM.value = 0x0;
        bport1_ab_data.ED.value = 0x0;
        bport1_ab_data.C5.value = 0x0;
        bport1_ab_data.C4.value = 0x0;
        bport1_ab_data.MA2.value = 0x0;
        bport1_ab_data.MA1.value = 0x0;
        bport1_ab_data.D.value = 0x0;
        bport1_ab_data.C3.value = 0x0;
        bport1_ab_data.S2.value = 0x0;
        bport1_ab_data.S1.value = 0xc0;
        bport1_ab_data.C2.value = 0x0;
        bport1_ab_data.C1.value = 0x0;
        bport1_ab_data.BDL.value = 0x4;
        bport1_ab_data.BDH.value = 0x0;
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

