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

typedef struct BCUP0_reg0_dataS { 
    union { 
        Uns16 value;
        struct {
            unsigned CS0 : 4;
            unsigned CS1 : 4;
            unsigned CS2 : 4;
            unsigned CS3 : 4;
        } bits;
    } CSC0;
    union { 
        Uns16 value;
        struct {
            unsigned CS7 : 4;
            unsigned CS6 : 4;
            unsigned CS5 : 4;
            unsigned CS4 : 4;
        } bits;
    } CSC1;
    union { 
        Uns16 value;
    } BPC;
    union { 
        Uns16 value;
        struct {
            unsigned BS0 : 2;
            unsigned BS1 : 2;
            unsigned BS2 : 2;
            unsigned BS3 : 2;
            unsigned BS4 : 2;
            unsigned BS5 : 2;
            unsigned BS6 : 2;
            unsigned BS7 : 2;
        } bits;
    } BSC;
    union { 
        Uns16 value;
        struct {
            unsigned BE00 : 1;
            unsigned __pad1 : 1;
            unsigned BE10 : 1;
            unsigned __pad3 : 1;
            unsigned BE20 : 1;
            unsigned __pad5 : 1;
            unsigned BE30 : 1;
            unsigned __pad7 : 1;
            unsigned BE40 : 1;
            unsigned __pad9 : 1;
            unsigned BE50 : 1;
            unsigned __pad11 : 1;
            unsigned BE60 : 1;
            unsigned __pad13 : 1;
            unsigned BE70 : 1;
        } bits;
    } BEC;
} BCUP0_reg0_dataT, *BCUP0_reg0_dataTP;

typedef struct BCUP0_reg1_dataS { 
    union { 
        Uns8 value;
    } VSWC;
} BCUP0_reg1_dataT, *BCUP0_reg1_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern BCUP0_reg0_dataT BCUP0_reg0_data;

extern BCUP0_reg1_dataT BCUP0_reg1_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *BCUP0;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(writeBEC);
PPM_REG_WRITE_CB(writeBPC);
PPM_REG_WRITE_CB(writeBSC);
PPM_REG_WRITE_CB(writeCSC1);
PPM_REG_WRITE_CB(writeCSCO);
PPM_REG_WRITE_CB(writeVSWC);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
