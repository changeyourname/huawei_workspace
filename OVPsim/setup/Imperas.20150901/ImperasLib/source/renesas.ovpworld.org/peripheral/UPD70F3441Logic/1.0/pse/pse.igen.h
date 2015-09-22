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

typedef struct LOGICP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned BRGSSR : 1;
            unsigned __pad1 : 3;
            unsigned INTSEL4 : 1;
            unsigned __pad5 : 2;
            unsigned ISR : 1;
        } bits;
    } INTSEL;
    union { 
        Uns8 value;
        struct {
            unsigned INTERR0 : 1;
            unsigned INTERR1 : 1;
            unsigned INTERR2 : 1;
            unsigned __pad3 : 4;
            unsigned INTERR7 : 1;
        } bits;
    } INTERRF;
} LOGICP0_reg0_dataT, *LOGICP0_reg0_dataTP;

typedef struct LOGICP1_reg0_dataS { 
    union { 
        Uns8 value;
    } LOGICP0;
    union { 
        Uns8 value;
    } P1;
    union { 
        Uns8 value;
    } PM1;
    union { 
        Uns8 value;
    } PMC1;
    union { 
        Uns8 value;
    } P2;
    union { 
        Uns8 value;
    } PM2;
    union { 
        Uns8 value;
    } PMC2;
    union { 
        Uns8 value;
    } P3;
    union { 
        Uns8 value;
    } PM3;
    union { 
        Uns8 value;
    } PMC3;
    union { 
        Uns8 value;
    } P4;
    union { 
        Uns8 value;
    } PM4;
    union { 
        Uns8 value;
    } PMC4;
    union { 
        Uns8 value;
    } P5;
    union { 
        Uns8 value;
    } PM5;
    union { 
        Uns8 value;
    } PMC5;
    union { 
        Uns8 value;
    } P6;
    union { 
        Uns8 value;
    } PM6;
    union { 
        Uns8 value;
    } PMC6;
    union { 
        Uns8 value;
    } P7;
    union { 
        Uns8 value;
    } PM7;
    union { 
        Uns8 value;
    } PMC7;
    union { 
        Uns8 value;
    } P8;
    union { 
        Uns8 value;
    } PM8;
    union { 
        Uns8 value;
    } PMC8;
    union { 
        Uns8 value;
    } P9;
    union { 
        Uns8 value;
    } PM9;
    union { 
        Uns8 value;
    } PMC9;
    union { 
        Uns8 value;
    } P10;
    union { 
        Uns8 value;
    } PM10;
    union { 
        Uns8 value;
    } PMC10;
    union { 
        Uns8 value;
    } P11;
    union { 
        Uns8 value;
    } PM11;
    union { 
        Uns8 value;
    } PMC11;
    union { 
        Uns8 value;
    } PFC1;
    union { 
        Uns8 value;
    } PFC2;
    union { 
        Uns8 value;
        struct {
            unsigned PFC40 : 1;
            unsigned PFC41 : 1;
        } bits;
    } PFC4;
    union { 
        Uns8 value;
    } PFC7;
    union { 
        Uns8 value;
    } PFC8;
    union { 
        Uns8 value;
    } PFC9;
    union { 
        Uns8 value;
    } PFC10;
} LOGICP1_reg0_dataT, *LOGICP1_reg0_dataTP;

typedef struct LOGICP2_reg0_dataS { 
    union { 
        Uns8 value;
    } PESC5;
    union { 
        Uns8 value;
    } ESOST5;
    union { 
        Uns8 value;
    } PESC6;
    union { 
        Uns8 value;
    } ESOST6;
    union { 
        Uns8 value;
    } PESMK5;
    union { 
        Uns8 value;
    } PESMK6;
} LOGICP2_reg0_dataT, *LOGICP2_reg0_dataTP;

typedef struct LOGICP3_reg0_dataS { 
    union { 
        Uns8 value;
    } PRCMD;
} LOGICP3_reg0_dataT, *LOGICP3_reg0_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern LOGICP0_reg0_dataT LOGICP0_reg0_data;

extern LOGICP1_reg0_dataT LOGICP1_reg0_data;

extern LOGICP2_reg0_dataT LOGICP2_reg0_data;

extern LOGICP3_reg0_dataT LOGICP3_reg0_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *LOGICP0;
    void                 *LOGICP1;
    void                 *LOGICP2;
    void                 *LOGICP3;
    ppmNetHandle          NMIIN;
    ppmNetHandle          INTDEDF;
    ppmNetHandle          INTDEDR;
    ppmNetHandle          INTDEDFR;
    ppmNetHandle          INTOSD;
    ppmNetHandle          INTP4;
    ppmNetHandle          INTUC0R;
    ppmNetHandle          INTP5;
    ppmNetHandle          INTUC1R;
    ppmNetHandle          INTBRG0;
    ppmNetHandle          INTBRG1;
    ppmNetHandle          INTCB0T;
    ppmNetHandle          INTUC2T;
    ppmNetHandle          INTCB0R;
    ppmNetHandle          INTUC2R;
    ppmNetHandle          INTP13;
    ppmNetHandle          INTCB0RE;
    ppmNetHandle          INTUC2RE;
    ppmNetHandle          INTDMA3;
    ppmNetHandle          INTFL;
    ppmNetHandle          NMIOUT;
    ppmNetHandle          INT0;
    ppmNetHandle          INT1;
    ppmNetHandle          INT6;
    ppmNetHandle          INT7;
    ppmNetHandle          INT75;
    ppmNetHandle          INT99;
    ppmNetHandle          INT100;
    ppmNetHandle          INT101;
    ppmNetHandle          INT116;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_INTBRG0);
PPM_NET_CB(P_INTBRG1);
PPM_NET_CB(P_INTCB0R);
PPM_NET_CB(P_INTCB0RE);
PPM_NET_CB(P_INTCB0T);
PPM_NET_CB(P_INTDEDF);
PPM_NET_CB(P_INTDEDFR);
PPM_NET_CB(P_INTDEDR);
PPM_NET_CB(P_INTDMA3);
PPM_NET_CB(P_INTFL);
PPM_NET_CB(P_INTOSD);
PPM_NET_CB(P_INTP13);
PPM_NET_CB(P_INTP4);
PPM_NET_CB(P_INTP5);
PPM_NET_CB(P_INTUC0R);
PPM_NET_CB(P_INTUC1R);
PPM_NET_CB(P_INTUC2R);
PPM_NET_CB(P_INTUC2RE);
PPM_NET_CB(P_INTUC2T);
PPM_NET_CB(P_NMIIN);
PPM_REG_WRITE_CB(writeERR);
PPM_REG_WRITE_CB(writeESOST5);
PPM_REG_WRITE_CB(writeESOST6);
PPM_REG_WRITE_CB(writeP);
PPM_REG_WRITE_CB(writePESC5);
PPM_REG_WRITE_CB(writePESC6);
PPM_REG_WRITE_CB(writePESMK5);
PPM_REG_WRITE_CB(writePESMK6);
PPM_REG_WRITE_CB(writePFC);
PPM_REG_WRITE_CB(writePM);
PPM_REG_WRITE_CB(writePMC);
PPM_REG_WRITE_CB(writePRCMD);
PPM_REG_WRITE_CB(writeSEL);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
