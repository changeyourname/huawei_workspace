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
            unsigned __pad0 : 1;
            unsigned EDBG : 1;
            unsigned ERCA : 1;
            unsigned ERGA : 1;
            unsigned HOE : 1;
            unsigned HALT : 1;
            unsigned CLM : 1;
            unsigned EMLM : 1;
            unsigned GRP0PRI : 2;
            unsigned GRP1PRI : 2;
            unsigned __pad12 : 4;
            unsigned ECX : 1;
            unsigned CX : 1;
        } bits;
    } CR;
    union { 
        Uns32 value;
        struct {
            unsigned DBE : 1;
            unsigned SBE : 1;
            unsigned SGE : 1;
            unsigned NCE : 1;
            unsigned DOE : 1;
            unsigned DAE : 1;
            unsigned SOE : 1;
            unsigned SAE : 1;
            unsigned ERRCHN : 5;
            unsigned __pad13 : 1;
            unsigned CPE : 1;
            unsigned GPE : 1;
            unsigned ECX : 1;
            unsigned __pad17 : 14;
            unsigned VLD : 1;
        } bits;
    } ES;
    union { 
        Uns32 value;
        struct {
            unsigned ERQ0 : 1;
            unsigned ERQ1 : 1;
            unsigned ERQ2 : 1;
            unsigned ERQ3 : 1;
            unsigned ERQ4 : 1;
            unsigned ERQ5 : 1;
            unsigned ERQ6 : 1;
            unsigned ERQ7 : 1;
            unsigned ERQ8 : 1;
            unsigned ERQ9 : 1;
            unsigned ERQ10 : 1;
            unsigned ERQ11 : 1;
            unsigned ERQ12 : 1;
            unsigned ERQ13 : 1;
            unsigned ERQ14 : 1;
            unsigned ERQ15 : 1;
            unsigned ERQ16 : 1;
            unsigned ERQ17 : 1;
            unsigned ERQ18 : 1;
            unsigned ERQ19 : 1;
            unsigned ERQ20 : 1;
            unsigned ERQ21 : 1;
            unsigned ERQ22 : 1;
            unsigned ERQ23 : 1;
            unsigned ERQ24 : 1;
            unsigned ERQ25 : 1;
            unsigned ERQ26 : 1;
            unsigned ERQ27 : 1;
            unsigned ERQ28 : 1;
            unsigned ERQ29 : 1;
            unsigned ERQ30 : 1;
            unsigned ERQ31 : 1;
        } bits;
    } ERQ;
    union { 
        Uns32 value;
        struct {
            unsigned EEI0 : 1;
            unsigned EEI1 : 1;
            unsigned EEI2 : 1;
            unsigned EEI3 : 1;
            unsigned EEI4 : 1;
            unsigned EEI5 : 1;
            unsigned EEI6 : 1;
            unsigned EEI7 : 1;
            unsigned EEI8 : 1;
            unsigned EEI9 : 1;
            unsigned EEI10 : 1;
            unsigned EEI11 : 1;
            unsigned EEI12 : 1;
            unsigned EEI13 : 1;
            unsigned EEI14 : 1;
            unsigned EEI15 : 1;
            unsigned EEI16 : 1;
            unsigned EEI17 : 1;
            unsigned EEI18 : 1;
            unsigned EEI19 : 1;
            unsigned EEI20 : 1;
            unsigned EEI21 : 1;
            unsigned EEI22 : 1;
            unsigned EEI23 : 1;
            unsigned EEI24 : 1;
            unsigned EEI25 : 1;
            unsigned EEI26 : 1;
            unsigned EEI27 : 1;
            unsigned EEI28 : 1;
            unsigned EEI29 : 1;
            unsigned EEI30 : 1;
            unsigned EEI31 : 1;
        } bits;
    } EEI;
    union { 
        Uns32 value;
    } CS_EEI_ERC;
    union { 
        Uns32 value;
    } DNE_SRT_ERR_INT;
    union { 
        Uns32 value;
        struct {
            unsigned INT0 : 1;
            unsigned INT1 : 1;
            unsigned INT2 : 1;
            unsigned INT3 : 1;
            unsigned INT4 : 1;
            unsigned INT5 : 1;
            unsigned INT6 : 1;
            unsigned INT7 : 1;
            unsigned INT8 : 1;
            unsigned INT9 : 1;
            unsigned INT10 : 1;
            unsigned INT11 : 1;
            unsigned INT12 : 1;
            unsigned INT13 : 1;
            unsigned INT14 : 1;
            unsigned INT15 : 1;
            unsigned INT16 : 1;
            unsigned INT17 : 1;
            unsigned INT18 : 1;
            unsigned INT19 : 1;
            unsigned INT20 : 1;
            unsigned INT21 : 1;
            unsigned INT22 : 1;
            unsigned INT23 : 1;
            unsigned INT24 : 1;
            unsigned INT25 : 1;
            unsigned INT26 : 1;
            unsigned INT27 : 1;
            unsigned INT28 : 1;
            unsigned INT29 : 1;
            unsigned INT30 : 1;
            unsigned INT31 : 1;
        } bits;
    } INT;
    union { 
        Uns32 value;
        struct {
            unsigned ERR0 : 1;
            unsigned ERR1 : 1;
            unsigned ERR2 : 1;
            unsigned ERR3 : 1;
            unsigned ERR4 : 1;
            unsigned ERR5 : 1;
            unsigned ERR6 : 1;
            unsigned ERR7 : 1;
            unsigned ERR8 : 1;
            unsigned ERR9 : 1;
            unsigned ERR10 : 1;
            unsigned ERR11 : 1;
            unsigned ERR12 : 1;
            unsigned ERR13 : 1;
            unsigned ERR14 : 1;
            unsigned ERR15 : 1;
            unsigned ERR16 : 1;
            unsigned ERR17 : 1;
            unsigned ERR18 : 1;
            unsigned ERR19 : 1;
            unsigned ERR20 : 1;
            unsigned ERR21 : 1;
            unsigned ERR22 : 1;
            unsigned ERR23 : 1;
            unsigned ERR24 : 1;
            unsigned ERR25 : 1;
            unsigned ERR26 : 1;
            unsigned ERR27 : 1;
            unsigned ERR28 : 1;
            unsigned ERR29 : 1;
            unsigned ERR30 : 1;
            unsigned ERR31 : 1;
        } bits;
    } ERR;
    union { 
        Uns32 value;
        struct {
            unsigned HRS0 : 1;
            unsigned HRS1 : 1;
            unsigned HRS2 : 1;
            unsigned HRS3 : 1;
            unsigned HRS4 : 1;
            unsigned HRS5 : 1;
            unsigned HRS6 : 1;
            unsigned HRS7 : 1;
            unsigned HRS8 : 1;
            unsigned HRS9 : 1;
            unsigned HRS10 : 1;
            unsigned HRS11 : 1;
            unsigned HRS12 : 1;
            unsigned HRS13 : 1;
            unsigned HRS14 : 1;
            unsigned HRS15 : 1;
            unsigned HRS16 : 1;
            unsigned HRS17 : 1;
            unsigned HRS18 : 1;
            unsigned HRS19 : 1;
            unsigned HRS20 : 1;
            unsigned HRS21 : 1;
            unsigned HRS22 : 1;
            unsigned HRS23 : 1;
            unsigned HRS24 : 1;
            unsigned HRS25 : 1;
            unsigned HRS26 : 1;
            unsigned HRS27 : 1;
            unsigned HRS28 : 1;
            unsigned HRS29 : 1;
            unsigned HRS30 : 1;
            unsigned HRS31 : 1;
        } bits;
    } HRS;
    union { 
        Uns32 value;
    } DCHPRI3_0;
    union { 
        Uns32 value;
    } DCHPRI7_4;
    union { 
        Uns32 value;
    } DCHPRI11_8;
    union { 
        Uns32 value;
    } DCHPRI15_12;
    union { 
        Uns32 value;
    } DCHPRI19_16;
    union { 
        Uns32 value;
    } DCHPRI23_20;
    union { 
        Uns32 value;
    } DCHPRI27_24;
    union { 
        Uns32 value;
    } DCHPRI31_28;
    union { 
        Uns32 value;
    } TCD0_SADDR;
    union { 
        Uns32 value;
    } TCD0_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD0_NBYTES;
    union { 
        Uns32 value;
    } TCD0_SLAST;
    union { 
        Uns32 value;
    } TCD0_DADDR;
    union { 
        Uns32 value;
    } TCD0_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD0_DLASTSGA;
    union { 
        Uns32 value;
    } TCD0_CSR_BITER;
    union { 
        Uns32 value;
    } TCD1_SADDR;
    union { 
        Uns32 value;
    } TCD1_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD1_NBYTES;
    union { 
        Uns32 value;
    } TCD1_SLAST;
    union { 
        Uns32 value;
    } TCD1_DADDR;
    union { 
        Uns32 value;
    } TCD1_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD1_DLASTSGA;
    union { 
        Uns32 value;
    } TCD1_CSR_BITER;
    union { 
        Uns32 value;
    } TCD2_SADDR;
    union { 
        Uns32 value;
    } TCD2_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD2_NBYTES;
    union { 
        Uns32 value;
    } TCD2_SLAST;
    union { 
        Uns32 value;
    } TCD2_DADDR;
    union { 
        Uns32 value;
    } TCD2_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD2_DLASTSGA;
    union { 
        Uns32 value;
    } TCD2_CSR_BITER;
    union { 
        Uns32 value;
    } TCD3_SADDR;
    union { 
        Uns32 value;
    } TCD3_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD3_NBYTES;
    union { 
        Uns32 value;
    } TCD3_SLAST;
    union { 
        Uns32 value;
    } TCD3_DADDR;
    union { 
        Uns32 value;
    } TCD3_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD3_DLASTSGA;
    union { 
        Uns32 value;
    } TCD3_CSR_BITER;
    union { 
        Uns32 value;
    } TCD4_SADDR;
    union { 
        Uns32 value;
    } TCD4_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD4_NBYTES;
    union { 
        Uns32 value;
    } TCD4_SLAST;
    union { 
        Uns32 value;
    } TCD4_DADDR;
    union { 
        Uns32 value;
    } TCD4_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD4_DLASTSGA;
    union { 
        Uns32 value;
    } TCD4_CSR_BITER;
    union { 
        Uns32 value;
    } TCD5_SADDR;
    union { 
        Uns32 value;
    } TCD5_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD5_NBYTES;
    union { 
        Uns32 value;
    } TCD5_SLAST;
    union { 
        Uns32 value;
    } TCD5_DADDR;
    union { 
        Uns32 value;
    } TCD5_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD5_DLASTSGA;
    union { 
        Uns32 value;
    } TCD5_CSR_BITER;
    union { 
        Uns32 value;
    } TCD6_SADDR;
    union { 
        Uns32 value;
    } TCD6_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD6_NBYTES;
    union { 
        Uns32 value;
    } TCD6_SLAST;
    union { 
        Uns32 value;
    } TCD6_DADDR;
    union { 
        Uns32 value;
    } TCD6_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD6_DLASTSGA;
    union { 
        Uns32 value;
    } TCD6_CSR_BITER;
    union { 
        Uns32 value;
    } TCD7_SADDR;
    union { 
        Uns32 value;
    } TCD7_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD7_NBYTES;
    union { 
        Uns32 value;
    } TCD7_SLAST;
    union { 
        Uns32 value;
    } TCD7_DADDR;
    union { 
        Uns32 value;
    } TCD7_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD7_DLASTSGA;
    union { 
        Uns32 value;
    } TCD7_CSR_BITER;
    union { 
        Uns32 value;
    } TCD8_SADDR;
    union { 
        Uns32 value;
    } TCD8_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD8_NBYTES;
    union { 
        Uns32 value;
    } TCD8_SLAST;
    union { 
        Uns32 value;
    } TCD8_DADDR;
    union { 
        Uns32 value;
    } TCD8_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD8_DLASTSGA;
    union { 
        Uns32 value;
    } TCD8_CSR_BITER;
    union { 
        Uns32 value;
    } TCD9_SADDR;
    union { 
        Uns32 value;
    } TCD9_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD9_NBYTES;
    union { 
        Uns32 value;
    } TCD9_SLAST;
    union { 
        Uns32 value;
    } TCD9_DADDR;
    union { 
        Uns32 value;
    } TCD9_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD9_DLASTSGA;
    union { 
        Uns32 value;
    } TCD9_CSR_BITER;
    union { 
        Uns32 value;
    } TCD10_SADDR;
    union { 
        Uns32 value;
    } TCD10_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD10_NBYTES;
    union { 
        Uns32 value;
    } TCD10_SLAST;
    union { 
        Uns32 value;
    } TCD10_DADDR;
    union { 
        Uns32 value;
    } TCD10_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD10_DLASTSGA;
    union { 
        Uns32 value;
    } TCD10_CSR_BITER;
    union { 
        Uns32 value;
    } TCD11_SADDR;
    union { 
        Uns32 value;
    } TCD11_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD11_NBYTES;
    union { 
        Uns32 value;
    } TCD11_SLAST;
    union { 
        Uns32 value;
    } TCD11_DADDR;
    union { 
        Uns32 value;
    } TCD11_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD11_DLASTSGA;
    union { 
        Uns32 value;
    } TCD11_CSR_BITER;
    union { 
        Uns32 value;
    } TCD12_SADDR;
    union { 
        Uns32 value;
    } TCD12_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD12_NBYTES;
    union { 
        Uns32 value;
    } TCD12_SLAST;
    union { 
        Uns32 value;
    } TCD12_DADDR;
    union { 
        Uns32 value;
    } TCD12_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD12_DLASTSGA;
    union { 
        Uns32 value;
    } TCD12_CSR_BITER;
    union { 
        Uns32 value;
    } TCD13_SADDR;
    union { 
        Uns32 value;
    } TCD13_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD13_NBYTES;
    union { 
        Uns32 value;
    } TCD13_SLAST;
    union { 
        Uns32 value;
    } TCD13_DADDR;
    union { 
        Uns32 value;
    } TCD13_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD13_DLASTSGA;
    union { 
        Uns32 value;
    } TCD13_CSR_BITER;
    union { 
        Uns32 value;
    } TCD14_SADDR;
    union { 
        Uns32 value;
    } TCD14_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD14_NBYTES;
    union { 
        Uns32 value;
    } TCD14_SLAST;
    union { 
        Uns32 value;
    } TCD14_DADDR;
    union { 
        Uns32 value;
    } TCD14_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD14_DLASTSGA;
    union { 
        Uns32 value;
    } TCD14_CSR_BITER;
    union { 
        Uns32 value;
    } TCD15_SADDR;
    union { 
        Uns32 value;
    } TCD15_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD15_NBYTES;
    union { 
        Uns32 value;
    } TCD15_SLAST;
    union { 
        Uns32 value;
    } TCD15_DADDR;
    union { 
        Uns32 value;
    } TCD15_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD15_DLASTSGA;
    union { 
        Uns32 value;
    } TCD15_CSR_BITER;
    union { 
        Uns32 value;
    } TCD16_SADDR;
    union { 
        Uns32 value;
    } TCD16_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD16_NBYTES;
    union { 
        Uns32 value;
    } TCD16_SLAST;
    union { 
        Uns32 value;
    } TCD16_DADDR;
    union { 
        Uns32 value;
    } TCD16_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD16_DLASTSGA;
    union { 
        Uns32 value;
    } TCD16_CSR_BITER;
    union { 
        Uns32 value;
    } TCD17_SADDR;
    union { 
        Uns32 value;
    } TCD17_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD17_NBYTES;
    union { 
        Uns32 value;
    } TCD17_SLAST;
    union { 
        Uns32 value;
    } TCD17_DADDR;
    union { 
        Uns32 value;
    } TCD17_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD17_DLASTSGA;
    union { 
        Uns32 value;
    } TCD17_CSR_BITER;
    union { 
        Uns32 value;
    } TCD18_SADDR;
    union { 
        Uns32 value;
    } TCD18_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD18_NBYTES;
    union { 
        Uns32 value;
    } TCD18_SLAST;
    union { 
        Uns32 value;
    } TCD18_DADDR;
    union { 
        Uns32 value;
    } TCD18_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD18_DLASTSGA;
    union { 
        Uns32 value;
    } TCD18_CSR_BITER;
    union { 
        Uns32 value;
    } TCD19_SADDR;
    union { 
        Uns32 value;
    } TCD19_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD19_NBYTES;
    union { 
        Uns32 value;
    } TCD19_SLAST;
    union { 
        Uns32 value;
    } TCD19_DADDR;
    union { 
        Uns32 value;
    } TCD19_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD19_DLASTSGA;
    union { 
        Uns32 value;
    } TCD19_CSR_BITER;
    union { 
        Uns32 value;
    } TCD20_SADDR;
    union { 
        Uns32 value;
    } TCD20_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD20_NBYTES;
    union { 
        Uns32 value;
    } TCD20_SLAST;
    union { 
        Uns32 value;
    } TCD20_DADDR;
    union { 
        Uns32 value;
    } TCD20_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD20_DLASTSGA;
    union { 
        Uns32 value;
    } TCD20_CSR_BITER;
    union { 
        Uns32 value;
    } TCD21_SADDR;
    union { 
        Uns32 value;
    } TCD21_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD21_NBYTES;
    union { 
        Uns32 value;
    } TCD21_SLAST;
    union { 
        Uns32 value;
    } TCD21_DADDR;
    union { 
        Uns32 value;
    } TCD21_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD21_DLASTSGA;
    union { 
        Uns32 value;
    } TCD21_CSR_BITER;
    union { 
        Uns32 value;
    } TCD22_SADDR;
    union { 
        Uns32 value;
    } TCD22_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD22_NBYTES;
    union { 
        Uns32 value;
    } TCD22_SLAST;
    union { 
        Uns32 value;
    } TCD22_DADDR;
    union { 
        Uns32 value;
    } TCD22_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD22_DLASTSGA;
    union { 
        Uns32 value;
    } TCD22_CSR_BITER;
    union { 
        Uns32 value;
    } TCD23_SADDR;
    union { 
        Uns32 value;
    } TCD23_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD23_NBYTES;
    union { 
        Uns32 value;
    } TCD23_SLAST;
    union { 
        Uns32 value;
    } TCD23_DADDR;
    union { 
        Uns32 value;
    } TCD23_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD23_DLASTSGA;
    union { 
        Uns32 value;
    } TCD23_CSR_BITER;
    union { 
        Uns32 value;
    } TCD24_SADDR;
    union { 
        Uns32 value;
    } TCD24_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD24_NBYTES;
    union { 
        Uns32 value;
    } TCD24_SLAST;
    union { 
        Uns32 value;
    } TCD24_DADDR;
    union { 
        Uns32 value;
    } TCD24_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD24_DLASTSGA;
    union { 
        Uns32 value;
    } TCD24_CSR_BITER;
    union { 
        Uns32 value;
    } TCD25_SADDR;
    union { 
        Uns32 value;
    } TCD25_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD25_NBYTES;
    union { 
        Uns32 value;
    } TCD25_SLAST;
    union { 
        Uns32 value;
    } TCD25_DADDR;
    union { 
        Uns32 value;
    } TCD25_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD25_DLASTSGA;
    union { 
        Uns32 value;
    } TCD25_CSR_BITER;
    union { 
        Uns32 value;
    } TCD26_SADDR;
    union { 
        Uns32 value;
    } TCD26_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD26_NBYTES;
    union { 
        Uns32 value;
    } TCD26_SLAST;
    union { 
        Uns32 value;
    } TCD26_DADDR;
    union { 
        Uns32 value;
    } TCD26_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD26_DLASTSGA;
    union { 
        Uns32 value;
    } TCD26_CSR_BITER;
    union { 
        Uns32 value;
    } TCD27_SADDR;
    union { 
        Uns32 value;
    } TCD27_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD27_NBYTES;
    union { 
        Uns32 value;
    } TCD27_SLAST;
    union { 
        Uns32 value;
    } TCD27_DADDR;
    union { 
        Uns32 value;
    } TCD27_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD27_DLASTSGA;
    union { 
        Uns32 value;
    } TCD27_CSR_BITER;
    union { 
        Uns32 value;
    } TCD28_SADDR;
    union { 
        Uns32 value;
    } TCD28_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD28_NBYTES;
    union { 
        Uns32 value;
    } TCD28_SLAST;
    union { 
        Uns32 value;
    } TCD28_DADDR;
    union { 
        Uns32 value;
    } TCD28_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD28_DLASTSGA;
    union { 
        Uns32 value;
    } TCD28_CSR_BITER;
    union { 
        Uns32 value;
    } TCD29_SADDR;
    union { 
        Uns32 value;
    } TCD29_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD29_NBYTES;
    union { 
        Uns32 value;
    } TCD29_SLAST;
    union { 
        Uns32 value;
    } TCD29_DADDR;
    union { 
        Uns32 value;
    } TCD29_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD29_DLASTSGA;
    union { 
        Uns32 value;
    } TCD29_CSR_BITER;
    union { 
        Uns32 value;
    } TCD30_SADDR;
    union { 
        Uns32 value;
    } TCD30_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD30_NBYTES;
    union { 
        Uns32 value;
    } TCD30_SLAST;
    union { 
        Uns32 value;
    } TCD30_DADDR;
    union { 
        Uns32 value;
    } TCD30_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD30_DLASTSGA;
    union { 
        Uns32 value;
    } TCD30_CSR_BITER;
    union { 
        Uns32 value;
    } TCD31_SADDR;
    union { 
        Uns32 value;
    } TCD31_SOFF_ATTR;
    union { 
        Uns32 value;
    } TCD31_NBYTES;
    union { 
        Uns32 value;
    } TCD31_SLAST;
    union { 
        Uns32 value;
    } TCD31_DADDR;
    union { 
        Uns32 value;
    } TCD31_DOFF_CITER;
    union { 
        Uns32 value;
    } TCD31_DLASTSGA;
    union { 
        Uns32 value;
    } TCD31_CSR_BITER;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle MREAD;
    ppmAddressSpaceHandle MWRITE;
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          eDMARequest;
    ppmNetHandle          eDMADone;
    ppmNetHandle          errorInterrupt;
    ppmNetHandle          dmaInterrupt_ch0;
    ppmNetHandle          dmaInterrupt_ch1;
    ppmNetHandle          dmaInterrupt_ch2;
    ppmNetHandle          dmaInterrupt_ch3;
    ppmNetHandle          dmaInterrupt_ch4;
    ppmNetHandle          dmaInterrupt_ch5;
    ppmNetHandle          dmaInterrupt_ch6;
    ppmNetHandle          dmaInterrupt_ch7;
    ppmNetHandle          dmaInterrupt_ch8;
    ppmNetHandle          dmaInterrupt_ch9;
    ppmNetHandle          dmaInterrupt_ch10;
    ppmNetHandle          dmaInterrupt_ch11;
    ppmNetHandle          dmaInterrupt_ch12;
    ppmNetHandle          dmaInterrupt_ch13;
    ppmNetHandle          dmaInterrupt_ch14;
    ppmNetHandle          dmaInterrupt_ch15;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(DMARequest);
PPM_NET_CB(DMAReset);
PPM_REG_READ_CB(regRead32);
PPM_REG_READ_CB(regReadCHPRI);
PPM_REG_READ_CB(regReadCR);
PPM_REG_READ_CB(regReadES);
PPM_REG_READ_CB(regReadTCD);
PPM_REG_READ_CB(regReadTCD16);
PPM_REG_READ_CB(regReadZero);
PPM_REG_WRITE_CB(regSetGroup);
PPM_REG_WRITE_CB(regWrite1c);
PPM_REG_WRITE_CB(regWrite32);
PPM_REG_WRITE_CB(regWriteCHPRI);
PPM_REG_WRITE_CB(regWriteCR);
PPM_REG_WRITE_CB(regWriteTCD);
PPM_REG_WRITE_CB(regWriteTCD16);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
