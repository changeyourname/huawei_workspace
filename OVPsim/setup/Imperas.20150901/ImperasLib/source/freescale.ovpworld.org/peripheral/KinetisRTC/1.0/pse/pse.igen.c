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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisRTC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CR_maskWrite) {
    bport1_ab_data.CR.value = (bport1_ab_data.CR.value & 0xffffc0f0) | (data & 0x3f0f);
}

static PPM_WRITE_CB(bport1_ab_IER_maskWrite) {
    bport1_ab_data.IER.value = (bport1_ab_data.IER.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_LR_maskWrite) {
    bport1_ab_data.LR.value = (bport1_ab_data.LR.value & 0xffff0087) | (data & 0xff78);
}

static PPM_WRITE_CB(bport1_ab_MCHR_maskWrite) {
    bport1_ab_data.MCHR.value = (bport1_ab_data.MCHR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MCLR_maskWrite) {
    bport1_ab_data.MCLR.value = (bport1_ab_data.MCLR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_MER_maskWrite) {
    bport1_ab_data.MER.value = (bport1_ab_data.MER.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_RAR_maskWrite) {
    bport1_ab_data.RAR.value = (bport1_ab_data.RAR.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & 0xffffffef) | (data & 0x10);
}

static PPM_WRITE_CB(bport1_ab_TAR_maskWrite) {
    bport1_ab_data.TAR.value = (bport1_ab_data.TAR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_TDR_maskWrite) {
    bport1_ab_data.TDR.value = (bport1_ab_data.TDR.value & 0xffffffc1) | (data & 0x3e);
}

static PPM_WRITE_CB(bport1_ab_TER_maskWrite) {
    bport1_ab_data.TER.value = (bport1_ab_data.TER.value & 0xffffffc1) | (data & 0x3e);
}

static PPM_WRITE_CB(bport1_ab_TIR_maskWrite) {
    bport1_ab_data.TIR.value = (bport1_ab_data.TIR.value & 0xffffffc1) | (data & 0x3e);
}

static PPM_WRITE_CB(bport1_ab_TPR_maskWrite) {
    bport1_ab_data.TPR.value = (bport1_ab_data.TPR.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_TSR_maskWrite) {
    bport1_ab_data.TSR.value = (bport1_ab_data.TSR.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_TTR_maskWrite) {
    bport1_ab_data.TTR.value = (bport1_ab_data.TTR.value & 0xfffc0000) | (data & 0x3ffff);
}

static PPM_WRITE_CB(bport1_ab_WAR_maskWrite) {
    bport1_ab_data.WAR.value = (bport1_ab_data.WAR.value & 0xffff0000) | (data & 0xffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_TSR",
        "RTC Time Seconds Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_TSR_maskWrite,
        view32,
        &(bport1_ab_data.TSR.value),
        True
    );
    ppmCreateRegister("ab_TPR",
        "RTC Time Prescaler Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_TPR_maskWrite,
        view32,
        &(bport1_ab_data.TPR.value),
        True
    );
    ppmCreateRegister("ab_TAR",
        "RTC Time Alarm Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_TAR_maskWrite,
        view32,
        &(bport1_ab_data.TAR.value),
        True
    );
    ppmCreateRegister("ab_TCR",
        "RTC Time Compensation Register, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_TCR_maskWrite,
        view32,
        &(bport1_ab_data.TCR.value),
        True
    );
    ppmCreateRegister("ab_CR",
        "RTC Control Register, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_CR_maskWrite,
        view32,
        &(bport1_ab_data.CR.value),
        True
    );
    ppmCreateRegister("ab_SR",
        "RTC Status Register, offset: 0x14 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_SR_maskWrite,
        view32,
        &(bport1_ab_data.SR.value),
        True
    );
    ppmCreateRegister("ab_LR",
        "RTC Lock Register, offset: 0x18 ",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_LR_maskWrite,
        view32,
        &(bport1_ab_data.LR.value),
        True
    );
    ppmCreateRegister("ab_IER",
        "RTC Interrupt Enable Register, offset: 0x1C ",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_IER_maskWrite,
        view32,
        &(bport1_ab_data.IER.value),
        True
    );
    ppmCreateRegister("ab_TTSR",
        "RTC Tamper Time Seconds Register, offset: 0x20 ",
        handles.bport1,
        32,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.TTSR.value),
        True
    );
    ppmCreateRegister("ab_MER",
        "RTC Monotonic Enable Register, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_MER_maskWrite,
        view32,
        &(bport1_ab_data.MER.value),
        True
    );
    ppmCreateRegister("ab_MCLR",
        "RTC Monotonic Counter Low Register, offset: 0x28 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_MCLR_maskWrite,
        view32,
        &(bport1_ab_data.MCLR.value),
        True
    );
    ppmCreateRegister("ab_MCHR",
        "RTC Monotonic Counter High Register, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_MCHR_maskWrite,
        view32,
        &(bport1_ab_data.MCHR.value),
        True
    );
    ppmCreateRegister("ab_TER",
        "RTC Tamper Enable Register, offset: 0x30 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_TER_maskWrite,
        view32,
        &(bport1_ab_data.TER.value),
        True
    );
    ppmCreateRegister("ab_TDR",
        "RTC Tamper Detect Register, offset: 0x34 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_TDR_maskWrite,
        view32,
        &(bport1_ab_data.TDR.value),
        True
    );
    ppmCreateRegister("ab_TTR",
        "RTC Tamper Trim Register, offset: 0x38 ",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_TTR_maskWrite,
        view32,
        &(bport1_ab_data.TTR.value),
        True
    );
    ppmCreateRegister("ab_TIR",
        "RTC Tamper Interrupt Register, offset: 0x3C ",
        handles.bport1,
        60,
        4,
        read_32,
        bport1_ab_TIR_maskWrite,
        view32,
        &(bport1_ab_data.TIR.value),
        True
    );
    ppmCreateRegister("ab_WAR",
        "RTC Write Access Register, offset: 0x800 ",
        handles.bport1,
        2048,
        4,
        read_32,
        bport1_ab_WAR_maskWrite,
        view32,
        &(bport1_ab_data.WAR.value),
        True
    );
    ppmCreateRegister("ab_RAR",
        "RTC Read Access Register, offset: 0x804 ",
        handles.bport1,
        2052,
        4,
        read_32,
        bport1_ab_RAR_maskWrite,
        view32,
        &(bport1_ab_data.RAR.value),
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
        bport1_ab_data.RAR.value = 0xffff;
        bport1_ab_data.WAR.value = 0xffff;
        bport1_ab_data.TIR.value = 0x0;
        bport1_ab_data.TTR.value = 0x0;
        bport1_ab_data.TDR.value = 0x0;
        bport1_ab_data.TER.value = 0x0;
        bport1_ab_data.MCHR.value = 0x0;
        bport1_ab_data.MCLR.value = 0x0;
        bport1_ab_data.MER.value = 0x0;
        bport1_ab_data.TTSR.value = 0x0;
        bport1_ab_data.IER.value = 0x7;
        bport1_ab_data.LR.value = 0xffff;
        bport1_ab_data.SR.value = 0x1;
        bport1_ab_data.CR.value = 0x0;
        bport1_ab_data.TCR.value = 0x0;
        bport1_ab_data.TAR.value = 0x0;
        bport1_ab_data.TPR.value = 0x0;
        bport1_ab_data.TSR.value = 0x0;
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

