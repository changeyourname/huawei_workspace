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

// VMI header files
#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"

// model header files
#include "or1kDecode.h"
#include "or1kInstructions.h"


//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(     \
        table,              \
        #_NAME,             \
        OR1K_IT_##_NAME,    \
        _FMT,               \
        _PRIORITY           \
    )

//
// Create the OR1K decode table
//
static vmidDecodeTableP createDecodeTable(void) {
    
    vmidDecodeTableP table = vmidNewDecodeTable(32, OR1K_IT_LAST);

    // handle arithmetic instructions (second argument constant)
    DECODE_ENTRY(0, ADDI,  "|100111..........................|");
    DECODE_ENTRY(0, ADDIC, "|101000..........................|");
    DECODE_ENTRY(0, ANDI,  "|101001..........................|");
    DECODE_ENTRY(0, ORI,   "|101010..........................|");
    DECODE_ENTRY(0, XORI,  "|101011..........................|");
    DECODE_ENTRY(0, MULI,  "|101100..........................|");

    // handle branch instructions
    DECODE_ENTRY(0, J,     "|000000..........................|");
    DECODE_ENTRY(0, JR,    "|010001..........................|");
    DECODE_ENTRY(0, JAL,   "|000001..........................|");
    DECODE_ENTRY(0, JALR,  "|010010..........................|");

    return table;
}

//
// Decode the instruction and return an enum describing it
//
static or1kInstructionType decode(Uns32 instruction) {

    // get the OR1K decode table
    static vmidDecodeTableP decodeTable;
    if(!decodeTable) {
        decodeTable = createDecodeTable();
    }

    // decode the instruction to get the type
    or1kInstructionType type = vmidDecode(decodeTable, instruction);

    return type;
}

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
) {
    // get the instruction at the passed address - always 4 bytes on OR1K
    vmiProcessorP       processor   = (vmiProcessorP)or1k;
    Uns32               instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kInstructionType type        = decode(instruction);

    // apply the callback, or the default if no match
    if(type!=OR1K_IT_LAST) {
        ((*table)[type])(or1k, thisPC, instruction, userData, inDelaySlot);
        return True;
    } else {
        defaultCB(or1k, thisPC, instruction, userData, inDelaySlot);
        return False;
    }
}

