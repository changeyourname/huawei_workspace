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

typedef struct bp1_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR0;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR1;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR2;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR3;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR4;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR5;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR6;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR7;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR8;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR9;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR10;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR11;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR12;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR13;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR14;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR15;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR16;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR17;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR18;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR19;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR20;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR21;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR22;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR23;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR24;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR25;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR26;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR27;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR28;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR29;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR30;
    union { 
        Uns32 value;
        struct {
            unsigned PRIOR : 2;
            unsigned __pad2 : 3;
            unsigned SRCTYPE : 2;
        } bits;
    } AIC_SMR31;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR0;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR1;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR2;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR3;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR4;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR5;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR6;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR7;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR8;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR9;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR10;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR11;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR12;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR13;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR14;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR15;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR16;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR17;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR18;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR19;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR20;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR21;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR22;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR23;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR24;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR25;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR26;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR27;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR28;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR29;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR30;
    union { 
        Uns32 value;
        struct {
            unsigned VECTOR : 32;
        } bits;
    } AIC_SVR31;
    union { 
        Uns32 value;
    } AIC_IVR;
    union { 
        Uns32 value;
    } AIC_FVR;
    union { 
        Uns32 value;
        struct {
            unsigned IRQID : 5;
        } bits;
    } AIC_ISR;
    union { 
        Uns32 value;
        struct {
            unsigned FIQ : 1;
            unsigned SWIRQ : 1;
            unsigned US0IRQ : 1;
            unsigned US1IRQ : 1;
            unsigned TC0IRQ : 1;
            unsigned TC1IRQ : 1;
            unsigned TC2IRQ : 1;
            unsigned WDIRQ : 1;
            unsigned PIOIRQ : 1;
            unsigned __pad9 : 7;
            unsigned IRQ0 : 1;
            unsigned IRQ1 : 1;
            unsigned IRQ2 : 1;
        } bits;
    } AIC_IPR;
    union { 
        Uns32 value;
        struct {
            unsigned FIQ : 1;
            unsigned SWIRQ : 1;
            unsigned US0IRQ : 1;
            unsigned US1IRQ : 1;
            unsigned TC0IRQ : 1;
            unsigned TC1IRQ : 1;
            unsigned TC2IRQ : 1;
            unsigned WDIRQ : 1;
            unsigned PIOIRQ : 1;
            unsigned __pad9 : 7;
            unsigned IRQ0 : 1;
            unsigned IRQ1 : 1;
            unsigned IRQ2 : 1;
        } bits;
    } AIC_IMR;
    union { 
        Uns32 value;
        struct {
            unsigned NFIQ : 1;
            unsigned NIRQ : 1;
        } bits;
    } AIC_CISR;
    union { 
        Uns32 value;
        struct {
            unsigned FIQ : 1;
            unsigned SWIRQ : 1;
            unsigned US0IRQ : 1;
            unsigned US1IRQ : 1;
            unsigned TC0IRQ : 1;
            unsigned TC1IRQ : 1;
            unsigned TC2IRQ : 1;
            unsigned WDIRQ : 1;
            unsigned PIOIRQ : 1;
            unsigned __pad9 : 7;
            unsigned IRQ0 : 1;
            unsigned IRQ1 : 1;
            unsigned IRQ2 : 1;
        } bits;
    } AIC_IECR;
    union { 
        Uns32 value;
        struct {
            unsigned FIQ : 1;
            unsigned SWIRQ : 1;
            unsigned US0IRQ : 1;
            unsigned US1IRQ : 1;
            unsigned TC0IRQ : 1;
            unsigned TC1IRQ : 1;
            unsigned TC2IRQ : 1;
            unsigned WDIRQ : 1;
            unsigned PIOIRQ : 1;
            unsigned __pad9 : 7;
            unsigned IRQ0 : 1;
            unsigned IRQ1 : 1;
            unsigned IRQ2 : 1;
        } bits;
    } AIC_IDCR;
    union { 
        Uns32 value;
        struct {
            unsigned FIQ : 1;
            unsigned SWIRQ : 1;
            unsigned US0IRQ : 1;
            unsigned US1IRQ : 1;
            unsigned TC0IRQ : 1;
            unsigned TC1IRQ : 1;
            unsigned TC2IRQ : 1;
            unsigned WDIRQ : 1;
            unsigned PIOIRQ : 1;
            unsigned __pad9 : 7;
            unsigned IRQ0 : 1;
            unsigned IRQ1 : 1;
            unsigned IRQ2 : 1;
        } bits;
    } AIC_ICCR;
    union { 
        Uns32 value;
        struct {
            unsigned FIQ : 1;
            unsigned SWIRQ : 1;
            unsigned US0IRQ : 1;
            unsigned US1IRQ : 1;
            unsigned TC0IRQ : 1;
            unsigned TC1IRQ : 1;
            unsigned TC2IRQ : 1;
            unsigned WDIRQ : 1;
            unsigned PIOIRQ : 1;
            unsigned __pad9 : 7;
            unsigned IRQ0 : 1;
            unsigned IRQ1 : 1;
            unsigned IRQ2 : 1;
        } bits;
    } AIC_ISCR;
    union { 
        Uns32 value;
    } AIC_EOICR;
    union { 
        Uns32 value;
    } AIC_SPU;
} bp1_REG_dataT, *bp1_REG_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bp1_REG_dataT bp1_REG_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bp1;
    ppmNetHandle          NFIQ;
    ppmNetHandle          NIRQ;
    ppmNetHandle          FIQ;
    ppmNetHandle          SWIRQ;
    ppmNetHandle          US0IRQ;
    ppmNetHandle          US1IRQ;
    ppmNetHandle          TC0IRQ;
    ppmNetHandle          TC1IRQ;
    ppmNetHandle          TC2IRQ;
    ppmNetHandle          WDIRQ;
    ppmNetHandle          PIOIRQ;
    ppmNetHandle          IRQ0;
    ppmNetHandle          IRQ1;
    ppmNetHandle          IRQ2;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(AIC_EOICR_wcb);
PPM_REG_WRITE_CB(AIC_ICCR_wcb);
PPM_REG_WRITE_CB(AIC_IDCR_wcb);
PPM_REG_WRITE_CB(AIC_IECR_wcb);
PPM_REG_WRITE_CB(AIC_ISCR_wcb);
PPM_REG_READ_CB(AIC_IVR_rcb);
PPM_REG_WRITE_CB(AIC_SMR_wcb0);
PPM_REG_WRITE_CB(AIC_SMR_wcb1);
PPM_REG_WRITE_CB(AIC_SMR_wcb10);
PPM_REG_WRITE_CB(AIC_SMR_wcb11);
PPM_REG_WRITE_CB(AIC_SMR_wcb12);
PPM_REG_WRITE_CB(AIC_SMR_wcb13);
PPM_REG_WRITE_CB(AIC_SMR_wcb14);
PPM_REG_WRITE_CB(AIC_SMR_wcb15);
PPM_REG_WRITE_CB(AIC_SMR_wcb16);
PPM_REG_WRITE_CB(AIC_SMR_wcb17);
PPM_REG_WRITE_CB(AIC_SMR_wcb18);
PPM_REG_WRITE_CB(AIC_SMR_wcb19);
PPM_REG_WRITE_CB(AIC_SMR_wcb2);
PPM_REG_WRITE_CB(AIC_SMR_wcb20);
PPM_REG_WRITE_CB(AIC_SMR_wcb21);
PPM_REG_WRITE_CB(AIC_SMR_wcb22);
PPM_REG_WRITE_CB(AIC_SMR_wcb23);
PPM_REG_WRITE_CB(AIC_SMR_wcb24);
PPM_REG_WRITE_CB(AIC_SMR_wcb25);
PPM_REG_WRITE_CB(AIC_SMR_wcb26);
PPM_REG_WRITE_CB(AIC_SMR_wcb27);
PPM_REG_WRITE_CB(AIC_SMR_wcb28);
PPM_REG_WRITE_CB(AIC_SMR_wcb29);
PPM_REG_WRITE_CB(AIC_SMR_wcb3);
PPM_REG_WRITE_CB(AIC_SMR_wcb30);
PPM_REG_WRITE_CB(AIC_SMR_wcb31);
PPM_REG_WRITE_CB(AIC_SMR_wcb4);
PPM_REG_WRITE_CB(AIC_SMR_wcb5);
PPM_REG_WRITE_CB(AIC_SMR_wcb6);
PPM_REG_WRITE_CB(AIC_SMR_wcb7);
PPM_REG_WRITE_CB(AIC_SMR_wcb8);
PPM_REG_WRITE_CB(AIC_SMR_wcb9);
PPM_REG_WRITE_CB(AIC_SPU_wcb);
PPM_REG_WRITE_CB(AIC_SVR_wcb0);
PPM_REG_WRITE_CB(AIC_SVR_wcb1);
PPM_REG_WRITE_CB(AIC_SVR_wcb10);
PPM_REG_WRITE_CB(AIC_SVR_wcb11);
PPM_REG_WRITE_CB(AIC_SVR_wcb12);
PPM_REG_WRITE_CB(AIC_SVR_wcb13);
PPM_REG_WRITE_CB(AIC_SVR_wcb14);
PPM_REG_WRITE_CB(AIC_SVR_wcb15);
PPM_REG_WRITE_CB(AIC_SVR_wcb16);
PPM_REG_WRITE_CB(AIC_SVR_wcb17);
PPM_REG_WRITE_CB(AIC_SVR_wcb18);
PPM_REG_WRITE_CB(AIC_SVR_wcb19);
PPM_REG_WRITE_CB(AIC_SVR_wcb2);
PPM_REG_WRITE_CB(AIC_SVR_wcb20);
PPM_REG_WRITE_CB(AIC_SVR_wcb21);
PPM_REG_WRITE_CB(AIC_SVR_wcb22);
PPM_REG_WRITE_CB(AIC_SVR_wcb23);
PPM_REG_WRITE_CB(AIC_SVR_wcb24);
PPM_REG_WRITE_CB(AIC_SVR_wcb25);
PPM_REG_WRITE_CB(AIC_SVR_wcb26);
PPM_REG_WRITE_CB(AIC_SVR_wcb27);
PPM_REG_WRITE_CB(AIC_SVR_wcb28);
PPM_REG_WRITE_CB(AIC_SVR_wcb29);
PPM_REG_WRITE_CB(AIC_SVR_wcb3);
PPM_REG_WRITE_CB(AIC_SVR_wcb30);
PPM_REG_WRITE_CB(AIC_SVR_wcb31);
PPM_REG_WRITE_CB(AIC_SVR_wcb4);
PPM_REG_WRITE_CB(AIC_SVR_wcb5);
PPM_REG_WRITE_CB(AIC_SVR_wcb6);
PPM_REG_WRITE_CB(AIC_SVR_wcb7);
PPM_REG_WRITE_CB(AIC_SVR_wcb8);
PPM_REG_WRITE_CB(AIC_SVR_wcb9);
PPM_NET_CB(FIQ_wcb);
PPM_NET_CB(IRQ0_wcb);
PPM_NET_CB(IRQ1_wcb);
PPM_NET_CB(IRQ2_wcb);
PPM_NET_CB(PIOIRQ_wcb);
PPM_NET_CB(SWIRQ_wcb);
PPM_NET_CB(TC0IRQ_wcb);
PPM_NET_CB(TC1IRQ_wcb);
PPM_NET_CB(TC2IRQ_wcb);
PPM_NET_CB(US0IRQ_wcb);
PPM_NET_CB(US1IRQ_wcb);
PPM_NET_CB(WDIRQ_wcb);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
