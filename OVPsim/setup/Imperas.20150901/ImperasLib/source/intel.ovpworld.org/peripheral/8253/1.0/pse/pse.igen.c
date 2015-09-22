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

bport1_reg_dataT bport1_reg_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "8253", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg_CTR0",
        0,
        handles.bport1,
        0,
        1,
        readCTR0,
        writeCTR0,
        view8,
        &(bport1_reg_data.CTR0.value),
        True
    );
    ppmCreateRegister("reg_CTR1",
        0,
        handles.bport1,
        1,
        1,
        readCTR1,
        writeCTR1,
        view8,
        &(bport1_reg_data.CTR1.value),
        True
    );
    ppmCreateRegister("reg_CTR2",
        0,
        handles.bport1,
        2,
        1,
        readCTR2,
        writeCTR2,
        view8,
        &(bport1_reg_data.CTR2.value),
        True
    );
    ppmCreateRegister("reg_CNTL",
        0,
        handles.bport1,
        3,
        1,
        readCNTL,
        writeCNTL,
        view8,
        &(bport1_reg_data.CNTL.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.clk0 = ppmOpenNetPort("clk0");

    handles.gate0 = ppmOpenNetPort("gate0");

// To write to this net, use ppmWriteNet(handles.out0, value);

    handles.out0 = ppmOpenNetPort("out0");

    handles.clk1 = ppmOpenNetPort("clk1");

    handles.gate1 = ppmOpenNetPort("gate1");

// To write to this net, use ppmWriteNet(handles.out1, value);

    handles.out1 = ppmOpenNetPort("out1");

    handles.clk2 = ppmOpenNetPort("clk2");

    handles.gate2 = ppmOpenNetPort("gate2");

// To write to this net, use ppmWriteNet(handles.out2, value);

    handles.out2 = ppmOpenNetPort("out2");

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
        ppmDocAddText(doc2_node, "Intel 8253 Programmable Interval Timer (PIT)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform.\n           Not all modes are supported.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Intel 8253 Datasheet. MIPS Malta Platform Reference Guide.");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

