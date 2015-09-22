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

typedef struct io_reg_dataS { 
    union { 
        Uns8 value;
    } io0;
    union { 
        Uns8 value;
    } io1;
} io_reg_dataT, *io_reg_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern io_reg_dataT io_reg_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle cascade;
    void                 *io;
    void                 *PCIackS;
    void                 *elcr;
    ppmNetHandle          ir0;
    ppmNetHandle          ir1;
    ppmNetHandle          ir2;
    ppmNetHandle          ir3;
    ppmNetHandle          ir4;
    ppmNetHandle          ir5;
    ppmNetHandle          ir6;
    ppmNetHandle          ir7;
    ppmNetHandle          cas;
    ppmNetHandle          intp;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(CB_ior0);
PPM_REG_READ_CB(CB_ior1);
PPM_REG_WRITE_CB(CB_iow0);
PPM_REG_WRITE_CB(CB_iow1);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif