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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UartInterface", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_dr",
        "UARTDR",
        handles.bport1,
        0,
        4,
        readDR,
        writeDR,
        view32,
        &(bport1_ab_data.dr.value),
        True
    );
    ppmCreateRegister("ab_rsrecr",
        "UARTRSRECR",
        handles.bport1,
        4,
        4,
        readSRRECR,
        writeSRRECR,
        view32,
        &(bport1_ab_data.rsrecr.value),
        True
    );
    ppmCreateRegister("ab_fr",
        "UARTFR",
        handles.bport1,
        24,
        4,
        readSR,
        0,
        view32,
        &(bport1_ab_data.fr.value),
        True
    );
    ppmCreateRegister("ab_fbrd",
        "UARTFBDR",
        handles.bport1,
        36,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.fbrd.value),
        True
    );
    ppmCreateRegister("ab_ibrd",
        "UARTIBRD",
        handles.bport1,
        40,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.ibrd.value),
        True
    );
    ppmCreateRegister("ab_lcrh",
        "UARTLCRH",
        handles.bport1,
        44,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.lcrh.value),
        True
    );
    ppmCreateRegister("ab_ctl",
        "UARTLCTL",
        handles.bport1,
        48,
        4,
        readCTL,
        writeCTL,
        view32,
        &(bport1_ab_data.ctl.value),
        True
    );
    ppmCreateRegister("ab_ifls",
        "UARTIFLS",
        handles.bport1,
        52,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.ifls.value),
        True
    );
    ppmCreateRegister("ab_im",
        "UARTIM",
        handles.bport1,
        56,
        4,
        readIM,
        writeIM,
        view32,
        &(bport1_ab_data.im.value),
        True
    );
    ppmCreateRegister("ab_ris",
        "UARTRIS",
        handles.bport1,
        60,
        4,
        readRIS,
        writeRIS,
        view32,
        &(bport1_ab_data.ris.value),
        True
    );
    ppmCreateRegister("ab_mis",
        "UARTMIS",
        handles.bport1,
        64,
        4,
        readMIS,
        writeMIS,
        view32,
        &(bport1_ab_data.mis.value),
        True
    );
    ppmCreateRegister("ab_icr",
        "UARTICR",
        handles.bport1,
        68,
        4,
        readICR,
        writeICR,
        view32,
        &(bport1_ab_data.icr.value),
        True
    );
    ppmCreateRegister("ab_pid0",
        0,
        handles.bport1,
        4048,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid0.value),
        True
    );
    ppmCreateRegister("ab_pid1",
        0,
        handles.bport1,
        4052,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid1.value),
        True
    );
    ppmCreateRegister("ab_pid2",
        0,
        handles.bport1,
        4056,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid2.value),
        True
    );
    ppmCreateRegister("ab_pid3",
        0,
        handles.bport1,
        4060,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid3.value),
        True
    );
    ppmCreateRegister("ab_pid4",
        0,
        handles.bport1,
        4064,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid4.value),
        True
    );
    ppmCreateRegister("ab_pid5",
        0,
        handles.bport1,
        4068,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid5.value),
        True
    );
    ppmCreateRegister("ab_pid6",
        0,
        handles.bport1,
        4072,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid6.value),
        True
    );
    ppmCreateRegister("ab_pid7",
        0,
        handles.bport1,
        4076,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pid7.value),
        True
    );
    ppmCreateRegister("ab_cid0",
        0,
        handles.bport1,
        4080,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.cid0.value),
        True
    );
    ppmCreateRegister("ab_cid1",
        0,
        handles.bport1,
        4084,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.cid1.value),
        True
    );
    ppmCreateRegister("ab_cid2",
        0,
        handles.bport1,
        4088,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.cid2.value),
        True
    );
    ppmCreateRegister("ab_cid3",
        0,
        handles.bport1,
        4092,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.cid3.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq, value);

    handles.irq = ppmOpenNetPort("irq");

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.cid3.value = 0xb1;
        bport1_ab_data.cid2.value = 0x5;
        bport1_ab_data.cid1.value = 0xf0;
        bport1_ab_data.cid0.value = 0xd;
        bport1_ab_data.pid7.value = 0x0;
        bport1_ab_data.pid6.value = 0x0;
        bport1_ab_data.pid5.value = 0x0;
        bport1_ab_data.pid4.value = 0x0;
        bport1_ab_data.pid3.value = 0x1;
        bport1_ab_data.pid2.value = 0x18;
        bport1_ab_data.pid1.value = 0x0;
        bport1_ab_data.pid0.value = 0x11;
        bport1_ab_data.icr.value = 0x0;
        bport1_ab_data.mis.value = 0x0;
        bport1_ab_data.ris.value = 0xf;
        bport1_ab_data.im.value = 0x0;
        bport1_ab_data.ifls.value = 0x12;
        bport1_ab_data.ctl.value = 0x0;
        bport1_ab_data.lcrh.value = 0x0;
        bport1_ab_data.ibrd.value = 0x0;
        bport1_ab_data.fbrd.value = 0x0;
        bport1_ab_data.fr.value = 0x90;
        bport1_ab_data.rsrecr.value = 0x0;
        bport1_ab_data.dr.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\nUART: Universal Asynchronous Receiver Transmitter\nThis model contains an accurate Register set interface for the TI Stellaris ARM Cortex-M3 based device.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "\nThe functionality of this model is limited. \nBasic status flag setting allows character reception and transmission.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "\nFreeRTOS Cortex-M3 / GCC Port LM3S102 with GCC for Luminary Micros Stellaris microcontrollers\nhttp://www.freertos.org/portcortexgcc.html");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

