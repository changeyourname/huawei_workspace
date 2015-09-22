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
    } status;
    union { 
        Uns32 value;
    } level;
    union { 
        Uns32 value;
    } enable;
    union { 
        Uns32 value;
    } clr;
    union { 
        Uns32 value;
    } softset;
    union { 
        Uns32 value;
    } softclr;
    union { 
        Uns32 value;
    } frqstat;
    union { 
        Uns32 value;
    } rawstat;
    union { 
        Uns32 value;
    } fiqen;
    union { 
        Uns32 value;
    } fiqenclr;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
    ppmNetHandle          fiq;
    ppmNetHandle          ir0;
    ppmNetHandle          ir1;
    ppmNetHandle          ir2;
    ppmNetHandle          ir3;
    ppmNetHandle          ir4;
    ppmNetHandle          ir5;
    ppmNetHandle          ir6;
    ppmNetHandle          ir7;
    ppmNetHandle          ir8;
    ppmNetHandle          ir9;
    ppmNetHandle          ir10;
    ppmNetHandle          ir11;
    ppmNetHandle          ir12;
    ppmNetHandle          ir13;
    ppmNetHandle          ir14;
    ppmNetHandle          ir15;
    ppmNetHandle          ir16;
    ppmNetHandle          ir17;
    ppmNetHandle          ir18;
    ppmNetHandle          ir19;
    ppmNetHandle          ir20;
    ppmNetHandle          ir21;
    ppmNetHandle          ir22;
    ppmNetHandle          ir23;
    ppmNetHandle          ir24;
    ppmNetHandle          ir25;
    ppmNetHandle          ir26;
    ppmNetHandle          ir27;
    ppmNetHandle          ir28;
    ppmNetHandle          ir29;
    ppmNetHandle          ir30;
    ppmNetHandle          ir31;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(irqUpdate);
PPM_REG_READ_CB(readFIQ);
PPM_REG_READ_CB(readIRQ);
PPM_REG_READ_CB(readLEV);
PPM_REG_READ_CB(readLevel);
PPM_REG_WRITE_CB(writeCLR);
PPM_REG_WRITE_CB(writeFIQC);
PPM_REG_WRITE_CB(writeFIQS);
PPM_REG_WRITE_CB(writeSCL);
PPM_REG_WRITE_CB(writeSET);
PPM_REG_WRITE_CB(writeSST);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
