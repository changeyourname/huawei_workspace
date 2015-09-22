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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MIPS_OVPWORLD_ORG_PROCESSOR_MIPS32_INTERAPTIVUP__1_0
#define MIPS_OVPWORLD_ORG_PROCESSOR_MIPS32_INTERAPTIVUP__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class mips32_interAptivUP : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "semihosting", "mips32SDE", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      yq;
    icmCpuInterrupt      reset;
    icmCpuInterrupt      dint;
    icmCpuInterrupt      SI_UseExceptionBase;
    icmCpuInterrupt      SI_ExceptionBase;
    icmCpuInterrupt      SI_EVAReset;
    icmCpuInterrupt      SI_ExceptionBasePA;
    icmCpuInterrupt      SI_ExceptionBaseMask;
    icmCpuInterrupt      hwint0_VPE0;
    icmCpuInterrupt      hwint1_VPE0;
    icmCpuInterrupt      hwint2_VPE0;
    icmCpuInterrupt      hwint3_VPE0;
    icmCpuInterrupt      hwint4_VPE0;
    icmCpuInterrupt      hwint5_VPE0;
    icmCpuInterrupt      nmi_VPE0;
    icmCpuInterrupt      hwint0;
    icmCpuInterrupt      hwint0_VPE1;
    icmCpuInterrupt      hwint1_VPE1;
    icmCpuInterrupt      hwint2_VPE1;
    icmCpuInterrupt      hwint3_VPE1;
    icmCpuInterrupt      hwint4_VPE1;
    icmCpuInterrupt      hwint5_VPE1;
    icmCpuInterrupt      nmi_VPE1;

    mips32_interAptivUP(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "mips32", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
    , yq("yq", this)
    , reset("reset", this)
    , dint("dint", this)
    , SI_UseExceptionBase("SI_UseExceptionBase", this)
    , SI_ExceptionBase("SI_ExceptionBase", this)
    , SI_EVAReset("SI_EVAReset", this)
    , SI_ExceptionBasePA("SI_ExceptionBasePA", this)
    , SI_ExceptionBaseMask("SI_ExceptionBaseMask", this)
    , hwint0_VPE0("hwint0_VPE0", this)
    , hwint1_VPE0("hwint1_VPE0", this)
    , hwint2_VPE0("hwint2_VPE0", this)
    , hwint3_VPE0("hwint3_VPE0", this)
    , hwint4_VPE0("hwint4_VPE0", this)
    , hwint5_VPE0("hwint5_VPE0", this)
    , nmi_VPE0("nmi_VPE0", this)
    , hwint0("hwint0", this)
    , hwint0_VPE1("hwint0_VPE1", this)
    , hwint1_VPE1("hwint1_VPE1", this)
    , hwint2_VPE1("hwint2_VPE1", this)
    , hwint3_VPE1("hwint3_VPE1", this)
    , hwint4_VPE1("hwint4_VPE1", this)
    , hwint5_VPE1("hwint5_VPE1", this)
    , nmi_VPE1("nmi_VPE1", this)
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        m_dmi = on;
        if(!on) {
            INSTRUCTION.invalidateDMI();
            DATA.invalidateDMI();
        }
    }
}; /* class mips32_interAptivUP */

#endif
