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

CRCP0_reg0_dataT CRCP0_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "crc", "Example");
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
    handles.CRCP0 = ppmCreateSlaveBusPort("CRCP0", 128);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_CCRCIN0",
        0,
        handles.CRCP0,
        0,
        4,
        read_32,
        writeCCRCIN0,
        view32,
        &(CRCP0_reg0_data.CCRCIN0.value),
        True
    );
    ppmCreateRegister("reg0_CCRCD0",
        0,
        handles.CRCP0,
        4,
        4,
        read_32,
        writeCCRCD0,
        view32,
        &(CRCP0_reg0_data.CCRCD0.value),
        True
    );
    ppmCreateRegister("reg0_CCRCIN1",
        0,
        handles.CRCP0,
        8,
        4,
        read_32,
        writeCCRCIN1,
        view32,
        &(CRCP0_reg0_data.CCRCIN1.value),
        True
    );
    ppmCreateRegister("reg0_CCRCD1",
        0,
        handles.CRCP0,
        12,
        4,
        read_32,
        writeCCRCD1,
        view32,
        &(CRCP0_reg0_data.CCRCD1.value),
        True
    );
    ppmCreateRegister("reg0_CCRCIN2",
        0,
        handles.CRCP0,
        16,
        4,
        read_32,
        writeCCRCIN2,
        view32,
        &(CRCP0_reg0_data.CCRCIN2.value),
        True
    );
    ppmCreateRegister("reg0_CCRCD2",
        0,
        handles.CRCP0,
        20,
        4,
        read_32,
        writeCCRCD2,
        view32,
        &(CRCP0_reg0_data.CCRCD2.value),
        True
    );
    ppmCreateRegister("reg0_CCRCIN3",
        0,
        handles.CRCP0,
        24,
        4,
        read_32,
        writeCCRCIN3,
        view32,
        &(CRCP0_reg0_data.CCRCIN3.value),
        True
    );
    ppmCreateRegister("reg0_CCRCD3",
        0,
        handles.CRCP0,
        28,
        4,
        read_32,
        writeCCRCD3,
        view32,
        &(CRCP0_reg0_data.CCRCD3.value),
        True
    );
    ppmCreateRegister("reg0_CCRCIN4",
        0,
        handles.CRCP0,
        32,
        4,
        read_32,
        writeCCRCIN4,
        view32,
        &(CRCP0_reg0_data.CCRCIN4.value),
        True
    );
    ppmCreateRegister("reg0_CCRCD4",
        0,
        handles.CRCP0,
        36,
        4,
        read_32,
        writeCCRCD4,
        view32,
        &(CRCP0_reg0_data.CCRCD4.value),
        True
    );
    ppmCreateRegister("reg0_DCRCIN",
        0,
        handles.CRCP0,
        48,
        4,
        read_32,
        writeDCRCIN,
        view32,
        &(CRCP0_reg0_data.DCRCIN.value),
        True
    );
    ppmCreateRegister("reg0_DCRCD",
        0,
        handles.CRCP0,
        52,
        4,
        read_32,
        writeDCRCD,
        view32,
        &(CRCP0_reg0_data.DCRCD.value),
        True
    );
    ppmCreateRegister("reg0_CRCC",
        0,
        handles.CRCP0,
        64,
        4,
        read_32,
        writeCRCC,
        view32,
        &(CRCP0_reg0_data.CRCC.value),
        True
    );

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        CRCP0_reg0_data.CRCC.value = 0x0;
        CRCP0_reg0_data.CCRCD4.value = 0x0;
        CRCP0_reg0_data.CCRCIN4.value = 0x0;
        CRCP0_reg0_data.CCRCD3.value = 0x0;
        CRCP0_reg0_data.CCRCIN3.value = 0x0;
        CRCP0_reg0_data.CCRCD2.value = 0x0;
        CRCP0_reg0_data.CCRCIN2.value = 0x0;
        CRCP0_reg0_data.CCRCD1.value = 0x0;
        CRCP0_reg0_data.CCRCIN1.value = 0x0;
        CRCP0_reg0_data.CCRCD0.value = 0x0;
        CRCP0_reg0_data.CCRCIN0.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas Cyclic Redundancy Generator");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Register View Model Only");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

