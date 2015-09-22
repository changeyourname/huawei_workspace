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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisPORT", "Example");
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

static PPM_WRITE_CB(bport1_ab_DFCR_maskWrite) {
    bport1_ab_data.DFCR.value = (bport1_ab_data.DFCR.value & 0xfffffffe) | (data & 0x1);
}

static PPM_WRITE_CB(bport1_ab_DFER_maskWrite) {
    bport1_ab_data.DFER.value = (bport1_ab_data.DFER.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DFWR_maskWrite) {
    bport1_ab_data.DFWR.value = (bport1_ab_data.DFWR.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_GPCHR_maskWrite) {
    bport1_ab_data.GPCHR.value = (bport1_ab_data.GPCHR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_GPCLR_maskWrite) {
    bport1_ab_data.GPCLR.value = (bport1_ab_data.GPCLR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_ISFR_maskWrite) {
    bport1_ab_data.ISFR.value = (bport1_ab_data.ISFR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_PCR0_maskWrite) {
    bport1_ab_data.PCR0.value = (bport1_ab_data.PCR0.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR10_maskWrite) {
    bport1_ab_data.PCR10.value = (bport1_ab_data.PCR10.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR11_maskWrite) {
    bport1_ab_data.PCR11.value = (bport1_ab_data.PCR11.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR12_maskWrite) {
    bport1_ab_data.PCR12.value = (bport1_ab_data.PCR12.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR13_maskWrite) {
    bport1_ab_data.PCR13.value = (bport1_ab_data.PCR13.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR14_maskWrite) {
    bport1_ab_data.PCR14.value = (bport1_ab_data.PCR14.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR15_maskWrite) {
    bport1_ab_data.PCR15.value = (bport1_ab_data.PCR15.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR16_maskWrite) {
    bport1_ab_data.PCR16.value = (bport1_ab_data.PCR16.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR17_maskWrite) {
    bport1_ab_data.PCR17.value = (bport1_ab_data.PCR17.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR18_maskWrite) {
    bport1_ab_data.PCR18.value = (bport1_ab_data.PCR18.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR19_maskWrite) {
    bport1_ab_data.PCR19.value = (bport1_ab_data.PCR19.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR1_maskWrite) {
    bport1_ab_data.PCR1.value = (bport1_ab_data.PCR1.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR20_maskWrite) {
    bport1_ab_data.PCR20.value = (bport1_ab_data.PCR20.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR21_maskWrite) {
    bport1_ab_data.PCR21.value = (bport1_ab_data.PCR21.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR22_maskWrite) {
    bport1_ab_data.PCR22.value = (bport1_ab_data.PCR22.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR23_maskWrite) {
    bport1_ab_data.PCR23.value = (bport1_ab_data.PCR23.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR24_maskWrite) {
    bport1_ab_data.PCR24.value = (bport1_ab_data.PCR24.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR25_maskWrite) {
    bport1_ab_data.PCR25.value = (bport1_ab_data.PCR25.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR26_maskWrite) {
    bport1_ab_data.PCR26.value = (bport1_ab_data.PCR26.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR27_maskWrite) {
    bport1_ab_data.PCR27.value = (bport1_ab_data.PCR27.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR28_maskWrite) {
    bport1_ab_data.PCR28.value = (bport1_ab_data.PCR28.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR29_maskWrite) {
    bport1_ab_data.PCR29.value = (bport1_ab_data.PCR29.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR2_maskWrite) {
    bport1_ab_data.PCR2.value = (bport1_ab_data.PCR2.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR30_maskWrite) {
    bport1_ab_data.PCR30.value = (bport1_ab_data.PCR30.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR31_maskWrite) {
    bport1_ab_data.PCR31.value = (bport1_ab_data.PCR31.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR3_maskWrite) {
    bport1_ab_data.PCR3.value = (bport1_ab_data.PCR3.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR4_maskWrite) {
    bport1_ab_data.PCR4.value = (bport1_ab_data.PCR4.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR5_maskWrite) {
    bport1_ab_data.PCR5.value = (bport1_ab_data.PCR5.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR6_maskWrite) {
    bport1_ab_data.PCR6.value = (bport1_ab_data.PCR6.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR7_maskWrite) {
    bport1_ab_data.PCR7.value = (bport1_ab_data.PCR7.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR8_maskWrite) {
    bport1_ab_data.PCR8.value = (bport1_ab_data.PCR8.value & 0xfef07888) | (data & 0x10f8777);
}

static PPM_WRITE_CB(bport1_ab_PCR9_maskWrite) {
    bport1_ab_data.PCR9.value = (bport1_ab_data.PCR9.value & 0xfef07888) | (data & 0x10f8777);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_PCR0",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_PCR0_maskWrite,
        view32,
        &(bport1_ab_data.PCR0.value),
        True
    );
    ppmCreateRegister("ab_PCR1",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_PCR1_maskWrite,
        view32,
        &(bport1_ab_data.PCR1.value),
        True
    );
    ppmCreateRegister("ab_PCR2",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_PCR2_maskWrite,
        view32,
        &(bport1_ab_data.PCR2.value),
        True
    );
    ppmCreateRegister("ab_PCR3",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_PCR3_maskWrite,
        view32,
        &(bport1_ab_data.PCR3.value),
        True
    );
    ppmCreateRegister("ab_PCR4",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_PCR4_maskWrite,
        view32,
        &(bport1_ab_data.PCR4.value),
        True
    );
    ppmCreateRegister("ab_PCR5",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_PCR5_maskWrite,
        view32,
        &(bport1_ab_data.PCR5.value),
        True
    );
    ppmCreateRegister("ab_PCR6",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_PCR6_maskWrite,
        view32,
        &(bport1_ab_data.PCR6.value),
        True
    );
    ppmCreateRegister("ab_PCR7",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_PCR7_maskWrite,
        view32,
        &(bport1_ab_data.PCR7.value),
        True
    );
    ppmCreateRegister("ab_PCR8",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_PCR8_maskWrite,
        view32,
        &(bport1_ab_data.PCR8.value),
        True
    );
    ppmCreateRegister("ab_PCR9",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_PCR9_maskWrite,
        view32,
        &(bport1_ab_data.PCR9.value),
        True
    );
    ppmCreateRegister("ab_PCR10",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_PCR10_maskWrite,
        view32,
        &(bport1_ab_data.PCR10.value),
        True
    );
    ppmCreateRegister("ab_PCR11",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_PCR11_maskWrite,
        view32,
        &(bport1_ab_data.PCR11.value),
        True
    );
    ppmCreateRegister("ab_PCR12",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_PCR12_maskWrite,
        view32,
        &(bport1_ab_data.PCR12.value),
        True
    );
    ppmCreateRegister("ab_PCR13",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_PCR13_maskWrite,
        view32,
        &(bport1_ab_data.PCR13.value),
        True
    );
    ppmCreateRegister("ab_PCR14",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_PCR14_maskWrite,
        view32,
        &(bport1_ab_data.PCR14.value),
        True
    );
    ppmCreateRegister("ab_PCR15",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        60,
        4,
        read_32,
        bport1_ab_PCR15_maskWrite,
        view32,
        &(bport1_ab_data.PCR15.value),
        True
    );
    ppmCreateRegister("ab_PCR16",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_PCR16_maskWrite,
        view32,
        &(bport1_ab_data.PCR16.value),
        True
    );
    ppmCreateRegister("ab_PCR17",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_PCR17_maskWrite,
        view32,
        &(bport1_ab_data.PCR17.value),
        True
    );
    ppmCreateRegister("ab_PCR18",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        72,
        4,
        read_32,
        bport1_ab_PCR18_maskWrite,
        view32,
        &(bport1_ab_data.PCR18.value),
        True
    );
    ppmCreateRegister("ab_PCR19",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        76,
        4,
        read_32,
        bport1_ab_PCR19_maskWrite,
        view32,
        &(bport1_ab_data.PCR19.value),
        True
    );
    ppmCreateRegister("ab_PCR20",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        80,
        4,
        read_32,
        bport1_ab_PCR20_maskWrite,
        view32,
        &(bport1_ab_data.PCR20.value),
        True
    );
    ppmCreateRegister("ab_PCR21",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        84,
        4,
        read_32,
        bport1_ab_PCR21_maskWrite,
        view32,
        &(bport1_ab_data.PCR21.value),
        True
    );
    ppmCreateRegister("ab_PCR22",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        88,
        4,
        read_32,
        bport1_ab_PCR22_maskWrite,
        view32,
        &(bport1_ab_data.PCR22.value),
        True
    );
    ppmCreateRegister("ab_PCR23",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        92,
        4,
        read_32,
        bport1_ab_PCR23_maskWrite,
        view32,
        &(bport1_ab_data.PCR23.value),
        True
    );
    ppmCreateRegister("ab_PCR24",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        96,
        4,
        read_32,
        bport1_ab_PCR24_maskWrite,
        view32,
        &(bport1_ab_data.PCR24.value),
        True
    );
    ppmCreateRegister("ab_PCR25",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        100,
        4,
        read_32,
        bport1_ab_PCR25_maskWrite,
        view32,
        &(bport1_ab_data.PCR25.value),
        True
    );
    ppmCreateRegister("ab_PCR26",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        104,
        4,
        read_32,
        bport1_ab_PCR26_maskWrite,
        view32,
        &(bport1_ab_data.PCR26.value),
        True
    );
    ppmCreateRegister("ab_PCR27",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        108,
        4,
        read_32,
        bport1_ab_PCR27_maskWrite,
        view32,
        &(bport1_ab_data.PCR27.value),
        True
    );
    ppmCreateRegister("ab_PCR28",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        112,
        4,
        read_32,
        bport1_ab_PCR28_maskWrite,
        view32,
        &(bport1_ab_data.PCR28.value),
        True
    );
    ppmCreateRegister("ab_PCR29",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        116,
        4,
        read_32,
        bport1_ab_PCR29_maskWrite,
        view32,
        &(bport1_ab_data.PCR29.value),
        True
    );
    ppmCreateRegister("ab_PCR30",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        120,
        4,
        read_32,
        bport1_ab_PCR30_maskWrite,
        view32,
        &(bport1_ab_data.PCR30.value),
        True
    );
    ppmCreateRegister("ab_PCR31",
        "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        124,
        4,
        read_32,
        bport1_ab_PCR31_maskWrite,
        view32,
        &(bport1_ab_data.PCR31.value),
        True
    );
    ppmCreateRegister("ab_GPCLR",
        "Global Pin Control Low Register, offset: 0x80 ",
        handles.bport1,
        128,
        4,
        0,
        bport1_ab_GPCLR_maskWrite,
        view32,
        &(bport1_ab_data.GPCLR.value),
        True
    );
    ppmCreateRegister("ab_GPCHR",
        "Global Pin Control High Register, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        0,
        bport1_ab_GPCHR_maskWrite,
        view32,
        &(bport1_ab_data.GPCHR.value),
        True
    );
    ppmCreateRegister("ab_ISFR",
        "Interrupt Status Flag Register, offset: 0xA0 ",
        handles.bport1,
        160,
        4,
        read_32,
        bport1_ab_ISFR_maskWrite,
        view32,
        &(bport1_ab_data.ISFR.value),
        True
    );
    ppmCreateRegister("ab_DFER",
        "Digital Filter Enable Register, offset: 0xC0 ",
        handles.bport1,
        192,
        4,
        read_32,
        bport1_ab_DFER_maskWrite,
        view32,
        &(bport1_ab_data.DFER.value),
        True
    );
    ppmCreateRegister("ab_DFCR",
        "Digital Filter Clock Register, offset: 0xC4 ",
        handles.bport1,
        196,
        4,
        read_32,
        bport1_ab_DFCR_maskWrite,
        view32,
        &(bport1_ab_data.DFCR.value),
        True
    );
    ppmCreateRegister("ab_DFWR",
        "Digital Filter Width Register, offset: 0xC8 ",
        handles.bport1,
        200,
        4,
        read_32,
        bport1_ab_DFWR_maskWrite,
        view32,
        &(bport1_ab_data.DFWR.value),
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
        bport1_ab_data.DFWR.value = 0x0;
        bport1_ab_data.DFCR.value = 0x0;
        bport1_ab_data.DFER.value = 0x0;
        bport1_ab_data.ISFR.value = 0x0;
        bport1_ab_data.GPCHR.value = 0x0;
        bport1_ab_data.GPCLR.value = 0x0;
        bport1_ab_data.PCR31.value = 0x0;
        bport1_ab_data.PCR30.value = 0x0;
        bport1_ab_data.PCR29.value = 0x0;
        bport1_ab_data.PCR28.value = 0x0;
        bport1_ab_data.PCR27.value = 0x0;
        bport1_ab_data.PCR26.value = 0x0;
        bport1_ab_data.PCR25.value = 0x0;
        bport1_ab_data.PCR24.value = 0x0;
        bport1_ab_data.PCR23.value = 0x0;
        bport1_ab_data.PCR22.value = 0x0;
        bport1_ab_data.PCR21.value = 0x0;
        bport1_ab_data.PCR20.value = 0x0;
        bport1_ab_data.PCR19.value = 0x0;
        bport1_ab_data.PCR18.value = 0x0;
        bport1_ab_data.PCR17.value = 0x0;
        bport1_ab_data.PCR16.value = 0x0;
        bport1_ab_data.PCR15.value = 0x0;
        bport1_ab_data.PCR14.value = 0x0;
        bport1_ab_data.PCR13.value = 0x0;
        bport1_ab_data.PCR12.value = 0x0;
        bport1_ab_data.PCR11.value = 0x0;
        bport1_ab_data.PCR10.value = 0x0;
        bport1_ab_data.PCR9.value = 0x0;
        bport1_ab_data.PCR8.value = 0x0;
        bport1_ab_data.PCR7.value = 0x0;
        bport1_ab_data.PCR6.value = 0x0;
        bport1_ab_data.PCR5.value = 0x0;
        bport1_ab_data.PCR4.value = 0x0;
        bport1_ab_data.PCR3.value = 0x0;
        bport1_ab_data.PCR2.value = 0x0;
        bport1_ab_data.PCR1.value = 0x0;
        bport1_ab_data.PCR0.value = 0x0;
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

