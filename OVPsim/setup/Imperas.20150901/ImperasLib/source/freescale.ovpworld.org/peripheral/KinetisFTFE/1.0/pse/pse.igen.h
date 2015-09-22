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
            unsigned MGSTAT0 : 1;
            unsigned __pad1 : 3;
            unsigned FPVIOL : 1;
            unsigned ACCERR : 1;
            unsigned RDCOLERR : 1;
            unsigned CCIF : 1;
        } bits;
    } FSTAT;
    union { 
        Uns8 value;
        struct {
            unsigned EEERDY : 1;
            unsigned RAMRDY : 1;
            unsigned PFLSH : 1;
            unsigned SWAP : 1;
            unsigned ERSSUSP : 1;
            unsigned ERSAREQ : 1;
            unsigned RDCOLLIE : 1;
            unsigned CCIE : 1;
        } bits;
    } FCNFG;
    union { 
        Uns8 value;
        struct {
            unsigned SEC : 2;
            unsigned FSLACC : 2;
            unsigned MEEN : 2;
            unsigned KEYEN : 2;
        } bits;
    } FSEC;
    union { 
        Uns8 value;
        struct {
            unsigned OPT : 8;
        } bits;
    } FOPT;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB3;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB2;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB1;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB0;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB7;
    union { 
        Uns8 value;
    } FCCOB6;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB5;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB4;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOBB;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOBA;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB9;
    union { 
        Uns8 value;
        struct {
            unsigned CCOBn : 8;
        } bits;
    } FCCOB8;
    union { 
        Uns8 value;
        struct {
            unsigned PROT : 8;
        } bits;
    } FPROT3;
    union { 
        Uns8 value;
        struct {
            unsigned PROT : 8;
        } bits;
    } FPROT2;
    union { 
        Uns8 value;
        struct {
            unsigned PROT : 8;
        } bits;
    } FPROT1;
    union { 
        Uns8 value;
        struct {
            unsigned PROT : 8;
        } bits;
    } FPROT0;
    union { 
        Uns8 value;
        struct {
            unsigned EPROT : 8;
        } bits;
    } FEPROT;
    union { 
        Uns8 value;
        struct {
            unsigned DPROT : 8;
        } bits;
    } FDPROT;
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
