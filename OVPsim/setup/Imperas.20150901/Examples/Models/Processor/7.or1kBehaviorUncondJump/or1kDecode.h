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

    // arithmetic instructions
    OR1K_IT_ADDI,
    OR1K_IT_ADDIC,
    OR1K_IT_ANDI,
    OR1K_IT_ORI,
    OR1K_IT_XORI,
    OR1K_IT_MULI,

    // handle branch instructions
    OR1K_IT_J,
    OR1K_IT_JR,
    OR1K_IT_JAL,
    OR1K_IT_JALR,

    // KEEP LAST: for sizing the array
    OR1K_IT_LAST

} or1kInstructionType;

//
// Dispatch table
//
typedef const or1kDispatchFn or1kDispatchTableC[OR1K_IT_LAST];
typedef or1kDispatchTableC *or1kDispatchTableCP;

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

