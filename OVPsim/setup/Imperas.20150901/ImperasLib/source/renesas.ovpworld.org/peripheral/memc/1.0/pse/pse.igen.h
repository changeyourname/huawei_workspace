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

typedef struct MEMCP0_reg0_dataS { 
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 3;
            unsigned ME0 : 1;
            unsigned __pad4 : 3;
            unsigned ME1 : 1;
            unsigned __pad8 : 3;
            unsigned ME2 : 1;
            unsigned __pad12 : 3;
            unsigned ME3 : 1;
        } bits;
    } BCT0;
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 3;
            unsigned ME4 : 1;
            unsigned __pad4 : 3;
            unsigned ME5 : 1;
            unsigned __pad8 : 3;
            unsigned ME6 : 1;
            unsigned __pad12 : 3;
            unsigned ME7 : 1;
        } bits;
    } BCT1;
    union { 
        Uns16 value;
        struct {
            unsigned DW0 : 3;
            unsigned __pad3 : 1;
            unsigned DW1 : 3;
            unsigned __pad7 : 1;
            unsigned DW2 : 3;
            unsigned __pad11 : 1;
            unsigned DW3 : 3;
        } bits;
    } DWC0;
    union { 
        Uns16 value;
        struct {
            unsigned DW4 : 3;
            unsigned __pad3 : 1;
            unsigned DW5 : 3;
            unsigned __pad7 : 1;
            unsigned DW6 : 3;
            unsigned __pad11 : 1;
            unsigned DW7 : 3;
        } bits;
    } DWC1;
    union { 
        Uns16 value;
        struct {
            unsigned ASW0 : 1;
            unsigned AHW0 : 1;
            unsigned ASW1 : 1;
            unsigned AHW1 : 1;
            unsigned ASW2 : 1;
            unsigned AHW2 : 1;
            unsigned ASW3 : 1;
            unsigned AHW3 : 1;
            unsigned ASW4 : 1;
            unsigned AHW4 : 1;
            unsigned ASW5 : 1;
            unsigned AHW5 : 1;
            unsigned ASW6 : 1;
            unsigned AHW6 : 1;
            unsigned ASW7 : 1;
            unsigned AHW7 : 1;
        } bits;
    } AWC;
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 1;
            unsigned BC01 : 1;
            unsigned __pad2 : 1;
            unsigned BC11 : 1;
            unsigned __pad4 : 1;
            unsigned BC21 : 1;
            unsigned __pad6 : 1;
            unsigned BC31 : 1;
            unsigned __pad8 : 1;
            unsigned BC41 : 1;
            unsigned __pad10 : 1;
            unsigned BC51 : 1;
            unsigned __pad12 : 1;
            unsigned BC61 : 1;
            unsigned __pad14 : 1;
            unsigned BC71 : 1;
        } bits;
    } BCC;
} MEMCP0_reg0_dataT, *MEMCP0_reg0_dataTP;

typedef struct MEMCP0_reg1_dataS { 
    union { 
        Uns8 value;
    } DVC;
} MEMCP0_reg1_dataT, *MEMCP0_reg1_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern MEMCP0_reg0_dataT MEMCP0_reg0_data;

extern MEMCP0_reg1_dataT MEMCP0_reg1_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *MEMCP0;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(writeAWC);
PPM_REG_WRITE_CB(writeBCC);
PPM_REG_WRITE_CB(writeBCT0);
PPM_REG_WRITE_CB(writeBCT1);
PPM_REG_WRITE_CB(writeDVC);
PPM_REG_WRITE_CB(writeDWC0);
PPM_REG_WRITE_CB(writeDWC1);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
