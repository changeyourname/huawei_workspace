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

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"
#include "dmacModel.h"

controlRegs control;
channelRegs ch[2];

Uns32 diag = 0;

//
// BusPort handles
//
ppmLocalBusHandle DMACSP_handle;

//
// netPort handles
//
ppmNetHandle INTR_handle;
ppmNetHandle INTTC_handle;
ppmNetHandle Reset_handle;

static void resetCB(Uns32 v, void *user) {
    if(v != 0) {
        userReset(v);
    }
}

static void createRegisters(void *w) {

    //                 name              description           base offset size read          write           view      user-data

    // common registers
    ppmCreateRegister("intStatus",      "internal status",       w, 0x00,  1, regRd8,          NULL,           viewReg8, &control.intStatus,      True);
    ppmCreateRegister("intTCstatus",    "internal TC status",    w, 0x04,  1, regRd8,          NULL,           viewReg8, &control.intTCstatus,    True);
    ppmCreateRegister("TCclear",        "clear TC status",       w, 0x08,  1, NULL,            TCclearWr,      NULL,     NULL,                    True);
    ppmCreateRegister("intErrStatus",   "internal error status", w, 0x0C,  1, regRd8,          NULL,           viewReg8, &control.errStatus,      True);
    ppmCreateRegister("clearErrStatus", "clear error status",    w, 0x10,  1, NULL,            errClearWr,     NULL,     NULL,                    True);
    ppmCreateRegister("rawTCstatus",    "raw TC status",         w, 0x14,  1, regRd8,          NULL,           viewReg8, &control.rawTCstatus,    True);
    ppmCreateRegister("rawErrStatus",   "raw error status",      w, 0x18,  1, regRd8,          NULL,           viewReg8, &control.rawErrorStatus, True);
    ppmCreateRegister("enbldChns",      "enabled channels",      w, 0x1C,  1, regRd8,          NULL,           viewReg8, &control.enbldChns,      True);
    ppmCreateRegister("config",         "configuration",         w, 0x30,  1, regRd8,          configWr,       viewReg8, &control.config.value,   True);

    // channel registers
    ppmCreateRegister("srcAddr0",        "source address ch0",   w, 0x100, 4, regRd32,         regWr32,       viewReg32, &ch[0].srcAddr,          True);
    ppmCreateRegister("dstAddr0",        "dest   address ch0",   w, 0x104, 4, regRd32,         regWr32,       viewReg32, &ch[0].dstAddr,          True);
    ppmCreateRegister("LLI0",            "LLI ch0",              w, 0x108, 4, regRd32,         regWr32,       viewReg32, &ch[0].LLI,              True);
    ppmCreateRegister("control0",        "control ch0",          w, 0x10C, 4, regRd32,         regWr32,       viewReg32, &ch[0].control.value,    True);
    ppmCreateRegister("config0",         "configuration ch0",    w, 0x110, 4, regRd32,         configCh0Wr,   viewReg32, &ch[0].config.value,     True);

    ppmCreateRegister("srcAddr1",        "source address ch1",   w, 0x120, 4, regRd32,         regWr32,       viewReg32, &ch[1].srcAddr,          True);
    ppmCreateRegister("dstAddr1",        "dest   address ch1",   w, 0x124, 4, regRd32,         regWr32,       viewReg32, &ch[1].dstAddr,          True);
    ppmCreateRegister("LLI1",            "LLI ch1",              w, 0x128, 4, regRd32,         regWr32,       viewReg32, &ch[1].LLI,              True);
    ppmCreateRegister("control1",        "control ch1",          w, 0x12C, 4, regRd32,         regWr32,       viewReg32, &ch[1].control.value,    True);
    ppmCreateRegister("config1",         "configuration ch1",    w, 0x130, 4, regRd32,         configCh1Wr,   viewReg32, &ch[1].config.value,     True);
}

//
// Connect bus ports
//
static void busPortConnections(void) {
    static unsigned char DMACSP_Window[0x140];

    DMACSP_handle = ppmOpenSlaveBusPort(
        "DMACSP",
        DMACSP_Window,
        sizeof(DMACSP_Window)
    );

    createRegisters(DMACSP_Window);
}

//
// Connect net ports
//
static void netPortConnections(void) {
    INTR_handle  = ppmOpenNetPort("INTR");
    INTTC_handle = ppmOpenNetPort("INTTC");
    Reset_handle = ppmOpenNetPort("RESET");
    if(Reset_handle) {
         ppmInstallNetCallback(Reset_handle, resetCB, 0);
    }
}

//
// Called when the diagnostic level is changed by the simulator
//
static void setDiagLevel(Uns32 new) {
    diag = new;
}

//
// Main for  DMAC
//
int main(int argc, char **argv) {
	// Model Documentation
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Basic DMA Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is a basic DMA engine example implementation, it does not conform to an actual device");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "This is not based upon a real device");
    }
    bhmInstallDiagCB(setDiagLevel);
    busPortConnections();
    netPortConnections();
    userInit();
    return 0;
}

