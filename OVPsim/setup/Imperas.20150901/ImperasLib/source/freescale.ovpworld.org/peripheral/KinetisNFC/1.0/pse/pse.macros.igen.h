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
#define BPORT1_AB_CMD1    (BPORT1 + 0x3f00)

#define BPORT1_AB_CMD1_BYTE2   (0xff << 24)
#define BPORT1_AB_CMD1_BYTE3   (0xff << 16)
#define BPORT1_AB_CMD2    (BPORT1 + 0x3f04)

#define BPORT1_AB_CMD2_BUFNO   (0x3 << 1)
#define BPORT1_AB_CMD2_BUSY_START   0x1
#define BPORT1_AB_CMD2_BYTE1   (0xff << 24)
#define BPORT1_AB_CMD2_CODE   (0xffff << 8)
#define BPORT1_AB_CAR    (BPORT1 + 0x3f08)

#define BPORT1_AB_CAR_BYTE1   0xff
#define BPORT1_AB_CAR_BYTE2   (0xff << 8)
#define BPORT1_AB_RAR    (BPORT1 + 0x3f0c)

#define BPORT1_AB_RAR_BYTE1   0xff
#define BPORT1_AB_RAR_BYTE2   (0xff << 8)
#define BPORT1_AB_RAR_BYTE3   (0xff << 16)
#define BPORT1_AB_RAR_CS0   (0x1 << 28)
#define BPORT1_AB_RAR_CS1   (0x1 << 29)
#define BPORT1_AB_RAR_RB0   (0x1 << 24)
#define BPORT1_AB_RAR_RB1   (0x1 << 25)
#define BPORT1_AB_RPT    (BPORT1 + 0x3f10)

#define BPORT1_AB_RPT_COUNT   0xffff
#define BPORT1_AB_RAI    (BPORT1 + 0x3f14)

#define BPORT1_AB_RAI_INC1   0xff
#define BPORT1_AB_RAI_INC2   (0xff << 8)
#define BPORT1_AB_RAI_INC3   (0xff << 16)
#define BPORT1_AB_SR1    (BPORT1 + 0x3f18)

#define BPORT1_AB_SR1_ID1   (0xff << 24)
#define BPORT1_AB_SR1_ID2   (0xff << 16)
#define BPORT1_AB_SR1_ID3   (0xff << 8)
#define BPORT1_AB_SR1_ID4   0xff
#define BPORT1_AB_SR2    (BPORT1 + 0x3f1c)

#define BPORT1_AB_SR2_ID5   (0xff << 24)
#define BPORT1_AB_SR2_STATUS1   0xff
#define BPORT1_AB_DMA1    (BPORT1 + 0x3f20)

#define BPORT1_AB_DMA1_ADDRESS   0xffffffff
#define BPORT1_AB_DMACFG    (BPORT1 + 0x3f24)

#define BPORT1_AB_DMACFG_ACT1   (0x1 << 1)
#define BPORT1_AB_DMACFG_ACT2   0x1
#define BPORT1_AB_DMACFG_COUNT1   (0xfff << 20)
#define BPORT1_AB_DMACFG_COUNT2   (0x7f << 13)
#define BPORT1_AB_DMACFG_OFFSET2   (0xf << 9)
#define BPORT1_AB_SWAP    (BPORT1 + 0x3f28)

#define BPORT1_AB_SWAP_ADDR1   (0x7ff << 17)
#define BPORT1_AB_SWAP_ADDR2   (0x7ff << 1)
#define BPORT1_AB_SECSZ    (BPORT1 + 0x3f2c)

#define BPORT1_AB_SECSZ_SIZE   0x1fff
#define BPORT1_AB_CFG    (BPORT1 + 0x3f30)

#define BPORT1_AB_CFG_AIAD   (0x1 << 5)
#define BPORT1_AB_CFG_AIBN   (0x1 << 4)
#define BPORT1_AB_CFG_BITWIDTH   (0x1 << 7)
#define BPORT1_AB_CFG_BTMD   (0x1 << 6)
#define BPORT1_AB_CFG_DMAREQ   (0x1 << 20)
#define BPORT1_AB_CFG_ECCAD   (0x1ff << 22)
#define BPORT1_AB_CFG_ECCMODE   (0x7 << 17)
#define BPORT1_AB_CFG_ECCSRAM   (0x1 << 21)
#define BPORT1_AB_CFG_FAST   (0x1 << 16)
#define BPORT1_AB_CFG_IDCNT   (0x7 << 13)
#define BPORT1_AB_CFG_PAGECNT   0xf
#define BPORT1_AB_CFG_STOPWERR   (0x1 << 31)
#define BPORT1_AB_CFG_TIMEOUT   (0x1f << 8)
#define BPORT1_AB_DMA2    (BPORT1 + 0x3f34)

#define BPORT1_AB_DMA2_ADDRESS   0xffffffff
#define BPORT1_AB_ISR    (BPORT1 + 0x3f38)

#define BPORT1_AB_ISR_CMDBUSY   (0x1 << 26)
#define BPORT1_AB_ISR_DMABN   0x3
#define BPORT1_AB_ISR_DMABUSY   (0x1 << 23)
#define BPORT1_AB_ISR_DONE   (0x1 << 30)
#define BPORT1_AB_ISR_DONECLR   (0x1 << 18)
#define BPORT1_AB_ISR_DONEEN   (0x1 << 21)
#define BPORT1_AB_ISR_ECCBN   (0x3 << 2)
#define BPORT1_AB_ISR_ECCBUSY   (0x1 << 24)
#define BPORT1_AB_ISR_IDLE   (0x1 << 29)
#define BPORT1_AB_ISR_IDLECLR   (0x1 << 17)
#define BPORT1_AB_ISR_IDLEEN   (0x1 << 20)
#define BPORT1_AB_ISR_RESBN   (0x3 << 4)
#define BPORT1_AB_ISR_RESBUSY   (0x1 << 25)
#define BPORT1_AB_ISR_WERR   (0x1 << 31)
#define BPORT1_AB_ISR_WERRCLR   (0x1 << 19)
#define BPORT1_AB_ISR_WERREN   (0x1 << 22)
#define BPORT1_AB_ISR_WERRNS   (0x1 << 27)


#endif
