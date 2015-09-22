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
// Set the macro 'SP1' to the base of port 'sp1'
#ifndef SP1
    #error SP1 is undefined.It needs to be set to the port base address
#endif
#define SP1_REG0_T0LO    (SP1 + 0x0)

#define SP1_REG0_T0HI    (SP1 + 0x4)

#define SP1_REG0_T0EV    (SP1 + 0x8)

#define SP1_REG0_T1LO    (SP1 + 0xc)

#define SP1_REG0_T1HI    (SP1 + 0x10)

#define SP1_REG0_T1EV    (SP1 + 0x14)

#define SP1_REG0_T2LO    (SP1 + 0x18)

#define SP1_REG0_T2HI    (SP1 + 0x1c)

#define SP1_REG0_T2EV    (SP1 + 0x20)

#define SP1_REG0_T3LO    (SP1 + 0x24)

#define SP1_REG0_T3HI    (SP1 + 0x28)

#define SP1_REG0_T3EV    (SP1 + 0x2c)

#define SP1_REG0_T4LO    (SP1 + 0x30)

#define SP1_REG0_T4HI    (SP1 + 0x34)

#define SP1_REG0_T4EV    (SP1 + 0x38)

#define SP1_REG0_T5LO    (SP1 + 0x3c)

#define SP1_REG0_T5HI    (SP1 + 0x40)

#define SP1_REG0_T5EV    (SP1 + 0x44)



#endif
