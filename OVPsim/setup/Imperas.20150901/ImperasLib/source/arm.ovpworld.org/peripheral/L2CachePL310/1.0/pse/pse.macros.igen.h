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
#define BPORT1_AB_REG0_CACHE_ID    (BPORT1 + 0x0)

#define BPORT1_AB_REG0_CACHE_TYPE    (BPORT1 + 0x4)

#define BPORT1_AB_REG1_CONTROL    (BPORT1 + 0x100)

#define BPORT1_AB_REG1_AUX_CONTROL    (BPORT1 + 0x104)

#define BPORT1_AB_REG1_TAG_RAM_CONTROL    (BPORT1 + 0x108)

#define BPORT1_AB_REG1_DATA_RAM_CONTROL    (BPORT1 + 0x10c)

#define BPORT1_AB_REG2_EV_COUNTER_CTRL    (BPORT1 + 0x200)

#define BPORT1_AB_REG2_EV_COUNTER1_CFG    (BPORT1 + 0x204)

#define BPORT1_AB_REG2_EV_COUNTER0_CFG    (BPORT1 + 0x208)

#define BPORT1_AB_REG2_EV_COUNTER1    (BPORT1 + 0x20c)

#define BPORT1_AB_REG2_EV_COUNTER0    (BPORT1 + 0x210)

#define BPORT1_AB_REG2_INT_MASKE    (BPORT1 + 0x214)

#define BPORT1_AB_REG2_INT_MASK_STATUSE    (BPORT1 + 0x218)

#define BPORT1_AB_REG2_INT_RAW_STATUSE    (BPORT1 + 0x21c)

#define BPORT1_AB_REG2_INT_CLEARE    (BPORT1 + 0x220)

#define BPORT1_AB_REG7_CACHE_SYNC    (BPORT1 + 0x730)

#define BPORT1_AB_REG7_INV_PA    (BPORT1 + 0x770)

#define BPORT1_AB_REG7_INV_WAY    (BPORT1 + 0x77c)

#define BPORT1_AB_REG7_CLEAN_PA    (BPORT1 + 0x7b0)

#define BPORT1_AB_REG7_CLEAN_INDEX    (BPORT1 + 0x7b8)

#define BPORT1_AB_REG7_CLEAN_WAY    (BPORT1 + 0x7bc)

#define BPORT1_AB_REG7_CLEAN_INV_PA    (BPORT1 + 0x7f0)

#define BPORT1_AB_REG7_CLEAN_INV_INDEX    (BPORT1 + 0x7f8)

#define BPORT1_AB_REG7_CLEAN_INV_WAY    (BPORT1 + 0x7fc)

#define BPORT1_AB_REG9_D_LOCKDOWN0    (BPORT1 + 0x900)

#define BPORT1_AB_REG9_I_LOCKDOWN0    (BPORT1 + 0x904)

#define BPORT1_AB_REG9_D_LOCKDOWN1F    (BPORT1 + 0x908)

#define BPORT1_AB_REG9_I_LOCKDOWN1F    (BPORT1 + 0x90c)

#define BPORT1_AB_REG9_D_LOCKDOWN2F    (BPORT1 + 0x910)

#define BPORT1_AB_REG9_I_LOCKDOWN2F    (BPORT1 + 0x914)

#define BPORT1_AB_REG9_D_LOCKDOWN3F    (BPORT1 + 0x918)

#define BPORT1_AB_REG9_I_LOCKDOWN3F    (BPORT1 + 0x91c)

#define BPORT1_AB_REG9_D_LOCKDOWN4F    (BPORT1 + 0x920)

#define BPORT1_AB_REG9_I_LOCKDOWN4F    (BPORT1 + 0x924)

#define BPORT1_AB_REG9_D_LOCKDOWN5F    (BPORT1 + 0x928)

#define BPORT1_AB_REG9_I_LOCKDOWN5F    (BPORT1 + 0x92c)

#define BPORT1_AB_REG9_D_LOCKDOWN6F    (BPORT1 + 0x930)

#define BPORT1_AB_REG9_I_LOCKDOWN6F    (BPORT1 + 0x934)

#define BPORT1_AB_REG9_D_LOCKDOWN7F    (BPORT1 + 0x938)

#define BPORT1_AB_REG9_I_LOCKDOWN7F    (BPORT1 + 0x93c)

#define BPORT1_AB_REG9_LOCK_LINE_ENG    (BPORT1 + 0x950)

#define BPORT1_AB_REG9_UNLOCK_WAYG    (BPORT1 + 0x954)

#define BPORT1_AB_REG12_ADDR_FILT_START    (BPORT1 + 0xc00)

#define BPORT1_AB_REG12_ADDR_FILT_END    (BPORT1 + 0xc04)

#define BPORT1_AB_REG15_DEBUG_CTRL    (BPORT1 + 0xf40)

#define BPORT1_AB_REG15_PREFETCH_CTRL    (BPORT1 + 0xf60)

#define BPORT1_AB_REG15_POWER_CTRL    (BPORT1 + 0xf80)



#endif
