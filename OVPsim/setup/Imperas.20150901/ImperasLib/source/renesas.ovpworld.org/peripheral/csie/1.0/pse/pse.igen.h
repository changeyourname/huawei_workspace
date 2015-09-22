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

typedef struct CSIEP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned CSM : 1;
            unsigned WE : 1;
            unsigned SIT : 1;
            unsigned DIR : 1;
            unsigned TMS : 1;
            unsigned RXE : 1;
            unsigned TXE : 1;
            unsigned PWR : 1;
        } bits;
    } CTL0;
    union { 
        Uns8 value;
        struct {
            unsigned CKS : 3;
            unsigned DAP : 1;
            unsigned CKP : 1;
            unsigned MDL : 3;
        } bits;
    } CTL1;
} CSIEP0_reg0_dataT, *CSIEP0_reg0_dataTP;

typedef struct CSIEP0_reg1_dataS { 
    union { 
        Uns16 value;
    } RX;
    union { 
        Uns16 value;
        struct {
            unsigned CS : 4;
        } bits;
    } CS;
    union { 
        Uns16 value;
    } TX;
} CSIEP0_reg1_dataT, *CSIEP0_reg1_dataTP;

typedef struct CSIEP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned SFP : 4;
            unsigned TSF : 1;
            unsigned EMF : 1;
            unsigned FLF : 1;
            unsigned PCT : 1;
        } bits;
    } STR;
    union { 
        Uns8 value;
        struct {
            unsigned DL : 4;
            unsigned CSL : 4;
        } bits;
    } CTL2;
    union { 
        Uns8 value;
        struct {
            unsigned SFN : 4;
        } bits;
    } CTL3;
    union { 
        Uns8 value;
        struct {
            unsigned MD : 1;
            unsigned OPE : 1;
            unsigned DPA : 1;
            unsigned CPA : 1;
            unsigned CSL : 4;
        } bits;
    } CTL4;
} CSIEP0_reg2_dataT, *CSIEP0_reg2_dataTP;

typedef struct CSIEP0_reg3_dataS { 
    union { 
        Uns16 value;
    } OPT0;
    union { 
        Uns16 value;
    } OPT1;
    union { 
        Uns16 value;
    } OPT2;
    union { 
        Uns16 value;
    } OPT3;
    union { 
        Uns16 value;
    } OPT4;
    union { 
        Uns16 value;
    } OPT5;
    union { 
        Uns16 value;
    } OPT6;
    union { 
        Uns16 value;
    } OPT7;
} CSIEP0_reg3_dataT, *CSIEP0_reg3_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern CSIEP0_reg0_dataT CSIEP0_reg0_data;

extern CSIEP0_reg1_dataT CSIEP0_reg1_data;

extern CSIEP0_reg2_dataT CSIEP0_reg2_data;

extern CSIEP0_reg3_dataT CSIEP0_reg3_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *CSIEP0;
    ppmNetHandle          INTCEOF;
    ppmNetHandle          INTCEC;
    ppmNetHandle          SOE;
    ppmNetHandle          SCSE0;
    ppmNetHandle          SCSE1;
    ppmNetHandle          SCSE2;
    ppmNetHandle          SCSE3;
    ppmNetHandle          SCSE4;
    ppmNetHandle          SCSE5;
    ppmNetHandle          SCSE6;
    ppmNetHandle          SCSE7;
    ppmNetHandle          SIE;
    ppmNetHandle          SCKE;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_SCKE);
PPM_NET_CB(P_SIE);
PPM_REG_READ_CB(readRX);
PPM_REG_READ_CB(readTX);
PPM_REG_WRITE_CB(writeCS);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeCTL2);
PPM_REG_WRITE_CB(writeCTL3);
PPM_REG_WRITE_CB(writeCTL4);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeOPT1);
PPM_REG_WRITE_CB(writeOPT2);
PPM_REG_WRITE_CB(writeOPT3);
PPM_REG_WRITE_CB(writeOPT4);
PPM_REG_WRITE_CB(writeOPT5);
PPM_REG_WRITE_CB(writeOPT6);
PPM_REG_WRITE_CB(writeOPT7);
PPM_REG_WRITE_CB(writeSTR);
PPM_REG_WRITE_CB(writeTX);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
