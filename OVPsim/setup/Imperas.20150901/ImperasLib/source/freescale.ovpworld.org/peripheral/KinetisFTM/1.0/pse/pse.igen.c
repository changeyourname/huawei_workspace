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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFTM", "Example");
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

static PPM_WRITE_CB(bport1_ab_C0SC_maskWrite) {
    bport1_ab_data.C0SC.value = (bport1_ab_data.C0SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C0V_maskWrite) {
    bport1_ab_data.C0V.value = (bport1_ab_data.C0V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C1SC_maskWrite) {
    bport1_ab_data.C1SC.value = (bport1_ab_data.C1SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C1V_maskWrite) {
    bport1_ab_data.C1V.value = (bport1_ab_data.C1V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C2SC_maskWrite) {
    bport1_ab_data.C2SC.value = (bport1_ab_data.C2SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C2V_maskWrite) {
    bport1_ab_data.C2V.value = (bport1_ab_data.C2V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C3SC_maskWrite) {
    bport1_ab_data.C3SC.value = (bport1_ab_data.C3SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C3V_maskWrite) {
    bport1_ab_data.C3V.value = (bport1_ab_data.C3V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C4SC_maskWrite) {
    bport1_ab_data.C4SC.value = (bport1_ab_data.C4SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C4V_maskWrite) {
    bport1_ab_data.C4V.value = (bport1_ab_data.C4V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C5SC_maskWrite) {
    bport1_ab_data.C5SC.value = (bport1_ab_data.C5SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C5V_maskWrite) {
    bport1_ab_data.C5V.value = (bport1_ab_data.C5V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C6SC_maskWrite) {
    bport1_ab_data.C6SC.value = (bport1_ab_data.C6SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C6V_maskWrite) {
    bport1_ab_data.C6V.value = (bport1_ab_data.C6V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_C7SC_maskWrite) {
    bport1_ab_data.C7SC.value = (bport1_ab_data.C7SC.value & 0xffffff82) | (data & 0x7d);
}

static PPM_WRITE_CB(bport1_ab_C7V_maskWrite) {
    bport1_ab_data.C7V.value = (bport1_ab_data.C7V.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CNTIN_maskWrite) {
    bport1_ab_data.CNTIN.value = (bport1_ab_data.CNTIN.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CNT_maskWrite) {
    bport1_ab_data.CNT.value = (bport1_ab_data.CNT.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_COMBINE_maskWrite) {
    bport1_ab_data.COMBINE.value = (bport1_ab_data.COMBINE.value & 0x80808080) | (data & 0x7f7f7f7f);
}

static PPM_WRITE_CB(bport1_ab_CONF_maskWrite) {
    bport1_ab_data.CONF.value = (bport1_ab_data.CONF.value & 0xfffff920) | (data & 0x6df);
}

static PPM_WRITE_CB(bport1_ab_DEADTIME_maskWrite) {
    bport1_ab_data.DEADTIME.value = (bport1_ab_data.DEADTIME.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_EXTTRIG_maskWrite) {
    bport1_ab_data.EXTTRIG.value = (bport1_ab_data.EXTTRIG.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_FILTER_maskWrite) {
    bport1_ab_data.FILTER.value = (bport1_ab_data.FILTER.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_FLTCTRL_maskWrite) {
    bport1_ab_data.FLTCTRL.value = (bport1_ab_data.FLTCTRL.value & 0xfffff000) | (data & 0xfff);
}

static PPM_WRITE_CB(bport1_ab_FLTPOL_maskWrite) {
    bport1_ab_data.FLTPOL.value = (bport1_ab_data.FLTPOL.value & 0xfffffff0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_FMS_maskWrite) {
    bport1_ab_data.FMS.value = (bport1_ab_data.FMS.value & 0xffffffbf) | (data & 0x40);
}

static PPM_WRITE_CB(bport1_ab_INVCTRL_maskWrite) {
    bport1_ab_data.INVCTRL.value = (bport1_ab_data.INVCTRL.value & 0xfffffff0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_MODE_maskWrite) {
    bport1_ab_data.MODE.value = (bport1_ab_data.MODE.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_MOD_maskWrite) {
    bport1_ab_data.MOD.value = (bport1_ab_data.MOD.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_OUTINIT_maskWrite) {
    bport1_ab_data.OUTINIT.value = (bport1_ab_data.OUTINIT.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_OUTMASK_maskWrite) {
    bport1_ab_data.OUTMASK.value = (bport1_ab_data.OUTMASK.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_POL_maskWrite) {
    bport1_ab_data.POL.value = (bport1_ab_data.POL.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_PWMLOAD_maskWrite) {
    bport1_ab_data.PWMLOAD.value = (bport1_ab_data.PWMLOAD.value & 0xfffffd00) | (data & 0x2ff);
}

static PPM_WRITE_CB(bport1_ab_QDCTRL_maskWrite) {
    bport1_ab_data.QDCTRL.value = (bport1_ab_data.QDCTRL.value & 0xffffff06) | (data & 0xf9);
}

static PPM_WRITE_CB(bport1_ab_SWOCTRL_maskWrite) {
    bport1_ab_data.SWOCTRL.value = (bport1_ab_data.SWOCTRL.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_SYNCONF_maskWrite) {
    bport1_ab_data.SYNCONF.value = (bport1_ab_data.SYNCONF.value & 0xffe0e04a) | (data & 0x1f1fb5);
}

static PPM_WRITE_CB(bport1_ab_SYNC_maskWrite) {
    bport1_ab_data.SYNC.value = (bport1_ab_data.SYNC.value & 0xffffff00) | (data & 0xff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_SC",
        "Status and Control, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        readSC,
        writeSC,
        view32,
        &(bport1_ab_data.SC.value),
        True
    );
    ppmCreateRegister("ab_CNT",
        "Counter, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_CNT_maskWrite,
        view32,
        &(bport1_ab_data.CNT.value),
        True
    );
    ppmCreateRegister("ab_MOD",
        "Modulo, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_MOD_maskWrite,
        view32,
        &(bport1_ab_data.MOD.value),
        True
    );
    ppmCreateRegister("ab_C0SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_C0SC_maskWrite,
        view32,
        &(bport1_ab_data.C0SC.value),
        True
    );
    ppmCreateRegister("ab_C0V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        16,
        4,
        read_32,
        bport1_ab_C0V_maskWrite,
        view32,
        &(bport1_ab_data.C0V.value),
        True
    );
    ppmCreateRegister("ab_C1SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        20,
        4,
        read_32,
        bport1_ab_C1SC_maskWrite,
        view32,
        &(bport1_ab_data.C1SC.value),
        True
    );
    ppmCreateRegister("ab_C1V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_C1V_maskWrite,
        view32,
        &(bport1_ab_data.C1V.value),
        True
    );
    ppmCreateRegister("ab_C2SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_C2SC_maskWrite,
        view32,
        &(bport1_ab_data.C2SC.value),
        True
    );
    ppmCreateRegister("ab_C2V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_C2V_maskWrite,
        view32,
        &(bport1_ab_data.C2V.value),
        True
    );
    ppmCreateRegister("ab_C3SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_C3SC_maskWrite,
        view32,
        &(bport1_ab_data.C3SC.value),
        True
    );
    ppmCreateRegister("ab_C3V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_C3V_maskWrite,
        view32,
        &(bport1_ab_data.C3V.value),
        True
    );
    ppmCreateRegister("ab_C4SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_C4SC_maskWrite,
        view32,
        &(bport1_ab_data.C4SC.value),
        True
    );
    ppmCreateRegister("ab_C4V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_C4V_maskWrite,
        view32,
        &(bport1_ab_data.C4V.value),
        True
    );
    ppmCreateRegister("ab_C5SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_C5SC_maskWrite,
        view32,
        &(bport1_ab_data.C5SC.value),
        True
    );
    ppmCreateRegister("ab_C5V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_C5V_maskWrite,
        view32,
        &(bport1_ab_data.C5V.value),
        True
    );
    ppmCreateRegister("ab_C6SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        60,
        4,
        read_32,
        bport1_ab_C6SC_maskWrite,
        view32,
        &(bport1_ab_data.C6SC.value),
        True
    );
    ppmCreateRegister("ab_C6V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_C6V_maskWrite,
        view32,
        &(bport1_ab_data.C6V.value),
        True
    );
    ppmCreateRegister("ab_C7SC",
        "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_C7SC_maskWrite,
        view32,
        &(bport1_ab_data.C7SC.value),
        True
    );
    ppmCreateRegister("ab_C7V",
        "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
        handles.bport1,
        72,
        4,
        read_32,
        bport1_ab_C7V_maskWrite,
        view32,
        &(bport1_ab_data.C7V.value),
        True
    );
    ppmCreateRegister("ab_CNTIN",
        "Counter Initial Value, offset: 0x4C ",
        handles.bport1,
        76,
        4,
        read_32,
        bport1_ab_CNTIN_maskWrite,
        view32,
        &(bport1_ab_data.CNTIN.value),
        True
    );
    ppmCreateRegister("ab_STATUS",
        "Capture and Compare Status, offset: 0x50 ",
        handles.bport1,
        80,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.STATUS.value),
        True
    );
    ppmCreateRegister("ab_MODE",
        "Features Mode Selection, offset: 0x54 ",
        handles.bport1,
        84,
        4,
        read_32,
        bport1_ab_MODE_maskWrite,
        view32,
        &(bport1_ab_data.MODE.value),
        True
    );
    ppmCreateRegister("ab_SYNC",
        "Synchronization, offset: 0x58 ",
        handles.bport1,
        88,
        4,
        read_32,
        bport1_ab_SYNC_maskWrite,
        view32,
        &(bport1_ab_data.SYNC.value),
        True
    );
    ppmCreateRegister("ab_OUTINIT",
        "Initial State for Channels Output, offset: 0x5C ",
        handles.bport1,
        92,
        4,
        read_32,
        bport1_ab_OUTINIT_maskWrite,
        view32,
        &(bport1_ab_data.OUTINIT.value),
        True
    );
    ppmCreateRegister("ab_OUTMASK",
        "Output Mask, offset: 0x60 ",
        handles.bport1,
        96,
        4,
        read_32,
        bport1_ab_OUTMASK_maskWrite,
        view32,
        &(bport1_ab_data.OUTMASK.value),
        True
    );
    ppmCreateRegister("ab_COMBINE",
        "Function for Linked Channels, offset: 0x64 ",
        handles.bport1,
        100,
        4,
        read_32,
        bport1_ab_COMBINE_maskWrite,
        view32,
        &(bport1_ab_data.COMBINE.value),
        True
    );
    ppmCreateRegister("ab_DEADTIME",
        "Deadtime Insertion Control, offset: 0x68 ",
        handles.bport1,
        104,
        4,
        read_32,
        bport1_ab_DEADTIME_maskWrite,
        view32,
        &(bport1_ab_data.DEADTIME.value),
        True
    );
    ppmCreateRegister("ab_EXTTRIG",
        "FTM External Trigger, offset: 0x6C ",
        handles.bport1,
        108,
        4,
        read_32,
        bport1_ab_EXTTRIG_maskWrite,
        view32,
        &(bport1_ab_data.EXTTRIG.value),
        True
    );
    ppmCreateRegister("ab_POL",
        "Channels Polarity, offset: 0x70 ",
        handles.bport1,
        112,
        4,
        read_32,
        bport1_ab_POL_maskWrite,
        view32,
        &(bport1_ab_data.POL.value),
        True
    );
    ppmCreateRegister("ab_FMS",
        "Fault Mode Status, offset: 0x74 ",
        handles.bport1,
        116,
        4,
        read_32,
        bport1_ab_FMS_maskWrite,
        view32,
        &(bport1_ab_data.FMS.value),
        True
    );
    ppmCreateRegister("ab_FILTER",
        "Input Capture Filter Control, offset: 0x78 ",
        handles.bport1,
        120,
        4,
        read_32,
        bport1_ab_FILTER_maskWrite,
        view32,
        &(bport1_ab_data.FILTER.value),
        True
    );
    ppmCreateRegister("ab_FLTCTRL",
        "Fault Control, offset: 0x7C ",
        handles.bport1,
        124,
        4,
        read_32,
        bport1_ab_FLTCTRL_maskWrite,
        view32,
        &(bport1_ab_data.FLTCTRL.value),
        True
    );
    ppmCreateRegister("ab_QDCTRL",
        "Quadrature Decoder Control and Status, offset: 0x80 ",
        handles.bport1,
        128,
        4,
        read_32,
        bport1_ab_QDCTRL_maskWrite,
        view32,
        &(bport1_ab_data.QDCTRL.value),
        True
    );
    ppmCreateRegister("ab_CONF",
        "Configuration, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        read_32,
        bport1_ab_CONF_maskWrite,
        view32,
        &(bport1_ab_data.CONF.value),
        True
    );
    ppmCreateRegister("ab_FLTPOL",
        "FTM Fault Input Polarity, offset: 0x88 ",
        handles.bport1,
        136,
        4,
        read_32,
        bport1_ab_FLTPOL_maskWrite,
        view32,
        &(bport1_ab_data.FLTPOL.value),
        True
    );
    ppmCreateRegister("ab_SYNCONF",
        "Synchronization Configuration, offset: 0x8C ",
        handles.bport1,
        140,
        4,
        read_32,
        bport1_ab_SYNCONF_maskWrite,
        view32,
        &(bport1_ab_data.SYNCONF.value),
        True
    );
    ppmCreateRegister("ab_INVCTRL",
        "FTM Inverting Control, offset: 0x90 ",
        handles.bport1,
        144,
        4,
        read_32,
        bport1_ab_INVCTRL_maskWrite,
        view32,
        &(bport1_ab_data.INVCTRL.value),
        True
    );
    ppmCreateRegister("ab_SWOCTRL",
        "FTM Software Output Control, offset: 0x94 ",
        handles.bport1,
        148,
        4,
        read_32,
        bport1_ab_SWOCTRL_maskWrite,
        view32,
        &(bport1_ab_data.SWOCTRL.value),
        True
    );
    ppmCreateRegister("ab_PWMLOAD",
        "FTM PWM Load, offset: 0x98 ",
        handles.bport1,
        152,
        4,
        read_32,
        bport1_ab_PWMLOAD_maskWrite,
        view32,
        &(bport1_ab_data.PWMLOAD.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.PhaseA = ppmOpenNetPort("PhaseA");
    if (handles.PhaseA) {
        ppmInstallNetCallback(handles.PhaseA, phaseACB, (void*)0);
    }

    handles.PhaseB = ppmOpenNetPort("PhaseB");
    if (handles.PhaseB) {
        ppmInstallNetCallback(handles.PhaseB, phaseBCB, (void*)0);
    }

// To write to this net, use ppmWriteNet(handles.Interrupt, value);

    handles.Interrupt = ppmOpenNetPort("Interrupt");

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PWMLOAD.value = 0x0;
        bport1_ab_data.SWOCTRL.value = 0x0;
        bport1_ab_data.INVCTRL.value = 0x0;
        bport1_ab_data.SYNCONF.value = 0x0;
        bport1_ab_data.FLTPOL.value = 0x0;
        bport1_ab_data.CONF.value = 0x0;
        bport1_ab_data.QDCTRL.value = 0x0;
        bport1_ab_data.FLTCTRL.value = 0x0;
        bport1_ab_data.FILTER.value = 0x0;
        bport1_ab_data.FMS.value = 0x0;
        bport1_ab_data.POL.value = 0x0;
        bport1_ab_data.EXTTRIG.value = 0x0;
        bport1_ab_data.DEADTIME.value = 0x0;
        bport1_ab_data.COMBINE.value = 0x0;
        bport1_ab_data.OUTMASK.value = 0x0;
        bport1_ab_data.OUTINIT.value = 0x0;
        bport1_ab_data.SYNC.value = 0x0;
        bport1_ab_data.MODE.value = 0x4;
        bport1_ab_data.STATUS.value = 0x0;
        bport1_ab_data.CNTIN.value = 0x0;
        bport1_ab_data.C7V.value = 0x0;
        bport1_ab_data.C7SC.value = 0x0;
        bport1_ab_data.C6V.value = 0x0;
        bport1_ab_data.C6SC.value = 0x0;
        bport1_ab_data.C5V.value = 0x0;
        bport1_ab_data.C5SC.value = 0x0;
        bport1_ab_data.C4V.value = 0x0;
        bport1_ab_data.C4SC.value = 0x0;
        bport1_ab_data.C3V.value = 0x0;
        bport1_ab_data.C3SC.value = 0x0;
        bport1_ab_data.C2V.value = 0x0;
        bport1_ab_data.C2SC.value = 0x0;
        bport1_ab_data.C1V.value = 0x0;
        bport1_ab_data.C1SC.value = 0x0;
        bport1_ab_data.C0V.value = 0x0;
        bport1_ab_data.C0SC.value = 0x0;
        bport1_ab_data.MOD.value = 0x0;
        bport1_ab_data.CNT.value = 0x0;
        bport1_ab_data.SC.value = 0x0;
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

