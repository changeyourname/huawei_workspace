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
    } PIO_PER;
    union { 
        Uns32 value;
    } PIO_PDR;
    union { 
        Uns32 value;
    } PIO_PSR;
    union { 
        Uns32 value;
    } PIO_OER;
    union { 
        Uns32 value;
    } PIO_ODR;
    union { 
        Uns32 value;
    } PIO_OSR;
    union { 
        Uns32 value;
    } PIO_IFER;
    union { 
        Uns32 value;
    } PIO_IFDR;
    union { 
        Uns32 value;
    } PIO_IFSR;
    union { 
        Uns32 value;
    } PIO_SODR;
    union { 
        Uns32 value;
    } PIO_CODR;
    union { 
        Uns32 value;
    } PIO_ODSR;
    union { 
        Uns32 value;
    } PIO_PDSR;
    union { 
        Uns32 value;
    } PIO_IER;
    union { 
        Uns32 value;
    } PIO_IDR;
    union { 
        Uns32 value;
    } PIO_IMR;
    union { 
        Uns32 value;
    } PIO_ISR;
} bp1_REG_dataT, *bp1_REG_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bp1_REG_dataT bp1_REG_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bp1;
    ppmNetHandle          P0;
    ppmNetHandle          P1;
    ppmNetHandle          P2;
    ppmNetHandle          P3;
    ppmNetHandle          P4;
    ppmNetHandle          P5;
    ppmNetHandle          P6;
    ppmNetHandle          P7;
    ppmNetHandle          P8;
    ppmNetHandle          P9;
    ppmNetHandle          P10;
    ppmNetHandle          P11;
    ppmNetHandle          P12;
    ppmNetHandle          P13;
    ppmNetHandle          P14;
    ppmNetHandle          P15;
    ppmNetHandle          P16;
    ppmNetHandle          P17;
    ppmNetHandle          P18;
    ppmNetHandle          P19;
    ppmNetHandle          P20;
    ppmNetHandle          P21;
    ppmNetHandle          P22;
    ppmNetHandle          P23;
    ppmNetHandle          P24;
    ppmNetHandle          P25;
    ppmNetHandle          P26;
    ppmNetHandle          P27;
    ppmNetHandle          P28;
    ppmNetHandle          P29;
    ppmNetHandle          P30;
    ppmNetHandle          P31;
    ppmNetHandle          IRQ;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(PIO_CODR_wcb);
PPM_REG_WRITE_CB(PIO_IDR_wcb);
PPM_REG_WRITE_CB(PIO_IER_wcb);
PPM_REG_WRITE_CB(PIO_IFDR_wcb);
PPM_REG_WRITE_CB(PIO_IFER_wcb);
PPM_REG_WRITE_CB(PIO_ODR_wcb);
PPM_REG_WRITE_CB(PIO_OER_wcb);
PPM_REG_WRITE_CB(PIO_PDR_wcb);
PPM_REG_WRITE_CB(PIO_PER_wcb);
PPM_REG_WRITE_CB(PIO_SODR_wcb);
PPM_NET_CB(P_wcb);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
