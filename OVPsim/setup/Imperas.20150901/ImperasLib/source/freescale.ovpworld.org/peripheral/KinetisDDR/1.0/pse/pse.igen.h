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
            unsigned START : 1;
            unsigned __pad1 : 7;
            unsigned DDRCLS : 4;
            unsigned __pad12 : 4;
            unsigned VERSION : 16;
        } bits;
    } CR00;
    union { 
        Uns32 value;
        struct {
            unsigned MAXROW : 5;
            unsigned __pad5 : 3;
            unsigned MAXCOL : 4;
            unsigned __pad12 : 4;
            unsigned CSMAX : 2;
        } bits;
    } CR01;
    union { 
        Uns32 value;
        struct {
            unsigned TINIT : 24;
            unsigned INITAREF : 4;
        } bits;
    } CR02;
    union { 
        Uns32 value;
        struct {
            unsigned LATLIN : 4;
            unsigned __pad4 : 4;
            unsigned LATGATE : 4;
            unsigned __pad12 : 4;
            unsigned WRLAT : 4;
            unsigned __pad20 : 4;
            unsigned TCCD : 5;
        } bits;
    } CR03;
    union { 
        Uns32 value;
        struct {
            unsigned TBINT : 3;
            unsigned __pad3 : 5;
            unsigned TRRD : 3;
            unsigned __pad11 : 5;
            unsigned TRC : 6;
            unsigned __pad22 : 2;
            unsigned TRASMIN : 8;
        } bits;
    } CR04;
    union { 
        Uns32 value;
        struct {
            unsigned TWTR : 4;
            unsigned __pad4 : 4;
            unsigned TRP : 4;
            unsigned __pad12 : 4;
            unsigned TRTP : 3;
            unsigned __pad19 : 5;
            unsigned TMRD : 5;
        } bits;
    } CR05;
    union { 
        Uns32 value;
        struct {
            unsigned TMOD : 8;
            unsigned TRASMAX : 16;
            unsigned INTWBR : 1;
        } bits;
    } CR06;
    union { 
        Uns32 value;
        struct {
            unsigned CLKPW : 3;
            unsigned __pad3 : 5;
            unsigned TCKESR : 5;
            unsigned __pad13 : 3;
            unsigned AP : 1;
            unsigned __pad17 : 7;
            unsigned CCAPEN : 1;
        } bits;
    } CR07;
    union { 
        Uns32 value;
        struct {
            unsigned TRAS : 1;
            unsigned __pad1 : 7;
            unsigned TRASDI : 8;
            unsigned TWR : 5;
            unsigned __pad21 : 3;
            unsigned TDAL : 5;
        } bits;
    } CR08;
    union { 
        Uns32 value;
        struct {
            unsigned TDLL : 16;
            unsigned NOCMD : 1;
            unsigned __pad17 : 7;
            unsigned BSTLEN : 3;
        } bits;
    } CR09;
    union { 
        Uns32 value;
        struct {
            unsigned TFAW : 6;
            unsigned __pad6 : 2;
            unsigned TCPD : 16;
            unsigned TRPAB : 4;
        } bits;
    } CR10;
    union { 
        Uns32 value;
        struct {
            unsigned REGDIMM : 1;
            unsigned __pad1 : 7;
            unsigned AREF : 1;
            unsigned __pad9 : 7;
            unsigned AREFMODE : 1;
            unsigned __pad17 : 7;
            unsigned TREFEN : 1;
        } bits;
    } CR11;
    union { 
        Uns32 value;
        struct {
            unsigned TRFC : 10;
            unsigned __pad10 : 6;
            unsigned TREF : 14;
        } bits;
    } CR12;
    union { 
        Uns32 value;
        struct {
            unsigned TREFINT : 14;
            unsigned __pad14 : 2;
            unsigned PD : 1;
        } bits;
    } CR13;
    union { 
        Uns32 value;
        struct {
            unsigned TPDEX : 16;
            unsigned TXSR : 16;
        } bits;
    } CR14;
    union { 
        Uns32 value;
        struct {
            unsigned TXSNR : 16;
            unsigned SREF : 1;
            unsigned __pad17 : 7;
            unsigned PUREF : 1;
        } bits;
    } CR15;
    union { 
        Uns32 value;
        struct {
            unsigned QKREF : 1;
            unsigned __pad1 : 7;
            unsigned CLKDLY : 3;
            unsigned __pad11 : 5;
            unsigned LPCTRL : 5;
        } bits;
    } CR16;
    union { 
        Uns32 value;
        struct {
            unsigned LPPDCNT : 16;
            unsigned LPRFCNT : 16;
        } bits;
    } CR17;
    union { 
        Uns32 value;
        struct {
            unsigned LPEXTCNT : 16;
            unsigned LPAUTO : 5;
        } bits;
    } CR18;
    union { 
        Uns32 value;
        struct {
            unsigned LPINTCNT : 16;
            unsigned LPRFHOLD : 16;
        } bits;
    } CR19;
    union { 
        Uns32 value;
        struct {
            unsigned LPRE : 2;
            unsigned __pad2 : 6;
            unsigned CKSRE : 4;
            unsigned __pad12 : 4;
            unsigned CKSRX : 4;
            unsigned __pad20 : 4;
            unsigned WRMD : 1;
        } bits;
    } CR20;
    union { 
        Uns32 value;
        struct {
            unsigned MR0DAT0 : 16;
            unsigned MR1DAT0 : 16;
        } bits;
    } CR21;
    union { 
        Uns32 value;
        struct {
            unsigned MR2DATA0 : 16;
            unsigned MR3DAT0 : 16;
        } bits;
    } CR22;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR23;
    union { 
        Uns32 value;
    } CR24;
    union { 
        Uns32 value;
        struct {
            unsigned BNK8 : 1;
            unsigned __pad1 : 7;
            unsigned ADDPINS : 3;
            unsigned __pad11 : 5;
            unsigned COLSIZ : 3;
            unsigned __pad19 : 5;
            unsigned APREBIT : 4;
        } bits;
    } CR25;
    union { 
        Uns32 value;
        struct {
            unsigned AGECNT : 8;
            unsigned CMDAGE : 8;
            unsigned ADDCOL : 1;
            unsigned __pad17 : 7;
            unsigned BNKSPT : 1;
        } bits;
    } CR26;
    union { 
        Uns32 value;
        struct {
            unsigned PLEN : 1;
            unsigned __pad1 : 7;
            unsigned PRIEN : 1;
            unsigned __pad9 : 7;
            unsigned RWEN : 1;
            unsigned __pad17 : 7;
            unsigned SWPEN : 1;
        } bits;
    } CR27;
    union { 
        Uns32 value;
        struct {
            unsigned CSMAP : 1;
            unsigned __pad1 : 7;
            unsigned REDUC : 1;
            unsigned __pad9 : 7;
            unsigned BIGEND : 1;
            unsigned __pad17 : 7;
            unsigned CMDLATR : 1;
        } bits;
    } CR28;
    union { 
        Uns32 value;
        struct {
            unsigned WRLATR : 1;
            unsigned __pad1 : 7;
            unsigned FSTWR : 1;
            unsigned __pad9 : 7;
            unsigned QFULL : 2;
            unsigned __pad18 : 6;
            unsigned RESYNC : 1;
        } bits;
    } CR29;
    union { 
        Uns32 value;
        struct {
            unsigned RSYNCRF : 1;
            unsigned __pad1 : 7;
            unsigned INTSTAT : 9;
            unsigned __pad17 : 7;
            unsigned INTACK : 8;
        } bits;
    } CR30;
    union { 
        Uns32 value;
        struct {
            unsigned INTMASK : 9;
        } bits;
    } CR31;
    union { 
        Uns32 value;
        struct {
            unsigned OORAD : 32;
        } bits;
    } CR32;
    union { 
        Uns32 value;
        struct {
            unsigned OORLEN : 10;
            unsigned __pad10 : 6;
            unsigned OORTYP : 6;
            unsigned __pad22 : 2;
            unsigned OORID : 2;
        } bits;
    } CR33;
    union { 
        Uns32 value;
        struct {
            unsigned ODTRDC : 1;
            unsigned __pad1 : 7;
            unsigned ODTWRCS : 1;
        } bits;
    } CR34;
    union { 
        Uns32 value;
        struct {
            unsigned R2WSMCS : 4;
            unsigned __pad4 : 4;
            unsigned W2RSMCS : 4;
        } bits;
    } CR35;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR36;
    union { 
        Uns32 value;
        struct {
            unsigned R2RSAME : 3;
            unsigned __pad3 : 5;
            unsigned R2WSAME : 3;
            unsigned __pad11 : 5;
            unsigned W2RSAME : 3;
            unsigned __pad19 : 5;
            unsigned W2WSAME : 3;
        } bits;
    } CR37;
    union { 
        Uns32 value;
        struct {
            unsigned PDNCS : 5;
            unsigned __pad5 : 3;
            unsigned PUPCS : 5;
            unsigned __pad13 : 3;
            unsigned PWRCNT : 11;
        } bits;
    } CR38;
    union { 
        Uns32 value;
        struct {
            unsigned P0RDCNT : 11;
            unsigned __pad11 : 5;
            unsigned RP0 : 2;
            unsigned __pad18 : 6;
            unsigned WP0 : 2;
        } bits;
    } CR39;
    union { 
        Uns32 value;
        struct {
            unsigned P0TYP : 2;
            unsigned __pad2 : 6;
            unsigned P1WRCNT : 11;
        } bits;
    } CR40;
    union { 
        Uns32 value;
        struct {
            unsigned P1RDCNT : 11;
            unsigned __pad11 : 5;
            unsigned RP1 : 2;
            unsigned __pad18 : 6;
            unsigned WP1 : 2;
        } bits;
    } CR41;
    union { 
        Uns32 value;
        struct {
            unsigned P1TYP : 2;
            unsigned __pad2 : 6;
            unsigned P2WRCNT : 11;
        } bits;
    } CR42;
    union { 
        Uns32 value;
        struct {
            unsigned P2RDCNT : 11;
            unsigned __pad11 : 5;
            unsigned RP2 : 2;
            unsigned __pad18 : 6;
            unsigned WP2 : 2;
        } bits;
    } CR43;
    union { 
        Uns32 value;
        struct {
            unsigned P2TYP : 2;
            unsigned __pad2 : 6;
            unsigned WRRLAT : 1;
            unsigned __pad9 : 7;
            unsigned WRRSHARE : 1;
            unsigned __pad17 : 7;
            unsigned WRRERR : 4;
        } bits;
    } CR44;
    union { 
        Uns32 value;
        struct {
            unsigned P0PRI0 : 4;
            unsigned __pad4 : 4;
            unsigned P0PRI1 : 4;
            unsigned __pad12 : 4;
            unsigned P0PRI2 : 4;
            unsigned __pad20 : 4;
            unsigned P0PRI3 : 4;
        } bits;
    } CR45;
    union { 
        Uns32 value;
        struct {
            unsigned P0ORD : 2;
            unsigned __pad2 : 6;
            unsigned P0PRIRLX : 10;
            unsigned __pad18 : 6;
            unsigned P1PRI0 : 4;
        } bits;
    } CR46;
    union { 
        Uns32 value;
        struct {
            unsigned P1PRI1 : 4;
            unsigned __pad4 : 4;
            unsigned P1PRI2 : 4;
            unsigned __pad12 : 4;
            unsigned P1PRI3 : 4;
            unsigned __pad20 : 4;
            unsigned P1ORD : 2;
        } bits;
    } CR47;
    union { 
        Uns32 value;
        struct {
            unsigned P1PRIRLX : 10;
            unsigned __pad10 : 6;
            unsigned P2PRI0 : 4;
            unsigned __pad20 : 4;
            unsigned P2PRI1 : 4;
        } bits;
    } CR48;
    union { 
        Uns32 value;
        struct {
            unsigned P2PRI2 : 4;
            unsigned __pad4 : 4;
            unsigned P2PRI3 : 4;
            unsigned __pad12 : 4;
            unsigned P2ORD : 2;
        } bits;
    } CR49;
    union { 
        Uns32 value;
        struct {
            unsigned P2PRIRLX : 10;
            unsigned __pad10 : 6;
            unsigned CLKSTATUS : 1;
        } bits;
    } CR50;
    union { 
        Uns32 value;
        struct {
            unsigned DLLRSTDLY : 16;
            unsigned DLLRADLY : 8;
            unsigned PHYWRLAT : 4;
        } bits;
    } CR51;
    union { 
        Uns32 value;
        struct {
            unsigned PYWRLTBS : 4;
            unsigned __pad4 : 4;
            unsigned PHYRDLAT : 4;
            unsigned __pad12 : 4;
            unsigned RDDATAEN : 4;
            unsigned __pad20 : 4;
            unsigned RDDTENBAS : 4;
        } bits;
    } CR52;
    union { 
        Uns32 value;
        struct {
            unsigned CLKDISCS : 1;
            unsigned __pad1 : 7;
            unsigned CRTLUPDMN : 4;
            unsigned __pad12 : 4;
            unsigned CTRLUPDMX : 14;
        } bits;
    } CR53;
    union { 
        Uns32 value;
        struct {
            unsigned PHYUPDTY0 : 14;
            unsigned __pad14 : 2;
            unsigned PHYUPDTY1 : 14;
        } bits;
    } CR54;
    union { 
        Uns32 value;
        struct {
            unsigned PHYUPDTY2 : 14;
            unsigned __pad14 : 2;
            unsigned PHYUPDTY3 : 14;
        } bits;
    } CR55;
    union { 
        Uns32 value;
        struct {
            unsigned PHYUPDRESP : 14;
            unsigned __pad14 : 2;
            unsigned RDLATADJ : 4;
            unsigned __pad20 : 4;
            unsigned WRLATADJ : 4;
        } bits;
    } CR56;
    union { 
        Uns32 value;
        struct {
            unsigned CMDDLY : 4;
            unsigned __pad4 : 4;
            unsigned CLKDISDLY : 3;
            unsigned __pad11 : 5;
            unsigned CLKENDLY : 4;
            unsigned __pad20 : 4;
            unsigned ODTALTEN : 1;
        } bits;
    } CR57;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR58;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR59;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR60;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR61;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR62;
    union { 
        Uns32 value;
        struct {
            unsigned Not_Used : 16;
            unsigned NOT_USED : 16;
        } bits;
    } CR63;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 30;
            unsigned RST : 1;
        } bits;
    } RCR;
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
