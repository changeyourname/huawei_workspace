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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridADC", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CAL_maskWrite) {
    bport1_ab_data.CAL.value = (bport1_ab_data.CAL.value & 0xfffffff0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_CFG_maskWrite) {
    bport1_ab_data.CFG.value = (bport1_ab_data.CFG.value & 0xfffe0000) | (data & 0x1ffff);
}

static PPM_WRITE_CB(bport1_ab_CV_maskWrite) {
    bport1_ab_data.CV.value = (bport1_ab_data.CV.value & 0xf000f000) | (data & 0xfff0fff);
}

static PPM_WRITE_CB(bport1_ab_GC_maskWrite) {
    bport1_ab_data.GC.value = (bport1_ab_data.GC.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_HC0_maskWrite) {
    bport1_ab_data.HC0.value = (bport1_ab_data.HC0.value & 0xffffff60) | (data & 0x9f);
}

static PPM_WRITE_CB(bport1_ab_HC1_maskWrite) {
    bport1_ab_data.HC1.value = (bport1_ab_data.HC1.value & 0xffffff60) | (data & 0x9f);
}

static PPM_WRITE_CB(bport1_ab_OFS_maskWrite) {
    bport1_ab_data.OFS.value = (bport1_ab_data.OFS.value & 0xffffe000) | (data & 0x1fff);
}

static PPM_WRITE_CB(bport1_ab_PCTL_maskWrite) {
    bport1_ab_data.PCTL.value = (bport1_ab_data.PCTL.value & 0xff000000) | (data & 0xffffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_HC0",
        "Control register for hardware triggers, offset: 0x0",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_HC0_maskWrite,
        view32,
        &(bport1_ab_data.HC0.value),
        True
    );
    ppmCreateRegister("ab_HC1",
        "Control register for hardware triggers, offset: 0x4",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_HC1_maskWrite,
        view32,
        &(bport1_ab_data.HC1.value),
        True
    );
    ppmCreateRegister("ab_HS",
        "Status register for HW triggers, offset: 0x8",
        handles.bport1,
        8,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HS.value),
        True
    );
    ppmCreateRegister("ab_R0",
        "Data result register for HW triggers, offset: 0xC",
        handles.bport1,
        12,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.R0.value),
        True
    );
    ppmCreateRegister("ab_R1",
        "Data result register for HW triggers, offset: 0x10",
        handles.bport1,
        16,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.R1.value),
        True
    );
    ppmCreateRegister("ab_CFG",
        "Configuration register, offset: 0x14",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_CFG_maskWrite,
        view32,
        &(bport1_ab_data.CFG.value),
        True
    );
    ppmCreateRegister("ab_GC",
        "General control register, offset: 0x18",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_GC_maskWrite,
        view32,
        &(bport1_ab_data.GC.value),
        True
    );
    ppmCreateRegister("ab_GS",
        "General status register, offset: 0x1C",
        handles.bport1,
        28,
        4,
        read_32,
        GSWrite1C,
        view32,
        &(bport1_ab_data.GS.value),
        True
    );
    ppmCreateRegister("ab_CV",
        "Compare value register, offset: 0x20",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_CV_maskWrite,
        view32,
        &(bport1_ab_data.CV.value),
        True
    );
    ppmCreateRegister("ab_OFS",
        "Offset correction value register, offset: 0x24",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_OFS_maskWrite,
        view32,
        &(bport1_ab_data.OFS.value),
        True
    );
    ppmCreateRegister("ab_CAL",
        "Calibration value register, offset: 0x28",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_CAL_maskWrite,
        view32,
        &(bport1_ab_data.CAL.value),
        True
    );
    ppmCreateRegister("ab_PCTL",
        "Pin control register, offset: 0x30",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_PCTL_maskWrite,
        view32,
        &(bport1_ab_data.PCTL.value),
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
        bport1_ab_data.PCTL.value = 0x0;
        bport1_ab_data.CAL.value = 0x0;
        bport1_ab_data.OFS.value = 0x0;
        bport1_ab_data.CV.value = 0x0;
        bport1_ab_data.GS.value = 0x0;
        bport1_ab_data.GC.value = 0x0;
        bport1_ab_data.CFG.value = 0x200;
        bport1_ab_data.R1.value = 0x0;
        bport1_ab_data.R0.value = 0x0;
        bport1_ab_data.HS.value = 0x0;
        bport1_ab_data.HC1.value = 0x1f;
        bport1_ab_data.HC0.value = 0x1f;
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

