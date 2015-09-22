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
#define BPORT1_AB_PCR0    (BPORT1 + 0x0)

#define BPORT1_AB_PCR0_DSE   (0x1 << 6)
#define BPORT1_AB_PCR0_IRQC   (0xf << 16)
#define BPORT1_AB_PCR0_ISF   (0x1 << 24)
#define BPORT1_AB_PCR0_LK   (0x1 << 15)
#define BPORT1_AB_PCR0_MUX   (0x7 << 8)
#define BPORT1_AB_PCR0_ODE   (0x1 << 5)
#define BPORT1_AB_PCR0_PE   (0x1 << 1)
#define BPORT1_AB_PCR0_PFE   (0x1 << 4)
#define BPORT1_AB_PCR0_PS   0x1
#define BPORT1_AB_PCR0_SRE   (0x1 << 2)
#define BPORT1_AB_PCR1    (BPORT1 + 0x4)

#define BPORT1_AB_PCR1_DSE   (0x1 << 6)
#define BPORT1_AB_PCR1_IRQC   (0xf << 16)
#define BPORT1_AB_PCR1_ISF   (0x1 << 24)
#define BPORT1_AB_PCR1_LK   (0x1 << 15)
#define BPORT1_AB_PCR1_MUX   (0x7 << 8)
#define BPORT1_AB_PCR1_ODE   (0x1 << 5)
#define BPORT1_AB_PCR1_PE   (0x1 << 1)
#define BPORT1_AB_PCR1_PFE   (0x1 << 4)
#define BPORT1_AB_PCR1_PS   0x1
#define BPORT1_AB_PCR1_SRE   (0x1 << 2)
#define BPORT1_AB_PCR2    (BPORT1 + 0x8)

#define BPORT1_AB_PCR2_DSE   (0x1 << 6)
#define BPORT1_AB_PCR2_IRQC   (0xf << 16)
#define BPORT1_AB_PCR2_ISF   (0x1 << 24)
#define BPORT1_AB_PCR2_LK   (0x1 << 15)
#define BPORT1_AB_PCR2_MUX   (0x7 << 8)
#define BPORT1_AB_PCR2_ODE   (0x1 << 5)
#define BPORT1_AB_PCR2_PE   (0x1 << 1)
#define BPORT1_AB_PCR2_PFE   (0x1 << 4)
#define BPORT1_AB_PCR2_PS   0x1
#define BPORT1_AB_PCR2_SRE   (0x1 << 2)
#define BPORT1_AB_PCR3    (BPORT1 + 0xc)

#define BPORT1_AB_PCR3_DSE   (0x1 << 6)
#define BPORT1_AB_PCR3_IRQC   (0xf << 16)
#define BPORT1_AB_PCR3_ISF   (0x1 << 24)
#define BPORT1_AB_PCR3_LK   (0x1 << 15)
#define BPORT1_AB_PCR3_MUX   (0x7 << 8)
#define BPORT1_AB_PCR3_ODE   (0x1 << 5)
#define BPORT1_AB_PCR3_PE   (0x1 << 1)
#define BPORT1_AB_PCR3_PFE   (0x1 << 4)
#define BPORT1_AB_PCR3_PS   0x1
#define BPORT1_AB_PCR3_SRE   (0x1 << 2)
#define BPORT1_AB_PCR4    (BPORT1 + 0x10)

#define BPORT1_AB_PCR4_DSE   (0x1 << 6)
#define BPORT1_AB_PCR4_IRQC   (0xf << 16)
#define BPORT1_AB_PCR4_ISF   (0x1 << 24)
#define BPORT1_AB_PCR4_LK   (0x1 << 15)
#define BPORT1_AB_PCR4_MUX   (0x7 << 8)
#define BPORT1_AB_PCR4_ODE   (0x1 << 5)
#define BPORT1_AB_PCR4_PE   (0x1 << 1)
#define BPORT1_AB_PCR4_PFE   (0x1 << 4)
#define BPORT1_AB_PCR4_PS   0x1
#define BPORT1_AB_PCR4_SRE   (0x1 << 2)
#define BPORT1_AB_PCR5    (BPORT1 + 0x14)

#define BPORT1_AB_PCR5_DSE   (0x1 << 6)
#define BPORT1_AB_PCR5_IRQC   (0xf << 16)
#define BPORT1_AB_PCR5_ISF   (0x1 << 24)
#define BPORT1_AB_PCR5_LK   (0x1 << 15)
#define BPORT1_AB_PCR5_MUX   (0x7 << 8)
#define BPORT1_AB_PCR5_ODE   (0x1 << 5)
#define BPORT1_AB_PCR5_PE   (0x1 << 1)
#define BPORT1_AB_PCR5_PFE   (0x1 << 4)
#define BPORT1_AB_PCR5_PS   0x1
#define BPORT1_AB_PCR5_SRE   (0x1 << 2)
#define BPORT1_AB_PCR6    (BPORT1 + 0x18)

#define BPORT1_AB_PCR6_DSE   (0x1 << 6)
#define BPORT1_AB_PCR6_IRQC   (0xf << 16)
#define BPORT1_AB_PCR6_ISF   (0x1 << 24)
#define BPORT1_AB_PCR6_LK   (0x1 << 15)
#define BPORT1_AB_PCR6_MUX   (0x7 << 8)
#define BPORT1_AB_PCR6_ODE   (0x1 << 5)
#define BPORT1_AB_PCR6_PE   (0x1 << 1)
#define BPORT1_AB_PCR6_PFE   (0x1 << 4)
#define BPORT1_AB_PCR6_PS   0x1
#define BPORT1_AB_PCR6_SRE   (0x1 << 2)
#define BPORT1_AB_PCR7    (BPORT1 + 0x1c)

#define BPORT1_AB_PCR7_DSE   (0x1 << 6)
#define BPORT1_AB_PCR7_IRQC   (0xf << 16)
#define BPORT1_AB_PCR7_ISF   (0x1 << 24)
#define BPORT1_AB_PCR7_LK   (0x1 << 15)
#define BPORT1_AB_PCR7_MUX   (0x7 << 8)
#define BPORT1_AB_PCR7_ODE   (0x1 << 5)
#define BPORT1_AB_PCR7_PE   (0x1 << 1)
#define BPORT1_AB_PCR7_PFE   (0x1 << 4)
#define BPORT1_AB_PCR7_PS   0x1
#define BPORT1_AB_PCR7_SRE   (0x1 << 2)
#define BPORT1_AB_PCR8    (BPORT1 + 0x20)

#define BPORT1_AB_PCR8_DSE   (0x1 << 6)
#define BPORT1_AB_PCR8_IRQC   (0xf << 16)
#define BPORT1_AB_PCR8_ISF   (0x1 << 24)
#define BPORT1_AB_PCR8_LK   (0x1 << 15)
#define BPORT1_AB_PCR8_MUX   (0x7 << 8)
#define BPORT1_AB_PCR8_ODE   (0x1 << 5)
#define BPORT1_AB_PCR8_PE   (0x1 << 1)
#define BPORT1_AB_PCR8_PFE   (0x1 << 4)
#define BPORT1_AB_PCR8_PS   0x1
#define BPORT1_AB_PCR8_SRE   (0x1 << 2)
#define BPORT1_AB_PCR9    (BPORT1 + 0x24)

#define BPORT1_AB_PCR9_DSE   (0x1 << 6)
#define BPORT1_AB_PCR9_IRQC   (0xf << 16)
#define BPORT1_AB_PCR9_ISF   (0x1 << 24)
#define BPORT1_AB_PCR9_LK   (0x1 << 15)
#define BPORT1_AB_PCR9_MUX   (0x7 << 8)
#define BPORT1_AB_PCR9_ODE   (0x1 << 5)
#define BPORT1_AB_PCR9_PE   (0x1 << 1)
#define BPORT1_AB_PCR9_PFE   (0x1 << 4)
#define BPORT1_AB_PCR9_PS   0x1
#define BPORT1_AB_PCR9_SRE   (0x1 << 2)
#define BPORT1_AB_PCR10    (BPORT1 + 0x28)

#define BPORT1_AB_PCR10_DSE   (0x1 << 6)
#define BPORT1_AB_PCR10_IRQC   (0xf << 16)
#define BPORT1_AB_PCR10_ISF   (0x1 << 24)
#define BPORT1_AB_PCR10_LK   (0x1 << 15)
#define BPORT1_AB_PCR10_MUX   (0x7 << 8)
#define BPORT1_AB_PCR10_ODE   (0x1 << 5)
#define BPORT1_AB_PCR10_PE   (0x1 << 1)
#define BPORT1_AB_PCR10_PFE   (0x1 << 4)
#define BPORT1_AB_PCR10_PS   0x1
#define BPORT1_AB_PCR10_SRE   (0x1 << 2)
#define BPORT1_AB_PCR11    (BPORT1 + 0x2c)

#define BPORT1_AB_PCR11_DSE   (0x1 << 6)
#define BPORT1_AB_PCR11_IRQC   (0xf << 16)
#define BPORT1_AB_PCR11_ISF   (0x1 << 24)
#define BPORT1_AB_PCR11_LK   (0x1 << 15)
#define BPORT1_AB_PCR11_MUX   (0x7 << 8)
#define BPORT1_AB_PCR11_ODE   (0x1 << 5)
#define BPORT1_AB_PCR11_PE   (0x1 << 1)
#define BPORT1_AB_PCR11_PFE   (0x1 << 4)
#define BPORT1_AB_PCR11_PS   0x1
#define BPORT1_AB_PCR11_SRE   (0x1 << 2)
#define BPORT1_AB_PCR12    (BPORT1 + 0x30)

#define BPORT1_AB_PCR12_DSE   (0x1 << 6)
#define BPORT1_AB_PCR12_IRQC   (0xf << 16)
#define BPORT1_AB_PCR12_ISF   (0x1 << 24)
#define BPORT1_AB_PCR12_LK   (0x1 << 15)
#define BPORT1_AB_PCR12_MUX   (0x7 << 8)
#define BPORT1_AB_PCR12_ODE   (0x1 << 5)
#define BPORT1_AB_PCR12_PE   (0x1 << 1)
#define BPORT1_AB_PCR12_PFE   (0x1 << 4)
#define BPORT1_AB_PCR12_PS   0x1
#define BPORT1_AB_PCR12_SRE   (0x1 << 2)
#define BPORT1_AB_PCR13    (BPORT1 + 0x34)

#define BPORT1_AB_PCR13_DSE   (0x1 << 6)
#define BPORT1_AB_PCR13_IRQC   (0xf << 16)
#define BPORT1_AB_PCR13_ISF   (0x1 << 24)
#define BPORT1_AB_PCR13_LK   (0x1 << 15)
#define BPORT1_AB_PCR13_MUX   (0x7 << 8)
#define BPORT1_AB_PCR13_ODE   (0x1 << 5)
#define BPORT1_AB_PCR13_PE   (0x1 << 1)
#define BPORT1_AB_PCR13_PFE   (0x1 << 4)
#define BPORT1_AB_PCR13_PS   0x1
#define BPORT1_AB_PCR13_SRE   (0x1 << 2)
#define BPORT1_AB_PCR14    (BPORT1 + 0x38)

#define BPORT1_AB_PCR14_DSE   (0x1 << 6)
#define BPORT1_AB_PCR14_IRQC   (0xf << 16)
#define BPORT1_AB_PCR14_ISF   (0x1 << 24)
#define BPORT1_AB_PCR14_LK   (0x1 << 15)
#define BPORT1_AB_PCR14_MUX   (0x7 << 8)
#define BPORT1_AB_PCR14_ODE   (0x1 << 5)
#define BPORT1_AB_PCR14_PE   (0x1 << 1)
#define BPORT1_AB_PCR14_PFE   (0x1 << 4)
#define BPORT1_AB_PCR14_PS   0x1
#define BPORT1_AB_PCR14_SRE   (0x1 << 2)
#define BPORT1_AB_PCR15    (BPORT1 + 0x3c)

#define BPORT1_AB_PCR15_DSE   (0x1 << 6)
#define BPORT1_AB_PCR15_IRQC   (0xf << 16)
#define BPORT1_AB_PCR15_ISF   (0x1 << 24)
#define BPORT1_AB_PCR15_LK   (0x1 << 15)
#define BPORT1_AB_PCR15_MUX   (0x7 << 8)
#define BPORT1_AB_PCR15_ODE   (0x1 << 5)
#define BPORT1_AB_PCR15_PE   (0x1 << 1)
#define BPORT1_AB_PCR15_PFE   (0x1 << 4)
#define BPORT1_AB_PCR15_PS   0x1
#define BPORT1_AB_PCR15_SRE   (0x1 << 2)
#define BPORT1_AB_PCR16    (BPORT1 + 0x40)

#define BPORT1_AB_PCR16_DSE   (0x1 << 6)
#define BPORT1_AB_PCR16_IRQC   (0xf << 16)
#define BPORT1_AB_PCR16_ISF   (0x1 << 24)
#define BPORT1_AB_PCR16_LK   (0x1 << 15)
#define BPORT1_AB_PCR16_MUX   (0x7 << 8)
#define BPORT1_AB_PCR16_ODE   (0x1 << 5)
#define BPORT1_AB_PCR16_PE   (0x1 << 1)
#define BPORT1_AB_PCR16_PFE   (0x1 << 4)
#define BPORT1_AB_PCR16_PS   0x1
#define BPORT1_AB_PCR16_SRE   (0x1 << 2)
#define BPORT1_AB_PCR17    (BPORT1 + 0x44)

#define BPORT1_AB_PCR17_DSE   (0x1 << 6)
#define BPORT1_AB_PCR17_IRQC   (0xf << 16)
#define BPORT1_AB_PCR17_ISF   (0x1 << 24)
#define BPORT1_AB_PCR17_LK   (0x1 << 15)
#define BPORT1_AB_PCR17_MUX   (0x7 << 8)
#define BPORT1_AB_PCR17_ODE   (0x1 << 5)
#define BPORT1_AB_PCR17_PE   (0x1 << 1)
#define BPORT1_AB_PCR17_PFE   (0x1 << 4)
#define BPORT1_AB_PCR17_PS   0x1
#define BPORT1_AB_PCR17_SRE   (0x1 << 2)
#define BPORT1_AB_PCR18    (BPORT1 + 0x48)

#define BPORT1_AB_PCR18_DSE   (0x1 << 6)
#define BPORT1_AB_PCR18_IRQC   (0xf << 16)
#define BPORT1_AB_PCR18_ISF   (0x1 << 24)
#define BPORT1_AB_PCR18_LK   (0x1 << 15)
#define BPORT1_AB_PCR18_MUX   (0x7 << 8)
#define BPORT1_AB_PCR18_ODE   (0x1 << 5)
#define BPORT1_AB_PCR18_PE   (0x1 << 1)
#define BPORT1_AB_PCR18_PFE   (0x1 << 4)
#define BPORT1_AB_PCR18_PS   0x1
#define BPORT1_AB_PCR18_SRE   (0x1 << 2)
#define BPORT1_AB_PCR19    (BPORT1 + 0x4c)

#define BPORT1_AB_PCR19_DSE   (0x1 << 6)
#define BPORT1_AB_PCR19_IRQC   (0xf << 16)
#define BPORT1_AB_PCR19_ISF   (0x1 << 24)
#define BPORT1_AB_PCR19_LK   (0x1 << 15)
#define BPORT1_AB_PCR19_MUX   (0x7 << 8)
#define BPORT1_AB_PCR19_ODE   (0x1 << 5)
#define BPORT1_AB_PCR19_PE   (0x1 << 1)
#define BPORT1_AB_PCR19_PFE   (0x1 << 4)
#define BPORT1_AB_PCR19_PS   0x1
#define BPORT1_AB_PCR19_SRE   (0x1 << 2)
#define BPORT1_AB_PCR20    (BPORT1 + 0x50)

#define BPORT1_AB_PCR20_DSE   (0x1 << 6)
#define BPORT1_AB_PCR20_IRQC   (0xf << 16)
#define BPORT1_AB_PCR20_ISF   (0x1 << 24)
#define BPORT1_AB_PCR20_LK   (0x1 << 15)
#define BPORT1_AB_PCR20_MUX   (0x7 << 8)
#define BPORT1_AB_PCR20_ODE   (0x1 << 5)
#define BPORT1_AB_PCR20_PE   (0x1 << 1)
#define BPORT1_AB_PCR20_PFE   (0x1 << 4)
#define BPORT1_AB_PCR20_PS   0x1
#define BPORT1_AB_PCR20_SRE   (0x1 << 2)
#define BPORT1_AB_PCR21    (BPORT1 + 0x54)

#define BPORT1_AB_PCR21_DSE   (0x1 << 6)
#define BPORT1_AB_PCR21_IRQC   (0xf << 16)
#define BPORT1_AB_PCR21_ISF   (0x1 << 24)
#define BPORT1_AB_PCR21_LK   (0x1 << 15)
#define BPORT1_AB_PCR21_MUX   (0x7 << 8)
#define BPORT1_AB_PCR21_ODE   (0x1 << 5)
#define BPORT1_AB_PCR21_PE   (0x1 << 1)
#define BPORT1_AB_PCR21_PFE   (0x1 << 4)
#define BPORT1_AB_PCR21_PS   0x1
#define BPORT1_AB_PCR21_SRE   (0x1 << 2)
#define BPORT1_AB_PCR22    (BPORT1 + 0x58)

#define BPORT1_AB_PCR22_DSE   (0x1 << 6)
#define BPORT1_AB_PCR22_IRQC   (0xf << 16)
#define BPORT1_AB_PCR22_ISF   (0x1 << 24)
#define BPORT1_AB_PCR22_LK   (0x1 << 15)
#define BPORT1_AB_PCR22_MUX   (0x7 << 8)
#define BPORT1_AB_PCR22_ODE   (0x1 << 5)
#define BPORT1_AB_PCR22_PE   (0x1 << 1)
#define BPORT1_AB_PCR22_PFE   (0x1 << 4)
#define BPORT1_AB_PCR22_PS   0x1
#define BPORT1_AB_PCR22_SRE   (0x1 << 2)
#define BPORT1_AB_PCR23    (BPORT1 + 0x5c)

#define BPORT1_AB_PCR23_DSE   (0x1 << 6)
#define BPORT1_AB_PCR23_IRQC   (0xf << 16)
#define BPORT1_AB_PCR23_ISF   (0x1 << 24)
#define BPORT1_AB_PCR23_LK   (0x1 << 15)
#define BPORT1_AB_PCR23_MUX   (0x7 << 8)
#define BPORT1_AB_PCR23_ODE   (0x1 << 5)
#define BPORT1_AB_PCR23_PE   (0x1 << 1)
#define BPORT1_AB_PCR23_PFE   (0x1 << 4)
#define BPORT1_AB_PCR23_PS   0x1
#define BPORT1_AB_PCR23_SRE   (0x1 << 2)
#define BPORT1_AB_PCR24    (BPORT1 + 0x60)

#define BPORT1_AB_PCR24_DSE   (0x1 << 6)
#define BPORT1_AB_PCR24_IRQC   (0xf << 16)
#define BPORT1_AB_PCR24_ISF   (0x1 << 24)
#define BPORT1_AB_PCR24_LK   (0x1 << 15)
#define BPORT1_AB_PCR24_MUX   (0x7 << 8)
#define BPORT1_AB_PCR24_ODE   (0x1 << 5)
#define BPORT1_AB_PCR24_PE   (0x1 << 1)
#define BPORT1_AB_PCR24_PFE   (0x1 << 4)
#define BPORT1_AB_PCR24_PS   0x1
#define BPORT1_AB_PCR24_SRE   (0x1 << 2)
#define BPORT1_AB_PCR25    (BPORT1 + 0x64)

#define BPORT1_AB_PCR25_DSE   (0x1 << 6)
#define BPORT1_AB_PCR25_IRQC   (0xf << 16)
#define BPORT1_AB_PCR25_ISF   (0x1 << 24)
#define BPORT1_AB_PCR25_LK   (0x1 << 15)
#define BPORT1_AB_PCR25_MUX   (0x7 << 8)
#define BPORT1_AB_PCR25_ODE   (0x1 << 5)
#define BPORT1_AB_PCR25_PE   (0x1 << 1)
#define BPORT1_AB_PCR25_PFE   (0x1 << 4)
#define BPORT1_AB_PCR25_PS   0x1
#define BPORT1_AB_PCR25_SRE   (0x1 << 2)
#define BPORT1_AB_PCR26    (BPORT1 + 0x68)

#define BPORT1_AB_PCR26_DSE   (0x1 << 6)
#define BPORT1_AB_PCR26_IRQC   (0xf << 16)
#define BPORT1_AB_PCR26_ISF   (0x1 << 24)
#define BPORT1_AB_PCR26_LK   (0x1 << 15)
#define BPORT1_AB_PCR26_MUX   (0x7 << 8)
#define BPORT1_AB_PCR26_ODE   (0x1 << 5)
#define BPORT1_AB_PCR26_PE   (0x1 << 1)
#define BPORT1_AB_PCR26_PFE   (0x1 << 4)
#define BPORT1_AB_PCR26_PS   0x1
#define BPORT1_AB_PCR26_SRE   (0x1 << 2)
#define BPORT1_AB_PCR27    (BPORT1 + 0x6c)

#define BPORT1_AB_PCR27_DSE   (0x1 << 6)
#define BPORT1_AB_PCR27_IRQC   (0xf << 16)
#define BPORT1_AB_PCR27_ISF   (0x1 << 24)
#define BPORT1_AB_PCR27_LK   (0x1 << 15)
#define BPORT1_AB_PCR27_MUX   (0x7 << 8)
#define BPORT1_AB_PCR27_ODE   (0x1 << 5)
#define BPORT1_AB_PCR27_PE   (0x1 << 1)
#define BPORT1_AB_PCR27_PFE   (0x1 << 4)
#define BPORT1_AB_PCR27_PS   0x1
#define BPORT1_AB_PCR27_SRE   (0x1 << 2)
#define BPORT1_AB_PCR28    (BPORT1 + 0x70)

#define BPORT1_AB_PCR28_DSE   (0x1 << 6)
#define BPORT1_AB_PCR28_IRQC   (0xf << 16)
#define BPORT1_AB_PCR28_ISF   (0x1 << 24)
#define BPORT1_AB_PCR28_LK   (0x1 << 15)
#define BPORT1_AB_PCR28_MUX   (0x7 << 8)
#define BPORT1_AB_PCR28_ODE   (0x1 << 5)
#define BPORT1_AB_PCR28_PE   (0x1 << 1)
#define BPORT1_AB_PCR28_PFE   (0x1 << 4)
#define BPORT1_AB_PCR28_PS   0x1
#define BPORT1_AB_PCR28_SRE   (0x1 << 2)
#define BPORT1_AB_PCR29    (BPORT1 + 0x74)

#define BPORT1_AB_PCR29_DSE   (0x1 << 6)
#define BPORT1_AB_PCR29_IRQC   (0xf << 16)
#define BPORT1_AB_PCR29_ISF   (0x1 << 24)
#define BPORT1_AB_PCR29_LK   (0x1 << 15)
#define BPORT1_AB_PCR29_MUX   (0x7 << 8)
#define BPORT1_AB_PCR29_ODE   (0x1 << 5)
#define BPORT1_AB_PCR29_PE   (0x1 << 1)
#define BPORT1_AB_PCR29_PFE   (0x1 << 4)
#define BPORT1_AB_PCR29_PS   0x1
#define BPORT1_AB_PCR29_SRE   (0x1 << 2)
#define BPORT1_AB_PCR30    (BPORT1 + 0x78)

#define BPORT1_AB_PCR30_DSE   (0x1 << 6)
#define BPORT1_AB_PCR30_IRQC   (0xf << 16)
#define BPORT1_AB_PCR30_ISF   (0x1 << 24)
#define BPORT1_AB_PCR30_LK   (0x1 << 15)
#define BPORT1_AB_PCR30_MUX   (0x7 << 8)
#define BPORT1_AB_PCR30_ODE   (0x1 << 5)
#define BPORT1_AB_PCR30_PE   (0x1 << 1)
#define BPORT1_AB_PCR30_PFE   (0x1 << 4)
#define BPORT1_AB_PCR30_PS   0x1
#define BPORT1_AB_PCR30_SRE   (0x1 << 2)
#define BPORT1_AB_PCR31    (BPORT1 + 0x7c)

#define BPORT1_AB_PCR31_DSE   (0x1 << 6)
#define BPORT1_AB_PCR31_IRQC   (0xf << 16)
#define BPORT1_AB_PCR31_ISF   (0x1 << 24)
#define BPORT1_AB_PCR31_LK   (0x1 << 15)
#define BPORT1_AB_PCR31_MUX   (0x7 << 8)
#define BPORT1_AB_PCR31_ODE   (0x1 << 5)
#define BPORT1_AB_PCR31_PE   (0x1 << 1)
#define BPORT1_AB_PCR31_PFE   (0x1 << 4)
#define BPORT1_AB_PCR31_PS   0x1
#define BPORT1_AB_PCR31_SRE   (0x1 << 2)
#define BPORT1_AB_GPCLR    (BPORT1 + 0x80)

#define BPORT1_AB_GPCLR_GPWD   0xffff
#define BPORT1_AB_GPCLR_GPWE   (0xffff << 16)
#define BPORT1_AB_GPCHR    (BPORT1 + 0x84)

#define BPORT1_AB_GPCHR_GPWD   0xffff
#define BPORT1_AB_GPCHR_GPWE   (0xffff << 16)
#define BPORT1_AB_ISFR    (BPORT1 + 0xa0)

#define BPORT1_AB_ISFR_ISF   0xffffffff
#define BPORT1_AB_DFER    (BPORT1 + 0xc0)

#define BPORT1_AB_DFER_DFE   0xffffffff
#define BPORT1_AB_DFCR    (BPORT1 + 0xc4)

#define BPORT1_AB_DFCR_CS   0x1
#define BPORT1_AB_DFWR    (BPORT1 + 0xc8)

#define BPORT1_AB_DFWR_FILT   0x1f


#endif
