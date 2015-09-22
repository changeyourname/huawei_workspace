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
            unsigned FRZ : 1;
            unsigned MDIS : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            unsigned TSV : 32;
        } bits;
    } LDVAL0;
    union { 
        Uns32 value;
        struct {
            unsigned TVL : 32;
        } bits;
    } CVAL0;
    union { 
        Uns32 value;
        struct {
            unsigned TEN : 1;
            unsigned TIE : 1;
        } bits;
    } TCTRL0;
    union { 
        Uns32 value;
        struct {
            unsigned TIF : 1;
        } bits;
    } TFLG0;
    union { 
        Uns32 value;
        struct {
            unsigned TSV : 32;
        } bits;
    } LDVAL1;
    union { 
        Uns32 value;
        struct {
            unsigned TVL : 32;
        } bits;
    } CVAL1;
    union { 
        Uns32 value;
        struct {
            unsigned TEN : 1;
            unsigned TIE : 1;
        } bits;
    } TCTRL1;
    union { 
        Uns32 value;
        struct {
            unsigned TIF : 1;
        } bits;
    } TFLG1;
    union { 
        Uns32 value;
        struct {
            unsigned TSV : 32;
        } bits;
    } LDVAL2;
    union { 
        Uns32 value;
        struct {
            unsigned TVL : 32;
        } bits;
    } CVAL2;
    union { 
        Uns32 value;
        struct {
            unsigned TEN : 1;
            unsigned TIE : 1;
        } bits;
    } TCTRL2;
    union { 
        Uns32 value;
        struct {
            unsigned TIF : 1;
        } bits;
    } TFLG2;
    union { 
        Uns32 value;
        struct {
            unsigned TSV : 32;
        } bits;
    } LDVAL3;
    union { 
        Uns32 value;
        struct {
            unsigned TVL : 32;
        } bits;
    } CVAL3;
    union { 
        Uns32 value;
        struct {
            unsigned TEN : 1;
            unsigned TIE : 1;
        } bits;
    } TCTRL3;
    union { 
        Uns32 value;
        struct {
            unsigned TIF : 1;
        } bits;
    } TFLG3;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          irq0;
    ppmNetHandle          trg0;
    ppmNetHandle          irq1;
    ppmNetHandle          trg1;
    ppmNetHandle          irq2;
    ppmNetHandle          trg2;
    ppmNetHandle          irq3;
    ppmNetHandle          trg3;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readCVAL);
PPM_REG_VIEW_CB(viewCVAL);
PPM_REG_WRITE_CB(writeMCR);
PPM_REG_WRITE_CB(writeTCTRL);
PPM_REG_WRITE_CB(writeTFLG);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
