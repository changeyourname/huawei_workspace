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
// OR1K disassembler dispatch table
//
static or1kDispatchTableC dispatchTable = {

    // handle arithmetic instructions
    [OR1K_IT_ADDI]  = disDefault,
    [OR1K_IT_ADDIC] = disDefault,
    [OR1K_IT_ANDI]  = disDefault,
    [OR1K_IT_ORI]   = disDefault,
    [OR1K_IT_XORI]  = disDefault,
    [OR1K_IT_MULI]  = disDefault
};

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

