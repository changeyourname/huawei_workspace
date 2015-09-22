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
            unsigned SWRSTSD : 1;
            unsigned SWRSTHD : 1;
            unsigned END_CFG : 2;
            unsigned __pad4 : 2;
            unsigned DQS_EN : 1;
            unsigned DDR_EN : 1;
            unsigned __pad8 : 2;
            unsigned CLR_RXF : 1;
            unsigned CLR_TXF : 1;
            unsigned __pad12 : 2;
            unsigned MDIS : 1;
            unsigned __pad15 : 9;
            unsigned SCLKCFG : 8;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            unsigned IDATSZ : 16;
            unsigned PAR_EN : 1;
            unsigned __pad17 : 7;
            unsigned SEQID : 4;
        } bits;
    } IPCR;
    union { 
        Uns32 value;
        struct {
            unsigned TCSS : 4;
            unsigned __pad4 : 4;
            unsigned TCSH : 4;
        } bits;
    } FLSHCR;
    union { 
        Uns32 value;
        struct {
            unsigned MSTRID : 4;
            unsigned __pad4 : 4;
            unsigned ADATSZ : 8;
            unsigned __pad16 : 15;
            unsigned HP_EN : 1;
        } bits;
    } BUF0CR;
    union { 
        Uns32 value;
        struct {
            unsigned MSTRID : 4;
            unsigned __pad4 : 4;
            unsigned ADATSZ : 8;
        } bits;
    } BUF1CR;
    union { 
        Uns32 value;
        struct {
            unsigned MSTRID : 4;
            unsigned __pad4 : 4;
            unsigned ADATSZ : 8;
        } bits;
    } BUF2CR;
    union { 
        Uns32 value;
        struct {
            unsigned MSTRID : 4;
            unsigned __pad4 : 4;
            unsigned ADATSZ : 8;
            unsigned __pad16 : 15;
            unsigned ALLMST : 1;
        } bits;
    } BUF3CR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 12;
            unsigned SEQID : 4;
            unsigned PAR_EN : 1;
        } bits;
    } BFGENCR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned TPINDX0 : 29;
        } bits;
    } BUF0IND;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned TPINDX1 : 29;
        } bits;
    } BUF1IND;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 3;
            unsigned TPINDX2 : 29;
        } bits;
    } BUF2IND;
    union { 
        Uns32 value;
        struct {
            unsigned SFADR : 32;
        } bits;
    } SFAR;
    union { 
        Uns32 value;
        struct {
            unsigned HSENA : 1;
            unsigned HSPHS : 1;
            unsigned HSDLY : 1;
            unsigned __pad3 : 2;
            unsigned FSPHS : 1;
            unsigned FSDLY : 1;
            unsigned __pad7 : 9;
            unsigned DDRSMP : 3;
        } bits;
    } SMPR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 8;
            unsigned RDBFL : 6;
            unsigned __pad14 : 2;
            unsigned RDCTR : 16;
        } bits;
    } RBSR;
    union { 
        Uns32 value;
        struct {
            unsigned WMRK : 5;
            unsigned __pad5 : 3;
            unsigned RXBRD : 1;
        } bits;
    } RBCT;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 8;
            unsigned TRBFL : 5;
            unsigned __pad13 : 3;
            unsigned TRCTR : 16;
        } bits;
    } TBSR;
    union { 
        Uns32 value;
        struct {
            unsigned TXDATA : 32;
        } bits;
    } TBDR;
    union { 
        Uns32 value;
        struct {
            unsigned BUSY : 1;
            unsigned IP_ACC : 1;
            unsigned AHB_ACC : 1;
            unsigned __pad3 : 2;
            unsigned AHBGNT : 1;
            unsigned AHBTRN : 1;
            unsigned AHB0NE : 1;
            unsigned AHB1NE : 1;
            unsigned AHB2NE : 1;
            unsigned AHB3NE : 1;
            unsigned AHB0FUL : 1;
            unsigned AHB1FUL : 1;
            unsigned AHB2FUL : 1;
            unsigned AHB3FUL : 1;
            unsigned __pad15 : 1;
            unsigned RXWE : 1;
            unsigned __pad17 : 2;
            unsigned RXFULL : 1;
            unsigned __pad20 : 3;
            unsigned RXDMA : 1;
            unsigned TXNE : 1;
            unsigned __pad25 : 2;
            unsigned TXFULL : 1;
            unsigned __pad28 : 1;
            unsigned DLPSMP : 3;
        } bits;
    } SR;
    union { 
        Uns32 value;
        struct {
            unsigned TFF : 1;
            unsigned __pad1 : 3;
            unsigned IPGEF : 1;
            unsigned __pad5 : 1;
            unsigned IPIEF : 1;
            unsigned IPAEF : 1;
            unsigned __pad8 : 3;
            unsigned IUEF : 1;
            unsigned ABOF : 1;
            unsigned __pad13 : 2;
            unsigned ABSEF : 1;
            unsigned RBDF : 1;
            unsigned RBOF : 1;
            unsigned __pad18 : 5;
            unsigned ILLINE : 1;
            unsigned __pad24 : 2;
            unsigned TBUF : 1;
            unsigned TBFF : 1;
            unsigned __pad28 : 3;
            unsigned DLPFF : 1;
        } bits;
    } FR;
    union { 
        Uns32 value;
        struct {
            unsigned TFIE : 1;
            unsigned __pad1 : 3;
            unsigned IPGEIE : 1;
            unsigned __pad5 : 1;
            unsigned IPIEIE : 1;
            unsigned IPAEIE : 1;
            unsigned __pad8 : 3;
            unsigned IUEIE : 1;
            unsigned ABOIE : 1;
            unsigned __pad13 : 2;
            unsigned ABSEIE : 1;
            unsigned RBDIE : 1;
            unsigned RBOIE : 1;
            unsigned __pad18 : 3;
            unsigned RBDDE : 1;
            unsigned __pad22 : 1;
            unsigned ILLINIE : 1;
            unsigned __pad24 : 2;
            unsigned TBUIE : 1;
            unsigned TBFIE : 1;
            unsigned __pad28 : 3;
            unsigned DLPFIE : 1;
        } bits;
    } RSER;
    union { 
        Uns32 value;
        struct {
            unsigned SUSPND : 1;
            unsigned __pad1 : 5;
            unsigned SPDBUF : 2;
            unsigned __pad8 : 1;
            unsigned DATLFT : 7;
        } bits;
    } SPNDST;
    union { 
        Uns32 value;
        struct {
            unsigned BFPTRC : 1;
            unsigned __pad1 : 7;
            unsigned IPPTRC : 1;
        } bits;
    } SPTRCLR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 10;
            unsigned TPADA1 : 22;
        } bits;
    } SFA1AD;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 10;
            unsigned TPADA2 : 22;
        } bits;
    } SFA2AD;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 10;
            unsigned TPADB1 : 22;
        } bits;
    } SFB1AD;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 10;
            unsigned TPADB2 : 22;
        } bits;
    } SFB2AD;
    union { 
        Uns32 value;
        struct {
            unsigned KEY : 32;
        } bits;
    } LUTKEY;
    union { 
        Uns32 value;
        struct {
            unsigned LOCK : 1;
            unsigned UNLOCK : 1;
        } bits;
    } LCKCR;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR0;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR1;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR2;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR3;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR4;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR5;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR6;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR7;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR8;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR9;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR10;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR11;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR12;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR13;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR14;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR15;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR16;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR17;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR18;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR19;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR20;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR21;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR22;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR23;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR24;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR25;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR26;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR27;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR28;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR29;
    union { 
        Uns32 value;
        struct {
            unsigned RXDATA : 32;
        } bits;
    } RBDR30;
    union { 
        Uns32 value;
    } RBDR31;
    union { 
        Uns32 value;
    } RBDR32;
    union { 
        Uns32 value;
    } RBDR33;
    union { 
        Uns32 value;
    } RBDR34;
    union { 
        Uns32 value;
    } RBDR35;
    union { 
        Uns32 value;
    } RBDR36;
    union { 
        Uns32 value;
    } RBDR37;
    union { 
        Uns32 value;
    } RBDR38;
    union { 
        Uns32 value;
    } RBDR39;
    union { 
        Uns32 value;
    } RBDR40;
    union { 
        Uns32 value;
    } RBDR41;
    union { 
        Uns32 value;
    } RBDR42;
    union { 
        Uns32 value;
    } RBDR43;
    union { 
        Uns32 value;
    } RBDR44;
    union { 
        Uns32 value;
    } RBDR45;
    union { 
        Uns32 value;
    } RBDR46;
    union { 
        Uns32 value;
    } RBDR47;
    union { 
        Uns32 value;
    } RBDR48;
    union { 
        Uns32 value;
    } RBDR49;
    union { 
        Uns32 value;
    } RBDR50;
    union { 
        Uns32 value;
    } RBDR51;
    union { 
        Uns32 value;
    } RBDR52;
    union { 
        Uns32 value;
    } RBDR53;
    union { 
        Uns32 value;
    } RBDR54;
    union { 
        Uns32 value;
    } RBDR55;
    union { 
        Uns32 value;
    } RBDR56;
    union { 
        Uns32 value;
    } RBDR57;
    union { 
        Uns32 value;
    } RBDR58;
    union { 
        Uns32 value;
    } RBDR59;
    union { 
        Uns32 value;
    } RBDR60;
    union { 
        Uns32 value;
    } RBDR61;
    union { 
        Uns32 value;
    } RBDR62;
    union { 
        Uns32 value;
    } RBDR63;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT0;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT1;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT2;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT3;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT4;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT5;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT6;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT7;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT8;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT9;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT10;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT11;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT12;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT13;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT14;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT15;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT16;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT17;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT18;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT19;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT20;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT21;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT22;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT23;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT24;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT25;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT26;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT27;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT28;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT29;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT30;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT31;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT32;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT33;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT34;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT35;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT36;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT37;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT38;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT39;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT40;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT41;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT42;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT43;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT44;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT45;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT46;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT47;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT48;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT49;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT50;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT51;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT52;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT53;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT54;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT55;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT56;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT57;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT58;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT59;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT60;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT61;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT62;
    union { 
        Uns32 value;
        struct {
            unsigned OPRND0 : 8;
            unsigned PAD0 : 2;
            unsigned INSTR0 : 6;
            unsigned OPRND1 : 8;
            unsigned PAD1 : 2;
            unsigned INSTR1 : 6;
        } bits;
    } LUT63;
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

PPM_REG_READ_CB(readLutKey);
PPM_REG_READ_CB(readLutLck);
PPM_REG_WRITE_CB(writeLutKey);
PPM_REG_WRITE_CB(writeLutLck);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
