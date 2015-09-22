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

#ifndef V850_EXCEPTIONS_H
#define V850_EXCEPTIONS_H

#include "vmi/vmiDbg.h"

#include "v850TypeRefs.h"
#include "v850Structure.h"

//
// Exception vectors
//
typedef enum v850ExceptVectorE {
    v850_VECTOR_HIGH  = 0x0000ffff,
    v850_VECTOR_reset = 0x00000000,
    v850_VECTOR_nmi0  = 0x00000010,
    v850_VECTOR_nmi1  = 0x00000020,
    v850_VECTOR_nmi2  = 0x00000030,
    v850_VECTOR_intp  = 0x0000ffff,
    v850_VECTOR_trap0 = 0x00000040,
    v850_VECTOR_trap1 = 0x00000050,
    v850_VECTOR_ilgop = 0x00000060,
} v850ExceptVector;

//
// helper macro for filling exception table
//
#define V850_EXCEPTION_INFO(_D,_T) [v850_E_##_D] = {name:#_D, code:v850_VECTOR_##_D, description:_T}

//
// Table of exception mode descriptors
//
static const vmiExceptionInfo exceptions[v850_E_LAST] = {
    V850_EXCEPTION_INFO(reset, "Reset Signal Exception"),
    V850_EXCEPTION_INFO(nmi0,  "Non Maskable Interrupt(0) Exception"),
    V850_EXCEPTION_INFO(nmi1,  "Non Maskable Interrupt(1) Exception"),
    V850_EXCEPTION_INFO(nmi2,  "Non Maskable Interrupt(2) Exception"),
    V850_EXCEPTION_INFO(intp,  "Maskable Interrupt Exception - Vector value = (0x0000ffff AND intp)"),
    V850_EXCEPTION_INFO(trap0, "TRAP0 Exception"),
    V850_EXCEPTION_INFO(trap1, "TRAP1 Exception"),
    V850_EXCEPTION_INFO(ilgop, "Illegal OPCODE Exception"),
};

void v850MaskEnable(Uns32 *mask, Bool Enable, Uns32 left, Uns32 right);
void v850ProcessException(vmiProcessorP processor);
Bool v850InterruptPending(v850P v850);
void v850TestInterrupt(v850P v850);
void v850ProcessReset(v850P v850);

#endif

