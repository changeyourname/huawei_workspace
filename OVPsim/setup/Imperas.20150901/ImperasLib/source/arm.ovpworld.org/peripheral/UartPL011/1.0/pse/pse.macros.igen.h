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
#define BPORT1_AB_DR    (BPORT1 + 0x0)

#define BPORT1_AB_ECR    (BPORT1 + 0x4)

#define BPORT1_AB_FLAGS    (BPORT1 + 0x18)

#define BPORT1_AB_FLAGS_TXFE   (0x1 << 7)
#define BPORT1_AB_FLAGS_RXFF   (0x1 << 6)
#define BPORT1_AB_FLAGS_TXFF   (0x1 << 5)
#define BPORT1_AB_FLAGS_RXFE   (0x1 << 4)
#define BPORT1_AB_ILPR    (BPORT1 + 0x20)

#define BPORT1_AB_IBRD    (BPORT1 + 0x24)

#define BPORT1_AB_VBRD    (BPORT1 + 0x28)

#define BPORT1_AB_LCR    (BPORT1 + 0x2c)

#define BPORT1_AB_LCR_FEN   (0x1 << 4)
#define BPORT1_AB_CR    (BPORT1 + 0x30)

#define BPORT1_AB_IFL    (BPORT1 + 0x34)

#define BPORT1_AB_INT_ENABLED    (BPORT1 + 0x38)

#define BPORT1_AB_INT_LEVEL    (BPORT1 + 0x3c)

#define BPORT1_AB_INT_LEVEL_TX   (0x1 << 5)
#define BPORT1_AB_INT_LEVEL_RX   (0x1 << 4)
#define BPORT1_AB_MIS    (BPORT1 + 0x40)

#define BPORT1_AB_ICR    (BPORT1 + 0x44)

#define BPORT1_AB_DMACR    (BPORT1 + 0x48)

#define BPORT1_AB_ID0    (BPORT1 + 0xfe0)

#define BPORT1_AB_ID1    (BPORT1 + 0xfe4)

#define BPORT1_AB_ID2    (BPORT1 + 0xfe8)

#define BPORT1_AB_ID3    (BPORT1 + 0xfec)

#define BPORT1_AB_ID4    (BPORT1 + 0xff0)

#define BPORT1_AB_ID5    (BPORT1 + 0xff4)

#define BPORT1_AB_ID6    (BPORT1 + 0xff8)

#define BPORT1_AB_ID7    (BPORT1 + 0xffc)



#endif
