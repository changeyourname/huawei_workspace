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
#define BP1_REG_AIC_SMR0    (BP1 + 0x0)

#define BP1_REG_AIC_SMR0_PRIOR   0x3
#define BP1_REG_AIC_SMR0_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR1    (BP1 + 0x4)

#define BP1_REG_AIC_SMR1_PRIOR   0x3
#define BP1_REG_AIC_SMR1_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR2    (BP1 + 0x8)

#define BP1_REG_AIC_SMR2_PRIOR   0x3
#define BP1_REG_AIC_SMR2_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR3    (BP1 + 0xc)

#define BP1_REG_AIC_SMR3_PRIOR   0x3
#define BP1_REG_AIC_SMR3_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR4    (BP1 + 0x10)

#define BP1_REG_AIC_SMR4_PRIOR   0x3
#define BP1_REG_AIC_SMR4_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR5    (BP1 + 0x14)

#define BP1_REG_AIC_SMR5_PRIOR   0x3
#define BP1_REG_AIC_SMR5_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR6    (BP1 + 0x18)

#define BP1_REG_AIC_SMR6_PRIOR   0x3
#define BP1_REG_AIC_SMR6_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR7    (BP1 + 0x1c)

#define BP1_REG_AIC_SMR7_PRIOR   0x3
#define BP1_REG_AIC_SMR7_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR8    (BP1 + 0x20)

#define BP1_REG_AIC_SMR8_PRIOR   0x3
#define BP1_REG_AIC_SMR8_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR9    (BP1 + 0x24)

#define BP1_REG_AIC_SMR9_PRIOR   0x3
#define BP1_REG_AIC_SMR9_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR10    (BP1 + 0x28)

#define BP1_REG_AIC_SMR10_PRIOR   0x3
#define BP1_REG_AIC_SMR10_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR11    (BP1 + 0x2c)

#define BP1_REG_AIC_SMR11_PRIOR   0x3
#define BP1_REG_AIC_SMR11_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR12    (BP1 + 0x30)

#define BP1_REG_AIC_SMR12_PRIOR   0x3
#define BP1_REG_AIC_SMR12_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR13    (BP1 + 0x34)

#define BP1_REG_AIC_SMR13_PRIOR   0x3
#define BP1_REG_AIC_SMR13_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR14    (BP1 + 0x38)

#define BP1_REG_AIC_SMR14_PRIOR   0x3
#define BP1_REG_AIC_SMR14_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR15    (BP1 + 0x3c)

#define BP1_REG_AIC_SMR15_PRIOR   0x3
#define BP1_REG_AIC_SMR15_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR16    (BP1 + 0x40)

#define BP1_REG_AIC_SMR16_PRIOR   0x3
#define BP1_REG_AIC_SMR16_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR17    (BP1 + 0x44)

#define BP1_REG_AIC_SMR17_PRIOR   0x3
#define BP1_REG_AIC_SMR17_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR18    (BP1 + 0x48)

#define BP1_REG_AIC_SMR18_PRIOR   0x3
#define BP1_REG_AIC_SMR18_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR19    (BP1 + 0x4c)

#define BP1_REG_AIC_SMR19_PRIOR   0x3
#define BP1_REG_AIC_SMR19_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR20    (BP1 + 0x50)

#define BP1_REG_AIC_SMR20_PRIOR   0x3
#define BP1_REG_AIC_SMR20_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR21    (BP1 + 0x54)

#define BP1_REG_AIC_SMR21_PRIOR   0x3
#define BP1_REG_AIC_SMR21_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR22    (BP1 + 0x58)

#define BP1_REG_AIC_SMR22_PRIOR   0x3
#define BP1_REG_AIC_SMR22_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR23    (BP1 + 0x5c)

#define BP1_REG_AIC_SMR23_PRIOR   0x3
#define BP1_REG_AIC_SMR23_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR24    (BP1 + 0x60)

#define BP1_REG_AIC_SMR24_PRIOR   0x3
#define BP1_REG_AIC_SMR24_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR25    (BP1 + 0x64)

#define BP1_REG_AIC_SMR25_PRIOR   0x3
#define BP1_REG_AIC_SMR25_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR26    (BP1 + 0x68)

#define BP1_REG_AIC_SMR26_PRIOR   0x3
#define BP1_REG_AIC_SMR26_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR27    (BP1 + 0x6c)

#define BP1_REG_AIC_SMR27_PRIOR   0x3
#define BP1_REG_AIC_SMR27_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR28    (BP1 + 0x70)

#define BP1_REG_AIC_SMR28_PRIOR   0x3
#define BP1_REG_AIC_SMR28_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR29    (BP1 + 0x74)

#define BP1_REG_AIC_SMR29_PRIOR   0x3
#define BP1_REG_AIC_SMR29_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR30    (BP1 + 0x78)

#define BP1_REG_AIC_SMR30_PRIOR   0x3
#define BP1_REG_AIC_SMR30_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SMR31    (BP1 + 0x7c)

#define BP1_REG_AIC_SMR31_PRIOR   0x3
#define BP1_REG_AIC_SMR31_SRCTYPE   (0x3 << 5)
#define BP1_REG_AIC_SVR0    (BP1 + 0x80)

#define BP1_REG_AIC_SVR0_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR1    (BP1 + 0x84)

#define BP1_REG_AIC_SVR1_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR2    (BP1 + 0x88)

#define BP1_REG_AIC_SVR2_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR3    (BP1 + 0x8c)

#define BP1_REG_AIC_SVR3_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR4    (BP1 + 0x90)

#define BP1_REG_AIC_SVR4_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR5    (BP1 + 0x94)

#define BP1_REG_AIC_SVR5_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR6    (BP1 + 0x98)

#define BP1_REG_AIC_SVR6_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR7    (BP1 + 0x9c)

#define BP1_REG_AIC_SVR7_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR8    (BP1 + 0xa0)

#define BP1_REG_AIC_SVR8_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR9    (BP1 + 0xa4)

#define BP1_REG_AIC_SVR9_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR10    (BP1 + 0xa8)

#define BP1_REG_AIC_SVR10_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR11    (BP1 + 0xac)

#define BP1_REG_AIC_SVR11_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR12    (BP1 + 0xb0)

#define BP1_REG_AIC_SVR12_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR13    (BP1 + 0xb4)

#define BP1_REG_AIC_SVR13_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR14    (BP1 + 0xb8)

#define BP1_REG_AIC_SVR14_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR15    (BP1 + 0xbc)

#define BP1_REG_AIC_SVR15_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR16    (BP1 + 0xc0)

#define BP1_REG_AIC_SVR16_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR17    (BP1 + 0xc4)

#define BP1_REG_AIC_SVR17_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR18    (BP1 + 0xc8)

#define BP1_REG_AIC_SVR18_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR19    (BP1 + 0xcc)

#define BP1_REG_AIC_SVR19_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR20    (BP1 + 0xd0)

#define BP1_REG_AIC_SVR20_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR21    (BP1 + 0xd4)

#define BP1_REG_AIC_SVR21_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR22    (BP1 + 0xd8)

#define BP1_REG_AIC_SVR22_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR23    (BP1 + 0xdc)

#define BP1_REG_AIC_SVR23_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR24    (BP1 + 0xe0)

#define BP1_REG_AIC_SVR24_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR25    (BP1 + 0xe4)

#define BP1_REG_AIC_SVR25_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR26    (BP1 + 0xe8)

#define BP1_REG_AIC_SVR26_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR27    (BP1 + 0xec)

#define BP1_REG_AIC_SVR27_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR28    (BP1 + 0xf0)

#define BP1_REG_AIC_SVR28_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR29    (BP1 + 0xf4)

#define BP1_REG_AIC_SVR29_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR30    (BP1 + 0xf8)

#define BP1_REG_AIC_SVR30_VECTOR   0xffffffff
#define BP1_REG_AIC_SVR31    (BP1 + 0xfc)

#define BP1_REG_AIC_SVR31_VECTOR   0xffffffff
#define BP1_REG_AIC_IVR    (BP1 + 0x100)

#define BP1_REG_AIC_FVR    (BP1 + 0x104)

#define BP1_REG_AIC_ISR    (BP1 + 0x108)

#define BP1_REG_AIC_ISR_IRQID   0x1f
#define BP1_REG_AIC_IPR    (BP1 + 0x10c)

#define BP1_REG_AIC_IPR_IRQ2   (0x1 << 18)
#define BP1_REG_AIC_IPR_IRQ1   (0x1 << 17)
#define BP1_REG_AIC_IPR_IRQ0   (0x1 << 16)
#define BP1_REG_AIC_IPR_PIOIRQ   (0x1 << 8)
#define BP1_REG_AIC_IPR_WDIRQ   (0x1 << 7)
#define BP1_REG_AIC_IPR_TC2IRQ   (0x1 << 6)
#define BP1_REG_AIC_IPR_TC1IRQ   (0x1 << 5)
#define BP1_REG_AIC_IPR_TC0IRQ   (0x1 << 4)
#define BP1_REG_AIC_IPR_US1IRQ   (0x1 << 3)
#define BP1_REG_AIC_IPR_US0IRQ   (0x1 << 2)
#define BP1_REG_AIC_IPR_SWIRQ   (0x1 << 1)
#define BP1_REG_AIC_IPR_FIQ   0x1
#define BP1_REG_AIC_IMR    (BP1 + 0x110)

#define BP1_REG_AIC_IMR_IRQ2   (0x1 << 18)
#define BP1_REG_AIC_IMR_IRQ1   (0x1 << 17)
#define BP1_REG_AIC_IMR_IRQ0   (0x1 << 16)
#define BP1_REG_AIC_IMR_PIOIRQ   (0x1 << 8)
#define BP1_REG_AIC_IMR_WDIRQ   (0x1 << 7)
#define BP1_REG_AIC_IMR_TC2IRQ   (0x1 << 6)
#define BP1_REG_AIC_IMR_TC1IRQ   (0x1 << 5)
#define BP1_REG_AIC_IMR_TC0IRQ   (0x1 << 4)
#define BP1_REG_AIC_IMR_US1IRQ   (0x1 << 3)
#define BP1_REG_AIC_IMR_US0IRQ   (0x1 << 2)
#define BP1_REG_AIC_IMR_SWIRQ   (0x1 << 1)
#define BP1_REG_AIC_IMR_FIQ   0x1
#define BP1_REG_AIC_CISR    (BP1 + 0x114)

#define BP1_REG_AIC_CISR_NIRQ   (0x1 << 1)
#define BP1_REG_AIC_CISR_NFIQ   0x1
#define BP1_REG_AIC_IECR    (BP1 + 0x120)

#define BP1_REG_AIC_IECR_IRQ2   (0x1 << 18)
#define BP1_REG_AIC_IECR_IRQ1   (0x1 << 17)
#define BP1_REG_AIC_IECR_IRQ0   (0x1 << 16)
#define BP1_REG_AIC_IECR_PIOIRQ   (0x1 << 8)
#define BP1_REG_AIC_IECR_WDIRQ   (0x1 << 7)
#define BP1_REG_AIC_IECR_TC2IRQ   (0x1 << 6)
#define BP1_REG_AIC_IECR_TC1IRQ   (0x1 << 5)
#define BP1_REG_AIC_IECR_TC0IRQ   (0x1 << 4)
#define BP1_REG_AIC_IECR_US1IRQ   (0x1 << 3)
#define BP1_REG_AIC_IECR_US0IRQ   (0x1 << 2)
#define BP1_REG_AIC_IECR_SWIRQ   (0x1 << 1)
#define BP1_REG_AIC_IECR_FIQ   0x1
#define BP1_REG_AIC_IDCR    (BP1 + 0x124)

#define BP1_REG_AIC_IDCR_IRQ2   (0x1 << 18)
#define BP1_REG_AIC_IDCR_IRQ1   (0x1 << 17)
#define BP1_REG_AIC_IDCR_IRQ0   (0x1 << 16)
#define BP1_REG_AIC_IDCR_PIOIRQ   (0x1 << 8)
#define BP1_REG_AIC_IDCR_WDIRQ   (0x1 << 7)
#define BP1_REG_AIC_IDCR_TC2IRQ   (0x1 << 6)
#define BP1_REG_AIC_IDCR_TC1IRQ   (0x1 << 5)
#define BP1_REG_AIC_IDCR_TC0IRQ   (0x1 << 4)
#define BP1_REG_AIC_IDCR_US1IRQ   (0x1 << 3)
#define BP1_REG_AIC_IDCR_US0IRQ   (0x1 << 2)
#define BP1_REG_AIC_IDCR_SWIRQ   (0x1 << 1)
#define BP1_REG_AIC_IDCR_FIQ   0x1
#define BP1_REG_AIC_ICCR    (BP1 + 0x128)

#define BP1_REG_AIC_ICCR_IRQ2   (0x1 << 18)
#define BP1_REG_AIC_ICCR_IRQ1   (0x1 << 17)
#define BP1_REG_AIC_ICCR_IRQ0   (0x1 << 16)
#define BP1_REG_AIC_ICCR_PIOIRQ   (0x1 << 8)
#define BP1_REG_AIC_ICCR_WDIRQ   (0x1 << 7)
#define BP1_REG_AIC_ICCR_TC2IRQ   (0x1 << 6)
#define BP1_REG_AIC_ICCR_TC1IRQ   (0x1 << 5)
#define BP1_REG_AIC_ICCR_TC0IRQ   (0x1 << 4)
#define BP1_REG_AIC_ICCR_US1IRQ   (0x1 << 3)
#define BP1_REG_AIC_ICCR_US0IRQ   (0x1 << 2)
#define BP1_REG_AIC_ICCR_SWIRQ   (0x1 << 1)
#define BP1_REG_AIC_ICCR_FIQ   0x1
#define BP1_REG_AIC_ISCR    (BP1 + 0x12c)

#define BP1_REG_AIC_ISCR_IRQ2   (0x1 << 18)
#define BP1_REG_AIC_ISCR_IRQ1   (0x1 << 17)
#define BP1_REG_AIC_ISCR_IRQ0   (0x1 << 16)
#define BP1_REG_AIC_ISCR_PIOIRQ   (0x1 << 8)
#define BP1_REG_AIC_ISCR_WDIRQ   (0x1 << 7)
#define BP1_REG_AIC_ISCR_TC2IRQ   (0x1 << 6)
#define BP1_REG_AIC_ISCR_TC1IRQ   (0x1 << 5)
#define BP1_REG_AIC_ISCR_TC0IRQ   (0x1 << 4)
#define BP1_REG_AIC_ISCR_US1IRQ   (0x1 << 3)
#define BP1_REG_AIC_ISCR_US0IRQ   (0x1 << 2)
#define BP1_REG_AIC_ISCR_SWIRQ   (0x1 << 1)
#define BP1_REG_AIC_ISCR_FIQ   0x1
#define BP1_REG_AIC_EOICR    (BP1 + 0x130)

#define BP1_REG_AIC_SPU    (BP1 + 0x134)



#endif
