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

// Definition of masks for OR1K instructions

#ifndef OR1KINSTRUCTIONS_H
#define OR1KINSTRUCTIONS_H

#define WIDTH(_W, _ARG)  ((_ARG) & ((1<<(_W))-1))

////////////////////////////////////////////////////////////////////////////////
// OPCODE FORM 2
// OPCODE(6) D(5) A(5) I(16)
////////////////////////////////////////////////////////////////////////////////
#define OP2_D(_I)       WIDTH(5,(_I)>>21)
#define OP2_A(_I)       WIDTH(5,(_I)>>16)
#define OP2_I(_I)       WIDTH(16,(_I)>>0)

////////////////////////////////////////////////////////////////////////////////
// OPCODE FORM 7
// OPCODE(6) N(26)
////////////////////////////////////////////////////////////////////////////////
#define OP7_N(_I)       WIDTH(26,(_I)>>0)

////////////////////////////////////////////////////////////////////////////////
// OPCODE FORM 8
// OPCODE(6) UNUSED(10) B(5) UNUSED(11)
////////////////////////////////////////////////////////////////////////////////
#define OP8_B(_I)       WIDTH(5,(_I)>>11)

#endif

