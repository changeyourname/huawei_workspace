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
#define BPORT1_AB_PRS0    (BPORT1 + 0x0)

#define BPORT1_AB_PRS0_M0   0x7
#define BPORT1_AB_PRS0_M1   (0x7 << 4)
#define BPORT1_AB_PRS0_M2   (0x7 << 8)
#define BPORT1_AB_PRS0_M3   (0x7 << 12)
#define BPORT1_AB_PRS0_M4   (0x7 << 16)
#define BPORT1_AB_PRS0_M5   (0x7 << 20)
#define BPORT1_AB_PRS0_M6   (0x7 << 24)
#define BPORT1_AB_PRS0_M7   (0x7 << 28)
#define BPORT1_AB_CRS0    (BPORT1 + 0x10)

#define BPORT1_AB_CRS0_ARB   (0x3 << 8)
#define BPORT1_AB_CRS0_HLP   (0x1 << 30)
#define BPORT1_AB_CRS0_PARK   0x7
#define BPORT1_AB_CRS0_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS0_RO   (0x1 << 31)
#define BPORT1_AB_PRS1    (BPORT1 + 0x100)

#define BPORT1_AB_PRS1_M0   0x7
#define BPORT1_AB_PRS1_M1   (0x7 << 4)
#define BPORT1_AB_PRS1_M2   (0x7 << 8)
#define BPORT1_AB_PRS1_M3   (0x7 << 12)
#define BPORT1_AB_PRS1_M4   (0x7 << 16)
#define BPORT1_AB_PRS1_M5   (0x7 << 20)
#define BPORT1_AB_PRS1_M6   (0x7 << 24)
#define BPORT1_AB_PRS1_M7   (0x7 << 28)
#define BPORT1_AB_CRS1    (BPORT1 + 0x110)

#define BPORT1_AB_CRS1_ARB   (0x3 << 8)
#define BPORT1_AB_CRS1_HLP   (0x1 << 30)
#define BPORT1_AB_CRS1_PARK   0x7
#define BPORT1_AB_CRS1_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS1_RO   (0x1 << 31)
#define BPORT1_AB_PRS2    (BPORT1 + 0x200)

#define BPORT1_AB_PRS2_M0   0x7
#define BPORT1_AB_PRS2_M1   (0x7 << 4)
#define BPORT1_AB_PRS2_M2   (0x7 << 8)
#define BPORT1_AB_PRS2_M3   (0x7 << 12)
#define BPORT1_AB_PRS2_M4   (0x7 << 16)
#define BPORT1_AB_PRS2_M5   (0x7 << 20)
#define BPORT1_AB_PRS2_M6   (0x7 << 24)
#define BPORT1_AB_PRS2_M7   (0x7 << 28)
#define BPORT1_AB_CRS2    (BPORT1 + 0x210)

#define BPORT1_AB_CRS2_ARB   (0x3 << 8)
#define BPORT1_AB_CRS2_HLP   (0x1 << 30)
#define BPORT1_AB_CRS2_PARK   0x7
#define BPORT1_AB_CRS2_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS2_RO   (0x1 << 31)
#define BPORT1_AB_PRS3    (BPORT1 + 0x300)

#define BPORT1_AB_PRS3_M0   0x7
#define BPORT1_AB_PRS3_M1   (0x7 << 4)
#define BPORT1_AB_PRS3_M2   (0x7 << 8)
#define BPORT1_AB_PRS3_M3   (0x7 << 12)
#define BPORT1_AB_PRS3_M4   (0x7 << 16)
#define BPORT1_AB_PRS3_M5   (0x7 << 20)
#define BPORT1_AB_PRS3_M6   (0x7 << 24)
#define BPORT1_AB_PRS3_M7   (0x7 << 28)
#define BPORT1_AB_CRS3    (BPORT1 + 0x310)

#define BPORT1_AB_CRS3_ARB   (0x3 << 8)
#define BPORT1_AB_CRS3_HLP   (0x1 << 30)
#define BPORT1_AB_CRS3_PARK   0x7
#define BPORT1_AB_CRS3_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS3_RO   (0x1 << 31)
#define BPORT1_AB_PRS4    (BPORT1 + 0x400)

#define BPORT1_AB_PRS4_M0   0x7
#define BPORT1_AB_PRS4_M1   (0x7 << 4)
#define BPORT1_AB_PRS4_M2   (0x7 << 8)
#define BPORT1_AB_PRS4_M3   (0x7 << 12)
#define BPORT1_AB_PRS4_M4   (0x7 << 16)
#define BPORT1_AB_PRS4_M5   (0x7 << 20)
#define BPORT1_AB_PRS4_M6   (0x7 << 24)
#define BPORT1_AB_PRS4_M7   (0x7 << 28)
#define BPORT1_AB_CRS4    (BPORT1 + 0x410)

#define BPORT1_AB_CRS4_ARB   (0x3 << 8)
#define BPORT1_AB_CRS4_HLP   (0x1 << 30)
#define BPORT1_AB_CRS4_PARK   0x7
#define BPORT1_AB_CRS4_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS4_RO   (0x1 << 31)
#define BPORT1_AB_PRS5    (BPORT1 + 0x500)

#define BPORT1_AB_PRS5_M0   0x7
#define BPORT1_AB_PRS5_M1   (0x7 << 4)
#define BPORT1_AB_PRS5_M2   (0x7 << 8)
#define BPORT1_AB_PRS5_M3   (0x7 << 12)
#define BPORT1_AB_PRS5_M4   (0x7 << 16)
#define BPORT1_AB_PRS5_M5   (0x7 << 20)
#define BPORT1_AB_PRS5_M6   (0x7 << 24)
#define BPORT1_AB_PRS5_M7   (0x7 << 28)
#define BPORT1_AB_CRS5    (BPORT1 + 0x510)

#define BPORT1_AB_CRS5_ARB   (0x3 << 8)
#define BPORT1_AB_CRS5_HLP   (0x1 << 30)
#define BPORT1_AB_CRS5_PARK   0x7
#define BPORT1_AB_CRS5_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS5_RO   (0x1 << 31)
#define BPORT1_AB_PRS6    (BPORT1 + 0x600)

#define BPORT1_AB_PRS6_M0   0x7
#define BPORT1_AB_PRS6_M1   (0x7 << 4)
#define BPORT1_AB_PRS6_M2   (0x7 << 8)
#define BPORT1_AB_PRS6_M3   (0x7 << 12)
#define BPORT1_AB_PRS6_M4   (0x7 << 16)
#define BPORT1_AB_PRS6_M5   (0x7 << 20)
#define BPORT1_AB_PRS6_M6   (0x7 << 24)
#define BPORT1_AB_PRS6_M7   (0x7 << 28)
#define BPORT1_AB_CRS6    (BPORT1 + 0x610)

#define BPORT1_AB_CRS6_ARB   (0x3 << 8)
#define BPORT1_AB_CRS6_HLP   (0x1 << 30)
#define BPORT1_AB_CRS6_PARK   0x7
#define BPORT1_AB_CRS6_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS6_RO   (0x1 << 31)
#define BPORT1_AB_PRS7    (BPORT1 + 0x700)

#define BPORT1_AB_PRS7_M0   0x7
#define BPORT1_AB_PRS7_M1   (0x7 << 4)
#define BPORT1_AB_PRS7_M2   (0x7 << 8)
#define BPORT1_AB_PRS7_M3   (0x7 << 12)
#define BPORT1_AB_PRS7_M4   (0x7 << 16)
#define BPORT1_AB_PRS7_M5   (0x7 << 20)
#define BPORT1_AB_PRS7_M6   (0x7 << 24)
#define BPORT1_AB_PRS7_M7   (0x7 << 28)
#define BPORT1_AB_CRS7    (BPORT1 + 0x710)

#define BPORT1_AB_CRS7_ARB   (0x3 << 8)
#define BPORT1_AB_CRS7_HLP   (0x1 << 30)
#define BPORT1_AB_CRS7_PARK   0x7
#define BPORT1_AB_CRS7_PCTL   (0x3 << 4)
#define BPORT1_AB_CRS7_RO   (0x1 << 31)
#define BPORT1_AB_MGPCR0    (BPORT1 + 0x800)

#define BPORT1_AB_MGPCR0_AULB   0x7
#define BPORT1_AB_MGPCR1    (BPORT1 + 0x900)

#define BPORT1_AB_MGPCR1_AULB   0x7
#define BPORT1_AB_MGPCR2    (BPORT1 + 0xa00)

#define BPORT1_AB_MGPCR2_AULB   0x7
#define BPORT1_AB_MGPCR3    (BPORT1 + 0xb00)

#define BPORT1_AB_MGPCR3_AULB   0x7
#define BPORT1_AB_MGPCR6    (BPORT1 + 0xe00)

#define BPORT1_AB_MGPCR6_AULB   0x7
#define BPORT1_AB_MGPCR7    (BPORT1 + 0xf00)

#define BPORT1_AB_MGPCR7_AULB   0x7


#endif
