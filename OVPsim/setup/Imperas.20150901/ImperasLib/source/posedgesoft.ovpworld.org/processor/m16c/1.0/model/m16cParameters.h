/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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


#ifndef M16C_PARAMETERS_H
#define M16C_PARAMETERS_H

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

#include "m16cTypeRefs.h"

//
// Define the attributes value structure
//
typedef struct m16cParamValuesS {
    VMI_ENUM_PARAM(variant);
    VMI_ENUM_PARAM(compatibility);
    VMI_BOOL_PARAM(verbose);
} m16cParamValues, *m16cParamValuesP;

#endif
