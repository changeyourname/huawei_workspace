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
#include "vmi/vmiTypes.h"

// model header files
#include "or1kDecode.h"
#include "or1kInstructions.h"

//
// This type supplies comparison type information for SF and SFI instructions
//
typedef struct cmpInfoS {
    const char  *name;  // comparison operation name (for disassembly)
    vmiCondition cond;  // equivalent VMI condition code
} cmpInfo;

//
// Lookup table mapping from cmpOp (0..15) to cmpInfo
//
const static cmpInfo cmpLut[16] = {
    {"eq",  vmi_COND_Z  },  // 0x0: a == b
    {"ne",  vmi_COND_NZ },  // 0x1: a != b
    {"gtu", vmi_COND_NBE},  // 0x2: a >  b (unsigned)
    {"geu", vmi_COND_NB },  // 0x3: a >= b (unsigned)
    {"ltu", vmi_COND_B  },  // 0x4: a <  b (unsigned)
    {"leu", vmi_COND_BE },  // 0x5: a <= b (unsigned)
    {0,     vmi_COND_Z  },  // 0x6: invalid
    {0,     vmi_COND_Z  },  // 0x7: invalid
    {0,     vmi_COND_Z  },  // 0x8: invalid
    {0,     vmi_COND_Z  },  // 0x9: invalid
    {"gts", vmi_COND_NLE},  // 0xa: a >  b (signed)
    {"ges", vmi_COND_NL },  // 0xb: a >= b (signed)
    {"lts", vmi_COND_L  },  // 0xc: a <  b (signed)
    {"les", vmi_COND_LE },  // 0xd: a <= b (signed)
    {0,     vmi_COND_Z  },  // 0xe: invalid
    {0,     vmi_COND_Z  }   // 0xf: invalid
};

//
// Return a cmpInfo structure for a specific OR1K comparison operation. The
// name field is NULL if the operation is invalid.
//
static const cmpInfo *getCmpInfo(Uns32 cmpOp) {
    return &cmpLut[cmpOp];
}

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
    
    vmidDecodeTableP table = vmidNewDecodeTable(OR1K_BITS, OR1K_IT_LAST);

    // handle movhi instruction
    DECODE_ENTRY(0, MOVHI, "|000110.........0................|");

    // handle arithmetic instructions (second argument constant)
    DECODE_ENTRY(0, ADDI,  "|100111..........................|");
    DECODE_ENTRY(0, ADDIC, "|101000..........................|");
    DECODE_ENTRY(0, ANDI,  "|101001..........................|");
    DECODE_ENTRY(0, ORI,   "|101010..........................|");
    DECODE_ENTRY(0, XORI,  "|101011..........................|");
    DECODE_ENTRY(0, MULI,  "|101100..........................|");

    // handle arithmetic instructions (second argument register)
    DECODE_ENTRY(0, ADD,   "|111000................00....0000|");
    DECODE_ENTRY(0, ADDC,  "|111000................00....0001|");
    DECODE_ENTRY(0, SUB,   "|111000................00....0010|");
    DECODE_ENTRY(0, AND,   "|111000................00....0011|");
    DECODE_ENTRY(0, OR,    "|111000................00....0100|");
    DECODE_ENTRY(0, XOR,   "|111000................00....0101|");
    DECODE_ENTRY(0, MUL,   "|111000................11....0110|");
    DECODE_ENTRY(0, DIV,   "|111000................11....1001|");
    DECODE_ENTRY(0, DIVU,  "|111000................11....1010|");

    // handle shift/rotate instructions (second argument constant)
    DECODE_ENTRY(0, SLLI,  "|101110..................00......|");
    DECODE_ENTRY(0, SRLI,  "|101110..................01......|");
    DECODE_ENTRY(0, SRAI,  "|101110..................10......|");
    DECODE_ENTRY(0, RORI,  "|101110..................11......|");

    // handle shift/rotate instructions (second argument register)
    DECODE_ENTRY(0, SLL,   "|111000................0000..1000|");
    DECODE_ENTRY(0, SRL,   "|111000................0001..1000|");
    DECODE_ENTRY(0, SRA,   "|111000................0010..1000|");
    DECODE_ENTRY(0, ROR,   "|111000................0011..1000|");

    // handle branch instructions
    DECODE_ENTRY(0, BF,    "|000100..........................|");
    DECODE_ENTRY(0, BNF,   "|000011..........................|");
    DECODE_ENTRY(0, J,     "|000000..........................|");
    DECODE_ENTRY(0, JR,    "|010001..........................|");
    DECODE_ENTRY(0, JAL,   "|000001..........................|");
    DECODE_ENTRY(0, JALR,  "|010010..........................|");

    // handle load instructions
    DECODE_ENTRY(0, LWZ,   "|100001..........................|");
    DECODE_ENTRY(0, LWS,   "|100010..........................|");
    DECODE_ENTRY(0, LBZ,   "|100011..........................|");
    DECODE_ENTRY(0, LBS,   "|100100..........................|");
    DECODE_ENTRY(0, LHZ,   "|100101..........................|");
    DECODE_ENTRY(0, LHS,   "|100110..........................|");

    // handle store instructions
    DECODE_ENTRY(0, SW,    "|110101..........................|");
    DECODE_ENTRY(0, SB,    "|110110..........................|");
    DECODE_ENTRY(0, SH,    "|110111..........................|");

    // handle comparison instructions
    DECODE_ENTRY(0, SF,    "|1110010.........................|");
    DECODE_ENTRY(0, SFI,   "|1011110.........................|");

    // handle nop instruction
    DECODE_ENTRY(0, NOP,   "|00010101........................|");

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

    // some arguments to l.sf and l.sfi are invalid: filter them here
    if((type==OR1K_IT_SF) && !getCmpInfo(OP5_CMPOP(instruction))->name) {
        type = OR1K_IT_LAST;
    } else if((type==OR1K_IT_SFI) && !getCmpInfo(OP6_CMPOP(instruction))->name) {
        type = OR1K_IT_LAST;
    }

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

//
// Return the type string for a specific OR1K comparison operation, or NULL
// if the operation is invalid
//
const char *or1kDecodeCmpName(Uns32 instruction) {
    switch(decode(instruction)) {
        case OR1K_IT_SF:
            return getCmpInfo(OP5_CMPOP(instruction))->name;
        case OR1K_IT_SFI:
            return getCmpInfo(OP6_CMPOP(instruction))->name;
        default:
            return 0;
    }
}

//
// Return the equivalent vmiCondition for a specific OR1K comparison operation,
// or vmi_COND_Z if the operation is invalid
//
vmiCondition or1kDecodeCmpCondition(Uns32 instruction) {
    switch(decode(instruction)) {
        case OR1K_IT_SF:
            return getCmpInfo(OP5_CMPOP(instruction))->cond;
        case OR1K_IT_SFI:
            return getCmpInfo(OP6_CMPOP(instruction))->cond;
        default:
            return vmi_COND_Z;
    }
}
