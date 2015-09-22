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

// standard includes
#include <stdio.h>

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "or1kDecode.h"
#include "or1kFunctions.h"
#include "or1kInstructions.h"

//
// Disassemble a OR1K movhi instruction
//
static void doMovHi(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns16 i  = OP_I1(instr);

    sprintf(buffer, "%-8s r%u,0x%x", or1kop, rd, i);
}

//
// Disassemble a binary/signed literal OR1K instruction
//
static void doBinopSLit(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Int16 i  = OP_I1(instr);

    sprintf(buffer, "%-8s r%u,r%u,0x%x", or1kop, rd, ra, i);
}

//
// Disassemble a binary/unsigned literal OR1K instruction
//
static void doBinopULit(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Uns16 k  = OP_I1(instr);

    sprintf(buffer, "%-8s r%u,r%u,0x%x", or1kop, rd, ra, k);
}

//
// Disassemble a binary/register OR1K instruction
//
static void doBinopReg(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Uns32 rb = OP_B(instr);

    sprintf(buffer, "%-8s r%u,r%u,r%u", or1kop, rd, ra, rb);
}

//
// Disassemble a shift/literal OR1K instruction
//
static void doShiftopLit(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Int16 l  = OP_L(instr) & 0x1f;

    sprintf(buffer, "%-8s r%u,r%u,0x%x", or1kop, rd, ra, l);
}

//
// Disassemble a shift/register OR1K instruction
//
static void doShiftopReg(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Uns32 rb = OP_B(instr);

    sprintf(buffer, "%-8s r%u,r%u,r%u", or1kop, rd, ra, rb);
}

//
// Disassemble a branch or jump instruction.
//
static void doBranchJump(char *buffer, Uns32 thisPC, Uns32 instr, char *or1kop){

    Int32 n         = OP_N(instr);
    Int32 offset    = ((n<<6) >> 4);
    Uns32 toAddress = thisPC + offset;

    sprintf(buffer, "%-8s 0x%08x", or1kop, toAddress);
}

//
// Disassemble an indirect jump instruction
//
static void doJumpReg(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rb = OP_B(instr);

    sprintf(buffer, "%-8s r%u", or1kop, rb);
}

//
// Disassemble a sys instruction
//
static void doSYS(char *buffer, Uns32 instr, char *or1kop) {

    sprintf(buffer, "%-8s", or1kop);
}

//
// Disassemble an rfe instruction
//
static void doRFE(char *buffer, Uns32 instr, char *or1kop) {

    sprintf(buffer, "%-8s", or1kop);
}

//
// Disassemble OR1K mfspr instruction
//
static void doMFSPR(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Uns16 k  = OP_I1(instr);

    sprintf(buffer, "%-8s r%u,r%u,%u", or1kop, rd, ra, (Uns32)k);
}

//
// Disassemble OR1K mtspr instruction
//
static void doMTSPR(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 ra = OP_A(instr);
    Uns32 rb = OP_B(instr);
    Uns16 k  = OP_I2(instr);

    sprintf(buffer, "%-8s r%u,r%u,%u", or1kop, ra, rb, (Uns32)k);
}

//
// Disassemble a load from an address
//
static void doLoad(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP_D(instr);
    Uns32 ra = OP_A(instr);
    Int16 i  = OP_I1(instr);

    sprintf(buffer, "%-8s r%u,0x%x(r%u)", or1kop, rd, i, ra);
}

//
// Disassemble a store to an address
//
static void doStore(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 ra = OP_A(instr);
    Uns32 rb = OP_B(instr);
    Int16 i  = OP_I2(instr);

    sprintf(buffer, "%-8s 0x%x(r%u),r%u", or1kop, i, ra, rb);
}

//
// Disassemble a register comparison instruction
//
static void doCompareReg(char *buffer, Uns32 instr, char *or1kopFmt) {

    Uns32 ra = OP_A(instr);
    Uns32 rb = OP_B(instr);
    char  opBuf[16];

    sprintf(opBuf, or1kopFmt, or1kDecodeCmpName(instr));
    sprintf(buffer, "%-8s r%u,r%u", opBuf, ra, rb);
}

//
// Disassemble a literal comparison instruction
//
static void doCompareLit(char *buffer, Uns32 instr, char *or1kopFmt) {

    Uns32 ra = OP_A(instr);
    Int16 i  = OP_I1(instr);
    char  opBuf[16];

    sprintf(opBuf, or1kopFmt, or1kDecodeCmpName(instr));
    sprintf(buffer, "%-8s r%u,0x%x", opBuf, ra, i);
}

//
// Disassemble a OR1K NOP instruction
//
static void doNop(char *buffer, Uns32 instr, char *or1kop) {
    sprintf(buffer, "%-8s 0x%x", or1kop, OP_I1(instr));
}

//
// Handle movhi instruction
//
static OR1K_DISPATCH_FN(disMOVHI) {doMovHi(userData, instr, "l.movhi");}

//
// Handle arithmetic instructions (second argument constant)
//
static OR1K_DISPATCH_FN(disADDI)  {doBinopSLit(userData, instr, "l.addi");}
static OR1K_DISPATCH_FN(disADDIC) {doBinopSLit(userData, instr, "l.addic");}
static OR1K_DISPATCH_FN(disANDI)  {doBinopULit(userData, instr, "l.andi");}
static OR1K_DISPATCH_FN(disORI)   {doBinopULit(userData, instr, "l.ori");}
static OR1K_DISPATCH_FN(disXORI)  {doBinopSLit(userData, instr, "l.xori");}
static OR1K_DISPATCH_FN(disMULI)  {doBinopSLit(userData, instr, "l.muli");}

//
// Handle arithmetic instructions (second argument register)
//
static OR1K_DISPATCH_FN(disADD)   {doBinopReg(userData, instr, "l.add");}
static OR1K_DISPATCH_FN(disADDC)  {doBinopReg(userData, instr, "l.addc");}
static OR1K_DISPATCH_FN(disSUB)   {doBinopReg(userData, instr, "l.sub");}
static OR1K_DISPATCH_FN(disAND)   {doBinopReg(userData, instr, "l.and");}
static OR1K_DISPATCH_FN(disOR)    {doBinopReg(userData, instr, "l.or");}
static OR1K_DISPATCH_FN(disXOR)   {doBinopReg(userData, instr, "l.xor");}
static OR1K_DISPATCH_FN(disMUL)   {doBinopReg(userData, instr, "l.mul");}
static OR1K_DISPATCH_FN(disDIV)   {doBinopReg(userData, instr, "l.div");}
static OR1K_DISPATCH_FN(disDIVU)  {doBinopReg(userData, instr, "l.divu");}

//
// Handle shift/rotate instructions (second argument constant)
//
static OR1K_DISPATCH_FN(disSLLI)  {doShiftopLit(userData, instr, "l.slli");}
static OR1K_DISPATCH_FN(disSRLI)  {doShiftopLit(userData, instr, "l.srli");}
static OR1K_DISPATCH_FN(disSRAI)  {doShiftopLit(userData, instr, "l.srai");}
static OR1K_DISPATCH_FN(disRORI)  {doShiftopLit(userData, instr, "l.rori");}

//
// Handle shift/rotate instructions (second argument register)
//
static OR1K_DISPATCH_FN(disSLL)   {doShiftopReg(userData, instr, "l.sll");}
static OR1K_DISPATCH_FN(disSRL)   {doShiftopReg(userData, instr, "l.srl");}
static OR1K_DISPATCH_FN(disSRA)   {doShiftopReg(userData, instr, "l.sra");}
static OR1K_DISPATCH_FN(disROR)   {doShiftopReg(userData, instr, "l.ror");}

//
// Handle branch instructions
//
static OR1K_DISPATCH_FN(disBF)    {doBranchJump(userData, thisPC, instr, "l.bf");}
static OR1K_DISPATCH_FN(disBNF)   {doBranchJump(userData, thisPC, instr, "l.bnf");}
static OR1K_DISPATCH_FN(disJ)     {doBranchJump(userData, thisPC, instr, "l.j");}
static OR1K_DISPATCH_FN(disJR)    {doJumpReg(userData, instr, "l.jr");}
static OR1K_DISPATCH_FN(disJAL)   {doBranchJump(userData, thisPC, instr, "l.jal");}
static OR1K_DISPATCH_FN(disJALR)  {doJumpReg(userData, instr, "l.jalr");}

//
// Handle sys and rfe instructions
//
static OR1K_DISPATCH_FN(disSYS)   {doSYS(userData, instr, "l.sys");}
static OR1K_DISPATCH_FN(disRFE)   {doRFE(userData, instr, "l.rfe");}

//
// Handle mtspr and mfspr instructions
//
static OR1K_DISPATCH_FN(disMTSPR) {doMTSPR(userData, instr, "l.mtspr");}
static OR1K_DISPATCH_FN(disMFSPR) {doMFSPR(userData, instr, "l.mfspr");}

//
// Handle load instructions
//
static OR1K_DISPATCH_FN(disLWZ)   {doLoad(userData, instr, "l.lwz");}
static OR1K_DISPATCH_FN(disLWS)   {doLoad(userData, instr, "l.lws");}
static OR1K_DISPATCH_FN(disLBZ)   {doLoad(userData, instr, "l.lbz");}
static OR1K_DISPATCH_FN(disLBS)   {doLoad(userData, instr, "l.lbs");}
static OR1K_DISPATCH_FN(disLHZ)   {doLoad(userData, instr, "l.lhz");}
static OR1K_DISPATCH_FN(disLHS)   {doLoad(userData, instr, "l.lhs");}

//
// Handle store instructions
//
static OR1K_DISPATCH_FN(disSW)    {doStore(userData, instr, "l.sw");}
static OR1K_DISPATCH_FN(disSB)    {doStore(userData, instr, "l.sb");}
static OR1K_DISPATCH_FN(disSH)    {doStore(userData, instr, "l.sh");}

//
// Handle comparison instructions
//
static OR1K_DISPATCH_FN(disSF)    {doCompareReg(userData, instr, "l.sf%s");}
static OR1K_DISPATCH_FN(disSFI)   {doCompareLit(userData, instr, "l.sf%si");}

//
// Handle nop instruction
//
static OR1K_DISPATCH_FN(disNOP)   {doNop(userData, instr, "l.nop");}

//
// OR1K disassembler dispatch table
//
static or1kDispatchTableC dispatchTable = {

    // handle movhi instruction
    [OR1K_IT_MOVHI] = disMOVHI,

    // handle arithmetic instructions
    [OR1K_IT_ADDI]  = disADDI,
    [OR1K_IT_ADDIC] = disADDIC,
    [OR1K_IT_ANDI]  = disANDI,
    [OR1K_IT_ORI]   = disORI,
    [OR1K_IT_XORI]  = disXORI,
    [OR1K_IT_MULI]  = disMULI,

    // handle arithmetic instructions (second argument register)
    [OR1K_IT_ADD]   = disADD,
    [OR1K_IT_ADDC]  = disADDC,
    [OR1K_IT_SUB]   = disSUB,
    [OR1K_IT_AND]   = disAND,
    [OR1K_IT_OR]    = disOR,
    [OR1K_IT_XOR]   = disXOR,
    [OR1K_IT_MUL]   = disMUL,
    [OR1K_IT_DIV]   = disDIV,
    [OR1K_IT_DIVU]  = disDIVU,

    // handle shift/rotate instructions (second argument constant)
    [OR1K_IT_SLLI]  = disSLLI,
    [OR1K_IT_SRLI]  = disSRLI,
    [OR1K_IT_SRAI]  = disSRAI,
    [OR1K_IT_RORI]  = disRORI,

    // handle shift/rotate instructions (second argument register)
    [OR1K_IT_SLL]   = disSLL,
    [OR1K_IT_SRL]   = disSRL,
    [OR1K_IT_SRA]   = disSRA,
    [OR1K_IT_ROR]   = disROR,

    // handle branch instructions
    [OR1K_IT_BF]    = disBF,
    [OR1K_IT_BNF]   = disBNF,
    [OR1K_IT_J]     = disJ,
    [OR1K_IT_JR]    = disJR,
    [OR1K_IT_JAL]   = disJAL,
    [OR1K_IT_JALR]  = disJALR,

    // handle sys and rfe instructions
    [OR1K_IT_SYS]   = disSYS,
    [OR1K_IT_RFE]   = disRFE,

    // mtspr and mfspr instructions
    [OR1K_IT_MTSPR] = disMTSPR,
    [OR1K_IT_MFSPR] = disMFSPR,

    // handle load instructions
    [OR1K_IT_LWZ]   = disLWZ,
    [OR1K_IT_LWS]   = disLWS,
    [OR1K_IT_LBZ]   = disLBZ,
    [OR1K_IT_LBS]   = disLBS,
    [OR1K_IT_LHZ]   = disLHZ,
    [OR1K_IT_LHS]   = disLHS,

    // handle store instructions
    [OR1K_IT_SW]    = disSW,
    [OR1K_IT_SB]    = disSB,
    [OR1K_IT_SH]    = disSH,

    // handle comparison instructions
    [OR1K_IT_SF]    = disSF,
    [OR1K_IT_SFI]   = disSFI,

    // handle nop instruction
    [OR1K_IT_NOP]   = disNOP
};

//
// Default disassembler callback
//
static OR1K_DISPATCH_FN(disDefault) {

    // get output buffer for disassembly
    char *result = (char *)userData;

    // default disassembly just shows instruction pattern
    sprintf(result, "??? instruction:0x%08x", instr);
}

//
// OR1K disassembler
//
VMI_DISASSEMBLE_FN(or1kDisassemble) {

    // static buffer to hold disassembly result
    static char result[256];

    // disassemble, filling the result buffer
    or1kDecode(
        (or1kP)processor, thisPC, &dispatchTable, disDefault, &result, False
    );

    // return the result
    return result;
}

