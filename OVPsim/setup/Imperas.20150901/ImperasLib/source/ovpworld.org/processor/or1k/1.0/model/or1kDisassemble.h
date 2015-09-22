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

#ifndef OR1KDISASSEMBLE_H
#define OR1KDISASSEMBLE_H

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "or1kDecode.h"

// Handle movhi instruction
OR1K_DISPATCH_FN(or1kDisMOVHI);

//
// Handle arithmetic instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kDisADDI);
OR1K_DISPATCH_FN(or1kDisADDIC);
OR1K_DISPATCH_FN(or1kDisANDI);
OR1K_DISPATCH_FN(or1kDisORI);
OR1K_DISPATCH_FN(or1kDisXORI);
OR1K_DISPATCH_FN(or1kDisMULI);

//
// Handle arithmetic instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kDisADD);
OR1K_DISPATCH_FN(or1kDisADDC);
OR1K_DISPATCH_FN(or1kDisSUB);
OR1K_DISPATCH_FN(or1kDisAND);
OR1K_DISPATCH_FN(or1kDisOR);
OR1K_DISPATCH_FN(or1kDisXOR);
OR1K_DISPATCH_FN(or1kDisMUL);
OR1K_DISPATCH_FN(or1kDisDIV);
OR1K_DISPATCH_FN(or1kDisDIVU);

//
// Handle shift/rotate instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kDisSLLI);
OR1K_DISPATCH_FN(or1kDisSRLI);
OR1K_DISPATCH_FN(or1kDisSRAI);
OR1K_DISPATCH_FN(or1kDisRORI);

//
// Handle shift/rotate instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kDisSLL);
OR1K_DISPATCH_FN(or1kDisSRL);
OR1K_DISPATCH_FN(or1kDisSRA);
OR1K_DISPATCH_FN(or1kDisROR);

//
// Handle branch instructions
//
OR1K_DISPATCH_FN(or1kDisBF);
OR1K_DISPATCH_FN(or1kDisBNF);
OR1K_DISPATCH_FN(or1kDisJ);
OR1K_DISPATCH_FN(or1kDisJR);
OR1K_DISPATCH_FN(or1kDisJAL);
OR1K_DISPATCH_FN(or1kDisJALR);

//
// Handle sys and rfe instructions
//
OR1K_DISPATCH_FN(or1kDisSYS);
OR1K_DISPATCH_FN(or1kDisRFE);

//
// Handle mtspr and mfspr instructions
//
OR1K_DISPATCH_FN(or1kDisMTSPR);
OR1K_DISPATCH_FN(or1kDisMFSPR);

//
// Handle load instructions
//
OR1K_DISPATCH_FN(or1kDisLWZ);
OR1K_DISPATCH_FN(or1kDisLWS);
OR1K_DISPATCH_FN(or1kDisLBZ);
OR1K_DISPATCH_FN(or1kDisLBS);
OR1K_DISPATCH_FN(or1kDisLHZ);
OR1K_DISPATCH_FN(or1kDisLHS);

//
// Handle store instructions
//
OR1K_DISPATCH_FN(or1kDisSW);
OR1K_DISPATCH_FN(or1kDisSB);
OR1K_DISPATCH_FN(or1kDisSH);

//
// Handle comparison instructions
//
OR1K_DISPATCH_FN(or1kDisSF);
OR1K_DISPATCH_FN(or1kDisSFI);

//
// Handle nop instruction
//
OR1K_DISPATCH_FN(or1kDisNOP);

//
// Default disassembler callback
//
OR1K_DISPATCH_FN(or1kDisDefault);

#endif

