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

typedef struct bport1_timer1_dataS { 
    union { 
        Uns32 value;
    } loadcount;
    union { 
        Uns32 value;
    } currentval;
    union { 
        Uns32 value;
        struct {
            unsigned enable : 1;
            unsigned mode : 1;
            unsigned interrupt_mask : 1;
        } bits;
    } controlreg;
    union { 
        Uns32 value;
        struct {
            unsigned eoi : 1;
        } bits;
    } eoi;
    union { 
        Uns32 value;
        struct {
            unsigned intstat : 1;
        } bits;
    } intstat;
} bport1_timer1_dataT, *bport1_timer1_dataTP;

typedef struct bport1_timers_dataS { 
    union { 
        Uns32 value;
        struct {
            unsigned intstat : 1;
        } bits;
    } intstat;
    union { 
        Uns32 value;
        struct {
            unsigned eoi : 1;
        } bits;
    } eoi;
    union { 
        Uns32 value;
        struct {
            unsigned intstat : 1;
        } bits;
    } rawintstat;
    union { 
        Uns32 value;
    } compversion;
} bport1_timers_dataT, *bport1_timers_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_timer1_dataT bport1_timer1_data;

extern bport1_timers_dataT bport1_timers_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(Readcurrentval);
PPM_REG_READ_CB(Readeoi);
PPM_REG_READ_CB(Readintstat);
PPM_REG_READ_CB(Readrawintstat);
PPM_REG_WRITE_CB(Writecontrolreg);
PPM_REG_WRITE_CB(Writeloadcount);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
