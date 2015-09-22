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
            unsigned __pad0 : 16;
            unsigned BA : 16;
        } bits;
    } CSAR0;
    union { 
        Uns32 value;
        struct {
            unsigned V : 1;
            unsigned __pad1 : 7;
            unsigned WP : 1;
            unsigned __pad9 : 7;
            unsigned BAM : 16;
        } bits;
    } CSMR0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BSTW : 1;
            unsigned BSTR : 1;
            unsigned BEM : 1;
            unsigned PS : 2;
            unsigned AA : 1;
            unsigned BLS : 1;
            unsigned WS : 6;
            unsigned WRAH : 2;
            unsigned RDAH : 2;
            unsigned ASET : 2;
            unsigned EXTS : 1;
            unsigned SWSEN : 1;
            unsigned __pad24 : 2;
            unsigned SWS : 6;
        } bits;
    } CSCR0;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned BA : 16;
        } bits;
    } CSAR1;
    union { 
        Uns32 value;
        struct {
            unsigned V : 1;
            unsigned __pad1 : 7;
            unsigned WP : 1;
            unsigned __pad9 : 7;
            unsigned BAM : 16;
        } bits;
    } CSMR1;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BSTW : 1;
            unsigned BSTR : 1;
            unsigned BEM : 1;
            unsigned PS : 2;
            unsigned AA : 1;
            unsigned BLS : 1;
            unsigned WS : 6;
            unsigned WRAH : 2;
            unsigned RDAH : 2;
            unsigned ASET : 2;
            unsigned EXTS : 1;
            unsigned SWSEN : 1;
            unsigned __pad24 : 2;
            unsigned SWS : 6;
        } bits;
    } CSCR1;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned BA : 16;
        } bits;
    } CSAR2;
    union { 
        Uns32 value;
        struct {
            unsigned V : 1;
            unsigned __pad1 : 7;
            unsigned WP : 1;
            unsigned __pad9 : 7;
            unsigned BAM : 16;
        } bits;
    } CSMR2;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BSTW : 1;
            unsigned BSTR : 1;
            unsigned BEM : 1;
            unsigned PS : 2;
            unsigned AA : 1;
            unsigned BLS : 1;
            unsigned WS : 6;
            unsigned WRAH : 2;
            unsigned RDAH : 2;
            unsigned ASET : 2;
            unsigned EXTS : 1;
            unsigned SWSEN : 1;
            unsigned __pad24 : 2;
            unsigned SWS : 6;
        } bits;
    } CSCR2;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned BA : 16;
        } bits;
    } CSAR3;
    union { 
        Uns32 value;
        struct {
            unsigned V : 1;
            unsigned __pad1 : 7;
            unsigned WP : 1;
            unsigned __pad9 : 7;
            unsigned BAM : 16;
        } bits;
    } CSMR3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BSTW : 1;
            unsigned BSTR : 1;
            unsigned BEM : 1;
            unsigned PS : 2;
            unsigned AA : 1;
            unsigned BLS : 1;
            unsigned WS : 6;
            unsigned WRAH : 2;
            unsigned RDAH : 2;
            unsigned ASET : 2;
            unsigned EXTS : 1;
            unsigned SWSEN : 1;
            unsigned __pad24 : 2;
            unsigned SWS : 6;
        } bits;
    } CSCR3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned BA : 16;
        } bits;
    } CSAR4;
    union { 
        Uns32 value;
        struct {
            unsigned V : 1;
            unsigned __pad1 : 7;
            unsigned WP : 1;
            unsigned __pad9 : 7;
            unsigned BAM : 16;
        } bits;
    } CSMR4;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BSTW : 1;
            unsigned BSTR : 1;
            unsigned BEM : 1;
            unsigned PS : 2;
            unsigned AA : 1;
            unsigned BLS : 1;
            unsigned WS : 6;
            unsigned WRAH : 2;
            unsigned RDAH : 2;
            unsigned ASET : 2;
            unsigned EXTS : 1;
            unsigned SWSEN : 1;
            unsigned __pad24 : 2;
            unsigned SWS : 6;
        } bits;
    } CSCR4;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned BA : 16;
        } bits;
    } CSAR5;
    union { 
        Uns32 value;
        struct {
            unsigned V : 1;
            unsigned __pad1 : 7;
            unsigned WP : 1;
            unsigned __pad9 : 7;
            unsigned BAM : 16;
        } bits;
    } CSMR5;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BSTW : 1;
            unsigned BSTR : 1;
            unsigned BEM : 1;
            unsigned PS : 2;
            unsigned AA : 1;
            unsigned BLS : 1;
            unsigned WS : 6;
            unsigned WRAH : 2;
            unsigned RDAH : 2;
            unsigned ASET : 2;
            unsigned EXTS : 1;
            unsigned SWSEN : 1;
            unsigned __pad24 : 2;
            unsigned SWS : 6;
        } bits;
    } CSCR5;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 12;
            unsigned GROUP5 : 4;
            unsigned GROUP4 : 4;
            unsigned GROUP3 : 4;
            unsigned GROUP2 : 4;
            unsigned GROUP1 : 4;
        } bits;
    } CSPMCR;
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
