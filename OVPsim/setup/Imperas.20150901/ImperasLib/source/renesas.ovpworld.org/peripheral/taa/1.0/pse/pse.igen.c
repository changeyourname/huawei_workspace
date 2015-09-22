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

TAAP0_reg0_dataT TAAP0_reg0_data;

TAAP0_reg1_dataT TAAP0_reg1_data;

TAAP0_reg2_dataT TAAP0_reg2_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "taa", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.TAAP0 = ppmCreateSlaveBusPort("TAAP0", 16);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_CTL0",
        0,
        handles.TAAP0,
        0,
        1,
        read_8,
        writeCTL0,
        view8,
        &(TAAP0_reg0_data.CTL0.value),
        True
    );
    ppmCreateRegister("reg0_CTL1",
        0,
        handles.TAAP0,
        1,
        1,
        read_8,
        writeCTL1,
        view8,
        &(TAAP0_reg0_data.CTL1.value),
        True
    );
    ppmCreateRegister("reg0_IOC0",
        0,
        handles.TAAP0,
        2,
        1,
        read_8,
        writeIOC0,
        view8,
        &(TAAP0_reg0_data.IOC0.value),
        True
    );
    ppmCreateRegister("reg0_IOC1",
        0,
        handles.TAAP0,
        3,
        1,
        read_8,
        writeIOC1,
        view8,
        &(TAAP0_reg0_data.IOC1.value),
        True
    );
    ppmCreateRegister("reg0_IOC2",
        0,
        handles.TAAP0,
        4,
        1,
        read_8,
        writeIOC2,
        view8,
        &(TAAP0_reg0_data.IOC2.value),
        True
    );
    ppmCreateRegister("reg0_OPT0",
        0,
        handles.TAAP0,
        5,
        1,
        read_8,
        writeOPT0,
        view8,
        &(TAAP0_reg0_data.OPT0.value),
        True
    );
    ppmCreateRegister("reg1_CCR0",
        0,
        handles.TAAP0,
        6,
        2,
        read_16,
        writeCCR0,
        view16,
        &(TAAP0_reg1_data.CCR0.value),
        True
    );
    ppmCreateRegister("reg1_CCR1",
        0,
        handles.TAAP0,
        8,
        2,
        read_16,
        writeCCR1,
        view16,
        &(TAAP0_reg1_data.CCR1.value),
        True
    );
    ppmCreateRegister("reg1_CNT",
        0,
        handles.TAAP0,
        10,
        2,
        readCNT,
        0,
        view16,
        &(TAAP0_reg1_data.CNT.value),
        True
    );
    ppmCreateRegister("reg2_IOC4",
        0,
        handles.TAAP0,
        12,
        1,
        read_8,
        writeIOC4,
        view8,
        &(TAAP0_reg2_data.IOC4.value),
        True
    );
    ppmCreateRegister("reg2_SVC",
        0,
        handles.TAAP0,
        14,
        1,
        read_8,
        writeSVC,
        view8,
        &(TAAP0_reg2_data.SVC.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.TOAA0, value);

    handles.TOAA0 = ppmOpenNetPort("TOAA0");

// To write to this net, use ppmWriteNet(handles.TOAA1, value);

    handles.TOAA1 = ppmOpenNetPort("TOAA1");

// To write to this net, use ppmWriteNet(handles.INTTAAOV, value);

    handles.INTTAAOV = ppmOpenNetPort("INTTAAOV");

// To write to this net, use ppmWriteNet(handles.INTTAACC0, value);

    handles.INTTAACC0 = ppmOpenNetPort("INTTAACC0");

// To write to this net, use ppmWriteNet(handles.INTTAACC1, value);

    handles.INTTAACC1 = ppmOpenNetPort("INTTAACC1");

    handles.TIAA0 = ppmOpenNetPort("TIAA0");
    if (handles.TIAA0) {
        ppmInstallNetCallback(handles.TIAA0, P_TIAA0, (void*)0);
    }

    handles.TIAA1 = ppmOpenNetPort("TIAA1");
    if (handles.TIAA1) {
        ppmInstallNetCallback(handles.TIAA1, P_TIAA1, (void*)0);
    }

    handles.TTRGAA = ppmOpenNetPort("TTRGAA");
    if (handles.TTRGAA) {
        ppmInstallNetCallback(handles.TTRGAA, P_TTRGAA, (void*)0);
    }

    handles.TEVTAA = ppmOpenNetPort("TEVTAA");
    if (handles.TEVTAA) {
        ppmInstallNetCallback(handles.TEVTAA, P_TEVTAA, (void*)0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        TAAP0_reg2_data.SVC.value = 0x0;
        TAAP0_reg2_data.IOC4.value = 0x0;
        TAAP0_reg1_data.CNT.value = 0x0;
        TAAP0_reg1_data.CCR1.value = 0x0;
        TAAP0_reg1_data.CCR0.value = 0x0;
        TAAP0_reg0_data.OPT0.value = 0x0;
        TAAP0_reg0_data.IOC2.value = 0x0;
        TAAP0_reg0_data.IOC1.value = 0x0;
        TAAP0_reg0_data.IOC0.value = 0x0;
        TAAP0_reg0_data.CTL1.value = 0x0;
        TAAP0_reg0_data.CTL0.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas TAA Timer/Event Counter AA");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Status of Modes\n- Interval Timer Mode                  - Supported\n- External Event Count Mode            - Unsupported\n- External Trigger Pulse Output Mode   - Unsupported\n- One-Shot Pulse Mode                  - Unsupported\n- PWM Mode                             - Unsupported\n- Free-Running Mode                    - Supported\n- Pulse Width Measurement Mode         - Unsupported\n");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

