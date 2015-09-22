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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisWDOG", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_PRESC_maskWrite) {
    bport1_ab_data.PRESC.value = (bport1_ab_data.PRESC.value & 0xf8ff) | (data & 0x700);
}

static PPM_WRITE_CB(bport1_ab_REFRESH_maskWrite) {
    bport1_ab_data.REFRESH.value = (bport1_ab_data.REFRESH.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_RSTCNT_maskWrite) {
    bport1_ab_data.RSTCNT.value = (bport1_ab_data.RSTCNT.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_STCTRLH_maskWrite) {
    bport1_ab_data.STCTRLH.value = (bport1_ab_data.STCTRLH.value & 0x8300) | (data & 0x7cff);
}

static PPM_WRITE_CB(bport1_ab_STCTRLL_maskWrite) {
    bport1_ab_data.STCTRLL.value = (bport1_ab_data.STCTRLL.value & 0x7fff) | (data & 0x8000);
}

static PPM_WRITE_CB(bport1_ab_TMROUTH_maskWrite) {
    bport1_ab_data.TMROUTH.value = (bport1_ab_data.TMROUTH.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_TMROUTL_maskWrite) {
    bport1_ab_data.TMROUTL.value = (bport1_ab_data.TMROUTL.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_TOVALH_maskWrite) {
    bport1_ab_data.TOVALH.value = (bport1_ab_data.TOVALH.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_TOVALL_maskWrite) {
    bport1_ab_data.TOVALL.value = (bport1_ab_data.TOVALL.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_UNLOCK_maskWrite) {
    bport1_ab_data.UNLOCK.value = (bport1_ab_data.UNLOCK.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_WINH_maskWrite) {
    bport1_ab_data.WINH.value = (bport1_ab_data.WINH.value & 0x0) | (data & 0xffff);
}

static PPM_WRITE_CB(bport1_ab_WINL_maskWrite) {
    bport1_ab_data.WINL.value = (bport1_ab_data.WINL.value & 0x0) | (data & 0xffff);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_STCTRLH",
        "Watchdog Status and Control Register High, offset: 0x0 ",
        handles.bport1,
        0,
        2,
        read_16,
        bport1_ab_STCTRLH_maskWrite,
        view16,
        &(bport1_ab_data.STCTRLH.value),
        True
    );
    ppmCreateRegister("ab_STCTRLL",
        "Watchdog Status and Control Register Low, offset: 0x2 ",
        handles.bport1,
        2,
        2,
        read_16,
        bport1_ab_STCTRLL_maskWrite,
        view16,
        &(bport1_ab_data.STCTRLL.value),
        True
    );
    ppmCreateRegister("ab_TOVALH",
        "Watchdog Time-out Value Register High, offset: 0x4 ",
        handles.bport1,
        4,
        2,
        read_16,
        bport1_ab_TOVALH_maskWrite,
        view16,
        &(bport1_ab_data.TOVALH.value),
        True
    );
    ppmCreateRegister("ab_TOVALL",
        "Watchdog Time-out Value Register Low, offset: 0x6 ",
        handles.bport1,
        6,
        2,
        read_16,
        bport1_ab_TOVALL_maskWrite,
        view16,
        &(bport1_ab_data.TOVALL.value),
        True
    );
    ppmCreateRegister("ab_WINH",
        "Watchdog Window Register High, offset: 0x8 ",
        handles.bport1,
        8,
        2,
        read_16,
        bport1_ab_WINH_maskWrite,
        view16,
        &(bport1_ab_data.WINH.value),
        True
    );
    ppmCreateRegister("ab_WINL",
        "Watchdog Window Register Low, offset: 0xA ",
        handles.bport1,
        10,
        2,
        read_16,
        bport1_ab_WINL_maskWrite,
        view16,
        &(bport1_ab_data.WINL.value),
        True
    );
    ppmCreateRegister("ab_REFRESH",
        "Watchdog Refresh Register, offset: 0xC ",
        handles.bport1,
        12,
        2,
        read_16,
        bport1_ab_REFRESH_maskWrite,
        view16,
        &(bport1_ab_data.REFRESH.value),
        True
    );
    ppmCreateRegister("ab_UNLOCK",
        "Watchdog Unlock Register, offset: 0xE ",
        handles.bport1,
        14,
        2,
        read_16,
        bport1_ab_UNLOCK_maskWrite,
        view16,
        &(bport1_ab_data.UNLOCK.value),
        True
    );
    ppmCreateRegister("ab_TMROUTH",
        "Watchdog Timer Output Register High, offset: 0x10 ",
        handles.bport1,
        16,
        2,
        read_16,
        bport1_ab_TMROUTH_maskWrite,
        view16,
        &(bport1_ab_data.TMROUTH.value),
        True
    );
    ppmCreateRegister("ab_TMROUTL",
        "Watchdog Timer Output Register Low, offset: 0x12 ",
        handles.bport1,
        18,
        2,
        read_16,
        bport1_ab_TMROUTL_maskWrite,
        view16,
        &(bport1_ab_data.TMROUTL.value),
        True
    );
    ppmCreateRegister("ab_RSTCNT",
        "Watchdog Reset Count Register, offset: 0x14 ",
        handles.bport1,
        20,
        2,
        read_16,
        bport1_ab_RSTCNT_maskWrite,
        view16,
        &(bport1_ab_data.RSTCNT.value),
        True
    );
    ppmCreateRegister("ab_PRESC",
        "Watchdog Prescaler Register, offset: 0x16 ",
        handles.bport1,
        22,
        2,
        read_16,
        bport1_ab_PRESC_maskWrite,
        view16,
        &(bport1_ab_data.PRESC.value),
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
        bport1_ab_data.PRESC.value = 0x400;
        bport1_ab_data.RSTCNT.value = 0x0;
        bport1_ab_data.TMROUTL.value = 0x0;
        bport1_ab_data.TMROUTH.value = 0x0;
        bport1_ab_data.UNLOCK.value = 0x0;
        bport1_ab_data.REFRESH.value = 0xb480;
        bport1_ab_data.WINL.value = 0x10;
        bport1_ab_data.WINH.value = 0x0;
        bport1_ab_data.TOVALL.value = 0x4b4c;
        bport1_ab_data.TOVALH.value = 0x4c;
        bport1_ab_data.STCTRLL.value = 0x1;
        bport1_ab_data.STCTRLH.value = 0x1d3;
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

