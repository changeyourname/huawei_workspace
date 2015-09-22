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

typedef struct TMSP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned CKS : 3;
            unsigned __pad3 : 4;
            unsigned CE : 1;
        } bits;
    } CTL0;
    union { 
        Uns8 value;
        struct {
            unsigned MD : 4;
            unsigned __pad4 : 1;
            unsigned EEE : 1;
            unsigned EST : 1;
        } bits;
    } CTL1;
} TMSP0_reg0_dataT, *TMSP0_reg0_dataTP;

typedef struct TMSP0_reg1_dataS { 
    union { 
        Uns16 value;
        struct {
            unsigned OE0 : 1;
            unsigned OL0 : 1;
            unsigned OE1 : 1;
            unsigned OL1 : 1;
            unsigned OE2 : 1;
            unsigned OL2 : 1;
            unsigned OE3 : 1;
            unsigned OL3 : 1;
            unsigned OE4 : 1;
            unsigned OL4 : 1;
            unsigned OE5 : 1;
            unsigned OL5 : 1;
            unsigned OE6 : 1;
            unsigned OL6 : 1;
            unsigned OE7 : 1;
            unsigned OL7 : 1;
        } bits;
    } IOC0;
} TMSP0_reg1_dataT, *TMSP0_reg1_dataTP;

typedef struct TMSP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned ETS : 2;
            unsigned EES : 2;
        } bits;
    } IOC2;
    union { 
        Uns8 value;
        struct {
            unsigned EOC : 1;
            unsigned __pad1 : 1;
            unsigned WOC : 1;
            unsigned __pad3 : 1;
            unsigned BA : 3;
        } bits;
    } IOC4;
    union { 
        Uns8 value;
        struct {
            unsigned OVF : 1;
            unsigned CUF : 1;
            unsigned CMS : 1;
            unsigned DSE : 1;
        } bits;
    } OPT0;
    union { 
        Uns8 value;
        struct {
            unsigned IPC : 3;
            unsigned PSC : 1;
            unsigned __pad4 : 3;
            unsigned SOC : 1;
        } bits;
    } OPT4;
    union { 
        Uns8 value;
        struct {
            unsigned OPF : 3;
            unsigned TSF : 1;
            unsigned PTS : 1;
            unsigned PSS : 1;
            unsigned POT : 1;
            unsigned ADC : 1;
        } bits;
    } OPT5;
    union { 
        Uns8 value;
        struct {
            unsigned TOS : 1;
            unsigned PTC : 2;
            unsigned TDC : 1;
            unsigned PPC : 1;
            unsigned IDC : 1;
        } bits;
    } OPT7;
} TMSP0_reg2_dataT, *TMSP0_reg2_dataTP;

typedef struct TMSP0_reg3_dataS { 
    union { 
        Uns16 value;
        struct {
            unsigned ID : 5;
            unsigned RDE : 1;
            unsigned IOE : 1;
            unsigned ICE : 1;
            unsigned RBE : 1;
            unsigned RTE : 1;
        } bits;
    } OPT1;
    union { 
        Uns16 value;
        struct {
            unsigned AT00 : 1;
            unsigned AT01 : 1;
            unsigned AT02 : 1;
            unsigned AT03 : 1;
            unsigned AT04 : 1;
            unsigned AT05 : 1;
            unsigned AT06 : 1;
            unsigned AT07 : 1;
            unsigned ACC0 : 1;
            unsigned ACC1 : 1;
        } bits;
    } OPT2;
    union { 
        Uns16 value;
        struct {
            unsigned AT00 : 1;
            unsigned AT01 : 1;
            unsigned AT02 : 1;
            unsigned AT03 : 1;
            unsigned AT04 : 1;
            unsigned AT05 : 1;
            unsigned AT06 : 1;
            unsigned AT07 : 1;
            unsigned ACC2 : 1;
            unsigned ACC3 : 1;
        } bits;
    } OPT3;
    union { 
        Uns16 value;
        struct {
            unsigned RSF : 1;
            unsigned SUF : 1;
            unsigned TBF : 1;
            unsigned PEF : 1;
            unsigned PRF : 1;
            unsigned NDF : 1;
            unsigned TDF : 1;
            unsigned PTF : 1;
            unsigned PPF : 1;
        } bits;
    } OPT6;
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 1;
            unsigned DTV : 9;
        } bits;
    } DTC0;
    union { 
        Uns16 value;
        struct {
            unsigned __pad0 : 1;
            unsigned DTV : 9;
        } bits;
    } DTC1;
    union { 
        Uns16 value;
        struct {
            unsigned SP0 : 4;
            unsigned SP1 : 4;
            unsigned SP2 : 4;
            unsigned SP3 : 4;
        } bits;
    } PAT0;
    union { 
        Uns16 value;
        struct {
            unsigned SP4 : 4;
            unsigned SP5 : 4;
            unsigned SP6 : 4;
            unsigned SP7 : 4;
        } bits;
    } PAT1;
    union { 
        Uns16 value;
    } CCR0;
    union { 
        Uns16 value;
    } CCR1;
    union { 
        Uns16 value;
    } CCR2;
    union { 
        Uns16 value;
    } CCR3;
    union { 
        Uns16 value;
    } CCR4;
    union { 
        Uns16 value;
    } CCR5;
    union { 
        Uns16 value;
        struct {
            unsigned MODE : 1;
            unsigned VAL : 15;
        } bits;
    } CNT;
    union { 
        Uns16 value;
        struct {
            unsigned MODE : 1;
            unsigned SVAL : 15;
        } bits;
    } SBC;
} TMSP0_reg3_dataT, *TMSP0_reg3_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern TMSP0_reg0_dataT TMSP0_reg0_data;

extern TMSP0_reg1_dataT TMSP0_reg1_data;

extern TMSP0_reg2_dataT TMSP0_reg2_data;

extern TMSP0_reg3_dataT TMSP0_reg3_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *TMSP0;
    ppmNetHandle          TOS0;
    ppmNetHandle          TOS1;
    ppmNetHandle          TOS2;
    ppmNetHandle          TOS3;
    ppmNetHandle          TOS4;
    ppmNetHandle          TOS5;
    ppmNetHandle          TOS6;
    ppmNetHandle          TOS7;
    ppmNetHandle          TSADTRG0;
    ppmNetHandle          TSADTRG1;
    ppmNetHandle          TSAEDO;
    ppmNetHandle          TSESG;
    ppmNetHandle          TSTSF;
    ppmNetHandle          INTTSCC0;
    ppmNetHandle          INTTSCC1;
    ppmNetHandle          INTTSCC2;
    ppmNetHandle          INTTSCC3;
    ppmNetHandle          INTTSCC4;
    ppmNetHandle          INTTSCC5;
    ppmNetHandle          INTTSCD0;
    ppmNetHandle          INTTSOD;
    ppmNetHandle          INTTSOV;
    ppmNetHandle          INTTSER;
    ppmNetHandle          INTTSWN;
    ppmNetHandle          TTRGS;
    ppmNetHandle          TEVTS;
    ppmNetHandle          TAPTS0;
    ppmNetHandle          TAPTS1;
    ppmNetHandle          TAPTS2;
    ppmNetHandle          ESO;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_ESO);
PPM_NET_CB(P_TAPTS0);
PPM_NET_CB(P_TAPTS1);
PPM_NET_CB(P_TAPTS2);
PPM_NET_CB(P_TEVTS);
PPM_NET_CB(P_TTRGS);
PPM_REG_READ_CB(readCNT);
PPM_REG_READ_CB(readIOC0);
PPM_REG_READ_CB(readOPT1);
PPM_REG_READ_CB(readOPT2);
PPM_REG_READ_CB(readOPT3);
PPM_REG_READ_CB(readOPT6);
PPM_REG_READ_CB(readSBC);
PPM_REG_WRITE_CB(writeCCR0);
PPM_REG_WRITE_CB(writeCCR1);
PPM_REG_WRITE_CB(writeCCR2);
PPM_REG_WRITE_CB(writeCCR3);
PPM_REG_WRITE_CB(writeCCR4);
PPM_REG_WRITE_CB(writeCCR5);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeDTC0);
PPM_REG_WRITE_CB(writeDTC1);
PPM_REG_WRITE_CB(writeIOC0);
PPM_REG_WRITE_CB(writeIOC2);
PPM_REG_WRITE_CB(writeIOC4);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeOPT1);
PPM_REG_WRITE_CB(writeOPT2);
PPM_REG_WRITE_CB(writeOPT3);
PPM_REG_WRITE_CB(writeOPT4);
PPM_REG_WRITE_CB(writeOPT5);
PPM_REG_WRITE_CB(writeOPT6);
PPM_REG_WRITE_CB(writeOPT7);
PPM_REG_WRITE_CB(writePAT0);
PPM_REG_WRITE_CB(writePAT1);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
