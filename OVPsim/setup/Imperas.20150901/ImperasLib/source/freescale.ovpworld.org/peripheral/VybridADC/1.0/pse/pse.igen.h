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
            unsigned ADCH : 5;
            unsigned __pad5 : 2;
            unsigned AIEN : 1;
        } bits;
    } HC0;
    union { 
        Uns32 value;
        struct {
            unsigned ADCH : 5;
            unsigned __pad5 : 2;
            unsigned AIEN : 1;
        } bits;
    } HC1;
    union { 
        Uns32 value;
        struct {
            unsigned COCO1 : 1;
            unsigned COCO2 : 1;
        } bits;
    } HS;
    union { 
        Uns32 value;
        struct {
            unsigned D : 12;
        } bits;
    } R0;
    union { 
        Uns32 value;
        struct {
            unsigned D : 12;
        } bits;
    } R1;
    union { 
        Uns32 value;
        struct {
            unsigned ADICLK : 2;
            unsigned MODE : 2;
            unsigned ADLSMP : 1;
            unsigned ADIV : 2;
            unsigned ADLPC : 1;
            unsigned ADSTS : 2;
            unsigned ADHSC : 1;
            unsigned REFSEL : 2;
            unsigned ADTRG : 1;
            unsigned AVGS : 2;
            unsigned OVWREN : 1;
        } bits;
    } CFG;
    union { 
        Uns32 value;
        struct {
            unsigned ADACKEN : 1;
            unsigned DMAEN : 1;
            unsigned ACREN : 1;
            unsigned ACFGT : 1;
            unsigned ACFE : 1;
            unsigned AVGE : 1;
            unsigned ADCO : 1;
            unsigned CAL : 1;
        } bits;
    } GC;
    union { 
        Uns32 value;
        struct {
            unsigned ADACT : 1;
            unsigned CALF : 1;
            unsigned AWKST : 1;
        } bits;
    } GS;
    union { 
        Uns32 value;
        struct {
            unsigned CV1 : 12;
            unsigned __pad12 : 4;
            unsigned CV2 : 12;
        } bits;
    } CV;
    union { 
        Uns32 value;
        struct {
            unsigned OFS : 12;
            unsigned SIGN : 1;
        } bits;
    } OFS;
    union { 
        Uns32 value;
        struct {
            unsigned CAL_CODE : 4;
        } bits;
    } CAL;
    union { 
        Uns32 value;
        struct {
            unsigned ADPC0 : 1;
            unsigned ADPC1 : 1;
            unsigned ADPC2 : 1;
            unsigned ADPC3 : 1;
            unsigned ADPC4 : 1;
            unsigned ADPC5 : 1;
            unsigned ADPC6 : 1;
            unsigned ADPC7 : 1;
            unsigned ADPC8 : 1;
            unsigned ADPC9 : 1;
            unsigned ADPC10 : 1;
            unsigned ADPC11 : 1;
            unsigned ADPC12 : 1;
            unsigned ADPC13 : 1;
            unsigned ADPC14 : 1;
            unsigned ADPC15 : 1;
            unsigned ADPC16 : 1;
            unsigned ADPC17 : 1;
            unsigned ADPC18 : 1;
            unsigned ADPC19 : 1;
            unsigned ADPC20 : 1;
            unsigned ADPC21 : 1;
            unsigned ADPC22 : 1;
            unsigned ADPC23 : 1;
        } bits;
    } PCTL;
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

PPM_REG_WRITE_CB(GSWrite1C);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
