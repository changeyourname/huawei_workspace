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
//    Slave Port BRGP0
//    Net output  BRGOUT;
//    Net output  INTBRG;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_BRG__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_BRG__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class brg : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "brg", "1.0", "pse");
    }

  public:
    icmSlavePort        BRGP0;
    icmOutputNetPort BRGOUT;
    icmOutputNetPort INTBRG;

    brg(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , BRGP0(this, "BRGP0", 0x2) // static
        , BRGOUT(this, "BRGOUT")
        , INTBRG(this, "INTBRG")
    {
    }

}; /* class brg */

#endif
