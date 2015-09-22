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
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG0;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG1;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG2;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG3;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG4;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG5;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG6;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG7;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG8;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG9;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG10;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG11;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG12;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG13;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG14;
    union { 
        Uns8 value;
        struct {
            unsigned SOURCE : 6;
            unsigned TRIG : 1;
            unsigned ENBL : 1;
        } bits;
    } CHCFG15;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          eDMARequest;
    ppmNetHandle          dmaSrc0;
    ppmNetHandle          dmaSrc1;
    ppmNetHandle          dmaSrc2;
    ppmNetHandle          dmaSrc3;
    ppmNetHandle          dmaSrc4;
    ppmNetHandle          dmaSrc5;
    ppmNetHandle          dmaSrc6;
    ppmNetHandle          dmaSrc7;
    ppmNetHandle          dmaSrc8;
    ppmNetHandle          dmaSrc9;
    ppmNetHandle          dmaSrc10;
    ppmNetHandle          dmaSrc11;
    ppmNetHandle          dmaSrc12;
    ppmNetHandle          dmaSrc13;
    ppmNetHandle          dmaSrc14;
    ppmNetHandle          dmaSrc15;
    ppmNetHandle          dmaSrc16;
    ppmNetHandle          dmaSrc17;
    ppmNetHandle          dmaSrc18;
    ppmNetHandle          dmaSrc19;
    ppmNetHandle          dmaSrc20;
    ppmNetHandle          dmaSrc21;
    ppmNetHandle          dmaSrc22;
    ppmNetHandle          dmaSrc23;
    ppmNetHandle          dmaSrc24;
    ppmNetHandle          dmaSrc25;
    ppmNetHandle          dmaSrc26;
    ppmNetHandle          dmaSrc27;
    ppmNetHandle          dmaSrc28;
    ppmNetHandle          dmaSrc29;
    ppmNetHandle          dmaSrc30;
    ppmNetHandle          dmaSrc31;
    ppmNetHandle          dmaSrc32;
    ppmNetHandle          dmaSrc33;
    ppmNetHandle          dmaSrc34;
    ppmNetHandle          dmaSrc35;
    ppmNetHandle          dmaSrc36;
    ppmNetHandle          dmaSrc37;
    ppmNetHandle          dmaSrc38;
    ppmNetHandle          dmaSrc39;
    ppmNetHandle          dmaSrc40;
    ppmNetHandle          dmaSrc41;
    ppmNetHandle          dmaSrc42;
    ppmNetHandle          dmaSrc43;
    ppmNetHandle          dmaSrc44;
    ppmNetHandle          dmaSrc45;
    ppmNetHandle          dmaSrc46;
    ppmNetHandle          dmaSrc47;
    ppmNetHandle          dmaSrc48;
    ppmNetHandle          dmaSrc49;
    ppmNetHandle          dmaSrc50;
    ppmNetHandle          dmaSrc51;
    ppmNetHandle          dmaSrc52;
    ppmNetHandle          dmaSrc53;
    ppmNetHandle          dmaSrc54;
    ppmNetHandle          dmaSrc55;
    ppmNetHandle          dmaSrc56;
    ppmNetHandle          dmaSrc57;
    ppmNetHandle          dmaSrc58;
    ppmNetHandle          dmaSrc59;
    ppmNetHandle          dmaSrc60;
    ppmNetHandle          dmaSrc61;
    ppmNetHandle          dmaSrc62;
    ppmNetHandle          dmaSrc63;
    ppmNetHandle          trg1;
    ppmNetHandle          trg2;
    ppmNetHandle          trg3;
    ppmNetHandle          trg4;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(dmaSrcRequest);
PPM_NET_CB(dmaTrgRequest);
PPM_REG_WRITE_CB(dmamuxWrite);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
