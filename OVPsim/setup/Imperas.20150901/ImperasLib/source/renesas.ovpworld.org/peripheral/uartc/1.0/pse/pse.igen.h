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

typedef struct UARTP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned SL : 1;
            unsigned CL : 1;
            unsigned PS : 2;
            unsigned DIR : 1;
            unsigned RXE : 1;
            unsigned TXE : 1;
            unsigned PWR : 1;
        } bits;
    } CTL0;
    union { 
        Uns8 value;
        struct {
            unsigned CKS : 4;
        } bits;
    } CTL1;
    union { 
        Uns8 value;
        struct {
            unsigned BRS : 8;
        } bits;
    } CTL2;
    union { 
        Uns8 value;
        struct {
            unsigned RDL : 1;
            unsigned TDL : 1;
            unsigned SLS : 3;
            unsigned STT : 1;
            unsigned SRT : 1;
            unsigned SRF : 1;
        } bits;
    } OPT0;
    union { 
        Uns8 value;
        struct {
            unsigned OVE : 1;
            unsigned FE : 1;
            unsigned PE : 1;
            unsigned __pad3 : 4;
            unsigned TSF : 1;
        } bits;
    } STR;
} UARTP0_reg0_dataT, *UARTP0_reg0_dataTP;

typedef struct UARTP0_reg1_dataS { 
    union { 
        Uns16 value;
        struct {
            unsigned RXL : 8;
            unsigned B9 : 1;
        } bits;
    } RX;
    union { 
        Uns16 value;
        struct {
            unsigned TXL : 8;
            unsigned B9 : 1;
        } bits;
    } TX;
} UARTP0_reg1_dataT, *UARTP0_reg1_dataTP;

typedef struct UARTP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned EBE : 1;
        } bits;
    } OPT1;
    union { 
        Uns8 value;
        struct {
            unsigned RSF : 1;
        } bits;
    } OPT2;
} UARTP0_reg2_dataT, *UARTP0_reg2_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern UARTP0_reg0_dataT UARTP0_reg0_data;

extern UARTP0_reg1_dataT UARTP0_reg1_data;

extern UARTP0_reg2_dataT UARTP0_reg2_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *UARTP0;
    ppmNetHandle          INTUCT;
    ppmNetHandle          INTUCR;
    ppmNetHandle          INTUCRE;
    ppmNetHandle          TXDC;
    ppmNetHandle          RXDC;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_RXDC);
PPM_REG_READ_CB(readRX);
PPM_REG_READ_CB(readTX);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeCTL2);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeOPT1);
PPM_REG_WRITE_CB(writeSTR);
PPM_REG_WRITE_CB(writeTX);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
