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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "ParallelIOController", "Example");
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

    ppmCreateRegister("REG_PIO_PER",
        0,
        handles.bp1,
        0,
        4,
        0,
        PIO_PER_wcb,
        view32,
        &(bp1_REG_data.PIO_PER.value),
        True
    );
    ppmCreateRegister("REG_PIO_PDR",
        0,
        handles.bp1,
        4,
        4,
        0,
        PIO_PDR_wcb,
        view32,
        &(bp1_REG_data.PIO_PDR.value),
        True
    );
    ppmCreateRegister("REG_PIO_PSR",
        0,
        handles.bp1,
        8,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_PSR.value),
        True
    );
    ppmCreateRegister("REG_PIO_OER",
        0,
        handles.bp1,
        16,
        4,
        0,
        PIO_OER_wcb,
        view32,
        &(bp1_REG_data.PIO_OER.value),
        True
    );
    ppmCreateRegister("REG_PIO_ODR",
        0,
        handles.bp1,
        20,
        4,
        0,
        PIO_ODR_wcb,
        view32,
        &(bp1_REG_data.PIO_ODR.value),
        True
    );
    ppmCreateRegister("REG_PIO_OSR",
        0,
        handles.bp1,
        24,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_OSR.value),
        True
    );
    ppmCreateRegister("REG_PIO_IFER",
        0,
        handles.bp1,
        32,
        4,
        0,
        PIO_IFER_wcb,
        view32,
        &(bp1_REG_data.PIO_IFER.value),
        True
    );
    ppmCreateRegister("REG_PIO_IFDR",
        0,
        handles.bp1,
        36,
        4,
        0,
        PIO_IFDR_wcb,
        view32,
        &(bp1_REG_data.PIO_IFDR.value),
        True
    );
    ppmCreateRegister("REG_PIO_IFSR",
        0,
        handles.bp1,
        40,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_IFSR.value),
        True
    );
    ppmCreateRegister("REG_PIO_SODR",
        0,
        handles.bp1,
        48,
        4,
        0,
        PIO_SODR_wcb,
        view32,
        &(bp1_REG_data.PIO_SODR.value),
        True
    );
    ppmCreateRegister("REG_PIO_CODR",
        0,
        handles.bp1,
        52,
        4,
        0,
        PIO_CODR_wcb,
        view32,
        &(bp1_REG_data.PIO_CODR.value),
        True
    );
    ppmCreateRegister("REG_PIO_ODSR",
        0,
        handles.bp1,
        56,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_ODSR.value),
        True
    );
    ppmCreateRegister("REG_PIO_PDSR",
        0,
        handles.bp1,
        60,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_PDSR.value),
        True
    );
    ppmCreateRegister("REG_PIO_IER",
        0,
        handles.bp1,
        64,
        4,
        0,
        PIO_IER_wcb,
        view32,
        &(bp1_REG_data.PIO_IER.value),
        True
    );
    ppmCreateRegister("REG_PIO_IDR",
        0,
        handles.bp1,
        68,
        4,
        0,
        PIO_IDR_wcb,
        view32,
        &(bp1_REG_data.PIO_IDR.value),
        True
    );
    ppmCreateRegister("REG_PIO_IMR",
        0,
        handles.bp1,
        72,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_IMR.value),
        True
    );
    ppmCreateRegister("REG_PIO_ISR",
        0,
        handles.bp1,
        76,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.PIO_ISR.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.P0, value);

    handles.P0 = ppmOpenNetPort("P0");
    if (handles.P0) {
        ppmInstallNetCallback(handles.P0, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P1, value);

    handles.P1 = ppmOpenNetPort("P1");
    if (handles.P1) {
        ppmInstallNetCallback(handles.P1, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P2, value);

    handles.P2 = ppmOpenNetPort("P2");
    if (handles.P2) {
        ppmInstallNetCallback(handles.P2, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P3, value);

    handles.P3 = ppmOpenNetPort("P3");
    if (handles.P3) {
        ppmInstallNetCallback(handles.P3, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P4, value);

    handles.P4 = ppmOpenNetPort("P4");
    if (handles.P4) {
        ppmInstallNetCallback(handles.P4, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P5, value);

    handles.P5 = ppmOpenNetPort("P5");
    if (handles.P5) {
        ppmInstallNetCallback(handles.P5, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P6, value);

    handles.P6 = ppmOpenNetPort("P6");
    if (handles.P6) {
        ppmInstallNetCallback(handles.P6, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P7, value);

    handles.P7 = ppmOpenNetPort("P7");
    if (handles.P7) {
        ppmInstallNetCallback(handles.P7, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P8, value);

    handles.P8 = ppmOpenNetPort("P8");
    if (handles.P8) {
        ppmInstallNetCallback(handles.P8, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P9, value);

    handles.P9 = ppmOpenNetPort("P9");
    if (handles.P9) {
        ppmInstallNetCallback(handles.P9, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P10, value);

    handles.P10 = ppmOpenNetPort("P10");
    if (handles.P10) {
        ppmInstallNetCallback(handles.P10, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P11, value);

    handles.P11 = ppmOpenNetPort("P11");
    if (handles.P11) {
        ppmInstallNetCallback(handles.P11, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P12, value);

    handles.P12 = ppmOpenNetPort("P12");
    if (handles.P12) {
        ppmInstallNetCallback(handles.P12, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P13, value);

    handles.P13 = ppmOpenNetPort("P13");
    if (handles.P13) {
        ppmInstallNetCallback(handles.P13, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P14, value);

    handles.P14 = ppmOpenNetPort("P14");
    if (handles.P14) {
        ppmInstallNetCallback(handles.P14, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P15, value);

    handles.P15 = ppmOpenNetPort("P15");
    if (handles.P15) {
        ppmInstallNetCallback(handles.P15, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P16, value);

    handles.P16 = ppmOpenNetPort("P16");
    if (handles.P16) {
        ppmInstallNetCallback(handles.P16, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P17, value);

    handles.P17 = ppmOpenNetPort("P17");
    if (handles.P17) {
        ppmInstallNetCallback(handles.P17, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P18, value);

    handles.P18 = ppmOpenNetPort("P18");
    if (handles.P18) {
        ppmInstallNetCallback(handles.P18, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P19, value);

    handles.P19 = ppmOpenNetPort("P19");
    if (handles.P19) {
        ppmInstallNetCallback(handles.P19, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P20, value);

    handles.P20 = ppmOpenNetPort("P20");
    if (handles.P20) {
        ppmInstallNetCallback(handles.P20, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P21, value);

    handles.P21 = ppmOpenNetPort("P21");
    if (handles.P21) {
        ppmInstallNetCallback(handles.P21, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P22, value);

    handles.P22 = ppmOpenNetPort("P22");
    if (handles.P22) {
        ppmInstallNetCallback(handles.P22, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P23, value);

    handles.P23 = ppmOpenNetPort("P23");
    if (handles.P23) {
        ppmInstallNetCallback(handles.P23, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P24, value);

    handles.P24 = ppmOpenNetPort("P24");
    if (handles.P24) {
        ppmInstallNetCallback(handles.P24, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P25, value);

    handles.P25 = ppmOpenNetPort("P25");
    if (handles.P25) {
        ppmInstallNetCallback(handles.P25, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P26, value);

    handles.P26 = ppmOpenNetPort("P26");
    if (handles.P26) {
        ppmInstallNetCallback(handles.P26, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P27, value);

    handles.P27 = ppmOpenNetPort("P27");
    if (handles.P27) {
        ppmInstallNetCallback(handles.P27, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P28, value);

    handles.P28 = ppmOpenNetPort("P28");
    if (handles.P28) {
        ppmInstallNetCallback(handles.P28, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P29, value);

    handles.P29 = ppmOpenNetPort("P29");
    if (handles.P29) {
        ppmInstallNetCallback(handles.P29, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P30, value);

    handles.P30 = ppmOpenNetPort("P30");
    if (handles.P30) {
        ppmInstallNetCallback(handles.P30, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.P31, value);

    handles.P31 = ppmOpenNetPort("P31");
    if (handles.P31) {
        ppmInstallNetCallback(handles.P31, P_wcb, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.IRQ, value);

    handles.IRQ = ppmOpenNetPort("IRQ");

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.PIO_ISR.value = 0x0;
        bp1_REG_data.PIO_IMR.value = 0x0;
        bp1_REG_data.PIO_IDR.value = 0x0;
        bp1_REG_data.PIO_IER.value = 0x0;
        bp1_REG_data.PIO_PDSR.value = 0x0;
        bp1_REG_data.PIO_ODSR.value = 0x0;
        bp1_REG_data.PIO_CODR.value = 0x0;
        bp1_REG_data.PIO_SODR.value = 0x0;
        bp1_REG_data.PIO_IFSR.value = 0x0;
        bp1_REG_data.PIO_IFDR.value = 0x0;
        bp1_REG_data.PIO_IFER.value = 0x0;
        bp1_REG_data.PIO_OSR.value = 0x0;
        bp1_REG_data.PIO_ODR.value = 0x0;
        bp1_REG_data.PIO_OER.value = 0x0;
        bp1_REG_data.PIO_PSR.value = 0x1ffffff;
        bp1_REG_data.PIO_PDR.value = 0x0;
        bp1_REG_data.PIO_PER.value = 0x0;
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
        ppmDocAddText(doc2_node, "\nPIO: Parallel I/O Controller\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe Parallel I/O Controller has 32 programmable I/O lines. Six pins are dedicated as general-purpose\nI/O pins. Other I/O lines are multiplexed with an external signal of a peripheral to optimize\nthe use of available package pins. The PIO controller enables generation of an interrupt on input\nchange and insertion of a simple input glitch filter on any of the PIO pins.\nfor more information visit http://www.atmel.com/products/at91\n");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D–ATARM–08/02");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    periphConstructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

