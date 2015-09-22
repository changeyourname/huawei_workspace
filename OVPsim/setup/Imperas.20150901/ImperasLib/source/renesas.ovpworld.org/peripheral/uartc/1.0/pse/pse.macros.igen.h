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
// Set the macro 'UARTP0' to the base of port 'UARTP0'
#ifndef UARTP0
    #error UARTP0 is undefined.It needs to be set to the port base address
#endif
#define UARTP0_REG0_CTL0    (UARTP0 + 0x0)

#define UARTP0_REG0_CTL0_SL   0x1
#define UARTP0_REG0_CTL0_CL   (0x1 << 1)
#define UARTP0_REG0_CTL0_PS   (0x3 << 2)
#define UARTP0_REG0_CTL0_DIR   (0x1 << 4)
#define UARTP0_REG0_CTL0_RXE   (0x1 << 5)
#define UARTP0_REG0_CTL0_TXE   (0x1 << 6)
#define UARTP0_REG0_CTL0_PWR   (0x1 << 7)
#define UARTP0_REG0_CTL1    (UARTP0 + 0x1)

#define UARTP0_REG0_CTL1_CKS   0xf
#define UARTP0_REG0_CTL2    (UARTP0 + 0x2)

#define UARTP0_REG0_CTL2_BRS   0xff
#define UARTP0_REG0_OPT0    (UARTP0 + 0x3)

#define UARTP0_REG0_OPT0_RDL   0x1
#define UARTP0_REG0_OPT0_TDL   (0x1 << 1)
#define UARTP0_REG0_OPT0_SLS   (0x7 << 2)
#define UARTP0_REG0_OPT0_STT   (0x1 << 5)
#define UARTP0_REG0_OPT0_SRT   (0x1 << 6)
#define UARTP0_REG0_OPT0_SRF   (0x1 << 7)
#define UARTP0_REG0_STR    (UARTP0 + 0x4)

#define UARTP0_REG0_STR_OVE   0x1
#define UARTP0_REG0_STR_FE   (0x1 << 1)
#define UARTP0_REG0_STR_PE   (0x1 << 2)
#define UARTP0_REG0_STR_TSF   (0x1 << 7)
#define UARTP0_REG1_RX    (UARTP0 + 0x6)

#define UARTP0_REG1_RX_RXL   0xff
#define UARTP0_REG1_RX_B9   (0x1 << 8)
#define UARTP0_REG1_TX    (UARTP0 + 0x8)

#define UARTP0_REG1_TX_TXL   0xff
#define UARTP0_REG1_TX_B9   (0x1 << 8)
#define UARTP0_REG2_OPT1    (UARTP0 + 0xa)

#define UARTP0_REG2_OPT1_EBE   0x1
#define UARTP0_REG2_OPT2    (UARTP0 + 0xb)

#define UARTP0_REG2_OPT2_RSF   0x1


#endif
