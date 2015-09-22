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
//    Master Port PCIconfigM
//    Master Port PCIackM
//    Slave Port busPort
//    Slave Port PCIconfigS
//    Slave Port PCIconfig
//    Net output  timerInt;

#ifndef MARVELL_OVPWORLD_ORG_PERIPHERAL_GT6412X__1_0
#define MARVELL_OVPWORLD_ORG_PERIPHERAL_GT6412X__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class GT6412x : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "marvell.ovpworld.org", "peripheral", "GT6412x", "1.0", "pse");
    }

  public:
    icmDynamicSlavePort busPort;
    icmSlavePort        PCIconfigS;
    icmDynamicSlavePort PCIconfig;
    icmMasterPort       PCIconfigM;
    icmMasterPort       PCIackM;
    icmOutputNetPort timerInt;

    GT6412x(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , busPort(this, "busPort", 32) // dynamic
        , PCIconfigS(this, "PCIconfigS", 0x10000) // static
        , PCIconfig(this, "PCIconfig", 16) // dynamic
        , PCIconfigM(this, "PCIconfigM", 16)
        , PCIackM(this, "PCIackM", 1)
        , timerInt(this, "timerInt")
    {
    }

    void before_end_of_elaboration() {
        PCIackM.bindIfNotBound();
    }
}; /* class GT6412x */

#endif
