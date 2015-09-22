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

// VMI area includes
#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"


#define OR1K_GPR_NUM 32
#define OR1K_BITS    32

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

//
// Field extraction macros
//
#define WIDTH(_W, _ARG) ((_ARG) & ((1<<(_W))-1))
#define OPEX_A(_I)      WIDTH(5,(_I)>>16)
#define OPEX_B(_I)      WIDTH(5,(_I)>>11)
#define OPEX_I(_I)      ((WIDTH(5,(_I)>>21)<<11) | WIDTH(11,(_I)>>0))


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

typedef struct vmiosObjectS {

    // handles for the OR1K GPRs
    vmiRegInfoCP regs[OR1K_GPR_NUM];

    // enhanced instruction decode table
    vmidDecodeTableP table;

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// ENHANCED DECODER
////////////////////////////////////////////////////////////////////////////////

//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(     \
        table,              \
        #_NAME,             \
        OR1K_EIT_##_NAME,   \
        _FMT,               \
        _PRIORITY           \
    )

//
// Enhanced nstruction type enumeration
//
typedef enum or1kEnhancedInstrTypeE {

    // exchange instruction
    OR1K_EIT_EXW,

    // KEEP LAST: for sizing the array
    OR1K_EIT_LAST

} or1kEnhancedInstrType;

//
// Create the OR1K decode table
//
static vmidDecodeTableP createDecodeTable(void) {

    vmidDecodeTableP table = vmidNewDecodeTable(OR1K_BITS, OR1K_EIT_LAST);

    // handle exchnage instruction
    DECODE_ENTRY(0, EXW, "|111101..........................|");

    return table;
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    Uns32 i;

    // get handles to the OR1K GPRs
    for(i=0; i<OR1K_GPR_NUM; i++) {
        char regName[8];
        sprintf(regName, "R%u", i);
        object->regs[i] = vmiosGetRegDesc(processor, regName);
    }

    // create enhanced instruction decoder
    object->table = createDecodeTable();
}


////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF ENHANCED EXCHANGE INSTRUCTION
////////////////////////////////////////////////////////////////////////////////

//
// Byte swap the passed value
//
inline static Uns32 swap4(Uns32 value) {

    union {Uns32 v32; Uns8 v8[4];} u = {value};

    Uns8 tmp1 = u.v8[0];
    Uns8 tmp2 = u.v8[1];
    u.v8[0]   = u.v8[3];
    u.v8[1]   = u.v8[2];
    u.v8[2]   = tmp2;
    u.v8[3]   = tmp1;

    return u.v32;
}

//
// Morpher callback implementing exchange instructions
//
static VMIOS_INTERCEPT_FN(doExchange) {

    // get processor data domain and endianness
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    // recover instruction
    Uns32 instruction = (UnsPS)userData;

    // extract instruction fields
    Uns32 ra = OPEX_A(instruction);
    Uns32 rb = OPEX_B(instruction);
    Int16 i  = OPEX_I(instruction);

    // get old value of rb register
    Uns32 rbOld;
    vmiosRegRead(processor, object->regs[rb], &rbOld);

    // get value of ra register (address)
    Uns32 raValue;
    vmiosRegRead(processor, object->regs[ra], &raValue);

    // get new value of rb register
    Uns32 rbNew;
    vmirtReadNByteDomain(domain, raValue+i, &rbNew, sizeof(rbNew), 0, True);

    // swap rbOld and rbNew endianness if required
    if(endian != ENDIAN_NATIVE) {
        rbOld = swap4(rbOld);
        rbNew = swap4(rbNew);
    }

    // write old value of rb register
    vmirtWriteNByteDomain(domain, raValue+i, &rbOld, sizeof(rbOld), 0, True);

    // update rb register in processor model
    vmiosRegWrite(processor, object->regs[rb], &rbNew);
}

//
// Morpher callback implementing exchange instructions
//
static VMIOS_MORPH_FN(exchangeMorph) {

    // decode the instruction to get the type
    UnsPS                 instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if(type==OR1K_EIT_EXW) {

        // instruction is enhanced exchange
        *opaque   = True;
        *userData = (void *)instruction;
        return doExchange;

    } else {

        // instruction not enhanced exchange
        return 0;
    }
}

//
// Return instruction address after passed program counter
//
static VMIOS_NEXT_PC_FN(exchangeNextPC) {

    // decode the instruction to get the type
    Uns32                 instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if(type==OR1K_EIT_EXW) {
        *nextPC = thisPC+4;
        return True;
    } else {
        return False;
    }
}

//
// Disassembler callback disassembling exchange instructions
//
static VMIOS_DISASSEMBLE_FN(exchangeDisass) {

    // decode the instruction to get the type
    Uns32                 instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if(type==OR1K_EIT_EXW) {

        // instruction is enhanced exchange
        static char buffer[256];

        // extract instruction fields
        Uns32 ra = OPEX_A(instruction);
        Uns32 rb = OPEX_B(instruction);
        Int16 i  = OPEX_I(instruction);

        sprintf(buffer, "%-8s 0x%x(r%u),r%u", "l.exw", i, ra, rb);

        return buffer;

    } else {

        // instruction not enhanced exchange
        return 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,            // version string
    .modelType     = VMI_INTERCEPT_LIBRARY,  // type
    .packageName   = "Exchange",             // description
    .objectSize    = sizeof(vmiosObject),    // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = constructor,            // object constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = exchangeMorph,          // morph callback
    .nextPCCB      = exchangeNextPC,         // get next instruction address
    .disCB         = exchangeDisass,         // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};

