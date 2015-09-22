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
            unsigned MPL7 : 1;
            unsigned MTW7 : 1;
            unsigned MTR7 : 1;
            unsigned __pad3 : 1;
            unsigned MPL6 : 1;
            unsigned MTW6 : 1;
            unsigned MTR6 : 1;
            unsigned __pad7 : 1;
            unsigned MPL5 : 1;
            unsigned MTW5 : 1;
            unsigned MTR5 : 1;
            unsigned __pad11 : 1;
            unsigned MPL4 : 1;
            unsigned MTW4 : 1;
            unsigned MTR4 : 1;
            unsigned __pad15 : 1;
            unsigned MPL3 : 1;
            unsigned MTW3 : 1;
            unsigned MTR3 : 1;
            unsigned __pad19 : 1;
            unsigned MPL2 : 1;
            unsigned MTW2 : 1;
            unsigned MTR2 : 1;
            unsigned __pad23 : 1;
            unsigned MPL1 : 1;
            unsigned MTW1 : 1;
            unsigned MTR1 : 1;
            unsigned __pad27 : 1;
            unsigned MPL0 : 1;
            unsigned MTW0 : 1;
            unsigned MTR0 : 1;
        } bits;
    } MPRA;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRA;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRB;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRC;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRD;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRE;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRF;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRG;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRH;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRI;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRJ;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRK;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRL;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRM;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRN;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRO;
    union { 
        Uns32 value;
        struct {
            unsigned TP7 : 1;
            unsigned WP7 : 1;
            unsigned SP7 : 1;
            unsigned __pad3 : 1;
            unsigned TP6 : 1;
            unsigned WP6 : 1;
            unsigned SP6 : 1;
            unsigned __pad7 : 1;
            unsigned TP5 : 1;
            unsigned WP5 : 1;
            unsigned SP5 : 1;
            unsigned __pad11 : 1;
            unsigned TP4 : 1;
            unsigned WP4 : 1;
            unsigned SP4 : 1;
            unsigned __pad15 : 1;
            unsigned TP3 : 1;
            unsigned WP3 : 1;
            unsigned SP3 : 1;
            unsigned __pad19 : 1;
            unsigned TP2 : 1;
            unsigned WP2 : 1;
            unsigned SP2 : 1;
            unsigned __pad23 : 1;
            unsigned TP1 : 1;
            unsigned WP1 : 1;
            unsigned SP1 : 1;
            unsigned __pad27 : 1;
            unsigned TP0 : 1;
            unsigned WP0 : 1;
            unsigned SP0 : 1;
        } bits;
    } PACRP;
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
