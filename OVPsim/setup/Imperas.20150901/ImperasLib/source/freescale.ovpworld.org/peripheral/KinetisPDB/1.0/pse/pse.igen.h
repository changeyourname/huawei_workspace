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
            unsigned LDOK : 1;
            unsigned CONT : 1;
            unsigned MULT : 2;
            unsigned __pad4 : 1;
            unsigned PDBIE : 1;
            unsigned PDBIF : 1;
            unsigned PDBEN : 1;
            unsigned TRGSEL : 4;
            unsigned PRESCALER : 3;
            unsigned DMAEN : 1;
            unsigned SWTRIG : 1;
            unsigned PDBEIE : 1;
            unsigned LDMOD : 2;
        } bits;
    } SC;
    union { 
        Uns32 value;
        struct {
            unsigned MOD : 16;
        } bits;
    } MOD;
    union { 
        Uns32 value;
        struct {
            unsigned CNT : 16;
        } bits;
    } CNT;
    union { 
        Uns32 value;
        struct {
            unsigned IDLY : 16;
        } bits;
    } IDLY;
    union { 
        Uns32 value;
        struct {
            unsigned EN : 8;
            unsigned TOS : 8;
            unsigned BB : 8;
        } bits;
    } CH0C1;
    union { 
        Uns32 value;
        struct {
            unsigned ERR : 8;
            unsigned __pad8 : 8;
            unsigned CF : 8;
        } bits;
    } CH0S;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH0DLY0;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH0DLY1;
    union { 
        Uns32 value;
        struct {
            unsigned EN : 8;
            unsigned TOS : 8;
            unsigned BB : 8;
        } bits;
    } CH1C1;
    union { 
        Uns32 value;
        struct {
            unsigned ERR : 8;
            unsigned __pad8 : 8;
            unsigned CF : 8;
        } bits;
    } CH1S;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH1DLY0;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH1DLY1;
    union { 
        Uns32 value;
        struct {
            unsigned EN : 8;
            unsigned TOS : 8;
            unsigned BB : 8;
        } bits;
    } CH2C1;
    union { 
        Uns32 value;
        struct {
            unsigned ERR : 8;
            unsigned __pad8 : 8;
            unsigned CF : 8;
        } bits;
    } CH2S;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH2DLY0;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH2DLY1;
    union { 
        Uns32 value;
        struct {
            unsigned EN : 8;
            unsigned TOS : 8;
            unsigned BB : 8;
        } bits;
    } CH3C1;
    union { 
        Uns32 value;
        struct {
            unsigned ERR : 8;
            unsigned __pad8 : 8;
            unsigned CF : 8;
        } bits;
    } CH3S;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH3DLY0;
    union { 
        Uns32 value;
        struct {
            unsigned DLY : 16;
        } bits;
    } CH3DLY1;
    union { 
        Uns32 value;
        struct {
            unsigned TOE : 1;
            unsigned EXT : 1;
        } bits;
    } DACINTC0;
    union { 
        Uns32 value;
        struct {
            unsigned INT : 16;
        } bits;
    } DACINT0;
    union { 
        Uns32 value;
        struct {
            unsigned TOE : 1;
            unsigned EXT : 1;
        } bits;
    } DACINTC1;
    union { 
        Uns32 value;
        struct {
            unsigned INT : 16;
        } bits;
    } DACINT1;
    union { 
        Uns32 value;
        struct {
            unsigned POEN : 8;
        } bits;
    } POEN;
    union { 
        Uns32 value;
        struct {
            unsigned DLY2 : 16;
            unsigned DLY1 : 16;
        } bits;
    } PO0DLY;
    union { 
        Uns32 value;
        struct {
            unsigned DLY2 : 16;
            unsigned DLY1 : 16;
        } bits;
    } PO1DLY;
    union { 
        Uns32 value;
        struct {
            unsigned DLY2 : 16;
            unsigned DLY1 : 16;
        } bits;
    } PO2DLY;
    union { 
        Uns32 value;
        struct {
            unsigned DLY2 : 16;
            unsigned DLY1 : 16;
        } bits;
    } PO3DLY;
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
