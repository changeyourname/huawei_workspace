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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridUSB", "Example");
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

static PPM_WRITE_CB(bport1_ab_BURSTSIZE_maskWrite) {
    bport1_ab_data.BURSTSIZE.value = (bport1_ab_data.BURSTSIZE.value & 0xffffe000) | (data & 0x1fff);
}

static PPM_WRITE_CB(bport1_ab_CTRL_maskWrite) {
    bport1_ab_data.CTRL.value = (bport1_ab_data.CTRL.value & 0xfcfd007f) | (data & 0x302ff80);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCOMPLETE_maskWrite) {
    bport1_ab_data.ENDPTCOMPLETE.value = (bport1_ab_data.ENDPTCOMPLETE.value & 0xffc0ffc0) | (data & 0x3f003f);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL0_maskWrite) {
    bport1_ab_data.ENDPTCTRL0.value = (bport1_ab_data.ENDPTCTRL0.value & 0xff72ff72) | (data & 0x8d008d);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL1_maskWrite) {
    bport1_ab_data.ENDPTCTRL1.value = (bport1_ab_data.ENDPTCTRL1.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL2_maskWrite) {
    bport1_ab_data.ENDPTCTRL2.value = (bport1_ab_data.ENDPTCTRL2.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL3_maskWrite) {
    bport1_ab_data.ENDPTCTRL3.value = (bport1_ab_data.ENDPTCTRL3.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL4_maskWrite) {
    bport1_ab_data.ENDPTCTRL4.value = (bport1_ab_data.ENDPTCTRL4.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL5_maskWrite) {
    bport1_ab_data.ENDPTCTRL5.value = (bport1_ab_data.ENDPTCTRL5.value & 0xff10ff10) | (data & 0xef00ef);
}

static PPM_WRITE_CB(bport1_ab_ENDPTFLUSH_maskWrite) {
    bport1_ab_data.ENDPTFLUSH.value = (bport1_ab_data.ENDPTFLUSH.value & 0xffc0ffc0) | (data & 0x3f003f);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAKEN_maskWrite) {
    bport1_ab_data.ENDPTNAKEN.value = (bport1_ab_data.ENDPTNAKEN.value & 0xffc0ffc0) | (data & 0x3f003f);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAK_maskWrite) {
    bport1_ab_data.ENDPTNAK.value = (bport1_ab_data.ENDPTNAK.value & 0xffc0ffc0) | (data & 0x3f003f);
}

static PPM_WRITE_CB(bport1_ab_ENDPTPRIME_maskWrite) {
    bport1_ab_data.ENDPTPRIME.value = (bport1_ab_data.ENDPTPRIME.value & 0xffc0ffc0) | (data & 0x3f003f);
}

static PPM_WRITE_CB(bport1_ab_ENDPTSETUPSTAT_maskWrite) {
    bport1_ab_data.ENDPTSETUPSTAT.value = (bport1_ab_data.ENDPTSETUPSTAT.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_FRINDEX_maskWrite) {
    bport1_ab_data.FRINDEX.value = (bport1_ab_data.FRINDEX.value & 0xffffc000) | (data & 0x3fff);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0CTRL_maskWrite) {
    bport1_ab_data.GPTIMER0CTRL.value = (bport1_ab_data.GPTIMER0CTRL.value & 0x3e000000) | (data & 0xc1ffffff);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0LD_maskWrite) {
    bport1_ab_data.GPTIMER0LD.value = (bport1_ab_data.GPTIMER0LD.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1CTRL_maskWrite) {
    bport1_ab_data.GPTIMER1CTRL.value = (bport1_ab_data.GPTIMER1CTRL.value & 0x3e000000) | (data & 0xc1ffffff);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1LD_maskWrite) {
    bport1_ab_data.GPTIMER1LD.value = (bport1_ab_data.GPTIMER1LD.value & 0xff000000) | (data & 0xffffff);
}

static PPM_WRITE_CB(bport1_ab_OTGSC_maskWrite) {
    bport1_ab_data.OTGSC.value = (bport1_ab_data.OTGSC.value & 0x808080d6) | (data & 0x7f7f7f29);
}

static PPM_WRITE_CB(bport1_ab_PORTSC1_maskWrite) {
    bport1_ab_data.PORTSC1.value = (bport1_ab_data.PORTSC1.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_SBUSCFG_maskWrite) {
    bport1_ab_data.SBUSCFG.value = (bport1_ab_data.SBUSCFG.value & 0xfffffff8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_TXFILLTUNING_maskWrite) {
    bport1_ab_data.TXFILLTUNING.value = (bport1_ab_data.TXFILLTUNING.value & 0xffc0e000) | (data & 0x3f1fff);
}

static PPM_WRITE_CB(bport1_ab_USBCMD_maskWrite) {
    bport1_ab_data.USBCMD.value = (bport1_ab_data.USBCMD.value & 0xff001480) | (data & 0xffeb7f);
}

static PPM_WRITE_CB(bport1_ab_USBINTR_maskWrite) {
    bport1_ab_data.USBINTR.value = (bport1_ab_data.USBINTR.value & 0xfcf3fa00) | (data & 0x30c05ff);
}

static PPM_WRITE_CB(bport1_ab_USBMODE_maskWrite) {
    bport1_ab_data.USBMODE.value = (bport1_ab_data.USBMODE.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_USBSTS_maskWrite) {
    bport1_ab_data.USBSTS.value = (bport1_ab_data.USBSTS.value & 0xfcf30a00) | (data & 0x30cf5ff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_ID",
        "Identification register, offset: 0x0",
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
        "Hardware General, offset: 0x4",
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
        "Host Hardware Parameters, offset: 0x8",
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
        "Device Hardware Parameters, offset: 0xC",
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
        "TX Buffer Hardware Parameters, offset: 0x10",
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
        "RX Buffer Hardware Parameters, offset: 0x14",
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
        "General Purpose Timer #0 Load, offset: 0x80",
        handles.bport1,
        128,
        4,
        read_32,
        bport1_ab_GPTIMER0LD_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER0LD.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER0CTRL",
        "General Purpose Timer #0 Controller, offset: 0x84",
        handles.bport1,
        132,
        4,
        read_32,
        bport1_ab_GPTIMER0CTRL_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER0CTRL.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER1LD",
        "General Purpose Timer #1 Load, offset: 0x88",
        handles.bport1,
        136,
        4,
        read_32,
        bport1_ab_GPTIMER1LD_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER1LD.value),
        True
    );
    ppmCreateRegister("ab_GPTIMER1CTRL",
        "General Purpose Timer #1 Controller, offset: 0x8C",
        handles.bport1,
        140,
        4,
        read_32,
        bport1_ab_GPTIMER1CTRL_maskWrite,
        view32,
        &(bport1_ab_data.GPTIMER1CTRL.value),
        True
    );
    ppmCreateRegister("ab_SBUSCFG",
        "System Bus Config, offset: 0x90",
        handles.bport1,
        144,
        4,
        read_32,
        bport1_ab_SBUSCFG_maskWrite,
        view32,
        &(bport1_ab_data.SBUSCFG.value),
        True
    );
    ppmCreateRegister("ab_CAPVERSION",
        "Capability Register Length, offset: 0x100",
        handles.bport1,
        256,
        4,
        readCapVersion,
        0,
        view32,
        &(bport1_ab_data.CAPVERSION.value),
        True
    );
    ppmCreateRegister("ab_HCSPARAMS",
        "Host Controller Structural Parameters, offset: 0x104",
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
        "Host Controller Capability Parameters, offset: 0x108",
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
        "Device Controller Interface Version, offset: 0x120",
        handles.bport1,
        288,
        4,
        readDCIVersion,
        0,
        view32,
        &(bport1_ab_data.DCIVERSION.value),
        True
    );
    ppmCreateRegister("ab_DCCPARAMS",
        "Device Controller Capability Parameters, offset: 0x124",
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
        "USB Command Register, offset: 0x140",
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
        "USB Status Register, offset: 0x144",
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
        "Interrupt Enable Register, offset: 0x148",
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
        "USB Frame Index, offset: 0x14C",
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
        "Device_FrameList Base Address, offset: 0x154",
        handles.bport1,
        340,
        4,
        readShare154h,
        writeShare154h,
        view32,
        &(bport1_ab_data.DEVICEADDR.value),
        True
    );
    ppmCreateRegister("ab_ASYNCLISTADDR",
        "Next Asynch._Enpoint List Address, offset: 0x158",
        handles.bport1,
        344,
        4,
        readShare158h,
        writeShare154h,
        view32,
        &(bport1_ab_data.ASYNCLISTADDR.value),
        True
    );
    ppmCreateRegister("ab_BURSTSIZE",
        "Programmable Burst Size, offset: 0x160",
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
        "TX FIFO Fill Tuning, offset: 0x164",
        handles.bport1,
        356,
        4,
        read_32,
        bport1_ab_TXFILLTUNING_maskWrite,
        view32,
        &(bport1_ab_data.TXFILLTUNING.value),
        True
    );
    ppmCreateRegister("ab_ENDPTNAK",
        "Endpoint NAK, offset: 0x178",
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
        "Endpoint NAK Enable, offset: 0x17C",
        handles.bport1,
        380,
        4,
        read_32,
        bport1_ab_ENDPTNAKEN_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTNAKEN.value),
        True
    );
    ppmCreateRegister("ab_PORTSC1",
        "Port Status & Control, offset: 0x184",
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
        "On-The-Go Status & control, offset: 0x1A4",
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
        "USB Device Mode, offset: 0x1A8",
        handles.bport1,
        424,
        4,
        read_32,
        bport1_ab_USBMODE_maskWrite,
        view32,
        &(bport1_ab_data.USBMODE.value),
        True
    );
    ppmCreateRegister("ab_ENDPTSETUPSTAT",
        "Endpoint Setup Status, offset: 0x1AC",
        handles.bport1,
        428,
        4,
        read_32,
        bport1_ab_ENDPTSETUPSTAT_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTSETUPSTAT.value),
        True
    );
    ppmCreateRegister("ab_ENDPTPRIME",
        "Endpoint Initialization, offset: 0x1B0",
        handles.bport1,
        432,
        4,
        read_32,
        bport1_ab_ENDPTPRIME_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTPRIME.value),
        True
    );
    ppmCreateRegister("ab_ENDPTFLUSH",
        "Endpoint De-Initialize, offset: 0x1B4",
        handles.bport1,
        436,
        4,
        read_32,
        bport1_ab_ENDPTFLUSH_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTFLUSH.value),
        True
    );
    ppmCreateRegister("ab_ENDPTSTAT",
        "Endpoint Status, offset: 0x1B8",
        handles.bport1,
        440,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.ENDPTSTAT.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCOMPLETE",
        "Endpoint Complete, offset: 0x1BC",
        handles.bport1,
        444,
        4,
        read_32,
        bport1_ab_ENDPTCOMPLETE_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCOMPLETE.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCTRL0",
        "Endpoint Control0, offset: 0x1C0",
        handles.bport1,
        448,
        4,
        read_32,
        bport1_ab_ENDPTCTRL0_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCTRL0.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCTRL1",
        "Endpoint Control1, offset: 0x1C4",
        handles.bport1,
        452,
        4,
        read_32,
        bport1_ab_ENDPTCTRL1_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCTRL1.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCTRL2",
        "Endpoint Control2, offset: 0x1C8",
        handles.bport1,
        456,
        4,
        read_32,
        bport1_ab_ENDPTCTRL2_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCTRL2.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCTRL3",
        "Endpoint Control3, offset: 0x1Cc",
        handles.bport1,
        460,
        4,
        read_32,
        bport1_ab_ENDPTCTRL3_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCTRL3.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCTRL4",
        "Endpoint Control4, offset: 0x1d0",
        handles.bport1,
        464,
        4,
        read_32,
        bport1_ab_ENDPTCTRL4_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCTRL4.value),
        True
    );
    ppmCreateRegister("ab_ENDPTCTRL5",
        "Endpoint Control5, offset: 0x1d4",
        handles.bport1,
        468,
        4,
        read_32,
        bport1_ab_ENDPTCTRL5_maskWrite,
        view32,
        &(bport1_ab_data.ENDPTCTRL5.value),
        True
    );
    ppmCreateRegister("ab_CTRL",
        "Non-Core Register: USB Control Register",
        handles.bport1,
        2048,
        4,
        read_32,
        bport1_ab_CTRL_maskWrite,
        view32,
        &(bport1_ab_data.CTRL.value),
        True
    );
    ppmCreateRegister("ab_PHY",
        "Non-Core Register: USB PHY Control Register",
        handles.bport1,
        2072,
        4,
        read_32,
        PHYWrite1c,
        view32,
        &(bport1_ab_data.PHY.value),
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
        bport1_ab_data.PHY.value = 0x0;
        bport1_ab_data.CTRL.value = 0x3000;
        bport1_ab_data.ENDPTCTRL5.value = 0x0;
        bport1_ab_data.ENDPTCTRL4.value = 0x0;
        bport1_ab_data.ENDPTCTRL3.value = 0x0;
        bport1_ab_data.ENDPTCTRL2.value = 0x0;
        bport1_ab_data.ENDPTCTRL1.value = 0x0;
        bport1_ab_data.ENDPTCTRL0.value = 0x800080;
        bport1_ab_data.ENDPTCOMPLETE.value = 0x0;
        bport1_ab_data.ENDPTSTAT.value = 0x0;
        bport1_ab_data.ENDPTFLUSH.value = 0x0;
        bport1_ab_data.ENDPTPRIME.value = 0x0;
        bport1_ab_data.ENDPTSETUPSTAT.value = 0x0;
        bport1_ab_data.USBMODE.value = 0x5002;
        bport1_ab_data.OTGSC.value = 0x220;
        bport1_ab_data.PORTSC1.value = 0x10000000;
        bport1_ab_data.ENDPTNAKEN.value = 0x0;
        bport1_ab_data.ENDPTNAK.value = 0x0;
        bport1_ab_data.TXFILLTUNING.value = 0x808;
        bport1_ab_data.BURSTSIZE.value = 0x1010;
        bport1_ab_data.ASYNCLISTADDR.value = 0x0;
        bport1_ab_data.DEVICEADDR.value = 0x0;
        bport1_ab_data.FRINDEX.value = 0x0;
        bport1_ab_data.USBINTR.value = 0x0;
        bport1_ab_data.USBSTS.value = 0x0;
        bport1_ab_data.USBCMD.value = 0x80000;
        bport1_ab_data.DCCPARAMS.value = 0x186;
        bport1_ab_data.DCIVERSION.value = 0x1;
        bport1_ab_data.HCCPARAMS.value = 0x6;
        bport1_ab_data.HCSPARAMS.value = 0x10011;
        bport1_ab_data.CAPVERSION.value = 0x40;
        bport1_ab_data.SBUSCFG.value = 0x1;
        bport1_ab_data.GPTIMER1CTRL.value = 0x0;
        bport1_ab_data.GPTIMER1LD.value = 0x0;
        bport1_ab_data.GPTIMER0CTRL.value = 0x0;
        bport1_ab_data.GPTIMER0LD.value = 0x0;
        bport1_ab_data.HWRXBUF.value = 0x904;
        bport1_ab_data.HWTXBUF.value = 0x80080b04;
        bport1_ab_data.HWDEVICE.value = 0xd;
        bport1_ab_data.HWHOST.value = 0x10020001;
        bport1_ab_data.HWGENERAL.value = 0x15;
        bport1_ab_data.ID.value = 0xe481fa05;
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

