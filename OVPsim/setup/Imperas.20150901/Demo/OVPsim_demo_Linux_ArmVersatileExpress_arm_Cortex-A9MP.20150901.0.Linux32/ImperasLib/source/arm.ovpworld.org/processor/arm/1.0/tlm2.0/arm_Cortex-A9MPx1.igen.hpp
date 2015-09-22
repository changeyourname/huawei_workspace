/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * YOU MAY USE THE SOFTWARE SUBJECT TO THE LICENSE TERMS BELOW
 * PROVIDED THAT YOU ENSURE THAT THIS NOTICE IS REPLICATED UNMODIFIED
 * AND IN ITS ENTIRETY IN ALL DISTRIBUTIONS OF THE SOFTWARE,
 * MODIFIED OR UNMODIFIED, IN SOURCE CODE OR IN BINARY FORM.
 *
 * In respect of all models:
 *   The license shall not be construed as granting a license to create a hardware
 *   implementation of the functionality of the software licensed hereunder.
 *
 * In respect of ARM related models:
 *   The license below extends only for your use of the software for the sole
 *   purpose of designing, developing, analyzing, debugging, testing,
 *   verifying, validating and optimizing software which: (a) (i) is for ARM
 *   based systems; and (ii) does not incorporate the ARM Models or any part
 *   thereof; and (b) such ARM Models may not be used to emulate an ARM based
 *   system to run application software in a production or live environment.
 *
 *   The license does not entitle you to use the ARM models for evaluating
 *   the validity of any ARM patent.
 *
 * The license is non-exclusive, worldwide, non-transferable and revocable.
 *
 * Licensed under an Imperas Modified Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.ovpworld.org/licenses/OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf
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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ARM_OVPWORLD_ORG_PROCESSOR_ARM_CORTEX_A9MPX1__1_0
#define ARM_OVPWORLD_ORG_PROCESSOR_ARM_CORTEX_A9MPX1__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class arm_Cortex_A9MPx1 : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "semihosting", "armNewlib", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuMasterPort     GICRegisters;
    icmCpuInterrupt      SPI32;
    icmCpuInterrupt      SPI33;
    icmCpuInterrupt      SPI34;
    icmCpuInterrupt      SPI35;
    icmCpuInterrupt      SPI36;
    icmCpuInterrupt      SPI37;
    icmCpuInterrupt      SPI38;
    icmCpuInterrupt      SPI39;
    icmCpuInterrupt      SPI40;
    icmCpuInterrupt      SPI41;
    icmCpuInterrupt      SPI42;
    icmCpuInterrupt      SPI43;
    icmCpuInterrupt      SPI44;
    icmCpuInterrupt      SPI45;
    icmCpuInterrupt      SPI46;
    icmCpuInterrupt      SPI47;
    icmCpuInterrupt      SPI48;
    icmCpuInterrupt      SPI49;
    icmCpuInterrupt      SPI50;
    icmCpuInterrupt      SPI51;
    icmCpuInterrupt      SPI52;
    icmCpuInterrupt      SPI53;
    icmCpuInterrupt      SPI54;
    icmCpuInterrupt      SPI55;
    icmCpuInterrupt      SPI56;
    icmCpuInterrupt      SPI57;
    icmCpuInterrupt      SPI58;
    icmCpuInterrupt      SPI59;
    icmCpuInterrupt      SPI60;
    icmCpuInterrupt      SPI61;
    icmCpuInterrupt      SPI62;
    icmCpuInterrupt      SPI63;
    icmCpuInterrupt      SPI64;
    icmCpuInterrupt      SPI65;
    icmCpuInterrupt      SPI66;
    icmCpuInterrupt      SPI67;
    icmCpuInterrupt      SPI68;
    icmCpuInterrupt      SPI69;
    icmCpuInterrupt      SPI70;
    icmCpuInterrupt      SPI71;
    icmCpuInterrupt      SPI72;
    icmCpuInterrupt      SPI73;
    icmCpuInterrupt      SPI74;
    icmCpuInterrupt      SPI75;
    icmCpuInterrupt      SPI76;
    icmCpuInterrupt      SPI77;
    icmCpuInterrupt      SPI78;
    icmCpuInterrupt      SPI79;
    icmCpuInterrupt      SPI80;
    icmCpuInterrupt      SPI81;
    icmCpuInterrupt      SPI82;
    icmCpuInterrupt      SPI83;
    icmCpuInterrupt      SPI84;
    icmCpuInterrupt      SPI85;
    icmCpuInterrupt      SPI86;
    icmCpuInterrupt      SPI87;
    icmCpuInterrupt      SPI88;
    icmCpuInterrupt      SPI89;
    icmCpuInterrupt      SPI90;
    icmCpuInterrupt      SPI91;
    icmCpuInterrupt      SPI92;
    icmCpuInterrupt      SPI93;
    icmCpuInterrupt      SPI94;
    icmCpuInterrupt      SPI95;
    icmCpuInterrupt      SPIVector;
    icmCpuInterrupt      periphReset;
    icmCpuOutputNetPort  wdResetReq_CPU0;
    icmCpuInterrupt      wdReset_CPU0;
    icmCpuInterrupt      scuReset;
    icmCpuInterrupt      VINITHI_CPU0;
    icmCpuInterrupt      CFGEND_CPU0;
    icmCpuInterrupt      TEINIT_CPU0;
    icmCpuInterrupt      CFGNMFI_CPU0;
    icmCpuInterrupt      reset_CPU0;
    icmCpuInterrupt      fiq_CPU0;
    icmCpuInterrupt      irq_CPU0;
    icmCpuInterrupt      AXI_SLVERR_CPU0;
    icmCpuInterrupt      CP15SDISABLE_CPU0;

    arm_Cortex_A9MPx1(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "arm", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
    , GICRegisters (this, "GICRegisters", 32)
    , SPI32("SPI32", this)
    , SPI33("SPI33", this)
    , SPI34("SPI34", this)
    , SPI35("SPI35", this)
    , SPI36("SPI36", this)
    , SPI37("SPI37", this)
    , SPI38("SPI38", this)
    , SPI39("SPI39", this)
    , SPI40("SPI40", this)
    , SPI41("SPI41", this)
    , SPI42("SPI42", this)
    , SPI43("SPI43", this)
    , SPI44("SPI44", this)
    , SPI45("SPI45", this)
    , SPI46("SPI46", this)
    , SPI47("SPI47", this)
    , SPI48("SPI48", this)
    , SPI49("SPI49", this)
    , SPI50("SPI50", this)
    , SPI51("SPI51", this)
    , SPI52("SPI52", this)
    , SPI53("SPI53", this)
    , SPI54("SPI54", this)
    , SPI55("SPI55", this)
    , SPI56("SPI56", this)
    , SPI57("SPI57", this)
    , SPI58("SPI58", this)
    , SPI59("SPI59", this)
    , SPI60("SPI60", this)
    , SPI61("SPI61", this)
    , SPI62("SPI62", this)
    , SPI63("SPI63", this)
    , SPI64("SPI64", this)
    , SPI65("SPI65", this)
    , SPI66("SPI66", this)
    , SPI67("SPI67", this)
    , SPI68("SPI68", this)
    , SPI69("SPI69", this)
    , SPI70("SPI70", this)
    , SPI71("SPI71", this)
    , SPI72("SPI72", this)
    , SPI73("SPI73", this)
    , SPI74("SPI74", this)
    , SPI75("SPI75", this)
    , SPI76("SPI76", this)
    , SPI77("SPI77", this)
    , SPI78("SPI78", this)
    , SPI79("SPI79", this)
    , SPI80("SPI80", this)
    , SPI81("SPI81", this)
    , SPI82("SPI82", this)
    , SPI83("SPI83", this)
    , SPI84("SPI84", this)
    , SPI85("SPI85", this)
    , SPI86("SPI86", this)
    , SPI87("SPI87", this)
    , SPI88("SPI88", this)
    , SPI89("SPI89", this)
    , SPI90("SPI90", this)
    , SPI91("SPI91", this)
    , SPI92("SPI92", this)
    , SPI93("SPI93", this)
    , SPI94("SPI94", this)
    , SPI95("SPI95", this)
    , SPIVector("SPIVector", this)
    , periphReset("periphReset", this)
    , wdResetReq_CPU0("wdResetReq_CPU0", this)
    , wdReset_CPU0("wdReset_CPU0", this)
    , scuReset("scuReset", this)
    , VINITHI_CPU0("VINITHI_CPU0", this)
    , CFGEND_CPU0("CFGEND_CPU0", this)
    , TEINIT_CPU0("TEINIT_CPU0", this)
    , CFGNMFI_CPU0("CFGNMFI_CPU0", this)
    , reset_CPU0("reset_CPU0", this)
    , fiq_CPU0("fiq_CPU0", this)
    , irq_CPU0("irq_CPU0", this)
    , AXI_SLVERR_CPU0("AXI_SLVERR_CPU0", this)
    , CP15SDISABLE_CPU0("CP15SDISABLE_CPU0", this)
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
        GICRegisters.bindIfNotBound();
    }

    void dmi(bool on) {
        m_dmi = on;
        if(!on) {
            INSTRUCTION.invalidateDMI();
            DATA.invalidateDMI();
            GICRegisters.invalidateDMI();
        }
    }
}; /* class arm_Cortex_A9MPx1 */

#endif
