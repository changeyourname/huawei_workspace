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

#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "v850Exceptions.h"
#include "v850Functions.h"
#include "v850MorphFP.h"
#include "v850Instructions.h"
#include "v850Structure.h"
#include "v850Utils.h"

//
// mask is a pointer to the mask register in the structure
// left and right are the indices 0..31, so reverse format
// similar to the PPC
//
void v850MaskEnable(Uns32 *mask, Bool Enable, Uns32 left, Uns32 right) {
    //
    // set bits left downto right (inclusive) to be the value '1' in the mask
    //
    Uns32 l = 31 - left;
    Uns32 r = 31 - right;
    Uns32 addmask = 0xffffffff;

    if (Enable) {
        *mask |= VECINDEX(addmask, l, r, r);
    } else {
        *mask &= ~(VECINDEX(addmask, l, r, r));
    }
}

inline static Bool isHalted(v850P v850) {
    return vmirtIsHalted((vmiProcessorP)v850);
}

//
// Is NMI interrupt pending and enabled?
//
inline static Bool nmiPendingAndEnabled(v850P v850) {
    Bool enabled = False;

    if (v850->ResetPending) {
        // Held in reset
        return False;
    }

    if (v850->FLG_NMIPEND) {
        if (v850->FLG_NP) {
            //
            // NMI Interrupt Pending
            //
        } else {
            //
            // Begin Interrupt Service
            //
            enabled = True;
        }
    }
    return enabled;
}

//
// Is INTP interrupt pending and enabled?
//
inline static Bool intpPendingAndEnabled(v850P v850) {
    Bool enabled = False;

    if (v850->ResetPending) {
        // Held in reset
        return False;
    }

    //
    // Check Maskable interrupt
    //
    if (v850->FLG_INTPEND) {
        if (v850->FLG_NP) {
            //
            // NMI Interrupt Pending
            //
        } else {
            if (v850->FLG_ID == 1) {
                //
                // INTP Disabled
                //
            } else {
                //
                // Begin Interrupt Service
                //
                enabled = True;
            }
        }
    }
    return enabled;
}

Bool v850InterruptPending(v850P v850) {
    if(isHalted(v850)) {
        return ((v850->FLG_INTPEND != 0) || (v850->FLG_NMIPEND != 0));
    } else {
        return nmiPendingAndEnabled(v850) || intpPendingAndEnabled(v850);
    }
}

void v850TestInterrupt(v850P v850) {
    if(v850InterruptPending(v850)) {
        v850ProcessException((vmiProcessorP)v850);
    }
}

//
// Process NON Maskable Interrupt
//
static void doNonMaskableInterrupt(v850P v850) {
    Uns32 nmiHandler = 0;

    // FEPC <- PC
    v850->SPR_FEPC.reg = vmirtGetPC((vmiProcessorP)v850);

    // FEPSW <- PSW
    v850->SPR_FEPSW.reg = v850PackPSW(v850);

    // Which NMI is active ?
    // According to v850e2r
    //    the priority is 0x20, 0x30, 0x10
    //
    if (v850->netValue.nmi1) {
        nmiHandler = v850_VECTOR_nmi1;
    } else if (v850->netValue.nmi2) {
        nmiHandler = v850_VECTOR_nmi2;
    } else if (v850->netValue.nmi0) {
        nmiHandler = v850_VECTOR_nmi0;
    }

    v850->SPR_FEIC.reg = nmiHandler;

    // PSE.NP
    v850->FLG_NP = 1;

    // PSE.EP
    v850->FLG_EP = 0;

    // PSW.ID
    v850->FLG_ID = 1;

    // PC
    vmirtSetPCException((vmiProcessorP)v850, nmiHandler);

    // Send interrupt Acknowledge
    vmirtWriteNetPort((vmiProcessorP)v850, v850->netValue.intack, 1);
}

//
// Process Maskable Interrupt
//
static void doMaskableInterrupt(v850P v850) {
    // EIPC <- PC
    v850->SPR_EIPC.reg = vmirtGetPC((vmiProcessorP)v850);

    // EIPSW
    v850->SPR_EIPSW.reg = v850PackPSW(v850);

    // ECR.EICC (mask in lower 16 bits of Handler)
    v850->SPR_EIIC.reg = v850_VECTOR_intp & v850->netValue.intp;

    // PSE.EP
    v850->FLG_EP = 0;

    // PSW.ID
    v850->FLG_ID = 1;

    // PC
    vmirtSetPCException((vmiProcessorP)v850, v850->netValue.intp);

    // Send interrupt Acknowledge
    vmirtWriteNetPort((vmiProcessorP)v850, v850->netValue.intack, 1);
}

VMI_RD_PRIV_EXCEPT_FN(v850RdPrivExcept) {
}

VMI_WR_PRIV_EXCEPT_FN(v850WrPrivExcept) {
}

VMI_RD_ALIGN_EXCEPT_FN(v850RdAlignExcept) {
    return 0;
}

VMI_WR_ALIGN_EXCEPT_FN(v850WrAlignExcept) {
    return 0;
}

VMI_RD_ABORT_EXCEPT_FN(v850RdAbortExcept) {
}

VMI_WR_ABORT_EXCEPT_FN(v850WrAbortExcept) {
}

VMI_ARITH_EXCEPT_FN(v850ArithExcept) {
    v850P v850 = (v850P)processor;

    switch(exceptionType) {
        // integer divide-by-zero and overflow should not generate exceptions
        // but instead set the overflow flag
        case VMI_INTEGER_OVERFLOW:
            v850->FLG_SI = 1;
            v850->FLG_ZR = 0;
            /* no break */

        case VMI_INTEGER_DIVIDE_BY_ZERO:
            v850->FLG_OV = 1;
            return True;

        // not expecting any other arithmetic exception types
        default:
            return False;
    }
}

VMI_FP_ARITH_EXCEPT_FN(v850E1FPArithExcept) {

    //
    // Test Flags structure
    //
    // Denormal, tested after instruction completion
    if (flags->f.D) {
        flags->f.O = 0;
        flags->f.U = 0;
        flags->f.P = 0;
    }

    return VMI_FLOAT_CONTINUE;
}

VMI_FP_IND32_RESULT_FN(v850E2ConvertInd32) {
    Uns32 result = 0;
    VMI_ABORT("TODO: implement v850E2ConvertInd32 = %08x", value.u32);
    return result;
}

Uns64 clampDouble(
        vmiFPArg value,
        vmiFType type,
        Uns64 CLAMP_MIN,
        Uns64 CLAMP_MAX,
        Flt64 FCOMP_MIN,
        Flt64 FCOMP_MAX
) {
    Uns64 result = 0;

    if (value.type == vmi_FT_64_IEEE_754) {
        //
        // 64 bit Float -> 64/32 bit Signed/Unsigned CLAMP
        //
        if (IS_V850_FP64_INF(value.u64) && !IS_V850_FP64_NEG(value.u64)) {
            result = CLAMP_MAX;

        } else if (IS_V850_FP64_INF(value.u64) && IS_V850_FP64_NEG(value.u64)) {
            result = CLAMP_MIN;

        } else if (IS_V850_FP64_NAN(value.u64)) {
            result = CLAMP_MIN;

        } else if (value.f64 >= FCOMP_MAX) {
            result = CLAMP_MAX;

        } else if (value.f64 <= FCOMP_MIN) {
            result = CLAMP_MIN;

        } else {
            vmiMessage("F", "IND DBL->INT", "value.u64=" FMT_64x " %s:%d", value.u64, __FILE__, __LINE__);
        }

    } else if (value.type == vmi_FT_32_IEEE_754) {
        //
        // 32 bit Float -> 64/32 bit Signed/Unsigned CLAMP
        //
        if (IS_V850_FP32_INF(value.u32) && !IS_V850_FP32_NEG(value.u32)) {
            result = CLAMP_MAX;

        } else if (IS_V850_FP32_INF(value.u32) && IS_V850_FP32_NEG(value.u32)) {
            result = CLAMP_MIN;

        } else if (IS_V850_FP32_NAN(value.u32)) {
            result = CLAMP_MIN;

        } else if (value.f32 >= FCOMP_MAX) {
            result = CLAMP_MAX;

        } else if (value.f32 <= FCOMP_MIN) {
            result = CLAMP_MIN;

        } else {
            vmiMessage("F", "IND FLT->INT", "value.u32=0x%08x %s:%d", value.u32, __FILE__, __LINE__);
        }

    } else {
        vmiMessage("F", "IND DBL/FLT->INT", "value.u64=" FMT_64x " %s:%d", value.u64, __FILE__, __LINE__);
    }

    return result;
}

VMI_FP_IND32_RESULT_FN(v850E2Ind64_ds32) {
    Uns32 result = 0;

    result = (Uns32)
        clampDouble(value, vmi_FT_32_INT,
            (Int64)(Int32)V850_INT32_MIN, (Int64)(Int32)V850_INT32_MAX,
            (Flt64)(Int32)V850_INT32_MIN, (Flt64)(Int32)V850_INT32_MAX
        );
    return result;
}

VMI_FP_IND64_RESULT_FN(v850E2Ind64_ds64) {
    Uns64 result = 0;

    result = (Uns64)
        clampDouble(value, vmi_FT_64_INT,
            (Int64)V850_INT64_MIN, (Int64)V850_INT64_MAX,
            (Flt64)V850_INT64_MIN, (Flt64)V850_INT64_MAX
        );
    return result;
}

VMI_FP_IND32_RESULT_FN(v850E2Ind32_du32) {
    Uns32 result = 0;

    result = (Uns32)
        clampDouble(value, vmi_FT_32_UNS,
            (Uns64)(Uns32)V850_UNS32_MIN, (Uns64)(Uns32)V850_UNS32_MAX,
            (Flt64)(Uns32)V850_UNS32_MIN, (Flt64)(Uns32)V850_UNS32_MAX
        );
    return result;
}

VMI_FP_IND64_RESULT_FN(v850E2Ind64_du64) {
    Uns64 result = 0;

    result = (Uns64)
        clampDouble(value, vmi_FT_64_UNS,
            (Uns64)V850_UNS64_MIN, (Uns64)V850_UNS64_MAX,
            (Flt64)V850_UNS64_MIN, (Flt64)V850_UNS64_MAX
        );
    return result;
}

VMI_FP_64_RESULT_FN(v850E2ConvertResult64) {
    vmiPrintf("v850E2ConvertResult64\n");
    vmiPrintf("  argNum=%d\n", argNum);
    vmiPrintf("  result64=" FMT_64x "\n", result64);
    return result64;
}

VMI_FP_32_RESULT_FN(v850E2ConvertResult32) {
    vmiPrintf("v850E2ConvertResult32\n");
    vmiPrintf("  argNum=%d\n", argNum);
    vmiPrintf("  result32=0x%08x\n", result32);
    return result32;
}

VMI_FP_ARITH_EXCEPT_FN(v850E2FPArithExcept) {

    VMI_ABORT("TODO: implement FP exception");

    return VMI_FLOAT_CONTINUE;
}

VMI_IFETCH_FN(v850IfetchExcept) {
    v850P v850    = (v850P)processor;
    Uns32 thisPC  = (Uns32)address;

    Bool  fetchOK = False;

    if (nmiPendingAndEnabled(v850)) {

        fetchOK = False;

        if(complete) {
            doNonMaskableInterrupt(v850);
        }

    } else if (intpPendingAndEnabled(v850)) {

        fetchOK = False;

        if(complete) {
            doMaskableInterrupt(v850);
        }

    } else if (vmirtIsExecutable(processor, thisPC)) {

        // no exception pending
        fetchOK = True;

    } else {

        fetchOK = True;
    }

    if(fetchOK) {
        return VMI_FETCH_NONE;
    } else if(complete) {
        return VMI_FETCH_EXCEPTION_COMPLETE;
    } else {
        return VMI_FETCH_EXCEPTION_PENDING;
    }
}

VMI_ICOUNT_FN(v850IcountExcept) {
}

VMI_EXCEPTION_INFO_FN(v850ExceptionInfo) {

    //v850P              v850 = (v850P)processor;
    vmiExceptionInfoCP end = exceptions+v850_E_LAST;
    vmiExceptionInfoCP this;

    // on the first call, start with the first member of the table
    if(!prev) {
        prev = exceptions-1;
    }

    // search for the next member
    for(this=prev+1; this!=end; this++) {
        return this;
    }

    // no more exceptions
    return 0;
}

VMI_GET_EXCEPTION_FN(v850GetException) {
    return 0;
}

void v850ProcessException(vmiProcessorP processor) {
    vmirtRestartNext(processor);
    vmirtDoSynchronousInterrupt(processor);
}

static void v850RegisterInit (v850P v850) {
    v850->SPR_PSW.reg = 0x00000020;
    v850UnPackPSW(v850);
    if (v850->params.GDBSIMMODE) {
        v850->FLG_ID = 0;
        v850PackPSW(v850);
    }

    v850->SPR_EIIC.reg = 0x0;
    v850->SPR_FEIC.reg = 0x0;
    v850->SPR_EIWR.reg = 0x0;
    v850->SPR_FEWR.reg = 0x0;
    v850->SPR_DBWR.reg = 0x0;
    v850->SPR_BSEL.reg = 0x0;

    v850->SPR_FPSR.reg = 0x0;
    v850->SPR_FPSR.bits.FS = 1;
}

void v850ProcessReset(v850P v850) {
    //
    // Perform reset actions, then jump to reset vector
    //
    v850->exception = v850_E_reset;

    v850RegisterInit(v850);

    // jump to reset vector
    vmirtSetPCException((vmiProcessorP)v850, v850_VECTOR_reset);
}
