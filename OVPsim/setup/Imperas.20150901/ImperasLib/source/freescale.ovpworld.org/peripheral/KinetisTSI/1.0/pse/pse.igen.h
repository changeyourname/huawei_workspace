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
            unsigned STPE : 1;
            unsigned STM : 1;
            unsigned __pad2 : 2;
            unsigned ESOR : 1;
            unsigned ERIE : 1;
            unsigned TSIIE : 1;
            unsigned TSIEN : 1;
            unsigned SWTS : 1;
            unsigned SCNIP : 1;
            unsigned __pad10 : 2;
            unsigned OVRF : 1;
            unsigned EXTERF : 1;
            unsigned OUTRGF : 1;
            unsigned EOSF : 1;
            unsigned PS : 3;
            unsigned NSCN : 5;
            unsigned LPSCNITV : 4;
            unsigned LPCLKS : 1;
        } bits;
    } GENCS;
    union { 
        Uns32 value;
        struct {
            unsigned AMPSC : 3;
            unsigned AMCLKS : 2;
            unsigned __pad5 : 3;
            unsigned SMOD : 8;
            unsigned EXTCHRG : 4;
            unsigned __pad20 : 4;
            unsigned REFCHRG : 4;
        } bits;
    } SCANC;
    union { 
        Uns32 value;
        struct {
            unsigned PEN0 : 1;
            unsigned PEN1 : 1;
            unsigned PEN2 : 1;
            unsigned PEN3 : 1;
            unsigned PEN4 : 1;
            unsigned PEN5 : 1;
            unsigned PEN6 : 1;
            unsigned PEN7 : 1;
            unsigned PEN8 : 1;
            unsigned PEN9 : 1;
            unsigned PEN10 : 1;
            unsigned PEN11 : 1;
            unsigned PEN12 : 1;
            unsigned PEN13 : 1;
            unsigned PEN14 : 1;
            unsigned PEN15 : 1;
            unsigned LPSP : 4;
        } bits;
    } PEN;
    union { 
        Uns32 value;
        struct {
            unsigned WUCNT : 16;
        } bits;
    } WUCNTR;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR1;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR3;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR5;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR7;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR9;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR11;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR13;
    union { 
        Uns32 value;
        struct {
            unsigned CTN1 : 16;
            unsigned CTN : 16;
        } bits;
    } CNTR15;
    union { 
        Uns32 value;
        struct {
            unsigned HTHH : 16;
            unsigned LTHH : 16;
        } bits;
    } THRESHOLD;
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
