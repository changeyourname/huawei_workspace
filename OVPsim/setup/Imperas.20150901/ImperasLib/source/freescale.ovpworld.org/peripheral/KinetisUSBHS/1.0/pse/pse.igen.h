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
            unsigned ID : 6;
            unsigned __pad6 : 2;
            unsigned NID : 6;
            unsigned __pad14 : 2;
            unsigned TAG : 5;
            unsigned REVISION : 4;
            unsigned VERSION : 4;
            unsigned VERSIONID : 3;
        } bits;
    } ID;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 6;
            unsigned PHYM : 3;
            unsigned SM : 2;
        } bits;
    } HWGENERAL;
    union { 
        Uns32 value;
        struct {
            unsigned HC : 1;
            unsigned NPORT : 3;
            unsigned __pad4 : 12;
            unsigned TTASY : 8;
            unsigned TTPER : 8;
        } bits;
    } HWHOST;
    union { 
        Uns32 value;
        struct {
            unsigned DC : 1;
            unsigned DEVEP : 5;
        } bits;
    } HWDEVICE;
    union { 
        Uns32 value;
        struct {
            unsigned TXBURST : 8;
            unsigned TXADD : 8;
            unsigned TXCHANADD : 8;
            unsigned __pad24 : 7;
            unsigned TXLC : 1;
        } bits;
    } HWTXBUF;
    union { 
        Uns32 value;
        struct {
            unsigned RXBURST : 8;
            unsigned RXADD : 8;
        } bits;
    } HWRXBUF;
    union { 
        Uns32 value;
        struct {
            unsigned GPTLD : 24;
        } bits;
    } GPTIMER0LD;
    union { 
        Uns32 value;
        struct {
            unsigned GPTCNT : 24;
            unsigned MODE : 1;
            unsigned __pad25 : 5;
            unsigned RST : 1;
            unsigned RUN : 1;
        } bits;
    } GPTIMER0CTL;
    union { 
        Uns32 value;
        struct {
            unsigned GPTLD : 24;
        } bits;
    } GPTIMER1LD;
    union { 
        Uns32 value;
        struct {
            unsigned GPTCNT : 24;
            unsigned MODE : 1;
            unsigned __pad25 : 5;
            unsigned RST : 1;
            unsigned RUN : 1;
        } bits;
    } GPTIMER1CTL;
    union { 
        Uns32 value;
        struct {
            unsigned BURSTMODE : 3;
        } bits;
    } SBUSCFG;
    union { 
        Uns32 value;
        struct {
            unsigned CAPLENGTH : 8;
            unsigned __pad8 : 8;
            unsigned HCIVERSION : 16;
        } bits;
    } HCIVERSION;
    union { 
        Uns32 value;
        struct {
            unsigned N_PORTS : 4;
            unsigned PPC : 1;
            unsigned __pad5 : 3;
            unsigned N_PCC : 4;
            unsigned N_CC : 4;
            unsigned PI : 1;
            unsigned __pad17 : 3;
            unsigned N_PTT : 4;
            unsigned N_TT : 4;
        } bits;
    } HCSPARAMS;
    union { 
        Uns32 value;
        struct {
            unsigned ADC : 1;
            unsigned PFL : 1;
            unsigned ASP : 1;
            unsigned __pad3 : 1;
            unsigned IST : 4;
            unsigned EECP : 8;
        } bits;
    } HCCPARAMS;
    union { 
        Uns32 value;
        struct {
            unsigned DCIVERSION : 16;
        } bits;
    } DCIVERSION;
    union { 
        Uns32 value;
        struct {
            unsigned DEN : 5;
            unsigned __pad5 : 2;
            unsigned DC : 1;
            unsigned HC : 1;
        } bits;
    } DCCPARAMS;
    union { 
        Uns32 value;
        struct {
            unsigned RS : 1;
            unsigned RST : 1;
            unsigned FS : 2;
            unsigned PSE : 1;
            unsigned ASE : 1;
            unsigned IAA : 1;
            unsigned __pad7 : 1;
            unsigned ASP : 2;
            unsigned __pad10 : 1;
            unsigned ASPE : 1;
            unsigned __pad12 : 1;
            unsigned SUTW : 1;
            unsigned ATDTW : 1;
            unsigned FS2 : 1;
            unsigned ITC : 8;
        } bits;
    } USBCMD;
    union { 
        Uns32 value;
        struct {
            unsigned UI : 1;
            unsigned UEI : 1;
            unsigned PCI : 1;
            unsigned FRI : 1;
            unsigned SEI : 1;
            unsigned AAI : 1;
            unsigned URI : 1;
            unsigned SRI : 1;
            unsigned SLI : 1;
            unsigned __pad9 : 1;
            unsigned ULPII : 1;
            unsigned __pad11 : 1;
            unsigned HCH : 1;
            unsigned RCL : 1;
            unsigned PS : 1;
            unsigned AS : 1;
            unsigned NAKI : 1;
            unsigned __pad17 : 1;
            unsigned UAI : 1;
            unsigned UPI : 1;
            unsigned __pad20 : 4;
            unsigned TI0 : 1;
            unsigned TI1 : 1;
        } bits;
    } USBSTS;
    union { 
        Uns32 value;
        struct {
            unsigned UE : 1;
            unsigned UEE : 1;
            unsigned PCE : 1;
            unsigned FRE : 1;
            unsigned SEE : 1;
            unsigned AAE : 1;
            unsigned URE : 1;
            unsigned SRE : 1;
            unsigned SLE : 1;
            unsigned __pad9 : 1;
            unsigned ULPIE : 1;
            unsigned __pad11 : 5;
            unsigned NAKE : 1;
            unsigned __pad17 : 1;
            unsigned UAIE : 1;
            unsigned UPIE : 1;
            unsigned __pad20 : 4;
            unsigned TIE0 : 1;
            unsigned TIE1 : 1;
        } bits;
    } USBINTR;
    union { 
        Uns32 value;
        struct {
            unsigned FRINDEX : 14;
        } bits;
    } FRINDEX;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned USBADRA : 1;
            unsigned USBADR : 7;
        } bits;
    } DEVICEADDR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned ASYBASE : 27;
        } bits;
    } ASYNCLISTADDR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned TTHA : 7;
        } bits;
    } TTCTRL;
    union { 
        Uns32 value;
        struct {
            unsigned RXPBURST : 8;
            unsigned TXPBURST : 8;
        } bits;
    } BURSTSIZE;
    union { 
        Uns32 value;
        struct {
            unsigned TXSCHOH : 7;
            unsigned __pad7 : 1;
            unsigned TXSCHHEALTH : 5;
            unsigned __pad13 : 3;
            unsigned TXFIFOTHRES : 6;
        } bits;
    } TXFILLTUNING;
    union { 
        Uns32 value;
        struct {
            unsigned ULPI_DATWR : 8;
            unsigned ULPI_DATRD : 8;
            unsigned ULPI_ADDR : 8;
            unsigned ULPI_PORT : 3;
            unsigned ULPI_SS : 1;
            unsigned __pad28 : 1;
            unsigned ULPI_RW : 1;
            unsigned ULPI_RUN : 1;
            unsigned ULPI_WU : 1;
        } bits;
    } ULPI_VIEWPORT;
    union { 
        Uns32 value;
        struct {
            unsigned EPRNE : 4;
            unsigned __pad4 : 12;
            unsigned EPTNE : 4;
        } bits;
    } ENDPTNAK;
    union { 
        Uns32 value;
        struct {
            unsigned EPRNE : 4;
            unsigned __pad4 : 12;
            unsigned EPTNE : 4;
        } bits;
    } ENDPTNAKEN;
    union { 
        Uns32 value;
    } CONFIGFLAG;
    union { 
        Uns32 value;
        struct {
            unsigned CCS : 1;
            unsigned CSC : 1;
            unsigned PE : 1;
            unsigned PEC : 1;
            unsigned OCA : 1;
            unsigned OCC : 1;
            unsigned FPR : 1;
            unsigned SUSP : 1;
            unsigned PR : 1;
            unsigned HSP : 1;
            unsigned LS : 2;
            unsigned PP : 1;
            unsigned PO : 1;
            unsigned PIC : 2;
            unsigned PTC : 4;
            unsigned WKCN : 1;
            unsigned WKDS : 1;
            unsigned WKOC : 1;
            unsigned PHCD : 1;
            unsigned PFSC : 1;
            unsigned __pad25 : 1;
            unsigned PSPD : 2;
            unsigned __pad28 : 2;
            unsigned PTS : 2;
        } bits;
    } PORTSC1;
    union { 
        Uns32 value;
        struct {
            unsigned VD : 1;
            unsigned VC : 1;
            unsigned HAAR : 1;
            unsigned OT : 1;
            unsigned DP : 1;
            unsigned IDPU : 1;
            unsigned __pad6 : 1;
            unsigned HABA : 1;
            unsigned ID : 1;
            unsigned AVV : 1;
            unsigned ASV : 1;
            unsigned BSV : 1;
            unsigned BSE : 1;
            unsigned MST : 1;
            unsigned DPS : 1;
            unsigned __pad15 : 1;
            unsigned IDIS : 1;
            unsigned AVVIS : 1;
            unsigned ASVIS : 1;
            unsigned BSVIS : 1;
            unsigned BSEIS : 1;
            unsigned MSS : 1;
            unsigned DPIS : 1;
            unsigned __pad23 : 1;
            unsigned IDIE : 1;
            unsigned AVVIE : 1;
            unsigned ASVIE : 1;
            unsigned BSVIE : 1;
            unsigned BSEIE : 1;
            unsigned MSE : 1;
            unsigned DPIE : 1;
        } bits;
    } OTGSC;
    union { 
        Uns32 value;
        struct {
            unsigned CM : 2;
            unsigned ES : 1;
            unsigned SLOM : 1;
            unsigned SDIS : 1;
            unsigned __pad5 : 7;
            unsigned TXHSD : 3;
        } bits;
    } USBMODE;
    union { 
        Uns32 value;
        struct {
            unsigned EPSETUPSTAT : 4;
        } bits;
    } EPSETUPSR;
    union { 
        Uns32 value;
        struct {
            unsigned PERB : 4;
            unsigned __pad4 : 12;
            unsigned PETB : 4;
        } bits;
    } EPPRIME;
    union { 
        Uns32 value;
        struct {
            unsigned FERB : 4;
            unsigned __pad4 : 12;
            unsigned FETB : 4;
        } bits;
    } EPFLUSH;
    union { 
        Uns32 value;
        struct {
            unsigned ERBR : 4;
            unsigned __pad4 : 12;
            unsigned ETBR : 4;
        } bits;
    } EPSR;
    union { 
        Uns32 value;
        struct {
            unsigned ERCE : 4;
            unsigned __pad4 : 12;
            unsigned ETCE : 4;
        } bits;
    } EPCOMPLETE;
    union { 
        Uns32 value;
        struct {
            unsigned RXS : 1;
            unsigned __pad1 : 1;
            unsigned RXT : 2;
            unsigned __pad4 : 3;
            unsigned RXE : 1;
            unsigned __pad8 : 8;
            unsigned TXS : 1;
            unsigned __pad17 : 1;
            unsigned TXT : 2;
            unsigned __pad20 : 3;
            unsigned TXE : 1;
        } bits;
    } EPCR0;
    union { 
        Uns32 value;
        struct {
            unsigned RXS : 1;
            unsigned RXD : 1;
            unsigned RXT : 2;
            unsigned __pad4 : 1;
            unsigned RXI : 1;
            unsigned RXR : 1;
            unsigned RXE : 1;
            unsigned __pad8 : 8;
            unsigned TXS : 1;
            unsigned TXD : 1;
            unsigned TXT : 2;
            unsigned __pad20 : 1;
            unsigned TXI : 1;
            unsigned TXR : 1;
            unsigned TXE : 1;
        } bits;
    } EPCR1;
    union { 
        Uns32 value;
        struct {
            unsigned RXS : 1;
            unsigned RXD : 1;
            unsigned RXT : 2;
            unsigned __pad4 : 1;
            unsigned RXI : 1;
            unsigned RXR : 1;
            unsigned RXE : 1;
            unsigned __pad8 : 8;
            unsigned TXS : 1;
            unsigned TXD : 1;
            unsigned TXT : 2;
            unsigned __pad20 : 1;
            unsigned TXI : 1;
            unsigned TXR : 1;
            unsigned TXE : 1;
        } bits;
    } EPCR2;
    union { 
        Uns32 value;
        struct {
            unsigned RXS : 1;
            unsigned RXD : 1;
            unsigned RXT : 2;
            unsigned __pad4 : 1;
            unsigned RXI : 1;
            unsigned RXR : 1;
            unsigned RXE : 1;
            unsigned __pad8 : 8;
            unsigned TXS : 1;
            unsigned TXD : 1;
            unsigned TXT : 2;
            unsigned __pad20 : 1;
            unsigned TXI : 1;
            unsigned TXR : 1;
            unsigned TXE : 1;
        } bits;
    } EPCR3;
    union { 
        Uns32 value;
        struct {
            unsigned WU_IE : 1;
            unsigned WU_ULPI_EN : 1;
            unsigned __pad2 : 3;
            unsigned WU_INT_CLR : 1;
        } bits;
    } USBGENCTRL;
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
