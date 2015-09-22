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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisSPI", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CTAR0_maskWrite) {
    bport1_ab_data.CTAR0.value = (bport1_ab_data.CTAR0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_CTAR1_maskWrite) {
    bport1_ab_data.CTAR1.value = (bport1_ab_data.CTAR1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & 0xc000fe) | (data & 0xff3fff01);
}

static PPM_WRITE_CB(bport1_ab_PUSHR_maskWrite) {
    bport1_ab_data.PUSHR.value = (bport1_ab_data.PUSHR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RSER_maskWrite) {
    bport1_ab_data.RSER.value = (bport1_ab_data.RSER.value & 0x64f4ffff) | (data & 0x9b0b0000);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & 0x25f5ffff) | (data & 0xda0a0000);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & 0xffff) | (data & 0xffff0000);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_MCR",
        "DSPI Module Configuration Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_MCR_maskWrite,
        view32,
        &(bport1_ab_data.MCR.value),
        True
    );
    ppmCreateRegister("ab_TCR",
        "DSPI Transfer Count Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_TCR_maskWrite,
        view32,
        &(bport1_ab_data.TCR.value),
        True
    );
    ppmCreateRegister("ab_CTAR0",
        "DSPI Clock and Transfer Attributes Register 0, Master/Slave modes, offset 0x0c",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_CTAR0_maskWrite,
        view32,
        &(bport1_ab_data.CTAR0.value),
        True
    );
    ppmCreateRegister("ab_CTAR1",
        "DSPI Clock and Transfer Attributes Register 1, Master mode, offset 0x10",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_CTAR1_maskWrite,
        view32,
        &(bport1_ab_data.CTAR1.value),
        True
    );
    ppmCreateRegister("ab_SR",
        "DSPI Status Register, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_SR_maskWrite,
        view32,
        &(bport1_ab_data.SR.value),
        True
    );
    ppmCreateRegister("ab_RSER",
        "DSPI DMA/Interrupt Request Select and Enable Register, offset: 0x30 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_RSER_maskWrite,
        view32,
        &(bport1_ab_data.RSER.value),
        True
    );
    ppmCreateRegister("ab_PUSHR",
        "DSPI PUSH TX FIFO Register In Master Mode, offset: 0x34 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_PUSHR_maskWrite,
        view32,
        &(bport1_ab_data.PUSHR.value),
        True
    );
    ppmCreateRegister("ab_POPR",
        "DSPI POP RX FIFO Register, offset: 0x38 ",
        handles.bport1,
        56,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.POPR.value),
        True
    );
    ppmCreateRegister("ab_TXFR0",
        "DSPI Transmit FIFO Registers, offset: 0x3C ",
        handles.bport1,
        60,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TXFR0.value),
        True
    );
    ppmCreateRegister("ab_TXFR1",
        "DSPI Transmit FIFO Registers, offset: 0x40 ",
        handles.bport1,
        64,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TXFR1.value),
        True
    );
    ppmCreateRegister("ab_TXFR2",
        "DSPI Transmit FIFO Registers, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TXFR2.value),
        True
    );
    ppmCreateRegister("ab_TXFR3",
        "DSPI Transmit FIFO Registers, offset: 0x48 ",
        handles.bport1,
        72,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TXFR3.value),
        True
    );
    ppmCreateRegister("ab_RXFR0",
        "DSPI Receive FIFO Registers, offset: 0x7C ",
        handles.bport1,
        124,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RXFR0.value),
        True
    );
    ppmCreateRegister("ab_RXFR1",
        "DSPI Receive FIFO Registers, offset: 0x80 ",
        handles.bport1,
        128,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RXFR1.value),
        True
    );
    ppmCreateRegister("ab_RXFR2",
        "DSPI Receive FIFO Registers, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RXFR2.value),
        True
    );
    ppmCreateRegister("ab_RXFR3",
        "DSPI Receive FIFO Registers, offset: 0x88 ",
        handles.bport1,
        136,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RXFR3.value),
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
        bport1_ab_data.RXFR3.value = 0x0;
        bport1_ab_data.RXFR2.value = 0x0;
        bport1_ab_data.RXFR1.value = 0x0;
        bport1_ab_data.RXFR0.value = 0x0;
        bport1_ab_data.TXFR3.value = 0x0;
        bport1_ab_data.TXFR2.value = 0x0;
        bport1_ab_data.TXFR1.value = 0x0;
        bport1_ab_data.TXFR0.value = 0x0;
        bport1_ab_data.POPR.value = 0x0;
        bport1_ab_data.PUSHR.value = 0x0;
        bport1_ab_data.RSER.value = 0x0;
        bport1_ab_data.SR.value = 0x0;
        bport1_ab_data.CTAR1.value = 0x78000000;
        bport1_ab_data.CTAR0.value = 0x78000000;
        bport1_ab_data.TCR.value = 0x0;
        bport1_ab_data.MCR.value = 0x4001;
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

