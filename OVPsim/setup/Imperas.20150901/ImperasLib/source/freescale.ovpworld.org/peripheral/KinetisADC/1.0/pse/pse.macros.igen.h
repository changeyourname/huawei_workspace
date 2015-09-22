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
#define BPORT1_AB_SC1A    (BPORT1 + 0x0)

#define BPORT1_AB_SC1A_ADCH   0x1f
#define BPORT1_AB_SC1A_AIEN   (0x1 << 6)
#define BPORT1_AB_SC1A_COCO   (0x1 << 7)
#define BPORT1_AB_SC1A_DIFF   (0x1 << 5)
#define BPORT1_AB_SC1B    (BPORT1 + 0x4)

#define BPORT1_AB_SC1B_ADCH   0x1f
#define BPORT1_AB_SC1B_AIEN   (0x1 << 6)
#define BPORT1_AB_SC1B_COCO   (0x1 << 7)
#define BPORT1_AB_SC1B_DIFF   (0x1 << 5)
#define BPORT1_AB_CFG1    (BPORT1 + 0x8)

#define BPORT1_AB_CFG1_ADICLK   0x3
#define BPORT1_AB_CFG1_ADIV   (0x3 << 5)
#define BPORT1_AB_CFG1_ADLPC   (0x1 << 7)
#define BPORT1_AB_CFG1_ADLSMP   (0x1 << 4)
#define BPORT1_AB_CFG1_MODE   (0x3 << 2)
#define BPORT1_AB_CFG2    (BPORT1 + 0xc)

#define BPORT1_AB_CFG2_ADACKEN   (0x1 << 3)
#define BPORT1_AB_CFG2_ADHSC   (0x1 << 2)
#define BPORT1_AB_CFG2_ADLSTS   0x3
#define BPORT1_AB_CFG2_MUXSEL   (0x1 << 4)
#define BPORT1_AB_RA    (BPORT1 + 0x10)

#define BPORT1_AB_RA_D   0xffff
#define BPORT1_AB_RB    (BPORT1 + 0x14)

#define BPORT1_AB_RB_D   0xffff
#define BPORT1_AB_CV1    (BPORT1 + 0x18)

#define BPORT1_AB_CV1_CV   0xffff
#define BPORT1_AB_CV2    (BPORT1 + 0x1c)

#define BPORT1_AB_CV2_CV   0xffff
#define BPORT1_AB_SC2    (BPORT1 + 0x20)

#define BPORT1_AB_SC2_ACFE   (0x1 << 5)
#define BPORT1_AB_SC2_ACFGT   (0x1 << 4)
#define BPORT1_AB_SC2_ACREN   (0x1 << 3)
#define BPORT1_AB_SC2_ADACT   (0x1 << 7)
#define BPORT1_AB_SC2_ADTRG   (0x1 << 6)
#define BPORT1_AB_SC2_DMAEN   (0x1 << 2)
#define BPORT1_AB_SC2_REFSEL   0x3
#define BPORT1_AB_SC3    (BPORT1 + 0x24)

#define BPORT1_AB_SC3_ADCO   (0x1 << 3)
#define BPORT1_AB_SC3_AVGE   (0x1 << 2)
#define BPORT1_AB_SC3_AVGS   0x3
#define BPORT1_AB_SC3_CAL   (0x1 << 7)
#define BPORT1_AB_SC3_CALF   (0x1 << 6)
#define BPORT1_AB_OFS    (BPORT1 + 0x28)

#define BPORT1_AB_OFS_OFS   0xffff
#define BPORT1_AB_PG    (BPORT1 + 0x2c)

#define BPORT1_AB_PG_PG   0xffff
#define BPORT1_AB_MG    (BPORT1 + 0x30)

#define BPORT1_AB_MG_MG   0xffff
#define BPORT1_AB_CLPD    (BPORT1 + 0x34)

#define BPORT1_AB_CLPD_CLPD   0x3f
#define BPORT1_AB_CLPS    (BPORT1 + 0x38)

#define BPORT1_AB_CLPS_CLPS   0x3f
#define BPORT1_AB_CLP4    (BPORT1 + 0x3c)

#define BPORT1_AB_CLP4_CLP4   0x3ff
#define BPORT1_AB_CLP3    (BPORT1 + 0x40)

#define BPORT1_AB_CLP3_CLP3   0x1ff
#define BPORT1_AB_CLP2    (BPORT1 + 0x44)

#define BPORT1_AB_CLP2_CLP2   0xff
#define BPORT1_AB_CLP1    (BPORT1 + 0x48)

#define BPORT1_AB_CLP1_CLP1   0x7f
#define BPORT1_AB_CLP0    (BPORT1 + 0x4c)

#define BPORT1_AB_CLP0_CLP0   0x3f
#define BPORT1_AB_PGA    (BPORT1 + 0x50)

#define BPORT1_AB_PGA_PGACHPB   (0x1 << 21)
#define BPORT1_AB_PGA_PGAEN   (0x1 << 23)
#define BPORT1_AB_PGA_PGAG   (0xf << 16)
#define BPORT1_AB_PGA_PGALPB   (0x1 << 20)
#define BPORT1_AB_PGA_PGAOFSM   (0x1 << 14)
#define BPORT1_AB_CLMD    (BPORT1 + 0x54)

#define BPORT1_AB_CLMD_CLMD   0x3f
#define BPORT1_AB_CLMS    (BPORT1 + 0x58)

#define BPORT1_AB_CLMS_CLMS   0x3f
#define BPORT1_AB_CLM4    (BPORT1 + 0x5c)

#define BPORT1_AB_CLM4_CLM4   0x3ff
#define BPORT1_AB_CLM3    (BPORT1 + 0x60)

#define BPORT1_AB_CLM3_CLM3   0x1ff
#define BPORT1_AB_CLM2    (BPORT1 + 0x64)

#define BPORT1_AB_CLM2_CLM2   0xff
#define BPORT1_AB_CLM1    (BPORT1 + 0x68)

#define BPORT1_AB_CLM1_CLM1   0x7f
#define BPORT1_AB_CLM0    (BPORT1 + 0x6c)

#define BPORT1_AB_CLM0_CLM0   0x3f


#endif
