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

#ifndef IMGTEC_OVPWORLD_ORG_PROCESSOR_MIPS32__1_0
#define IMGTEC_OVPWORLD_ORG_PROCESSOR_MIPS32__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class mips32 : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "imgtec.ovpworld.org", "processor", "mips32", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "semihosting", "mips32SDE", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      reset;
    icmCpuInterrupt      dint;
    icmCpuInterrupt      hwint0;
    icmCpuInterrupt      hwint1;
    icmCpuInterrupt      hwint2;
    icmCpuInterrupt      hwint3;
    icmCpuInterrupt      hwint4;
    icmCpuInterrupt      hwint5;
    icmCpuInterrupt      hwint6;
    icmCpuInterrupt      hwint7;
    icmCpuInterrupt      nmi;
    icmCpuInterrupt      EICPresent;
    icmCpuInterrupt      EIC_RIPL;
    icmCpuInterrupt      EIC_EICSS;
    icmCpuInterrupt      EIC_VectorNum;
    icmCpuInterrupt      EIC_VectorOffset;
    icmCpuInterrupt      EIC_GID;
    icmCpuOutputNetPort  intISS;
    icmCpuOutputNetPort  causeTI;
    icmCpuOutputNetPort  causeIP0;
    icmCpuOutputNetPort  causeIP1;
    icmCpuInterrupt      Guest_EIC_RIPL;
    icmCpuInterrupt      Guest_EIC_EICSS;
    icmCpuInterrupt      Guest_EIC_VectorNum;
    icmCpuInterrupt      Guest_EIC_VectorOffset;
    icmCpuInterrupt      Guest_EIC_GID;
    icmCpuOutputNetPort  Guest_intISS;
    icmCpuOutputNetPort  Guest_causeTI;
    icmCpuOutputNetPort  Guest_causeIP0;
    icmCpuOutputNetPort  Guest_causeIP1;

    mips32(
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
    , reset("reset", this)
    , dint("dint", this)
    , hwint0("hwint0", this)
    , hwint1("hwint1", this)
    , hwint2("hwint2", this)
    , hwint3("hwint3", this)
    , hwint4("hwint4", this)
    , hwint5("hwint5", this)
    , hwint6("hwint6", this)
    , hwint7("hwint7", this)
    , nmi("nmi", this)
    , EICPresent("EICPresent", this)
    , EIC_RIPL("EIC_RIPL", this)
    , EIC_EICSS("EIC_EICSS", this)
    , EIC_VectorNum("EIC_VectorNum", this)
    , EIC_VectorOffset("EIC_VectorOffset", this)
    , EIC_GID("EIC_GID", this)
    , intISS("intISS", this)
    , causeTI("causeTI", this)
    , causeIP0("causeIP0", this)
    , causeIP1("causeIP1", this)
    , Guest_EIC_RIPL("Guest.EIC_RIPL", this)
    , Guest_EIC_EICSS("Guest.EIC_EICSS", this)
    , Guest_EIC_VectorNum("Guest.EIC_VectorNum", this)
    , Guest_EIC_VectorOffset("Guest.EIC_VectorOffset", this)
    , Guest_EIC_GID("Guest.EIC_GID", this)
    , Guest_intISS("Guest.intISS", this)
    , Guest_causeTI("Guest.causeTI", this)
    , Guest_causeIP0("Guest.causeIP0", this)
    , Guest_causeIP1("Guest.causeIP1", this)
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
}; /* class mips32 */

#endif
