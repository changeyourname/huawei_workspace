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

#ifndef OR1KEXCEPTIONS_H
#define OR1KEXCEPTIONS_H

//
// Exception vector addresses
//
#define BUS_ADDRESS 0x200   // alignment exception vector
#define DPF_ADDRESS 0x300   // data privilege exception vector
#define IPF_ADDRESS 0x400   // instruction privilege exception vector
#define ILL_ADDRESS 0x700   // illegal instruction exception vector
#define SYS_ADDRESS 0xc00   // sys vector address

#endif
