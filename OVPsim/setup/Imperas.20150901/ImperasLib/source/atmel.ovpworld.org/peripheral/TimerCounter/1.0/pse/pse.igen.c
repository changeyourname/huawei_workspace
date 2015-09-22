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

bp1_REG_dataT bp1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "TimerCounter", "Example");
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
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 16384);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("REG_TC_CCR0",
        0,
        handles.bp1,
        0,
        4,
        0,
        TC_CCR_wcb0,
        view32,
        &(bp1_REG_data.TC_CCR0.value),
        True
    );
    ppmCreateRegister("REG_TC_CMR0",
        0,
        handles.bp1,
        4,
        4,
        read_32,
        TC_CMR_wcb0,
        view32,
        &(bp1_REG_data.TC_CMR0.value),
        True
    );
    ppmCreateRegister("REG_TC_CVR0",
        0,
        handles.bp1,
        16,
        4,
        read_32,
        TC_CVR_wcb0,
        view32,
        &(bp1_REG_data.TC_CVR0.value),
        True
    );
    ppmCreateRegister("REG_TC_RA0",
        0,
        handles.bp1,
        20,
        4,
        read_32,
        TC_RA_wcb0,
        view32,
        &(bp1_REG_data.TC_RA0.value),
        True
    );
    ppmCreateRegister("REG_TC_RB0",
        0,
        handles.bp1,
        24,
        4,
        read_32,
        TC_RB_wcb0,
        view32,
        &(bp1_REG_data.TC_RB0.value),
        True
    );
    ppmCreateRegister("REG_TC_RC0",
        0,
        handles.bp1,
        28,
        4,
        read_32,
        TC_RC_wcb0,
        view32,
        &(bp1_REG_data.TC_RC0.value),
        True
    );
    ppmCreateRegister("REG_TC_SR0",
        0,
        handles.bp1,
        32,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.TC_SR0.value),
        True
    );
    ppmCreateRegister("REG_TC_IER0",
        0,
        handles.bp1,
        36,
        4,
        0,
        TC_IER_wcb0,
        view32,
        &(bp1_REG_data.TC_IER0.value),
        True
    );
    ppmCreateRegister("REG_TC_IDR0",
        0,
        handles.bp1,
        40,
        4,
        0,
        TC_IDR_wcb0,
        view32,
        &(bp1_REG_data.TC_IDR0.value),
        True
    );
    ppmCreateRegister("REG_TC_IMR0",
        0,
        handles.bp1,
        44,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.TC_IMR0.value),
        True
    );
    ppmCreateRegister("REG_TC_CCR1",
        0,
        handles.bp1,
        64,
        4,
        0,
        TC_CCR_wcb1,
        view32,
        &(bp1_REG_data.TC_CCR1.value),
        True
    );
    ppmCreateRegister("REG_TC_CMR1",
        0,
        handles.bp1,
        68,
        4,
        read_32,
        TC_CMR_wcb1,
        view32,
        &(bp1_REG_data.TC_CMR1.value),
        True
    );
    ppmCreateRegister("REG_TC_CVR1",
        0,
        handles.bp1,
        80,
        4,
        read_32,
        TC_CVR_wcb1,
        view32,
        &(bp1_REG_data.TC_CVR1.value),
        True
    );
    ppmCreateRegister("REG_TC_RA1",
        0,
        handles.bp1,
        84,
        4,
        read_32,
        TC_RA_wcb1,
        view32,
        &(bp1_REG_data.TC_RA1.value),
        True
    );
    ppmCreateRegister("REG_TC_RB1",
        0,
        handles.bp1,
        88,
        4,
        read_32,
        TC_RB_wcb1,
        view32,
        &(bp1_REG_data.TC_RB1.value),
        True
    );
    ppmCreateRegister("REG_TC_RC1",
        0,
        handles.bp1,
        92,
        4,
        read_32,
        TC_RC_wcb1,
        view32,
        &(bp1_REG_data.TC_RC1.value),
        True
    );
    ppmCreateRegister("REG_TC_SR1",
        0,
        handles.bp1,
        96,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.TC_SR1.value),
        True
    );
    ppmCreateRegister("REG_TC_IER1",
        0,
        handles.bp1,
        100,
        4,
        0,
        TC_IER_wcb1,
        view32,
        &(bp1_REG_data.TC_IER1.value),
        True
    );
    ppmCreateRegister("REG_TC_IDR1",
        0,
        handles.bp1,
        104,
        4,
        0,
        TC_IDR_wcb1,
        view32,
        &(bp1_REG_data.TC_IDR1.value),
        True
    );
    ppmCreateRegister("REG_TC_IMR1",
        0,
        handles.bp1,
        108,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.TC_IMR1.value),
        True
    );
    ppmCreateRegister("REG_TC_CCR2",
        0,
        handles.bp1,
        128,
        4,
        0,
        TC_CCR_wcb2,
        view32,
        &(bp1_REG_data.TC_CCR2.value),
        True
    );
    ppmCreateRegister("REG_TC_CMR2",
        0,
        handles.bp1,
        132,
        4,
        read_32,
        TC_CMR_wcb2,
        view32,
        &(bp1_REG_data.TC_CMR2.value),
        True
    );
    ppmCreateRegister("REG_TC_CVR2",
        0,
        handles.bp1,
        144,
        4,
        read_32,
        TC_CVR_wcb2,
        view32,
        &(bp1_REG_data.TC_CVR2.value),
        True
    );
    ppmCreateRegister("REG_TC_RA2",
        0,
        handles.bp1,
        148,
        4,
        read_32,
        TC_RA_wcb2,
        view32,
        &(bp1_REG_data.TC_RA2.value),
        True
    );
    ppmCreateRegister("REG_TC_RB2",
        0,
        handles.bp1,
        152,
        4,
        read_32,
        TC_RB_wcb2,
        view32,
        &(bp1_REG_data.TC_RB2.value),
        True
    );
    ppmCreateRegister("REG_TC_RC2",
        0,
        handles.bp1,
        156,
        4,
        read_32,
        TC_RC_wcb2,
        view32,
        &(bp1_REG_data.TC_RC2.value),
        True
    );
    ppmCreateRegister("REG_TC_SR2",
        0,
        handles.bp1,
        160,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.TC_SR2.value),
        True
    );
    ppmCreateRegister("REG_TC_IER2",
        0,
        handles.bp1,
        164,
        4,
        0,
        TC_IER_wcb2,
        view32,
        &(bp1_REG_data.TC_IER2.value),
        True
    );
    ppmCreateRegister("REG_TC_IDR2",
        0,
        handles.bp1,
        168,
        4,
        0,
        TC_IDR_wcb2,
        view32,
        &(bp1_REG_data.TC_IDR2.value),
        True
    );
    ppmCreateRegister("REG_TC_IMR2",
        0,
        handles.bp1,
        172,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.TC_IMR2.value),
        True
    );
    ppmCreateRegister("REG_TC_BCR",
        0,
        handles.bp1,
        192,
        4,
        0,
        TC_BCR_wcb,
        view32,
        &(bp1_REG_data.TC_BCR.value),
        True
    );
    ppmCreateRegister("REG_TC_BMR",
        0,
        handles.bp1,
        196,
        4,
        0,
        TC_BMR_wcb,
        view32,
        &(bp1_REG_data.TC_BMR.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.IRQ0, value);

    handles.IRQ0 = ppmOpenNetPort("IRQ0");

// To write to this net, use ppmWriteNet(handles.IRQ1, value);

    handles.IRQ1 = ppmOpenNetPort("IRQ1");

// To write to this net, use ppmWriteNet(handles.IRQ2, value);

    handles.IRQ2 = ppmOpenNetPort("IRQ2");

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.TC_BMR.value = 0x0;
        bp1_REG_data.TC_BCR.value = 0x0;
        bp1_REG_data.TC_IMR2.value = 0x0;
        bp1_REG_data.TC_IDR2.value = 0x0;
        bp1_REG_data.TC_IER2.value = 0x0;
        bp1_REG_data.TC_SR2.value = 0x0;
        bp1_REG_data.TC_RC2.value = 0x0;
        bp1_REG_data.TC_RB2.value = 0x0;
        bp1_REG_data.TC_RA2.value = 0x0;
        bp1_REG_data.TC_CVR2.value = 0x0;
        bp1_REG_data.TC_CMR2.value = 0x0;
        bp1_REG_data.TC_CCR2.value = 0x0;
        bp1_REG_data.TC_IMR1.value = 0x0;
        bp1_REG_data.TC_IDR1.value = 0x0;
        bp1_REG_data.TC_IER1.value = 0x0;
        bp1_REG_data.TC_SR1.value = 0x0;
        bp1_REG_data.TC_RC1.value = 0x0;
        bp1_REG_data.TC_RB1.value = 0x0;
        bp1_REG_data.TC_RA1.value = 0x0;
        bp1_REG_data.TC_CVR1.value = 0x0;
        bp1_REG_data.TC_CMR1.value = 0x0;
        bp1_REG_data.TC_CCR1.value = 0x0;
        bp1_REG_data.TC_IMR0.value = 0x0;
        bp1_REG_data.TC_IDR0.value = 0x0;
        bp1_REG_data.TC_IER0.value = 0x0;
        bp1_REG_data.TC_SR0.value = 0x0;
        bp1_REG_data.TC_RC0.value = 0x0;
        bp1_REG_data.TC_RB0.value = 0x0;
        bp1_REG_data.TC_RA0.value = 0x0;
        bp1_REG_data.TC_CVR0.value = 0x0;
        bp1_REG_data.TC_CMR0.value = 0x0;
        bp1_REG_data.TC_CCR0.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\nTC: Timer Counter\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe Timer Counter block includes three identical 16-bit timer\ncounter channels. Each channel can be independently programmed to perform a wide range of\nfunctions including frequency measurement, event counting, interval measurement, pulse generation,\ndelay timing and pulse width modulation.\nThe Timer Counter can be used in Capture or Waveform mode, and all three counter channels\ncan be started simultaneously and chained together.\nfor more information visit http://www.atmel.com/products/at91\n");
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
    return 0;
}

