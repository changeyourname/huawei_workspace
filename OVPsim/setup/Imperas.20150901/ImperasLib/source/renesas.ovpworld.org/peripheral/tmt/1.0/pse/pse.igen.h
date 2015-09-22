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

typedef struct TMTP0_reg0_dataS { 
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
    union { 
        Uns8 value;
        struct {
            unsigned UDS : 2;
            unsigned ECM : 2;
            unsigned LDE : 1;
            unsigned __pad5 : 2;
            unsigned ECC : 1;
        } bits;
    } CTL2;
    union { 
        Uns8 value;
        struct {
            unsigned OE0 : 1;
            unsigned OL0 : 1;
            unsigned OE1 : 1;
            unsigned OL1 : 1;
        } bits;
    } IOC0;
    union { 
        Uns8 value;
        struct {
            unsigned IS : 4;
        } bits;
    } IOC1;
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
            unsigned EIS : 2;
            unsigned ECS : 2;
            unsigned ACL : 1;
            unsigned BCL : 1;
            unsigned ZCL : 1;
            unsigned SCE : 1;
        } bits;
    } IOC3;
    union { 
        Uns8 value;
        struct {
            unsigned OVF : 1;
            unsigned __pad1 : 3;
            unsigned CCS : 2;
        } bits;
    } OPT0;
    union { 
        Uns8 value;
        struct {
            unsigned ESF : 1;
            unsigned EOF : 1;
            unsigned EUF : 1;
        } bits;
    } OPT1;
    union { 
        Uns8 value;
        struct {
            unsigned RSF : 1;
        } bits;
    } OPT2;
} TMTP0_reg0_dataT, *TMTP0_reg0_dataTP;

typedef struct TMTP0_reg1_dataS { 
    union { 
        Uns16 value;
    } CCR0;
    union { 
        Uns16 value;
    } CCR1;
    union { 
        Uns16 value;
    } CNT;
} TMTP0_reg1_dataT, *TMTP0_reg1_dataTP;

typedef struct TMTP1_reg0_dataS { 
    union { 
        Uns16 value;
    } TCW;
} TMTP1_reg0_dataT, *TMTP1_reg0_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern TMTP0_reg0_dataT TMTP0_reg0_data;

extern TMTP0_reg1_dataT TMTP0_reg1_data;

extern TMTP1_reg0_dataT TMTP1_reg0_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *TMTP0;
    void                 *TMTP1;
    ppmNetHandle          TOT0;
    ppmNetHandle          TOT1;
    ppmNetHandle          TTTTO0;
    ppmNetHandle          TTTT01;
    ppmNetHandle          TTTICC0;
    ppmNetHandle          TTTICC1;
    ppmNetHandle          TTTEQC0;
    ppmNetHandle          TTTEQC1;
    ppmNetHandle          INTTTCC0;
    ppmNetHandle          INTTTCC1;
    ppmNetHandle          INTTTOV;
    ppmNetHandle          INTTTEC;
    ppmNetHandle          TIT0;
    ppmNetHandle          TIT1;
    ppmNetHandle          TEVTT;
    ppmNetHandle          TTRGT;
    ppmNetHandle          TENCT0;
    ppmNetHandle          TENCT1;
    ppmNetHandle          TECRT;
    ppmNetHandle          TTTTI0;
    ppmNetHandle          TTTTI1;
    ppmNetHandle          TTTENC0;
    ppmNetHandle          TTTENC1;
    ppmNetHandle          TTTTRG;
    ppmNetHandle          TTTEVT;
    ppmNetHandle          TTTECR;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_TECRT);
PPM_NET_CB(P_TENCT0);
PPM_NET_CB(P_TENCT1);
PPM_NET_CB(P_TEVTT);
PPM_NET_CB(P_TIT0);
PPM_NET_CB(P_TIT1);
PPM_NET_CB(P_TTRGT);
PPM_NET_CB(P_TTTECR);
PPM_NET_CB(P_TTTENC0);
PPM_NET_CB(P_TTTENC1);
PPM_NET_CB(P_TTTEVT);
PPM_NET_CB(P_TTTTI0);
PPM_NET_CB(P_TTTTI1);
PPM_NET_CB(P_TTTTRG);
PPM_REG_READ_CB(readCNT);
PPM_REG_WRITE_CB(writeCCR0);
PPM_REG_WRITE_CB(writeCCR1);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeCTL2);
PPM_REG_WRITE_CB(writeIOC0);
PPM_REG_WRITE_CB(writeIOC1);
PPM_REG_WRITE_CB(writeIOC2);
PPM_REG_WRITE_CB(writeIOC3);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeOPT1);
PPM_REG_WRITE_CB(writeOPT2);
PPM_REG_WRITE_CB(writeTCW);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
