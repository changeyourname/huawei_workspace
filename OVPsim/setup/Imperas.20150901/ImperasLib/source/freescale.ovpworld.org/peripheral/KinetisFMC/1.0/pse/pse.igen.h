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
            unsigned M0AP : 2;
            unsigned M1AP : 2;
            unsigned M2AP : 2;
            unsigned M3AP : 2;
            unsigned M4AP : 2;
            unsigned M5AP : 2;
            unsigned M6AP : 2;
            unsigned M7AP : 2;
            unsigned M0PFD : 1;
            unsigned M1PFD : 1;
            unsigned M2PFD : 1;
            unsigned M3PFD : 1;
            unsigned M4PFD : 1;
            unsigned M5PFD : 1;
            unsigned M6PFD : 1;
            unsigned M7PFD : 1;
        } bits;
    } PFAPR;
    union { 
        Uns32 value;
        struct {
            unsigned B01SEBE : 1;
            unsigned B01IPE : 1;
            unsigned B01DPE : 1;
            unsigned B01ICE : 1;
            unsigned B01DCE : 1;
            unsigned CRC : 3;
            unsigned __pad8 : 9;
            unsigned B01MW : 2;
            unsigned S_B_INV : 1;
            unsigned CINV_WAY : 4;
            unsigned CLCK_WAY : 4;
            unsigned B01RWSC : 4;
        } bits;
    } PFB01CR;
    union { 
        Uns32 value;
        struct {
            unsigned B23SEBE : 1;
            unsigned B23IPE : 1;
            unsigned B23DPE : 1;
            unsigned B23ICE : 1;
            unsigned B23DCE : 1;
            unsigned __pad5 : 12;
            unsigned B23MW : 2;
            unsigned __pad19 : 9;
            unsigned B23RWSC : 4;
        } bits;
    } PFB23CR;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW0S0;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW0S1;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW0S2;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW0S3;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW1S0;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW1S1;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW1S2;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW1S3;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW2S0;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW2S1;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW2S2;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW2S3;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW3S0;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW3S1;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW3S2;
    union { 
        Uns32 value;
        struct {
            unsigned valid : 1;
            unsigned __pad1 : 5;
            unsigned tag : 14;
        } bits;
    } TAGVDW3S3;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S0UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S0MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S0ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S0LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S1UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S1MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S1ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S1LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S2UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S2MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S2ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S2LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S3UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S3MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S3ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW0S3LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S0UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S0MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S0ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S0LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S1UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S1MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S1ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S1LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S2UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S2MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S2ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S2LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S3UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S3MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S3ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW1S3LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S0UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S0MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S0ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S0LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S1UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S1MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S1ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S1LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S2UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S2MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S2ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S2LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S3UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S3MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S3ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW2S3LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S0UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S0MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S0ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S0LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S1UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S1MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S1ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S1LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S2UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S2MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S2ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S2LM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S3UM;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S3MU;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S3ML;
    union { 
        Uns32 value;
        struct {
            unsigned data : 32;
        } bits;
    } DATAW3S3LM;
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
