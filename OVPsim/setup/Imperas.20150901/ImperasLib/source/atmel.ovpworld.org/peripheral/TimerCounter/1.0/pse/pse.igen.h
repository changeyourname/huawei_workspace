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
            unsigned CLKEN : 1;
            unsigned CLKDIS : 1;
            unsigned SWTRG : 1;
        } bits;
    } TC_CCR0;
    union { 
        Uns32 value;
        struct {
            unsigned TCCLKS : 3;
            unsigned CLKI : 1;
            unsigned BURST : 2;
            unsigned LDBSTOP : 1;
            unsigned LDBDIS : 1;
            unsigned ETRGEDG : 2;
            unsigned ABETRG : 1;
            unsigned __pad11 : 3;
            unsigned CPCTRG : 1;
            unsigned WAVE : 1;
            unsigned LDRA : 2;
            unsigned LDRB : 2;
        } bits;
    } TC_CMR0;
    union { 
        Uns32 value;
        struct {
            unsigned CV : 16;
        } bits;
    } TC_CVR0;
    union { 
        Uns32 value;
        struct {
            unsigned RA : 16;
        } bits;
    } TC_RA0;
    union { 
        Uns32 value;
        struct {
            unsigned RB : 16;
        } bits;
    } TC_RB0;
    union { 
        Uns32 value;
        struct {
            unsigned RC : 16;
        } bits;
    } TC_RC0;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
            unsigned __pad8 : 8;
            unsigned CLKSTA : 1;
            unsigned MTIOA : 1;
            unsigned MTIOB : 1;
        } bits;
    } TC_SR0;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IER0;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IDR0;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IMR0;
    union { 
        Uns32 value;
        struct {
            unsigned CLKEN : 1;
            unsigned CLKDIS : 1;
            unsigned SWTRG : 1;
        } bits;
    } TC_CCR1;
    union { 
        Uns32 value;
        struct {
            unsigned TCCLKS : 3;
            unsigned CLKI : 1;
            unsigned BURST : 2;
            unsigned LDBSTOP : 1;
            unsigned LDBDIS : 1;
            unsigned ETRGEDG : 2;
            unsigned ABETRG : 1;
            unsigned __pad11 : 3;
            unsigned CPCTRG : 1;
            unsigned WAVE : 1;
            unsigned LDRA : 2;
            unsigned LDRB : 2;
        } bits;
    } TC_CMR1;
    union { 
        Uns32 value;
        struct {
            unsigned CV : 16;
        } bits;
    } TC_CVR1;
    union { 
        Uns32 value;
        struct {
            unsigned RA : 16;
        } bits;
    } TC_RA1;
    union { 
        Uns32 value;
        struct {
            unsigned RB : 16;
        } bits;
    } TC_RB1;
    union { 
        Uns32 value;
        struct {
            unsigned RC : 16;
        } bits;
    } TC_RC1;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
            unsigned __pad8 : 8;
            unsigned CLKSTA : 1;
            unsigned MTIOA : 1;
            unsigned MTIOB : 1;
        } bits;
    } TC_SR1;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IER1;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IDR1;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IMR1;
    union { 
        Uns32 value;
        struct {
            unsigned CLKEN : 1;
            unsigned CLKDIS : 1;
            unsigned SWTRG : 1;
        } bits;
    } TC_CCR2;
    union { 
        Uns32 value;
        struct {
            unsigned TCCLKS : 3;
            unsigned CLKI : 1;
            unsigned BURST : 2;
            unsigned LDBSTOP : 1;
            unsigned LDBDIS : 1;
            unsigned ETRGEDG : 2;
            unsigned ABETRG : 1;
            unsigned __pad11 : 3;
            unsigned CPCTRG : 1;
            unsigned WAVE : 1;
            unsigned LDRA : 2;
            unsigned LDRB : 2;
        } bits;
    } TC_CMR2;
    union { 
        Uns32 value;
        struct {
            unsigned CV : 16;
        } bits;
    } TC_CVR2;
    union { 
        Uns32 value;
        struct {
            unsigned RA : 16;
        } bits;
    } TC_RA2;
    union { 
        Uns32 value;
        struct {
            unsigned RB : 16;
        } bits;
    } TC_RB2;
    union { 
        Uns32 value;
        struct {
            unsigned RC : 16;
        } bits;
    } TC_RC2;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
            unsigned __pad8 : 8;
            unsigned CLKSTA : 1;
            unsigned MTIOA : 1;
            unsigned MTIOB : 1;
        } bits;
    } TC_SR2;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IER2;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IDR2;
    union { 
        Uns32 value;
        struct {
            unsigned COVFS : 1;
            unsigned LOVRS : 1;
            unsigned CPAS : 1;
            unsigned CPBS : 1;
            unsigned CPCS : 1;
            unsigned LDRAS : 1;
            unsigned LDRBS : 1;
            unsigned ETRGS : 1;
        } bits;
    } TC_IMR2;
    union { 
        Uns32 value;
        struct {
            unsigned SYNC : 1;
        } bits;
    } TC_BCR;
    union { 
        Uns32 value;
        struct {
            unsigned TC0X0CS : 2;
            unsigned TC1X1CS : 2;
            unsigned TC2X2CS : 2;
        } bits;
    } TC_BMR;
} bp1_REG_dataT, *bp1_REG_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bp1_REG_dataT bp1_REG_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bp1;
    ppmNetHandle          IRQ0;
    ppmNetHandle          IRQ1;
    ppmNetHandle          IRQ2;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(TC_BCR_wcb);
PPM_REG_WRITE_CB(TC_BMR_wcb);
PPM_REG_WRITE_CB(TC_CCR_wcb0);
PPM_REG_WRITE_CB(TC_CCR_wcb1);
PPM_REG_WRITE_CB(TC_CCR_wcb2);
PPM_REG_WRITE_CB(TC_CMR_wcb0);
PPM_REG_WRITE_CB(TC_CMR_wcb1);
PPM_REG_WRITE_CB(TC_CMR_wcb2);
PPM_REG_WRITE_CB(TC_CVR_wcb0);
PPM_REG_WRITE_CB(TC_CVR_wcb1);
PPM_REG_WRITE_CB(TC_CVR_wcb2);
PPM_REG_WRITE_CB(TC_IDR_wcb0);
PPM_REG_WRITE_CB(TC_IDR_wcb1);
PPM_REG_WRITE_CB(TC_IDR_wcb2);
PPM_REG_WRITE_CB(TC_IER_wcb0);
PPM_REG_WRITE_CB(TC_IER_wcb1);
PPM_REG_WRITE_CB(TC_IER_wcb2);
PPM_REG_WRITE_CB(TC_RA_wcb0);
PPM_REG_WRITE_CB(TC_RA_wcb1);
PPM_REG_WRITE_CB(TC_RA_wcb2);
PPM_REG_WRITE_CB(TC_RB_wcb0);
PPM_REG_WRITE_CB(TC_RB_wcb1);
PPM_REG_WRITE_CB(TC_RB_wcb2);
PPM_REG_WRITE_CB(TC_RC_wcb0);
PPM_REG_WRITE_CB(TC_RC_wcb1);
PPM_REG_WRITE_CB(TC_RC_wcb2);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
