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
            unsigned ID : 6;
        } bits;
    } PERID;
    union { 
        Uns8 value;
        struct {
            unsigned NID : 6;
        } bits;
    } IDCOMP;
    union { 
        Uns8 value;
        struct {
            unsigned REV : 8;
        } bits;
    } REV;
    union { 
        Uns8 value;
        struct {
            unsigned IEHOST : 1;
            unsigned __pad1 : 2;
            unsigned IRQNUM : 5;
        } bits;
    } ADDINFO;
    union { 
        Uns8 value;
        struct {
            unsigned AVBUSCHG : 1;
            unsigned __pad1 : 1;
            unsigned B_SESS_CHG : 1;
            unsigned SESSVLDCHG : 1;
            unsigned __pad4 : 1;
            unsigned LINE_STATE_CHG : 1;
            unsigned ONEMSEC : 1;
            unsigned IDCHG : 1;
        } bits;
    } OTGISTAT;
    union { 
        Uns8 value;
        struct {
            unsigned AVBUSEN : 1;
            unsigned __pad1 : 1;
            unsigned BSESSEN : 1;
            unsigned SESSVLDEN : 1;
            unsigned __pad4 : 1;
            unsigned LINESTATEEN : 1;
            unsigned ONEMSECEN : 1;
            unsigned IDEN : 1;
        } bits;
    } OTGICR;
    union { 
        Uns8 value;
        struct {
            unsigned AVBUSVLD : 1;
            unsigned __pad1 : 1;
            unsigned BSESSEND : 1;
            unsigned SESS_VLD : 1;
            unsigned __pad4 : 1;
            unsigned LINESTATESTABLE : 1;
            unsigned ONEMSECEN : 1;
            unsigned ID : 1;
        } bits;
    } OTGSTAT;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 2;
            unsigned OTGEN : 1;
            unsigned __pad3 : 1;
            unsigned DMLOW : 1;
            unsigned DPLOW : 1;
            unsigned __pad6 : 1;
            unsigned DPHIGH : 1;
        } bits;
    } OTGCTL;
    union { 
        Uns8 value;
        struct {
            unsigned USBRST : 1;
            unsigned ERROR : 1;
            unsigned SOFTOK : 1;
            unsigned TOKDNE : 1;
            unsigned SLEEP : 1;
            unsigned RESUME : 1;
            unsigned ATTACH : 1;
            unsigned STALL : 1;
        } bits;
    } ISTAT;
    union { 
        Uns8 value;
        struct {
            unsigned USBRSTEN : 1;
            unsigned ERROREN : 1;
            unsigned SOFTOKEN : 1;
            unsigned TOKDNEEN : 1;
            unsigned SLEEPEN : 1;
            unsigned RESUMEEN : 1;
            unsigned ATTACHEN : 1;
            unsigned STALLEN : 1;
        } bits;
    } INTEN;
    union { 
        Uns8 value;
        struct {
            unsigned PIDERR : 1;
            unsigned CRC5EOF : 1;
            unsigned CRC16 : 1;
            unsigned DFN8 : 1;
            unsigned BTOERR : 1;
            unsigned DMAERR : 1;
            unsigned __pad6 : 1;
            unsigned BTSERR : 1;
        } bits;
    } ERRSTAT;
    union { 
        Uns8 value;
        struct {
            unsigned PIDERREN : 1;
            unsigned CRC5EOFEN : 1;
            unsigned CRC16EN : 1;
            unsigned DFN8EN : 1;
            unsigned BTOERREN : 1;
            unsigned DMAERREN : 1;
            unsigned __pad6 : 1;
            unsigned BTSERREN : 1;
        } bits;
    } ERREN;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 2;
            unsigned ODD : 1;
            unsigned TX : 1;
            unsigned ENDP : 4;
        } bits;
    } STAT;
    union { 
        Uns8 value;
        struct {
            unsigned USBENSOFEN : 1;
            unsigned ODDRST : 1;
            unsigned RESUME : 1;
            unsigned HOSTMODEEN : 1;
            unsigned RESET : 1;
            unsigned TXSUSPENDTOKENBUSY : 1;
            unsigned SE0 : 1;
            unsigned JSTATE : 1;
        } bits;
    } CTL;
    union { 
        Uns8 value;
        struct {
            unsigned ADDR : 7;
            unsigned LSEN : 1;
        } bits;
    } ADDR;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 1;
            unsigned BDTBA : 7;
        } bits;
    } BDTPAGE1;
    union { 
        Uns8 value;
        struct {
            unsigned FRM : 8;
        } bits;
    } FRMNUML;
    union { 
        Uns8 value;
        struct {
            unsigned FRM : 3;
        } bits;
    } FRMNUMH;
    union { 
        Uns8 value;
        struct {
            unsigned TOKENENDPT : 4;
            unsigned TOKENPID : 4;
        } bits;
    } TOKEN;
    union { 
        Uns8 value;
        struct {
            unsigned CNT : 8;
        } bits;
    } SOFTHLD;
    union { 
        Uns8 value;
        struct {
            unsigned BDTBA : 8;
        } bits;
    } BDTPAGE2;
    union { 
        Uns8 value;
        struct {
            unsigned BDTBA : 8;
        } bits;
    } BDTPAGE3;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT0;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT1;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT2;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT3;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT4;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT5;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT6;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT7;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT8;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT9;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT10;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT11;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT12;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT13;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT14;
    union { 
        Uns8 value;
        struct {
            unsigned EPHSHK : 1;
            unsigned EPSTALL : 1;
            unsigned EPTXEN : 1;
            unsigned EPRXEN : 1;
            unsigned EPCTLDIS : 1;
            unsigned __pad5 : 1;
            unsigned RETRYDIS : 1;
            unsigned HOSTWOHUB : 1;
        } bits;
    } ENDPOINT15;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 6;
            unsigned PDE : 1;
            unsigned SUSP : 1;
        } bits;
    } USBCTRL;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned DMPD : 1;
            unsigned __pad5 : 1;
            unsigned DPPD : 1;
            unsigned DPPU : 1;
        } bits;
    } OBSERVE;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned DPPULLUPNONOTG : 1;
        } bits;
    } CONTROL;
    union { 
        Uns8 value;
        struct {
            unsigned USB_RESUME_INT : 1;
            unsigned SYNC_DET : 1;
            unsigned __pad2 : 3;
            unsigned USBRESMEN : 1;
            unsigned __pad6 : 1;
            unsigned USBRESET : 1;
        } bits;
    } USBTRC0;
    union { 
        Uns8 value;
        struct {
            unsigned ADJ : 8;
        } bits;
    } USBFRMADJUST;
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
