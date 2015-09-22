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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "TzpcBP147", "Example");
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

    ppmCreateRegister("ab_TZPCR0SIZE",
        0,
        handles.bport1,
        0,
        4,
        read_32,
        WriteTZPCR0SIZE,
        view32,
        &(bport1_ab_data.TZPCR0SIZE.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT0Stat",
        0,
        handles.bport1,
        2048,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCDECPROT0Stat.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT0Set",
        0,
        handles.bport1,
        2052,
        4,
        0,
        WriteTZPCDECPROT0Set,
        view32,
        &(bport1_ab_data.TZPCDECPROT0Set.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT0Clr",
        0,
        handles.bport1,
        2056,
        4,
        0,
        WriteTZPCDECPROT0Clr,
        view32,
        &(bport1_ab_data.TZPCDECPROT0Clr.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT1Stat",
        0,
        handles.bport1,
        2060,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCDECPROT1Stat.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT1Set",
        0,
        handles.bport1,
        2064,
        4,
        0,
        WriteTZPCDECPROT1Set,
        view32,
        &(bport1_ab_data.TZPCDECPROT1Set.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT1Clr",
        0,
        handles.bport1,
        2068,
        4,
        0,
        WriteTZPCDECPROT1Clr,
        view32,
        &(bport1_ab_data.TZPCDECPROT1Clr.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT2Stat",
        0,
        handles.bport1,
        2072,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCDECPROT2Stat.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT2Set",
        0,
        handles.bport1,
        2076,
        4,
        0,
        WriteTZPCDECPROT2Set,
        view32,
        &(bport1_ab_data.TZPCDECPROT2Set.value),
        True
    );
    ppmCreateRegister("ab_TZPCDECPROT2Clr",
        0,
        handles.bport1,
        2080,
        4,
        0,
        WriteTZPCDECPROT2Clr,
        view32,
        &(bport1_ab_data.TZPCDECPROT2Clr.value),
        True
    );
    ppmCreateRegister("ab_TZPCPERIPHID0",
        0,
        handles.bport1,
        4064,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPERIPHID0.value),
        True
    );
    ppmCreateRegister("ab_TZPCPERIPHID1",
        0,
        handles.bport1,
        4068,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPERIPHID1.value),
        True
    );
    ppmCreateRegister("ab_TZPCPERIPHID2",
        0,
        handles.bport1,
        4072,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPERIPHID2.value),
        True
    );
    ppmCreateRegister("ab_TZPCPERIPHID3",
        0,
        handles.bport1,
        4076,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPERIPHID3.value),
        True
    );
    ppmCreateRegister("ab_TZPCPCELLID0",
        0,
        handles.bport1,
        4080,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPCELLID0.value),
        True
    );
    ppmCreateRegister("ab_TZPCPCELLID1",
        0,
        handles.bport1,
        4084,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPCELLID1.value),
        True
    );
    ppmCreateRegister("ab_TZPCPCELLID2",
        0,
        handles.bport1,
        4088,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPCELLID2.value),
        True
    );
    ppmCreateRegister("ab_TZPCPCELLID3",
        0,
        handles.bport1,
        4092,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TZPCPCELLID3.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.resetNet = ppmOpenNetPort("resetNet");
    if (handles.resetNet) {
        ppmInstallNetCallback(handles.resetNet, reset_resetNet, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.TZPCR0SIZE, value);

    handles.TZPCR0SIZE = ppmOpenNetPort("TZPCR0SIZE");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_0, value);

    handles.TZPCDECPROT0_0 = ppmOpenNetPort("TZPCDECPROT0_0");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_1, value);

    handles.TZPCDECPROT0_1 = ppmOpenNetPort("TZPCDECPROT0_1");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_2, value);

    handles.TZPCDECPROT0_2 = ppmOpenNetPort("TZPCDECPROT0_2");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_3, value);

    handles.TZPCDECPROT0_3 = ppmOpenNetPort("TZPCDECPROT0_3");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_4, value);

    handles.TZPCDECPROT0_4 = ppmOpenNetPort("TZPCDECPROT0_4");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_5, value);

    handles.TZPCDECPROT0_5 = ppmOpenNetPort("TZPCDECPROT0_5");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_6, value);

    handles.TZPCDECPROT0_6 = ppmOpenNetPort("TZPCDECPROT0_6");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_7, value);

    handles.TZPCDECPROT0_7 = ppmOpenNetPort("TZPCDECPROT0_7");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_8, value);

    handles.TZPCDECPROT0_8 = ppmOpenNetPort("TZPCDECPROT0_8");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_9, value);

    handles.TZPCDECPROT0_9 = ppmOpenNetPort("TZPCDECPROT0_9");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_10, value);

    handles.TZPCDECPROT0_10 = ppmOpenNetPort("TZPCDECPROT0_10");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_11, value);

    handles.TZPCDECPROT0_11 = ppmOpenNetPort("TZPCDECPROT0_11");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_12, value);

    handles.TZPCDECPROT0_12 = ppmOpenNetPort("TZPCDECPROT0_12");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_13, value);

    handles.TZPCDECPROT0_13 = ppmOpenNetPort("TZPCDECPROT0_13");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_14, value);

    handles.TZPCDECPROT0_14 = ppmOpenNetPort("TZPCDECPROT0_14");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT0_15, value);

    handles.TZPCDECPROT0_15 = ppmOpenNetPort("TZPCDECPROT0_15");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_0, value);

    handles.TZPCDECPROT1_0 = ppmOpenNetPort("TZPCDECPROT1_0");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_1, value);

    handles.TZPCDECPROT1_1 = ppmOpenNetPort("TZPCDECPROT1_1");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_2, value);

    handles.TZPCDECPROT1_2 = ppmOpenNetPort("TZPCDECPROT1_2");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_3, value);

    handles.TZPCDECPROT1_3 = ppmOpenNetPort("TZPCDECPROT1_3");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_4, value);

    handles.TZPCDECPROT1_4 = ppmOpenNetPort("TZPCDECPROT1_4");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_5, value);

    handles.TZPCDECPROT1_5 = ppmOpenNetPort("TZPCDECPROT1_5");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_6, value);

    handles.TZPCDECPROT1_6 = ppmOpenNetPort("TZPCDECPROT1_6");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_7, value);

    handles.TZPCDECPROT1_7 = ppmOpenNetPort("TZPCDECPROT1_7");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_8, value);

    handles.TZPCDECPROT1_8 = ppmOpenNetPort("TZPCDECPROT1_8");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_9, value);

    handles.TZPCDECPROT1_9 = ppmOpenNetPort("TZPCDECPROT1_9");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_10, value);

    handles.TZPCDECPROT1_10 = ppmOpenNetPort("TZPCDECPROT1_10");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_11, value);

    handles.TZPCDECPROT1_11 = ppmOpenNetPort("TZPCDECPROT1_11");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_12, value);

    handles.TZPCDECPROT1_12 = ppmOpenNetPort("TZPCDECPROT1_12");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_13, value);

    handles.TZPCDECPROT1_13 = ppmOpenNetPort("TZPCDECPROT1_13");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_14, value);

    handles.TZPCDECPROT1_14 = ppmOpenNetPort("TZPCDECPROT1_14");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT1_15, value);

    handles.TZPCDECPROT1_15 = ppmOpenNetPort("TZPCDECPROT1_15");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_0, value);

    handles.TZPCDECPROT2_0 = ppmOpenNetPort("TZPCDECPROT2_0");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_1, value);

    handles.TZPCDECPROT2_1 = ppmOpenNetPort("TZPCDECPROT2_1");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_2, value);

    handles.TZPCDECPROT2_2 = ppmOpenNetPort("TZPCDECPROT2_2");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_3, value);

    handles.TZPCDECPROT2_3 = ppmOpenNetPort("TZPCDECPROT2_3");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_4, value);

    handles.TZPCDECPROT2_4 = ppmOpenNetPort("TZPCDECPROT2_4");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_5, value);

    handles.TZPCDECPROT2_5 = ppmOpenNetPort("TZPCDECPROT2_5");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_6, value);

    handles.TZPCDECPROT2_6 = ppmOpenNetPort("TZPCDECPROT2_6");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_7, value);

    handles.TZPCDECPROT2_7 = ppmOpenNetPort("TZPCDECPROT2_7");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_8, value);

    handles.TZPCDECPROT2_8 = ppmOpenNetPort("TZPCDECPROT2_8");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_9, value);

    handles.TZPCDECPROT2_9 = ppmOpenNetPort("TZPCDECPROT2_9");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_10, value);

    handles.TZPCDECPROT2_10 = ppmOpenNetPort("TZPCDECPROT2_10");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_11, value);

    handles.TZPCDECPROT2_11 = ppmOpenNetPort("TZPCDECPROT2_11");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_12, value);

    handles.TZPCDECPROT2_12 = ppmOpenNetPort("TZPCDECPROT2_12");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_13, value);

    handles.TZPCDECPROT2_13 = ppmOpenNetPort("TZPCDECPROT2_13");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_14, value);

    handles.TZPCDECPROT2_14 = ppmOpenNetPort("TZPCDECPROT2_14");

// To write to this net, use ppmWriteNet(handles.TZPCDECPROT2_15, value);

    handles.TZPCDECPROT2_15 = ppmOpenNetPort("TZPCDECPROT2_15");

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.TZPCPCELLID3.value = 0x81;
        bport1_ab_data.TZPCPCELLID2.value = 0x5;
        bport1_ab_data.TZPCPCELLID1.value = 0xf0;
        bport1_ab_data.TZPCPCELLID0.value = 0xd;
        bport1_ab_data.TZPCPERIPHID3.value = 0x0;
        bport1_ab_data.TZPCPERIPHID2.value = 0x4;
        bport1_ab_data.TZPCPERIPHID1.value = 0x18;
        bport1_ab_data.TZPCPERIPHID0.value = 0x70;
        bport1_ab_data.TZPCDECPROT2Stat.value = 0x0;
        bport1_ab_data.TZPCDECPROT1Stat.value = 0x0;
        bport1_ab_data.TZPCDECPROT0Stat.value = 0x0;
        bport1_ab_data.TZPCR0SIZE.value = 0x200;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM BP147 TrustZone Protection Controller.");
        ppmDocAddText(doc2_node, "There are 24 output net ports (TZPCDECPROT0_0 thru TZPCDECPROT2_7) corresponding to the 24 enables defined as 3 banks of 8 enables.");
        ppmDocAddText(doc2_node, "Each net port may be used to drive a net connected to a peripheral such as the DynamicBridge which can enable/disable a BusBridge mapping under control of an input net.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "ARM PrimeCell Infrastructure AMBA3 TrustZone Protection Controller (BP147) Technical Overview (ARM DTO 0015)");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

