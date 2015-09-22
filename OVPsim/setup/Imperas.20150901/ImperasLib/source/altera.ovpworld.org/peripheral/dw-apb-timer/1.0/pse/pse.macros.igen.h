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
#define BPORT1_TIMER1_LOADCOUNT    (BPORT1 + 0x0)

#define BPORT1_TIMER1_CURRENTVAL    (BPORT1 + 0x4)

#define BPORT1_TIMER1_CONTROLREG    (BPORT1 + 0x8)

#define BPORT1_TIMER1_CONTROLREG_ENABLE   0x1
#define BPORT1_TIMER1_CONTROLREG_MODE   (0x1 << 1)
#define BPORT1_TIMER1_CONTROLREG_INTERRUPT_MASK   (0x1 << 2)
#define BPORT1_TIMER1_EOI    (BPORT1 + 0xc)

#define BPORT1_TIMER1_EOI_EOI   0x1
#define BPORT1_TIMER1_INTSTAT    (BPORT1 + 0x10)

#define BPORT1_TIMER1_INTSTAT_INTSTAT   0x1
#define BPORT1_TIMERS_INTSTAT    (BPORT1 + 0xa0)

#define BPORT1_TIMERS_INTSTAT_INTSTAT   0x1
#define BPORT1_TIMERS_EOI    (BPORT1 + 0xa4)

#define BPORT1_TIMERS_EOI_EOI   0x1
#define BPORT1_TIMERS_RAWINTSTAT    (BPORT1 + 0xa8)

#define BPORT1_TIMERS_RAWINTSTAT_INTSTAT   0x1
#define BPORT1_TIMERS_COMPVERSION    (BPORT1 + 0xac)



#endif
