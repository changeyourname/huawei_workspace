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

#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"
#include "v850Structure.h"
#include "v850Exceptions.h"
#include "v850Morph.h"
#include "v850MorphFP.h"
#include "v850Utils.h"

#define MFSREG(GPR, SREG) \
    if (GPR) \
    v850->gpr[GPR] = v850->SPR_ ## SREG .reg & v850->SPR_ ## SREG ## _rmask.reg;

#define MTSREG(SREG, GPR) { \
    Uns32 mask    = v850->SPR_ ## SREG ## _wmask.reg; \
    Uns32 prevREG = v850->SPR_ ## SREG .reg & ~mask;  \
    Uns32 nextREG = v850->gpr[GPR]          &  mask;  \
    v850->SPR_ ## SREG .reg = prevREG | nextREG;      \
}

typedef enum ldstE {
    LOAD,
    STORE,
    UNKNOWN
} ldstT;

#define MFMTSREG(SREG, GPR, LDST) {                   \
    if (LDST == LOAD) {                               \
        MTSREG(SREG, GPR);                            \
    } else if (LDST == STORE) {                       \
        MFSREG(GPR, SREG);                            \
    }                                                 \
}

static void vmic_LDSTSR_e0(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {
    switch (regID) {
        case V850_SPR_EIPC:
            MFMTSREG(EIPC, reg2, dir);
            break;
        case V850_SPR_EIPSW:
            MFMTSREG(EIPSW, reg2, dir);
            break;
        case V850_SPR_FEPC:
            MFMTSREG(FEPC, reg2, dir);
            break;
        case V850_SPR_FEPSW:
            MFMTSREG(FEPSW, reg2, dir);
            break;
        case V850_SPR_ECR:
            if (dir == LOAD) {
            } else {
                v850PackECR(v850);
                MFMTSREG(ECR, reg2, dir);
            }
            break;
        case V850_SPR_PSW:
            if (dir == LOAD) {
                MFMTSREG(PSW, reg2, dir);
                v850UnPackPSW(v850);
                //
                // Check for pending interrupts being enabled
                //
                v850TestInterrupt(v850);
            } else {
                v850PackPSW(v850);
                MFMTSREG(PSW, reg2, dir);
            }
            break;
        //
        // 6 - 15 reserved for E0
        //
        case V850_SPR_CTPC:
            MFMTSREG(CTPC, reg2, dir);
            break;
        case V850_SPR_CTPSW:
            MFMTSREG(CTPSW, reg2, dir);
            break;
        case V850_SPR_DBPC:
            MFMTSREG(DBPC, reg2, dir);
            break;
        case V850_SPR_DBPSW:
            MFMTSREG(DBPSW, reg2, dir);
            break;
        case V850_SPR_CTBP:
            MFMTSREG(CTBP, reg2, dir);
            break;
        default:
            // Illegal instruction
            vmiMessage("W", "LDSR/STSR", "Illegal SPR %s\n", getstr_SPR(regID)); // LCOV_EXCL_LINE
            break;
    }
}

static void vmic_LDSTSR_e2_main(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {
    switch (regID) {
    case V850_SPR_EIIC:
        MFMTSREG(EIIC, reg2, dir);
        break;
    case V850_SPR_FEIC:
        MFMTSREG(FEIC, reg2, dir);
        break;
    case V850_SPR_DBIC:
        MFMTSREG(DBIC, reg2, dir);
        break;
    default:
        vmic_LDSTSR_e0(v850, reg2, regID, dir);
        break;
    }
}

//
// MPU Registers
//
static void vmic_LDSTSR_e2_mpu_violation(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {
    vmiMessage("F", "LDSR/STSR", "Illegal group=MPU/bank=VIOLATION\n"); // LCOV_EXCL_LINE
}
static void vmic_LDSTSR_e2_mpu_setting(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {
    vmiMessage("F", "LDSR/STSR", "Illegal group=MPU/bank=SETTING\n"); // LCOV_EXCL_LINE
}

static void vmic_LDSTSR_e2_fpu_status(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {
    switch (regID) {
    case V850_SPR_FPSR:
        if (dir == LOAD) {
            MFMTSREG(FPSR, reg2, LOAD);
            v850UnPackFPSR(v850);
            v850UpdateFPControlWord(v850);
        } else {
            v850PackFPSR(v850);
            MFMTSREG(FPSR, reg2, STORE);
        }
        break;
    case V850_SPR_FPEPC:
        MFMTSREG(FPEPC, reg2, dir);
        break;
    case V850_SPR_FPST:
        if (dir == LOAD) {
            MFMTSREG(FPST, reg2, LOAD);
            v850UnPackFPST(v850);
        } else {
            v850PackFPST(v850);
            MFMTSREG(FPST, reg2, STORE);
        }
        break;
    case V850_SPR_FPCC:
        if (dir == LOAD) {
            MFMTSREG(FPCC, reg2, LOAD);
            v850UnPackFPCC(v850);
        } else {
            v850PackFPCC(v850);
            MFMTSREG(FPCC, reg2, STORE);
        }
        break;
    case V850_SPR_FPCFG:
        if (dir == LOAD) {
            MFMTSREG(FPCFG, reg2, LOAD);
            v850UnPackFPCFG(v850);
            v850UpdateFPControlWord(v850);
        } else {
            v850PackFPCFG(v850);
            MFMTSREG(FPCFG, reg2, STORE);
        }
        break;
    default:
        vmiMessage("F", "LDSR/STSR", "Illegal group=PMU/bank=FPU/id=%d\n", regID); // LCOV_EXCL_LINE
        break;
    }
}

static void vmic_LDSTSR_e2_1(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {
    //
    // Obtain group and bank based upon bsel if available
    //
    Uns8 group = v850->SPR_BSEL.bits.GRP;
    Uns8 bank  = v850->SPR_BSEL.bits.BNK;

    switch (group) {
    case 0x00:              // Main Bank
        switch (bank) {
        case 0x00:          // Main Bank
            vmic_LDSTSR_e2_main(v850, reg2, regID, dir);
            break;

        case 0x10:          // Exception handler switching function bank 0
        case 0x11:          // Exception handler switching function bank 1
        default:
           vmiMessage("F", "LDSR/STSR", "Illegal group=Main/bank=%02x\n",  bank); // LCOV_EXCL_LINE
           break;
        }
        break;
    case 0x10:              // MPU Bank
        switch (bank) {
        case 0x00:          // MPU violation bank
            vmic_LDSTSR_e2_mpu_violation(v850, reg2, regID, dir);
            break;

        case 0x01:          // MPU setting bank
            vmic_LDSTSR_e2_mpu_setting(v850, reg2, regID, dir);
            break;

        default:
           vmiMessage("F", "LDSR/STSR", "Illegal group=MPU/bank=%02x\n", bank); // LCOV_EXCL_LINE
           break;
        }
        break;
    case 0x11:              // PMU Bank
        switch (bank) {
        case 0x00:          // PMU function bank
        default:
           vmiMessage("F", "LDSR/STSR", "Illegal group=PMU/bank=%02x\n", bank); // LCOV_EXCL_LINE
           break;
        }
        break;
    case 0x20:              // FPU Bank
        switch (bank) {
        case 0x00:          // FPU status bank
            vmic_LDSTSR_e2_fpu_status(v850, reg2, regID, dir);
            break;
        default:
           vmiMessage("F", "LDSR/STSR", "Illegal group=FPU/bank=%02x\n", bank); // LCOV_EXCL_LINE
           break;
        }
        break;
    case 0xFF:              // User Bank
        switch (bank) {
        case 0x00:          // User 0 bank
        case 0xFF:          // User compatible bank
        default:
           vmiMessage("F", "LDSR/STSR","Illegal group=User/bank=%02x\n", bank); // LCOV_EXCL_LINE
           break;
        }
        break;
    default:
        // Illegal instruction
        vmiMessage("F", "LDSR/STSR", "Illegal group=0x%02x\n", group); // LCOV_EXCL_LINE
        break;
    }
}

static void vmic_LDSTSR_e2_0(v850P v850, Uns32 reg2, Uns32 regID, ldstT dir) {

    //
    // These registers are independant of the bank selection
    //
    switch (regID) {
    case V850_SPR_EIWR:
        MFMTSREG(EIWR, reg2, dir);
        break;
    case V850_SPR_FEWR:
        MFMTSREG(FEWR, reg2, dir);
        break;
    case V850_SPR_DBWR:
        MFMTSREG(DBWR, reg2, dir);
        break;
    case V850_SPR_BSEL:
        MFMTSREG(BSEL, reg2, dir);
        break;
    default:
        vmic_LDSTSR_e2_1(v850, reg2, regID, dir);
        break;
    }
}

//
// SPR[] <= GPR[]
//
static void vmic_LDSR(v850P v850, Uns32 reg2, Uns32 regID) {
    if (v850->configInfo.arch & ISA_E2) {

        vmic_LDSTSR_e2_0(v850, reg2, regID, LOAD);

    } else if (v850->configInfo.arch & ISA_E1) {

        vmic_LDSTSR_e0(v850, reg2, regID, LOAD);

    } else if (v850->configInfo.arch & ISA_E0) {

        vmic_LDSTSR_e0(v850, reg2, regID, LOAD);

    }
}

V850_MORPH_FN(morphLDSR_F09RS1) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;

    vmimtArgProcessor();
    vmimtArgUns32(reg1);
    vmimtArgUns32(reg2);
    vmimtCall((vmiCallFn)vmic_LDSR);
}

//
// SPR[] => GPR[]
//
static void vmic_STSR(v850P v850, Uns32 regID, Uns32 reg2) {
    if (v850->configInfo.arch & ISA_E2) {

        vmic_LDSTSR_e2_0(v850, reg2, regID, STORE);

    } else if (v850->configInfo.arch & ISA_E1) {

        vmic_LDSTSR_e0(v850, reg2, regID, STORE);

    } else if (v850->configInfo.arch & ISA_E0) {

        vmic_LDSTSR_e0(v850, reg2, regID, STORE);

    }
}

V850_MORPH_FN(morphSTSR_F09SR) {
    //
    // Supported Architecture=V850_ISA_E0
    //
    Uns8 reg1 = state->info.reg1;
    Uns8 reg2 = state->info.reg2;

    vmimtArgProcessor();
    vmimtArgUns32(reg1);
    vmimtArgUns32(reg2);
    vmimtCall((vmiCallFn)vmic_STSR);
}
