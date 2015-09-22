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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridI2C", "Example");
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

static PPM_WRITE_CB(bport1_ab_IBAD_maskWrite) {
    bport1_ab_data.IBAD.value = (bport1_ab_data.IBAD.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_IBCR_maskWrite) {
    bport1_ab_data.IBCR.value = (bport1_ab_data.IBCR.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_IBDBG_maskWrite) {
    bport1_ab_data.IBDBG.value = (bport1_ab_data.IBDBG.value & 0xfe) | (data & 0x1);
}

static PPM_WRITE_CB(bport1_ab_IBDR_maskWrite) {
    bport1_ab_data.IBDR.value = (bport1_ab_data.IBDR.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_IBFD_maskWrite) {
    bport1_ab_data.IBFD.value = (bport1_ab_data.IBFD.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_IBIC_maskWrite) {
    bport1_ab_data.IBIC.value = (bport1_ab_data.IBIC.value & 0x7f) | (data & 0x80);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_IBAD",
        "I2C Bus Address Register, offset: 0x0",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_IBAD_maskWrite,
        view8,
        &(bport1_ab_data.IBAD.value),
        True
    );
    ppmCreateRegister("ab_IBFD",
        "I2C Bus Frequency Divider Register, offset: 0x1",
        handles.bport1,
        1,
        1,
        read_8,
        bport1_ab_IBFD_maskWrite,
        view8,
        &(bport1_ab_data.IBFD.value),
        True
    );
    ppmCreateRegister("ab_IBCR",
        "I2C Bus Control Register, offset: 0x2",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_IBCR_maskWrite,
        view8,
        &(bport1_ab_data.IBCR.value),
        True
    );
    ppmCreateRegister("ab_IBSR",
        "I2C Bus Status Register, offset: 0x3",
        handles.bport1,
        3,
        1,
        read_8,
        BSRWrite1C,
        view8,
        &(bport1_ab_data.IBSR.value),
        True
    );
    ppmCreateRegister("ab_IBDR",
        "I2C Bus Data I/O Register, offset: 0x4",
        handles.bport1,
        4,
        1,
        read_8,
        bport1_ab_IBDR_maskWrite,
        view8,
        &(bport1_ab_data.IBDR.value),
        True
    );
    ppmCreateRegister("ab_IBIC",
        "I2C Bus Interrupt Config Register, offset: 0x5",
        handles.bport1,
        5,
        1,
        read_8,
        bport1_ab_IBIC_maskWrite,
        view8,
        &(bport1_ab_data.IBIC.value),
        True
    );
    ppmCreateRegister("ab_IBDBG",
        "I2C Bus Debug Register, offset: 0x6",
        handles.bport1,
        6,
        1,
        read_8,
        bport1_ab_IBDBG_maskWrite,
        view8,
        &(bport1_ab_data.IBDBG.value),
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
        bport1_ab_data.IBDBG.value = 0x0;
        bport1_ab_data.IBIC.value = 0x0;
        bport1_ab_data.IBDR.value = 0x0;
        bport1_ab_data.IBSR.value = 0x80;
        bport1_ab_data.IBCR.value = 0x80;
        bport1_ab_data.IBFD.value = 0x0;
        bport1_ab_data.IBAD.value = 0x0;
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

