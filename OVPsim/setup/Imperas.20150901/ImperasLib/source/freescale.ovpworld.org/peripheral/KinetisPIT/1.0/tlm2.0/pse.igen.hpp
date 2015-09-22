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
//    Slave Port bport1
//    Net input  Reset;
//    Net output  irq0;
//    Net output  trg0;
//    Net output  irq1;
//    Net output  trg1;
//    Net output  irq2;
//    Net output  trg2;
//    Net output  irq3;
//    Net output  trg3;

#ifndef FREESCALE_OVPWORLD_ORG_PERIPHERAL_KINETISPIT__1_0
#define FREESCALE_OVPWORLD_ORG_PERIPHERAL_KINETISPIT__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class KinetisPIT : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "freescale.ovpworld.org", "peripheral", "KinetisPIT", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmInputNetPort Reset;
    icmOutputNetPort irq0;
    icmOutputNetPort trg0;
    icmOutputNetPort irq1;
    icmOutputNetPort trg1;
    icmOutputNetPort irq2;
    icmOutputNetPort trg2;
    icmOutputNetPort irq3;
    icmOutputNetPort trg3;

    KinetisPIT(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x1000) // static
        , Reset(this, "Reset")
        , irq0(this, "irq0")
        , trg0(this, "trg0")
        , irq1(this, "irq1")
        , trg1(this, "trg1")
        , irq2(this, "irq2")
        , trg2(this, "trg2")
        , irq3(this, "irq3")
        , trg3(this, "trg3")
    {
    }

}; /* class KinetisPIT */

#endif
