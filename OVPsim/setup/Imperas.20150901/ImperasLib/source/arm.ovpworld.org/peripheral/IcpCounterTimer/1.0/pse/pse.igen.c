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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "IcpCounterTimer", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_ab_load0) {
    *(Uns32*)data = bport1_ab_data.load0.value;
}

static PPM_VIEW_CB(view_bport1_ab_limit0) {
    *(Uns32*)data = bport1_ab_data.limit0.value;
}

static PPM_VIEW_CB(view_bport1_ab_control0) {
    *(Uns32*)data = bport1_ab_data.control0.value;
}

static PPM_VIEW_CB(view_bport1_ab_intclr0) {
    *(Uns32*)data = bport1_ab_data.intclr0.value;
}

static PPM_VIEW_CB(view_bport1_ab_mis0) {
    *(Uns32*)data = bport1_ab_data.mis0.value;
}

static PPM_VIEW_CB(view_bport1_ab_bgload0) {
    *(Uns32*)data = bport1_ab_data.bgload0.value;
}

static PPM_VIEW_CB(view_bport1_ab_load1) {
    *(Uns32*)data = bport1_ab_data.load1.value;
}

static PPM_VIEW_CB(view_bport1_ab_limit1) {
    *(Uns32*)data = bport1_ab_data.limit1.value;
}

static PPM_VIEW_CB(view_bport1_ab_control1) {
    *(Uns32*)data = bport1_ab_data.control1.value;
}

static PPM_VIEW_CB(view_bport1_ab_intclr1) {
    *(Uns32*)data = bport1_ab_data.intclr1.value;
}

static PPM_VIEW_CB(view_bport1_ab_mis1) {
    *(Uns32*)data = bport1_ab_data.mis1.value;
}

static PPM_VIEW_CB(view_bport1_ab_bgload1) {
    *(Uns32*)data = bport1_ab_data.bgload1.value;
}

static PPM_VIEW_CB(view_bport1_ab_load2) {
    *(Uns32*)data = bport1_ab_data.load2.value;
}

static PPM_VIEW_CB(view_bport1_ab_limit2) {
    *(Uns32*)data = bport1_ab_data.limit2.value;
}

static PPM_VIEW_CB(view_bport1_ab_control2) {
    *(Uns32*)data = bport1_ab_data.control2.value;
}

static PPM_VIEW_CB(view_bport1_ab_intclr2) {
    *(Uns32*)data = bport1_ab_data.intclr2.value;
}

static PPM_VIEW_CB(view_bport1_ab_mis2) {
    *(Uns32*)data = bport1_ab_data.mis2.value;
}

static PPM_VIEW_CB(view_bport1_ab_bgload2) {
    *(Uns32*)data = bport1_ab_data.bgload2.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_load0",
        "Timer Load",
        handles.bport1,
        0,
        4,
        readLimit,
        writeLimit,
        view_bport1_ab_load0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_limit0",
        "Timer Value",
        handles.bport1,
        4,
        4,
        readValue,
        writeValue,
        view_bport1_ab_limit0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_control0",
        "Timer Control",
        handles.bport1,
        8,
        4,
        readControl,
        writeControl,
        view_bport1_ab_control0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_intclr0",
        "Interrupt Clear",
        handles.bport1,
        12,
        4,
        0,
        writeClear,
        view_bport1_ab_intclr0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_intlevel0",
        "Interrupt level",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.intlevel0.value),
        True
    );
    ppmCreateRegister("ab_mis0",
        "Timer MIS",
        handles.bport1,
        20,
        4,
        readMIS,
        0,
        view_bport1_ab_mis0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_bgload0",
        "Timer BG Load",
        handles.bport1,
        24,
        4,
        0,
        writeBG,
        view_bport1_ab_bgload0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_load1",
        "Timer Load",
        handles.bport1,
        256,
        4,
        readLimit,
        writeLimit,
        view_bport1_ab_load1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_limit1",
        "Timer Value",
        handles.bport1,
        260,
        4,
        readValue,
        writeValue,
        view_bport1_ab_limit1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_control1",
        "Timer Control",
        handles.bport1,
        264,
        4,
        readControl,
        writeControl,
        view_bport1_ab_control1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_intclr1",
        "Interrupt Clear",
        handles.bport1,
        268,
        4,
        0,
        writeClear,
        view_bport1_ab_intclr1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_intlevel1",
        "Interrupt level",
        handles.bport1,
        272,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.intlevel1.value),
        True
    );
    ppmCreateRegister("ab_mis1",
        "Timer MIS",
        handles.bport1,
        276,
        4,
        readMIS,
        0,
        view_bport1_ab_mis1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_bgload1",
        "Timer BG Load",
        handles.bport1,
        280,
        4,
        0,
        writeBG,
        view_bport1_ab_bgload1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_load2",
        "Timer Load",
        handles.bport1,
        512,
        4,
        readLimit,
        writeLimit,
        view_bport1_ab_load2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_limit2",
        "Timer Value",
        handles.bport1,
        516,
        4,
        readValue,
        writeValue,
        view_bport1_ab_limit2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_control2",
        "Timer Control",
        handles.bport1,
        520,
        4,
        readControl,
        writeControl,
        view_bport1_ab_control2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_intclr2",
        "Interrupt Clear",
        handles.bport1,
        524,
        4,
        0,
        writeClear,
        view_bport1_ab_intclr2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_intlevel2",
        "Interrupt level",
        handles.bport1,
        528,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.intlevel2.value),
        True
    );
    ppmCreateRegister("ab_mis2",
        "Timer MIS",
        handles.bport1,
        532,
        4,
        readMIS,
        0,
        view_bport1_ab_mis2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_bgload2",
        "Timer BG Load",
        handles.bport1,
        536,
        4,
        0,
        writeBG,
        view_bport1_ab_bgload2,
        (void*)0x2,
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq0, value);

    handles.irq0 = ppmOpenNetPort("irq0");

// To write to this net, use ppmWriteNet(handles.irq1, value);

    handles.irq1 = ppmOpenNetPort("irq1");

// To write to this net, use ppmWriteNet(handles.irq2, value);

    handles.irq2 = ppmOpenNetPort("irq2");

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
        ppmDocAddText(doc2_node, "ARM Integrator Board Counter/Timer Module");
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
    destructor();
    return 0;
}

