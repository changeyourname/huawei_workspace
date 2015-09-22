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


#ifndef M16C_EXCEPTIONS_H
#define M16C_EXCEPTIONS_H

#include "m16cTypeRefs.h"
#include "m16cStructure.h"

Bool m16cInterruptPending(m16cP);

void m16cNewNetPorts(m16cP);

void m16cFreeNetPorts(m16cP);

#endif

