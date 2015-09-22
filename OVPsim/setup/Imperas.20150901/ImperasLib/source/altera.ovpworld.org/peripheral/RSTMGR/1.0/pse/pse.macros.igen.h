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
#define BPORT1_REGS_STAT    (BPORT1 + 0x0)

#define BPORT1_REGS_CTRL    (BPORT1 + 0x4)

#define BPORT1_REGS_COUNTS    (BPORT1 + 0x8)

#define BPORT1_REGS_MPUMODRST    (BPORT1 + 0x10)

#define BPORT1_REGS_MPUMODRST_CPU0   0x1
#define BPORT1_REGS_MPUMODRST_CPU1   (0x1 << 1)
#define BPORT1_REGS_PERMODRST    (BPORT1 + 0x14)

#define BPORT1_REGS_PER2MODRST    (BPORT1 + 0x18)

#define BPORT1_REGS_BRGMODRST    (BPORT1 + 0x1c)

#define BPORT1_REGS_MISCMODRST    (BPORT1 + 0x20)



#endif
