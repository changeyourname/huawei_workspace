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
            unsigned DATA : 8;
        } bits;
    } DAT0L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT0H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT1L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT1H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT2L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT2H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT3L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT3H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT4L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT4H;
    union { 
        Uns8 value;
    } DAT5L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT5H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT6L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT6H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT7L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT7H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT8L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT8H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT9L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT9H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT10L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT10H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT11L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT11H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT12L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT12H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT13L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT13H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT14L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT14H;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } DAT15L;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 4;
        } bits;
    } DAT15H;
    union { 
        Uns8 value;
        struct {
            unsigned DACBFRPBF : 1;
            unsigned DACBFRPTF : 1;
            unsigned DACBFWMF : 1;
        } bits;
    } SR;
    union { 
        Uns8 value;
        struct {
            unsigned DACBBIEN : 1;
            unsigned DACBTIEN : 1;
            unsigned DACBWIEN : 1;
            unsigned LPEN : 1;
            unsigned DACSWTRG : 1;
            unsigned DACTRGSEL : 1;
            unsigned DACRFS : 1;
            unsigned DACEN : 1;
        } bits;
    } C0;
    union { 
        Uns8 value;
        struct {
            unsigned DACBFEN : 1;
            unsigned DACBFMD : 2;
            unsigned DACBFWM : 2;
            unsigned __pad5 : 2;
            unsigned DMAEN : 1;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            unsigned DACBFUP : 4;
            unsigned DACBFRP : 4;
        } bits;
    } C2;
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
