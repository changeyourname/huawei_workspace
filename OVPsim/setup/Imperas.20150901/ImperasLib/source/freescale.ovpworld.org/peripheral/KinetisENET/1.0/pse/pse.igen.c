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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisENET", "Example");
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

static PPM_WRITE_CB(bport1_ab_ATCOR_maskWrite) {
    bport1_ab_data.ATCOR.value = (bport1_ab_data.ATCOR.value & 0x80000000) | (data & 0x7fffffff);
}

static PPM_WRITE_CB(bport1_ab_ATCR_maskWrite) {
    bport1_ab_data.ATCR.value = (bport1_ab_data.ATCR.value & 0xffffd562) | (data & 0x2a9d);
}

static PPM_WRITE_CB(bport1_ab_ATINC_maskWrite) {
    bport1_ab_data.ATINC.value = (bport1_ab_data.ATINC.value & 0xffff8180) | (data & 0x7e7f);
}

static PPM_WRITE_CB(bport1_ab_ATOFF_maskWrite) {
    bport1_ab_data.ATOFF.value = (bport1_ab_data.ATOFF.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_ATPER_maskWrite) {
    bport1_ab_data.ATPER.value = (bport1_ab_data.ATPER.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_ATSTMP_maskWrite) {
    bport1_ab_data.ATSTMP.value = (bport1_ab_data.ATSTMP.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_ATVR_maskWrite) {
    bport1_ab_data.ATVR.value = (bport1_ab_data.ATVR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_ECR_maskWrite) {
    bport1_ab_data.ECR.value = (bport1_ab_data.ECR.value & 0xfffffe20) | (data & 0x1df);
}

static PPM_WRITE_CB(bport1_ab_EIMR_maskWrite) {
    bport1_ab_data.EIMR.value = (bport1_ab_data.EIMR.value & 0x80007fff) | (data & 0x7fff8000);
}

static PPM_WRITE_CB(bport1_ab_EIR_maskWrite) {
    bport1_ab_data.EIR.value = (bport1_ab_data.EIR.value & 0x80007fff) | (data & 0x7fff8000);
}

static PPM_WRITE_CB(bport1_ab_FTRL_maskWrite) {
    bport1_ab_data.FTRL.value = (bport1_ab_data.FTRL.value & 0xffffc000) | (data & 0x3fff);
}

static PPM_WRITE_CB(bport1_ab_GALR_maskWrite) {
    bport1_ab_data.GALR.value = (bport1_ab_data.GALR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_GAUR_maskWrite) {
    bport1_ab_data.GAUR.value = (bport1_ab_data.GAUR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_IALR_maskWrite) {
    bport1_ab_data.IALR.value = (bport1_ab_data.IALR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_IAUR_maskWrite) {
    bport1_ab_data.IAUR.value = (bport1_ab_data.IAUR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MIBC_maskWrite) {
    bport1_ab_data.MIBC.value = (bport1_ab_data.MIBC.value & 0x5fffffff) | (data & 0xa0000000);
}

static PPM_WRITE_CB(bport1_ab_MMFR_maskWrite) {
    bport1_ab_data.MMFR.value = (bport1_ab_data.MMFR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MRBR_maskWrite) {
    bport1_ab_data.MRBR.value = (bport1_ab_data.MRBR.value & 0xffffc00f) | (data & 0x3ff0);
}

static PPM_WRITE_CB(bport1_ab_MSCR_maskWrite) {
    bport1_ab_data.MSCR.value = (bport1_ab_data.MSCR.value & 0xfffff801) | (data & 0x7fe);
}

static PPM_WRITE_CB(bport1_ab_OPD_maskWrite) {
    bport1_ab_data.OPD.value = (bport1_ab_data.OPD.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_PALR_maskWrite) {
    bport1_ab_data.PALR.value = (bport1_ab_data.PALR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_PAUR_maskWrite) {
    bport1_ab_data.PAUR.value = (bport1_ab_data.PAUR.value & 0xffff) | (data & 0xffff0000);
}

static PPM_WRITE_CB(bport1_ab_RACC_maskWrite) {
    bport1_ab_data.RACC.value = (bport1_ab_data.RACC.value & 0xffffff38) | (data & 0xc7);
}

static PPM_WRITE_CB(bport1_ab_RAEM_maskWrite) {
    bport1_ab_data.RAEM.value = (bport1_ab_data.RAEM.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_RAFL_maskWrite) {
    bport1_ab_data.RAFL.value = (bport1_ab_data.RAFL.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_RCR_maskWrite) {
    bport1_ab_data.RCR.value = (bport1_ab_data.RCR.value & 0xb8000cc0) | (data & 0x47fff33f);
}

static PPM_WRITE_CB(bport1_ab_RDAR_maskWrite) {
    bport1_ab_data.RDAR.value = (bport1_ab_data.RDAR.value & 0xfeffffff) | (data & 0x1000000);
}

static PPM_WRITE_CB(bport1_ab_RDSR_maskWrite) {
    bport1_ab_data.RDSR.value = (bport1_ab_data.RDSR.value & 0x7) | (data & 0xfffffff8);
}

static PPM_WRITE_CB(bport1_ab_RSEM_maskWrite) {
    bport1_ab_data.RSEM.value = (bport1_ab_data.RSEM.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_RSFL_maskWrite) {
    bport1_ab_data.RSFL.value = (bport1_ab_data.RSFL.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_TACC_maskWrite) {
    bport1_ab_data.TACC.value = (bport1_ab_data.TACC.value & 0xffffffe6) | (data & 0x19);
}

static PPM_WRITE_CB(bport1_ab_TAEM_maskWrite) {
    bport1_ab_data.TAEM.value = (bport1_ab_data.TAEM.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_TAFL_maskWrite) {
    bport1_ab_data.TAFL.value = (bport1_ab_data.TAFL.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_TCCR0_maskWrite) {
    bport1_ab_data.TCCR0.value = (bport1_ab_data.TCCR0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TCCR1_maskWrite) {
    bport1_ab_data.TCCR1.value = (bport1_ab_data.TCCR1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TCCR2_maskWrite) {
    bport1_ab_data.TCCR2.value = (bport1_ab_data.TCCR2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TCCR3_maskWrite) {
    bport1_ab_data.TCCR3.value = (bport1_ab_data.TCCR3.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & 0xfffffc12) | (data & 0x3ed);
}

static PPM_WRITE_CB(bport1_ab_TCSR0_maskWrite) {
    bport1_ab_data.TCSR0.value = (bport1_ab_data.TCSR0.value & 0xffffff02) | (data & 0xfd);
}

static PPM_WRITE_CB(bport1_ab_TCSR1_maskWrite) {
    bport1_ab_data.TCSR1.value = (bport1_ab_data.TCSR1.value & 0xffffff02) | (data & 0xfd);
}

static PPM_WRITE_CB(bport1_ab_TCSR2_maskWrite) {
    bport1_ab_data.TCSR2.value = (bport1_ab_data.TCSR2.value & 0xffffff02) | (data & 0xfd);
}

static PPM_WRITE_CB(bport1_ab_TCSR3_maskWrite) {
    bport1_ab_data.TCSR3.value = (bport1_ab_data.TCSR3.value & 0xffffff02) | (data & 0xfd);
}

static PPM_WRITE_CB(bport1_ab_TDAR_maskWrite) {
    bport1_ab_data.TDAR.value = (bport1_ab_data.TDAR.value & 0xfeffffff) | (data & 0x1000000);
}

static PPM_WRITE_CB(bport1_ab_TDSR_maskWrite) {
    bport1_ab_data.TDSR.value = (bport1_ab_data.TDSR.value & 0x7) | (data & 0xfffffff8);
}

static PPM_WRITE_CB(bport1_ab_TFWR_maskWrite) {
    bport1_ab_data.TFWR.value = (bport1_ab_data.TFWR.value & 0xfffffec0) | (data & 0x13f);
}

static PPM_WRITE_CB(bport1_ab_TGSR_maskWrite) {
    bport1_ab_data.TGSR.value = (bport1_ab_data.TGSR.value & 0xfffffff0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_TIPG_maskWrite) {
    bport1_ab_data.TIPG.value = (bport1_ab_data.TIPG.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_TSEM_maskWrite) {
    bport1_ab_data.TSEM.value = (bport1_ab_data.TSEM.value & 0xffffff00) | (data & 0xff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_EIR",
        "Interrupt Event Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_EIR_maskWrite,
        view32,
        &(bport1_ab_data.EIR.value),
        True
    );
    ppmCreateRegister("ab_EIMR",
        "Interrupt Mask Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_EIMR_maskWrite,
        view32,
        &(bport1_ab_data.EIMR.value),
        True
    );
    ppmCreateRegister("ab_RDAR",
        "Receive Descriptor Active Register, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_RDAR_maskWrite,
        view32,
        &(bport1_ab_data.RDAR.value),
        True
    );
    ppmCreateRegister("ab_TDAR",
        "Transmit Descriptor Active Register, offset: 0x14 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_TDAR_maskWrite,
        view32,
        &(bport1_ab_data.TDAR.value),
        True
    );
    ppmCreateRegister("ab_ECR",
        "Ethernet Control Register, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_ECR_maskWrite,
        view32,
        &(bport1_ab_data.ECR.value),
        True
    );
    ppmCreateRegister("ab_MMFR",
        "MII Management Frame Register, offset: 0x40 ",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_MMFR_maskWrite,
        view32,
        &(bport1_ab_data.MMFR.value),
        True
    );
    ppmCreateRegister("ab_MSCR",
        "MII Speed Control Register, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_MSCR_maskWrite,
        view32,
        &(bport1_ab_data.MSCR.value),
        True
    );
    ppmCreateRegister("ab_MIBC",
        "MIB Control Register, offset: 0x64 ",
        handles.bport1,
        100,
        4,
        read_32,
        bport1_ab_MIBC_maskWrite,
        view32,
        &(bport1_ab_data.MIBC.value),
        True
    );
    ppmCreateRegister("ab_RCR",
        "Receive Control Register, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        read_32,
        bport1_ab_RCR_maskWrite,
        view32,
        &(bport1_ab_data.RCR.value),
        True
    );
    ppmCreateRegister("ab_TCR",
        "Transmit Control Register, offset: 0xC4 ",
        handles.bport1,
        196,
        4,
        read_32,
        bport1_ab_TCR_maskWrite,
        view32,
        &(bport1_ab_data.TCR.value),
        True
    );
    ppmCreateRegister("ab_PALR",
        "Physical Address Lower Register, offset: 0xE4 ",
        handles.bport1,
        228,
        4,
        read_32,
        bport1_ab_PALR_maskWrite,
        view32,
        &(bport1_ab_data.PALR.value),
        True
    );
    ppmCreateRegister("ab_PAUR",
        "Physical Address Upper Register, offset: 0xE8 ",
        handles.bport1,
        232,
        4,
        read_32,
        bport1_ab_PAUR_maskWrite,
        view32,
        &(bport1_ab_data.PAUR.value),
        True
    );
    ppmCreateRegister("ab_OPD",
        "Opcode/Pause Duration Register, offset: 0xEC ",
        handles.bport1,
        236,
        4,
        read_32,
        bport1_ab_OPD_maskWrite,
        view32,
        &(bport1_ab_data.OPD.value),
        True
    );
    ppmCreateRegister("ab_IAUR",
        "Descriptor Individual Upper Address Register, offset: 0x118 ",
        handles.bport1,
        280,
        4,
        read_32,
        bport1_ab_IAUR_maskWrite,
        view32,
        &(bport1_ab_data.IAUR.value),
        True
    );
    ppmCreateRegister("ab_IALR",
        "Descriptor Individual Lower Address Register, offset: 0x11C ",
        handles.bport1,
        284,
        4,
        read_32,
        bport1_ab_IALR_maskWrite,
        view32,
        &(bport1_ab_data.IALR.value),
        True
    );
    ppmCreateRegister("ab_GAUR",
        "Descriptor Group Upper Address Register, offset: 0x120 ",
        handles.bport1,
        288,
        4,
        read_32,
        bport1_ab_GAUR_maskWrite,
        view32,
        &(bport1_ab_data.GAUR.value),
        True
    );
    ppmCreateRegister("ab_GALR",
        "Descriptor Group Lower Address Register, offset: 0x124 ",
        handles.bport1,
        292,
        4,
        read_32,
        bport1_ab_GALR_maskWrite,
        view32,
        &(bport1_ab_data.GALR.value),
        True
    );
    ppmCreateRegister("ab_TFWR",
        "Transmit FIFO Watermark Register, offset: 0x144 ",
        handles.bport1,
        324,
        4,
        read_32,
        bport1_ab_TFWR_maskWrite,
        view32,
        &(bport1_ab_data.TFWR.value),
        True
    );
    ppmCreateRegister("ab_RDSR",
        "Receive Descriptor Ring Start Register, offset: 0x180 ",
        handles.bport1,
        384,
        4,
        read_32,
        bport1_ab_RDSR_maskWrite,
        view32,
        &(bport1_ab_data.RDSR.value),
        True
    );
    ppmCreateRegister("ab_TDSR",
        "Transmit Buffer Descriptor Ring Start Register, offset: 0x184 ",
        handles.bport1,
        388,
        4,
        read_32,
        bport1_ab_TDSR_maskWrite,
        view32,
        &(bport1_ab_data.TDSR.value),
        True
    );
    ppmCreateRegister("ab_MRBR",
        "Maximum Receive Buffer Size Register, offset: 0x188 ",
        handles.bport1,
        392,
        4,
        read_32,
        bport1_ab_MRBR_maskWrite,
        view32,
        &(bport1_ab_data.MRBR.value),
        True
    );
    ppmCreateRegister("ab_RSFL",
        "Receive FIFO Section Full Threshold, offset: 0x190 ",
        handles.bport1,
        400,
        4,
        read_32,
        bport1_ab_RSFL_maskWrite,
        view32,
        &(bport1_ab_data.RSFL.value),
        True
    );
    ppmCreateRegister("ab_RSEM",
        "Receive FIFO Section Empty Threshold, offset: 0x194 ",
        handles.bport1,
        404,
        4,
        read_32,
        bport1_ab_RSEM_maskWrite,
        view32,
        &(bport1_ab_data.RSEM.value),
        True
    );
    ppmCreateRegister("ab_RAEM",
        "Receive FIFO Almost Empty Threshold, offset: 0x198 ",
        handles.bport1,
        408,
        4,
        read_32,
        bport1_ab_RAEM_maskWrite,
        view32,
        &(bport1_ab_data.RAEM.value),
        True
    );
    ppmCreateRegister("ab_RAFL",
        "Receive FIFO Almost Full Threshold, offset: 0x19C ",
        handles.bport1,
        412,
        4,
        read_32,
        bport1_ab_RAFL_maskWrite,
        view32,
        &(bport1_ab_data.RAFL.value),
        True
    );
    ppmCreateRegister("ab_TSEM",
        "Transmit FIFO Section Empty Threshold, offset: 0x1A0 ",
        handles.bport1,
        416,
        4,
        read_32,
        bport1_ab_TSEM_maskWrite,
        view32,
        &(bport1_ab_data.TSEM.value),
        True
    );
    ppmCreateRegister("ab_TAEM",
        "Transmit FIFO Almost Empty Threshold, offset: 0x1A4 ",
        handles.bport1,
        420,
        4,
        read_32,
        bport1_ab_TAEM_maskWrite,
        view32,
        &(bport1_ab_data.TAEM.value),
        True
    );
    ppmCreateRegister("ab_TAFL",
        "Transmit FIFO Almost Full Threshold, offset: 0x1A8 ",
        handles.bport1,
        424,
        4,
        read_32,
        bport1_ab_TAFL_maskWrite,
        view32,
        &(bport1_ab_data.TAFL.value),
        True
    );
    ppmCreateRegister("ab_TIPG",
        "Transmit Inter-Packet Gap, offset: 0x1AC ",
        handles.bport1,
        428,
        4,
        read_32,
        bport1_ab_TIPG_maskWrite,
        view32,
        &(bport1_ab_data.TIPG.value),
        True
    );
    ppmCreateRegister("ab_FTRL",
        "Frame Truncation Length, offset: 0x1B0 ",
        handles.bport1,
        432,
        4,
        read_32,
        bport1_ab_FTRL_maskWrite,
        view32,
        &(bport1_ab_data.FTRL.value),
        True
    );
    ppmCreateRegister("ab_TACC",
        "Transmit Accelerator Function Configuration, offset: 0x1C0 ",
        handles.bport1,
        448,
        4,
        read_32,
        bport1_ab_TACC_maskWrite,
        view32,
        &(bport1_ab_data.TACC.value),
        True
    );
    ppmCreateRegister("ab_RACC",
        "Receive Accelerator Function Configuration, offset: 0x1C4 ",
        handles.bport1,
        452,
        4,
        read_32,
        bport1_ab_RACC_maskWrite,
        view32,
        &(bport1_ab_data.RACC.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_DROP",
        "Count of frames not counted correctly (RMON_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x200 ",
        handles.bport1,
        512,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_DROP.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_PACKETS",
        "RMON Tx packet count (RMON_T_PACKETS), offset: 0x204 ",
        handles.bport1,
        516,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_PACKETS.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_BC_PKT",
        "RMON Tx Broadcast Packets (RMON_T_BC_PKT), offset: 0x208 ",
        handles.bport1,
        520,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_BC_PKT.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_MC_PKT",
        "RMON Tx Multicast Packets (RMON_T_MC_PKT), offset: 0x20C ",
        handles.bport1,
        524,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_MC_PKT.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_CRC_ALIGN",
        "RMON Tx Packets w CRC/Align error (RMON_T_CRC_ALIGN), offset: 0x210 ",
        handles.bport1,
        528,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_CRC_ALIGN.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_UNDERSIZE",
        "RMON Tx Packets < 64 bytes, good CRC (RMON_T_UNDERSIZE), offset: 0x214 ",
        handles.bport1,
        532,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_UNDERSIZE.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_OVERSIZE",
        "RMON Tx Packets > MAX_FL bytes, good CRC (RMON_T_OVERSIZE), offset: 0x218 ",
        handles.bport1,
        536,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_OVERSIZE.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_FRAG",
        "RMON Tx Packets < 64 bytes, bad CRC (RMON_T_FRAG), offset: 0x21C ",
        handles.bport1,
        540,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_FRAG.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_JAB",
        "RMON Tx Packets > MAX_FL bytes, bad CRC (RMON_T_JAB), offset: 0x220 ",
        handles.bport1,
        544,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_JAB.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_COL",
        "RMON Tx collision count (RMON_T_COL), offset: 0x224 ",
        handles.bport1,
        548,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_COL.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P64",
        "RMON Tx 64 byte packets (RMON_T_P64), offset: 0x228 ",
        handles.bport1,
        552,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P64.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P65TO127",
        "RMON Tx 65 to 127 byte packets (RMON_T_P65TO127), offset: 0x22C ",
        handles.bport1,
        556,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P65TO127.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P128TO255",
        "RMON Tx 128 to 255 byte packets (RMON_T_P128TO255), offset: 0x230 ",
        handles.bport1,
        560,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P128TO255.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P256TO511",
        "RMON Tx 256 to 511 byte packets (RMON_T_P256TO511), offset: 0x234 ",
        handles.bport1,
        564,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P256TO511.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P512TO1023",
        "RMON Tx 512 to 1023 byte packets (RMON_T_P512TO1023), offset: 0x238 ",
        handles.bport1,
        568,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P512TO1023.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P1024TO2047",
        "RMON Tx 1024 to 2047 byte packets (RMON_T_P1024TO2047), offset: 0x23C ",
        handles.bport1,
        572,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P1024TO2047.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_P_GTE2048",
        "RMON Tx packets w > 2048 bytes (RMON_T_P_GTE2048), offset: 0x240 ",
        handles.bport1,
        576,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_P_GTE2048.value),
        True
    );
    ppmCreateRegister("ab_RMON_T_OCTETS",
        "RMON Tx Octets (RMON_T_OCTETS), offset: 0x244 ",
        handles.bport1,
        580,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_T_OCTETS.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_DROP",
        "Count of frames not counted correctly (IEEE_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x248 ",
        handles.bport1,
        584,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_DROP.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_FRAME_OK",
        "Frames Transmitted OK (IEEE_T_FRAME_OK), offset: 0x24C ",
        handles.bport1,
        588,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_FRAME_OK.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_1COL",
        "Frames Transmitted with Single Collision (IEEE_T_1COL), offset: 0x250 ",
        handles.bport1,
        592,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_1COL.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_MCOL",
        "Frames Transmitted with Multiple Collisions (IEEE_T_MCOL), offset: 0x254 ",
        handles.bport1,
        596,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_MCOL.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_DEF",
        "Frames Transmitted after Deferral Delay (IEEE_T_DEF), offset: 0x258 ",
        handles.bport1,
        600,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_DEF.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_LCOL",
        "Frames Transmitted with Late Collision (IEEE_T_LCOL), offset: 0x25C ",
        handles.bport1,
        604,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_LCOL.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_EXCOL",
        "Frames Transmitted with Excessive Collisions (IEEE_T_EXCOL), offset: 0x260 ",
        handles.bport1,
        608,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_EXCOL.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_MACERR",
        "Frames Transmitted with Tx FIFO Underrun (IEEE_T_MACERR), offset: 0x264 ",
        handles.bport1,
        612,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_MACERR.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_CSERR",
        "Frames Transmitted with Carrier Sense Error (IEEE_T_CSERR), offset: 0x268 ",
        handles.bport1,
        616,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_CSERR.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_SQE",
        "Frames Transmitted with SQE Error (IEEE_T_SQE). NOTE: Counter not implemented (read 0 always) as no SQE information is available., offset: 0x26C ",
        handles.bport1,
        620,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_SQE.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_FDXFC",
        "Flow Control Pause frames transmitted (IEEE_T_FDXFC), offset: 0x270 ",
        handles.bport1,
        624,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_FDXFC.value),
        True
    );
    ppmCreateRegister("ab_IEEE_T_OCTETS_OK",
        "Octet count for Frames Transmitted w/o Error (IEEE_T_OCTETS_OK). NOTE: Counts total octets (includes header and FCS fields)., offset: 0x274 ",
        handles.bport1,
        628,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_T_OCTETS_OK.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_PACKETS",
        "RMON Rx packet count (RMON_R_PACKETS), offset: 0x284 ",
        handles.bport1,
        644,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_PACKETS.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_BC_PKT",
        "RMON Rx Broadcast Packets (RMON_R_BC_PKT), offset: 0x288 ",
        handles.bport1,
        648,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_BC_PKT.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_MC_PKT",
        "RMON Rx Multicast Packets (RMON_R_MC_PKT), offset: 0x28C ",
        handles.bport1,
        652,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_MC_PKT.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_CRC_ALIGN",
        "RMON Rx Packets w CRC/Align error (RMON_R_CRC_ALIGN), offset: 0x290 ",
        handles.bport1,
        656,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_CRC_ALIGN.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_UNDERSIZE",
        "RMON Rx Packets < 64 bytes, good CRC (RMON_R_UNDERSIZE), offset: 0x294 ",
        handles.bport1,
        660,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_UNDERSIZE.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_OVERSIZE",
        "RMON Rx Packets > MAX_FL bytes, good CRC (RMON_R_OVERSIZE), offset: 0x298 ",
        handles.bport1,
        664,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_OVERSIZE.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_FRAG",
        "RMON Rx Packets < 64 bytes, bad CRC (RMON_R_FRAG), offset: 0x29C ",
        handles.bport1,
        668,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_FRAG.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_JAB",
        "RMON Rx Packets > MAX_FL bytes, bad CRC (RMON_R_JAB), offset: 0x2A0 ",
        handles.bport1,
        672,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_JAB.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_RESVD_0",
        "Reserved (RMON_R_RESVD_0), offset: 0x2A4 ",
        handles.bport1,
        676,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_RESVD_0.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P64",
        "RMON Rx 64 byte packets (RMON_R_P64), offset: 0x2A8 ",
        handles.bport1,
        680,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P64.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P65TO127",
        "RMON Rx 65 to 127 byte packets (RMON_R_P65TO127), offset: 0x2AC ",
        handles.bport1,
        684,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P65TO127.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P128TO255",
        "RMON Rx 128 to 255 byte packets (RMON_R_P128TO255), offset: 0x2B0 ",
        handles.bport1,
        688,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P128TO255.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P256TO511",
        "RMON Rx 256 to 511 byte packets (RMON_R_P256TO511), offset: 0x2B4 ",
        handles.bport1,
        692,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P256TO511.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P512TO1023",
        "RMON Rx 512 to 1023 byte packets (RMON_R_P512TO1023), offset: 0x2B8 ",
        handles.bport1,
        696,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P512TO1023.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P1024TO2047",
        "RMON Rx 1024 to 2047 byte packets (RMON_R_P1024TO2047), offset: 0x2BC ",
        handles.bport1,
        700,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P1024TO2047.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_P_GTE2048",
        "RMON Rx packets w > 2048 bytes (RMON_R_P_GTE2048), offset: 0x2C0 ",
        handles.bport1,
        704,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_P_GTE2048.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_OCTETS",
        "RMON Rx Octets (RMON_R_OCTETS), offset: 0x2C4 ",
        handles.bport1,
        708,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_OCTETS.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_DROP",
        "Count of frames not counted correctly (IEEE_R_DROP). NOTE: Counter increments if a frame with valid/missing SFD character is detected and has been dropped. None of the other counters increments if this counter increments., offset: 0x2C8 ",
        handles.bport1,
        712,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_DROP.value),
        True
    );
    ppmCreateRegister("ab_RMON_R_FRAME_OK",
        "Frames Received OK (IEEE_R_FRAME_OK), offset: 0x2CC ",
        handles.bport1,
        716,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RMON_R_FRAME_OK.value),
        True
    );
    ppmCreateRegister("ab_IEEE_R_CRC",
        "Frames Received with CRC Error (IEEE_R_CRC), offset: 0x2D0 ",
        handles.bport1,
        720,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_R_CRC.value),
        True
    );
    ppmCreateRegister("ab_IEEE_R_ALIGN",
        "Frames Received with Alignment Error (IEEE_R_ALIGN), offset: 0x2D4 ",
        handles.bport1,
        724,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_R_ALIGN.value),
        True
    );
    ppmCreateRegister("ab_IEEE_R_MACERR",
        "Receive Fifo Overflow count (IEEE_R_MACERR), offset: 0x2D8 ",
        handles.bport1,
        728,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_R_MACERR.value),
        True
    );
    ppmCreateRegister("ab_IEEE_R_FDXFC",
        "Flow Control Pause frames received (IEEE_R_FDXFC), offset: 0x2DC ",
        handles.bport1,
        732,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_R_FDXFC.value),
        True
    );
    ppmCreateRegister("ab_IEEE_R_OCTETS_OK",
        "Octet count for Frames Rcvd w/o Error (IEEE_R_OCTETS_OK). Counts total octets (includes header and FCS fields)., offset: 0x2E0 ",
        handles.bport1,
        736,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.IEEE_R_OCTETS_OK.value),
        True
    );
    ppmCreateRegister("ab_ATCR",
        "Timer Control Register, offset: 0x400 ",
        handles.bport1,
        1024,
        4,
        read_32,
        bport1_ab_ATCR_maskWrite,
        view32,
        &(bport1_ab_data.ATCR.value),
        True
    );
    ppmCreateRegister("ab_ATVR",
        "Timer Value Register, offset: 0x404 ",
        handles.bport1,
        1028,
        4,
        read_32,
        bport1_ab_ATVR_maskWrite,
        view32,
        &(bport1_ab_data.ATVR.value),
        True
    );
    ppmCreateRegister("ab_ATOFF",
        "Timer Offset Register, offset: 0x408 ",
        handles.bport1,
        1032,
        4,
        read_32,
        bport1_ab_ATOFF_maskWrite,
        view32,
        &(bport1_ab_data.ATOFF.value),
        True
    );
    ppmCreateRegister("ab_ATPER",
        "Timer Period Register, offset: 0x40C ",
        handles.bport1,
        1036,
        4,
        read_32,
        bport1_ab_ATPER_maskWrite,
        view32,
        &(bport1_ab_data.ATPER.value),
        True
    );
    ppmCreateRegister("ab_ATCOR",
        "Timer Correction Register, offset: 0x410 ",
        handles.bport1,
        1040,
        4,
        read_32,
        bport1_ab_ATCOR_maskWrite,
        view32,
        &(bport1_ab_data.ATCOR.value),
        True
    );
    ppmCreateRegister("ab_ATINC",
        "Time-Stamping Clock Period Register, offset: 0x414 ",
        handles.bport1,
        1044,
        4,
        read_32,
        bport1_ab_ATINC_maskWrite,
        view32,
        &(bport1_ab_data.ATINC.value),
        True
    );
    ppmCreateRegister("ab_ATSTMP",
        "Timestamp of Last Transmitted Frame, offset: 0x418 ",
        handles.bport1,
        1048,
        4,
        read_32,
        bport1_ab_ATSTMP_maskWrite,
        view32,
        &(bport1_ab_data.ATSTMP.value),
        True
    );
    ppmCreateRegister("ab_TGSR",
        "Timer Global Status Register, offset: 0x604 ",
        handles.bport1,
        1540,
        4,
        read_32,
        bport1_ab_TGSR_maskWrite,
        view32,
        &(bport1_ab_data.TGSR.value),
        True
    );
    ppmCreateRegister("ab_TCSR0",
        "Timer Control Status Register, array offset: 0x608, array step: 0x8 ",
        handles.bport1,
        1544,
        4,
        read_32,
        bport1_ab_TCSR0_maskWrite,
        view32,
        &(bport1_ab_data.TCSR0.value),
        True
    );
    ppmCreateRegister("ab_TCCR0",
        "Timer Compare Capture Register, array offset: 0x60C, array step: 0x8 ",
        handles.bport1,
        1548,
        4,
        read_32,
        bport1_ab_TCCR0_maskWrite,
        view32,
        &(bport1_ab_data.TCCR0.value),
        True
    );
    ppmCreateRegister("ab_TCSR1",
        "Timer Control Status Register, array offset: 0x610, array step: 0x8 ",
        handles.bport1,
        1552,
        4,
        read_32,
        bport1_ab_TCSR1_maskWrite,
        view32,
        &(bport1_ab_data.TCSR1.value),
        True
    );
    ppmCreateRegister("ab_TCCR1",
        "Timer Compare Capture Register, array offset: 0x614, array step: 0x8 ",
        handles.bport1,
        1556,
        4,
        read_32,
        bport1_ab_TCCR1_maskWrite,
        view32,
        &(bport1_ab_data.TCCR1.value),
        True
    );
    ppmCreateRegister("ab_TCSR2",
        "Timer Control Status Register, array offset: 0x618, array step: 0x8 ",
        handles.bport1,
        1560,
        4,
        read_32,
        bport1_ab_TCSR2_maskWrite,
        view32,
        &(bport1_ab_data.TCSR2.value),
        True
    );
    ppmCreateRegister("ab_TCCR2",
        "Timer Compare Capture Register, array offset: 0x61c, array step: 0x8 ",
        handles.bport1,
        1564,
        4,
        read_32,
        bport1_ab_TCCR2_maskWrite,
        view32,
        &(bport1_ab_data.TCCR2.value),
        True
    );
    ppmCreateRegister("ab_TCSR3",
        "Timer Control Status Register, array offset: 0x620, array step: 0x8 ",
        handles.bport1,
        1568,
        4,
        read_32,
        bport1_ab_TCSR3_maskWrite,
        view32,
        &(bport1_ab_data.TCSR3.value),
        True
    );
    ppmCreateRegister("ab_TCCR3",
        "Timer Compare Capture Register, array offset: 0x624, array step: 0x8 ",
        handles.bport1,
        1572,
        4,
        read_32,
        bport1_ab_TCCR3_maskWrite,
        view32,
        &(bport1_ab_data.TCCR3.value),
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
        bport1_ab_data.TCCR3.value = 0x0;
        bport1_ab_data.TCSR3.value = 0x0;
        bport1_ab_data.TCCR2.value = 0x0;
        bport1_ab_data.TCSR2.value = 0x0;
        bport1_ab_data.TCCR1.value = 0x0;
        bport1_ab_data.TCSR1.value = 0x0;
        bport1_ab_data.TCCR0.value = 0x0;
        bport1_ab_data.TCSR0.value = 0x0;
        bport1_ab_data.TGSR.value = 0x0;
        bport1_ab_data.ATSTMP.value = 0x0;
        bport1_ab_data.ATINC.value = 0x0;
        bport1_ab_data.ATCOR.value = 0x0;
        bport1_ab_data.ATPER.value = 0x3b9aca00;
        bport1_ab_data.ATOFF.value = 0x0;
        bport1_ab_data.ATVR.value = 0x0;
        bport1_ab_data.ATCR.value = 0x0;
        bport1_ab_data.IEEE_R_OCTETS_OK.value = 0x0;
        bport1_ab_data.IEEE_R_FDXFC.value = 0x0;
        bport1_ab_data.IEEE_R_MACERR.value = 0x0;
        bport1_ab_data.IEEE_R_ALIGN.value = 0x0;
        bport1_ab_data.IEEE_R_CRC.value = 0x0;
        bport1_ab_data.RMON_R_FRAME_OK.value = 0x0;
        bport1_ab_data.RMON_R_DROP.value = 0x0;
        bport1_ab_data.RMON_R_OCTETS.value = 0x0;
        bport1_ab_data.RMON_R_P_GTE2048.value = 0x0;
        bport1_ab_data.RMON_R_P1024TO2047.value = 0x0;
        bport1_ab_data.RMON_R_P512TO1023.value = 0x0;
        bport1_ab_data.RMON_R_P256TO511.value = 0x0;
        bport1_ab_data.RMON_R_P128TO255.value = 0x0;
        bport1_ab_data.RMON_R_P65TO127.value = 0x0;
        bport1_ab_data.RMON_R_P64.value = 0x0;
        bport1_ab_data.RMON_R_RESVD_0.value = 0x0;
        bport1_ab_data.RMON_R_JAB.value = 0x0;
        bport1_ab_data.RMON_R_FRAG.value = 0x0;
        bport1_ab_data.RMON_R_OVERSIZE.value = 0x0;
        bport1_ab_data.RMON_R_UNDERSIZE.value = 0x0;
        bport1_ab_data.RMON_R_CRC_ALIGN.value = 0x0;
        bport1_ab_data.RMON_R_MC_PKT.value = 0x0;
        bport1_ab_data.RMON_R_BC_PKT.value = 0x0;
        bport1_ab_data.RMON_R_PACKETS.value = 0x0;
        bport1_ab_data.IEEE_T_OCTETS_OK.value = 0x0;
        bport1_ab_data.IEEE_T_FDXFC.value = 0x0;
        bport1_ab_data.IEEE_T_SQE.value = 0x0;
        bport1_ab_data.IEEE_T_CSERR.value = 0x0;
        bport1_ab_data.IEEE_T_MACERR.value = 0x0;
        bport1_ab_data.IEEE_T_EXCOL.value = 0x0;
        bport1_ab_data.IEEE_T_LCOL.value = 0x0;
        bport1_ab_data.IEEE_T_DEF.value = 0x0;
        bport1_ab_data.IEEE_T_MCOL.value = 0x0;
        bport1_ab_data.IEEE_T_1COL.value = 0x0;
        bport1_ab_data.IEEE_T_FRAME_OK.value = 0x0;
        bport1_ab_data.IEEE_T_DROP.value = 0x0;
        bport1_ab_data.RMON_T_OCTETS.value = 0x0;
        bport1_ab_data.RMON_T_P_GTE2048.value = 0x0;
        bport1_ab_data.RMON_T_P1024TO2047.value = 0x0;
        bport1_ab_data.RMON_T_P512TO1023.value = 0x0;
        bport1_ab_data.RMON_T_P256TO511.value = 0x0;
        bport1_ab_data.RMON_T_P128TO255.value = 0x0;
        bport1_ab_data.RMON_T_P65TO127.value = 0x0;
        bport1_ab_data.RMON_T_P64.value = 0x0;
        bport1_ab_data.RMON_T_COL.value = 0x0;
        bport1_ab_data.RMON_T_JAB.value = 0x0;
        bport1_ab_data.RMON_T_FRAG.value = 0x0;
        bport1_ab_data.RMON_T_OVERSIZE.value = 0x0;
        bport1_ab_data.RMON_T_UNDERSIZE.value = 0x0;
        bport1_ab_data.RMON_T_CRC_ALIGN.value = 0x0;
        bport1_ab_data.RMON_T_MC_PKT.value = 0x0;
        bport1_ab_data.RMON_T_BC_PKT.value = 0x0;
        bport1_ab_data.RMON_T_PACKETS.value = 0x0;
        bport1_ab_data.RMON_T_DROP.value = 0x0;
        bport1_ab_data.RACC.value = 0x0;
        bport1_ab_data.TACC.value = 0x0;
        bport1_ab_data.FTRL.value = 0x7ff;
        bport1_ab_data.TIPG.value = 0xc;
        bport1_ab_data.TAFL.value = 0x8;
        bport1_ab_data.TAEM.value = 0x4;
        bport1_ab_data.TSEM.value = 0x0;
        bport1_ab_data.RAFL.value = 0x4;
        bport1_ab_data.RAEM.value = 0x4;
        bport1_ab_data.RSEM.value = 0x0;
        bport1_ab_data.RSFL.value = 0x0;
        bport1_ab_data.MRBR.value = 0x0;
        bport1_ab_data.TDSR.value = 0x0;
        bport1_ab_data.RDSR.value = 0x0;
        bport1_ab_data.TFWR.value = 0x0;
        bport1_ab_data.GALR.value = 0x0;
        bport1_ab_data.GAUR.value = 0x0;
        bport1_ab_data.IALR.value = 0x0;
        bport1_ab_data.IAUR.value = 0x0;
        bport1_ab_data.OPD.value = 0x10000;
        bport1_ab_data.PAUR.value = 0x8808;
        bport1_ab_data.PALR.value = 0x0;
        bport1_ab_data.TCR.value = 0x0;
        bport1_ab_data.RCR.value = 0xfee0001;
        bport1_ab_data.MIBC.value = 0xc0000000;
        bport1_ab_data.MSCR.value = 0x0;
        bport1_ab_data.MMFR.value = 0x0;
        bport1_ab_data.ECR.value = 0xf0000000;
        bport1_ab_data.TDAR.value = 0x0;
        bport1_ab_data.RDAR.value = 0x0;
        bport1_ab_data.EIMR.value = 0x0;
        bport1_ab_data.EIR.value = 0x0;
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

