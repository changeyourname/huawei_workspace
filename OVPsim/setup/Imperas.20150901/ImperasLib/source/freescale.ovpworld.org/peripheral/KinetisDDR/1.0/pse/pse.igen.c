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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisDDR", "Example");
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

    ppmCreateRegister("ab_CR00",
        "DDR Control Register 0, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR00.value),
        True
    );
    ppmCreateRegister("ab_CR01",
        "DDR Control Register 1, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR01.value),
        True
    );
    ppmCreateRegister("ab_CR02",
        "DDR Control Register 2, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR02.value),
        True
    );
    ppmCreateRegister("ab_CR03",
        "DDR Control Register 3, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR03.value),
        True
    );
    ppmCreateRegister("ab_CR04",
        "DDR Control Register 4, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR04.value),
        True
    );
    ppmCreateRegister("ab_CR05",
        "DDR Control Register 5, offset: 0x14 ",
        handles.bport1,
        20,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR05.value),
        True
    );
    ppmCreateRegister("ab_CR06",
        "DDR Control Register 6, offset: 0x18 ",
        handles.bport1,
        24,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR06.value),
        True
    );
    ppmCreateRegister("ab_CR07",
        "DDR Control Register 7, offset: 0x1C ",
        handles.bport1,
        28,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR07.value),
        True
    );
    ppmCreateRegister("ab_CR08",
        "DDR Control Register 8, offset: 0x20 ",
        handles.bport1,
        32,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR08.value),
        True
    );
    ppmCreateRegister("ab_CR09",
        "DDR Control Register 9, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR09.value),
        True
    );
    ppmCreateRegister("ab_CR10",
        "DDR Control Register 10, offset: 0x28 ",
        handles.bport1,
        40,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR10.value),
        True
    );
    ppmCreateRegister("ab_CR11",
        "DDR Control Register 11, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR11.value),
        True
    );
    ppmCreateRegister("ab_CR12",
        "DDR Control Register 12, offset: 0x30 ",
        handles.bport1,
        48,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR12.value),
        True
    );
    ppmCreateRegister("ab_CR13",
        "DDR Control Register 13, offset: 0x34 ",
        handles.bport1,
        52,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR13.value),
        True
    );
    ppmCreateRegister("ab_CR14",
        "DDR Control Register 14, offset: 0x38 ",
        handles.bport1,
        56,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR14.value),
        True
    );
    ppmCreateRegister("ab_CR15",
        "DDR Control Register 15, offset: 0x3C ",
        handles.bport1,
        60,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR15.value),
        True
    );
    ppmCreateRegister("ab_CR16",
        "DDR Control Register 16, offset: 0x40 ",
        handles.bport1,
        64,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR16.value),
        True
    );
    ppmCreateRegister("ab_CR17",
        "DDR Control Register 17, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR17.value),
        True
    );
    ppmCreateRegister("ab_CR18",
        "DDR Control Register 18, offset: 0x48 ",
        handles.bport1,
        72,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR18.value),
        True
    );
    ppmCreateRegister("ab_CR19",
        "DDR Control Register 19, offset: 0x4C ",
        handles.bport1,
        76,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR19.value),
        True
    );
    ppmCreateRegister("ab_CR20",
        "DDR Control Register 20, offset: 0x50 ",
        handles.bport1,
        80,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR20.value),
        True
    );
    ppmCreateRegister("ab_CR21",
        "DDR Control Register 21, offset: 0x54 ",
        handles.bport1,
        84,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR21.value),
        True
    );
    ppmCreateRegister("ab_CR22",
        "DDR Control Register 22, offset: 0x58 ",
        handles.bport1,
        88,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR22.value),
        True
    );
    ppmCreateRegister("ab_CR23",
        "DDR Control Register 23, offset: 0x5C ",
        handles.bport1,
        92,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR23.value),
        True
    );
    ppmCreateRegister("ab_CR24",
        "DDR Control Register 24, offset: 0x60 ",
        handles.bport1,
        96,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR24.value),
        True
    );
    ppmCreateRegister("ab_CR25",
        "DDR Control Register 25, offset: 0x64 ",
        handles.bport1,
        100,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR25.value),
        True
    );
    ppmCreateRegister("ab_CR26",
        "DDR Control Register 26, offset: 0x68 ",
        handles.bport1,
        104,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR26.value),
        True
    );
    ppmCreateRegister("ab_CR27",
        "DDR Control Register 27, offset: 0x6C ",
        handles.bport1,
        108,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR27.value),
        True
    );
    ppmCreateRegister("ab_CR28",
        "DDR Control Register 28, offset: 0x70 ",
        handles.bport1,
        112,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR28.value),
        True
    );
    ppmCreateRegister("ab_CR29",
        "DDR Control Register 29, offset: 0x74 ",
        handles.bport1,
        116,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR29.value),
        True
    );
    ppmCreateRegister("ab_CR30",
        "DDR Control Register 30, offset: 0x78 ",
        handles.bport1,
        120,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR30.value),
        True
    );
    ppmCreateRegister("ab_CR31",
        "DDR Control Register 31, offset: 0x7C ",
        handles.bport1,
        124,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR31.value),
        True
    );
    ppmCreateRegister("ab_CR32",
        "DDR Control Register 32, offset: 0x80 ",
        handles.bport1,
        128,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR32.value),
        True
    );
    ppmCreateRegister("ab_CR33",
        "DDR Control Register 33, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR33.value),
        True
    );
    ppmCreateRegister("ab_CR34",
        "DDR Control Register 34, offset: 0x88 ",
        handles.bport1,
        136,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR34.value),
        True
    );
    ppmCreateRegister("ab_CR35",
        "DDR Control Register 35, offset: 0x8C ",
        handles.bport1,
        140,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR35.value),
        True
    );
    ppmCreateRegister("ab_CR36",
        "DDR Control Register 36, offset: 0x90 ",
        handles.bport1,
        144,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR36.value),
        True
    );
    ppmCreateRegister("ab_CR37",
        "DDR Control Register 37, offset: 0x94 ",
        handles.bport1,
        148,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR37.value),
        True
    );
    ppmCreateRegister("ab_CR38",
        "DDR Control Register 38, offset: 0x98 ",
        handles.bport1,
        152,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR38.value),
        True
    );
    ppmCreateRegister("ab_CR39",
        "DDR Control Register 39, offset: 0x9C ",
        handles.bport1,
        156,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR39.value),
        True
    );
    ppmCreateRegister("ab_CR40",
        "DDR Control Register 40, offset: 0xA0 ",
        handles.bport1,
        160,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR40.value),
        True
    );
    ppmCreateRegister("ab_CR41",
        "DDR Control Register 41, offset: 0xA4 ",
        handles.bport1,
        164,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR41.value),
        True
    );
    ppmCreateRegister("ab_CR42",
        "DDR Control Register 42, offset: 0xA8 ",
        handles.bport1,
        168,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR42.value),
        True
    );
    ppmCreateRegister("ab_CR43",
        "DDR Control Register 43, offset: 0xAC ",
        handles.bport1,
        172,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR43.value),
        True
    );
    ppmCreateRegister("ab_CR44",
        "DDR Control Register 44, offset: 0xB0 ",
        handles.bport1,
        176,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR44.value),
        True
    );
    ppmCreateRegister("ab_CR45",
        "DDR Control Register 45, offset: 0xB4 ",
        handles.bport1,
        180,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR45.value),
        True
    );
    ppmCreateRegister("ab_CR46",
        "DDR Control Register 46, offset: 0xB8 ",
        handles.bport1,
        184,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR46.value),
        True
    );
    ppmCreateRegister("ab_CR47",
        "DDR Control Register 47, offset: 0xBC ",
        handles.bport1,
        188,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR47.value),
        True
    );
    ppmCreateRegister("ab_CR48",
        "DDR Control Register 48, offset: 0xC0 ",
        handles.bport1,
        192,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR48.value),
        True
    );
    ppmCreateRegister("ab_CR49",
        "DDR Control Register 49, offset: 0xC4 ",
        handles.bport1,
        196,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR49.value),
        True
    );
    ppmCreateRegister("ab_CR50",
        "DDR Control Register 50, offset: 0xC8 ",
        handles.bport1,
        200,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR50.value),
        True
    );
    ppmCreateRegister("ab_CR51",
        "DDR Control Register 51, offset: 0xCC ",
        handles.bport1,
        204,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR51.value),
        True
    );
    ppmCreateRegister("ab_CR52",
        "DDR Control Register 52, offset: 0xD0 ",
        handles.bport1,
        208,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR52.value),
        True
    );
    ppmCreateRegister("ab_CR53",
        "DDR Control Register 53, offset: 0xD4 ",
        handles.bport1,
        212,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR53.value),
        True
    );
    ppmCreateRegister("ab_CR54",
        "DDR Control Register 54, offset: 0xD8 ",
        handles.bport1,
        216,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR54.value),
        True
    );
    ppmCreateRegister("ab_CR55",
        "DDR Control Register 55, offset: 0xDC ",
        handles.bport1,
        220,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR55.value),
        True
    );
    ppmCreateRegister("ab_CR56",
        "DDR Control Register 56, offset: 0xE0 ",
        handles.bport1,
        224,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR56.value),
        True
    );
    ppmCreateRegister("ab_CR57",
        "DDR Control Register 57, offset: 0xE4 ",
        handles.bport1,
        228,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR57.value),
        True
    );
    ppmCreateRegister("ab_CR58",
        "DDR Control Register 58, offset: 0xE8 ",
        handles.bport1,
        232,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR58.value),
        True
    );
    ppmCreateRegister("ab_CR59",
        "DDR Control Register 59, offset: 0xEC ",
        handles.bport1,
        236,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR59.value),
        True
    );
    ppmCreateRegister("ab_CR60",
        "DDR Control Register 60, offset: 0xF0 ",
        handles.bport1,
        240,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR60.value),
        True
    );
    ppmCreateRegister("ab_CR61",
        "DDR Control Register 61, offset: 0xF4 ",
        handles.bport1,
        244,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR61.value),
        True
    );
    ppmCreateRegister("ab_CR62",
        "DDR Control Register 62, offset: 0xF8 ",
        handles.bport1,
        248,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR62.value),
        True
    );
    ppmCreateRegister("ab_CR63",
        "DDR Control Register 63, offset: 0xFC ",
        handles.bport1,
        252,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CR63.value),
        True
    );
    ppmCreateRegister("ab_RCR",
        "RCR Control Register, offset: 0x180 ",
        handles.bport1,
        384,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.RCR.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, reset_Reset, (void*)0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.RCR.value = 0x0;
        bport1_ab_data.CR63.value = 0x0;
        bport1_ab_data.CR62.value = 0x0;
        bport1_ab_data.CR61.value = 0x0;
        bport1_ab_data.CR60.value = 0x0;
        bport1_ab_data.CR59.value = 0x0;
        bport1_ab_data.CR58.value = 0x0;
        bport1_ab_data.CR57.value = 0x0;
        bport1_ab_data.CR56.value = 0x0;
        bport1_ab_data.CR55.value = 0x0;
        bport1_ab_data.CR54.value = 0x0;
        bport1_ab_data.CR53.value = 0x0;
        bport1_ab_data.CR52.value = 0x0;
        bport1_ab_data.CR51.value = 0x0;
        bport1_ab_data.CR50.value = 0x0;
        bport1_ab_data.CR49.value = 0x0;
        bport1_ab_data.CR48.value = 0x0;
        bport1_ab_data.CR47.value = 0x0;
        bport1_ab_data.CR46.value = 0x0;
        bport1_ab_data.CR45.value = 0x0;
        bport1_ab_data.CR44.value = 0x0;
        bport1_ab_data.CR43.value = 0x0;
        bport1_ab_data.CR42.value = 0x0;
        bport1_ab_data.CR41.value = 0x0;
        bport1_ab_data.CR40.value = 0x0;
        bport1_ab_data.CR39.value = 0x0;
        bport1_ab_data.CR38.value = 0x0;
        bport1_ab_data.CR37.value = 0x0;
        bport1_ab_data.CR36.value = 0x0;
        bport1_ab_data.CR35.value = 0x0;
        bport1_ab_data.CR34.value = 0x0;
        bport1_ab_data.CR33.value = 0x0;
        bport1_ab_data.CR32.value = 0x0;
        bport1_ab_data.CR31.value = 0x0;
        bport1_ab_data.CR30.value = 0x0;
        bport1_ab_data.CR29.value = 0x0;
        bport1_ab_data.CR28.value = 0x0;
        bport1_ab_data.CR27.value = 0x0;
        bport1_ab_data.CR26.value = 0x0;
        bport1_ab_data.CR25.value = 0x0;
        bport1_ab_data.CR24.value = 0x0;
        bport1_ab_data.CR23.value = 0x0;
        bport1_ab_data.CR22.value = 0x0;
        bport1_ab_data.CR21.value = 0x0;
        bport1_ab_data.CR20.value = 0x0;
        bport1_ab_data.CR19.value = 0x0;
        bport1_ab_data.CR18.value = 0x0;
        bport1_ab_data.CR17.value = 0x0;
        bport1_ab_data.CR16.value = 0x0;
        bport1_ab_data.CR15.value = 0x0;
        bport1_ab_data.CR14.value = 0x0;
        bport1_ab_data.CR13.value = 0x0;
        bport1_ab_data.CR12.value = 0x0;
        bport1_ab_data.CR11.value = 0x0;
        bport1_ab_data.CR10.value = 0x0;
        bport1_ab_data.CR09.value = 0x0;
        bport1_ab_data.CR08.value = 0x0;
        bport1_ab_data.CR07.value = 0x0;
        bport1_ab_data.CR06.value = 0x0;
        bport1_ab_data.CR05.value = 0x0;
        bport1_ab_data.CR04.value = 0x0;
        bport1_ab_data.CR03.value = 0x0;
        bport1_ab_data.CR02.value = 0x0;
        bport1_ab_data.CR01.value = 0x0;
        bport1_ab_data.CR00.value = 0x0;
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

