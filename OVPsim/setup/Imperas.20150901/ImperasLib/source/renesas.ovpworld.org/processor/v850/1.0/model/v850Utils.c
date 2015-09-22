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
#include "vmi/vmiMessage.h"
#include "v850Functions.h"
#include "v850Decode.h"
#include "v850Utils.h"

VMI_ENDIAN_FN(v850GetEndian) {
    v850P v850 = (v850P)processor;
    if (isFetch) {
        return v850->iendian;
    } else {
        return v850->dendian;
    }
}

VMI_NEXT_PC_FN(v850nextPC) {
    v850InstructionInfo info = {0};
    v850Decode((v850P)processor, thisPC, &info);
    v850Addr nextAddress = info.nextPC;
    return nextAddress;
}

VMI_IASSWITCH_FN(v850Switch) {
}

VMI_GET_MODE_FN(v850GetMode) {
    return 0;
}

VMI_MODE_INFO_FN(v850ModeInfo) {
    return 0;
}

void v850UnPackPSW(v850P v850) {
    v850->FLG_ZR  = v850->SPR_PSW.bits.Z;
    v850->FLG_SI  = v850->SPR_PSW.bits.S;
    v850->FLG_OV  = v850->SPR_PSW.bits.OV;
    v850->FLG_CO  = v850->SPR_PSW.bits.CY;
    v850->FLG_SAT = v850->SPR_PSW.bits.SAT;
    v850->FLG_ID  = v850->SPR_PSW.bits.ID;
    v850->FLG_EP  = v850->SPR_PSW.bits.EP;
    v850->FLG_NP  = v850->SPR_PSW.bits.NP;

    //
    // Execution levels determined by
    // NPV, DMP, IMP
    //   0    0    0    Exception Handler, OS Kernel etc
    //   0    1    0
    //   0    0    1
    //   0    1    1    OS Kernel Protected
    //   1    0    0    Common Library
    //   1    1    0
    //   1    0    1
    //   1    1    1    User Tasks
    //
}

Uns32 v850PackPSW(v850P v850) {
    v850->SPR_PSW.bits.Z   = v850->FLG_ZR;
    v850->SPR_PSW.bits.S   = v850->FLG_SI;
    v850->SPR_PSW.bits.OV  = v850->FLG_OV;
    v850->SPR_PSW.bits.CY  = v850->FLG_CO;
    v850->SPR_PSW.bits.SAT = v850->FLG_SAT;
    v850->SPR_PSW.bits.ID  = v850->FLG_ID;
    v850->SPR_PSW.bits.EP  = v850->FLG_EP;
    v850->SPR_PSW.bits.NP  = v850->FLG_NP;

    return v850->SPR_PSW.reg;
}

void v850UnPackEFG(v850P v850) {
    Uns32 efg;
    v850->FLG_FPZ         = v850->SPR_EFG.bits.Z;
    v850->FLG_FPS         = v850->SPR_EFG.bits.S;
    v850->FLG_FPOV        = v850->SPR_EFG.bits.OV;
    v850->FLG_FPF_STICKY  = v850->SPR_EFG.bits.TR;

    efg = v850->SPR_EFG.bits.IV << 0;
    efg = v850->SPR_EFG.bits.RO << 1;
    efg = v850->SPR_EFG.bits.ZD << 2;
    efg = v850->SPR_EFG.bits.VF << 3;
    efg = v850->SPR_EFG.bits.UD << 4;
    efg = v850->SPR_EFG.bits.PR << 5;

    v850->FLG_FPF = efg;

    /*
    vmiFPFlags flags;
    flags.bits = 0;
    flags.f.I = v850->SPR_EFG.bits.IV;
    flags.f.D = v850->SPR_EFG.bits.RO;
    flags.f.Z = v850->SPR_EFG.bits.ZD;
    flags.f.O = v850->SPR_EFG.bits.VF;
    flags.f.U = v850->SPR_EFG.bits.UD;
    flags.f.P = v850->SPR_EFG.bits.PR;
    v850->FLG_FPF = flags.bits;
    */
}

Uns32 v850PackEFG(v850P v850) {
    v850->SPR_EFG.bits.Z  = v850->FLG_FPZ;
    v850->SPR_EFG.bits.S  = v850->FLG_FPS;
    v850->SPR_EFG.bits.OV = v850->FLG_FPOV;
    v850->SPR_EFG.bits.TR = (v850->FLG_FPF_STICKY != 0) ? 1 : 0;   // Sticky TR Bit
    v850->SPR_EFG.bits.PR = (v850->FLG_FPF & 0x20)      ? 1 : 0;   // Precision Bit
    v850->SPR_EFG.bits.UD = (v850->FLG_FPF & 0x10)      ? 1 : 0;   // Underflow Bit
    v850->SPR_EFG.bits.VF = (v850->FLG_FPF & 0x08)      ? 1 : 0;   // Overflow Bit
    v850->SPR_EFG.bits.ZD = (v850->FLG_FPF & 0x04)      ? 1 : 0;   // Divide-By-Zero Bit
    v850->SPR_EFG.bits.IV = (v850->FLG_FPF & 0x01)      ? 1 : 0;   // Invalid Operation Bit
    v850->SPR_EFG.bits.RO = (v850->FLG_FPF & 0x02)      ? 1 : 0;   // Reserved Operand Bit

    return v850->SPR_EFG.reg;
}

Uns32 v850PackECR(v850P v850) {
    v850->SPR_ECR.bits.EICC = v850->SPR_EIIC.reg;
    v850->SPR_ECR.bits.FECC = v850->SPR_FEIC.reg;

    return v850->SPR_ECR.reg;
}

//
// Preservation bits
//
#define UNPACK_XP(SREG) {                             \
    vmiFPFlags flagsSticky = { 0 };                   \
    flagsSticky.f.P = v850->SPR_ ## SREG .bits.XP_I;  \
    flagsSticky.f.U = v850->SPR_ ## SREG .bits.XP_U;  \
    flagsSticky.f.O = v850->SPR_ ## SREG .bits.XP_O;  \
    flagsSticky.f.Z = v850->SPR_ ## SREG .bits.XP_Z;  \
    flagsSticky.f.I = v850->SPR_ ## SREG .bits.XP_V;  \
    v850->FLG_FPF_STICKY = flagsSticky.bits;          \
}
#define PACK_XP(SREG) {                                   \
    vmiFPFlags flagsSticky = {bits:v850->FLG_FPF_STICKY}; \
    v850->SPR_ ## SREG .bits.XP_I = flagsSticky.f.P;      \
    v850->SPR_ ## SREG .bits.XP_U = flagsSticky.f.U;      \
    v850->SPR_ ## SREG .bits.XP_O = flagsSticky.f.O;      \
    v850->SPR_ ## SREG .bits.XP_Z = flagsSticky.f.Z;      \
    v850->SPR_ ## SREG .bits.XP_V = flagsSticky.f.I;      \
}

//
// Cause bits (need to add XC_E bit)
//
#define UNPACK_XC(SREG) {                       \
    vmiFPFlags flags = { 0 };                   \
    flags.f.P = v850->SPR_ ## SREG .bits.XC_I;  \
    flags.f.U = v850->SPR_ ## SREG .bits.XC_U;  \
    flags.f.O = v850->SPR_ ## SREG .bits.XC_O;  \
    flags.f.Z = v850->SPR_ ## SREG .bits.XC_Z;  \
    flags.f.I = v850->SPR_ ## SREG .bits.XC_V;  \
    v850->FLG_FPF = flags.bits;                 \
}
#define PACK_XC(SREG) {                         \
    vmiFPFlags flags = {bits:v850->FLG_FPF};    \
    v850->SPR_ ## SREG .bits.XC_I = flags.f.P;  \
    v850->SPR_ ## SREG .bits.XC_U = flags.f.U;  \
    v850->SPR_ ## SREG .bits.XC_O = flags.f.O;  \
    v850->SPR_ ## SREG .bits.XC_Z = flags.f.Z;  \
    v850->SPR_ ## SREG .bits.XC_V = flags.f.I;  \
}

//
// CondCode bits
//
#define UNPACK_CC(SREG) {                             \
    v850->FPSR_CC[0] = v850->SPR_ ## SREG .bits.CC0;  \
    v850->FPSR_CC[1] = v850->SPR_ ## SREG .bits.CC1;  \
    v850->FPSR_CC[2] = v850->SPR_ ## SREG .bits.CC2;  \
    v850->FPSR_CC[3] = v850->SPR_ ## SREG .bits.CC3;  \
    v850->FPSR_CC[4] = v850->SPR_ ## SREG .bits.CC4;  \
    v850->FPSR_CC[5] = v850->SPR_ ## SREG .bits.CC5;  \
    v850->FPSR_CC[6] = v850->SPR_ ## SREG .bits.CC6;  \
    v850->FPSR_CC[7] = v850->SPR_ ## SREG .bits.CC7;  \
}

#define PACK_CC(SREG) {                                \
    v850->SPR_ ## SREG .bits.CC0  = v850->FPSR_CC[0];  \
    v850->SPR_ ## SREG .bits.CC1  = v850->FPSR_CC[1];  \
    v850->SPR_ ## SREG .bits.CC2  = v850->FPSR_CC[2];  \
    v850->SPR_ ## SREG .bits.CC3  = v850->FPSR_CC[3];  \
    v850->SPR_ ## SREG .bits.CC4  = v850->FPSR_CC[4];  \
    v850->SPR_ ## SREG .bits.CC5  = v850->FPSR_CC[5];  \
    v850->SPR_ ## SREG .bits.CC6  = v850->FPSR_CC[6];  \
    v850->SPR_ ## SREG .bits.CC7  = v850->FPSR_CC[7];  \
}


void v850UnPackFPSR(v850P v850) {

    //
    // Preservation Bits
    //
    UNPACK_XP(FPSR);

    //
    // Cause Bits
    //
    UNPACK_XC(FPSR);

    //
    // CC Bits
    //
    UNPACK_CC(FPSR);
}

Uns32 v850PackFPSR(v850P v850) {

    //
    // Preservation Bits
    //
    PACK_XP(FPSR);

    //
    // Cause Bits
    //
    PACK_XC(FPSR)

    //
    // CC Bits
    //
    PACK_CC(FPSR);

    return v850->SPR_FPSR.reg;
}

void v850UnPackFPST(v850P v850) {

    //
    // Preservation Bits
    //
    UNPACK_XP(FPST);

    //
    // Cause Bits
    //
    UNPACK_XC(FPST);
}

Uns32 v850PackFPST(v850P v850) {
    //
    // Preservation Bits
    //
    PACK_XP(FPST);

    //
    // Cause Bits
    //
    PACK_XC(FPST);

    //
    // PR bit
    //
    v850->SPR_FPST.bits.PR  = v850->SPR_FPSR.bits.PR;

    return v850->SPR_FPST.reg;
}

void v850UnPackFPCC(v850P v850) {

    //
    // CC Bits
    //
    UNPACK_CC(FPCC);
}

Uns32 v850PackFPCC(v850P v850) {

    //
    // CC Bits
    //
    PACK_CC(FPCC);

    return v850->SPR_FPCC.reg;
}

Uns32 v850PackFPCFG(v850P v850) {

    //
    // Copy FPSR.XE -> FPCFG.XE
    //
    v850->SPR_FPCFG.bits.XE_I = v850->SPR_FPSR.bits.XE_I;
    v850->SPR_FPCFG.bits.XE_U = v850->SPR_FPSR.bits.XE_U;
    v850->SPR_FPCFG.bits.XE_O = v850->SPR_FPSR.bits.XE_O;
    v850->SPR_FPCFG.bits.XE_Z = v850->SPR_FPSR.bits.XE_Z;
    v850->SPR_FPCFG.bits.XE_V = v850->SPR_FPSR.bits.XE_V;

    v850->SPR_FPCFG.bits.RM   = v850->SPR_FPSR.bits.RM;

    return v850->SPR_FPCFG.reg;
}

void v850UnPackFPCFG(v850P v850) {

    //
    // Copy FPCFG.XE -> FPSR.XE
    //
    v850->SPR_FPSR.bits.XE_I = v850->SPR_FPCFG.bits.XE_I;
    v850->SPR_FPSR.bits.XE_U = v850->SPR_FPCFG.bits.XE_U;
    v850->SPR_FPSR.bits.XE_O = v850->SPR_FPCFG.bits.XE_O;
    v850->SPR_FPSR.bits.XE_Z = v850->SPR_FPCFG.bits.XE_Z;
    v850->SPR_FPSR.bits.XE_V = v850->SPR_FPCFG.bits.XE_V;

    v850->SPR_FPSR.bits.RM   = v850->SPR_FPCFG.bits.RM;
}

