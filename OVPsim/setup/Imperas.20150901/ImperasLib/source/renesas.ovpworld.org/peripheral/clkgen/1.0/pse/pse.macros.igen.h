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
// Set the macro 'CLKGENP0' to the base of port 'CLKGENP0'
#ifndef CLKGENP0
    #error CLKGENP0 is undefined.It needs to be set to the port base address
#endif
#define CLKGENP0_REG0_CANCKSEL    (CLKGENP0 + 0x0)

#define CLKGENP0_REG0_CANCKSEL_CANCK0   0x1

// Set the macro 'CLKGENP1' to the base of port 'CLKGENP1'
#ifndef CLKGENP1
    #error CLKGENP1 is undefined.It needs to be set to the port base address
#endif
#define CLKGENP1_REG0_CLM    (CLKGENP1 + 0x0)

#define CLKGENP1_REG0_CLM_CLME   0x1
#define CLKGENP1_REG0_CLM_CLMD   (0x1 << 1)


#endif
