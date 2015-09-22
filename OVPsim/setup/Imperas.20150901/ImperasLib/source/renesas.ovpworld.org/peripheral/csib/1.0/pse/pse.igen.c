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

CSIBP0_reg0_dataT CSIBP0_reg0_data;

CSIBP0_reg1_dataT CSIBP0_reg1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "csib", "Example");
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

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.CSIBP0 = ppmCreateSlaveBusPort("CSIBP0", 8);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_CTL0",
        0,
        handles.CSIBP0,
        0,
        1,
        read_8,
        writeCTL0,
        view8,
        &(CSIBP0_reg0_data.CTL0.value),
        True
    );
    ppmCreateRegister("reg0_CTL1",
        0,
        handles.CSIBP0,
        1,
        1,
        read_8,
        writeCTL1,
        view8,
        &(CSIBP0_reg0_data.CTL1.value),
        True
    );
    ppmCreateRegister("reg0_CTL2",
        0,
        handles.CSIBP0,
        2,
        1,
        read_8,
        writeCTL2,
        view8,
        &(CSIBP0_reg0_data.CTL2.value),
        True
    );
    ppmCreateRegister("reg0_STR",
        0,
        handles.CSIBP0,
        3,
        1,
        read_8,
        writeSTR,
        view8,
        &(CSIBP0_reg0_data.STR.value),
        True
    );
    ppmCreateRegister("reg1_RX",
        0,
        handles.CSIBP0,
        4,
        2,
        readRX,
        0,
        view16,
        &(CSIBP0_reg1_data.RX.value),
        True
    );
    ppmCreateRegister("reg1_TX",
        0,
        handles.CSIBP0,
        6,
        2,
        readTX,
        writeTX,
        view16,
        &(CSIBP0_reg1_data.TX.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.INTCBT, value);

    handles.INTCBT = ppmOpenNetPort("INTCBT");

// To write to this net, use ppmWriteNet(handles.INTCBR, value);

    handles.INTCBR = ppmOpenNetPort("INTCBR");

// To write to this net, use ppmWriteNet(handles.INTCBRE, value);

    handles.INTCBRE = ppmOpenNetPort("INTCBRE");

// To write to this net, use ppmWriteNet(handles.SOB, value);

    handles.SOB = ppmOpenNetPort("SOB");

    handles.SIB = ppmOpenNetPort("SIB");
    if (handles.SIB) {
        ppmInstallNetCallback(handles.SIB, P_SIB, (void*)0);
    }

    handles.SSB = ppmOpenNetPort("SSB");
    if (handles.SSB) {
        ppmInstallNetCallback(handles.SSB, P_SSB, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.SCKB, value);

    handles.SCKB = ppmOpenNetPort("SCKB");
    if (handles.SCKB) {
        ppmInstallNetCallback(handles.SCKB, P_SCKB, (void*)0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        CSIBP0_reg1_data.TX.value = 0x0;
        CSIBP0_reg1_data.RX.value = 0x0;
        CSIBP0_reg0_data.STR.value = 0x0;
        CSIBP0_reg0_data.CTL2.value = 0x0;
        CSIBP0_reg0_data.CTL1.value = 0x0;
        CSIBP0_reg0_data.CTL0.value = 0x1;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas CSIB Clocked Serial Interface");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No Support for pin level transitions Clock selection for BRG0, BRG1 or SCKB defaults to PCLK6");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

