/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "vmi/vmiAttrs.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "v850Structure.h"
#include "v850Functions.h"
#include "v850Utils.h"

typedef enum v850RegSetE {
    V850_GPR     = 0x00000001,

    V850_SPR     = 0x00000002,
    V850E_SPR    = 0x00000004,
    V850E2_SPR   = 0x00000008,
    V850E3V5_SPR = 0x00000010,

    V850_REGSET    = V850_GPR | V850_SPR,
    V850E_REGSET   = V850_GPR | V850E_SPR,
    V850E2_REGSET  = V850_GPR | V850E2_SPR,
    V850E2M_REGSET = V850_GPR | V850E2_SPR,
    V850E2R_REGSET = V850_GPR | V850E2_SPR,

} v850RegSet;

typedef const struct v850RegVariantInfoS {
    vmiRegInfo vmi;
    v850RegSet set;
} v850RegVariantInfo, *v850RegVariantInfoCP;

static v850RegSet getRegSet(v850Architecture arch) {
    if (arch == V850) {
        return V850_REGSET;

    } else if ((arch == V850E1) || (arch == V850E1F) || (arch == V850ES)) {
        return V850E_REGSET;

    } else if (arch == V850E2) {
        return V850E2_REGSET;

    } else if (arch == V850E2M) {
        return V850E2_REGSET;


    } else if (arch == V850E2R) {
        return V850E2R_REGSET;
    }

    return V850_REGSET;
}


//
// Macro to specify basic register attributes
//
#define V850_REG_INFO(_SET, _NAME, _INDEX, _USAGE, _BITS, _GROUP, _DETAIL, _DESC) { \
    {\
        name        : _NAME,    \
        description : _DESC,    \
        gdbIndex    : _INDEX,   \
        usage       : _USAGE,   \
        bits        : _BITS,    \
        group       : _GROUP,   \
        _DETAIL                 \
    }, \
    _SET \
}

//
// Macro to specify a register accessible raw for read/write
//
#define V850_RAW_REG_RW(_R) \
    access   : vmi_RA_RW,           \
    raw      : V850_CPU_REG(_R)

//
// Macro to specify a register accessible raw for read only
//
#define V850_RAW_REG_R(_R) \
    access   : vmi_RA_R,            \
    raw      : V850_CPU_REG(_R)

//
// Macro to specify a register accessible with callbacks for read/write
//
#define V850_CB_REG_RW(_RCB, _WCB) \
    access   : vmi_RA_RW,           \
    readCB   : _RCB,                \
    writeCB  : _WCB

//
// Macro to specify a register accessible with callbacks for read only
//
#define V850_CB_REG_R(_RCB) \
    access   : vmi_RA_R,            \
    readCB   : _RCB

static VMI_REG_READ_FN(readPC) {
    *(v850Addr*)buffer = (Uns32)vmirtGetPC(processor);
    return True;
}

static VMI_REG_WRITE_FN(writePC) {
    vmirtSetPC(processor, *(v850Addr*)buffer);
    return True;
}

static VMI_REG_READ_FN(readECR) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850PackECR(v850);
    return True;
}

static VMI_REG_READ_FN(readPSW) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850PackPSW(v850);
    return True;
}

static VMI_REG_READ_FN(padZERO) {
    *(Uns32*)buffer = 0x00000000;
    return True;
}

static VMI_REG_READ_FN(readFPSR) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850PackFPSR(v850);
    return True;
}

static VMI_REG_READ_FN(readFPST) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850PackFPST(v850);
    return True;
}

static VMI_REG_READ_FN(readFPCC) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850PackFPCC(v850);
    return True;
}

static VMI_REG_READ_FN(readFPCFG) {
    v850P v850 = (v850P)processor;
    *(Uns32*)buffer = v850PackFPCFG(v850);
    return True;
}

//  static const char *v850_reg_names[] =
//  {
//    "r0",   "r1",     "r2",    "r3",    "r4",   "r5",   "r6",   "r7",
//    "r8",   "r9",     "r10",   "r11",   "r12",  "r13",  "r14",  "r15",
//    "r16",  "r17",    "r18",   "r19",   "r20",  "r21",  "r22",  "r23",
//    "r24",  "r25",    "r26",   "r27",   "r28",  "r29",  "r30",  "r31",
//
//
//    "eipc", "eipsw",  "fepc",  "fepsw", "ecr",  "psw",  "sr6",  "sr7",
//    "sr8",  "sr9",    "sr10",  "sr11",  "sr12", "sr13", "sr14", "sr15",
//    "sr16", "sr17",   "sr18",  "sr19",  "sr20", "sr21", "sr22", "sr23",
//    "sr24", "sr25",   "sr26",  "sr27",  "sr28", "sr29", "sr30", "sr31",
//    "pc",   "fp"
//  };

//  static const char *v850e_reg_names[] =
//  {
//    "r0",   "r1",    "r2",   "r3",    "r4",   "r5",   "r6",   "r7",
//    "r8",   "r9",    "r10",  "r11",   "r12",  "r13",  "r14",  "r15",
//    "r16",  "r17",   "r18",  "r19",   "r20",  "r21",  "r22",  "r23",
//    "r24",  "r25",   "r26",  "r27",   "r28",  "r29",  "r30",  "r31",
//
//    "eipc", "eipsw", "fepc", "fepsw", "ecr",  "psw",  "sr6",  "sr7",
//    "sr8",  "sr9",   "sr10", "sr11",  "sr12", "sr13", "sr14", "sr15",
//    "ctpc", "ctpsw", "dbpc", "dbpsw", "ctbp", "sr21", "sr22", "sr23",
//    "sr24", "sr25",  "sr26", "sr27",  "sr28", "sr29", "sr30", "sr31",
//    "pc",   "fp"
//  };


//  static const char *v850e2_reg_names[] =
//  {
//    /* General purpose registers.  */
//    "r0",   "r1", "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
//    "r8",   "r9", "r10", "r11", "r12", "r13", "r14", "r15",
//    "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
//    "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
//
//    /* System registers - main banks.  */
//    "eipc", "eipsw", "fepc",  "fepsw", "ecr",  "psw",  "pid",  "cfg",
//    "",     "",      "",      "sccfg", "scbp", "eiic", "feic", "dbic",
//    "ctpc", "ctpsw", "dbpc",  "dbpsw", "ctbp", "dir",  "",     "",
//    "",     "",      "",      "",      "eiwr", "fewr", "dbwr", "bsel",
//
//
//    /* PC.  */
//    "pc", "",
//
//    /* System registers - MPV (PROT00) bank.  */
//    "vsecr", "vstid", "vsadr", "",     "vmecr", "vmtid", "vmadr", "",
//    "vpecr", "vptid", "vpadr", "",     "",      "",       "",     "",
//    "",      "",      "",      "",     "",      "",       "",     "",
//    "mca",   "mcs",   "mcc",   "mcr",
//
//    /* System registers - MPU (PROT01) bank.  */
//    "mpm",   "mpc",   "tid",   "",      "",      "",      "ipa0l", "ipa0u",
//    "ipa1l", "ipa1u", "ipa2l", "ipa2u", "ipa3l", "ipa3u", "ipa4l", "ipa4u",
//    "dpa0l", "dpa0u", "dpa1l", "dpa1u", "dpa2l", "dpa2u", "dpa3l", "dpa3u",
//    "dpa4l", "dpa4u", "dpa5l", "dpa5u",
//
//    /* FPU system registers.  */
//    "",     "",     "",      "",     "", "", "fpsr", "fpepc",
//    "fpst", "fpcc", "fpcfg", "fpec", "", "", "",     "",
//    "",     "",     "",      "",     "", "", "",     "",
//    "",     "",     "",      "fpspc"
//  };

//  static const char *v850e3v5_reg_names[] =
//  {
//    /* General purpose registers.  */
//    "r0",   "r1", "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
//    "r8",   "r9", "r10", "r11", "r12", "r13", "r14", "r15",
//    "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
//    "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
//
//    /* selID 0, not including FPU registers.  The FPU registers are
//       listed later on.  32:63*/
//    "eipc", "eipsw", "fepc", "fepsw", "",     "psw", "" /* fpsr */, "" /* fpepc */,
//    "" /* fpst */, "" /* fpcc */, "" /* fpcfg */, "" /* fpec */,
//    "sesr", "eiic", "feic", "",
//    "ctpc", "ctpsw", "", "", "ctbp", "", "", "",
//    "", "", "", "", "eiwr", "fewr", "", "bsel",
//
//
//    /* PC.  64,65 */
//    "pc", "",
//
//    /* v850e2 MPV bank.  66:+=28*/
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "",
//
//    /* Skip v850e2 MPU bank.  It's tempting to reuse these, but we need
//       32 entries for this bank.  66:+=(2*28)*/
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "",
//
//    /* FPU system registers.  These are actually in selID 0, but
//       are placed here to preserve register numbering compatibility
//       with previous architectures.  66:+=(3*28) */
//    "", "", "", "", "", "", "fpsr", "fpepc",
//    "fpst", "fpcc", "fpcfg", "fpec", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "",
//
//    /* selID 1.  */
//    "mcfg0", "mcfg1", "rbase", "ebase", "intbp", "mctl", "pid", "fpipr",
//    "", "", "tcsel", "sccfg", "scbp", "hvccfg", "hvcbp", "vsel",
//    "vmprt0", "vmprt1", "vmprt2", "", "", "", "", "vmscctl",
//    "vmsctbl0", "vmsctbl1", "vmsctbl2", "vmsctbl3", "", "", "", "",
//
//    /* selID 2.  */
//    "htcfg0", "", "", "", "", "htctl", "mea", "asid",
//    "mei", "ispr", "pmr", "icsr", "intcfg", "", "", "",
//    "tlbsch", "", "", "", "", "", "", "htscctl",
//    "htsctbl0", "htsctbl1", "htsctbl2", "htsctbl3",
//    "htsctbl4", "htsctbl5", "htsctbl6", "htsctbl7",
//
//    /* selID 3.  */
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//    "", "", "", "", "", "", "", "",
//
//    /* selID 4.  */
//    "tlbidx", "", "", "", "telo0", "telo1", "tehi0", "tehi1",
//    "", "", "tlbcfg", "", "bwerrl", "bwerrh", "brerrl", "brerrh",
//    "ictagl", "ictagh", "icdatl", "icdath",
//    "dctagl", "dctagh", "dcdatl", "dcdath",
//    "icctrl", "dcctrl", "iccfg", "dccfg", "icerr", "dcerr", "", "",
//
//    /* selID 5.  */
//    "mpm", "mprc", "", "", "mpbrgn", "mptrgn", "", "",
//    "mca", "mcs", "mcc", "mcr", "", "", "", "",
//    "", "", "", "", "mpprt0", "mpprt1", "mpprt2", "",
//    "", "", "", "", "", "", "", "",
//
//    /* selID 6.  */
//    "mpla0", "mpua0", "mpat0", "", "mpla1", "mpua1", "mpat1", "",
//    "mpla2", "mpua2", "mpat2", "", "mpla3", "mpua3", "mpat3", "",
//    "mpla4", "mpua4", "mpat4", "", "mpla5", "mpua5", "mpat5", "",
//    "mpla6", "mpua6", "mpat6", "", "mpla7", "mpua7", "mpat7", "",
//
//    /* selID 7.  */
//    "mpla8", "mpua8", "mpat8", "", "mpla9", "mpua9", "mpat9", "",
//    "mpla10", "mpua10", "mpat10", "", "mpla11", "mpua11", "mpat11", "",
//    "mpla12", "mpua12", "mpat12", "", "mpla13", "mpua13", "mpat13", "",
//    "mpla14", "mpua14", "mpat14", "", "mpla15", "mpua15", "mpat15", "",
//
//    /* Vector Registers */
//    "vr0", "vr1", "vr2", "vr3", "vr4", "vr5", "vr6", "vr7",
//    "vr8", "vr9", "vr10", "vr11", "vr12", "vr13", "vr14", "vr15",
//    "vr16", "vr17", "vr18", "vr19", "vr20", "vr21", "vr22", "vr23",
//    "vr24", "vr25", "vr26", "vr27", "vr28", "vr29", "vr30", "vr31",
//  };


typedef enum v850RegGroupIdE {
    V850_RG_USER,
    V850_RG_SYSTEM,
    V850_RG_LAST
} v850RegGroupId;

static const vmiRegGroup groups[V850_RG_LAST+1] = {
    [V850_RG_USER]   = {name: "User"          },
    [V850_RG_SYSTEM] = {name: "System"        },
};

//
// Return next supported group on this processor
//
static vmiRegGroupCP getNextGroup(vmiRegGroupCP group) {
    if(!group) {
        group = groups;
    } else if((group+1)->name) {
        group = group+1;
    } else {
        group = 0;
    }
    return group;
}


static const v850RegVariantInfo registers[] = {
    /* General Purpose Registers = 32 */
    V850_REG_INFO(V850_GPR,   "R0",   0, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_R (gpr[0]),  "Zero Register"),
    V850_REG_INFO(V850_GPR,   "R1",   1, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[1]),  "Assembler-reserved register"),
    V850_REG_INFO(V850_GPR,   "R2",   2, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[2]),  "Address/data variable register (when the real-time OS to be used is not using r2)"),
    V850_REG_INFO(V850_GPR,   "R3",   3, vmi_REG_SP,   V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[3]),  "Stack pointer (SP)"),
    V850_REG_INFO(V850_GPR,   "R4",   4, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[4]),  "Global pointer (GP)"),
    V850_REG_INFO(V850_GPR,   "R5",   5, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[5]),  "Test pointer (TP)"),
    V850_REG_INFO(V850_GPR,   "R6",   6, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[6]),  "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R7",   7, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[7]),  "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R8",   8, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[8]),  "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R9",   9, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[9]),  "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R10", 10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[10]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R11", 11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[11]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R12", 12, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[12]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R13", 13, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[13]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R14", 14, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[14]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R15", 15, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[15]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R16", 16, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[16]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R17", 17, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[17]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R18", 18, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[18]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R19", 19, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[19]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R20", 20, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[20]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R21", 21, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[21]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R22", 22, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[22]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R23", 23, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[23]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R24", 24, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[24]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R25", 25, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[25]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R26", 26, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[26]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R27", 27, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[27]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R28", 28, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[28]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R29", 29, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[29]), "Address/data variable registers"),
    V850_REG_INFO(V850_GPR,   "R30", 30, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[30]), "Element pointer (EP)"),
    V850_REG_INFO(V850_GPR,   "R31", 31, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_USER], V850_RAW_REG_RW(gpr[31]), "Link pointer (LP)"),

    /* V850  System Registers */
    V850_REG_INFO(V850_SPR,   "EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO(V850_SPR,   "EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO(V850_SPR,   "FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO(V850_SPR,   "FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO(V850_SPR,   "ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readECR),   "Exception cause register"),
    V850_REG_INFO(V850_SPR,   "PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readPSW),   "Program status word"),
    V850_REG_INFO(V850_SPR,   "SR6",   38, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR7",   39, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR8",   40, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR9",   41, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR10",  42, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR11",  43, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR12",  44, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR13",  45, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR14",  46, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR15",  47, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR16",  48, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR17",  49, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR18",  50, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR19",  51, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR20",  52, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR21",  53, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR22",  54, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR23",  55, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR24",  56, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR25",  57, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR26",  58, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR27",  59, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR28",  60, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR29",  61, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR30",  62, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "SR31",  63, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850_SPR,   "PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_RW(readPC, writePC), "Program Counter"),
    V850_REG_INFO(V850_SPR,   "FP",    65, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(gpr[0]), 0),

    /* V850E  System Registers */
    V850_REG_INFO(V850E_SPR,  "EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO(V850E_SPR,  "EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO(V850E_SPR,  "FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO(V850E_SPR,  "FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO(V850E_SPR,  "ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readECR),   "Exception cause register"),
    V850_REG_INFO(V850E_SPR,  "PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readPSW),   "Program status word"),
    V850_REG_INFO(V850E_SPR,  "SR6",   38, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR7",   39, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR8",   40, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR9",   41, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR10",  42, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR11",  43, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR12",  44, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR13",  45, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR14",  46, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR15",  47, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "CTPC",  48, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO(V850E_SPR,  "CTPSW", 49, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTPSW), "CALLT status-saving register PSW"),
    V850_REG_INFO(V850E_SPR,  "DBPC",  50, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBPC),  "Exception/Debug trap status-saving register PC"),
    V850_REG_INFO(V850E_SPR,  "DBPSW", 51, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBPSW), "Exception/Debug trap status-saving register PSW"),
    V850_REG_INFO(V850E_SPR,  "CTBP",  52, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTBP),  "CALLT base pointer"),
    V850_REG_INFO(V850E_SPR,  "DIR",   53, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DIR),   "Debug Interface register"),
    V850_REG_INFO(V850E_SPR,  "SR22",  54, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR23",  55, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR24",  56, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR25",  57, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR26",  58, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR27",  59, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR28",  60, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR29",  61, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR30",  62, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "SR31",  63, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E_SPR,  "PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_RW(readPC, writePC), "Program Counter"),
    V850_REG_INFO(V850E_SPR,  "FP",    65, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(gpr[0]), 0),

    /* V850E2  System Registers */
    V850_REG_INFO(V850E2_SPR, "EIPC",  32, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO(V850E2_SPR, "EIPSW", 33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO(V850E2_SPR, "FEPC",  34, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO(V850E2_SPR, "FEPSW", 35, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO(V850E2_SPR, "ECR",   36, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readECR),   "Exception cause register"),
    V850_REG_INFO(V850E2_SPR, "PSW",   37, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readPSW),   "Program status word"),
/**/V850_REG_INFO(V850E2_SPR, "PID",   38, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
/**/V850_REG_INFO(V850E2_SPR, "CFG",   39, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR8",   40, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR9",   41, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR10",  42, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
/**/V850_REG_INFO(V850E2_SPR, "SCCFG", 43, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
/**/V850_REG_INFO(V850E2_SPR, "SCBP",  44, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "EIIC",  45, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIIC),  "EI Cause Register"),
    V850_REG_INFO(V850E2_SPR, "FEIC",  46, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEIC),  "FE Cause Register"),
    V850_REG_INFO(V850E2_SPR, "DBIC",  47, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBIC),  "DB Cause Register"),
    V850_REG_INFO(V850E2_SPR, "CTPC",  48, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO(V850E2_SPR, "CTPSW", 49, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTPSW), "CALLT status-saving register PSW"),
    V850_REG_INFO(V850E2_SPR, "DBPC",  50, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBPC),  "Exception/Debug trap status-saving register PC"),
    V850_REG_INFO(V850E2_SPR, "DBPSW", 51, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBPSW), "Exception/Debug trap status-saving register PSW"),
    V850_REG_INFO(V850E2_SPR, "CTBP",  52, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTBP),  "CALLT base pointer"),
    V850_REG_INFO(V850E2_SPR, "DIR",   53, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DIR),   "Debug Interface register"),
    V850_REG_INFO(V850E2_SPR, "SR22",  54, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR23",  55, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR24",  56, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR25",  57, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR26",  58, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E2_SPR, "SR27",  59, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
/**/V850_REG_INFO(V850E2_SPR, "EIWR",  60, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIWR),  "EIWR"),
/**/V850_REG_INFO(V850E2_SPR, "FEWR",  61, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEWR),  "FEWR"),
/**/V850_REG_INFO(V850E2_SPR, "DBWR",  62, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBWR),  "DBWR"),
/**/V850_REG_INFO(V850E2_SPR, "BSEL",  63, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_BSEL),  "Bank Select Register"),
    V850_REG_INFO(V850E2_SPR, "PC",    64, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_RW(readPC, writePC), "Program Counter"),

    /* MP Violation */
    V850_REG_INFO(V850E2_SPR, "FPVIP",  65, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR33",   66, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR34",   67, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR35",   68, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VMECR",  69, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VMTID",  70, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VMADR",  71, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR39",   72, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VPECR",  73, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VPTID",  74, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VPADR",  75, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR43",   76, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VDECR",  77, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "VDTID",  78, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR46",   79, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR47",   80, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR48",   81, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR49",   82, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR50",   83, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR51",   84, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR52",   85, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR53",   86, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR54",   87, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR55",   88, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR56",   89, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR57",   90, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR58",   91, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR59",   92, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    /* MP Setting */
    V850_REG_INFO(V850E2_SPR, "MPM",    93, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "MPC",    94, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "TID",    95, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "PPA",    96, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "PPM",    97, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "PPC",    98, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DCC",    99, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DCV0",  100, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DCV1",  101, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR69",  102, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SPAL",  103, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SPAU",  104, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA0L", 105, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA0U", 106, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA1L", 107, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA1U", 108, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA2L", 109, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA2U", 110, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA3L", 111, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "IPA3U", 112, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA0L", 113, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA0U", 114, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA1L", 115, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA1U", 116, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA2L", 117, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA2U", 118, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA3L", 119, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "DPA3U", 120, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR88",  121, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR89",  122, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR80",  123, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR91",  124, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR92",  125, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    V850_REG_INFO(V850E2_SPR, "SR93",  126, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO), 0),
    /* FPU system registers.  */
    V850_REG_INFO(V850E2_SPR, "FPSR",  127, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readFPSR), 0),
    V850_REG_INFO(V850E2_SPR, "FPEPC", 128, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FPEPC), 0),
    V850_REG_INFO(V850E2_SPR, "FPST",  129, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readFPST), 0),
    V850_REG_INFO(V850E2_SPR, "FPCC",  130, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readFPCC), 0),
    V850_REG_INFO(V850E2_SPR, "FPCFG", 131, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readFPCFG),0),
    V850_REG_INFO(V850E2_SPR, "SR99",  132, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR100", 133, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR101", 134, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR102", 135, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR103", 136, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR104", 137, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR105", 138, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR106", 139, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR107", 140, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR108", 141, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR109", 142, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR100", 143, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR101", 144, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR102", 145, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR103", 146, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR104", 147, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),
    V850_REG_INFO(V850E2_SPR, "SR105", 148, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),  0),

    /* V850E2V3  System Registers */
    V850_REG_INFO(V850E3V5_SPR, "EIPC",  32+0,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPC),  "Interrupt status-saving register PC"),
    V850_REG_INFO(V850E3V5_SPR, "EIPSW", 32+1,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIPSW), "Interrupt status-saving register PSW"),
    V850_REG_INFO(V850E3V5_SPR, "FEPC",  32+2,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPC),  "NMI status-saving register PC"),
    V850_REG_INFO(V850E3V5_SPR, "FEPSW", 32+3,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEPSW), "NMI status-saving register PSW"),
    V850_REG_INFO(V850E3V5_SPR, "ECR",   32+4,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readECR),   "Exception cause register"),
    V850_REG_INFO(V850E3V5_SPR, "PSW",   32+5,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (readPSW),   "Program status word"),
    V850_REG_INFO(V850E3V5_SPR, "SR6",   32+6,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR7",   32+7,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR8",   32+8,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR9",   32+9,  vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR10",  32+10, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR11",  32+11, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR12",  32+12, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "EIIC",  32+13, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIIC),  "EI Cause Register"),
    V850_REG_INFO(V850E3V5_SPR, "FEIC",  32+14, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEIC),  "FE Cause Register"),
    V850_REG_INFO(V850E3V5_SPR, "DBIC",  32+15, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBIC),  "DB Cause Register"),
    V850_REG_INFO(V850E3V5_SPR, "CTPC",  32+16, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTPC),  "CALLT status-saving register PC"),
    V850_REG_INFO(V850E3V5_SPR, "CTPSW", 32+17, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTPSW), "CALLT status-saving register PSW"),
    V850_REG_INFO(V850E3V5_SPR, "DBPC",  32+18, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBPC),  "Exception/Debug trap status-saving register PC"),
    V850_REG_INFO(V850E3V5_SPR, "DBPSW", 32+19, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBPSW), "Exception/Debug trap status-saving register PSW"),
    V850_REG_INFO(V850E3V5_SPR, "CTBP",  32+20, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_CTBP),  "CALLT base pointer"),
    V850_REG_INFO(V850E3V5_SPR, "DIR",   32+21, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DIR),   "Debug Interface register"),
    V850_REG_INFO(V850E3V5_SPR, "SR22",  32+22, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR23",  32+23, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR24",  32+24, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR25",  32+25, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR26",  32+26, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "SR27",  32+27, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_R (padZERO),   "_UNIMPLEMENTED_"),
    V850_REG_INFO(V850E3V5_SPR, "EIWR",  32+28, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_EIWR),  "Working Register for EI Exception"),
    V850_REG_INFO(V850E3V5_SPR, "FEWR",  32+29, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_FEWR),  "Working Register for FE Exception"),
    V850_REG_INFO(V850E3V5_SPR, "DBWR",  32+30, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_DBWR),  "Working Register for DB Exception"),
    V850_REG_INFO(V850E3V5_SPR, "BSEL",  32+31, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(SPR_BSEL),  "Register bank Select register"),
    V850_REG_INFO(V850E3V5_SPR, "PC",    32+32, vmi_REG_PC,   V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_CB_REG_RW(readPC, writePC), "Program Counter"),
    V850_REG_INFO(V850E3V5_SPR, "",      32+33, vmi_REG_NONE, V850_GPR_BITS, &groups[V850_RG_SYSTEM], V850_RAW_REG_R(gpr[0]), 0),
    /* System registers - MPV (PROT00) bank.  */
    /* System registers - MPU (PROT01) bank.  */

    { {0}, 0}
};

VMI_REG_GROUP_FN(v850RegGroup) {
    return getNextGroup(prev);
}

//
// Is the passed register supported on this processor?
//
static Bool isRegSupported(v850P v850, v850RegVariantInfoCP reg) {
    v850RegSet regset  = reg->set;
    v850RegSet archset = getRegSet(v850->configInfo.arch);

    if (regset & archset) {
        return True;
    } else {
        return False;
    }
}

VMI_REG_INFO_FN(v850RegInfo) {
    v850RegVariantInfoCP reg = (v850RegVariantInfoCP)prev;
    v850P v850 = (v850P)processor;

    do {
        if(!reg) {
            reg = registers;
        } else if((reg+1)->vmi.name) {
            reg = reg+1;
        } else {
            reg = 0;
        }
    } while (reg && !isRegSupported(v850, reg));

    return (vmiRegInfoCP) reg;
}

VMI_DEBUG_FN(v850Debug) {
    v850P v850 = (v850P)processor;
    Int32 iter;

    vmiPrintf("-----------------  -----------------  -----------------  -----------------\n");

    for (iter=0; iter<32; iter++) {
        vmiPrintf(" R%-5u: %08x", iter, v850->gpr[iter]);
        if(!((iter+1)&3)) {
            vmiPrintf("\n");
        } else {
            vmiPrintf("  ");
        }
    }

    // newline if required before derived registers
    if(iter&3) {
        vmiPrintf("\n");
    }

    vmiPrintf(" EIPC  : %08x  ", v850->SPR_EIPC.reg);
    vmiPrintf(" EIPSW : %08x  ", v850->SPR_EIPSW.reg);
    vmiPrintf(" FEPC  : %08x  ", v850->SPR_FEPC.reg);
    vmiPrintf(" FEPSW : %08x\n", v850->SPR_FEPSW.reg);

    v850PackECR(v850);
    vmiPrintf(" ECR   : %08x  ", v850->SPR_ECR.reg);

    v850PackPSW(v850);
    vmiPrintf(" PSW   : %08x",   v850->SPR_PSW.reg);

    if (v850->configInfo.arch == V850E1F) {
        vmiPrintf("  ");
        v850PackEFG(v850);
        vmiPrintf(" EFG   : %08x  ", v850->SPR_EFG.reg);
        vmiPrintf(" ECT   : %08x  ", v850->SPR_ECT.reg);
    }
    if (v850->configInfo.arch & ISA_E2) {
        v850PackFPSR(v850);
        v850PackFPST(v850);
        v850PackFPCC(v850);
        v850PackFPCFG(v850);
        vmiPrintf("  ");
        vmiPrintf(" FPSR  : %08x  ", v850->SPR_FPSR.reg);
        vmiPrintf(" FPST  : %08x  ", v850->SPR_FPST.reg);
        vmiPrintf("\n");
        vmiPrintf(" FPCC  : %08x  ", v850->SPR_FPCC.reg);
        vmiPrintf(" FPCFG : %08x  ", v850->SPR_FPCFG.reg);
        vmiPrintf(" BSEL  : %08x  ", v850->SPR_BSEL.reg);

    }

    vmiPrintf("\n");

    vmiPrintf(" PC    : %08x", (v850Addr)vmirtGetPC(processor));

    vmiPrintf("\n-----------------  -----------------  -----------------  -----------------\n\n");
}

