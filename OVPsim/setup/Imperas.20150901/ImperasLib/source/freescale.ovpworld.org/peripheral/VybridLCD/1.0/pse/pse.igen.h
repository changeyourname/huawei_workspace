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
            unsigned LCDBPS : 3;
            unsigned __pad3 : 1;
            unsigned LCDBPA : 2;
            unsigned __pad6 : 2;
            unsigned NOF : 8;
            unsigned EOF : 1;
            unsigned LCDINT : 1;
            unsigned LCDOCS : 1;
            unsigned BSTAO : 1;
            unsigned BSTSEL : 1;
            unsigned BSTEN : 1;
            unsigned PWR : 2;
            unsigned VLCDS : 1;
            unsigned BIAS : 1;
            unsigned DUTY : 3;
            unsigned LCDRCS : 1;
            unsigned LCDRST : 1;
            unsigned LCDEN : 1;
        } bits;
    } LCDCR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned LCLK : 4;
        } bits;
    } LCDPCR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned LCC : 11;
            unsigned __pad27 : 4;
            unsigned CCEN : 1;
        } bits;
    } LCDCCR;
    union { 
        Uns32 value;
        struct {
            unsigned ENFP : 32;
        } bits;
    } ENFPR0;
    union { 
        Uns32 value;
        struct {
            unsigned ENFP : 32;
        } bits;
    } ENFPR1;
    union { 
        Uns32 value;
        struct {
            unsigned FP3_BP : 8;
            unsigned FP2_BP : 8;
            unsigned FP1_BP : 8;
            unsigned FP0_BP : 8;
        } bits;
    } LCDRAM0;
    union { 
        Uns32 value;
        struct {
            unsigned FP7_BP : 8;
            unsigned FP6_BP : 8;
            unsigned FP5_BP : 8;
            unsigned FP4_BP : 8;
        } bits;
    } LCDRAM1;
    union { 
        Uns32 value;
        struct {
            unsigned FP11_BP : 8;
            unsigned FP10_BP : 8;
            unsigned FP9_BP : 8;
            unsigned FP8_BP : 8;
        } bits;
    } LCDRAM2;
    union { 
        Uns32 value;
        struct {
            unsigned FP15_BP : 8;
            unsigned FP14_BP : 8;
            unsigned FP13_BP : 8;
            unsigned FP12_BP : 8;
        } bits;
    } LCDRAM3;
    union { 
        Uns32 value;
        struct {
            unsigned FP19_BP : 8;
            unsigned FP18_BP : 8;
            unsigned FP17_BP : 8;
            unsigned FP16_BP : 8;
        } bits;
    } LCDRAM4;
    union { 
        Uns32 value;
        struct {
            unsigned FP23_BP : 8;
            unsigned FP22_BP : 8;
            unsigned FP21_BP : 8;
            unsigned FP20_BP : 8;
        } bits;
    } LCDRAM5;
    union { 
        Uns32 value;
        struct {
            unsigned FP27_BP : 8;
            unsigned FP26_BP : 8;
            unsigned FP25_BP : 8;
            unsigned FP24_BP : 8;
        } bits;
    } LCDRAM6;
    union { 
        Uns32 value;
        struct {
            unsigned FP31_BP : 8;
            unsigned FP30_BP : 8;
            unsigned FP29_BP : 8;
            unsigned FP28_BP : 8;
        } bits;
    } LCDRAM7;
    union { 
        Uns32 value;
        struct {
            unsigned FP35_BP : 8;
            unsigned FP34_BP : 8;
            unsigned FP33_BP : 8;
            unsigned FP32_BP : 8;
        } bits;
    } LCDRAM8;
    union { 
        Uns32 value;
        struct {
            unsigned FP39_BP : 8;
            unsigned FP38_BP : 8;
            unsigned FP37_BP : 8;
            unsigned FP36_BP : 8;
        } bits;
    } LCDRAM9;
    union { 
        Uns32 value;
        struct {
            unsigned FP43_BP : 8;
            unsigned FP42_BP : 8;
            unsigned FP41_BP : 8;
            unsigned FP40_BP : 8;
        } bits;
    } LCDRAM10;
    union { 
        Uns32 value;
        struct {
            unsigned FP47_BP : 8;
            unsigned FP46_BP : 8;
            unsigned FP45_BP : 8;
            unsigned FP44_BP : 8;
        } bits;
    } LCDRAM11;
    union { 
        Uns32 value;
        struct {
            unsigned FP51_BP : 8;
            unsigned FP50_BP : 8;
            unsigned FP49_BP : 8;
            unsigned FP48_BP : 8;
        } bits;
    } LCDRAM12;
    union { 
        Uns32 value;
        struct {
            unsigned FP55_BP : 8;
            unsigned FP54_BP : 8;
            unsigned FP53_BP : 8;
            unsigned FP52_BP : 8;
        } bits;
    } LCDRAM13;
    union { 
        Uns32 value;
        struct {
            unsigned FP59_BP : 8;
            unsigned FP58_BP : 8;
            unsigned FP57_BP : 8;
            unsigned FP56_BP : 8;
        } bits;
    } LCDRAM14;
    union { 
        Uns32 value;
        struct {
            unsigned FP63_BP : 8;
            unsigned FP62_BP : 8;
            unsigned FP61_BP : 8;
            unsigned FP60_BP : 8;
        } bits;
    } LCDRAM15;
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
