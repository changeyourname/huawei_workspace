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
        Uns8 value;
        struct {
            unsigned __pad0 : 1;
            unsigned AD : 7;
        } bits;
    } A1;
    union { 
        Uns8 value;
        struct {
            unsigned ICR : 6;
            unsigned MULT : 2;
        } bits;
    } F;
    union { 
        Uns8 value;
        struct {
            unsigned DMAEN : 1;
            unsigned WUEN : 1;
            unsigned RSTA : 1;
            unsigned TXAK : 1;
            unsigned TX : 1;
            unsigned MST : 1;
            unsigned IICIE : 1;
            unsigned IICEN : 1;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            unsigned RXAK : 1;
            unsigned IICIF : 1;
            unsigned SRW : 1;
            unsigned RAM : 1;
            unsigned ARBL : 1;
            unsigned BUSY : 1;
            unsigned IAAS : 1;
            unsigned TCF : 1;
        } bits;
    } S;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } D;
    union { 
        Uns8 value;
        struct {
            unsigned AD : 3;
            unsigned RMEN : 1;
            unsigned SBRC : 1;
            unsigned HDRS : 1;
            unsigned ADEXT : 1;
            unsigned GCAEN : 1;
        } bits;
    } C2;
    union { 
        Uns8 value;
        struct {
            unsigned FLT : 5;
        } bits;
    } FLT;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 1;
            unsigned RAD : 7;
        } bits;
    } RA;
    union { 
        Uns8 value;
        struct {
            unsigned SHTF2IE : 1;
            unsigned SHTF2 : 1;
            unsigned SHTF1 : 1;
            unsigned SLTF : 1;
            unsigned TCKSEL : 1;
            unsigned SIICAEN : 1;
            unsigned ALERTEN : 1;
            unsigned FACK : 1;
        } bits;
    } SMB;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 1;
            unsigned SAD : 7;
        } bits;
    } A2;
    union { 
        Uns8 value;
        struct {
            unsigned SSLT : 8;
        } bits;
    } SLTH;
    union { 
        Uns8 value;
        struct {
            unsigned SSLT : 8;
        } bits;
    } SLTL;
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
