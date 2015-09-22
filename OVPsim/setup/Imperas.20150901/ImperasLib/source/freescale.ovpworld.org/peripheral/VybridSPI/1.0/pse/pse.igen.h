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
            unsigned HALT : 1;
            unsigned PES : 1;
            unsigned FCPCS : 1;
            unsigned __pad3 : 5;
            unsigned SMPL_PT : 2;
            unsigned CLR_RXF : 1;
            unsigned CLR_TXF : 1;
            unsigned DIS_RXF : 1;
            unsigned DIS_TXF : 1;
            unsigned MDIS : 1;
            unsigned __pad15 : 1;
            unsigned PCSIS : 6;
            unsigned __pad22 : 2;
            unsigned ROOE : 1;
            unsigned PCSSE : 1;
            unsigned MTFE : 1;
            unsigned FRZ : 1;
            unsigned DCONF : 2;
            unsigned CONT_SCKE : 1;
            unsigned MSTR : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned SPI_TCNT : 16;
        } bits;
    } TCR;
    union { 
        Uns32 value;
        struct {
            unsigned BR : 4;
            unsigned DT : 4;
            unsigned ASC : 4;
            unsigned CSSCK : 4;
            unsigned PBR : 2;
            unsigned PDT : 2;
            unsigned PASC : 2;
            unsigned PCSSCK : 2;
            unsigned LSBFE : 1;
            unsigned CPHA : 1;
            unsigned CPOL : 1;
            unsigned FMSZ : 4;
            unsigned DBR : 1;
        } bits;
    } CTAR0;
    union { 
        Uns32 value;
        struct {
            unsigned BR : 4;
            unsigned DT : 4;
            unsigned ASC : 4;
            unsigned CSSCK : 4;
            unsigned PBR : 2;
            unsigned PDT : 2;
            unsigned PASC : 2;
            unsigned PCSSCK : 2;
            unsigned LSBFE : 1;
            unsigned CPHA : 1;
            unsigned CPOL : 1;
            unsigned FMSZ : 4;
            unsigned DBR : 1;
        } bits;
    } CTAR1;
    union { 
        Uns32 value;
        struct {
            unsigned BR : 4;
            unsigned DT : 4;
            unsigned ASC : 4;
            unsigned CSSCK : 4;
            unsigned PBR : 2;
            unsigned PDT : 2;
            unsigned PASC : 2;
            unsigned PCSSCK : 2;
            unsigned LSBFE : 1;
            unsigned CPHA : 1;
            unsigned CPOL : 1;
            unsigned FMSZ : 4;
            unsigned DBR : 1;
        } bits;
    } CTAR2;
    union { 
        Uns32 value;
        struct {
            unsigned BR : 4;
            unsigned DT : 4;
            unsigned ASC : 4;
            unsigned CSSCK : 4;
            unsigned PBR : 2;
            unsigned PDT : 2;
            unsigned PASC : 2;
            unsigned PCSSCK : 2;
            unsigned LSBFE : 1;
            unsigned CPHA : 1;
            unsigned CPOL : 1;
            unsigned FMSZ : 4;
            unsigned DBR : 1;
        } bits;
    } CTAR3;
    union { 
        Uns32 value;
        struct {
            unsigned POPNXTPTR : 4;
            unsigned RXCTR : 4;
            unsigned TXNXTPTR : 4;
            unsigned TXCTR : 4;
            unsigned __pad16 : 1;
            unsigned RFDF : 1;
            unsigned __pad18 : 1;
            unsigned RFOF : 1;
            unsigned __pad20 : 1;
            unsigned SPEF : 1;
            unsigned __pad22 : 3;
            unsigned TFFF : 1;
            unsigned __pad26 : 1;
            unsigned TFUF : 1;
            unsigned EOQF : 1;
            unsigned __pad29 : 1;
            unsigned TXRXS : 1;
            unsigned TCF : 1;
        } bits;
    } SR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned RFDF_DIRS : 1;
            unsigned RFDF_RE : 1;
            unsigned __pad18 : 1;
            unsigned RFOF_RE : 1;
            unsigned __pad20 : 1;
            unsigned SPEF_RE : 1;
            unsigned __pad22 : 2;
            unsigned TFFF_DIRS : 1;
            unsigned TFFF_RE : 1;
            unsigned __pad26 : 1;
            unsigned TFUF_RE : 1;
            unsigned EOQF_RE : 1;
            unsigned __pad29 : 2;
            unsigned TCF_RE : 1;
        } bits;
    } RSER;
    union { 
        Uns32 value;
        struct {
            unsigned TXDATA : 16;
            unsigned PCS : 6;
            unsigned __pad22 : 2;
            unsigned PP_MCSC : 1;
            unsigned PE_MASC : 1;
            unsigned CTCNT : 1;
            unsigned EOQ : 1;
            unsigned CTAS : 3;
            unsigned CONT : 1;
        } bits;
    } PUSHR;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } POPR;
    union { 
        Uns32 value;
        struct {
            unsigned TXDATA : 16;
            unsigned TXCMD_TXDATA : 16;
        } bits;
    } TXFR0;
    union { 
        Uns32 value;
        struct {
            unsigned TXDATA : 16;
            unsigned TXCMD_TXDATA : 16;
        } bits;
    } TXFR1;
    union { 
        Uns32 value;
        struct {
            unsigned TXDATA : 16;
            unsigned TXCMD_TXDATA : 16;
        } bits;
    } TXFR2;
    union { 
        Uns32 value;
        struct {
            unsigned TXDATA : 16;
            unsigned TXCMD_TXDATA : 16;
        } bits;
    } TXFR3;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RXFR0;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RXFR1;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RXFR2;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RXFR3;
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
