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
            unsigned DATA : 8;
            unsigned FE : 1;
            unsigned PE : 1;
            unsigned BE : 1;
            unsigned OE : 1;
        } bits;
    } dr;
    union { 
        Uns32 value;
        struct {
            unsigned FE : 1;
            unsigned PE : 1;
            unsigned BE : 1;
            unsigned OE : 1;
        } bits;
    } rsrecr;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned BUSY : 1;
            unsigned RXFE : 1;
            unsigned TXFF : 1;
            unsigned RXFF : 1;
            unsigned TXFE : 1;
        } bits;
    } fr;
    union { 
        Uns32 value;
        struct {
            unsigned DIVFRAC : 6;
        } bits;
    } fbrd;
    union { 
        Uns32 value;
        struct {
            unsigned DIVINT : 16;
        } bits;
    } ibrd;
    union { 
        Uns32 value;
        struct {
            unsigned BRK : 1;
            unsigned PEN : 1;
            unsigned EPS : 1;
            unsigned STP2 : 1;
            unsigned FEN : 1;
            unsigned WLEN : 2;
            unsigned SPS : 1;
        } bits;
    } lcrh;
    union { 
        Uns32 value;
        struct {
            unsigned UARTEN : 1;
            unsigned __pad1 : 6;
            unsigned LBE : 1;
            unsigned TXE : 1;
            unsigned RXE : 1;
        } bits;
    } ctl;
    union { 
        Uns32 value;
        struct {
            unsigned TXIFLSEL : 3;
            unsigned RXIFLSEL : 3;
        } bits;
    } ifls;
    union { 
        Uns32 value;
        struct {
            unsigned RXIM : 1;
            unsigned TXIM : 1;
            unsigned RTIM : 1;
            unsigned FEIM : 1;
            unsigned PEIM : 1;
            unsigned BEIM : 1;
            unsigned OEIM : 1;
        } bits;
    } im;
    union { 
        Uns32 value;
        struct {
            unsigned RXRIS : 1;
            unsigned TXRIS : 1;
            unsigned RTRIS : 1;
            unsigned FERIS : 1;
            unsigned PERIS : 1;
            unsigned BERIS : 1;
            unsigned OERIS : 1;
        } bits;
    } ris;
    union { 
        Uns32 value;
        struct {
            unsigned RXMIS : 1;
            unsigned TXMIS : 1;
            unsigned RTMIS : 1;
            unsigned FEMIS : 1;
            unsigned PEMIS : 1;
            unsigned BEMIS : 1;
            unsigned OEMIS : 1;
        } bits;
    } mis;
    union { 
        Uns32 value;
        struct {
            unsigned RXIC : 1;
            unsigned TXIC : 1;
            unsigned RTIC : 1;
            unsigned FEIC : 1;
            unsigned PEIC : 1;
            unsigned BEIC : 1;
            unsigned OEIC : 1;
        } bits;
    } icr;
    union { 
        Uns32 value;
    } pid0;
    union { 
        Uns32 value;
    } pid1;
    union { 
        Uns32 value;
    } pid2;
    union { 
        Uns32 value;
    } pid3;
    union { 
        Uns32 value;
    } pid4;
    union { 
        Uns32 value;
    } pid5;
    union { 
        Uns32 value;
    } pid6;
    union { 
        Uns32 value;
    } pid7;
    union { 
        Uns32 value;
    } cid0;
    union { 
        Uns32 value;
    } cid1;
    union { 
        Uns32 value;
    } cid2;
    union { 
        Uns32 value;
    } cid3;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readCTL);
PPM_REG_READ_CB(readDR);
PPM_REG_READ_CB(readICR);
PPM_REG_READ_CB(readIM);
PPM_REG_READ_CB(readMIS);
PPM_REG_READ_CB(readRIS);
PPM_REG_READ_CB(readSR);
PPM_REG_READ_CB(readSRRECR);
PPM_REG_WRITE_CB(writeCTL);
PPM_REG_WRITE_CB(writeDR);
PPM_REG_WRITE_CB(writeICR);
PPM_REG_WRITE_CB(writeIM);
PPM_REG_WRITE_CB(writeMIS);
PPM_REG_WRITE_CB(writeRIS);
PPM_REG_WRITE_CB(writeSRRECR);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
