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
// Set the macro 'TAAP0' to the base of port 'TAAP0'
#ifndef TAAP0
    #error TAAP0 is undefined.It needs to be set to the port base address
#endif
#define TAAP0_REG0_CTL0    (TAAP0 + 0x0)

#define TAAP0_REG0_CTL0_CKS   0x7
#define TAAP0_REG0_CTL0_CE   (0x1 << 7)
#define TAAP0_REG0_CTL1    (TAAP0 + 0x1)

#define TAAP0_REG0_CTL1_MD   0x7
#define TAAP0_REG0_CTL1_EEE   (0x1 << 5)
#define TAAP0_REG0_CTL1_EST   (0x1 << 6)
#define TAAP0_REG0_CTL1_SYE   (0x1 << 7)
#define TAAP0_REG0_IOC0    (TAAP0 + 0x2)

#define TAAP0_REG0_IOC0_OE0   0x1
#define TAAP0_REG0_IOC0_OL0   (0x1 << 1)
#define TAAP0_REG0_IOC0_OE1   (0x1 << 2)
#define TAAP0_REG0_IOC0_OL1   (0x1 << 3)
#define TAAP0_REG0_IOC1    (TAAP0 + 0x3)

#define TAAP0_REG0_IOC1_IS   0xf
#define TAAP0_REG0_IOC2    (TAAP0 + 0x4)

#define TAAP0_REG0_IOC2_ETS   0x3
#define TAAP0_REG0_IOC2_EES   (0x3 << 2)
#define TAAP0_REG0_OPT0    (TAAP0 + 0x5)

#define TAAP0_REG0_OPT0_OVF   0x1
#define TAAP0_REG0_OPT0_CCS   (0x3 << 4)
#define TAAP0_REG1_CCR0    (TAAP0 + 0x6)

#define TAAP0_REG1_CCR1    (TAAP0 + 0x8)

#define TAAP0_REG1_CNT    (TAAP0 + 0xa)

#define TAAP0_REG2_IOC4    (TAAP0 + 0xc)

#define TAAP0_REG2_IOC4_OR0   0x1
#define TAAP0_REG2_IOC4_OS0   (0x1 << 1)
#define TAAP0_REG2_IOC4_OR1   (0x1 << 2)
#define TAAP0_REG2_IOC4_OS1   (0x1 << 3)
#define TAAP0_REG2_SVC    (TAAP0 + 0xe)

#define TAAP0_REG2_SVC_CSR0   0x1
#define TAAP0_REG2_SVC_CSD0   (0x1 << 1)
#define TAAP0_REG2_SVC_CSE0   (0x1 << 2)
#define TAAP0_REG2_SVC_ENC0   (0x1 << 3)
#define TAAP0_REG2_SVC_CSR1   (0x1 << 4)
#define TAAP0_REG2_SVC_CSD1   (0x1 << 5)
#define TAAP0_REG2_SVC_CSE1   (0x1 << 6)
#define TAAP0_REG2_SVC_ENC1   (0x1 << 7)


#endif
