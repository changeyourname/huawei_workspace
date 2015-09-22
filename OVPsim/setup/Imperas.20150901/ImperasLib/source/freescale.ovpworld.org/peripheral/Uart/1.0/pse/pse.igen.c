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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "Uart", "Example");
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

static PPM_WRITE_CB(bport1_ab_c3_maskWrite) {
    bport1_ab_data.c3.value = (bport1_ab_data.c3.value & 0x80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_c5_maskWrite) {
    bport1_ab_data.c5.value = (bport1_ab_data.c5.value & 0x5f) | (data & 0xa0);
}

static PPM_WRITE_CB(bport1_ab_infrared_maskWrite) {
    bport1_ab_data.infrared.value = (bport1_ab_data.infrared.value & 0xf8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_modem_maskWrite) {
    bport1_ab_data.modem.value = (bport1_ab_data.modem.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_pfifo_maskWrite) {
    bport1_ab_data.pfifo.value = (bport1_ab_data.pfifo.value & 0x77) | (data & 0x88);
}

static PPM_WRITE_CB(bport1_ab_s2_maskWrite) {
    bport1_ab_data.s2.value = (bport1_ab_data.s2.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_sfifo_maskWrite) {
    bport1_ab_data.sfifo.value = (bport1_ab_data.sfifo.value & 0xfc) | (data & 0x3);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_bdh",
        "UART Baud Rate Registers:High",
        handles.bport1,
        0,
        1,
        read_8,
        writeBDH,
        view8,
        &(bport1_ab_data.bdh.value),
        True
    );
    ppmCreateRegister("ab_bdl",
        "UART Baud Rate Registers:Low",
        handles.bport1,
        1,
        1,
        read_8,
        writeBDL,
        view8,
        &(bport1_ab_data.bdl.value),
        True
    );
    ppmCreateRegister("ab_c1",
        "UART Control Register 1",
        handles.bport1,
        2,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.c1.value),
        True
    );
    ppmCreateRegister("ab_c2",
        "UART Control Register 2",
        handles.bport1,
        3,
        1,
        read_8,
        writeC2,
        view8,
        &(bport1_ab_data.c2.value),
        True
    );
    ppmCreateRegister("ab_s1",
        "UART Status Register 1",
        handles.bport1,
        4,
        1,
        readS1,
        0,
        view8,
        &(bport1_ab_data.s1.value),
        True
    );
    ppmCreateRegister("ab_s2",
        "UART Status Register 2",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_s2_maskWrite,
        view8,
        &(bport1_ab_data.s2.value),
        True
    );
    ppmCreateRegister("ab_c3",
        "UART Control Register 3",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_c3_maskWrite,
        view8,
        &(bport1_ab_data.c3.value),
        True
    );
    ppmCreateRegister("ab_d",
        "UART Data Register",
        handles.bport1,
        7,
        1,
        readD,
        writeD,
        view8,
        &(bport1_ab_data.d.value),
        True
    );
    ppmCreateRegister("ab_ma1",
        "UART Match Address Registers 1",
        handles.bport1,
        8,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.ma1.value),
        True
    );
    ppmCreateRegister("ab_ma2",
        "UART Match Address Registers 2",
        handles.bport1,
        9,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.ma2.value),
        True
    );
    ppmCreateRegister("ab_c4",
        "UART Control Register 4",
        handles.bport1,
        10,
        1,
        read_8,
        writeC4,
        view8,
        &(bport1_ab_data.c4.value),
        True
    );
    ppmCreateRegister("ab_c5",
        "UART Control Register 5",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_c5_maskWrite,
        view8,
        &(bport1_ab_data.c5.value),
        True
    );
    ppmCreateRegister("ab_ed",
        "UART Extended Data Register",
        handles.bport1,
        12,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.ed.value),
        True
    );
    ppmCreateRegister("ab_modem",
        "UART Modem Register",
        handles.bport1,
        13,
        1,
        read_8,
        bport1_ab_modem_maskWrite,
        view8,
        &(bport1_ab_data.modem.value),
        True
    );
    ppmCreateRegister("ab_infrared",
        "UART Infrared Register",
        handles.bport1,
        14,
        1,
        read_8,
        bport1_ab_infrared_maskWrite,
        view8,
        &(bport1_ab_data.infrared.value),
        True
    );
    ppmCreateRegister("ab_pfifo",
        "UART FIFO Parameters Register",
        handles.bport1,
        16,
        1,
        read_8,
        bport1_ab_pfifo_maskWrite,
        view8,
        &(bport1_ab_data.pfifo.value),
        True
    );
    ppmCreateRegister("ab_cfifo",
        "UART FIFO Control Register",
        handles.bport1,
        17,
        1,
        read_8,
        writeCFIFO,
        view8,
        &(bport1_ab_data.cfifo.value),
        True
    );
    ppmCreateRegister("ab_sfifo",
        "UART FIFO Status Register",
        handles.bport1,
        18,
        1,
        read_8,
        bport1_ab_sfifo_maskWrite,
        view8,
        &(bport1_ab_data.sfifo.value),
        True
    );
    ppmCreateRegister("ab_twfifo",
        "UART FIFO Transmit Watermark Register",
        handles.bport1,
        19,
        1,
        read_8,
        writeTWFIFO,
        view8,
        &(bport1_ab_data.twfifo.value),
        True
    );
    ppmCreateRegister("ab_tcfifo",
        "UART FIFO Transmit Count Register",
        handles.bport1,
        20,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.tcfifo.value),
        True
    );
    ppmCreateRegister("ab_rwfifo",
        "UART FIFO Receive Watermark Register",
        handles.bport1,
        21,
        1,
        read_8,
        writeRWFIFO,
        view8,
        &(bport1_ab_data.rwfifo.value),
        True
    );
    ppmCreateRegister("ab_rcfifo",
        "UART FIFO Receive Count Register",
        handles.bport1,
        22,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.rcfifo.value),
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
        bport1_ab_data.rcfifo.value = 0x0;
        bport1_ab_data.rwfifo.value = 0x1;
        bport1_ab_data.tcfifo.value = 0x0;
        bport1_ab_data.twfifo.value = 0x0;
        bport1_ab_data.sfifo.value = 0xc0;
        bport1_ab_data.cfifo.value = 0x0;
        bport1_ab_data.pfifo.value = 0x22;
        bport1_ab_data.infrared.value = 0x0;
        bport1_ab_data.modem.value = 0x0;
        bport1_ab_data.ed.value = 0x0;
        bport1_ab_data.c5.value = 0x0;
        bport1_ab_data.c4.value = 0x0;
        bport1_ab_data.ma2.value = 0x0;
        bport1_ab_data.ma1.value = 0x0;
        bport1_ab_data.d.value = 0x0;
        bport1_ab_data.c3.value = 0x0;
        bport1_ab_data.s2.value = 0x0;
        bport1_ab_data.s1.value = 0xc0;
        bport1_ab_data.c2.value = 0x0;
        bport1_ab_data.c1.value = 0x0;
        bport1_ab_data.bdl.value = 0x4;
        bport1_ab_data.bdh.value = 0x0;
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
        ppmDocAddText(doc2_node, "Freescale UART - Supports interrupts and fifos.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "\nError conditions, DMA, ISO7816 mode and Wake up are not supported.\n");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Freescale Kinetis Peripheral User Guide");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

