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

#ifndef ARC_OVPWORLD_ORG_PROCESSOR_ARC_0X22__1_0
#define ARC_OVPWORLD_ORG_PROCESSOR_ARC_0X22__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class arc_0x22 : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "arc.ovpworld.org", "processor", "arc", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      reset;
    icmCpuOutputNetPort  watchdog;
    icmCpuInterrupt      irq4;
    icmCpuInterrupt      irq5;
    icmCpuInterrupt      irq6;
    icmCpuInterrupt      irq8;
    icmCpuInterrupt      irq9;
    icmCpuInterrupt      irq10;
    icmCpuInterrupt      irq11;
    icmCpuInterrupt      irq12;
    icmCpuInterrupt      irq13;
    icmCpuInterrupt      irq14;
    icmCpuInterrupt      irq15;

    arc_0x22(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "arc", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
    , reset("reset", this)
    , watchdog("watchdog", this)
    , irq4("irq4", this)
    , irq5("irq5", this)
    , irq6("irq6", this)
    , irq8("irq8", this)
    , irq9("irq9", this)
    , irq10("irq10", this)
    , irq11("irq11", this)
    , irq12("irq12", this)
    , irq13("irq13", this)
    , irq14("irq14", this)
    , irq15("irq15", this)
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
}; /* class arc_0x22 */

#endif
