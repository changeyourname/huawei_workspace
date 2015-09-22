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

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H
// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.
// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
    #error BPORT1 is undefined.It needs to be set to the port base address
#endif
#define BPORT1_AB_TSR    (BPORT1 + 0x0)

#define BPORT1_AB_TSR_TSR   0xffffffff
#define BPORT1_AB_TPR    (BPORT1 + 0x4)

#define BPORT1_AB_TPR_TPR   0xffff
#define BPORT1_AB_TAR    (BPORT1 + 0x8)

#define BPORT1_AB_TAR_TAR   0xffffffff
#define BPORT1_AB_TCR    (BPORT1 + 0xc)

#define BPORT1_AB_TCR_CIC   (0xff << 24)
#define BPORT1_AB_TCR_CIR   (0xff << 8)
#define BPORT1_AB_TCR_TCR   0xff
#define BPORT1_AB_TCR_TCV   (0xff << 16)
#define BPORT1_AB_CR    (BPORT1 + 0x10)

#define BPORT1_AB_CR_CLKO   (0x1 << 9)
#define BPORT1_AB_CR_OSCE   (0x1 << 8)
#define BPORT1_AB_CR_SC16P   (0x1 << 10)
#define BPORT1_AB_CR_SC2P   (0x1 << 13)
#define BPORT1_AB_CR_SC4P   (0x1 << 12)
#define BPORT1_AB_CR_SC8P   (0x1 << 11)
#define BPORT1_AB_CR_SUP   (0x1 << 2)
#define BPORT1_AB_CR_SWR   0x1
#define BPORT1_AB_CR_UM   (0x1 << 3)
#define BPORT1_AB_CR_WPE   (0x1 << 1)
#define BPORT1_AB_SR    (BPORT1 + 0x14)

#define BPORT1_AB_SR_MOF   (0x1 << 3)
#define BPORT1_AB_SR_TAF   (0x1 << 2)
#define BPORT1_AB_SR_TCE   (0x1 << 4)
#define BPORT1_AB_SR_TIF   0x1
#define BPORT1_AB_SR_TOF   (0x1 << 1)
#define BPORT1_AB_LR    (BPORT1 + 0x18)

#define BPORT1_AB_LR_CRL   (0x1 << 4)
#define BPORT1_AB_LR_LRL   (0x1 << 6)
#define BPORT1_AB_LR_MCHL   (0x1 << 11)
#define BPORT1_AB_LR_MCLL   (0x1 << 10)
#define BPORT1_AB_LR_MEL   (0x1 << 9)
#define BPORT1_AB_LR_SRL   (0x1 << 5)
#define BPORT1_AB_LR_TCL   (0x1 << 3)
#define BPORT1_AB_LR_TDL   (0x1 << 13)
#define BPORT1_AB_LR_TEL   (0x1 << 12)
#define BPORT1_AB_LR_TIL   (0x1 << 15)
#define BPORT1_AB_LR_TTL   (0x1 << 14)
#define BPORT1_AB_LR_TTSL   (0x1 << 8)
#define BPORT1_AB_IER    (BPORT1 + 0x1c)

#define BPORT1_AB_IER_MOIE   (0x1 << 3)
#define BPORT1_AB_IER_TAIE   (0x1 << 2)
#define BPORT1_AB_IER_TIIE   0x1
#define BPORT1_AB_IER_TOIE   (0x1 << 1)
#define BPORT1_AB_IER_TSIE   (0x1 << 4)
#define BPORT1_AB_TTSR    (BPORT1 + 0x20)

#define BPORT1_AB_TTSR_TTS   0xffffffff
#define BPORT1_AB_MER    (BPORT1 + 0x24)

#define BPORT1_AB_MER_MCE   (0x1 << 4)
#define BPORT1_AB_MCLR    (BPORT1 + 0x28)

#define BPORT1_AB_MCLR_MCL   0xffffffff
#define BPORT1_AB_MCHR    (BPORT1 + 0x2c)

#define BPORT1_AB_MCHR_MCH   0xffffffff
#define BPORT1_AB_TER    (BPORT1 + 0x30)

#define BPORT1_AB_TER_CTE   (0x1 << 2)
#define BPORT1_AB_TER_DTE   0x1
#define BPORT1_AB_TER_FSE   (0x1 << 4)
#define BPORT1_AB_TER_TME   (0x1 << 5)
#define BPORT1_AB_TER_TTE   (0x1 << 3)
#define BPORT1_AB_TER_VTE   (0x1 << 1)
#define BPORT1_AB_TDR    (BPORT1 + 0x34)

#define BPORT1_AB_TDR_CTF   (0x1 << 2)
#define BPORT1_AB_TDR_DTF   0x1
#define BPORT1_AB_TDR_FSF   (0x1 << 4)
#define BPORT1_AB_TDR_TMF   (0x1 << 5)
#define BPORT1_AB_TDR_TTF   (0x1 << 3)
#define BPORT1_AB_TDR_VTF   (0x1 << 1)
#define BPORT1_AB_TTR    (BPORT1 + 0x38)

#define BPORT1_AB_TTR_CDTH   (0x7 << 6)
#define BPORT1_AB_TTR_CDTL   (0x7 << 9)
#define BPORT1_AB_TTR_TDTH   (0x7 << 12)
#define BPORT1_AB_TTR_TDTL   (0x7 << 15)
#define BPORT1_AB_TTR_VDTH   (0x7 << 3)
#define BPORT1_AB_TTR_VDTL   0x7
#define BPORT1_AB_TIR    (BPORT1 + 0x3c)

#define BPORT1_AB_TIR_CTIE   (0x1 << 2)
#define BPORT1_AB_TIR_DTIE   0x1
#define BPORT1_AB_TIR_FSIE   (0x1 << 4)
#define BPORT1_AB_TIR_TMIE   (0x1 << 5)
#define BPORT1_AB_TIR_TTIE   (0x1 << 3)
#define BPORT1_AB_TIR_VTIE   (0x1 << 1)
#define BPORT1_AB_WAR    (BPORT1 + 0x800)

#define BPORT1_AB_WAR_CRW   (0x1 << 4)
#define BPORT1_AB_WAR_IERW   (0x1 << 7)
#define BPORT1_AB_WAR_LRW   (0x1 << 6)
#define BPORT1_AB_WAR_MCHW   (0x1 << 11)
#define BPORT1_AB_WAR_MCLW   (0x1 << 10)
#define BPORT1_AB_WAR_MERW   (0x1 << 9)
#define BPORT1_AB_WAR_SRW   (0x1 << 5)
#define BPORT1_AB_WAR_TARW   (0x1 << 2)
#define BPORT1_AB_WAR_TCRW   (0x1 << 3)
#define BPORT1_AB_WAR_TDRW   (0x1 << 13)
#define BPORT1_AB_WAR_TERW   (0x1 << 12)
#define BPORT1_AB_WAR_TIRW   (0x1 << 15)
#define BPORT1_AB_WAR_TPRW   (0x1 << 1)
#define BPORT1_AB_WAR_TSRW   0x1
#define BPORT1_AB_WAR_TTRW   (0x1 << 14)
#define BPORT1_AB_WAR_TTSW   (0x1 << 8)
#define BPORT1_AB_RAR    (BPORT1 + 0x804)

#define BPORT1_AB_RAR_CRR   (0x1 << 4)
#define BPORT1_AB_RAR_IERR   (0x1 << 7)
#define BPORT1_AB_RAR_LRR   (0x1 << 6)
#define BPORT1_AB_RAR_MCHR   (0x1 << 11)
#define BPORT1_AB_RAR_MCLR   (0x1 << 10)
#define BPORT1_AB_RAR_MERR   (0x1 << 9)
#define BPORT1_AB_RAR_SRR   (0x1 << 5)
#define BPORT1_AB_RAR_TARR   (0x1 << 2)
#define BPORT1_AB_RAR_TCRR   (0x1 << 3)
#define BPORT1_AB_RAR_TDRR   (0x1 << 13)
#define BPORT1_AB_RAR_TERR   (0x1 << 12)
#define BPORT1_AB_RAR_TIRR   (0x1 << 15)
#define BPORT1_AB_RAR_TPRR   (0x1 << 1)
#define BPORT1_AB_RAR_TSRR   0x1
#define BPORT1_AB_RAR_TTRR   (0x1 << 14)
#define BPORT1_AB_RAR_TTSR   (0x1 << 8)


#endif
