/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                              Version 99999999
//                          Thu Aug  7 11:47:06 2014
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DMAC_MACROS_IGEN_H
#define DMAC_MACROS_IGEN_H
////////////////////////////////// Description /////////////////////////////////

// DMAC peripheral model

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.
// Set the macro 'DMACSP' to the base of port 'DMACSP'
#ifndef DMACSP
    #error DMACSP is undefined.It needs to be set to the port base address
#endif
#define DMACSP_AB8_INTSTATUS    (DMACSP + 0x0)

#define DMACSP_AB8_INTTCSTATUS    (DMACSP + 0x4)

#define DMACSP_AB8_INTERRSTATUS    (DMACSP + 0xc)

#define DMACSP_AB8_RAWTCSTATUS    (DMACSP + 0x14)

#define DMACSP_AB8_RAWERRSTATUS    (DMACSP + 0x18)

#define DMACSP_AB8_ENBLDCHNS    (DMACSP + 0x1c)

#define DMACSP_AB8_CONFIG    (DMACSP + 0x30)

#define DMACSP_AB8_CONFIG_BURSTSIZE   0x3
#define DMACSP_AB32CH0_SRCADDR    (DMACSP + 0x100)

#define DMACSP_AB32CH0_DSTADDR    (DMACSP + 0x104)

#define DMACSP_AB32CH0_LLI    (DMACSP + 0x108)

#define DMACSP_AB32CH0_CONTROL    (DMACSP + 0x10c)

#define DMACSP_AB32CH0_CONTROL_TRANSFERSIZE   0xfff
#define DMACSP_AB32CH0_CONFIG    (DMACSP + 0x110)

#define DMACSP_AB32CH0_CONFIG_ENABLE   0x1
#define DMACSP_AB32CH0_CONFIG_INTEN   (0x1 << 15)
#define DMACSP_AB32CH0_CONFIG_HALT   (0x1 << 18)
#define DMACSP_AB32CH1_SRCADDR    (DMACSP + 0x120)

#define DMACSP_AB32CH1_DSTADDR    (DMACSP + 0x124)

#define DMACSP_AB32CH1_LLI    (DMACSP + 0x128)

#define DMACSP_AB32CH1_CONTROL    (DMACSP + 0x12c)

#define DMACSP_AB32CH1_CONTROL_TRANSFERSIZE   0xfff
#define DMACSP_AB32CH1_CONFIG    (DMACSP + 0x130)

#define DMACSP_AB32CH1_CONFIG_ENABLE   0x1
#define DMACSP_AB32CH1_CONFIG_HALT   (0x1 << 18)


#endif
