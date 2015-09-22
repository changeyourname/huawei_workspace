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
#define BPORT1_AB_IBAD    (BPORT1 + 0x0)

#define BPORT1_AB_IBAD_ADR   (0x7f << 1)
#define BPORT1_AB_IBFD    (BPORT1 + 0x1)

#define BPORT1_AB_IBFD_IBC   0xff
#define BPORT1_AB_IBCR    (BPORT1 + 0x2)

#define BPORT1_AB_IBCR_DMAEN   (0x1 << 1)
#define BPORT1_AB_IBCR_IBIE   (0x1 << 6)
#define BPORT1_AB_IBCR_MDIS   (0x1 << 7)
#define BPORT1_AB_IBCR_MSSL   (0x1 << 5)
#define BPORT1_AB_IBCR_NOACK   (0x1 << 3)
#define BPORT1_AB_IBCR_RSTA   (0x1 << 2)
#define BPORT1_AB_IBCR_TXRX   (0x1 << 4)
#define BPORT1_AB_IBSR    (BPORT1 + 0x3)

#define BPORT1_AB_IBSR_IAAS   (0x1 << 6)
#define BPORT1_AB_IBSR_IBAL   (0x1 << 4)
#define BPORT1_AB_IBSR_IBB   (0x1 << 5)
#define BPORT1_AB_IBSR_IBIF   (0x1 << 1)
#define BPORT1_AB_IBSR_RXAK   0x1
#define BPORT1_AB_IBSR_SRW   (0x1 << 2)
#define BPORT1_AB_IBSR_TCF   (0x1 << 7)
#define BPORT1_AB_IBDR    (BPORT1 + 0x4)

#define BPORT1_AB_IBDR_DATA   0xff
#define BPORT1_AB_IBIC    (BPORT1 + 0x5)

#define BPORT1_AB_IBIC_BIIE   (0x1 << 7)
#define BPORT1_AB_IBDBG    (BPORT1 + 0x6)

#define BPORT1_AB_IBDBG_IPG_DEBUG_EN   0x1
#define BPORT1_AB_IBDBG_IPG_DEBUG_HALTED   (0x1 << 1)


#endif
