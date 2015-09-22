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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "RtcPL031", "Example");
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

    ppmCreateRegister("ab_dr",
        "Data read",
        handles.bport1,
        0,
        4,
        readDR,
        0,
        view32,
        &(bport1_ab_data.dr.value),
        True
    );
    ppmCreateRegister("ab_mr",
        "Match",
        handles.bport1,
        4,
        4,
        read_32,
        writeMR,
        view32,
        &(bport1_ab_data.mr.value),
        True
    );
    ppmCreateRegister("ab_lr",
        "Data load",
        handles.bport1,
        8,
        4,
        read_32,
        writeLR,
        view32,
        &(bport1_ab_data.lr.value),
        True
    );
    ppmCreateRegister("ab_cr",
        "Control",
        handles.bport1,
        12,
        4,
        readCR,
        writeCR,
        view32,
        &(bport1_ab_data.cr.value),
        True
    );
    ppmCreateRegister("ab_im",
        "Interrupt mask",
        handles.bport1,
        16,
        4,
        read_32,
        writeIM,
        view32,
        &(bport1_ab_data.im.value),
        True
    );
    ppmCreateRegister("ab_is",
        "Raw interrupt",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.is.value),
        True
    );
    ppmCreateRegister("ab_mis",
        "Masked interrupt",
        handles.bport1,
        24,
        4,
        readMIS,
        0,
        view32,
        &(bport1_ab_data.mis.value),
        True
    );
    ppmCreateRegister("ab_icr",
        "Interrupt clear",
        handles.bport1,
        28,
        4,
        0,
        writeICR,
        view32,
        &(bport1_ab_data.icr.value),
        True
    );
    ppmCreateRegister("ab_id0",
        0,
        handles.bport1,
        4064,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id0.value),
        True
    );
    ppmCreateRegister("ab_id1",
        0,
        handles.bport1,
        4068,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id1.value),
        True
    );
    ppmCreateRegister("ab_id2",
        0,
        handles.bport1,
        4072,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id2.value),
        True
    );
    ppmCreateRegister("ab_id3",
        0,
        handles.bport1,
        4076,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id3.value),
        True
    );
    ppmCreateRegister("ab_id4",
        0,
        handles.bport1,
        4080,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id4.value),
        True
    );
    ppmCreateRegister("ab_id5",
        0,
        handles.bport1,
        4084,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id5.value),
        True
    );
    ppmCreateRegister("ab_id6",
        0,
        handles.bport1,
        4088,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id6.value),
        True
    );
    ppmCreateRegister("ab_id7",
        0,
        handles.bport1,
        4092,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id7.value),
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
        ppmDocAddText(doc2_node, "ARM PL031 Real Time Clock (RTC)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM PrimeCell Real Time Clock (PL031) Technical Reference Manual (ARM DDI 0224)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

