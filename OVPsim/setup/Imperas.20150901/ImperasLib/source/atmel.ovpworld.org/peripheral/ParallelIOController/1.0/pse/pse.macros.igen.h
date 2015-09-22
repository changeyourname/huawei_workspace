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
// Set the macro 'BP1' to the base of port 'bp1'
#ifndef BP1
    #error BP1 is undefined.It needs to be set to the port base address
#endif
#define BP1_REG_PIO_PER    (BP1 + 0x0)

#define BP1_REG_PIO_PDR    (BP1 + 0x4)

#define BP1_REG_PIO_PSR    (BP1 + 0x8)

#define BP1_REG_PIO_OER    (BP1 + 0x10)

#define BP1_REG_PIO_ODR    (BP1 + 0x14)

#define BP1_REG_PIO_OSR    (BP1 + 0x18)

#define BP1_REG_PIO_IFER    (BP1 + 0x20)

#define BP1_REG_PIO_IFDR    (BP1 + 0x24)

#define BP1_REG_PIO_IFSR    (BP1 + 0x28)

#define BP1_REG_PIO_SODR    (BP1 + 0x30)

#define BP1_REG_PIO_CODR    (BP1 + 0x34)

#define BP1_REG_PIO_ODSR    (BP1 + 0x38)

#define BP1_REG_PIO_PDSR    (BP1 + 0x3c)

#define BP1_REG_PIO_IER    (BP1 + 0x40)

#define BP1_REG_PIO_IDR    (BP1 + 0x44)

#define BP1_REG_PIO_IMR    (BP1 + 0x48)

#define BP1_REG_PIO_ISR    (BP1 + 0x4c)



#endif
