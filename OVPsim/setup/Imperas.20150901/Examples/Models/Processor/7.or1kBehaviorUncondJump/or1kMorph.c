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
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kDecode.h"
#include "or1kFunctions.h"
#include "or1kInstructions.h"
#include "or1kStructure.h"

//
// Update carry & overflow flags
//
const vmiFlags flagsCO = {
    OR1K_CARRY_CONST,           // offset to carry in flag
    {
        OR1K_CARRY_CONST,       // offset to carry out flag
        VMI_NOFLAG_CONST,       // parity flag not used
        VMI_NOFLAG_CONST,       // zero flag not used
        VMI_NOFLAG_CONST,       // sign flag not used
        OR1K_OVERFLOW_CONST     // offset to overflow flag
    }
};

//
// Emit code to implement a binary/signed literal OR1K instruction
//
static void doBinopSLit(Uns32 instr, vmiBinop op, vmiFlagsCP flags) {

    Uns32  rd     = OP2_D(instr);
    Uns32  ra     = OP2_A(instr);
    Int16  i      = OP2_I(instr);
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    if(ra==0) {
        vmimtBinopRCC(OR1K_BITS, op, target, 0, i, flags);
    } else {
        vmimtBinopRRC(OR1K_BITS, op, target, OR1K_REG(ra), i, flags);
    }
}

//
// Emit code to implement a binary/unsigned literal OR1K instruction
//
static void doBinopULit(Uns32 instr, vmiBinop op, vmiFlagsCP flags) {

    Uns32  rd     = OP2_D(instr);
    Uns32  ra     = OP2_A(instr);
    Uns16  k      = OP2_I(instr);
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    if(ra==0) {
        vmimtBinopRCC(OR1K_BITS, op, target, 0, k, flags);
    } else {
        vmimtBinopRRC(OR1K_BITS, op, target, OR1K_REG(ra), k, flags);
    }
}

//
// Emit code for a jump instruction
//
static void doJump(
    Uns32 instr,
    Uns32 thisPC,
    Bool  link,
    Bool  inDelaySlot
) {
    Int32       n           = OP7_N(instr);
    Int32       offset      = ((n<<6) >> 4);
    Uns32       toAddress   = thisPC + offset;
    Uns32       nextAddress = thisPC + 8;
    vmiReg      linkReg     = link ? OR1K_LINKREG : VMI_NOREG;
    vmiJumpHint hint;

    // select an appropriate jump hint
    if(link) {
        hint = vmi_JH_CALL;
    } else {
        hint = vmi_JH_NONE;
    }

    if(inDelaySlot) {
        // jump in the delay slot does nothing
    } else {
        vmimtUncondJumpDelaySlot(
            1,                  // slotOps
            nextAddress,        // linkPC
            toAddress,          // toAddress
            linkReg,            // linkReg
            hint,               // hint
            0                   // slotCB
        );
    }
}

//
// Emit code for an indirect jump instruction
//
static void doJumpReg(
    Uns32 instr,
    Uns32 thisPC,
    Bool  link,
    Bool  inDelaySlot
) {
    Uns32       rb          = OP8_B(instr);
    Uns32       nextAddress = thisPC + 8;
    vmiReg      linkReg     = link ? OR1K_LINKREG : VMI_NOREG;
    vmiJumpHint hint;

    // select an appropriate jump hint
    if(link) {
        hint = vmi_JH_CALL;
    } else if(rb==OR1K_LINK) {
        hint = vmi_JH_RETURN;
    } else {
        hint = vmi_JH_NONE;
    }

    if(inDelaySlot) {
        // jump in the delay slot does nothing
    } else {
        vmimtUncondJumpRegDelaySlot(
            1,                  // slotOps
            nextAddress,        // linkPC
            OR1K_REG(rb),       // toReg
            linkReg,            // linkReg
            hint,               // hint
            0                   // slotCB
        );
    }
}

//
// Handle arithmetic instructions
//
static OR1K_DISPATCH_FN(morphADDI)  {doBinopSLit(instr, vmi_ADD,  &flagsCO);}
static OR1K_DISPATCH_FN(morphADDIC) {doBinopSLit(instr, vmi_ADC,  &flagsCO);}
static OR1K_DISPATCH_FN(morphANDI)  {doBinopULit(instr, vmi_AND,  0);}
static OR1K_DISPATCH_FN(morphORI)   {doBinopULit(instr, vmi_OR,   0);}
static OR1K_DISPATCH_FN(morphXORI)  {doBinopSLit(instr, vmi_XOR,  0);}
static OR1K_DISPATCH_FN(morphMULI)  {doBinopSLit(instr, vmi_IMUL, &flagsCO);}

//
// Handle branch instructions
//
static OR1K_DISPATCH_FN(morphJ)     {doJump(instr, thisPC, False, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJR)    {doJumpReg(instr, thisPC, False, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJAL)   {doJump(instr, thisPC, True, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJALR)  {doJumpReg(instr, thisPC, True, inDelaySlot);}

//
// OR1K morpher dispatch table
//
static or1kDispatchTableC dispatchTable = {

    // handle arithmetic instructions
    [OR1K_IT_ADDI]  = morphADDI,
    [OR1K_IT_ADDIC] = morphADDIC,
    [OR1K_IT_ANDI]  = morphANDI,
    [OR1K_IT_ORI]   = morphORI,
    [OR1K_IT_XORI]  = morphXORI,
    [OR1K_IT_MULI]  = morphMULI,

    // handle branch instructions
    [OR1K_IT_J]     = morphJ,
    [OR1K_IT_JR]    = morphJR,
    [OR1K_IT_JAL]   = morphJAL,
    [OR1K_IT_JALR]  = morphJALR,
};

//
// Called for an undecoded instruction
//
static void undecoded(
    vmiProcessorP processor,
    Uns32         thisPC,
    Uns32         instruction
) {
    // report that undecoded instruction was encountered
    vmiPrintf(
        "CPU '%s' 0x%08x:0x%08x *** undecoded instruction: exiting ***\n",
        vmirtProcessorName(processor),
        thisPC,
        instruction
    );

    // exit the CPU
    vmirtExit(processor);
}

//
// Default morpher callback
//
static OR1K_DISPATCH_FN(morphDefault) {

    // print message warning about the undecoded instruction
    vmimtArgProcessor();
    vmimtArgUns32((Uns32)thisPC);
    vmimtArgUns32(instr);
    vmimtCall((vmiCallFn)undecoded);
}

//
// Create code for the OR1K instruction at the simulated address referenced
// by 'thisPC'.
//
VMI_MORPH_FN(or1kMorphInstruction) {
    or1kDecode(
        (or1kP)processor, thisPC, &dispatchTable, morphDefault, 0, inDelaySlot
    );
}

