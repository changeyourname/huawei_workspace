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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisUSB", "Example");
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

static PPM_WRITE_CB(bport1_ab_ADDR_maskWrite) {
    bport1_ab_data.ADDR.value = (bport1_ab_data.ADDR.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_BDTPAGE1_maskWrite) {
    bport1_ab_data.BDTPAGE1.value = (bport1_ab_data.BDTPAGE1.value & 0x1) | (data & 0xfe);
}

static PPM_WRITE_CB(bport1_ab_BDTPAGE2_maskWrite) {
    bport1_ab_data.BDTPAGE2.value = (bport1_ab_data.BDTPAGE2.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_BDTPAGE3_maskWrite) {
    bport1_ab_data.BDTPAGE3.value = (bport1_ab_data.BDTPAGE3.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CONTROL_maskWrite) {
    bport1_ab_data.CONTROL.value = (bport1_ab_data.CONTROL.value & 0xef) | (data & 0x10);
}

static PPM_WRITE_CB(bport1_ab_CTL_maskWrite) {
    bport1_ab_data.CTL.value = (bport1_ab_data.CTL.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT0_maskWrite) {
    bport1_ab_data.ENDPOINT0.value = (bport1_ab_data.ENDPOINT0.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT10_maskWrite) {
    bport1_ab_data.ENDPOINT10.value = (bport1_ab_data.ENDPOINT10.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT11_maskWrite) {
    bport1_ab_data.ENDPOINT11.value = (bport1_ab_data.ENDPOINT11.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT12_maskWrite) {
    bport1_ab_data.ENDPOINT12.value = (bport1_ab_data.ENDPOINT12.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT13_maskWrite) {
    bport1_ab_data.ENDPOINT13.value = (bport1_ab_data.ENDPOINT13.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT14_maskWrite) {
    bport1_ab_data.ENDPOINT14.value = (bport1_ab_data.ENDPOINT14.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT15_maskWrite) {
    bport1_ab_data.ENDPOINT15.value = (bport1_ab_data.ENDPOINT15.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT1_maskWrite) {
    bport1_ab_data.ENDPOINT1.value = (bport1_ab_data.ENDPOINT1.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT2_maskWrite) {
    bport1_ab_data.ENDPOINT2.value = (bport1_ab_data.ENDPOINT2.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT3_maskWrite) {
    bport1_ab_data.ENDPOINT3.value = (bport1_ab_data.ENDPOINT3.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT4_maskWrite) {
    bport1_ab_data.ENDPOINT4.value = (bport1_ab_data.ENDPOINT4.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT5_maskWrite) {
    bport1_ab_data.ENDPOINT5.value = (bport1_ab_data.ENDPOINT5.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT6_maskWrite) {
    bport1_ab_data.ENDPOINT6.value = (bport1_ab_data.ENDPOINT6.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT7_maskWrite) {
    bport1_ab_data.ENDPOINT7.value = (bport1_ab_data.ENDPOINT7.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT8_maskWrite) {
    bport1_ab_data.ENDPOINT8.value = (bport1_ab_data.ENDPOINT8.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT9_maskWrite) {
    bport1_ab_data.ENDPOINT9.value = (bport1_ab_data.ENDPOINT9.value & 0x20) | (data & 0xdf);
}

static PPM_WRITE_CB(bport1_ab_ERREN_maskWrite) {
    bport1_ab_data.ERREN.value = (bport1_ab_data.ERREN.value & 0x40) | (data & 0xbf);
}

static PPM_WRITE_CB(bport1_ab_ERRSTAT_maskWrite) {
    bport1_ab_data.ERRSTAT.value = (bport1_ab_data.ERRSTAT.value & 0x40) | (data & 0xbf);
}

static PPM_WRITE_CB(bport1_ab_FRMNUMH_maskWrite) {
    bport1_ab_data.FRMNUMH.value = (bport1_ab_data.FRMNUMH.value & 0xf8) | (data & 0x7);
}

static PPM_WRITE_CB(bport1_ab_FRMNUML_maskWrite) {
    bport1_ab_data.FRMNUML.value = (bport1_ab_data.FRMNUML.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_INTEN_maskWrite) {
    bport1_ab_data.INTEN.value = (bport1_ab_data.INTEN.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_ISTAT_maskWrite) {
    bport1_ab_data.ISTAT.value = (bport1_ab_data.ISTAT.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_OTGCTL_maskWrite) {
    bport1_ab_data.OTGCTL.value = (bport1_ab_data.OTGCTL.value & 0x4b) | (data & 0xb4);
}

static PPM_WRITE_CB(bport1_ab_OTGICR_maskWrite) {
    bport1_ab_data.OTGICR.value = (bport1_ab_data.OTGICR.value & 0x12) | (data & 0xed);
}

static PPM_WRITE_CB(bport1_ab_OTGISTAT_maskWrite) {
    bport1_ab_data.OTGISTAT.value = (bport1_ab_data.OTGISTAT.value & 0x12) | (data & 0xed);
}

static PPM_WRITE_CB(bport1_ab_OTGSTAT_maskWrite) {
    bport1_ab_data.OTGSTAT.value = (bport1_ab_data.OTGSTAT.value & 0x12) | (data & 0xed);
}

static PPM_WRITE_CB(bport1_ab_SOFTHLD_maskWrite) {
    bport1_ab_data.SOFTHLD.value = (bport1_ab_data.SOFTHLD.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_TOKEN_maskWrite) {
    bport1_ab_data.TOKEN.value = (bport1_ab_data.TOKEN.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_USBCTRL_maskWrite) {
    bport1_ab_data.USBCTRL.value = (bport1_ab_data.USBCTRL.value & 0x3f) | (data & 0xc0);
}

static PPM_WRITE_CB(bport1_ab_USBFRMADJUST_maskWrite) {
    bport1_ab_data.USBFRMADJUST.value = (bport1_ab_data.USBFRMADJUST.value & 0x0) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_USBTRC0_maskWrite) {
    bport1_ab_data.USBTRC0.value = (bport1_ab_data.USBTRC0.value & 0x5f) | (data & 0xa0);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_PERID",
        "Peripheral ID Register, offset: 0x0 ",
        handles.bport1,
        0,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.PERID.value),
        True
    );
    ppmCreateRegister("ab_IDCOMP",
        "Peripheral ID Complement Register, offset: 0x4 ",
        handles.bport1,
        4,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.IDCOMP.value),
        True
    );
    ppmCreateRegister("ab_REV",
        "Peripheral Revision Register, offset: 0x8 ",
        handles.bport1,
        8,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.REV.value),
        True
    );
    ppmCreateRegister("ab_ADDINFO",
        "Peripheral Additional Info Register, offset: 0xC ",
        handles.bport1,
        12,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.ADDINFO.value),
        True
    );
    ppmCreateRegister("ab_OTGISTAT",
        "OTG Interrupt Status Register, offset: 0x10 ",
        handles.bport1,
        16,
        1,
        read_8,
        bport1_ab_OTGISTAT_maskWrite,
        view8,
        &(bport1_ab_data.OTGISTAT.value),
        True
    );
    ppmCreateRegister("ab_OTGICR",
        "OTG Interrupt Control Register, offset: 0x14 ",
        handles.bport1,
        20,
        1,
        read_8,
        bport1_ab_OTGICR_maskWrite,
        view8,
        &(bport1_ab_data.OTGICR.value),
        True
    );
    ppmCreateRegister("ab_OTGSTAT",
        "OTG Status Register, offset: 0x18 ",
        handles.bport1,
        24,
        1,
        read_8,
        bport1_ab_OTGSTAT_maskWrite,
        view8,
        &(bport1_ab_data.OTGSTAT.value),
        True
    );
    ppmCreateRegister("ab_OTGCTL",
        "OTG Control Register, offset: 0x1C ",
        handles.bport1,
        28,
        1,
        read_8,
        bport1_ab_OTGCTL_maskWrite,
        view8,
        &(bport1_ab_data.OTGCTL.value),
        True
    );
    ppmCreateRegister("ab_ISTAT",
        "Interrupt Status Register, offset: 0x80 ",
        handles.bport1,
        128,
        1,
        read_8,
        bport1_ab_ISTAT_maskWrite,
        view8,
        &(bport1_ab_data.ISTAT.value),
        True
    );
    ppmCreateRegister("ab_INTEN",
        "Interrupt Enable Register, offset: 0x84 ",
        handles.bport1,
        132,
        1,
        read_8,
        bport1_ab_INTEN_maskWrite,
        view8,
        &(bport1_ab_data.INTEN.value),
        True
    );
    ppmCreateRegister("ab_ERRSTAT",
        "Error Interrupt Status Register, offset: 0x88 ",
        handles.bport1,
        136,
        1,
        read_8,
        bport1_ab_ERRSTAT_maskWrite,
        view8,
        &(bport1_ab_data.ERRSTAT.value),
        True
    );
    ppmCreateRegister("ab_ERREN",
        "Error Interrupt Enable Register, offset: 0x8C ",
        handles.bport1,
        140,
        1,
        read_8,
        bport1_ab_ERREN_maskWrite,
        view8,
        &(bport1_ab_data.ERREN.value),
        True
    );
    ppmCreateRegister("ab_STAT",
        "Status Register, offset: 0x90 ",
        handles.bport1,
        144,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.STAT.value),
        True
    );
    ppmCreateRegister("ab_CTL",
        "Control Register, offset: 0x94 ",
        handles.bport1,
        148,
        1,
        read_8,
        bport1_ab_CTL_maskWrite,
        view8,
        &(bport1_ab_data.CTL.value),
        True
    );
    ppmCreateRegister("ab_ADDR",
        "Address Register, offset: 0x98 ",
        handles.bport1,
        152,
        1,
        read_8,
        bport1_ab_ADDR_maskWrite,
        view8,
        &(bport1_ab_data.ADDR.value),
        True
    );
    ppmCreateRegister("ab_BDTPAGE1",
        "BDT Page Register 1, offset: 0x9C ",
        handles.bport1,
        156,
        1,
        read_8,
        bport1_ab_BDTPAGE1_maskWrite,
        view8,
        &(bport1_ab_data.BDTPAGE1.value),
        True
    );
    ppmCreateRegister("ab_FRMNUML",
        "Frame Number Register Low, offset: 0xA0 ",
        handles.bport1,
        160,
        1,
        read_8,
        bport1_ab_FRMNUML_maskWrite,
        view8,
        &(bport1_ab_data.FRMNUML.value),
        True
    );
    ppmCreateRegister("ab_FRMNUMH",
        "Frame Number Register High, offset: 0xA4 ",
        handles.bport1,
        164,
        1,
        read_8,
        bport1_ab_FRMNUMH_maskWrite,
        view8,
        &(bport1_ab_data.FRMNUMH.value),
        True
    );
    ppmCreateRegister("ab_TOKEN",
        "Token Register, offset: 0xA8 ",
        handles.bport1,
        168,
        1,
        read_8,
        bport1_ab_TOKEN_maskWrite,
        view8,
        &(bport1_ab_data.TOKEN.value),
        True
    );
    ppmCreateRegister("ab_SOFTHLD",
        "SOF Threshold Register, offset: 0xAC ",
        handles.bport1,
        172,
        1,
        read_8,
        bport1_ab_SOFTHLD_maskWrite,
        view8,
        &(bport1_ab_data.SOFTHLD.value),
        True
    );
    ppmCreateRegister("ab_BDTPAGE2",
        "BDT Page Register 2, offset: 0xB0 ",
        handles.bport1,
        176,
        1,
        read_8,
        bport1_ab_BDTPAGE2_maskWrite,
        view8,
        &(bport1_ab_data.BDTPAGE2.value),
        True
    );
    ppmCreateRegister("ab_BDTPAGE3",
        "BDT Page Register 3, offset: 0xB4 ",
        handles.bport1,
        180,
        1,
        read_8,
        bport1_ab_BDTPAGE3_maskWrite,
        view8,
        &(bport1_ab_data.BDTPAGE3.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT0",
        "Endpoint Control Register 0, offset 0xc0",
        handles.bport1,
        192,
        1,
        read_8,
        bport1_ab_ENDPOINT0_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT0.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT1",
        "Endpoint Control Register 1, offset 0xc4",
        handles.bport1,
        196,
        1,
        read_8,
        bport1_ab_ENDPOINT1_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT1.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT2",
        "Endpoint Control Register 2, offset 0xc8",
        handles.bport1,
        200,
        1,
        read_8,
        bport1_ab_ENDPOINT2_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT2.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT3",
        "Endpoint Control Register 3, offset 0xcc",
        handles.bport1,
        204,
        1,
        read_8,
        bport1_ab_ENDPOINT3_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT3.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT4",
        "Endpoint Control Register 4, offset 0xd0",
        handles.bport1,
        208,
        1,
        read_8,
        bport1_ab_ENDPOINT4_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT4.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT5",
        "Endpoint Control Register 5, offset 0xd4",
        handles.bport1,
        212,
        1,
        read_8,
        bport1_ab_ENDPOINT5_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT5.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT6",
        "Endpoint Control Register 6, offset 0xd8",
        handles.bport1,
        216,
        1,
        read_8,
        bport1_ab_ENDPOINT6_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT6.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT7",
        "Endpoint Control Register 7, offset 0xdc",
        handles.bport1,
        220,
        1,
        read_8,
        bport1_ab_ENDPOINT7_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT7.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT8",
        "Endpoint Control Register 8, offset 0xe0",
        handles.bport1,
        224,
        1,
        read_8,
        bport1_ab_ENDPOINT8_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT8.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT9",
        "Endpoint Control Register 9, offset 0xe4",
        handles.bport1,
        228,
        1,
        read_8,
        bport1_ab_ENDPOINT9_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT9.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT10",
        "Endpoint Control Register 10, offset 0xe8",
        handles.bport1,
        232,
        1,
        read_8,
        bport1_ab_ENDPOINT10_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT10.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT11",
        "Endpoint Control Register 11, offset 0xec",
        handles.bport1,
        236,
        1,
        read_8,
        bport1_ab_ENDPOINT11_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT11.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT12",
        "Endpoint Control Register 12, offset 0xf0",
        handles.bport1,
        240,
        1,
        read_8,
        bport1_ab_ENDPOINT12_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT12.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT13",
        "Endpoint Control Register 13, offset 0xf4",
        handles.bport1,
        244,
        1,
        read_8,
        bport1_ab_ENDPOINT13_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT13.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT14",
        "Endpoint Control Register 14, offset 0xf8",
        handles.bport1,
        248,
        1,
        read_8,
        bport1_ab_ENDPOINT14_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT14.value),
        True
    );
    ppmCreateRegister("ab_ENDPOINT15",
        "Endpoint Control Register 15, offset 0xfc",
        handles.bport1,
        252,
        1,
        read_8,
        bport1_ab_ENDPOINT15_maskWrite,
        view8,
        &(bport1_ab_data.ENDPOINT15.value),
        True
    );
    ppmCreateRegister("ab_USBCTRL",
        "USB Control Register, offset: 0x100 ",
        handles.bport1,
        256,
        1,
        read_8,
        bport1_ab_USBCTRL_maskWrite,
        view8,
        &(bport1_ab_data.USBCTRL.value),
        True
    );
    ppmCreateRegister("ab_OBSERVE",
        "USB OTG Observe Register, offset: 0x104 ",
        handles.bport1,
        260,
        1,
        read_8,
        0,
        view8,
        &(bport1_ab_data.OBSERVE.value),
        True
    );
    ppmCreateRegister("ab_CONTROL",
        "USB OTG Control Register, offset: 0x108 ",
        handles.bport1,
        264,
        1,
        read_8,
        bport1_ab_CONTROL_maskWrite,
        view8,
        &(bport1_ab_data.CONTROL.value),
        True
    );
    ppmCreateRegister("ab_USBTRC0",
        "USB Transceiver Control Register 0, offset: 0x10C ",
        handles.bport1,
        268,
        1,
        read_8,
        bport1_ab_USBTRC0_maskWrite,
        view8,
        &(bport1_ab_data.USBTRC0.value),
        True
    );
    ppmCreateRegister("ab_USBFRMADJUST",
        "Frame Adjust Register, offset: 0x114 ",
        handles.bport1,
        276,
        1,
        read_8,
        bport1_ab_USBFRMADJUST_maskWrite,
        view8,
        &(bport1_ab_data.USBFRMADJUST.value),
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
        bport1_ab_data.USBFRMADJUST.value = 0x0;
        bport1_ab_data.USBTRC0.value = 0x0;
        bport1_ab_data.CONTROL.value = 0x0;
        bport1_ab_data.OBSERVE.value = 0x50;
        bport1_ab_data.USBCTRL.value = 0xc0;
        bport1_ab_data.ENDPOINT15.value = 0x0;
        bport1_ab_data.ENDPOINT14.value = 0x0;
        bport1_ab_data.ENDPOINT13.value = 0x0;
        bport1_ab_data.ENDPOINT12.value = 0x0;
        bport1_ab_data.ENDPOINT11.value = 0x0;
        bport1_ab_data.ENDPOINT10.value = 0x0;
        bport1_ab_data.ENDPOINT9.value = 0x0;
        bport1_ab_data.ENDPOINT8.value = 0x0;
        bport1_ab_data.ENDPOINT7.value = 0x0;
        bport1_ab_data.ENDPOINT6.value = 0x0;
        bport1_ab_data.ENDPOINT5.value = 0x0;
        bport1_ab_data.ENDPOINT4.value = 0x0;
        bport1_ab_data.ENDPOINT3.value = 0x0;
        bport1_ab_data.ENDPOINT2.value = 0x0;
        bport1_ab_data.ENDPOINT1.value = 0x0;
        bport1_ab_data.ENDPOINT0.value = 0x0;
        bport1_ab_data.BDTPAGE3.value = 0x0;
        bport1_ab_data.BDTPAGE2.value = 0x0;
        bport1_ab_data.SOFTHLD.value = 0x0;
        bport1_ab_data.TOKEN.value = 0x0;
        bport1_ab_data.FRMNUMH.value = 0x0;
        bport1_ab_data.FRMNUML.value = 0x0;
        bport1_ab_data.BDTPAGE1.value = 0x0;
        bport1_ab_data.ADDR.value = 0x0;
        bport1_ab_data.CTL.value = 0x0;
        bport1_ab_data.STAT.value = 0x0;
        bport1_ab_data.ERREN.value = 0x0;
        bport1_ab_data.ERRSTAT.value = 0x0;
        bport1_ab_data.INTEN.value = 0x0;
        bport1_ab_data.ISTAT.value = 0x0;
        bport1_ab_data.OTGCTL.value = 0x0;
        bport1_ab_data.OTGSTAT.value = 0x0;
        bport1_ab_data.OTGICR.value = 0x0;
        bport1_ab_data.OTGISTAT.value = 0x0;
        bport1_ab_data.ADDINFO.value = 0x1;
        bport1_ab_data.REV.value = 0x33;
        bport1_ab_data.IDCOMP.value = 0xfb;
        bport1_ab_data.PERID.value = 0x4;
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

