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

#ifndef OR1KINSTRUCTIONS_H
#define OR1KINSTRUCTIONS_H

#define WIDTH(_W, _ARG) ((_ARG) & ((1<<(_W))-1))

#define OP_D(_I)        WIDTH(5,(_I)>>21)
#define OP_A(_I)        WIDTH(5,(_I)>>16)
#define OP_B(_I)        WIDTH(5,(_I)>>11)
#define OP_I1(_I)       WIDTH(16,(_I)>>0)
#define OP_I2(_I)       ((WIDTH(5,(_I)>>21)<<11) | WIDTH(11,(_I)>>0))
#define OP_CMPOP(_I)    WIDTH(4,(_I)>>21)
#define OP_N(_I)        WIDTH(26,(_I)>>0)
#define OP_L(_I)        WIDTH(6,(_I)>>0)

#endif

