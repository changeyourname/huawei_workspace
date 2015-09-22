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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "IntICP", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_status",
        "IRQ_STATUS",
        handles.bport1,
        0,
        4,
        readIRQ,
        0,
        view32,
        &(bport1_ab_data.status.value),
        True
    );
    ppmCreateRegister("ab_level",
        "IRQ_RAWSTAT",
        handles.bport1,
        4,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.level.value),
        True
    );
    ppmCreateRegister("ab_enable",
        "IRQ_ENABLE_SET",
        handles.bport1,
        8,
        4,
        read_32,
        writeSET,
        view32,
        &(bport1_ab_data.enable.value),
        True
    );
    ppmCreateRegister("ab_clr",
        "IRQ_ENABLE_CLR",
        handles.bport1,
        12,
        4,
        0,
        writeCLR,
        view32,
        &(bport1_ab_data.clr.value),
        True
    );
    ppmCreateRegister("ab_softset",
        "INT_SOFTSET",
        handles.bport1,
        16,
        4,
        readLEV,
        writeSST,
        view32,
        &(bport1_ab_data.softset.value),
        True
    );
    ppmCreateRegister("ab_softclr",
        "INT_SOFTCLR",
        handles.bport1,
        20,
        4,
        0,
        writeSCL,
        view32,
        &(bport1_ab_data.softclr.value),
        True
    );
    ppmCreateRegister("ab_frqstat",
        "FRQ_STATUS",
        handles.bport1,
        32,
        4,
        readFIQ,
        0,
        view32,
        &(bport1_ab_data.frqstat.value),
        True
    );
    ppmCreateRegister("ab_rawstat",
        "FRQ_RAWSTAT",
        handles.bport1,
        36,
        4,
        readLevel,
        0,
        view32,
        &(bport1_ab_data.rawstat.value),
        True
    );
    ppmCreateRegister("ab_fiqen",
        "FIQ_ENABLESET",
        handles.bport1,
        40,
        4,
        0,
        writeFIQS,
        view32,
        &(bport1_ab_data.fiqen.value),
        True
    );
    ppmCreateRegister("ab_fiqenclr",
        "FRQ_ENABLECLR",
        handles.bport1,
        44,
        4,
        0,
        writeFIQC,
        view32,
        &(bport1_ab_data.fiqenclr.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq, value);

    handles.irq = ppmOpenNetPort("irq");

// To write to this net, use ppmWriteNet(handles.fiq, value);

    handles.fiq = ppmOpenNetPort("fiq");

    handles.ir0 = ppmOpenNetPort("ir0");
    if (handles.ir0) {
        ppmInstallNetCallback(handles.ir0, irqUpdate, (void*)0);
    }

    handles.ir1 = ppmOpenNetPort("ir1");
    if (handles.ir1) {
        ppmInstallNetCallback(handles.ir1, irqUpdate, (void*)1);
    }

    handles.ir2 = ppmOpenNetPort("ir2");
    if (handles.ir2) {
        ppmInstallNetCallback(handles.ir2, irqUpdate, (void*)2);
    }

    handles.ir3 = ppmOpenNetPort("ir3");
    if (handles.ir3) {
        ppmInstallNetCallback(handles.ir3, irqUpdate, (void*)3);
    }

    handles.ir4 = ppmOpenNetPort("ir4");
    if (handles.ir4) {
        ppmInstallNetCallback(handles.ir4, irqUpdate, (void*)4);
    }

    handles.ir5 = ppmOpenNetPort("ir5");
    if (handles.ir5) {
        ppmInstallNetCallback(handles.ir5, irqUpdate, (void*)5);
    }

    handles.ir6 = ppmOpenNetPort("ir6");
    if (handles.ir6) {
        ppmInstallNetCallback(handles.ir6, irqUpdate, (void*)6);
    }

    handles.ir7 = ppmOpenNetPort("ir7");
    if (handles.ir7) {
        ppmInstallNetCallback(handles.ir7, irqUpdate, (void*)7);
    }

    handles.ir8 = ppmOpenNetPort("ir8");
    if (handles.ir8) {
        ppmInstallNetCallback(handles.ir8, irqUpdate, (void*)8);
    }

    handles.ir9 = ppmOpenNetPort("ir9");
    if (handles.ir9) {
        ppmInstallNetCallback(handles.ir9, irqUpdate, (void*)9);
    }

    handles.ir10 = ppmOpenNetPort("ir10");
    if (handles.ir10) {
        ppmInstallNetCallback(handles.ir10, irqUpdate, (void*)10);
    }

    handles.ir11 = ppmOpenNetPort("ir11");
    if (handles.ir11) {
        ppmInstallNetCallback(handles.ir11, irqUpdate, (void*)11);
    }

    handles.ir12 = ppmOpenNetPort("ir12");
    if (handles.ir12) {
        ppmInstallNetCallback(handles.ir12, irqUpdate, (void*)12);
    }

    handles.ir13 = ppmOpenNetPort("ir13");
    if (handles.ir13) {
        ppmInstallNetCallback(handles.ir13, irqUpdate, (void*)13);
    }

    handles.ir14 = ppmOpenNetPort("ir14");
    if (handles.ir14) {
        ppmInstallNetCallback(handles.ir14, irqUpdate, (void*)14);
    }

    handles.ir15 = ppmOpenNetPort("ir15");
    if (handles.ir15) {
        ppmInstallNetCallback(handles.ir15, irqUpdate, (void*)15);
    }

    handles.ir16 = ppmOpenNetPort("ir16");
    if (handles.ir16) {
        ppmInstallNetCallback(handles.ir16, irqUpdate, (void*)16);
    }

    handles.ir17 = ppmOpenNetPort("ir17");
    if (handles.ir17) {
        ppmInstallNetCallback(handles.ir17, irqUpdate, (void*)17);
    }

    handles.ir18 = ppmOpenNetPort("ir18");
    if (handles.ir18) {
        ppmInstallNetCallback(handles.ir18, irqUpdate, (void*)18);
    }

    handles.ir19 = ppmOpenNetPort("ir19");
    if (handles.ir19) {
        ppmInstallNetCallback(handles.ir19, irqUpdate, (void*)19);
    }

    handles.ir20 = ppmOpenNetPort("ir20");
    if (handles.ir20) {
        ppmInstallNetCallback(handles.ir20, irqUpdate, (void*)20);
    }

    handles.ir21 = ppmOpenNetPort("ir21");
    if (handles.ir21) {
        ppmInstallNetCallback(handles.ir21, irqUpdate, (void*)21);
    }

    handles.ir22 = ppmOpenNetPort("ir22");
    if (handles.ir22) {
        ppmInstallNetCallback(handles.ir22, irqUpdate, (void*)22);
    }

    handles.ir23 = ppmOpenNetPort("ir23");
    if (handles.ir23) {
        ppmInstallNetCallback(handles.ir23, irqUpdate, (void*)23);
    }

    handles.ir24 = ppmOpenNetPort("ir24");
    if (handles.ir24) {
        ppmInstallNetCallback(handles.ir24, irqUpdate, (void*)24);
    }

    handles.ir25 = ppmOpenNetPort("ir25");
    if (handles.ir25) {
        ppmInstallNetCallback(handles.ir25, irqUpdate, (void*)25);
    }

    handles.ir26 = ppmOpenNetPort("ir26");
    if (handles.ir26) {
        ppmInstallNetCallback(handles.ir26, irqUpdate, (void*)26);
    }

    handles.ir27 = ppmOpenNetPort("ir27");
    if (handles.ir27) {
        ppmInstallNetCallback(handles.ir27, irqUpdate, (void*)27);
    }

    handles.ir28 = ppmOpenNetPort("ir28");
    if (handles.ir28) {
        ppmInstallNetCallback(handles.ir28, irqUpdate, (void*)28);
    }

    handles.ir29 = ppmOpenNetPort("ir29");
    if (handles.ir29) {
        ppmInstallNetCallback(handles.ir29, irqUpdate, (void*)29);
    }

    handles.ir30 = ppmOpenNetPort("ir30");
    if (handles.ir30) {
        ppmInstallNetCallback(handles.ir30, irqUpdate, (void*)30);
    }

    handles.ir31 = ppmOpenNetPort("ir31");
    if (handles.ir31) {
        ppmInstallNetCallback(handles.ir31, irqUpdate, (void*)31);
    }

}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM Integrator Board interrupt controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

