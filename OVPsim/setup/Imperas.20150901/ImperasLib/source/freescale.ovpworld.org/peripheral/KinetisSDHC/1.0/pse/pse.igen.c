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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisSDHC", "Example");
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

static PPM_WRITE_CB(bport1_ab_ADSADDR_maskWrite) {
    bport1_ab_data.ADSADDR.value = (bport1_ab_data.ADSADDR.value & 0x3) | (data & 0xfffffffc);
}

static PPM_WRITE_CB(bport1_ab_BLKATTR_maskWrite) {
    bport1_ab_data.BLKATTR.value = (bport1_ab_data.BLKATTR.value & 0xe000) | (data & 0xffff1fff);
}

static PPM_WRITE_CB(bport1_ab_CMDARG_maskWrite) {
    bport1_ab_data.CMDARG.value = (bport1_ab_data.CMDARG.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DATPORT_maskWrite) {
    bport1_ab_data.DATPORT.value = (bport1_ab_data.DATPORT.value & 0x0) | (data & 0xffffffff);
}

static PPM_WRITE_CB(bport1_ab_DSADDR_maskWrite) {
    bport1_ab_data.DSADDR.value = (bport1_ab_data.DSADDR.value & 0x3) | (data & 0xfffffffc);
}

static PPM_WRITE_CB(bport1_ab_FEVT_maskWrite) {
    bport1_ab_data.FEVT.value = (bport1_ab_data.FEVT.value & 0x6e80ff60) | (data & 0x917f009f);
}

static PPM_WRITE_CB(bport1_ab_IRQSIGEN_maskWrite) {
    bport1_ab_data.IRQSIGEN.value = (bport1_ab_data.IRQSIGEN.value & 0xeec0fe00) | (data & 0x113f01ff);
}

static PPM_WRITE_CB(bport1_ab_IRQSTATEN_maskWrite) {
    bport1_ab_data.IRQSTATEN.value = (bport1_ab_data.IRQSTATEN.value & 0xeec0fe00) | (data & 0x113f01ff);
}

static PPM_WRITE_CB(bport1_ab_IRQSTAT_maskWrite) {
    bport1_ab_data.IRQSTAT.value = (bport1_ab_data.IRQSTAT.value & 0xeec0fe00) | (data & 0x113f01ff);
}

static PPM_WRITE_CB(bport1_ab_MMCBOOT_maskWrite) {
    bport1_ab_data.MMCBOOT.value = (bport1_ab_data.MMCBOOT.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_PROCTL_maskWrite) {
    bport1_ab_data.PROCTL.value = (bport1_ab_data.PROCTL.value & 0xf8f0fc00) | (data & 0x70f03ff);
}

static PPM_WRITE_CB(bport1_ab_SYSCTL_maskWrite) {
    bport1_ab_data.SYSCTL.value = (bport1_ab_data.SYSCTL.value & 0xf0f00000) | (data & 0xf0fffff);
}

static PPM_WRITE_CB(bport1_ab_VENDOR_maskWrite) {
    bport1_ab_data.VENDOR.value = (bport1_ab_data.VENDOR.value & 0xfffffffc) | (data & 0x3);
}

static PPM_WRITE_CB(bport1_ab_WML_maskWrite) {
    bport1_ab_data.WML.value = (bport1_ab_data.WML.value & 0xff00ff00) | (data & 0xff00ff);
}

static PPM_WRITE_CB(bport1_ab_XFERTYP_maskWrite) {
    bport1_ab_data.XFERTYP.value = (bport1_ab_data.XFERTYP.value & 0xc004ffc8) | (data & 0x3ffb0037);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_DSADDR",
        "DMA System Address Register, offset: 0x0 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_DSADDR_maskWrite,
        view32,
        &(bport1_ab_data.DSADDR.value),
        True
    );
    ppmCreateRegister("ab_BLKATTR",
        "Block Attributes Register, offset: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_BLKATTR_maskWrite,
        view32,
        &(bport1_ab_data.BLKATTR.value),
        True
    );
    ppmCreateRegister("ab_CMDARG",
        "Command Argument Register, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_CMDARG_maskWrite,
        view32,
        &(bport1_ab_data.CMDARG.value),
        True
    );
    ppmCreateRegister("ab_XFERTYP",
        "Transfer Type Register, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_XFERTYP_maskWrite,
        view32,
        &(bport1_ab_data.XFERTYP.value),
        True
    );
    ppmCreateRegister("ab_CMDRSP0",
        "Command Response 0, offset: 0x10, array step: 0x4 ",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CMDRSP0.value),
        True
    );
    ppmCreateRegister("ab_CMDRSP1",
        "Command Response 1, offset: 0x10, array step: 0x4 ",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CMDRSP1.value),
        True
    );
    ppmCreateRegister("ab_CMDRSP2",
        "Command Response 2, offset: 0x10, array step: 0x4 ",
        handles.bport1,
        24,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CMDRSP2.value),
        True
    );
    ppmCreateRegister("ab_CMDRSP3",
        "Command Response 3, offset: 0x10, array step: 0x4 ",
        handles.bport1,
        28,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.CMDRSP3.value),
        True
    );
    ppmCreateRegister("ab_DATPORT",
        "Buffer Data Port Register, offset: 0x20 ",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_DATPORT_maskWrite,
        view32,
        &(bport1_ab_data.DATPORT.value),
        True
    );
    ppmCreateRegister("ab_PRSSTAT",
        "Present State Register, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.PRSSTAT.value),
        True
    );
    ppmCreateRegister("ab_PROCTL",
        "Protocol Control Register, offset: 0x28 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_PROCTL_maskWrite,
        view32,
        &(bport1_ab_data.PROCTL.value),
        True
    );
    ppmCreateRegister("ab_SYSCTL",
        "System Control Register, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_SYSCTL_maskWrite,
        view32,
        &(bport1_ab_data.SYSCTL.value),
        True
    );
    ppmCreateRegister("ab_IRQSTAT",
        "Interrupt Status Register, offset: 0x30 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_IRQSTAT_maskWrite,
        view32,
        &(bport1_ab_data.IRQSTAT.value),
        True
    );
    ppmCreateRegister("ab_IRQSTATEN",
        "Interrupt Status Enable Register, offset: 0x34 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_IRQSTATEN_maskWrite,
        view32,
        &(bport1_ab_data.IRQSTATEN.value),
        True
    );
    ppmCreateRegister("ab_IRQSIGEN",
        "Interrupt Signal Enable Register, offset: 0x38 ",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_IRQSIGEN_maskWrite,
        view32,
        &(bport1_ab_data.IRQSIGEN.value),
        True
    );
    ppmCreateRegister("ab_AC12ERR",
        "Auto CMD12 Error Status Register, offset: 0x3C ",
        handles.bport1,
        60,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.AC12ERR.value),
        True
    );
    ppmCreateRegister("ab_HTCAPBLT",
        "Host Controller Capabilities, offset: 0x40 ",
        handles.bport1,
        64,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HTCAPBLT.value),
        True
    );
    ppmCreateRegister("ab_WML",
        "Watermark Level Register, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_WML_maskWrite,
        view32,
        &(bport1_ab_data.WML.value),
        True
    );
    ppmCreateRegister("ab_FEVT",
        "Force Event Register, offset: 0x50 ",
        handles.bport1,
        80,
        4,
        0,
        bport1_ab_FEVT_maskWrite,
        view32,
        &(bport1_ab_data.FEVT.value),
        True
    );
    ppmCreateRegister("ab_ADMAES",
        "ADMA Error Status Register, offset: 0x54 ",
        handles.bport1,
        84,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.ADMAES.value),
        True
    );
    ppmCreateRegister("ab_ADSADDR",
        "ADMA System Address Register, offset: 0x58 ",
        handles.bport1,
        88,
        4,
        read_32,
        bport1_ab_ADSADDR_maskWrite,
        view32,
        &(bport1_ab_data.ADSADDR.value),
        True
    );
    ppmCreateRegister("ab_VENDOR",
        "Vendor Specific Register, offset: 0xC0 ",
        handles.bport1,
        192,
        4,
        read_32,
        bport1_ab_VENDOR_maskWrite,
        view32,
        &(bport1_ab_data.VENDOR.value),
        True
    );
    ppmCreateRegister("ab_MMCBOOT",
        "MMC Boot Register, offset: 0xC4 ",
        handles.bport1,
        196,
        4,
        read_32,
        bport1_ab_MMCBOOT_maskWrite,
        view32,
        &(bport1_ab_data.MMCBOOT.value),
        True
    );
    ppmCreateRegister("ab_HOSTVER",
        "Host Controller Version, offset: 0xFC ",
        handles.bport1,
        252,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.HOSTVER.value),
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
        bport1_ab_data.HOSTVER.value = 0x1201;
        bport1_ab_data.MMCBOOT.value = 0x0;
        bport1_ab_data.VENDOR.value = 0x1;
        bport1_ab_data.ADSADDR.value = 0x0;
        bport1_ab_data.ADMAES.value = 0x0;
        bport1_ab_data.FEVT.value = 0x0;
        bport1_ab_data.WML.value = 0x100010;
        bport1_ab_data.HTCAPBLT.value = 0x7f30000;
        bport1_ab_data.AC12ERR.value = 0x0;
        bport1_ab_data.IRQSIGEN.value = 0x0;
        bport1_ab_data.IRQSTATEN.value = 0x117f013f;
        bport1_ab_data.IRQSTAT.value = 0x0;
        bport1_ab_data.SYSCTL.value = 0x8008;
        bport1_ab_data.PROCTL.value = 0x20;
        bport1_ab_data.PRSSTAT.value = 0x0;
        bport1_ab_data.DATPORT.value = 0x0;
        bport1_ab_data.CMDRSP3.value = 0x0;
        bport1_ab_data.CMDRSP2.value = 0x0;
        bport1_ab_data.CMDRSP1.value = 0x0;
        bport1_ab_data.CMDRSP0.value = 0x0;
        bport1_ab_data.XFERTYP.value = 0x0;
        bport1_ab_data.CMDARG.value = 0x0;
        bport1_ab_data.BLKATTR.value = 0x0;
        bport1_ab_data.DSADDR.value = 0x0;
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

