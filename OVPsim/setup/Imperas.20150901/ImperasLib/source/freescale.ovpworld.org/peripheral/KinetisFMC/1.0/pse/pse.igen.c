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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFMC", "Example");
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

static PPM_WRITE_CB(bport1_ab_DATAW0S0LM_maskWrite) {
    bport1_ab_data.DATAW0S0LM.value = (bport1_ab_data.DATAW0S0LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S0ML_maskWrite) {
    bport1_ab_data.DATAW0S0ML.value = (bport1_ab_data.DATAW0S0ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S0MU_maskWrite) {
    bport1_ab_data.DATAW0S0MU.value = (bport1_ab_data.DATAW0S0MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S0UM_maskWrite) {
    bport1_ab_data.DATAW0S0UM.value = (bport1_ab_data.DATAW0S0UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1LM_maskWrite) {
    bport1_ab_data.DATAW0S1LM.value = (bport1_ab_data.DATAW0S1LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1ML_maskWrite) {
    bport1_ab_data.DATAW0S1ML.value = (bport1_ab_data.DATAW0S1ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1MU_maskWrite) {
    bport1_ab_data.DATAW0S1MU.value = (bport1_ab_data.DATAW0S1MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1UM_maskWrite) {
    bport1_ab_data.DATAW0S1UM.value = (bport1_ab_data.DATAW0S1UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2LM_maskWrite) {
    bport1_ab_data.DATAW0S2LM.value = (bport1_ab_data.DATAW0S2LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2ML_maskWrite) {
    bport1_ab_data.DATAW0S2ML.value = (bport1_ab_data.DATAW0S2ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2MU_maskWrite) {
    bport1_ab_data.DATAW0S2MU.value = (bport1_ab_data.DATAW0S2MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2UM_maskWrite) {
    bport1_ab_data.DATAW0S2UM.value = (bport1_ab_data.DATAW0S2UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3LM_maskWrite) {
    bport1_ab_data.DATAW0S3LM.value = (bport1_ab_data.DATAW0S3LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3ML_maskWrite) {
    bport1_ab_data.DATAW0S3ML.value = (bport1_ab_data.DATAW0S3ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3MU_maskWrite) {
    bport1_ab_data.DATAW0S3MU.value = (bport1_ab_data.DATAW0S3MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3UM_maskWrite) {
    bport1_ab_data.DATAW0S3UM.value = (bport1_ab_data.DATAW0S3UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0LM_maskWrite) {
    bport1_ab_data.DATAW1S0LM.value = (bport1_ab_data.DATAW1S0LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0ML_maskWrite) {
    bport1_ab_data.DATAW1S0ML.value = (bport1_ab_data.DATAW1S0ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0MU_maskWrite) {
    bport1_ab_data.DATAW1S0MU.value = (bport1_ab_data.DATAW1S0MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0UM_maskWrite) {
    bport1_ab_data.DATAW1S0UM.value = (bport1_ab_data.DATAW1S0UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1LM_maskWrite) {
    bport1_ab_data.DATAW1S1LM.value = (bport1_ab_data.DATAW1S1LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1ML_maskWrite) {
    bport1_ab_data.DATAW1S1ML.value = (bport1_ab_data.DATAW1S1ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1MU_maskWrite) {
    bport1_ab_data.DATAW1S1MU.value = (bport1_ab_data.DATAW1S1MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1UM_maskWrite) {
    bport1_ab_data.DATAW1S1UM.value = (bport1_ab_data.DATAW1S1UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2LM_maskWrite) {
    bport1_ab_data.DATAW1S2LM.value = (bport1_ab_data.DATAW1S2LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2ML_maskWrite) {
    bport1_ab_data.DATAW1S2ML.value = (bport1_ab_data.DATAW1S2ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2MU_maskWrite) {
    bport1_ab_data.DATAW1S2MU.value = (bport1_ab_data.DATAW1S2MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2UM_maskWrite) {
    bport1_ab_data.DATAW1S2UM.value = (bport1_ab_data.DATAW1S2UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3LM_maskWrite) {
    bport1_ab_data.DATAW1S3LM.value = (bport1_ab_data.DATAW1S3LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3ML_maskWrite) {
    bport1_ab_data.DATAW1S3ML.value = (bport1_ab_data.DATAW1S3ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3MU_maskWrite) {
    bport1_ab_data.DATAW1S3MU.value = (bport1_ab_data.DATAW1S3MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3UM_maskWrite) {
    bport1_ab_data.DATAW1S3UM.value = (bport1_ab_data.DATAW1S3UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0LM_maskWrite) {
    bport1_ab_data.DATAW2S0LM.value = (bport1_ab_data.DATAW2S0LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0ML_maskWrite) {
    bport1_ab_data.DATAW2S0ML.value = (bport1_ab_data.DATAW2S0ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0MU_maskWrite) {
    bport1_ab_data.DATAW2S0MU.value = (bport1_ab_data.DATAW2S0MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0UM_maskWrite) {
    bport1_ab_data.DATAW2S0UM.value = (bport1_ab_data.DATAW2S0UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1LM_maskWrite) {
    bport1_ab_data.DATAW2S1LM.value = (bport1_ab_data.DATAW2S1LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1ML_maskWrite) {
    bport1_ab_data.DATAW2S1ML.value = (bport1_ab_data.DATAW2S1ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1MU_maskWrite) {
    bport1_ab_data.DATAW2S1MU.value = (bport1_ab_data.DATAW2S1MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1UM_maskWrite) {
    bport1_ab_data.DATAW2S1UM.value = (bport1_ab_data.DATAW2S1UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2LM_maskWrite) {
    bport1_ab_data.DATAW2S2LM.value = (bport1_ab_data.DATAW2S2LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2ML_maskWrite) {
    bport1_ab_data.DATAW2S2ML.value = (bport1_ab_data.DATAW2S2ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2MU_maskWrite) {
    bport1_ab_data.DATAW2S2MU.value = (bport1_ab_data.DATAW2S2MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2UM_maskWrite) {
    bport1_ab_data.DATAW2S2UM.value = (bport1_ab_data.DATAW2S2UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3LM_maskWrite) {
    bport1_ab_data.DATAW2S3LM.value = (bport1_ab_data.DATAW2S3LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3ML_maskWrite) {
    bport1_ab_data.DATAW2S3ML.value = (bport1_ab_data.DATAW2S3ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3MU_maskWrite) {
    bport1_ab_data.DATAW2S3MU.value = (bport1_ab_data.DATAW2S3MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3UM_maskWrite) {
    bport1_ab_data.DATAW2S3UM.value = (bport1_ab_data.DATAW2S3UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0LM_maskWrite) {
    bport1_ab_data.DATAW3S0LM.value = (bport1_ab_data.DATAW3S0LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0ML_maskWrite) {
    bport1_ab_data.DATAW3S0ML.value = (bport1_ab_data.DATAW3S0ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0MU_maskWrite) {
    bport1_ab_data.DATAW3S0MU.value = (bport1_ab_data.DATAW3S0MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0UM_maskWrite) {
    bport1_ab_data.DATAW3S0UM.value = (bport1_ab_data.DATAW3S0UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1LM_maskWrite) {
    bport1_ab_data.DATAW3S1LM.value = (bport1_ab_data.DATAW3S1LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1ML_maskWrite) {
    bport1_ab_data.DATAW3S1ML.value = (bport1_ab_data.DATAW3S1ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1MU_maskWrite) {
    bport1_ab_data.DATAW3S1MU.value = (bport1_ab_data.DATAW3S1MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1UM_maskWrite) {
    bport1_ab_data.DATAW3S1UM.value = (bport1_ab_data.DATAW3S1UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2LM_maskWrite) {
    bport1_ab_data.DATAW3S2LM.value = (bport1_ab_data.DATAW3S2LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2ML_maskWrite) {
    bport1_ab_data.DATAW3S2ML.value = (bport1_ab_data.DATAW3S2ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2MU_maskWrite) {
    bport1_ab_data.DATAW3S2MU.value = (bport1_ab_data.DATAW3S2MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2UM_maskWrite) {
    bport1_ab_data.DATAW3S2UM.value = (bport1_ab_data.DATAW3S2UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3LM_maskWrite) {
    bport1_ab_data.DATAW3S3LM.value = (bport1_ab_data.DATAW3S3LM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3ML_maskWrite) {
    bport1_ab_data.DATAW3S3ML.value = (bport1_ab_data.DATAW3S3ML.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3MU_maskWrite) {
    bport1_ab_data.DATAW3S3MU.value = (bport1_ab_data.DATAW3S3MU.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3UM_maskWrite) {
    bport1_ab_data.DATAW3S3UM.value = (bport1_ab_data.DATAW3S3UM.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_PFAPR_maskWrite) {
    bport1_ab_data.PFAPR.value = (bport1_ab_data.PFAPR.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_PFB01CR_maskWrite) {
    bport1_ab_data.PFB01CR.value = (bport1_ab_data.PFB01CR.value & 0xf0f7ff00) | (data & 0xf0800ff);
}

static PPM_WRITE_CB(bport1_ab_PFB23CR_maskWrite) {
    bport1_ab_data.PFB23CR.value = (bport1_ab_data.PFB23CR.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S0_maskWrite) {
    bport1_ab_data.TAGVDW0S0.value = (bport1_ab_data.TAGVDW0S0.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S1_maskWrite) {
    bport1_ab_data.TAGVDW0S1.value = (bport1_ab_data.TAGVDW0S1.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S2_maskWrite) {
    bport1_ab_data.TAGVDW0S2.value = (bport1_ab_data.TAGVDW0S2.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S3_maskWrite) {
    bport1_ab_data.TAGVDW0S3.value = (bport1_ab_data.TAGVDW0S3.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S0_maskWrite) {
    bport1_ab_data.TAGVDW1S0.value = (bport1_ab_data.TAGVDW1S0.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S1_maskWrite) {
    bport1_ab_data.TAGVDW1S1.value = (bport1_ab_data.TAGVDW1S1.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S2_maskWrite) {
    bport1_ab_data.TAGVDW1S2.value = (bport1_ab_data.TAGVDW1S2.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S3_maskWrite) {
    bport1_ab_data.TAGVDW1S3.value = (bport1_ab_data.TAGVDW1S3.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S0_maskWrite) {
    bport1_ab_data.TAGVDW2S0.value = (bport1_ab_data.TAGVDW2S0.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S1_maskWrite) {
    bport1_ab_data.TAGVDW2S1.value = (bport1_ab_data.TAGVDW2S1.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S2_maskWrite) {
    bport1_ab_data.TAGVDW2S2.value = (bport1_ab_data.TAGVDW2S2.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S3_maskWrite) {
    bport1_ab_data.TAGVDW2S3.value = (bport1_ab_data.TAGVDW2S3.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S0_maskWrite) {
    bport1_ab_data.TAGVDW3S0.value = (bport1_ab_data.TAGVDW3S0.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S1_maskWrite) {
    bport1_ab_data.TAGVDW3S1.value = (bport1_ab_data.TAGVDW3S1.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S2_maskWrite) {
    bport1_ab_data.TAGVDW3S2.value = (bport1_ab_data.TAGVDW3S2.value & 0xfff0003e) | (data & 0xfffc1);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S3_maskWrite) {
    bport1_ab_data.TAGVDW3S3.value = (bport1_ab_data.TAGVDW3S3.value & 0xfff0003e) | (data & 0xfffc1);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_PFAPR",
        "Flash Access Protection Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_PFAPR_maskWrite,
        view32,
        &(bport1_ab_data.PFAPR.value),
        True
    );
    ppmCreateRegister("ab_PFB01CR",
        "Flash Bank 0-1 Control Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_PFB01CR_maskWrite,
        view32,
        &(bport1_ab_data.PFB01CR.value),
        True
    );
    ppmCreateRegister("ab_PFB23CR",
        "Flash Bank 2-3 Control Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_PFB23CR_maskWrite,
        view32,
        &(bport1_ab_data.PFB23CR.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW0S0",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        256,
        4,
        read_32,
        bport1_ab_TAGVDW0S0_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW0S0.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW0S1",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        260,
        4,
        read_32,
        bport1_ab_TAGVDW0S1_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW0S1.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW0S2",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        264,
        4,
        read_32,
        bport1_ab_TAGVDW0S2_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW0S2.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW0S3",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        268,
        4,
        read_32,
        bport1_ab_TAGVDW0S3_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW0S3.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW1S0",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        272,
        4,
        read_32,
        bport1_ab_TAGVDW1S0_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW1S0.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW1S1",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        276,
        4,
        read_32,
        bport1_ab_TAGVDW1S1_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW1S1.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW1S2",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        280,
        4,
        read_32,
        bport1_ab_TAGVDW1S2_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW1S2.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW1S3",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        284,
        4,
        read_32,
        bport1_ab_TAGVDW1S3_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW1S3.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW2S0",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        288,
        4,
        read_32,
        bport1_ab_TAGVDW2S0_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW2S0.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW2S1",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        292,
        4,
        read_32,
        bport1_ab_TAGVDW2S1_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW2S1.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW2S2",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        296,
        4,
        read_32,
        bport1_ab_TAGVDW2S2_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW2S2.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW2S3",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        300,
        4,
        read_32,
        bport1_ab_TAGVDW2S3_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW2S3.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW3S0",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        304,
        4,
        read_32,
        bport1_ab_TAGVDW3S0_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW3S0.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW3S1",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        308,
        4,
        read_32,
        bport1_ab_TAGVDW3S1_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW3S1.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW3S2",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        312,
        4,
        read_32,
        bport1_ab_TAGVDW3S2_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW3S2.value),
        True
    );
    ppmCreateRegister("ab_TAGVDW3S3",
        "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
        handles.bport1,
        316,
        4,
        read_32,
        bport1_ab_TAGVDW3S3_maskWrite,
        view32,
        &(bport1_ab_data.TAGVDW3S3.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S0UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        512,
        4,
        read_32,
        bport1_ab_DATAW0S0UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S0UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S0MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        516,
        4,
        read_32,
        bport1_ab_DATAW0S0MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S0MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S0ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        520,
        4,
        read_32,
        bport1_ab_DATAW0S0ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S0ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S0LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        524,
        4,
        read_32,
        bport1_ab_DATAW0S0LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S0LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S1UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        528,
        4,
        read_32,
        bport1_ab_DATAW0S1UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S1UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S1MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        532,
        4,
        read_32,
        bport1_ab_DATAW0S1MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S1MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S1ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        536,
        4,
        read_32,
        bport1_ab_DATAW0S1ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S1ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S1LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        540,
        4,
        read_32,
        bport1_ab_DATAW0S1LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S1LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S2UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        544,
        4,
        read_32,
        bport1_ab_DATAW0S2UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S2UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S2MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        548,
        4,
        read_32,
        bport1_ab_DATAW0S2MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S2MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S2ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        552,
        4,
        read_32,
        bport1_ab_DATAW0S2ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S2ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S2LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        556,
        4,
        read_32,
        bport1_ab_DATAW0S2LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S2LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S3UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        560,
        4,
        read_32,
        bport1_ab_DATAW0S3UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S3UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S3MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        564,
        4,
        read_32,
        bport1_ab_DATAW0S3MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S3MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S3ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        568,
        4,
        read_32,
        bport1_ab_DATAW0S3ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S3ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW0S3LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        572,
        4,
        read_32,
        bport1_ab_DATAW0S3LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW0S3LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S0UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        576,
        4,
        read_32,
        bport1_ab_DATAW1S0UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S0UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S0MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        580,
        4,
        read_32,
        bport1_ab_DATAW1S0MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S0MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S0ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        584,
        4,
        read_32,
        bport1_ab_DATAW1S0ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S0ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S0LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        588,
        4,
        read_32,
        bport1_ab_DATAW1S0LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S0LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S1UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        592,
        4,
        read_32,
        bport1_ab_DATAW1S1UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S1UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S1MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        596,
        4,
        read_32,
        bport1_ab_DATAW1S1MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S1MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S1ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        600,
        4,
        read_32,
        bport1_ab_DATAW1S1ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S1ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S1LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        604,
        4,
        read_32,
        bport1_ab_DATAW1S1LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S1LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S2UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        608,
        4,
        read_32,
        bport1_ab_DATAW1S2UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S2UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S2MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        612,
        4,
        read_32,
        bport1_ab_DATAW1S2MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S2MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S2ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        616,
        4,
        read_32,
        bport1_ab_DATAW1S2ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S2ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S2LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        620,
        4,
        read_32,
        bport1_ab_DATAW1S2LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S2LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S3UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        624,
        4,
        read_32,
        bport1_ab_DATAW1S3UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S3UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S3MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        628,
        4,
        read_32,
        bport1_ab_DATAW1S3MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S3MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S3ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        632,
        4,
        read_32,
        bport1_ab_DATAW1S3ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S3ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW1S3LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        636,
        4,
        read_32,
        bport1_ab_DATAW1S3LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW1S3LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S0UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        640,
        4,
        read_32,
        bport1_ab_DATAW2S0UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S0UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S0MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        644,
        4,
        read_32,
        bport1_ab_DATAW2S0MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S0MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S0ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        648,
        4,
        read_32,
        bport1_ab_DATAW2S0ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S0ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S0LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        652,
        4,
        read_32,
        bport1_ab_DATAW2S0LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S0LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S1UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        656,
        4,
        read_32,
        bport1_ab_DATAW2S1UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S1UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S1MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        660,
        4,
        read_32,
        bport1_ab_DATAW2S1MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S1MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S1ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        664,
        4,
        read_32,
        bport1_ab_DATAW2S1ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S1ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S1LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        668,
        4,
        read_32,
        bport1_ab_DATAW2S1LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S1LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S2UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        672,
        4,
        read_32,
        bport1_ab_DATAW2S2UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S2UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S2MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        676,
        4,
        read_32,
        bport1_ab_DATAW2S2MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S2MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S2ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        680,
        4,
        read_32,
        bport1_ab_DATAW2S2ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S2ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S2LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        684,
        4,
        read_32,
        bport1_ab_DATAW2S2LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S2LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S3UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        688,
        4,
        read_32,
        bport1_ab_DATAW2S3UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S3UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S3MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        692,
        4,
        read_32,
        bport1_ab_DATAW2S3MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S3MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S3ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        696,
        4,
        read_32,
        bport1_ab_DATAW2S3ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S3ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW2S3LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        700,
        4,
        read_32,
        bport1_ab_DATAW2S3LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW2S3LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S0UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        704,
        4,
        read_32,
        bport1_ab_DATAW3S0UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S0UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S0MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        708,
        4,
        read_32,
        bport1_ab_DATAW3S0MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S0MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S0ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        712,
        4,
        read_32,
        bport1_ab_DATAW3S0ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S0ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S0LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        716,
        4,
        read_32,
        bport1_ab_DATAW3S0LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S0LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S1UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        720,
        4,
        read_32,
        bport1_ab_DATAW3S1UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S1UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S1MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        724,
        4,
        read_32,
        bport1_ab_DATAW3S1MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S1MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S1ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        728,
        4,
        read_32,
        bport1_ab_DATAW3S1ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S1ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S1LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        732,
        4,
        read_32,
        bport1_ab_DATAW3S1LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S1LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S2UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        736,
        4,
        read_32,
        bport1_ab_DATAW3S2UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S2UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S2MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        740,
        4,
        read_32,
        bport1_ab_DATAW3S2MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S2MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S2ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        744,
        4,
        read_32,
        bport1_ab_DATAW3S2ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S2ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S2LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        748,
        4,
        read_32,
        bport1_ab_DATAW3S2LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S2LM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S3UM",
        "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        752,
        4,
        read_32,
        bport1_ab_DATAW3S3UM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S3UM.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S3MU",
        "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        756,
        4,
        read_32,
        bport1_ab_DATAW3S3MU_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S3MU.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S3ML",
        "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        760,
        4,
        read_32,
        bport1_ab_DATAW3S3ML_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S3ML.value),
        True
    );
    ppmCreateRegister("ab_DATAW3S3LM",
        "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
        handles.bport1,
        764,
        4,
        read_32,
        bport1_ab_DATAW3S3LM_maskWrite,
        view32,
        &(bport1_ab_data.DATAW3S3LM.value),
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
        bport1_ab_data.DATAW3S3LM.value = 0x0;
        bport1_ab_data.DATAW3S3ML.value = 0x0;
        bport1_ab_data.DATAW3S3MU.value = 0x0;
        bport1_ab_data.DATAW3S3UM.value = 0x0;
        bport1_ab_data.DATAW3S2LM.value = 0x0;
        bport1_ab_data.DATAW3S2ML.value = 0x0;
        bport1_ab_data.DATAW3S2MU.value = 0x0;
        bport1_ab_data.DATAW3S2UM.value = 0x0;
        bport1_ab_data.DATAW3S1LM.value = 0x0;
        bport1_ab_data.DATAW3S1ML.value = 0x0;
        bport1_ab_data.DATAW3S1MU.value = 0x0;
        bport1_ab_data.DATAW3S1UM.value = 0x0;
        bport1_ab_data.DATAW3S0LM.value = 0x0;
        bport1_ab_data.DATAW3S0ML.value = 0x0;
        bport1_ab_data.DATAW3S0MU.value = 0x0;
        bport1_ab_data.DATAW3S0UM.value = 0x0;
        bport1_ab_data.DATAW2S3LM.value = 0x0;
        bport1_ab_data.DATAW2S3ML.value = 0x0;
        bport1_ab_data.DATAW2S3MU.value = 0x0;
        bport1_ab_data.DATAW2S3UM.value = 0x0;
        bport1_ab_data.DATAW2S2LM.value = 0x0;
        bport1_ab_data.DATAW2S2ML.value = 0x0;
        bport1_ab_data.DATAW2S2MU.value = 0x0;
        bport1_ab_data.DATAW2S2UM.value = 0x0;
        bport1_ab_data.DATAW2S1LM.value = 0x0;
        bport1_ab_data.DATAW2S1ML.value = 0x0;
        bport1_ab_data.DATAW2S1MU.value = 0x0;
        bport1_ab_data.DATAW2S1UM.value = 0x0;
        bport1_ab_data.DATAW2S0LM.value = 0x0;
        bport1_ab_data.DATAW2S0ML.value = 0x0;
        bport1_ab_data.DATAW2S0MU.value = 0x0;
        bport1_ab_data.DATAW2S0UM.value = 0x0;
        bport1_ab_data.DATAW1S3LM.value = 0x0;
        bport1_ab_data.DATAW1S3ML.value = 0x0;
        bport1_ab_data.DATAW1S3MU.value = 0x0;
        bport1_ab_data.DATAW1S3UM.value = 0x0;
        bport1_ab_data.DATAW1S2LM.value = 0x0;
        bport1_ab_data.DATAW1S2ML.value = 0x0;
        bport1_ab_data.DATAW1S2MU.value = 0x0;
        bport1_ab_data.DATAW1S2UM.value = 0x0;
        bport1_ab_data.DATAW1S1LM.value = 0x0;
        bport1_ab_data.DATAW1S1ML.value = 0x0;
        bport1_ab_data.DATAW1S1MU.value = 0x0;
        bport1_ab_data.DATAW1S1UM.value = 0x0;
        bport1_ab_data.DATAW1S0LM.value = 0x0;
        bport1_ab_data.DATAW1S0ML.value = 0x0;
        bport1_ab_data.DATAW1S0MU.value = 0x0;
        bport1_ab_data.DATAW1S0UM.value = 0x0;
        bport1_ab_data.DATAW0S3LM.value = 0x0;
        bport1_ab_data.DATAW0S3ML.value = 0x0;
        bport1_ab_data.DATAW0S3MU.value = 0x0;
        bport1_ab_data.DATAW0S3UM.value = 0x0;
        bport1_ab_data.DATAW0S2LM.value = 0x0;
        bport1_ab_data.DATAW0S2ML.value = 0x0;
        bport1_ab_data.DATAW0S2MU.value = 0x0;
        bport1_ab_data.DATAW0S2UM.value = 0x0;
        bport1_ab_data.DATAW0S1LM.value = 0x0;
        bport1_ab_data.DATAW0S1ML.value = 0x0;
        bport1_ab_data.DATAW0S1MU.value = 0x0;
        bport1_ab_data.DATAW0S1UM.value = 0x0;
        bport1_ab_data.DATAW0S0LM.value = 0x0;
        bport1_ab_data.DATAW0S0ML.value = 0x0;
        bport1_ab_data.DATAW0S0MU.value = 0x0;
        bport1_ab_data.DATAW0S0UM.value = 0x0;
        bport1_ab_data.TAGVDW3S3.value = 0x0;
        bport1_ab_data.TAGVDW3S2.value = 0x0;
        bport1_ab_data.TAGVDW3S1.value = 0x0;
        bport1_ab_data.TAGVDW3S0.value = 0x0;
        bport1_ab_data.TAGVDW2S3.value = 0x0;
        bport1_ab_data.TAGVDW2S2.value = 0x0;
        bport1_ab_data.TAGVDW2S1.value = 0x0;
        bport1_ab_data.TAGVDW2S0.value = 0x0;
        bport1_ab_data.TAGVDW1S3.value = 0x0;
        bport1_ab_data.TAGVDW1S2.value = 0x0;
        bport1_ab_data.TAGVDW1S1.value = 0x0;
        bport1_ab_data.TAGVDW1S0.value = 0x0;
        bport1_ab_data.TAGVDW0S3.value = 0x0;
        bport1_ab_data.TAGVDW0S2.value = 0x0;
        bport1_ab_data.TAGVDW0S1.value = 0x0;
        bport1_ab_data.TAGVDW0S0.value = 0x0;
        bport1_ab_data.PFB23CR.value = 0x3004001f;
        bport1_ab_data.PFB01CR.value = 0x3004001f;
        bport1_ab_data.PFAPR.value = 0xf8003f;
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

