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
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR0;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR1;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR2;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR3;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR4;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR5;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR6;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR7;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR8;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR9;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR10;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR11;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR12;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR13;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR14;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR15;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR16;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR17;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR18;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR19;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR20;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR21;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR22;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR23;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR24;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR25;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR26;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR27;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR28;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR29;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR30;
    union { 
        Uns32 value;
        struct {
            unsigned PS : 1;
            unsigned PE : 1;
            unsigned SRE : 1;
            unsigned __pad3 : 1;
            unsigned PFE : 1;
            unsigned ODE : 1;
            unsigned DSE : 1;
            unsigned __pad7 : 1;
            unsigned MUX : 3;
            unsigned __pad11 : 4;
            unsigned LK : 1;
            unsigned IRQC : 4;
            unsigned __pad20 : 4;
            unsigned ISF : 1;
        } bits;
    } PCR31;
    union { 
        Uns32 value;
        struct {
            unsigned GPWD : 16;
            unsigned GPWE : 16;
        } bits;
    } GPCLR;
    union { 
        Uns32 value;
        struct {
            unsigned GPWD : 16;
            unsigned GPWE : 16;
        } bits;
    } GPCHR;
    union { 
        Uns32 value;
        struct {
            unsigned ISF : 32;
        } bits;
    } ISFR;
    union { 
        Uns32 value;
        struct {
            unsigned DFE : 32;
        } bits;
    } DFER;
    union { 
        Uns32 value;
        struct {
            unsigned CS : 1;
        } bits;
    } DFCR;
    union { 
        Uns32 value;
        struct {
            unsigned FILT : 5;
        } bits;
    } DFWR;
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
