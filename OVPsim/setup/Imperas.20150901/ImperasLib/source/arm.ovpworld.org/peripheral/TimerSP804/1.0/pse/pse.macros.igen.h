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
#define BPORT1_AB_T0LOAD    (BPORT1 + 0x0)

#define BPORT1_AB_T0VALUE    (BPORT1 + 0x4)

#define BPORT1_AB_T0CONTROL    (BPORT1 + 0x8)

#define BPORT1_AB_T0CONTROL_ONESHOT   0x1
#define BPORT1_AB_T0CONTROL_M32BIT   (0x1 << 1)
#define BPORT1_AB_T0CONTROL_DIV   (0x3 << 2)
#define BPORT1_AB_T0CONTROL_IE   (0x1 << 5)
#define BPORT1_AB_T0CONTROL_PERIODIC   (0x1 << 6)
#define BPORT1_AB_T0CONTROL_ENABLE   (0x1 << 7)
#define BPORT1_AB_T0INTCLR    (BPORT1 + 0xc)

#define BPORT1_AB_T0RIS    (BPORT1 + 0x10)

#define BPORT1_AB_T0MIS    (BPORT1 + 0x14)

#define BPORT1_AB_T0BGLOAD    (BPORT1 + 0x18)

#define BPORT1_AB_T1LOAD    (BPORT1 + 0x20)

#define BPORT1_AB_T1VALUE    (BPORT1 + 0x24)

#define BPORT1_AB_T1CONTROL    (BPORT1 + 0x28)

#define BPORT1_AB_T1CONTROL_ONESHOT   0x1
#define BPORT1_AB_T1CONTROL_M32BIT   (0x1 << 1)
#define BPORT1_AB_T1CONTROL_DIV   (0x3 << 2)
#define BPORT1_AB_T1CONTROL_IE   (0x1 << 5)
#define BPORT1_AB_T1CONTROL_PERIODIC   (0x1 << 6)
#define BPORT1_AB_T1CONTROL_ENABLE   (0x1 << 7)
#define BPORT1_AB_T1INTCLR    (BPORT1 + 0x2c)

#define BPORT1_AB_T1RIS    (BPORT1 + 0x30)

#define BPORT1_AB_T1MIS    (BPORT1 + 0x34)

#define BPORT1_AB_T1BGLOAD    (BPORT1 + 0x38)

#define BPORT1_AB_ITCR    (BPORT1 + 0xf00)

#define BPORT1_AB_ITOP    (BPORT1 + 0xf04)

#define BPORT1_AB_PERIPHID0    (BPORT1 + 0xfe0)

#define BPORT1_AB_PERIPHID1    (BPORT1 + 0xfe4)

#define BPORT1_AB_PERIPHID2    (BPORT1 + 0xfe8)

#define BPORT1_AB_PERIPHID3    (BPORT1 + 0xfec)

#define BPORT1_AB_PCELLID0    (BPORT1 + 0xff0)

#define BPORT1_AB_PCELLID1    (BPORT1 + 0xff4)

#define BPORT1_AB_PCELLID2    (BPORT1 + 0xff8)

#define BPORT1_AB_PCELLID3    (BPORT1 + 0xffc)



#endif
