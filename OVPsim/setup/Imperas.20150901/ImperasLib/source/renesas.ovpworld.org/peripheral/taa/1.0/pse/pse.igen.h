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

typedef struct TAAP0_reg0_dataS { 
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
            unsigned MD : 3;
            unsigned __pad3 : 2;
            unsigned EEE : 1;
            unsigned EST : 1;
            unsigned SYE : 1;
        } bits;
    } CTL1;
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
            unsigned OVF : 1;
            unsigned __pad1 : 3;
            unsigned CCS : 2;
        } bits;
    } OPT0;
} TAAP0_reg0_dataT, *TAAP0_reg0_dataTP;

typedef struct TAAP0_reg1_dataS { 
    union { 
        Uns16 value;
    } CCR0;
    union { 
        Uns16 value;
    } CCR1;
    union { 
        Uns16 value;
    } CNT;
} TAAP0_reg1_dataT, *TAAP0_reg1_dataTP;

typedef struct TAAP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned OR0 : 1;
            unsigned OS0 : 1;
            unsigned OR1 : 1;
            unsigned OS1 : 1;
        } bits;
    } IOC4;
    union { 
        Uns8 value;
        struct {
            unsigned CSR0 : 1;
            unsigned CSD0 : 1;
            unsigned CSE0 : 1;
            unsigned ENC0 : 1;
            unsigned CSR1 : 1;
            unsigned CSD1 : 1;
            unsigned CSE1 : 1;
            unsigned ENC1 : 1;
        } bits;
    } SVC;
} TAAP0_reg2_dataT, *TAAP0_reg2_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern TAAP0_reg0_dataT TAAP0_reg0_data;

extern TAAP0_reg1_dataT TAAP0_reg1_data;

extern TAAP0_reg2_dataT TAAP0_reg2_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *TAAP0;
    ppmNetHandle          TOAA0;
    ppmNetHandle          TOAA1;
    ppmNetHandle          INTTAAOV;
    ppmNetHandle          INTTAACC0;
    ppmNetHandle          INTTAACC1;
    ppmNetHandle          TIAA0;
    ppmNetHandle          TIAA1;
    ppmNetHandle          TTRGAA;
    ppmNetHandle          TEVTAA;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_TEVTAA);
PPM_NET_CB(P_TIAA0);
PPM_NET_CB(P_TIAA1);
PPM_NET_CB(P_TTRGAA);
PPM_REG_READ_CB(readCNT);
PPM_REG_WRITE_CB(writeCCR0);
PPM_REG_WRITE_CB(writeCCR1);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeIOC0);
PPM_REG_WRITE_CB(writeIOC1);
PPM_REG_WRITE_CB(writeIOC2);
PPM_REG_WRITE_CB(writeIOC4);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeSVC);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
