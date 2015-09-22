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

#ifndef OR1KMORPH_H
#define OR1KMORPH_H

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "or1kDecode.h"

//
// Handle arithmetic instructions
//
OR1K_DISPATCH_FN(or1kMorphADDI);
OR1K_DISPATCH_FN(or1kMorphADDIC);
OR1K_DISPATCH_FN(or1kMorphANDI);
OR1K_DISPATCH_FN(or1kMorphORI);
OR1K_DISPATCH_FN(or1kMorphXORI);
OR1K_DISPATCH_FN(or1kMorphMULI);

//
// NOP morpher callback
//
OR1K_DISPATCH_FN(or1kMorphNOP);

//
// Default morpher callback
//
OR1K_DISPATCH_FN(or1kMorphDefault);

#endif

