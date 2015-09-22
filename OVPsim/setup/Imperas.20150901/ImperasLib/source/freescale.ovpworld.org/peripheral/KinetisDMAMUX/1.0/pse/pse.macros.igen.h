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
#define BPORT1_AB_CHCFG0    (BPORT1 + 0x0)

#define BPORT1_AB_CHCFG0_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG0_SOURCE   0x3f
#define BPORT1_AB_CHCFG0_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG1    (BPORT1 + 0x1)

#define BPORT1_AB_CHCFG1_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG1_SOURCE   0x3f
#define BPORT1_AB_CHCFG1_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG2    (BPORT1 + 0x2)

#define BPORT1_AB_CHCFG2_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG2_SOURCE   0x3f
#define BPORT1_AB_CHCFG2_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG3    (BPORT1 + 0x3)

#define BPORT1_AB_CHCFG3_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG3_SOURCE   0x3f
#define BPORT1_AB_CHCFG3_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG4    (BPORT1 + 0x4)

#define BPORT1_AB_CHCFG4_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG4_SOURCE   0x3f
#define BPORT1_AB_CHCFG4_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG5    (BPORT1 + 0x5)

#define BPORT1_AB_CHCFG5_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG5_SOURCE   0x3f
#define BPORT1_AB_CHCFG5_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG6    (BPORT1 + 0x6)

#define BPORT1_AB_CHCFG6_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG6_SOURCE   0x3f
#define BPORT1_AB_CHCFG6_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG7    (BPORT1 + 0x7)

#define BPORT1_AB_CHCFG7_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG7_SOURCE   0x3f
#define BPORT1_AB_CHCFG7_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG8    (BPORT1 + 0x8)

#define BPORT1_AB_CHCFG8_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG8_SOURCE   0x3f
#define BPORT1_AB_CHCFG8_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG9    (BPORT1 + 0x9)

#define BPORT1_AB_CHCFG9_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG9_SOURCE   0x3f
#define BPORT1_AB_CHCFG9_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG10    (BPORT1 + 0xa)

#define BPORT1_AB_CHCFG10_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG10_SOURCE   0x3f
#define BPORT1_AB_CHCFG10_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG11    (BPORT1 + 0xb)

#define BPORT1_AB_CHCFG11_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG11_SOURCE   0x3f
#define BPORT1_AB_CHCFG11_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG12    (BPORT1 + 0xc)

#define BPORT1_AB_CHCFG12_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG12_SOURCE   0x3f
#define BPORT1_AB_CHCFG12_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG13    (BPORT1 + 0xd)

#define BPORT1_AB_CHCFG13_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG13_SOURCE   0x3f
#define BPORT1_AB_CHCFG13_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG14    (BPORT1 + 0xe)

#define BPORT1_AB_CHCFG14_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG14_SOURCE   0x3f
#define BPORT1_AB_CHCFG14_TRIG   (0x1 << 6)
#define BPORT1_AB_CHCFG15    (BPORT1 + 0xf)

#define BPORT1_AB_CHCFG15_ENBL   (0x1 << 7)
#define BPORT1_AB_CHCFG15_SOURCE   0x3f
#define BPORT1_AB_CHCFG15_TRIG   (0x1 << 6)


#endif
