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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "LcdPL110", "Example");
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

static PPM_VIEW_CB(view_bport1_ab_timing0) {
    *(Uns32*)data = bport1_ab_data.timing0.value;
}

static PPM_VIEW_CB(view_bport1_ab_timing1) {
    *(Uns32*)data = bport1_ab_data.timing1.value;
}

static PPM_VIEW_CB(view_bport1_ab_timing2) {
    *(Uns32*)data = bport1_ab_data.timing2.value;
}

static PPM_VIEW_CB(view_bport1_ab_timing3) {
    *(Uns32*)data = bport1_ab_data.timing3.value;
}

static PPM_VIEW_CB(view_bport1_ab_id0) {
    *(Uns32*)data = bport1_ab_data.id0.value;
}

static PPM_VIEW_CB(view_bport1_ab_id1) {
    *(Uns32*)data = bport1_ab_data.id1.value;
}

static PPM_VIEW_CB(view_bport1_ab_id2) {
    *(Uns32*)data = bport1_ab_data.id2.value;
}

static PPM_VIEW_CB(view_bport1_ab_id3) {
    *(Uns32*)data = bport1_ab_data.id3.value;
}

static PPM_VIEW_CB(view_bport1_ab_id4) {
    *(Uns32*)data = bport1_ab_data.id4.value;
}

static PPM_VIEW_CB(view_bport1_ab_id5) {
    *(Uns32*)data = bport1_ab_data.id5.value;
}

static PPM_VIEW_CB(view_bport1_ab_id6) {
    *(Uns32*)data = bport1_ab_data.id6.value;
}

static PPM_VIEW_CB(view_bport1_ab_id7) {
    *(Uns32*)data = bport1_ab_data.id7.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {


    ppmCreateRegister("ab_timing0",
        "LCD Timing 0",
        handles.bport1,
        0,
        4,
        readTiming,
        writeTiming,
        view_bport1_ab_timing0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_timing1",
        "LCD Timing 1",
        handles.bport1,
        4,
        4,
        readTiming,
        writeTiming,
        view_bport1_ab_timing1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_timing2",
        "LCD Timing 2",
        handles.bport1,
        8,
        4,
        readTiming,
        writeTiming,
        view_bport1_ab_timing2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_timing3",
        "LCD Timing 3",
        handles.bport1,
        12,
        4,
        readTiming,
        writeTiming,
        view_bport1_ab_timing3,
        (void*)0x3,
        True
    );
    ppmCreateRegister("ab_upbase",
        "LCD UP Base",
        handles.bport1,
        16,
        4,
        read_32,
        writeUP,
        view32,
        &(bport1_ab_data.upbase.value),
        True
    );
    ppmCreateRegister("ab_lpbase",
        "LCD LP Base",
        handles.bport1,
        20,
        4,
        read_32,
        writeLP,
        view32,
        &(bport1_ab_data.lpbase.value),
        True
    );
    ppmCreateRegister("ab_imsc",
        "LCD IMSC",
        handles.bport1,
        24,
        4,
        readIMSC,
        writeIMSC,
        view32,
        &(bport1_ab_data.imsc.value),
        True
    );
    ppmCreateRegister("ab_control",
        "LCD Control",
        handles.bport1,
        28,
        4,
        readControl,
        writeControl,
        view32,
        &(bport1_ab_data.control.value),
        True
    );
    ppmCreateRegister("ab_int_status",
        "LCD RIS",
        handles.bport1,
        32,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.int_status.value),
        True
    );
    ppmCreateRegister("ab_int_mis",
        "LCD MIS",
        handles.bport1,
        36,
        4,
        readMIS,
        0,
        view32,
        &(bport1_ab_data.int_mis.value),
        True
    );
    ppmCreateRegister("ab_int_clr",
        "LCD ICR",
        handles.bport1,
        40,
        4,
        0,
        writeICR,
        view32,
        &(bport1_ab_data.int_clr.value),
        True
    );
    ppmCreateRegister("ab_upbase2",
        "LCD UP current",
        handles.bport1,
        44,
        4,
        readUP,
        0,
        view32,
        &(bport1_ab_data.upbase2.value),
        True
    );
    ppmCreateRegister("ab_lpbase2",
        "LCD LP current",
        handles.bport1,
        48,
        4,
        readLP,
        0,
        view32,
        &(bport1_ab_data.lpbase2.value),
        True
    );
    ppmCreateRegister("ab_id0",
        0,
        handles.bport1,
        4064,
        4,
        readID,
        0,
        view_bport1_ab_id0,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_id1",
        0,
        handles.bport1,
        4068,
        4,
        readID,
        0,
        view_bport1_ab_id1,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_id2",
        0,
        handles.bport1,
        4072,
        4,
        readID,
        0,
        view_bport1_ab_id2,
        (void*)0x2,
        True
    );
    ppmCreateRegister("ab_id3",
        0,
        handles.bport1,
        4076,
        4,
        readID,
        0,
        view_bport1_ab_id3,
        (void*)0x3,
        True
    );
    ppmCreateRegister("ab_id4",
        0,
        handles.bport1,
        4080,
        4,
        readID,
        0,
        view_bport1_ab_id4,
        (void*)0x4,
        True
    );
    ppmCreateRegister("ab_id5",
        0,
        handles.bport1,
        4084,
        4,
        readID,
        0,
        view_bport1_ab_id5,
        (void*)0x5,
        True
    );
    ppmCreateRegister("ab_id6",
        0,
        handles.bport1,
        4088,
        4,
        readID,
        0,
        view_bport1_ab_id6,
        (void*)0x6,
        True
    );
    ppmCreateRegister("ab_id7",
        0,
        handles.bport1,
        4092,
        4,
        readID,
        0,
        view_bport1_ab_id7,
        (void*)0x7,
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq, value);

    handles.irq = ppmOpenNetPort("irq");

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
        ppmDocAddText(doc2_node, "ARM PL110 LCD Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "The VGA display refresh is not optimised resulting in the VGA peripheral causing a limit on the maximum performance of a platform it contains to be around 300 MIPS (actual dependent upon refresh rate of LCD).");
        ppmDocAddText(doc_12_node, "The LCD peripheral utilises memory watchpoints to optimise display refresh. This requires the use of ICM memory for the frame buffers, which currently may stop its use in SystemC TLM2 platforms.");
        ppmDocAddText(doc_12_node, "Interrupts are not supported");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM PrimeCell Color LCD Controller (PL111) Technical Reference Manual (ARM DDI 0293)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

