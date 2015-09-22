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

#ifndef V850_VARIANT_H
#define V850_VARIANT_H

typedef enum v850ArchitectureE {
    //
    // Base Enumerated Architecture types
    //
    ISA_E0       = 0x00000002,
    ISA_E1       = 0x00000004,
    ISA_E2       = 0x00000008,
    ISA_E2M      = 0x00000010,
    ISA_E2R      = 0x00000020,
    ISA_E1_FP    = 0x00000040,
    ISA_E2_FP    = 0x00000080,

    //
    // Compound Enumerated Architecture types
    //
    V850         = 0x00000100 | ISA_E0,
    V850E1       = 0x00000200 | ISA_E0 | ISA_E1,
    V850E1F      = 0x00000400 | ISA_E0 | ISA_E1 | ISA_E1_FP,
    V850ES       = 0x00000800 | ISA_E0 | ISA_E1,
    V850E2       = 0x00001000 | ISA_E0 | ISA_E1 | ISA_E2,
    V850E2M      = 0x00002000 | ISA_E0 | ISA_E1 | ISA_E2 | ISA_E2M,
    V850E2R      = 0x00004000 | ISA_E0 | ISA_E1 | ISA_E2 | ISA_E2M | ISA_E2R | ISA_E2_FP,
} v850Architecture;

#endif // V850_VARIANT_H
