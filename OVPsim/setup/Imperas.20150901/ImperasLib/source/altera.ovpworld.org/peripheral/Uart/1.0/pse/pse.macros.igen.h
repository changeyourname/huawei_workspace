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
// Set the macro 'SP1' to the base of port 'sp1'
#ifndef SP1
    #error SP1 is undefined.It needs to be set to the port base address
#endif
#define SP1_REG0_RXDATA    (SP1 + 0x0)

#define SP1_REG0_TXDATA    (SP1 + 0x4)

#define SP1_REG0_STATUS    (SP1 + 0x8)

#define SP1_REG0_STATUS_PE   0x1
#define SP1_REG0_STATUS_FE   (0x1 << 1)
#define SP1_REG0_STATUS_BRK   (0x1 << 2)
#define SP1_REG0_STATUS_ROE   (0x1 << 3)
#define SP1_REG0_STATUS_TOE   (0x1 << 4)
#define SP1_REG0_STATUS_TMT   (0x1 << 5)
#define SP1_REG0_STATUS_TRDY   (0x1 << 6)
#define SP1_REG0_STATUS_RRDY   (0x1 << 7)
#define SP1_REG0_STATUS_E   (0x3 << 8)
#define SP1_REG0_STATUS_DCTS   (0x1 << 10)
#define SP1_REG0_STATUS_CTS   (0x1 << 11)
#define SP1_REG0_STATUS_EOP   (0x1 << 12)
#define SP1_REG0_CONTROL    (SP1 + 0xc)

#define SP1_REG0_CONTROL_IPE   0x1
#define SP1_REG0_CONTROL_IFE   (0x1 << 1)
#define SP1_REG0_CONTROL_IBRK   (0x1 << 2)
#define SP1_REG0_CONTROL_IROE   (0x1 << 3)
#define SP1_REG0_CONTROL_ITOE   (0x1 << 4)
#define SP1_REG0_CONTROL_ITMT   (0x1 << 5)
#define SP1_REG0_CONTROL_ITRDY   (0x1 << 6)
#define SP1_REG0_CONTROL_IRRDY   (0x1 << 7)
#define SP1_REG0_CONTROL_IE   (0x1 << 8)
#define SP1_REG0_CONTROL_TRBK   (0x1 << 9)
#define SP1_REG0_CONTROL_IDCTS   (0x1 << 10)
#define SP1_REG0_CONTROL_RTS   (0x1 << 11)
#define SP1_REG0_CONTROL_IEOP   (0x1 << 12)
#define SP1_REG0_DIVISOR    (SP1 + 0x10)

#define SP1_REG0_EOP    (SP1 + 0x14)



#endif
