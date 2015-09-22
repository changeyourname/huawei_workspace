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

typedef struct DMAP0_abc_dataS { 
    union { 
        Uns16 value;
    } DMAWC0;
    union { 
        Uns16 value;
    } DMAWC1;
} DMAP0_abc_dataT, *DMAP0_abc_dataTP;

typedef struct DMAP1_abw_dataS { 
    union { 
        Uns16 value;
    } MAR0;
    union { 
        Uns16 value;
    } MAR1;
    union { 
        Uns16 value;
    } MAR2;
    union { 
        Uns16 value;
    } MAR3;
    union { 
        Uns16 value;
    } MAR4;
    union { 
        Uns16 value;
    } MAR5;
    union { 
        Uns16 value;
    } MAR6;
    union { 
        Uns16 value;
    } MAR7;
    union { 
        Uns16 value;
    } MAR8;
    union { 
        Uns16 value;
    } MAR9;
} DMAP1_abw_dataT, *DMAP1_abw_dataTP;

typedef struct DMAP1_abb_dataS { 
    union { 
        Uns8 value;
        struct {
            unsigned SAR : 4;
        } bits;
    } SAR2;
    union { 
        Uns8 value;
        struct {
            unsigned SAR : 4;
        } bits;
    } SAR3;
    union { 
        Uns8 value;
        struct {
            unsigned IFCn : 3;
        } bits;
    } DTFR4;
    union { 
        Uns8 value;
        struct {
            unsigned IFCn : 3;
        } bits;
    } DTFR5;
    union { 
        Uns8 value;
        struct {
            unsigned IFCn : 3;
        } bits;
    } DTFR6;
    union { 
        Uns8 value;
        struct {
            unsigned IFCn : 3;
        } bits;
    } DTFR7;
    union { 
        Uns8 value;
    } DTCR0;
    union { 
        Uns8 value;
    } DTCR1;
    union { 
        Uns8 value;
    } DTCR2;
    union { 
        Uns8 value;
    } DTCR3;
    union { 
        Uns8 value;
    } DTCR4;
    union { 
        Uns8 value;
    } DTCR5;
    union { 
        Uns8 value;
    } DTCR6;
    union { 
        Uns8 value;
    } DTCR7;
    union { 
        Uns8 value;
    } DTCR8;
    union { 
        Uns8 value;
    } DTCR9;
    union { 
        Uns8 value;
        struct {
            unsigned DMAS0 : 1;
            unsigned DMAS1 : 1;
            unsigned DMAS2 : 1;
            unsigned DMAS3 : 1;
            unsigned DMAS4 : 1;
            unsigned DMAS5 : 1;
            unsigned DMAS6 : 1;
            unsigned DMAS7 : 1;
        } bits;
    } DMASL;
    union { 
        Uns8 value;
        struct {
            unsigned DE0 : 1;
            unsigned DE1 : 1;
            unsigned DE2 : 1;
            unsigned DE3 : 1;
            unsigned DE4 : 1;
            unsigned DE5 : 1;
            unsigned DE6 : 1;
            unsigned DE7 : 1;
        } bits;
    } DMAMCL;
    union { 
        Uns8 value;
        struct {
            unsigned __pad0 : 4;
            unsigned DMADCS4 : 1;
            unsigned DMADCS5 : 1;
            unsigned DMADCS6 : 1;
            unsigned DMADCS7 : 1;
        } bits;
    } DMADSCL;
} DMAP1_abb_dataT, *DMAP1_abb_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern DMAP0_abc_dataT DMAP0_abc_data;

extern DMAP1_abw_dataT DMAP1_abw_data;

extern DMAP1_abb_dataT DMAP1_abb_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle DMAPM;
    void                 *DMAP0;
    void                 *DMAP1;
    ppmNetHandle          INTDMA0;
    ppmNetHandle          INTDMA1;
    ppmNetHandle          INTDMA2;
    ppmNetHandle          INTDMA3;
    ppmNetHandle          INTDMA4;
    ppmNetHandle          INTDMA5;
    ppmNetHandle          INTDMA6;
    ppmNetHandle          INTDMA7;
    ppmNetHandle          INTDMA8;
    ppmNetHandle          INTDMA9;
    ppmNetHandle          DMA0EN;
    ppmNetHandle          DMA1EN;
    ppmNetHandle          ADDMARQ0;
    ppmNetHandle          ADDMARQ1;
    ppmNetHandle          INTTS0CD;
    ppmNetHandle          INTTS1CD;
    ppmNetHandle          INTCE0C;
    ppmNetHandle          INTCE1C;
    ppmNetHandle          INTBE0R;
    ppmNetHandle          INTBE1R;
    ppmNetHandle          INTUC0R;
    ppmNetHandle          INTUC1R;
    ppmNetHandle          INTUC2R;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readDMADSCL);
PPM_REG_READ_CB(readDMAMCL);
PPM_REG_READ_CB(readDMASL);
PPM_REG_READ_CB(readDMAWC0);
PPM_REG_READ_CB(readDMAWC1);
PPM_REG_READ_CB(readDTCR0);
PPM_REG_READ_CB(readDTCR1);
PPM_REG_READ_CB(readDTCR2);
PPM_REG_READ_CB(readDTCR3);
PPM_REG_READ_CB(readDTCR4);
PPM_REG_READ_CB(readDTCR5);
PPM_REG_READ_CB(readDTCR6);
PPM_REG_READ_CB(readDTCR7);
PPM_REG_READ_CB(readDTCR8);
PPM_REG_READ_CB(readDTCR9);
PPM_REG_READ_CB(readDTFR4);
PPM_REG_READ_CB(readDTFR5);
PPM_REG_READ_CB(readDTFR6);
PPM_REG_READ_CB(readDTFR7);
PPM_REG_READ_CB(readMAR0);
PPM_REG_READ_CB(readMAR1);
PPM_REG_READ_CB(readMAR2);
PPM_REG_READ_CB(readMAR3);
PPM_REG_READ_CB(readMAR4);
PPM_REG_READ_CB(readMAR5);
PPM_REG_READ_CB(readMAR6);
PPM_REG_READ_CB(readMAR7);
PPM_REG_READ_CB(readMAR8);
PPM_REG_READ_CB(readMAR9);
PPM_REG_READ_CB(readSAR2);
PPM_REG_READ_CB(readSAR3);
PPM_NET_CB(triggerADDMARQ0);
PPM_NET_CB(triggerADDMARQ1);
PPM_NET_CB(triggerINTBE0R);
PPM_NET_CB(triggerINTBE1R);
PPM_NET_CB(triggerINTCE0C);
PPM_NET_CB(triggerINTCE1C);
PPM_NET_CB(triggerINTTS0CD);
PPM_NET_CB(triggerINTTS1CD);
PPM_NET_CB(triggerINTUC0R);
PPM_NET_CB(triggerINTUC1R);
PPM_NET_CB(triggerINTUC2R);
PPM_REG_WRITE_CB(writeDMADSCL);
PPM_REG_WRITE_CB(writeDMAMCL);
PPM_REG_WRITE_CB(writeDMASL);
PPM_REG_WRITE_CB(writeDMAWC0);
PPM_REG_WRITE_CB(writeDMAWC1);
PPM_REG_WRITE_CB(writeDTCR0);
PPM_REG_WRITE_CB(writeDTCR1);
PPM_REG_WRITE_CB(writeDTCR2);
PPM_REG_WRITE_CB(writeDTCR3);
PPM_REG_WRITE_CB(writeDTCR4);
PPM_REG_WRITE_CB(writeDTCR5);
PPM_REG_WRITE_CB(writeDTCR6);
PPM_REG_WRITE_CB(writeDTCR7);
PPM_REG_WRITE_CB(writeDTCR8);
PPM_REG_WRITE_CB(writeDTCR9);
PPM_REG_WRITE_CB(writeDTFR4);
PPM_REG_WRITE_CB(writeDTFR5);
PPM_REG_WRITE_CB(writeDTFR6);
PPM_REG_WRITE_CB(writeDTFR7);
PPM_REG_WRITE_CB(writeMAR0);
PPM_REG_WRITE_CB(writeMAR1);
PPM_REG_WRITE_CB(writeMAR2);
PPM_REG_WRITE_CB(writeMAR3);
PPM_REG_WRITE_CB(writeMAR4);
PPM_REG_WRITE_CB(writeMAR5);
PPM_REG_WRITE_CB(writeMAR6);
PPM_REG_WRITE_CB(writeMAR7);
PPM_REG_WRITE_CB(writeMAR8);
PPM_REG_WRITE_CB(writeMAR9);
PPM_REG_WRITE_CB(writeSAR2);
PPM_REG_WRITE_CB(writeSAR3);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
