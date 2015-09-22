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
#define BPORT1_AB_CR0    (BPORT1 + 0x0)

#define BPORT1_AB_CR0_FILTER_CNT   (0x7 << 4)
#define BPORT1_AB_CR0_HYSTCTR   0x3
#define BPORT1_AB_CR1    (BPORT1 + 0x1)

#define BPORT1_AB_CR1_COS   (0x1 << 2)
#define BPORT1_AB_CR1_EN   0x1
#define BPORT1_AB_CR1_INV   (0x1 << 3)
#define BPORT1_AB_CR1_OPE   (0x1 << 1)
#define BPORT1_AB_CR1_PMODE   (0x1 << 4)
#define BPORT1_AB_CR1_SE   (0x1 << 7)
#define BPORT1_AB_CR1_WE   (0x1 << 6)
#define BPORT1_AB_FPR    (BPORT1 + 0x2)

#define BPORT1_AB_FPR_FILT_PER   0xff
#define BPORT1_AB_SCR    (BPORT1 + 0x3)

#define BPORT1_AB_SCR_CFF   (0x1 << 1)
#define BPORT1_AB_SCR_CFR   (0x1 << 2)
#define BPORT1_AB_SCR_COUT   0x1
#define BPORT1_AB_SCR_DMAEN   (0x1 << 6)
#define BPORT1_AB_SCR_IEF   (0x1 << 3)
#define BPORT1_AB_SCR_IER   (0x1 << 4)
#define BPORT1_AB_DACCR    (BPORT1 + 0x4)

#define BPORT1_AB_DACCR_DACEN   (0x1 << 7)
#define BPORT1_AB_DACCR_VOSEL   0x3f
#define BPORT1_AB_DACCR_VRSEL   (0x1 << 6)
#define BPORT1_AB_MUXCR    (BPORT1 + 0x5)

#define BPORT1_AB_MUXCR_MSEL   0x7
#define BPORT1_AB_MUXCR_PSEL   (0x7 << 3)


#endif
