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
            unsigned FRDE : 1;
            unsigned FWDE : 1;
            unsigned __pad2 : 6;
            unsigned FRIE : 1;
            unsigned FWIE : 1;
            unsigned FEIE : 1;
            unsigned SEIE : 1;
            unsigned WSIE : 1;
            unsigned __pad13 : 3;
            unsigned FRF : 1;
            unsigned FWF : 1;
            unsigned FEF : 1;
            unsigned SEF : 1;
            unsigned WSF : 1;
            unsigned __pad21 : 3;
            unsigned SR : 1;
            unsigned FR : 1;
            unsigned __pad26 : 2;
            unsigned BCE : 1;
            unsigned DBGE : 1;
            unsigned STOPE : 1;
            unsigned TE : 1;
        } bits;
    } TCSR;
    union { 
        Uns32 value;
        struct {
            unsigned TFW : 3;
        } bits;
    } TCR1;
    union { 
        Uns32 value;
        struct {
            unsigned DIV : 8;
            unsigned __pad8 : 16;
            unsigned BCD : 1;
            unsigned BCP : 1;
            unsigned MSEL : 2;
            unsigned BCI : 1;
            unsigned BCS : 1;
            unsigned SYNC : 2;
        } bits;
    } TCR2;
    union { 
        Uns32 value;
        struct {
            unsigned WDFL : 5;
            unsigned __pad5 : 11;
            unsigned TCE : 2;
        } bits;
    } TCR3;
    union { 
        Uns32 value;
        struct {
            unsigned FSD : 1;
            unsigned FSP : 1;
            unsigned __pad2 : 1;
            unsigned FSE : 1;
            unsigned MF : 1;
            unsigned __pad5 : 3;
            unsigned SYWD : 5;
            unsigned __pad13 : 3;
            unsigned FRSZ : 5;
        } bits;
    } TCR4;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 8;
            unsigned FBT : 5;
            unsigned __pad13 : 3;
            unsigned W0W : 5;
            unsigned __pad21 : 3;
            unsigned WNW : 5;
        } bits;
    } TCR5;
    union { 
        Uns32 value;
        struct {
            unsigned TDR : 32;
        } bits;
    } TDR0;
    union { 
        Uns32 value;
        struct {
            unsigned TDR : 32;
        } bits;
    } TDR1;
    union { 
        Uns32 value;
        struct {
            unsigned RFP : 4;
            unsigned __pad4 : 12;
            unsigned WFP : 4;
        } bits;
    } TFR0;
    union { 
        Uns32 value;
        struct {
            unsigned RFP : 4;
            unsigned __pad4 : 12;
            unsigned WFP : 4;
        } bits;
    } TFR1;
    union { 
        Uns32 value;
        struct {
            unsigned TWM : 32;
        } bits;
    } TMR;
    union { 
        Uns32 value;
        struct {
            unsigned FRDE : 1;
            unsigned FWDE : 1;
            unsigned __pad2 : 6;
            unsigned FRIE : 1;
            unsigned FWIE : 1;
            unsigned FEIE : 1;
            unsigned SEIE : 1;
            unsigned WSIE : 1;
            unsigned __pad13 : 3;
            unsigned FRF : 1;
            unsigned FWF : 1;
            unsigned FEF : 1;
            unsigned SEF : 1;
            unsigned WSF : 1;
            unsigned __pad21 : 3;
            unsigned SR : 1;
            unsigned FR : 1;
            unsigned __pad26 : 2;
            unsigned BCE : 1;
            unsigned DBGE : 1;
            unsigned STOPE : 1;
            unsigned RE : 1;
        } bits;
    } RCSR;
    union { 
        Uns32 value;
        struct {
            unsigned RFW : 3;
        } bits;
    } RCR1;
    union { 
        Uns32 value;
        struct {
            unsigned DIV : 8;
            unsigned __pad8 : 16;
            unsigned BCD : 1;
            unsigned BCP : 1;
            unsigned MSEL : 2;
            unsigned BCI : 1;
            unsigned BCS : 1;
            unsigned SYNC : 2;
        } bits;
    } RCR2;
    union { 
        Uns32 value;
        struct {
            unsigned WDFL : 5;
            unsigned __pad5 : 11;
            unsigned RCE : 2;
        } bits;
    } RCR3;
    union { 
        Uns32 value;
        struct {
            unsigned FSD : 1;
            unsigned FSP : 1;
            unsigned __pad2 : 1;
            unsigned FSE : 1;
            unsigned MF : 1;
            unsigned __pad5 : 3;
            unsigned SYWD : 5;
            unsigned __pad13 : 3;
            unsigned FRSZ : 5;
        } bits;
    } RCR4;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 8;
            unsigned FBT : 5;
            unsigned __pad13 : 3;
            unsigned W0W : 5;
            unsigned __pad21 : 3;
            unsigned WNW : 5;
        } bits;
    } RCR5;
    union { 
        Uns32 value;
        struct {
            unsigned RDR : 32;
        } bits;
    } RDR0;
    union { 
        Uns32 value;
        struct {
            unsigned RDR : 32;
        } bits;
    } RDR1;
    union { 
        Uns32 value;
        struct {
            unsigned RFP : 4;
            unsigned __pad4 : 12;
            unsigned WFP : 4;
        } bits;
    } RFR0;
    union { 
        Uns32 value;
        struct {
            unsigned RFP : 4;
            unsigned __pad4 : 12;
            unsigned WFP : 4;
        } bits;
    } RFR1;
    union { 
        Uns32 value;
        struct {
            unsigned RWM : 32;
        } bits;
    } RMR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned MICS : 2;
            unsigned __pad26 : 4;
            unsigned MOE : 1;
            unsigned DUF : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            unsigned DIVIDE : 12;
            unsigned FRACT : 8;
        } bits;
    } MDR;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
