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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisADC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CFG1_maskWrite) {
    bport1_ab_data.CFG1.value = (bport1_ab_data.CFG1.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CFG2_maskWrite) {
    bport1_ab_data.CFG2.value = (bport1_ab_data.CFG2.value & 0xffffffe0) | (data & 0x1f);
}

static PPM_WRITE_CB(bport1_ab_CLM0_maskWrite) {
    bport1_ab_data.CLM0.value = (bport1_ab_data.CLM0.value & 0xffffffc0) | (data & 0x3f);
}

static PPM_WRITE_CB(bport1_ab_CLM1_maskWrite) {
    bport1_ab_data.CLM1.value = (bport1_ab_data.CLM1.value & 0xffffff80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_CLM2_maskWrite) {
    bport1_ab_data.CLM2.value = (bport1_ab_data.CLM2.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CLM3_maskWrite) {
    bport1_ab_data.CLM3.value = (bport1_ab_data.CLM3.value & 0xfffffe00) | (data & 0x1ff);
}

static PPM_WRITE_CB(bport1_ab_CLM4_maskWrite) {
    bport1_ab_data.CLM4.value = (bport1_ab_data.CLM4.value & 0xfffffc00) | (data & 0x3ff);
}

static PPM_WRITE_CB(bport1_ab_CLMD_maskWrite) {
    bport1_ab_data.CLMD.value = (bport1_ab_data.CLMD.value & 0xffffffc0) | (data & 0x3f);
}

static PPM_WRITE_CB(bport1_ab_CLMS_maskWrite) {
    bport1_ab_data.CLMS.value = (bport1_ab_data.CLMS.value & 0xffffffc0) | (data & 0x3f);
}

static PPM_WRITE_CB(bport1_ab_CLP0_maskWrite) {
    bport1_ab_data.CLP0.value = (bport1_ab_data.CLP0.value & 0xffffffc0) | (data & 0x3f);
}

static PPM_WRITE_CB(bport1_ab_CLP1_maskWrite) {
    bport1_ab_data.CLP1.value = (bport1_ab_data.CLP1.value & 0xffffff80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_CLP2_maskWrite) {
    bport1_ab_data.CLP2.value = (bport1_ab_data.CLP2.value & 0xffffff00) | (data & 0xff);
}

static PPM_WRITE_CB(bport1_ab_CLP3_maskWrite) {
    bport1_ab_data.CLP3.value = (bport1_ab_data.CLP3.value & 0xfffffe00) | (data & 0x1ff);
}

static PPM_WRITE_CB(bport1_ab_CLP4_maskWrite) {
    bport1_ab_data.CLP4.value = (bport1_ab_data.CLP4.value & 0xfffffc00) | (data & 0x3ff);
}

static PPM_WRITE_CB(bport1_ab_CLPD_maskWrite) {
    bport1_ab_data.CLPD.value = (bport1_ab_data.CLPD.value & 0xffffffc0) | (data & 0x3f);
}

static PPM_WRITE_CB(bport1_ab_CLPS_maskWrite) {
    bport1_ab_data.CLPS.value = (bport1_ab_data.CLPS.value & 0xffffffc0) | (data & 0x3f);
}

static PPM_WRITE_CB(bport1_ab_CV1_maskWrite) {
    bport1_ab_data.CV1.value = (bport1_ab_data.CV1.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_CV2_maskWrite) {
    bport1_ab_data.CV2.value = (bport1_ab_data.CV2.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_MG_maskWrite) {
    bport1_ab_data.MG.value = (bport1_ab_data.MG.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_OFS_maskWrite) {
    bport1_ab_data.OFS.value = (bport1_ab_data.OFS.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_PGA_maskWrite) {
    bport1_ab_data.PGA.value = (bport1_ab_data.PGA.value & 0xff40bfff) | (data & 0xbf4000);
}

static PPM_WRITE_CB(bport1_ab_PG_maskWrite) {
    bport1_ab_data.PG.value = (bport1_ab_data.PG.value & 0xffff0000) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_SC1A_maskWrite) {
    bport1_ab_data.SC1A.value = (bport1_ab_data.SC1A.value & 0xffffff80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_SC1B_maskWrite) {
    bport1_ab_data.SC1B.value = (bport1_ab_data.SC1B.value & 0xffffff80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_SC2_maskWrite) {
    bport1_ab_data.SC2.value = (bport1_ab_data.SC2.value & 0xffffff80) | (data & 0x7f);
}

static PPM_WRITE_CB(bport1_ab_SC3_maskWrite) {
    bport1_ab_data.SC3.value = (bport1_ab_data.SC3.value & 0xffffff70) | (data & 0x8f);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_SC1A",
        "ADC status and control registers 1, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        0,
        4,
        read_32,
        bport1_ab_SC1A_maskWrite,
        view32,
        &(bport1_ab_data.SC1A.value),
        True
    );
    ppmCreateRegister("ab_SC1B",
        "ADC status and control registers 1, array offset: 0x0, array step: 0x4 ",
        handles.bport1,
        4,
        4,
        read_32,
        bport1_ab_SC1B_maskWrite,
        view32,
        &(bport1_ab_data.SC1B.value),
        True
    );
    ppmCreateRegister("ab_CFG1",
        "ADC configuration register 1, offset: 0x8 ",
        handles.bport1,
        8,
        4,
        read_32,
        bport1_ab_CFG1_maskWrite,
        view32,
        &(bport1_ab_data.CFG1.value),
        True
    );
    ppmCreateRegister("ab_CFG2",
        "Configuration register 2, offset: 0xC ",
        handles.bport1,
        12,
        4,
        read_32,
        bport1_ab_CFG2_maskWrite,
        view32,
        &(bport1_ab_data.CFG2.value),
        True
    );
    ppmCreateRegister("ab_RA",
        "ADC data result register, array offset: 0x10, array step: 0x4 ",
        handles.bport1,
        16,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RA.value),
        True
    );
    ppmCreateRegister("ab_RB",
        "ADC data result register, array offset: 0x10, array step: 0x4 ",
        handles.bport1,
        20,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.RB.value),
        True
    );
    ppmCreateRegister("ab_CV1",
        "Compare value registers, offset: 0x18 ",
        handles.bport1,
        24,
        4,
        read_32,
        bport1_ab_CV1_maskWrite,
        view32,
        &(bport1_ab_data.CV1.value),
        True
    );
    ppmCreateRegister("ab_CV2",
        "Compare value registers, offset: 0x1C ",
        handles.bport1,
        28,
        4,
        read_32,
        bport1_ab_CV2_maskWrite,
        view32,
        &(bport1_ab_data.CV2.value),
        True
    );
    ppmCreateRegister("ab_SC2",
        "Status and control register 2, offset: 0x20 ",
        handles.bport1,
        32,
        4,
        read_32,
        bport1_ab_SC2_maskWrite,
        view32,
        &(bport1_ab_data.SC2.value),
        True
    );
    ppmCreateRegister("ab_SC3",
        "Status and control register 3, offset: 0x24 ",
        handles.bport1,
        36,
        4,
        read_32,
        bport1_ab_SC3_maskWrite,
        view32,
        &(bport1_ab_data.SC3.value),
        True
    );
    ppmCreateRegister("ab_OFS",
        "ADC offset correction register, offset: 0x28 ",
        handles.bport1,
        40,
        4,
        read_32,
        bport1_ab_OFS_maskWrite,
        view32,
        &(bport1_ab_data.OFS.value),
        True
    );
    ppmCreateRegister("ab_PG",
        "ADC plus-side gain register, offset: 0x2C ",
        handles.bport1,
        44,
        4,
        read_32,
        bport1_ab_PG_maskWrite,
        view32,
        &(bport1_ab_data.PG.value),
        True
    );
    ppmCreateRegister("ab_MG",
        "ADC minus-side gain register, offset: 0x30 ",
        handles.bport1,
        48,
        4,
        read_32,
        bport1_ab_MG_maskWrite,
        view32,
        &(bport1_ab_data.MG.value),
        True
    );
    ppmCreateRegister("ab_CLPD",
        "ADC plus-side general calibration value register, offset: 0x34 ",
        handles.bport1,
        52,
        4,
        read_32,
        bport1_ab_CLPD_maskWrite,
        view32,
        &(bport1_ab_data.CLPD.value),
        True
    );
    ppmCreateRegister("ab_CLPS",
        "ADC plus-side general calibration value register, offset: 0x38 ",
        handles.bport1,
        56,
        4,
        read_32,
        bport1_ab_CLPS_maskWrite,
        view32,
        &(bport1_ab_data.CLPS.value),
        True
    );
    ppmCreateRegister("ab_CLP4",
        "ADC plus-side general calibration value register, offset: 0x3C ",
        handles.bport1,
        60,
        4,
        read_32,
        bport1_ab_CLP4_maskWrite,
        view32,
        &(bport1_ab_data.CLP4.value),
        True
    );
    ppmCreateRegister("ab_CLP3",
        "ADC plus-side general calibration value register, offset: 0x40 ",
        handles.bport1,
        64,
        4,
        read_32,
        bport1_ab_CLP3_maskWrite,
        view32,
        &(bport1_ab_data.CLP3.value),
        True
    );
    ppmCreateRegister("ab_CLP2",
        "ADC plus-side general calibration value register, offset: 0x44 ",
        handles.bport1,
        68,
        4,
        read_32,
        bport1_ab_CLP2_maskWrite,
        view32,
        &(bport1_ab_data.CLP2.value),
        True
    );
    ppmCreateRegister("ab_CLP1",
        "ADC plus-side general calibration value register, offset: 0x48 ",
        handles.bport1,
        72,
        4,
        read_32,
        bport1_ab_CLP1_maskWrite,
        view32,
        &(bport1_ab_data.CLP1.value),
        True
    );
    ppmCreateRegister("ab_CLP0",
        "ADC plus-side general calibration value register, offset: 0x4C ",
        handles.bport1,
        76,
        4,
        read_32,
        bport1_ab_CLP0_maskWrite,
        view32,
        &(bport1_ab_data.CLP0.value),
        True
    );
    ppmCreateRegister("ab_PGA",
        "ADC PGA register, offset: 0x50 ",
        handles.bport1,
        80,
        4,
        read_32,
        bport1_ab_PGA_maskWrite,
        view32,
        &(bport1_ab_data.PGA.value),
        True
    );
    ppmCreateRegister("ab_CLMD",
        "ADC minus-side general calibration value register, offset: 0x54 ",
        handles.bport1,
        84,
        4,
        read_32,
        bport1_ab_CLMD_maskWrite,
        view32,
        &(bport1_ab_data.CLMD.value),
        True
    );
    ppmCreateRegister("ab_CLMS",
        "ADC minus-side general calibration value register, offset: 0x58 ",
        handles.bport1,
        88,
        4,
        read_32,
        bport1_ab_CLMS_maskWrite,
        view32,
        &(bport1_ab_data.CLMS.value),
        True
    );
    ppmCreateRegister("ab_CLM4",
        "ADC minus-side general calibration value register, offset: 0x5C ",
        handles.bport1,
        92,
        4,
        read_32,
        bport1_ab_CLM4_maskWrite,
        view32,
        &(bport1_ab_data.CLM4.value),
        True
    );
    ppmCreateRegister("ab_CLM3",
        "ADC minus-side general calibration value register, offset: 0x60 ",
        handles.bport1,
        96,
        4,
        read_32,
        bport1_ab_CLM3_maskWrite,
        view32,
        &(bport1_ab_data.CLM3.value),
        True
    );
    ppmCreateRegister("ab_CLM2",
        "ADC minus-side general calibration value register, offset: 0x64 ",
        handles.bport1,
        100,
        4,
        read_32,
        bport1_ab_CLM2_maskWrite,
        view32,
        &(bport1_ab_data.CLM2.value),
        True
    );
    ppmCreateRegister("ab_CLM1",
        "ADC minus-side general calibration value register, offset: 0x68 ",
        handles.bport1,
        104,
        4,
        read_32,
        bport1_ab_CLM1_maskWrite,
        view32,
        &(bport1_ab_data.CLM1.value),
        True
    );
    ppmCreateRegister("ab_CLM0",
        "ADC minus-side general calibration value register, offset: 0x6C ",
        handles.bport1,
        108,
        4,
        read_32,
        bport1_ab_CLM0_maskWrite,
        view32,
        &(bport1_ab_data.CLM0.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.Reset = ppmOpenNetPort("Reset");
    if (handles.Reset) {
        ppmInstallNetCallback(handles.Reset, reset_Reset, (void*)0);
    }

    handles.AltClk = ppmOpenNetPort("AltClk");
    if (handles.AltClk) {
        ppmInstallNetCallback(handles.AltClk, altClkCB, (void*)0);
    }

    handles.HwTrig = ppmOpenNetPort("HwTrig");
    if (handles.HwTrig) {
        ppmInstallNetCallback(handles.HwTrig, hwTrigCB, (void*)0);
    }

    handles.AdIn = ppmOpenNetPort("AdIn");

    handles.Vrefsh = ppmOpenNetPort("Vrefsh");

    handles.Vrefsl = ppmOpenNetPort("Vrefsl");

// To write to this net, use ppmWriteNet(handles.AdInId, value);

    handles.AdInId = ppmOpenNetPort("AdInId");

// To write to this net, use ppmWriteNet(handles.Interrupt, value);

    handles.Interrupt = ppmOpenNetPort("Interrupt");

// To write to this net, use ppmWriteNet(handles.DmaReq, value);

    handles.DmaReq = ppmOpenNetPort("DmaReq");

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CLM0.value = 0x20;
        bport1_ab_data.CLM1.value = 0x40;
        bport1_ab_data.CLM2.value = 0x80;
        bport1_ab_data.CLM3.value = 0x100;
        bport1_ab_data.CLM4.value = 0x200;
        bport1_ab_data.CLMS.value = 0x20;
        bport1_ab_data.CLMD.value = 0xa;
        bport1_ab_data.PGA.value = 0x0;
        bport1_ab_data.CLP0.value = 0x20;
        bport1_ab_data.CLP1.value = 0x40;
        bport1_ab_data.CLP2.value = 0x80;
        bport1_ab_data.CLP3.value = 0x100;
        bport1_ab_data.CLP4.value = 0x200;
        bport1_ab_data.CLPS.value = 0x20;
        bport1_ab_data.CLPD.value = 0xa;
        bport1_ab_data.MG.value = 0x8200;
        bport1_ab_data.PG.value = 0x8200;
        bport1_ab_data.OFS.value = 0x4;
        bport1_ab_data.SC3.value = 0x0;
        bport1_ab_data.SC2.value = 0x0;
        bport1_ab_data.CV2.value = 0x0;
        bport1_ab_data.CV1.value = 0x0;
        bport1_ab_data.RB.value = 0x0;
        bport1_ab_data.RA.value = 0x0;
        bport1_ab_data.CFG2.value = 0x0;
        bport1_ab_data.CFG1.value = 0x0;
        bport1_ab_data.SC1B.value = 0x1f;
        bport1_ab_data.SC1A.value = 0x1f;
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

