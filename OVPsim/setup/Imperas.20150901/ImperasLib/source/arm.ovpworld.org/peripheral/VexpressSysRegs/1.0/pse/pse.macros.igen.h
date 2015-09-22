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
#define BPORT1_AB_ID    (BPORT1 + 0x0)

#define BPORT1_AB_SW    (BPORT1 + 0x4)

#define BPORT1_AB_LED    (BPORT1 + 0x8)

#define BPORT1_AB_CNT100HZ    (BPORT1 + 0x24)

#define BPORT1_AB_FLAGSSET    (BPORT1 + 0x30)

#define BPORT1_AB_FLAGSCLR    (BPORT1 + 0x34)

#define BPORT1_AB_NVFLAGSSET    (BPORT1 + 0x38)

#define BPORT1_AB_NVFLAGSCLR    (BPORT1 + 0x3c)

#define BPORT1_AB_MCI    (BPORT1 + 0x48)

#define BPORT1_AB_FLASH    (BPORT1 + 0x4c)

#define BPORT1_AB_CFGSW    (BPORT1 + 0x58)

#define BPORT1_AB_CNT24MHZ    (BPORT1 + 0x5c)

#define BPORT1_AB_MISC    (BPORT1 + 0x60)

#define BPORT1_AB_DMA    (BPORT1 + 0x64)

#define BPORT1_AB_PROCID0    (BPORT1 + 0x84)

#define BPORT1_AB_PROCID1    (BPORT1 + 0x88)

#define BPORT1_AB_CFGDATA    (BPORT1 + 0xa0)

#define BPORT1_AB_CFGCTRL    (BPORT1 + 0xa4)

#define BPORT1_AB_CFGSTAT    (BPORT1 + 0xa8)



#endif
