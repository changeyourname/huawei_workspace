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
#define BPORT1_AB_PFAPR    (BPORT1 + 0x0)

#define BPORT1_AB_PFAPR_M0AP   0x3
#define BPORT1_AB_PFAPR_M0PFD   (0x1 << 16)
#define BPORT1_AB_PFAPR_M1AP   (0x3 << 2)
#define BPORT1_AB_PFAPR_M1PFD   (0x1 << 17)
#define BPORT1_AB_PFAPR_M2AP   (0x3 << 4)
#define BPORT1_AB_PFAPR_M2PFD   (0x1 << 18)
#define BPORT1_AB_PFAPR_M3AP   (0x3 << 6)
#define BPORT1_AB_PFAPR_M3PFD   (0x1 << 19)
#define BPORT1_AB_PFAPR_M4AP   (0x3 << 8)
#define BPORT1_AB_PFAPR_M4PFD   (0x1 << 20)
#define BPORT1_AB_PFAPR_M5AP   (0x3 << 10)
#define BPORT1_AB_PFAPR_M5PFD   (0x1 << 21)
#define BPORT1_AB_PFAPR_M6AP   (0x3 << 12)
#define BPORT1_AB_PFAPR_M6PFD   (0x1 << 22)
#define BPORT1_AB_PFAPR_M7AP   (0x3 << 14)
#define BPORT1_AB_PFAPR_M7PFD   (0x1 << 23)
#define BPORT1_AB_PFB01CR    (BPORT1 + 0x4)

#define BPORT1_AB_PFB01CR_B01DCE   (0x1 << 4)
#define BPORT1_AB_PFB01CR_B01DPE   (0x1 << 2)
#define BPORT1_AB_PFB01CR_B01ICE   (0x1 << 3)
#define BPORT1_AB_PFB01CR_B01IPE   (0x1 << 1)
#define BPORT1_AB_PFB01CR_B01MW   (0x3 << 17)
#define BPORT1_AB_PFB01CR_B01RWSC   (0xf << 28)
#define BPORT1_AB_PFB01CR_B01SEBE   0x1
#define BPORT1_AB_PFB01CR_CINV_WAY   (0xf << 20)
#define BPORT1_AB_PFB01CR_CLCK_WAY   (0xf << 24)
#define BPORT1_AB_PFB01CR_CRC   (0x7 << 5)
#define BPORT1_AB_PFB01CR_S_B_INV   (0x1 << 19)
#define BPORT1_AB_PFB23CR    (BPORT1 + 0x8)

#define BPORT1_AB_PFB23CR_B23DCE   (0x1 << 4)
#define BPORT1_AB_PFB23CR_B23DPE   (0x1 << 2)
#define BPORT1_AB_PFB23CR_B23ICE   (0x1 << 3)
#define BPORT1_AB_PFB23CR_B23IPE   (0x1 << 1)
#define BPORT1_AB_PFB23CR_B23MW   (0x3 << 17)
#define BPORT1_AB_PFB23CR_B23RWSC   (0xf << 28)
#define BPORT1_AB_PFB23CR_B23SEBE   0x1
#define BPORT1_AB_TAGVDW0S0    (BPORT1 + 0x100)

#define BPORT1_AB_TAGVDW0S0_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW0S0_VALID   0x1
#define BPORT1_AB_TAGVDW0S1    (BPORT1 + 0x104)

#define BPORT1_AB_TAGVDW0S1_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW0S1_VALID   0x1
#define BPORT1_AB_TAGVDW0S2    (BPORT1 + 0x108)

#define BPORT1_AB_TAGVDW0S2_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW0S2_VALID   0x1
#define BPORT1_AB_TAGVDW0S3    (BPORT1 + 0x10c)

#define BPORT1_AB_TAGVDW0S3_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW0S3_VALID   0x1
#define BPORT1_AB_TAGVDW1S0    (BPORT1 + 0x110)

#define BPORT1_AB_TAGVDW1S0_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW1S0_VALID   0x1
#define BPORT1_AB_TAGVDW1S1    (BPORT1 + 0x114)

#define BPORT1_AB_TAGVDW1S1_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW1S1_VALID   0x1
#define BPORT1_AB_TAGVDW1S2    (BPORT1 + 0x118)

#define BPORT1_AB_TAGVDW1S2_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW1S2_VALID   0x1
#define BPORT1_AB_TAGVDW1S3    (BPORT1 + 0x11c)

#define BPORT1_AB_TAGVDW1S3_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW1S3_VALID   0x1
#define BPORT1_AB_TAGVDW2S0    (BPORT1 + 0x120)

#define BPORT1_AB_TAGVDW2S0_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW2S0_VALID   0x1
#define BPORT1_AB_TAGVDW2S1    (BPORT1 + 0x124)

#define BPORT1_AB_TAGVDW2S1_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW2S1_VALID   0x1
#define BPORT1_AB_TAGVDW2S2    (BPORT1 + 0x128)

#define BPORT1_AB_TAGVDW2S2_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW2S2_VALID   0x1
#define BPORT1_AB_TAGVDW2S3    (BPORT1 + 0x12c)

#define BPORT1_AB_TAGVDW2S3_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW2S3_VALID   0x1
#define BPORT1_AB_TAGVDW3S0    (BPORT1 + 0x130)

#define BPORT1_AB_TAGVDW3S0_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW3S0_VALID   0x1
#define BPORT1_AB_TAGVDW3S1    (BPORT1 + 0x134)

#define BPORT1_AB_TAGVDW3S1_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW3S1_VALID   0x1
#define BPORT1_AB_TAGVDW3S2    (BPORT1 + 0x138)

#define BPORT1_AB_TAGVDW3S2_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW3S2_VALID   0x1
#define BPORT1_AB_TAGVDW3S3    (BPORT1 + 0x13c)

#define BPORT1_AB_TAGVDW3S3_TAG   (0x3fff << 6)
#define BPORT1_AB_TAGVDW3S3_VALID   0x1
#define BPORT1_AB_DATAW0S0UM    (BPORT1 + 0x200)

#define BPORT1_AB_DATAW0S0UM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S0MU    (BPORT1 + 0x204)

#define BPORT1_AB_DATAW0S0MU_DATA   0xffffffff
#define BPORT1_AB_DATAW0S0ML    (BPORT1 + 0x208)

#define BPORT1_AB_DATAW0S0ML_DATA   0xffffffff
#define BPORT1_AB_DATAW0S0LM    (BPORT1 + 0x20c)

#define BPORT1_AB_DATAW0S0LM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S1UM    (BPORT1 + 0x210)

#define BPORT1_AB_DATAW0S1UM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S1MU    (BPORT1 + 0x214)

#define BPORT1_AB_DATAW0S1MU_DATA   0xffffffff
#define BPORT1_AB_DATAW0S1ML    (BPORT1 + 0x218)

#define BPORT1_AB_DATAW0S1ML_DATA   0xffffffff
#define BPORT1_AB_DATAW0S1LM    (BPORT1 + 0x21c)

#define BPORT1_AB_DATAW0S1LM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S2UM    (BPORT1 + 0x220)

#define BPORT1_AB_DATAW0S2UM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S2MU    (BPORT1 + 0x224)

#define BPORT1_AB_DATAW0S2MU_DATA   0xffffffff
#define BPORT1_AB_DATAW0S2ML    (BPORT1 + 0x228)

#define BPORT1_AB_DATAW0S2ML_DATA   0xffffffff
#define BPORT1_AB_DATAW0S2LM    (BPORT1 + 0x22c)

#define BPORT1_AB_DATAW0S2LM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S3UM    (BPORT1 + 0x230)

#define BPORT1_AB_DATAW0S3UM_DATA   0xffffffff
#define BPORT1_AB_DATAW0S3MU    (BPORT1 + 0x234)

#define BPORT1_AB_DATAW0S3MU_DATA   0xffffffff
#define BPORT1_AB_DATAW0S3ML    (BPORT1 + 0x238)

#define BPORT1_AB_DATAW0S3ML_DATA   0xffffffff
#define BPORT1_AB_DATAW0S3LM    (BPORT1 + 0x23c)

#define BPORT1_AB_DATAW0S3LM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S0UM    (BPORT1 + 0x240)

#define BPORT1_AB_DATAW1S0UM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S0MU    (BPORT1 + 0x244)

#define BPORT1_AB_DATAW1S0MU_DATA   0xffffffff
#define BPORT1_AB_DATAW1S0ML    (BPORT1 + 0x248)

#define BPORT1_AB_DATAW1S0ML_DATA   0xffffffff
#define BPORT1_AB_DATAW1S0LM    (BPORT1 + 0x24c)

#define BPORT1_AB_DATAW1S0LM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S1UM    (BPORT1 + 0x250)

#define BPORT1_AB_DATAW1S1UM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S1MU    (BPORT1 + 0x254)

#define BPORT1_AB_DATAW1S1MU_DATA   0xffffffff
#define BPORT1_AB_DATAW1S1ML    (BPORT1 + 0x258)

#define BPORT1_AB_DATAW1S1ML_DATA   0xffffffff
#define BPORT1_AB_DATAW1S1LM    (BPORT1 + 0x25c)

#define BPORT1_AB_DATAW1S1LM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S2UM    (BPORT1 + 0x260)

#define BPORT1_AB_DATAW1S2UM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S2MU    (BPORT1 + 0x264)

#define BPORT1_AB_DATAW1S2MU_DATA   0xffffffff
#define BPORT1_AB_DATAW1S2ML    (BPORT1 + 0x268)

#define BPORT1_AB_DATAW1S2ML_DATA   0xffffffff
#define BPORT1_AB_DATAW1S2LM    (BPORT1 + 0x26c)

#define BPORT1_AB_DATAW1S2LM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S3UM    (BPORT1 + 0x270)

#define BPORT1_AB_DATAW1S3UM_DATA   0xffffffff
#define BPORT1_AB_DATAW1S3MU    (BPORT1 + 0x274)

#define BPORT1_AB_DATAW1S3MU_DATA   0xffffffff
#define BPORT1_AB_DATAW1S3ML    (BPORT1 + 0x278)

#define BPORT1_AB_DATAW1S3ML_DATA   0xffffffff
#define BPORT1_AB_DATAW1S3LM    (BPORT1 + 0x27c)

#define BPORT1_AB_DATAW1S3LM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S0UM    (BPORT1 + 0x280)

#define BPORT1_AB_DATAW2S0UM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S0MU    (BPORT1 + 0x284)

#define BPORT1_AB_DATAW2S0MU_DATA   0xffffffff
#define BPORT1_AB_DATAW2S0ML    (BPORT1 + 0x288)

#define BPORT1_AB_DATAW2S0ML_DATA   0xffffffff
#define BPORT1_AB_DATAW2S0LM    (BPORT1 + 0x28c)

#define BPORT1_AB_DATAW2S0LM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S1UM    (BPORT1 + 0x290)

#define BPORT1_AB_DATAW2S1UM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S1MU    (BPORT1 + 0x294)

#define BPORT1_AB_DATAW2S1MU_DATA   0xffffffff
#define BPORT1_AB_DATAW2S1ML    (BPORT1 + 0x298)

#define BPORT1_AB_DATAW2S1ML_DATA   0xffffffff
#define BPORT1_AB_DATAW2S1LM    (BPORT1 + 0x29c)

#define BPORT1_AB_DATAW2S1LM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S2UM    (BPORT1 + 0x2a0)

#define BPORT1_AB_DATAW2S2UM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S2MU    (BPORT1 + 0x2a4)

#define BPORT1_AB_DATAW2S2MU_DATA   0xffffffff
#define BPORT1_AB_DATAW2S2ML    (BPORT1 + 0x2a8)

#define BPORT1_AB_DATAW2S2ML_DATA   0xffffffff
#define BPORT1_AB_DATAW2S2LM    (BPORT1 + 0x2ac)

#define BPORT1_AB_DATAW2S2LM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S3UM    (BPORT1 + 0x2b0)

#define BPORT1_AB_DATAW2S3UM_DATA   0xffffffff
#define BPORT1_AB_DATAW2S3MU    (BPORT1 + 0x2b4)

#define BPORT1_AB_DATAW2S3MU_DATA   0xffffffff
#define BPORT1_AB_DATAW2S3ML    (BPORT1 + 0x2b8)

#define BPORT1_AB_DATAW2S3ML_DATA   0xffffffff
#define BPORT1_AB_DATAW2S3LM    (BPORT1 + 0x2bc)

#define BPORT1_AB_DATAW2S3LM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S0UM    (BPORT1 + 0x2c0)

#define BPORT1_AB_DATAW3S0UM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S0MU    (BPORT1 + 0x2c4)

#define BPORT1_AB_DATAW3S0MU_DATA   0xffffffff
#define BPORT1_AB_DATAW3S0ML    (BPORT1 + 0x2c8)

#define BPORT1_AB_DATAW3S0ML_DATA   0xffffffff
#define BPORT1_AB_DATAW3S0LM    (BPORT1 + 0x2cc)

#define BPORT1_AB_DATAW3S0LM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S1UM    (BPORT1 + 0x2d0)

#define BPORT1_AB_DATAW3S1UM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S1MU    (BPORT1 + 0x2d4)

#define BPORT1_AB_DATAW3S1MU_DATA   0xffffffff
#define BPORT1_AB_DATAW3S1ML    (BPORT1 + 0x2d8)

#define BPORT1_AB_DATAW3S1ML_DATA   0xffffffff
#define BPORT1_AB_DATAW3S1LM    (BPORT1 + 0x2dc)

#define BPORT1_AB_DATAW3S1LM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S2UM    (BPORT1 + 0x2e0)

#define BPORT1_AB_DATAW3S2UM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S2MU    (BPORT1 + 0x2e4)

#define BPORT1_AB_DATAW3S2MU_DATA   0xffffffff
#define BPORT1_AB_DATAW3S2ML    (BPORT1 + 0x2e8)

#define BPORT1_AB_DATAW3S2ML_DATA   0xffffffff
#define BPORT1_AB_DATAW3S2LM    (BPORT1 + 0x2ec)

#define BPORT1_AB_DATAW3S2LM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S3UM    (BPORT1 + 0x2f0)

#define BPORT1_AB_DATAW3S3UM_DATA   0xffffffff
#define BPORT1_AB_DATAW3S3MU    (BPORT1 + 0x2f4)

#define BPORT1_AB_DATAW3S3MU_DATA   0xffffffff
#define BPORT1_AB_DATAW3S3ML    (BPORT1 + 0x2f8)

#define BPORT1_AB_DATAW3S3ML_DATA   0xffffffff
#define BPORT1_AB_DATAW3S3LM    (BPORT1 + 0x2fc)

#define BPORT1_AB_DATAW3S3LM_DATA   0xffffffff


#endif
