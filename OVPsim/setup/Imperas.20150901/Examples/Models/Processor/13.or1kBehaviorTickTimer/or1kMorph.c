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
#include "or1kExceptions.h"
#include "or1kFunctions.h"
#include "or1kInstructions.h"
#include "or1kSPR.h"
#include "or1kStructure.h"
#include "or1kUtils.h"


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
// Set temporary flag if zero
//
const vmiFlags flagsTZ = {
    VMI_NOFLAG_CONST,           // carry in flag not used
    {
        VMI_NOFLAG_CONST,       // carry out flag not used
        VMI_NOFLAG_CONST,       // parity flag not used
        OR1K_TEMPFLAG_CONST,    // offset to zero flag
        VMI_NOFLAG_CONST,       // sign flag not used
        VMI_NOFLAG_CONST        // overflow flag not used
    }
};

//
// Emit code for a OR1K movhi instruction
//
static void doMovHi(Uns32 instr) {

    Uns32 rd = OP4_D(instr);
    Uns16 i  = OP4_I(instr);

    if(rd==0) {
        // attempt to write to r0 shouldn't do anything
    } else {
        vmimtMoveRC(OR1K_BITS, OR1K_REG(rd), i<<16);
    }
}

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
// Emit code for a binary/register OR1K instruction
//
static void doBinopReg(Uns32 instr, vmiBinop op, vmiFlagsCP flags) {

    Uns32  rd     = OP1_D(instr);
    Uns32  ra     = OP1_A(instr);
    Uns32  rb     = OP1_B(instr);
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    if(rb==0) {
        vmimtBinopRRC(OR1K_BITS, op, target, OR1K_REG(ra), 0, flags);
    } else {
        vmimtBinopRRR(OR1K_BITS, op, target, OR1K_REG(ra), OR1K_REG(rb), flags);
    }
}

//
// Emit code for a shift/literal OR1K instruction
//
static void doShiftopLit(Uns32 instr, vmiBinop op, vmiFlagsCP flags) {

    Uns32  rd     = OP9_D(instr);
    Uns32  ra     = OP9_A(instr);
    Int16  l      = OP9_L(instr) & 0x1f;
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    vmimtBinopRRC(OR1K_BITS, op, target, OR1K_REG(ra), l, flags);

}

//
// Emit code for a shift/register OR1K instruction
//
static void doShiftopReg(Uns32 instr, vmiBinop op, vmiFlagsCP flags) {

    Uns32  rd     = OP12_D(instr);
    Uns32  ra     = OP12_A(instr);
    Uns32  rb     = OP12_B(instr);
    vmiReg target = (rd==0) ? VMI_NOREG : OR1K_REG(rd);

    vmimtBinopRRR(OR1K_BITS, op, target, OR1K_REG(ra), OR1K_REG(rb), flags);
}

//
// Emit code for a branch instruction.
//
static void doBranch(
    Uns32 instr,
    Uns32 thisPC,
    Bool  jumpIfTrue,
    Bool  inDelaySlot
) {
    Int32 n         = OP7_N(instr);
    Int32 offset    = ((n<<6) >> 4);
    Uns32 toAddress = thisPC + offset;

    if(inDelaySlot) {
        // jump in the delay slot does nothing
    } else {
        vmimtCondJumpDelaySlot(
            1,                  // slotOps
            OR1K_BRANCH,        // flagReg
            jumpIfTrue,         // jumpIfTrue
            0,                  // linkPC
            toAddress,          // toAddress
            VMI_NOREG,          // linkReg
            vmi_JH_NONE,        // hint
            0                   // slotCB
        );
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
// Emit code for a sys instruction
//
static void doSYS(Uns32 instr, Uns32 thisPC) {

    vmimtArgProcessor();
    vmimtArgUns32(OR1K_EXCPT_SYS);
    vmimtArgUns32(4);
    vmimtCall((vmiCallFn)or1kTakeException);

    // terminate the current code block
    vmimtEndBlock();
}

//
// Emit code for an rfe instruction
//
static void doRFE(or1kP or1k) {

    if(IN_SUPERVISOR_MODE(or1k)) {

        // set sr from esr (must call or1kSetSR to do this)
        vmimtArgProcessor();
        vmimtArgReg(OR1K_BITS, OR1K_ESR);
        vmimtCall((vmiCallFn)or1kSetSR);

        // return to exception program counter
        vmimtUncondJumpReg(0, OR1K_EPC, VMI_NOREG, vmi_JH_RETURNINT);

    } else {

        // take illegal instruction exception
        vmimtArgProcessor();
        vmimtArgUns32(OR1K_EXCPT_ILL);
        vmimtArgUns32(0);
        vmimtCall((vmiCallFn)or1kTakeException);
    }
}

//
// Return endianness of this model
//
static memEndian getEndian(void) {
    return MEM_ENDIAN_BIG;
}

//
// Emit code to load from an address
//
static void doLoad(Uns32 instr, Uns32 bytes, Bool signExtend) {

    Uns32     rd     = OP2_D(instr);
    Uns32     ra     = OP2_A(instr);
    Int16     i      = OP2_I(instr);
    memEndian endian = getEndian();
    vmiReg    rdReg  = rd ? OR1K_REG(rd) : VMI_NOREG;
    vmiReg    raReg  = ra ? OR1K_REG(ra) : VMI_NOREG;

    vmimtLoadRRO(
        OR1K_BITS,      // destBits
        bytes*8,        // memBits
        i,              // offset
        rdReg,          // rd
        raReg,          // ra
        endian,         // endian
        signExtend,     // signExtend
        True            // checkAlign
    );
}

//
// Emit code to store to an address
//
static void doStore(Uns32 instr, Uns32 bytes) {

    Uns32     ra     = OP10_A(instr);
    Uns32     rb     = OP10_B(instr);
    Int16     i      = OP10_I(instr);
    memEndian endian = getEndian();
    vmiReg    raReg  = ra ? OR1K_REG(ra) : VMI_NOREG;

    if(rb==0) {
        vmimtStoreRCO(
            bytes*8,        // bits
            i,              // offset
            raReg,          // ra
            0,              // c
            endian,         // endian
            True            // checkAlign
        );
    } else {
        vmimtStoreRRO(
            bytes*8,        // bits
            i,              // offset
            raReg,          // ra
            OR1K_REG(rb),   // rb
            endian,         // endian
            True            // checkAlign
        );
    }
}

//
// Emit code for a literal comparison instruction
//
static void doCompareLit(Uns32 instr) {

    Uns32        ra   = OP6_A(instr);
    Int16        i    = OP6_I(instr);
    vmiCondition cond = or1kDecodeCmpCondition(instr);

    vmimtCompareRC(OR1K_BITS, cond, OR1K_REG(ra), i, OR1K_BRANCH);
}

//
// Emit code for a register comparison instruction
//
static void doCompareReg(Uns32 instr) {

    Uns32        ra   = OP5_A(instr);
    Uns32        rb   = OP5_B(instr);
    vmiCondition cond = or1kDecodeCmpCondition(instr);

    if(rb==0) {
        vmimtCompareRC(
            OR1K_BITS, cond, OR1K_REG(ra), 0, OR1K_BRANCH
        );
    } else {
        vmimtCompareRR(
            OR1K_BITS, cond, OR1K_REG(ra), OR1K_REG(rb), OR1K_BRANCH
        );
    }
}

//
// Return string description of spr group
//
const static char *sprDescription(Uns32 spr) {

    // lookup table of group descriptions
    static const char *descriptions[] = {
        "SYS",  "DMMU", "IMMU", "DC",
        "IC",   "MAC",  "D",    "PC",
        "PM",   "PIC",  "TT",   "FPU"
    };

    // number of entries in the table
    Uns32 descNum = sizeof(descriptions)/sizeof(descriptions[0]);

    // extract group number from spr
    Uns32 group = spr >> 11;

    return (group<descNum) ? descriptions[group] : "Unknown";
}

//
// Issue warning for unimplemented mtspr target
//
static void ignoreMTSPR(
    Uns32 thisPC,
    Uns32 ra,
    Uns32 rb,
    Uns32 k,
    Uns32 sprNum
) {
    vmiMessage("W", "OR1K_MTSPR",
        "%08x: ignoring 'l.mtspr r%u,r%u,0x%x (spr 0x%x %s)'\n",
        thisPC, ra, rb, k, sprNum, sprDescription(sprNum)
    );
}

//
// Issue warning for unimplemented mfspr target
//
static void ignoreMFSPR(
    Uns32 thisPC,
    Uns32 rd,
    Uns32 ra,
    Uns32 k,
    Uns32 sprNum
) {
    vmiMessage("W", "OR1K_MFSPR",
        "%08x: assuming 'l.mfspr r%u,r%u,%u (spr 0x%x %s)' returns 0\n",
        thisPC, rd, ra, k, sprNum, sprDescription(sprNum)
    );
}

//
// Run-time implementation of mtspr with sr register
//
static void vmic_MTSPR_SYS_SR(or1kP or1k, Uns32 rb) {
    or1kSetSR(or1k, or1k->regs[rb]);
}

//
// Run-time implementation of mtspr with epc register
//
static void vmic_MTSPR_SYS_EPC(or1kP or1k, Uns32 rb) {
    or1k->EPC = or1k->regs[rb];
}

//
// Run-time implementation of mtspr with eear register
//
static void vmic_MTSPR_SYS_EEAR(or1kP or1k, Uns32 rb) {
    or1k->EEAR = or1k->regs[rb];
}

//
// Run-time implementation of mtspr with esr register
//
static void vmic_MTSPR_SYS_ESR(or1kP or1k, Uns32 rb) {
    or1k->ESR = or1k->regs[rb];
}

//
// Run-time implementation of mtspr with ttcr register
//
static void vmic_MTSPR_TT_CR(or1kP or1k, Uns32 rb) {
    or1kSetTTCR(or1k, or1k->regs[rb]);
}

//
// Run-time implementation of mtspr with ttmr register
//
static void vmic_MTSPR_TT_MR(or1kP or1k, Uns32 rb) {
    or1kSetTTMR(or1k, or1k->regs[rb]);
}

//
// Run-time implementation of mfspr with sr register
//
static void vmic_MFSPR_SYS_SR(or1kP or1k, Uns32 rd) {
    or1k->regs[rd] = or1kGetSR(or1k);
}

//
// Run-time implementation of mfspr with epc register
//
static void vmic_MFSPR_SYS_EPC(or1kP or1k, Uns32 rd) {
    or1k->regs[rd] = or1k->EPC;
}

//
// Run-time implementation of mfspr with eear register
//
static void vmic_MFSPR_SYS_EEAR(or1kP or1k, Uns32 rd) {
    or1k->regs[rd] = or1k->EEAR;
}

//
// Run-time implementation of mfspr with esr register
//
static void vmic_MFSPR_SYS_ESR(or1kP or1k, Uns32 rd) {
    or1k->regs[rd] = or1k->ESR;
}

//
// Run-time implementation of mfspr with ttcr register, supervisor mode
//
static void vmic_MFSPR_TT_CR_SM(or1kP or1k, Uns32 rd) {
    or1k->regs[rd] = or1kGetTTCR(or1k);
}

//
// Run-time implementation of mfspr with ttcr register, user mode
//
static void vmic_MFSPR_TT_CR_UM(or1kP or1k, Uns32 rd) {
    if(or1k->SR & SPR_SR_SUMRA) {
        or1k->regs[rd] = or1kGetTTCR(or1k);
    } else {
        or1kTakeException(or1k, OR1K_EXCPT_ILL, 0);
    }
}

//
// Run-time implementation of mfspr with ttmr register
//
static void vmic_MFSPR_TT_MR(or1kP or1k, Uns32 rd) {
    or1k->regs[rd] = or1k->TTMR;
}

//
// Run-time implementation of mtspr instruction, when contents of ra are not
// known at morph time. Function called in SUPERVISOR MODE ONLY
//
static void vmic_MTSPR_SM(
    or1kP or1k,
    Uns32 thisPC,
    Uns32 ra,
    Uns32 rb,
    Uns32 k
) {
    Uns32 sprNum = or1k->regs[ra] | k;

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
            vmic_MTSPR_SYS_SR(or1k, rb);
            break;

        case SPR_OFF(SPR_SYS,SYS_EPC):
            vmic_MTSPR_SYS_EPC(or1k, rb);
            break;

        case SPR_OFF(SPR_SYS,SYS_EEAR):
            vmic_MTSPR_SYS_EEAR(or1k, rb);
            break;

        case SPR_OFF(SPR_SYS,SYS_ESR):
            vmic_MTSPR_SYS_ESR(or1k, rb);
            break;

        case SPR_OFF(SPR_TT,TT_CR):
            vmic_MTSPR_TT_CR(or1k, rb);
            break;

        case SPR_OFF(SPR_TT,TT_MR):
            vmic_MTSPR_TT_MR(or1k, rb);
            break;

        default:
            ignoreMTSPR(thisPC, ra, rb, k, sprNum);
            break;
    }
}

//
// Run-time implementation of mfspr instruction, when contents of ra are not
// known at morph time. Function called in SUPERVISOR MODE ONLY
//
static void vmic_MFSPR_SM(
    or1kP or1k,
    Uns32 thisPC,
    Uns32 rd,
    Uns32 ra,
    Uns32 k
) {
    Uns32 sprNum = or1k->regs[ra] | k;

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
            vmic_MFSPR_SYS_SR(or1k, rd);
            break;

        case SPR_OFF(SPR_SYS,SYS_EPC):
            vmic_MFSPR_SYS_EPC(or1k, rd);
            break;

        case SPR_OFF(SPR_SYS,SYS_EEAR):
            vmic_MFSPR_SYS_EEAR(or1k, rd);
            break;

        case SPR_OFF(SPR_SYS,SYS_ESR):
            vmic_MFSPR_SYS_ESR(or1k, rd);
            break;

        case SPR_OFF(SPR_TT,TT_CR):
            vmic_MFSPR_TT_CR_SM(or1k, rd);
            break;

        case SPR_OFF(SPR_TT,TT_MR):
            vmic_MFSPR_TT_MR(or1k, rd);
            break;

        default:
            ignoreMFSPR(thisPC, rd, ra, k, sprNum);
            break;
    }
}

//
// Run-time implementation of mtspr instruction, when contents of ra are not
// known at morph time. Function called in USER MODE ONLY
//
static void vmic_MTSPR_UM(
    or1kP or1k,
    Uns32 thisPC,
    Uns32 ra,
    Uns32 rb,
    Uns32 k
) {
    Uns32 sprNum = or1k->regs[ra] | k;

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
        case SPR_OFF(SPR_SYS,SYS_EPC):
        case SPR_OFF(SPR_SYS,SYS_EEAR):
        case SPR_OFF(SPR_SYS,SYS_ESR):
        case SPR_OFF(SPR_TT,TT_CR):
        case SPR_OFF(SPR_TT,TT_MR):
            or1kTakeException(or1k, OR1K_EXCPT_ILL, 0);
            break;

        default:
            ignoreMTSPR(thisPC, ra, rb, k, sprNum);
            break;
    }
}

//
// Run-time implementation of mfspr instruction, when contents of ra are not
// known at morph time. Function called in USER MODE ONLY
//
static void vmic_MFSPR_UM(
    or1kP or1k,
    Uns32 thisPC,
    Uns32 rd,
    Uns32 ra,
    Uns32 k
) {
    Uns32 sprNum = or1k->regs[ra] | k;

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
        case SPR_OFF(SPR_SYS,SYS_EPC):
        case SPR_OFF(SPR_SYS,SYS_EEAR):
        case SPR_OFF(SPR_SYS,SYS_ESR):
        case SPR_OFF(SPR_TT,TT_MR):
            or1kTakeException(or1k, OR1K_EXCPT_ILL, 0);
            break;

        case SPR_OFF(SPR_TT,TT_CR):
            vmic_MFSPR_TT_CR_UM(or1k, rd);
            break;

        default:
            ignoreMFSPR(thisPC, rd, ra, k, sprNum);
            break;
    }
}

//
// Emit default action for unimplemented mtspr
//
static void doMTSPR_ra_0_Default(Uns32 thisPC, Uns32 rb, Uns32 sprNum) {

    // warn about the unimplemented mtspr
    ignoreMTSPR(thisPC, 0, rb, sprNum, sprNum);
}

//
// Emit default action for unimplemented mfspr
//
static void doMFSPR_ra_0_Default(Uns32 thisPC, Uns32 rd, Uns32 sprNum) {

    // warn about the unimplemented mfspr
    ignoreMFSPR(thisPC, rd, 0, sprNum, sprNum);

    // assume zero is read
    vmimtMoveRC(OR1K_BITS, OR1K_REG(rd), 0);
}

//
// Emit code for mtspr instruction - variant when contents of ra known to
// be zero at morph time. Function called in SUPERVISOR MODE ONLY
//
static void doMTSPR_ra_0_SM(Uns32 thisPC, Uns32 rb, Uns32 sprNum) {

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
            vmimtArgProcessor();
            vmimtArgReg(OR1K_BITS, OR1K_REG(rb));
            vmimtCall((vmiCallFn)or1kSetSR);
            break;

        case SPR_OFF(SPR_SYS,SYS_EPC):
            vmimtMoveRR(OR1K_BITS, OR1K_EPC, OR1K_REG(rb));
            break;

        case SPR_OFF(SPR_SYS,SYS_EEAR):
            vmimtMoveRR(OR1K_BITS, OR1K_EEAR, OR1K_REG(rb));
            break;

        case SPR_OFF(SPR_SYS,SYS_ESR):
            vmimtMoveRR(OR1K_BITS, OR1K_ESR, OR1K_REG(rb));
            break;

        case SPR_OFF(SPR_TT,TT_CR):
            vmimtArgProcessor();
            vmimtArgReg(OR1K_BITS, OR1K_REG(rb));
            vmimtCall((vmiCallFn)or1kSetTTCR);
            break;

        case SPR_OFF(SPR_TT,TT_MR):
            vmimtArgProcessor();
            vmimtArgReg(OR1K_BITS, OR1K_REG(rb));
            vmimtCall((vmiCallFn)or1kSetTTMR);
            break;

        default:
            doMTSPR_ra_0_Default(thisPC, rb, sprNum);
            break;
    }
}

//
// Emit code for mfspr instruction - variant when contents of ra known to
// be zero at morph time. Function called in SUPERVISOR MODE ONLY
//
static void doMFSPR_ra_0_SM(Uns32 thisPC, Uns32 rd, Uns32 sprNum) {

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
            vmimtArgProcessor();
            vmimtCallResult((vmiCallFn)or1kGetSR, OR1K_BITS, OR1K_REG(rd));
            break;

        case SPR_OFF(SPR_SYS,SYS_EPC):
            vmimtMoveRR(OR1K_BITS, OR1K_REG(rd), OR1K_EPC);
            break;

        case SPR_OFF(SPR_SYS,SYS_EEAR):
            vmimtMoveRR(OR1K_BITS, OR1K_REG(rd), OR1K_EEAR);
            break;

        case SPR_OFF(SPR_SYS,SYS_ESR):
            vmimtMoveRR(OR1K_BITS, OR1K_REG(rd), OR1K_ESR);
            break;

        case SPR_OFF(SPR_TT,TT_CR):
            vmimtArgProcessor();
            vmimtCallResult((vmiCallFn)or1kGetTTCR, OR1K_BITS, OR1K_REG(rd));
            break;

        case SPR_OFF(SPR_TT,TT_MR):
            vmimtMoveRR(OR1K_BITS, OR1K_REG(rd), OR1K_TTMR);
            break;

        default:
            doMFSPR_ra_0_Default(thisPC, rd, sprNum);
            break;
    }
}

//
// Emit code for mtspr instruction - variant when contents of ra known to
// be zero at morph time. Function called in USER MODE ONLY
//
static void doMTSPR_ra_0_UM(Uns32 thisPC, Uns32 rb, Uns32 sprNum) {

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
        case SPR_OFF(SPR_SYS,SYS_EPC):
        case SPR_OFF(SPR_SYS,SYS_EEAR):
        case SPR_OFF(SPR_SYS,SYS_ESR):
        case SPR_OFF(SPR_TT,TT_CR):
        case SPR_OFF(SPR_TT,TT_MR):
            vmimtArgProcessor();
            vmimtArgUns32(OR1K_EXCPT_ILL);
            vmimtArgUns32(0);
            vmimtCall((vmiCallFn)or1kTakeException);
            break;

        default:
            doMTSPR_ra_0_Default(thisPC, rb, sprNum);
            break;
    }
}

//
// Emit code for mfspr instruction - variant when contents of ra known to
// be zero at morph time. Function called in USER MODE ONLY
//
static void doMFSPR_ra_0_UM(Uns32 thisPC, Uns32 rd, Uns32 sprNum) {

    switch(sprNum) {

        case SPR_OFF(SPR_SYS,SYS_SR):
        case SPR_OFF(SPR_SYS,SYS_EPC):
        case SPR_OFF(SPR_SYS,SYS_EEAR):
        case SPR_OFF(SPR_SYS,SYS_ESR):
        case SPR_OFF(SPR_TT,TT_MR):
            vmimtArgProcessor();
            vmimtArgUns32(OR1K_EXCPT_ILL);
            vmimtArgUns32(0);
            vmimtCall((vmiCallFn)or1kTakeException);
            break;

        case SPR_OFF(SPR_TT,TT_CR):
            vmimtArgProcessor();
            vmimtArgUns32(rd);
            vmimtCall((vmiCallFn)vmic_MFSPR_TT_CR_UM);
            break;

        default:
            doMFSPR_ra_0_Default(thisPC, rd, sprNum);
            break;
    }
}

//
// Emit code for OR1K mtspr instruction
//
static void doMTSPR(or1kP or1k, Uns32 instr, Uns32 thisPC) {

    Uns32 ra = OP10_A(instr);
    Uns32 rb = OP10_B(instr);
    Uns16 k  = OP10_I(instr);

    if(ra==0) {

        // faster variant when ra is r0 - select either supervisor mode or user
        // mode function, based on current mode setting in sr
        if(IN_SUPERVISOR_MODE(or1k)) {
            doMTSPR_ra_0_SM(thisPC, rb, k);
        } else {
            doMTSPR_ra_0_UM(thisPC, rb, k);
        }

    } else {

        // slower variant when ra is not r0
        vmimtArgProcessor();
        vmimtArgUns32(thisPC);
        vmimtArgUns32(ra);
        vmimtArgUns32(rb);
        vmimtArgUns32(k);

        // select either supervisor mode or user mode callback, based on
        // current mode setting in sr
        if(IN_SUPERVISOR_MODE(or1k)) {
            vmimtCall((vmiCallFn)vmic_MTSPR_SM);
        } else {
            vmimtCall((vmiCallFn)vmic_MTSPR_UM);
        }
    }
}

//
// Emit code for OR1K mfspr instruction
//
static void doMFSPR(or1kP or1k, Uns32 instr, Uns32 thisPC) {

    Uns32 rd = OP2_D(instr);
    Uns32 ra = OP2_A(instr);
    Uns16 k  = OP2_I(instr);

    if(rd==0) {

        // attempt to write to r0 shouldn't do anything

    } else if(ra==0) {

        // faster variant when ra is r0 - select either supervisor mode or user
        // mode function, based on current mode setting in sr
        if(IN_SUPERVISOR_MODE(or1k)) {
            doMFSPR_ra_0_SM(thisPC, rd, k);
        } else {
            doMFSPR_ra_0_UM(thisPC, rd, k);
        }

    } else {

        // slower variant when ra is not r0
        vmimtArgProcessor();
        vmimtArgUns32(thisPC);
        vmimtArgUns32(rd);
        vmimtArgUns32(ra);
        vmimtArgUns32(k);

        // select either supervisor mode or user mode callback, based on
        // current mode setting in sr
        if(IN_SUPERVISOR_MODE(or1k)) {
            vmimtCall((vmiCallFn)vmic_MFSPR_SM);
        } else {
            vmimtCall((vmiCallFn)vmic_MFSPR_UM);
        }
    }
}

//
// Handle movhi instruction
//
static OR1K_DISPATCH_FN(morphMOVHI) {doMovHi(instr);}

//
// Handle arithmetic instructions (second argument constant)
//
static OR1K_DISPATCH_FN(morphADDI)  {doBinopSLit(instr, vmi_ADD,  &flagsCO);}
static OR1K_DISPATCH_FN(morphADDIC) {doBinopSLit(instr, vmi_ADC,  &flagsCO);}
static OR1K_DISPATCH_FN(morphANDI)  {doBinopULit(instr, vmi_AND,  0);}
static OR1K_DISPATCH_FN(morphORI)   {doBinopULit(instr, vmi_OR,   0);}
static OR1K_DISPATCH_FN(morphXORI)  {doBinopSLit(instr, vmi_XOR,  0);}
static OR1K_DISPATCH_FN(morphMULI)  {doBinopSLit(instr, vmi_IMUL, &flagsCO);}

//
// Handle arithmetic instructions (second argument register)
//
static OR1K_DISPATCH_FN(morphADD)   {doBinopReg(instr, vmi_ADD,  &flagsCO);}
static OR1K_DISPATCH_FN(morphADDC)  {doBinopReg(instr, vmi_ADC,  &flagsCO);}
static OR1K_DISPATCH_FN(morphSUB)   {doBinopReg(instr, vmi_SUB,  &flagsCO);}
static OR1K_DISPATCH_FN(morphAND)   {doBinopReg(instr, vmi_AND,  0);}
static OR1K_DISPATCH_FN(morphOR)    {doBinopReg(instr, vmi_OR,   0);}
static OR1K_DISPATCH_FN(morphXOR)   {doBinopReg(instr, vmi_XOR,  0);}
static OR1K_DISPATCH_FN(morphMUL)   {doBinopReg(instr, vmi_IMUL, &flagsCO);}
static OR1K_DISPATCH_FN(morphDIV)   {doBinopReg(instr, vmi_IDIV, 0);}
static OR1K_DISPATCH_FN(morphDIVU)  {doBinopReg(instr, vmi_DIV,  0);}

//
// Handle shift/rotate instructions (second argument constant)
//
static OR1K_DISPATCH_FN(morphSLLI)  {doShiftopLit(instr, vmi_SHL, 0);}
static OR1K_DISPATCH_FN(morphSRLI)  {doShiftopLit(instr, vmi_SHR, 0);}
static OR1K_DISPATCH_FN(morphSRAI)  {doShiftopLit(instr, vmi_SAR, 0);}
static OR1K_DISPATCH_FN(morphRORI)  {doShiftopLit(instr, vmi_ROR, 0);}

//
// Handle shift/rotate instructions (second argument register)
//
static OR1K_DISPATCH_FN(morphSLL)   {doShiftopReg(instr, vmi_SHL, 0);}
static OR1K_DISPATCH_FN(morphSRL)   {doShiftopReg(instr, vmi_SHR, 0);}
static OR1K_DISPATCH_FN(morphSRA)   {doShiftopReg(instr, vmi_SAR, 0);}
static OR1K_DISPATCH_FN(morphROR)   {doShiftopReg(instr, vmi_ROR, 0);}

//
// Handle branch instructions
//
static OR1K_DISPATCH_FN(morphBF)    {doBranch(instr, thisPC, True, inDelaySlot);}
static OR1K_DISPATCH_FN(morphBNF)   {doBranch(instr, thisPC, False, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJ)     {doJump(instr, thisPC, False, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJR)    {doJumpReg(instr, thisPC, False, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJAL)   {doJump(instr, thisPC, True, inDelaySlot);}
static OR1K_DISPATCH_FN(morphJALR)  {doJumpReg(instr, thisPC, True, inDelaySlot);}

//
// Handle sys and rfe instructions
//
static OR1K_DISPATCH_FN(morphSYS)   {doSYS(instr, thisPC);}
static OR1K_DISPATCH_FN(morphRFE)   {doRFE(or1k);}

//
// Handle mtspr and mfspr instructions
//
static OR1K_DISPATCH_FN(morphMTSPR) {doMTSPR(or1k, instr, thisPC);}
static OR1K_DISPATCH_FN(morphMFSPR) {doMFSPR(or1k, instr, thisPC);}

//
// Handle load instructions
//
static OR1K_DISPATCH_FN(morphLWZ)   {doLoad(instr, 4, False);}
static OR1K_DISPATCH_FN(morphLWS)   {doLoad(instr, 4, True );}
static OR1K_DISPATCH_FN(morphLBZ)   {doLoad(instr, 1, False);}
static OR1K_DISPATCH_FN(morphLBS)   {doLoad(instr, 1, True );}
static OR1K_DISPATCH_FN(morphLHZ)   {doLoad(instr, 2, False);}
static OR1K_DISPATCH_FN(morphLHS)   {doLoad(instr, 2, True );}

//
// Handle store instructions
//
static OR1K_DISPATCH_FN(morphSW)    {doStore(instr, 4);}
static OR1K_DISPATCH_FN(morphSB)    {doStore(instr, 1);}
static OR1K_DISPATCH_FN(morphSH)    {doStore(instr, 2);}

//
// Handle comparison instructions
//
static OR1K_DISPATCH_FN(morphSF)    {doCompareReg(instr);}
static OR1K_DISPATCH_FN(morphSFI)   {doCompareLit(instr);}

//
// NOP morpher callback
//
static OR1K_DISPATCH_FN(morphNOP)   {/* no action for a NOP */}

//
// OR1K morpher dispatch table
//
static or1kDispatchTableC dispatchTable = {

    // handle movhi instruction
    [OR1K_IT_MOVHI] = morphMOVHI,

    // handle arithmetic instructions
    [OR1K_IT_ADDI]  = morphADDI,
    [OR1K_IT_ADDIC] = morphADDIC,
    [OR1K_IT_ANDI]  = morphANDI,
    [OR1K_IT_ORI]   = morphORI,
    [OR1K_IT_XORI]  = morphXORI,
    [OR1K_IT_MULI]  = morphMULI,

    // handle arithmetic instructions (second argument register)
    [OR1K_IT_ADD]   = morphADD,
    [OR1K_IT_ADDC]  = morphADDC,
    [OR1K_IT_SUB]   = morphSUB,
    [OR1K_IT_AND]   = morphAND,
    [OR1K_IT_OR]    = morphOR,
    [OR1K_IT_XOR]   = morphXOR,
    [OR1K_IT_MUL]   = morphMUL,
    [OR1K_IT_DIV]   = morphDIV,
    [OR1K_IT_DIVU]  = morphDIVU,

    // handle shift/rotate instructions (second argument constant)
    [OR1K_IT_SLLI]  = morphSLLI,
    [OR1K_IT_SRLI]  = morphSRLI,
    [OR1K_IT_SRAI]  = morphSRAI,
    [OR1K_IT_RORI]  = morphRORI,

    // handle shift/rotate instructions (second argument register)
    [OR1K_IT_SLL]   = morphSLL,
    [OR1K_IT_SRL]   = morphSRL,
    [OR1K_IT_SRA]   = morphSRA,
    [OR1K_IT_ROR]   = morphROR,

    // handle branch instructions
    [OR1K_IT_BF]    = morphBF,
    [OR1K_IT_BNF]   = morphBNF,
    [OR1K_IT_J]     = morphJ,
    [OR1K_IT_JR]    = morphJR,
    [OR1K_IT_JAL]   = morphJAL,
    [OR1K_IT_JALR]  = morphJALR,

    // handle sys and rfe instructions
    [OR1K_IT_SYS]   = morphSYS,
    [OR1K_IT_RFE]   = morphRFE,

    // mtspr and mfspr instructions
    [OR1K_IT_MTSPR] = morphMTSPR,
    [OR1K_IT_MFSPR] = morphMFSPR,

    // handle load instructions
    [OR1K_IT_LWZ]   = morphLWZ,
    [OR1K_IT_LWS]   = morphLWS,
    [OR1K_IT_LBZ]   = morphLBZ,
    [OR1K_IT_LBS]   = morphLBS,
    [OR1K_IT_LHZ]   = morphLHZ,
    [OR1K_IT_LHS]   = morphLHS,

    // handle store instructions
    [OR1K_IT_SW]    = morphSW,
    [OR1K_IT_SB]    = morphSB,
    [OR1K_IT_SH]    = morphSH,

    // handle comparison instructions
    [OR1K_IT_SF]    = morphSF,
    [OR1K_IT_SFI]   = morphSFI,

    // handle nop instruction
    [OR1K_IT_NOP]   = morphNOP
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

