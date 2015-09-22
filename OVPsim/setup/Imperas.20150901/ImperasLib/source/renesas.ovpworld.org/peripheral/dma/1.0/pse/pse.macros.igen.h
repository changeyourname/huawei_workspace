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
// Set the macro 'DMAP0' to the base of port 'DMAP0'
#ifndef DMAP0
    #error DMAP0 is undefined.It needs to be set to the port base address
#endif
#define DMAP0_ABC_DMAWC0    (DMAP0 + 0x0)

#define DMAP0_ABC_DMAWC1    (DMAP0 + 0x2)


// Set the macro 'DMAP1' to the base of port 'DMAP1'
#ifndef DMAP1
    #error DMAP1 is undefined.It needs to be set to the port base address
#endif
#define DMAP1_ABW_MAR0    (DMAP1 + 0x0)

#define DMAP1_ABW_MAR1    (DMAP1 + 0x2)

#define DMAP1_ABW_MAR2    (DMAP1 + 0x4)

#define DMAP1_ABW_MAR3    (DMAP1 + 0x6)

#define DMAP1_ABW_MAR4    (DMAP1 + 0x8)

#define DMAP1_ABW_MAR5    (DMAP1 + 0xa)

#define DMAP1_ABW_MAR6    (DMAP1 + 0xc)

#define DMAP1_ABW_MAR7    (DMAP1 + 0xe)

#define DMAP1_ABW_MAR8    (DMAP1 + 0x10)

#define DMAP1_ABW_MAR9    (DMAP1 + 0x12)

#define DMAP1_ABB_SAR2    (DMAP1 + 0x24)

#define DMAP1_ABB_SAR2_SAR   0xf
#define DMAP1_ABB_SAR3    (DMAP1 + 0x26)

#define DMAP1_ABB_SAR3_SAR   0xf
#define DMAP1_ABB_DTFR4    (DMAP1 + 0x88)

#define DMAP1_ABB_DTFR4_IFCN   0x7
#define DMAP1_ABB_DTFR5    (DMAP1 + 0x8a)

#define DMAP1_ABB_DTFR5_IFCN   0x7
#define DMAP1_ABB_DTFR6    (DMAP1 + 0x8c)

#define DMAP1_ABB_DTFR6_IFCN   0x7
#define DMAP1_ABB_DTFR7    (DMAP1 + 0x8e)

#define DMAP1_ABB_DTFR7_IFCN   0x7
#define DMAP1_ABB_DTCR0    (DMAP1 + 0x40)

#define DMAP1_ABB_DTCR1    (DMAP1 + 0x42)

#define DMAP1_ABB_DTCR2    (DMAP1 + 0x44)

#define DMAP1_ABB_DTCR3    (DMAP1 + 0x46)

#define DMAP1_ABB_DTCR4    (DMAP1 + 0x48)

#define DMAP1_ABB_DTCR5    (DMAP1 + 0x4a)

#define DMAP1_ABB_DTCR6    (DMAP1 + 0x4c)

#define DMAP1_ABB_DTCR7    (DMAP1 + 0x4e)

#define DMAP1_ABB_DTCR8    (DMAP1 + 0x50)

#define DMAP1_ABB_DTCR9    (DMAP1 + 0x52)

#define DMAP1_ABB_DMASL    (DMAP1 + 0x62)

#define DMAP1_ABB_DMASL_DMAS7   (0x1 << 7)
#define DMAP1_ABB_DMASL_DMAS6   (0x1 << 6)
#define DMAP1_ABB_DMASL_DMAS5   (0x1 << 5)
#define DMAP1_ABB_DMASL_DMAS4   (0x1 << 4)
#define DMAP1_ABB_DMASL_DMAS3   (0x1 << 3)
#define DMAP1_ABB_DMASL_DMAS2   (0x1 << 2)
#define DMAP1_ABB_DMASL_DMAS1   (0x1 << 1)
#define DMAP1_ABB_DMASL_DMAS0   0x1
#define DMAP1_ABB_DMAMCL    (DMAP1 + 0x60)

#define DMAP1_ABB_DMAMCL_DE7   (0x1 << 7)
#define DMAP1_ABB_DMAMCL_DE6   (0x1 << 6)
#define DMAP1_ABB_DMAMCL_DE5   (0x1 << 5)
#define DMAP1_ABB_DMAMCL_DE4   (0x1 << 4)
#define DMAP1_ABB_DMAMCL_DE3   (0x1 << 3)
#define DMAP1_ABB_DMAMCL_DE2   (0x1 << 2)
#define DMAP1_ABB_DMAMCL_DE1   (0x1 << 1)
#define DMAP1_ABB_DMAMCL_DE0   0x1
#define DMAP1_ABB_DMADSCL    (DMAP1 + 0x64)

#define DMAP1_ABB_DMADSCL_DMADCS7   (0x1 << 7)
#define DMAP1_ABB_DMADSCL_DMADCS6   (0x1 << 6)
#define DMAP1_ABB_DMADSCL_DMADCS5   (0x1 << 5)
#define DMAP1_ABB_DMADSCL_DMADCS4   (0x1 << 4)


#endif
