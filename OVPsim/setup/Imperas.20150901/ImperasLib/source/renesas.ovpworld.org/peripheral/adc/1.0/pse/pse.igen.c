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

ADCP0_reg0_dataT ADCP0_reg0_data;

ADCP0_reg1_dataT ADCP0_reg1_data;

ADCP0_reg2_dataT ADCP0_reg2_data;

ADCP1_reg0_dataT ADCP1_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "adc", "Example");
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

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR0) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR0.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR1) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR1.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR2) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR2.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR3) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR3.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR4) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR4.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR5) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR5.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR6) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR6.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR7) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR7.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR8) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR8.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR9) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR9.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.ADCP0 = ppmCreateSlaveBusPort("ADCP0", 48);

    handles.ADCP1 = ppmCreateSlaveBusPort("ADCP1", 1);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_ADM0",
        0,
        handles.ADCP0,
        0,
        1,
        read_8,
        writeADM0,
        view8,
        &(ADCP0_reg0_data.ADM0.value),
        True
    );
    ppmCreateRegister("reg0_ADM1",
        0,
        handles.ADCP0,
        1,
        1,
        read_8,
        writeADM1,
        view8,
        &(ADCP0_reg0_data.ADM1.value),
        True
    );
    ppmCreateRegister("reg0_ADM2",
        0,
        handles.ADCP0,
        2,
        1,
        read_8,
        writeADM2,
        view8,
        &(ADCP0_reg0_data.ADM2.value),
        True
    );
    ppmCreateRegister("reg1_ADCR0",
        0,
        handles.ADCP0,
        16,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("reg1_ADCR1",
        0,
        handles.ADCP0,
        18,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("reg1_ADCR2",
        0,
        handles.ADCP0,
        20,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("reg1_ADCR3",
        0,
        handles.ADCP0,
        22,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR3,
        (void*)0x3,
        True
    );
    ppmCreateRegister("reg1_ADCR4",
        0,
        handles.ADCP0,
        24,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR4,
        (void*)0x4,
        True
    );
    ppmCreateRegister("reg1_ADCR5",
        0,
        handles.ADCP0,
        26,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR5,
        (void*)0x5,
        True
    );
    ppmCreateRegister("reg1_ADCR6",
        0,
        handles.ADCP0,
        28,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR6,
        (void*)0x6,
        True
    );
    ppmCreateRegister("reg1_ADCR7",
        0,
        handles.ADCP0,
        30,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR7,
        (void*)0x7,
        True
    );
    ppmCreateRegister("reg1_ADCR8",
        0,
        handles.ADCP0,
        32,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR8,
        (void*)0x8,
        True
    );
    ppmCreateRegister("reg1_ADCR9",
        0,
        handles.ADCP0,
        34,
        2,
        readADCR,
        0,
        view_ADCP0_reg1_ADCR9,
        (void*)0x9,
        True
    );
    ppmCreateRegister("reg2_ADDMA",
        0,
        handles.ADCP0,
        46,
        2,
        readADDMA,
        0,
        view16,
        &(ADCP0_reg2_data.ADDMA.value),
        True
    );

    ppmCreateRegister("reg0_ADTRSEL",
        0,
        handles.ADCP1,
        0,
        1,
        read_8,
        writeADTRSEL,
        view8,
        &(ADCP1_reg0_data.ADTRSEL.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.INTAD, value);

    handles.INTAD = ppmOpenNetPort("INTAD");

// To write to this net, use ppmWriteNet(handles.ADDMARQ, value);

    handles.ADDMARQ = ppmOpenNetPort("ADDMARQ");

    handles.INTADEN = ppmOpenNetPort("INTADEN");
    if (handles.INTADEN) {
        ppmInstallNetCallback(handles.INTADEN, P_INTADEN, (void*)0);
    }

    handles.ADTRG = ppmOpenNetPort("ADTRG");
    if (handles.ADTRG) {
        ppmInstallNetCallback(handles.ADTRG, P_ADTRG, (void*)0);
    }

    handles.TS0ADT0 = ppmOpenNetPort("TS0ADT0");
    if (handles.TS0ADT0) {
        ppmInstallNetCallback(handles.TS0ADT0, P_TS0ADT0, (void*)0);
    }

    handles.TS0ADT1 = ppmOpenNetPort("TS0ADT1");
    if (handles.TS0ADT1) {
        ppmInstallNetCallback(handles.TS0ADT1, P_TS0ADT1, (void*)0);
    }

    handles.INTTS0OD = ppmOpenNetPort("INTTS0OD");
    if (handles.INTTS0OD) {
        ppmInstallNetCallback(handles.INTTS0OD, P_INTTS0OD, (void*)0);
    }

    handles.INTTS0CD = ppmOpenNetPort("INTTS0CD");
    if (handles.INTTS0CD) {
        ppmInstallNetCallback(handles.INTTS0CD, P_INTTS0CD, (void*)0);
    }

    handles.TS1ADT0 = ppmOpenNetPort("TS1ADT0");
    if (handles.TS1ADT0) {
        ppmInstallNetCallback(handles.TS1ADT0, P_TS1ADT0, (void*)0);
    }

    handles.TS1ADT1 = ppmOpenNetPort("TS1ADT1");
    if (handles.TS1ADT1) {
        ppmInstallNetCallback(handles.TS1ADT1, P_TS1ADT1, (void*)0);
    }

    handles.INTTS1OD = ppmOpenNetPort("INTTS1OD");
    if (handles.INTTS1OD) {
        ppmInstallNetCallback(handles.INTTS1OD, P_INTTS1OD, (void*)0);
    }

    handles.INTTS1CD = ppmOpenNetPort("INTTS1CD");
    if (handles.INTTS1CD) {
        ppmInstallNetCallback(handles.INTTS1CD, P_INTTS1CD, (void*)0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        ADCP1_reg0_data.ADTRSEL.value = 0x0;
        ADCP0_reg2_data.ADDMA.value = 0x0;
        ADCP0_reg1_data.ADCR9.value = 0x0;
        ADCP0_reg1_data.ADCR8.value = 0x0;
        ADCP0_reg1_data.ADCR7.value = 0x0;
        ADCP0_reg1_data.ADCR6.value = 0x0;
        ADCP0_reg1_data.ADCR5.value = 0x0;
        ADCP0_reg1_data.ADCR4.value = 0x0;
        ADCP0_reg1_data.ADCR3.value = 0x0;
        ADCP0_reg1_data.ADCR2.value = 0x0;
        ADCP0_reg1_data.ADCR1.value = 0x0;
        ADCP0_reg1_data.ADCR0.value = 0x0;
        ADCP0_reg0_data.ADM2.value = 0x0;
        ADCP0_reg0_data.ADM1.value = 0x0;
        ADCP0_reg0_data.ADM0.value = 0x0;
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
        ppmDocAddText(doc_12_node, "Renesas ADC A/D Converter");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Model supports Modes Select, Scan, 1xBuffer, 4xBuffer - no support for external trigger");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

