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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCMP", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CR0_maskWrite) {
    bport1_ab_data.CR0.value = (bport1_ab_data.CR0.value & 0x8c) | (data & 0x73);
}

static PPM_WRITE_CB(bport1_ab_FPR_maskWrite) {
    bport1_ab_data.FPR.value = (bport1_ab_data.FPR.value & 0x0) | (data & 0xff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 8);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_CR0",
        "CMP Control Register 0, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        bport1_ab_CR0_maskWrite,
        view8,
        &(bport1_ab_data.CR0.value),
        True
    );
    ppmCreateRegister("ab_CR1",
        "CMP Control Register 1, offset: 0x1 ",
        handles.bport1,
        1,
        1,
        read_8,
        writeCR1,
        view8,
        &(bport1_ab_data.CR1.value),
        True
    );
    ppmCreateRegister("ab_FPR",
        "CMP Filter Period Register, offset: 0x2 ",
        handles.bport1,
        2,
        1,
        read_8,
        bport1_ab_FPR_maskWrite,
        view8,
        &(bport1_ab_data.FPR.value),
        True
    );
    ppmCreateRegister("ab_SCR",
        "CMP Status and Control Register, offset: 0x3 ",
        handles.bport1,
        3,
        1,
        read_8,
        writeSCR,
        view8,
        &(bport1_ab_data.SCR.value),
        True
    );
    ppmCreateRegister("ab_DACCR",
        "DAC Control Register, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        writeDAC,
        view8,
        &(bport1_ab_data.DACCR.value),
        True
    );
    ppmCreateRegister("ab_MUXCR",
        "MUX Control Register, offset: 0x5 ",
        handles.bport1,
        5,
        1,
        read_8,
        writeMUX,
        view8,
        &(bport1_ab_data.MUXCR.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, reset_Reset, (void*)0);
    }

    handles.ExtSample = ppmOpenNetPort("ExtSample");
    if (handles.ExtSample) {
        ppmInstallNetCallback(handles.ExtSample, extSampleCB, (void*)0);
    }

    handles.Vin1 = ppmOpenNetPort("Vin1");

    handles.Vin2 = ppmOpenNetPort("Vin2");

    handles.Input0 = ppmOpenNetPort("Input0");
    if (handles.Input0) {
        ppmInstallNetCallback(handles.Input0, input0CB, (void*)0);
    }

    handles.Input1 = ppmOpenNetPort("Input1");
    if (handles.Input1) {
        ppmInstallNetCallback(handles.Input1, input1CB, (void*)0);
    }

    handles.Input2 = ppmOpenNetPort("Input2");
    if (handles.Input2) {
        ppmInstallNetCallback(handles.Input2, input2CB, (void*)0);
    }

    handles.Input3 = ppmOpenNetPort("Input3");
    if (handles.Input3) {
        ppmInstallNetCallback(handles.Input3, input3CB, (void*)0);
    }

    handles.Input4 = ppmOpenNetPort("Input4");
    if (handles.Input4) {
        ppmInstallNetCallback(handles.Input4, input4CB, (void*)0);
    }

    handles.Input5 = ppmOpenNetPort("Input5");
    if (handles.Input5) {
        ppmInstallNetCallback(handles.Input5, input5CB, (void*)0);
    }

    handles.Input6 = ppmOpenNetPort("Input6");
    if (handles.Input6) {
        ppmInstallNetCallback(handles.Input6, input6CB, (void*)0);
    }

    handles.Input7 = ppmOpenNetPort("Input7");
    if (handles.Input7) {
        ppmInstallNetCallback(handles.Input7, input7CB, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.DacOutput, value);

    handles.DacOutput = ppmOpenNetPort("DacOutput");

// To write to this net, use ppmWriteNet(handles.CoutSoc, value);

    handles.CoutSoc = ppmOpenNetPort("CoutSoc");

// To write to this net, use ppmWriteNet(handles.Interrupt, value);

    handles.Interrupt = ppmOpenNetPort("Interrupt");

// To write to this net, use ppmWriteNet(handles.DmaReq, value);

    handles.DmaReq = ppmOpenNetPort("DmaReq");

// To write to this net, use ppmWriteNet(handles.CmpOPad, value);

    handles.CmpOPad = ppmOpenNetPort("CmpOPad");

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.MUXCR.value = 0x0;
        bport1_ab_data.DACCR.value = 0x0;
        bport1_ab_data.SCR.value = 0x0;
        bport1_ab_data.FPR.value = 0x0;
        bport1_ab_data.CR1.value = 0x0;
        bport1_ab_data.CR0.value = 0x0;
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

