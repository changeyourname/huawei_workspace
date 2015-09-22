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

bp1_REG_dataT bp1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "AdvancedInterruptController", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
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
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 4096);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("REG_AIC_SMR0",
        0,
        handles.bp1,
        0,
        4,
        read_32,
        AIC_SMR_wcb0,
        view32,
        &(bp1_REG_data.AIC_SMR0.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR1",
        0,
        handles.bp1,
        4,
        4,
        read_32,
        AIC_SMR_wcb1,
        view32,
        &(bp1_REG_data.AIC_SMR1.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR2",
        0,
        handles.bp1,
        8,
        4,
        read_32,
        AIC_SMR_wcb2,
        view32,
        &(bp1_REG_data.AIC_SMR2.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR3",
        0,
        handles.bp1,
        12,
        4,
        read_32,
        AIC_SMR_wcb3,
        view32,
        &(bp1_REG_data.AIC_SMR3.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR4",
        0,
        handles.bp1,
        16,
        4,
        read_32,
        AIC_SMR_wcb4,
        view32,
        &(bp1_REG_data.AIC_SMR4.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR5",
        0,
        handles.bp1,
        20,
        4,
        read_32,
        AIC_SMR_wcb5,
        view32,
        &(bp1_REG_data.AIC_SMR5.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR6",
        0,
        handles.bp1,
        24,
        4,
        read_32,
        AIC_SMR_wcb6,
        view32,
        &(bp1_REG_data.AIC_SMR6.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR7",
        0,
        handles.bp1,
        28,
        4,
        read_32,
        AIC_SMR_wcb7,
        view32,
        &(bp1_REG_data.AIC_SMR7.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR8",
        0,
        handles.bp1,
        32,
        4,
        read_32,
        AIC_SMR_wcb8,
        view32,
        &(bp1_REG_data.AIC_SMR8.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR9",
        0,
        handles.bp1,
        36,
        4,
        read_32,
        AIC_SMR_wcb9,
        view32,
        &(bp1_REG_data.AIC_SMR9.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR10",
        0,
        handles.bp1,
        40,
        4,
        read_32,
        AIC_SMR_wcb10,
        view32,
        &(bp1_REG_data.AIC_SMR10.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR11",
        0,
        handles.bp1,
        44,
        4,
        read_32,
        AIC_SMR_wcb11,
        view32,
        &(bp1_REG_data.AIC_SMR11.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR12",
        0,
        handles.bp1,
        48,
        4,
        read_32,
        AIC_SMR_wcb12,
        view32,
        &(bp1_REG_data.AIC_SMR12.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR13",
        0,
        handles.bp1,
        52,
        4,
        read_32,
        AIC_SMR_wcb13,
        view32,
        &(bp1_REG_data.AIC_SMR13.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR14",
        0,
        handles.bp1,
        56,
        4,
        read_32,
        AIC_SMR_wcb14,
        view32,
        &(bp1_REG_data.AIC_SMR14.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR15",
        0,
        handles.bp1,
        60,
        4,
        read_32,
        AIC_SMR_wcb15,
        view32,
        &(bp1_REG_data.AIC_SMR15.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR16",
        0,
        handles.bp1,
        64,
        4,
        read_32,
        AIC_SMR_wcb16,
        view32,
        &(bp1_REG_data.AIC_SMR16.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR17",
        0,
        handles.bp1,
        68,
        4,
        read_32,
        AIC_SMR_wcb17,
        view32,
        &(bp1_REG_data.AIC_SMR17.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR18",
        0,
        handles.bp1,
        72,
        4,
        read_32,
        AIC_SMR_wcb18,
        view32,
        &(bp1_REG_data.AIC_SMR18.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR19",
        0,
        handles.bp1,
        76,
        4,
        read_32,
        AIC_SMR_wcb19,
        view32,
        &(bp1_REG_data.AIC_SMR19.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR20",
        0,
        handles.bp1,
        80,
        4,
        read_32,
        AIC_SMR_wcb20,
        view32,
        &(bp1_REG_data.AIC_SMR20.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR21",
        0,
        handles.bp1,
        84,
        4,
        read_32,
        AIC_SMR_wcb21,
        view32,
        &(bp1_REG_data.AIC_SMR21.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR22",
        0,
        handles.bp1,
        88,
        4,
        read_32,
        AIC_SMR_wcb22,
        view32,
        &(bp1_REG_data.AIC_SMR22.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR23",
        0,
        handles.bp1,
        92,
        4,
        read_32,
        AIC_SMR_wcb23,
        view32,
        &(bp1_REG_data.AIC_SMR23.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR24",
        0,
        handles.bp1,
        96,
        4,
        read_32,
        AIC_SMR_wcb24,
        view32,
        &(bp1_REG_data.AIC_SMR24.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR25",
        0,
        handles.bp1,
        100,
        4,
        read_32,
        AIC_SMR_wcb25,
        view32,
        &(bp1_REG_data.AIC_SMR25.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR26",
        0,
        handles.bp1,
        104,
        4,
        read_32,
        AIC_SMR_wcb26,
        view32,
        &(bp1_REG_data.AIC_SMR26.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR27",
        0,
        handles.bp1,
        108,
        4,
        read_32,
        AIC_SMR_wcb27,
        view32,
        &(bp1_REG_data.AIC_SMR27.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR28",
        0,
        handles.bp1,
        112,
        4,
        read_32,
        AIC_SMR_wcb28,
        view32,
        &(bp1_REG_data.AIC_SMR28.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR29",
        0,
        handles.bp1,
        116,
        4,
        read_32,
        AIC_SMR_wcb29,
        view32,
        &(bp1_REG_data.AIC_SMR29.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR30",
        0,
        handles.bp1,
        120,
        4,
        read_32,
        AIC_SMR_wcb30,
        view32,
        &(bp1_REG_data.AIC_SMR30.value),
        True
    );
    ppmCreateRegister("REG_AIC_SMR31",
        0,
        handles.bp1,
        124,
        4,
        read_32,
        AIC_SMR_wcb31,
        view32,
        &(bp1_REG_data.AIC_SMR31.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR0",
        0,
        handles.bp1,
        128,
        4,
        read_32,
        AIC_SVR_wcb0,
        view32,
        &(bp1_REG_data.AIC_SVR0.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR1",
        0,
        handles.bp1,
        132,
        4,
        read_32,
        AIC_SVR_wcb1,
        view32,
        &(bp1_REG_data.AIC_SVR1.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR2",
        0,
        handles.bp1,
        136,
        4,
        read_32,
        AIC_SVR_wcb2,
        view32,
        &(bp1_REG_data.AIC_SVR2.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR3",
        0,
        handles.bp1,
        140,
        4,
        read_32,
        AIC_SVR_wcb3,
        view32,
        &(bp1_REG_data.AIC_SVR3.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR4",
        0,
        handles.bp1,
        144,
        4,
        read_32,
        AIC_SVR_wcb4,
        view32,
        &(bp1_REG_data.AIC_SVR4.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR5",
        0,
        handles.bp1,
        148,
        4,
        read_32,
        AIC_SVR_wcb5,
        view32,
        &(bp1_REG_data.AIC_SVR5.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR6",
        0,
        handles.bp1,
        152,
        4,
        read_32,
        AIC_SVR_wcb6,
        view32,
        &(bp1_REG_data.AIC_SVR6.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR7",
        0,
        handles.bp1,
        156,
        4,
        read_32,
        AIC_SVR_wcb7,
        view32,
        &(bp1_REG_data.AIC_SVR7.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR8",
        0,
        handles.bp1,
        160,
        4,
        read_32,
        AIC_SVR_wcb8,
        view32,
        &(bp1_REG_data.AIC_SVR8.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR9",
        0,
        handles.bp1,
        164,
        4,
        read_32,
        AIC_SVR_wcb9,
        view32,
        &(bp1_REG_data.AIC_SVR9.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR10",
        0,
        handles.bp1,
        168,
        4,
        read_32,
        AIC_SVR_wcb10,
        view32,
        &(bp1_REG_data.AIC_SVR10.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR11",
        0,
        handles.bp1,
        172,
        4,
        read_32,
        AIC_SVR_wcb11,
        view32,
        &(bp1_REG_data.AIC_SVR11.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR12",
        0,
        handles.bp1,
        176,
        4,
        read_32,
        AIC_SVR_wcb12,
        view32,
        &(bp1_REG_data.AIC_SVR12.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR13",
        0,
        handles.bp1,
        180,
        4,
        read_32,
        AIC_SVR_wcb13,
        view32,
        &(bp1_REG_data.AIC_SVR13.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR14",
        0,
        handles.bp1,
        184,
        4,
        read_32,
        AIC_SVR_wcb14,
        view32,
        &(bp1_REG_data.AIC_SVR14.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR15",
        0,
        handles.bp1,
        188,
        4,
        read_32,
        AIC_SVR_wcb15,
        view32,
        &(bp1_REG_data.AIC_SVR15.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR16",
        0,
        handles.bp1,
        192,
        4,
        read_32,
        AIC_SVR_wcb16,
        view32,
        &(bp1_REG_data.AIC_SVR16.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR17",
        0,
        handles.bp1,
        196,
        4,
        read_32,
        AIC_SVR_wcb17,
        view32,
        &(bp1_REG_data.AIC_SVR17.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR18",
        0,
        handles.bp1,
        200,
        4,
        read_32,
        AIC_SVR_wcb18,
        view32,
        &(bp1_REG_data.AIC_SVR18.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR19",
        0,
        handles.bp1,
        204,
        4,
        read_32,
        AIC_SVR_wcb19,
        view32,
        &(bp1_REG_data.AIC_SVR19.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR20",
        0,
        handles.bp1,
        208,
        4,
        read_32,
        AIC_SVR_wcb20,
        view32,
        &(bp1_REG_data.AIC_SVR20.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR21",
        0,
        handles.bp1,
        212,
        4,
        read_32,
        AIC_SVR_wcb21,
        view32,
        &(bp1_REG_data.AIC_SVR21.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR22",
        0,
        handles.bp1,
        216,
        4,
        read_32,
        AIC_SVR_wcb22,
        view32,
        &(bp1_REG_data.AIC_SVR22.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR23",
        0,
        handles.bp1,
        220,
        4,
        read_32,
        AIC_SVR_wcb23,
        view32,
        &(bp1_REG_data.AIC_SVR23.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR24",
        0,
        handles.bp1,
        224,
        4,
        read_32,
        AIC_SVR_wcb24,
        view32,
        &(bp1_REG_data.AIC_SVR24.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR25",
        0,
        handles.bp1,
        228,
        4,
        read_32,
        AIC_SVR_wcb25,
        view32,
        &(bp1_REG_data.AIC_SVR25.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR26",
        0,
        handles.bp1,
        232,
        4,
        read_32,
        AIC_SVR_wcb26,
        view32,
        &(bp1_REG_data.AIC_SVR26.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR27",
        0,
        handles.bp1,
        236,
        4,
        read_32,
        AIC_SVR_wcb27,
        view32,
        &(bp1_REG_data.AIC_SVR27.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR28",
        0,
        handles.bp1,
        240,
        4,
        read_32,
        AIC_SVR_wcb28,
        view32,
        &(bp1_REG_data.AIC_SVR28.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR29",
        0,
        handles.bp1,
        244,
        4,
        read_32,
        AIC_SVR_wcb29,
        view32,
        &(bp1_REG_data.AIC_SVR29.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR30",
        0,
        handles.bp1,
        248,
        4,
        read_32,
        AIC_SVR_wcb30,
        view32,
        &(bp1_REG_data.AIC_SVR30.value),
        True
    );
    ppmCreateRegister("REG_AIC_SVR31",
        0,
        handles.bp1,
        252,
        4,
        read_32,
        AIC_SVR_wcb31,
        view32,
        &(bp1_REG_data.AIC_SVR31.value),
        True
    );
    ppmCreateRegister("REG_AIC_IVR",
        0,
        handles.bp1,
        256,
        4,
        AIC_IVR_rcb,
        0,
        view32,
        &(bp1_REG_data.AIC_IVR.value),
        True
    );
    ppmCreateRegister("REG_AIC_FVR",
        0,
        handles.bp1,
        260,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.AIC_FVR.value),
        True
    );
    ppmCreateRegister("REG_AIC_ISR",
        0,
        handles.bp1,
        264,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.AIC_ISR.value),
        True
    );
    ppmCreateRegister("REG_AIC_IPR",
        0,
        handles.bp1,
        268,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.AIC_IPR.value),
        True
    );
    ppmCreateRegister("REG_AIC_IMR",
        0,
        handles.bp1,
        272,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.AIC_IMR.value),
        True
    );
    ppmCreateRegister("REG_AIC_CISR",
        0,
        handles.bp1,
        276,
        4,
        read_32,
        0,
        view32,
        &(bp1_REG_data.AIC_CISR.value),
        True
    );
    ppmCreateRegister("REG_AIC_IECR",
        0,
        handles.bp1,
        288,
        4,
        0,
        AIC_IECR_wcb,
        view32,
        &(bp1_REG_data.AIC_IECR.value),
        True
    );
    ppmCreateRegister("REG_AIC_IDCR",
        0,
        handles.bp1,
        292,
        4,
        0,
        AIC_IDCR_wcb,
        view32,
        &(bp1_REG_data.AIC_IDCR.value),
        True
    );
    ppmCreateRegister("REG_AIC_ICCR",
        0,
        handles.bp1,
        296,
        4,
        0,
        AIC_ICCR_wcb,
        view32,
        &(bp1_REG_data.AIC_ICCR.value),
        True
    );
    ppmCreateRegister("REG_AIC_ISCR",
        0,
        handles.bp1,
        300,
        4,
        0,
        AIC_ISCR_wcb,
        view32,
        &(bp1_REG_data.AIC_ISCR.value),
        True
    );
    ppmCreateRegister("REG_AIC_EOICR",
        0,
        handles.bp1,
        304,
        4,
        0,
        AIC_EOICR_wcb,
        view32,
        &(bp1_REG_data.AIC_EOICR.value),
        True
    );
    ppmCreateRegister("REG_AIC_SPU",
        0,
        handles.bp1,
        308,
        4,
        read_32,
        AIC_SPU_wcb,
        view32,
        &(bp1_REG_data.AIC_SPU.value),
        True
    );

}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.NFIQ, value);

    handles.NFIQ = ppmOpenNetPort("NFIQ");

// To write to this net, use ppmWriteNet(handles.NIRQ, value);

    handles.NIRQ = ppmOpenNetPort("NIRQ");

    handles.FIQ = ppmOpenNetPort("FIQ");
    if (handles.FIQ) {
        ppmInstallNetCallback(handles.FIQ, FIQ_wcb, (void*)0);
    }

    handles.SWIRQ = ppmOpenNetPort("SWIRQ");
    if (handles.SWIRQ) {
        ppmInstallNetCallback(handles.SWIRQ, SWIRQ_wcb, (void*)0);
    }

    handles.US0IRQ = ppmOpenNetPort("US0IRQ");
    if (handles.US0IRQ) {
        ppmInstallNetCallback(handles.US0IRQ, US0IRQ_wcb, (void*)0);
    }

    handles.US1IRQ = ppmOpenNetPort("US1IRQ");
    if (handles.US1IRQ) {
        ppmInstallNetCallback(handles.US1IRQ, US1IRQ_wcb, (void*)0);
    }

    handles.TC0IRQ = ppmOpenNetPort("TC0IRQ");
    if (handles.TC0IRQ) {
        ppmInstallNetCallback(handles.TC0IRQ, TC0IRQ_wcb, (void*)0);
    }

    handles.TC1IRQ = ppmOpenNetPort("TC1IRQ");
    if (handles.TC1IRQ) {
        ppmInstallNetCallback(handles.TC1IRQ, TC1IRQ_wcb, (void*)0);
    }

    handles.TC2IRQ = ppmOpenNetPort("TC2IRQ");
    if (handles.TC2IRQ) {
        ppmInstallNetCallback(handles.TC2IRQ, TC2IRQ_wcb, (void*)0);
    }

    handles.WDIRQ = ppmOpenNetPort("WDIRQ");
    if (handles.WDIRQ) {
        ppmInstallNetCallback(handles.WDIRQ, WDIRQ_wcb, (void*)0);
    }

    handles.PIOIRQ = ppmOpenNetPort("PIOIRQ");
    if (handles.PIOIRQ) {
        ppmInstallNetCallback(handles.PIOIRQ, PIOIRQ_wcb, (void*)0);
    }

    handles.IRQ0 = ppmOpenNetPort("IRQ0");
    if (handles.IRQ0) {
        ppmInstallNetCallback(handles.IRQ0, IRQ0_wcb, (void*)0);
    }

    handles.IRQ1 = ppmOpenNetPort("IRQ1");
    if (handles.IRQ1) {
        ppmInstallNetCallback(handles.IRQ1, IRQ1_wcb, (void*)0);
    }

    handles.IRQ2 = ppmOpenNetPort("IRQ2");
    if (handles.IRQ2) {
        ppmInstallNetCallback(handles.IRQ2, IRQ2_wcb, (void*)0);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.AIC_SPU.value = 0x0;
        bp1_REG_data.AIC_EOICR.value = 0x0;
        bp1_REG_data.AIC_ISCR.value = 0x0;
        bp1_REG_data.AIC_ICCR.value = 0x0;
        bp1_REG_data.AIC_IDCR.value = 0x0;
        bp1_REG_data.AIC_IECR.value = 0x0;
        bp1_REG_data.AIC_CISR.value = 0x0;
        bp1_REG_data.AIC_IMR.value = 0x0;
        bp1_REG_data.AIC_IPR.value = 0x0;
        bp1_REG_data.AIC_ISR.value = 0x0;
        bp1_REG_data.AIC_FVR.value = 0x0;
        bp1_REG_data.AIC_IVR.value = 0x0;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installNetPorts();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\nAIC: Advanced Interrupt Controller\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe Advanced Interrupt Controller has an 8-level priority, individually maskable, vectored interrupt\ncontroller, and drives the NIRQ and NFIQ pins of the ARM7TDMI from:\n The external fast interrupt line (FIQ)\n The three external interrupt request lines (IRQ0 - IRQ2)\n The interrupt signals from the on-chip peripherals\nThe AIC is extensively programmable offering maximum flexibility, and its vectoring features\nreduce the real-time overhead in handling interrupts.\nThe AIC also features a spurious vector detection feature, which reduces spurious interrupt handling\nto a minimum, and a protect mode that facilitates the debug capabilities.\n");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D–ATARM–08/02");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

