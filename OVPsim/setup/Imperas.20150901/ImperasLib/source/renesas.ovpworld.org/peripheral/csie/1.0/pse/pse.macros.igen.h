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
// Set the macro 'CSIEP0' to the base of port 'CSIEP0'
#ifndef CSIEP0
    #error CSIEP0 is undefined.It needs to be set to the port base address
#endif
#define CSIEP0_REG0_CTL0    (CSIEP0 + 0x0)

#define CSIEP0_REG0_CTL0_CSM   0x1
#define CSIEP0_REG0_CTL0_WE   (0x1 << 1)
#define CSIEP0_REG0_CTL0_SIT   (0x1 << 2)
#define CSIEP0_REG0_CTL0_DIR   (0x1 << 3)
#define CSIEP0_REG0_CTL0_TMS   (0x1 << 4)
#define CSIEP0_REG0_CTL0_RXE   (0x1 << 5)
#define CSIEP0_REG0_CTL0_TXE   (0x1 << 6)
#define CSIEP0_REG0_CTL0_PWR   (0x1 << 7)
#define CSIEP0_REG0_CTL1    (CSIEP0 + 0x1)

#define CSIEP0_REG0_CTL1_CKS   0x7
#define CSIEP0_REG0_CTL1_DAP   (0x1 << 3)
#define CSIEP0_REG0_CTL1_CKP   (0x1 << 4)
#define CSIEP0_REG0_CTL1_MDL   (0x7 << 5)
#define CSIEP0_REG1_RX    (CSIEP0 + 0x2)

#define CSIEP0_REG1_CS    (CSIEP0 + 0x4)

#define CSIEP0_REG1_CS_CS   0xf
#define CSIEP0_REG1_TX    (CSIEP0 + 0x6)

#define CSIEP0_REG2_STR    (CSIEP0 + 0x8)

#define CSIEP0_REG2_STR_SFP   0xf
#define CSIEP0_REG2_STR_TSF   (0x1 << 4)
#define CSIEP0_REG2_STR_EMF   (0x1 << 5)
#define CSIEP0_REG2_STR_FLF   (0x1 << 6)
#define CSIEP0_REG2_STR_PCT   (0x1 << 7)
#define CSIEP0_REG2_CTL2    (CSIEP0 + 0x9)

#define CSIEP0_REG2_CTL2_DL   0xf
#define CSIEP0_REG2_CTL2_CSL   (0xf << 4)
#define CSIEP0_REG2_CTL3    (CSIEP0 + 0xc)

#define CSIEP0_REG2_CTL3_SFN   0xf
#define CSIEP0_REG2_CTL4    (CSIEP0 + 0xd)

#define CSIEP0_REG2_CTL4_MD   0x1
#define CSIEP0_REG2_CTL4_OPE   (0x1 << 1)
#define CSIEP0_REG2_CTL4_DPA   (0x1 << 2)
#define CSIEP0_REG2_CTL4_CPA   (0x1 << 3)
#define CSIEP0_REG2_CTL4_CSL   (0xf << 4)
#define CSIEP0_REG3_OPT0    (CSIEP0 + 0x10)

#define CSIEP0_REG3_OPT1    (CSIEP0 + 0x12)

#define CSIEP0_REG3_OPT2    (CSIEP0 + 0x14)

#define CSIEP0_REG3_OPT3    (CSIEP0 + 0x16)

#define CSIEP0_REG3_OPT4    (CSIEP0 + 0x18)

#define CSIEP0_REG3_OPT5    (CSIEP0 + 0x1a)

#define CSIEP0_REG3_OPT6    (CSIEP0 + 0x1c)

#define CSIEP0_REG3_OPT7    (CSIEP0 + 0x1e)



#endif
