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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW      (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM   (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))
#define PSE_DIAG_HIGH     (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            unsigned PS : 3;
            unsigned CLKS : 2;
            unsigned CPWMS : 1;
            unsigned TOIE : 1;
            unsigned TOF : 1;
        } bits;
    } SC;
    union { 
        Uns32 value;
        struct {
            unsigned COUNT : 16;
        } bits;
    } CNT;
    union { 
        Uns32 value;
        struct {
            unsigned MOD : 16;
        } bits;
    } MOD;
    union { 
        Uns32 value;
        struct {
            unsigned DMA : 1;
            unsigned __pad1 : 1;
            unsigned ELSA : 1;
            unsigned ELSB : 1;
            unsigned MSA : 1;
            unsigned MSB : 1;
            unsigned CHIE : 1;
            unsigned CHF : 1;
        } bits;
    } C0SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C0V;
    union { 
        Uns32 value;
        struct {
            unsigned DMA : 1;
            unsigned __pad1 : 1;
            unsigned ELSA : 1;
            unsigned ELSB : 1;
            unsigned MSA : 1;
            unsigned MSB : 1;
            unsigned CHIE : 1;
            unsigned CHF : 1;
        } bits;
    } C1SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C1V;
    union { 
        Uns32 value;
        struct {
            unsigned DMA : 1;
            unsigned __pad1 : 1;
            unsigned ELSA : 1;
            unsigned ELSB : 1;
            unsigned MSA : 1;
            unsigned MSB : 1;
            unsigned CHIE : 1;
            unsigned CHF : 1;
        } bits;
    } C2SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C2V;
    union { 
        Uns32 value;
        struct {
            unsigned DMA : 1;
            unsigned __pad1 : 1;
            unsigned ELSA : 1;
            unsigned ELSB : 1;
            unsigned MSA : 1;
            unsigned MSB : 1;
            unsigned CHIE : 1;
            unsigned CHF : 1;
        } bits;
    } C3SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C3V;
    union { 
        Uns32 value;
    } C4SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C4V;
    union { 
        Uns32 value;
    } C5SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C5V;
    union { 
        Uns32 value;
    } C6SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C6V;
    union { 
        Uns32 value;
    } C7SC;
    union { 
        Uns32 value;
        struct {
            unsigned VAL : 16;
        } bits;
    } C7V;
    union { 
        Uns32 value;
        struct {
            unsigned INIT : 16;
        } bits;
    } CNTIN;
    union { 
        Uns32 value;
        struct {
            unsigned CH0F : 1;
            unsigned CH1F : 1;
            unsigned CH2F : 1;
            unsigned CH3F : 1;
            unsigned CH4F : 1;
            unsigned CH5F : 1;
            unsigned CH6F : 1;
            unsigned CH7F : 1;
        } bits;
    } STATUS;
    union { 
        Uns32 value;
        struct {
            unsigned FTMEN : 1;
            unsigned INIT : 1;
            unsigned WPDIS : 1;
            unsigned PWMSYNC : 1;
            unsigned CAPTEST : 1;
            unsigned FAULTM : 2;
            unsigned FAULTIE : 1;
        } bits;
    } MODE;
    union { 
        Uns32 value;
        struct {
            unsigned CNTMIN : 1;
            unsigned CNTMAX : 1;
            unsigned REINIT : 1;
            unsigned SYNCHOM : 1;
            unsigned TRIG0 : 1;
            unsigned TRIG1 : 1;
            unsigned TRIG2 : 1;
            unsigned SWSYNC : 1;
        } bits;
    } SYNC;
    union { 
        Uns32 value;
        struct {
            unsigned CH0OI : 1;
            unsigned CH1OI : 1;
            unsigned CH2OI : 1;
            unsigned CH3OI : 1;
            unsigned CH4OI : 1;
            unsigned CH5OI : 1;
            unsigned CH6OI : 1;
            unsigned CH7OI : 1;
        } bits;
    } OUTINIT;
    union { 
        Uns32 value;
        struct {
            unsigned CH0OM : 1;
            unsigned CH1OM : 1;
            unsigned CH2OM : 1;
            unsigned CH3OM : 1;
            unsigned CH4OM : 1;
            unsigned CH5OM : 1;
            unsigned CH6OM : 1;
            unsigned CH7OM : 1;
        } bits;
    } OUTMASK;
    union { 
        Uns32 value;
        struct {
            unsigned COMBINE0 : 1;
            unsigned COMP0 : 1;
            unsigned DECAPEN0 : 1;
            unsigned DECAP0 : 1;
            unsigned DTEN0 : 1;
            unsigned SYNCEN0 : 1;
            unsigned FAULTEN0 : 1;
            unsigned __pad7 : 1;
            unsigned COMBINE1 : 1;
            unsigned COMP1 : 1;
            unsigned DECAPEN1 : 1;
            unsigned DECAP1 : 1;
            unsigned DTEN1 : 1;
            unsigned SYNCEN1 : 1;
            unsigned FAULTEN1 : 1;
            unsigned __pad15 : 1;
            unsigned COMBINE2 : 1;
            unsigned COMP2 : 1;
            unsigned DECAPEN2 : 1;
            unsigned DECAP2 : 1;
            unsigned DTEN2 : 1;
            unsigned SYNCEN2 : 1;
            unsigned FAULTEN2 : 1;
            unsigned __pad23 : 1;
            unsigned COMBINE3 : 1;
            unsigned COMP3 : 1;
            unsigned DECAPEN3 : 1;
            unsigned DECAP3 : 1;
            unsigned DTEN3 : 1;
            unsigned SYNCEN3 : 1;
            unsigned FAULTEN3 : 1;
        } bits;
    } COMBINE;
    union { 
        Uns32 value;
        struct {
            unsigned DTVAL : 6;
            unsigned DTPS : 2;
        } bits;
    } DEADTIME;
    union { 
        Uns32 value;
        struct {
            unsigned CH2TRIG : 1;
            unsigned CH3TRIG : 1;
            unsigned CH4TRIG : 1;
            unsigned CH5TRIG : 1;
            unsigned CH0TRIG : 1;
            unsigned CH1TRIG : 1;
            unsigned INITTRIGEN : 1;
            unsigned TRIGF : 1;
        } bits;
    } EXTTRIG;
    union { 
        Uns32 value;
        struct {
            unsigned POL0 : 1;
            unsigned POL1 : 1;
            unsigned POL2 : 1;
            unsigned POL3 : 1;
            unsigned POL4 : 1;
            unsigned POL5 : 1;
            unsigned POL6 : 1;
            unsigned POL7 : 1;
        } bits;
    } POL;
    union { 
        Uns32 value;
        struct {
            unsigned FAULTF0 : 1;
            unsigned FAULTF1 : 1;
            unsigned FAULTF2 : 1;
            unsigned FAULTF3 : 1;
            unsigned __pad4 : 1;
            unsigned FAULTIN : 1;
            unsigned WPEN : 1;
            unsigned FAULTF : 1;
        } bits;
    } FMS;
    union { 
        Uns32 value;
        struct {
            unsigned CH0FVAL : 4;
            unsigned CH1FVAL : 4;
            unsigned CH2FVAL : 4;
            unsigned CH3FVAL : 4;
        } bits;
    } FILTER;
    union { 
        Uns32 value;
        struct {
            unsigned FAULT0EN : 1;
            unsigned FAULT1EN : 1;
            unsigned FAULT2EN : 1;
            unsigned FAULT3EN : 1;
            unsigned FFLTR0EN : 1;
            unsigned FFLTR1EN : 1;
            unsigned FFLTR2EN : 1;
            unsigned FFLTR3EN : 1;
            unsigned FFVAL : 4;
        } bits;
    } FLTCTRL;
    union { 
        Uns32 value;
        struct {
            unsigned QUADEN : 1;
            unsigned TOFDIR : 1;
            unsigned QUADIR : 1;
            unsigned QUADMODE : 1;
            unsigned PHBPOL : 1;
            unsigned PHAPOL : 1;
            unsigned PHBFLTREN : 1;
            unsigned PHAFLTREN : 1;
        } bits;
    } QDCTRL;
    union { 
        Uns32 value;
        struct {
            unsigned NUMTOF : 5;
            unsigned __pad5 : 1;
            unsigned BDMMODE : 2;
            unsigned __pad8 : 1;
            unsigned GTBEEN : 1;
            unsigned GTBEOUT : 1;
        } bits;
    } CONF;
    union { 
        Uns32 value;
        struct {
            unsigned FLT0POL : 1;
            unsigned FLT1POL : 1;
            unsigned FLT2POL : 1;
            unsigned FLT3POL : 1;
        } bits;
    } FLTPOL;
    union { 
        Uns32 value;
        struct {
            unsigned HWTRIGMODE : 1;
            unsigned __pad1 : 1;
            unsigned CNTINC : 1;
            unsigned __pad3 : 1;
            unsigned INVC : 1;
            unsigned SWOC : 1;
            unsigned __pad6 : 1;
            unsigned SYNCMODE : 1;
            unsigned SWRSTCNT : 1;
            unsigned SWWRBUF : 1;
            unsigned SWOM : 1;
            unsigned SWINVC : 1;
            unsigned SWSOC : 1;
            unsigned __pad13 : 3;
            unsigned HWRSTCNT : 1;
            unsigned HWWRBUF : 1;
            unsigned HWOM : 1;
            unsigned HWINVC : 1;
            unsigned HWSOC : 1;
        } bits;
    } SYNCONF;
    union { 
        Uns32 value;
        struct {
            unsigned INV0EN : 1;
            unsigned INV1EN : 1;
            unsigned INV2EN : 1;
            unsigned INV3EN : 1;
        } bits;
    } INVCTRL;
    union { 
        Uns32 value;
        struct {
            unsigned CH0OC : 1;
            unsigned CH1OC : 1;
            unsigned CH2OC : 1;
            unsigned CH3OC : 1;
            unsigned CH4OC : 1;
            unsigned CH5OC : 1;
            unsigned CH6OC : 1;
            unsigned CH7OC : 1;
            unsigned CH0OCV : 1;
            unsigned CH1OCV : 1;
            unsigned CH2OCV : 1;
            unsigned CH3OCV : 1;
            unsigned CH4OCV : 1;
            unsigned CH5OCV : 1;
            unsigned CH6OCV : 1;
            unsigned CH7OCV : 1;
        } bits;
    } SWOCTRL;
    union { 
        Uns32 value;
        struct {
            unsigned CH0SEL : 1;
            unsigned CH1SEL : 1;
            unsigned CH2SEL : 1;
            unsigned CH3SEL : 1;
            unsigned CH4SEL : 1;
            unsigned CH5SEL : 1;
            unsigned CH6SEL : 1;
            unsigned CH7SEL : 1;
            unsigned __pad8 : 1;
            unsigned LDOK : 1;
        } bits;
    } PWMLOAD;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          PhaseA;
    ppmNetHandle          PhaseB;
    ppmNetHandle          Interrupt;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(phaseACB);
PPM_NET_CB(phaseBCB);
PPM_REG_READ_CB(readSC);
PPM_REG_WRITE_CB(writeSC);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
