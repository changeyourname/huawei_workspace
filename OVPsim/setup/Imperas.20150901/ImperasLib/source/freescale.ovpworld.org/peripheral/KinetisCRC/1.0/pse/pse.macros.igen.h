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
#define BPORT1_AB_CRC    (BPORT1 + 0x0)

#define BPORT1_AB_CRC_LL   0xff
#define BPORT1_AB_CRC_LU   (0xff << 8)
#define BPORT1_AB_CRC_HL   (0xff << 16)
#define BPORT1_AB_CRC_HU   (0xff << 24)
#define BPORT1_AB_GPOLY    (BPORT1 + 0x4)

#define BPORT1_AB_GPOLY_LOW   0xffff
#define BPORT1_AB_GPOLY_HIGH   (0xffff << 16)
#define BPORT1_AB_CTRL    (BPORT1 + 0x8)

#define BPORT1_AB_CTRL_TCRC   (0x1 << 24)
#define BPORT1_AB_CTRL_WAS   (0x1 << 25)
#define BPORT1_AB_CTRL_FXOR   (0x1 << 26)
#define BPORT1_AB_CTRL_TOTR   (0x3 << 28)
#define BPORT1_AB_CTRL_TOT   (0x3 << 30)


#endif
