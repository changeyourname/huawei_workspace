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
// Set the macro 'TMSP0' to the base of port 'TMSP0'
#ifndef TMSP0
    #error TMSP0 is undefined.It needs to be set to the port base address
#endif
#define TMSP0_REG0_CTL0    (TMSP0 + 0x0)

#define TMSP0_REG0_CTL0_CKS   0x7
#define TMSP0_REG0_CTL0_CE   (0x1 << 7)
#define TMSP0_REG0_CTL1    (TMSP0 + 0x1)

#define TMSP0_REG0_CTL1_MD   0xf
#define TMSP0_REG0_CTL1_EEE   (0x1 << 5)
#define TMSP0_REG0_CTL1_EST   (0x1 << 6)
#define TMSP0_REG1_IOC0    (TMSP0 + 0x2)

#define TMSP0_REG1_IOC0_OE0   0x1
#define TMSP0_REG1_IOC0_OL0   (0x1 << 1)
#define TMSP0_REG1_IOC0_OE1   (0x1 << 2)
#define TMSP0_REG1_IOC0_OL1   (0x1 << 3)
#define TMSP0_REG1_IOC0_OE2   (0x1 << 4)
#define TMSP0_REG1_IOC0_OL2   (0x1 << 5)
#define TMSP0_REG1_IOC0_OE3   (0x1 << 6)
#define TMSP0_REG1_IOC0_OL3   (0x1 << 7)
#define TMSP0_REG1_IOC0_OE4   (0x1 << 8)
#define TMSP0_REG1_IOC0_OL4   (0x1 << 9)
#define TMSP0_REG1_IOC0_OE5   (0x1 << 10)
#define TMSP0_REG1_IOC0_OL5   (0x1 << 11)
#define TMSP0_REG1_IOC0_OE6   (0x1 << 12)
#define TMSP0_REG1_IOC0_OL6   (0x1 << 13)
#define TMSP0_REG1_IOC0_OE7   (0x1 << 14)
#define TMSP0_REG1_IOC0_OL7   (0x1 << 15)
#define TMSP0_REG2_IOC2    (TMSP0 + 0x4)

#define TMSP0_REG2_IOC2_ETS   0x3
#define TMSP0_REG2_IOC2_EES   (0x3 << 2)
#define TMSP0_REG2_IOC4    (TMSP0 + 0x5)

#define TMSP0_REG2_IOC4_EOC   0x1
#define TMSP0_REG2_IOC4_WOC   (0x1 << 2)
#define TMSP0_REG2_IOC4_BA   (0x7 << 4)
#define TMSP0_REG2_OPT0    (TMSP0 + 0x6)

#define TMSP0_REG2_OPT0_OVF   0x1
#define TMSP0_REG2_OPT0_CUF   (0x1 << 1)
#define TMSP0_REG2_OPT0_CMS   (0x1 << 2)
#define TMSP0_REG2_OPT0_DSE   (0x1 << 3)
#define TMSP0_REG2_OPT4    (TMSP0 + 0x8)

#define TMSP0_REG2_OPT4_IPC   0x7
#define TMSP0_REG2_OPT4_PSC   (0x1 << 3)
#define TMSP0_REG2_OPT4_SOC   (0x1 << 7)
#define TMSP0_REG2_OPT5    (TMSP0 + 0x9)

#define TMSP0_REG2_OPT5_OPF   0x7
#define TMSP0_REG2_OPT5_TSF   (0x1 << 3)
#define TMSP0_REG2_OPT5_PTS   (0x1 << 4)
#define TMSP0_REG2_OPT5_PSS   (0x1 << 5)
#define TMSP0_REG2_OPT5_POT   (0x1 << 6)
#define TMSP0_REG2_OPT5_ADC   (0x1 << 7)
#define TMSP0_REG2_OPT7    (TMSP0 + 0x7)

#define TMSP0_REG2_OPT7_TOS   0x1
#define TMSP0_REG2_OPT7_PTC   (0x3 << 1)
#define TMSP0_REG2_OPT7_TDC   (0x1 << 3)
#define TMSP0_REG2_OPT7_PPC   (0x1 << 4)
#define TMSP0_REG2_OPT7_IDC   (0x1 << 5)
#define TMSP0_REG3_OPT1    (TMSP0 + 0xa)

#define TMSP0_REG3_OPT1_ID   0x1f
#define TMSP0_REG3_OPT1_RDE   (0x1 << 5)
#define TMSP0_REG3_OPT1_IOE   (0x1 << 6)
#define TMSP0_REG3_OPT1_ICE   (0x1 << 7)
#define TMSP0_REG3_OPT1_RBE   (0x1 << 8)
#define TMSP0_REG3_OPT1_RTE   (0x1 << 9)
#define TMSP0_REG3_OPT2    (TMSP0 + 0x20)

#define TMSP0_REG3_OPT2_AT00   0x1
#define TMSP0_REG3_OPT2_AT01   (0x1 << 1)
#define TMSP0_REG3_OPT2_AT02   (0x1 << 2)
#define TMSP0_REG3_OPT2_AT03   (0x1 << 3)
#define TMSP0_REG3_OPT2_AT04   (0x1 << 4)
#define TMSP0_REG3_OPT2_AT05   (0x1 << 5)
#define TMSP0_REG3_OPT2_AT06   (0x1 << 6)
#define TMSP0_REG3_OPT2_AT07   (0x1 << 7)
#define TMSP0_REG3_OPT2_ACC0   (0x1 << 8)
#define TMSP0_REG3_OPT2_ACC1   (0x1 << 9)
#define TMSP0_REG3_OPT3    (TMSP0 + 0x22)

#define TMSP0_REG3_OPT3_AT00   0x1
#define TMSP0_REG3_OPT3_AT01   (0x1 << 1)
#define TMSP0_REG3_OPT3_AT02   (0x1 << 2)
#define TMSP0_REG3_OPT3_AT03   (0x1 << 3)
#define TMSP0_REG3_OPT3_AT04   (0x1 << 4)
#define TMSP0_REG3_OPT3_AT05   (0x1 << 5)
#define TMSP0_REG3_OPT3_AT06   (0x1 << 6)
#define TMSP0_REG3_OPT3_AT07   (0x1 << 7)
#define TMSP0_REG3_OPT3_ACC2   (0x1 << 8)
#define TMSP0_REG3_OPT3_ACC3   (0x1 << 9)
#define TMSP0_REG3_OPT6    (TMSP0 + 0x24)

#define TMSP0_REG3_OPT6_RSF   0x1
#define TMSP0_REG3_OPT6_SUF   (0x1 << 1)
#define TMSP0_REG3_OPT6_TBF   (0x1 << 2)
#define TMSP0_REG3_OPT6_PEF   (0x1 << 3)
#define TMSP0_REG3_OPT6_PRF   (0x1 << 4)
#define TMSP0_REG3_OPT6_NDF   (0x1 << 5)
#define TMSP0_REG3_OPT6_TDF   (0x1 << 6)
#define TMSP0_REG3_OPT6_PTF   (0x1 << 7)
#define TMSP0_REG3_OPT6_PPF   (0x1 << 8)
#define TMSP0_REG3_DTC0    (TMSP0 + 0xe)

#define TMSP0_REG3_DTC0_DTV   (0x1ff << 1)
#define TMSP0_REG3_DTC1    (TMSP0 + 0xc)

#define TMSP0_REG3_DTC1_DTV   (0x1ff << 1)
#define TMSP0_REG3_PAT0    (TMSP0 + 0x16)

#define TMSP0_REG3_PAT0_SP0   0xf
#define TMSP0_REG3_PAT0_SP1   (0xf << 4)
#define TMSP0_REG3_PAT0_SP2   (0xf << 8)
#define TMSP0_REG3_PAT0_SP3   (0xf << 12)
#define TMSP0_REG3_PAT1    (TMSP0 + 0x14)

#define TMSP0_REG3_PAT1_SP4   0xf
#define TMSP0_REG3_PAT1_SP5   (0xf << 4)
#define TMSP0_REG3_PAT1_SP6   (0xf << 8)
#define TMSP0_REG3_PAT1_SP7   (0xf << 12)
#define TMSP0_REG3_CCR0    (TMSP0 + 0x18)

#define TMSP0_REG3_CCR1    (TMSP0 + 0x1e)

#define TMSP0_REG3_CCR2    (TMSP0 + 0x1c)

#define TMSP0_REG3_CCR3    (TMSP0 + 0x1a)

#define TMSP0_REG3_CCR4    (TMSP0 + 0x12)

#define TMSP0_REG3_CCR5    (TMSP0 + 0x10)

#define TMSP0_REG3_CNT    (TMSP0 + 0x26)

#define TMSP0_REG3_CNT_MODE   0x1
#define TMSP0_REG3_CNT_VAL   (0x7fff << 1)
#define TMSP0_REG3_SBC    (TMSP0 + 0x28)

#define TMSP0_REG3_SBC_MODE   0x1
#define TMSP0_REG3_SBC_SVAL   (0x7fff << 1)


#endif
