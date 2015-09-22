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
// Set the macro 'LOGICP0' to the base of port 'LOGICP0'
#ifndef LOGICP0
    #error LOGICP0 is undefined.It needs to be set to the port base address
#endif
#define LOGICP0_REG0_INTSEL    (LOGICP0 + 0x0)

#define LOGICP0_REG0_INTSEL_BRGSSR   0x1
#define LOGICP0_REG0_INTSEL_INTSEL4   (0x1 << 4)
#define LOGICP0_REG0_INTSEL_ISR   (0x1 << 7)
#define LOGICP0_REG0_INTERRF    (LOGICP0 + 0x2)

#define LOGICP0_REG0_INTERRF_INTERR0   0x1
#define LOGICP0_REG0_INTERRF_INTERR1   (0x1 << 1)
#define LOGICP0_REG0_INTERRF_INTERR2   (0x1 << 2)
#define LOGICP0_REG0_INTERRF_INTERR7   (0x1 << 7)

// Set the macro 'LOGICP1' to the base of port 'LOGICP1'
#ifndef LOGICP1
    #error LOGICP1 is undefined.It needs to be set to the port base address
#endif
#define LOGICP1_REG0_LOGICP0    (LOGICP1 + 0x0)

#define LOGICP1_REG0_P1    (LOGICP1 + 0x2)

#define LOGICP1_REG0_PM1    (LOGICP1 + 0x22)

#define LOGICP1_REG0_PMC1    (LOGICP1 + 0x42)

#define LOGICP1_REG0_P2    (LOGICP1 + 0x4)

#define LOGICP1_REG0_PM2    (LOGICP1 + 0x24)

#define LOGICP1_REG0_PMC2    (LOGICP1 + 0x44)

#define LOGICP1_REG0_P3    (LOGICP1 + 0x6)

#define LOGICP1_REG0_PM3    (LOGICP1 + 0x26)

#define LOGICP1_REG0_PMC3    (LOGICP1 + 0x46)

#define LOGICP1_REG0_P4    (LOGICP1 + 0x8)

#define LOGICP1_REG0_PM4    (LOGICP1 + 0x28)

#define LOGICP1_REG0_PMC4    (LOGICP1 + 0x48)

#define LOGICP1_REG0_P5    (LOGICP1 + 0xa)

#define LOGICP1_REG0_PM5    (LOGICP1 + 0x2a)

#define LOGICP1_REG0_PMC5    (LOGICP1 + 0x4a)

#define LOGICP1_REG0_P6    (LOGICP1 + 0xc)

#define LOGICP1_REG0_PM6    (LOGICP1 + 0x2c)

#define LOGICP1_REG0_PMC6    (LOGICP1 + 0x4c)

#define LOGICP1_REG0_P7    (LOGICP1 + 0xe)

#define LOGICP1_REG0_PM7    (LOGICP1 + 0x2e)

#define LOGICP1_REG0_PMC7    (LOGICP1 + 0x4e)

#define LOGICP1_REG0_P8    (LOGICP1 + 0x10)

#define LOGICP1_REG0_PM8    (LOGICP1 + 0x30)

#define LOGICP1_REG0_PMC8    (LOGICP1 + 0x50)

#define LOGICP1_REG0_P9    (LOGICP1 + 0x12)

#define LOGICP1_REG0_PM9    (LOGICP1 + 0x32)

#define LOGICP1_REG0_PMC9    (LOGICP1 + 0x52)

#define LOGICP1_REG0_P10    (LOGICP1 + 0x14)

#define LOGICP1_REG0_PM10    (LOGICP1 + 0x34)

#define LOGICP1_REG0_PMC10    (LOGICP1 + 0x54)

#define LOGICP1_REG0_P11    (LOGICP1 + 0x16)

#define LOGICP1_REG0_PM11    (LOGICP1 + 0x36)

#define LOGICP1_REG0_PMC11    (LOGICP1 + 0x56)

#define LOGICP1_REG0_PFC1    (LOGICP1 + 0x62)

#define LOGICP1_REG0_PFC2    (LOGICP1 + 0x64)

#define LOGICP1_REG0_PFC4    (LOGICP1 + 0x68)

#define LOGICP1_REG0_PFC4_PFC40   0x1
#define LOGICP1_REG0_PFC4_PFC41   (0x1 << 1)
#define LOGICP1_REG0_PFC7    (LOGICP1 + 0x6e)

#define LOGICP1_REG0_PFC8    (LOGICP1 + 0x70)

#define LOGICP1_REG0_PFC9    (LOGICP1 + 0x72)

#define LOGICP1_REG0_PFC10    (LOGICP1 + 0x74)


// Set the macro 'LOGICP2' to the base of port 'LOGICP2'
#ifndef LOGICP2
    #error LOGICP2 is undefined.It needs to be set to the port base address
#endif
#define LOGICP2_REG0_PESC5    (LOGICP2 + 0x0)

#define LOGICP2_REG0_ESOST5    (LOGICP2 + 0x2)

#define LOGICP2_REG0_PESC6    (LOGICP2 + 0x4)

#define LOGICP2_REG0_ESOST6    (LOGICP2 + 0x6)

#define LOGICP2_REG0_PESMK5    (LOGICP2 + 0x8)

#define LOGICP2_REG0_PESMK6    (LOGICP2 + 0xa)


// Set the macro 'LOGICP3' to the base of port 'LOGICP3'
#ifndef LOGICP3
    #error LOGICP3 is undefined.It needs to be set to the port base address
#endif
#define LOGICP3_REG0_PRCMD    (LOGICP3 + 0x0)



#endif
