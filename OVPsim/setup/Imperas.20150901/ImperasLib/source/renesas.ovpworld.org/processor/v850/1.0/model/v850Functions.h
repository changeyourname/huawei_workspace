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

#ifndef V850_FUNCTIONS_H
#define V850_FUNCTIONS_H
#include "vmi/vmiAttrs.h"

// constructor & destructor
VMI_CONSTRUCTOR_FN(v850Constructor);
VMI_VMINIT_FN(v850VMInit);
VMI_DESTRUCTOR_FN(v850Destructor);

// morph function
VMI_MORPH_FN(v850Morph);
VMI_FETCH_SNAP_FN(v850FetchSnap);
VMI_RD_WR_SNAP_FN(v850RdSnap);
VMI_RD_WR_SNAP_FN(v850WrSnap);

// simulation support functions
VMI_ENDIAN_FN(v850GetEndian);
VMI_NEXT_PC_FN(v850nextPC);
VMI_DISASSEMBLE_FN(v850Dis);
VMI_IASSWITCH_FN(v850Switch);

// debugger integration support routines
VMI_REG_GROUP_FN(v850RegGroup);
VMI_REG_INFO_FN(v850RegInfo);
VMI_EXCEPTION_INFO_FN(v850ExceptionInfo);
VMI_MODE_INFO_FN(v850ModeInfo);
VMI_GET_EXCEPTION_FN(v850GetException);
VMI_GET_MODE_FN(v850GetMode);
VMI_DEBUG_FN(v850Debug);

// exception functions
VMI_RD_PRIV_EXCEPT_FN(v850RdPrivExcept);
VMI_WR_PRIV_EXCEPT_FN(v850WrPrivExcept);
VMI_RD_ALIGN_EXCEPT_FN(v850RdAlignExcept);
VMI_WR_ALIGN_EXCEPT_FN(v850WrAlignExcept);
VMI_RD_ABORT_EXCEPT_FN(v850RdAbortExcept);
VMI_WR_ABORT_EXCEPT_FN(v850WrAbortExcept);
VMI_IFETCH_FN(v850IfetchExcept);
VMI_ARITH_EXCEPT_FN(v850ArithExcept);
VMI_FP_ARITH_EXCEPT_FN(v850E1FPArithExcept);
VMI_FP_IND16_RESULT_FN(v850E2ConvertInd16);
VMI_FP_IND32_RESULT_FN(v850E2ConvertInd32);

VMI_FP_IND32_RESULT_FN(v850E2Ind64_ds32);
VMI_FP_IND64_RESULT_FN(v850E2Ind64_ds64);
VMI_FP_IND32_RESULT_FN(v850E2Ind32_du32);
VMI_FP_IND64_RESULT_FN(v850E2Ind64_du64);

VMI_FP_64_RESULT_FN(v850E2ConvertResult64);
VMI_FP_32_RESULT_FN(v850E2ConvertResult32);
VMI_FP_ARITH_EXCEPT_FN(v850E2FPArithExcept);
VMI_ICOUNT_FN(v850IcountExcept);

// parameter support functions
VMI_PROC_PARAM_SPECS_FN(v850ParamSpecs);
VMI_PROC_PARAM_TABLE_SIZE_FN(v850ParamValueSize);

// port/net functions
VMI_BUS_PORT_SPECS_FN(v850BusPortSpecs);
VMI_NET_PORT_SPECS_FN(v850NetPortSpecs);

// Imperas intercepted function support
VMI_INT_RETURN_FN(v850IntReturn);
VMI_INT_RESULT_FN(v850IntResult);
VMI_INT_PAR_FN(v850IntPar);

// Processor information support
VMI_PROC_INFO_FN(v850ProcInfo);
#endif // V850_FUNCTIONS_H
