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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCAN", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CTRL1_maskWrite) {
    bport1_ab_data.CTRL1.value = (bport1_ab_data.CTRL1.value & 0x300) | (data & 0xfffffcff);
}

static PPM_WRITE_CB(bport1_ab_CTRL2_maskWrite) {
    bport1_ab_data.CTRL2.value = (bport1_ab_data.CTRL2.value & 0xe000ffff) | (data & 0x1fff0000);
}

static PPM_WRITE_CB(bport1_ab_ECR_maskWrite) {
    bport1_ab_data.ECR.value = (bport1_ab_data.ECR.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_ESR1_maskWrite) {
    bport1_ab_data.ESR1.value = (bport1_ab_data.ESR1.value & 0xfffcfff8) | (data & 0x30007);
}

static PPM_WRITE_CB(bport1_ab_IFLAG1_maskWrite) {
    bport1_ab_data.IFLAG1.value = (bport1_ab_data.IFLAG1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_IFLAG2_maskWrite) {
    bport1_ab_data.IFLAG2.value = (bport1_ab_data.IFLAG2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_IMASK1_maskWrite) {
    bport1_ab_data.IMASK1.value = (bport1_ab_data.IMASK1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_IMASK2_maskWrite) {
    bport1_ab_data.IMASK2.value = (bport1_ab_data.IMASK2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & 0x918cc80) | (data & 0xf6e7337f);
}

static PPM_WRITE_CB(bport1_ab_RX14MASK_maskWrite) {
    bport1_ab_data.RX14MASK.value = (bport1_ab_data.RX14MASK.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RX15MASK_maskWrite) {
    bport1_ab_data.RX15MASK.value = (bport1_ab_data.RX15MASK.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXFGMASK_maskWrite) {
    bport1_ab_data.RXFGMASK.value = (bport1_ab_data.RXFGMASK.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR0_maskWrite) {
    bport1_ab_data.RXIMR0.value = (bport1_ab_data.RXIMR0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR10_maskWrite) {
    bport1_ab_data.RXIMR10.value = (bport1_ab_data.RXIMR10.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR11_maskWrite) {
    bport1_ab_data.RXIMR11.value = (bport1_ab_data.RXIMR11.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR12_maskWrite) {
    bport1_ab_data.RXIMR12.value = (bport1_ab_data.RXIMR12.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR13_maskWrite) {
    bport1_ab_data.RXIMR13.value = (bport1_ab_data.RXIMR13.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR14_maskWrite) {
    bport1_ab_data.RXIMR14.value = (bport1_ab_data.RXIMR14.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR15_maskWrite) {
    bport1_ab_data.RXIMR15.value = (bport1_ab_data.RXIMR15.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR1_maskWrite) {
    bport1_ab_data.RXIMR1.value = (bport1_ab_data.RXIMR1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR2_maskWrite) {
    bport1_ab_data.RXIMR2.value = (bport1_ab_data.RXIMR2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR3_maskWrite) {
    bport1_ab_data.RXIMR3.value = (bport1_ab_data.RXIMR3.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR4_maskWrite) {
    bport1_ab_data.RXIMR4.value = (bport1_ab_data.RXIMR4.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR5_maskWrite) {
    bport1_ab_data.RXIMR5.value = (bport1_ab_data.RXIMR5.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR6_maskWrite) {
    bport1_ab_data.RXIMR6.value = (bport1_ab_data.RXIMR6.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR7_maskWrite) {
    bport1_ab_data.RXIMR7.value = (bport1_ab_data.RXIMR7.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR8_maskWrite) {
    bport1_ab_data.RXIMR8.value = (bport1_ab_data.RXIMR8.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXIMR9_maskWrite) {
    bport1_ab_data.RXIMR9.value = (bport1_ab_data.RXIMR9.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RXMGMASK_maskWrite) {
    bport1_ab_data.RXMGMASK.value = (bport1_ab_data.RXMGMASK.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TIMER_maskWrite) {
    bport1_ab_data.TIMER.value = (bport1_ab_data.TIMER.value & 0xffff0000) | (data & 0xffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_MCR",
        "Module Configuration Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_MCR_maskWrite,
        view32,
        &(bport1_ab_data.MCR.value),
        True
    );
    ppmCreateRegister("ab_CTRL1",
        "Control 1 Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_CTRL1_maskWrite,
        view32,
        &(bport1_ab_data.CTRL1.value),
        True
    );
    ppmCreateRegister("ab_TIMER",
        "Free Running Timer, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_TIMER_maskWrite,
        view32,
        &(bport1_ab_data.TIMER.value),
        True
    );
    ppmCreateRegister("ab_RXMGMASK",
        "Rx Mailboxes Global Mask Register, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_RXMGMASK_maskWrite,
        view32,
        &(bport1_ab_data.RXMGMASK.value),
        True
    );
    ppmCreateRegister("ab_RX14MASK",
        "Rx 14 Mask Register, offset: 0x14 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_RX14MASK_maskWrite,
        view32,
        &(bport1_ab_data.RX14MASK.value),
        True
    );
    ppmCreateRegister("ab_RX15MASK",
        "Rx 15 Mask Register, offset: 0x18 ",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_RX15MASK_maskWrite,
        view32,
        &(bport1_ab_data.RX15MASK.value),
        True
    );
    ppmCreateRegister("ab_ECR",
        "Error Counter, offset: 0x1C ",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_ECR_maskWrite,
        view32,
        &(bport1_ab_data.ECR.value),
        True
    );
    ppmCreateRegister("ab_ESR1",
        "Error and Status 1 Register, offset: 0x20 ",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_ESR1_maskWrite,
        view32,
        &(bport1_ab_data.ESR1.value),
        True
    );
    ppmCreateRegister("ab_IMASK2",
        "Interrupt Masks 2 Register, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_IMASK2_maskWrite,
        view32,
        &(bport1_ab_data.IMASK2.value),
        True
    );
    ppmCreateRegister("ab_IMASK1",
        "Interrupt Masks 1 Register, offset: 0x28 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_IMASK1_maskWrite,
        view32,
        &(bport1_ab_data.IMASK1.value),
        True
    );
    ppmCreateRegister("ab_IFLAG2",
        "Interrupt Flags 2 Register, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_IFLAG2_maskWrite,
        view32,
        &(bport1_ab_data.IFLAG2.value),
        True
    );
    ppmCreateRegister("ab_IFLAG1",
        "Interrupt Flags 1 Register, offset: 0x30 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_IFLAG1_maskWrite,
        view32,
        &(bport1_ab_data.IFLAG1.value),
        True
    );
    ppmCreateRegister("ab_CTRL2",
        "Control 2 Register, offset: 0x34 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_CTRL2_maskWrite,
        view32,
        &(bport1_ab_data.CTRL2.value),
        True
    );
    ppmCreateRegister("ab_ESR2",
        "Error and Status 2 Register, offset: 0x38 ",
        handles.bport1,
        56,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.ESR2.value),
        True
    );
    ppmCreateRegister("ab_CRCR",
        "CRC Register, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CRCR.value),
        True
    );
    ppmCreateRegister("ab_RXFGMASK",
        "Rx FIFO Global Mask Register, offset: 0x48 ",
        handles.bport1,
        72,
        4,
        read_32,
        bport1_ab_RXFGMASK_maskWrite,
        view32,
        &(bport1_ab_data.RXFGMASK.value),
        True
    );
    ppmCreateRegister("ab_RXFIR",
        "Rx FIFO Information Register, offset: 0x4C ",
        handles.bport1,
        76,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RXFIR.value),
        True
    );
    ppmCreateRegister("ab_RXIMR0",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2176,
        4,
        read_32,
        bport1_ab_RXIMR0_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR0.value),
        True
    );
    ppmCreateRegister("ab_RXIMR1",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2180,
        4,
        read_32,
        bport1_ab_RXIMR1_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR1.value),
        True
    );
    ppmCreateRegister("ab_RXIMR2",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2184,
        4,
        read_32,
        bport1_ab_RXIMR2_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR2.value),
        True
    );
    ppmCreateRegister("ab_RXIMR3",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2188,
        4,
        read_32,
        bport1_ab_RXIMR3_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR3.value),
        True
    );
    ppmCreateRegister("ab_RXIMR4",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2192,
        4,
        read_32,
        bport1_ab_RXIMR4_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR4.value),
        True
    );
    ppmCreateRegister("ab_RXIMR5",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2196,
        4,
        read_32,
        bport1_ab_RXIMR5_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR5.value),
        True
    );
    ppmCreateRegister("ab_RXIMR6",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2200,
        4,
        read_32,
        bport1_ab_RXIMR6_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR6.value),
        True
    );
    ppmCreateRegister("ab_RXIMR7",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2204,
        4,
        read_32,
        bport1_ab_RXIMR7_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR7.value),
        True
    );
    ppmCreateRegister("ab_RXIMR8",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2208,
        4,
        read_32,
        bport1_ab_RXIMR8_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR8.value),
        True
    );
    ppmCreateRegister("ab_RXIMR9",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2212,
        4,
        read_32,
        bport1_ab_RXIMR9_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR9.value),
        True
    );
    ppmCreateRegister("ab_RXIMR10",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2216,
        4,
        read_32,
        bport1_ab_RXIMR10_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR10.value),
        True
    );
    ppmCreateRegister("ab_RXIMR11",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2220,
        4,
        read_32,
        bport1_ab_RXIMR11_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR11.value),
        True
    );
    ppmCreateRegister("ab_RXIMR12",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2224,
        4,
        read_32,
        bport1_ab_RXIMR12_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR12.value),
        True
    );
    ppmCreateRegister("ab_RXIMR13",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2228,
        4,
        read_32,
        bport1_ab_RXIMR13_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR13.value),
        True
    );
    ppmCreateRegister("ab_RXIMR14",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2232,
        4,
        read_32,
        bport1_ab_RXIMR14_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR14.value),
        True
    );
    ppmCreateRegister("ab_RXIMR15",
        "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
        handles.bport1,
        2236,
        4,
        read_32,
        bport1_ab_RXIMR15_maskWrite,
        view32,
        &(bport1_ab_data.RXIMR15.value),
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
        bport1_ab_data.RXFGMASK.value = 0xffffffff;
        bport1_ab_data.CRCR.value = 0x0;
        bport1_ab_data.ESR2.value = 0x0;
        bport1_ab_data.CTRL2.value = 0xb00000;
        bport1_ab_data.IFLAG1.value = 0x0;
        bport1_ab_data.IFLAG2.value = 0x0;
        bport1_ab_data.IMASK1.value = 0x0;
        bport1_ab_data.IMASK2.value = 0x0;
        bport1_ab_data.ESR1.value = 0x0;
        bport1_ab_data.ECR.value = 0x0;
        bport1_ab_data.RX15MASK.value = 0xffffffff;
        bport1_ab_data.RX14MASK.value = 0xffffffff;
        bport1_ab_data.RXMGMASK.value = 0xffffffff;
        bport1_ab_data.TIMER.value = 0x0;
        bport1_ab_data.CTRL1.value = 0x0;
        bport1_ab_data.MCR.value = 0xd890000f;
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

