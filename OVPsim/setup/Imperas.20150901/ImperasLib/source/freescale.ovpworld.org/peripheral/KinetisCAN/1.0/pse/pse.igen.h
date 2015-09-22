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
            unsigned MAXMB : 7;
            unsigned __pad7 : 1;
            unsigned IDAM : 2;
            unsigned __pad10 : 2;
            unsigned AEN : 1;
            unsigned LPRIOEN : 1;
            unsigned __pad14 : 2;
            unsigned IRMQ : 1;
            unsigned SRXDIS : 1;
            unsigned DOZE : 1;
            unsigned __pad19 : 1;
            unsigned LPMACK : 1;
            unsigned WRNEN : 1;
            unsigned SLFWAK : 1;
            unsigned SUPV : 1;
            unsigned FRZACK : 1;
            unsigned SOFTRST : 1;
            unsigned WAKMSK : 1;
            unsigned NOTRDY : 1;
            unsigned HALT : 1;
            unsigned RFEN : 1;
            unsigned FRZ : 1;
            unsigned MDIS : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            unsigned PROPSEG : 3;
            unsigned LOM : 1;
            unsigned LBUF : 1;
            unsigned TSYN : 1;
            unsigned BOFFREC : 1;
            unsigned SMP : 1;
            unsigned __pad8 : 2;
            unsigned RWRNMSK : 1;
            unsigned TWRNMSK : 1;
            unsigned LPB : 1;
            unsigned CLKSRC : 1;
            unsigned ERRMSK : 1;
            unsigned BOFFMSK : 1;
            unsigned PSEG2 : 3;
            unsigned PSEG1 : 3;
            unsigned RJW : 2;
            unsigned PRESDIV : 8;
        } bits;
    } CTRL1;
    union { 
        Uns32 value;
        struct {
            unsigned TIMER : 16;
        } bits;
    } TIMER;
    union { 
        Uns32 value;
        struct {
            unsigned MG : 32;
        } bits;
    } RXMGMASK;
    union { 
        Uns32 value;
        struct {
            unsigned RX14M : 32;
        } bits;
    } RX14MASK;
    union { 
        Uns32 value;
        struct {
            unsigned RX15M : 32;
        } bits;
    } RX15MASK;
    union { 
        Uns32 value;
        struct {
            unsigned TXERRCNT : 8;
            unsigned RXERRCNT : 8;
        } bits;
    } ECR;
    union { 
        Uns32 value;
        struct {
            unsigned WAKINT : 1;
            unsigned ERRINT : 1;
            unsigned BOFFINT : 1;
            unsigned RX : 1;
            unsigned FLTCONF : 2;
            unsigned TX : 1;
            unsigned IDLE : 1;
            unsigned RXWRN : 1;
            unsigned TXWRN : 1;
            unsigned STFERR : 1;
            unsigned FRMERR : 1;
            unsigned CRCERR : 1;
            unsigned ACKERR : 1;
            unsigned BIT0ERR : 1;
            unsigned BIT1ERR : 1;
            unsigned RWRNINT : 1;
            unsigned TWRNINT : 1;
            unsigned SYNCH : 1;
        } bits;
    } ESR1;
    union { 
        Uns32 value;
        struct {
            unsigned BUFHM : 32;
        } bits;
    } IMASK2;
    union { 
        Uns32 value;
        struct {
            unsigned BUFLM : 32;
        } bits;
    } IMASK1;
    union { 
        Uns32 value;
        struct {
            unsigned BUFHI : 32;
        } bits;
    } IFLAG2;
    union { 
        Uns32 value;
        struct {
            unsigned BUF4TO0I : 5;
            unsigned BUF5I : 1;
            unsigned BUF6I : 1;
            unsigned BUF7I : 1;
            unsigned BUF31TO8I : 24;
        } bits;
    } IFLAG1;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned EACEN : 1;
            unsigned RRS : 1;
            unsigned MRP : 1;
            unsigned TASD : 5;
            unsigned RFFN : 4;
            unsigned WRMFRZ : 1;
        } bits;
    } CTRL2;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 13;
            unsigned IMB : 1;
            unsigned VPS : 1;
            unsigned __pad15 : 1;
            unsigned LPTM : 7;
        } bits;
    } ESR2;
    union { 
        Uns32 value;
        struct {
            unsigned TXCRC : 15;
            unsigned __pad15 : 1;
            unsigned MBCRC : 7;
        } bits;
    } CRCR;
    union { 
        Uns32 value;
        struct {
            unsigned FGM : 32;
        } bits;
    } RXFGMASK;
    union { 
        Uns32 value;
        struct {
            unsigned IDHIT : 9;
        } bits;
    } RXFIR;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR0;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR1;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR2;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR3;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR4;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR5;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR6;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR7;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR8;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR9;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR10;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR11;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR12;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR13;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR14;
    union { 
        Uns32 value;
        struct {
            unsigned MI : 32;
        } bits;
    } RXIMR15;
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
