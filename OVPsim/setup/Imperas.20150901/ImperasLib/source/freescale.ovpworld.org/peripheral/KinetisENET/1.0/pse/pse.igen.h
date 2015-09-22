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
            unsigned __pad0 : 15;
            unsigned TS_TIMER : 1;
            unsigned TS_AVAIL : 1;
            unsigned WAKEUP : 1;
            unsigned PLR : 1;
            unsigned UN : 1;
            unsigned RL : 1;
            unsigned LC : 1;
            unsigned EBERR : 1;
            unsigned MII : 1;
            unsigned RXB : 1;
            unsigned RXF : 1;
            unsigned TXB : 1;
            unsigned TXF : 1;
            unsigned GRA : 1;
            unsigned BABT : 1;
            unsigned BABR : 1;
        } bits;
    } EIR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 15;
            unsigned TS_TIMER : 1;
            unsigned TS_AVAIL : 1;
            unsigned WAKEUP : 1;
            unsigned PLR : 1;
            unsigned UN : 1;
            unsigned RL : 1;
            unsigned LC : 1;
            unsigned EBERR : 1;
            unsigned MII : 1;
            unsigned RXB : 1;
            unsigned RXF : 1;
            unsigned TXB : 1;
            unsigned TXF : 1;
            unsigned GRA : 1;
            unsigned BABT : 1;
            unsigned BABR : 1;
        } bits;
    } EIMR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned RDAR : 1;
        } bits;
    } RDAR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned TDAR : 1;
        } bits;
    } TDAR;
    union { 
        Uns32 value;
        struct {
            unsigned RESET : 1;
            unsigned ETHEREN : 1;
            unsigned MAGICEN : 1;
            unsigned SLEEP : 1;
            unsigned EN1588 : 1;
            unsigned __pad5 : 1;
            unsigned DBGEN : 1;
            unsigned STOPEN : 1;
            unsigned DBSWP : 1;
        } bits;
    } ECR;
    union { 
        Uns32 value;
        struct {
            unsigned DATA : 16;
            unsigned TA : 2;
            unsigned RA : 5;
            unsigned PA : 5;
            unsigned OP : 2;
            unsigned ST : 2;
        } bits;
    } MMFR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 1;
            unsigned MII_SPEED : 6;
            unsigned DIS_PRE : 1;
            unsigned HOLDTIME : 3;
        } bits;
    } MSCR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 29;
            unsigned MIB_CLEAR : 1;
            unsigned MIB_IDLE : 1;
            unsigned MIB_DIS : 1;
        } bits;
    } MIBC;
    union { 
        Uns32 value;
        struct {
            unsigned LOOP : 1;
            unsigned DRT : 1;
            unsigned MII_MODE : 1;
            unsigned PROM : 1;
            unsigned BC_REJ : 1;
            unsigned FCE : 1;
            unsigned __pad6 : 2;
            unsigned RMII_MODE : 1;
            unsigned RMII_10T : 1;
            unsigned __pad10 : 2;
            unsigned PADEN : 1;
            unsigned PAUFWD : 1;
            unsigned CRCFWD : 1;
            unsigned CFEN : 1;
            unsigned MAX_FL : 14;
            unsigned NLC : 1;
            unsigned GRS : 1;
        } bits;
    } RCR;
    union { 
        Uns32 value;
        struct {
            unsigned GTS : 1;
            unsigned __pad1 : 1;
            unsigned FDEN : 1;
            unsigned TFC_PAUSE : 1;
            unsigned RFC_PAUSE : 1;
            unsigned ADDSEL : 3;
            unsigned ADDINS : 1;
            unsigned CRCFWD : 1;
        } bits;
    } TCR;
    union { 
        Uns32 value;
        struct {
            unsigned PADDR1 : 32;
        } bits;
    } PALR;
    union { 
        Uns32 value;
        struct {
            unsigned TYPE : 16;
            unsigned PADDR2 : 16;
        } bits;
    } PAUR;
    union { 
        Uns32 value;
        struct {
            unsigned PAUSE_DUR : 16;
            unsigned OPCODE : 16;
        } bits;
    } OPD;
    union { 
        Uns32 value;
        struct {
            unsigned IADDR1 : 32;
        } bits;
    } IAUR;
    union { 
        Uns32 value;
        struct {
            unsigned IADDR2 : 32;
        } bits;
    } IALR;
    union { 
        Uns32 value;
        struct {
            unsigned GADDR1 : 32;
        } bits;
    } GAUR;
    union { 
        Uns32 value;
        struct {
            unsigned GADDR2 : 32;
        } bits;
    } GALR;
    union { 
        Uns32 value;
        struct {
            unsigned TFWR : 6;
            unsigned __pad6 : 2;
            unsigned STRFWD : 1;
        } bits;
    } TFWR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned R_DES_START : 29;
        } bits;
    } RDSR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned X_DES_START : 29;
        } bits;
    } TDSR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 4;
            unsigned R_BUF_SIZE : 10;
        } bits;
    } MRBR;
    union { 
        Uns32 value;
        struct {
            unsigned RX_SECTION_FULL : 8;
        } bits;
    } RSFL;
    union { 
        Uns32 value;
        struct {
            unsigned RX_SECTION_EMPTY : 8;
        } bits;
    } RSEM;
    union { 
        Uns32 value;
        struct {
            unsigned RX_ALMOST_EMPTY : 8;
        } bits;
    } RAEM;
    union { 
        Uns32 value;
        struct {
            unsigned RX_ALMOST_FULL : 8;
        } bits;
    } RAFL;
    union { 
        Uns32 value;
        struct {
            unsigned TX_SECTION_EMPTY : 8;
        } bits;
    } TSEM;
    union { 
        Uns32 value;
        struct {
            unsigned TX_ALMOST_EMPTY : 8;
        } bits;
    } TAEM;
    union { 
        Uns32 value;
        struct {
            unsigned TX_ALMOST_FULL : 8;
        } bits;
    } TAFL;
    union { 
        Uns32 value;
        struct {
            unsigned IPG : 5;
        } bits;
    } TIPG;
    union { 
        Uns32 value;
        struct {
            unsigned TRUNC_FL : 14;
        } bits;
    } FTRL;
    union { 
        Uns32 value;
        struct {
            unsigned SHIFT16 : 1;
            unsigned __pad1 : 2;
            unsigned IPCHK : 1;
            unsigned PROCHK : 1;
        } bits;
    } TACC;
    union { 
        Uns32 value;
        struct {
            unsigned PADREM : 1;
            unsigned IPDIS : 1;
            unsigned PRODIS : 1;
            unsigned __pad3 : 3;
            unsigned LINEDIS : 1;
            unsigned SHIFT16 : 1;
        } bits;
    } RACC;
    union { 
        Uns32 value;
    } RMON_T_DROP;
    union { 
        Uns32 value;
    } RMON_T_PACKETS;
    union { 
        Uns32 value;
    } RMON_T_BC_PKT;
    union { 
        Uns32 value;
    } RMON_T_MC_PKT;
    union { 
        Uns32 value;
    } RMON_T_CRC_ALIGN;
    union { 
        Uns32 value;
    } RMON_T_UNDERSIZE;
    union { 
        Uns32 value;
    } RMON_T_OVERSIZE;
    union { 
        Uns32 value;
    } RMON_T_FRAG;
    union { 
        Uns32 value;
    } RMON_T_JAB;
    union { 
        Uns32 value;
    } RMON_T_COL;
    union { 
        Uns32 value;
    } RMON_T_P64;
    union { 
        Uns32 value;
    } RMON_T_P65TO127;
    union { 
        Uns32 value;
    } RMON_T_P128TO255;
    union { 
        Uns32 value;
    } RMON_T_P256TO511;
    union { 
        Uns32 value;
    } RMON_T_P512TO1023;
    union { 
        Uns32 value;
    } RMON_T_P1024TO2047;
    union { 
        Uns32 value;
    } RMON_T_P_GTE2048;
    union { 
        Uns32 value;
    } RMON_T_OCTETS;
    union { 
        Uns32 value;
    } IEEE_T_DROP;
    union { 
        Uns32 value;
    } IEEE_T_FRAME_OK;
    union { 
        Uns32 value;
    } IEEE_T_1COL;
    union { 
        Uns32 value;
    } IEEE_T_MCOL;
    union { 
        Uns32 value;
    } IEEE_T_DEF;
    union { 
        Uns32 value;
    } IEEE_T_LCOL;
    union { 
        Uns32 value;
    } IEEE_T_EXCOL;
    union { 
        Uns32 value;
    } IEEE_T_MACERR;
    union { 
        Uns32 value;
    } IEEE_T_CSERR;
    union { 
        Uns32 value;
    } IEEE_T_SQE;
    union { 
        Uns32 value;
    } IEEE_T_FDXFC;
    union { 
        Uns32 value;
    } IEEE_T_OCTETS_OK;
    union { 
        Uns32 value;
    } RMON_R_PACKETS;
    union { 
        Uns32 value;
    } RMON_R_BC_PKT;
    union { 
        Uns32 value;
    } RMON_R_MC_PKT;
    union { 
        Uns32 value;
    } RMON_R_CRC_ALIGN;
    union { 
        Uns32 value;
    } RMON_R_UNDERSIZE;
    union { 
        Uns32 value;
    } RMON_R_OVERSIZE;
    union { 
        Uns32 value;
    } RMON_R_FRAG;
    union { 
        Uns32 value;
    } RMON_R_JAB;
    union { 
        Uns32 value;
    } RMON_R_RESVD_0;
    union { 
        Uns32 value;
    } RMON_R_P64;
    union { 
        Uns32 value;
    } RMON_R_P65TO127;
    union { 
        Uns32 value;
    } RMON_R_P128TO255;
    union { 
        Uns32 value;
    } RMON_R_P256TO511;
    union { 
        Uns32 value;
    } RMON_R_P512TO1023;
    union { 
        Uns32 value;
    } RMON_R_P1024TO2047;
    union { 
        Uns32 value;
    } RMON_R_P_GTE2048;
    union { 
        Uns32 value;
    } RMON_R_OCTETS;
    union { 
        Uns32 value;
    } RMON_R_DROP;
    union { 
        Uns32 value;
    } RMON_R_FRAME_OK;
    union { 
        Uns32 value;
    } IEEE_R_CRC;
    union { 
        Uns32 value;
    } IEEE_R_ALIGN;
    union { 
        Uns32 value;
    } IEEE_R_MACERR;
    union { 
        Uns32 value;
    } IEEE_R_FDXFC;
    union { 
        Uns32 value;
    } IEEE_R_OCTETS_OK;
    union { 
        Uns32 value;
        struct {
            unsigned EN : 1;
            unsigned __pad1 : 1;
            unsigned OFFEN : 1;
            unsigned OFFRST : 1;
            unsigned PEREN : 1;
            unsigned __pad5 : 2;
            unsigned PINPER : 1;
            unsigned __pad8 : 1;
            unsigned RESTART : 1;
            unsigned __pad10 : 1;
            unsigned CAPTURE : 1;
            unsigned __pad12 : 1;
            unsigned SLAVE : 1;
        } bits;
    } ATCR;
    union { 
        Uns32 value;
        struct {
            unsigned ATIME : 32;
        } bits;
    } ATVR;
    union { 
        Uns32 value;
        struct {
            unsigned OFFSET : 32;
        } bits;
    } ATOFF;
    union { 
        Uns32 value;
        struct {
            unsigned PERIOD : 32;
        } bits;
    } ATPER;
    union { 
        Uns32 value;
        struct {
            unsigned COR : 31;
        } bits;
    } ATCOR;
    union { 
        Uns32 value;
        struct {
            unsigned INC : 7;
            unsigned __pad7 : 1;
            unsigned INC_CORR : 7;
        } bits;
    } ATINC;
    union { 
        Uns32 value;
        struct {
            unsigned TIMESTAMP : 32;
        } bits;
    } ATSTMP;
    union { 
        Uns32 value;
        struct {
            unsigned TF0 : 1;
            unsigned TF1 : 1;
            unsigned TF2 : 1;
            unsigned TF3 : 1;
        } bits;
    } TGSR;
    union { 
        Uns32 value;
        struct {
            unsigned TDRE : 1;
            unsigned __pad1 : 1;
            unsigned TMODE : 4;
            unsigned TIE : 1;
            unsigned TF : 1;
        } bits;
    } TCSR0;
    union { 
        Uns32 value;
        struct {
            unsigned TCC : 32;
        } bits;
    } TCCR0;
    union { 
        Uns32 value;
        struct {
            unsigned TDRE : 1;
            unsigned __pad1 : 1;
            unsigned TMODE : 4;
            unsigned TIE : 1;
            unsigned TF : 1;
        } bits;
    } TCSR1;
    union { 
        Uns32 value;
        struct {
            unsigned TCC : 32;
        } bits;
    } TCCR1;
    union { 
        Uns32 value;
        struct {
            unsigned TDRE : 1;
            unsigned __pad1 : 1;
            unsigned TMODE : 4;
            unsigned TIE : 1;
            unsigned TF : 1;
        } bits;
    } TCSR2;
    union { 
        Uns32 value;
        struct {
            unsigned TCC : 32;
        } bits;
    } TCCR2;
    union { 
        Uns32 value;
        struct {
            unsigned TDRE : 1;
            unsigned __pad1 : 1;
            unsigned TMODE : 4;
            unsigned TIE : 1;
            unsigned TF : 1;
        } bits;
    } TCSR3;
    union { 
        Uns32 value;
        struct {
            unsigned TCC : 32;
        } bits;
    } TCCR3;
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
