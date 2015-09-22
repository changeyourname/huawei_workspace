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

TMSP0_reg0_dataT TMSP0_reg0_data;

TMSP0_reg1_dataT TMSP0_reg1_data;

TMSP0_reg2_dataT TMSP0_reg2_data;

TMSP0_reg3_dataT TMSP0_reg3_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "tms", "Example");
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
    handles.TMSP0 = ppmCreateSlaveBusPort("TMSP0", 42);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_CTL0",
        0,
        handles.TMSP0,
        0,
        1,
        read_8,
        writeCTL0,
        view8,
        &(TMSP0_reg0_data.CTL0.value),
        True
    );
    ppmCreateRegister("reg0_CTL1",
        0,
        handles.TMSP0,
        1,
        1,
        read_8,
        writeCTL1,
        view8,
        &(TMSP0_reg0_data.CTL1.value),
        True
    );
    ppmCreateRegister("reg1_IOC0",
        0,
        handles.TMSP0,
        2,
        2,
        readIOC0,
        writeIOC0,
        view16,
        &(TMSP0_reg1_data.IOC0.value),
        True
    );
    ppmCreateRegister("reg2_IOC2",
        0,
        handles.TMSP0,
        4,
        1,
        read_8,
        writeIOC2,
        view8,
        &(TMSP0_reg2_data.IOC2.value),
        True
    );
    ppmCreateRegister("reg2_IOC4",
        0,
        handles.TMSP0,
        5,
        1,
        read_8,
        writeIOC4,
        view8,
        &(TMSP0_reg2_data.IOC4.value),
        True
    );
    ppmCreateRegister("reg2_OPT0",
        0,
        handles.TMSP0,
        6,
        1,
        read_8,
        writeOPT0,
        view8,
        &(TMSP0_reg2_data.OPT0.value),
        True
    );
    ppmCreateRegister("reg2_OPT4",
        0,
        handles.TMSP0,
        8,
        1,
        read_8,
        writeOPT4,
        view8,
        &(TMSP0_reg2_data.OPT4.value),
        True
    );
    ppmCreateRegister("reg2_OPT5",
        0,
        handles.TMSP0,
        9,
        1,
        read_8,
        writeOPT5,
        view8,
        &(TMSP0_reg2_data.OPT5.value),
        True
    );
    ppmCreateRegister("reg2_OPT7",
        0,
        handles.TMSP0,
        7,
        1,
        read_8,
        writeOPT7,
        view8,
        &(TMSP0_reg2_data.OPT7.value),
        True
    );
    ppmCreateRegister("reg3_OPT1",
        0,
        handles.TMSP0,
        10,
        2,
        readOPT1,
        writeOPT1,
        view16,
        &(TMSP0_reg3_data.OPT1.value),
        True
    );
    ppmCreateRegister("reg3_OPT2",
        0,
        handles.TMSP0,
        32,
        2,
        readOPT2,
        writeOPT2,
        view16,
        &(TMSP0_reg3_data.OPT2.value),
        True
    );
    ppmCreateRegister("reg3_OPT3",
        0,
        handles.TMSP0,
        34,
        2,
        readOPT3,
        writeOPT3,
        view16,
        &(TMSP0_reg3_data.OPT3.value),
        True
    );
    ppmCreateRegister("reg3_OPT6",
        0,
        handles.TMSP0,
        36,
        2,
        readOPT6,
        writeOPT6,
        view16,
        &(TMSP0_reg3_data.OPT6.value),
        True
    );
    ppmCreateRegister("reg3_DTC0",
        0,
        handles.TMSP0,
        14,
        2,
        read_16,
        writeDTC0,
        view16,
        &(TMSP0_reg3_data.DTC0.value),
        True
    );
    ppmCreateRegister("reg3_DTC1",
        0,
        handles.TMSP0,
        12,
        2,
        read_16,
        writeDTC1,
        view16,
        &(TMSP0_reg3_data.DTC1.value),
        True
    );
    ppmCreateRegister("reg3_PAT0",
        0,
        handles.TMSP0,
        22,
        2,
        read_16,
        writePAT0,
        view16,
        &(TMSP0_reg3_data.PAT0.value),
        True
    );
    ppmCreateRegister("reg3_PAT1",
        0,
        handles.TMSP0,
        20,
        2,
        read_16,
        writePAT1,
        view16,
        &(TMSP0_reg3_data.PAT1.value),
        True
    );
    ppmCreateRegister("reg3_CCR0",
        0,
        handles.TMSP0,
        24,
        2,
        read_16,
        writeCCR0,
        view16,
        &(TMSP0_reg3_data.CCR0.value),
        True
    );
    ppmCreateRegister("reg3_CCR1",
        0,
        handles.TMSP0,
        30,
        2,
        read_16,
        writeCCR1,
        view16,
        &(TMSP0_reg3_data.CCR1.value),
        True
    );
    ppmCreateRegister("reg3_CCR2",
        0,
        handles.TMSP0,
        28,
        2,
        read_16,
        writeCCR2,
        view16,
        &(TMSP0_reg3_data.CCR2.value),
        True
    );
    ppmCreateRegister("reg3_CCR3",
        0,
        handles.TMSP0,
        26,
        2,
        read_16,
        writeCCR3,
        view16,
        &(TMSP0_reg3_data.CCR3.value),
        True
    );
    ppmCreateRegister("reg3_CCR4",
        0,
        handles.TMSP0,
        18,
        2,
        read_16,
        writeCCR4,
        view16,
        &(TMSP0_reg3_data.CCR4.value),
        True
    );
    ppmCreateRegister("reg3_CCR5",
        0,
        handles.TMSP0,
        16,
        2,
        read_16,
        writeCCR5,
        view16,
        &(TMSP0_reg3_data.CCR5.value),
        True
    );
    ppmCreateRegister("reg3_CNT",
        0,
        handles.TMSP0,
        38,
        2,
        readCNT,
        0,
        view16,
        &(TMSP0_reg3_data.CNT.value),
        True
    );
    ppmCreateRegister("reg3_SBC",
        0,
        handles.TMSP0,
        40,
        2,
        readSBC,
        0,
        view16,
        &(TMSP0_reg3_data.SBC.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.TOS0, value);

    handles.TOS0 = ppmOpenNetPort("TOS0");

// To write to this net, use ppmWriteNet(handles.TOS1, value);

    handles.TOS1 = ppmOpenNetPort("TOS1");

// To write to this net, use ppmWriteNet(handles.TOS2, value);

    handles.TOS2 = ppmOpenNetPort("TOS2");

// To write to this net, use ppmWriteNet(handles.TOS3, value);

    handles.TOS3 = ppmOpenNetPort("TOS3");

// To write to this net, use ppmWriteNet(handles.TOS4, value);

    handles.TOS4 = ppmOpenNetPort("TOS4");

// To write to this net, use ppmWriteNet(handles.TOS5, value);

    handles.TOS5 = ppmOpenNetPort("TOS5");

// To write to this net, use ppmWriteNet(handles.TOS6, value);

    handles.TOS6 = ppmOpenNetPort("TOS6");

// To write to this net, use ppmWriteNet(handles.TOS7, value);

    handles.TOS7 = ppmOpenNetPort("TOS7");

// To write to this net, use ppmWriteNet(handles.TSADTRG0, value);

    handles.TSADTRG0 = ppmOpenNetPort("TSADTRG0");

// To write to this net, use ppmWriteNet(handles.TSADTRG1, value);

    handles.TSADTRG1 = ppmOpenNetPort("TSADTRG1");

// To write to this net, use ppmWriteNet(handles.TSAEDO, value);

    handles.TSAEDO = ppmOpenNetPort("TSAEDO");

// To write to this net, use ppmWriteNet(handles.TSESG, value);

    handles.TSESG = ppmOpenNetPort("TSESG");

// To write to this net, use ppmWriteNet(handles.TSTSF, value);

    handles.TSTSF = ppmOpenNetPort("TSTSF");

// To write to this net, use ppmWriteNet(handles.INTTSCC0, value);

    handles.INTTSCC0 = ppmOpenNetPort("INTTSCC0");

// To write to this net, use ppmWriteNet(handles.INTTSCC1, value);

    handles.INTTSCC1 = ppmOpenNetPort("INTTSCC1");

// To write to this net, use ppmWriteNet(handles.INTTSCC2, value);

    handles.INTTSCC2 = ppmOpenNetPort("INTTSCC2");

// To write to this net, use ppmWriteNet(handles.INTTSCC3, value);

    handles.INTTSCC3 = ppmOpenNetPort("INTTSCC3");

// To write to this net, use ppmWriteNet(handles.INTTSCC4, value);

    handles.INTTSCC4 = ppmOpenNetPort("INTTSCC4");

// To write to this net, use ppmWriteNet(handles.INTTSCC5, value);

    handles.INTTSCC5 = ppmOpenNetPort("INTTSCC5");

// To write to this net, use ppmWriteNet(handles.INTTSCD0, value);

    handles.INTTSCD0 = ppmOpenNetPort("INTTSCD0");

// To write to this net, use ppmWriteNet(handles.INTTSOD, value);

    handles.INTTSOD = ppmOpenNetPort("INTTSOD");

// To write to this net, use ppmWriteNet(handles.INTTSOV, value);

    handles.INTTSOV = ppmOpenNetPort("INTTSOV");

// To write to this net, use ppmWriteNet(handles.INTTSER, value);

    handles.INTTSER = ppmOpenNetPort("INTTSER");

// To write to this net, use ppmWriteNet(handles.INTTSWN, value);

    handles.INTTSWN = ppmOpenNetPort("INTTSWN");

    handles.TTRGS = ppmOpenNetPort("TTRGS");
    if (handles.TTRGS) {
        ppmInstallNetCallback(handles.TTRGS, P_TTRGS, (void*)0);
    }

    handles.TEVTS = ppmOpenNetPort("TEVTS");
    if (handles.TEVTS) {
        ppmInstallNetCallback(handles.TEVTS, P_TEVTS, (void*)0);
    }

    handles.TAPTS0 = ppmOpenNetPort("TAPTS0");
    if (handles.TAPTS0) {
        ppmInstallNetCallback(handles.TAPTS0, P_TAPTS0, (void*)0);
    }

    handles.TAPTS1 = ppmOpenNetPort("TAPTS1");
    if (handles.TAPTS1) {
        ppmInstallNetCallback(handles.TAPTS1, P_TAPTS1, (void*)0);
    }

    handles.TAPTS2 = ppmOpenNetPort("TAPTS2");
    if (handles.TAPTS2) {
        ppmInstallNetCallback(handles.TAPTS2, P_TAPTS2, (void*)0);
    }

    handles.ESO = ppmOpenNetPort("ESO");
    if (handles.ESO) {
        ppmInstallNetCallback(handles.ESO, P_ESO, (void*)0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        TMSP0_reg3_data.SBC.value = 0x0;
        TMSP0_reg3_data.CNT.value = 0x0;
        TMSP0_reg3_data.CCR5.value = 0x0;
        TMSP0_reg3_data.CCR4.value = 0x0;
        TMSP0_reg3_data.CCR3.value = 0x0;
        TMSP0_reg3_data.CCR2.value = 0x0;
        TMSP0_reg3_data.CCR1.value = 0x0;
        TMSP0_reg3_data.CCR0.value = 0x0;
        TMSP0_reg3_data.PAT1.value = 0x0;
        TMSP0_reg3_data.PAT0.value = 0x0;
        TMSP0_reg3_data.DTC1.value = 0x0;
        TMSP0_reg3_data.DTC0.value = 0x0;
        TMSP0_reg3_data.OPT6.value = 0x0;
        TMSP0_reg3_data.OPT3.value = 0x0;
        TMSP0_reg3_data.OPT2.value = 0x0;
        TMSP0_reg2_data.OPT7.value = 0x0;
        TMSP0_reg2_data.OPT5.value = 0x0;
        TMSP0_reg2_data.OPT4.value = 0x0;
        TMSP0_reg2_data.OPT0.value = 0x0;
        TMSP0_reg2_data.IOC4.value = 0x0;
        TMSP0_reg2_data.IOC2.value = 0x0;
        TMSP0_reg1_data.IOC0.value = 0x0;
        TMSP0_reg0_data.CTL1.value = 0x0;
        TMSP0_reg0_data.CTL0.value = 0x0;
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
        ppmDocAddText(doc_12_node, "Renesas TMS Timer/Event Counter S");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Status of Modes\n- Interval Timer Mode                  - Supported\n- External Event Count Mode            - Untested\n- External Trigger Pulse Output Mode   - Unsupported\n- One-Shot Pulse Mode                  - Unsupported\n- PWM Mode                             - Unsupported\n- Free-Running Mode                    - Supported\n- Triangular-Wave PWM Mode             - Unsupported\n- High Accuracy T-PWM Mode             - Unsupported\n- PWM Mode with Dead Time              - Unsupported\n- 120Deg Excitation Mode               - Unsupported\n- Special 120Deg Excitation Mode       - Unsupported\n- Special Pattern Output Mode          - Unsupported\n");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

