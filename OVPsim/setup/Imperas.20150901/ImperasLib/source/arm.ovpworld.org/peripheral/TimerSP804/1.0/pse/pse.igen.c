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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "TimerSP804", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_ab_T0Load) {
    *(Uns32*)data = bport1_ab_data.T0Load.value;
}

static PPM_VIEW_CB(view_bport1_ab_T0Value) {
    *(Uns32*)data = bport1_ab_data.T0Value.value;
}

static PPM_VIEW_CB(view_bport1_ab_T0Control) {
    *(Uns32*)data = bport1_ab_data.T0Control.value;
}

static PPM_VIEW_CB(view_bport1_ab_T0IntClr) {
    *(Uns32*)data = bport1_ab_data.T0IntClr.value;
}

static PPM_VIEW_CB(view_bport1_ab_T0RIS) {
    *(Uns32*)data = bport1_ab_data.T0RIS.value;
}

static PPM_VIEW_CB(view_bport1_ab_T0MIS) {
    *(Uns32*)data = bport1_ab_data.T0MIS.value;
}

static PPM_VIEW_CB(view_bport1_ab_T0BGLoad) {
    *(Uns32*)data = bport1_ab_data.T0BGLoad.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1Load) {
    *(Uns32*)data = bport1_ab_data.T1Load.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1Value) {
    *(Uns32*)data = bport1_ab_data.T1Value.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1Control) {
    *(Uns32*)data = bport1_ab_data.T1Control.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1IntClr) {
    *(Uns32*)data = bport1_ab_data.T1IntClr.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1RIS) {
    *(Uns32*)data = bport1_ab_data.T1RIS.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1MIS) {
    *(Uns32*)data = bport1_ab_data.T1MIS.value;
}

static PPM_VIEW_CB(view_bport1_ab_T1BGLoad) {
    *(Uns32*)data = bport1_ab_data.T1BGLoad.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_T0Load",
        0,
        handles.bport1,
        0,
        4,
        readLoad,
        writeLoad,
        view_bport1_ab_T0Load,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T0Value",
        0,
        handles.bport1,
        4,
        4,
        readValue,
        0,
        view_bport1_ab_T0Value,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T0Control",
        0,
        handles.bport1,
        8,
        4,
        readControl,
        writeControl,
        view_bport1_ab_T0Control,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T0IntClr",
        0,
        handles.bport1,
        12,
        4,
        0,
        writeIntClr,
        view_bport1_ab_T0IntClr,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T0RIS",
        0,
        handles.bport1,
        16,
        4,
        readRIS,
        0,
        view_bport1_ab_T0RIS,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T0MIS",
        0,
        handles.bport1,
        20,
        4,
        readMIS,
        0,
        view_bport1_ab_T0MIS,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T0BGLoad",
        0,
        handles.bport1,
        24,
        4,
        readLoad,
        writeBGLoad,
        view_bport1_ab_T0BGLoad,
        (void*)0x0,
        True
    );
    ppmCreateRegister("ab_T1Load",
        0,
        handles.bport1,
        32,
        4,
        readLoad,
        writeLoad,
        view_bport1_ab_T1Load,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_T1Value",
        0,
        handles.bport1,
        36,
        4,
        readValue,
        0,
        view_bport1_ab_T1Value,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_T1Control",
        0,
        handles.bport1,
        40,
        4,
        readControl,
        writeControl,
        view_bport1_ab_T1Control,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_T1IntClr",
        0,
        handles.bport1,
        44,
        4,
        0,
        writeIntClr,
        view_bport1_ab_T1IntClr,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_T1RIS",
        0,
        handles.bport1,
        48,
        4,
        readRIS,
        0,
        view_bport1_ab_T1RIS,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_T1MIS",
        0,
        handles.bport1,
        52,
        4,
        readMIS,
        0,
        view_bport1_ab_T1MIS,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_T1BGLoad",
        0,
        handles.bport1,
        56,
        4,
        readLoad,
        writeBGLoad,
        view_bport1_ab_T1BGLoad,
        (void*)0x1,
        True
    );
    ppmCreateRegister("ab_ITCR",
        0,
        handles.bport1,
        3840,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.ITCR.value),
        True
    );
    ppmCreateRegister("ab_ITOP",
        0,
        handles.bport1,
        3844,
        4,
        0,
        write_32,
        view32,
        &(bport1_ab_data.ITOP.value),
        True
    );
    ppmCreateRegister("ab_PeriphID0",
        0,
        handles.bport1,
        4064,
        4,
        readPeriphID0,
        0,
        view32,
        &(bport1_ab_data.PeriphID0.value),
        True
    );
    ppmCreateRegister("ab_PeriphID1",
        0,
        handles.bport1,
        4068,
        4,
        readPeriphID1,
        0,
        view32,
        &(bport1_ab_data.PeriphID1.value),
        True
    );
    ppmCreateRegister("ab_PeriphID2",
        0,
        handles.bport1,
        4072,
        4,
        readPeriphID2,
        0,
        view32,
        &(bport1_ab_data.PeriphID2.value),
        True
    );
    ppmCreateRegister("ab_PeriphID3",
        0,
        handles.bport1,
        4076,
        4,
        readPeriphID3,
        0,
        view32,
        &(bport1_ab_data.PeriphID3.value),
        True
    );
    ppmCreateRegister("ab_PCellID0",
        0,
        handles.bport1,
        4080,
        4,
        readPCellID0,
        0,
        view32,
        &(bport1_ab_data.PCellID0.value),
        True
    );
    ppmCreateRegister("ab_PCellID1",
        0,
        handles.bport1,
        4084,
        4,
        readPCellID1,
        0,
        view32,
        &(bport1_ab_data.PCellID1.value),
        True
    );
    ppmCreateRegister("ab_PCellID2",
        0,
        handles.bport1,
        4088,
        4,
        readPCellID2,
        0,
        view32,
        &(bport1_ab_data.PCellID2.value),
        True
    );
    ppmCreateRegister("ab_PCellID3",
        0,
        handles.bport1,
        4092,
        4,
        readPCellID3,
        0,
        view32,
        &(bport1_ab_data.PCellID3.value),
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
        ppmDocAddText(doc2_node, "Timer SP804 Module");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "none");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "ARM Dual-Timer Module (SP804) Technical Reference Manual (ARM DDI 0271)");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

