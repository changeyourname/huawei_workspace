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
#define BPORT1_AB_BDH    (BPORT1 + 0x0)

#define BPORT1_AB_BDH_SBR   0x1f
#define BPORT1_AB_BDL    (BPORT1 + 0x1)

#define BPORT1_AB_C1    (BPORT1 + 0x2)

#define BPORT1_AB_C2    (BPORT1 + 0x3)

#define BPORT1_AB_C2_TIE   (0x1 << 7)
#define BPORT1_AB_C2_TCIE   (0x1 << 6)
#define BPORT1_AB_C2_RIE   (0x1 << 5)
#define BPORT1_AB_C2_ILIE   (0x1 << 4)
#define BPORT1_AB_C2_TE   (0x1 << 3)
#define BPORT1_AB_C2_RE   (0x1 << 2)
#define BPORT1_AB_S1    (BPORT1 + 0x4)

#define BPORT1_AB_S1_TDRE   (0x1 << 7)
#define BPORT1_AB_S1_TC   (0x1 << 6)
#define BPORT1_AB_S1_RDRF   (0x1 << 5)
#define BPORT1_AB_S1_IDLE   (0x1 << 4)
#define BPORT1_AB_S2    (BPORT1 + 0x5)

#define BPORT1_AB_C3    (BPORT1 + 0x6)

#define BPORT1_AB_D    (BPORT1 + 0x7)

#define BPORT1_AB_MA1    (BPORT1 + 0x8)

#define BPORT1_AB_MA2    (BPORT1 + 0x9)

#define BPORT1_AB_C4    (BPORT1 + 0xa)

#define BPORT1_AB_C4_BRFA   0x1f
#define BPORT1_AB_C5    (BPORT1 + 0xb)

#define BPORT1_AB_ED    (BPORT1 + 0xc)

#define BPORT1_AB_MODEM    (BPORT1 + 0xd)

#define BPORT1_AB_INFRARED    (BPORT1 + 0xe)

#define BPORT1_AB_PFIFO    (BPORT1 + 0x10)

#define BPORT1_AB_PFIFO_TXFE   (0x1 << 7)
#define BPORT1_AB_PFIFO_TXFIFOSIZE   (0x7 << 4)
#define BPORT1_AB_PFIFO_RXFE   (0x1 << 3)
#define BPORT1_AB_PFIFO_RXFIFOSIZE   0x7
#define BPORT1_AB_CFIFO    (BPORT1 + 0x11)

#define BPORT1_AB_CFIFO_TXFLUSH   (0x1 << 7)
#define BPORT1_AB_CFIFO_RXFLUSH   (0x1 << 6)
#define BPORT1_AB_SFIFO    (BPORT1 + 0x12)

#define BPORT1_AB_TWFIFO    (BPORT1 + 0x13)

#define BPORT1_AB_TCFIFO    (BPORT1 + 0x14)

#define BPORT1_AB_RWFIFO    (BPORT1 + 0x15)

#define BPORT1_AB_RCFIFO    (BPORT1 + 0x16)



#endif
