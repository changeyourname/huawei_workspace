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

CSIEP0_reg0_dataT CSIEP0_reg0_data;

CSIEP0_reg1_dataT CSIEP0_reg1_data;

CSIEP0_reg2_dataT CSIEP0_reg2_data;

CSIEP0_reg3_dataT CSIEP0_reg3_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "csie", "Example");
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
    handles.CSIEP0 = ppmCreateSlaveBusPort("CSIEP0", 32);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_CTL0",
        0,
        handles.CSIEP0,
        0,
        1,
        read_8,
        writeCTL0,
        view8,
        &(CSIEP0_reg0_data.CTL0.value),
        True
    );
    ppmCreateRegister("reg0_CTL1",
        0,
        handles.CSIEP0,
        1,
        1,
        read_8,
        writeCTL1,
        view8,
        &(CSIEP0_reg0_data.CTL1.value),
        True
    );
    ppmCreateRegister("reg1_RX",
        0,
        handles.CSIEP0,
        2,
        2,
        readRX,
        0,
        view16,
        &(CSIEP0_reg1_data.RX.value),
        True
    );
    ppmCreateRegister("reg1_CS",
        0,
        handles.CSIEP0,
        4,
        2,
        read_16,
        writeCS,
        view16,
        &(CSIEP0_reg1_data.CS.value),
        True
    );
    ppmCreateRegister("reg1_TX",
        0,
        handles.CSIEP0,
        6,
        2,
        readTX,
        writeTX,
        view16,
        &(CSIEP0_reg1_data.TX.value),
        True
    );
    ppmCreateRegister("reg2_STR",
        0,
        handles.CSIEP0,
        8,
        1,
        read_8,
        writeSTR,
        view8,
        &(CSIEP0_reg2_data.STR.value),
        True
    );
    ppmCreateRegister("reg2_CTL2",
        0,
        handles.CSIEP0,
        9,
        1,
        read_8,
        writeCTL2,
        view8,
        &(CSIEP0_reg2_data.CTL2.value),
        True
    );
    ppmCreateRegister("reg2_CTL3",
        0,
        handles.CSIEP0,
        12,
        1,
        read_8,
        writeCTL3,
        view8,
        &(CSIEP0_reg2_data.CTL3.value),
        True
    );
    ppmCreateRegister("reg2_CTL4",
        0,
        handles.CSIEP0,
        13,
        1,
        read_8,
        writeCTL4,
        view8,
        &(CSIEP0_reg2_data.CTL4.value),
        True
    );
    ppmCreateRegister("reg3_OPT0",
        0,
        handles.CSIEP0,
        16,
        2,
        read_16,
        writeOPT0,
        view16,
        &(CSIEP0_reg3_data.OPT0.value),
        True
    );
    ppmCreateRegister("reg3_OPT1",
        0,
        handles.CSIEP0,
        18,
        2,
        read_16,
        writeOPT1,
        view16,
        &(CSIEP0_reg3_data.OPT1.value),
        True
    );
    ppmCreateRegister("reg3_OPT2",
        0,
        handles.CSIEP0,
        20,
        2,
        read_16,
        writeOPT2,
        view16,
        &(CSIEP0_reg3_data.OPT2.value),
        True
    );
    ppmCreateRegister("reg3_OPT3",
        0,
        handles.CSIEP0,
        22,
        2,
        read_16,
        writeOPT3,
        view16,
        &(CSIEP0_reg3_data.OPT3.value),
        True
    );
    ppmCreateRegister("reg3_OPT4",
        0,
        handles.CSIEP0,
        24,
        2,
        read_16,
        writeOPT4,
        view16,
        &(CSIEP0_reg3_data.OPT4.value),
        True
    );
    ppmCreateRegister("reg3_OPT5",
        0,
        handles.CSIEP0,
        26,
        2,
        read_16,
        writeOPT5,
        view16,
        &(CSIEP0_reg3_data.OPT5.value),
        True
    );
    ppmCreateRegister("reg3_OPT6",
        0,
        handles.CSIEP0,
        28,
        2,
        read_16,
        writeOPT6,
        view16,
        &(CSIEP0_reg3_data.OPT6.value),
        True
    );
    ppmCreateRegister("reg3_OPT7",
        0,
        handles.CSIEP0,
        30,
        2,
        read_16,
        writeOPT7,
        view16,
        &(CSIEP0_reg3_data.OPT7.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.INTCEOF, value);

    handles.INTCEOF = ppmOpenNetPort("INTCEOF");

// To write to this net, use ppmWriteNet(handles.INTCEC, value);

    handles.INTCEC = ppmOpenNetPort("INTCEC");

// To write to this net, use ppmWriteNet(handles.SOE, value);

    handles.SOE = ppmOpenNetPort("SOE");

// To write to this net, use ppmWriteNet(handles.SCSE0, value);

    handles.SCSE0 = ppmOpenNetPort("SCSE0");

// To write to this net, use ppmWriteNet(handles.SCSE1, value);

    handles.SCSE1 = ppmOpenNetPort("SCSE1");

// To write to this net, use ppmWriteNet(handles.SCSE2, value);

    handles.SCSE2 = ppmOpenNetPort("SCSE2");

// To write to this net, use ppmWriteNet(handles.SCSE3, value);

    handles.SCSE3 = ppmOpenNetPort("SCSE3");

// To write to this net, use ppmWriteNet(handles.SCSE4, value);

    handles.SCSE4 = ppmOpenNetPort("SCSE4");

// To write to this net, use ppmWriteNet(handles.SCSE5, value);

    handles.SCSE5 = ppmOpenNetPort("SCSE5");

// To write to this net, use ppmWriteNet(handles.SCSE6, value);

    handles.SCSE6 = ppmOpenNetPort("SCSE6");

// To write to this net, use ppmWriteNet(handles.SCSE7, value);

    handles.SCSE7 = ppmOpenNetPort("SCSE7");

    handles.SIE = ppmOpenNetPort("SIE");
    if (handles.SIE) {
        ppmInstallNetCallback(handles.SIE, P_SIE, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.SCKE, value);

    handles.SCKE = ppmOpenNetPort("SCKE");
    if (handles.SCKE) {
        ppmInstallNetCallback(handles.SCKE, P_SCKE, (void*)0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        CSIEP0_reg3_data.OPT7.value = 0x2;
        CSIEP0_reg3_data.OPT6.value = 0x2;
        CSIEP0_reg3_data.OPT5.value = 0x2;
        CSIEP0_reg3_data.OPT4.value = 0x2;
        CSIEP0_reg3_data.OPT3.value = 0x2;
        CSIEP0_reg3_data.OPT2.value = 0x2;
        CSIEP0_reg3_data.OPT1.value = 0x2;
        CSIEP0_reg3_data.OPT0.value = 0x2;
        CSIEP0_reg2_data.CTL4.value = 0x0;
        CSIEP0_reg2_data.CTL3.value = 0x0;
        CSIEP0_reg2_data.CTL2.value = 0x0;
        CSIEP0_reg2_data.STR.value = 0x20;
        CSIEP0_reg1_data.TX.value = 0x0;
        CSIEP0_reg1_data.CS.value = 0xffff;
        CSIEP0_reg1_data.RX.value = 0x0;
        CSIEP0_reg0_data.CTL1.value = 0x7;
        CSIEP0_reg0_data.CTL0.value = 0x0;
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
        ppmDocAddText(doc_12_node, "Renesas CSIE Enhanced Queued Clocked Serial Interface");
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

