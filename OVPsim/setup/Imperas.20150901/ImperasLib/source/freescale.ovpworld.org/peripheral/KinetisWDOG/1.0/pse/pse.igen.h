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
        Uns16 value;
        struct {
            unsigned WDOGEN : 1;
            unsigned CLKSRC : 1;
            unsigned IRQRSTEN : 1;
            unsigned WINEN : 1;
            unsigned ALLOWUPDATE : 1;
            unsigned DBGEN : 1;
            unsigned STOPEN : 1;
            unsigned WAITEN : 1;
            unsigned STNDBYEN : 1;
            unsigned __pad9 : 1;
            unsigned TESTWDOG : 1;
            unsigned TESTSEL : 1;
            unsigned BYTESEL : 2;
            unsigned DISTESTWDOG : 1;
        } bits;
    } STCTRLH;
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 15;
            unsigned INTFLG : 1;
        } bits;
    } STCTRLL;
    union { 
        Uns16 value;
        struct {
            unsigned TOVALHIGH : 16;
        } bits;
    } TOVALH;
    union { 
        Uns16 value;
        struct {
            unsigned TOVALLOW : 16;
        } bits;
    } TOVALL;
    union { 
        Uns16 value;
        struct {
            unsigned WINHIGH : 16;
        } bits;
    } WINH;
    union { 
        Uns16 value;
        struct {
            unsigned WINLOW : 16;
        } bits;
    } WINL;
    union { 
        Uns16 value;
        struct {
            unsigned WDOGREFRESH : 16;
        } bits;
    } REFRESH;
    union { 
        Uns16 value;
        struct {
            unsigned WDOGUNLOCK : 16;
        } bits;
    } UNLOCK;
    union { 
        Uns16 value;
        struct {
            unsigned TIMEROUTHIGH : 16;
        } bits;
    } TMROUTH;
    union { 
        Uns16 value;
        struct {
            unsigned TIMEROUTLOW : 16;
        } bits;
    } TMROUTL;
    union { 
        Uns16 value;
        struct {
            unsigned RSTCNT : 16;
        } bits;
    } RSTCNT;
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 8;
            unsigned PRESCVAL : 3;
        } bits;
    } PRESC;
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
