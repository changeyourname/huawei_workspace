/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                              Version 99999999
//                          Thu Aug  7 11:47:10 2014
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////// Description /////////////////////////////////

// DMAC peripheral model


#include "dmac.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

DMACSP_ab8_dataT DMACSP_ab8_data;

DMACSP_ab32ch0_dataT DMACSP_ab32ch0_data;

DMACSP_ab32ch1_dataT DMACSP_ab32ch1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel > 0) bhmMessage("I", "dmac", "Example");

Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.DMACSP = ppmCreateSlaveBusPort("DMACSP", 320);
    if (!handles.DMACSP) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'DMACSP'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab8_intStatus",
        "internal status",
        handles.DMACSP,
        0,
        1,
        regRd8,
        0,
        view8,
        &(DMACSP_ab8_data.intStatus.value),
        True
    );
    ppmCreateRegister("ab8_intTCstatus",
        "internal TC status",
        handles.DMACSP,
        4,
        1,
        regRd8,
        TCclearWr,
        view8,
        &(DMACSP_ab8_data.intTCstatus.value),
        True
    );
    ppmCreateRegister("ab8_intErrStatus",
        "internal error status",
        handles.DMACSP,
        12,
        1,
        regRd8,
        errClearWr,
        view8,
        &(DMACSP_ab8_data.intErrStatus.value),
        True
    );
    ppmCreateRegister("ab8_rawTCstatus",
        "raw TC status",
        handles.DMACSP,
        20,
        1,
        regRd8,
        0,
        view8,
        &(DMACSP_ab8_data.rawTCstatus.value),
        True
    );
    ppmCreateRegister("ab8_rawErrStatus",
        "raw error status",
        handles.DMACSP,
        24,
        1,
        regRd8,
        0,
        view8,
        &(DMACSP_ab8_data.rawErrStatus.value),
        True
    );
    ppmCreateRegister("ab8_enbldChns",
        "enabled channels",
        handles.DMACSP,
        28,
        1,
        regRd8,
        0,
        view8,
        &(DMACSP_ab8_data.enbldChns.value),
        True
    );
    ppmCreateRegister("ab8_config",
        "configuration",
        handles.DMACSP,
        48,
        1,
        regRd8,
        configWr,
        view8,
        &(DMACSP_ab8_data.config.value),
        True
    );
    ppmCreateRegister("ab32ch0_srcAddr",
        "channel 0 source address",
        handles.DMACSP,
        256,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch0_data.srcAddr.value),
        True
    );
    ppmCreateRegister("ab32ch0_dstAddr",
        "channel 0 dest address",
        handles.DMACSP,
        260,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch0_data.dstAddr.value),
        True
    );
    ppmCreateRegister("ab32ch0_LLI",
        "channel 0 LLI",
        handles.DMACSP,
        264,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch0_data.LLI.value),
        True
    );
    ppmCreateRegister("ab32ch0_control",
        "channel 0 control",
        handles.DMACSP,
        268,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch0_data.control.value),
        True
    );
    ppmCreateRegister("ab32ch0_config",
        "channel 0 configuration",
        handles.DMACSP,
        272,
        4,
        regRd32,
        configCh0Wr,
        view32,
        &(DMACSP_ab32ch0_data.config.value),
        True
    );
    ppmCreateRegister("ab32ch1_srcAddr",
        "channel 1 source address",
        handles.DMACSP,
        288,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch1_data.srcAddr.value),
        True
    );
    ppmCreateRegister("ab32ch1_dstAddr",
        "channel 1 dest address",
        handles.DMACSP,
        292,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch1_data.dstAddr.value),
        True
    );
    ppmCreateRegister("ab32ch1_LLI",
        "channel 1 LLI",
        handles.DMACSP,
        296,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch1_data.LLI.value),
        True
    );
    ppmCreateRegister("ab32ch1_control",
        "channel 1 control",
        handles.DMACSP,
        300,
        4,
        regRd32,
        regWr32,
        view32,
        &(DMACSP_ab32ch1_data.control.value),
        True
    );
    ppmCreateRegister("ab32ch1_config",
        "channel 1 configuration",
        handles.DMACSP,
        304,
        4,
        regRd32,
        configCh1Wr,
        view32,
        &(DMACSP_ab32ch1_data.config.value),
        True
    );

}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {
    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

