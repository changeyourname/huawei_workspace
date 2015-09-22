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
#define BPORT1_AB_MCR_DDR_EN   (0x1 << 7)
#define BPORT1_AB_MCR_DQS_EN   (0x1 << 6)
#define BPORT1_AB_MCR_END_CFG   (0x3 << 2)
#define BPORT1_AB_MCR_MDIS   (0x1 << 14)
#define BPORT1_AB_MCR_SCLKCFG   (0xff << 24)
#define BPORT1_AB_MCR_SWRSTHD   (0x1 << 1)
#define BPORT1_AB_MCR_SWRSTSD   0x1
#define BPORT1_AB_IPCR    (BPORT1 + 0x8)

#define BPORT1_AB_IPCR_IDATSZ   0xffff
#define BPORT1_AB_IPCR_PAR_EN   (0x1 << 16)
#define BPORT1_AB_IPCR_SEQID   (0xf << 24)
#define BPORT1_AB_FLSHCR    (BPORT1 + 0xc)

#define BPORT1_AB_FLSHCR_TCSH   (0xf << 8)
#define BPORT1_AB_FLSHCR_TCSS   0xf
#define BPORT1_AB_BUF0CR    (BPORT1 + 0x10)

#define BPORT1_AB_BUF0CR_ADATSZ   (0xff << 8)
#define BPORT1_AB_BUF0CR_HP_EN   (0x1 << 31)
#define BPORT1_AB_BUF0CR_MSTRID   0xf
#define BPORT1_AB_BUF1CR    (BPORT1 + 0x14)

#define BPORT1_AB_BUF1CR_ADATSZ   (0xff << 8)
#define BPORT1_AB_BUF1CR_MSTRID   0xf
#define BPORT1_AB_BUF2CR    (BPORT1 + 0x18)

#define BPORT1_AB_BUF2CR_ADATSZ   (0xff << 8)
#define BPORT1_AB_BUF2CR_MSTRID   0xf
#define BPORT1_AB_BUF3CR    (BPORT1 + 0x1c)

#define BPORT1_AB_BUF3CR_ADATSZ   (0xff << 8)
#define BPORT1_AB_BUF3CR_ALLMST   (0x1 << 31)
#define BPORT1_AB_BUF3CR_MSTRID   0xf
#define BPORT1_AB_BFGENCR    (BPORT1 + 0x20)

#define BPORT1_AB_BFGENCR_PAR_EN   (0x1 << 16)
#define BPORT1_AB_BFGENCR_SEQID   (0xf << 12)
#define BPORT1_AB_BUF0IND    (BPORT1 + 0x30)

#define BPORT1_AB_BUF0IND_TPINDX0   (0x1fffffff << 3)
#define BPORT1_AB_BUF1IND    (BPORT1 + 0x34)

#define BPORT1_AB_BUF1IND_TPINDX1   (0x1fffffff << 3)
#define BPORT1_AB_BUF2IND    (BPORT1 + 0x38)

#define BPORT1_AB_BUF2IND_TPINDX2   (0x1fffffff << 3)
#define BPORT1_AB_SFAR    (BPORT1 + 0x100)

#define BPORT1_AB_SFAR_SFADR   0xffffffff
#define BPORT1_AB_SMPR    (BPORT1 + 0x108)

#define BPORT1_AB_SMPR_DDRSMP   (0x7 << 16)
#define BPORT1_AB_SMPR_FSDLY   (0x1 << 6)
#define BPORT1_AB_SMPR_FSPHS   (0x1 << 5)
#define BPORT1_AB_SMPR_HSDLY   (0x1 << 2)
#define BPORT1_AB_SMPR_HSENA   0x1
#define BPORT1_AB_SMPR_HSPHS   (0x1 << 1)
#define BPORT1_AB_RBSR    (BPORT1 + 0x10c)

#define BPORT1_AB_RBSR_RDBFL   (0x3f << 8)
#define BPORT1_AB_RBSR_RDCTR   (0xffff << 16)
#define BPORT1_AB_RBCT    (BPORT1 + 0x110)

#define BPORT1_AB_RBCT_RXBRD   (0x1 << 8)
#define BPORT1_AB_RBCT_WMRK   0x1f
#define BPORT1_AB_TBSR    (BPORT1 + 0x150)

#define BPORT1_AB_TBSR_TRBFL   (0x1f << 8)
#define BPORT1_AB_TBSR_TRCTR   (0xffff << 16)
#define BPORT1_AB_TBDR    (BPORT1 + 0x154)

#define BPORT1_AB_TBDR_TXDATA   0xffffffff
#define BPORT1_AB_SR    (BPORT1 + 0x15c)

#define BPORT1_AB_SR_AHB0FUL   (0x1 << 11)
#define BPORT1_AB_SR_AHB0NE   (0x1 << 7)
#define BPORT1_AB_SR_AHB1FUL   (0x1 << 12)
#define BPORT1_AB_SR_AHB1NE   (0x1 << 8)
#define BPORT1_AB_SR_AHB2FUL   (0x1 << 13)
#define BPORT1_AB_SR_AHB2NE   (0x1 << 9)
#define BPORT1_AB_SR_AHB3FUL   (0x1 << 14)
#define BPORT1_AB_SR_AHB3NE   (0x1 << 10)
#define BPORT1_AB_SR_AHB_ACC   (0x1 << 2)
#define BPORT1_AB_SR_AHBGNT   (0x1 << 5)
#define BPORT1_AB_SR_AHBTRN   (0x1 << 6)
#define BPORT1_AB_SR_BUSY   0x1
#define BPORT1_AB_SR_DLPSMP   (0x7 << 29)
#define BPORT1_AB_SR_IP_ACC   (0x1 << 1)
#define BPORT1_AB_SR_RXDMA   (0x1 << 23)
#define BPORT1_AB_SR_RXFULL   (0x1 << 19)
#define BPORT1_AB_SR_RXWE   (0x1 << 16)
#define BPORT1_AB_SR_TXFULL   (0x1 << 27)
#define BPORT1_AB_SR_TXNE   (0x1 << 24)
#define BPORT1_AB_FR    (BPORT1 + 0x160)

#define BPORT1_AB_FR_ABOF   (0x1 << 12)
#define BPORT1_AB_FR_ABSEF   (0x1 << 15)
#define BPORT1_AB_FR_DLPFF   (0x1 << 31)
#define BPORT1_AB_FR_ILLINE   (0x1 << 23)
#define BPORT1_AB_FR_IPAEF   (0x1 << 7)
#define BPORT1_AB_FR_IPGEF   (0x1 << 4)
#define BPORT1_AB_FR_IPIEF   (0x1 << 6)
#define BPORT1_AB_FR_IUEF   (0x1 << 11)
#define BPORT1_AB_FR_RBDF   (0x1 << 16)
#define BPORT1_AB_FR_RBOF   (0x1 << 17)
#define BPORT1_AB_FR_TBFF   (0x1 << 27)
#define BPORT1_AB_FR_TBUF   (0x1 << 26)
#define BPORT1_AB_FR_TFF   0x1
#define BPORT1_AB_RSER    (BPORT1 + 0x164)

#define BPORT1_AB_RSER_ABOIE   (0x1 << 12)
#define BPORT1_AB_RSER_ABSEIE   (0x1 << 15)
#define BPORT1_AB_RSER_DLPFIE   (0x1 << 31)
#define BPORT1_AB_RSER_ILLINIE   (0x1 << 23)
#define BPORT1_AB_RSER_IPAEIE   (0x1 << 7)
#define BPORT1_AB_RSER_IPGEIE   (0x1 << 4)
#define BPORT1_AB_RSER_IPIEIE   (0x1 << 6)
#define BPORT1_AB_RSER_IUEIE   (0x1 << 11)
#define BPORT1_AB_RSER_RBDDE   (0x1 << 21)
#define BPORT1_AB_RSER_RBDIE   (0x1 << 16)
#define BPORT1_AB_RSER_RBOIE   (0x1 << 17)
#define BPORT1_AB_RSER_TBFIE   (0x1 << 27)
#define BPORT1_AB_RSER_TBUIE   (0x1 << 26)
#define BPORT1_AB_RSER_TFIE   0x1
#define BPORT1_AB_SPNDST    (BPORT1 + 0x168)

#define BPORT1_AB_SPNDST_DATLFT   (0x7f << 9)
#define BPORT1_AB_SPNDST_SPDBUF   (0x3 << 6)
#define BPORT1_AB_SPNDST_SUSPND   0x1
#define BPORT1_AB_SPTRCLR    (BPORT1 + 0x16c)

#define BPORT1_AB_SPTRCLR_BFPTRC   0x1
#define BPORT1_AB_SPTRCLR_IPPTRC   (0x1 << 8)
#define BPORT1_AB_SFA1AD    (BPORT1 + 0x180)

#define BPORT1_AB_SFA1AD_TPADA1   (0x3fffff << 10)
#define BPORT1_AB_SFA2AD    (BPORT1 + 0x184)

#define BPORT1_AB_SFA2AD_TPADA2   (0x3fffff << 10)
#define BPORT1_AB_SFB1AD    (BPORT1 + 0x188)

#define BPORT1_AB_SFB1AD_TPADB1   (0x3fffff << 10)
#define BPORT1_AB_SFB2AD    (BPORT1 + 0x18c)

#define BPORT1_AB_SFB2AD_TPADB2   (0x3fffff << 10)
#define BPORT1_AB_LUTKEY    (BPORT1 + 0x300)

#define BPORT1_AB_LUTKEY_KEY   0xffffffff
#define BPORT1_AB_LCKCR    (BPORT1 + 0x304)

#define BPORT1_AB_LCKCR_LOCK   0x1
#define BPORT1_AB_LCKCR_UNLOCK   (0x1 << 1)
#define BPORT1_AB_RBDR0    (BPORT1 + 0x200)

#define BPORT1_AB_RBDR0_RXDATA   0xffffffff
#define BPORT1_AB_RBDR1    (BPORT1 + 0x204)

#define BPORT1_AB_RBDR1_RXDATA   0xffffffff
#define BPORT1_AB_RBDR2    (BPORT1 + 0x208)

#define BPORT1_AB_RBDR2_RXDATA   0xffffffff
#define BPORT1_AB_RBDR3    (BPORT1 + 0x20c)

#define BPORT1_AB_RBDR3_RXDATA   0xffffffff
#define BPORT1_AB_RBDR4    (BPORT1 + 0x210)

#define BPORT1_AB_RBDR4_RXDATA   0xffffffff
#define BPORT1_AB_RBDR5    (BPORT1 + 0x214)

#define BPORT1_AB_RBDR5_RXDATA   0xffffffff
#define BPORT1_AB_RBDR6    (BPORT1 + 0x218)

#define BPORT1_AB_RBDR6_RXDATA   0xffffffff
#define BPORT1_AB_RBDR7    (BPORT1 + 0x21c)

#define BPORT1_AB_RBDR7_RXDATA   0xffffffff
#define BPORT1_AB_RBDR8    (BPORT1 + 0x220)

#define BPORT1_AB_RBDR8_RXDATA   0xffffffff
#define BPORT1_AB_RBDR9    (BPORT1 + 0x224)

#define BPORT1_AB_RBDR9_RXDATA   0xffffffff
#define BPORT1_AB_RBDR10    (BPORT1 + 0x228)

#define BPORT1_AB_RBDR10_RXDATA   0xffffffff
#define BPORT1_AB_RBDR11    (BPORT1 + 0x22c)

#define BPORT1_AB_RBDR11_RXDATA   0xffffffff
#define BPORT1_AB_RBDR12    (BPORT1 + 0x230)

#define BPORT1_AB_RBDR12_RXDATA   0xffffffff
#define BPORT1_AB_RBDR13    (BPORT1 + 0x234)

#define BPORT1_AB_RBDR13_RXDATA   0xffffffff
#define BPORT1_AB_RBDR14    (BPORT1 + 0x238)

#define BPORT1_AB_RBDR14_RXDATA   0xffffffff
#define BPORT1_AB_RBDR15    (BPORT1 + 0x23c)

#define BPORT1_AB_RBDR15_RXDATA   0xffffffff
#define BPORT1_AB_RBDR16    (BPORT1 + 0x240)

#define BPORT1_AB_RBDR16_RXDATA   0xffffffff
#define BPORT1_AB_RBDR17    (BPORT1 + 0x244)

#define BPORT1_AB_RBDR17_RXDATA   0xffffffff
#define BPORT1_AB_RBDR18    (BPORT1 + 0x248)

#define BPORT1_AB_RBDR18_RXDATA   0xffffffff
#define BPORT1_AB_RBDR19    (BPORT1 + 0x24c)

#define BPORT1_AB_RBDR19_RXDATA   0xffffffff
#define BPORT1_AB_RBDR20    (BPORT1 + 0x250)

#define BPORT1_AB_RBDR20_RXDATA   0xffffffff
#define BPORT1_AB_RBDR21    (BPORT1 + 0x254)

#define BPORT1_AB_RBDR21_RXDATA   0xffffffff
#define BPORT1_AB_RBDR22    (BPORT1 + 0x258)

#define BPORT1_AB_RBDR22_RXDATA   0xffffffff
#define BPORT1_AB_RBDR23    (BPORT1 + 0x25c)

#define BPORT1_AB_RBDR23_RXDATA   0xffffffff
#define BPORT1_AB_RBDR24    (BPORT1 + 0x260)

#define BPORT1_AB_RBDR24_RXDATA   0xffffffff
#define BPORT1_AB_RBDR25    (BPORT1 + 0x264)

#define BPORT1_AB_RBDR25_RXDATA   0xffffffff
#define BPORT1_AB_RBDR26    (BPORT1 + 0x268)

#define BPORT1_AB_RBDR26_RXDATA   0xffffffff
#define BPORT1_AB_RBDR27    (BPORT1 + 0x26c)

#define BPORT1_AB_RBDR27_RXDATA   0xffffffff
#define BPORT1_AB_RBDR28    (BPORT1 + 0x270)

#define BPORT1_AB_RBDR28_RXDATA   0xffffffff
#define BPORT1_AB_RBDR29    (BPORT1 + 0x274)

#define BPORT1_AB_RBDR29_RXDATA   0xffffffff
#define BPORT1_AB_RBDR30    (BPORT1 + 0x278)

#define BPORT1_AB_RBDR30_RXDATA   0xffffffff
#define BPORT1_AB_RBDR31    (BPORT1 + 0x27c)

#define BPORT1_AB_RBDR32    (BPORT1 + 0x280)

#define BPORT1_AB_RBDR33    (BPORT1 + 0x284)

#define BPORT1_AB_RBDR34    (BPORT1 + 0x288)

#define BPORT1_AB_RBDR35    (BPORT1 + 0x28c)

#define BPORT1_AB_RBDR36    (BPORT1 + 0x290)

#define BPORT1_AB_RBDR37    (BPORT1 + 0x294)

#define BPORT1_AB_RBDR38    (BPORT1 + 0x298)

#define BPORT1_AB_RBDR39    (BPORT1 + 0x29c)

#define BPORT1_AB_RBDR40    (BPORT1 + 0x2a0)

#define BPORT1_AB_RBDR41    (BPORT1 + 0x2a4)

#define BPORT1_AB_RBDR42    (BPORT1 + 0x2a8)

#define BPORT1_AB_RBDR43    (BPORT1 + 0x2ac)

#define BPORT1_AB_RBDR44    (BPORT1 + 0x2b0)

#define BPORT1_AB_RBDR45    (BPORT1 + 0x2b4)

#define BPORT1_AB_RBDR46    (BPORT1 + 0x2b8)

#define BPORT1_AB_RBDR47    (BPORT1 + 0x2bc)

#define BPORT1_AB_RBDR48    (BPORT1 + 0x2c0)

#define BPORT1_AB_RBDR49    (BPORT1 + 0x2c4)

#define BPORT1_AB_RBDR50    (BPORT1 + 0x2c8)

#define BPORT1_AB_RBDR51    (BPORT1 + 0x2cc)

#define BPORT1_AB_RBDR52    (BPORT1 + 0x2d0)

#define BPORT1_AB_RBDR53    (BPORT1 + 0x2d4)

#define BPORT1_AB_RBDR54    (BPORT1 + 0x2d8)

#define BPORT1_AB_RBDR55    (BPORT1 + 0x2dc)

#define BPORT1_AB_RBDR56    (BPORT1 + 0x2e0)

#define BPORT1_AB_RBDR57    (BPORT1 + 0x2e4)

#define BPORT1_AB_RBDR58    (BPORT1 + 0x2e8)

#define BPORT1_AB_RBDR59    (BPORT1 + 0x2ec)

#define BPORT1_AB_RBDR60    (BPORT1 + 0x2f0)

#define BPORT1_AB_RBDR61    (BPORT1 + 0x2f4)

#define BPORT1_AB_RBDR62    (BPORT1 + 0x2f8)

#define BPORT1_AB_RBDR63    (BPORT1 + 0x2fc)

#define BPORT1_AB_LUT0    (BPORT1 + 0x310)

#define BPORT1_AB_LUT0_OPRND0   0xff
#define BPORT1_AB_LUT0_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT0_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT0_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT0_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT0_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT1    (BPORT1 + 0x314)

#define BPORT1_AB_LUT1_OPRND0   0xff
#define BPORT1_AB_LUT1_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT1_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT1_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT1_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT1_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT2    (BPORT1 + 0x318)

#define BPORT1_AB_LUT2_OPRND0   0xff
#define BPORT1_AB_LUT2_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT2_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT2_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT2_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT2_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT3    (BPORT1 + 0x31c)

#define BPORT1_AB_LUT3_OPRND0   0xff
#define BPORT1_AB_LUT3_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT3_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT3_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT3_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT3_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT4    (BPORT1 + 0x320)

#define BPORT1_AB_LUT4_OPRND0   0xff
#define BPORT1_AB_LUT4_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT4_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT4_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT4_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT4_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT5    (BPORT1 + 0x324)

#define BPORT1_AB_LUT5_OPRND0   0xff
#define BPORT1_AB_LUT5_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT5_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT5_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT5_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT5_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT6    (BPORT1 + 0x328)

#define BPORT1_AB_LUT6_OPRND0   0xff
#define BPORT1_AB_LUT6_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT6_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT6_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT6_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT6_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT7    (BPORT1 + 0x32c)

#define BPORT1_AB_LUT7_OPRND0   0xff
#define BPORT1_AB_LUT7_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT7_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT7_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT7_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT7_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT8    (BPORT1 + 0x330)

#define BPORT1_AB_LUT8_OPRND0   0xff
#define BPORT1_AB_LUT8_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT8_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT8_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT8_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT8_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT9    (BPORT1 + 0x334)

#define BPORT1_AB_LUT9_OPRND0   0xff
#define BPORT1_AB_LUT9_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT9_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT9_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT9_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT9_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT10    (BPORT1 + 0x338)

#define BPORT1_AB_LUT10_OPRND0   0xff
#define BPORT1_AB_LUT10_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT10_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT10_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT10_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT10_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT11    (BPORT1 + 0x33c)

#define BPORT1_AB_LUT11_OPRND0   0xff
#define BPORT1_AB_LUT11_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT11_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT11_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT11_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT11_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT12    (BPORT1 + 0x340)

#define BPORT1_AB_LUT12_OPRND0   0xff
#define BPORT1_AB_LUT12_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT12_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT12_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT12_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT12_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT13    (BPORT1 + 0x344)

#define BPORT1_AB_LUT13_OPRND0   0xff
#define BPORT1_AB_LUT13_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT13_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT13_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT13_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT13_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT14    (BPORT1 + 0x348)

#define BPORT1_AB_LUT14_OPRND0   0xff
#define BPORT1_AB_LUT14_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT14_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT14_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT14_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT14_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT15    (BPORT1 + 0x34c)

#define BPORT1_AB_LUT15_OPRND0   0xff
#define BPORT1_AB_LUT15_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT15_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT15_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT15_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT15_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT16    (BPORT1 + 0x350)

#define BPORT1_AB_LUT16_OPRND0   0xff
#define BPORT1_AB_LUT16_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT16_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT16_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT16_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT16_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT17    (BPORT1 + 0x354)

#define BPORT1_AB_LUT17_OPRND0   0xff
#define BPORT1_AB_LUT17_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT17_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT17_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT17_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT17_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT18    (BPORT1 + 0x358)

#define BPORT1_AB_LUT18_OPRND0   0xff
#define BPORT1_AB_LUT18_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT18_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT18_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT18_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT18_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT19    (BPORT1 + 0x35c)

#define BPORT1_AB_LUT19_OPRND0   0xff
#define BPORT1_AB_LUT19_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT19_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT19_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT19_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT19_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT20    (BPORT1 + 0x360)

#define BPORT1_AB_LUT20_OPRND0   0xff
#define BPORT1_AB_LUT20_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT20_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT20_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT20_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT20_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT21    (BPORT1 + 0x364)

#define BPORT1_AB_LUT21_OPRND0   0xff
#define BPORT1_AB_LUT21_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT21_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT21_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT21_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT21_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT22    (BPORT1 + 0x368)

#define BPORT1_AB_LUT22_OPRND0   0xff
#define BPORT1_AB_LUT22_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT22_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT22_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT22_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT22_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT23    (BPORT1 + 0x36c)

#define BPORT1_AB_LUT23_OPRND0   0xff
#define BPORT1_AB_LUT23_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT23_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT23_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT23_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT23_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT24    (BPORT1 + 0x370)

#define BPORT1_AB_LUT24_OPRND0   0xff
#define BPORT1_AB_LUT24_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT24_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT24_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT24_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT24_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT25    (BPORT1 + 0x374)

#define BPORT1_AB_LUT25_OPRND0   0xff
#define BPORT1_AB_LUT25_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT25_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT25_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT25_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT25_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT26    (BPORT1 + 0x378)

#define BPORT1_AB_LUT26_OPRND0   0xff
#define BPORT1_AB_LUT26_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT26_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT26_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT26_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT26_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT27    (BPORT1 + 0x37c)

#define BPORT1_AB_LUT27_OPRND0   0xff
#define BPORT1_AB_LUT27_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT27_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT27_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT27_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT27_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT28    (BPORT1 + 0x380)

#define BPORT1_AB_LUT28_OPRND0   0xff
#define BPORT1_AB_LUT28_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT28_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT28_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT28_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT28_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT29    (BPORT1 + 0x384)

#define BPORT1_AB_LUT29_OPRND0   0xff
#define BPORT1_AB_LUT29_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT29_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT29_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT29_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT29_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT30    (BPORT1 + 0x388)

#define BPORT1_AB_LUT30_OPRND0   0xff
#define BPORT1_AB_LUT30_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT30_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT30_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT30_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT30_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT31    (BPORT1 + 0x38c)

#define BPORT1_AB_LUT31_OPRND0   0xff
#define BPORT1_AB_LUT31_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT31_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT31_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT31_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT31_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT32    (BPORT1 + 0x390)

#define BPORT1_AB_LUT32_OPRND0   0xff
#define BPORT1_AB_LUT32_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT32_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT32_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT32_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT32_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT33    (BPORT1 + 0x394)

#define BPORT1_AB_LUT33_OPRND0   0xff
#define BPORT1_AB_LUT33_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT33_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT33_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT33_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT33_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT34    (BPORT1 + 0x398)

#define BPORT1_AB_LUT34_OPRND0   0xff
#define BPORT1_AB_LUT34_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT34_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT34_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT34_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT34_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT35    (BPORT1 + 0x39c)

#define BPORT1_AB_LUT35_OPRND0   0xff
#define BPORT1_AB_LUT35_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT35_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT35_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT35_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT35_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT36    (BPORT1 + 0x3a0)

#define BPORT1_AB_LUT36_OPRND0   0xff
#define BPORT1_AB_LUT36_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT36_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT36_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT36_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT36_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT37    (BPORT1 + 0x3a4)

#define BPORT1_AB_LUT37_OPRND0   0xff
#define BPORT1_AB_LUT37_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT37_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT37_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT37_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT37_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT38    (BPORT1 + 0x3a8)

#define BPORT1_AB_LUT38_OPRND0   0xff
#define BPORT1_AB_LUT38_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT38_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT38_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT38_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT38_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT39    (BPORT1 + 0x3ac)

#define BPORT1_AB_LUT39_OPRND0   0xff
#define BPORT1_AB_LUT39_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT39_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT39_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT39_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT39_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT40    (BPORT1 + 0x3b0)

#define BPORT1_AB_LUT40_OPRND0   0xff
#define BPORT1_AB_LUT40_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT40_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT40_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT40_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT40_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT41    (BPORT1 + 0x3b4)

#define BPORT1_AB_LUT41_OPRND0   0xff
#define BPORT1_AB_LUT41_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT41_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT41_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT41_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT41_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT42    (BPORT1 + 0x3b8)

#define BPORT1_AB_LUT42_OPRND0   0xff
#define BPORT1_AB_LUT42_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT42_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT42_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT42_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT42_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT43    (BPORT1 + 0x3bc)

#define BPORT1_AB_LUT43_OPRND0   0xff
#define BPORT1_AB_LUT43_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT43_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT43_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT43_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT43_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT44    (BPORT1 + 0x3c0)

#define BPORT1_AB_LUT44_OPRND0   0xff
#define BPORT1_AB_LUT44_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT44_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT44_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT44_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT44_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT45    (BPORT1 + 0x3c4)

#define BPORT1_AB_LUT45_OPRND0   0xff
#define BPORT1_AB_LUT45_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT45_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT45_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT45_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT45_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT46    (BPORT1 + 0x3c8)

#define BPORT1_AB_LUT46_OPRND0   0xff
#define BPORT1_AB_LUT46_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT46_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT46_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT46_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT46_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT47    (BPORT1 + 0x3cc)

#define BPORT1_AB_LUT47_OPRND0   0xff
#define BPORT1_AB_LUT47_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT47_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT47_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT47_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT47_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT48    (BPORT1 + 0x3d0)

#define BPORT1_AB_LUT48_OPRND0   0xff
#define BPORT1_AB_LUT48_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT48_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT48_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT48_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT48_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT49    (BPORT1 + 0x3d4)

#define BPORT1_AB_LUT49_OPRND0   0xff
#define BPORT1_AB_LUT49_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT49_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT49_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT49_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT49_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT50    (BPORT1 + 0x3d8)

#define BPORT1_AB_LUT50_OPRND0   0xff
#define BPORT1_AB_LUT50_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT50_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT50_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT50_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT50_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT51    (BPORT1 + 0x3dc)

#define BPORT1_AB_LUT51_OPRND0   0xff
#define BPORT1_AB_LUT51_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT51_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT51_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT51_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT51_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT52    (BPORT1 + 0x3e0)

#define BPORT1_AB_LUT52_OPRND0   0xff
#define BPORT1_AB_LUT52_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT52_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT52_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT52_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT52_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT53    (BPORT1 + 0x3e4)

#define BPORT1_AB_LUT53_OPRND0   0xff
#define BPORT1_AB_LUT53_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT53_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT53_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT53_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT53_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT54    (BPORT1 + 0x3e8)

#define BPORT1_AB_LUT54_OPRND0   0xff
#define BPORT1_AB_LUT54_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT54_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT54_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT54_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT54_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT55    (BPORT1 + 0x3ec)

#define BPORT1_AB_LUT55_OPRND0   0xff
#define BPORT1_AB_LUT55_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT55_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT55_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT55_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT55_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT56    (BPORT1 + 0x3f0)

#define BPORT1_AB_LUT56_OPRND0   0xff
#define BPORT1_AB_LUT56_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT56_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT56_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT56_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT56_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT57    (BPORT1 + 0x3f4)

#define BPORT1_AB_LUT57_OPRND0   0xff
#define BPORT1_AB_LUT57_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT57_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT57_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT57_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT57_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT58    (BPORT1 + 0x3f8)

#define BPORT1_AB_LUT58_OPRND0   0xff
#define BPORT1_AB_LUT58_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT58_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT58_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT58_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT58_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT59    (BPORT1 + 0x3fc)

#define BPORT1_AB_LUT59_OPRND0   0xff
#define BPORT1_AB_LUT59_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT59_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT59_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT59_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT59_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT60    (BPORT1 + 0x400)

#define BPORT1_AB_LUT60_OPRND0   0xff
#define BPORT1_AB_LUT60_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT60_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT60_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT60_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT60_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT61    (BPORT1 + 0x404)

#define BPORT1_AB_LUT61_OPRND0   0xff
#define BPORT1_AB_LUT61_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT61_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT61_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT61_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT61_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT62    (BPORT1 + 0x408)

#define BPORT1_AB_LUT62_OPRND0   0xff
#define BPORT1_AB_LUT62_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT62_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT62_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT62_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT62_INSTR1   (0x3f << 26)
#define BPORT1_AB_LUT63    (BPORT1 + 0x40c)

#define BPORT1_AB_LUT63_OPRND0   0xff
#define BPORT1_AB_LUT63_PAD0   (0x3 << 8)
#define BPORT1_AB_LUT63_INSTR0   (0x3f << 10)
#define BPORT1_AB_LUT63_OPRND1   (0xff << 16)
#define BPORT1_AB_LUT63_PAD1   (0x3 << 24)
#define BPORT1_AB_LUT63_INSTR1   (0x3f << 26)


#endif
