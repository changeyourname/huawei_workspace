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

typedef struct apb_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 2;
            unsigned RSTRX : 1;
            unsigned RSTTX : 1;
            unsigned RXEN : 1;
            unsigned RXDIS : 1;
            unsigned TXEN : 1;
            unsigned TXDIS : 1;
            unsigned RSTSTA : 1;
            unsigned STTBRK : 1;
            unsigned STPBRK : 1;
            unsigned STTTO : 1;
            unsigned SENDA : 1;
        } bits;
    } US_CR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 4;
            unsigned HSCLKS : 2;
            unsigned CHRL : 2;
            unsigned SYNC : 1;
            unsigned PAR : 3;
            unsigned NBSTOP : 2;
            unsigned CHMODE : 2;
            unsigned __pad16 : 1;
            unsigned MODE9 : 1;
            unsigned CLKO : 1;
        } bits;
    } US_MR;
    union { 
        Uns32 value;
        struct {
            unsigned RXRDY : 1;
            unsigned TXRDY : 1;
            unsigned RXBRK : 1;
            unsigned ENDRX : 1;
            unsigned ENDTX : 1;
            unsigned OVRE : 1;
            unsigned FRAME : 1;
            unsigned PARE : 1;
            unsigned TIMEOUT : 1;
            unsigned TXEMPTY : 1;
        } bits;
    } US_IER;
    union { 
        Uns32 value;
        struct {
            unsigned RXRDY : 1;
            unsigned TXRDY : 1;
            unsigned RXBRK : 1;
            unsigned ENDRX : 1;
            unsigned ENDTX : 1;
            unsigned OVRE : 1;
            unsigned FRAME : 1;
            unsigned PARE : 1;
            unsigned TIMEOUT : 1;
            unsigned TXEMPTY : 1;
        } bits;
    } US_IDR;
    union { 
        Uns32 value;
        struct {
            unsigned RXRDY : 1;
            unsigned TXRDY : 1;
            unsigned RXBRK : 1;
            unsigned ENDRX : 1;
            unsigned ENDTX : 1;
            unsigned OVRE : 1;
            unsigned FRAME : 1;
            unsigned PARE : 1;
            unsigned TIMEOUT : 1;
            unsigned TXEMPTY : 1;
        } bits;
    } US_IMR;
    union { 
        Uns32 value;
        struct {
            unsigned RXRDY : 1;
            unsigned TXRDY : 1;
            unsigned RXBRK : 1;
            unsigned ENDRX : 1;
            unsigned ENDTX : 1;
            unsigned OVRE : 1;
            unsigned FRAME : 1;
            unsigned PARE : 1;
            unsigned TIMEOUT : 1;
            unsigned TXEMPTY : 1;
        } bits;
    } US_CSR;
    union { 
        Uns32 value;
        struct {
            unsigned RXCHR : 8;
        } bits;
    } US_RHR;
    union { 
        Uns32 value;
        struct {
            unsigned TXCHR : 8;
        } bits;
    } US_THR;
    union { 
        Uns32 value;
        struct {
            unsigned CD : 16;
        } bits;
    } US_BRGR;
    union { 
        Uns32 value;
        struct {
            unsigned TO : 8;
        } bits;
    } US_RTOR;
    union { 
        Uns32 value;
        struct {
            unsigned TG : 8;
        } bits;
    } US_TTGR;
    union { 
        Uns32 value;
        struct {
            unsigned RXPTR : 32;
        } bits;
    } US_RPR;
    union { 
        Uns32 value;
        struct {
            unsigned RXCTR : 16;
        } bits;
    } US_RCR;
    union { 
        Uns32 value;
        struct {
            unsigned TXPTR : 32;
        } bits;
    } US_TPR;
    union { 
        Uns32 value;
        struct {
            unsigned TXCTR : 16;
        } bits;
    } US_TCR;
} apb_REG_dataT, *apb_REG_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern apb_REG_dataT apb_REG_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle asb;
    void                 *apb;
    ppmNetHandle          IRQ;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(US_BRGR_wcb);
PPM_REG_WRITE_CB(US_CR_wcb);
PPM_REG_WRITE_CB(US_IDR_wcb);
PPM_REG_WRITE_CB(US_IER_wcb);
PPM_REG_WRITE_CB(US_MR_wcb);
PPM_REG_WRITE_CB(US_RCR_wcb);
PPM_REG_READ_CB(US_RHR_rcb);
PPM_REG_WRITE_CB(US_RPR_wcb);
PPM_REG_WRITE_CB(US_RTOR_wcb);
PPM_REG_WRITE_CB(US_TCR_wcb);
PPM_REG_WRITE_CB(US_THR_wcb);
PPM_REG_WRITE_CB(US_TPR_wcb);
PPM_REG_WRITE_CB(US_TTGR_wcb);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
