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

#ifndef POSEDGESOFT_OVPWORLD_ORG_PROCESSOR_M16C__1_0
#define POSEDGESOFT_OVPWORLD_ORG_PROCESSOR_M16C__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class m16c : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "posedgesoft.ovpworld.org", "processor", "m16c", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "posedgesoft.ovpworld.org", "semihosting", "m16cNewlib", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      reset;
    icmCpuInterrupt      nmi;
    icmCpuInterrupt      int_per;
    icmCpuOutputNetPort  int_ack;

    m16c(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "m16c", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
    , reset("reset", this)
    , nmi("nmi", this)
    , int_per("int_per", this)
    , int_ack("int_ack", this)
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
}; /* class m16c */

#endif
