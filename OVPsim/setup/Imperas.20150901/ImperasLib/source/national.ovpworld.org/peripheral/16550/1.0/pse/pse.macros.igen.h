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
#define BPORT1_AB_RBR_DLL    (BPORT1 + 0x0)

#define BPORT1_AB_THR_DLL    (BPORT1 + 0x0)

#define BPORT1_AB_IER_DLH    (BPORT1 + 0x1)

#define BPORT1_AB_IER_DLH_ERBFI   0x1
#define BPORT1_AB_IER_DLH_ETBEI   (0x1 << 1)
#define BPORT1_AB_IER_DLH_ELSI   (0x1 << 2)
#define BPORT1_AB_IER_DLH_EDSSI   (0x1 << 3)
#define BPORT1_AB_IIR    (BPORT1 + 0x2)

#define BPORT1_AB_IIR_INTID   0xf
#define BPORT1_AB_IIR_FIFOEN   (0x3 << 6)
#define BPORT1_AB_FCR    (BPORT1 + 0x2)

#define BPORT1_AB_FCR_FIFOEN   0x1
#define BPORT1_AB_FCR_FIFORCVRRST   (0x1 << 1)
#define BPORT1_AB_FCR_FIFOXMITRST   (0x1 << 2)
#define BPORT1_AB_FCR_DMAMODESEL   (0x1 << 3)
#define BPORT1_AB_FCR_FIFOXMITTRIG   (0x3 << 4)
#define BPORT1_AB_FCR_FIFORCVRTRIG   (0x3 << 6)
#define BPORT1_AB_LCR    (BPORT1 + 0x3)

#define BPORT1_AB_LCR_DLS   0x3
#define BPORT1_AB_LCR_STOP   (0x1 << 2)
#define BPORT1_AB_LCR_PEN   (0x1 << 3)
#define BPORT1_AB_LCR_EPS   (0x1 << 4)
#define BPORT1_AB_LCR_STICK   (0x1 << 5)
#define BPORT1_AB_LCR_BRK   (0x1 << 6)
#define BPORT1_AB_LCR_DLAB   (0x1 << 7)
#define BPORT1_AB_MCR    (BPORT1 + 0x4)

#define BPORT1_AB_LSR    (BPORT1 + 0x5)

#define BPORT1_AB_LSR_DR   0x1
#define BPORT1_AB_LSR_OE   (0x1 << 1)
#define BPORT1_AB_LSR_PE   (0x1 << 2)
#define BPORT1_AB_LSR_FE   (0x1 << 3)
#define BPORT1_AB_LSR_BI   (0x1 << 4)
#define BPORT1_AB_LSR_THRE   (0x1 << 5)
#define BPORT1_AB_LSR_TEMT   (0x1 << 6)
#define BPORT1_AB_LSR_RFE   (0x1 << 7)
#define BPORT1_AB_MSR    (BPORT1 + 0x6)

#define BPORT1_AB_SCR    (BPORT1 + 0x7)



#endif
