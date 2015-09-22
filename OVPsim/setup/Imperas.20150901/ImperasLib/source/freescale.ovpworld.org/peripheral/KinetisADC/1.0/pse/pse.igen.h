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
            unsigned DIFF : 1;
            unsigned AIEN : 1;
            unsigned COCO : 1;
        } bits;
    } SC1A;
    union { 
        Uns32 value;
        struct {
            unsigned ADCH : 5;
            unsigned DIFF : 1;
            unsigned AIEN : 1;
            unsigned COCO : 1;
        } bits;
    } SC1B;
    union { 
        Uns32 value;
        struct {
            unsigned ADICLK : 2;
            unsigned MODE : 2;
            unsigned ADLSMP : 1;
            unsigned ADIV : 2;
            unsigned ADLPC : 1;
        } bits;
    } CFG1;
    union { 
        Uns32 value;
        struct {
            unsigned ADLSTS : 2;
            unsigned ADHSC : 1;
            unsigned ADACKEN : 1;
            unsigned MUXSEL : 1;
        } bits;
    } CFG2;
    union { 
        Uns32 value;
        struct {
            unsigned D : 16;
        } bits;
    } RA;
    union { 
        Uns32 value;
        struct {
            unsigned D : 16;
        } bits;
    } RB;
    union { 
        Uns32 value;
        struct {
            unsigned CV : 16;
        } bits;
    } CV1;
    union { 
        Uns32 value;
        struct {
            unsigned CV : 16;
        } bits;
    } CV2;
    union { 
        Uns32 value;
        struct {
            unsigned REFSEL : 2;
            unsigned DMAEN : 1;
            unsigned ACREN : 1;
            unsigned ACFGT : 1;
            unsigned ACFE : 1;
            unsigned ADTRG : 1;
            unsigned ADACT : 1;
        } bits;
    } SC2;
    union { 
        Uns32 value;
        struct {
            unsigned AVGS : 2;
            unsigned AVGE : 1;
            unsigned ADCO : 1;
            unsigned __pad4 : 2;
            unsigned CALF : 1;
            unsigned CAL : 1;
        } bits;
    } SC3;
    union { 
        Uns32 value;
        struct {
            unsigned OFS : 16;
        } bits;
    } OFS;
    union { 
        Uns32 value;
        struct {
            unsigned PG : 16;
        } bits;
    } PG;
    union { 
        Uns32 value;
        struct {
            unsigned MG : 16;
        } bits;
    } MG;
    union { 
        Uns32 value;
        struct {
            unsigned CLPD : 6;
        } bits;
    } CLPD;
    union { 
        Uns32 value;
        struct {
            unsigned CLPS : 6;
        } bits;
    } CLPS;
    union { 
        Uns32 value;
        struct {
            unsigned CLP4 : 10;
        } bits;
    } CLP4;
    union { 
        Uns32 value;
        struct {
            unsigned CLP3 : 9;
        } bits;
    } CLP3;
    union { 
        Uns32 value;
        struct {
            unsigned CLP2 : 8;
        } bits;
    } CLP2;
    union { 
        Uns32 value;
        struct {
            unsigned CLP1 : 7;
        } bits;
    } CLP1;
    union { 
        Uns32 value;
        struct {
            unsigned CLP0 : 6;
        } bits;
    } CLP0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 14;
            unsigned PGAOFSM : 1;
            unsigned __pad15 : 1;
            unsigned PGAG : 4;
            unsigned PGALPb : 1;
            unsigned PGACHPb : 1;
            unsigned __pad22 : 1;
            unsigned PGAEN : 1;
        } bits;
    } PGA;
    union { 
        Uns32 value;
        struct {
            unsigned CLMD : 6;
        } bits;
    } CLMD;
    union { 
        Uns32 value;
        struct {
            unsigned CLMS : 6;
        } bits;
    } CLMS;
    union { 
        Uns32 value;
        struct {
            unsigned CLM4 : 10;
        } bits;
    } CLM4;
    union { 
        Uns32 value;
        struct {
            unsigned CLM3 : 9;
        } bits;
    } CLM3;
    union { 
        Uns32 value;
        struct {
            unsigned CLM2 : 8;
        } bits;
    } CLM2;
    union { 
        Uns32 value;
        struct {
            unsigned CLM1 : 7;
        } bits;
    } CLM1;
    union { 
        Uns32 value;
        struct {
            unsigned CLM0 : 6;
        } bits;
    } CLM0;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          AltClk;
    ppmNetHandle          HwTrig;
    ppmNetHandle          AdIn;
    ppmNetHandle          Vrefsh;
    ppmNetHandle          Vrefsl;
    ppmNetHandle          AdInId;
    ppmNetHandle          Interrupt;
    ppmNetHandle          DmaReq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(altClkCB);
PPM_NET_CB(hwTrigCB);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
