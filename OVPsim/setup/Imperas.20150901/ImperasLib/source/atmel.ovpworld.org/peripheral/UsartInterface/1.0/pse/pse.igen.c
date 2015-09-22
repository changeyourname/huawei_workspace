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

apb_REG_dataT apb_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UsartInterface", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.apb = ppmCreateSlaveBusPort("apb", 16384);
    if (!handles.apb) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'apb'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("REG_US_CR",
        0,
        handles.apb,
        0,
        4,
        0,
        US_CR_wcb,
        view32,
        &(apb_REG_data.US_CR.value),
        True
    );
    ppmCreateRegister("REG_US_MR",
        0,
        handles.apb,
        4,
        4,
        read_32,
        US_MR_wcb,
        view32,
        &(apb_REG_data.US_MR.value),
        True
    );
    ppmCreateRegister("REG_US_IER",
        0,
        handles.apb,
        8,
        4,
        0,
        US_IER_wcb,
        view32,
        &(apb_REG_data.US_IER.value),
        True
    );
    ppmCreateRegister("REG_US_IDR",
        0,
        handles.apb,
        12,
        4,
        0,
        US_IDR_wcb,
        view32,
        &(apb_REG_data.US_IDR.value),
        True
    );
    ppmCreateRegister("REG_US_IMR",
        0,
        handles.apb,
        16,
        4,
        read_32,
        0,
        view32,
        &(apb_REG_data.US_IMR.value),
        True
    );
    ppmCreateRegister("REG_US_CSR",
        0,
        handles.apb,
        20,
        4,
        US_RHR_rcb,
        0,
        view32,
        &(apb_REG_data.US_CSR.value),
        True
    );
    ppmCreateRegister("REG_US_RHR",
        0,
        handles.apb,
        24,
        4,
        read_32,
        0,
        view32,
        &(apb_REG_data.US_RHR.value),
        True
    );
    ppmCreateRegister("REG_US_THR",
        0,
        handles.apb,
        28,
        4,
        0,
        US_THR_wcb,
        view32,
        &(apb_REG_data.US_THR.value),
        True
    );
    ppmCreateRegister("REG_US_BRGR",
        0,
        handles.apb,
        32,
        4,
        read_32,
        US_BRGR_wcb,
        view32,
        &(apb_REG_data.US_BRGR.value),
        True
    );
    ppmCreateRegister("REG_US_RTOR",
        0,
        handles.apb,
        36,
        4,
        read_32,
        US_RTOR_wcb,
        view32,
        &(apb_REG_data.US_RTOR.value),
        True
    );
    ppmCreateRegister("REG_US_TTGR",
        0,
        handles.apb,
        40,
        4,
        read_32,
        US_TTGR_wcb,
        view32,
        &(apb_REG_data.US_TTGR.value),
        True
    );
    ppmCreateRegister("REG_US_RPR",
        0,
        handles.apb,
        48,
        4,
        read_32,
        US_RPR_wcb,
        view32,
        &(apb_REG_data.US_RPR.value),
        True
    );
    ppmCreateRegister("REG_US_RCR",
        0,
        handles.apb,
        52,
        4,
        read_32,
        US_RCR_wcb,
        view32,
        &(apb_REG_data.US_RCR.value),
        True
    );
    ppmCreateRegister("REG_US_TPR",
        0,
        handles.apb,
        56,
        4,
        read_32,
        US_TPR_wcb,
        view32,
        &(apb_REG_data.US_TPR.value),
        True
    );
    ppmCreateRegister("REG_US_TCR",
        0,
        handles.apb,
        60,
        4,
        read_32,
        US_TCR_wcb,
        view32,
        &(apb_REG_data.US_TCR.value),
        True
    );

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.asb = ppmOpenAddressSpace("asb");
    if (!handles.asb) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'asb'");
    }
}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.IRQ, value);

    handles.IRQ = ppmOpenNetPort("IRQ");

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        apb_REG_data.US_TCR.value = 0x0;
        apb_REG_data.US_TPR.value = 0x0;
        apb_REG_data.US_RCR.value = 0x0;
        apb_REG_data.US_RPR.value = 0x0;
        apb_REG_data.US_TTGR.value = 0x0;
        apb_REG_data.US_RTOR.value = 0x0;
        apb_REG_data.US_BRGR.value = 0x0;
        apb_REG_data.US_THR.value = 0x0;
        apb_REG_data.US_RHR.value = 0x0;
        apb_REG_data.US_CSR.value = 0x18;
        apb_REG_data.US_IMR.value = 0x0;
        apb_REG_data.US_IDR.value = 0x0;
        apb_REG_data.US_IER.value = 0x0;
        apb_REG_data.US_MR.value = 0x0;
        apb_REG_data.US_CR.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    installNetPorts();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\nUSART: Universal Synchronous/Asynchronous Receiver Transmitter\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe USART has its own baud rate generator, and two dedicated Peripheral Data Controller\nchannels. The data format includes a start bit, up to 8 data bits, an optional programmable parity\nbit and up to 2 stop bits.\nThe USART also features a Receiver Timeout register, facilitating variable length frame support\nwhen it is working with the PDC, and a Time-guard register, used when interfacing with slow\nremote equipment.\nfor more information visit http://www.atmel.com/products/at91\n");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D–ATARM–08/02");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

