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
#define BPORT1_AB_GENCS    (BPORT1 + 0x0)

#define BPORT1_AB_GENCS_EOSF   (0x1 << 15)
#define BPORT1_AB_GENCS_ERIE   (0x1 << 5)
#define BPORT1_AB_GENCS_ESOR   (0x1 << 4)
#define BPORT1_AB_GENCS_EXTERF   (0x1 << 13)
#define BPORT1_AB_GENCS_LPCLKS   (0x1 << 28)
#define BPORT1_AB_GENCS_LPSCNITV   (0xf << 24)
#define BPORT1_AB_GENCS_NSCN   (0x1f << 19)
#define BPORT1_AB_GENCS_OUTRGF   (0x1 << 14)
#define BPORT1_AB_GENCS_OVRF   (0x1 << 12)
#define BPORT1_AB_GENCS_PS   (0x7 << 16)
#define BPORT1_AB_GENCS_SCNIP   (0x1 << 9)
#define BPORT1_AB_GENCS_STM   (0x1 << 1)
#define BPORT1_AB_GENCS_STPE   0x1
#define BPORT1_AB_GENCS_SWTS   (0x1 << 8)
#define BPORT1_AB_GENCS_TSIEN   (0x1 << 7)
#define BPORT1_AB_GENCS_TSIIE   (0x1 << 6)
#define BPORT1_AB_SCANC    (BPORT1 + 0x4)

#define BPORT1_AB_SCANC_AMCLKS   (0x3 << 3)
#define BPORT1_AB_SCANC_AMPSC   0x7
#define BPORT1_AB_SCANC_EXTCHRG   (0xf << 16)
#define BPORT1_AB_SCANC_REFCHRG   (0xf << 24)
#define BPORT1_AB_SCANC_SMOD   (0xff << 8)
#define BPORT1_AB_PEN    (BPORT1 + 0x8)

#define BPORT1_AB_PEN_LPSP   (0xf << 16)
#define BPORT1_AB_PEN_PEN0   0x1
#define BPORT1_AB_PEN_PEN1   (0x1 << 1)
#define BPORT1_AB_PEN_PEN10   (0x1 << 10)
#define BPORT1_AB_PEN_PEN11   (0x1 << 11)
#define BPORT1_AB_PEN_PEN12   (0x1 << 12)
#define BPORT1_AB_PEN_PEN13   (0x1 << 13)
#define BPORT1_AB_PEN_PEN14   (0x1 << 14)
#define BPORT1_AB_PEN_PEN15   (0x1 << 15)
#define BPORT1_AB_PEN_PEN2   (0x1 << 2)
#define BPORT1_AB_PEN_PEN3   (0x1 << 3)
#define BPORT1_AB_PEN_PEN4   (0x1 << 4)
#define BPORT1_AB_PEN_PEN5   (0x1 << 5)
#define BPORT1_AB_PEN_PEN6   (0x1 << 6)
#define BPORT1_AB_PEN_PEN7   (0x1 << 7)
#define BPORT1_AB_PEN_PEN8   (0x1 << 8)
#define BPORT1_AB_PEN_PEN9   (0x1 << 9)
#define BPORT1_AB_WUCNTR    (BPORT1 + 0x10)

#define BPORT1_AB_WUCNTR_WUCNT   0xffff
#define BPORT1_AB_CNTR1    (BPORT1 + 0x100)

#define BPORT1_AB_CNTR1_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR1_CTN1   0xffff
#define BPORT1_AB_CNTR3    (BPORT1 + 0x104)

#define BPORT1_AB_CNTR3_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR3_CTN1   0xffff
#define BPORT1_AB_CNTR5    (BPORT1 + 0x108)

#define BPORT1_AB_CNTR5_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR5_CTN1   0xffff
#define BPORT1_AB_CNTR7    (BPORT1 + 0x10c)

#define BPORT1_AB_CNTR7_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR7_CTN1   0xffff
#define BPORT1_AB_CNTR9    (BPORT1 + 0x110)

#define BPORT1_AB_CNTR9_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR9_CTN1   0xffff
#define BPORT1_AB_CNTR11    (BPORT1 + 0x114)

#define BPORT1_AB_CNTR11_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR11_CTN1   0xffff
#define BPORT1_AB_CNTR13    (BPORT1 + 0x118)

#define BPORT1_AB_CNTR13_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR13_CTN1   0xffff
#define BPORT1_AB_CNTR15    (BPORT1 + 0x11c)

#define BPORT1_AB_CNTR15_CTN   (0xffff << 16)
#define BPORT1_AB_CNTR15_CTN1   0xffff
#define BPORT1_AB_THRESHOLD    (BPORT1 + 0x120)

#define BPORT1_AB_THRESHOLD_HTHH   0xffff
#define BPORT1_AB_THRESHOLD_LTHH   (0xffff << 16)


#endif
