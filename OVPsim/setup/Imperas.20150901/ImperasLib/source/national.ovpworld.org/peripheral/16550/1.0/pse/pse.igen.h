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
        Uns8 value;
    } rbr_dll;
    union { 
        Uns8 value;
    } thr_dll;
    union { 
        Uns8 value;
        struct {
            unsigned erbfi : 1;
            unsigned etbei : 1;
            unsigned elsi : 1;
            unsigned edssi : 1;
        } bits;
    } ier_dlh;
    union { 
        Uns8 value;
        struct {
            unsigned intid : 4;
            unsigned __pad4 : 2;
            unsigned fifoen : 2;
        } bits;
    } iir;
    union { 
        Uns8 value;
        struct {
            unsigned fifoEn : 1;
            unsigned fifoRcvrRst : 1;
            unsigned fifoXmitRst : 1;
            unsigned dmaModeSel : 1;
            unsigned fifoXmitTrig : 2;
            unsigned fifoRcvrTrig : 2;
        } bits;
    } fcr;
    union { 
        Uns8 value;
        struct {
            unsigned dls : 2;
            unsigned stop : 1;
            unsigned pen : 1;
            unsigned eps : 1;
            unsigned stick : 1;
            unsigned brk : 1;
            unsigned dlab : 1;
        } bits;
    } lcr;
    union { 
        Uns8 value;
    } mcr;
    union { 
        Uns8 value;
        struct {
            unsigned dr : 1;
            unsigned oe : 1;
            unsigned pe : 1;
            unsigned fe : 1;
            unsigned bi : 1;
            unsigned thre : 1;
            unsigned temt : 1;
            unsigned rfe : 1;
        } bits;
    } lsr;
    union { 
        Uns8 value;
    } msr;
    union { 
        Uns8 value;
    } scr;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          reset_uart;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readIER_DLH);
PPM_REG_READ_CB(readIIR);
PPM_REG_READ_CB(readLSR);
PPM_REG_READ_CB(readRBR_DLL);
PPM_NET_CB(resetCB);
PPM_REG_VIEW_CB(viewIER_DLH);
PPM_REG_VIEW_CB(viewIIR);
PPM_REG_VIEW_CB(viewLSR);
PPM_REG_VIEW_CB(viewRBR_DLL);
PPM_REG_VIEW_CB(viewTHR_DLL);
PPM_REG_WRITE_CB(writeFCR);
PPM_REG_WRITE_CB(writeIER_DLH);
PPM_REG_WRITE_CB(writeLCR);
PPM_REG_WRITE_CB(writeTHR_DLL);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
