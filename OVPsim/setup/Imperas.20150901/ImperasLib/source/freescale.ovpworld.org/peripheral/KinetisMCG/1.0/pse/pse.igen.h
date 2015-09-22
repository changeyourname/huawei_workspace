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
            unsigned IREFSTEN : 1;
            unsigned IRCLKEN : 1;
            unsigned IREFS : 1;
            unsigned FRDIV : 3;
            unsigned CLKS : 2;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            unsigned IRCS : 1;
            unsigned LP : 1;
            unsigned EREFS0 : 1;
            unsigned HGO0 : 1;
            unsigned RANGE0 : 2;
            unsigned __pad6 : 1;
            unsigned LOCRE0 : 1;
        } bits;
    } C2;
    union { 
        Uns8 value;
        struct {
            unsigned SCTRIM : 8;
        } bits;
    } C3;
    union { 
        Uns8 value;
        struct {
            unsigned SCFTRIM : 1;
            unsigned FCTRIM : 4;
            unsigned DRST_DRS : 2;
            unsigned DMX32 : 1;
        } bits;
    } C4;
    union { 
        Uns8 value;
        struct {
            unsigned PRDIV0 : 3;
            unsigned __pad3 : 2;
            unsigned PLLSTEN0 : 1;
            unsigned PLLCLKEN0 : 1;
            unsigned PLLREFSEL0 : 1;
        } bits;
    } C5;
    union { 
        Uns8 value;
        struct {
            unsigned VDIV0 : 5;
            unsigned CME0 : 1;
            unsigned PLLS : 1;
            unsigned LOLIE0 : 1;
        } bits;
    } C6;
    union { 
        Uns8 value;
        struct {
            unsigned IRCST : 1;
            unsigned OSCINIT0 : 1;
            unsigned CLKST : 2;
            unsigned IREFST : 1;
            unsigned PLLST : 1;
            unsigned LOCK0 : 1;
            unsigned LOLS0 : 1;
        } bits;
    } S;
    union { 
        Uns8 value;
        struct {
            unsigned LOCS0 : 1;
            unsigned FCIRDIV : 3;
            unsigned FLTPRSRV : 1;
            unsigned ATMF : 1;
            unsigned ATMS : 1;
            unsigned ATME : 1;
        } bits;
    } SC;
    union { 
        Uns8 value;
        struct {
            unsigned ATCVH : 8;
        } bits;
    } ATCVH;
    union { 
        Uns8 value;
        struct {
            unsigned ATCVL : 8;
        } bits;
    } ATCVL;
    union { 
        Uns8 value;
        struct {
            unsigned OSCSEL : 1;
        } bits;
    } C7;
    union { 
        Uns8 value;
        struct {
            unsigned LOCS1 : 1;
            unsigned __pad1 : 4;
            unsigned CME1 : 1;
            unsigned __pad6 : 1;
            unsigned LOCRE1 : 1;
        } bits;
    } C8;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 2;
            unsigned EREFS1 : 1;
            unsigned HGO1 : 1;
            unsigned RANGE1 : 2;
            unsigned __pad6 : 1;
            unsigned LOCRE2 : 1;
        } bits;
    } C10;
    union { 
        Uns8 value;
        struct {
            unsigned PRDIV1 : 3;
            unsigned __pad3 : 1;
            unsigned PLLCS : 1;
            unsigned PLLSTEN1 : 1;
            unsigned PLLCLKEN1 : 1;
            unsigned PLLREFSEL1 : 1;
        } bits;
    } C11;
    union { 
        Uns8 value;
        struct {
            unsigned VDIV1 : 5;
            unsigned CME2 : 1;
            unsigned __pad6 : 1;
            unsigned LOLIE1 : 1;
        } bits;
    } C12;
    union { 
        Uns8 value;
        struct {
            unsigned LOCS2 : 1;
            unsigned OSCINIT2 : 1;
            unsigned __pad2 : 2;
            unsigned PLLCST : 1;
            unsigned __pad5 : 1;
            unsigned LOCK2 : 1;
            unsigned LOLS2 : 1;
        } bits;
    } S2;
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

PPM_REG_READ_CB(readS);
PPM_REG_VIEW_CB(viewS);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
