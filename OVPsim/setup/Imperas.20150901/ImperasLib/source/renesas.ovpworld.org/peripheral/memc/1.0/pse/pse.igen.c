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

MEMCP0_reg0_dataT MEMCP0_reg0_data;

MEMCP0_reg1_dataT MEMCP0_reg1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "memc", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.MEMCP0 = ppmCreateSlaveBusPort("MEMCP0", 16);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_BCT0",
        0,
        handles.MEMCP0,
        0,
        2,
        read_16,
        writeBCT0,
        view16,
        &(MEMCP0_reg0_data.BCT0.value),
        True
    );
    ppmCreateRegister("reg0_BCT1",
        0,
        handles.MEMCP0,
        2,
        2,
        read_16,
        writeBCT1,
        view16,
        &(MEMCP0_reg0_data.BCT1.value),
        True
    );
    ppmCreateRegister("reg0_DWC0",
        0,
        handles.MEMCP0,
        4,
        2,
        read_16,
        writeDWC0,
        view16,
        &(MEMCP0_reg0_data.DWC0.value),
        True
    );
    ppmCreateRegister("reg0_DWC1",
        0,
        handles.MEMCP0,
        6,
        2,
        read_16,
        writeDWC1,
        view16,
        &(MEMCP0_reg0_data.DWC1.value),
        True
    );
    ppmCreateRegister("reg0_AWC",
        0,
        handles.MEMCP0,
        8,
        2,
        read_16,
        writeAWC,
        view16,
        &(MEMCP0_reg0_data.AWC.value),
        True
    );
    ppmCreateRegister("reg0_BCC",
        0,
        handles.MEMCP0,
        10,
        2,
        read_16,
        writeBCC,
        view16,
        &(MEMCP0_reg0_data.BCC.value),
        True
    );
    ppmCreateRegister("reg1_DVC",
        0,
        handles.MEMCP0,
        15,
        1,
        read_8,
        writeDVC,
        view8,
        &(MEMCP0_reg1_data.DVC.value),
        True
    );

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        MEMCP0_reg1_data.DVC.value = 0x0;
        MEMCP0_reg0_data.BCC.value = 0xaaaa;
        MEMCP0_reg0_data.AWC.value = 0xffff;
        MEMCP0_reg0_data.DWC1.value = 0x7777;
        MEMCP0_reg0_data.DWC0.value = 0x7777;
        MEMCP0_reg0_data.BCT1.value = 0x4444;
        MEMCP0_reg0_data.BCT0.value = 0x4444;
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
        ppmDocAddText(doc_12_node, "Renesas MEMC Bus Control Unit");
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

