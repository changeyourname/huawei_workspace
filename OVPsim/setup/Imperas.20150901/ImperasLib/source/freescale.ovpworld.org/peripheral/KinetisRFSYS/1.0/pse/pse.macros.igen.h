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
#define BPORT1_AB_REGA    (BPORT1 + 0x0)

#define BPORT1_AB_REGA_HH   (0xff << 24)
#define BPORT1_AB_REGA_HL   (0xff << 16)
#define BPORT1_AB_REGA_LH   (0xff << 8)
#define BPORT1_AB_REGA_LL   0xff
#define BPORT1_AB_REGB    (BPORT1 + 0x4)

#define BPORT1_AB_REGB_HH   (0xff << 24)
#define BPORT1_AB_REGB_HL   (0xff << 16)
#define BPORT1_AB_REGB_LH   (0xff << 8)
#define BPORT1_AB_REGB_LL   0xff
#define BPORT1_AB_REGC    (BPORT1 + 0x8)

#define BPORT1_AB_REGC_HH   (0xff << 24)
#define BPORT1_AB_REGC_HL   (0xff << 16)
#define BPORT1_AB_REGC_LH   (0xff << 8)
#define BPORT1_AB_REGC_LL   0xff
#define BPORT1_AB_REGD    (BPORT1 + 0xc)

#define BPORT1_AB_REGD_HH   (0xff << 24)
#define BPORT1_AB_REGD_HL   (0xff << 16)
#define BPORT1_AB_REGD_LH   (0xff << 8)
#define BPORT1_AB_REGD_LL   0xff
#define BPORT1_AB_REGE    (BPORT1 + 0x10)

#define BPORT1_AB_REGE_HH   (0xff << 24)
#define BPORT1_AB_REGE_HL   (0xff << 16)
#define BPORT1_AB_REGE_LH   (0xff << 8)
#define BPORT1_AB_REGE_LL   0xff
#define BPORT1_AB_REGF    (BPORT1 + 0x14)

#define BPORT1_AB_REGF_HH   (0xff << 24)
#define BPORT1_AB_REGF_HL   (0xff << 16)
#define BPORT1_AB_REGF_LH   (0xff << 8)
#define BPORT1_AB_REGF_LL   0xff
#define BPORT1_AB_REGG    (BPORT1 + 0x18)

#define BPORT1_AB_REGG_HH   (0xff << 24)
#define BPORT1_AB_REGG_HL   (0xff << 16)
#define BPORT1_AB_REGG_LH   (0xff << 8)
#define BPORT1_AB_REGG_LL   0xff
#define BPORT1_AB_REGH    (BPORT1 + 0x1c)

#define BPORT1_AB_REGH_HH   (0xff << 24)
#define BPORT1_AB_REGH_HL   (0xff << 16)
#define BPORT1_AB_REGH_LH   (0xff << 8)
#define BPORT1_AB_REGH_LL   0xff


#endif
