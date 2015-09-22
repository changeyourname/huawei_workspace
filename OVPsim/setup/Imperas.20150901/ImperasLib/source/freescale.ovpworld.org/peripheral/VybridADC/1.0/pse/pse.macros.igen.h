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
#define BPORT1_AB_HC0    (BPORT1 + 0x0)

#define BPORT1_AB_HC0_ADCH   0x1f
#define BPORT1_AB_HC0_AIEN   (0x1 << 7)
#define BPORT1_AB_HC1    (BPORT1 + 0x4)

#define BPORT1_AB_HC1_ADCH   0x1f
#define BPORT1_AB_HC1_AIEN   (0x1 << 7)
#define BPORT1_AB_HS    (BPORT1 + 0x8)

#define BPORT1_AB_HS_COCO1   0x1
#define BPORT1_AB_HS_COCO2   (0x1 << 1)
#define BPORT1_AB_R0    (BPORT1 + 0xc)

#define BPORT1_AB_R0_D   0xfff
#define BPORT1_AB_R1    (BPORT1 + 0x10)

#define BPORT1_AB_R1_D   0xfff
#define BPORT1_AB_CFG    (BPORT1 + 0x14)

#define BPORT1_AB_CFG_ADHSC   (0x1 << 10)
#define BPORT1_AB_CFG_ADICLK   0x3
#define BPORT1_AB_CFG_ADIV   (0x3 << 5)
#define BPORT1_AB_CFG_ADLPC   (0x1 << 7)
#define BPORT1_AB_CFG_ADLSMP   (0x1 << 4)
#define BPORT1_AB_CFG_ADSTS   (0x3 << 8)
#define BPORT1_AB_CFG_ADTRG   (0x1 << 13)
#define BPORT1_AB_CFG_AVGS   (0x3 << 14)
#define BPORT1_AB_CFG_MODE   (0x3 << 2)
#define BPORT1_AB_CFG_OVWREN   (0x1 << 16)
#define BPORT1_AB_CFG_REFSEL   (0x3 << 11)
#define BPORT1_AB_GC    (BPORT1 + 0x18)

#define BPORT1_AB_GC_ACFE   (0x1 << 4)
#define BPORT1_AB_GC_ACFGT   (0x1 << 3)
#define BPORT1_AB_GC_ACREN   (0x1 << 2)
#define BPORT1_AB_GC_ADACKEN   0x1
#define BPORT1_AB_GC_ADCO   (0x1 << 6)
#define BPORT1_AB_GC_AVGE   (0x1 << 5)
#define BPORT1_AB_GC_CAL   (0x1 << 7)
#define BPORT1_AB_GC_DMAEN   (0x1 << 1)
#define BPORT1_AB_GS    (BPORT1 + 0x1c)

#define BPORT1_AB_GS_ADACT   0x1
#define BPORT1_AB_GS_AWKST   (0x1 << 2)
#define BPORT1_AB_GS_CALF   (0x1 << 1)
#define BPORT1_AB_CV    (BPORT1 + 0x20)

#define BPORT1_AB_CV_CV1   0xfff
#define BPORT1_AB_CV_CV2   (0xfff << 16)
#define BPORT1_AB_OFS    (BPORT1 + 0x24)

#define BPORT1_AB_OFS_OFS   0xfff
#define BPORT1_AB_OFS_SIGN   (0x1 << 12)
#define BPORT1_AB_CAL    (BPORT1 + 0x28)

#define BPORT1_AB_CAL_CAL_CODE   0xf
#define BPORT1_AB_PCTL    (BPORT1 + 0x30)

#define BPORT1_AB_PCTL_ADPC0   0x1
#define BPORT1_AB_PCTL_ADPC1   (0x1 << 1)
#define BPORT1_AB_PCTL_ADPC10   (0x1 << 10)
#define BPORT1_AB_PCTL_ADPC11   (0x1 << 11)
#define BPORT1_AB_PCTL_ADPC12   (0x1 << 12)
#define BPORT1_AB_PCTL_ADPC13   (0x1 << 13)
#define BPORT1_AB_PCTL_ADPC14   (0x1 << 14)
#define BPORT1_AB_PCTL_ADPC15   (0x1 << 15)
#define BPORT1_AB_PCTL_ADPC16   (0x1 << 16)
#define BPORT1_AB_PCTL_ADPC17   (0x1 << 17)
#define BPORT1_AB_PCTL_ADPC18   (0x1 << 18)
#define BPORT1_AB_PCTL_ADPC19   (0x1 << 19)
#define BPORT1_AB_PCTL_ADPC2   (0x1 << 2)
#define BPORT1_AB_PCTL_ADPC20   (0x1 << 20)
#define BPORT1_AB_PCTL_ADPC21   (0x1 << 21)
#define BPORT1_AB_PCTL_ADPC22   (0x1 << 22)
#define BPORT1_AB_PCTL_ADPC23   (0x1 << 23)
#define BPORT1_AB_PCTL_ADPC3   (0x1 << 3)
#define BPORT1_AB_PCTL_ADPC4   (0x1 << 4)
#define BPORT1_AB_PCTL_ADPC5   (0x1 << 5)
#define BPORT1_AB_PCTL_ADPC6   (0x1 << 6)
#define BPORT1_AB_PCTL_ADPC7   (0x1 << 7)
#define BPORT1_AB_PCTL_ADPC8   (0x1 << 8)
#define BPORT1_AB_PCTL_ADPC9   (0x1 << 9)


#endif
