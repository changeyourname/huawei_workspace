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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisDAC", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_C0_maskWrite) {
    bport1_ab_data.C0.value = (bport1_ab_data.C0.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & 0x60) | (data & 0x9f);
}

static PPM_WRITE_CB(bport1_ab_C2_maskWrite) {
    bport1_ab_data.C2.value = (bport1_ab_data.C2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT0H_maskWrite) {
    bport1_ab_data.DAT0H.value = (bport1_ab_data.DAT0H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT0L_maskWrite) {
    bport1_ab_data.DAT0L.value = (bport1_ab_data.DAT0L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT10H_maskWrite) {
    bport1_ab_data.DAT10H.value = (bport1_ab_data.DAT10H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT10L_maskWrite) {
    bport1_ab_data.DAT10L.value = (bport1_ab_data.DAT10L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT11H_maskWrite) {
    bport1_ab_data.DAT11H.value = (bport1_ab_data.DAT11H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT11L_maskWrite) {
    bport1_ab_data.DAT11L.value = (bport1_ab_data.DAT11L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT12H_maskWrite) {
    bport1_ab_data.DAT12H.value = (bport1_ab_data.DAT12H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT12L_maskWrite) {
    bport1_ab_data.DAT12L.value = (bport1_ab_data.DAT12L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT13H_maskWrite) {
    bport1_ab_data.DAT13H.value = (bport1_ab_data.DAT13H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT13L_maskWrite) {
    bport1_ab_data.DAT13L.value = (bport1_ab_data.DAT13L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT14H_maskWrite) {
    bport1_ab_data.DAT14H.value = (bport1_ab_data.DAT14H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT14L_maskWrite) {
    bport1_ab_data.DAT14L.value = (bport1_ab_data.DAT14L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT15H_maskWrite) {
    bport1_ab_data.DAT15H.value = (bport1_ab_data.DAT15H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT15L_maskWrite) {
    bport1_ab_data.DAT15L.value = (bport1_ab_data.DAT15L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT1H_maskWrite) {
    bport1_ab_data.DAT1H.value = (bport1_ab_data.DAT1H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT1L_maskWrite) {
    bport1_ab_data.DAT1L.value = (bport1_ab_data.DAT1L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT2H_maskWrite) {
    bport1_ab_data.DAT2H.value = (bport1_ab_data.DAT2H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT2L_maskWrite) {
    bport1_ab_data.DAT2L.value = (bport1_ab_data.DAT2L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT3H_maskWrite) {
    bport1_ab_data.DAT3H.value = (bport1_ab_data.DAT3H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT3L_maskWrite) {
    bport1_ab_data.DAT3L.value = (bport1_ab_data.DAT3L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT4H_maskWrite) {
    bport1_ab_data.DAT4H.value = (bport1_ab_data.DAT4H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT4L_maskWrite) {
    bport1_ab_data.DAT4L.value = (bport1_ab_data.DAT4L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT5H_maskWrite) {
    bport1_ab_data.DAT5H.value = (bport1_ab_data.DAT5H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT5L_maskWrite) {
    bport1_ab_data.DAT5L.value = (bport1_ab_data.DAT5L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT6H_maskWrite) {
    bport1_ab_data.DAT6H.value = (bport1_ab_data.DAT6H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT6L_maskWrite) {
    bport1_ab_data.DAT6L.value = (bport1_ab_data.DAT6L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT7H_maskWrite) {
    bport1_ab_data.DAT7H.value = (bport1_ab_data.DAT7H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT7L_maskWrite) {
    bport1_ab_data.DAT7L.value = (bport1_ab_data.DAT7L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT8H_maskWrite) {
    bport1_ab_data.DAT8H.value = (bport1_ab_data.DAT8H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT8L_maskWrite) {
    bport1_ab_data.DAT8L.value = (bport1_ab_data.DAT8L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_DAT9H_maskWrite) {
    bport1_ab_data.DAT9H.value = (bport1_ab_data.DAT9H.value & 0xf0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_DAT9L_maskWrite) {
    bport1_ab_data.DAT9L.value = (bport1_ab_data.DAT9L.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & 0xf8) | (data & 0x7);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_DAT0L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_DAT0L_maskWrite,
        view8,
        &(bport1_ab_data.DAT0L.value),
        True
    );
    ppmCreateRegister("ab_DAT0H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_DAT0H_maskWrite,
        view8,
        &(bport1_ab_data.DAT0H.value),
        True
    );
    ppmCreateRegister("ab_DAT1L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_DAT1L_maskWrite,
        view8,
        &(bport1_ab_data.DAT1L.value),
        True
    );
    ppmCreateRegister("ab_DAT1H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        3,
        1,
        read_8,
        bport1_ab_DAT1H_maskWrite,
        view8,
        &(bport1_ab_data.DAT1H.value),
        True
    );
    ppmCreateRegister("ab_DAT2L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_DAT2L_maskWrite,
        view8,
        &(bport1_ab_data.DAT2L.value),
        True
    );
    ppmCreateRegister("ab_DAT2H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_DAT2H_maskWrite,
        view8,
        &(bport1_ab_data.DAT2H.value),
        True
    );
    ppmCreateRegister("ab_DAT3L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_DAT3L_maskWrite,
        view8,
        &(bport1_ab_data.DAT3L.value),
        True
    );
    ppmCreateRegister("ab_DAT3H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        7,
        1,
        read_8,
        bport1_ab_DAT3H_maskWrite,
        view8,
        &(bport1_ab_data.DAT3H.value),
        True
    );
    ppmCreateRegister("ab_DAT4L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_DAT4L_maskWrite,
        view8,
        &(bport1_ab_data.DAT4L.value),
        True
    );
    ppmCreateRegister("ab_DAT4H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        9,
        1,
        read_8,
        bport1_ab_DAT4H_maskWrite,
        view8,
        &(bport1_ab_data.DAT4H.value),
        True
    );
    ppmCreateRegister("ab_DAT5L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        10,
        1,
        read_8,
        bport1_ab_DAT5L_maskWrite,
        view8,
        &(bport1_ab_data.DAT5L.value),
        True
    );
    ppmCreateRegister("ab_DAT5H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_DAT5H_maskWrite,
        view8,
        &(bport1_ab_data.DAT5H.value),
        True
    );
    ppmCreateRegister("ab_DAT6L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        12,
        1,
        read_8,
        bport1_ab_DAT6L_maskWrite,
        view8,
        &(bport1_ab_data.DAT6L.value),
        True
    );
    ppmCreateRegister("ab_DAT6H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        13,
        1,
        read_8,
        bport1_ab_DAT6H_maskWrite,
        view8,
        &(bport1_ab_data.DAT6H.value),
        True
    );
    ppmCreateRegister("ab_DAT7L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        14,
        1,
        read_8,
        bport1_ab_DAT7L_maskWrite,
        view8,
        &(bport1_ab_data.DAT7L.value),
        True
    );
    ppmCreateRegister("ab_DAT7H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        15,
        1,
        read_8,
        bport1_ab_DAT7H_maskWrite,
        view8,
        &(bport1_ab_data.DAT7H.value),
        True
    );
    ppmCreateRegister("ab_DAT8L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        16,
        1,
        read_8,
        bport1_ab_DAT8L_maskWrite,
        view8,
        &(bport1_ab_data.DAT8L.value),
        True
    );
    ppmCreateRegister("ab_DAT8H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        17,
        1,
        read_8,
        bport1_ab_DAT8H_maskWrite,
        view8,
        &(bport1_ab_data.DAT8H.value),
        True
    );
    ppmCreateRegister("ab_DAT9L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        18,
        1,
        read_8,
        bport1_ab_DAT9L_maskWrite,
        view8,
        &(bport1_ab_data.DAT9L.value),
        True
    );
    ppmCreateRegister("ab_DAT9H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        19,
        1,
        read_8,
        bport1_ab_DAT9H_maskWrite,
        view8,
        &(bport1_ab_data.DAT9H.value),
        True
    );
    ppmCreateRegister("ab_DAT10L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        20,
        1,
        read_8,
        bport1_ab_DAT10L_maskWrite,
        view8,
        &(bport1_ab_data.DAT10L.value),
        True
    );
    ppmCreateRegister("ab_DAT10H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        21,
        1,
        read_8,
        bport1_ab_DAT10H_maskWrite,
        view8,
        &(bport1_ab_data.DAT10H.value),
        True
    );
    ppmCreateRegister("ab_DAT11L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        22,
        1,
        read_8,
        bport1_ab_DAT11L_maskWrite,
        view8,
        &(bport1_ab_data.DAT11L.value),
        True
    );
    ppmCreateRegister("ab_DAT11H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        23,
        1,
        read_8,
        bport1_ab_DAT11H_maskWrite,
        view8,
        &(bport1_ab_data.DAT11H.value),
        True
    );
    ppmCreateRegister("ab_DAT12L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        24,
        1,
        read_8,
        bport1_ab_DAT12L_maskWrite,
        view8,
        &(bport1_ab_data.DAT12L.value),
        True
    );
    ppmCreateRegister("ab_DAT12H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        25,
        1,
        read_8,
        bport1_ab_DAT12H_maskWrite,
        view8,
        &(bport1_ab_data.DAT12H.value),
        True
    );
    ppmCreateRegister("ab_DAT13L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        26,
        1,
        read_8,
        bport1_ab_DAT13L_maskWrite,
        view8,
        &(bport1_ab_data.DAT13L.value),
        True
    );
    ppmCreateRegister("ab_DAT13H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        27,
        1,
        read_8,
        bport1_ab_DAT13H_maskWrite,
        view8,
        &(bport1_ab_data.DAT13H.value),
        True
    );
    ppmCreateRegister("ab_DAT14L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        28,
        1,
        read_8,
        bport1_ab_DAT14L_maskWrite,
        view8,
        &(bport1_ab_data.DAT14L.value),
        True
    );
    ppmCreateRegister("ab_DAT14H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        29,
        1,
        read_8,
        bport1_ab_DAT14H_maskWrite,
        view8,
        &(bport1_ab_data.DAT14H.value),
        True
    );
    ppmCreateRegister("ab_DAT15L",
        "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
        handles.bport1,
        30,
        1,
        read_8,
        bport1_ab_DAT15L_maskWrite,
        view8,
        &(bport1_ab_data.DAT15L.value),
        True
    );
    ppmCreateRegister("ab_DAT15H",
        "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
        handles.bport1,
        31,
        1,
        read_8,
        bport1_ab_DAT15H_maskWrite,
        view8,
        &(bport1_ab_data.DAT15H.value),
        True
    );
    ppmCreateRegister("ab_SR",
        "DAC Status Register, offset: 0x20 ",
        handles.bport1,
        32,
        1,
        read_8,
        bport1_ab_SR_maskWrite,
        view8,
        &(bport1_ab_data.SR.value),
        True
    );
    ppmCreateRegister("ab_C0",
        "DAC Control Register, offset: 0x21 ",
        handles.bport1,
        33,
        1,
        read_8,
        bport1_ab_C0_maskWrite,
        view8,
        &(bport1_ab_data.C0.value),
        True
    );
    ppmCreateRegister("ab_C1",
        "DAC Control Register 1, offset: 0x22 ",
        handles.bport1,
        34,
        1,
        read_8,
        bport1_ab_C1_maskWrite,
        view8,
        &(bport1_ab_data.C1.value),
        True
    );
    ppmCreateRegister("ab_C2",
        "DAC Control Register 2, offset: 0x23 ",
        handles.bport1,
        35,
        1,
        read_8,
        bport1_ab_C2_maskWrite,
        view8,
        &(bport1_ab_data.C2.value),
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
        bport1_ab_data.C2.value = 0xf;
        bport1_ab_data.C1.value = 0x0;
        bport1_ab_data.C0.value = 0x0;
        bport1_ab_data.SR.value = 0x2;
        bport1_ab_data.DAT15H.value = 0x0;
        bport1_ab_data.DAT15L.value = 0x0;
        bport1_ab_data.DAT14H.value = 0x0;
        bport1_ab_data.DAT14L.value = 0x0;
        bport1_ab_data.DAT13H.value = 0x0;
        bport1_ab_data.DAT13L.value = 0x0;
        bport1_ab_data.DAT12H.value = 0x0;
        bport1_ab_data.DAT12L.value = 0x0;
        bport1_ab_data.DAT11H.value = 0x0;
        bport1_ab_data.DAT11L.value = 0x0;
        bport1_ab_data.DAT10H.value = 0x0;
        bport1_ab_data.DAT10L.value = 0x0;
        bport1_ab_data.DAT9H.value = 0x0;
        bport1_ab_data.DAT9L.value = 0x0;
        bport1_ab_data.DAT8H.value = 0x0;
        bport1_ab_data.DAT8L.value = 0x0;
        bport1_ab_data.DAT7H.value = 0x0;
        bport1_ab_data.DAT7L.value = 0x0;
        bport1_ab_data.DAT6H.value = 0x0;
        bport1_ab_data.DAT6L.value = 0x0;
        bport1_ab_data.DAT5H.value = 0x0;
        bport1_ab_data.DAT5L.value = 0x0;
        bport1_ab_data.DAT4H.value = 0x0;
        bport1_ab_data.DAT4L.value = 0x0;
        bport1_ab_data.DAT3H.value = 0x0;
        bport1_ab_data.DAT3L.value = 0x0;
        bport1_ab_data.DAT2H.value = 0x0;
        bport1_ab_data.DAT2L.value = 0x0;
        bport1_ab_data.DAT1H.value = 0x0;
        bport1_ab_data.DAT1L.value = 0x0;
        bport1_ab_data.DAT0H.value = 0x0;
        bport1_ab_data.DAT0L.value = 0x0;
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

