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
#define BPORT1_AB_LVDSC1    (BPORT1 + 0x0)

#define BPORT1_AB_LVDSC1_LVDACK   (0x1 << 6)
#define BPORT1_AB_LVDSC1_LVDF   (0x1 << 7)
#define BPORT1_AB_LVDSC1_LVDIE   (0x1 << 5)
#define BPORT1_AB_LVDSC1_LVDRE   (0x1 << 4)
#define BPORT1_AB_LVDSC1_LVDV   0x3
#define BPORT1_AB_LVDSC2    (BPORT1 + 0x1)

#define BPORT1_AB_LVDSC2_LVWACK   (0x1 << 6)
#define BPORT1_AB_LVDSC2_LVWF   (0x1 << 7)
#define BPORT1_AB_LVDSC2_LVWIE   (0x1 << 5)
#define BPORT1_AB_LVDSC2_LVWV   0x3
#define BPORT1_AB_REGSC    (BPORT1 + 0x2)

#define BPORT1_AB_REGSC_ACKISO   (0x1 << 3)
#define BPORT1_AB_REGSC_BGBE   0x1
#define BPORT1_AB_REGSC_BGEN   (0x1 << 4)
#define BPORT1_AB_REGSC_REGONS   (0x1 << 2)


#endif
