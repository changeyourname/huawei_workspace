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

#ifndef V850_MORPHFP_H
#define V850_MORPHFP_H

// VMI header files
#include "vmi/vmiTypes.h"
#include "vmi/vmiDbg.h"

//
// Set simulator floating point control word
//
void v850UpdateFPControlWord(v850P v850);

//
// Configure FPU
//
void v850ConfigureFPU(v850P v850);

//
// Floating point masks FP32
//
#define V850E1_FP32_QNAN      0xFFC00000
#define V850E2_FP32_QNAN      0x7FC00000

#define V850_FP32_MINUS_ZERO  0x80000000
#define V850_FP32_PLUS_ZERO   0x00000000
#define V850_INT32_MIN        0x80000000
#define V850_UNS32_MIN        0x00000000
#define V850_INT32_MAX        0x7FFFFFFF
#define V850_UNS32_MAX        0xFFFFFFFF

#define V850_FP32_SIGN(_arg)      ((_arg >> 31) & 0x1)
#define V850_FP32_EXPONENT(_arg)  ((_arg >> 23) & 0xFF)
#define V850_FP32_MANTISSA(_arg)  ((_arg >> 0)  & 0x7FFFFF)
#define IS_V850_FP32_NEG(_arg)    (V850_FP32_SIGN(_arg)==0x1)
#define IS_V850_FP32_NAN(_arg)    (V850_FP32_EXPONENT(_arg)==0xff && V850_FP32_MANTISSA(_arg)!=0)
#define IS_V850_FP32_INF(_arg)    (V850_FP32_EXPONENT(_arg)==0xff && V850_FP32_MANTISSA(_arg)==0)
#define IS_V850_FP32_DNORM(_arg)  (V850_FP32_EXPONENT(_arg)==0x00 && V850_FP32_MANTISSA(_arg)!=0)
#define IS_V850_FP32_ZERO(_arg)   (V850_FP32_EXPONENT(_arg)==0x00 && V850_FP32_MANTISSA(_arg)==0)

//
// Floating point masks FP64
//
#define V850E2_FP64_SIG      0xFFF7FFFFFFFFFFFFULL
#define V850E2_FP64_SNAN     0x7FF0000000000001ULL
#define V850E2_FP64_QNAN     0x7FF8000000000000ULL

#define V850_FP64_MINUS_ZERO 0x8000000000000000ULL
#define V850_FP64_PLUS_ZERO  0x0000000000000000ULL
#define V850_INT64_MIN       0x8000000000000000ULL
#define V850_UNS64_MIN       0x0000000000000000ULL
#define V850_INT64_MAX       0x7FFFFFFFFFFFFFFFULL
#define V850_UNS64_MAX       0xFFFFFFFFFFFFFFFFULL

#define V850_FP64_SIGN(_arg)      ((_arg >> 63) & 0x1)
#define V850_FP64_EXPONENT(_arg)  ((_arg >> 52) & 0x7FF)
#define V850_FP64_MANTISSA(_arg)  ((_arg >> 0)  & 0xFFFFFFFFFFFFFULL)
#define IS_V850_FP64_NEG(_arg)    (V850_FP64_SIGN(_arg)==0x1)
#define IS_V850_FP64_NAN(_arg)    (V850_FP64_EXPONENT(_arg)==0x7FF && V850_FP64_MANTISSA(_arg)!=0)
#define IS_V850_FP64_INF(_arg)    (V850_FP64_EXPONENT(_arg)==0x7FF && V850_FP64_MANTISSA(_arg)==0)
#define IS_V850_FP64_DNORM(_arg)  (V850_FP64_EXPONENT(_arg)==0x000 && V850_FP64_MANTISSA(_arg)!=0)
#define IS_V850_FP64_ZERO(_arg)   (V850_FP64_EXPONENT(_arg)==0x000 && V850_FP64_MANTISSA(_arg)==0)

//
// vmiFPFlags indices
//
#define FPFLAGS_I 0x01
#define FPFLAGS_D 0x02
#define FPFLAGS_Z 0x04
#define FPFLAGS_O 0x08
#define FPFLAGS_U 0x10
#define FPFLAGS_P 0x20

typedef enum v850FPCtrlE {
    V850_FP_DEFAULT,
    V850_FP_E1,
    V850_FP_E2,
    V850_FP_E2_CONVERT,
    V850_FP_FLT_TO_INT,
    V850_FP_FLT_TO_UNS,
    V850_FP_LAST         // KEEP LAST
} v850FPCtrl;

vmiFPConfigCP v850GetFPconfig(v850FPCtrl ctrl);

#endif // V850_MORPHFP_H
