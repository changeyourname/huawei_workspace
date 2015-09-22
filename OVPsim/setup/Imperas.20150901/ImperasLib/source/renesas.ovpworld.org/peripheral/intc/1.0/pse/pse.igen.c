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

INTCP0_reg0_dataT INTCP0_reg0_data;

INTCP0_reg1_dataT INTCP0_reg1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "intc", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.INTCP0 = ppmCreateSlaveBusPort("INTCP0", 252);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_IMR0",
        0,
        handles.INTCP0,
        0,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR0.value),
        True
    );
    ppmCreateRegister("reg0_IMR1",
        0,
        handles.INTCP0,
        2,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR1.value),
        True
    );
    ppmCreateRegister("reg0_IMR2",
        0,
        handles.INTCP0,
        4,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR2.value),
        True
    );
    ppmCreateRegister("reg0_IMR3",
        0,
        handles.INTCP0,
        6,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR3.value),
        True
    );
    ppmCreateRegister("reg0_IMR4",
        0,
        handles.INTCP0,
        8,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR4.value),
        True
    );
    ppmCreateRegister("reg0_IMR5",
        0,
        handles.INTCP0,
        10,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR5.value),
        True
    );
    ppmCreateRegister("reg0_IMR6",
        0,
        handles.INTCP0,
        12,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR6.value),
        True
    );
    ppmCreateRegister("reg0_IMR7",
        0,
        handles.INTCP0,
        14,
        2,
        readIMR,
        writeIMR,
        view16,
        &(INTCP0_reg0_data.IMR7.value),
        True
    );
    ppmCreateRegister("reg1_IC000",
        0,
        handles.INTCP0,
        16,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC000.value),
        True
    );
    ppmCreateRegister("reg1_IC001",
        0,
        handles.INTCP0,
        18,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC001.value),
        True
    );
    ppmCreateRegister("reg1_IC002",
        0,
        handles.INTCP0,
        20,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC002.value),
        True
    );
    ppmCreateRegister("reg1_IC003",
        0,
        handles.INTCP0,
        22,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC003.value),
        True
    );
    ppmCreateRegister("reg1_IC004",
        0,
        handles.INTCP0,
        24,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC004.value),
        True
    );
    ppmCreateRegister("reg1_IC005",
        0,
        handles.INTCP0,
        26,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC005.value),
        True
    );
    ppmCreateRegister("reg1_IC006",
        0,
        handles.INTCP0,
        28,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC006.value),
        True
    );
    ppmCreateRegister("reg1_IC007",
        0,
        handles.INTCP0,
        30,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC007.value),
        True
    );
    ppmCreateRegister("reg1_IC008",
        0,
        handles.INTCP0,
        32,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC008.value),
        True
    );
    ppmCreateRegister("reg1_IC009",
        0,
        handles.INTCP0,
        34,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC009.value),
        True
    );
    ppmCreateRegister("reg1_IC010",
        0,
        handles.INTCP0,
        36,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC010.value),
        True
    );
    ppmCreateRegister("reg1_IC011",
        0,
        handles.INTCP0,
        38,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC011.value),
        True
    );
    ppmCreateRegister("reg1_IC012",
        0,
        handles.INTCP0,
        40,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC012.value),
        True
    );
    ppmCreateRegister("reg1_IC013",
        0,
        handles.INTCP0,
        42,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC013.value),
        True
    );
    ppmCreateRegister("reg1_IC014",
        0,
        handles.INTCP0,
        44,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC014.value),
        True
    );
    ppmCreateRegister("reg1_IC015",
        0,
        handles.INTCP0,
        46,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC015.value),
        True
    );
    ppmCreateRegister("reg1_IC016",
        0,
        handles.INTCP0,
        48,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC016.value),
        True
    );
    ppmCreateRegister("reg1_IC017",
        0,
        handles.INTCP0,
        50,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC017.value),
        True
    );
    ppmCreateRegister("reg1_IC018",
        0,
        handles.INTCP0,
        52,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC018.value),
        True
    );
    ppmCreateRegister("reg1_IC019",
        0,
        handles.INTCP0,
        54,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC019.value),
        True
    );
    ppmCreateRegister("reg1_IC020",
        0,
        handles.INTCP0,
        56,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC020.value),
        True
    );
    ppmCreateRegister("reg1_IC021",
        0,
        handles.INTCP0,
        58,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC021.value),
        True
    );
    ppmCreateRegister("reg1_IC022",
        0,
        handles.INTCP0,
        60,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC022.value),
        True
    );
    ppmCreateRegister("reg1_IC023",
        0,
        handles.INTCP0,
        62,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC023.value),
        True
    );
    ppmCreateRegister("reg1_IC024",
        0,
        handles.INTCP0,
        64,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC024.value),
        True
    );
    ppmCreateRegister("reg1_IC025",
        0,
        handles.INTCP0,
        66,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC025.value),
        True
    );
    ppmCreateRegister("reg1_IC026",
        0,
        handles.INTCP0,
        68,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC026.value),
        True
    );
    ppmCreateRegister("reg1_IC027",
        0,
        handles.INTCP0,
        70,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC027.value),
        True
    );
    ppmCreateRegister("reg1_IC028",
        0,
        handles.INTCP0,
        72,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC028.value),
        True
    );
    ppmCreateRegister("reg1_IC029",
        0,
        handles.INTCP0,
        74,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC029.value),
        True
    );
    ppmCreateRegister("reg1_IC030",
        0,
        handles.INTCP0,
        76,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC030.value),
        True
    );
    ppmCreateRegister("reg1_IC031",
        0,
        handles.INTCP0,
        78,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC031.value),
        True
    );
    ppmCreateRegister("reg1_IC032",
        0,
        handles.INTCP0,
        80,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC032.value),
        True
    );
    ppmCreateRegister("reg1_IC033",
        0,
        handles.INTCP0,
        82,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC033.value),
        True
    );
    ppmCreateRegister("reg1_IC034",
        0,
        handles.INTCP0,
        84,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC034.value),
        True
    );
    ppmCreateRegister("reg1_IC035",
        0,
        handles.INTCP0,
        86,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC035.value),
        True
    );
    ppmCreateRegister("reg1_IC036",
        0,
        handles.INTCP0,
        88,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC036.value),
        True
    );
    ppmCreateRegister("reg1_IC037",
        0,
        handles.INTCP0,
        90,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC037.value),
        True
    );
    ppmCreateRegister("reg1_IC038",
        0,
        handles.INTCP0,
        92,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC038.value),
        True
    );
    ppmCreateRegister("reg1_IC039",
        0,
        handles.INTCP0,
        94,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC039.value),
        True
    );
    ppmCreateRegister("reg1_IC040",
        0,
        handles.INTCP0,
        96,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC040.value),
        True
    );
    ppmCreateRegister("reg1_IC041",
        0,
        handles.INTCP0,
        98,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC041.value),
        True
    );
    ppmCreateRegister("reg1_IC042",
        0,
        handles.INTCP0,
        100,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC042.value),
        True
    );
    ppmCreateRegister("reg1_IC043",
        0,
        handles.INTCP0,
        102,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC043.value),
        True
    );
    ppmCreateRegister("reg1_IC044",
        0,
        handles.INTCP0,
        104,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC044.value),
        True
    );
    ppmCreateRegister("reg1_IC045",
        0,
        handles.INTCP0,
        106,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC045.value),
        True
    );
    ppmCreateRegister("reg1_IC046",
        0,
        handles.INTCP0,
        108,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC046.value),
        True
    );
    ppmCreateRegister("reg1_IC047",
        0,
        handles.INTCP0,
        110,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC047.value),
        True
    );
    ppmCreateRegister("reg1_IC048",
        0,
        handles.INTCP0,
        112,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC048.value),
        True
    );
    ppmCreateRegister("reg1_IC049",
        0,
        handles.INTCP0,
        114,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC049.value),
        True
    );
    ppmCreateRegister("reg1_IC050",
        0,
        handles.INTCP0,
        116,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC050.value),
        True
    );
    ppmCreateRegister("reg1_IC051",
        0,
        handles.INTCP0,
        118,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC051.value),
        True
    );
    ppmCreateRegister("reg1_IC052",
        0,
        handles.INTCP0,
        120,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC052.value),
        True
    );
    ppmCreateRegister("reg1_IC053",
        0,
        handles.INTCP0,
        122,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC053.value),
        True
    );
    ppmCreateRegister("reg1_IC054",
        0,
        handles.INTCP0,
        124,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC054.value),
        True
    );
    ppmCreateRegister("reg1_IC055",
        0,
        handles.INTCP0,
        126,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC055.value),
        True
    );
    ppmCreateRegister("reg1_IC056",
        0,
        handles.INTCP0,
        128,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC056.value),
        True
    );
    ppmCreateRegister("reg1_IC057",
        0,
        handles.INTCP0,
        130,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC057.value),
        True
    );
    ppmCreateRegister("reg1_IC058",
        0,
        handles.INTCP0,
        132,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC058.value),
        True
    );
    ppmCreateRegister("reg1_IC059",
        0,
        handles.INTCP0,
        134,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC059.value),
        True
    );
    ppmCreateRegister("reg1_IC060",
        0,
        handles.INTCP0,
        136,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC060.value),
        True
    );
    ppmCreateRegister("reg1_IC061",
        0,
        handles.INTCP0,
        138,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC061.value),
        True
    );
    ppmCreateRegister("reg1_IC062",
        0,
        handles.INTCP0,
        140,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC062.value),
        True
    );
    ppmCreateRegister("reg1_IC063",
        0,
        handles.INTCP0,
        142,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC063.value),
        True
    );
    ppmCreateRegister("reg1_IC064",
        0,
        handles.INTCP0,
        144,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC064.value),
        True
    );
    ppmCreateRegister("reg1_IC065",
        0,
        handles.INTCP0,
        146,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC065.value),
        True
    );
    ppmCreateRegister("reg1_IC066",
        0,
        handles.INTCP0,
        148,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC066.value),
        True
    );
    ppmCreateRegister("reg1_IC067",
        0,
        handles.INTCP0,
        150,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC067.value),
        True
    );
    ppmCreateRegister("reg1_IC068",
        0,
        handles.INTCP0,
        152,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC068.value),
        True
    );
    ppmCreateRegister("reg1_IC069",
        0,
        handles.INTCP0,
        154,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC069.value),
        True
    );
    ppmCreateRegister("reg1_IC070",
        0,
        handles.INTCP0,
        156,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC070.value),
        True
    );
    ppmCreateRegister("reg1_IC071",
        0,
        handles.INTCP0,
        158,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC071.value),
        True
    );
    ppmCreateRegister("reg1_IC072",
        0,
        handles.INTCP0,
        160,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC072.value),
        True
    );
    ppmCreateRegister("reg1_IC073",
        0,
        handles.INTCP0,
        162,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC073.value),
        True
    );
    ppmCreateRegister("reg1_IC074",
        0,
        handles.INTCP0,
        164,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC074.value),
        True
    );
    ppmCreateRegister("reg1_IC075",
        0,
        handles.INTCP0,
        166,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC075.value),
        True
    );
    ppmCreateRegister("reg1_IC076",
        0,
        handles.INTCP0,
        168,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC076.value),
        True
    );
    ppmCreateRegister("reg1_IC077",
        0,
        handles.INTCP0,
        170,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC077.value),
        True
    );
    ppmCreateRegister("reg1_IC078",
        0,
        handles.INTCP0,
        172,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC078.value),
        True
    );
    ppmCreateRegister("reg1_IC079",
        0,
        handles.INTCP0,
        174,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC079.value),
        True
    );
    ppmCreateRegister("reg1_IC080",
        0,
        handles.INTCP0,
        176,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC080.value),
        True
    );
    ppmCreateRegister("reg1_IC081",
        0,
        handles.INTCP0,
        178,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC081.value),
        True
    );
    ppmCreateRegister("reg1_IC082",
        0,
        handles.INTCP0,
        180,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC082.value),
        True
    );
    ppmCreateRegister("reg1_IC083",
        0,
        handles.INTCP0,
        182,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC083.value),
        True
    );
    ppmCreateRegister("reg1_IC084",
        0,
        handles.INTCP0,
        184,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC084.value),
        True
    );
    ppmCreateRegister("reg1_IC085",
        0,
        handles.INTCP0,
        186,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC085.value),
        True
    );
    ppmCreateRegister("reg1_IC086",
        0,
        handles.INTCP0,
        188,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC086.value),
        True
    );
    ppmCreateRegister("reg1_IC087",
        0,
        handles.INTCP0,
        190,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC087.value),
        True
    );
    ppmCreateRegister("reg1_IC088",
        0,
        handles.INTCP0,
        192,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC088.value),
        True
    );
    ppmCreateRegister("reg1_IC089",
        0,
        handles.INTCP0,
        194,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC089.value),
        True
    );
    ppmCreateRegister("reg1_IC090",
        0,
        handles.INTCP0,
        196,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC090.value),
        True
    );
    ppmCreateRegister("reg1_IC091",
        0,
        handles.INTCP0,
        198,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC091.value),
        True
    );
    ppmCreateRegister("reg1_IC092",
        0,
        handles.INTCP0,
        200,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC092.value),
        True
    );
    ppmCreateRegister("reg1_IC093",
        0,
        handles.INTCP0,
        202,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC093.value),
        True
    );
    ppmCreateRegister("reg1_IC094",
        0,
        handles.INTCP0,
        204,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC094.value),
        True
    );
    ppmCreateRegister("reg1_IC095",
        0,
        handles.INTCP0,
        206,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC095.value),
        True
    );
    ppmCreateRegister("reg1_IC096",
        0,
        handles.INTCP0,
        208,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC096.value),
        True
    );
    ppmCreateRegister("reg1_IC097",
        0,
        handles.INTCP0,
        210,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC097.value),
        True
    );
    ppmCreateRegister("reg1_IC098",
        0,
        handles.INTCP0,
        212,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC098.value),
        True
    );
    ppmCreateRegister("reg1_IC099",
        0,
        handles.INTCP0,
        214,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC099.value),
        True
    );
    ppmCreateRegister("reg1_IC100",
        0,
        handles.INTCP0,
        216,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC100.value),
        True
    );
    ppmCreateRegister("reg1_IC101",
        0,
        handles.INTCP0,
        218,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC101.value),
        True
    );
    ppmCreateRegister("reg1_IC102",
        0,
        handles.INTCP0,
        220,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC102.value),
        True
    );
    ppmCreateRegister("reg1_IC103",
        0,
        handles.INTCP0,
        222,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC103.value),
        True
    );
    ppmCreateRegister("reg1_IC104",
        0,
        handles.INTCP0,
        224,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC104.value),
        True
    );
    ppmCreateRegister("reg1_IC105",
        0,
        handles.INTCP0,
        226,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC105.value),
        True
    );
    ppmCreateRegister("reg1_IC106",
        0,
        handles.INTCP0,
        228,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC106.value),
        True
    );
    ppmCreateRegister("reg1_IC107",
        0,
        handles.INTCP0,
        230,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC107.value),
        True
    );
    ppmCreateRegister("reg1_IC108",
        0,
        handles.INTCP0,
        232,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC108.value),
        True
    );
    ppmCreateRegister("reg1_IC109",
        0,
        handles.INTCP0,
        234,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC109.value),
        True
    );
    ppmCreateRegister("reg1_IC110",
        0,
        handles.INTCP0,
        236,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC110.value),
        True
    );
    ppmCreateRegister("reg1_IC111",
        0,
        handles.INTCP0,
        238,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC111.value),
        True
    );
    ppmCreateRegister("reg1_IC112",
        0,
        handles.INTCP0,
        240,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC112.value),
        True
    );
    ppmCreateRegister("reg1_IC113",
        0,
        handles.INTCP0,
        242,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC113.value),
        True
    );
    ppmCreateRegister("reg1_IC114",
        0,
        handles.INTCP0,
        244,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC114.value),
        True
    );
    ppmCreateRegister("reg1_IC115",
        0,
        handles.INTCP0,
        246,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC115.value),
        True
    );
    ppmCreateRegister("reg1_IC116",
        0,
        handles.INTCP0,
        248,
        1,
        readIC,
        writeIC,
        view8,
        &(INTCP0_reg1_data.IC116.value),
        True
    );
    ppmCreateRegister("reg1_ISPR",
        0,
        handles.INTCP0,
        250,
        1,
        read_8,
        0,
        view8,
        &(INTCP0_reg1_data.ISPR.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.RESET, value);

    handles.RESET = ppmOpenNetPort("RESET");

// To write to this net, use ppmWriteNet(handles.NMI0, value);

    handles.NMI0 = ppmOpenNetPort("NMI0");

// To write to this net, use ppmWriteNet(handles.NMI1, value);

    handles.NMI1 = ppmOpenNetPort("NMI1");

// To write to this net, use ppmWriteNet(handles.NMI2, value);

    handles.NMI2 = ppmOpenNetPort("NMI2");

// To write to this net, use ppmWriteNet(handles.INTP, value);

    handles.INTP = ppmOpenNetPort("INTP");

    handles.INTACK = ppmOpenNetPort("INTACK");
    if (handles.INTACK) {
        ppmInstallNetCallback(handles.INTACK, P_INTACK, (void*)0);
    }

    handles.MIRETI = ppmOpenNetPort("MIRETI");
    if (handles.MIRETI) {
        ppmInstallNetCallback(handles.MIRETI, P_MIRETI, (void*)0);
    }

    handles.IRESET = ppmOpenNetPort("IRESET");
    if (handles.IRESET) {
        ppmInstallNetCallback(handles.IRESET, P_IRESET, (void*)0);
    }

    handles.NMI_00 = ppmOpenNetPort("NMI_00");
    if (handles.NMI_00) {
        ppmInstallNetCallback(handles.NMI_00, P_NMI, (void*)0);
    }

    handles.NMI_01 = ppmOpenNetPort("NMI_01");
    if (handles.NMI_01) {
        ppmInstallNetCallback(handles.NMI_01, P_NMI, (void*)1);
    }

    handles.NMI_02 = ppmOpenNetPort("NMI_02");
    if (handles.NMI_02) {
        ppmInstallNetCallback(handles.NMI_02, P_NMI, (void*)2);
    }

    handles.NMI_03 = ppmOpenNetPort("NMI_03");
    if (handles.NMI_03) {
        ppmInstallNetCallback(handles.NMI_03, P_NMI, (void*)3);
    }

    handles.NMI_04 = ppmOpenNetPort("NMI_04");
    if (handles.NMI_04) {
        ppmInstallNetCallback(handles.NMI_04, P_NMI, (void*)4);
    }

    handles.NMI_05 = ppmOpenNetPort("NMI_05");
    if (handles.NMI_05) {
        ppmInstallNetCallback(handles.NMI_05, P_NMI, (void*)5);
    }

    handles.NMI_06 = ppmOpenNetPort("NMI_06");
    if (handles.NMI_06) {
        ppmInstallNetCallback(handles.NMI_06, P_NMI, (void*)6);
    }

    handles.NMI_07 = ppmOpenNetPort("NMI_07");
    if (handles.NMI_07) {
        ppmInstallNetCallback(handles.NMI_07, P_NMI, (void*)7);
    }

    handles.NMI_08 = ppmOpenNetPort("NMI_08");
    if (handles.NMI_08) {
        ppmInstallNetCallback(handles.NMI_08, P_NMI, (void*)8);
    }

    handles.NMI_09 = ppmOpenNetPort("NMI_09");
    if (handles.NMI_09) {
        ppmInstallNetCallback(handles.NMI_09, P_NMI, (void*)9);
    }

    handles.NMI_10 = ppmOpenNetPort("NMI_10");
    if (handles.NMI_10) {
        ppmInstallNetCallback(handles.NMI_10, P_NMI, (void*)10);
    }

    handles.NMI_11 = ppmOpenNetPort("NMI_11");
    if (handles.NMI_11) {
        ppmInstallNetCallback(handles.NMI_11, P_NMI, (void*)11);
    }

    handles.NMI_12 = ppmOpenNetPort("NMI_12");
    if (handles.NMI_12) {
        ppmInstallNetCallback(handles.NMI_12, P_NMI, (void*)12);
    }

    handles.NMI_13 = ppmOpenNetPort("NMI_13");
    if (handles.NMI_13) {
        ppmInstallNetCallback(handles.NMI_13, P_NMI, (void*)13);
    }

    handles.NMI_14 = ppmOpenNetPort("NMI_14");
    if (handles.NMI_14) {
        ppmInstallNetCallback(handles.NMI_14, P_NMI, (void*)14);
    }

    handles.NMI_15 = ppmOpenNetPort("NMI_15");
    if (handles.NMI_15) {
        ppmInstallNetCallback(handles.NMI_15, P_NMI, (void*)15);
    }

    handles.NMI_16 = ppmOpenNetPort("NMI_16");
    if (handles.NMI_16) {
        ppmInstallNetCallback(handles.NMI_16, P_NMI, (void*)16);
    }

    handles.NMI_17 = ppmOpenNetPort("NMI_17");
    if (handles.NMI_17) {
        ppmInstallNetCallback(handles.NMI_17, P_NMI, (void*)17);
    }

    handles.NMI_18 = ppmOpenNetPort("NMI_18");
    if (handles.NMI_18) {
        ppmInstallNetCallback(handles.NMI_18, P_NMI, (void*)18);
    }

    handles.NMI_19 = ppmOpenNetPort("NMI_19");
    if (handles.NMI_19) {
        ppmInstallNetCallback(handles.NMI_19, P_NMI, (void*)19);
    }

    handles.NMI_20 = ppmOpenNetPort("NMI_20");
    if (handles.NMI_20) {
        ppmInstallNetCallback(handles.NMI_20, P_NMI, (void*)20);
    }

    handles.NMI_21 = ppmOpenNetPort("NMI_21");
    if (handles.NMI_21) {
        ppmInstallNetCallback(handles.NMI_21, P_NMI, (void*)21);
    }

    handles.NMI_22 = ppmOpenNetPort("NMI_22");
    if (handles.NMI_22) {
        ppmInstallNetCallback(handles.NMI_22, P_NMI, (void*)22);
    }

    handles.NMI_23 = ppmOpenNetPort("NMI_23");
    if (handles.NMI_23) {
        ppmInstallNetCallback(handles.NMI_23, P_NMI, (void*)23);
    }

    handles.NMI_24 = ppmOpenNetPort("NMI_24");
    if (handles.NMI_24) {
        ppmInstallNetCallback(handles.NMI_24, P_NMI, (void*)24);
    }

    handles.NMI_25 = ppmOpenNetPort("NMI_25");
    if (handles.NMI_25) {
        ppmInstallNetCallback(handles.NMI_25, P_NMI, (void*)25);
    }

    handles.NMI_26 = ppmOpenNetPort("NMI_26");
    if (handles.NMI_26) {
        ppmInstallNetCallback(handles.NMI_26, P_NMI, (void*)26);
    }

    handles.NMI_27 = ppmOpenNetPort("NMI_27");
    if (handles.NMI_27) {
        ppmInstallNetCallback(handles.NMI_27, P_NMI, (void*)27);
    }

    handles.NMI_28 = ppmOpenNetPort("NMI_28");
    if (handles.NMI_28) {
        ppmInstallNetCallback(handles.NMI_28, P_NMI, (void*)28);
    }

    handles.NMI_29 = ppmOpenNetPort("NMI_29");
    if (handles.NMI_29) {
        ppmInstallNetCallback(handles.NMI_29, P_NMI, (void*)29);
    }

    handles.NMI_30 = ppmOpenNetPort("NMI_30");
    if (handles.NMI_30) {
        ppmInstallNetCallback(handles.NMI_30, P_NMI, (void*)30);
    }

    handles.NMI_31 = ppmOpenNetPort("NMI_31");
    if (handles.NMI_31) {
        ppmInstallNetCallback(handles.NMI_31, P_NMI, (void*)31);
    }

    handles.NMI_32 = ppmOpenNetPort("NMI_32");
    if (handles.NMI_32) {
        ppmInstallNetCallback(handles.NMI_32, P_NMI, (void*)32);
    }

    handles.NMI_33 = ppmOpenNetPort("NMI_33");
    if (handles.NMI_33) {
        ppmInstallNetCallback(handles.NMI_33, P_NMI, (void*)33);
    }

    handles.NMI_34 = ppmOpenNetPort("NMI_34");
    if (handles.NMI_34) {
        ppmInstallNetCallback(handles.NMI_34, P_NMI, (void*)34);
    }

    handles.NMI_35 = ppmOpenNetPort("NMI_35");
    if (handles.NMI_35) {
        ppmInstallNetCallback(handles.NMI_35, P_NMI, (void*)35);
    }

    handles.NMI_36 = ppmOpenNetPort("NMI_36");
    if (handles.NMI_36) {
        ppmInstallNetCallback(handles.NMI_36, P_NMI, (void*)36);
    }

    handles.NMI_37 = ppmOpenNetPort("NMI_37");
    if (handles.NMI_37) {
        ppmInstallNetCallback(handles.NMI_37, P_NMI, (void*)37);
    }

    handles.NMI_38 = ppmOpenNetPort("NMI_38");
    if (handles.NMI_38) {
        ppmInstallNetCallback(handles.NMI_38, P_NMI, (void*)38);
    }

    handles.NMI_39 = ppmOpenNetPort("NMI_39");
    if (handles.NMI_39) {
        ppmInstallNetCallback(handles.NMI_39, P_NMI, (void*)39);
    }

    handles.NMI_40 = ppmOpenNetPort("NMI_40");
    if (handles.NMI_40) {
        ppmInstallNetCallback(handles.NMI_40, P_NMI, (void*)40);
    }

    handles.NMI_41 = ppmOpenNetPort("NMI_41");
    if (handles.NMI_41) {
        ppmInstallNetCallback(handles.NMI_41, P_NMI, (void*)41);
    }

    handles.NMI_42 = ppmOpenNetPort("NMI_42");
    if (handles.NMI_42) {
        ppmInstallNetCallback(handles.NMI_42, P_NMI, (void*)42);
    }

    handles.NMI_43 = ppmOpenNetPort("NMI_43");
    if (handles.NMI_43) {
        ppmInstallNetCallback(handles.NMI_43, P_NMI, (void*)43);
    }

    handles.NMI_44 = ppmOpenNetPort("NMI_44");
    if (handles.NMI_44) {
        ppmInstallNetCallback(handles.NMI_44, P_NMI, (void*)44);
    }

    handles.NMI_45 = ppmOpenNetPort("NMI_45");
    if (handles.NMI_45) {
        ppmInstallNetCallback(handles.NMI_45, P_NMI, (void*)45);
    }

    handles.NMI_46 = ppmOpenNetPort("NMI_46");
    if (handles.NMI_46) {
        ppmInstallNetCallback(handles.NMI_46, P_NMI, (void*)46);
    }

    handles.NMI_47 = ppmOpenNetPort("NMI_47");
    if (handles.NMI_47) {
        ppmInstallNetCallback(handles.NMI_47, P_NMI, (void*)47);
    }

    handles.NMI_48 = ppmOpenNetPort("NMI_48");
    if (handles.NMI_48) {
        ppmInstallNetCallback(handles.NMI_48, P_NMI, (void*)48);
    }

    handles.NMI_49 = ppmOpenNetPort("NMI_49");
    if (handles.NMI_49) {
        ppmInstallNetCallback(handles.NMI_49, P_NMI, (void*)49);
    }

    handles.NMI_50 = ppmOpenNetPort("NMI_50");
    if (handles.NMI_50) {
        ppmInstallNetCallback(handles.NMI_50, P_NMI, (void*)50);
    }

    handles.NMI_51 = ppmOpenNetPort("NMI_51");
    if (handles.NMI_51) {
        ppmInstallNetCallback(handles.NMI_51, P_NMI, (void*)51);
    }

    handles.NMI_52 = ppmOpenNetPort("NMI_52");
    if (handles.NMI_52) {
        ppmInstallNetCallback(handles.NMI_52, P_NMI, (void*)52);
    }

    handles.NMI_53 = ppmOpenNetPort("NMI_53");
    if (handles.NMI_53) {
        ppmInstallNetCallback(handles.NMI_53, P_NMI, (void*)53);
    }

    handles.NMI_54 = ppmOpenNetPort("NMI_54");
    if (handles.NMI_54) {
        ppmInstallNetCallback(handles.NMI_54, P_NMI, (void*)54);
    }

    handles.NMI_55 = ppmOpenNetPort("NMI_55");
    if (handles.NMI_55) {
        ppmInstallNetCallback(handles.NMI_55, P_NMI, (void*)55);
    }

    handles.NMI_56 = ppmOpenNetPort("NMI_56");
    if (handles.NMI_56) {
        ppmInstallNetCallback(handles.NMI_56, P_NMI, (void*)56);
    }

    handles.NMI_57 = ppmOpenNetPort("NMI_57");
    if (handles.NMI_57) {
        ppmInstallNetCallback(handles.NMI_57, P_NMI, (void*)57);
    }

    handles.NMI_58 = ppmOpenNetPort("NMI_58");
    if (handles.NMI_58) {
        ppmInstallNetCallback(handles.NMI_58, P_NMI, (void*)58);
    }

    handles.NMI_59 = ppmOpenNetPort("NMI_59");
    if (handles.NMI_59) {
        ppmInstallNetCallback(handles.NMI_59, P_NMI, (void*)59);
    }

    handles.NMI_60 = ppmOpenNetPort("NMI_60");
    if (handles.NMI_60) {
        ppmInstallNetCallback(handles.NMI_60, P_NMI, (void*)60);
    }

    handles.NMI_61 = ppmOpenNetPort("NMI_61");
    if (handles.NMI_61) {
        ppmInstallNetCallback(handles.NMI_61, P_NMI, (void*)61);
    }

    handles.NMI_62 = ppmOpenNetPort("NMI_62");
    if (handles.NMI_62) {
        ppmInstallNetCallback(handles.NMI_62, P_NMI, (void*)62);
    }

    handles.NMI_63 = ppmOpenNetPort("NMI_63");
    if (handles.NMI_63) {
        ppmInstallNetCallback(handles.NMI_63, P_NMI, (void*)63);
    }

    handles.INT_00 = ppmOpenNetPort("INT_00");
    if (handles.INT_00) {
        ppmInstallNetCallback(handles.INT_00, P_INT, (void*)0);
    }

    handles.INT_01 = ppmOpenNetPort("INT_01");
    if (handles.INT_01) {
        ppmInstallNetCallback(handles.INT_01, P_INT, (void*)1);
    }

    handles.INT_02 = ppmOpenNetPort("INT_02");
    if (handles.INT_02) {
        ppmInstallNetCallback(handles.INT_02, P_INT, (void*)2);
    }

    handles.INT_03 = ppmOpenNetPort("INT_03");
    if (handles.INT_03) {
        ppmInstallNetCallback(handles.INT_03, P_INT, (void*)3);
    }

    handles.INT_04 = ppmOpenNetPort("INT_04");
    if (handles.INT_04) {
        ppmInstallNetCallback(handles.INT_04, P_INT, (void*)4);
    }

    handles.INT_05 = ppmOpenNetPort("INT_05");
    if (handles.INT_05) {
        ppmInstallNetCallback(handles.INT_05, P_INT, (void*)5);
    }

    handles.INT_06 = ppmOpenNetPort("INT_06");
    if (handles.INT_06) {
        ppmInstallNetCallback(handles.INT_06, P_INT, (void*)6);
    }

    handles.INT_07 = ppmOpenNetPort("INT_07");
    if (handles.INT_07) {
        ppmInstallNetCallback(handles.INT_07, P_INT, (void*)7);
    }

    handles.INT_08 = ppmOpenNetPort("INT_08");
    if (handles.INT_08) {
        ppmInstallNetCallback(handles.INT_08, P_INT, (void*)8);
    }

    handles.INT_09 = ppmOpenNetPort("INT_09");
    if (handles.INT_09) {
        ppmInstallNetCallback(handles.INT_09, P_INT, (void*)9);
    }

    handles.INT_10 = ppmOpenNetPort("INT_10");
    if (handles.INT_10) {
        ppmInstallNetCallback(handles.INT_10, P_INT, (void*)10);
    }

    handles.INT_11 = ppmOpenNetPort("INT_11");
    if (handles.INT_11) {
        ppmInstallNetCallback(handles.INT_11, P_INT, (void*)11);
    }

    handles.INT_12 = ppmOpenNetPort("INT_12");
    if (handles.INT_12) {
        ppmInstallNetCallback(handles.INT_12, P_INT, (void*)12);
    }

    handles.INT_13 = ppmOpenNetPort("INT_13");
    if (handles.INT_13) {
        ppmInstallNetCallback(handles.INT_13, P_INT, (void*)13);
    }

    handles.INT_14 = ppmOpenNetPort("INT_14");
    if (handles.INT_14) {
        ppmInstallNetCallback(handles.INT_14, P_INT, (void*)14);
    }

    handles.INT_15 = ppmOpenNetPort("INT_15");
    if (handles.INT_15) {
        ppmInstallNetCallback(handles.INT_15, P_INT, (void*)15);
    }

    handles.INT_16 = ppmOpenNetPort("INT_16");
    if (handles.INT_16) {
        ppmInstallNetCallback(handles.INT_16, P_INT, (void*)16);
    }

    handles.INT_17 = ppmOpenNetPort("INT_17");
    if (handles.INT_17) {
        ppmInstallNetCallback(handles.INT_17, P_INT, (void*)17);
    }

    handles.INT_18 = ppmOpenNetPort("INT_18");
    if (handles.INT_18) {
        ppmInstallNetCallback(handles.INT_18, P_INT, (void*)18);
    }

    handles.INT_19 = ppmOpenNetPort("INT_19");
    if (handles.INT_19) {
        ppmInstallNetCallback(handles.INT_19, P_INT, (void*)19);
    }

    handles.INT_20 = ppmOpenNetPort("INT_20");
    if (handles.INT_20) {
        ppmInstallNetCallback(handles.INT_20, P_INT, (void*)20);
    }

    handles.INT_21 = ppmOpenNetPort("INT_21");
    if (handles.INT_21) {
        ppmInstallNetCallback(handles.INT_21, P_INT, (void*)21);
    }

    handles.INT_22 = ppmOpenNetPort("INT_22");
    if (handles.INT_22) {
        ppmInstallNetCallback(handles.INT_22, P_INT, (void*)22);
    }

    handles.INT_23 = ppmOpenNetPort("INT_23");
    if (handles.INT_23) {
        ppmInstallNetCallback(handles.INT_23, P_INT, (void*)23);
    }

    handles.INT_24 = ppmOpenNetPort("INT_24");
    if (handles.INT_24) {
        ppmInstallNetCallback(handles.INT_24, P_INT, (void*)24);
    }

    handles.INT_25 = ppmOpenNetPort("INT_25");
    if (handles.INT_25) {
        ppmInstallNetCallback(handles.INT_25, P_INT, (void*)25);
    }

    handles.INT_26 = ppmOpenNetPort("INT_26");
    if (handles.INT_26) {
        ppmInstallNetCallback(handles.INT_26, P_INT, (void*)26);
    }

    handles.INT_27 = ppmOpenNetPort("INT_27");
    if (handles.INT_27) {
        ppmInstallNetCallback(handles.INT_27, P_INT, (void*)27);
    }

    handles.INT_28 = ppmOpenNetPort("INT_28");
    if (handles.INT_28) {
        ppmInstallNetCallback(handles.INT_28, P_INT, (void*)28);
    }

    handles.INT_29 = ppmOpenNetPort("INT_29");
    if (handles.INT_29) {
        ppmInstallNetCallback(handles.INT_29, P_INT, (void*)29);
    }

    handles.INT_30 = ppmOpenNetPort("INT_30");
    if (handles.INT_30) {
        ppmInstallNetCallback(handles.INT_30, P_INT, (void*)30);
    }

    handles.INT_31 = ppmOpenNetPort("INT_31");
    if (handles.INT_31) {
        ppmInstallNetCallback(handles.INT_31, P_INT, (void*)31);
    }

    handles.INT_32 = ppmOpenNetPort("INT_32");
    if (handles.INT_32) {
        ppmInstallNetCallback(handles.INT_32, P_INT, (void*)32);
    }

    handles.INT_33 = ppmOpenNetPort("INT_33");
    if (handles.INT_33) {
        ppmInstallNetCallback(handles.INT_33, P_INT, (void*)33);
    }

    handles.INT_34 = ppmOpenNetPort("INT_34");
    if (handles.INT_34) {
        ppmInstallNetCallback(handles.INT_34, P_INT, (void*)34);
    }

    handles.INT_35 = ppmOpenNetPort("INT_35");
    if (handles.INT_35) {
        ppmInstallNetCallback(handles.INT_35, P_INT, (void*)35);
    }

    handles.INT_36 = ppmOpenNetPort("INT_36");
    if (handles.INT_36) {
        ppmInstallNetCallback(handles.INT_36, P_INT, (void*)36);
    }

    handles.INT_37 = ppmOpenNetPort("INT_37");
    if (handles.INT_37) {
        ppmInstallNetCallback(handles.INT_37, P_INT, (void*)37);
    }

    handles.INT_38 = ppmOpenNetPort("INT_38");
    if (handles.INT_38) {
        ppmInstallNetCallback(handles.INT_38, P_INT, (void*)38);
    }

    handles.INT_39 = ppmOpenNetPort("INT_39");
    if (handles.INT_39) {
        ppmInstallNetCallback(handles.INT_39, P_INT, (void*)39);
    }

    handles.INT_40 = ppmOpenNetPort("INT_40");
    if (handles.INT_40) {
        ppmInstallNetCallback(handles.INT_40, P_INT, (void*)40);
    }

    handles.INT_41 = ppmOpenNetPort("INT_41");
    if (handles.INT_41) {
        ppmInstallNetCallback(handles.INT_41, P_INT, (void*)41);
    }

    handles.INT_42 = ppmOpenNetPort("INT_42");
    if (handles.INT_42) {
        ppmInstallNetCallback(handles.INT_42, P_INT, (void*)42);
    }

    handles.INT_43 = ppmOpenNetPort("INT_43");
    if (handles.INT_43) {
        ppmInstallNetCallback(handles.INT_43, P_INT, (void*)43);
    }

    handles.INT_44 = ppmOpenNetPort("INT_44");
    if (handles.INT_44) {
        ppmInstallNetCallback(handles.INT_44, P_INT, (void*)44);
    }

    handles.INT_45 = ppmOpenNetPort("INT_45");
    if (handles.INT_45) {
        ppmInstallNetCallback(handles.INT_45, P_INT, (void*)45);
    }

    handles.INT_46 = ppmOpenNetPort("INT_46");
    if (handles.INT_46) {
        ppmInstallNetCallback(handles.INT_46, P_INT, (void*)46);
    }

    handles.INT_47 = ppmOpenNetPort("INT_47");
    if (handles.INT_47) {
        ppmInstallNetCallback(handles.INT_47, P_INT, (void*)47);
    }

    handles.INT_48 = ppmOpenNetPort("INT_48");
    if (handles.INT_48) {
        ppmInstallNetCallback(handles.INT_48, P_INT, (void*)48);
    }

    handles.INT_49 = ppmOpenNetPort("INT_49");
    if (handles.INT_49) {
        ppmInstallNetCallback(handles.INT_49, P_INT, (void*)49);
    }

    handles.INT_50 = ppmOpenNetPort("INT_50");
    if (handles.INT_50) {
        ppmInstallNetCallback(handles.INT_50, P_INT, (void*)50);
    }

    handles.INT_51 = ppmOpenNetPort("INT_51");
    if (handles.INT_51) {
        ppmInstallNetCallback(handles.INT_51, P_INT, (void*)51);
    }

    handles.INT_52 = ppmOpenNetPort("INT_52");
    if (handles.INT_52) {
        ppmInstallNetCallback(handles.INT_52, P_INT, (void*)52);
    }

    handles.INT_53 = ppmOpenNetPort("INT_53");
    if (handles.INT_53) {
        ppmInstallNetCallback(handles.INT_53, P_INT, (void*)53);
    }

    handles.INT_54 = ppmOpenNetPort("INT_54");
    if (handles.INT_54) {
        ppmInstallNetCallback(handles.INT_54, P_INT, (void*)54);
    }

    handles.INT_55 = ppmOpenNetPort("INT_55");
    if (handles.INT_55) {
        ppmInstallNetCallback(handles.INT_55, P_INT, (void*)55);
    }

    handles.INT_56 = ppmOpenNetPort("INT_56");
    if (handles.INT_56) {
        ppmInstallNetCallback(handles.INT_56, P_INT, (void*)56);
    }

    handles.INT_57 = ppmOpenNetPort("INT_57");
    if (handles.INT_57) {
        ppmInstallNetCallback(handles.INT_57, P_INT, (void*)57);
    }

    handles.INT_58 = ppmOpenNetPort("INT_58");
    if (handles.INT_58) {
        ppmInstallNetCallback(handles.INT_58, P_INT, (void*)58);
    }

    handles.INT_59 = ppmOpenNetPort("INT_59");
    if (handles.INT_59) {
        ppmInstallNetCallback(handles.INT_59, P_INT, (void*)59);
    }

    handles.INT_60 = ppmOpenNetPort("INT_60");
    if (handles.INT_60) {
        ppmInstallNetCallback(handles.INT_60, P_INT, (void*)60);
    }

    handles.INT_61 = ppmOpenNetPort("INT_61");
    if (handles.INT_61) {
        ppmInstallNetCallback(handles.INT_61, P_INT, (void*)61);
    }

    handles.INT_62 = ppmOpenNetPort("INT_62");
    if (handles.INT_62) {
        ppmInstallNetCallback(handles.INT_62, P_INT, (void*)62);
    }

    handles.INT_63 = ppmOpenNetPort("INT_63");
    if (handles.INT_63) {
        ppmInstallNetCallback(handles.INT_63, P_INT, (void*)63);
    }

    handles.INT_64 = ppmOpenNetPort("INT_64");
    if (handles.INT_64) {
        ppmInstallNetCallback(handles.INT_64, P_INT, (void*)64);
    }

    handles.INT_65 = ppmOpenNetPort("INT_65");
    if (handles.INT_65) {
        ppmInstallNetCallback(handles.INT_65, P_INT, (void*)65);
    }

    handles.INT_66 = ppmOpenNetPort("INT_66");
    if (handles.INT_66) {
        ppmInstallNetCallback(handles.INT_66, P_INT, (void*)66);
    }

    handles.INT_67 = ppmOpenNetPort("INT_67");
    if (handles.INT_67) {
        ppmInstallNetCallback(handles.INT_67, P_INT, (void*)67);
    }

    handles.INT_68 = ppmOpenNetPort("INT_68");
    if (handles.INT_68) {
        ppmInstallNetCallback(handles.INT_68, P_INT, (void*)68);
    }

    handles.INT_69 = ppmOpenNetPort("INT_69");
    if (handles.INT_69) {
        ppmInstallNetCallback(handles.INT_69, P_INT, (void*)69);
    }

    handles.INT_70 = ppmOpenNetPort("INT_70");
    if (handles.INT_70) {
        ppmInstallNetCallback(handles.INT_70, P_INT, (void*)70);
    }

    handles.INT_71 = ppmOpenNetPort("INT_71");
    if (handles.INT_71) {
        ppmInstallNetCallback(handles.INT_71, P_INT, (void*)71);
    }

    handles.INT_72 = ppmOpenNetPort("INT_72");
    if (handles.INT_72) {
        ppmInstallNetCallback(handles.INT_72, P_INT, (void*)72);
    }

    handles.INT_73 = ppmOpenNetPort("INT_73");
    if (handles.INT_73) {
        ppmInstallNetCallback(handles.INT_73, P_INT, (void*)73);
    }

    handles.INT_74 = ppmOpenNetPort("INT_74");
    if (handles.INT_74) {
        ppmInstallNetCallback(handles.INT_74, P_INT, (void*)74);
    }

    handles.INT_75 = ppmOpenNetPort("INT_75");
    if (handles.INT_75) {
        ppmInstallNetCallback(handles.INT_75, P_INT, (void*)75);
    }

    handles.INT_76 = ppmOpenNetPort("INT_76");
    if (handles.INT_76) {
        ppmInstallNetCallback(handles.INT_76, P_INT, (void*)76);
    }

    handles.INT_77 = ppmOpenNetPort("INT_77");
    if (handles.INT_77) {
        ppmInstallNetCallback(handles.INT_77, P_INT, (void*)77);
    }

    handles.INT_78 = ppmOpenNetPort("INT_78");
    if (handles.INT_78) {
        ppmInstallNetCallback(handles.INT_78, P_INT, (void*)78);
    }

    handles.INT_79 = ppmOpenNetPort("INT_79");
    if (handles.INT_79) {
        ppmInstallNetCallback(handles.INT_79, P_INT, (void*)79);
    }

    handles.INT_80 = ppmOpenNetPort("INT_80");
    if (handles.INT_80) {
        ppmInstallNetCallback(handles.INT_80, P_INT, (void*)80);
    }

    handles.INT_81 = ppmOpenNetPort("INT_81");
    if (handles.INT_81) {
        ppmInstallNetCallback(handles.INT_81, P_INT, (void*)81);
    }

    handles.INT_82 = ppmOpenNetPort("INT_82");
    if (handles.INT_82) {
        ppmInstallNetCallback(handles.INT_82, P_INT, (void*)82);
    }

    handles.INT_83 = ppmOpenNetPort("INT_83");
    if (handles.INT_83) {
        ppmInstallNetCallback(handles.INT_83, P_INT, (void*)83);
    }

    handles.INT_84 = ppmOpenNetPort("INT_84");
    if (handles.INT_84) {
        ppmInstallNetCallback(handles.INT_84, P_INT, (void*)84);
    }

    handles.INT_85 = ppmOpenNetPort("INT_85");
    if (handles.INT_85) {
        ppmInstallNetCallback(handles.INT_85, P_INT, (void*)85);
    }

    handles.INT_86 = ppmOpenNetPort("INT_86");
    if (handles.INT_86) {
        ppmInstallNetCallback(handles.INT_86, P_INT, (void*)86);
    }

    handles.INT_87 = ppmOpenNetPort("INT_87");
    if (handles.INT_87) {
        ppmInstallNetCallback(handles.INT_87, P_INT, (void*)87);
    }

    handles.INT_88 = ppmOpenNetPort("INT_88");
    if (handles.INT_88) {
        ppmInstallNetCallback(handles.INT_88, P_INT, (void*)88);
    }

    handles.INT_89 = ppmOpenNetPort("INT_89");
    if (handles.INT_89) {
        ppmInstallNetCallback(handles.INT_89, P_INT, (void*)89);
    }

    handles.INT_90 = ppmOpenNetPort("INT_90");
    if (handles.INT_90) {
        ppmInstallNetCallback(handles.INT_90, P_INT, (void*)90);
    }

    handles.INT_91 = ppmOpenNetPort("INT_91");
    if (handles.INT_91) {
        ppmInstallNetCallback(handles.INT_91, P_INT, (void*)91);
    }

    handles.INT_92 = ppmOpenNetPort("INT_92");
    if (handles.INT_92) {
        ppmInstallNetCallback(handles.INT_92, P_INT, (void*)92);
    }

    handles.INT_93 = ppmOpenNetPort("INT_93");
    if (handles.INT_93) {
        ppmInstallNetCallback(handles.INT_93, P_INT, (void*)93);
    }

    handles.INT_94 = ppmOpenNetPort("INT_94");
    if (handles.INT_94) {
        ppmInstallNetCallback(handles.INT_94, P_INT, (void*)94);
    }

    handles.INT_95 = ppmOpenNetPort("INT_95");
    if (handles.INT_95) {
        ppmInstallNetCallback(handles.INT_95, P_INT, (void*)95);
    }

    handles.INT_96 = ppmOpenNetPort("INT_96");
    if (handles.INT_96) {
        ppmInstallNetCallback(handles.INT_96, P_INT, (void*)96);
    }

    handles.INT_97 = ppmOpenNetPort("INT_97");
    if (handles.INT_97) {
        ppmInstallNetCallback(handles.INT_97, P_INT, (void*)97);
    }

    handles.INT_98 = ppmOpenNetPort("INT_98");
    if (handles.INT_98) {
        ppmInstallNetCallback(handles.INT_98, P_INT, (void*)98);
    }

    handles.INT_99 = ppmOpenNetPort("INT_99");
    if (handles.INT_99) {
        ppmInstallNetCallback(handles.INT_99, P_INT, (void*)99);
    }

    handles.INT_100 = ppmOpenNetPort("INT_100");
    if (handles.INT_100) {
        ppmInstallNetCallback(handles.INT_100, P_INT, (void*)100);
    }

    handles.INT_101 = ppmOpenNetPort("INT_101");
    if (handles.INT_101) {
        ppmInstallNetCallback(handles.INT_101, P_INT, (void*)101);
    }

    handles.INT_102 = ppmOpenNetPort("INT_102");
    if (handles.INT_102) {
        ppmInstallNetCallback(handles.INT_102, P_INT, (void*)102);
    }

    handles.INT_103 = ppmOpenNetPort("INT_103");
    if (handles.INT_103) {
        ppmInstallNetCallback(handles.INT_103, P_INT, (void*)103);
    }

    handles.INT_104 = ppmOpenNetPort("INT_104");
    if (handles.INT_104) {
        ppmInstallNetCallback(handles.INT_104, P_INT, (void*)104);
    }

    handles.INT_105 = ppmOpenNetPort("INT_105");
    if (handles.INT_105) {
        ppmInstallNetCallback(handles.INT_105, P_INT, (void*)105);
    }

    handles.INT_106 = ppmOpenNetPort("INT_106");
    if (handles.INT_106) {
        ppmInstallNetCallback(handles.INT_106, P_INT, (void*)106);
    }

    handles.INT_107 = ppmOpenNetPort("INT_107");
    if (handles.INT_107) {
        ppmInstallNetCallback(handles.INT_107, P_INT, (void*)107);
    }

    handles.INT_108 = ppmOpenNetPort("INT_108");
    if (handles.INT_108) {
        ppmInstallNetCallback(handles.INT_108, P_INT, (void*)108);
    }

    handles.INT_109 = ppmOpenNetPort("INT_109");
    if (handles.INT_109) {
        ppmInstallNetCallback(handles.INT_109, P_INT, (void*)109);
    }

    handles.INT_110 = ppmOpenNetPort("INT_110");
    if (handles.INT_110) {
        ppmInstallNetCallback(handles.INT_110, P_INT, (void*)110);
    }

    handles.INT_111 = ppmOpenNetPort("INT_111");
    if (handles.INT_111) {
        ppmInstallNetCallback(handles.INT_111, P_INT, (void*)111);
    }

    handles.INT_112 = ppmOpenNetPort("INT_112");
    if (handles.INT_112) {
        ppmInstallNetCallback(handles.INT_112, P_INT, (void*)112);
    }

    handles.INT_113 = ppmOpenNetPort("INT_113");
    if (handles.INT_113) {
        ppmInstallNetCallback(handles.INT_113, P_INT, (void*)113);
    }

    handles.INT_114 = ppmOpenNetPort("INT_114");
    if (handles.INT_114) {
        ppmInstallNetCallback(handles.INT_114, P_INT, (void*)114);
    }

    handles.INT_115 = ppmOpenNetPort("INT_115");
    if (handles.INT_115) {
        ppmInstallNetCallback(handles.INT_115, P_INT, (void*)115);
    }

    handles.INT_116 = ppmOpenNetPort("INT_116");
    if (handles.INT_116) {
        ppmInstallNetCallback(handles.INT_116, P_INT, (void*)116);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        INTCP0_reg1_data.IC116.value = 0x47;
        INTCP0_reg1_data.IC115.value = 0x47;
        INTCP0_reg1_data.IC114.value = 0x47;
        INTCP0_reg1_data.IC113.value = 0x47;
        INTCP0_reg1_data.IC112.value = 0x47;
        INTCP0_reg1_data.IC111.value = 0x47;
        INTCP0_reg1_data.IC110.value = 0x47;
        INTCP0_reg1_data.IC109.value = 0x47;
        INTCP0_reg1_data.IC108.value = 0x47;
        INTCP0_reg1_data.IC107.value = 0x47;
        INTCP0_reg1_data.IC106.value = 0x47;
        INTCP0_reg1_data.IC105.value = 0x47;
        INTCP0_reg1_data.IC104.value = 0x47;
        INTCP0_reg1_data.IC103.value = 0x47;
        INTCP0_reg1_data.IC102.value = 0x47;
        INTCP0_reg1_data.IC101.value = 0x47;
        INTCP0_reg1_data.IC100.value = 0x47;
        INTCP0_reg1_data.IC099.value = 0x47;
        INTCP0_reg1_data.IC098.value = 0x47;
        INTCP0_reg1_data.IC097.value = 0x47;
        INTCP0_reg1_data.IC096.value = 0x47;
        INTCP0_reg1_data.IC095.value = 0x47;
        INTCP0_reg1_data.IC094.value = 0x47;
        INTCP0_reg1_data.IC093.value = 0x47;
        INTCP0_reg1_data.IC092.value = 0x47;
        INTCP0_reg1_data.IC091.value = 0x47;
        INTCP0_reg1_data.IC090.value = 0x47;
        INTCP0_reg1_data.IC089.value = 0x47;
        INTCP0_reg1_data.IC088.value = 0x47;
        INTCP0_reg1_data.IC087.value = 0x47;
        INTCP0_reg1_data.IC086.value = 0x47;
        INTCP0_reg1_data.IC085.value = 0x47;
        INTCP0_reg1_data.IC084.value = 0x47;
        INTCP0_reg1_data.IC083.value = 0x47;
        INTCP0_reg1_data.IC082.value = 0x47;
        INTCP0_reg1_data.IC081.value = 0x47;
        INTCP0_reg1_data.IC080.value = 0x47;
        INTCP0_reg1_data.IC079.value = 0x47;
        INTCP0_reg1_data.IC078.value = 0x47;
        INTCP0_reg1_data.IC077.value = 0x47;
        INTCP0_reg1_data.IC076.value = 0x47;
        INTCP0_reg1_data.IC075.value = 0x47;
        INTCP0_reg1_data.IC074.value = 0x47;
        INTCP0_reg1_data.IC073.value = 0x47;
        INTCP0_reg1_data.IC072.value = 0x47;
        INTCP0_reg1_data.IC071.value = 0x47;
        INTCP0_reg1_data.IC070.value = 0x47;
        INTCP0_reg1_data.IC069.value = 0x47;
        INTCP0_reg1_data.IC068.value = 0x47;
        INTCP0_reg1_data.IC067.value = 0x47;
        INTCP0_reg1_data.IC066.value = 0x47;
        INTCP0_reg1_data.IC065.value = 0x47;
        INTCP0_reg1_data.IC064.value = 0x47;
        INTCP0_reg1_data.IC063.value = 0x47;
        INTCP0_reg1_data.IC062.value = 0x47;
        INTCP0_reg1_data.IC061.value = 0x47;
        INTCP0_reg1_data.IC060.value = 0x47;
        INTCP0_reg1_data.IC059.value = 0x47;
        INTCP0_reg1_data.IC058.value = 0x47;
        INTCP0_reg1_data.IC057.value = 0x47;
        INTCP0_reg1_data.IC056.value = 0x47;
        INTCP0_reg1_data.IC055.value = 0x47;
        INTCP0_reg1_data.IC054.value = 0x47;
        INTCP0_reg1_data.IC053.value = 0x47;
        INTCP0_reg1_data.IC052.value = 0x47;
        INTCP0_reg1_data.IC051.value = 0x47;
        INTCP0_reg1_data.IC050.value = 0x47;
        INTCP0_reg1_data.IC049.value = 0x47;
        INTCP0_reg1_data.IC048.value = 0x47;
        INTCP0_reg1_data.IC047.value = 0x47;
        INTCP0_reg1_data.IC046.value = 0x47;
        INTCP0_reg1_data.IC045.value = 0x47;
        INTCP0_reg1_data.IC044.value = 0x47;
        INTCP0_reg1_data.IC043.value = 0x47;
        INTCP0_reg1_data.IC042.value = 0x47;
        INTCP0_reg1_data.IC041.value = 0x47;
        INTCP0_reg1_data.IC040.value = 0x47;
        INTCP0_reg1_data.IC039.value = 0x47;
        INTCP0_reg1_data.IC038.value = 0x47;
        INTCP0_reg1_data.IC037.value = 0x47;
        INTCP0_reg1_data.IC036.value = 0x47;
        INTCP0_reg1_data.IC035.value = 0x47;
        INTCP0_reg1_data.IC034.value = 0x47;
        INTCP0_reg1_data.IC033.value = 0x47;
        INTCP0_reg1_data.IC032.value = 0x47;
        INTCP0_reg1_data.IC031.value = 0x47;
        INTCP0_reg1_data.IC030.value = 0x47;
        INTCP0_reg1_data.IC029.value = 0x47;
        INTCP0_reg1_data.IC028.value = 0x47;
        INTCP0_reg1_data.IC027.value = 0x47;
        INTCP0_reg1_data.IC026.value = 0x47;
        INTCP0_reg1_data.IC025.value = 0x47;
        INTCP0_reg1_data.IC024.value = 0x47;
        INTCP0_reg1_data.IC023.value = 0x47;
        INTCP0_reg1_data.IC022.value = 0x47;
        INTCP0_reg1_data.IC021.value = 0x47;
        INTCP0_reg1_data.IC020.value = 0x47;
        INTCP0_reg1_data.IC019.value = 0x47;
        INTCP0_reg1_data.IC018.value = 0x47;
        INTCP0_reg1_data.IC017.value = 0x47;
        INTCP0_reg1_data.IC016.value = 0x47;
        INTCP0_reg1_data.IC015.value = 0x47;
        INTCP0_reg1_data.IC014.value = 0x47;
        INTCP0_reg1_data.IC013.value = 0x47;
        INTCP0_reg1_data.IC012.value = 0x47;
        INTCP0_reg1_data.IC011.value = 0x47;
        INTCP0_reg1_data.IC010.value = 0x47;
        INTCP0_reg1_data.IC009.value = 0x47;
        INTCP0_reg1_data.IC008.value = 0x47;
        INTCP0_reg1_data.IC007.value = 0x47;
        INTCP0_reg1_data.IC006.value = 0x47;
        INTCP0_reg1_data.IC005.value = 0x47;
        INTCP0_reg1_data.IC004.value = 0x47;
        INTCP0_reg1_data.IC003.value = 0x47;
        INTCP0_reg1_data.IC002.value = 0x47;
        INTCP0_reg1_data.IC001.value = 0x47;
        INTCP0_reg1_data.IC000.value = 0x47;
        INTCP0_reg0_data.IMR7.value = 0x1f;
        INTCP0_reg0_data.IMR6.value = 0xffff;
        INTCP0_reg0_data.IMR5.value = 0xffff;
        INTCP0_reg0_data.IMR4.value = 0xffff;
        INTCP0_reg0_data.IMR3.value = 0xffff;
        INTCP0_reg0_data.IMR2.value = 0xffff;
        INTCP0_reg0_data.IMR1.value = 0xffff;
        INTCP0_reg0_data.IMR0.value = 0xffff;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas INTC Interrupt Controller");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Register View Model Only");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

