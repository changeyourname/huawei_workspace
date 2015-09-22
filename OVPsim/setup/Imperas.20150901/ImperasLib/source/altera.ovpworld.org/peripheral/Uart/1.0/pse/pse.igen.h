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

typedef struct sp1_reg0_dataS { 
    union { 
        Uns32 value;
    } rxdata;
    union { 
        Uns32 value;
    } txdata;
    union { 
        Uns32 value;
        struct {
            unsigned pe : 1;
            unsigned fe : 1;
            unsigned brk : 1;
            unsigned roe : 1;
            unsigned toe : 1;
            unsigned tmt : 1;
            unsigned trdy : 1;
            unsigned rrdy : 1;
            unsigned e : 2;
            unsigned dcts : 1;
            unsigned cts : 1;
            unsigned eop : 1;
        } bits;
    } status;
    union { 
        Uns32 value;
        struct {
            unsigned ipe : 1;
            unsigned ife : 1;
            unsigned ibrk : 1;
            unsigned iroe : 1;
            unsigned itoe : 1;
            unsigned itmt : 1;
            unsigned itrdy : 1;
            unsigned irrdy : 1;
            unsigned ie : 1;
            unsigned trbk : 1;
            unsigned idcts : 1;
            unsigned rts : 1;
            unsigned ieop : 1;
        } bits;
    } control;
    union { 
        Uns32 value;
    } divisor;
    union { 
        Uns32 value;
    } eop;
} sp1_reg0_dataT, *sp1_reg0_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern sp1_reg0_dataT sp1_reg0_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *sp1;
    ppmNetHandle          irq;
    ppmNetHandle          endofpacket;
    ppmNetHandle          dataavailable;
    ppmNetHandle          readyfordata;
    ppmNetHandle          RXD;
    ppmNetHandle          CTS;
    ppmNetHandle          TXD;
    ppmNetHandle          RTS;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(read_control);
PPM_REG_READ_CB(read_divisor);
PPM_REG_READ_CB(read_eop);
PPM_REG_READ_CB(read_rxdata);
PPM_REG_READ_CB(read_status);
PPM_REG_WRITE_CB(write_control);
PPM_REG_WRITE_CB(write_divisor);
PPM_REG_WRITE_CB(write_eop);
PPM_REG_WRITE_CB(write_status);
PPM_REG_WRITE_CB(write_txdata);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
