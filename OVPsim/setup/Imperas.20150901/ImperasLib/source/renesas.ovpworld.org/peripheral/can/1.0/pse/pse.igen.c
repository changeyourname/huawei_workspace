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

busPortGR_GR1_dataT busPortGR_GR1_data;

busPortGR_GR2_dataT busPortGR_GR2_data;

busPortGR_GR3_dataT busPortGR_GR3_data;

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

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.busPortGR = ppmCreateSlaveBusPort("busPortGR", 256);
    if (!handles.busPortGR) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPortGR'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("GR1_GMCTRL",
        0,
        handles.busPortGR,
        0,
        2,
        readGMCTRL,
        writeGMCTRL,
        viewGMCTRL,
        &(busPortGR_GR1_data.GMCTRL.value),
        True
    );
    ppmCreateRegister("GR1_GMCS",
        0,
        handles.busPortGR,
        2,
        1,
        readGMCS,
        writeGMCS,
        viewGMCS,
        &(busPortGR_GR1_data.GMCS.value),
        True
    );
    ppmCreateRegister("GR1_GMABT",
        0,
        handles.busPortGR,
        6,
        2,
        readGMABT,
        writeGMABT,
        viewGMABT,
        &(busPortGR_GR1_data.GMABT.value),
        True
    );
    ppmCreateRegister("GR1_GMABTD",
        0,
        handles.busPortGR,
        8,
        1,
        readGMABTD,
        writeGMABTD,
        viewGMABTD,
        &(busPortGR_GR1_data.GMABTD.value),
        True
    );
    ppmCreateRegister("GR1_MASK1L",
        0,
        handles.busPortGR,
        64,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x1,
        True
    );
    ppmCreateRegister("GR1_MASK1H",
        0,
        handles.busPortGR,
        66,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x1,
        True
    );
    ppmCreateRegister("GR1_MASK2L",
        0,
        handles.busPortGR,
        68,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x2,
        True
    );
    ppmCreateRegister("GR1_MASK2H",
        0,
        handles.busPortGR,
        70,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x2,
        True
    );
    ppmCreateRegister("GR1_MASK3L",
        0,
        handles.busPortGR,
        72,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x3,
        True
    );
    ppmCreateRegister("GR1_MASK3H",
        0,
        handles.busPortGR,
        74,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x3,
        True
    );
    ppmCreateRegister("GR1_MASK4L",
        0,
        handles.busPortGR,
        76,
        2,
        readMASKL,
        writeMASKL,
        viewMASKL,
        (void*)0x4,
        True
    );
    ppmCreateRegister("GR1_MASK4H",
        0,
        handles.busPortGR,
        78,
        2,
        readMASKH,
        writeMASKH,
        viewMASKH,
        (void*)0x4,
        True
    );
    ppmCreateRegister("GR1_CTRL",
        0,
        handles.busPortGR,
        80,
        2,
        readCTRL,
        writeCTRL,
        viewCTRL,
        &(busPortGR_GR1_data.CTRL.value),
        True
    );
    ppmCreateRegister("GR2_LEC",
        0,
        handles.busPortGR,
        82,
        1,
        readLEC,
        writeLEC,
        viewLEC,
        &(busPortGR_GR2_data.LEC.value),
        True
    );
    ppmCreateRegister("GR2_INFO",
        0,
        handles.busPortGR,
        83,
        1,
        readINFO,
        0,
        viewINFO,
        &(busPortGR_GR2_data.INFO.value),
        True
    );
    ppmCreateRegister("GR3_ERC",
        0,
        handles.busPortGR,
        84,
        2,
        readERC,
        0,
        viewERC,
        &(busPortGR_GR3_data.ERC.value),
        True
    );
    ppmCreateRegister("GR3_IE",
        0,
        handles.busPortGR,
        86,
        2,
        readIE,
        writeIE,
        viewIE,
        &(busPortGR_GR3_data.IE.value),
        True
    );
    ppmCreateRegister("GR3_INTS",
        0,
        handles.busPortGR,
        88,
        2,
        readINTS,
        writeINTS,
        viewINTS,
        &(busPortGR_GR3_data.INTS.value),
        True
    );
    ppmCreateRegister("GR3_BRP",
        0,
        handles.busPortGR,
        90,
        1,
        readBRP,
        writeBRP,
        viewBRP,
        &(busPortGR_GR3_data.BRP.value),
        True
    );
    ppmCreateRegister("GR3_BTR",
        0,
        handles.busPortGR,
        92,
        2,
        readBTR,
        writeBTR,
        viewBTR,
        &(busPortGR_GR3_data.BTR.value),
        True
    );
    ppmCreateRegister("GR3_LIPT",
        0,
        handles.busPortGR,
        94,
        1,
        readLIPT,
        0,
        viewLIPT,
        &(busPortGR_GR3_data.LIPT.value),
        True
    );
    ppmCreateRegister("GR3_RGPT",
        0,
        handles.busPortGR,
        96,
        2,
        readRGPT,
        writeRGPT,
        viewRGPT,
        &(busPortGR_GR3_data.RGPT.value),
        True
    );
    ppmCreateRegister("GR3_LOPT",
        0,
        handles.busPortGR,
        98,
        1,
        readLOPT,
        0,
        viewLOPT,
        &(busPortGR_GR3_data.LOPT.value),
        True
    );
    ppmCreateRegister("GR3_TGPT",
        0,
        handles.busPortGR,
        100,
        2,
        readTGPT,
        writeTGPT,
        viewTGPT,
        &(busPortGR_GR3_data.TGPT.value),
        True
    );
    ppmCreateRegister("GR3_TS",
        0,
        handles.busPortGR,
        102,
        2,
        readTS,
        writeTS,
        viewTS,
        &(busPortGR_GR3_data.TS.value),
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
        ppmDocAddText(doc_32_node, "V850E/PHO3 uPD70F3441, uPD70F3483: R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

