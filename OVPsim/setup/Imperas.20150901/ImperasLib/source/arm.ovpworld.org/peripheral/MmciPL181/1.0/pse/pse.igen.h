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
    } power;
    union { 
        Uns32 value;
    } clock;
    union { 
        Uns32 value;
    } cmdarg;
    union { 
        Uns32 value;
        struct {
            unsigned C_INDEX : 6;
            unsigned C_RESPONSE : 1;
            unsigned C_LONGRESP : 1;
            unsigned C_INTERRUPT : 1;
            unsigned C_PENDING : 1;
            unsigned C_ENABLE : 1;
        } bits;
    } cmd;
    union { 
        Uns32 value;
    } respcmd;
    union { 
        Uns32 value;
    } response0;
    union { 
        Uns32 value;
    } response1;
    union { 
        Uns32 value;
    } response2;
    union { 
        Uns32 value;
    } response3;
    union { 
        Uns32 value;
    } datatimer;
    union { 
        Uns32 value;
    } datalength;
    union { 
        Uns32 value;
        struct {
            unsigned D_ENABLE : 1;
            unsigned D_DIRECTION : 1;
            unsigned D_MODE : 1;
            unsigned D_DMAENABLE : 1;
        } bits;
    } datactrl;
    union { 
        Uns32 value;
    } datacnt;
    union { 
        Uns32 value;
        struct {
            unsigned S_CMDCRCFAIL : 1;
            unsigned S_DATACRCFAIL : 1;
            unsigned S_CMDTIMEOUT : 1;
            unsigned S_DATATIMEOUT : 1;
            unsigned S_TXUNDERRUN : 1;
            unsigned S_RXOVERRUN : 1;
            unsigned S_CMDRESPEND : 1;
            unsigned S_CMDSENT : 1;
            unsigned S_DATAEND : 1;
            unsigned __pad9 : 1;
            unsigned S_DATABLOCKEND : 1;
            unsigned S_CMDACTIVE : 1;
            unsigned S_TXACTIVE : 1;
            unsigned S_RXACTIVE : 1;
            unsigned S_TXFIFOHALFEMPTY : 1;
            unsigned S_RXFIFOHALFFULL : 1;
            unsigned S_TXFIFOFULL : 1;
            unsigned S_RXFIFOFULL : 1;
            unsigned S_TXFIFOEMPTY : 1;
            unsigned S_RXFIFOEMPTY : 1;
            unsigned S_TXDATAAVLBL : 1;
            unsigned S_RXDATAAVLBL : 1;
        } bits;
    } status;
    union { 
        Uns32 value;
    } clear;
    union { 
        Uns32 value;
    } mask0;
    union { 
        Uns32 value;
    } mask1;
    union { 
        Uns32 value;
    } fifoCnt;
    union { 
        Uns32 value;
    } periphID0;
    union { 
        Uns32 value;
    } periphID1;
    union { 
        Uns32 value;
    } periphID2;
    union { 
        Uns32 value;
    } periphID3;
    union { 
        Uns32 value;
    } pCellID0;
    union { 
        Uns32 value;
    } pCellID1;
    union { 
        Uns32 value;
    } pCellID2;
    union { 
        Uns32 value;
    } pCellID3;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq0;
    ppmNetHandle          irq1;
    ppmNetHandle          cardin;
    ppmNetHandle          wprot;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readFifoCnt);
PPM_REG_READ_CB(readStatus);
PPM_REG_WRITE_CB(write8);
PPM_REG_WRITE_CB(writeArg);
PPM_REG_WRITE_CB(writeClear);
PPM_REG_WRITE_CB(writeClock);
PPM_REG_WRITE_CB(writeCmd);
PPM_REG_WRITE_CB(writeDC);
PPM_REG_WRITE_CB(writeDL);
PPM_REG_WRITE_CB(writeMask0);
PPM_REG_WRITE_CB(writeMask1);
PPM_READ_CB(reservedRead);
PPM_WRITE_CB(reservedWrite);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
