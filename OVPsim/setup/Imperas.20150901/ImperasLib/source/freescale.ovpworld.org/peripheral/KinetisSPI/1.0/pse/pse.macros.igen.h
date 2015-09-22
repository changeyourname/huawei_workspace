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
#define BPORT1_AB_MCR    (BPORT1 + 0x0)

#define BPORT1_AB_MCR_CLR_RXF   (0x1 << 10)
#define BPORT1_AB_MCR_CLR_TXF   (0x1 << 11)
#define BPORT1_AB_MCR_CONT_SCKE   (0x1 << 30)
#define BPORT1_AB_MCR_DCONF   (0x3 << 28)
#define BPORT1_AB_MCR_DIS_RXF   (0x1 << 12)
#define BPORT1_AB_MCR_DIS_TXF   (0x1 << 13)
#define BPORT1_AB_MCR_DOZE   (0x1 << 15)
#define BPORT1_AB_MCR_FRZ   (0x1 << 27)
#define BPORT1_AB_MCR_HALT   0x1
#define BPORT1_AB_MCR_MDIS   (0x1 << 14)
#define BPORT1_AB_MCR_MSTR   (0x1 << 31)
#define BPORT1_AB_MCR_MTFE   (0x1 << 26)
#define BPORT1_AB_MCR_PCSIS   (0x3f << 16)
#define BPORT1_AB_MCR_PCSSE   (0x1 << 25)
#define BPORT1_AB_MCR_ROOE   (0x1 << 24)
#define BPORT1_AB_MCR_SMPL_PT   (0x3 << 8)
#define BPORT1_AB_TCR    (BPORT1 + 0x8)

#define BPORT1_AB_TCR_SPI_TCNT   (0xffff << 16)
#define BPORT1_AB_CTAR0    (BPORT1 + 0xc)

#define BPORT1_AB_CTAR0_ASC   (0xf << 8)
#define BPORT1_AB_CTAR0_BR   0xf
#define BPORT1_AB_CTAR0_CPHA   (0x1 << 25)
#define BPORT1_AB_CTAR0_CPOL   (0x1 << 26)
#define BPORT1_AB_CTAR0_CSSCK   (0xf << 12)
#define BPORT1_AB_CTAR0_DBR   (0x1 << 31)
#define BPORT1_AB_CTAR0_DT   (0xf << 4)
#define BPORT1_AB_CTAR0_FMSZ   (0xf << 27)
#define BPORT1_AB_CTAR0_LSBFE   (0x1 << 24)
#define BPORT1_AB_CTAR0_PASC   (0x3 << 20)
#define BPORT1_AB_CTAR0_PBR   (0x3 << 16)
#define BPORT1_AB_CTAR0_PCSSCK   (0x3 << 22)
#define BPORT1_AB_CTAR0_PDT   (0x3 << 18)
#define BPORT1_AB_CTAR1    (BPORT1 + 0x10)

#define BPORT1_AB_CTAR1_ASC   (0xf << 8)
#define BPORT1_AB_CTAR1_BR   0xf
#define BPORT1_AB_CTAR1_CPHA   (0x1 << 25)
#define BPORT1_AB_CTAR1_CPOL   (0x1 << 26)
#define BPORT1_AB_CTAR1_CSSCK   (0xf << 12)
#define BPORT1_AB_CTAR1_DBR   (0x1 << 31)
#define BPORT1_AB_CTAR1_DT   (0xf << 4)
#define BPORT1_AB_CTAR1_FMSZ   (0xf << 27)
#define BPORT1_AB_CTAR1_LSBFE   (0x1 << 24)
#define BPORT1_AB_CTAR1_PASC   (0x3 << 20)
#define BPORT1_AB_CTAR1_PBR   (0x3 << 16)
#define BPORT1_AB_CTAR1_PCSSCK   (0x3 << 22)
#define BPORT1_AB_CTAR1_PDT   (0x3 << 18)
#define BPORT1_AB_SR    (BPORT1 + 0x2c)

#define BPORT1_AB_SR_EOQF   (0x1 << 28)
#define BPORT1_AB_SR_POPNXTPTR   0xf
#define BPORT1_AB_SR_RFDF   (0x1 << 17)
#define BPORT1_AB_SR_RFOF   (0x1 << 19)
#define BPORT1_AB_SR_RXCTR   (0xf << 4)
#define BPORT1_AB_SR_TCF   (0x1 << 31)
#define BPORT1_AB_SR_TFFF   (0x1 << 25)
#define BPORT1_AB_SR_TFUF   (0x1 << 27)
#define BPORT1_AB_SR_TXCTR   (0xf << 12)
#define BPORT1_AB_SR_TXNXTPTR   (0xf << 8)
#define BPORT1_AB_SR_TXRXS   (0x1 << 30)
#define BPORT1_AB_RSER    (BPORT1 + 0x30)

#define BPORT1_AB_RSER_EOQF_RE   (0x1 << 28)
#define BPORT1_AB_RSER_RFDF_DIRS   (0x1 << 16)
#define BPORT1_AB_RSER_RFDF_RE   (0x1 << 17)
#define BPORT1_AB_RSER_RFOF_RE   (0x1 << 19)
#define BPORT1_AB_RSER_TCF_RE   (0x1 << 31)
#define BPORT1_AB_RSER_TFFF_DIRS   (0x1 << 24)
#define BPORT1_AB_RSER_TFFF_RE   (0x1 << 25)
#define BPORT1_AB_RSER_TFUF_RE   (0x1 << 27)
#define BPORT1_AB_PUSHR    (BPORT1 + 0x34)

#define BPORT1_AB_PUSHR_CONT   (0x1 << 31)
#define BPORT1_AB_PUSHR_CTAS   (0x7 << 28)
#define BPORT1_AB_PUSHR_CTCNT   (0x1 << 26)
#define BPORT1_AB_PUSHR_EOQ   (0x1 << 27)
#define BPORT1_AB_PUSHR_PCS   (0x3f << 16)
#define BPORT1_AB_PUSHR_TXDATA   0xffff
#define BPORT1_AB_POPR    (BPORT1 + 0x38)

#define BPORT1_AB_POPR_RXDATA   0xffffffff
#define BPORT1_AB_TXFR0    (BPORT1 + 0x3c)

#define BPORT1_AB_TXFR0_TXCMD_TXDATA   (0xffff << 16)
#define BPORT1_AB_TXFR0_TXDATA   0xffff
#define BPORT1_AB_TXFR1    (BPORT1 + 0x40)

#define BPORT1_AB_TXFR1_TXCMD_TXDATA   (0xffff << 16)
#define BPORT1_AB_TXFR1_TXDATA   0xffff
#define BPORT1_AB_TXFR2    (BPORT1 + 0x44)

#define BPORT1_AB_TXFR2_TXCMD_TXDATA   (0xffff << 16)
#define BPORT1_AB_TXFR2_TXDATA   0xffff
#define BPORT1_AB_TXFR3    (BPORT1 + 0x48)

#define BPORT1_AB_TXFR3_TXCMD_TXDATA   (0xffff << 16)
#define BPORT1_AB_TXFR3_TXDATA   0xffff
#define BPORT1_AB_RXFR0    (BPORT1 + 0x7c)

#define BPORT1_AB_RXFR0_RXDATA   0xffffffff
#define BPORT1_AB_RXFR1    (BPORT1 + 0x80)

#define BPORT1_AB_RXFR1_RXDATA   0xffffffff
#define BPORT1_AB_RXFR2    (BPORT1 + 0x84)

#define BPORT1_AB_RXFR2_RXDATA   0xffffffff
#define BPORT1_AB_RXFR3    (BPORT1 + 0x88)

#define BPORT1_AB_RXFR3_RXDATA   0xffffffff


#endif
