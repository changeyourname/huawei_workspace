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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "WdtSP805", "Example");
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

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_WdogLoad",
        "                 ",
        handles.bport1,
        0,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.WdogLoad.value),
        True
    );
    ppmCreateRegister("ab_WdogValue",
        "                 ",
        handles.bport1,
        4,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.WdogValue.value),
        True
    );
    ppmCreateRegister("ab_WdogControl",
        "                 ",
        handles.bport1,
        8,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.WdogControl.value),
        True
    );
    ppmCreateRegister("ab_WdogIntClr",
        "                 ",
        handles.bport1,
        12,
        4,
        0,
        write_32,
        view32,
        &(bport1_ab_data.WdogIntClr.value),
        True
    );
    ppmCreateRegister("ab_WdogRIS",
        "                 ",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.WdogRIS.value),
        True
    );
    ppmCreateRegister("ab_WdogMIS",
        "                 ",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.WdogMIS.value),
        True
    );
    ppmCreateRegister("ab_WdogLock",
        "                 ",
        handles.bport1,
        3072,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.WdogLock.value),
        True
    );
    ppmCreateRegister("ab_WdogITCR",
        "                 ",
        handles.bport1,
        3840,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.WdogITCR.value),
        True
    );
    ppmCreateRegister("ab_WdogITOP",
        "                 ",
        handles.bport1,
        3844,
        4,
        0,
        write_32,
        view32,
        &(bport1_ab_data.WdogITOP.value),
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

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM SP805 Watchdog Registers.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Does NOT model watchdog functionality, just provides registers to allow code to run.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM Watchdog Module (SP805) Technical Reference Manual (ARM DDI 0270)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

