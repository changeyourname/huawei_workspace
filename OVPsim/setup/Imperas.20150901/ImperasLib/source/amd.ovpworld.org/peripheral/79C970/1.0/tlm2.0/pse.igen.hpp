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

// MODEL IO:
//    Master Port dmaPort
//    Slave Port busPort
//    Slave Port PCIconfig
//    Net output  intOut0;

#ifndef AMD_OVPWORLD_ORG_PERIPHERAL__79C970__1_0
#define AMD_OVPWORLD_ORG_PERIPHERAL__79C970__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class _79C970 : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "amd.ovpworld.org", "peripheral", "79C970", "1.0", "pse");
    }

  public:
    icmDynamicSlavePort busPort;
    icmDynamicSlavePort PCIconfig;
    icmMasterPort       dmaPort;
    icmOutputNetPort intOut0;

    _79C970(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , busPort(this, "busPort", 32) // dynamic
        , PCIconfig(this, "PCIconfig", 32) // dynamic
        , dmaPort(this, "dmaPort", 32)
        , intOut0(this, "intOut0")
    {
    }

    void before_end_of_elaboration() {
        dmaPort.bindIfNotBound();
    }
}; /* class _79C970 */

#endif
