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

io_reg_dataT io_reg_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "8259A", "Example");
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
    handles.io = ppmCreateSlaveBusPort("io", 2);
    if (!handles.io) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'io'");
    }

    handles.PCIackS = ppmCreateSlaveBusPort("PCIackS", 1);

    handles.elcr = ppmCreateSlaveBusPort("elcr", 1);
    if (!handles.elcr) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'elcr'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg_io0",
        0,
        handles.io,
        0,
        1,
        CB_ior0,
        CB_iow0,
        view8,
        &(io_reg_data.io0.value),
        True
    );
    ppmCreateRegister("reg_io1",
        0,
        handles.io,
        1,
        1,
        CB_ior1,
        CB_iow1,
        view8,
        &(io_reg_data.io1.value),
        True
    );



}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.cascade = ppmOpenAddressSpace("cascade");
}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.ir0 = ppmOpenNetPort("ir0");

    handles.ir1 = ppmOpenNetPort("ir1");

    handles.ir2 = ppmOpenNetPort("ir2");

    handles.ir3 = ppmOpenNetPort("ir3");

    handles.ir4 = ppmOpenNetPort("ir4");

    handles.ir5 = ppmOpenNetPort("ir5");

    handles.ir6 = ppmOpenNetPort("ir6");

    handles.ir7 = ppmOpenNetPort("ir7");

// To write to this net, use ppmWriteNet(handles.cas, value);

    handles.cas = ppmOpenNetPort("cas");

// To write to this net, use ppmWriteNet(handles.intp, value);

    handles.intp = ppmOpenNetPort("intp");
    if (!handles.intp) {
        bhmMessage("E", "PPM_NPNC", "Could not connect port 'intp'");
    }

}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    installNetPorts();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Intel 8259A Programmable Interrupt Controller (PIT).");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Intel 8259A Datasheet. MIPS Malta Platform Reference Guide.");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

