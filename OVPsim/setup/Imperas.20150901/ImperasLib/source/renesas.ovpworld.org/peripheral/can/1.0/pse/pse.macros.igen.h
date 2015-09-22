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
// Set the macro 'BUSPORTGR' to the base of port 'busPortGR'
#ifndef BUSPORTGR
    #error BUSPORTGR is undefined.It needs to be set to the port base address
#endif
#define BUSPORTGR_GR1_GMCTRL    (BUSPORTGR + 0x0)

#define BUSPORTGR_GR1_GMCS    (BUSPORTGR + 0x2)

#define BUSPORTGR_GR1_GMABT    (BUSPORTGR + 0x6)

#define BUSPORTGR_GR1_GMABTD    (BUSPORTGR + 0x8)

#define BUSPORTGR_GR1_MASK1L    (BUSPORTGR + 0x40)

#define BUSPORTGR_GR1_MASK1H    (BUSPORTGR + 0x42)

#define BUSPORTGR_GR1_MASK2L    (BUSPORTGR + 0x44)

#define BUSPORTGR_GR1_MASK2H    (BUSPORTGR + 0x46)

#define BUSPORTGR_GR1_MASK3L    (BUSPORTGR + 0x48)

#define BUSPORTGR_GR1_MASK3H    (BUSPORTGR + 0x4a)

#define BUSPORTGR_GR1_MASK4L    (BUSPORTGR + 0x4c)

#define BUSPORTGR_GR1_MASK4H    (BUSPORTGR + 0x4e)

#define BUSPORTGR_GR1_CTRL    (BUSPORTGR + 0x50)

#define BUSPORTGR_GR2_LEC    (BUSPORTGR + 0x52)

#define BUSPORTGR_GR2_INFO    (BUSPORTGR + 0x53)

#define BUSPORTGR_GR3_ERC    (BUSPORTGR + 0x54)

#define BUSPORTGR_GR3_IE    (BUSPORTGR + 0x56)

#define BUSPORTGR_GR3_INTS    (BUSPORTGR + 0x58)

#define BUSPORTGR_GR3_BRP    (BUSPORTGR + 0x5a)

#define BUSPORTGR_GR3_BTR    (BUSPORTGR + 0x5c)

#define BUSPORTGR_GR3_LIPT    (BUSPORTGR + 0x5e)

#define BUSPORTGR_GR3_RGPT    (BUSPORTGR + 0x60)

#define BUSPORTGR_GR3_LOPT    (BUSPORTGR + 0x62)

#define BUSPORTGR_GR3_TGPT    (BUSPORTGR + 0x64)

#define BUSPORTGR_GR3_TS    (BUSPORTGR + 0x66)



#endif
