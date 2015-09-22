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
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS0;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS0;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS1;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS1;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS2;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS2;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS3;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS3;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS4;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS4;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS5;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS5;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS6;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS6;
    union { 
        Uns32 value;
        struct {
            unsigned M0 : 3;
            unsigned __pad3 : 1;
            unsigned M1 : 3;
            unsigned __pad7 : 1;
            unsigned M2 : 3;
            unsigned __pad11 : 1;
            unsigned M3 : 3;
            unsigned __pad15 : 1;
            unsigned M4 : 3;
            unsigned __pad19 : 1;
            unsigned M5 : 3;
            unsigned __pad23 : 1;
            unsigned M6 : 3;
            unsigned __pad27 : 1;
            unsigned M7 : 3;
        } bits;
    } PRS7;
    union { 
        Uns32 value;
        struct {
            unsigned PARK : 3;
            unsigned __pad3 : 1;
            unsigned PCTL : 2;
            unsigned __pad6 : 2;
            unsigned ARB : 2;
            unsigned __pad10 : 20;
            unsigned HLP : 1;
            unsigned RO : 1;
        } bits;
    } CRS7;
    union { 
        Uns32 value;
        struct {
            unsigned AULB : 3;
        } bits;
    } MGPCR0;
    union { 
        Uns32 value;
        struct {
            unsigned AULB : 3;
        } bits;
    } MGPCR1;
    union { 
        Uns32 value;
        struct {
            unsigned AULB : 3;
        } bits;
    } MGPCR2;
    union { 
        Uns32 value;
        struct {
            unsigned AULB : 3;
        } bits;
    } MGPCR3;
    union { 
        Uns32 value;
        struct {
            unsigned AULB : 3;
        } bits;
    } MGPCR6;
    union { 
        Uns32 value;
        struct {
            unsigned AULB : 3;
        } bits;
    } MGPCR7;
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
