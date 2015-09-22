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
            unsigned WUPE0 : 2;
            unsigned WUPE1 : 2;
            unsigned WUPE2 : 2;
            unsigned WUPE3 : 2;
        } bits;
    } PE1;
    union { 
        Uns8 value;
        struct {
            unsigned WUPE4 : 2;
            unsigned WUPE5 : 2;
            unsigned WUPE6 : 2;
            unsigned WUPE7 : 2;
        } bits;
    } PE2;
    union { 
        Uns8 value;
        struct {
            unsigned WUPE8 : 2;
            unsigned WUPE9 : 2;
            unsigned WUPE10 : 2;
            unsigned WUPE11 : 2;
        } bits;
    } PE3;
    union { 
        Uns8 value;
        struct {
            unsigned WUPE12 : 2;
            unsigned WUPE13 : 2;
            unsigned WUPE14 : 2;
            unsigned WUPE15 : 2;
        } bits;
    } PE4;
    union { 
        Uns8 value;
        struct {
            unsigned WUME0 : 1;
            unsigned WUME1 : 1;
            unsigned WUME2 : 1;
            unsigned WUME3 : 1;
            unsigned WUME4 : 1;
            unsigned WUME5 : 1;
            unsigned WUME6 : 1;
            unsigned WUME7 : 1;
        } bits;
    } ME;
    union { 
        Uns8 value;
        struct {
            unsigned WUF0 : 1;
            unsigned WUF1 : 1;
            unsigned WUF2 : 1;
            unsigned WUF3 : 1;
            unsigned WUF4 : 1;
            unsigned WUF5 : 1;
            unsigned WUF6 : 1;
            unsigned WUF7 : 1;
        } bits;
    } F1;
    union { 
        Uns8 value;
        struct {
            unsigned WUF8 : 1;
            unsigned WUF9 : 1;
            unsigned WUF10 : 1;
            unsigned WUF11 : 1;
            unsigned WUF12 : 1;
            unsigned WUF13 : 1;
            unsigned WUF14 : 1;
            unsigned WUF15 : 1;
        } bits;
    } F2;
    union { 
        Uns8 value;
        struct {
            unsigned MWUF0 : 1;
            unsigned MWUF1 : 1;
            unsigned MWUF2 : 1;
            unsigned MWUF3 : 1;
            unsigned MWUF4 : 1;
            unsigned MWUF5 : 1;
            unsigned MWUF6 : 1;
            unsigned MWUF7 : 1;
        } bits;
    } F3;
    union { 
        Uns8 value;
        struct {
            unsigned FILTSEL : 4;
            unsigned __pad4 : 1;
            unsigned FILTE : 2;
            unsigned FILTF : 1;
        } bits;
    } FILT1;
    union { 
        Uns8 value;
        struct {
            unsigned FILTSEL : 4;
            unsigned __pad4 : 1;
            unsigned FILTE : 2;
            unsigned FILTF : 1;
        } bits;
    } FILT2;
    union { 
        Uns8 value;
        struct {
            unsigned RSTFILT : 1;
            unsigned LLRSTE : 1;
        } bits;
    } RST;
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
