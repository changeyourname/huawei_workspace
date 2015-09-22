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
//                          Thu Aug  7 11:47:03 2014
//
////////////////////////////////////////////////////////////////////////////////


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

sp1_ab1_dataT sp1_ab1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel > 0) bhmMessage("I", "Simple32", "Example");

Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp1 = ppmCreateSlaveBusPort("sp1", 16);
    if (!handles.sp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'sp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab1_r0",
        0,
        handles.sp1,
        0,
        4,
        read_32,
        0,
        view32,
        &(sp1_ab1_data.r0.value),
        True
    );
    ppmCreateRegister("ab1_r1",
        0,
        handles.sp1,
        4,
        4,
        read_32,
        0,
        view32,
        &(sp1_ab1_data.r1.value),
        True
    );
    ppmCreateRegister("ab1_r2",
        0,
        handles.sp1,
        8,
        4,
        read_32,
        0,
        view32,
        &(sp1_ab1_data.r2.value),
        True
    );
    ppmCreateRegister("ab1_r3",
        0,
        handles.sp1,
        12,
        4,
        read_32,
        0,
        view32,
        &(sp1_ab1_data.r3.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
    handles.reset = ppmOpenNetPort("reset");
    if (handles.reset) {
        ppmInstallNetCallback(handles.reset, reset, (void*)0);
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        sp1_ab1_data.r3.value = 0x31323334;
        sp1_ab1_data.r2.value = 0x21222324;
        sp1_ab1_data.r1.value = 0x11121314;
        sp1_ab1_data.r0.value = 0x1020304;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {
    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    init();

    return 0;
}

