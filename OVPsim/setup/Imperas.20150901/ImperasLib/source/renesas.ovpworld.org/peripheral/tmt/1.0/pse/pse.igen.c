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

TMTP0_reg0_dataT TMTP0_reg0_data;

TMTP0_reg1_dataT TMTP0_reg1_data;

TMTP1_reg0_dataT TMTP1_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "tmt", "Example");
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
    handles.TMTP0 = ppmCreateSlaveBusPort("TMTP0", 16);

    handles.TMTP1 = ppmCreateSlaveBusPort("TMTP1", 2);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_CTL0",
        0,
        handles.TMTP0,
        0,
        1,
        read_8,
        writeCTL0,
        view8,
        &(TMTP0_reg0_data.CTL0.value),
        True
    );
    ppmCreateRegister("reg0_CTL1",
        0,
        handles.TMTP0,
        1,
        1,
        read_8,
        writeCTL1,
        view8,
        &(TMTP0_reg0_data.CTL1.value),
        True
    );
    ppmCreateRegister("reg0_CTL2",
        0,
        handles.TMTP0,
        2,
        1,
        read_8,
        writeCTL2,
        view8,
        &(TMTP0_reg0_data.CTL2.value),
        True
    );
    ppmCreateRegister("reg0_IOC0",
        0,
        handles.TMTP0,
        3,
        1,
        read_8,
        writeIOC0,
        view8,
        &(TMTP0_reg0_data.IOC0.value),
        True
    );
    ppmCreateRegister("reg0_IOC1",
        0,
        handles.TMTP0,
        4,
        1,
        read_8,
        writeIOC1,
        view8,
        &(TMTP0_reg0_data.IOC1.value),
        True
    );
    ppmCreateRegister("reg0_IOC2",
        0,
        handles.TMTP0,
        5,
        1,
        read_8,
        writeIOC2,
        view8,
        &(TMTP0_reg0_data.IOC2.value),
        True
    );
    ppmCreateRegister("reg0_IOC3",
        0,
        handles.TMTP0,
        6,
        1,
        read_8,
        writeIOC3,
        view8,
        &(TMTP0_reg0_data.IOC3.value),
        True
    );
    ppmCreateRegister("reg0_OPT0",
        0,
        handles.TMTP0,
        7,
        1,
        read_8,
        writeOPT0,
        view8,
        &(TMTP0_reg0_data.OPT0.value),
        True
    );
    ppmCreateRegister("reg0_OPT1",
        0,
        handles.TMTP0,
        8,
        1,
        read_8,
        writeOPT1,
        view8,
        &(TMTP0_reg0_data.OPT1.value),
        True
    );
    ppmCreateRegister("reg0_OPT2",
        0,
        handles.TMTP0,
        9,
        1,
        read_8,
        writeOPT2,
        view8,
        &(TMTP0_reg0_data.OPT2.value),
        True
    );
    ppmCreateRegister("reg1_CCR0",
        0,
        handles.TMTP0,
        10,
        2,
        read_16,
        writeCCR0,
        view16,
        &(TMTP0_reg1_data.CCR0.value),
        True
    );
    ppmCreateRegister("reg1_CCR1",
        0,
        handles.TMTP0,
        12,
        2,
        read_16,
        writeCCR1,
        view16,
        &(TMTP0_reg1_data.CCR1.value),
        True
    );
    ppmCreateRegister("reg1_CNT",
        0,
        handles.TMTP0,
        14,
        2,
        readCNT,
        0,
        view16,
        &(TMTP0_reg1_data.CNT.value),
        True
    );

    ppmCreateRegister("reg0_TCW",
        0,
        handles.TMTP1,
        0,
        2,
        read_16,
        writeTCW,
        view16,
        &(TMTP1_reg0_data.TCW.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.TOT0, value);

    handles.TOT0 = ppmOpenNetPort("TOT0");

// To write to this net, use ppmWriteNet(handles.TOT1, value);

    handles.TOT1 = ppmOpenNetPort("TOT1");

// To write to this net, use ppmWriteNet(handles.TTTTO0, value);

    handles.TTTTO0 = ppmOpenNetPort("TTTTO0");

// To write to this net, use ppmWriteNet(handles.TTTT01, value);

    handles.TTTT01 = ppmOpenNetPort("TTTT01");

// To write to this net, use ppmWriteNet(handles.TTTICC0, value);

    handles.TTTICC0 = ppmOpenNetPort("TTTICC0");

// To write to this net, use ppmWriteNet(handles.TTTICC1, value);

    handles.TTTICC1 = ppmOpenNetPort("TTTICC1");

// To write to this net, use ppmWriteNet(handles.TTTEQC0, value);

    handles.TTTEQC0 = ppmOpenNetPort("TTTEQC0");

// To write to this net, use ppmWriteNet(handles.TTTEQC1, value);

    handles.TTTEQC1 = ppmOpenNetPort("TTTEQC1");

// To write to this net, use ppmWriteNet(handles.INTTTCC0, value);

    handles.INTTTCC0 = ppmOpenNetPort("INTTTCC0");

// To write to this net, use ppmWriteNet(handles.INTTTCC1, value);

    handles.INTTTCC1 = ppmOpenNetPort("INTTTCC1");

// To write to this net, use ppmWriteNet(handles.INTTTOV, value);

    handles.INTTTOV = ppmOpenNetPort("INTTTOV");

// To write to this net, use ppmWriteNet(handles.INTTTEC, value);

    handles.INTTTEC = ppmOpenNetPort("INTTTEC");

    handles.TIT0 = ppmOpenNetPort("TIT0");
    if (handles.TIT0) {
        ppmInstallNetCallback(handles.TIT0, P_TIT0, (void*)0);
    }

    handles.TIT1 = ppmOpenNetPort("TIT1");
    if (handles.TIT1) {
        ppmInstallNetCallback(handles.TIT1, P_TIT1, (void*)0);
    }

    handles.TEVTT = ppmOpenNetPort("TEVTT");
    if (handles.TEVTT) {
        ppmInstallNetCallback(handles.TEVTT, P_TEVTT, (void*)0);
    }

    handles.TTRGT = ppmOpenNetPort("TTRGT");
    if (handles.TTRGT) {
        ppmInstallNetCallback(handles.TTRGT, P_TTRGT, (void*)0);
    }

    handles.TENCT0 = ppmOpenNetPort("TENCT0");
    if (handles.TENCT0) {
        ppmInstallNetCallback(handles.TENCT0, P_TENCT0, (void*)0);
    }

    handles.TENCT1 = ppmOpenNetPort("TENCT1");
    if (handles.TENCT1) {
        ppmInstallNetCallback(handles.TENCT1, P_TENCT1, (void*)0);
    }

    handles.TECRT = ppmOpenNetPort("TECRT");
    if (handles.TECRT) {
        ppmInstallNetCallback(handles.TECRT, P_TECRT, (void*)0);
    }

    handles.TTTTI0 = ppmOpenNetPort("TTTTI0");
    if (handles.TTTTI0) {
        ppmInstallNetCallback(handles.TTTTI0, P_TTTTI0, (void*)0);
    }

    handles.TTTTI1 = ppmOpenNetPort("TTTTI1");
    if (handles.TTTTI1) {
        ppmInstallNetCallback(handles.TTTTI1, P_TTTTI1, (void*)0);
    }

    handles.TTTENC0 = ppmOpenNetPort("TTTENC0");
    if (handles.TTTENC0) {
        ppmInstallNetCallback(handles.TTTENC0, P_TTTENC0, (void*)0);
    }

    handles.TTTENC1 = ppmOpenNetPort("TTTENC1");
    if (handles.TTTENC1) {
        ppmInstallNetCallback(handles.TTTENC1, P_TTTENC1, (void*)0);
    }

    handles.TTTTRG = ppmOpenNetPort("TTTTRG");
    if (handles.TTTTRG) {
        ppmInstallNetCallback(handles.TTTTRG, P_TTTTRG, (void*)0);
    }

    handles.TTTEVT = ppmOpenNetPort("TTTEVT");
    if (handles.TTTEVT) {
        ppmInstallNetCallback(handles.TTTEVT, P_TTTEVT, (void*)0);
    }

    handles.TTTECR = ppmOpenNetPort("TTTECR");
    if (handles.TTTECR) {
        ppmInstallNetCallback(handles.TTTECR, P_TTTECR, (void*)0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        TMTP1_reg0_data.TCW.value = 0x0;
        TMTP0_reg1_data.CNT.value = 0x0;
        TMTP0_reg1_data.CCR1.value = 0x0;
        TMTP0_reg1_data.CCR0.value = 0x0;
        TMTP0_reg0_data.OPT2.value = 0x0;
        TMTP0_reg0_data.OPT1.value = 0x0;
        TMTP0_reg0_data.OPT0.value = 0x0;
        TMTP0_reg0_data.IOC3.value = 0x0;
        TMTP0_reg0_data.IOC2.value = 0x0;
        TMTP0_reg0_data.IOC1.value = 0x0;
        TMTP0_reg0_data.IOC0.value = 0x0;
        TMTP0_reg0_data.CTL2.value = 0x0;
        TMTP0_reg0_data.CTL1.value = 0x0;
        TMTP0_reg0_data.CTL0.value = 0x0;
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
        ppmDocAddText(doc_12_node, "Renesas TMT Timer/Event Counter T");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Status of Modes\n- Interval Timer Mode                  - Supported\n- External Event Count Mode            - Unsupported\n- External Trigger Pulse Output Mode   - Unsupported\n- One-Shot Pulse Mode                  - Unsupported\n- PWM Mode                             - Unsupported\n- Free-Running Mode                    - Supported\n- Pulse Width Measurement Mode         - Unsupported\n- Triangular Wave PWM Mode             - Unsupported\n- Encoder Compare Mode                 - Unsupported\n- Encoder Capture Mode                 - Unsupported\n- Encoder Capture Compare Mode         - Unsupported\n- Offset Trigger Generation Mode       - Unsupported\n");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

