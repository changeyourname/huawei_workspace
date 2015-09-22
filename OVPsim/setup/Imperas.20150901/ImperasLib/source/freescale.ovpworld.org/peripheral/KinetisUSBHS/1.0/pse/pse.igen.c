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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisUSBHS", "Example");
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

static PPM_WRITE_CB(bport1_ab_ASYNCLISTADDR_maskWrite) {
    bport1_ab_data.ASYNCLISTADDR.value = (bport1_ab_data.ASYNCLISTADDR.value & 0x1f) | (data & 0xffffffe0);
}

static PPM_WRITE_CB(bport1_ab_BURSTSIZE_maskWrite) {
    bport1_ab_data.BURSTSIZE.value = (bport1_ab_data.BURSTSIZE.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_DEVICEADDR_maskWrite) {
    bport1_ab_data.DEVICEADDR.value = (bport1_ab_data.DEVICEADDR.value & 0xfff) | (data & 0xfffff000);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAKEN_maskWrite) {
    bport1_ab_data.ENDPTNAKEN.value = (bport1_ab_data.ENDPTNAKEN.value & 0xfff0fff0) | (data & 0xf000f);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAK_maskWrite) {
    bport1_ab_data.ENDPTNAK.value = (bport1_ab_data.ENDPTNAK.value & 0xfff0fff0) | (data & 0xf000f);
}

static PPM_WRITE_CB(bport1_ab_EPCOMPLETE_maskWrite) {
    bport1_ab_data.EPCOMPLETE.value = (bport1_ab_data.EPCOMPLETE.value & 0xfff0fff0) | (data & 0xf000f);
}

static PPM_WRITE_CB(bport1_ab_EPCR0_maskWrite) {
    bport1_ab_data.EPCR0.value = (bport1_ab_data.EPCR0.value & 0xfffefffe) | (data & 0x10001);
}

static PPM_WRITE_CB(bport1_ab_EPCR1_maskWrite) {
    bport1_ab_data.EPCR1.value = (bport1_ab_data.EPCR1.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_EPCR2_maskWrite) {
    bport1_ab_data.EPCR2.value = (bport1_ab_data.EPCR2.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_EPCR3_maskWrite) {
    bport1_ab_data.EPCR3.value = (bport1_ab_data.EPCR3.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_EPFLUSH_maskWrite) {
    bport1_ab_data.EPFLUSH.value = (bport1_ab_data.EPFLUSH.value & 0xfff0fff0) | (data & 0xf000f);
}

static PPM_WRITE_CB(bport1_ab_EPPRIME_maskWrite) {
    bport1_ab_data.EPPRIME.value = (bport1_ab_data.EPPRIME.value & 0xfff0fff0) | (data & 0xf000f);
}

static PPM_WRITE_CB(bport1_ab_EPSETUPSR_maskWrite) {
    bport1_ab_data.EPSETUPSR.value = (bport1_ab_data.EPSETUPSR.value & 0xfffffff0) | (data & 0xf);
}

static PPM_WRITE_CB(bport1_ab_FRINDEX_maskWrite) {
    bport1_ab_data.FRINDEX.value = (bport1_ab_data.FRINDEX.value & 0xffffc000) | (data & 0x3fff);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0CTL_maskWrite) {
    bport1_ab_data.GPTIMER0CTL.value = (bport1_ab_data.GPTIMER0CTL.value & 0x3effffff) | (data & 0xc1000000);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0LD_maskWrite) {
    bport1_ab_data.GPTIMER0LD.value = (bport1_ab_data.GPTIMER0LD.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1CTL_maskWrite) {
    bport1_ab_data.GPTIMER1CTL.value = (bport1_ab_data.GPTIMER1CTL.value & 0x3effffff) | (data & 0xc1000000);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1LD_maskWrite) {
    bport1_ab_data.GPTIMER1LD.value = (bport1_ab_data.GPTIMER1LD.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_OTGSC_maskWrite) {
    bport1_ab_data.OTGSC.value = (bport1_ab_data.OTGSC.value & 0x8080ff40) | (data & 0x7f7f00bf);
}

static PPM_WRITE_CB(bport1_ab_PORTSC1_maskWrite) {
    bport1_ab_data.PORTSC1.value = (bport1_ab_data.PORTSC1.value & 0x3e000e11) | (data & 0xc1fff1ee);
}

static PPM_WRITE_CB(bport1_ab_SBUSCFG_maskWrite) {
    bport1_ab_data.SBUSCFG.value = (bport1_ab_data.SBUSCFG.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_TXFILLTUNING_maskWrite) {
    bport1_ab_data.TXFILLTUNING.value = (bport1_ab_data.TXFILLTUNING.value & 0xffc0e080) | (data & 0x3f1f7f);
}

static PPM_WRITE_CB(bport1_ab_ULPI_VIEWPORT_maskWrite) {
    bport1_ab_data.ULPI_VIEWPORT.value = (bport1_ab_data.ULPI_VIEWPORT.value & 0x1000ff00) | (data & 0xefff00ff);
}

static PPM_WRITE_CB(bport1_ab_USBCMD_maskWrite) {
    bport1_ab_data.USBCMD.value = (bport1_ab_data.USBCMD.value & 0xff001480) | (data & 0xffeb7f);
}

static PPM_WRITE_CB(bport1_ab_USBGENCTRL_maskWrite) {
    bport1_ab_data.USBGENCTRL.value = (bport1_ab_data.USBGENCTRL.value & 0xffffffdc) | (data & 0x23);
}

static PPM_WRITE_CB(bport1_ab_USBINTR_maskWrite) {
    bport1_ab_data.USBINTR.value = (bport1_ab_data.USBINTR.value & 0xfcf2fa00) | (data & 0x30d05ff);
}

static PPM_WRITE_CB(bport1_ab_USBMODE_maskWrite) {
    bport1_ab_data.USBMODE.value = (bport1_ab_data.USBMODE.value & 0xffff8fe0) | (data & 0x701f);
}

static PPM_WRITE_CB(bport1_ab_USBSTS_maskWrite) {
    bport1_ab_data.USBSTS.value = (bport1_ab_data.USBSTS.value & 0xfcf5fe00) | (data & 0x30a01ff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_ID",
        "Identification Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.ID.value),
        True
    );
    ppmCreateRegister("ab_HWGENERAL",
        "General Hardware Parameters Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HWGENERAL.value),
        True
    );
    ppmCreateRegister("ab_HWHOST",
        "Host Hardware Parameters Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HWHOST.value),
        True
    );
    ppmCreateRegister("ab_HWDEVICE",
        "Device Hardware Parameters Register, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HWDEVICE.value),
        True
    );
    ppmCreateRegister("ab_HWTXBUF",
        "Transmit Buffer Hardware Parameters Register, offset: 0x10 ",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HWTXBUF.value),
        True
    );
    ppmCreateRegister("ab_HWRXBUF",
        "Receive Buffer Hardware Parameters Register, offset: 0x14 ",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HWRXBUF.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER0LD",
        "General Purpose Timer n Load Register, offset: 0x80 ",
        handles.bport1,
        128,
        4,
        read_32,
        bport1_ab_GPTIMER0LD_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER0LD.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER0CTL",
        "General Purpose Timer n Control Register, offset: 0x84 ",
        handles.bport1,
        132,
        4,
        read_32,
        bport1_ab_GPTIMER0CTL_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER0CTL.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER1LD",
        "General Purpose Timer n Load Register, offset: 0x88 ",
        handles.bport1,
        136,
        4,
        read_32,
        bport1_ab_GPTIMER1LD_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER1LD.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER1CTL",
        "General Purpose Timer n Control Register, offset: 0x8C ",
        handles.bport1,
        140,
        4,
        read_32,
        bport1_ab_GPTIMER1CTL_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER1CTL.value),
        True
    );
    ppmCreateRegister("ab_SBUSCFG",
        "System Bus Interface Configuration Register, offset: 0x90 ",
        handles.bport1,
        144,
        4,
        read_32,
        bport1_ab_SBUSCFG_maskWrite,
        view32,
        &(bport1_ab_data.SBUSCFG.value),
        True
    );
    ppmCreateRegister("ab_HCIVERSION",
        "Host Controller Interface Version Register, offset: 0x100 ",
        handles.bport1,
        256,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HCIVERSION.value),
        True
    );
    ppmCreateRegister("ab_HCSPARAMS",
        "Host Controller Structural Parameters Register, offset: 0x104 ",
        handles.bport1,
        260,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HCSPARAMS.value),
        True
    );
    ppmCreateRegister("ab_HCCPARAMS",
        "Host Controller Capability Parameters Register, offset: 0x108 ",
        handles.bport1,
        264,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HCCPARAMS.value),
        True
    );
    ppmCreateRegister("ab_DCIVERSION",
        "Device Controller Interface Version, offset: 0x122, 16bit ",
        handles.bport1,
        288,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.DCIVERSION.value),
        True
    );
    ppmCreateRegister("ab_DCCPARAMS",
        "Device Controller Capability Parameters, offset: 0x124 ",
        handles.bport1,
        292,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.DCCPARAMS.value),
        True
    );
    ppmCreateRegister("ab_USBCMD",
        "USB Command Register, offset: 0x140 ",
        handles.bport1,
        320,
        4,
        read_32,
        bport1_ab_USBCMD_maskWrite,
        view32,
        &(bport1_ab_data.USBCMD.value),
        True
    );
    ppmCreateRegister("ab_USBSTS",
        "USB Status Register, offset: 0x144 ",
        handles.bport1,
        324,
        4,
        read_32,
        bport1_ab_USBSTS_maskWrite,
        view32,
        &(bport1_ab_data.USBSTS.value),
        True
    );
    ppmCreateRegister("ab_USBINTR",
        "USB Interrupt Enable Register, offset: 0x148 ",
        handles.bport1,
        328,
        4,
        read_32,
        bport1_ab_USBINTR_maskWrite,
        view32,
        &(bport1_ab_data.USBINTR.value),
        True
    );
    ppmCreateRegister("ab_FRINDEX",
        "Frame Index Register, offset: 0x14C ",
        handles.bport1,
        332,
        4,
        read_32,
        bport1_ab_FRINDEX_maskWrite,
        view32,
        &(bport1_ab_data.FRINDEX.value),
        True
    );
    ppmCreateRegister("ab_DEVICEADDR",
        "Device Address Register, offset: 0x154 ",
        handles.bport1,
        340,
        4,
        read_32,
        bport1_ab_DEVICEADDR_maskWrite,
        view32,
        &(bport1_ab_data.DEVICEADDR.value),
        True
    );
    ppmCreateRegister("ab_ASYNCLISTADDR",
        "Current Asynchronous List Address Register, offset: 0x158 ",
        handles.bport1,
        344,
        4,
        read_32,
        bport1_ab_ASYNCLISTADDR_maskWrite,
        view32,
        &(bport1_ab_data.ASYNCLISTADDR.value),
        True
    );
    ppmCreateRegister("ab_TTCTRL",
        "Host TT Asynchronous Buffer Control, offset: 0x15C ",
        handles.bport1,
        348,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.TTCTRL.value),
        True
    );
    ppmCreateRegister("ab_BURSTSIZE",
        "Master Interface Data Burst Size Register, offset: 0x160 ",
        handles.bport1,
        352,
        4,
        read_32,
        bport1_ab_BURSTSIZE_maskWrite,
        view32,
        &(bport1_ab_data.BURSTSIZE.value),
        True
    );
    ppmCreateRegister("ab_TXFILLTUNING",
        "Transmit FIFO Tuning Control Register, offset: 0x164 ",
        handles.bport1,
        356,
        4,
        read_32,
        bport1_ab_TXFILLTUNING_maskWrite,
        view32,
        &(bport1_ab_data.TXFILLTUNING.value),
        True
    );
    ppmCreateRegister("ab_ULPI_VIEWPORT",
        "ULPI Register Access, offset: 0x170 ",
        handles.bport1,
        368,
        4,
        read_32,
        bport1_ab_ULPI_VIEWPORT_maskWrite,
        view32,
        &(bport1_ab_data.ULPI_VIEWPORT.value),
        True
    );
    ppmCreateRegister("ab_ENDPTNAK",
        "ULPI Register Access, offset: 0x170 ",
        handles.bport1,
        376,
        4,
        read_32,
        bport1_ab_ENDPTNAK_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTNAK.value),
        True
    );
    ppmCreateRegister("ab_ENDPTNAKEN",
        "ULPI Register Access, offset: 0x170 ",
        handles.bport1,
        380,
        4,
        read_32,
        bport1_ab_ENDPTNAKEN_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTNAKEN.value),
        True
    );
    ppmCreateRegister("ab_CONFIGFLAG",
        "Configure Flag Register, offset: 0x180 ",
        handles.bport1,
        384,
        4,
        read_32,
        write_32,
        view32,
        &(bport1_ab_data.CONFIGFLAG.value),
        True
    );
    ppmCreateRegister("ab_PORTSC1",
        "Port Status and Control Registers, offset: 0x184 ",
        handles.bport1,
        388,
        4,
        read_32,
        bport1_ab_PORTSC1_maskWrite,
        view32,
        &(bport1_ab_data.PORTSC1.value),
        True
    );
    ppmCreateRegister("ab_OTGSC",
        "On-the-Go Status and Control Register, offset: 0x1A4 ",
        handles.bport1,
        420,
        4,
        read_32,
        bport1_ab_OTGSC_maskWrite,
        view32,
        &(bport1_ab_data.OTGSC.value),
        True
    );
    ppmCreateRegister("ab_USBMODE",
        "USB Mode Register, offset: 0x1A8 ",
        handles.bport1,
        424,
        4,
        read_32,
        bport1_ab_USBMODE_maskWrite,
        view32,
        &(bport1_ab_data.USBMODE.value),
        True
    );
    ppmCreateRegister("ab_EPSETUPSR",
        "Endpoint Setup Status Register, offset: 0x1AC ",
        handles.bport1,
        428,
        4,
        read_32,
        bport1_ab_EPSETUPSR_maskWrite,
        view32,
        &(bport1_ab_data.EPSETUPSR.value),
        True
    );
    ppmCreateRegister("ab_EPPRIME",
        "Endpoint Initialization Register, offset: 0x1B0 ",
        handles.bport1,
        432,
        4,
        read_32,
        bport1_ab_EPPRIME_maskWrite,
        view32,
        &(bport1_ab_data.EPPRIME.value),
        True
    );
    ppmCreateRegister("ab_EPFLUSH",
        "Endpoint Flush Register, offset: 0x1B4 ",
        handles.bport1,
        436,
        4,
        read_32,
        bport1_ab_EPFLUSH_maskWrite,
        view32,
        &(bport1_ab_data.EPFLUSH.value),
        True
    );
    ppmCreateRegister("ab_EPSR",
        "Endpoint Status Register, offset: 0x1B8 ",
        handles.bport1,
        440,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.EPSR.value),
        True
    );
    ppmCreateRegister("ab_EPCOMPLETE",
        "Endpoint Complete Register, offset: 0x1BC ",
        handles.bport1,
        444,
        4,
        read_32,
        bport1_ab_EPCOMPLETE_maskWrite,
        view32,
        &(bport1_ab_data.EPCOMPLETE.value),
        True
    );
    ppmCreateRegister("ab_EPCR0",
        "Endpoint Control Register 0, offset: 0x1C0 ",
        handles.bport1,
        448,
        4,
        read_32,
        bport1_ab_EPCR0_maskWrite,
        view32,
        &(bport1_ab_data.EPCR0.value),
        True
    );
    ppmCreateRegister("ab_EPCR1",
        "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 ",
        handles.bport1,
        452,
        4,
        read_32,
        bport1_ab_EPCR1_maskWrite,
        view32,
        &(bport1_ab_data.EPCR1.value),
        True
    );
    ppmCreateRegister("ab_EPCR2",
        "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 ",
        handles.bport1,
        456,
        4,
        read_32,
        bport1_ab_EPCR2_maskWrite,
        view32,
        &(bport1_ab_data.EPCR2.value),
        True
    );
    ppmCreateRegister("ab_EPCR3",
        "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 ",
        handles.bport1,
        460,
        4,
        read_32,
        bport1_ab_EPCR3_maskWrite,
        view32,
        &(bport1_ab_data.EPCR3.value),
        True
    );
    ppmCreateRegister("ab_USBGENCTRL",
        "General Control Regiser, offset: 0x20 ",
        handles.bport1,
        512,
        4,
        read_32,
        bport1_ab_USBGENCTRL_maskWrite,
        view32,
        &(bport1_ab_data.USBGENCTRL.value),
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
        bport1_ab_data.USBGENCTRL.value = 0x0;
        bport1_ab_data.EPCR3.value = 0x0;
        bport1_ab_data.EPCR2.value = 0x0;
        bport1_ab_data.EPCR1.value = 0x0;
        bport1_ab_data.EPCR0.value = 0x800080;
        bport1_ab_data.EPCOMPLETE.value = 0x0;
        bport1_ab_data.EPSR.value = 0x0;
        bport1_ab_data.EPFLUSH.value = 0x0;
        bport1_ab_data.EPPRIME.value = 0x0;
        bport1_ab_data.EPSETUPSR.value = 0x0;
        bport1_ab_data.USBMODE.value = 0x5000;
        bport1_ab_data.OTGSC.value = 0x1020;
        bport1_ab_data.PORTSC1.value = 0x80000000;
        bport1_ab_data.CONFIGFLAG.value = 0x1;
        bport1_ab_data.ENDPTNAKEN.value = 0x0;
        bport1_ab_data.ENDPTNAK.value = 0x0;
        bport1_ab_data.ULPI_VIEWPORT.value = 0x0;
        bport1_ab_data.TXFILLTUNING.value = 0x0;
        bport1_ab_data.BURSTSIZE.value = 0x8080;
        bport1_ab_data.TTCTRL.value = 0x0;
        bport1_ab_data.ASYNCLISTADDR.value = 0x0;
        bport1_ab_data.DEVICEADDR.value = 0x0;
        bport1_ab_data.FRINDEX.value = 0x0;
        bport1_ab_data.USBINTR.value = 0x0;
        bport1_ab_data.USBSTS.value = 0x0;
        bport1_ab_data.USBCMD.value = 0x80000;
        bport1_ab_data.DCCPARAMS.value = 0x184;
        bport1_ab_data.DCIVERSION.value = 0x1;
        bport1_ab_data.HCCPARAMS.value = 0x6;
        bport1_ab_data.HCSPARAMS.value = 0x10011;
        bport1_ab_data.HCIVERSION.value = 0x1000040;
        bport1_ab_data.SBUSCFG.value = 0x0;
        bport1_ab_data.GPTIMER1CTL.value = 0x0;
        bport1_ab_data.GPTIMER1LD.value = 0x0;
        bport1_ab_data.GPTIMER0CTL.value = 0x0;
        bport1_ab_data.GPTIMER0LD.value = 0x0;
        bport1_ab_data.HWRXBUF.value = 0x808;
        bport1_ab_data.HWTXBUF.value = 0x80070908;
        bport1_ab_data.HWDEVICE.value = 0x9;
        bport1_ab_data.HWHOST.value = 0x10020001;
        bport1_ab_data.HWGENERAL.value = 0x85;
        bport1_ab_data.ID.value = 0xe461fa05;
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

