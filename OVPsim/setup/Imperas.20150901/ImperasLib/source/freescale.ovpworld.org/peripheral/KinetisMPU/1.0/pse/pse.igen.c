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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisMPU", "Example");
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

static PPM_WRITE_CB(bport1_ab_CESR_maskWrite) {
    bport1_ab_data.CESR.value = (bport1_ab_data.CESR.value & 0xfffffe) | (data & 0xff000001);
}

static PPM_WRITE_CB(bport1_ab_RGD0_WORD0_maskWrite) {
    bport1_ab_data.RGD0_WORD0.value = (bport1_ab_data.RGD0_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD0_WORD1_maskWrite) {
    bport1_ab_data.RGD0_WORD1.value = (bport1_ab_data.RGD0_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD0_WORD2_maskWrite) {
    bport1_ab_data.RGD0_WORD2.value = (bport1_ab_data.RGD0_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD0_WORD3_maskWrite) {
    bport1_ab_data.RGD0_WORD3.value = (bport1_ab_data.RGD0_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD10_WORD0_maskWrite) {
    bport1_ab_data.RGD10_WORD0.value = (bport1_ab_data.RGD10_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD10_WORD1_maskWrite) {
    bport1_ab_data.RGD10_WORD1.value = (bport1_ab_data.RGD10_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD10_WORD2_maskWrite) {
    bport1_ab_data.RGD10_WORD2.value = (bport1_ab_data.RGD10_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD10_WORD3_maskWrite) {
    bport1_ab_data.RGD10_WORD3.value = (bport1_ab_data.RGD10_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD11_WORD0_maskWrite) {
    bport1_ab_data.RGD11_WORD0.value = (bport1_ab_data.RGD11_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD11_WORD1_maskWrite) {
    bport1_ab_data.RGD11_WORD1.value = (bport1_ab_data.RGD11_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD11_WORD2_maskWrite) {
    bport1_ab_data.RGD11_WORD2.value = (bport1_ab_data.RGD11_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD11_WORD3_maskWrite) {
    bport1_ab_data.RGD11_WORD3.value = (bport1_ab_data.RGD11_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD12_WORD0_maskWrite) {
    bport1_ab_data.RGD12_WORD0.value = (bport1_ab_data.RGD12_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD12_WORD1_maskWrite) {
    bport1_ab_data.RGD12_WORD1.value = (bport1_ab_data.RGD12_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD12_WORD2_maskWrite) {
    bport1_ab_data.RGD12_WORD2.value = (bport1_ab_data.RGD12_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD12_WORD3_maskWrite) {
    bport1_ab_data.RGD12_WORD3.value = (bport1_ab_data.RGD12_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD13_WORD0_maskWrite) {
    bport1_ab_data.RGD13_WORD0.value = (bport1_ab_data.RGD13_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD13_WORD1_maskWrite) {
    bport1_ab_data.RGD13_WORD1.value = (bport1_ab_data.RGD13_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD13_WORD2_maskWrite) {
    bport1_ab_data.RGD13_WORD2.value = (bport1_ab_data.RGD13_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD13_WORD3_maskWrite) {
    bport1_ab_data.RGD13_WORD3.value = (bport1_ab_data.RGD13_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD14_WORD0_maskWrite) {
    bport1_ab_data.RGD14_WORD0.value = (bport1_ab_data.RGD14_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD14_WORD1_maskWrite) {
    bport1_ab_data.RGD14_WORD1.value = (bport1_ab_data.RGD14_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD14_WORD2_maskWrite) {
    bport1_ab_data.RGD14_WORD2.value = (bport1_ab_data.RGD14_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD14_WORD3_maskWrite) {
    bport1_ab_data.RGD14_WORD3.value = (bport1_ab_data.RGD14_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD15_WORD0_maskWrite) {
    bport1_ab_data.RGD15_WORD0.value = (bport1_ab_data.RGD15_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD15_WORD1_maskWrite) {
    bport1_ab_data.RGD15_WORD1.value = (bport1_ab_data.RGD15_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD15_WORD2_maskWrite) {
    bport1_ab_data.RGD15_WORD2.value = (bport1_ab_data.RGD15_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD15_WORD3_maskWrite) {
    bport1_ab_data.RGD15_WORD3.value = (bport1_ab_data.RGD15_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD1_WORD0_maskWrite) {
    bport1_ab_data.RGD1_WORD0.value = (bport1_ab_data.RGD1_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD1_WORD1_maskWrite) {
    bport1_ab_data.RGD1_WORD1.value = (bport1_ab_data.RGD1_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD1_WORD2_maskWrite) {
    bport1_ab_data.RGD1_WORD2.value = (bport1_ab_data.RGD1_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD1_WORD3_maskWrite) {
    bport1_ab_data.RGD1_WORD3.value = (bport1_ab_data.RGD1_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD2_WORD0_maskWrite) {
    bport1_ab_data.RGD2_WORD0.value = (bport1_ab_data.RGD2_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD2_WORD1_maskWrite) {
    bport1_ab_data.RGD2_WORD1.value = (bport1_ab_data.RGD2_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD2_WORD2_maskWrite) {
    bport1_ab_data.RGD2_WORD2.value = (bport1_ab_data.RGD2_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD2_WORD3_maskWrite) {
    bport1_ab_data.RGD2_WORD3.value = (bport1_ab_data.RGD2_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD3_WORD0_maskWrite) {
    bport1_ab_data.RGD3_WORD0.value = (bport1_ab_data.RGD3_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD3_WORD1_maskWrite) {
    bport1_ab_data.RGD3_WORD1.value = (bport1_ab_data.RGD3_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD3_WORD2_maskWrite) {
    bport1_ab_data.RGD3_WORD2.value = (bport1_ab_data.RGD3_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD3_WORD3_maskWrite) {
    bport1_ab_data.RGD3_WORD3.value = (bport1_ab_data.RGD3_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD4_WORD0_maskWrite) {
    bport1_ab_data.RGD4_WORD0.value = (bport1_ab_data.RGD4_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD4_WORD1_maskWrite) {
    bport1_ab_data.RGD4_WORD1.value = (bport1_ab_data.RGD4_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD4_WORD2_maskWrite) {
    bport1_ab_data.RGD4_WORD2.value = (bport1_ab_data.RGD4_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD4_WORD3_maskWrite) {
    bport1_ab_data.RGD4_WORD3.value = (bport1_ab_data.RGD4_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD5_WORD0_maskWrite) {
    bport1_ab_data.RGD5_WORD0.value = (bport1_ab_data.RGD5_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD5_WORD1_maskWrite) {
    bport1_ab_data.RGD5_WORD1.value = (bport1_ab_data.RGD5_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD5_WORD2_maskWrite) {
    bport1_ab_data.RGD5_WORD2.value = (bport1_ab_data.RGD5_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD5_WORD3_maskWrite) {
    bport1_ab_data.RGD5_WORD3.value = (bport1_ab_data.RGD5_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD6_WORD0_maskWrite) {
    bport1_ab_data.RGD6_WORD0.value = (bport1_ab_data.RGD6_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD6_WORD1_maskWrite) {
    bport1_ab_data.RGD6_WORD1.value = (bport1_ab_data.RGD6_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD6_WORD2_maskWrite) {
    bport1_ab_data.RGD6_WORD2.value = (bport1_ab_data.RGD6_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD6_WORD3_maskWrite) {
    bport1_ab_data.RGD6_WORD3.value = (bport1_ab_data.RGD6_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD7_WORD0_maskWrite) {
    bport1_ab_data.RGD7_WORD0.value = (bport1_ab_data.RGD7_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD7_WORD1_maskWrite) {
    bport1_ab_data.RGD7_WORD1.value = (bport1_ab_data.RGD7_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD7_WORD2_maskWrite) {
    bport1_ab_data.RGD7_WORD2.value = (bport1_ab_data.RGD7_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD7_WORD3_maskWrite) {
    bport1_ab_data.RGD7_WORD3.value = (bport1_ab_data.RGD7_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD8_WORD0_maskWrite) {
    bport1_ab_data.RGD8_WORD0.value = (bport1_ab_data.RGD8_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD8_WORD1_maskWrite) {
    bport1_ab_data.RGD8_WORD1.value = (bport1_ab_data.RGD8_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD8_WORD2_maskWrite) {
    bport1_ab_data.RGD8_WORD2.value = (bport1_ab_data.RGD8_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD8_WORD3_maskWrite) {
    bport1_ab_data.RGD8_WORD3.value = (bport1_ab_data.RGD8_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGD9_WORD0_maskWrite) {
    bport1_ab_data.RGD9_WORD0.value = (bport1_ab_data.RGD9_WORD0.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD9_WORD1_maskWrite) {
    bport1_ab_data.RGD9_WORD1.value = (bport1_ab_data.RGD9_WORD1.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_RGD9_WORD2_maskWrite) {
    bport1_ab_data.RGD9_WORD2.value = (bport1_ab_data.RGD9_WORD2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGD9_WORD3_maskWrite) {
    bport1_ab_data.RGD9_WORD3.value = (bport1_ab_data.RGD9_WORD3.value & 0xfffe) | (data & 0xffff0001);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC0_maskWrite) {
    bport1_ab_data.RGDAAC0.value = (bport1_ab_data.RGDAAC0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC10_maskWrite) {
    bport1_ab_data.RGDAAC10.value = (bport1_ab_data.RGDAAC10.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC11_maskWrite) {
    bport1_ab_data.RGDAAC11.value = (bport1_ab_data.RGDAAC11.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC12_maskWrite) {
    bport1_ab_data.RGDAAC12.value = (bport1_ab_data.RGDAAC12.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC13_maskWrite) {
    bport1_ab_data.RGDAAC13.value = (bport1_ab_data.RGDAAC13.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC14_maskWrite) {
    bport1_ab_data.RGDAAC14.value = (bport1_ab_data.RGDAAC14.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC15_maskWrite) {
    bport1_ab_data.RGDAAC15.value = (bport1_ab_data.RGDAAC15.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC1_maskWrite) {
    bport1_ab_data.RGDAAC1.value = (bport1_ab_data.RGDAAC1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC2_maskWrite) {
    bport1_ab_data.RGDAAC2.value = (bport1_ab_data.RGDAAC2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC3_maskWrite) {
    bport1_ab_data.RGDAAC3.value = (bport1_ab_data.RGDAAC3.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC4_maskWrite) {
    bport1_ab_data.RGDAAC4.value = (bport1_ab_data.RGDAAC4.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC5_maskWrite) {
    bport1_ab_data.RGDAAC5.value = (bport1_ab_data.RGDAAC5.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC6_maskWrite) {
    bport1_ab_data.RGDAAC6.value = (bport1_ab_data.RGDAAC6.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC7_maskWrite) {
    bport1_ab_data.RGDAAC7.value = (bport1_ab_data.RGDAAC7.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC8_maskWrite) {
    bport1_ab_data.RGDAAC8.value = (bport1_ab_data.RGDAAC8.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RGDAAC9_maskWrite) {
    bport1_ab_data.RGDAAC9.value = (bport1_ab_data.RGDAAC9.value & 0x0) | (data & 0xffffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_CESR",
        "Control/Error Status Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_CESR_maskWrite,
        view32,
        &(bport1_ab_data.CESR.value),
        True
    );
    ppmCreateRegister("ab_EAR0",
        "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EAR0.value),
        True
    );
    ppmCreateRegister("ab_EDR0",
        "Error Detail Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EDR0.value),
        True
    );
    ppmCreateRegister("ab_EAR1",
        "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        24,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EAR1.value),
        True
    );
    ppmCreateRegister("ab_EDR1",
        "Error Detail Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
        handles.bport1,
        28,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EDR1.value),
        True
    );
    ppmCreateRegister("ab_EAR2",
        "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        32,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EAR2.value),
        True
    );
    ppmCreateRegister("ab_EDR2",
        "Error Detail Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
        handles.bport1,
        36,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EDR2.value),
        True
    );
    ppmCreateRegister("ab_EAR3",
        "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        40,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EAR3.value),
        True
    );
    ppmCreateRegister("ab_EDR3",
        "Error Detail Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
        handles.bport1,
        44,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EDR3.value),
        True
    );
    ppmCreateRegister("ab_EAR4",
        "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        48,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EAR4.value),
        True
    );
    ppmCreateRegister("ab_EDR4",
        "Error Detail Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
        handles.bport1,
        52,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EDR4.value),
        True
    );
    ppmCreateRegister("ab_RGD0_WORD0",
        "Region Descriptor 0, Word 0, offset: 0x400 ",
        handles.bport1,
        1024,
        4,
        read_32,
        bport1_ab_RGD0_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD0_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD0_WORD1",
        "Region Descriptor 0, Word 1, offset: 0x404 ",
        handles.bport1,
        1028,
        4,
        read_32,
        bport1_ab_RGD0_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD0_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD0_WORD2",
        "Region Descriptor 0, Word 2, offset: 0x408 ",
        handles.bport1,
        1032,
        4,
        read_32,
        bport1_ab_RGD0_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD0_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD0_WORD3",
        "Region Descriptor 0, Word 3, offset: 0x40c ",
        handles.bport1,
        1036,
        4,
        read_32,
        bport1_ab_RGD0_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD0_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD1_WORD0",
        "Region Descriptor 1, Word 0, offset: 0x410 ",
        handles.bport1,
        1040,
        4,
        read_32,
        bport1_ab_RGD1_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD1_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD1_WORD1",
        "Region Descriptor 1, Word 1, offset: 0x414 ",
        handles.bport1,
        1044,
        4,
        read_32,
        bport1_ab_RGD1_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD1_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD1_WORD2",
        "Region Descriptor 1, Word 2, offset: 0x418 ",
        handles.bport1,
        1048,
        4,
        read_32,
        bport1_ab_RGD1_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD1_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD1_WORD3",
        "Region Descriptor 1, Word 3, offset: 0x41c ",
        handles.bport1,
        1052,
        4,
        read_32,
        bport1_ab_RGD1_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD1_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD2_WORD0",
        "Region Descriptor 2, Word 0, offset: 0x420 ",
        handles.bport1,
        1056,
        4,
        read_32,
        bport1_ab_RGD2_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD2_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD2_WORD1",
        "Region Descriptor 2, Word 1, offset: 0x424 ",
        handles.bport1,
        1060,
        4,
        read_32,
        bport1_ab_RGD2_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD2_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD2_WORD2",
        "Region Descriptor 2, Word 2, offset: 0x428 ",
        handles.bport1,
        1064,
        4,
        read_32,
        bport1_ab_RGD2_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD2_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD2_WORD3",
        "Region Descriptor 2, Word 3, offset: 0x42c ",
        handles.bport1,
        1068,
        4,
        read_32,
        bport1_ab_RGD2_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD2_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD3_WORD0",
        "Region Descriptor 3, Word 0, offset: 0x430 ",
        handles.bport1,
        1072,
        4,
        read_32,
        bport1_ab_RGD3_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD3_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD3_WORD1",
        "Region Descriptor 3, Word 1, offset: 0x434 ",
        handles.bport1,
        1076,
        4,
        read_32,
        bport1_ab_RGD3_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD3_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD3_WORD2",
        "Region Descriptor 3, Word 2, offset: 0x438 ",
        handles.bport1,
        1080,
        4,
        read_32,
        bport1_ab_RGD3_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD3_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD3_WORD3",
        "Region Descriptor 3, Word 3, offset: 0x43c ",
        handles.bport1,
        1084,
        4,
        read_32,
        bport1_ab_RGD3_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD3_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD4_WORD0",
        "Region Descriptor 4, Word 0, offset: 0x440 ",
        handles.bport1,
        1088,
        4,
        read_32,
        bport1_ab_RGD4_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD4_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD4_WORD1",
        "Region Descriptor 4, Word 1, offset: 0x444 ",
        handles.bport1,
        1092,
        4,
        read_32,
        bport1_ab_RGD4_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD4_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD4_WORD2",
        "Region Descriptor 4, Word 2, offset: 0x448 ",
        handles.bport1,
        1096,
        4,
        read_32,
        bport1_ab_RGD4_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD4_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD4_WORD3",
        "Region Descriptor 4, Word 3, offset: 0x44c ",
        handles.bport1,
        1100,
        4,
        read_32,
        bport1_ab_RGD4_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD4_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD5_WORD0",
        "Region Descriptor 5, Word 0, offset: 0x450 ",
        handles.bport1,
        1104,
        4,
        read_32,
        bport1_ab_RGD5_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD5_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD5_WORD1",
        "Region Descriptor 5, Word 1, offset: 0x454 ",
        handles.bport1,
        1108,
        4,
        read_32,
        bport1_ab_RGD5_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD5_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD5_WORD2",
        "Region Descriptor 5, Word 2, offset: 0x458 ",
        handles.bport1,
        1112,
        4,
        read_32,
        bport1_ab_RGD5_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD5_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD5_WORD3",
        "Region Descriptor 5, Word 3, offset: 0x45c ",
        handles.bport1,
        1116,
        4,
        read_32,
        bport1_ab_RGD5_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD5_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD6_WORD0",
        "Region Descriptor 6, Word 0, offset: 0x460 ",
        handles.bport1,
        1120,
        4,
        read_32,
        bport1_ab_RGD6_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD6_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD6_WORD1",
        "Region Descriptor 6, Word 1, offset: 0x464 ",
        handles.bport1,
        1124,
        4,
        read_32,
        bport1_ab_RGD6_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD6_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD6_WORD2",
        "Region Descriptor 6, Word 2, offset: 0x468 ",
        handles.bport1,
        1128,
        4,
        read_32,
        bport1_ab_RGD6_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD6_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD6_WORD3",
        "Region Descriptor 6, Word 3, offset: 0x46c ",
        handles.bport1,
        1132,
        4,
        read_32,
        bport1_ab_RGD6_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD6_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD7_WORD0",
        "Region Descriptor 7, Word 0, offset: 0x470 ",
        handles.bport1,
        1136,
        4,
        read_32,
        bport1_ab_RGD7_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD7_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD7_WORD1",
        "Region Descriptor 7, Word 1, offset: 0x474 ",
        handles.bport1,
        1140,
        4,
        read_32,
        bport1_ab_RGD7_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD7_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD7_WORD2",
        "Region Descriptor 7, Word 2, offset: 0x478 ",
        handles.bport1,
        1144,
        4,
        read_32,
        bport1_ab_RGD7_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD7_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD7_WORD3",
        "Region Descriptor 7, Word 3, offset: 0x47c ",
        handles.bport1,
        1148,
        4,
        read_32,
        bport1_ab_RGD7_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD7_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD8_WORD0",
        "Region Descriptor 8, Word 0, offset: 0x480 ",
        handles.bport1,
        1152,
        4,
        read_32,
        bport1_ab_RGD8_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD8_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD8_WORD1",
        "Region Descriptor 8, Word 1, offset: 0x484 ",
        handles.bport1,
        1156,
        4,
        read_32,
        bport1_ab_RGD8_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD8_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD8_WORD2",
        "Region Descriptor 8, Word 2, offset: 0x488 ",
        handles.bport1,
        1160,
        4,
        read_32,
        bport1_ab_RGD8_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD8_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD8_WORD3",
        "Region Descriptor 8, Word 3, offset: 0x48c ",
        handles.bport1,
        1164,
        4,
        read_32,
        bport1_ab_RGD8_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD8_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD9_WORD0",
        "Region Descriptor 9, Word 0, offset: 0x490 ",
        handles.bport1,
        1168,
        4,
        read_32,
        bport1_ab_RGD9_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD9_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD9_WORD1",
        "Region Descriptor 9, Word 1, offset: 0x494 ",
        handles.bport1,
        1172,
        4,
        read_32,
        bport1_ab_RGD9_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD9_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD9_WORD2",
        "Region Descriptor 9, Word 2, offset: 0x498 ",
        handles.bport1,
        1176,
        4,
        read_32,
        bport1_ab_RGD9_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD9_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD9_WORD3",
        "Region Descriptor 9, Word 3, offset: 0x49c ",
        handles.bport1,
        1180,
        4,
        read_32,
        bport1_ab_RGD9_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD9_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD10_WORD0",
        "Region Descriptor 10, Word 0, offset: 0x4a0 ",
        handles.bport1,
        1184,
        4,
        read_32,
        bport1_ab_RGD10_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD10_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD10_WORD1",
        "Region Descriptor 10, Word 1, offset: 0x4a4 ",
        handles.bport1,
        1188,
        4,
        read_32,
        bport1_ab_RGD10_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD10_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD10_WORD2",
        "Region Descriptor 10, Word 2, offset: 0x4a8 ",
        handles.bport1,
        1192,
        4,
        read_32,
        bport1_ab_RGD10_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD10_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD10_WORD3",
        "Region Descriptor 10, Word 3, offset: 0x4ac ",
        handles.bport1,
        1196,
        4,
        read_32,
        bport1_ab_RGD10_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD10_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD11_WORD0",
        "Region Descriptor 11, Word 0, offset: 0x4b0 ",
        handles.bport1,
        1200,
        4,
        read_32,
        bport1_ab_RGD11_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD11_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD11_WORD1",
        "Region Descriptor 11, Word 1, offset: 0x4b4 ",
        handles.bport1,
        1204,
        4,
        read_32,
        bport1_ab_RGD11_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD11_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD11_WORD2",
        "Region Descriptor 11, Word 2, offset: 0x4b8 ",
        handles.bport1,
        1208,
        4,
        read_32,
        bport1_ab_RGD11_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD11_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD11_WORD3",
        "Region Descriptor 11, Word 3, offset: 0x4bc ",
        handles.bport1,
        1212,
        4,
        read_32,
        bport1_ab_RGD11_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD11_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD12_WORD0",
        "Region Descriptor 12, Word 0, offset: 0x4c0 ",
        handles.bport1,
        1216,
        4,
        read_32,
        bport1_ab_RGD12_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD12_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD12_WORD1",
        "Region Descriptor 12, Word 1, offset: 0x4c4 ",
        handles.bport1,
        1220,
        4,
        read_32,
        bport1_ab_RGD12_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD12_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD12_WORD2",
        "Region Descriptor 12, Word 2, offset: 0x4c8 ",
        handles.bport1,
        1224,
        4,
        read_32,
        bport1_ab_RGD12_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD12_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD12_WORD3",
        "Region Descriptor 12, Word 3, offset: 0x4cc ",
        handles.bport1,
        1228,
        4,
        read_32,
        bport1_ab_RGD12_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD12_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD13_WORD0",
        "Region Descriptor 13, Word 0, offset: 0x4d0 ",
        handles.bport1,
        1232,
        4,
        read_32,
        bport1_ab_RGD13_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD13_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD13_WORD1",
        "Region Descriptor 13, Word 1, offset: 0x4d4 ",
        handles.bport1,
        1236,
        4,
        read_32,
        bport1_ab_RGD13_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD13_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD13_WORD2",
        "Region Descriptor 13, Word 2, offset: 0x4d8 ",
        handles.bport1,
        1240,
        4,
        read_32,
        bport1_ab_RGD13_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD13_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD13_WORD3",
        "Region Descriptor 13, Word 3, offset: 0x4dc ",
        handles.bport1,
        1244,
        4,
        read_32,
        bport1_ab_RGD13_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD13_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD14_WORD0",
        "Region Descriptor 14, Word 0, offset: 0x4e0 ",
        handles.bport1,
        1248,
        4,
        read_32,
        bport1_ab_RGD14_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD14_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD14_WORD1",
        "Region Descriptor 14, Word 1, offset: 0x4e4 ",
        handles.bport1,
        1252,
        4,
        read_32,
        bport1_ab_RGD14_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD14_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD14_WORD2",
        "Region Descriptor 14, Word 2, offset: 0x4e8 ",
        handles.bport1,
        1256,
        4,
        read_32,
        bport1_ab_RGD14_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD14_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD14_WORD3",
        "Region Descriptor 14, Word 3, offset: 0x4ec ",
        handles.bport1,
        1260,
        4,
        read_32,
        bport1_ab_RGD14_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD14_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGD15_WORD0",
        "Region Descriptor 15, Word 0, offset: 0x4f0 ",
        handles.bport1,
        1264,
        4,
        read_32,
        bport1_ab_RGD15_WORD0_maskWrite,
        view32,
        &(bport1_ab_data.RGD15_WORD0.value),
        True
    );
    ppmCreateRegister("ab_RGD15_WORD1",
        "Region Descriptor 15, Word 1, offset: 0x4f4 ",
        handles.bport1,
        1268,
        4,
        read_32,
        bport1_ab_RGD15_WORD1_maskWrite,
        view32,
        &(bport1_ab_data.RGD15_WORD1.value),
        True
    );
    ppmCreateRegister("ab_RGD15_WORD2",
        "Region Descriptor 15, Word 2, offset: 0x4f8 ",
        handles.bport1,
        1272,
        4,
        read_32,
        bport1_ab_RGD15_WORD2_maskWrite,
        view32,
        &(bport1_ab_data.RGD15_WORD2.value),
        True
    );
    ppmCreateRegister("ab_RGD15_WORD3",
        "Region Descriptor 15, Word 3, offset: 0x4fc ",
        handles.bport1,
        1276,
        4,
        read_32,
        bport1_ab_RGD15_WORD3_maskWrite,
        view32,
        &(bport1_ab_data.RGD15_WORD3.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC0",
        "Region Descriptor Alternate Access Control 0, offset: 0x800",
        handles.bport1,
        2048,
        4,
        read_32,
        bport1_ab_RGDAAC0_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC0.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC1",
        "Region Descriptor Alternate Access Control 1, offset: 0x804",
        handles.bport1,
        2052,
        4,
        read_32,
        bport1_ab_RGDAAC1_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC1.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC2",
        "Region Descriptor Alternate Access Control 2, offset: 0x808",
        handles.bport1,
        2056,
        4,
        read_32,
        bport1_ab_RGDAAC2_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC2.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC3",
        "Region Descriptor Alternate Access Control 3, offset: 0x80c",
        handles.bport1,
        2060,
        4,
        read_32,
        bport1_ab_RGDAAC3_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC3.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC4",
        "Region Descriptor Alternate Access Control 4, offset: 0x810",
        handles.bport1,
        2064,
        4,
        read_32,
        bport1_ab_RGDAAC4_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC4.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC5",
        "Region Descriptor Alternate Access Control 5, offset: 0x814",
        handles.bport1,
        2068,
        4,
        read_32,
        bport1_ab_RGDAAC5_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC5.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC6",
        "Region Descriptor Alternate Access Control 6, offset: 0x818",
        handles.bport1,
        2072,
        4,
        read_32,
        bport1_ab_RGDAAC6_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC6.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC7",
        "Region Descriptor Alternate Access Control 7, offset: 0x81c",
        handles.bport1,
        2076,
        4,
        read_32,
        bport1_ab_RGDAAC7_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC7.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC8",
        "Region Descriptor Alternate Access Control 8, offset: 0x820",
        handles.bport1,
        2080,
        4,
        read_32,
        bport1_ab_RGDAAC8_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC8.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC9",
        "Region Descriptor Alternate Access Control 9, offset: 0x824",
        handles.bport1,
        2084,
        4,
        read_32,
        bport1_ab_RGDAAC9_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC9.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC10",
        "Region Descriptor Alternate Access Control 10, offset: 0x828",
        handles.bport1,
        2088,
        4,
        read_32,
        bport1_ab_RGDAAC10_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC10.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC11",
        "Region Descriptor Alternate Access Control 11, offset: 0x82c",
        handles.bport1,
        2092,
        4,
        read_32,
        bport1_ab_RGDAAC11_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC11.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC12",
        "Region Descriptor Alternate Access Control 12, offset: 0x830",
        handles.bport1,
        2096,
        4,
        read_32,
        bport1_ab_RGDAAC12_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC12.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC13",
        "Region Descriptor Alternate Access Control 13, offset: 0x834",
        handles.bport1,
        2100,
        4,
        read_32,
        bport1_ab_RGDAAC13_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC13.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC14",
        "Region Descriptor Alternate Access Control 14, offset: 0x838",
        handles.bport1,
        2104,
        4,
        read_32,
        bport1_ab_RGDAAC14_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC14.value),
        True
    );
    ppmCreateRegister("ab_RGDAAC15",
        "Region Descriptor Alternate Access Control 15, offset: 0x83c",
        handles.bport1,
        2108,
        4,
        read_32,
        bport1_ab_RGDAAC15_maskWrite,
        view32,
        &(bport1_ab_data.RGDAAC15.value),
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
        bport1_ab_data.RGDAAC15.value = 0x0;
        bport1_ab_data.RGDAAC14.value = 0x0;
        bport1_ab_data.RGDAAC13.value = 0x0;
        bport1_ab_data.RGDAAC12.value = 0x0;
        bport1_ab_data.RGDAAC11.value = 0x0;
        bport1_ab_data.RGDAAC10.value = 0x0;
        bport1_ab_data.RGDAAC9.value = 0x0;
        bport1_ab_data.RGDAAC8.value = 0x0;
        bport1_ab_data.RGDAAC7.value = 0x0;
        bport1_ab_data.RGDAAC6.value = 0x0;
        bport1_ab_data.RGDAAC5.value = 0x0;
        bport1_ab_data.RGDAAC4.value = 0x0;
        bport1_ab_data.RGDAAC3.value = 0x0;
        bport1_ab_data.RGDAAC2.value = 0x0;
        bport1_ab_data.RGDAAC1.value = 0x0;
        bport1_ab_data.RGDAAC0.value = 0x0;
        bport1_ab_data.RGD15_WORD3.value = 0x0;
        bport1_ab_data.RGD15_WORD2.value = 0x0;
        bport1_ab_data.RGD15_WORD1.value = 0x1f;
        bport1_ab_data.RGD15_WORD0.value = 0x0;
        bport1_ab_data.RGD14_WORD3.value = 0x0;
        bport1_ab_data.RGD14_WORD2.value = 0x0;
        bport1_ab_data.RGD14_WORD1.value = 0x1f;
        bport1_ab_data.RGD14_WORD0.value = 0x0;
        bport1_ab_data.RGD13_WORD3.value = 0x0;
        bport1_ab_data.RGD13_WORD2.value = 0x0;
        bport1_ab_data.RGD13_WORD1.value = 0x1f;
        bport1_ab_data.RGD13_WORD0.value = 0x0;
        bport1_ab_data.RGD12_WORD3.value = 0x0;
        bport1_ab_data.RGD12_WORD2.value = 0x0;
        bport1_ab_data.RGD12_WORD1.value = 0x1f;
        bport1_ab_data.RGD12_WORD0.value = 0x0;
        bport1_ab_data.RGD11_WORD3.value = 0x0;
        bport1_ab_data.RGD11_WORD2.value = 0x0;
        bport1_ab_data.RGD11_WORD1.value = 0x1f;
        bport1_ab_data.RGD11_WORD0.value = 0x0;
        bport1_ab_data.RGD10_WORD3.value = 0x0;
        bport1_ab_data.RGD10_WORD2.value = 0x0;
        bport1_ab_data.RGD10_WORD1.value = 0x1f;
        bport1_ab_data.RGD10_WORD0.value = 0x0;
        bport1_ab_data.RGD9_WORD3.value = 0x0;
        bport1_ab_data.RGD9_WORD2.value = 0x0;
        bport1_ab_data.RGD9_WORD1.value = 0x1f;
        bport1_ab_data.RGD9_WORD0.value = 0x0;
        bport1_ab_data.RGD8_WORD3.value = 0x0;
        bport1_ab_data.RGD8_WORD2.value = 0x0;
        bport1_ab_data.RGD8_WORD1.value = 0x1f;
        bport1_ab_data.RGD8_WORD0.value = 0x0;
        bport1_ab_data.RGD7_WORD3.value = 0x0;
        bport1_ab_data.RGD7_WORD2.value = 0x0;
        bport1_ab_data.RGD7_WORD1.value = 0x1f;
        bport1_ab_data.RGD7_WORD0.value = 0x0;
        bport1_ab_data.RGD6_WORD3.value = 0x0;
        bport1_ab_data.RGD6_WORD2.value = 0x0;
        bport1_ab_data.RGD6_WORD1.value = 0x1f;
        bport1_ab_data.RGD6_WORD0.value = 0x0;
        bport1_ab_data.RGD5_WORD3.value = 0x0;
        bport1_ab_data.RGD5_WORD2.value = 0x0;
        bport1_ab_data.RGD5_WORD1.value = 0x1f;
        bport1_ab_data.RGD5_WORD0.value = 0x0;
        bport1_ab_data.RGD4_WORD3.value = 0x0;
        bport1_ab_data.RGD4_WORD2.value = 0x0;
        bport1_ab_data.RGD4_WORD1.value = 0x1f;
        bport1_ab_data.RGD4_WORD0.value = 0x0;
        bport1_ab_data.RGD3_WORD3.value = 0x0;
        bport1_ab_data.RGD3_WORD2.value = 0x0;
        bport1_ab_data.RGD3_WORD1.value = 0x1f;
        bport1_ab_data.RGD3_WORD0.value = 0x0;
        bport1_ab_data.RGD2_WORD3.value = 0x0;
        bport1_ab_data.RGD2_WORD2.value = 0x0;
        bport1_ab_data.RGD2_WORD1.value = 0x1f;
        bport1_ab_data.RGD2_WORD0.value = 0x0;
        bport1_ab_data.RGD1_WORD3.value = 0x0;
        bport1_ab_data.RGD1_WORD2.value = 0x0;
        bport1_ab_data.RGD1_WORD1.value = 0x1f;
        bport1_ab_data.RGD1_WORD0.value = 0x0;
        bport1_ab_data.RGD0_WORD3.value = 0x0;
        bport1_ab_data.RGD0_WORD2.value = 0x0;
        bport1_ab_data.RGD0_WORD1.value = 0x1f;
        bport1_ab_data.RGD0_WORD0.value = 0x0;
        bport1_ab_data.CESR.value = 0x818201;
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

