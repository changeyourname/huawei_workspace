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
#define BPORT1_AB_MCR    (BPORT1 + 0x0)

#define BPORT1_AB_MCR_FRZ   0x1
#define BPORT1_AB_MCR_MDIS   (0x1 << 1)
#define BPORT1_AB_LDVAL0    (BPORT1 + 0x100)

#define BPORT1_AB_LDVAL0_TSV   0xffffffff
#define BPORT1_AB_CVAL0    (BPORT1 + 0x104)

#define BPORT1_AB_CVAL0_TVL   0xffffffff
#define BPORT1_AB_TCTRL0    (BPORT1 + 0x108)

#define BPORT1_AB_TCTRL0_TEN   0x1
#define BPORT1_AB_TCTRL0_TIE   (0x1 << 1)
#define BPORT1_AB_TFLG0    (BPORT1 + 0x10c)

#define BPORT1_AB_TFLG0_TIF   0x1
#define BPORT1_AB_LDVAL1    (BPORT1 + 0x110)

#define BPORT1_AB_LDVAL1_TSV   0xffffffff
#define BPORT1_AB_CVAL1    (BPORT1 + 0x114)

#define BPORT1_AB_CVAL1_TVL   0xffffffff
#define BPORT1_AB_TCTRL1    (BPORT1 + 0x118)

#define BPORT1_AB_TCTRL1_TEN   0x1
#define BPORT1_AB_TCTRL1_TIE   (0x1 << 1)
#define BPORT1_AB_TFLG1    (BPORT1 + 0x11c)

#define BPORT1_AB_TFLG1_TIF   0x1
#define BPORT1_AB_LDVAL2    (BPORT1 + 0x120)

#define BPORT1_AB_LDVAL2_TSV   0xffffffff
#define BPORT1_AB_CVAL2    (BPORT1 + 0x124)

#define BPORT1_AB_CVAL2_TVL   0xffffffff
#define BPORT1_AB_TCTRL2    (BPORT1 + 0x128)

#define BPORT1_AB_TCTRL2_TEN   0x1
#define BPORT1_AB_TCTRL2_TIE   (0x1 << 1)
#define BPORT1_AB_TFLG2    (BPORT1 + 0x12c)

#define BPORT1_AB_TFLG2_TIF   0x1
#define BPORT1_AB_LDVAL3    (BPORT1 + 0x130)

#define BPORT1_AB_LDVAL3_TSV   0xffffffff
#define BPORT1_AB_CVAL3    (BPORT1 + 0x134)

#define BPORT1_AB_CVAL3_TVL   0xffffffff
#define BPORT1_AB_TCTRL3    (BPORT1 + 0x138)

#define BPORT1_AB_TCTRL3_TEN   0x1
#define BPORT1_AB_TCTRL3_TIE   (0x1 << 1)
#define BPORT1_AB_TFLG3    (BPORT1 + 0x13c)

#define BPORT1_AB_TFLG3_TIF   0x1


#endif
