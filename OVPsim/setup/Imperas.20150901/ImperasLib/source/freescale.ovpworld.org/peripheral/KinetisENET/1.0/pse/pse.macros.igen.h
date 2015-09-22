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
#define BPORT1_AB_EIR    (BPORT1 + 0x4)

#define BPORT1_AB_EIR_BABR   (0x1 << 30)
#define BPORT1_AB_EIR_BABT   (0x1 << 29)
#define BPORT1_AB_EIR_EBERR   (0x1 << 22)
#define BPORT1_AB_EIR_GRA   (0x1 << 28)
#define BPORT1_AB_EIR_LC   (0x1 << 21)
#define BPORT1_AB_EIR_MII   (0x1 << 23)
#define BPORT1_AB_EIR_PLR   (0x1 << 18)
#define BPORT1_AB_EIR_RL   (0x1 << 20)
#define BPORT1_AB_EIR_RXB   (0x1 << 24)
#define BPORT1_AB_EIR_RXF   (0x1 << 25)
#define BPORT1_AB_EIR_TS_AVAIL   (0x1 << 16)
#define BPORT1_AB_EIR_TS_TIMER   (0x1 << 15)
#define BPORT1_AB_EIR_TXB   (0x1 << 26)
#define BPORT1_AB_EIR_TXF   (0x1 << 27)
#define BPORT1_AB_EIR_UN   (0x1 << 19)
#define BPORT1_AB_EIR_WAKEUP   (0x1 << 17)
#define BPORT1_AB_EIMR    (BPORT1 + 0x8)

#define BPORT1_AB_EIMR_BABR   (0x1 << 30)
#define BPORT1_AB_EIMR_BABT   (0x1 << 29)
#define BPORT1_AB_EIMR_EBERR   (0x1 << 22)
#define BPORT1_AB_EIMR_GRA   (0x1 << 28)
#define BPORT1_AB_EIMR_LC   (0x1 << 21)
#define BPORT1_AB_EIMR_MII   (0x1 << 23)
#define BPORT1_AB_EIMR_PLR   (0x1 << 18)
#define BPORT1_AB_EIMR_RL   (0x1 << 20)
#define BPORT1_AB_EIMR_RXB   (0x1 << 24)
#define BPORT1_AB_EIMR_RXF   (0x1 << 25)
#define BPORT1_AB_EIMR_TS_AVAIL   (0x1 << 16)
#define BPORT1_AB_EIMR_TS_TIMER   (0x1 << 15)
#define BPORT1_AB_EIMR_TXB   (0x1 << 26)
#define BPORT1_AB_EIMR_TXF   (0x1 << 27)
#define BPORT1_AB_EIMR_UN   (0x1 << 19)
#define BPORT1_AB_EIMR_WAKEUP   (0x1 << 17)
#define BPORT1_AB_RDAR    (BPORT1 + 0x10)

#define BPORT1_AB_RDAR_RDAR   (0x1 << 24)
#define BPORT1_AB_TDAR    (BPORT1 + 0x14)

#define BPORT1_AB_TDAR_TDAR   (0x1 << 24)
#define BPORT1_AB_ECR    (BPORT1 + 0x24)

#define BPORT1_AB_ECR_DBGEN   (0x1 << 6)
#define BPORT1_AB_ECR_DBSWP   (0x1 << 8)
#define BPORT1_AB_ECR_EN1588   (0x1 << 4)
#define BPORT1_AB_ECR_ETHEREN   (0x1 << 1)
#define BPORT1_AB_ECR_MAGICEN   (0x1 << 2)
#define BPORT1_AB_ECR_RESET   0x1
#define BPORT1_AB_ECR_SLEEP   (0x1 << 3)
#define BPORT1_AB_ECR_STOPEN   (0x1 << 7)
#define BPORT1_AB_MMFR    (BPORT1 + 0x40)

#define BPORT1_AB_MMFR_DATA   0xffff
#define BPORT1_AB_MMFR_OP   (0x3 << 28)
#define BPORT1_AB_MMFR_PA   (0x1f << 23)
#define BPORT1_AB_MMFR_RA   (0x1f << 18)
#define BPORT1_AB_MMFR_ST   (0x3 << 30)
#define BPORT1_AB_MMFR_TA   (0x3 << 16)
#define BPORT1_AB_MSCR    (BPORT1 + 0x44)

#define BPORT1_AB_MSCR_DIS_PRE   (0x1 << 7)
#define BPORT1_AB_MSCR_HOLDTIME   (0x7 << 8)
#define BPORT1_AB_MSCR_MII_SPEED   (0x3f << 1)
#define BPORT1_AB_MIBC    (BPORT1 + 0x64)

#define BPORT1_AB_MIBC_MIB_CLEAR   (0x1 << 29)
#define BPORT1_AB_MIBC_MIB_DIS   (0x1 << 31)
#define BPORT1_AB_MIBC_MIB_IDLE   (0x1 << 30)
#define BPORT1_AB_RCR    (BPORT1 + 0x84)

#define BPORT1_AB_RCR_BC_REJ   (0x1 << 4)
#define BPORT1_AB_RCR_CFEN   (0x1 << 15)
#define BPORT1_AB_RCR_CRCFWD   (0x1 << 14)
#define BPORT1_AB_RCR_DRT   (0x1 << 1)
#define BPORT1_AB_RCR_FCE   (0x1 << 5)
#define BPORT1_AB_RCR_GRS   (0x1 << 31)
#define BPORT1_AB_RCR_LOOP   0x1
#define BPORT1_AB_RCR_MAX_FL   (0x3fff << 16)
#define BPORT1_AB_RCR_MII_MODE   (0x1 << 2)
#define BPORT1_AB_RCR_NLC   (0x1 << 30)
#define BPORT1_AB_RCR_PADEN   (0x1 << 12)
#define BPORT1_AB_RCR_PAUFWD   (0x1 << 13)
#define BPORT1_AB_RCR_PROM   (0x1 << 3)
#define BPORT1_AB_RCR_RMII_10T   (0x1 << 9)
#define BPORT1_AB_RCR_RMII_MODE   (0x1 << 8)
#define BPORT1_AB_TCR    (BPORT1 + 0xc4)

#define BPORT1_AB_TCR_ADDINS   (0x1 << 8)
#define BPORT1_AB_TCR_ADDSEL   (0x7 << 5)
#define BPORT1_AB_TCR_CRCFWD   (0x1 << 9)
#define BPORT1_AB_TCR_FDEN   (0x1 << 2)
#define BPORT1_AB_TCR_GTS   0x1
#define BPORT1_AB_TCR_RFC_PAUSE   (0x1 << 4)
#define BPORT1_AB_TCR_TFC_PAUSE   (0x1 << 3)
#define BPORT1_AB_PALR    (BPORT1 + 0xe4)

#define BPORT1_AB_PALR_PADDR1   0xffffffff
#define BPORT1_AB_PAUR    (BPORT1 + 0xe8)

#define BPORT1_AB_PAUR_PADDR2   (0xffff << 16)
#define BPORT1_AB_PAUR_TYPE   0xffff
#define BPORT1_AB_OPD    (BPORT1 + 0xec)

#define BPORT1_AB_OPD_OPCODE   (0xffff << 16)
#define BPORT1_AB_OPD_PAUSE_DUR   0xffff
#define BPORT1_AB_IAUR    (BPORT1 + 0x118)

#define BPORT1_AB_IAUR_IADDR1   0xffffffff
#define BPORT1_AB_IALR    (BPORT1 + 0x11c)

#define BPORT1_AB_IALR_IADDR2   0xffffffff
#define BPORT1_AB_GAUR    (BPORT1 + 0x120)

#define BPORT1_AB_GAUR_GADDR1   0xffffffff
#define BPORT1_AB_GALR    (BPORT1 + 0x124)

#define BPORT1_AB_GALR_GADDR2   0xffffffff
#define BPORT1_AB_TFWR    (BPORT1 + 0x144)

#define BPORT1_AB_TFWR_STRFWD   (0x1 << 8)
#define BPORT1_AB_TFWR_TFWR   0x3f
#define BPORT1_AB_RDSR    (BPORT1 + 0x180)

#define BPORT1_AB_RDSR_R_DES_START   (0x1fffffff << 3)
#define BPORT1_AB_TDSR    (BPORT1 + 0x184)

#define BPORT1_AB_TDSR_X_DES_START   (0x1fffffff << 3)
#define BPORT1_AB_MRBR    (BPORT1 + 0x188)

#define BPORT1_AB_MRBR_R_BUF_SIZE   (0x3ff << 4)
#define BPORT1_AB_RSFL    (BPORT1 + 0x190)

#define BPORT1_AB_RSFL_RX_SECTION_FULL   0xff
#define BPORT1_AB_RSEM    (BPORT1 + 0x194)

#define BPORT1_AB_RSEM_RX_SECTION_EMPTY   0xff
#define BPORT1_AB_RAEM    (BPORT1 + 0x198)

#define BPORT1_AB_RAEM_RX_ALMOST_EMPTY   0xff
#define BPORT1_AB_RAFL    (BPORT1 + 0x19c)

#define BPORT1_AB_RAFL_RX_ALMOST_FULL   0xff
#define BPORT1_AB_TSEM    (BPORT1 + 0x1a0)

#define BPORT1_AB_TSEM_TX_SECTION_EMPTY   0xff
#define BPORT1_AB_TAEM    (BPORT1 + 0x1a4)

#define BPORT1_AB_TAEM_TX_ALMOST_EMPTY   0xff
#define BPORT1_AB_TAFL    (BPORT1 + 0x1a8)

#define BPORT1_AB_TAFL_TX_ALMOST_FULL   0xff
#define BPORT1_AB_TIPG    (BPORT1 + 0x1ac)

#define BPORT1_AB_TIPG_IPG   0x1f
#define BPORT1_AB_FTRL    (BPORT1 + 0x1b0)

#define BPORT1_AB_FTRL_TRUNC_FL   0x3fff
#define BPORT1_AB_TACC    (BPORT1 + 0x1c0)

#define BPORT1_AB_TACC_IPCHK   (0x1 << 3)
#define BPORT1_AB_TACC_PROCHK   (0x1 << 4)
#define BPORT1_AB_TACC_SHIFT16   0x1
#define BPORT1_AB_RACC    (BPORT1 + 0x1c4)

#define BPORT1_AB_RACC_IPDIS   (0x1 << 1)
#define BPORT1_AB_RACC_LINEDIS   (0x1 << 6)
#define BPORT1_AB_RACC_PADREM   0x1
#define BPORT1_AB_RACC_PRODIS   (0x1 << 2)
#define BPORT1_AB_RACC_SHIFT16   (0x1 << 7)
#define BPORT1_AB_RMON_T_DROP    (BPORT1 + 0x200)

#define BPORT1_AB_RMON_T_PACKETS    (BPORT1 + 0x204)

#define BPORT1_AB_RMON_T_BC_PKT    (BPORT1 + 0x208)

#define BPORT1_AB_RMON_T_MC_PKT    (BPORT1 + 0x20c)

#define BPORT1_AB_RMON_T_CRC_ALIGN    (BPORT1 + 0x210)

#define BPORT1_AB_RMON_T_UNDERSIZE    (BPORT1 + 0x214)

#define BPORT1_AB_RMON_T_OVERSIZE    (BPORT1 + 0x218)

#define BPORT1_AB_RMON_T_FRAG    (BPORT1 + 0x21c)

#define BPORT1_AB_RMON_T_JAB    (BPORT1 + 0x220)

#define BPORT1_AB_RMON_T_COL    (BPORT1 + 0x224)

#define BPORT1_AB_RMON_T_P64    (BPORT1 + 0x228)

#define BPORT1_AB_RMON_T_P65TO127    (BPORT1 + 0x22c)

#define BPORT1_AB_RMON_T_P128TO255    (BPORT1 + 0x230)

#define BPORT1_AB_RMON_T_P256TO511    (BPORT1 + 0x234)

#define BPORT1_AB_RMON_T_P512TO1023    (BPORT1 + 0x238)

#define BPORT1_AB_RMON_T_P1024TO2047    (BPORT1 + 0x23c)

#define BPORT1_AB_RMON_T_P_GTE2048    (BPORT1 + 0x240)

#define BPORT1_AB_RMON_T_OCTETS    (BPORT1 + 0x244)

#define BPORT1_AB_IEEE_T_DROP    (BPORT1 + 0x248)

#define BPORT1_AB_IEEE_T_FRAME_OK    (BPORT1 + 0x24c)

#define BPORT1_AB_IEEE_T_1COL    (BPORT1 + 0x250)

#define BPORT1_AB_IEEE_T_MCOL    (BPORT1 + 0x254)

#define BPORT1_AB_IEEE_T_DEF    (BPORT1 + 0x258)

#define BPORT1_AB_IEEE_T_LCOL    (BPORT1 + 0x25c)

#define BPORT1_AB_IEEE_T_EXCOL    (BPORT1 + 0x260)

#define BPORT1_AB_IEEE_T_MACERR    (BPORT1 + 0x264)

#define BPORT1_AB_IEEE_T_CSERR    (BPORT1 + 0x268)

#define BPORT1_AB_IEEE_T_SQE    (BPORT1 + 0x26c)

#define BPORT1_AB_IEEE_T_FDXFC    (BPORT1 + 0x270)

#define BPORT1_AB_IEEE_T_OCTETS_OK    (BPORT1 + 0x274)

#define BPORT1_AB_RMON_R_PACKETS    (BPORT1 + 0x284)

#define BPORT1_AB_RMON_R_BC_PKT    (BPORT1 + 0x288)

#define BPORT1_AB_RMON_R_MC_PKT    (BPORT1 + 0x28c)

#define BPORT1_AB_RMON_R_CRC_ALIGN    (BPORT1 + 0x290)

#define BPORT1_AB_RMON_R_UNDERSIZE    (BPORT1 + 0x294)

#define BPORT1_AB_RMON_R_OVERSIZE    (BPORT1 + 0x298)

#define BPORT1_AB_RMON_R_FRAG    (BPORT1 + 0x29c)

#define BPORT1_AB_RMON_R_JAB    (BPORT1 + 0x2a0)

#define BPORT1_AB_RMON_R_RESVD_0    (BPORT1 + 0x2a4)

#define BPORT1_AB_RMON_R_P64    (BPORT1 + 0x2a8)

#define BPORT1_AB_RMON_R_P65TO127    (BPORT1 + 0x2ac)

#define BPORT1_AB_RMON_R_P128TO255    (BPORT1 + 0x2b0)

#define BPORT1_AB_RMON_R_P256TO511    (BPORT1 + 0x2b4)

#define BPORT1_AB_RMON_R_P512TO1023    (BPORT1 + 0x2b8)

#define BPORT1_AB_RMON_R_P1024TO2047    (BPORT1 + 0x2bc)

#define BPORT1_AB_RMON_R_P_GTE2048    (BPORT1 + 0x2c0)

#define BPORT1_AB_RMON_R_OCTETS    (BPORT1 + 0x2c4)

#define BPORT1_AB_RMON_R_DROP    (BPORT1 + 0x2c8)

#define BPORT1_AB_RMON_R_FRAME_OK    (BPORT1 + 0x2cc)

#define BPORT1_AB_IEEE_R_CRC    (BPORT1 + 0x2d0)

#define BPORT1_AB_IEEE_R_ALIGN    (BPORT1 + 0x2d4)

#define BPORT1_AB_IEEE_R_MACERR    (BPORT1 + 0x2d8)

#define BPORT1_AB_IEEE_R_FDXFC    (BPORT1 + 0x2dc)

#define BPORT1_AB_IEEE_R_OCTETS_OK    (BPORT1 + 0x2e0)

#define BPORT1_AB_ATCR    (BPORT1 + 0x400)

#define BPORT1_AB_ATCR_CAPTURE   (0x1 << 11)
#define BPORT1_AB_ATCR_EN   0x1
#define BPORT1_AB_ATCR_OFFEN   (0x1 << 2)
#define BPORT1_AB_ATCR_OFFRST   (0x1 << 3)
#define BPORT1_AB_ATCR_PEREN   (0x1 << 4)
#define BPORT1_AB_ATCR_PINPER   (0x1 << 7)
#define BPORT1_AB_ATCR_RESTART   (0x1 << 9)
#define BPORT1_AB_ATCR_SLAVE   (0x1 << 13)
#define BPORT1_AB_ATVR    (BPORT1 + 0x404)

#define BPORT1_AB_ATVR_ATIME   0xffffffff
#define BPORT1_AB_ATOFF    (BPORT1 + 0x408)

#define BPORT1_AB_ATOFF_OFFSET   0xffffffff
#define BPORT1_AB_ATPER    (BPORT1 + 0x40c)

#define BPORT1_AB_ATPER_PERIOD   0xffffffff
#define BPORT1_AB_ATCOR    (BPORT1 + 0x410)

#define BPORT1_AB_ATCOR_COR   0x7fffffff
#define BPORT1_AB_ATINC    (BPORT1 + 0x414)

#define BPORT1_AB_ATINC_INC   0x7f
#define BPORT1_AB_ATINC_INC_CORR   (0x7f << 8)
#define BPORT1_AB_ATSTMP    (BPORT1 + 0x418)

#define BPORT1_AB_ATSTMP_TIMESTAMP   0xffffffff
#define BPORT1_AB_TGSR    (BPORT1 + 0x604)

#define BPORT1_AB_TGSR_TF0   0x1
#define BPORT1_AB_TGSR_TF1   (0x1 << 1)
#define BPORT1_AB_TGSR_TF2   (0x1 << 2)
#define BPORT1_AB_TGSR_TF3   (0x1 << 3)
#define BPORT1_AB_TCSR0    (BPORT1 + 0x608)

#define BPORT1_AB_TCSR0_TDRE   0x1
#define BPORT1_AB_TCSR0_TF   (0x1 << 7)
#define BPORT1_AB_TCSR0_TIE   (0x1 << 6)
#define BPORT1_AB_TCSR0_TMODE   (0xf << 2)
#define BPORT1_AB_TCCR0    (BPORT1 + 0x60c)

#define BPORT1_AB_TCCR0_TCC   0xffffffff
#define BPORT1_AB_TCSR1    (BPORT1 + 0x610)

#define BPORT1_AB_TCSR1_TDRE   0x1
#define BPORT1_AB_TCSR1_TF   (0x1 << 7)
#define BPORT1_AB_TCSR1_TIE   (0x1 << 6)
#define BPORT1_AB_TCSR1_TMODE   (0xf << 2)
#define BPORT1_AB_TCCR1    (BPORT1 + 0x614)

#define BPORT1_AB_TCCR1_TCC   0xffffffff
#define BPORT1_AB_TCSR2    (BPORT1 + 0x618)

#define BPORT1_AB_TCSR2_TDRE   0x1
#define BPORT1_AB_TCSR2_TF   (0x1 << 7)
#define BPORT1_AB_TCSR2_TIE   (0x1 << 6)
#define BPORT1_AB_TCSR2_TMODE   (0xf << 2)
#define BPORT1_AB_TCCR2    (BPORT1 + 0x61c)

#define BPORT1_AB_TCCR2_TCC   0xffffffff
#define BPORT1_AB_TCSR3    (BPORT1 + 0x620)

#define BPORT1_AB_TCSR3_TDRE   0x1
#define BPORT1_AB_TCSR3_TF   (0x1 << 7)
#define BPORT1_AB_TCSR3_TIE   (0x1 << 6)
#define BPORT1_AB_TCSR3_TMODE   (0xf << 2)
#define BPORT1_AB_TCCR3    (BPORT1 + 0x624)

#define BPORT1_AB_TCCR3_TCC   0xffffffff


#endif
