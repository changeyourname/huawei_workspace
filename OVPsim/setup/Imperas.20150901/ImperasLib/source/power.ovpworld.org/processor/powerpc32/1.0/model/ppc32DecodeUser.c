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

#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "ppc32Decode.h"
#include "ppc32Instructions.h"
#include "ppc32Structure.h"

//
// Decoder function for a given address
//
void ppc32Decode(
    ppc32P ppc32,
    ppc32Addr thisPC,
    ppc32InstructionInfoP info
) {
    //
    // Initialize the following info fields before table creation
    //
    info->thisPC = thisPC;
    info->arch = ppc32->configInfo.arch;
    vmiProcessorP processor = (vmiProcessorP)ppc32;

    //
    // Initialize the UISA decoder table
    //
    static vmidDecodeTableP decodeTable_UISA_16Bit;
    if(!decodeTable_UISA_16Bit) {
        if(ppc32->params.UISA_I_VLE) {
            decodeTable_UISA_16Bit = ppc32CreateDecodeTable_I_VLE_16Bit(decodeTable_UISA_16Bit, False);
        }
    }
    static vmidDecodeTableP decodeTable_UISA_32Bit;
    if(!decodeTable_UISA_32Bit) {
        if(ppc32->params.UISA_I_B) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_B_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_BCDA) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_BCDA_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_S) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_S_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_E) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_E_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_E_PC) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_E_PC_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_E_PD) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_E_PD_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_FP) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_FP_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_DFP) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_DFP_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_MA) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_MA_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_SP) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_SP_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_V) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_V_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_LMA) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_LMA_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_WT) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_WT_32Bit(decodeTable_UISA_32Bit, False);
        }
        if(ppc32->params.UISA_I_VLE) {
            decodeTable_UISA_32Bit = ppc32CreateDecodeTable_I_VLE_32Bit(decodeTable_UISA_32Bit, False);
        }
    }

    //
    // Initialize the mpc82x_32Bit decoder table
    //
    static vmidDecodeTableP decodeTable_mpc82x_32Bit;
    if(!decodeTable_mpc82x_32Bit && (info->arch == VARIANT_MPC82X)) {
        decodeTable_mpc82x_32Bit = ppc32CreateDecodeTable_I_B_32Bit(decodeTable_mpc82x_32Bit, False);
        decodeTable_mpc82x_32Bit = ppc32CreateDecodeTable_I_E_32Bit(decodeTable_mpc82x_32Bit, False);
        decodeTable_mpc82x_32Bit = ppc32CreateDecodeTable_I_MA_32Bit(decodeTable_mpc82x_32Bit, False);
    }

    //
    // Initialize the following info fields before lookup
    //

    info->instrsize = 0;
    info->type = PPC32_IT_LAST;
    Uns64 instruction = 0;

    if (info->arch == VARIANT_UISA) {
        if (info->type == PPC32_IT_LAST) info->type = PPC32_IT_INSTR16;
        //
        // Attempt to match a UISA 16 Bit instruction
        //
        if (info->type == PPC32_IT_INSTR16) {
            instruction  = (Uns64)vmicxtFetch2Byte(processor, thisPC+0) | (instruction << 0);
            info->type = PPC32_IT_LAST;
            if (decodeTable_UISA_16Bit) {
                info->type = vmidDecode(decodeTable_UISA_16Bit, instruction);
            } else {
                info->type = PPC32_IT_INSTR32;
            }
            info->nextPC = info->thisPC + 2;
            info->instrsize = 2;
            info->instruction = instruction;
        }
        //
        // Attempt to match a UISA 32 Bit instruction
        //
        if (info->type == PPC32_IT_INSTR32) {
            instruction  = (Uns64)vmicxtFetch2Byte(processor, thisPC+2) | (instruction << 16);
            info->type = PPC32_IT_LAST;
            if (decodeTable_UISA_32Bit) {
                info->type = vmidDecode(decodeTable_UISA_32Bit, instruction);
            }
            info->nextPC = info->thisPC + 4;
            info->instrsize = 4;
            info->instruction = instruction;
        }
    }

    if (info->arch == VARIANT_MPC82X) {
        if (info->type == PPC32_IT_LAST) info->type = PPC32_IT_INSTR32;
        //
        // Attempt to match a mpc82x 32 Bit instruction
        //
        if (info->type == PPC32_IT_INSTR32) {
            instruction  = (Uns64)vmicxtFetch4Byte(processor, thisPC+0) | (instruction << 0);
            info->type = PPC32_IT_LAST;
            info->type = vmidDecode(decodeTable_mpc82x_32Bit, instruction);
            info->nextPC = info->thisPC + 4;
            info->instrsize = 4;
            info->instruction = instruction;
        }
    }

    ppc32GenInstructionInfo(info);
}
