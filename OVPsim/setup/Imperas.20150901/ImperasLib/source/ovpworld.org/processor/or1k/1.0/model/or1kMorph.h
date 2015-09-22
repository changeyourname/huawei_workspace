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

#ifndef OR1KMORPH_H
#define OR1KMORPH_H

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "or1kDecode.h"

// Handle movhi instruction
OR1K_DISPATCH_FN(or1kMorphMOVHI);

//
// Handle arithmetic instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kMorphADDI);
OR1K_DISPATCH_FN(or1kMorphADDIC);
OR1K_DISPATCH_FN(or1kMorphANDI);
OR1K_DISPATCH_FN(or1kMorphORI);
OR1K_DISPATCH_FN(or1kMorphXORI);
OR1K_DISPATCH_FN(or1kMorphMULI);

//
// Handle arithmetic instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kMorphADD);
OR1K_DISPATCH_FN(or1kMorphADDC);
OR1K_DISPATCH_FN(or1kMorphSUB);
OR1K_DISPATCH_FN(or1kMorphAND);
OR1K_DISPATCH_FN(or1kMorphOR);
OR1K_DISPATCH_FN(or1kMorphXOR);
OR1K_DISPATCH_FN(or1kMorphMUL);
OR1K_DISPATCH_FN(or1kMorphDIV);
OR1K_DISPATCH_FN(or1kMorphDIVU);

//
// Handle shift/rotate instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kMorphSLLI);
OR1K_DISPATCH_FN(or1kMorphSRLI);
OR1K_DISPATCH_FN(or1kMorphSRAI);
OR1K_DISPATCH_FN(or1kMorphRORI);

//
// Handle shift/rotate instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kMorphSLL);
OR1K_DISPATCH_FN(or1kMorphSRL);
OR1K_DISPATCH_FN(or1kMorphSRA);
OR1K_DISPATCH_FN(or1kMorphROR);

//
// Handle branch instructions
//
OR1K_DISPATCH_FN(or1kMorphBF);
OR1K_DISPATCH_FN(or1kMorphBNF);
OR1K_DISPATCH_FN(or1kMorphJ);
OR1K_DISPATCH_FN(or1kMorphJR);
OR1K_DISPATCH_FN(or1kMorphJAL);
OR1K_DISPATCH_FN(or1kMorphJALR);

//
// Handle sys and rfe instructions
//
OR1K_DISPATCH_FN(or1kMorphSYS);
OR1K_DISPATCH_FN(or1kMorphRFE);

//
// Handle mtspr and mfspr instructions
//
OR1K_DISPATCH_FN(or1kMorphMTSPR);
OR1K_DISPATCH_FN(or1kMorphMFSPR);

//
// Handle load instructions
//
OR1K_DISPATCH_FN(or1kMorphLWZ);
OR1K_DISPATCH_FN(or1kMorphLWS);
OR1K_DISPATCH_FN(or1kMorphLBZ);
OR1K_DISPATCH_FN(or1kMorphLBS);
OR1K_DISPATCH_FN(or1kMorphLHZ);
OR1K_DISPATCH_FN(or1kMorphLHS);

//
// Handle store instructions
//
OR1K_DISPATCH_FN(or1kMorphSW);
OR1K_DISPATCH_FN(or1kMorphSB);
OR1K_DISPATCH_FN(or1kMorphSH);

//
// Handle comparison instructions
//
OR1K_DISPATCH_FN(or1kMorphSF);
OR1K_DISPATCH_FN(or1kMorphSFI);

//
// NOP morpher callback
//
OR1K_DISPATCH_FN(or1kMorphNOP);

//
// Default morpher callback
//
OR1K_DISPATCH_FN(or1kMorphDefault);

#endif

