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

DMAP0_abc_dataT DMAP0_abc_data;

DMAP1_abw_dataT DMAP1_abw_data;

DMAP1_abb_dataT DMAP1_abb_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "dma", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.DMAP0 = ppmCreateSlaveBusPort("DMAP0", 16);

    handles.DMAP1 = ppmCreateSlaveBusPort("DMAP1", 256);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("abc_DMAWC0",
        "DMA Controller Wait Control Register 0",
        handles.DMAP0,
        0,
        2,
        readDMAWC0,
        writeDMAWC0,
        view16,
        &(DMAP0_abc_data.DMAWC0.value),
        True
    );
    ppmCreateRegister("abc_DMAWC1",
        "DMA Controller Wait Control Register 1",
        handles.DMAP0,
        2,
        2,
        readDMAWC1,
        writeDMAWC1,
        view16,
        &(DMAP0_abc_data.DMAWC1.value),
        True
    );

    ppmCreateRegister("abw_MAR0",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        0,
        2,
        readMAR0,
        writeMAR0,
        view16,
        &(DMAP1_abw_data.MAR0.value),
        True
    );
    ppmCreateRegister("abw_MAR1",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        2,
        2,
        readMAR1,
        writeMAR1,
        view16,
        &(DMAP1_abw_data.MAR1.value),
        True
    );
    ppmCreateRegister("abw_MAR2",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        4,
        2,
        readMAR2,
        writeMAR2,
        view16,
        &(DMAP1_abw_data.MAR2.value),
        True
    );
    ppmCreateRegister("abw_MAR3",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        6,
        2,
        readMAR3,
        writeMAR3,
        view16,
        &(DMAP1_abw_data.MAR3.value),
        True
    );
    ppmCreateRegister("abw_MAR4",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        8,
        2,
        readMAR4,
        writeMAR4,
        view16,
        &(DMAP1_abw_data.MAR4.value),
        True
    );
    ppmCreateRegister("abw_MAR5",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        10,
        2,
        readMAR5,
        writeMAR5,
        view16,
        &(DMAP1_abw_data.MAR5.value),
        True
    );
    ppmCreateRegister("abw_MAR6",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        12,
        2,
        readMAR6,
        writeMAR6,
        view16,
        &(DMAP1_abw_data.MAR6.value),
        True
    );
    ppmCreateRegister("abw_MAR7",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        14,
        2,
        readMAR7,
        writeMAR7,
        view16,
        &(DMAP1_abw_data.MAR7.value),
        True
    );
    ppmCreateRegister("abw_MAR8",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        16,
        2,
        readMAR8,
        writeMAR8,
        view16,
        &(DMAP1_abw_data.MAR8.value),
        True
    );
    ppmCreateRegister("abw_MAR9",
        "DMA Controller Transfer Memory Start Address Register",
        handles.DMAP1,
        18,
        2,
        readMAR9,
        writeMAR9,
        view16,
        &(DMAP1_abw_data.MAR9.value),
        True
    );
    ppmCreateRegister("abb_SAR2",
        "DMA Controller Transfer SFR Start Adrress Register 2",
        handles.DMAP1,
        36,
        1,
        readSAR2,
        writeSAR2,
        view8,
        &(DMAP1_abb_data.SAR2.value),
        True
    );
    ppmCreateRegister("abb_SAR3",
        "DMA Controller Transfer SFR Start Adrress Register 3",
        handles.DMAP1,
        38,
        1,
        readSAR3,
        writeSAR3,
        view8,
        &(DMAP1_abb_data.SAR3.value),
        True
    );
    ppmCreateRegister("abb_DTFR4",
        "DMA Controller Trigger Factor register",
        handles.DMAP1,
        136,
        1,
        readDTFR4,
        writeDTFR4,
        view8,
        &(DMAP1_abb_data.DTFR4.value),
        True
    );
    ppmCreateRegister("abb_DTFR5",
        "DMA Controller Trigger Factor register",
        handles.DMAP1,
        138,
        1,
        readDTFR5,
        writeDTFR5,
        view8,
        &(DMAP1_abb_data.DTFR5.value),
        True
    );
    ppmCreateRegister("abb_DTFR6",
        "DMA Controller Trigger Factor register",
        handles.DMAP1,
        140,
        1,
        readDTFR6,
        writeDTFR6,
        view8,
        &(DMAP1_abb_data.DTFR6.value),
        True
    );
    ppmCreateRegister("abb_DTFR7",
        "DMA Controller Trigger Factor register",
        handles.DMAP1,
        142,
        1,
        readDTFR7,
        writeDTFR7,
        view8,
        &(DMAP1_abb_data.DTFR7.value),
        True
    );
    ppmCreateRegister("abb_DTCR0",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        64,
        1,
        readDTCR0,
        writeDTCR0,
        view8,
        &(DMAP1_abb_data.DTCR0.value),
        True
    );
    ppmCreateRegister("abb_DTCR1",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        66,
        1,
        readDTCR1,
        writeDTCR1,
        view8,
        &(DMAP1_abb_data.DTCR1.value),
        True
    );
    ppmCreateRegister("abb_DTCR2",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        68,
        1,
        readDTCR2,
        writeDTCR2,
        view8,
        &(DMAP1_abb_data.DTCR2.value),
        True
    );
    ppmCreateRegister("abb_DTCR3",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        70,
        1,
        readDTCR3,
        writeDTCR3,
        view8,
        &(DMAP1_abb_data.DTCR3.value),
        True
    );
    ppmCreateRegister("abb_DTCR4",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        72,
        1,
        readDTCR4,
        writeDTCR4,
        view8,
        &(DMAP1_abb_data.DTCR4.value),
        True
    );
    ppmCreateRegister("abb_DTCR5",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        74,
        1,
        readDTCR5,
        writeDTCR5,
        view8,
        &(DMAP1_abb_data.DTCR5.value),
        True
    );
    ppmCreateRegister("abb_DTCR6",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        76,
        1,
        readDTCR6,
        writeDTCR6,
        view8,
        &(DMAP1_abb_data.DTCR6.value),
        True
    );
    ppmCreateRegister("abb_DTCR7",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        78,
        1,
        readDTCR7,
        writeDTCR7,
        view8,
        &(DMAP1_abb_data.DTCR7.value),
        True
    );
    ppmCreateRegister("abb_DTCR8",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        80,
        1,
        readDTCR8,
        writeDTCR8,
        view8,
        &(DMAP1_abb_data.DTCR8.value),
        True
    );
    ppmCreateRegister("abb_DTCR9",
        "DMA Controller Transfer Count register",
        handles.DMAP1,
        82,
        1,
        readDTCR9,
        writeDTCR9,
        view8,
        &(DMAP1_abb_data.DTCR9.value),
        True
    );
    ppmCreateRegister("abb_DMASL",
        "DMA Controller Status Register",
        handles.DMAP1,
        98,
        1,
        readDMASL,
        writeDMASL,
        view8,
        &(DMAP1_abb_data.DMASL.value),
        True
    );
    ppmCreateRegister("abb_DMAMCL",
        "DMA Controller Mode Control Register",
        handles.DMAP1,
        96,
        1,
        readDMAMCL,
        writeDMAMCL,
        view8,
        &(DMAP1_abb_data.DMAMCL.value),
        True
    );
    ppmCreateRegister("abb_DMADSCL",
        "DMA Controller Data Size Control Register",
        handles.DMAP1,
        100,
        1,
        readDMADSCL,
        writeDMADSCL,
        view8,
        &(DMAP1_abb_data.DMADSCL.value),
        True
    );

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.DMAPM = ppmOpenAddressSpace("DMAPM");
}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.INTDMA0, value);

    handles.INTDMA0 = ppmOpenNetPort("INTDMA0");

// To write to this net, use ppmWriteNet(handles.INTDMA1, value);

    handles.INTDMA1 = ppmOpenNetPort("INTDMA1");

// To write to this net, use ppmWriteNet(handles.INTDMA2, value);

    handles.INTDMA2 = ppmOpenNetPort("INTDMA2");

// To write to this net, use ppmWriteNet(handles.INTDMA3, value);

    handles.INTDMA3 = ppmOpenNetPort("INTDMA3");

// To write to this net, use ppmWriteNet(handles.INTDMA4, value);

    handles.INTDMA4 = ppmOpenNetPort("INTDMA4");

// To write to this net, use ppmWriteNet(handles.INTDMA5, value);

    handles.INTDMA5 = ppmOpenNetPort("INTDMA5");

// To write to this net, use ppmWriteNet(handles.INTDMA6, value);

    handles.INTDMA6 = ppmOpenNetPort("INTDMA6");

// To write to this net, use ppmWriteNet(handles.INTDMA7, value);

    handles.INTDMA7 = ppmOpenNetPort("INTDMA7");

// To write to this net, use ppmWriteNet(handles.INTDMA8, value);

    handles.INTDMA8 = ppmOpenNetPort("INTDMA8");

// To write to this net, use ppmWriteNet(handles.INTDMA9, value);

    handles.INTDMA9 = ppmOpenNetPort("INTDMA9");

// To write to this net, use ppmWriteNet(handles.DMA0EN, value);

    handles.DMA0EN = ppmOpenNetPort("DMA0EN");

// To write to this net, use ppmWriteNet(handles.DMA1EN, value);

    handles.DMA1EN = ppmOpenNetPort("DMA1EN");

    handles.ADDMARQ0 = ppmOpenNetPort("ADDMARQ0");
    if (handles.ADDMARQ0) {
        ppmInstallNetCallback(handles.ADDMARQ0, triggerADDMARQ0, (void*)0);
    }

    handles.ADDMARQ1 = ppmOpenNetPort("ADDMARQ1");
    if (handles.ADDMARQ1) {
        ppmInstallNetCallback(handles.ADDMARQ1, triggerADDMARQ1, (void*)0);
    }

    handles.INTTS0CD = ppmOpenNetPort("INTTS0CD");
    if (handles.INTTS0CD) {
        ppmInstallNetCallback(handles.INTTS0CD, triggerINTTS0CD, (void*)0);
    }

    handles.INTTS1CD = ppmOpenNetPort("INTTS1CD");
    if (handles.INTTS1CD) {
        ppmInstallNetCallback(handles.INTTS1CD, triggerINTTS1CD, (void*)0);
    }

    handles.INTCE0C = ppmOpenNetPort("INTCE0C");
    if (handles.INTCE0C) {
        ppmInstallNetCallback(handles.INTCE0C, triggerINTCE0C, (void*)0);
    }

    handles.INTCE1C = ppmOpenNetPort("INTCE1C");
    if (handles.INTCE1C) {
        ppmInstallNetCallback(handles.INTCE1C, triggerINTCE1C, (void*)0);
    }

    handles.INTBE0R = ppmOpenNetPort("INTBE0R");
    if (handles.INTBE0R) {
        ppmInstallNetCallback(handles.INTBE0R, triggerINTBE0R, (void*)0);
    }

    handles.INTBE1R = ppmOpenNetPort("INTBE1R");
    if (handles.INTBE1R) {
        ppmInstallNetCallback(handles.INTBE1R, triggerINTBE1R, (void*)0);
    }

    handles.INTUC0R = ppmOpenNetPort("INTUC0R");
    if (handles.INTUC0R) {
        ppmInstallNetCallback(handles.INTUC0R, triggerINTUC0R, (void*)0);
    }

    handles.INTUC1R = ppmOpenNetPort("INTUC1R");
    if (handles.INTUC1R) {
        ppmInstallNetCallback(handles.INTUC1R, triggerINTUC1R, (void*)0);
    }

    handles.INTUC2R = ppmOpenNetPort("INTUC2R");
    if (handles.INTUC2R) {
        ppmInstallNetCallback(handles.INTUC2R, triggerINTUC2R, (void*)0);
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        DMAP1_abb_data.DMADSCL.value = 0x0;
        DMAP1_abb_data.DMAMCL.value = 0x0;
        DMAP1_abb_data.DMASL.value = 0x0;
        DMAP1_abb_data.DTCR9.value = 0x0;
        DMAP1_abb_data.DTCR8.value = 0x0;
        DMAP1_abb_data.DTCR7.value = 0x0;
        DMAP1_abb_data.DTCR6.value = 0x0;
        DMAP1_abb_data.DTCR5.value = 0x0;
        DMAP1_abb_data.DTCR4.value = 0x0;
        DMAP1_abb_data.DTCR3.value = 0x0;
        DMAP1_abb_data.DTCR2.value = 0x0;
        DMAP1_abb_data.DTCR1.value = 0x0;
        DMAP1_abb_data.DTCR0.value = 0x0;
        DMAP1_abb_data.DTFR7.value = 0x0;
        DMAP1_abb_data.DTFR6.value = 0x0;
        DMAP1_abb_data.DTFR5.value = 0x0;
        DMAP1_abb_data.DTFR4.value = 0x0;
        DMAP1_abb_data.SAR3.value = 0x0;
        DMAP1_abb_data.SAR2.value = 0x0;
        DMAP1_abw_data.MAR9.value = 0x0;
        DMAP1_abw_data.MAR8.value = 0x0;
        DMAP1_abw_data.MAR7.value = 0x0;
        DMAP1_abw_data.MAR6.value = 0x0;
        DMAP1_abw_data.MAR5.value = 0x0;
        DMAP1_abw_data.MAR4.value = 0x0;
        DMAP1_abw_data.MAR3.value = 0x0;
        DMAP1_abw_data.MAR2.value = 0x0;
        DMAP1_abw_data.MAR1.value = 0x0;
        DMAP1_abw_data.MAR0.value = 0x0;
        DMAP0_abc_data.DMAWC1.value = 0x7;
        DMAP0_abc_data.DMAWC0.value = 0x37;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    installNetPorts();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas DMA Controller");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Initial implementation to support CAN DMA message transfer only");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

