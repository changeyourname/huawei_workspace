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
// Emit code to implement a binary/signed literal OR1K instruction
//
static void doBinopSLit(Uns32 instr, vmiBinop op) {

    Uns32  rd     = OP2_D(instr);
    Uns32  ra     = OP2_A(instr);
    Int16  i      = OP2_I(instr);
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    if(ra==0) {
        vmimtBinopRCC(OR1K_BITS, op, target, 0, i, 0);
    } else {
        vmimtBinopRRC(OR1K_BITS, op, target, OR1K_REG(ra), i, 0);
    }
}

//
// Emit code to implement a binary/unsigned literal OR1K instruction
//
static void doBinopULit(Uns32 instr, vmiBinop op) {

    Uns32  rd     = OP2_D(instr);
    Uns32  ra     = OP2_A(instr);
    Uns16  k      = OP2_I(instr);
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    if(ra==0) {
        vmimtBinopRCC(OR1K_BITS, op, target, 0, k, 0);
    } else {
        vmimtBinopRRC(OR1K_BITS, op, target, OR1K_REG(ra), k, 0);
    }
}

//
// Handle arithmetic instructions
//
static OR1K_DISPATCH_FN(morphADDI)  {doBinopSLit(instr, vmi_ADD);}
static OR1K_DISPATCH_FN(morphADDIC) {doBinopSLit(instr, vmi_ADC);}
static OR1K_DISPATCH_FN(morphANDI)  {doBinopULit(instr, vmi_AND);}
static OR1K_DISPATCH_FN(morphORI)   {doBinopULit(instr, vmi_OR);}
static OR1K_DISPATCH_FN(morphXORI)  {doBinopSLit(instr, vmi_XOR);}
static OR1K_DISPATCH_FN(morphMULI)  {doBinopSLit(instr, vmi_IMUL);}

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
    [OR1K_IT_MULI]  = morphMULI
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
    or1kDecode((or1kP)processor, thisPC, &dispatchTable, morphDefault, 0);
}

