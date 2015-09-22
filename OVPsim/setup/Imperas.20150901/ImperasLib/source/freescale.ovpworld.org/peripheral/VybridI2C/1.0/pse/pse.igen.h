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
            unsigned __pad0 : 1;
            unsigned ADR : 7;
        } bits;
    } IBAD;
    union { 
        Uns8 value;
        struct {
            unsigned IBC : 8;
        } bits;
    } IBFD;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 1;
            unsigned DMAEN : 1;
            unsigned RSTA : 1;
            unsigned NOACK : 1;
            unsigned TXRX : 1;
            unsigned MSSL : 1;
            unsigned IBIE : 1;
            unsigned MDIS : 1;
        } bits;
    } IBCR;
    union { 
        Uns8 value;
        struct {
            unsigned RXAK : 1;
            unsigned IBIF : 1;
            unsigned SRW : 1;
            unsigned __pad3 : 1;
            unsigned IBAL : 1;
            unsigned IBB : 1;
            unsigned IAAS : 1;
            unsigned TCF : 1;
        } bits;
    } IBSR;
    union { 
        Uns8 value;
        struct {
            unsigned DATA : 8;
        } bits;
    } IBDR;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 7;
            unsigned BIIE : 1;
        } bits;
    } IBIC;
    union { 
        Uns8 value;
        struct {
            unsigned IPG_DEBUG_EN : 1;
            unsigned IPG_DEBUG_HALTED : 1;
        } bits;
    } IBDBG;
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

PPM_REG_WRITE_CB(BSRWrite1C);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
