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
    } dr;
    union { 
        Uns8 value;
    } ecr;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned RXFE : 1;
            unsigned TXFF : 1;
            unsigned RXFF : 1;
            unsigned TXFE : 1;
        } bits;
    } flags;
    union { 
        Uns8 value;
    } ilpr;
    union { 
        Uns8 value;
    } ibrd;
    union { 
        Uns8 value;
    } vbrd;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned FEN : 1;
        } bits;
    } lcr;
    union { 
        Uns8 value;
    } cr;
    union { 
        Uns8 value;
    } ifl;
    union { 
        Uns8 value;
    } int_enabled;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned RX : 1;
            unsigned TX : 1;
        } bits;
    } int_level;
    union { 
        Uns8 value;
    } mis;
    union { 
        Uns8 value;
    } icr;
    union { 
        Uns8 value;
    } dmacr;
    union { 
        Uns32 value;
    } id0;
    union { 
        Uns32 value;
    } id1;
    union { 
        Uns32 value;
    } id2;
    union { 
        Uns32 value;
    } id3;
    union { 
        Uns32 value;
    } id4;
    union { 
        Uns32 value;
    } id5;
    union { 
        Uns32 value;
    } id6;
    union { 
        Uns32 value;
    } id7;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readDR);
PPM_REG_READ_CB(readECR);
PPM_REG_READ_CB(readID);
PPM_REG_READ_CB(readMIS);
PPM_REG_WRITE_CB(writeDMA);
PPM_REG_WRITE_CB(writeDR);
PPM_REG_WRITE_CB(writeICR);
PPM_REG_WRITE_CB(writeIFL);
PPM_REG_WRITE_CB(writeIMSC);
PPM_REG_WRITE_CB(writeLCR);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(closeDown);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
