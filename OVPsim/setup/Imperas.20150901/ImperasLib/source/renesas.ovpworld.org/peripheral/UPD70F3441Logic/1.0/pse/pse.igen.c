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

LOGICP0_reg0_dataT LOGICP0_reg0_data;

LOGICP1_reg0_dataT LOGICP1_reg0_data;

LOGICP2_reg0_dataT LOGICP2_reg0_data;

LOGICP3_reg0_dataT LOGICP3_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UPD70F3441Logic", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.LOGICP0 = ppmCreateSlaveBusPort("LOGICP0", 4);

    handles.LOGICP1 = ppmCreateSlaveBusPort("LOGICP1", 118);

    handles.LOGICP2 = ppmCreateSlaveBusPort("LOGICP2", 12);

    handles.LOGICP3 = ppmCreateSlaveBusPort("LOGICP3", 1);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_INTSEL",
        0,
        handles.LOGICP0,
        0,
        1,
        read_8,
        writeSEL,
        view8,
        &(LOGICP0_reg0_data.INTSEL.value),
        True
    );
    ppmCreateRegister("reg0_INTERRF",
        0,
        handles.LOGICP0,
        2,
        1,
        read_8,
        writeERR,
        view8,
        &(LOGICP0_reg0_data.INTERRF.value),
        True
    );

    ppmCreateRegister("reg0_LOGICP0",
        0,
        handles.LOGICP1,
        0,
        1,
        read_8,
        0,
        view8,
        &(LOGICP1_reg0_data.LOGICP0.value),
        True
    );
    ppmCreateRegister("reg0_P1",
        0,
        handles.LOGICP1,
        2,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P1.value),
        True
    );
    ppmCreateRegister("reg0_PM1",
        0,
        handles.LOGICP1,
        34,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM1.value),
        True
    );
    ppmCreateRegister("reg0_PMC1",
        0,
        handles.LOGICP1,
        66,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC1.value),
        True
    );
    ppmCreateRegister("reg0_P2",
        0,
        handles.LOGICP1,
        4,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P2.value),
        True
    );
    ppmCreateRegister("reg0_PM2",
        0,
        handles.LOGICP1,
        36,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM2.value),
        True
    );
    ppmCreateRegister("reg0_PMC2",
        0,
        handles.LOGICP1,
        68,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC2.value),
        True
    );
    ppmCreateRegister("reg0_P3",
        0,
        handles.LOGICP1,
        6,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P3.value),
        True
    );
    ppmCreateRegister("reg0_PM3",
        0,
        handles.LOGICP1,
        38,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM3.value),
        True
    );
    ppmCreateRegister("reg0_PMC3",
        0,
        handles.LOGICP1,
        70,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC3.value),
        True
    );
    ppmCreateRegister("reg0_P4",
        0,
        handles.LOGICP1,
        8,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P4.value),
        True
    );
    ppmCreateRegister("reg0_PM4",
        0,
        handles.LOGICP1,
        40,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM4.value),
        True
    );
    ppmCreateRegister("reg0_PMC4",
        0,
        handles.LOGICP1,
        72,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC4.value),
        True
    );
    ppmCreateRegister("reg0_P5",
        0,
        handles.LOGICP1,
        10,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P5.value),
        True
    );
    ppmCreateRegister("reg0_PM5",
        0,
        handles.LOGICP1,
        42,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM5.value),
        True
    );
    ppmCreateRegister("reg0_PMC5",
        0,
        handles.LOGICP1,
        74,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC5.value),
        True
    );
    ppmCreateRegister("reg0_P6",
        0,
        handles.LOGICP1,
        12,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P6.value),
        True
    );
    ppmCreateRegister("reg0_PM6",
        0,
        handles.LOGICP1,
        44,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM6.value),
        True
    );
    ppmCreateRegister("reg0_PMC6",
        0,
        handles.LOGICP1,
        76,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC6.value),
        True
    );
    ppmCreateRegister("reg0_P7",
        0,
        handles.LOGICP1,
        14,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P7.value),
        True
    );
    ppmCreateRegister("reg0_PM7",
        0,
        handles.LOGICP1,
        46,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM7.value),
        True
    );
    ppmCreateRegister("reg0_PMC7",
        0,
        handles.LOGICP1,
        78,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC7.value),
        True
    );
    ppmCreateRegister("reg0_P8",
        0,
        handles.LOGICP1,
        16,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P8.value),
        True
    );
    ppmCreateRegister("reg0_PM8",
        0,
        handles.LOGICP1,
        48,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM8.value),
        True
    );
    ppmCreateRegister("reg0_PMC8",
        0,
        handles.LOGICP1,
        80,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC8.value),
        True
    );
    ppmCreateRegister("reg0_P9",
        0,
        handles.LOGICP1,
        18,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P9.value),
        True
    );
    ppmCreateRegister("reg0_PM9",
        0,
        handles.LOGICP1,
        50,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM9.value),
        True
    );
    ppmCreateRegister("reg0_PMC9",
        0,
        handles.LOGICP1,
        82,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC9.value),
        True
    );
    ppmCreateRegister("reg0_P10",
        0,
        handles.LOGICP1,
        20,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P10.value),
        True
    );
    ppmCreateRegister("reg0_PM10",
        0,
        handles.LOGICP1,
        52,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM10.value),
        True
    );
    ppmCreateRegister("reg0_PMC10",
        0,
        handles.LOGICP1,
        84,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC10.value),
        True
    );
    ppmCreateRegister("reg0_P11",
        0,
        handles.LOGICP1,
        22,
        1,
        read_8,
        writeP,
        view8,
        &(LOGICP1_reg0_data.P11.value),
        True
    );
    ppmCreateRegister("reg0_PM11",
        0,
        handles.LOGICP1,
        54,
        1,
        read_8,
        writePM,
        view8,
        &(LOGICP1_reg0_data.PM11.value),
        True
    );
    ppmCreateRegister("reg0_PMC11",
        0,
        handles.LOGICP1,
        86,
        1,
        read_8,
        writePMC,
        view8,
        &(LOGICP1_reg0_data.PMC11.value),
        True
    );
    ppmCreateRegister("reg0_PFC1",
        0,
        handles.LOGICP1,
        98,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC1.value),
        True
    );
    ppmCreateRegister("reg0_PFC2",
        0,
        handles.LOGICP1,
        100,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC2.value),
        True
    );
    ppmCreateRegister("reg0_PFC4",
        0,
        handles.LOGICP1,
        104,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC4.value),
        True
    );
    ppmCreateRegister("reg0_PFC7",
        0,
        handles.LOGICP1,
        110,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC7.value),
        True
    );
    ppmCreateRegister("reg0_PFC8",
        0,
        handles.LOGICP1,
        112,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC8.value),
        True
    );
    ppmCreateRegister("reg0_PFC9",
        0,
        handles.LOGICP1,
        114,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC9.value),
        True
    );
    ppmCreateRegister("reg0_PFC10",
        0,
        handles.LOGICP1,
        116,
        1,
        read_8,
        writePFC,
        view8,
        &(LOGICP1_reg0_data.PFC10.value),
        True
    );

    ppmCreateRegister("reg0_PESC5",
        0,
        handles.LOGICP2,
        0,
        1,
        read_8,
        writePESC5,
        view8,
        &(LOGICP2_reg0_data.PESC5.value),
        True
    );
    ppmCreateRegister("reg0_ESOST5",
        0,
        handles.LOGICP2,
        2,
        1,
        read_8,
        writeESOST5,
        view8,
        &(LOGICP2_reg0_data.ESOST5.value),
        True
    );
    ppmCreateRegister("reg0_PESC6",
        0,
        handles.LOGICP2,
        4,
        1,
        read_8,
        writePESC6,
        view8,
        &(LOGICP2_reg0_data.PESC6.value),
        True
    );
    ppmCreateRegister("reg0_ESOST6",
        0,
        handles.LOGICP2,
        6,
        1,
        read_8,
        writeESOST6,
        view8,
        &(LOGICP2_reg0_data.ESOST6.value),
        True
    );
    ppmCreateRegister("reg0_PESMK5",
        0,
        handles.LOGICP2,
        8,
        1,
        read_8,
        writePESMK5,
        view8,
        &(LOGICP2_reg0_data.PESMK5.value),
        True
    );
    ppmCreateRegister("reg0_PESMK6",
        0,
        handles.LOGICP2,
        10,
        1,
        read_8,
        writePESMK6,
        view8,
        &(LOGICP2_reg0_data.PESMK6.value),
        True
    );

    ppmCreateRegister("reg0_PRCMD",
        0,
        handles.LOGICP3,
        0,
        1,
        0,
        writePRCMD,
        view8,
        &(LOGICP3_reg0_data.PRCMD.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.NMIIN = ppmOpenNetPort("NMIIN");
    if (handles.NMIIN) {
        ppmInstallNetCallback(handles.NMIIN, P_NMIIN, (void*)0);
    }

    handles.INTDEDF = ppmOpenNetPort("INTDEDF");
    if (handles.INTDEDF) {
        ppmInstallNetCallback(handles.INTDEDF, P_INTDEDF, (void*)0);
    }

    handles.INTDEDR = ppmOpenNetPort("INTDEDR");
    if (handles.INTDEDR) {
        ppmInstallNetCallback(handles.INTDEDR, P_INTDEDR, (void*)0);
    }

    handles.INTDEDFR = ppmOpenNetPort("INTDEDFR");
    if (handles.INTDEDFR) {
        ppmInstallNetCallback(handles.INTDEDFR, P_INTDEDFR, (void*)0);
    }

    handles.INTOSD = ppmOpenNetPort("INTOSD");
    if (handles.INTOSD) {
        ppmInstallNetCallback(handles.INTOSD, P_INTOSD, (void*)0);
    }

    handles.INTP4 = ppmOpenNetPort("INTP4");
    if (handles.INTP4) {
        ppmInstallNetCallback(handles.INTP4, P_INTP4, (void*)0);
    }

    handles.INTUC0R = ppmOpenNetPort("INTUC0R");
    if (handles.INTUC0R) {
        ppmInstallNetCallback(handles.INTUC0R, P_INTUC0R, (void*)0);
    }

    handles.INTP5 = ppmOpenNetPort("INTP5");
    if (handles.INTP5) {
        ppmInstallNetCallback(handles.INTP5, P_INTP5, (void*)0);
    }

    handles.INTUC1R = ppmOpenNetPort("INTUC1R");
    if (handles.INTUC1R) {
        ppmInstallNetCallback(handles.INTUC1R, P_INTUC1R, (void*)0);
    }

    handles.INTBRG0 = ppmOpenNetPort("INTBRG0");
    if (handles.INTBRG0) {
        ppmInstallNetCallback(handles.INTBRG0, P_INTBRG0, (void*)0);
    }

    handles.INTBRG1 = ppmOpenNetPort("INTBRG1");
    if (handles.INTBRG1) {
        ppmInstallNetCallback(handles.INTBRG1, P_INTBRG1, (void*)0);
    }

    handles.INTCB0T = ppmOpenNetPort("INTCB0T");
    if (handles.INTCB0T) {
        ppmInstallNetCallback(handles.INTCB0T, P_INTCB0T, (void*)0);
    }

    handles.INTUC2T = ppmOpenNetPort("INTUC2T");
    if (handles.INTUC2T) {
        ppmInstallNetCallback(handles.INTUC2T, P_INTUC2T, (void*)0);
    }

    handles.INTCB0R = ppmOpenNetPort("INTCB0R");
    if (handles.INTCB0R) {
        ppmInstallNetCallback(handles.INTCB0R, P_INTCB0R, (void*)0);
    }

    handles.INTUC2R = ppmOpenNetPort("INTUC2R");
    if (handles.INTUC2R) {
        ppmInstallNetCallback(handles.INTUC2R, P_INTUC2R, (void*)0);
    }

    handles.INTP13 = ppmOpenNetPort("INTP13");
    if (handles.INTP13) {
        ppmInstallNetCallback(handles.INTP13, P_INTP13, (void*)0);
    }

    handles.INTCB0RE = ppmOpenNetPort("INTCB0RE");
    if (handles.INTCB0RE) {
        ppmInstallNetCallback(handles.INTCB0RE, P_INTCB0RE, (void*)0);
    }

    handles.INTUC2RE = ppmOpenNetPort("INTUC2RE");
    if (handles.INTUC2RE) {
        ppmInstallNetCallback(handles.INTUC2RE, P_INTUC2RE, (void*)0);
    }

    handles.INTDMA3 = ppmOpenNetPort("INTDMA3");
    if (handles.INTDMA3) {
        ppmInstallNetCallback(handles.INTDMA3, P_INTDMA3, (void*)0);
    }

    handles.INTFL = ppmOpenNetPort("INTFL");
    if (handles.INTFL) {
        ppmInstallNetCallback(handles.INTFL, P_INTFL, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.NMIOUT, value);

    handles.NMIOUT = ppmOpenNetPort("NMIOUT");

// To write to this net, use ppmWriteNet(handles.INT0, value);

    handles.INT0 = ppmOpenNetPort("INT0");

// To write to this net, use ppmWriteNet(handles.INT1, value);

    handles.INT1 = ppmOpenNetPort("INT1");

// To write to this net, use ppmWriteNet(handles.INT6, value);

    handles.INT6 = ppmOpenNetPort("INT6");

// To write to this net, use ppmWriteNet(handles.INT7, value);

    handles.INT7 = ppmOpenNetPort("INT7");

// To write to this net, use ppmWriteNet(handles.INT75, value);

    handles.INT75 = ppmOpenNetPort("INT75");

// To write to this net, use ppmWriteNet(handles.INT99, value);

    handles.INT99 = ppmOpenNetPort("INT99");

// To write to this net, use ppmWriteNet(handles.INT100, value);

    handles.INT100 = ppmOpenNetPort("INT100");

// To write to this net, use ppmWriteNet(handles.INT101, value);

    handles.INT101 = ppmOpenNetPort("INT101");

// To write to this net, use ppmWriteNet(handles.INT116, value);

    handles.INT116 = ppmOpenNetPort("INT116");

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        LOGICP2_reg0_data.PESMK6.value = 0x0;
        LOGICP2_reg0_data.PESMK5.value = 0x0;
        LOGICP2_reg0_data.ESOST6.value = 0x0;
        LOGICP2_reg0_data.PESC6.value = 0x0;
        LOGICP2_reg0_data.ESOST5.value = 0x0;
        LOGICP2_reg0_data.PESC5.value = 0x0;
        LOGICP0_reg0_data.INTERRF.value = 0x0;
        LOGICP0_reg0_data.INTSEL.value = 0x0;
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
        ppmDocAddText(doc_12_node, "Renesas V850PHO3 / UPD70F3441 Glue Logic");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No known limitations");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

