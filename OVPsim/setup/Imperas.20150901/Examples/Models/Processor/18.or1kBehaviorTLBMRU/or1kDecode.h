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

// Utility routines and structures for the OR1K decoder

#ifndef OR1KDECODE_H
#define OR1KDECODE_H

// basic number types
#include "hostapi/impTypes.h"

// VMI header files
#include "vmi/vmiTypes.h"

// model header files
#include "or1kStructure.h"

//
// Dispatcher callback type
//
#define OR1K_DISPATCH_FN(_NAME) void _NAME( \
    or1kP or1k,         \
    Uns32 thisPC,       \
    Uns32 instr,        \
    void *userData,     \
    Bool  inDelaySlot   \
)
typedef OR1K_DISPATCH_FN((*or1kDispatchFn));

//
// Instruction type enumeration
//
typedef enum or1kInstructionTypeE {

    // movhi instruction
    OR1K_IT_MOVHI,

    // arithmetic instructions (second argument constant)
    OR1K_IT_ADDI,
    OR1K_IT_ADDIC,
    OR1K_IT_ANDI,
    OR1K_IT_ORI,
    OR1K_IT_XORI,
    OR1K_IT_MULI,

    // arithmetic instructions (second argument register)
    OR1K_IT_ADD,
    OR1K_IT_ADDC,
    OR1K_IT_SUB,
    OR1K_IT_AND,
    OR1K_IT_OR,
    OR1K_IT_XOR,
    OR1K_IT_MUL,
    OR1K_IT_DIV,
    OR1K_IT_DIVU,

    // shift/rotate instructions (second argument constant)
    OR1K_IT_SLLI,
    OR1K_IT_SRLI,
    OR1K_IT_SRAI,
    OR1K_IT_RORI,

    // shift/rotate instructions (second argument register)
    OR1K_IT_SLL,
    OR1K_IT_SRL,
    OR1K_IT_SRA,
    OR1K_IT_ROR,

    // branch instructions
    OR1K_IT_BF,
    OR1K_IT_BNF,
    OR1K_IT_J,
    OR1K_IT_JR,
    OR1K_IT_JAL,
    OR1K_IT_JALR,

    // sys and rfe instructions
    OR1K_IT_SYS,
    OR1K_IT_RFE,

    // mtspr and mfspr instructions
    OR1K_IT_MTSPR,
    OR1K_IT_MFSPR,

    // load instructions
    OR1K_IT_LWZ,
    OR1K_IT_LWS,
    OR1K_IT_LBZ,
    OR1K_IT_LBS,
    OR1K_IT_LHZ,
    OR1K_IT_LHS,

    // store instructions
    OR1K_IT_SW,
    OR1K_IT_SB,
    OR1K_IT_SH,

    // comparison instructions
    OR1K_IT_SF,
    OR1K_IT_SFI,

    // nop instruction
    OR1K_IT_NOP,

    // KEEP LAST: for sizing the array
    OR1K_IT_LAST

} or1kInstructionType;

//
// Dispatch table
//
typedef const or1kDispatchFn or1kDispatchTableC[OR1K_IT_LAST];
typedef or1kDispatchTableC *or1kDispatchTableCP;

//
// Return the type string for a specific OR1K comparison operation, or NULL
// if the operation is invalid
//
const char *or1kDecodeCmpName(Uns32 instruction);

//
// Return the equivalent vmiCondition for a specific OR1K comparison operation,
// or vmi_COND_Z if the operation is invalid
//
vmiCondition or1kDecodeCmpCondition(Uns32 instruction);

//
// Decode the OR1K instruction at the passed address. If the decode succeeds,
// dispatch it to the corresponding function in the dispatch table and return
// True; otherwise, dispatch using the defaultCB and return False.
//
Bool or1kDecode(
    or1kP               or1k,
    Uns32               thisPC,
    or1kDispatchTableCP table,
    or1kDispatchFn      defaultCB,
    void               *userData,
    Bool                inDelaySlot
);

#endif

