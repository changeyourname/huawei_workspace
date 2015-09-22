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
            unsigned SBR : 5;
            unsigned __pad5 : 1;
            unsigned RXEDGIE : 1;
            unsigned LBKDIE : 1;
        } bits;
    } BDH;
    union { 
        Uns8 value;
        struct {
            unsigned SBR : 8;
        } bits;
    } BDL;
    union { 
        Uns8 value;
        struct {
            unsigned PT : 1;
            unsigned PE : 1;
            unsigned ILT : 1;
            unsigned WAKE : 1;
            unsigned M : 1;
            unsigned RSRC : 1;
            unsigned __pad6 : 1;
            unsigned LOOPS : 1;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            unsigned SBK : 1;
            unsigned RWU : 1;
            unsigned RE : 1;
            unsigned TE : 1;
            unsigned ILIE : 1;
            unsigned RIE : 1;
            unsigned TCIE : 1;
            unsigned TIE : 1;
        } bits;
    } C2;
    union { 
        Uns8 value;
        struct {
            unsigned PF : 1;
            unsigned FE : 1;
            unsigned NF : 1;
            unsigned OR : 1;
            unsigned IDLE : 1;
            unsigned RDRF : 1;
            unsigned TC : 1;
            unsigned TDRE : 1;
        } bits;
    } S1;
    union { 
        Uns8 value;
        struct {
            unsigned RAF : 1;
            unsigned LBKDE : 1;
            unsigned BRK13 : 1;
            unsigned RWUID : 1;
            unsigned RXINV : 1;
            unsigned MSBF : 1;
            unsigned RXEDGIF : 1;
            unsigned LBKDIF : 1;
        } bits;
    } S2;
    union { 
        Uns8 value;
        struct {
            unsigned PEIE : 1;
            unsigned FEIE : 1;
            unsigned NEIE : 1;
            unsigned ORIE : 1;
            unsigned TXINV : 1;
            unsigned TXDIR : 1;
            unsigned T8 : 1;
            unsigned R8 : 1;
        } bits;
    } C3;
    union { 
        Uns8 value;
        struct {
            unsigned RT : 8;
        } bits;
    } D;
    union { 
        Uns8 value;
        struct {
            unsigned MA : 8;
        } bits;
    } MA1;
    union { 
        Uns8 value;
        struct {
            unsigned MA : 8;
        } bits;
    } MA2;
    union { 
        Uns8 value;
        struct {
            unsigned BRFA : 5;
            unsigned M10 : 1;
            unsigned MAEN2 : 1;
            unsigned MAEN1 : 1;
        } bits;
    } C4;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 5;
            unsigned RDMAS : 1;
            unsigned __pad6 : 1;
            unsigned TDMAS : 1;
        } bits;
    } C5;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 6;
            unsigned PARITYE : 1;
            unsigned NOISY : 1;
        } bits;
    } ED;
    union { 
        Uns8 value;
        struct {
            unsigned TXCTSE : 1;
            unsigned TXRTSE : 1;
            unsigned TXRTSPOL : 1;
            unsigned RXRTSE : 1;
        } bits;
    } MODEM;
    union { 
        Uns8 value;
        struct {
            unsigned TNP : 2;
            unsigned IREN : 1;
        } bits;
    } IR;
    union { 
        Uns8 value;
        struct {
            unsigned RXFIFOSIZE : 3;
            unsigned RXFE : 1;
            unsigned TXFIFOSIZE : 3;
            unsigned TXFE : 1;
        } bits;
    } PFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned RXUFE : 1;
            unsigned TXOFE : 1;
            unsigned __pad2 : 4;
            unsigned RXFLUSH : 1;
            unsigned TXFLUSH : 1;
        } bits;
    } CFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned RXUF : 1;
            unsigned TXOF : 1;
            unsigned __pad2 : 4;
            unsigned RXEMPT : 1;
            unsigned TXEMPT : 1;
        } bits;
    } SFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned TXWATER : 8;
        } bits;
    } TWFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned TXCOUNT : 8;
        } bits;
    } TCFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned RXWATER : 8;
        } bits;
    } RWFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned RXCOUNT : 8;
        } bits;
    } RCFIFO;
    union { 
        Uns8 value;
        struct {
            unsigned ISO_7816E : 1;
            unsigned TTYPE : 1;
            unsigned INIT : 1;
            unsigned ANACK : 1;
            unsigned ONACK : 1;
        } bits;
    } C7816;
    union { 
        Uns8 value;
        struct {
            unsigned RXTE : 1;
            unsigned TXTE : 1;
            unsigned GTVE : 1;
            unsigned __pad3 : 1;
            unsigned INITDE : 1;
            unsigned BWTE : 1;
            unsigned CWTE : 1;
            unsigned WTE : 1;
        } bits;
    } IE7816;
    union { 
        Uns8 value;
        struct {
            unsigned RXT : 1;
            unsigned TXT : 1;
            unsigned GTV : 1;
            unsigned __pad3 : 1;
            unsigned INITD : 1;
            unsigned BWT : 1;
            unsigned CWT : 1;
            unsigned WT : 1;
        } bits;
    } IS7816;
    union { 
        Uns8 value;
        struct {
            unsigned WI : 8;
        } bits;
    } WP7816T0;
    union { 
        Uns8 value;
        struct {
            unsigned GTN : 8;
        } bits;
    } WN7816;
    union { 
        Uns8 value;
        struct {
            unsigned GTFD : 8;
        } bits;
    } WF7816;
    union { 
        Uns8 value;
        struct {
            unsigned RXTHRESHOLD : 4;
            unsigned TXTHRESHOLD : 4;
        } bits;
    } ET7816;
    union { 
        Uns8 value;
        struct {
            unsigned TLEN : 8;
        } bits;
    } TL7816;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          DirectWrite;
    ppmNetHandle          DirectRead;
    ppmNetHandle          Interrupt;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(directReadCB);
PPM_REG_READ_CB(readD);
PPM_REG_READ_CB(readS1);
PPM_NET_CB(resetCB);
PPM_REG_VIEW_CB(viewS1);
PPM_REG_WRITE_CB(writeBDH);
PPM_REG_WRITE_CB(writeBDL);
PPM_REG_WRITE_CB(writeC2);
PPM_REG_WRITE_CB(writeC4);
PPM_REG_WRITE_CB(writeCFIFO);
PPM_REG_WRITE_CB(writeD);
PPM_REG_WRITE_CB(writeRWFIFO);
PPM_REG_WRITE_CB(writeTWFIFO);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
