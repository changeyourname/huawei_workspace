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
            unsigned BYTE3 : 8;
            unsigned BYTE2 : 8;
        } bits;
    } CMD1;
    union { 
        Uns32 value;
        struct {
            unsigned BUSY_START : 1;
            unsigned BUFNO : 2;
            unsigned __pad3 : 5;
            unsigned CODE : 16;
            unsigned BYTE1 : 8;
        } bits;
    } CMD2;
    union { 
        Uns32 value;
        struct {
            unsigned BYTE1 : 8;
            unsigned BYTE2 : 8;
        } bits;
    } CAR;
    union { 
        Uns32 value;
        struct {
            unsigned BYTE1 : 8;
            unsigned BYTE2 : 8;
            unsigned BYTE3 : 8;
            unsigned RB0 : 1;
            unsigned RB1 : 1;
            unsigned __pad26 : 2;
            unsigned CS0 : 1;
            unsigned CS1 : 1;
        } bits;
    } RAR;
    union { 
        Uns32 value;
        struct {
            unsigned COUNT : 16;
        } bits;
    } RPT;
    union { 
        Uns32 value;
        struct {
            unsigned INC1 : 8;
            unsigned INC2 : 8;
            unsigned INC3 : 8;
        } bits;
    } RAI;
    union { 
        Uns32 value;
        struct {
            unsigned ID4 : 8;
            unsigned ID3 : 8;
            unsigned ID2 : 8;
            unsigned ID1 : 8;
        } bits;
    } SR1;
    union { 
        Uns32 value;
        struct {
            unsigned STATUS1 : 8;
            unsigned __pad8 : 16;
            unsigned ID5 : 8;
        } bits;
    } SR2;
    union { 
        Uns32 value;
        struct {
            unsigned ADDRESS : 32;
        } bits;
    } DMA1;
    union { 
        Uns32 value;
        struct {
            unsigned ACT2 : 1;
            unsigned ACT1 : 1;
            unsigned __pad2 : 7;
            unsigned OFFSET2 : 4;
            unsigned COUNT2 : 7;
            unsigned COUNT1 : 12;
        } bits;
    } DMACFG;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 1;
            unsigned ADDR2 : 11;
            unsigned __pad12 : 5;
            unsigned ADDR1 : 11;
        } bits;
    } SWAP;
    union { 
        Uns32 value;
        struct {
            unsigned SIZE : 13;
        } bits;
    } SECSZ;
    union { 
        Uns32 value;
        struct {
            unsigned PAGECNT : 4;
            unsigned AIBN : 1;
            unsigned AIAD : 1;
            unsigned BTMD : 1;
            unsigned BITWIDTH : 1;
            unsigned TIMEOUT : 5;
            unsigned IDCNT : 3;
            unsigned FAST : 1;
            unsigned ECCMODE : 3;
            unsigned DMAREQ : 1;
            unsigned ECCSRAM : 1;
            unsigned ECCAD : 9;
            unsigned STOPWERR : 1;
        } bits;
    } CFG;
    union { 
        Uns32 value;
        struct {
            unsigned ADDRESS : 32;
        } bits;
    } DMA2;
    union { 
        Uns32 value;
        struct {
            unsigned DMABN : 2;
            unsigned ECCBN : 2;
            unsigned RESBN : 2;
            unsigned __pad6 : 11;
            unsigned IDLECLR : 1;
            unsigned DONECLR : 1;
            unsigned WERRCLR : 1;
            unsigned IDLEEN : 1;
            unsigned DONEEN : 1;
            unsigned WERREN : 1;
            unsigned DMABUSY : 1;
            unsigned ECCBUSY : 1;
            unsigned RESBUSY : 1;
            unsigned CMDBUSY : 1;
            unsigned WERRNS : 1;
            unsigned __pad28 : 1;
            unsigned IDLE : 1;
            unsigned DONE : 1;
            unsigned WERR : 1;
        } bits;
    } ISR;
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
