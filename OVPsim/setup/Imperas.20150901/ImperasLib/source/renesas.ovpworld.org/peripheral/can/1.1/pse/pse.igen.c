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

busPortMR_MR_dataT busPortMR_MR_data;

busPortMDB_MDB_dataT busPortMDB_MDB_data;

busPortMDH_MDH_dataT busPortMDH_MDH_data;

busPortMDW_MDW_dataT busPortMDW_MDW_data;

busPortECC_ECC_dataT busPortECC_ECC_data;

busPortGR_GR_dataT busPortGR_GR_data;

busPortCR_CR_dataT busPortCR_CR_data;

busPortCRW_CRW_dataT busPortCRW_CRW_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "can", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

static PPM_WRITE_CB(write_16) { *(Uns16*)user = data; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA000) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA000.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA100) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA100.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA200) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA200.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA300) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA300.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA400) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA400.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA500) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA500.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA600) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA600.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA700) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA700.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA001) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA001.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA101) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA101.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA201) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA201.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA301) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA301.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA401) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA401.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA501) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA501.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA601) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA601.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA701) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA701.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA002) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA002.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA102) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA102.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA202) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA202.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA302) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA302.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA402) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA402.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA502) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA502.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA602) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA602.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA702) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA702.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA003) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA003.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA103) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA103.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA203) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA203.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA303) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA303.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA403) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA403.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA503) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA503.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA603) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA603.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA703) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA703.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA004) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA004.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA104) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA104.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA204) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA204.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA304) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA304.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA404) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA404.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA504) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA504.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA604) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA604.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA704) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA704.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA005) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA005.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA105) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA105.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA205) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA205.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA305) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA305.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA405) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA405.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA505) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA505.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA605) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA605.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA705) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA705.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA006) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA006.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA106) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA106.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA206) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA206.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA306) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA306.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA406) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA406.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA506) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA506.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA606) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA606.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA706) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA706.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA007) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA007.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA107) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA107.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA207) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA207.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA307) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA307.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA407) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA407.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA507) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA507.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA607) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA607.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA707) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA707.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA008) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA008.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA108) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA108.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA208) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA208.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA308) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA308.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA408) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA408.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA508) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA508.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA608) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA608.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA708) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA708.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA009) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA009.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA109) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA109.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA209) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA209.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA309) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA309.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA409) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA409.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA509) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA509.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA609) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA609.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA709) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA709.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA010) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA010.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA110) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA110.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA210) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA210.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA310) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA310.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA410) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA410.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA510) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA510.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA610) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA610.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA710) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA710.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA011) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA011.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA111) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA111.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA211) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA211.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA311) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA311.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA411) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA411.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA511) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA511.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA611) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA611.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA711) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA711.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA012) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA012.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA112) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA112.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA212) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA212.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA312) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA312.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA412) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA412.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA512) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA512.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA612) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA612.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA712) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA712.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA013) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA013.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA113) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA113.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA213) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA213.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA313) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA313.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA413) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA413.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA513) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA513.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA613) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA613.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA713) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA713.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA014) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA014.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA114) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA114.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA214) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA214.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA314) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA314.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA414) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA414.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA514) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA514.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA614) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA614.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA714) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA714.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA015) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA015.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA115) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA115.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA215) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA215.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA315) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA315.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA415) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA415.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA515) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA515.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA615) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA615.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA715) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA715.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA016) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA016.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA116) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA116.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA216) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA216.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA316) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA316.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA416) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA416.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA516) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA516.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA616) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA616.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA716) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA716.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA017) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA017.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA117) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA117.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA217) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA217.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA317) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA317.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA417) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA417.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA517) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA517.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA617) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA617.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA717) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA717.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA018) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA018.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA118) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA118.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA218) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA218.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA318) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA318.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA418) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA418.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA518) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA518.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA618) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA618.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA718) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA718.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA019) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA019.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA119) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA119.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA219) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA219.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA319) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA319.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA419) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA419.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA519) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA519.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA619) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA619.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA719) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA719.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA020) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA020.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA120) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA120.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA220) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA220.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA320) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA320.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA420) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA420.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA520) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA520.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA620) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA620.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA720) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA720.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA021) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA021.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA121) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA121.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA221) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA221.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA321) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA321.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA421) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA421.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA521) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA521.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA621) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA621.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA721) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA721.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA022) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA022.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA122) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA122.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA222) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA222.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA322) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA322.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA422) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA422.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA522) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA522.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA622) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA622.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA722) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA722.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA023) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA023.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA123) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA123.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA223) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA223.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA323) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA323.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA423) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA423.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA523) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA523.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA623) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA623.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA723) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA723.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA024) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA024.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA124) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA124.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA224) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA224.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA324) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA324.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA424) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA424.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA524) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA524.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA624) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA624.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA724) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA724.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA025) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA025.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA125) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA125.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA225) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA225.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA325) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA325.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA425) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA425.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA525) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA525.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA625) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA625.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA725) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA725.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA026) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA026.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA126) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA126.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA226) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA226.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA326) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA326.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA426) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA426.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA526) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA526.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA626) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA626.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA726) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA726.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA027) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA027.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA127) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA127.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA227) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA227.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA327) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA327.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA427) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA427.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA527) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA527.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA627) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA627.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA727) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA727.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA028) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA028.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA128) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA128.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA228) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA228.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA328) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA328.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA428) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA428.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA528) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA528.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA628) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA628.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA728) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA728.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA029) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA029.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA129) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA129.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA229) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA229.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA329) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA329.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA429) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA429.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA529) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA529.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA629) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA629.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA729) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA729.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA030) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA030.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA130) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA130.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA230) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA230.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA330) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA330.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA430) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA430.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA530) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA530.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA630) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA630.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA730) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA730.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA031) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA031.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA131) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA131.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA231) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA231.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA331) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA331.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA431) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA431.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA531) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA531.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA631) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA631.value;
}

static PPM_VIEW_CB(view_busPortMDB_MDB_MDATA731) {
    *(Uns32*)data = busPortMDB_MDB_data.MDATA731.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0100) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0100.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2300) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2300.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4500) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4500.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6700) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6700.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0101) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0101.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2301) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2301.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4501) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4501.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6701) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6701.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0102) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0102.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2302) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2302.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4502) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4502.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6702) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6702.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0103) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0103.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2303) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2303.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4503) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4503.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6703) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6703.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0104) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0104.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2304) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2304.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4504) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4504.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6704) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6704.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0105) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0105.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2305) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2305.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4505) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4505.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6705) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6705.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0106) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0106.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2306) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2306.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4506) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4506.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6706) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6706.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0107) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0107.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2307) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2307.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4507) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4507.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6707) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6707.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0108) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0108.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2308) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2308.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4508) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4508.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6708) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6708.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0109) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0109.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2309) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2309.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4509) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4509.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6709) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6709.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0110) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0110.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2310) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2310.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4510) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4510.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6710) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6710.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0111) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0111.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2311) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2311.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4511) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4511.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6711) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6711.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0112) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0112.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2312) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2312.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4512) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4512.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6712) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6712.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0113) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0113.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2313) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2313.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4513) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4513.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6713) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6713.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0114) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0114.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2314) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2314.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4514) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4514.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6714) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6714.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0115) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0115.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2315) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2315.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4515) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4515.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6715) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6715.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0116) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0116.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2316) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2316.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4516) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4516.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6716) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6716.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0117) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0117.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2317) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2317.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4517) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4517.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6717) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6717.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0118) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0118.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2318) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2318.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4518) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4518.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6718) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6718.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0119) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0119.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2319) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2319.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4519) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4519.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6719) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6719.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0120) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0120.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2320) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2320.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4520) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4520.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6720) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6720.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0121) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0121.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2321) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2321.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4521) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4521.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6721) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6721.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0122) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0122.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2322) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2322.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4522) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4522.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6722) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6722.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0123) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0123.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2323) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2323.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4523) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4523.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6723) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6723.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0124) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0124.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2324) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2324.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4524) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4524.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6724) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6724.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0125) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0125.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2325) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2325.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4525) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4525.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6725) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6725.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0126) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0126.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2326) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2326.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4526) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4526.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6726) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6726.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0127) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0127.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2327) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2327.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4527) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4527.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6727) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6727.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0128) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0128.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2328) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2328.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4528) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4528.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6728) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6728.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0129) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0129.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2329) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2329.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4529) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4529.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6729) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6729.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0130) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0130.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2330) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2330.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4530) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4530.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6730) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6730.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA0131) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA0131.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA2331) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA2331.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA4531) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA4531.value;
}

static PPM_VIEW_CB(view_busPortMDH_MDH_MDATA6731) {
    *(Uns32*)data = busPortMDH_MDH_data.MDATA6731.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012300) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012300.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456700) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456700.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012301) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012301.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456701) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456701.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012302) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012302.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456702) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456702.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012303) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012303.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456703) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456703.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012304) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012304.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456704) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456704.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012305) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012305.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456705) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456705.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012306) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012306.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456706) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456706.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012307) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012307.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456707) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456707.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012308) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012308.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456708) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456708.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012309) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012309.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456709) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456709.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012310) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012310.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456710) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456710.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012311) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012311.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456711) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456711.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012312) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012312.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456712) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456712.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012313) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012313.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456713) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456713.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012314) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012314.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456714) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456714.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012315) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012315.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456715) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456715.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012316) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012316.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456716) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456716.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012317) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012317.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456717) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456717.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012318) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012318.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456718) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456718.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012319) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012319.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456719) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456719.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012320) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012320.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456720) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456720.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012321) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012321.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456721) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456721.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012322) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012322.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456722) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456722.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012323) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012323.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456723) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456723.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012324) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012324.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456724) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456724.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012325) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012325.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456725) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456725.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012326) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012326.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456726) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456726.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012327) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012327.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456727) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456727.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012328) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012328.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456728) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456728.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012329) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012329.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456729) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456729.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012330) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012330.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456730) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456730.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA012331) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA012331.value;
}

static PPM_VIEW_CB(view_busPortMDW_MDW_MDATA456731) {
    *(Uns32*)data = busPortMDW_MDW_data.MDATA456731.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.busPortMR = ppmCreateSlaveBusPort("busPortMR", 768);
    if (!handles.busPortMR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMR'");
    }

    handles.busPortMDB = ppmCreateSlaveBusPort("busPortMDB", 4096);
    if (!handles.busPortMDB) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMDB'");
    }

    handles.busPortMDH = ppmCreateSlaveBusPort("busPortMDH", 4096);
    if (!handles.busPortMDH) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMDH'");
    }

    handles.busPortMDW = ppmCreateSlaveBusPort("busPortMDW", 4096);
    if (!handles.busPortMDW) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortMDW'");
    }

    handles.busPortECC = ppmCreateSlaveBusPort("busPortECC", 4);
    if (!handles.busPortECC) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortECC'");
    }

    handles.busPortGR = ppmCreateSlaveBusPort("busPortGR", 512);
    if (!handles.busPortGR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortGR'");
    }

    handles.busPortCR = ppmCreateSlaveBusPort("busPortCR", 512);
    if (!handles.busPortCR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortCR'");
    }

    handles.busPortCRW = ppmCreateSlaveBusPort("busPortCRW", 256);
    if (!handles.busPortCRW) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortCRW'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("MR_GMCS",
        0,
        handles.busPortMR,
        8,
        1,
        readGMCS,
        writeGMCS,
        viewGMCS,
        &(busPortMR_MR_data.GMCS.value),
        True
    );
    ppmCreateRegister("MR_GMABTD",
        0,
        handles.busPortMR,
        32,
        1,
        readGMABTD,
        writeGMABTD,
        viewGMABTD,
        &(busPortMR_MR_data.GMABTD.value),
        True
    );
    ppmCreateRegister("MR_LEC",
        0,
        handles.busPortMR,
        584,
        1,
        readLEC,
        writeLEC,
        viewLEC,
        &(busPortMR_MR_data.LEC.value),
        True
    );
    ppmCreateRegister("MR_INFO",
        0,
        handles.busPortMR,
        588,
        1,
        readINFO,
        writeINFO,
        viewINFO,
        &(busPortMR_MR_data.INFO.value),
        True
    );
    ppmCreateRegister("MR_BRP",
        0,
        handles.busPortMR,
        616,
        1,
        readBRP,
        writeBRP,
        viewBRP,
        &(busPortMR_MR_data.BRP.value),
        True
    );
    ppmCreateRegister("MR_LIPT",
        0,
        handles.busPortMR,
        632,
        1,
        readLIPT,
        write_8,
        viewLIPT,
        &(busPortMR_MR_data.LIPT.value),
        True
    );
    ppmCreateRegister("MR_LOPT",
        0,
        handles.busPortMR,
        648,
        1,
        readLOPT,
        write_8,
        viewLOPT,
        &(busPortMR_MR_data.LOPT.value),
        True
    );

    ppmCreateRegister("MDB_MDATA000",
        0,
        handles.busPortMDB,
        0,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA000,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDB_MDATA100",
        0,
        handles.busPortMDB,
        4,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA100,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDB_MDATA200",
        0,
        handles.busPortMDB,
        8,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA200,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDB_MDATA300",
        0,
        handles.busPortMDB,
        12,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA300,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDB_MDATA400",
        0,
        handles.busPortMDB,
        16,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA400,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDB_MDATA500",
        0,
        handles.busPortMDB,
        20,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA500,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDB_MDATA600",
        0,
        handles.busPortMDB,
        24,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA600,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDB_MDATA700",
        0,
        handles.busPortMDB,
        28,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA700,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDB_MDLC00",
        0,
        handles.busPortMDB,
        32,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDB_MCONF00",
        0,
        handles.busPortMDB,
        36,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDB_MDATA001",
        0,
        handles.busPortMDB,
        128,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA001,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDB_MDATA101",
        0,
        handles.busPortMDB,
        132,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA101,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDB_MDATA201",
        0,
        handles.busPortMDB,
        136,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA201,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDB_MDATA301",
        0,
        handles.busPortMDB,
        140,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA301,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDB_MDATA401",
        0,
        handles.busPortMDB,
        144,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA401,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDB_MDATA501",
        0,
        handles.busPortMDB,
        148,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA501,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDB_MDATA601",
        0,
        handles.busPortMDB,
        152,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA601,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDB_MDATA701",
        0,
        handles.busPortMDB,
        156,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA701,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDB_MDLC01",
        0,
        handles.busPortMDB,
        160,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDB_MCONF01",
        0,
        handles.busPortMDB,
        164,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDB_MDATA002",
        0,
        handles.busPortMDB,
        256,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA002,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDB_MDATA102",
        0,
        handles.busPortMDB,
        260,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA102,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDB_MDATA202",
        0,
        handles.busPortMDB,
        264,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA202,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDB_MDATA302",
        0,
        handles.busPortMDB,
        268,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA302,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDB_MDATA402",
        0,
        handles.busPortMDB,
        272,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA402,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDB_MDATA502",
        0,
        handles.busPortMDB,
        276,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA502,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDB_MDATA602",
        0,
        handles.busPortMDB,
        280,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA602,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDB_MDATA702",
        0,
        handles.busPortMDB,
        284,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA702,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDB_MDLC02",
        0,
        handles.busPortMDB,
        288,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDB_MCONF02",
        0,
        handles.busPortMDB,
        292,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDB_MDATA003",
        0,
        handles.busPortMDB,
        384,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA003,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDB_MDATA103",
        0,
        handles.busPortMDB,
        388,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA103,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDB_MDATA203",
        0,
        handles.busPortMDB,
        392,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA203,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDB_MDATA303",
        0,
        handles.busPortMDB,
        396,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA303,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDB_MDATA403",
        0,
        handles.busPortMDB,
        400,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA403,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDB_MDATA503",
        0,
        handles.busPortMDB,
        404,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA503,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDB_MDATA603",
        0,
        handles.busPortMDB,
        408,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA603,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDB_MDATA703",
        0,
        handles.busPortMDB,
        412,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA703,
        (void*)0x1f,
        True
    );
    ppmCreateRegister("MDB_MDLC03",
        0,
        handles.busPortMDB,
        416,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDB_MCONF03",
        0,
        handles.busPortMDB,
        420,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDB_MDATA004",
        0,
        handles.busPortMDB,
        512,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA004,
        (void*)0x20,
        True
    );
    ppmCreateRegister("MDB_MDATA104",
        0,
        handles.busPortMDB,
        516,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA104,
        (void*)0x21,
        True
    );
    ppmCreateRegister("MDB_MDATA204",
        0,
        handles.busPortMDB,
        520,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA204,
        (void*)0x22,
        True
    );
    ppmCreateRegister("MDB_MDATA304",
        0,
        handles.busPortMDB,
        524,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA304,
        (void*)0x23,
        True
    );
    ppmCreateRegister("MDB_MDATA404",
        0,
        handles.busPortMDB,
        528,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA404,
        (void*)0x24,
        True
    );
    ppmCreateRegister("MDB_MDATA504",
        0,
        handles.busPortMDB,
        532,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA504,
        (void*)0x25,
        True
    );
    ppmCreateRegister("MDB_MDATA604",
        0,
        handles.busPortMDB,
        536,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA604,
        (void*)0x26,
        True
    );
    ppmCreateRegister("MDB_MDATA704",
        0,
        handles.busPortMDB,
        540,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA704,
        (void*)0x27,
        True
    );
    ppmCreateRegister("MDB_MDLC04",
        0,
        handles.busPortMDB,
        544,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDB_MCONF04",
        0,
        handles.busPortMDB,
        548,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDB_MDATA005",
        0,
        handles.busPortMDB,
        640,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA005,
        (void*)0x28,
        True
    );
    ppmCreateRegister("MDB_MDATA105",
        0,
        handles.busPortMDB,
        644,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA105,
        (void*)0x29,
        True
    );
    ppmCreateRegister("MDB_MDATA205",
        0,
        handles.busPortMDB,
        648,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA205,
        (void*)0x2a,
        True
    );
    ppmCreateRegister("MDB_MDATA305",
        0,
        handles.busPortMDB,
        652,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA305,
        (void*)0x2b,
        True
    );
    ppmCreateRegister("MDB_MDATA405",
        0,
        handles.busPortMDB,
        656,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA405,
        (void*)0x2c,
        True
    );
    ppmCreateRegister("MDB_MDATA505",
        0,
        handles.busPortMDB,
        660,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA505,
        (void*)0x2d,
        True
    );
    ppmCreateRegister("MDB_MDATA605",
        0,
        handles.busPortMDB,
        664,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA605,
        (void*)0x2e,
        True
    );
    ppmCreateRegister("MDB_MDATA705",
        0,
        handles.busPortMDB,
        668,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA705,
        (void*)0x2f,
        True
    );
    ppmCreateRegister("MDB_MDLC05",
        0,
        handles.busPortMDB,
        672,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDB_MCONF05",
        0,
        handles.busPortMDB,
        676,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDB_MDATA006",
        0,
        handles.busPortMDB,
        768,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA006,
        (void*)0x30,
        True
    );
    ppmCreateRegister("MDB_MDATA106",
        0,
        handles.busPortMDB,
        772,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA106,
        (void*)0x31,
        True
    );
    ppmCreateRegister("MDB_MDATA206",
        0,
        handles.busPortMDB,
        776,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA206,
        (void*)0x32,
        True
    );
    ppmCreateRegister("MDB_MDATA306",
        0,
        handles.busPortMDB,
        780,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA306,
        (void*)0x33,
        True
    );
    ppmCreateRegister("MDB_MDATA406",
        0,
        handles.busPortMDB,
        784,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA406,
        (void*)0x34,
        True
    );
    ppmCreateRegister("MDB_MDATA506",
        0,
        handles.busPortMDB,
        788,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA506,
        (void*)0x35,
        True
    );
    ppmCreateRegister("MDB_MDATA606",
        0,
        handles.busPortMDB,
        792,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA606,
        (void*)0x36,
        True
    );
    ppmCreateRegister("MDB_MDATA706",
        0,
        handles.busPortMDB,
        796,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA706,
        (void*)0x37,
        True
    );
    ppmCreateRegister("MDB_MDLC06",
        0,
        handles.busPortMDB,
        800,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDB_MCONF06",
        0,
        handles.busPortMDB,
        804,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDB_MDATA007",
        0,
        handles.busPortMDB,
        896,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA007,
        (void*)0x38,
        True
    );
    ppmCreateRegister("MDB_MDATA107",
        0,
        handles.busPortMDB,
        900,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA107,
        (void*)0x39,
        True
    );
    ppmCreateRegister("MDB_MDATA207",
        0,
        handles.busPortMDB,
        904,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA207,
        (void*)0x3a,
        True
    );
    ppmCreateRegister("MDB_MDATA307",
        0,
        handles.busPortMDB,
        908,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA307,
        (void*)0x3b,
        True
    );
    ppmCreateRegister("MDB_MDATA407",
        0,
        handles.busPortMDB,
        912,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA407,
        (void*)0x3c,
        True
    );
    ppmCreateRegister("MDB_MDATA507",
        0,
        handles.busPortMDB,
        916,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA507,
        (void*)0x3d,
        True
    );
    ppmCreateRegister("MDB_MDATA607",
        0,
        handles.busPortMDB,
        920,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA607,
        (void*)0x3e,
        True
    );
    ppmCreateRegister("MDB_MDATA707",
        0,
        handles.busPortMDB,
        924,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA707,
        (void*)0x3f,
        True
    );
    ppmCreateRegister("MDB_MDLC07",
        0,
        handles.busPortMDB,
        928,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDB_MCONF07",
        0,
        handles.busPortMDB,
        932,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDB_MDATA008",
        0,
        handles.busPortMDB,
        1024,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA008,
        (void*)0x40,
        True
    );
    ppmCreateRegister("MDB_MDATA108",
        0,
        handles.busPortMDB,
        1028,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA108,
        (void*)0x41,
        True
    );
    ppmCreateRegister("MDB_MDATA208",
        0,
        handles.busPortMDB,
        1032,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA208,
        (void*)0x42,
        True
    );
    ppmCreateRegister("MDB_MDATA308",
        0,
        handles.busPortMDB,
        1036,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA308,
        (void*)0x43,
        True
    );
    ppmCreateRegister("MDB_MDATA408",
        0,
        handles.busPortMDB,
        1040,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA408,
        (void*)0x44,
        True
    );
    ppmCreateRegister("MDB_MDATA508",
        0,
        handles.busPortMDB,
        1044,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA508,
        (void*)0x45,
        True
    );
    ppmCreateRegister("MDB_MDATA608",
        0,
        handles.busPortMDB,
        1048,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA608,
        (void*)0x46,
        True
    );
    ppmCreateRegister("MDB_MDATA708",
        0,
        handles.busPortMDB,
        1052,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA708,
        (void*)0x47,
        True
    );
    ppmCreateRegister("MDB_MDLC08",
        0,
        handles.busPortMDB,
        1056,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDB_MCONF08",
        0,
        handles.busPortMDB,
        1060,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDB_MDATA009",
        0,
        handles.busPortMDB,
        1152,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA009,
        (void*)0x48,
        True
    );
    ppmCreateRegister("MDB_MDATA109",
        0,
        handles.busPortMDB,
        1156,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA109,
        (void*)0x49,
        True
    );
    ppmCreateRegister("MDB_MDATA209",
        0,
        handles.busPortMDB,
        1160,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA209,
        (void*)0x4a,
        True
    );
    ppmCreateRegister("MDB_MDATA309",
        0,
        handles.busPortMDB,
        1164,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA309,
        (void*)0x4b,
        True
    );
    ppmCreateRegister("MDB_MDATA409",
        0,
        handles.busPortMDB,
        1168,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA409,
        (void*)0x4c,
        True
    );
    ppmCreateRegister("MDB_MDATA509",
        0,
        handles.busPortMDB,
        1172,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA509,
        (void*)0x4d,
        True
    );
    ppmCreateRegister("MDB_MDATA609",
        0,
        handles.busPortMDB,
        1176,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA609,
        (void*)0x4e,
        True
    );
    ppmCreateRegister("MDB_MDATA709",
        0,
        handles.busPortMDB,
        1180,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA709,
        (void*)0x4f,
        True
    );
    ppmCreateRegister("MDB_MDLC09",
        0,
        handles.busPortMDB,
        1184,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDB_MCONF09",
        0,
        handles.busPortMDB,
        1188,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDB_MDATA010",
        0,
        handles.busPortMDB,
        1280,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA010,
        (void*)0x50,
        True
    );
    ppmCreateRegister("MDB_MDATA110",
        0,
        handles.busPortMDB,
        1284,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA110,
        (void*)0x51,
        True
    );
    ppmCreateRegister("MDB_MDATA210",
        0,
        handles.busPortMDB,
        1288,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA210,
        (void*)0x52,
        True
    );
    ppmCreateRegister("MDB_MDATA310",
        0,
        handles.busPortMDB,
        1292,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA310,
        (void*)0x53,
        True
    );
    ppmCreateRegister("MDB_MDATA410",
        0,
        handles.busPortMDB,
        1296,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA410,
        (void*)0x54,
        True
    );
    ppmCreateRegister("MDB_MDATA510",
        0,
        handles.busPortMDB,
        1300,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA510,
        (void*)0x55,
        True
    );
    ppmCreateRegister("MDB_MDATA610",
        0,
        handles.busPortMDB,
        1304,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA610,
        (void*)0x56,
        True
    );
    ppmCreateRegister("MDB_MDATA710",
        0,
        handles.busPortMDB,
        1308,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA710,
        (void*)0x57,
        True
    );
    ppmCreateRegister("MDB_MDLC10",
        0,
        handles.busPortMDB,
        1312,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDB_MCONF10",
        0,
        handles.busPortMDB,
        1316,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDB_MDATA011",
        0,
        handles.busPortMDB,
        1408,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA011,
        (void*)0x58,
        True
    );
    ppmCreateRegister("MDB_MDATA111",
        0,
        handles.busPortMDB,
        1412,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA111,
        (void*)0x59,
        True
    );
    ppmCreateRegister("MDB_MDATA211",
        0,
        handles.busPortMDB,
        1416,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA211,
        (void*)0x5a,
        True
    );
    ppmCreateRegister("MDB_MDATA311",
        0,
        handles.busPortMDB,
        1420,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA311,
        (void*)0x5b,
        True
    );
    ppmCreateRegister("MDB_MDATA411",
        0,
        handles.busPortMDB,
        1424,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA411,
        (void*)0x5c,
        True
    );
    ppmCreateRegister("MDB_MDATA511",
        0,
        handles.busPortMDB,
        1428,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA511,
        (void*)0x5d,
        True
    );
    ppmCreateRegister("MDB_MDATA611",
        0,
        handles.busPortMDB,
        1432,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA611,
        (void*)0x5e,
        True
    );
    ppmCreateRegister("MDB_MDATA711",
        0,
        handles.busPortMDB,
        1436,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA711,
        (void*)0x5f,
        True
    );
    ppmCreateRegister("MDB_MDLC11",
        0,
        handles.busPortMDB,
        1440,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDB_MCONF11",
        0,
        handles.busPortMDB,
        1444,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDB_MDATA012",
        0,
        handles.busPortMDB,
        1536,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA012,
        (void*)0x60,
        True
    );
    ppmCreateRegister("MDB_MDATA112",
        0,
        handles.busPortMDB,
        1540,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA112,
        (void*)0x61,
        True
    );
    ppmCreateRegister("MDB_MDATA212",
        0,
        handles.busPortMDB,
        1544,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA212,
        (void*)0x62,
        True
    );
    ppmCreateRegister("MDB_MDATA312",
        0,
        handles.busPortMDB,
        1548,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA312,
        (void*)0x63,
        True
    );
    ppmCreateRegister("MDB_MDATA412",
        0,
        handles.busPortMDB,
        1552,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA412,
        (void*)0x64,
        True
    );
    ppmCreateRegister("MDB_MDATA512",
        0,
        handles.busPortMDB,
        1556,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA512,
        (void*)0x65,
        True
    );
    ppmCreateRegister("MDB_MDATA612",
        0,
        handles.busPortMDB,
        1560,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA612,
        (void*)0x66,
        True
    );
    ppmCreateRegister("MDB_MDATA712",
        0,
        handles.busPortMDB,
        1564,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA712,
        (void*)0x67,
        True
    );
    ppmCreateRegister("MDB_MDLC12",
        0,
        handles.busPortMDB,
        1568,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDB_MCONF12",
        0,
        handles.busPortMDB,
        1572,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDB_MDATA013",
        0,
        handles.busPortMDB,
        1664,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA013,
        (void*)0x68,
        True
    );
    ppmCreateRegister("MDB_MDATA113",
        0,
        handles.busPortMDB,
        1668,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA113,
        (void*)0x69,
        True
    );
    ppmCreateRegister("MDB_MDATA213",
        0,
        handles.busPortMDB,
        1672,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA213,
        (void*)0x6a,
        True
    );
    ppmCreateRegister("MDB_MDATA313",
        0,
        handles.busPortMDB,
        1676,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA313,
        (void*)0x6b,
        True
    );
    ppmCreateRegister("MDB_MDATA413",
        0,
        handles.busPortMDB,
        1680,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA413,
        (void*)0x6c,
        True
    );
    ppmCreateRegister("MDB_MDATA513",
        0,
        handles.busPortMDB,
        1684,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA513,
        (void*)0x6d,
        True
    );
    ppmCreateRegister("MDB_MDATA613",
        0,
        handles.busPortMDB,
        1688,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA613,
        (void*)0x6e,
        True
    );
    ppmCreateRegister("MDB_MDATA713",
        0,
        handles.busPortMDB,
        1692,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA713,
        (void*)0x6f,
        True
    );
    ppmCreateRegister("MDB_MDLC13",
        0,
        handles.busPortMDB,
        1696,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDB_MCONF13",
        0,
        handles.busPortMDB,
        1700,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDB_MDATA014",
        0,
        handles.busPortMDB,
        1792,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA014,
        (void*)0x70,
        True
    );
    ppmCreateRegister("MDB_MDATA114",
        0,
        handles.busPortMDB,
        1796,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA114,
        (void*)0x71,
        True
    );
    ppmCreateRegister("MDB_MDATA214",
        0,
        handles.busPortMDB,
        1800,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA214,
        (void*)0x72,
        True
    );
    ppmCreateRegister("MDB_MDATA314",
        0,
        handles.busPortMDB,
        1804,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA314,
        (void*)0x73,
        True
    );
    ppmCreateRegister("MDB_MDATA414",
        0,
        handles.busPortMDB,
        1808,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA414,
        (void*)0x74,
        True
    );
    ppmCreateRegister("MDB_MDATA514",
        0,
        handles.busPortMDB,
        1812,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA514,
        (void*)0x75,
        True
    );
    ppmCreateRegister("MDB_MDATA614",
        0,
        handles.busPortMDB,
        1816,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA614,
        (void*)0x76,
        True
    );
    ppmCreateRegister("MDB_MDATA714",
        0,
        handles.busPortMDB,
        1820,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA714,
        (void*)0x77,
        True
    );
    ppmCreateRegister("MDB_MDLC14",
        0,
        handles.busPortMDB,
        1824,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDB_MCONF14",
        0,
        handles.busPortMDB,
        1828,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDB_MDATA015",
        0,
        handles.busPortMDB,
        1920,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA015,
        (void*)0x78,
        True
    );
    ppmCreateRegister("MDB_MDATA115",
        0,
        handles.busPortMDB,
        1924,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA115,
        (void*)0x79,
        True
    );
    ppmCreateRegister("MDB_MDATA215",
        0,
        handles.busPortMDB,
        1928,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA215,
        (void*)0x7a,
        True
    );
    ppmCreateRegister("MDB_MDATA315",
        0,
        handles.busPortMDB,
        1932,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA315,
        (void*)0x7b,
        True
    );
    ppmCreateRegister("MDB_MDATA415",
        0,
        handles.busPortMDB,
        1936,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA415,
        (void*)0x7c,
        True
    );
    ppmCreateRegister("MDB_MDATA515",
        0,
        handles.busPortMDB,
        1940,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA515,
        (void*)0x7d,
        True
    );
    ppmCreateRegister("MDB_MDATA615",
        0,
        handles.busPortMDB,
        1944,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA615,
        (void*)0x7e,
        True
    );
    ppmCreateRegister("MDB_MDATA715",
        0,
        handles.busPortMDB,
        1948,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA715,
        (void*)0x7f,
        True
    );
    ppmCreateRegister("MDB_MDLC15",
        0,
        handles.busPortMDB,
        1952,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDB_MCONF15",
        0,
        handles.busPortMDB,
        1956,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDB_MDATA016",
        0,
        handles.busPortMDB,
        2048,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA016,
        (void*)0x80,
        True
    );
    ppmCreateRegister("MDB_MDATA116",
        0,
        handles.busPortMDB,
        2052,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA116,
        (void*)0x81,
        True
    );
    ppmCreateRegister("MDB_MDATA216",
        0,
        handles.busPortMDB,
        2056,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA216,
        (void*)0x82,
        True
    );
    ppmCreateRegister("MDB_MDATA316",
        0,
        handles.busPortMDB,
        2060,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA316,
        (void*)0x83,
        True
    );
    ppmCreateRegister("MDB_MDATA416",
        0,
        handles.busPortMDB,
        2064,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA416,
        (void*)0x84,
        True
    );
    ppmCreateRegister("MDB_MDATA516",
        0,
        handles.busPortMDB,
        2068,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA516,
        (void*)0x85,
        True
    );
    ppmCreateRegister("MDB_MDATA616",
        0,
        handles.busPortMDB,
        2072,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA616,
        (void*)0x86,
        True
    );
    ppmCreateRegister("MDB_MDATA716",
        0,
        handles.busPortMDB,
        2076,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA716,
        (void*)0x87,
        True
    );
    ppmCreateRegister("MDB_MDLC16",
        0,
        handles.busPortMDB,
        2080,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDB_MCONF16",
        0,
        handles.busPortMDB,
        2084,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDB_MDATA017",
        0,
        handles.busPortMDB,
        2176,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA017,
        (void*)0x88,
        True
    );
    ppmCreateRegister("MDB_MDATA117",
        0,
        handles.busPortMDB,
        2180,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA117,
        (void*)0x89,
        True
    );
    ppmCreateRegister("MDB_MDATA217",
        0,
        handles.busPortMDB,
        2184,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA217,
        (void*)0x8a,
        True
    );
    ppmCreateRegister("MDB_MDATA317",
        0,
        handles.busPortMDB,
        2188,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA317,
        (void*)0x8b,
        True
    );
    ppmCreateRegister("MDB_MDATA417",
        0,
        handles.busPortMDB,
        2192,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA417,
        (void*)0x8c,
        True
    );
    ppmCreateRegister("MDB_MDATA517",
        0,
        handles.busPortMDB,
        2196,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA517,
        (void*)0x8d,
        True
    );
    ppmCreateRegister("MDB_MDATA617",
        0,
        handles.busPortMDB,
        2200,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA617,
        (void*)0x8e,
        True
    );
    ppmCreateRegister("MDB_MDATA717",
        0,
        handles.busPortMDB,
        2204,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA717,
        (void*)0x8f,
        True
    );
    ppmCreateRegister("MDB_MDLC17",
        0,
        handles.busPortMDB,
        2208,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDB_MCONF17",
        0,
        handles.busPortMDB,
        2212,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDB_MDATA018",
        0,
        handles.busPortMDB,
        2304,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA018,
        (void*)0x90,
        True
    );
    ppmCreateRegister("MDB_MDATA118",
        0,
        handles.busPortMDB,
        2308,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA118,
        (void*)0x91,
        True
    );
    ppmCreateRegister("MDB_MDATA218",
        0,
        handles.busPortMDB,
        2312,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA218,
        (void*)0x92,
        True
    );
    ppmCreateRegister("MDB_MDATA318",
        0,
        handles.busPortMDB,
        2316,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA318,
        (void*)0x93,
        True
    );
    ppmCreateRegister("MDB_MDATA418",
        0,
        handles.busPortMDB,
        2320,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA418,
        (void*)0x94,
        True
    );
    ppmCreateRegister("MDB_MDATA518",
        0,
        handles.busPortMDB,
        2324,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA518,
        (void*)0x95,
        True
    );
    ppmCreateRegister("MDB_MDATA618",
        0,
        handles.busPortMDB,
        2328,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA618,
        (void*)0x96,
        True
    );
    ppmCreateRegister("MDB_MDATA718",
        0,
        handles.busPortMDB,
        2332,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA718,
        (void*)0x97,
        True
    );
    ppmCreateRegister("MDB_MDLC18",
        0,
        handles.busPortMDB,
        2336,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDB_MCONF18",
        0,
        handles.busPortMDB,
        2340,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDB_MDATA019",
        0,
        handles.busPortMDB,
        2432,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA019,
        (void*)0x98,
        True
    );
    ppmCreateRegister("MDB_MDATA119",
        0,
        handles.busPortMDB,
        2436,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA119,
        (void*)0x99,
        True
    );
    ppmCreateRegister("MDB_MDATA219",
        0,
        handles.busPortMDB,
        2440,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA219,
        (void*)0x9a,
        True
    );
    ppmCreateRegister("MDB_MDATA319",
        0,
        handles.busPortMDB,
        2444,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA319,
        (void*)0x9b,
        True
    );
    ppmCreateRegister("MDB_MDATA419",
        0,
        handles.busPortMDB,
        2448,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA419,
        (void*)0x9c,
        True
    );
    ppmCreateRegister("MDB_MDATA519",
        0,
        handles.busPortMDB,
        2452,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA519,
        (void*)0x9d,
        True
    );
    ppmCreateRegister("MDB_MDATA619",
        0,
        handles.busPortMDB,
        2456,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA619,
        (void*)0x9e,
        True
    );
    ppmCreateRegister("MDB_MDATA719",
        0,
        handles.busPortMDB,
        2460,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA719,
        (void*)0x9f,
        True
    );
    ppmCreateRegister("MDB_MDLC19",
        0,
        handles.busPortMDB,
        2464,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDB_MCONF19",
        0,
        handles.busPortMDB,
        2468,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDB_MDATA020",
        0,
        handles.busPortMDB,
        2560,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA020,
        (void*)0xa0,
        True
    );
    ppmCreateRegister("MDB_MDATA120",
        0,
        handles.busPortMDB,
        2564,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA120,
        (void*)0xa1,
        True
    );
    ppmCreateRegister("MDB_MDATA220",
        0,
        handles.busPortMDB,
        2568,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA220,
        (void*)0xa2,
        True
    );
    ppmCreateRegister("MDB_MDATA320",
        0,
        handles.busPortMDB,
        2572,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA320,
        (void*)0xa3,
        True
    );
    ppmCreateRegister("MDB_MDATA420",
        0,
        handles.busPortMDB,
        2576,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA420,
        (void*)0xa4,
        True
    );
    ppmCreateRegister("MDB_MDATA520",
        0,
        handles.busPortMDB,
        2580,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA520,
        (void*)0xa5,
        True
    );
    ppmCreateRegister("MDB_MDATA620",
        0,
        handles.busPortMDB,
        2584,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA620,
        (void*)0xa6,
        True
    );
    ppmCreateRegister("MDB_MDATA720",
        0,
        handles.busPortMDB,
        2588,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA720,
        (void*)0xa7,
        True
    );
    ppmCreateRegister("MDB_MDLC20",
        0,
        handles.busPortMDB,
        2592,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDB_MCONF20",
        0,
        handles.busPortMDB,
        2596,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDB_MDATA021",
        0,
        handles.busPortMDB,
        2688,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA021,
        (void*)0xa8,
        True
    );
    ppmCreateRegister("MDB_MDATA121",
        0,
        handles.busPortMDB,
        2692,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA121,
        (void*)0xa9,
        True
    );
    ppmCreateRegister("MDB_MDATA221",
        0,
        handles.busPortMDB,
        2696,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA221,
        (void*)0xaa,
        True
    );
    ppmCreateRegister("MDB_MDATA321",
        0,
        handles.busPortMDB,
        2700,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA321,
        (void*)0xab,
        True
    );
    ppmCreateRegister("MDB_MDATA421",
        0,
        handles.busPortMDB,
        2704,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA421,
        (void*)0xac,
        True
    );
    ppmCreateRegister("MDB_MDATA521",
        0,
        handles.busPortMDB,
        2708,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA521,
        (void*)0xad,
        True
    );
    ppmCreateRegister("MDB_MDATA621",
        0,
        handles.busPortMDB,
        2712,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA621,
        (void*)0xae,
        True
    );
    ppmCreateRegister("MDB_MDATA721",
        0,
        handles.busPortMDB,
        2716,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA721,
        (void*)0xaf,
        True
    );
    ppmCreateRegister("MDB_MDLC21",
        0,
        handles.busPortMDB,
        2720,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDB_MCONF21",
        0,
        handles.busPortMDB,
        2724,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDB_MDATA022",
        0,
        handles.busPortMDB,
        2816,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA022,
        (void*)0xb0,
        True
    );
    ppmCreateRegister("MDB_MDATA122",
        0,
        handles.busPortMDB,
        2820,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA122,
        (void*)0xb1,
        True
    );
    ppmCreateRegister("MDB_MDATA222",
        0,
        handles.busPortMDB,
        2824,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA222,
        (void*)0xb2,
        True
    );
    ppmCreateRegister("MDB_MDATA322",
        0,
        handles.busPortMDB,
        2828,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA322,
        (void*)0xb3,
        True
    );
    ppmCreateRegister("MDB_MDATA422",
        0,
        handles.busPortMDB,
        2832,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA422,
        (void*)0xb4,
        True
    );
    ppmCreateRegister("MDB_MDATA522",
        0,
        handles.busPortMDB,
        2836,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA522,
        (void*)0xb5,
        True
    );
    ppmCreateRegister("MDB_MDATA622",
        0,
        handles.busPortMDB,
        2840,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA622,
        (void*)0xb6,
        True
    );
    ppmCreateRegister("MDB_MDATA722",
        0,
        handles.busPortMDB,
        2844,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA722,
        (void*)0xb7,
        True
    );
    ppmCreateRegister("MDB_MDLC22",
        0,
        handles.busPortMDB,
        2848,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDB_MCONF22",
        0,
        handles.busPortMDB,
        2852,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDB_MDATA023",
        0,
        handles.busPortMDB,
        2944,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA023,
        (void*)0xb8,
        True
    );
    ppmCreateRegister("MDB_MDATA123",
        0,
        handles.busPortMDB,
        2948,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA123,
        (void*)0xb9,
        True
    );
    ppmCreateRegister("MDB_MDATA223",
        0,
        handles.busPortMDB,
        2952,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA223,
        (void*)0xba,
        True
    );
    ppmCreateRegister("MDB_MDATA323",
        0,
        handles.busPortMDB,
        2956,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA323,
        (void*)0xbb,
        True
    );
    ppmCreateRegister("MDB_MDATA423",
        0,
        handles.busPortMDB,
        2960,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA423,
        (void*)0xbc,
        True
    );
    ppmCreateRegister("MDB_MDATA523",
        0,
        handles.busPortMDB,
        2964,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA523,
        (void*)0xbd,
        True
    );
    ppmCreateRegister("MDB_MDATA623",
        0,
        handles.busPortMDB,
        2968,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA623,
        (void*)0xbe,
        True
    );
    ppmCreateRegister("MDB_MDATA723",
        0,
        handles.busPortMDB,
        2972,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA723,
        (void*)0xbf,
        True
    );
    ppmCreateRegister("MDB_MDLC23",
        0,
        handles.busPortMDB,
        2976,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDB_MCONF23",
        0,
        handles.busPortMDB,
        2980,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDB_MDATA024",
        0,
        handles.busPortMDB,
        3072,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA024,
        (void*)0xc0,
        True
    );
    ppmCreateRegister("MDB_MDATA124",
        0,
        handles.busPortMDB,
        3076,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA124,
        (void*)0xc1,
        True
    );
    ppmCreateRegister("MDB_MDATA224",
        0,
        handles.busPortMDB,
        3080,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA224,
        (void*)0xc2,
        True
    );
    ppmCreateRegister("MDB_MDATA324",
        0,
        handles.busPortMDB,
        3084,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA324,
        (void*)0xc3,
        True
    );
    ppmCreateRegister("MDB_MDATA424",
        0,
        handles.busPortMDB,
        3088,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA424,
        (void*)0xc4,
        True
    );
    ppmCreateRegister("MDB_MDATA524",
        0,
        handles.busPortMDB,
        3092,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA524,
        (void*)0xc5,
        True
    );
    ppmCreateRegister("MDB_MDATA624",
        0,
        handles.busPortMDB,
        3096,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA624,
        (void*)0xc6,
        True
    );
    ppmCreateRegister("MDB_MDATA724",
        0,
        handles.busPortMDB,
        3100,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA724,
        (void*)0xc7,
        True
    );
    ppmCreateRegister("MDB_MDLC24",
        0,
        handles.busPortMDB,
        3104,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDB_MCONF24",
        0,
        handles.busPortMDB,
        3108,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDB_MDATA025",
        0,
        handles.busPortMDB,
        3200,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA025,
        (void*)0xc8,
        True
    );
    ppmCreateRegister("MDB_MDATA125",
        0,
        handles.busPortMDB,
        3204,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA125,
        (void*)0xc9,
        True
    );
    ppmCreateRegister("MDB_MDATA225",
        0,
        handles.busPortMDB,
        3208,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA225,
        (void*)0xca,
        True
    );
    ppmCreateRegister("MDB_MDATA325",
        0,
        handles.busPortMDB,
        3212,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA325,
        (void*)0xcb,
        True
    );
    ppmCreateRegister("MDB_MDATA425",
        0,
        handles.busPortMDB,
        3216,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA425,
        (void*)0xcc,
        True
    );
    ppmCreateRegister("MDB_MDATA525",
        0,
        handles.busPortMDB,
        3220,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA525,
        (void*)0xcd,
        True
    );
    ppmCreateRegister("MDB_MDATA625",
        0,
        handles.busPortMDB,
        3224,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA625,
        (void*)0xce,
        True
    );
    ppmCreateRegister("MDB_MDATA725",
        0,
        handles.busPortMDB,
        3228,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA725,
        (void*)0xcf,
        True
    );
    ppmCreateRegister("MDB_MDLC25",
        0,
        handles.busPortMDB,
        3232,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDB_MCONF25",
        0,
        handles.busPortMDB,
        3236,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDB_MDATA026",
        0,
        handles.busPortMDB,
        3328,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA026,
        (void*)0xd0,
        True
    );
    ppmCreateRegister("MDB_MDATA126",
        0,
        handles.busPortMDB,
        3332,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA126,
        (void*)0xd1,
        True
    );
    ppmCreateRegister("MDB_MDATA226",
        0,
        handles.busPortMDB,
        3336,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA226,
        (void*)0xd2,
        True
    );
    ppmCreateRegister("MDB_MDATA326",
        0,
        handles.busPortMDB,
        3340,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA326,
        (void*)0xd3,
        True
    );
    ppmCreateRegister("MDB_MDATA426",
        0,
        handles.busPortMDB,
        3344,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA426,
        (void*)0xd4,
        True
    );
    ppmCreateRegister("MDB_MDATA526",
        0,
        handles.busPortMDB,
        3348,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA526,
        (void*)0xd5,
        True
    );
    ppmCreateRegister("MDB_MDATA626",
        0,
        handles.busPortMDB,
        3352,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA626,
        (void*)0xd6,
        True
    );
    ppmCreateRegister("MDB_MDATA726",
        0,
        handles.busPortMDB,
        3356,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA726,
        (void*)0xd7,
        True
    );
    ppmCreateRegister("MDB_MDLC26",
        0,
        handles.busPortMDB,
        3360,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDB_MCONF26",
        0,
        handles.busPortMDB,
        3364,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDB_MDATA027",
        0,
        handles.busPortMDB,
        3456,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA027,
        (void*)0xd8,
        True
    );
    ppmCreateRegister("MDB_MDATA127",
        0,
        handles.busPortMDB,
        3460,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA127,
        (void*)0xd9,
        True
    );
    ppmCreateRegister("MDB_MDATA227",
        0,
        handles.busPortMDB,
        3464,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA227,
        (void*)0xda,
        True
    );
    ppmCreateRegister("MDB_MDATA327",
        0,
        handles.busPortMDB,
        3468,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA327,
        (void*)0xdb,
        True
    );
    ppmCreateRegister("MDB_MDATA427",
        0,
        handles.busPortMDB,
        3472,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA427,
        (void*)0xdc,
        True
    );
    ppmCreateRegister("MDB_MDATA527",
        0,
        handles.busPortMDB,
        3476,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA527,
        (void*)0xdd,
        True
    );
    ppmCreateRegister("MDB_MDATA627",
        0,
        handles.busPortMDB,
        3480,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA627,
        (void*)0xde,
        True
    );
    ppmCreateRegister("MDB_MDATA727",
        0,
        handles.busPortMDB,
        3484,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA727,
        (void*)0xdf,
        True
    );
    ppmCreateRegister("MDB_MDLC27",
        0,
        handles.busPortMDB,
        3488,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDB_MCONF27",
        0,
        handles.busPortMDB,
        3492,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDB_MDATA028",
        0,
        handles.busPortMDB,
        3584,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA028,
        (void*)0xe0,
        True
    );
    ppmCreateRegister("MDB_MDATA128",
        0,
        handles.busPortMDB,
        3588,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA128,
        (void*)0xe1,
        True
    );
    ppmCreateRegister("MDB_MDATA228",
        0,
        handles.busPortMDB,
        3592,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA228,
        (void*)0xe2,
        True
    );
    ppmCreateRegister("MDB_MDATA328",
        0,
        handles.busPortMDB,
        3596,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA328,
        (void*)0xe3,
        True
    );
    ppmCreateRegister("MDB_MDATA428",
        0,
        handles.busPortMDB,
        3600,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA428,
        (void*)0xe4,
        True
    );
    ppmCreateRegister("MDB_MDATA528",
        0,
        handles.busPortMDB,
        3604,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA528,
        (void*)0xe5,
        True
    );
    ppmCreateRegister("MDB_MDATA628",
        0,
        handles.busPortMDB,
        3608,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA628,
        (void*)0xe6,
        True
    );
    ppmCreateRegister("MDB_MDATA728",
        0,
        handles.busPortMDB,
        3612,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA728,
        (void*)0xe7,
        True
    );
    ppmCreateRegister("MDB_MDLC28",
        0,
        handles.busPortMDB,
        3616,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDB_MCONF28",
        0,
        handles.busPortMDB,
        3620,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDB_MDATA029",
        0,
        handles.busPortMDB,
        3712,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA029,
        (void*)0xe8,
        True
    );
    ppmCreateRegister("MDB_MDATA129",
        0,
        handles.busPortMDB,
        3716,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA129,
        (void*)0xe9,
        True
    );
    ppmCreateRegister("MDB_MDATA229",
        0,
        handles.busPortMDB,
        3720,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA229,
        (void*)0xea,
        True
    );
    ppmCreateRegister("MDB_MDATA329",
        0,
        handles.busPortMDB,
        3724,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA329,
        (void*)0xeb,
        True
    );
    ppmCreateRegister("MDB_MDATA429",
        0,
        handles.busPortMDB,
        3728,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA429,
        (void*)0xec,
        True
    );
    ppmCreateRegister("MDB_MDATA529",
        0,
        handles.busPortMDB,
        3732,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA529,
        (void*)0xed,
        True
    );
    ppmCreateRegister("MDB_MDATA629",
        0,
        handles.busPortMDB,
        3736,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA629,
        (void*)0xee,
        True
    );
    ppmCreateRegister("MDB_MDATA729",
        0,
        handles.busPortMDB,
        3740,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA729,
        (void*)0xef,
        True
    );
    ppmCreateRegister("MDB_MDLC29",
        0,
        handles.busPortMDB,
        3744,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDB_MCONF29",
        0,
        handles.busPortMDB,
        3748,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDB_MDATA030",
        0,
        handles.busPortMDB,
        3840,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA030,
        (void*)0xf0,
        True
    );
    ppmCreateRegister("MDB_MDATA130",
        0,
        handles.busPortMDB,
        3844,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA130,
        (void*)0xf1,
        True
    );
    ppmCreateRegister("MDB_MDATA230",
        0,
        handles.busPortMDB,
        3848,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA230,
        (void*)0xf2,
        True
    );
    ppmCreateRegister("MDB_MDATA330",
        0,
        handles.busPortMDB,
        3852,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA330,
        (void*)0xf3,
        True
    );
    ppmCreateRegister("MDB_MDATA430",
        0,
        handles.busPortMDB,
        3856,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA430,
        (void*)0xf4,
        True
    );
    ppmCreateRegister("MDB_MDATA530",
        0,
        handles.busPortMDB,
        3860,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA530,
        (void*)0xf5,
        True
    );
    ppmCreateRegister("MDB_MDATA630",
        0,
        handles.busPortMDB,
        3864,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA630,
        (void*)0xf6,
        True
    );
    ppmCreateRegister("MDB_MDATA730",
        0,
        handles.busPortMDB,
        3868,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA730,
        (void*)0xf7,
        True
    );
    ppmCreateRegister("MDB_MDLC30",
        0,
        handles.busPortMDB,
        3872,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDB_MCONF30",
        0,
        handles.busPortMDB,
        3876,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDB_MDATA031",
        0,
        handles.busPortMDB,
        3968,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA031,
        (void*)0xf8,
        True
    );
    ppmCreateRegister("MDB_MDATA131",
        0,
        handles.busPortMDB,
        3972,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA131,
        (void*)0xf9,
        True
    );
    ppmCreateRegister("MDB_MDATA231",
        0,
        handles.busPortMDB,
        3976,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA231,
        (void*)0xfa,
        True
    );
    ppmCreateRegister("MDB_MDATA331",
        0,
        handles.busPortMDB,
        3980,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA331,
        (void*)0xfb,
        True
    );
    ppmCreateRegister("MDB_MDATA431",
        0,
        handles.busPortMDB,
        3984,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA431,
        (void*)0xfc,
        True
    );
    ppmCreateRegister("MDB_MDATA531",
        0,
        handles.busPortMDB,
        3988,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA531,
        (void*)0xfd,
        True
    );
    ppmCreateRegister("MDB_MDATA631",
        0,
        handles.busPortMDB,
        3992,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA631,
        (void*)0xfe,
        True
    );
    ppmCreateRegister("MDB_MDATA731",
        0,
        handles.busPortMDB,
        3996,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDB_MDB_MDATA731,
        (void*)0xff,
        True
    );
    ppmCreateRegister("MDB_MDLC31",
        0,
        handles.busPortMDB,
        4000,
        4,
        readMDLC,
        writeMDLC,
        viewMDLC,
        (void*)0x1f,
        True
    );
    ppmCreateRegister("MDB_MCONF31",
        0,
        handles.busPortMDB,
        4004,
        4,
        readMCONF,
        writeMCONF,
        viewMCONF,
        (void*)0x1f,
        True
    );

    ppmCreateRegister("MDH_MDATA0100",
        0,
        handles.busPortMDH,
        0,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0100,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDH_MDATA2300",
        0,
        handles.busPortMDH,
        8,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2300,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDH_MDATA4500",
        0,
        handles.busPortMDH,
        16,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4500,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDH_MDATA6700",
        0,
        handles.busPortMDH,
        24,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6700,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDH_MIDL00",
        0,
        handles.busPortMDH,
        40,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDH_MIDH00",
        0,
        handles.busPortMDH,
        48,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDH_MCTRL00",
        0,
        handles.busPortMDH,
        56,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDH_MDATA0101",
        0,
        handles.busPortMDH,
        128,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0101,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDH_MDATA2301",
        0,
        handles.busPortMDH,
        136,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2301,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDH_MDATA4501",
        0,
        handles.busPortMDH,
        144,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4501,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDH_MDATA6701",
        0,
        handles.busPortMDH,
        152,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6701,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDH_MIDL01",
        0,
        handles.busPortMDH,
        168,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDH_MIDH01",
        0,
        handles.busPortMDH,
        176,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDH_MCTRL01",
        0,
        handles.busPortMDH,
        184,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDH_MDATA0102",
        0,
        handles.busPortMDH,
        256,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0102,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDH_MDATA2302",
        0,
        handles.busPortMDH,
        264,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2302,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDH_MDATA4502",
        0,
        handles.busPortMDH,
        272,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4502,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDH_MDATA6702",
        0,
        handles.busPortMDH,
        280,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6702,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDH_MIDL02",
        0,
        handles.busPortMDH,
        296,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDH_MIDH02",
        0,
        handles.busPortMDH,
        304,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDH_MCTRL02",
        0,
        handles.busPortMDH,
        312,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDH_MDATA0103",
        0,
        handles.busPortMDH,
        384,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0103,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDH_MDATA2303",
        0,
        handles.busPortMDH,
        392,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2303,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDH_MDATA4503",
        0,
        handles.busPortMDH,
        400,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4503,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDH_MDATA6703",
        0,
        handles.busPortMDH,
        408,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6703,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDH_MIDL03",
        0,
        handles.busPortMDH,
        424,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDH_MIDH03",
        0,
        handles.busPortMDH,
        432,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDH_MCTRL03",
        0,
        handles.busPortMDH,
        440,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDH_MDATA0104",
        0,
        handles.busPortMDH,
        512,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0104,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDH_MDATA2304",
        0,
        handles.busPortMDH,
        520,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2304,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDH_MDATA4504",
        0,
        handles.busPortMDH,
        528,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4504,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDH_MDATA6704",
        0,
        handles.busPortMDH,
        536,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6704,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDH_MIDL04",
        0,
        handles.busPortMDH,
        552,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDH_MIDH04",
        0,
        handles.busPortMDH,
        560,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDH_MCTRL04",
        0,
        handles.busPortMDH,
        568,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDH_MDATA0105",
        0,
        handles.busPortMDH,
        640,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0105,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDH_MDATA2305",
        0,
        handles.busPortMDH,
        648,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2305,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDH_MDATA4505",
        0,
        handles.busPortMDH,
        656,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4505,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDH_MDATA6705",
        0,
        handles.busPortMDH,
        664,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6705,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDH_MIDL05",
        0,
        handles.busPortMDH,
        680,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDH_MIDH05",
        0,
        handles.busPortMDH,
        688,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDH_MCTRL05",
        0,
        handles.busPortMDH,
        696,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDH_MDATA0106",
        0,
        handles.busPortMDH,
        768,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0106,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDH_MDATA2306",
        0,
        handles.busPortMDH,
        776,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2306,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDH_MDATA4506",
        0,
        handles.busPortMDH,
        784,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4506,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDH_MDATA6706",
        0,
        handles.busPortMDH,
        792,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6706,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDH_MIDL06",
        0,
        handles.busPortMDH,
        808,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDH_MIDH06",
        0,
        handles.busPortMDH,
        816,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDH_MCTRL06",
        0,
        handles.busPortMDH,
        824,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDH_MDATA0107",
        0,
        handles.busPortMDH,
        896,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0107,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDH_MDATA2307",
        0,
        handles.busPortMDH,
        904,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2307,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDH_MDATA4507",
        0,
        handles.busPortMDH,
        912,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4507,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDH_MDATA6707",
        0,
        handles.busPortMDH,
        920,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6707,
        (void*)0x1f,
        True
    );
    ppmCreateRegister("MDH_MIDL07",
        0,
        handles.busPortMDH,
        936,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDH_MIDH07",
        0,
        handles.busPortMDH,
        944,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDH_MCTRL07",
        0,
        handles.busPortMDH,
        952,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDH_MDATA0108",
        0,
        handles.busPortMDH,
        1024,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0108,
        (void*)0x20,
        True
    );
    ppmCreateRegister("MDH_MDATA2308",
        0,
        handles.busPortMDH,
        1032,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2308,
        (void*)0x21,
        True
    );
    ppmCreateRegister("MDH_MDATA4508",
        0,
        handles.busPortMDH,
        1040,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4508,
        (void*)0x22,
        True
    );
    ppmCreateRegister("MDH_MDATA6708",
        0,
        handles.busPortMDH,
        1048,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6708,
        (void*)0x23,
        True
    );
    ppmCreateRegister("MDH_MIDL08",
        0,
        handles.busPortMDH,
        1064,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDH_MIDH08",
        0,
        handles.busPortMDH,
        1072,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDH_MCTRL08",
        0,
        handles.busPortMDH,
        1080,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDH_MDATA0109",
        0,
        handles.busPortMDH,
        1152,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0109,
        (void*)0x24,
        True
    );
    ppmCreateRegister("MDH_MDATA2309",
        0,
        handles.busPortMDH,
        1160,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2309,
        (void*)0x25,
        True
    );
    ppmCreateRegister("MDH_MDATA4509",
        0,
        handles.busPortMDH,
        1168,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4509,
        (void*)0x26,
        True
    );
    ppmCreateRegister("MDH_MDATA6709",
        0,
        handles.busPortMDH,
        1176,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6709,
        (void*)0x27,
        True
    );
    ppmCreateRegister("MDH_MIDL09",
        0,
        handles.busPortMDH,
        1192,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDH_MIDH09",
        0,
        handles.busPortMDH,
        1200,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDH_MCTRL09",
        0,
        handles.busPortMDH,
        1208,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDH_MDATA0110",
        0,
        handles.busPortMDH,
        1280,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0110,
        (void*)0x28,
        True
    );
    ppmCreateRegister("MDH_MDATA2310",
        0,
        handles.busPortMDH,
        1288,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2310,
        (void*)0x29,
        True
    );
    ppmCreateRegister("MDH_MDATA4510",
        0,
        handles.busPortMDH,
        1296,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4510,
        (void*)0x2a,
        True
    );
    ppmCreateRegister("MDH_MDATA6710",
        0,
        handles.busPortMDH,
        1304,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6710,
        (void*)0x2b,
        True
    );
    ppmCreateRegister("MDH_MIDL10",
        0,
        handles.busPortMDH,
        1320,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDH_MIDH10",
        0,
        handles.busPortMDH,
        1328,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDH_MCTRL10",
        0,
        handles.busPortMDH,
        1336,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDH_MDATA0111",
        0,
        handles.busPortMDH,
        1408,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0111,
        (void*)0x2c,
        True
    );
    ppmCreateRegister("MDH_MDATA2311",
        0,
        handles.busPortMDH,
        1416,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2311,
        (void*)0x2d,
        True
    );
    ppmCreateRegister("MDH_MDATA4511",
        0,
        handles.busPortMDH,
        1424,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4511,
        (void*)0x2e,
        True
    );
    ppmCreateRegister("MDH_MDATA6711",
        0,
        handles.busPortMDH,
        1432,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6711,
        (void*)0x2f,
        True
    );
    ppmCreateRegister("MDH_MIDL11",
        0,
        handles.busPortMDH,
        1448,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDH_MIDH11",
        0,
        handles.busPortMDH,
        1456,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDH_MCTRL11",
        0,
        handles.busPortMDH,
        1464,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDH_MDATA0112",
        0,
        handles.busPortMDH,
        1536,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0112,
        (void*)0x30,
        True
    );
    ppmCreateRegister("MDH_MDATA2312",
        0,
        handles.busPortMDH,
        1544,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2312,
        (void*)0x31,
        True
    );
    ppmCreateRegister("MDH_MDATA4512",
        0,
        handles.busPortMDH,
        1552,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4512,
        (void*)0x32,
        True
    );
    ppmCreateRegister("MDH_MDATA6712",
        0,
        handles.busPortMDH,
        1560,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6712,
        (void*)0x33,
        True
    );
    ppmCreateRegister("MDH_MIDL12",
        0,
        handles.busPortMDH,
        1576,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDH_MIDH12",
        0,
        handles.busPortMDH,
        1584,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDH_MCTRL12",
        0,
        handles.busPortMDH,
        1592,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDH_MDATA0113",
        0,
        handles.busPortMDH,
        1664,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0113,
        (void*)0x34,
        True
    );
    ppmCreateRegister("MDH_MDATA2313",
        0,
        handles.busPortMDH,
        1672,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2313,
        (void*)0x35,
        True
    );
    ppmCreateRegister("MDH_MDATA4513",
        0,
        handles.busPortMDH,
        1680,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4513,
        (void*)0x36,
        True
    );
    ppmCreateRegister("MDH_MDATA6713",
        0,
        handles.busPortMDH,
        1688,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6713,
        (void*)0x37,
        True
    );
    ppmCreateRegister("MDH_MIDL13",
        0,
        handles.busPortMDH,
        1704,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDH_MIDH13",
        0,
        handles.busPortMDH,
        1712,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDH_MCTRL13",
        0,
        handles.busPortMDH,
        1720,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDH_MDATA0114",
        0,
        handles.busPortMDH,
        1792,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0114,
        (void*)0x38,
        True
    );
    ppmCreateRegister("MDH_MDATA2314",
        0,
        handles.busPortMDH,
        1800,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2314,
        (void*)0x39,
        True
    );
    ppmCreateRegister("MDH_MDATA4514",
        0,
        handles.busPortMDH,
        1808,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4514,
        (void*)0x3a,
        True
    );
    ppmCreateRegister("MDH_MDATA6714",
        0,
        handles.busPortMDH,
        1816,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6714,
        (void*)0x3b,
        True
    );
    ppmCreateRegister("MDH_MIDL14",
        0,
        handles.busPortMDH,
        1832,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDH_MIDH14",
        0,
        handles.busPortMDH,
        1840,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDH_MCTRL14",
        0,
        handles.busPortMDH,
        1848,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDH_MDATA0115",
        0,
        handles.busPortMDH,
        1920,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0115,
        (void*)0x3c,
        True
    );
    ppmCreateRegister("MDH_MDATA2315",
        0,
        handles.busPortMDH,
        1928,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2315,
        (void*)0x3d,
        True
    );
    ppmCreateRegister("MDH_MDATA4515",
        0,
        handles.busPortMDH,
        1936,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4515,
        (void*)0x3e,
        True
    );
    ppmCreateRegister("MDH_MDATA6715",
        0,
        handles.busPortMDH,
        1944,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6715,
        (void*)0x3f,
        True
    );
    ppmCreateRegister("MDH_MIDL15",
        0,
        handles.busPortMDH,
        1960,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDH_MIDH15",
        0,
        handles.busPortMDH,
        1968,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDH_MCTRL15",
        0,
        handles.busPortMDH,
        1976,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDH_MDATA0116",
        0,
        handles.busPortMDH,
        2048,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0116,
        (void*)0x40,
        True
    );
    ppmCreateRegister("MDH_MDATA2316",
        0,
        handles.busPortMDH,
        2056,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2316,
        (void*)0x41,
        True
    );
    ppmCreateRegister("MDH_MDATA4516",
        0,
        handles.busPortMDH,
        2064,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4516,
        (void*)0x42,
        True
    );
    ppmCreateRegister("MDH_MDATA6716",
        0,
        handles.busPortMDH,
        2072,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6716,
        (void*)0x43,
        True
    );
    ppmCreateRegister("MDH_MIDL16",
        0,
        handles.busPortMDH,
        2088,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDH_MIDH16",
        0,
        handles.busPortMDH,
        2096,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDH_MCTRL16",
        0,
        handles.busPortMDH,
        2104,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDH_MDATA0117",
        0,
        handles.busPortMDH,
        2176,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0117,
        (void*)0x44,
        True
    );
    ppmCreateRegister("MDH_MDATA2317",
        0,
        handles.busPortMDH,
        2184,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2317,
        (void*)0x45,
        True
    );
    ppmCreateRegister("MDH_MDATA4517",
        0,
        handles.busPortMDH,
        2192,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4517,
        (void*)0x46,
        True
    );
    ppmCreateRegister("MDH_MDATA6717",
        0,
        handles.busPortMDH,
        2200,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6717,
        (void*)0x47,
        True
    );
    ppmCreateRegister("MDH_MIDL17",
        0,
        handles.busPortMDH,
        2216,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDH_MIDH17",
        0,
        handles.busPortMDH,
        2224,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDH_MCTRL17",
        0,
        handles.busPortMDH,
        2232,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDH_MDATA0118",
        0,
        handles.busPortMDH,
        2304,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0118,
        (void*)0x48,
        True
    );
    ppmCreateRegister("MDH_MDATA2318",
        0,
        handles.busPortMDH,
        2312,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2318,
        (void*)0x49,
        True
    );
    ppmCreateRegister("MDH_MDATA4518",
        0,
        handles.busPortMDH,
        2320,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4518,
        (void*)0x4a,
        True
    );
    ppmCreateRegister("MDH_MDATA6718",
        0,
        handles.busPortMDH,
        2328,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6718,
        (void*)0x4b,
        True
    );
    ppmCreateRegister("MDH_MIDL18",
        0,
        handles.busPortMDH,
        2344,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDH_MIDH18",
        0,
        handles.busPortMDH,
        2352,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDH_MCTRL18",
        0,
        handles.busPortMDH,
        2360,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDH_MDATA0119",
        0,
        handles.busPortMDH,
        2432,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0119,
        (void*)0x4c,
        True
    );
    ppmCreateRegister("MDH_MDATA2319",
        0,
        handles.busPortMDH,
        2440,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2319,
        (void*)0x4d,
        True
    );
    ppmCreateRegister("MDH_MDATA4519",
        0,
        handles.busPortMDH,
        2448,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4519,
        (void*)0x4e,
        True
    );
    ppmCreateRegister("MDH_MDATA6719",
        0,
        handles.busPortMDH,
        2456,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6719,
        (void*)0x4f,
        True
    );
    ppmCreateRegister("MDH_MIDL19",
        0,
        handles.busPortMDH,
        2472,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDH_MIDH19",
        0,
        handles.busPortMDH,
        2480,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDH_MCTRL19",
        0,
        handles.busPortMDH,
        2488,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDH_MDATA0120",
        0,
        handles.busPortMDH,
        2560,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0120,
        (void*)0x50,
        True
    );
    ppmCreateRegister("MDH_MDATA2320",
        0,
        handles.busPortMDH,
        2568,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2320,
        (void*)0x51,
        True
    );
    ppmCreateRegister("MDH_MDATA4520",
        0,
        handles.busPortMDH,
        2576,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4520,
        (void*)0x52,
        True
    );
    ppmCreateRegister("MDH_MDATA6720",
        0,
        handles.busPortMDH,
        2584,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6720,
        (void*)0x53,
        True
    );
    ppmCreateRegister("MDH_MIDL20",
        0,
        handles.busPortMDH,
        2600,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDH_MIDH20",
        0,
        handles.busPortMDH,
        2608,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDH_MCTRL20",
        0,
        handles.busPortMDH,
        2616,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDH_MDATA0121",
        0,
        handles.busPortMDH,
        2688,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0121,
        (void*)0x54,
        True
    );
    ppmCreateRegister("MDH_MDATA2321",
        0,
        handles.busPortMDH,
        2696,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2321,
        (void*)0x55,
        True
    );
    ppmCreateRegister("MDH_MDATA4521",
        0,
        handles.busPortMDH,
        2704,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4521,
        (void*)0x56,
        True
    );
    ppmCreateRegister("MDH_MDATA6721",
        0,
        handles.busPortMDH,
        2712,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6721,
        (void*)0x57,
        True
    );
    ppmCreateRegister("MDH_MIDL21",
        0,
        handles.busPortMDH,
        2728,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDH_MIDH21",
        0,
        handles.busPortMDH,
        2736,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDH_MCTRL21",
        0,
        handles.busPortMDH,
        2744,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDH_MDATA0122",
        0,
        handles.busPortMDH,
        2816,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0122,
        (void*)0x58,
        True
    );
    ppmCreateRegister("MDH_MDATA2322",
        0,
        handles.busPortMDH,
        2824,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2322,
        (void*)0x59,
        True
    );
    ppmCreateRegister("MDH_MDATA4522",
        0,
        handles.busPortMDH,
        2832,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4522,
        (void*)0x5a,
        True
    );
    ppmCreateRegister("MDH_MDATA6722",
        0,
        handles.busPortMDH,
        2840,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6722,
        (void*)0x5b,
        True
    );
    ppmCreateRegister("MDH_MIDL22",
        0,
        handles.busPortMDH,
        2856,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDH_MIDH22",
        0,
        handles.busPortMDH,
        2864,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDH_MCTRL22",
        0,
        handles.busPortMDH,
        2872,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDH_MDATA0123",
        0,
        handles.busPortMDH,
        2944,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0123,
        (void*)0x5c,
        True
    );
    ppmCreateRegister("MDH_MDATA2323",
        0,
        handles.busPortMDH,
        2952,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2323,
        (void*)0x5d,
        True
    );
    ppmCreateRegister("MDH_MDATA4523",
        0,
        handles.busPortMDH,
        2960,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4523,
        (void*)0x5e,
        True
    );
    ppmCreateRegister("MDH_MDATA6723",
        0,
        handles.busPortMDH,
        2968,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6723,
        (void*)0x5f,
        True
    );
    ppmCreateRegister("MDH_MIDL23",
        0,
        handles.busPortMDH,
        2984,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDH_MIDH23",
        0,
        handles.busPortMDH,
        2992,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDH_MCTRL23",
        0,
        handles.busPortMDH,
        3000,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDH_MDATA0124",
        0,
        handles.busPortMDH,
        3072,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0124,
        (void*)0x60,
        True
    );
    ppmCreateRegister("MDH_MDATA2324",
        0,
        handles.busPortMDH,
        3080,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2324,
        (void*)0x61,
        True
    );
    ppmCreateRegister("MDH_MDATA4524",
        0,
        handles.busPortMDH,
        3088,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4524,
        (void*)0x62,
        True
    );
    ppmCreateRegister("MDH_MDATA6724",
        0,
        handles.busPortMDH,
        3096,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6724,
        (void*)0x63,
        True
    );
    ppmCreateRegister("MDH_MIDL24",
        0,
        handles.busPortMDH,
        3112,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDH_MIDH24",
        0,
        handles.busPortMDH,
        3120,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDH_MCTRL24",
        0,
        handles.busPortMDH,
        3128,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDH_MDATA0125",
        0,
        handles.busPortMDH,
        3200,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0125,
        (void*)0x64,
        True
    );
    ppmCreateRegister("MDH_MDATA2325",
        0,
        handles.busPortMDH,
        3208,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2325,
        (void*)0x65,
        True
    );
    ppmCreateRegister("MDH_MDATA4525",
        0,
        handles.busPortMDH,
        3216,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4525,
        (void*)0x66,
        True
    );
    ppmCreateRegister("MDH_MDATA6725",
        0,
        handles.busPortMDH,
        3224,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6725,
        (void*)0x67,
        True
    );
    ppmCreateRegister("MDH_MIDL25",
        0,
        handles.busPortMDH,
        3240,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDH_MIDH25",
        0,
        handles.busPortMDH,
        3248,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDH_MCTRL25",
        0,
        handles.busPortMDH,
        3256,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDH_MDATA0126",
        0,
        handles.busPortMDH,
        3328,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0126,
        (void*)0x68,
        True
    );
    ppmCreateRegister("MDH_MDATA2326",
        0,
        handles.busPortMDH,
        3336,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2326,
        (void*)0x69,
        True
    );
    ppmCreateRegister("MDH_MDATA4526",
        0,
        handles.busPortMDH,
        3344,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4526,
        (void*)0x6a,
        True
    );
    ppmCreateRegister("MDH_MDATA6726",
        0,
        handles.busPortMDH,
        3352,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6726,
        (void*)0x6b,
        True
    );
    ppmCreateRegister("MDH_MIDL26",
        0,
        handles.busPortMDH,
        3368,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDH_MIDH26",
        0,
        handles.busPortMDH,
        3376,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDH_MCTRL26",
        0,
        handles.busPortMDH,
        3384,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDH_MDATA0127",
        0,
        handles.busPortMDH,
        3456,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0127,
        (void*)0x6c,
        True
    );
    ppmCreateRegister("MDH_MDATA2327",
        0,
        handles.busPortMDH,
        3464,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2327,
        (void*)0x6d,
        True
    );
    ppmCreateRegister("MDH_MDATA4527",
        0,
        handles.busPortMDH,
        3472,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4527,
        (void*)0x6e,
        True
    );
    ppmCreateRegister("MDH_MDATA6727",
        0,
        handles.busPortMDH,
        3480,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6727,
        (void*)0x6f,
        True
    );
    ppmCreateRegister("MDH_MIDL27",
        0,
        handles.busPortMDH,
        3496,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDH_MIDH27",
        0,
        handles.busPortMDH,
        3504,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDH_MCTRL27",
        0,
        handles.busPortMDH,
        3512,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDH_MDATA0128",
        0,
        handles.busPortMDH,
        3584,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0128,
        (void*)0x70,
        True
    );
    ppmCreateRegister("MDH_MDATA2328",
        0,
        handles.busPortMDH,
        3592,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2328,
        (void*)0x71,
        True
    );
    ppmCreateRegister("MDH_MDATA4528",
        0,
        handles.busPortMDH,
        3600,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4528,
        (void*)0x72,
        True
    );
    ppmCreateRegister("MDH_MDATA6728",
        0,
        handles.busPortMDH,
        3608,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6728,
        (void*)0x73,
        True
    );
    ppmCreateRegister("MDH_MIDL28",
        0,
        handles.busPortMDH,
        3624,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDH_MIDH28",
        0,
        handles.busPortMDH,
        3632,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDH_MCTRL28",
        0,
        handles.busPortMDH,
        3640,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDH_MDATA0129",
        0,
        handles.busPortMDH,
        3712,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0129,
        (void*)0x74,
        True
    );
    ppmCreateRegister("MDH_MDATA2329",
        0,
        handles.busPortMDH,
        3720,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2329,
        (void*)0x75,
        True
    );
    ppmCreateRegister("MDH_MDATA4529",
        0,
        handles.busPortMDH,
        3728,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4529,
        (void*)0x76,
        True
    );
    ppmCreateRegister("MDH_MDATA6729",
        0,
        handles.busPortMDH,
        3736,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6729,
        (void*)0x77,
        True
    );
    ppmCreateRegister("MDH_MIDL29",
        0,
        handles.busPortMDH,
        3752,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDH_MIDH29",
        0,
        handles.busPortMDH,
        3760,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDH_MCTRL29",
        0,
        handles.busPortMDH,
        3768,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDH_MDATA0130",
        0,
        handles.busPortMDH,
        3840,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0130,
        (void*)0x78,
        True
    );
    ppmCreateRegister("MDH_MDATA2330",
        0,
        handles.busPortMDH,
        3848,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2330,
        (void*)0x79,
        True
    );
    ppmCreateRegister("MDH_MDATA4530",
        0,
        handles.busPortMDH,
        3856,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4530,
        (void*)0x7a,
        True
    );
    ppmCreateRegister("MDH_MDATA6730",
        0,
        handles.busPortMDH,
        3864,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6730,
        (void*)0x7b,
        True
    );
    ppmCreateRegister("MDH_MIDL30",
        0,
        handles.busPortMDH,
        3880,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDH_MIDH30",
        0,
        handles.busPortMDH,
        3888,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDH_MCTRL30",
        0,
        handles.busPortMDH,
        3896,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDH_MDATA0131",
        0,
        handles.busPortMDH,
        3968,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA0131,
        (void*)0x7c,
        True
    );
    ppmCreateRegister("MDH_MDATA2331",
        0,
        handles.busPortMDH,
        3976,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA2331,
        (void*)0x7d,
        True
    );
    ppmCreateRegister("MDH_MDATA4531",
        0,
        handles.busPortMDH,
        3984,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA4531,
        (void*)0x7e,
        True
    );
    ppmCreateRegister("MDH_MDATA6731",
        0,
        handles.busPortMDH,
        3992,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDH_MDH_MDATA6731,
        (void*)0x7f,
        True
    );
    ppmCreateRegister("MDH_MIDL31",
        0,
        handles.busPortMDH,
        4008,
        2,
        readMIDL,
        writeMIDL,
        viewMIDL,
        (void*)0x1f,
        True
    );
    ppmCreateRegister("MDH_MIDH31",
        0,
        handles.busPortMDH,
        4016,
        2,
        readMIDH,
        writeMIDH,
        viewMIDH,
        (void*)0x1f,
        True
    );
    ppmCreateRegister("MDH_MCTRL31",
        0,
        handles.busPortMDH,
        4024,
        2,
        readMCTRL,
        writeMCTRL,
        viewMCTRL,
        (void*)0x1f,
        True
    );

    ppmCreateRegister("MDW_MDATA012300",
        0,
        handles.busPortMDW,
        0,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012300,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDW_MDATA456700",
        0,
        handles.busPortMDW,
        16,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456700,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDW_MID00",
        0,
        handles.busPortMDW,
        32,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x0,
        True
    );
    ppmCreateRegister("MDW_MDATA012301",
        0,
        handles.busPortMDW,
        128,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012301,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDW_MDATA456701",
        0,
        handles.busPortMDW,
        144,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456701,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDW_MID01",
        0,
        handles.busPortMDW,
        160,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1,
        True
    );
    ppmCreateRegister("MDW_MDATA012302",
        0,
        handles.busPortMDW,
        256,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012302,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDW_MDATA456702",
        0,
        handles.busPortMDW,
        272,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456702,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDW_MID02",
        0,
        handles.busPortMDW,
        288,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x2,
        True
    );
    ppmCreateRegister("MDW_MDATA012303",
        0,
        handles.busPortMDW,
        384,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012303,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDW_MDATA456703",
        0,
        handles.busPortMDW,
        400,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456703,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDW_MID03",
        0,
        handles.busPortMDW,
        416,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x3,
        True
    );
    ppmCreateRegister("MDW_MDATA012304",
        0,
        handles.busPortMDW,
        512,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012304,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDW_MDATA456704",
        0,
        handles.busPortMDW,
        528,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456704,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDW_MID04",
        0,
        handles.busPortMDW,
        544,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x4,
        True
    );
    ppmCreateRegister("MDW_MDATA012305",
        0,
        handles.busPortMDW,
        640,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012305,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDW_MDATA456705",
        0,
        handles.busPortMDW,
        656,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456705,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDW_MID05",
        0,
        handles.busPortMDW,
        672,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x5,
        True
    );
    ppmCreateRegister("MDW_MDATA012306",
        0,
        handles.busPortMDW,
        768,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012306,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDW_MDATA456706",
        0,
        handles.busPortMDW,
        784,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456706,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDW_MID06",
        0,
        handles.busPortMDW,
        800,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x6,
        True
    );
    ppmCreateRegister("MDW_MDATA012307",
        0,
        handles.busPortMDW,
        896,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012307,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDW_MDATA456707",
        0,
        handles.busPortMDW,
        912,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456707,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDW_MID07",
        0,
        handles.busPortMDW,
        928,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x7,
        True
    );
    ppmCreateRegister("MDW_MDATA012308",
        0,
        handles.busPortMDW,
        1024,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012308,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDW_MDATA456708",
        0,
        handles.busPortMDW,
        1040,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456708,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDW_MID08",
        0,
        handles.busPortMDW,
        1056,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x8,
        True
    );
    ppmCreateRegister("MDW_MDATA012309",
        0,
        handles.busPortMDW,
        1152,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012309,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDW_MDATA456709",
        0,
        handles.busPortMDW,
        1168,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456709,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDW_MID09",
        0,
        handles.busPortMDW,
        1184,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x9,
        True
    );
    ppmCreateRegister("MDW_MDATA012310",
        0,
        handles.busPortMDW,
        1280,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012310,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDW_MDATA456710",
        0,
        handles.busPortMDW,
        1296,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456710,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDW_MID10",
        0,
        handles.busPortMDW,
        1312,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0xa,
        True
    );
    ppmCreateRegister("MDW_MDATA012311",
        0,
        handles.busPortMDW,
        1408,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012311,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDW_MDATA456711",
        0,
        handles.busPortMDW,
        1424,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456711,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDW_MID11",
        0,
        handles.busPortMDW,
        1440,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0xb,
        True
    );
    ppmCreateRegister("MDW_MDATA012312",
        0,
        handles.busPortMDW,
        1536,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012312,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDW_MDATA456712",
        0,
        handles.busPortMDW,
        1552,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456712,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDW_MID12",
        0,
        handles.busPortMDW,
        1568,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0xc,
        True
    );
    ppmCreateRegister("MDW_MDATA012313",
        0,
        handles.busPortMDW,
        1664,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012313,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDW_MDATA456713",
        0,
        handles.busPortMDW,
        1680,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456713,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDW_MID13",
        0,
        handles.busPortMDW,
        1696,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0xd,
        True
    );
    ppmCreateRegister("MDW_MDATA012314",
        0,
        handles.busPortMDW,
        1792,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012314,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDW_MDATA456714",
        0,
        handles.busPortMDW,
        1808,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456714,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDW_MID14",
        0,
        handles.busPortMDW,
        1824,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0xe,
        True
    );
    ppmCreateRegister("MDW_MDATA012315",
        0,
        handles.busPortMDW,
        1920,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012315,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDW_MDATA456715",
        0,
        handles.busPortMDW,
        1936,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456715,
        (void*)0x1f,
        True
    );
    ppmCreateRegister("MDW_MID15",
        0,
        handles.busPortMDW,
        1952,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0xf,
        True
    );
    ppmCreateRegister("MDW_MDATA012316",
        0,
        handles.busPortMDW,
        2048,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012316,
        (void*)0x20,
        True
    );
    ppmCreateRegister("MDW_MDATA456716",
        0,
        handles.busPortMDW,
        2064,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456716,
        (void*)0x21,
        True
    );
    ppmCreateRegister("MDW_MID16",
        0,
        handles.busPortMDW,
        2080,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x10,
        True
    );
    ppmCreateRegister("MDW_MDATA012317",
        0,
        handles.busPortMDW,
        2176,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012317,
        (void*)0x22,
        True
    );
    ppmCreateRegister("MDW_MDATA456717",
        0,
        handles.busPortMDW,
        2192,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456717,
        (void*)0x23,
        True
    );
    ppmCreateRegister("MDW_MID17",
        0,
        handles.busPortMDW,
        2208,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x11,
        True
    );
    ppmCreateRegister("MDW_MDATA012318",
        0,
        handles.busPortMDW,
        2304,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012318,
        (void*)0x24,
        True
    );
    ppmCreateRegister("MDW_MDATA456718",
        0,
        handles.busPortMDW,
        2320,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456718,
        (void*)0x25,
        True
    );
    ppmCreateRegister("MDW_MID18",
        0,
        handles.busPortMDW,
        2336,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x12,
        True
    );
    ppmCreateRegister("MDW_MDATA012319",
        0,
        handles.busPortMDW,
        2432,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012319,
        (void*)0x26,
        True
    );
    ppmCreateRegister("MDW_MDATA456719",
        0,
        handles.busPortMDW,
        2448,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456719,
        (void*)0x27,
        True
    );
    ppmCreateRegister("MDW_MID19",
        0,
        handles.busPortMDW,
        2464,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x13,
        True
    );
    ppmCreateRegister("MDW_MDATA012320",
        0,
        handles.busPortMDW,
        2560,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012320,
        (void*)0x28,
        True
    );
    ppmCreateRegister("MDW_MDATA456720",
        0,
        handles.busPortMDW,
        2576,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456720,
        (void*)0x29,
        True
    );
    ppmCreateRegister("MDW_MID20",
        0,
        handles.busPortMDW,
        2592,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x14,
        True
    );
    ppmCreateRegister("MDW_MDATA012321",
        0,
        handles.busPortMDW,
        2688,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012321,
        (void*)0x2a,
        True
    );
    ppmCreateRegister("MDW_MDATA456721",
        0,
        handles.busPortMDW,
        2704,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456721,
        (void*)0x2b,
        True
    );
    ppmCreateRegister("MDW_MID21",
        0,
        handles.busPortMDW,
        2720,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x15,
        True
    );
    ppmCreateRegister("MDW_MDATA012322",
        0,
        handles.busPortMDW,
        2816,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012322,
        (void*)0x2c,
        True
    );
    ppmCreateRegister("MDW_MDATA456722",
        0,
        handles.busPortMDW,
        2832,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456722,
        (void*)0x2d,
        True
    );
    ppmCreateRegister("MDW_MID22",
        0,
        handles.busPortMDW,
        2848,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x16,
        True
    );
    ppmCreateRegister("MDW_MDATA012323",
        0,
        handles.busPortMDW,
        2944,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012323,
        (void*)0x2e,
        True
    );
    ppmCreateRegister("MDW_MDATA456723",
        0,
        handles.busPortMDW,
        2960,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456723,
        (void*)0x2f,
        True
    );
    ppmCreateRegister("MDW_MID23",
        0,
        handles.busPortMDW,
        2976,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x17,
        True
    );
    ppmCreateRegister("MDW_MDATA012324",
        0,
        handles.busPortMDW,
        3072,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012324,
        (void*)0x30,
        True
    );
    ppmCreateRegister("MDW_MDATA456724",
        0,
        handles.busPortMDW,
        3088,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456724,
        (void*)0x31,
        True
    );
    ppmCreateRegister("MDW_MID24",
        0,
        handles.busPortMDW,
        3104,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x18,
        True
    );
    ppmCreateRegister("MDW_MDATA012325",
        0,
        handles.busPortMDW,
        3200,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012325,
        (void*)0x32,
        True
    );
    ppmCreateRegister("MDW_MDATA456725",
        0,
        handles.busPortMDW,
        3216,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456725,
        (void*)0x33,
        True
    );
    ppmCreateRegister("MDW_MID25",
        0,
        handles.busPortMDW,
        3232,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x19,
        True
    );
    ppmCreateRegister("MDW_MDATA012326",
        0,
        handles.busPortMDW,
        3328,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012326,
        (void*)0x34,
        True
    );
    ppmCreateRegister("MDW_MDATA456726",
        0,
        handles.busPortMDW,
        3344,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456726,
        (void*)0x35,
        True
    );
    ppmCreateRegister("MDW_MID26",
        0,
        handles.busPortMDW,
        3360,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1a,
        True
    );
    ppmCreateRegister("MDW_MDATA012327",
        0,
        handles.busPortMDW,
        3456,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012327,
        (void*)0x36,
        True
    );
    ppmCreateRegister("MDW_MDATA456727",
        0,
        handles.busPortMDW,
        3472,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456727,
        (void*)0x37,
        True
    );
    ppmCreateRegister("MDW_MID27",
        0,
        handles.busPortMDW,
        3488,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1b,
        True
    );
    ppmCreateRegister("MDW_MDATA012328",
        0,
        handles.busPortMDW,
        3584,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012328,
        (void*)0x38,
        True
    );
    ppmCreateRegister("MDW_MDATA456728",
        0,
        handles.busPortMDW,
        3600,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456728,
        (void*)0x39,
        True
    );
    ppmCreateRegister("MDW_MID28",
        0,
        handles.busPortMDW,
        3616,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1c,
        True
    );
    ppmCreateRegister("MDW_MDATA012329",
        0,
        handles.busPortMDW,
        3712,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012329,
        (void*)0x3a,
        True
    );
    ppmCreateRegister("MDW_MDATA456729",
        0,
        handles.busPortMDW,
        3728,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456729,
        (void*)0x3b,
        True
    );
    ppmCreateRegister("MDW_MID29",
        0,
        handles.busPortMDW,
        3744,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1d,
        True
    );
    ppmCreateRegister("MDW_MDATA012330",
        0,
        handles.busPortMDW,
        3840,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012330,
        (void*)0x3c,
        True
    );
    ppmCreateRegister("MDW_MDATA456730",
        0,
        handles.busPortMDW,
        3856,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456730,
        (void*)0x3d,
        True
    );
    ppmCreateRegister("MDW_MID30",
        0,
        handles.busPortMDW,
        3872,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1e,
        True
    );
    ppmCreateRegister("MDW_MDATA012331",
        0,
        handles.busPortMDW,
        3968,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA012331,
        (void*)0x3e,
        True
    );
    ppmCreateRegister("MDW_MDATA456731",
        0,
        handles.busPortMDW,
        3984,
        4,
        readMDATA,
        writeMDATA,
        view_busPortMDW_MDW_MDATA456731,
        (void*)0x3f,
        True
    );
    ppmCreateRegister("MDW_MID31",
        0,
        handles.busPortMDW,
        4000,
        4,
        readMID,
        writeMID,
        viewMID,
        (void*)0x1f,
        True
    );

    ppmCreateRegister("ECC_E6A0CTL",
        0,
        handles.busPortECC,
        0,
        2,
        readE6A0CTL,
        writeE6A0CTL,
        viewE6A0CTL,
        &(busPortECC_ECC_data.E6A0CTL.value),
        True
    );

    ppmCreateRegister("GR_GMCTRL",
        0,
        handles.busPortGR,
        0,
        2,
        readGMCTRL,
        writeGMCTRL,
        viewGMCTRL,
        &(busPortGR_GR_data.GMCTRL.value),
        True
    );
    ppmCreateRegister("GR_GMABT",
        0,
        handles.busPortGR,
        24,
        2,
        readGMABT,
        writeGMABT,
        viewGMABT,
        &(busPortGR_GR_data.GMABT.value),
        True
    );
    ppmCreateRegister("GR_GMCONF",
        0,
        handles.busPortGR,
        16,
        2,
        readGMCONF,
        write_16,
        viewGMCONF,
        &(busPortGR_GR_data.GMCONF.value),
        True
    );

    ppmCreateRegister("CR_MASK1L",
        0,
        handles.busPortCR,
        0,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x1,
        True
    );
    ppmCreateRegister("CR_MASK1H",
        0,
        handles.busPortCR,
        8,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x1,
        True
    );
    ppmCreateRegister("CR_MASK2L",
        0,
        handles.busPortCR,
        16,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x2,
        True
    );
    ppmCreateRegister("CR_MASK2H",
        0,
        handles.busPortCR,
        24,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x2,
        True
    );
    ppmCreateRegister("CR_MASK3L",
        0,
        handles.busPortCR,
        32,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x3,
        True
    );
    ppmCreateRegister("CR_MASK3H",
        0,
        handles.busPortCR,
        40,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x3,
        True
    );
    ppmCreateRegister("CR_MASK4L",
        0,
        handles.busPortCR,
        48,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x4,
        True
    );
    ppmCreateRegister("CR_MASK4H",
        0,
        handles.busPortCR,
        56,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x4,
        True
    );
    ppmCreateRegister("CR_CTRL",
        0,
        handles.busPortCR,
        64,
        2,
        readCTRL,
        writeCTRL,
        viewCTRL,
        &(busPortCR_CR_data.CTRL.value),
        True
    );
    ppmCreateRegister("CR_ERC",
        0,
        handles.busPortCR,
        80,
        2,
        readERC,
        writeERC,
        viewERC,
        &(busPortCR_CR_data.ERC.value),
        True
    );
    ppmCreateRegister("CR_IE",
        0,
        handles.busPortCR,
        88,
        2,
        readIE,
        writeIE,
        viewIE,
        &(busPortCR_CR_data.IE.value),
        True
    );
    ppmCreateRegister("CR_INTS",
        0,
        handles.busPortCR,
        96,
        2,
        readINTS,
        writeINTS,
        viewINTS,
        &(busPortCR_CR_data.INTS.value),
        True
    );
    ppmCreateRegister("CR_BTR",
        0,
        handles.busPortCR,
        112,
        2,
        readBTR,
        writeBTR,
        viewBTR,
        &(busPortCR_CR_data.BTR.value),
        True
    );
    ppmCreateRegister("CR_RGPT",
        0,
        handles.busPortCR,
        128,
        2,
        readRGPT,
        writeRGPT,
        viewRGPT,
        &(busPortCR_CR_data.RGPT.value),
        True
    );
    ppmCreateRegister("CR_TGPT",
        0,
        handles.busPortCR,
        144,
        2,
        readTGPT,
        writeTGPT,
        viewTGPT,
        &(busPortCR_CR_data.TGPT.value),
        True
    );
    ppmCreateRegister("CR_TS",
        0,
        handles.busPortCR,
        152,
        2,
        readTS,
        writeTS,
        viewTS,
        &(busPortCR_CR_data.TS.value),
        True
    );

    ppmCreateRegister("CRW_MASK1",
        0,
        handles.busPortCRW,
        0,
        2,
        readMASK,
        writeMASK,
        viewMASK,
        (void*)0x1,
        True
    );
    ppmCreateRegister("CRW_MASK2",
        0,
        handles.busPortCRW,
        16,
        2,
        readMASK,
        writeMASK,
        viewMASK,
        (void*)0x2,
        True
    );
    ppmCreateRegister("CRW_MASK3",
        0,
        handles.busPortCRW,
        32,
        2,
        readMASK,
        writeMASK,
        viewMASK,
        (void*)0x3,
        True
    );
    ppmCreateRegister("CRW_MASK4",
        0,
        handles.busPortCRW,
        48,
        2,
        readMASK,
        writeMASK,
        viewMASK,
        (void*)0x4,
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.INTTRX, value);

    handles.INTTRX = ppmOpenNetPort("INTTRX");

// To write to this net, use ppmWriteNet(handles.INTREC, value);

    handles.INTREC = ppmOpenNetPort("INTREC");

// To write to this net, use ppmWriteNet(handles.INTERR, value);

    handles.INTERR = ppmOpenNetPort("INTERR");

// To write to this net, use ppmWriteNet(handles.INTWUP, value);

    handles.INTWUP = ppmOpenNetPort("INTWUP");

}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Renesas CAN interface. This is an interface between the CAN controller register interface and a PacketNet can interface.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No CRC generation or checking.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "VFOREST: R01UH0021EJ0200, Rev. 2.00, Aug 5, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

