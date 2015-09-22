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
#include "or1kInstructions.h"
#include "or1kFunctions.h"

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
// Handle arithmetic instructions
//
static OR1K_DISPATCH_FN(disADDI)  {doBinopSLit(userData, instr, "l.addi");}
static OR1K_DISPATCH_FN(disADDIC) {doBinopSLit(userData, instr, "l.addic");}
static OR1K_DISPATCH_FN(disANDI)  {doBinopULit(userData, instr, "l.andi");}
static OR1K_DISPATCH_FN(disORI)   {doBinopULit(userData, instr, "l.ori");}
static OR1K_DISPATCH_FN(disXORI)  {doBinopSLit(userData, instr, "l.xori");}
static OR1K_DISPATCH_FN(disMULI)  {doBinopSLit(userData, instr, "l.muli");}

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
    [OR1K_IT_MULI]  = disMULI
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
    or1kDecode((or1kP)processor, thisPC, &dispatchTable, disDefault, &result);

    // return the result
    return result;
}

