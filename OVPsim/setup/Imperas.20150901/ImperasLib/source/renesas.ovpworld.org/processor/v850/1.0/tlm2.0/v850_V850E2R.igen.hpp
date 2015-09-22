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

#ifndef RENESAS_OVPWORLD_ORG_PROCESSOR_V850_V850E2R__1_0
#define RENESAS_OVPWORLD_ORG_PROCESSOR_V850_V850E2R__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class v850_V850E2R : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "processor", "v850", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "semihosting", "v850Newlib", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      intp;
    icmCpuInterrupt      nmi0;
    icmCpuInterrupt      nmi1;
    icmCpuInterrupt      nmi2;
    icmCpuInterrupt      reset;
    icmCpuOutputNetPort  mireti;
    icmCpuOutputNetPort  intack;

    v850_V850E2R(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "v850", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
    , intp("intp", this)
    , nmi0("nmi0", this)
    , nmi1("nmi1", this)
    , nmi2("nmi2", this)
    , reset("reset", this)
    , mireti("mireti", this)
    , intack("intack", this)
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
}; /* class v850_V850E2R */

#endif
