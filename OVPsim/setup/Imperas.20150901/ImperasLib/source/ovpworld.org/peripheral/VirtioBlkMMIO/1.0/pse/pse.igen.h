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
        Uns32 value;
    } MagicValue;
    union { 
        Uns32 value;
    } Version;
    union { 
        Uns32 value;
    } DeviceID;
    union { 
        Uns32 value;
    } VendorID;
    union { 
        Uns32 value;
    } HostFeatures;
    union { 
        Uns32 value;
    } HostFSel;
    union { 
        Uns32 value;
    } GuestFeatures;
    union { 
        Uns32 value;
    } GuestFSel;
    union { 
        Uns32 value;
    } GuestPageSz;
    union { 
        Uns32 value;
    } QueueSel;
    union { 
        Uns32 value;
    } QueueNumMax;
    union { 
        Uns32 value;
    } QueueNum;
    union { 
        Uns32 value;
    } QueueAlign;
    union { 
        Uns32 value;
    } QueuePFN;
    union { 
        Uns32 value;
    } QueueNotify;
    union { 
        Uns32 value;
        struct {
            unsigned UsedRingUpdate : 1;
            unsigned ConfigChange : 1;
        } bits;
    } IntStatus;
    union { 
        Uns32 value;
        struct {
            unsigned UsedRingUpdate : 1;
            unsigned ConfigChange : 1;
        } bits;
    } IntAck;
    union { 
        Uns32 value;
        struct {
            unsigned Ack : 1;
            unsigned Driver : 1;
            unsigned DriverOk : 1;
            unsigned __pad3 : 4;
            unsigned Failed : 1;
        } bits;
    } Status;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle dma;
    void                 *bport1;
    ppmNetHandle          Interrupt;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(rdHostF);
PPM_REG_READ_CB(rdIntStat);
PPM_REG_READ_CB(rdMagic);
PPM_REG_READ_CB(rdQPFN);
PPM_REG_READ_CB(rdStatus);
PPM_REG_WRITE_CB(wrGPgSz);
PPM_REG_WRITE_CB(wrGuestF);
PPM_REG_WRITE_CB(wrIntAck);
PPM_REG_WRITE_CB(wrQAlign);
PPM_REG_WRITE_CB(wrQNotify);
PPM_REG_WRITE_CB(wrQNum);
PPM_REG_WRITE_CB(wrQPFN);
PPM_REG_WRITE_CB(wrSel);
PPM_REG_WRITE_CB(wrStatus);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
