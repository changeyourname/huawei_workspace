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
// Set the macro 'CSIBP0' to the base of port 'CSIBP0'
#ifndef CSIBP0
    #error CSIBP0 is undefined.It needs to be set to the port base address
#endif
#define CSIBP0_REG0_CTL0    (CSIBP0 + 0x0)

#define CSIBP0_REG0_CTL0_SCE   0x1
#define CSIBP0_REG0_CTL0_TMS   (0x1 << 1)
#define CSIBP0_REG0_CTL0_SSE   (0x1 << 2)
#define CSIBP0_REG0_CTL0_DIR   (0x1 << 4)
#define CSIBP0_REG0_CTL0_RXE   (0x1 << 5)
#define CSIBP0_REG0_CTL0_TXE   (0x1 << 6)
#define CSIBP0_REG0_CTL0_PWR   (0x1 << 7)
#define CSIBP0_REG0_CTL1    (CSIBP0 + 0x1)

#define CSIBP0_REG0_CTL1_CKS   0xf
#define CSIBP0_REG0_CTL2    (CSIBP0 + 0x2)

#define CSIBP0_REG0_CTL2_CL   0xf
#define CSIBP0_REG0_STR    (CSIBP0 + 0x3)

#define CSIBP0_REG0_STR_OVE   0x1
#define CSIBP0_REG0_STR_TSF   (0x1 << 7)
#define CSIBP0_REG1_RX    (CSIBP0 + 0x4)

#define CSIBP0_REG1_RX_RXL   0xff
#define CSIBP0_REG1_RX_RXH   (0xff << 8)
#define CSIBP0_REG1_TX    (CSIBP0 + 0x6)

#define CSIBP0_REG1_TX_TXL   0xff
#define CSIBP0_REG1_TX_TXH   (0xff << 8)


#endif
