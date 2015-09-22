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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisDMAMUX", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_CHCFG0",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        0,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG0.value),
        True
    );
    ppmCreateRegister("ab_CHCFG1",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG1.value),
        True
    );
    ppmCreateRegister("ab_CHCFG2",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        2,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG2.value),
        True
    );
    ppmCreateRegister("ab_CHCFG3",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        3,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG3.value),
        True
    );
    ppmCreateRegister("ab_CHCFG4",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        4,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG4.value),
        True
    );
    ppmCreateRegister("ab_CHCFG5",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        5,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG5.value),
        True
    );
    ppmCreateRegister("ab_CHCFG6",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        6,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG6.value),
        True
    );
    ppmCreateRegister("ab_CHCFG7",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        7,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG7.value),
        True
    );
    ppmCreateRegister("ab_CHCFG8",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        8,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG8.value),
        True
    );
    ppmCreateRegister("ab_CHCFG9",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        9,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG9.value),
        True
    );
    ppmCreateRegister("ab_CHCFG10",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        10,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG10.value),
        True
    );
    ppmCreateRegister("ab_CHCFG11",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        11,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG11.value),
        True
    );
    ppmCreateRegister("ab_CHCFG12",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        12,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG12.value),
        True
    );
    ppmCreateRegister("ab_CHCFG13",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        13,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG13.value),
        True
    );
    ppmCreateRegister("ab_CHCFG14",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        14,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG14.value),
        True
    );
    ppmCreateRegister("ab_CHCFG15",
        "Channel Configuration Register, array offset: 0x0, array step: 0x1 ",
        handles.bport1,
        15,
        1,
        read_8,
        dmamuxWrite,
        view8,
        &(bport1_ab_data.CHCFG15.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, reset_Reset, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.eDMARequest, value);

    handles.eDMARequest = ppmOpenNetPort("eDMARequest");

    handles.dmaSrc0 = ppmOpenNetPort("dmaSrc0");
    if (handles.dmaSrc0) {
        ppmInstallNetCallback(handles.dmaSrc0, dmaSrcRequest, (void*)0);
    }

    handles.dmaSrc1 = ppmOpenNetPort("dmaSrc1");
    if (handles.dmaSrc1) {
        ppmInstallNetCallback(handles.dmaSrc1, dmaSrcRequest, (void*)1);
    }

    handles.dmaSrc2 = ppmOpenNetPort("dmaSrc2");
    if (handles.dmaSrc2) {
        ppmInstallNetCallback(handles.dmaSrc2, dmaSrcRequest, (void*)2);
    }

    handles.dmaSrc3 = ppmOpenNetPort("dmaSrc3");
    if (handles.dmaSrc3) {
        ppmInstallNetCallback(handles.dmaSrc3, dmaSrcRequest, (void*)3);
    }

    handles.dmaSrc4 = ppmOpenNetPort("dmaSrc4");
    if (handles.dmaSrc4) {
        ppmInstallNetCallback(handles.dmaSrc4, dmaSrcRequest, (void*)4);
    }

    handles.dmaSrc5 = ppmOpenNetPort("dmaSrc5");
    if (handles.dmaSrc5) {
        ppmInstallNetCallback(handles.dmaSrc5, dmaSrcRequest, (void*)5);
    }

    handles.dmaSrc6 = ppmOpenNetPort("dmaSrc6");
    if (handles.dmaSrc6) {
        ppmInstallNetCallback(handles.dmaSrc6, dmaSrcRequest, (void*)6);
    }

    handles.dmaSrc7 = ppmOpenNetPort("dmaSrc7");
    if (handles.dmaSrc7) {
        ppmInstallNetCallback(handles.dmaSrc7, dmaSrcRequest, (void*)7);
    }

    handles.dmaSrc8 = ppmOpenNetPort("dmaSrc8");
    if (handles.dmaSrc8) {
        ppmInstallNetCallback(handles.dmaSrc8, dmaSrcRequest, (void*)8);
    }

    handles.dmaSrc9 = ppmOpenNetPort("dmaSrc9");
    if (handles.dmaSrc9) {
        ppmInstallNetCallback(handles.dmaSrc9, dmaSrcRequest, (void*)9);
    }

    handles.dmaSrc10 = ppmOpenNetPort("dmaSrc10");
    if (handles.dmaSrc10) {
        ppmInstallNetCallback(handles.dmaSrc10, dmaSrcRequest, (void*)10);
    }

    handles.dmaSrc11 = ppmOpenNetPort("dmaSrc11");
    if (handles.dmaSrc11) {
        ppmInstallNetCallback(handles.dmaSrc11, dmaSrcRequest, (void*)11);
    }

    handles.dmaSrc12 = ppmOpenNetPort("dmaSrc12");
    if (handles.dmaSrc12) {
        ppmInstallNetCallback(handles.dmaSrc12, dmaSrcRequest, (void*)12);
    }

    handles.dmaSrc13 = ppmOpenNetPort("dmaSrc13");
    if (handles.dmaSrc13) {
        ppmInstallNetCallback(handles.dmaSrc13, dmaSrcRequest, (void*)13);
    }

    handles.dmaSrc14 = ppmOpenNetPort("dmaSrc14");
    if (handles.dmaSrc14) {
        ppmInstallNetCallback(handles.dmaSrc14, dmaSrcRequest, (void*)14);
    }

    handles.dmaSrc15 = ppmOpenNetPort("dmaSrc15");
    if (handles.dmaSrc15) {
        ppmInstallNetCallback(handles.dmaSrc15, dmaSrcRequest, (void*)15);
    }

    handles.dmaSrc16 = ppmOpenNetPort("dmaSrc16");
    if (handles.dmaSrc16) {
        ppmInstallNetCallback(handles.dmaSrc16, dmaSrcRequest, (void*)16);
    }

    handles.dmaSrc17 = ppmOpenNetPort("dmaSrc17");
    if (handles.dmaSrc17) {
        ppmInstallNetCallback(handles.dmaSrc17, dmaSrcRequest, (void*)17);
    }

    handles.dmaSrc18 = ppmOpenNetPort("dmaSrc18");
    if (handles.dmaSrc18) {
        ppmInstallNetCallback(handles.dmaSrc18, dmaSrcRequest, (void*)18);
    }

    handles.dmaSrc19 = ppmOpenNetPort("dmaSrc19");
    if (handles.dmaSrc19) {
        ppmInstallNetCallback(handles.dmaSrc19, dmaSrcRequest, (void*)19);
    }

    handles.dmaSrc20 = ppmOpenNetPort("dmaSrc20");
    if (handles.dmaSrc20) {
        ppmInstallNetCallback(handles.dmaSrc20, dmaSrcRequest, (void*)20);
    }

    handles.dmaSrc21 = ppmOpenNetPort("dmaSrc21");
    if (handles.dmaSrc21) {
        ppmInstallNetCallback(handles.dmaSrc21, dmaSrcRequest, (void*)21);
    }

    handles.dmaSrc22 = ppmOpenNetPort("dmaSrc22");
    if (handles.dmaSrc22) {
        ppmInstallNetCallback(handles.dmaSrc22, dmaSrcRequest, (void*)22);
    }

    handles.dmaSrc23 = ppmOpenNetPort("dmaSrc23");
    if (handles.dmaSrc23) {
        ppmInstallNetCallback(handles.dmaSrc23, dmaSrcRequest, (void*)23);
    }

    handles.dmaSrc24 = ppmOpenNetPort("dmaSrc24");
    if (handles.dmaSrc24) {
        ppmInstallNetCallback(handles.dmaSrc24, dmaSrcRequest, (void*)24);
    }

    handles.dmaSrc25 = ppmOpenNetPort("dmaSrc25");
    if (handles.dmaSrc25) {
        ppmInstallNetCallback(handles.dmaSrc25, dmaSrcRequest, (void*)25);
    }

    handles.dmaSrc26 = ppmOpenNetPort("dmaSrc26");
    if (handles.dmaSrc26) {
        ppmInstallNetCallback(handles.dmaSrc26, dmaSrcRequest, (void*)26);
    }

    handles.dmaSrc27 = ppmOpenNetPort("dmaSrc27");
    if (handles.dmaSrc27) {
        ppmInstallNetCallback(handles.dmaSrc27, dmaSrcRequest, (void*)27);
    }

    handles.dmaSrc28 = ppmOpenNetPort("dmaSrc28");
    if (handles.dmaSrc28) {
        ppmInstallNetCallback(handles.dmaSrc28, dmaSrcRequest, (void*)28);
    }

    handles.dmaSrc29 = ppmOpenNetPort("dmaSrc29");
    if (handles.dmaSrc29) {
        ppmInstallNetCallback(handles.dmaSrc29, dmaSrcRequest, (void*)29);
    }

    handles.dmaSrc30 = ppmOpenNetPort("dmaSrc30");
    if (handles.dmaSrc30) {
        ppmInstallNetCallback(handles.dmaSrc30, dmaSrcRequest, (void*)30);
    }

    handles.dmaSrc31 = ppmOpenNetPort("dmaSrc31");
    if (handles.dmaSrc31) {
        ppmInstallNetCallback(handles.dmaSrc31, dmaSrcRequest, (void*)31);
    }

    handles.dmaSrc32 = ppmOpenNetPort("dmaSrc32");
    if (handles.dmaSrc32) {
        ppmInstallNetCallback(handles.dmaSrc32, dmaSrcRequest, (void*)32);
    }

    handles.dmaSrc33 = ppmOpenNetPort("dmaSrc33");
    if (handles.dmaSrc33) {
        ppmInstallNetCallback(handles.dmaSrc33, dmaSrcRequest, (void*)33);
    }

    handles.dmaSrc34 = ppmOpenNetPort("dmaSrc34");
    if (handles.dmaSrc34) {
        ppmInstallNetCallback(handles.dmaSrc34, dmaSrcRequest, (void*)34);
    }

    handles.dmaSrc35 = ppmOpenNetPort("dmaSrc35");
    if (handles.dmaSrc35) {
        ppmInstallNetCallback(handles.dmaSrc35, dmaSrcRequest, (void*)35);
    }

    handles.dmaSrc36 = ppmOpenNetPort("dmaSrc36");
    if (handles.dmaSrc36) {
        ppmInstallNetCallback(handles.dmaSrc36, dmaSrcRequest, (void*)36);
    }

    handles.dmaSrc37 = ppmOpenNetPort("dmaSrc37");
    if (handles.dmaSrc37) {
        ppmInstallNetCallback(handles.dmaSrc37, dmaSrcRequest, (void*)37);
    }

    handles.dmaSrc38 = ppmOpenNetPort("dmaSrc38");
    if (handles.dmaSrc38) {
        ppmInstallNetCallback(handles.dmaSrc38, dmaSrcRequest, (void*)38);
    }

    handles.dmaSrc39 = ppmOpenNetPort("dmaSrc39");
    if (handles.dmaSrc39) {
        ppmInstallNetCallback(handles.dmaSrc39, dmaSrcRequest, (void*)39);
    }

    handles.dmaSrc40 = ppmOpenNetPort("dmaSrc40");
    if (handles.dmaSrc40) {
        ppmInstallNetCallback(handles.dmaSrc40, dmaSrcRequest, (void*)40);
    }

    handles.dmaSrc41 = ppmOpenNetPort("dmaSrc41");
    if (handles.dmaSrc41) {
        ppmInstallNetCallback(handles.dmaSrc41, dmaSrcRequest, (void*)41);
    }

    handles.dmaSrc42 = ppmOpenNetPort("dmaSrc42");
    if (handles.dmaSrc42) {
        ppmInstallNetCallback(handles.dmaSrc42, dmaSrcRequest, (void*)42);
    }

    handles.dmaSrc43 = ppmOpenNetPort("dmaSrc43");
    if (handles.dmaSrc43) {
        ppmInstallNetCallback(handles.dmaSrc43, dmaSrcRequest, (void*)43);
    }

    handles.dmaSrc44 = ppmOpenNetPort("dmaSrc44");
    if (handles.dmaSrc44) {
        ppmInstallNetCallback(handles.dmaSrc44, dmaSrcRequest, (void*)44);
    }

    handles.dmaSrc45 = ppmOpenNetPort("dmaSrc45");
    if (handles.dmaSrc45) {
        ppmInstallNetCallback(handles.dmaSrc45, dmaSrcRequest, (void*)45);
    }

    handles.dmaSrc46 = ppmOpenNetPort("dmaSrc46");
    if (handles.dmaSrc46) {
        ppmInstallNetCallback(handles.dmaSrc46, dmaSrcRequest, (void*)46);
    }

    handles.dmaSrc47 = ppmOpenNetPort("dmaSrc47");
    if (handles.dmaSrc47) {
        ppmInstallNetCallback(handles.dmaSrc47, dmaSrcRequest, (void*)47);
    }

    handles.dmaSrc48 = ppmOpenNetPort("dmaSrc48");
    if (handles.dmaSrc48) {
        ppmInstallNetCallback(handles.dmaSrc48, dmaSrcRequest, (void*)48);
    }

    handles.dmaSrc49 = ppmOpenNetPort("dmaSrc49");
    if (handles.dmaSrc49) {
        ppmInstallNetCallback(handles.dmaSrc49, dmaSrcRequest, (void*)49);
    }

    handles.dmaSrc50 = ppmOpenNetPort("dmaSrc50");
    if (handles.dmaSrc50) {
        ppmInstallNetCallback(handles.dmaSrc50, dmaSrcRequest, (void*)50);
    }

    handles.dmaSrc51 = ppmOpenNetPort("dmaSrc51");
    if (handles.dmaSrc51) {
        ppmInstallNetCallback(handles.dmaSrc51, dmaSrcRequest, (void*)51);
    }

    handles.dmaSrc52 = ppmOpenNetPort("dmaSrc52");
    if (handles.dmaSrc52) {
        ppmInstallNetCallback(handles.dmaSrc52, dmaSrcRequest, (void*)52);
    }

    handles.dmaSrc53 = ppmOpenNetPort("dmaSrc53");
    if (handles.dmaSrc53) {
        ppmInstallNetCallback(handles.dmaSrc53, dmaSrcRequest, (void*)53);
    }

    handles.dmaSrc54 = ppmOpenNetPort("dmaSrc54");
    if (handles.dmaSrc54) {
        ppmInstallNetCallback(handles.dmaSrc54, dmaSrcRequest, (void*)54);
    }

    handles.dmaSrc55 = ppmOpenNetPort("dmaSrc55");
    if (handles.dmaSrc55) {
        ppmInstallNetCallback(handles.dmaSrc55, dmaSrcRequest, (void*)55);
    }

    handles.dmaSrc56 = ppmOpenNetPort("dmaSrc56");
    if (handles.dmaSrc56) {
        ppmInstallNetCallback(handles.dmaSrc56, dmaSrcRequest, (void*)56);
    }

    handles.dmaSrc57 = ppmOpenNetPort("dmaSrc57");
    if (handles.dmaSrc57) {
        ppmInstallNetCallback(handles.dmaSrc57, dmaSrcRequest, (void*)57);
    }

    handles.dmaSrc58 = ppmOpenNetPort("dmaSrc58");
    if (handles.dmaSrc58) {
        ppmInstallNetCallback(handles.dmaSrc58, dmaSrcRequest, (void*)58);
    }

    handles.dmaSrc59 = ppmOpenNetPort("dmaSrc59");
    if (handles.dmaSrc59) {
        ppmInstallNetCallback(handles.dmaSrc59, dmaSrcRequest, (void*)59);
    }

    handles.dmaSrc60 = ppmOpenNetPort("dmaSrc60");
    if (handles.dmaSrc60) {
        ppmInstallNetCallback(handles.dmaSrc60, dmaSrcRequest, (void*)60);
    }

    handles.dmaSrc61 = ppmOpenNetPort("dmaSrc61");
    if (handles.dmaSrc61) {
        ppmInstallNetCallback(handles.dmaSrc61, dmaSrcRequest, (void*)61);
    }

    handles.dmaSrc62 = ppmOpenNetPort("dmaSrc62");
    if (handles.dmaSrc62) {
        ppmInstallNetCallback(handles.dmaSrc62, dmaSrcRequest, (void*)62);
    }

    handles.dmaSrc63 = ppmOpenNetPort("dmaSrc63");
    if (handles.dmaSrc63) {
        ppmInstallNetCallback(handles.dmaSrc63, dmaSrcRequest, (void*)63);
    }

    handles.trg1 = ppmOpenNetPort("trg1");
    if (handles.trg1) {
        ppmInstallNetCallback(handles.trg1, dmaTrgRequest, (void*)1);
    }

    handles.trg2 = ppmOpenNetPort("trg2");
    if (handles.trg2) {
        ppmInstallNetCallback(handles.trg2, dmaTrgRequest, (void*)2);
    }

    handles.trg3 = ppmOpenNetPort("trg3");
    if (handles.trg3) {
        ppmInstallNetCallback(handles.trg3, dmaTrgRequest, (void*)3);
    }

    handles.trg4 = ppmOpenNetPort("trg4");
    if (handles.trg4) {
        ppmInstallNetCallback(handles.trg4, dmaTrgRequest, (void*)4);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CHCFG15.value = 0x0;
        bport1_ab_data.CHCFG14.value = 0x0;
        bport1_ab_data.CHCFG13.value = 0x0;
        bport1_ab_data.CHCFG12.value = 0x0;
        bport1_ab_data.CHCFG11.value = 0x0;
        bport1_ab_data.CHCFG10.value = 0x0;
        bport1_ab_data.CHCFG9.value = 0x0;
        bport1_ab_data.CHCFG8.value = 0x0;
        bport1_ab_data.CHCFG7.value = 0x0;
        bport1_ab_data.CHCFG6.value = 0x0;
        bport1_ab_data.CHCFG5.value = 0x0;
        bport1_ab_data.CHCFG4.value = 0x0;
        bport1_ab_data.CHCFG3.value = 0x0;
        bport1_ab_data.CHCFG2.value = 0x0;
        bport1_ab_data.CHCFG1.value = 0x0;
        bport1_ab_data.CHCFG0.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, 0);
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, 0);
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

