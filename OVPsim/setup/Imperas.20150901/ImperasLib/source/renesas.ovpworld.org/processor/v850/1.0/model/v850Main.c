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

#include <string.h>
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "v850Bus.h"
#include "v850Ports.h"
#include "v850Decode.h"
#include "v850Doc.h"
#include "v850MorphFP.h"
#include "v850Structure.h"
#include "v850Config.h"
#include "v850Functions.h"
#include "v850Parameters.h"
#include "v850Exceptions.h"

VMI_CONSTRUCTOR_FN(v850Constructor) {
    v850P v850 = (v850P)processor;
    v850ParamValuesP params = (v850ParamValuesP)parameterValues;

    v850->flags = vmirtProcessorFlags(processor);
    v850->configInfo = v850ConfigTable[params->variant];
    if (v850->configInfo.name == NULL) {
        // Assign value as First Variant
        v850->configInfo = v850ConfigTable[0];
    }
    Int32 iter;
    for (iter=0; iter<32; iter++) {
        v850->gpr[iter] = 0;
    }
    v850->SPR_EIPC.reg = 0; // readonly=0
    v850->SPR_EIPC_wmask.reg = ~0;
    v850->SPR_EIPC_rmask.reg = ~0;
    v850->SPR_EIPSW.reg = 0; // readonly=0
    v850->SPR_EIPSW_wmask.reg = ~0;
    v850->SPR_EIPSW_rmask.reg = ~0;
    v850->SPR_FEPC.reg = 0; // readonly=0
    v850->SPR_FEPC_wmask.reg = ~0;
    v850->SPR_FEPC_rmask.reg = ~0;
    v850->SPR_FEPSW.reg = 0; // readonly=0
    v850->SPR_FEPSW_wmask.reg = ~0;
    v850->SPR_FEPSW_rmask.reg = ~0;

    // ECR is an alias of EIIC FEIC
    v850->SPR_EIIC.reg = 0; // readonly=0
    v850->SPR_EIIC_wmask.reg = ~0;
    v850->SPR_EIIC_rmask.reg = ~0;
    v850->SPR_FEIC.reg = 0; // readonly=0
    v850->SPR_FEIC_wmask.reg = ~0;
    v850->SPR_FEIC_rmask.reg = ~0;

    v850->SPR_PSW.reg = 0x000000020; // readonly=0
    v850->SPR_PSW_wmask.reg = 0x000000ff;   // e0
    if (v850->configInfo.arch & ISA_E2) {
        v850->SPR_PSW_wmask.reg |= 0x00070e00;
    }
    v850->SPR_PSW_rmask.reg = ~0;

    v850->SPR_CTPC.reg = 0; // readonly=0
    v850->SPR_CTPC_wmask.reg = ~0;
    v850->SPR_CTPC_rmask.reg = ~0;
    v850->SPR_CTPSW.reg = 0; // readonly=0
    v850->SPR_CTPSW_wmask.reg = ~0;
    v850->SPR_CTPSW_rmask.reg = ~0;
    v850->SPR_DBPC.reg = 0; // readonly=0
    v850->SPR_DBPC_wmask.reg = ~0;
    v850->SPR_DBPC_rmask.reg = ~0;
    v850->SPR_DBPSW.reg = 0; // readonly=0
    v850->SPR_DBPSW_wmask.reg = ~0;
    v850->SPR_DBPSW_rmask.reg = ~0;
    v850->SPR_CTBP.reg = 0; // readonly=0
    v850->SPR_CTBP_wmask.reg = ~0;
    v850->SPR_CTBP_rmask.reg = ~0;
    v850->SPR_DIR.reg = 0; // readonly=0
    v850->SPR_DIR_wmask.reg = ~0;
    v850->SPR_DIR_rmask.reg = ~0;
    v850->SPR_BPC.reg = 0; // readonly=0
    v850->SPR_BPC_wmask.reg = ~0;
    v850->SPR_BPC_rmask.reg = ~0;
    v850->SPR_ASID.reg = 0; // readonly=0
    v850->SPR_ASID_wmask.reg = ~0;
    v850->SPR_ASID_rmask.reg = ~0;
    v850->SPR_BPAV.reg = 0; // readonly=0
    v850->SPR_BPAV_wmask.reg = ~0;
    v850->SPR_BPAV_rmask.reg = ~0;
    v850->SPR_BPAM.reg = 0; // readonly=0
    v850->SPR_BPAM_wmask.reg = ~0;
    v850->SPR_BPAM_rmask.reg = ~0;
    v850->SPR_BPDV.reg = 0; // readonly=0
    v850->SPR_BPDV_wmask.reg = ~0;
    v850->SPR_BPDV_rmask.reg = ~0;
    v850->SPR_BPDM.reg = 0; // readonly=0
    v850->SPR_BPDM_wmask.reg = ~0;
    v850->SPR_BPDM_rmask.reg = ~0;
    for (iter=0; iter<4; iter++) {
        v850->tmp[iter] = 0;
    }
    v850->FLG_SAT = 0; // readonly=0
    v850->FLG_ID = 1; // readonly=0
    v850->FLG_EP = 0; // readonly=0
    v850->FLG_NP = 0; // readonly=0
    v850->FLG_INTPEND = 0; // readonly=0
    v850->FLG_NMIPEND = 0; // readonly=0
    v850->FLG_TMP = 0; // readonly=0
    v850->iendian = params->SETBIT(endian) ? params->endian : MEM_ENDIAN_LITTLE;
    v850->dendian = params->SETBIT(endian) ? params->endian : MEM_ENDIAN_LITTLE;
    v850->exception = v850_E_reset;

    //
    // Variant specific setup
    //
    if (v850->configInfo.arch == V850E1F) {
        v850->SPR_EFG.reg = 0; // readonly=0
        v850->SPR_EFG_wmask.reg = 0x00000017; // 0000 0000 0000 0000 0000 0000 0001 0111 = 0x00003F17 TR OV S Z
        v850->SPR_EFG_rmask.reg = 0x00003F17; // 0000 0000 0000 0000 0011 1111 0001 0111 = 0x00003F17
        v850->SPR_ECT.reg = 0; // readonly=0
        v850->SPR_ECT_wmask.reg = 0x00001F00; // 0000 0000 0000 0000 0001 1111 0000 0000 = 0x00001F00
        v850->SPR_ECT_rmask.reg = 0x00001F00;
    }

    //
    // Variant specific setup
    //
    if (v850->configInfo.arch & ISA_E2) {
        v850->SPR_EIWR_wmask.reg = ~0;
        v850->SPR_EIWR_rmask.reg = ~0;
        v850->SPR_FEWR_wmask.reg = ~0;
        v850->SPR_FEWR_rmask.reg = ~0;
        v850->SPR_DBWR_wmask.reg = ~0;
        v850->SPR_DBWR_rmask.reg = ~0;

        v850->SPR_BSEL_wmask.reg = ~0;
        v850->SPR_BSEL_wmask.bits.RSV0 = 0;
        v850->SPR_BSEL_rmask.reg = v850->SPR_BSEL_wmask.reg;

        v850->SPR_FPSR_wmask.reg = ~0;
        v850->SPR_FPSR_wmask.bits.RSV0 = 0;
        v850->SPR_FPSR_wmask.bits.RM = 0;
        v850->SPR_FPSR_wmask.bits.FS = 0;
        v850->SPR_FPSR_rmask.reg = v850->SPR_FPSR_wmask.reg;
        v850->SPR_FPSR_rmask.bits.FS = 1;

        v850->SPR_FPEPC_wmask.reg = ~0;
        v850->SPR_FPEPC_wmask.bits.RSV0 = 0;
        v850->SPR_FPEPC_wmask.bits.RSV1 = 0;
        v850->SPR_FPEPC_rmask.reg = v850->SPR_FPEPC_wmask.reg;

        v850->SPR_FPST_wmask.reg = ~0;
        v850->SPR_FPST_wmask.bits.RSV0 = 0;
        v850->SPR_FPST_wmask.bits.RSV1 = 0;
        v850->SPR_FPST_wmask.bits.RSV2 = 0;
        v850->SPR_FPST_rmask.reg = v850->SPR_FPST_wmask.reg;

        v850->SPR_FPCC_wmask.reg = ~0;
        v850->SPR_FPCC_wmask.bits.RSV0 = 0;
        v850->SPR_FPCC_rmask.reg = v850->SPR_FPCC_wmask.reg;

        v850->SPR_FPCFG_wmask.reg = ~0;
        v850->SPR_FPCFG_wmask.bits.RSV0 = 0;
        v850->SPR_FPCFG_wmask.bits.RM   = 0;
        v850->SPR_FPCFG_wmask.bits.RSV1 = 0;
        v850->SPR_FPCFG_rmask.reg = v850->SPR_FPCFG_wmask.reg;
    }

    // Store the parameters for later retrievel
    v850->params.GDBSIMMODE = params->GDBSIMMODE;

    //
    // allocate net port descriptions
    //
    v850NewNetPorts(v850);

    //
    // allocate bus port descriptions
    //
    v850NewBusPorts(v850);

    //
    // link the decoder callback
    //
    v850->decoder = v850Decode;

    //
    // Call the documentation constructor
    //
    v850Doc(processor, params);

    //
    // Cause a reset exception
    //
    v850ProcessReset(v850);

    //
    // Initialize FPU (if present)
    //
    v850ConfigureFPU(v850);
}

VMI_DESTRUCTOR_FN(v850Destructor) {
    v850P v850 = (v850P)processor;

    //
    // free bus port descriptions
    //
    v850FreeBusPorts(v850);
}
