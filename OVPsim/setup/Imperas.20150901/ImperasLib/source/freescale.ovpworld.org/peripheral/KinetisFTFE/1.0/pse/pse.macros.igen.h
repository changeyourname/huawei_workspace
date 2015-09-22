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
#define BPORT1_AB_FSTAT    (BPORT1 + 0x0)

#define BPORT1_AB_FSTAT_ACCERR   (0x1 << 5)
#define BPORT1_AB_FSTAT_CCIF   (0x1 << 7)
#define BPORT1_AB_FSTAT_FPVIOL   (0x1 << 4)
#define BPORT1_AB_FSTAT_MGSTAT0   0x1
#define BPORT1_AB_FSTAT_RDCOLERR   (0x1 << 6)
#define BPORT1_AB_FCNFG    (BPORT1 + 0x1)

#define BPORT1_AB_FCNFG_CCIE   (0x1 << 7)
#define BPORT1_AB_FCNFG_EEERDY   0x1
#define BPORT1_AB_FCNFG_ERSAREQ   (0x1 << 5)
#define BPORT1_AB_FCNFG_ERSSUSP   (0x1 << 4)
#define BPORT1_AB_FCNFG_PFLSH   (0x1 << 2)
#define BPORT1_AB_FCNFG_RAMRDY   (0x1 << 1)
#define BPORT1_AB_FCNFG_RDCOLLIE   (0x1 << 6)
#define BPORT1_AB_FCNFG_SWAP   (0x1 << 3)
#define BPORT1_AB_FSEC    (BPORT1 + 0x2)

#define BPORT1_AB_FSEC_FSLACC   (0x3 << 2)
#define BPORT1_AB_FSEC_KEYEN   (0x3 << 6)
#define BPORT1_AB_FSEC_MEEN   (0x3 << 4)
#define BPORT1_AB_FSEC_SEC   0x3
#define BPORT1_AB_FOPT    (BPORT1 + 0x3)

#define BPORT1_AB_FOPT_OPT   0xff
#define BPORT1_AB_FCCOB3    (BPORT1 + 0x4)

#define BPORT1_AB_FCCOB3_CCOBN   0xff
#define BPORT1_AB_FCCOB2    (BPORT1 + 0x5)

#define BPORT1_AB_FCCOB2_CCOBN   0xff
#define BPORT1_AB_FCCOB1    (BPORT1 + 0x6)

#define BPORT1_AB_FCCOB1_CCOBN   0xff
#define BPORT1_AB_FCCOB0    (BPORT1 + 0x7)

#define BPORT1_AB_FCCOB0_CCOBN   0xff
#define BPORT1_AB_FCCOB7    (BPORT1 + 0x8)

#define BPORT1_AB_FCCOB7_CCOBN   0xff
#define BPORT1_AB_FCCOB6    (BPORT1 + 0x9)

#define BPORT1_AB_FCCOB5    (BPORT1 + 0xa)

#define BPORT1_AB_FCCOB5_CCOBN   0xff
#define BPORT1_AB_FCCOB4    (BPORT1 + 0xb)

#define BPORT1_AB_FCCOB4_CCOBN   0xff
#define BPORT1_AB_FCCOBB    (BPORT1 + 0xc)

#define BPORT1_AB_FCCOBB_CCOBN   0xff
#define BPORT1_AB_FCCOBA    (BPORT1 + 0xd)

#define BPORT1_AB_FCCOBA_CCOBN   0xff
#define BPORT1_AB_FCCOB9    (BPORT1 + 0xe)

#define BPORT1_AB_FCCOB9_CCOBN   0xff
#define BPORT1_AB_FCCOB8    (BPORT1 + 0xf)

#define BPORT1_AB_FCCOB8_CCOBN   0xff
#define BPORT1_AB_FPROT3    (BPORT1 + 0x10)

#define BPORT1_AB_FPROT3_PROT   0xff
#define BPORT1_AB_FPROT2    (BPORT1 + 0x11)

#define BPORT1_AB_FPROT2_PROT   0xff
#define BPORT1_AB_FPROT1    (BPORT1 + 0x12)

#define BPORT1_AB_FPROT1_PROT   0xff
#define BPORT1_AB_FPROT0    (BPORT1 + 0x13)

#define BPORT1_AB_FPROT0_PROT   0xff
#define BPORT1_AB_FEPROT    (BPORT1 + 0x16)

#define BPORT1_AB_FEPROT_EPROT   0xff
#define BPORT1_AB_FDPROT    (BPORT1 + 0x17)

#define BPORT1_AB_FDPROT_DPROT   0xff


#endif
