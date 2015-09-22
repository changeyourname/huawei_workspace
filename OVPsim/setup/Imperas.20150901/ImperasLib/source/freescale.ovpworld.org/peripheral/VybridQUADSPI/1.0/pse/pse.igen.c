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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridQUADSPI", "Example");
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

static PPM_WRITE_CB(bport1_ab_BFGENCR_maskWrite) {
    bport1_ab_data.BFGENCR.value = (bport1_ab_data.BFGENCR.value & 0xfffe0fff) | (data & 0x1f000);
}

static PPM_WRITE_CB(bport1_ab_BUF0CR_maskWrite) {
    bport1_ab_data.BUF0CR.value = (bport1_ab_data.BUF0CR.value & 0x7fff00f0) | (data & 0x8000ff0f);
}

static PPM_WRITE_CB(bport1_ab_BUF0IND_maskWrite) {
    bport1_ab_data.BUF0IND.value = (bport1_ab_data.BUF0IND.value & 0x7) | (data & 0xfffffff8);
}

static PPM_WRITE_CB(bport1_ab_BUF1CR_maskWrite) {
    bport1_ab_data.BUF1CR.value = (bport1_ab_data.BUF1CR.value & 0xffff00f0) | (data & 0xff0f);
}

static PPM_WRITE_CB(bport1_ab_BUF1IND_maskWrite) {
    bport1_ab_data.BUF1IND.value = (bport1_ab_data.BUF1IND.value & 0x7) | (data & 0xfffffff8);
}

static PPM_WRITE_CB(bport1_ab_BUF2CR_maskWrite) {
    bport1_ab_data.BUF2CR.value = (bport1_ab_data.BUF2CR.value & 0xffff00f0) | (data & 0xff0f);
}

static PPM_WRITE_CB(bport1_ab_BUF2IND_maskWrite) {
    bport1_ab_data.BUF2IND.value = (bport1_ab_data.BUF2IND.value & 0x7) | (data & 0xfffffff8);
}

static PPM_WRITE_CB(bport1_ab_BUF3CR_maskWrite) {
    bport1_ab_data.BUF3CR.value = (bport1_ab_data.BUF3CR.value & 0x7fff00f0) | (data & 0x8000ff0f);
}

static PPM_WRITE_CB(bport1_ab_FLSHCR_maskWrite) {
    bport1_ab_data.FLSHCR.value = (bport1_ab_data.FLSHCR.value & 0xfffff0f0) | (data & 0xf0f);
}

static PPM_WRITE_CB(bport1_ab_FR_maskWrite) {
    bport1_ab_data.FR.value = (bport1_ab_data.FR.value & 0x737c672e) | (data & 0x8c8398d1);
}

static PPM_WRITE_CB(bport1_ab_IPCR_maskWrite) {
    bport1_ab_data.IPCR.value = (bport1_ab_data.IPCR.value & 0xf0fe0000) | (data & 0xf01ffff);
}

static PPM_WRITE_CB(bport1_ab_LUT0_maskWrite) {
    bport1_ab_data.LUT0.value = (bport1_ab_data.LUT0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT10_maskWrite) {
    bport1_ab_data.LUT10.value = (bport1_ab_data.LUT10.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT11_maskWrite) {
    bport1_ab_data.LUT11.value = (bport1_ab_data.LUT11.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT12_maskWrite) {
    bport1_ab_data.LUT12.value = (bport1_ab_data.LUT12.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT13_maskWrite) {
    bport1_ab_data.LUT13.value = (bport1_ab_data.LUT13.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT14_maskWrite) {
    bport1_ab_data.LUT14.value = (bport1_ab_data.LUT14.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT15_maskWrite) {
    bport1_ab_data.LUT15.value = (bport1_ab_data.LUT15.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT16_maskWrite) {
    bport1_ab_data.LUT16.value = (bport1_ab_data.LUT16.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT17_maskWrite) {
    bport1_ab_data.LUT17.value = (bport1_ab_data.LUT17.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT18_maskWrite) {
    bport1_ab_data.LUT18.value = (bport1_ab_data.LUT18.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT19_maskWrite) {
    bport1_ab_data.LUT19.value = (bport1_ab_data.LUT19.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT1_maskWrite) {
    bport1_ab_data.LUT1.value = (bport1_ab_data.LUT1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT20_maskWrite) {
    bport1_ab_data.LUT20.value = (bport1_ab_data.LUT20.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT21_maskWrite) {
    bport1_ab_data.LUT21.value = (bport1_ab_data.LUT21.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT22_maskWrite) {
    bport1_ab_data.LUT22.value = (bport1_ab_data.LUT22.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT23_maskWrite) {
    bport1_ab_data.LUT23.value = (bport1_ab_data.LUT23.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT24_maskWrite) {
    bport1_ab_data.LUT24.value = (bport1_ab_data.LUT24.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT25_maskWrite) {
    bport1_ab_data.LUT25.value = (bport1_ab_data.LUT25.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT26_maskWrite) {
    bport1_ab_data.LUT26.value = (bport1_ab_data.LUT26.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT27_maskWrite) {
    bport1_ab_data.LUT27.value = (bport1_ab_data.LUT27.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT28_maskWrite) {
    bport1_ab_data.LUT28.value = (bport1_ab_data.LUT28.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT29_maskWrite) {
    bport1_ab_data.LUT29.value = (bport1_ab_data.LUT29.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT2_maskWrite) {
    bport1_ab_data.LUT2.value = (bport1_ab_data.LUT2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT30_maskWrite) {
    bport1_ab_data.LUT30.value = (bport1_ab_data.LUT30.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT31_maskWrite) {
    bport1_ab_data.LUT31.value = (bport1_ab_data.LUT31.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT32_maskWrite) {
    bport1_ab_data.LUT32.value = (bport1_ab_data.LUT32.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT33_maskWrite) {
    bport1_ab_data.LUT33.value = (bport1_ab_data.LUT33.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT34_maskWrite) {
    bport1_ab_data.LUT34.value = (bport1_ab_data.LUT34.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT35_maskWrite) {
    bport1_ab_data.LUT35.value = (bport1_ab_data.LUT35.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT36_maskWrite) {
    bport1_ab_data.LUT36.value = (bport1_ab_data.LUT36.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT37_maskWrite) {
    bport1_ab_data.LUT37.value = (bport1_ab_data.LUT37.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT38_maskWrite) {
    bport1_ab_data.LUT38.value = (bport1_ab_data.LUT38.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT39_maskWrite) {
    bport1_ab_data.LUT39.value = (bport1_ab_data.LUT39.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT3_maskWrite) {
    bport1_ab_data.LUT3.value = (bport1_ab_data.LUT3.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT40_maskWrite) {
    bport1_ab_data.LUT40.value = (bport1_ab_data.LUT40.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT41_maskWrite) {
    bport1_ab_data.LUT41.value = (bport1_ab_data.LUT41.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT42_maskWrite) {
    bport1_ab_data.LUT42.value = (bport1_ab_data.LUT42.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT43_maskWrite) {
    bport1_ab_data.LUT43.value = (bport1_ab_data.LUT43.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT44_maskWrite) {
    bport1_ab_data.LUT44.value = (bport1_ab_data.LUT44.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT45_maskWrite) {
    bport1_ab_data.LUT45.value = (bport1_ab_data.LUT45.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT46_maskWrite) {
    bport1_ab_data.LUT46.value = (bport1_ab_data.LUT46.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT47_maskWrite) {
    bport1_ab_data.LUT47.value = (bport1_ab_data.LUT47.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT48_maskWrite) {
    bport1_ab_data.LUT48.value = (bport1_ab_data.LUT48.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT49_maskWrite) {
    bport1_ab_data.LUT49.value = (bport1_ab_data.LUT49.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT4_maskWrite) {
    bport1_ab_data.LUT4.value = (bport1_ab_data.LUT4.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT50_maskWrite) {
    bport1_ab_data.LUT50.value = (bport1_ab_data.LUT50.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT51_maskWrite) {
    bport1_ab_data.LUT51.value = (bport1_ab_data.LUT51.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT52_maskWrite) {
    bport1_ab_data.LUT52.value = (bport1_ab_data.LUT52.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT53_maskWrite) {
    bport1_ab_data.LUT53.value = (bport1_ab_data.LUT53.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT54_maskWrite) {
    bport1_ab_data.LUT54.value = (bport1_ab_data.LUT54.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT55_maskWrite) {
    bport1_ab_data.LUT55.value = (bport1_ab_data.LUT55.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT56_maskWrite) {
    bport1_ab_data.LUT56.value = (bport1_ab_data.LUT56.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT57_maskWrite) {
    bport1_ab_data.LUT57.value = (bport1_ab_data.LUT57.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT58_maskWrite) {
    bport1_ab_data.LUT58.value = (bport1_ab_data.LUT58.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT59_maskWrite) {
    bport1_ab_data.LUT59.value = (bport1_ab_data.LUT59.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT5_maskWrite) {
    bport1_ab_data.LUT5.value = (bport1_ab_data.LUT5.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT60_maskWrite) {
    bport1_ab_data.LUT60.value = (bport1_ab_data.LUT60.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT61_maskWrite) {
    bport1_ab_data.LUT61.value = (bport1_ab_data.LUT61.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT62_maskWrite) {
    bport1_ab_data.LUT62.value = (bport1_ab_data.LUT62.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT63_maskWrite) {
    bport1_ab_data.LUT63.value = (bport1_ab_data.LUT63.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT6_maskWrite) {
    bport1_ab_data.LUT6.value = (bport1_ab_data.LUT6.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT7_maskWrite) {
    bport1_ab_data.LUT7.value = (bport1_ab_data.LUT7.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT8_maskWrite) {
    bport1_ab_data.LUT8.value = (bport1_ab_data.LUT8.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_LUT9_maskWrite) {
    bport1_ab_data.LUT9.value = (bport1_ab_data.LUT9.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & 0xffb330) | (data & 0xff004ccf);
}

static PPM_WRITE_CB(bport1_ab_RBCT_maskWrite) {
    bport1_ab_data.RBCT.value = (bport1_ab_data.RBCT.value & 0xfffffee0) | (data & 0x11f);
}

static PPM_WRITE_CB(bport1_ab_RBDR0_maskWrite) {
    bport1_ab_data.RBDR0.value = (bport1_ab_data.RBDR0.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR10_maskWrite) {
    bport1_ab_data.RBDR10.value = (bport1_ab_data.RBDR10.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR11_maskWrite) {
    bport1_ab_data.RBDR11.value = (bport1_ab_data.RBDR11.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR12_maskWrite) {
    bport1_ab_data.RBDR12.value = (bport1_ab_data.RBDR12.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR13_maskWrite) {
    bport1_ab_data.RBDR13.value = (bport1_ab_data.RBDR13.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR14_maskWrite) {
    bport1_ab_data.RBDR14.value = (bport1_ab_data.RBDR14.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR15_maskWrite) {
    bport1_ab_data.RBDR15.value = (bport1_ab_data.RBDR15.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR16_maskWrite) {
    bport1_ab_data.RBDR16.value = (bport1_ab_data.RBDR16.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR17_maskWrite) {
    bport1_ab_data.RBDR17.value = (bport1_ab_data.RBDR17.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR18_maskWrite) {
    bport1_ab_data.RBDR18.value = (bport1_ab_data.RBDR18.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR19_maskWrite) {
    bport1_ab_data.RBDR19.value = (bport1_ab_data.RBDR19.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR1_maskWrite) {
    bport1_ab_data.RBDR1.value = (bport1_ab_data.RBDR1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR20_maskWrite) {
    bport1_ab_data.RBDR20.value = (bport1_ab_data.RBDR20.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR21_maskWrite) {
    bport1_ab_data.RBDR21.value = (bport1_ab_data.RBDR21.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR22_maskWrite) {
    bport1_ab_data.RBDR22.value = (bport1_ab_data.RBDR22.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR23_maskWrite) {
    bport1_ab_data.RBDR23.value = (bport1_ab_data.RBDR23.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR24_maskWrite) {
    bport1_ab_data.RBDR24.value = (bport1_ab_data.RBDR24.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR25_maskWrite) {
    bport1_ab_data.RBDR25.value = (bport1_ab_data.RBDR25.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR26_maskWrite) {
    bport1_ab_data.RBDR26.value = (bport1_ab_data.RBDR26.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR27_maskWrite) {
    bport1_ab_data.RBDR27.value = (bport1_ab_data.RBDR27.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR28_maskWrite) {
    bport1_ab_data.RBDR28.value = (bport1_ab_data.RBDR28.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR29_maskWrite) {
    bport1_ab_data.RBDR29.value = (bport1_ab_data.RBDR29.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR2_maskWrite) {
    bport1_ab_data.RBDR2.value = (bport1_ab_data.RBDR2.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR30_maskWrite) {
    bport1_ab_data.RBDR30.value = (bport1_ab_data.RBDR30.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR31_maskWrite) {
    bport1_ab_data.RBDR31.value = (bport1_ab_data.RBDR31.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR32_maskWrite) {
    bport1_ab_data.RBDR32.value = (bport1_ab_data.RBDR32.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR33_maskWrite) {
    bport1_ab_data.RBDR33.value = (bport1_ab_data.RBDR33.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR34_maskWrite) {
    bport1_ab_data.RBDR34.value = (bport1_ab_data.RBDR34.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR35_maskWrite) {
    bport1_ab_data.RBDR35.value = (bport1_ab_data.RBDR35.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR36_maskWrite) {
    bport1_ab_data.RBDR36.value = (bport1_ab_data.RBDR36.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR37_maskWrite) {
    bport1_ab_data.RBDR37.value = (bport1_ab_data.RBDR37.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR38_maskWrite) {
    bport1_ab_data.RBDR38.value = (bport1_ab_data.RBDR38.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR39_maskWrite) {
    bport1_ab_data.RBDR39.value = (bport1_ab_data.RBDR39.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR3_maskWrite) {
    bport1_ab_data.RBDR3.value = (bport1_ab_data.RBDR3.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR40_maskWrite) {
    bport1_ab_data.RBDR40.value = (bport1_ab_data.RBDR40.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR41_maskWrite) {
    bport1_ab_data.RBDR41.value = (bport1_ab_data.RBDR41.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR42_maskWrite) {
    bport1_ab_data.RBDR42.value = (bport1_ab_data.RBDR42.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR43_maskWrite) {
    bport1_ab_data.RBDR43.value = (bport1_ab_data.RBDR43.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR44_maskWrite) {
    bport1_ab_data.RBDR44.value = (bport1_ab_data.RBDR44.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR45_maskWrite) {
    bport1_ab_data.RBDR45.value = (bport1_ab_data.RBDR45.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR46_maskWrite) {
    bport1_ab_data.RBDR46.value = (bport1_ab_data.RBDR46.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR47_maskWrite) {
    bport1_ab_data.RBDR47.value = (bport1_ab_data.RBDR47.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR48_maskWrite) {
    bport1_ab_data.RBDR48.value = (bport1_ab_data.RBDR48.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR49_maskWrite) {
    bport1_ab_data.RBDR49.value = (bport1_ab_data.RBDR49.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR4_maskWrite) {
    bport1_ab_data.RBDR4.value = (bport1_ab_data.RBDR4.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR50_maskWrite) {
    bport1_ab_data.RBDR50.value = (bport1_ab_data.RBDR50.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR51_maskWrite) {
    bport1_ab_data.RBDR51.value = (bport1_ab_data.RBDR51.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR52_maskWrite) {
    bport1_ab_data.RBDR52.value = (bport1_ab_data.RBDR52.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR53_maskWrite) {
    bport1_ab_data.RBDR53.value = (bport1_ab_data.RBDR53.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR54_maskWrite) {
    bport1_ab_data.RBDR54.value = (bport1_ab_data.RBDR54.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR55_maskWrite) {
    bport1_ab_data.RBDR55.value = (bport1_ab_data.RBDR55.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR56_maskWrite) {
    bport1_ab_data.RBDR56.value = (bport1_ab_data.RBDR56.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR57_maskWrite) {
    bport1_ab_data.RBDR57.value = (bport1_ab_data.RBDR57.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR58_maskWrite) {
    bport1_ab_data.RBDR58.value = (bport1_ab_data.RBDR58.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR59_maskWrite) {
    bport1_ab_data.RBDR59.value = (bport1_ab_data.RBDR59.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR5_maskWrite) {
    bport1_ab_data.RBDR5.value = (bport1_ab_data.RBDR5.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR60_maskWrite) {
    bport1_ab_data.RBDR60.value = (bport1_ab_data.RBDR60.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR61_maskWrite) {
    bport1_ab_data.RBDR61.value = (bport1_ab_data.RBDR61.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR62_maskWrite) {
    bport1_ab_data.RBDR62.value = (bport1_ab_data.RBDR62.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR63_maskWrite) {
    bport1_ab_data.RBDR63.value = (bport1_ab_data.RBDR63.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR6_maskWrite) {
    bport1_ab_data.RBDR6.value = (bport1_ab_data.RBDR6.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR7_maskWrite) {
    bport1_ab_data.RBDR7.value = (bport1_ab_data.RBDR7.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR8_maskWrite) {
    bport1_ab_data.RBDR8.value = (bport1_ab_data.RBDR8.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RBDR9_maskWrite) {
    bport1_ab_data.RBDR9.value = (bport1_ab_data.RBDR9.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_RSER_maskWrite) {
    bport1_ab_data.RSER.value = (bport1_ab_data.RSER.value & 0x737c672e) | (data & 0x8c8398d1);
}

static PPM_WRITE_CB(bport1_ab_SFA1AD_maskWrite) {
    bport1_ab_data.SFA1AD.value = (bport1_ab_data.SFA1AD.value & 0x3ff) | (data & 0xfffffc00);
}

static PPM_WRITE_CB(bport1_ab_SFA2AD_maskWrite) {
    bport1_ab_data.SFA2AD.value = (bport1_ab_data.SFA2AD.value & 0x3ff) | (data & 0xfffffc00);
}

static PPM_WRITE_CB(bport1_ab_SFAR_maskWrite) {
    bport1_ab_data.SFAR.value = (bport1_ab_data.SFAR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_SFB1AD_maskWrite) {
    bport1_ab_data.SFB1AD.value = (bport1_ab_data.SFB1AD.value & 0x3ff) | (data & 0xfffffc00);
}

static PPM_WRITE_CB(bport1_ab_SFB2AD_maskWrite) {
    bport1_ab_data.SFB2AD.value = (bport1_ab_data.SFB2AD.value & 0x3ff) | (data & 0xfffffc00);
}

static PPM_WRITE_CB(bport1_ab_SMPR_maskWrite) {
    bport1_ab_data.SMPR.value = (bport1_ab_data.SMPR.value & 0xfff8ff98) | (data & 0x70067);
}

static PPM_WRITE_CB(bport1_ab_SPTRCLR_maskWrite) {
    bport1_ab_data.SPTRCLR.value = (bport1_ab_data.SPTRCLR.value & 0xfffffefe) | (data & 0x101);
}

static PPM_WRITE_CB(bport1_ab_TBDR_maskWrite) {
    bport1_ab_data.TBDR.value = (bport1_ab_data.TBDR.value & 0x0) | (data & 0xffffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_MCR",
        "Module Configuration Register, offset: 0x0",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_MCR_maskWrite,
        view32,
        &(bport1_ab_data.MCR.value),
        True
    );
    ppmCreateRegister("ab_IPCR",
        "IP Configuration Register, offset: 0x8",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_IPCR_maskWrite,
        view32,
        &(bport1_ab_data.IPCR.value),
        True
    );
    ppmCreateRegister("ab_FLSHCR",
        "Flash Configuration Register, offset: 0xC",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_FLSHCR_maskWrite,
        view32,
        &(bport1_ab_data.FLSHCR.value),
        True
    );
    ppmCreateRegister("ab_BUF0CR",
        "Buffer0 Configuration Register, offset: 0x10",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_BUF0CR_maskWrite,
        view32,
        &(bport1_ab_data.BUF0CR.value),
        True
    );
    ppmCreateRegister("ab_BUF1CR",
        "Buffer1 Configuration Register, offset: 0x14",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_BUF1CR_maskWrite,
        view32,
        &(bport1_ab_data.BUF1CR.value),
        True
    );
    ppmCreateRegister("ab_BUF2CR",
        "Buffer2 Configuration Register, offset: 0x18",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_BUF2CR_maskWrite,
        view32,
        &(bport1_ab_data.BUF2CR.value),
        True
    );
    ppmCreateRegister("ab_BUF3CR",
        "Buffer3 Configuration Register, offset: 0x1C",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_BUF3CR_maskWrite,
        view32,
        &(bport1_ab_data.BUF3CR.value),
        True
    );
    ppmCreateRegister("ab_BFGENCR",
        "Buffer Generic Configuration Register, offset: 0x20",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_BFGENCR_maskWrite,
        view32,
        &(bport1_ab_data.BFGENCR.value),
        True
    );
    ppmCreateRegister("ab_BUF0IND",
        "Buffer0 Top Index Register, offset: 0x30",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_BUF0IND_maskWrite,
        view32,
        &(bport1_ab_data.BUF0IND.value),
        True
    );
    ppmCreateRegister("ab_BUF1IND",
        "Buffer1 Top Index Register, offset: 0x34",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_BUF1IND_maskWrite,
        view32,
        &(bport1_ab_data.BUF1IND.value),
        True
    );
    ppmCreateRegister("ab_BUF2IND",
        "Buffer2 Top Index Register, offset: 0x38",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_BUF2IND_maskWrite,
        view32,
        &(bport1_ab_data.BUF2IND.value),
        True
    );
    ppmCreateRegister("ab_SFAR",
        "Serial Flash Address Register, offset: 0x100",
        handles.bport1,
        256,
        4,
        read_32,
        bport1_ab_SFAR_maskWrite,
        view32,
        &(bport1_ab_data.SFAR.value),
        True
    );
    ppmCreateRegister("ab_SMPR",
        "Sampling Register, offset: 0x108",
        handles.bport1,
        264,
        4,
        read_32,
        bport1_ab_SMPR_maskWrite,
        view32,
        &(bport1_ab_data.SMPR.value),
        True
    );
    ppmCreateRegister("ab_RBSR",
        "RX Buffer Status Register, offset: 0x10C",
        handles.bport1,
        268,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RBSR.value),
        True
    );
    ppmCreateRegister("ab_RBCT",
        "RX Buffer Control Register, offset: 0x110",
        handles.bport1,
        272,
        4,
        read_32,
        bport1_ab_RBCT_maskWrite,
        view32,
        &(bport1_ab_data.RBCT.value),
        True
    );
    ppmCreateRegister("ab_TBSR",
        "TX Buffer Status Register, offset: 0x150",
        handles.bport1,
        336,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TBSR.value),
        True
    );
    ppmCreateRegister("ab_TBDR",
        "TX Buffer Data Register, offset: 0x154",
        handles.bport1,
        340,
        4,
        read_32,
        bport1_ab_TBDR_maskWrite,
        view32,
        &(bport1_ab_data.TBDR.value),
        True
    );
    ppmCreateRegister("ab_SR",
        "Status Register, offset: 0x15C",
        handles.bport1,
        348,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.SR.value),
        True
    );
    ppmCreateRegister("ab_FR",
        "Flag Register, offset: 0x160",
        handles.bport1,
        352,
        4,
        read_32,
        bport1_ab_FR_maskWrite,
        view32,
        &(bport1_ab_data.FR.value),
        True
    );
    ppmCreateRegister("ab_RSER",
        "Interrupt and DMA Request Select and Enable Register, offset: 0x164",
        handles.bport1,
        356,
        4,
        read_32,
        bport1_ab_RSER_maskWrite,
        view32,
        &(bport1_ab_data.RSER.value),
        True
    );
    ppmCreateRegister("ab_SPNDST",
        "Sequence Suspend Status Register, offset: 0x168",
        handles.bport1,
        360,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.SPNDST.value),
        True
    );
    ppmCreateRegister("ab_SPTRCLR",
        "Sequence Pointer Clear Register, offset: 0x16C",
        handles.bport1,
        364,
        4,
        read_32,
        bport1_ab_SPTRCLR_maskWrite,
        view32,
        &(bport1_ab_data.SPTRCLR.value),
        True
    );
    ppmCreateRegister("ab_SFA1AD",
        "Serial Flash A1 Top Address, offset: 0x180",
        handles.bport1,
        384,
        4,
        read_32,
        bport1_ab_SFA1AD_maskWrite,
        view32,
        &(bport1_ab_data.SFA1AD.value),
        True
    );
    ppmCreateRegister("ab_SFA2AD",
        "Serial Flash A2 Top Address, offset: 0x184",
        handles.bport1,
        388,
        4,
        read_32,
        bport1_ab_SFA2AD_maskWrite,
        view32,
        &(bport1_ab_data.SFA2AD.value),
        True
    );
    ppmCreateRegister("ab_SFB1AD",
        "Serial Flash B1Top Address, offset: 0x188",
        handles.bport1,
        392,
        4,
        read_32,
        bport1_ab_SFB1AD_maskWrite,
        view32,
        &(bport1_ab_data.SFB1AD.value),
        True
    );
    ppmCreateRegister("ab_SFB2AD",
        "Serial Flash B2Top Address, offset: 0x18C",
        handles.bport1,
        396,
        4,
        read_32,
        bport1_ab_SFB2AD_maskWrite,
        view32,
        &(bport1_ab_data.SFB2AD.value),
        True
    );
    ppmCreateRegister("ab_LUTKEY",
        "LUT Key Register, offset: 0x300",
        handles.bport1,
        768,
        4,
        readLutKey,
        writeLutKey,
        view32,
        &(bport1_ab_data.LUTKEY.value),
        True
    );
    ppmCreateRegister("ab_LCKCR",
        "LUT Lock Configuration Register, offset: 0x304",
        handles.bport1,
        772,
        4,
        readLutLck,
        writeLutLck,
        view32,
        &(bport1_ab_data.LCKCR.value),
        True
    );
    ppmCreateRegister("ab_RBDR0",
        "RX Buffer DataRegister 0 offset base 0x200: array step: 0x4",
        handles.bport1,
        512,
        4,
        read_32,
        bport1_ab_RBDR0_maskWrite,
        view32,
        &(bport1_ab_data.RBDR0.value),
        True
    );
    ppmCreateRegister("ab_RBDR1",
        "RX Buffer DataRegister 1 offset base 0x200: array step: 0x4",
        handles.bport1,
        516,
        4,
        read_32,
        bport1_ab_RBDR1_maskWrite,
        view32,
        &(bport1_ab_data.RBDR1.value),
        True
    );
    ppmCreateRegister("ab_RBDR2",
        "RX Buffer DataRegister 2 offset base 0x200: array step: 0x4",
        handles.bport1,
        520,
        4,
        read_32,
        bport1_ab_RBDR2_maskWrite,
        view32,
        &(bport1_ab_data.RBDR2.value),
        True
    );
    ppmCreateRegister("ab_RBDR3",
        "RX Buffer DataRegister 3 offset base 0x200: array step: 0x4",
        handles.bport1,
        524,
        4,
        read_32,
        bport1_ab_RBDR3_maskWrite,
        view32,
        &(bport1_ab_data.RBDR3.value),
        True
    );
    ppmCreateRegister("ab_RBDR4",
        "RX Buffer DataRegister 4 offset base 0x200: array step: 0x4",
        handles.bport1,
        528,
        4,
        read_32,
        bport1_ab_RBDR4_maskWrite,
        view32,
        &(bport1_ab_data.RBDR4.value),
        True
    );
    ppmCreateRegister("ab_RBDR5",
        "RX Buffer DataRegister 5 offset base 0x200: array step: 0x4",
        handles.bport1,
        532,
        4,
        read_32,
        bport1_ab_RBDR5_maskWrite,
        view32,
        &(bport1_ab_data.RBDR5.value),
        True
    );
    ppmCreateRegister("ab_RBDR6",
        "RX Buffer DataRegister 6 offset base 0x200: array step: 0x4",
        handles.bport1,
        536,
        4,
        read_32,
        bport1_ab_RBDR6_maskWrite,
        view32,
        &(bport1_ab_data.RBDR6.value),
        True
    );
    ppmCreateRegister("ab_RBDR7",
        "RX Buffer DataRegister 7 offset base 0x200: array step: 0x4",
        handles.bport1,
        540,
        4,
        read_32,
        bport1_ab_RBDR7_maskWrite,
        view32,
        &(bport1_ab_data.RBDR7.value),
        True
    );
    ppmCreateRegister("ab_RBDR8",
        "RX Buffer DataRegister 8 offset base 0x200: array step: 0x4",
        handles.bport1,
        544,
        4,
        read_32,
        bport1_ab_RBDR8_maskWrite,
        view32,
        &(bport1_ab_data.RBDR8.value),
        True
    );
    ppmCreateRegister("ab_RBDR9",
        "RX Buffer DataRegister 9 offset base 0x200: array step: 0x4",
        handles.bport1,
        548,
        4,
        read_32,
        bport1_ab_RBDR9_maskWrite,
        view32,
        &(bport1_ab_data.RBDR9.value),
        True
    );
    ppmCreateRegister("ab_RBDR10",
        "RX Buffer DataRegister 10 offset base 0x200: array step: 0x4",
        handles.bport1,
        552,
        4,
        read_32,
        bport1_ab_RBDR10_maskWrite,
        view32,
        &(bport1_ab_data.RBDR10.value),
        True
    );
    ppmCreateRegister("ab_RBDR11",
        "RX Buffer DataRegister 11 offset base 0x200: array step: 0x4",
        handles.bport1,
        556,
        4,
        read_32,
        bport1_ab_RBDR11_maskWrite,
        view32,
        &(bport1_ab_data.RBDR11.value),
        True
    );
    ppmCreateRegister("ab_RBDR12",
        "RX Buffer DataRegister 12 offset base 0x200: array step: 0x4",
        handles.bport1,
        560,
        4,
        read_32,
        bport1_ab_RBDR12_maskWrite,
        view32,
        &(bport1_ab_data.RBDR12.value),
        True
    );
    ppmCreateRegister("ab_RBDR13",
        "RX Buffer DataRegister 13 offset base 0x200: array step: 0x4",
        handles.bport1,
        564,
        4,
        read_32,
        bport1_ab_RBDR13_maskWrite,
        view32,
        &(bport1_ab_data.RBDR13.value),
        True
    );
    ppmCreateRegister("ab_RBDR14",
        "RX Buffer DataRegister 14 offset base 0x200: array step: 0x4",
        handles.bport1,
        568,
        4,
        read_32,
        bport1_ab_RBDR14_maskWrite,
        view32,
        &(bport1_ab_data.RBDR14.value),
        True
    );
    ppmCreateRegister("ab_RBDR15",
        "RX Buffer DataRegister 15 offset base 0x200: array step: 0x4",
        handles.bport1,
        572,
        4,
        read_32,
        bport1_ab_RBDR15_maskWrite,
        view32,
        &(bport1_ab_data.RBDR15.value),
        True
    );
    ppmCreateRegister("ab_RBDR16",
        "RX Buffer DataRegister 16 offset base 0x200: array step: 0x4",
        handles.bport1,
        576,
        4,
        read_32,
        bport1_ab_RBDR16_maskWrite,
        view32,
        &(bport1_ab_data.RBDR16.value),
        True
    );
    ppmCreateRegister("ab_RBDR17",
        "RX Buffer DataRegister 17 offset base 0x200: array step: 0x4",
        handles.bport1,
        580,
        4,
        read_32,
        bport1_ab_RBDR17_maskWrite,
        view32,
        &(bport1_ab_data.RBDR17.value),
        True
    );
    ppmCreateRegister("ab_RBDR18",
        "RX Buffer DataRegister 18 offset base 0x200: array step: 0x4",
        handles.bport1,
        584,
        4,
        read_32,
        bport1_ab_RBDR18_maskWrite,
        view32,
        &(bport1_ab_data.RBDR18.value),
        True
    );
    ppmCreateRegister("ab_RBDR19",
        "RX Buffer DataRegister 19 offset base 0x200: array step: 0x4",
        handles.bport1,
        588,
        4,
        read_32,
        bport1_ab_RBDR19_maskWrite,
        view32,
        &(bport1_ab_data.RBDR19.value),
        True
    );
    ppmCreateRegister("ab_RBDR20",
        "RX Buffer DataRegister 20 offset base 0x200: array step: 0x4",
        handles.bport1,
        592,
        4,
        read_32,
        bport1_ab_RBDR20_maskWrite,
        view32,
        &(bport1_ab_data.RBDR20.value),
        True
    );
    ppmCreateRegister("ab_RBDR21",
        "RX Buffer DataRegister 21 offset base 0x200: array step: 0x4",
        handles.bport1,
        596,
        4,
        read_32,
        bport1_ab_RBDR21_maskWrite,
        view32,
        &(bport1_ab_data.RBDR21.value),
        True
    );
    ppmCreateRegister("ab_RBDR22",
        "RX Buffer DataRegister 22 offset base 0x200: array step: 0x4",
        handles.bport1,
        600,
        4,
        read_32,
        bport1_ab_RBDR22_maskWrite,
        view32,
        &(bport1_ab_data.RBDR22.value),
        True
    );
    ppmCreateRegister("ab_RBDR23",
        "RX Buffer DataRegister 23 offset base 0x200: array step: 0x4",
        handles.bport1,
        604,
        4,
        read_32,
        bport1_ab_RBDR23_maskWrite,
        view32,
        &(bport1_ab_data.RBDR23.value),
        True
    );
    ppmCreateRegister("ab_RBDR24",
        "RX Buffer DataRegister 24 offset base 0x200: array step: 0x4",
        handles.bport1,
        608,
        4,
        read_32,
        bport1_ab_RBDR24_maskWrite,
        view32,
        &(bport1_ab_data.RBDR24.value),
        True
    );
    ppmCreateRegister("ab_RBDR25",
        "RX Buffer DataRegister 25 offset base 0x200: array step: 0x4",
        handles.bport1,
        612,
        4,
        read_32,
        bport1_ab_RBDR25_maskWrite,
        view32,
        &(bport1_ab_data.RBDR25.value),
        True
    );
    ppmCreateRegister("ab_RBDR26",
        "RX Buffer DataRegister 26 offset base 0x200: array step: 0x4",
        handles.bport1,
        616,
        4,
        read_32,
        bport1_ab_RBDR26_maskWrite,
        view32,
        &(bport1_ab_data.RBDR26.value),
        True
    );
    ppmCreateRegister("ab_RBDR27",
        "RX Buffer DataRegister 27 offset base 0x200: array step: 0x4",
        handles.bport1,
        620,
        4,
        read_32,
        bport1_ab_RBDR27_maskWrite,
        view32,
        &(bport1_ab_data.RBDR27.value),
        True
    );
    ppmCreateRegister("ab_RBDR28",
        "RX Buffer DataRegister 28 offset base 0x200: array step: 0x4",
        handles.bport1,
        624,
        4,
        read_32,
        bport1_ab_RBDR28_maskWrite,
        view32,
        &(bport1_ab_data.RBDR28.value),
        True
    );
    ppmCreateRegister("ab_RBDR29",
        "RX Buffer DataRegister 29 offset base 0x200: array step: 0x4",
        handles.bport1,
        628,
        4,
        read_32,
        bport1_ab_RBDR29_maskWrite,
        view32,
        &(bport1_ab_data.RBDR29.value),
        True
    );
    ppmCreateRegister("ab_RBDR30",
        "RX Buffer DataRegister 30 offset base 0x200: array step: 0x4",
        handles.bport1,
        632,
        4,
        read_32,
        bport1_ab_RBDR30_maskWrite,
        view32,
        &(bport1_ab_data.RBDR30.value),
        True
    );
    ppmCreateRegister("ab_RBDR31",
        "RX Buffer DataRegister 31 offset base 0x200: array step: 0x4",
        handles.bport1,
        636,
        4,
        read_32,
        bport1_ab_RBDR31_maskWrite,
        view32,
        &(bport1_ab_data.RBDR31.value),
        True
    );
    ppmCreateRegister("ab_RBDR32",
        "RX Buffer DataRegister 32 offset base 0x200: array step: 0x4",
        handles.bport1,
        640,
        4,
        read_32,
        bport1_ab_RBDR32_maskWrite,
        view32,
        &(bport1_ab_data.RBDR32.value),
        True
    );
    ppmCreateRegister("ab_RBDR33",
        "RX Buffer DataRegister 33 offset base 0x200: array step: 0x4",
        handles.bport1,
        644,
        4,
        read_32,
        bport1_ab_RBDR33_maskWrite,
        view32,
        &(bport1_ab_data.RBDR33.value),
        True
    );
    ppmCreateRegister("ab_RBDR34",
        "RX Buffer DataRegister 34 offset base 0x200: array step: 0x4",
        handles.bport1,
        648,
        4,
        read_32,
        bport1_ab_RBDR34_maskWrite,
        view32,
        &(bport1_ab_data.RBDR34.value),
        True
    );
    ppmCreateRegister("ab_RBDR35",
        "RX Buffer DataRegister 35 offset base 0x200: array step: 0x4",
        handles.bport1,
        652,
        4,
        read_32,
        bport1_ab_RBDR35_maskWrite,
        view32,
        &(bport1_ab_data.RBDR35.value),
        True
    );
    ppmCreateRegister("ab_RBDR36",
        "RX Buffer DataRegister 36 offset base 0x200: array step: 0x4",
        handles.bport1,
        656,
        4,
        read_32,
        bport1_ab_RBDR36_maskWrite,
        view32,
        &(bport1_ab_data.RBDR36.value),
        True
    );
    ppmCreateRegister("ab_RBDR37",
        "RX Buffer DataRegister 37 offset base 0x200: array step: 0x4",
        handles.bport1,
        660,
        4,
        read_32,
        bport1_ab_RBDR37_maskWrite,
        view32,
        &(bport1_ab_data.RBDR37.value),
        True
    );
    ppmCreateRegister("ab_RBDR38",
        "RX Buffer DataRegister 38 offset base 0x200: array step: 0x4",
        handles.bport1,
        664,
        4,
        read_32,
        bport1_ab_RBDR38_maskWrite,
        view32,
        &(bport1_ab_data.RBDR38.value),
        True
    );
    ppmCreateRegister("ab_RBDR39",
        "RX Buffer DataRegister 39 offset base 0x200: array step: 0x4",
        handles.bport1,
        668,
        4,
        read_32,
        bport1_ab_RBDR39_maskWrite,
        view32,
        &(bport1_ab_data.RBDR39.value),
        True
    );
    ppmCreateRegister("ab_RBDR40",
        "RX Buffer DataRegister 40 offset base 0x200: array step: 0x4",
        handles.bport1,
        672,
        4,
        read_32,
        bport1_ab_RBDR40_maskWrite,
        view32,
        &(bport1_ab_data.RBDR40.value),
        True
    );
    ppmCreateRegister("ab_RBDR41",
        "RX Buffer DataRegister 41 offset base 0x200: array step: 0x4",
        handles.bport1,
        676,
        4,
        read_32,
        bport1_ab_RBDR41_maskWrite,
        view32,
        &(bport1_ab_data.RBDR41.value),
        True
    );
    ppmCreateRegister("ab_RBDR42",
        "RX Buffer DataRegister 42 offset base 0x200: array step: 0x4",
        handles.bport1,
        680,
        4,
        read_32,
        bport1_ab_RBDR42_maskWrite,
        view32,
        &(bport1_ab_data.RBDR42.value),
        True
    );
    ppmCreateRegister("ab_RBDR43",
        "RX Buffer DataRegister 43 offset base 0x200: array step: 0x4",
        handles.bport1,
        684,
        4,
        read_32,
        bport1_ab_RBDR43_maskWrite,
        view32,
        &(bport1_ab_data.RBDR43.value),
        True
    );
    ppmCreateRegister("ab_RBDR44",
        "RX Buffer DataRegister 44 offset base 0x200: array step: 0x4",
        handles.bport1,
        688,
        4,
        read_32,
        bport1_ab_RBDR44_maskWrite,
        view32,
        &(bport1_ab_data.RBDR44.value),
        True
    );
    ppmCreateRegister("ab_RBDR45",
        "RX Buffer DataRegister 45 offset base 0x200: array step: 0x4",
        handles.bport1,
        692,
        4,
        read_32,
        bport1_ab_RBDR45_maskWrite,
        view32,
        &(bport1_ab_data.RBDR45.value),
        True
    );
    ppmCreateRegister("ab_RBDR46",
        "RX Buffer DataRegister 46 offset base 0x200: array step: 0x4",
        handles.bport1,
        696,
        4,
        read_32,
        bport1_ab_RBDR46_maskWrite,
        view32,
        &(bport1_ab_data.RBDR46.value),
        True
    );
    ppmCreateRegister("ab_RBDR47",
        "RX Buffer DataRegister 47 offset base 0x200: array step: 0x4",
        handles.bport1,
        700,
        4,
        read_32,
        bport1_ab_RBDR47_maskWrite,
        view32,
        &(bport1_ab_data.RBDR47.value),
        True
    );
    ppmCreateRegister("ab_RBDR48",
        "RX Buffer DataRegister 48 offset base 0x200: array step: 0x4",
        handles.bport1,
        704,
        4,
        read_32,
        bport1_ab_RBDR48_maskWrite,
        view32,
        &(bport1_ab_data.RBDR48.value),
        True
    );
    ppmCreateRegister("ab_RBDR49",
        "RX Buffer DataRegister 49 offset base 0x200: array step: 0x4",
        handles.bport1,
        708,
        4,
        read_32,
        bport1_ab_RBDR49_maskWrite,
        view32,
        &(bport1_ab_data.RBDR49.value),
        True
    );
    ppmCreateRegister("ab_RBDR50",
        "RX Buffer DataRegister 50 offset base 0x200: array step: 0x4",
        handles.bport1,
        712,
        4,
        read_32,
        bport1_ab_RBDR50_maskWrite,
        view32,
        &(bport1_ab_data.RBDR50.value),
        True
    );
    ppmCreateRegister("ab_RBDR51",
        "RX Buffer DataRegister 51 offset base 0x200: array step: 0x4",
        handles.bport1,
        716,
        4,
        read_32,
        bport1_ab_RBDR51_maskWrite,
        view32,
        &(bport1_ab_data.RBDR51.value),
        True
    );
    ppmCreateRegister("ab_RBDR52",
        "RX Buffer DataRegister 52 offset base 0x200: array step: 0x4",
        handles.bport1,
        720,
        4,
        read_32,
        bport1_ab_RBDR52_maskWrite,
        view32,
        &(bport1_ab_data.RBDR52.value),
        True
    );
    ppmCreateRegister("ab_RBDR53",
        "RX Buffer DataRegister 53 offset base 0x200: array step: 0x4",
        handles.bport1,
        724,
        4,
        read_32,
        bport1_ab_RBDR53_maskWrite,
        view32,
        &(bport1_ab_data.RBDR53.value),
        True
    );
    ppmCreateRegister("ab_RBDR54",
        "RX Buffer DataRegister 54 offset base 0x200: array step: 0x4",
        handles.bport1,
        728,
        4,
        read_32,
        bport1_ab_RBDR54_maskWrite,
        view32,
        &(bport1_ab_data.RBDR54.value),
        True
    );
    ppmCreateRegister("ab_RBDR55",
        "RX Buffer DataRegister 55 offset base 0x200: array step: 0x4",
        handles.bport1,
        732,
        4,
        read_32,
        bport1_ab_RBDR55_maskWrite,
        view32,
        &(bport1_ab_data.RBDR55.value),
        True
    );
    ppmCreateRegister("ab_RBDR56",
        "RX Buffer DataRegister 56 offset base 0x200: array step: 0x4",
        handles.bport1,
        736,
        4,
        read_32,
        bport1_ab_RBDR56_maskWrite,
        view32,
        &(bport1_ab_data.RBDR56.value),
        True
    );
    ppmCreateRegister("ab_RBDR57",
        "RX Buffer DataRegister 57 offset base 0x200: array step: 0x4",
        handles.bport1,
        740,
        4,
        read_32,
        bport1_ab_RBDR57_maskWrite,
        view32,
        &(bport1_ab_data.RBDR57.value),
        True
    );
    ppmCreateRegister("ab_RBDR58",
        "RX Buffer DataRegister 58 offset base 0x200: array step: 0x4",
        handles.bport1,
        744,
        4,
        read_32,
        bport1_ab_RBDR58_maskWrite,
        view32,
        &(bport1_ab_data.RBDR58.value),
        True
    );
    ppmCreateRegister("ab_RBDR59",
        "RX Buffer DataRegister 59 offset base 0x200: array step: 0x4",
        handles.bport1,
        748,
        4,
        read_32,
        bport1_ab_RBDR59_maskWrite,
        view32,
        &(bport1_ab_data.RBDR59.value),
        True
    );
    ppmCreateRegister("ab_RBDR60",
        "RX Buffer DataRegister 60 offset base 0x200: array step: 0x4",
        handles.bport1,
        752,
        4,
        read_32,
        bport1_ab_RBDR60_maskWrite,
        view32,
        &(bport1_ab_data.RBDR60.value),
        True
    );
    ppmCreateRegister("ab_RBDR61",
        "RX Buffer DataRegister 61 offset base 0x200: array step: 0x4",
        handles.bport1,
        756,
        4,
        read_32,
        bport1_ab_RBDR61_maskWrite,
        view32,
        &(bport1_ab_data.RBDR61.value),
        True
    );
    ppmCreateRegister("ab_RBDR62",
        "RX Buffer DataRegister 62 offset base 0x200: array step: 0x4",
        handles.bport1,
        760,
        4,
        read_32,
        bport1_ab_RBDR62_maskWrite,
        view32,
        &(bport1_ab_data.RBDR62.value),
        True
    );
    ppmCreateRegister("ab_RBDR63",
        "RX Buffer DataRegister 63 offset base 0x200: array step: 0x4",
        handles.bport1,
        764,
        4,
        read_32,
        bport1_ab_RBDR63_maskWrite,
        view32,
        &(bport1_ab_data.RBDR63.value),
        True
    );
    ppmCreateRegister("ab_LUT0",
        "Look-up Table register 0, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        784,
        4,
        read_32,
        bport1_ab_LUT0_maskWrite,
        view32,
        &(bport1_ab_data.LUT0.value),
        True
    );
    ppmCreateRegister("ab_LUT1",
        "Look-up Table register 1, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        788,
        4,
        read_32,
        bport1_ab_LUT1_maskWrite,
        view32,
        &(bport1_ab_data.LUT1.value),
        True
    );
    ppmCreateRegister("ab_LUT2",
        "Look-up Table register 2, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        792,
        4,
        read_32,
        bport1_ab_LUT2_maskWrite,
        view32,
        &(bport1_ab_data.LUT2.value),
        True
    );
    ppmCreateRegister("ab_LUT3",
        "Look-up Table register 3, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        796,
        4,
        read_32,
        bport1_ab_LUT3_maskWrite,
        view32,
        &(bport1_ab_data.LUT3.value),
        True
    );
    ppmCreateRegister("ab_LUT4",
        "Look-up Table register 4, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        800,
        4,
        read_32,
        bport1_ab_LUT4_maskWrite,
        view32,
        &(bport1_ab_data.LUT4.value),
        True
    );
    ppmCreateRegister("ab_LUT5",
        "Look-up Table register 5, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        804,
        4,
        read_32,
        bport1_ab_LUT5_maskWrite,
        view32,
        &(bport1_ab_data.LUT5.value),
        True
    );
    ppmCreateRegister("ab_LUT6",
        "Look-up Table register 6, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        808,
        4,
        read_32,
        bport1_ab_LUT6_maskWrite,
        view32,
        &(bport1_ab_data.LUT6.value),
        True
    );
    ppmCreateRegister("ab_LUT7",
        "Look-up Table register 7, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        812,
        4,
        read_32,
        bport1_ab_LUT7_maskWrite,
        view32,
        &(bport1_ab_data.LUT7.value),
        True
    );
    ppmCreateRegister("ab_LUT8",
        "Look-up Table register 8, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        816,
        4,
        read_32,
        bport1_ab_LUT8_maskWrite,
        view32,
        &(bport1_ab_data.LUT8.value),
        True
    );
    ppmCreateRegister("ab_LUT9",
        "Look-up Table register 9, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        820,
        4,
        read_32,
        bport1_ab_LUT9_maskWrite,
        view32,
        &(bport1_ab_data.LUT9.value),
        True
    );
    ppmCreateRegister("ab_LUT10",
        "Look-up Table register 10, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        824,
        4,
        read_32,
        bport1_ab_LUT10_maskWrite,
        view32,
        &(bport1_ab_data.LUT10.value),
        True
    );
    ppmCreateRegister("ab_LUT11",
        "Look-up Table register 11, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        828,
        4,
        read_32,
        bport1_ab_LUT11_maskWrite,
        view32,
        &(bport1_ab_data.LUT11.value),
        True
    );
    ppmCreateRegister("ab_LUT12",
        "Look-up Table register 12, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        832,
        4,
        read_32,
        bport1_ab_LUT12_maskWrite,
        view32,
        &(bport1_ab_data.LUT12.value),
        True
    );
    ppmCreateRegister("ab_LUT13",
        "Look-up Table register 13, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        836,
        4,
        read_32,
        bport1_ab_LUT13_maskWrite,
        view32,
        &(bport1_ab_data.LUT13.value),
        True
    );
    ppmCreateRegister("ab_LUT14",
        "Look-up Table register 14, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        840,
        4,
        read_32,
        bport1_ab_LUT14_maskWrite,
        view32,
        &(bport1_ab_data.LUT14.value),
        True
    );
    ppmCreateRegister("ab_LUT15",
        "Look-up Table register 15, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        844,
        4,
        read_32,
        bport1_ab_LUT15_maskWrite,
        view32,
        &(bport1_ab_data.LUT15.value),
        True
    );
    ppmCreateRegister("ab_LUT16",
        "Look-up Table register 16, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        848,
        4,
        read_32,
        bport1_ab_LUT16_maskWrite,
        view32,
        &(bport1_ab_data.LUT16.value),
        True
    );
    ppmCreateRegister("ab_LUT17",
        "Look-up Table register 17, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        852,
        4,
        read_32,
        bport1_ab_LUT17_maskWrite,
        view32,
        &(bport1_ab_data.LUT17.value),
        True
    );
    ppmCreateRegister("ab_LUT18",
        "Look-up Table register 18, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        856,
        4,
        read_32,
        bport1_ab_LUT18_maskWrite,
        view32,
        &(bport1_ab_data.LUT18.value),
        True
    );
    ppmCreateRegister("ab_LUT19",
        "Look-up Table register 19, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        860,
        4,
        read_32,
        bport1_ab_LUT19_maskWrite,
        view32,
        &(bport1_ab_data.LUT19.value),
        True
    );
    ppmCreateRegister("ab_LUT20",
        "Look-up Table register 20, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        864,
        4,
        read_32,
        bport1_ab_LUT20_maskWrite,
        view32,
        &(bport1_ab_data.LUT20.value),
        True
    );
    ppmCreateRegister("ab_LUT21",
        "Look-up Table register 21, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        868,
        4,
        read_32,
        bport1_ab_LUT21_maskWrite,
        view32,
        &(bport1_ab_data.LUT21.value),
        True
    );
    ppmCreateRegister("ab_LUT22",
        "Look-up Table register 22, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        872,
        4,
        read_32,
        bport1_ab_LUT22_maskWrite,
        view32,
        &(bport1_ab_data.LUT22.value),
        True
    );
    ppmCreateRegister("ab_LUT23",
        "Look-up Table register 23, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        876,
        4,
        read_32,
        bport1_ab_LUT23_maskWrite,
        view32,
        &(bport1_ab_data.LUT23.value),
        True
    );
    ppmCreateRegister("ab_LUT24",
        "Look-up Table register 24, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        880,
        4,
        read_32,
        bport1_ab_LUT24_maskWrite,
        view32,
        &(bport1_ab_data.LUT24.value),
        True
    );
    ppmCreateRegister("ab_LUT25",
        "Look-up Table register 25, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        884,
        4,
        read_32,
        bport1_ab_LUT25_maskWrite,
        view32,
        &(bport1_ab_data.LUT25.value),
        True
    );
    ppmCreateRegister("ab_LUT26",
        "Look-up Table register 26, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        888,
        4,
        read_32,
        bport1_ab_LUT26_maskWrite,
        view32,
        &(bport1_ab_data.LUT26.value),
        True
    );
    ppmCreateRegister("ab_LUT27",
        "Look-up Table register 27, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        892,
        4,
        read_32,
        bport1_ab_LUT27_maskWrite,
        view32,
        &(bport1_ab_data.LUT27.value),
        True
    );
    ppmCreateRegister("ab_LUT28",
        "Look-up Table register 28, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        896,
        4,
        read_32,
        bport1_ab_LUT28_maskWrite,
        view32,
        &(bport1_ab_data.LUT28.value),
        True
    );
    ppmCreateRegister("ab_LUT29",
        "Look-up Table register 29, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        900,
        4,
        read_32,
        bport1_ab_LUT29_maskWrite,
        view32,
        &(bport1_ab_data.LUT29.value),
        True
    );
    ppmCreateRegister("ab_LUT30",
        "Look-up Table register 30, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        904,
        4,
        read_32,
        bport1_ab_LUT30_maskWrite,
        view32,
        &(bport1_ab_data.LUT30.value),
        True
    );
    ppmCreateRegister("ab_LUT31",
        "Look-up Table register 31, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        908,
        4,
        read_32,
        bport1_ab_LUT31_maskWrite,
        view32,
        &(bport1_ab_data.LUT31.value),
        True
    );
    ppmCreateRegister("ab_LUT32",
        "Look-up Table register 32, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        912,
        4,
        read_32,
        bport1_ab_LUT32_maskWrite,
        view32,
        &(bport1_ab_data.LUT32.value),
        True
    );
    ppmCreateRegister("ab_LUT33",
        "Look-up Table register 33, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        916,
        4,
        read_32,
        bport1_ab_LUT33_maskWrite,
        view32,
        &(bport1_ab_data.LUT33.value),
        True
    );
    ppmCreateRegister("ab_LUT34",
        "Look-up Table register 34, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        920,
        4,
        read_32,
        bport1_ab_LUT34_maskWrite,
        view32,
        &(bport1_ab_data.LUT34.value),
        True
    );
    ppmCreateRegister("ab_LUT35",
        "Look-up Table register 35, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        924,
        4,
        read_32,
        bport1_ab_LUT35_maskWrite,
        view32,
        &(bport1_ab_data.LUT35.value),
        True
    );
    ppmCreateRegister("ab_LUT36",
        "Look-up Table register 36, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        928,
        4,
        read_32,
        bport1_ab_LUT36_maskWrite,
        view32,
        &(bport1_ab_data.LUT36.value),
        True
    );
    ppmCreateRegister("ab_LUT37",
        "Look-up Table register 37, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        932,
        4,
        read_32,
        bport1_ab_LUT37_maskWrite,
        view32,
        &(bport1_ab_data.LUT37.value),
        True
    );
    ppmCreateRegister("ab_LUT38",
        "Look-up Table register 38, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        936,
        4,
        read_32,
        bport1_ab_LUT38_maskWrite,
        view32,
        &(bport1_ab_data.LUT38.value),
        True
    );
    ppmCreateRegister("ab_LUT39",
        "Look-up Table register 39, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        940,
        4,
        read_32,
        bport1_ab_LUT39_maskWrite,
        view32,
        &(bport1_ab_data.LUT39.value),
        True
    );
    ppmCreateRegister("ab_LUT40",
        "Look-up Table register 40, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        944,
        4,
        read_32,
        bport1_ab_LUT40_maskWrite,
        view32,
        &(bport1_ab_data.LUT40.value),
        True
    );
    ppmCreateRegister("ab_LUT41",
        "Look-up Table register 41, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        948,
        4,
        read_32,
        bport1_ab_LUT41_maskWrite,
        view32,
        &(bport1_ab_data.LUT41.value),
        True
    );
    ppmCreateRegister("ab_LUT42",
        "Look-up Table register 42, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        952,
        4,
        read_32,
        bport1_ab_LUT42_maskWrite,
        view32,
        &(bport1_ab_data.LUT42.value),
        True
    );
    ppmCreateRegister("ab_LUT43",
        "Look-up Table register 43, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        956,
        4,
        read_32,
        bport1_ab_LUT43_maskWrite,
        view32,
        &(bport1_ab_data.LUT43.value),
        True
    );
    ppmCreateRegister("ab_LUT44",
        "Look-up Table register 44, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        960,
        4,
        read_32,
        bport1_ab_LUT44_maskWrite,
        view32,
        &(bport1_ab_data.LUT44.value),
        True
    );
    ppmCreateRegister("ab_LUT45",
        "Look-up Table register 45, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        964,
        4,
        read_32,
        bport1_ab_LUT45_maskWrite,
        view32,
        &(bport1_ab_data.LUT45.value),
        True
    );
    ppmCreateRegister("ab_LUT46",
        "Look-up Table register 46, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        968,
        4,
        read_32,
        bport1_ab_LUT46_maskWrite,
        view32,
        &(bport1_ab_data.LUT46.value),
        True
    );
    ppmCreateRegister("ab_LUT47",
        "Look-up Table register 47, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        972,
        4,
        read_32,
        bport1_ab_LUT47_maskWrite,
        view32,
        &(bport1_ab_data.LUT47.value),
        True
    );
    ppmCreateRegister("ab_LUT48",
        "Look-up Table register 48, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        976,
        4,
        read_32,
        bport1_ab_LUT48_maskWrite,
        view32,
        &(bport1_ab_data.LUT48.value),
        True
    );
    ppmCreateRegister("ab_LUT49",
        "Look-up Table register 49, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        980,
        4,
        read_32,
        bport1_ab_LUT49_maskWrite,
        view32,
        &(bport1_ab_data.LUT49.value),
        True
    );
    ppmCreateRegister("ab_LUT50",
        "Look-up Table register 50, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        984,
        4,
        read_32,
        bport1_ab_LUT50_maskWrite,
        view32,
        &(bport1_ab_data.LUT50.value),
        True
    );
    ppmCreateRegister("ab_LUT51",
        "Look-up Table register 51, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        988,
        4,
        read_32,
        bport1_ab_LUT51_maskWrite,
        view32,
        &(bport1_ab_data.LUT51.value),
        True
    );
    ppmCreateRegister("ab_LUT52",
        "Look-up Table register 52, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        992,
        4,
        read_32,
        bport1_ab_LUT52_maskWrite,
        view32,
        &(bport1_ab_data.LUT52.value),
        True
    );
    ppmCreateRegister("ab_LUT53",
        "Look-up Table register 53, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        996,
        4,
        read_32,
        bport1_ab_LUT53_maskWrite,
        view32,
        &(bport1_ab_data.LUT53.value),
        True
    );
    ppmCreateRegister("ab_LUT54",
        "Look-up Table register 54, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1000,
        4,
        read_32,
        bport1_ab_LUT54_maskWrite,
        view32,
        &(bport1_ab_data.LUT54.value),
        True
    );
    ppmCreateRegister("ab_LUT55",
        "Look-up Table register 55, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1004,
        4,
        read_32,
        bport1_ab_LUT55_maskWrite,
        view32,
        &(bport1_ab_data.LUT55.value),
        True
    );
    ppmCreateRegister("ab_LUT56",
        "Look-up Table register 56, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1008,
        4,
        read_32,
        bport1_ab_LUT56_maskWrite,
        view32,
        &(bport1_ab_data.LUT56.value),
        True
    );
    ppmCreateRegister("ab_LUT57",
        "Look-up Table register 57, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1012,
        4,
        read_32,
        bport1_ab_LUT57_maskWrite,
        view32,
        &(bport1_ab_data.LUT57.value),
        True
    );
    ppmCreateRegister("ab_LUT58",
        "Look-up Table register 58, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1016,
        4,
        read_32,
        bport1_ab_LUT58_maskWrite,
        view32,
        &(bport1_ab_data.LUT58.value),
        True
    );
    ppmCreateRegister("ab_LUT59",
        "Look-up Table register 59, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1020,
        4,
        read_32,
        bport1_ab_LUT59_maskWrite,
        view32,
        &(bport1_ab_data.LUT59.value),
        True
    );
    ppmCreateRegister("ab_LUT60",
        "Look-up Table register 60, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1024,
        4,
        read_32,
        bport1_ab_LUT60_maskWrite,
        view32,
        &(bport1_ab_data.LUT60.value),
        True
    );
    ppmCreateRegister("ab_LUT61",
        "Look-up Table register 61, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1028,
        4,
        read_32,
        bport1_ab_LUT61_maskWrite,
        view32,
        &(bport1_ab_data.LUT61.value),
        True
    );
    ppmCreateRegister("ab_LUT62",
        "Look-up Table register 62, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1032,
        4,
        read_32,
        bport1_ab_LUT62_maskWrite,
        view32,
        &(bport1_ab_data.LUT62.value),
        True
    );
    ppmCreateRegister("ab_LUT63",
        "Look-up Table register 63, array offset base 0x310:  , array step: 0x4",
        handles.bport1,
        1036,
        4,
        read_32,
        bport1_ab_LUT63_maskWrite,
        view32,
        &(bport1_ab_data.LUT63.value),
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
        bport1_ab_data.LUT63.value = 0x0;
        bport1_ab_data.LUT62.value = 0x0;
        bport1_ab_data.LUT61.value = 0x0;
        bport1_ab_data.LUT60.value = 0x0;
        bport1_ab_data.LUT59.value = 0x0;
        bport1_ab_data.LUT58.value = 0x0;
        bport1_ab_data.LUT57.value = 0x0;
        bport1_ab_data.LUT56.value = 0x0;
        bport1_ab_data.LUT55.value = 0x0;
        bport1_ab_data.LUT54.value = 0x0;
        bport1_ab_data.LUT53.value = 0x0;
        bport1_ab_data.LUT52.value = 0x0;
        bport1_ab_data.LUT51.value = 0x0;
        bport1_ab_data.LUT50.value = 0x0;
        bport1_ab_data.LUT49.value = 0x0;
        bport1_ab_data.LUT48.value = 0x0;
        bport1_ab_data.LUT47.value = 0x0;
        bport1_ab_data.LUT46.value = 0x0;
        bport1_ab_data.LUT45.value = 0x0;
        bport1_ab_data.LUT44.value = 0x0;
        bport1_ab_data.LUT43.value = 0x0;
        bport1_ab_data.LUT42.value = 0x0;
        bport1_ab_data.LUT41.value = 0x0;
        bport1_ab_data.LUT40.value = 0x0;
        bport1_ab_data.LUT39.value = 0x0;
        bport1_ab_data.LUT38.value = 0x0;
        bport1_ab_data.LUT37.value = 0x0;
        bport1_ab_data.LUT36.value = 0x0;
        bport1_ab_data.LUT35.value = 0x0;
        bport1_ab_data.LUT34.value = 0x0;
        bport1_ab_data.LUT33.value = 0x0;
        bport1_ab_data.LUT32.value = 0x0;
        bport1_ab_data.LUT31.value = 0x0;
        bport1_ab_data.LUT30.value = 0x0;
        bport1_ab_data.LUT29.value = 0x0;
        bport1_ab_data.LUT28.value = 0x0;
        bport1_ab_data.LUT27.value = 0x0;
        bport1_ab_data.LUT26.value = 0x0;
        bport1_ab_data.LUT25.value = 0x0;
        bport1_ab_data.LUT24.value = 0x0;
        bport1_ab_data.LUT23.value = 0x0;
        bport1_ab_data.LUT22.value = 0x0;
        bport1_ab_data.LUT21.value = 0x0;
        bport1_ab_data.LUT20.value = 0x0;
        bport1_ab_data.LUT19.value = 0x0;
        bport1_ab_data.LUT18.value = 0x0;
        bport1_ab_data.LUT17.value = 0x0;
        bport1_ab_data.LUT16.value = 0x0;
        bport1_ab_data.LUT15.value = 0x0;
        bport1_ab_data.LUT14.value = 0x0;
        bport1_ab_data.LUT13.value = 0x0;
        bport1_ab_data.LUT12.value = 0x0;
        bport1_ab_data.LUT11.value = 0x0;
        bport1_ab_data.LUT10.value = 0x0;
        bport1_ab_data.LUT9.value = 0x0;
        bport1_ab_data.LUT8.value = 0x0;
        bport1_ab_data.LUT7.value = 0x0;
        bport1_ab_data.LUT6.value = 0x0;
        bport1_ab_data.LUT5.value = 0x0;
        bport1_ab_data.LUT4.value = 0x0;
        bport1_ab_data.LUT3.value = 0x0;
        bport1_ab_data.LUT2.value = 0x0;
        bport1_ab_data.LUT1.value = 0x0;
        bport1_ab_data.LUT0.value = 0x0;
        bport1_ab_data.RBDR63.value = 0x0;
        bport1_ab_data.RBDR62.value = 0x0;
        bport1_ab_data.RBDR61.value = 0x0;
        bport1_ab_data.RBDR60.value = 0x0;
        bport1_ab_data.RBDR59.value = 0x0;
        bport1_ab_data.RBDR58.value = 0x0;
        bport1_ab_data.RBDR57.value = 0x0;
        bport1_ab_data.RBDR56.value = 0x0;
        bport1_ab_data.RBDR55.value = 0x0;
        bport1_ab_data.RBDR54.value = 0x0;
        bport1_ab_data.RBDR53.value = 0x0;
        bport1_ab_data.RBDR52.value = 0x0;
        bport1_ab_data.RBDR51.value = 0x0;
        bport1_ab_data.RBDR50.value = 0x0;
        bport1_ab_data.RBDR49.value = 0x0;
        bport1_ab_data.RBDR48.value = 0x0;
        bport1_ab_data.RBDR47.value = 0x0;
        bport1_ab_data.RBDR46.value = 0x0;
        bport1_ab_data.RBDR45.value = 0x0;
        bport1_ab_data.RBDR44.value = 0x0;
        bport1_ab_data.RBDR43.value = 0x0;
        bport1_ab_data.RBDR42.value = 0x0;
        bport1_ab_data.RBDR41.value = 0x0;
        bport1_ab_data.RBDR40.value = 0x0;
        bport1_ab_data.RBDR39.value = 0x0;
        bport1_ab_data.RBDR38.value = 0x0;
        bport1_ab_data.RBDR37.value = 0x0;
        bport1_ab_data.RBDR36.value = 0x0;
        bport1_ab_data.RBDR35.value = 0x0;
        bport1_ab_data.RBDR34.value = 0x0;
        bport1_ab_data.RBDR33.value = 0x0;
        bport1_ab_data.RBDR32.value = 0x0;
        bport1_ab_data.RBDR31.value = 0x0;
        bport1_ab_data.RBDR30.value = 0x0;
        bport1_ab_data.RBDR29.value = 0x0;
        bport1_ab_data.RBDR28.value = 0x0;
        bport1_ab_data.RBDR27.value = 0x0;
        bport1_ab_data.RBDR26.value = 0x0;
        bport1_ab_data.RBDR25.value = 0x0;
        bport1_ab_data.RBDR24.value = 0x0;
        bport1_ab_data.RBDR23.value = 0x0;
        bport1_ab_data.RBDR22.value = 0x0;
        bport1_ab_data.RBDR21.value = 0x0;
        bport1_ab_data.RBDR20.value = 0x0;
        bport1_ab_data.RBDR19.value = 0x0;
        bport1_ab_data.RBDR18.value = 0x0;
        bport1_ab_data.RBDR17.value = 0x0;
        bport1_ab_data.RBDR16.value = 0x0;
        bport1_ab_data.RBDR15.value = 0x0;
        bport1_ab_data.RBDR14.value = 0x0;
        bport1_ab_data.RBDR13.value = 0x0;
        bport1_ab_data.RBDR12.value = 0x0;
        bport1_ab_data.RBDR11.value = 0x0;
        bport1_ab_data.RBDR10.value = 0x0;
        bport1_ab_data.RBDR9.value = 0x0;
        bport1_ab_data.RBDR8.value = 0x0;
        bport1_ab_data.RBDR7.value = 0x0;
        bport1_ab_data.RBDR6.value = 0x0;
        bport1_ab_data.RBDR5.value = 0x0;
        bport1_ab_data.RBDR4.value = 0x0;
        bport1_ab_data.RBDR3.value = 0x0;
        bport1_ab_data.RBDR2.value = 0x0;
        bport1_ab_data.RBDR1.value = 0x0;
        bport1_ab_data.RBDR0.value = 0x0;
        bport1_ab_data.LCKCR.value = 0x2;
        bport1_ab_data.LUTKEY.value = 0x5af05af0;
        bport1_ab_data.SFB2AD.value = 0x0;
        bport1_ab_data.SFB1AD.value = 0x0;
        bport1_ab_data.SFA2AD.value = 0x0;
        bport1_ab_data.SFA1AD.value = 0x0;
        bport1_ab_data.SPTRCLR.value = 0x0;
        bport1_ab_data.SPNDST.value = 0x0;
        bport1_ab_data.RSER.value = 0x0;
        bport1_ab_data.FR.value = 0x8000000;
        bport1_ab_data.SR.value = 0x3800;
        bport1_ab_data.TBDR.value = 0x0;
        bport1_ab_data.TBSR.value = 0x0;
        bport1_ab_data.RBCT.value = 0x0;
        bport1_ab_data.RBSR.value = 0x0;
        bport1_ab_data.SMPR.value = 0x0;
        bport1_ab_data.SFAR.value = 0x0;
        bport1_ab_data.BUF2IND.value = 0x0;
        bport1_ab_data.BUF1IND.value = 0x0;
        bport1_ab_data.BUF0IND.value = 0x0;
        bport1_ab_data.BFGENCR.value = 0x0;
        bport1_ab_data.BUF3CR.value = 0x0;
        bport1_ab_data.BUF2CR.value = 0x0;
        bport1_ab_data.BUF1CR.value = 0x0;
        bport1_ab_data.BUF0CR.value = 0x0;
        bport1_ab_data.FLSHCR.value = 0x303;
        bport1_ab_data.IPCR.value = 0x0;
        bport1_ab_data.MCR.value = 0xf4000;
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

