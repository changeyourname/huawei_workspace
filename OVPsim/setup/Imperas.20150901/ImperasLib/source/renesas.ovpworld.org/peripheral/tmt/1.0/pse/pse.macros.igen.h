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
// Set the macro 'TMTP0' to the base of port 'TMTP0'
#ifndef TMTP0
    #error TMTP0 is undefined.It needs to be set to the port base address
#endif
#define TMTP0_REG0_CTL0    (TMTP0 + 0x0)

#define TMTP0_REG0_CTL0_CKS   0x7
#define TMTP0_REG0_CTL0_CE   (0x1 << 7)
#define TMTP0_REG0_CTL1    (TMTP0 + 0x1)

#define TMTP0_REG0_CTL1_MD   0xf
#define TMTP0_REG0_CTL1_EEE   (0x1 << 5)
#define TMTP0_REG0_CTL1_EST   (0x1 << 6)
#define TMTP0_REG0_CTL2    (TMTP0 + 0x2)

#define TMTP0_REG0_CTL2_UDS   0x3
#define TMTP0_REG0_CTL2_ECM   (0x3 << 2)
#define TMTP0_REG0_CTL2_LDE   (0x1 << 4)
#define TMTP0_REG0_CTL2_ECC   (0x1 << 7)
#define TMTP0_REG0_IOC0    (TMTP0 + 0x3)

#define TMTP0_REG0_IOC0_OE0   0x1
#define TMTP0_REG0_IOC0_OL0   (0x1 << 1)
#define TMTP0_REG0_IOC0_OE1   (0x1 << 2)
#define TMTP0_REG0_IOC0_OL1   (0x1 << 3)
#define TMTP0_REG0_IOC1    (TMTP0 + 0x4)

#define TMTP0_REG0_IOC1_IS   0xf
#define TMTP0_REG0_IOC2    (TMTP0 + 0x5)

#define TMTP0_REG0_IOC2_ETS   0x3
#define TMTP0_REG0_IOC2_EES   (0x3 << 2)
#define TMTP0_REG0_IOC3    (TMTP0 + 0x6)

#define TMTP0_REG0_IOC3_EIS   0x3
#define TMTP0_REG0_IOC3_ECS   (0x3 << 2)
#define TMTP0_REG0_IOC3_ACL   (0x1 << 4)
#define TMTP0_REG0_IOC3_BCL   (0x1 << 5)
#define TMTP0_REG0_IOC3_ZCL   (0x1 << 6)
#define TMTP0_REG0_IOC3_SCE   (0x1 << 7)
#define TMTP0_REG0_OPT0    (TMTP0 + 0x7)

#define TMTP0_REG0_OPT0_OVF   0x1
#define TMTP0_REG0_OPT0_CCS   (0x3 << 4)
#define TMTP0_REG0_OPT1    (TMTP0 + 0x8)

#define TMTP0_REG0_OPT1_ESF   0x1
#define TMTP0_REG0_OPT1_EOF   (0x1 << 1)
#define TMTP0_REG0_OPT1_EUF   (0x1 << 2)
#define TMTP0_REG0_OPT2    (TMTP0 + 0x9)

#define TMTP0_REG0_OPT2_RSF   0x1
#define TMTP0_REG1_CCR0    (TMTP0 + 0xa)

#define TMTP0_REG1_CCR1    (TMTP0 + 0xc)

#define TMTP0_REG1_CNT    (TMTP0 + 0xe)


// Set the macro 'TMTP1' to the base of port 'TMTP1'
#ifndef TMTP1
    #error TMTP1 is undefined.It needs to be set to the port base address
#endif
#define TMTP1_REG0_TCW    (TMTP1 + 0x0)



#endif
