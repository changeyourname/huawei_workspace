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

sp1_reg0_dataT sp1_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "Uart", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp1 = ppmCreateSlaveBusPort("sp1", 32);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("reg0_rxdata",
        0,
        handles.sp1,
        0,
        4,
        read_rxdata,
        0,
        view32,
        &(sp1_reg0_data.rxdata.value),
        True
    );
    ppmCreateRegister("reg0_txdata",
        0,
        handles.sp1,
        4,
        4,
        0,
        write_txdata,
        view32,
        &(sp1_reg0_data.txdata.value),
        True
    );
    ppmCreateRegister("reg0_status",
        0,
        handles.sp1,
        8,
        4,
        read_status,
        write_status,
        view32,
        &(sp1_reg0_data.status.value),
        True
    );
    ppmCreateRegister("reg0_control",
        0,
        handles.sp1,
        12,
        4,
        read_control,
        write_control,
        view32,
        &(sp1_reg0_data.control.value),
        True
    );
    ppmCreateRegister("reg0_divisor",
        0,
        handles.sp1,
        16,
        4,
        read_divisor,
        write_divisor,
        view32,
        &(sp1_reg0_data.divisor.value),
        True
    );
    ppmCreateRegister("reg0_eop",
        0,
        handles.sp1,
        20,
        4,
        read_eop,
        write_eop,
        view32,
        &(sp1_reg0_data.eop.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.irq, value);

    handles.irq = ppmOpenNetPort("irq");

// To write to this net, use ppmWriteNet(handles.endofpacket, value);

    handles.endofpacket = ppmOpenNetPort("endofpacket");

// To write to this net, use ppmWriteNet(handles.dataavailable, value);

    handles.dataavailable = ppmOpenNetPort("dataavailable");

// To write to this net, use ppmWriteNet(handles.readyfordata, value);

    handles.readyfordata = ppmOpenNetPort("readyfordata");

    handles.RXD = ppmOpenNetPort("RXD");

    handles.CTS = ppmOpenNetPort("CTS");

// To write to this net, use ppmWriteNet(handles.TXD, value);

    handles.TXD = ppmOpenNetPort("TXD");

// To write to this net, use ppmWriteNet(handles.RTS, value);

    handles.RTS = ppmOpenNetPort("RTS");

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        sp1_reg0_data.eop.value = 0x0;
        sp1_reg0_data.divisor.value = 0x0;
        sp1_reg0_data.control.value = 0x0;
        sp1_reg0_data.status.value = 0xc60;
        sp1_reg0_data.txdata.value = 0x0;
        sp1_reg0_data.rxdata.value = 0x0;
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
        ppmDocAddText(doc_12_node, "Altera Avalon UART");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No Support for pin level transitions");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

