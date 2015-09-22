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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFTFE", "Example");
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

static PPM_WRITE_CB(bport1_ab_FCCOB0_maskWrite) {
    bport1_ab_data.FCCOB0.value = (bport1_ab_data.FCCOB0.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB1_maskWrite) {
    bport1_ab_data.FCCOB1.value = (bport1_ab_data.FCCOB1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB2_maskWrite) {
    bport1_ab_data.FCCOB2.value = (bport1_ab_data.FCCOB2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB3_maskWrite) {
    bport1_ab_data.FCCOB3.value = (bport1_ab_data.FCCOB3.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB4_maskWrite) {
    bport1_ab_data.FCCOB4.value = (bport1_ab_data.FCCOB4.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB5_maskWrite) {
    bport1_ab_data.FCCOB5.value = (bport1_ab_data.FCCOB5.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB6_maskWrite) {
    bport1_ab_data.FCCOB6.value = (bport1_ab_data.FCCOB6.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB7_maskWrite) {
    bport1_ab_data.FCCOB7.value = (bport1_ab_data.FCCOB7.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB8_maskWrite) {
    bport1_ab_data.FCCOB8.value = (bport1_ab_data.FCCOB8.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOB9_maskWrite) {
    bport1_ab_data.FCCOB9.value = (bport1_ab_data.FCCOB9.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOBA_maskWrite) {
    bport1_ab_data.FCCOBA.value = (bport1_ab_data.FCCOBA.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCCOBB_maskWrite) {
    bport1_ab_data.FCCOBB.value = (bport1_ab_data.FCCOBB.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FCNFG_maskWrite) {
    bport1_ab_data.FCNFG.value = (bport1_ab_data.FCNFG.value & 0x2f) | (data & 0xd0);
}

static PPM_WRITE_CB(bport1_ab_FDPROT_maskWrite) {
    bport1_ab_data.FDPROT.value = (bport1_ab_data.FDPROT.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FEPROT_maskWrite) {
    bport1_ab_data.FEPROT.value = (bport1_ab_data.FEPROT.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FPROT0_maskWrite) {
    bport1_ab_data.FPROT0.value = (bport1_ab_data.FPROT0.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FPROT1_maskWrite) {
    bport1_ab_data.FPROT1.value = (bport1_ab_data.FPROT1.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FPROT2_maskWrite) {
    bport1_ab_data.FPROT2.value = (bport1_ab_data.FPROT2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FPROT3_maskWrite) {
    bport1_ab_data.FPROT3.value = (bport1_ab_data.FPROT3.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FSTAT_maskWrite) {
    bport1_ab_data.FSTAT.value = (bport1_ab_data.FSTAT.value & 0xf) | (data & 0xf0);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_FSTAT",
        "Flash Status Register, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_FSTAT_maskWrite,
        view8,
        &(bport1_ab_data.FSTAT.value),
        True
    );
    ppmCreateRegister("ab_FCNFG",
        "Flash Configuration Register, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_FCNFG_maskWrite,
        view8,
        &(bport1_ab_data.FCNFG.value),
        True
    );
    ppmCreateRegister("ab_FSEC",
        "Flash Security Register, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.FSEC.value),
        True
    );
    ppmCreateRegister("ab_FOPT",
        "Flash Option Register, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.FOPT.value),
        True
    );
    ppmCreateRegister("ab_FCCOB3",
        "Flash Common Command Object Registers, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_FCCOB3_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB3.value),
        True
    );
    ppmCreateRegister("ab_FCCOB2",
        "Flash Common Command Object Registers, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_FCCOB2_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB2.value),
        True
    );
    ppmCreateRegister("ab_FCCOB1",
        "Flash Common Command Object Registers, offset: 0x6 ",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_FCCOB1_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB1.value),
        True
    );
    ppmCreateRegister("ab_FCCOB0",
        "Flash Common Command Object Registers, offset: 0x7 ",
        handles.bport1,
        7,
        1,
        read_8,
        bport1_ab_FCCOB0_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB0.value),
        True
    );
    ppmCreateRegister("ab_FCCOB7",
        "Flash Common Command Object Registers, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        bport1_ab_FCCOB7_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB7.value),
        True
    );
    ppmCreateRegister("ab_FCCOB6",
        "Flash Common Command Object Registers, offset: 0x9 ",
        handles.bport1,
        9,
        1,
        read_8,
        bport1_ab_FCCOB6_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB6.value),
        True
    );
    ppmCreateRegister("ab_FCCOB5",
        "Flash Common Command Object Registers, offset: 0xA ",
        handles.bport1,
        10,
        1,
        read_8,
        bport1_ab_FCCOB5_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB5.value),
        True
    );
    ppmCreateRegister("ab_FCCOB4",
        "Flash Common Command Object Registers, offset: 0xB ",
        handles.bport1,
        11,
        1,
        read_8,
        bport1_ab_FCCOB4_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB4.value),
        True
    );
    ppmCreateRegister("ab_FCCOBB",
        "Flash Common Command Object Registers, offset: 0xC ",
        handles.bport1,
        12,
        1,
        read_8,
        bport1_ab_FCCOBB_maskWrite,
        view8,
        &(bport1_ab_data.FCCOBB.value),
        True
    );
    ppmCreateRegister("ab_FCCOBA",
        "Flash Common Command Object Registers, offset: 0xD ",
        handles.bport1,
        13,
        1,
        read_8,
        bport1_ab_FCCOBA_maskWrite,
        view8,
        &(bport1_ab_data.FCCOBA.value),
        True
    );
    ppmCreateRegister("ab_FCCOB9",
        "Flash Common Command Object Registers, offset: 0xE ",
        handles.bport1,
        14,
        1,
        read_8,
        bport1_ab_FCCOB9_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB9.value),
        True
    );
    ppmCreateRegister("ab_FCCOB8",
        "Flash Common Command Object Registers, offset: 0xF ",
        handles.bport1,
        15,
        1,
        read_8,
        bport1_ab_FCCOB8_maskWrite,
        view8,
        &(bport1_ab_data.FCCOB8.value),
        True
    );
    ppmCreateRegister("ab_FPROT3",
        "Program Flash Protection Registers, offset: 0x10 ",
        handles.bport1,
        16,
        1,
        read_8,
        bport1_ab_FPROT3_maskWrite,
        view8,
        &(bport1_ab_data.FPROT3.value),
        True
    );
    ppmCreateRegister("ab_FPROT2",
        "Program Flash Protection Registers, offset: 0x11 ",
        handles.bport1,
        17,
        1,
        read_8,
        bport1_ab_FPROT2_maskWrite,
        view8,
        &(bport1_ab_data.FPROT2.value),
        True
    );
    ppmCreateRegister("ab_FPROT1",
        "Program Flash Protection Registers, offset: 0x12 ",
        handles.bport1,
        18,
        1,
        read_8,
        bport1_ab_FPROT1_maskWrite,
        view8,
        &(bport1_ab_data.FPROT1.value),
        True
    );
    ppmCreateRegister("ab_FPROT0",
        "Program Flash Protection Registers, offset: 0x13 ",
        handles.bport1,
        19,
        1,
        read_8,
        bport1_ab_FPROT0_maskWrite,
        view8,
        &(bport1_ab_data.FPROT0.value),
        True
    );
    ppmCreateRegister("ab_FEPROT",
        "EEPROM Protection Register, offset: 0x16 ",
        handles.bport1,
        22,
        1,
        read_8,
        bport1_ab_FEPROT_maskWrite,
        view8,
        &(bport1_ab_data.FEPROT.value),
        True
    );
    ppmCreateRegister("ab_FDPROT",
        "Data Flash Protection Register, offset: 0x17 ",
        handles.bport1,
        23,
        1,
        read_8,
        bport1_ab_FDPROT_maskWrite,
        view8,
        &(bport1_ab_data.FDPROT.value),
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
        bport1_ab_data.FCCOB8.value = 0x0;
        bport1_ab_data.FCCOB9.value = 0x0;
        bport1_ab_data.FCCOBA.value = 0x0;
        bport1_ab_data.FCCOBB.value = 0x0;
        bport1_ab_data.FCCOB4.value = 0x0;
        bport1_ab_data.FCCOB5.value = 0x0;
        bport1_ab_data.FCCOB6.value = 0x0;
        bport1_ab_data.FCCOB7.value = 0x0;
        bport1_ab_data.FCCOB0.value = 0x0;
        bport1_ab_data.FCCOB1.value = 0x0;
        bport1_ab_data.FCCOB2.value = 0x0;
        bport1_ab_data.FCCOB3.value = 0x0;
        bport1_ab_data.FCNFG.value = 0x0;
        bport1_ab_data.FSTAT.value = 0x0;
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

