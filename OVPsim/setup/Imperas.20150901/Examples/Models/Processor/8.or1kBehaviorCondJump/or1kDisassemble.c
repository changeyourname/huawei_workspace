/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
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
// Disassemble a binary/signed literal OR1K instruction
//
static void doBinopSLit(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP2_D(instr);
    Uns32 ra = OP2_A(instr);
    Int16 i  = OP2_I(instr);

    sprintf(buffer, "%-8s r%u,r%u,0x%x", or1kop, rd, ra, i);
}

//
// Disassemble a binary/unsigned literal OR1K instruction
//
static void doBinopULit(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP2_D(instr);
    Uns32 ra = OP2_A(instr);
    Uns16 k  = OP2_I(instr);

    sprintf(buffer, "%-8s r%u,r%u,0x%x", or1kop, rd, ra, k);
}

//
// Disassemble a binary/register OR1K instruction
//
static void doBinopReg(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rd = OP1_D(instr);
    Uns32 ra = OP1_A(instr);
    Uns32 rb = OP1_B(instr);

    sprintf(buffer, "%-8s r%u,r%u,r%u", or1kop, rd, ra, rb);
}

//
// Disassemble a branch or jump instruction.
//
static void doBranchJump(char *buffer, Uns32 thisPC, Uns32 instr, char *or1kop){

    Int32 n         = OP7_N(instr);
    Int32 offset    = ((n<<6) >> 4);
    Uns32 toAddress = thisPC + offset;

    sprintf(buffer, "%-8s 0x%08x", or1kop, toAddress);
}

//
// Disassemble an indirect jump instruction
//
static void doJumpReg(char *buffer, Uns32 instr, char *or1kop) {

    Uns32 rb = OP8_B(instr);

    sprintf(buffer, "%-8s r%u", or1kop, rb);
}

//
// Disassemble a register comparison instruction
//
static void doCompareReg(char *buffer, Uns32 instr, char *or1kopFmt) {

    Uns32 ra = OP5_A(instr);
    Uns32 rb = OP5_B(instr);
    char  opBuf[16];

    sprintf(opBuf, or1kopFmt, or1kDecodeCmpName(instr));
    sprintf(buffer, "%-8s r%u,r%u", opBuf, ra, rb);
}

//
// Disassemble a literal comparison instruction
//
static void doCompareLit(char *buffer, Uns32 instr, char *or1kopFmt) {

    Uns32 ra = OP6_A(instr);
    Int16 i  = OP6_I(instr);
    char  opBuf[16];

    sprintf(opBuf, or1kopFmt, or1kDecodeCmpName(instr));
    sprintf(buffer, "%-8s r%u,0x%x", opBuf, ra, i);
}

//
// Disassemble a OR1K NOP instruction
//
static void doNop(char *buffer, Uns32 instr, char *or1kop) {
    sprintf(buffer, "%-8s 0x%x", or1kop, OP3_I(instr));
}

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
// Handle branch instructions
//
static OR1K_DISPATCH_FN(disBF)    {doBranchJump(userData, thisPC, instr, "l.bf");}
static OR1K_DISPATCH_FN(disBNF)   {doBranchJump(userData, thisPC, instr, "l.bnf");}
static OR1K_DISPATCH_FN(disJ)     {doBranchJump(userData, thisPC, instr, "l.j");}
static OR1K_DISPATCH_FN(disJR)    {doJumpReg(userData, instr, "l.jr");}
static OR1K_DISPATCH_FN(disJAL)   {doBranchJump(userData, thisPC, instr, "l.jal");}
static OR1K_DISPATCH_FN(disJALR)  {doJumpReg(userData, instr, "l.jalr");}

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

    // handle branch instructions
    [OR1K_IT_BF]    = disBF,
    [OR1K_IT_BNF]   = disBNF,
    [OR1K_IT_J]     = disJ,
    [OR1K_IT_JR]    = disJR,
    [OR1K_IT_JAL]   = disJAL,
    [OR1K_IT_JALR]  = disJALR,

    // handle comparison instructions
    [OR1K_IT_SF]    = disSF,
    [OR1K_IT_SFI]   = disSFI,

    // handle nop instruction
    [OR1K_IT_NOP]   = disNOP
};

//
// Default disassembler callback
//
OR1K_DISPATCH_FN(disDefault) {

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

