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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UartPL011", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_dr",
        "UARTDR",
        handles.bport1,
        0,
        1,
        readDR,
        writeDR,
        view8,
        &(bport1_ab_data.dr.value),
        True
    );
    ppmCreateRegister("ab_ecr",
        "UARTECR",
        handles.bport1,
        4,
        1,
        readECR,
        write_8,
        view8,
        &(bport1_ab_data.ecr.value),
        True
    );
    ppmCreateRegister("ab_flags",
        "UARTFR",
        handles.bport1,
        24,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.flags.value),
        True
    );
    ppmCreateRegister("ab_ilpr",
        "UARTILPR",
        handles.bport1,
        32,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.ilpr.value),
        True
    );
    ppmCreateRegister("ab_ibrd",
        "UARTIBRD",
        handles.bport1,
        36,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.ibrd.value),
        True
    );
    ppmCreateRegister("ab_vbrd",
        "UARTFBRD",
        handles.bport1,
        40,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.vbrd.value),
        True
    );
    ppmCreateRegister("ab_lcr",
        "UARTLCR_H",
        handles.bport1,
        44,
        1,
        read_8,
        writeLCR,
        view8,
        &(bport1_ab_data.lcr.value),
        True
    );
    ppmCreateRegister("ab_cr",
        "UARTCR",
        handles.bport1,
        48,
        1,
        read_8,
        write_8,
        view8,
        &(bport1_ab_data.cr.value),
        True
    );
    ppmCreateRegister("ab_ifl",
        "UARTIFS",
        handles.bport1,
        52,
        1,
        read_8,
        writeIFL,
        view8,
        &(bport1_ab_data.ifl.value),
        True
    );
    ppmCreateRegister("ab_int_enabled",
        "UARTIMSC",
        handles.bport1,
        56,
        1,
        read_8,
        writeIMSC,
        view8,
        &(bport1_ab_data.int_enabled.value),
        True
    );
    ppmCreateRegister("ab_int_level",
        "UARTRIS",
        handles.bport1,
        60,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.int_level.value),
        True
    );
    ppmCreateRegister("ab_mis",
        "UARTMIS",
        handles.bport1,
        64,
        1,
        readMIS,
        0,
        view8,
        &(bport1_ab_data.mis.value),
        True
    );
    ppmCreateRegister("ab_icr",
        "UARTDICR",
        handles.bport1,
        68,
        1,
        0,
        writeICR,
        view8,
        &(bport1_ab_data.icr.value),
        True
    );
    ppmCreateRegister("ab_dmacr",
        "UARTDMACR",
        handles.bport1,
        72,
        1,
        read_8,
        writeDMA,
        view8,
        &(bport1_ab_data.dmacr.value),
        True
    );
    ppmCreateRegister("ab_id0",
        0,
        handles.bport1,
        4064,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id0.value),
        True
    );
    ppmCreateRegister("ab_id1",
        0,
        handles.bport1,
        4068,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id1.value),
        True
    );
    ppmCreateRegister("ab_id2",
        0,
        handles.bport1,
        4072,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id2.value),
        True
    );
    ppmCreateRegister("ab_id3",
        0,
        handles.bport1,
        4076,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id3.value),
        True
    );
    ppmCreateRegister("ab_id4",
        0,
        handles.bport1,
        4080,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id4.value),
        True
    );
    ppmCreateRegister("ab_id5",
        0,
        handles.bport1,
        4084,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id5.value),
        True
    );
    ppmCreateRegister("ab_id6",
        0,
        handles.bport1,
        4088,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id6.value),
        True
    );
    ppmCreateRegister("ab_id7",
        0,
        handles.bport1,
        4092,
        4,
        readID,
        0,
        view32,
        &(bport1_ab_data.id7.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq, value);

    handles.irq = ppmOpenNetPort("irq");

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
        ppmDocAddText(doc2_node, "ARM PL011 UART");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "This is not a complete model of the PL011. There is no modeling of physical aspects of the UART, such as baud rates etc.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM PrimeCell UART (PL011) Technical Reference Manual (ARM DDI 0183)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    closeDown();
    return 0;
}

