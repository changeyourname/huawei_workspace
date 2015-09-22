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
//    Net input  clk0;
//    Net input  gate0;
//    Net output  out0;
//    Net input  clk1;
//    Net input  gate1;
//    Net output  out1;
//    Net input  clk2;
//    Net input  gate2;
//    Net output  out2;

#ifndef INTEL_OVPWORLD_ORG_PERIPHERAL__8253__1_0
#define INTEL_OVPWORLD_ORG_PERIPHERAL__8253__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class _8253 : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "intel.ovpworld.org", "peripheral", "8253", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmInputNetPort clk0;
    icmInputNetPort gate0;
    icmOutputNetPort out0;
    icmInputNetPort clk1;
    icmInputNetPort gate1;
    icmOutputNetPort out1;
    icmInputNetPort clk2;
    icmInputNetPort gate2;
    icmOutputNetPort out2;

    _8253(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x4) // static
        , clk0(this, "clk0")
        , gate0(this, "gate0")
        , out0(this, "out0")
        , clk1(this, "clk1")
        , gate1(this, "gate1")
        , out1(this, "out1")
        , clk2(this, "clk2")
        , gate2(this, "gate2")
        , out2(this, "out2")
    {
    }

}; /* class _8253 */

#endif
