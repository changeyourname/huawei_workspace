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
        struct {
            unsigned TSR : 32;
        } bits;
    } TSR;
    union { 
        Uns32 value;
        struct {
            unsigned TPR : 16;
        } bits;
    } TPR;
    union { 
        Uns32 value;
        struct {
            unsigned TAR : 32;
        } bits;
    } TAR;
    union { 
        Uns32 value;
        struct {
            unsigned TCR : 8;
            unsigned CIR : 8;
            unsigned TCV : 8;
            unsigned CIC : 8;
        } bits;
    } TCR;
    union { 
        Uns32 value;
        struct {
            unsigned SWR : 1;
            unsigned WPE : 1;
            unsigned SUP : 1;
            unsigned UM : 1;
            unsigned __pad4 : 4;
            unsigned OSCE : 1;
            unsigned CLKO : 1;
            unsigned SC16P : 1;
            unsigned SC8P : 1;
            unsigned SC4P : 1;
            unsigned SC2P : 1;
        } bits;
    } CR;
    union { 
        Uns32 value;
        struct {
            unsigned TIF : 1;
            unsigned TOF : 1;
            unsigned TAF : 1;
            unsigned MOF : 1;
            unsigned TCE : 1;
        } bits;
    } SR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned TCL : 1;
            unsigned CRL : 1;
            unsigned SRL : 1;
            unsigned LRL : 1;
            unsigned __pad7 : 1;
            unsigned TTSL : 1;
            unsigned MEL : 1;
            unsigned MCLL : 1;
            unsigned MCHL : 1;
            unsigned TEL : 1;
            unsigned TDL : 1;
            unsigned TTL : 1;
            unsigned TIL : 1;
        } bits;
    } LR;
    union { 
        Uns32 value;
        struct {
            unsigned TIIE : 1;
            unsigned TOIE : 1;
            unsigned TAIE : 1;
            unsigned MOIE : 1;
            unsigned TSIE : 1;
        } bits;
    } IER;
    union { 
        Uns32 value;
        struct {
            unsigned TTS : 32;
        } bits;
    } TTSR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 4;
            unsigned MCE : 1;
        } bits;
    } MER;
    union { 
        Uns32 value;
        struct {
            unsigned MCL : 32;
        } bits;
    } MCLR;
    union { 
        Uns32 value;
        struct {
            unsigned MCH : 32;
        } bits;
    } MCHR;
    union { 
        Uns32 value;
        struct {
            unsigned DTE : 1;
            unsigned VTE : 1;
            unsigned CTE : 1;
            unsigned TTE : 1;
            unsigned FSE : 1;
            unsigned TME : 1;
        } bits;
    } TER;
    union { 
        Uns32 value;
        struct {
            unsigned DTF : 1;
            unsigned VTF : 1;
            unsigned CTF : 1;
            unsigned TTF : 1;
            unsigned FSF : 1;
            unsigned TMF : 1;
        } bits;
    } TDR;
    union { 
        Uns32 value;
        struct {
            unsigned VDTL : 3;
            unsigned VDTH : 3;
            unsigned CDTH : 3;
            unsigned CDTL : 3;
            unsigned TDTH : 3;
            unsigned TDTL : 3;
        } bits;
    } TTR;
    union { 
        Uns32 value;
        struct {
            unsigned DTIE : 1;
            unsigned VTIE : 1;
            unsigned CTIE : 1;
            unsigned TTIE : 1;
            unsigned FSIE : 1;
            unsigned TMIE : 1;
        } bits;
    } TIR;
    union { 
        Uns32 value;
        struct {
            unsigned TSRW : 1;
            unsigned TPRW : 1;
            unsigned TARW : 1;
            unsigned TCRW : 1;
            unsigned CRW : 1;
            unsigned SRW : 1;
            unsigned LRW : 1;
            unsigned IERW : 1;
            unsigned TTSW : 1;
            unsigned MERW : 1;
            unsigned MCLW : 1;
            unsigned MCHW : 1;
            unsigned TERW : 1;
            unsigned TDRW : 1;
            unsigned TTRW : 1;
            unsigned TIRW : 1;
        } bits;
    } WAR;
    union { 
        Uns32 value;
        struct {
            unsigned TSRR : 1;
            unsigned TPRR : 1;
            unsigned TARR : 1;
            unsigned TCRR : 1;
            unsigned CRR : 1;
            unsigned SRR : 1;
            unsigned LRR : 1;
            unsigned IERR : 1;
            unsigned TTSR : 1;
            unsigned MERR : 1;
            unsigned MCLR : 1;
            unsigned MCHR : 1;
            unsigned TERR : 1;
            unsigned TDRR : 1;
            unsigned TTRR : 1;
            unsigned TIRR : 1;
        } bits;
    } RAR;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
