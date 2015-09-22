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
        struct {
            unsigned sbr : 5;
        } bits;
    } bdh;
    union { 
        Uns8 value;
    } bdl;
    union { 
        Uns8 value;
    } c1;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 2;
            unsigned re : 1;
            unsigned te : 1;
            unsigned ilie : 1;
            unsigned rie : 1;
            unsigned tcie : 1;
            unsigned tie : 1;
        } bits;
    } c2;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned idle : 1;
            unsigned rdrf : 1;
            unsigned tc : 1;
            unsigned tdre : 1;
        } bits;
    } s1;
    union { 
        Uns8 value;
    } s2;
    union { 
        Uns8 value;
    } c3;
    union { 
        Uns8 value;
    } d;
    union { 
        Uns8 value;
    } ma1;
    union { 
        Uns8 value;
    } ma2;
    union { 
        Uns8 value;
        struct {
            unsigned brfa : 5;
        } bits;
    } c4;
    union { 
        Uns8 value;
    } c5;
    union { 
        Uns8 value;
    } ed;
    union { 
        Uns8 value;
    } modem;
    union { 
        Uns8 value;
    } infrared;
    union { 
        Uns8 value;
        struct {
            unsigned rxfifosize : 3;
            unsigned rxfe : 1;
            unsigned txfifosize : 3;
            unsigned txfe : 1;
        } bits;
    } pfifo;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 6;
            unsigned rxflush : 1;
            unsigned txflush : 1;
        } bits;
    } cfifo;
    union { 
        Uns8 value;
    } sfifo;
    union { 
        Uns8 value;
    } twfifo;
    union { 
        Uns8 value;
    } tcfifo;
    union { 
        Uns8 value;
    } rwfifo;
    union { 
        Uns8 value;
    } rcfifo;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          DirectWrite;
    ppmNetHandle          DirectRead;
    ppmNetHandle          Interrupt;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(directReadCB);
PPM_REG_READ_CB(readD);
PPM_REG_READ_CB(readS1);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(writeBDH);
PPM_REG_WRITE_CB(writeBDL);
PPM_REG_WRITE_CB(writeC2);
PPM_REG_WRITE_CB(writeC4);
PPM_REG_WRITE_CB(writeCFIFO);
PPM_REG_WRITE_CB(writeD);
PPM_REG_WRITE_CB(writeRWFIFO);
PPM_REG_WRITE_CB(writeTWFIFO);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
