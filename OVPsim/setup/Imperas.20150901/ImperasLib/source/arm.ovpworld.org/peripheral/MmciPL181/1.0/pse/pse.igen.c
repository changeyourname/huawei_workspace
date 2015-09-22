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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "MmciPL181", "Example");
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

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

    ppmInstallReadCallback(reservedRead, (void*)0x0 , handles.bport1 + 0x4c, 0x34);
    ppmInstallWriteCallback(reservedWrite, (void*)0x0 , handles.bport1 + 0x4c, 0x34);
    ppmInstallReadCallback(reservedRead, (void*)0x0 , handles.bport1 + 0xc0, 0xf20);
    ppmInstallWriteCallback(reservedWrite, (void*)0x0 , handles.bport1 + 0xc0, 0xf20);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_power",
        "Power Control",
        handles.bport1,
        0,
        4,
        read_32,
        write8,
        view32,
        &(bport1_ab_data.power.value),
        True
    );
    ppmCreateRegister("ab_clock",
        "Clock Control",
        handles.bport1,
        4,
        4,
        read_32,
        writeClock,
        view32,
        &(bport1_ab_data.clock.value),
        True
    );
    ppmCreateRegister("ab_cmdarg",
        "Command Arguments",
        handles.bport1,
        8,
        4,
        read_32,
        writeArg,
        view32,
        &(bport1_ab_data.cmdarg.value),
        True
    );
    ppmCreateRegister("ab_cmd",
        "Command",
        handles.bport1,
        12,
        4,
        read_32,
        writeCmd,
        view32,
        &(bport1_ab_data.cmd.value),
        True
    );
    ppmCreateRegister("ab_respcmd",
        "RESP Command",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.respcmd.value),
        True
    );
    ppmCreateRegister("ab_response0",
        "Response 0",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.response0.value),
        True
    );
    ppmCreateRegister("ab_response1",
        "Response 1",
        handles.bport1,
        24,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.response1.value),
        True
    );
    ppmCreateRegister("ab_response2",
        "Response 2",
        handles.bport1,
        28,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.response2.value),
        True
    );
    ppmCreateRegister("ab_response3",
        "Response 3",
        handles.bport1,
        32,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.response3.value),
        True
    );
    ppmCreateRegister("ab_datatimer",
        "Data Timer",
        handles.bport1,
        36,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.datatimer.value),
        True
    );
    ppmCreateRegister("ab_datalength",
        "Data Length",
        handles.bport1,
        40,
        4,
        read_32,
        writeDL,
        view32,
        &(bport1_ab_data.datalength.value),
        True
    );
    ppmCreateRegister("ab_datactrl",
        "Data Control",
        handles.bport1,
        44,
        4,
        read_32,
        writeDC,
        view32,
        &(bport1_ab_data.datactrl.value),
        True
    );
    ppmCreateRegister("ab_datacnt",
        "Data Count",
        handles.bport1,
        48,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.datacnt.value),
        True
    );
    ppmCreateRegister("ab_status",
        "Data Count",
        handles.bport1,
        52,
        4,
        readStatus,
        0,
        view32,
        &(bport1_ab_data.status.value),
        True
    );
    ppmCreateRegister("ab_clear",
        "Clear",
        handles.bport1,
        56,
        4,
        0,
        writeClear,
        view32,
        &(bport1_ab_data.clear.value),
        True
    );
    ppmCreateRegister("ab_mask0",
        "Mask 0",
        handles.bport1,
        60,
        4,
        read_32,
        writeMask0,
        view32,
        &(bport1_ab_data.mask0.value),
        True
    );
    ppmCreateRegister("ab_mask1",
        "Mask 1",
        handles.bport1,
        64,
        4,
        read_32,
        writeMask1,
        view32,
        &(bport1_ab_data.mask1.value),
        True
    );
    ppmCreateRegister("ab_fifoCnt",
        "FIFO Count",
        handles.bport1,
        72,
        4,
        readFifoCnt,
        0,
        view32,
        &(bport1_ab_data.fifoCnt.value),
        True
    );
    ppmCreateRegister("ab_periphID0",
        "ID Register 0",
        handles.bport1,
        4064,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.periphID0.value),
        True
    );
    ppmCreateRegister("ab_periphID1",
        "ID Register 1",
        handles.bport1,
        4068,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.periphID1.value),
        True
    );
    ppmCreateRegister("ab_periphID2",
        "ID Register 2",
        handles.bport1,
        4072,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.periphID2.value),
        True
    );
    ppmCreateRegister("ab_periphID3",
        "ID Register 3",
        handles.bport1,
        4076,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.periphID3.value),
        True
    );
    ppmCreateRegister("ab_pCellID0",
        "Cell ID 0",
        handles.bport1,
        4080,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pCellID0.value),
        True
    );
    ppmCreateRegister("ab_pCellID1",
        "Cell ID 1",
        handles.bport1,
        4084,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pCellID1.value),
        True
    );
    ppmCreateRegister("ab_pCellID2",
        "Cell ID 2",
        handles.bport1,
        4088,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pCellID2.value),
        True
    );
    ppmCreateRegister("ab_pCellID3",
        "Cell ID 3",
        handles.bport1,
        4092,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.pCellID3.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq0, value);

    handles.irq0 = ppmOpenNetPort("irq0");

// To write to this net, use ppmWriteNet(handles.irq1, value);

    handles.irq1 = ppmOpenNetPort("irq1");

// To write to this net, use ppmWriteNet(handles.cardin, value);

    handles.cardin = ppmOpenNetPort("cardin");

// To write to this net, use ppmWriteNet(handles.wprot, value);

    handles.wprot = ppmOpenNetPort("wprot");

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.pCellID3.value = 0xb1;
        bport1_ab_data.pCellID2.value = 0x5;
        bport1_ab_data.pCellID1.value = 0xf0;
        bport1_ab_data.pCellID0.value = 0xd;
        bport1_ab_data.periphID3.value = 0x0;
        bport1_ab_data.periphID2.value = 0x4;
        bport1_ab_data.periphID1.value = 0x11;
        bport1_ab_data.periphID0.value = 0x81;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM PrimeCell Multimedia Card Interface (MMCI)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "None");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "ARM PrimeCell Multimedia Card Interface (Pl180) Technical Reference Manual (ARM DDI 0172)");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

