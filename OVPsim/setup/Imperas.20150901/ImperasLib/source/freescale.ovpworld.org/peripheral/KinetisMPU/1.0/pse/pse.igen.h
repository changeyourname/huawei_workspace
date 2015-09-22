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
            unsigned VLD : 1;
            unsigned __pad1 : 7;
            unsigned NRGD : 4;
            unsigned NSP : 4;
            unsigned HRL : 4;
            unsigned __pad20 : 4;
            unsigned SPERR : 8;
        } bits;
    } CESR;
    union { 
        Uns32 value;
        struct {
            unsigned EADDR : 32;
        } bits;
    } EAR0;
    union { 
        Uns32 value;
        struct {
            unsigned ERW : 1;
            unsigned EATTR : 3;
            unsigned EMN : 4;
            unsigned EPID : 8;
            unsigned EACD : 16;
        } bits;
    } EDR0;
    union { 
        Uns32 value;
        struct {
            unsigned EADDR : 32;
        } bits;
    } EAR1;
    union { 
        Uns32 value;
        struct {
            unsigned ERW : 1;
            unsigned EATTR : 3;
            unsigned EMN : 4;
            unsigned EPID : 8;
            unsigned EACD : 16;
        } bits;
    } EDR1;
    union { 
        Uns32 value;
        struct {
            unsigned EADDR : 32;
        } bits;
    } EAR2;
    union { 
        Uns32 value;
        struct {
            unsigned ERW : 1;
            unsigned EATTR : 3;
            unsigned EMN : 4;
            unsigned EPID : 8;
            unsigned EACD : 16;
        } bits;
    } EDR2;
    union { 
        Uns32 value;
        struct {
            unsigned EADDR : 32;
        } bits;
    } EAR3;
    union { 
        Uns32 value;
        struct {
            unsigned ERW : 1;
            unsigned EATTR : 3;
            unsigned EMN : 4;
            unsigned EPID : 8;
            unsigned EACD : 16;
        } bits;
    } EDR3;
    union { 
        Uns32 value;
        struct {
            unsigned EADDR : 32;
        } bits;
    } EAR4;
    union { 
        Uns32 value;
        struct {
            unsigned ERW : 1;
            unsigned EATTR : 3;
            unsigned EMN : 4;
            unsigned EPID : 8;
            unsigned EACD : 16;
        } bits;
    } EDR4;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD0_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD0_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD0_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD0_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD1_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD1_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD1_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD1_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD2_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD2_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD2_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD2_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD3_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD3_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD3_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD3_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD4_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD4_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD4_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD4_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD5_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD5_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD5_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD5_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD6_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD6_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD6_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD6_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD7_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD7_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD7_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD7_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD8_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD8_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD8_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD8_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD9_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD9_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD9_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD9_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD10_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD10_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD10_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD10_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD11_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD11_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD11_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD11_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD12_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD12_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD12_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD12_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD13_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD13_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD13_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD13_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD14_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD14_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD14_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD14_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned SRTADDR : 27;
        } bits;
    } RGD15_WORD0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ENDADDR : 27;
        } bits;
    } RGD15_WORD1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGD15_WORD2;
    union { 
        Uns32 value;
        struct {
            unsigned VLD : 1;
            unsigned __pad1 : 15;
            unsigned PIDMASK : 8;
            unsigned PID : 8;
        } bits;
    } RGD15_WORD3;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC0;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC1;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC2;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC3;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC4;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC5;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC6;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC7;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC8;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC9;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC10;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC11;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC12;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC13;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC14;
    union { 
        Uns32 value;
        struct {
            unsigned M0UM : 3;
            unsigned M0SM : 2;
            unsigned M0PE : 1;
            unsigned M1UM : 3;
            unsigned M1SM : 2;
            unsigned M1PE : 1;
            unsigned M2UM : 3;
            unsigned M2SM : 2;
            unsigned M2PE : 1;
            unsigned M3UM : 3;
            unsigned M3SM : 2;
            unsigned M3PE : 1;
            unsigned M4WE : 1;
            unsigned M4RE : 1;
            unsigned M5WE : 1;
            unsigned M5RE : 1;
            unsigned M6WE : 1;
            unsigned M6RE : 1;
            unsigned M7WE : 1;
            unsigned M7RE : 1;
        } bits;
    } RGDAAC15;
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
