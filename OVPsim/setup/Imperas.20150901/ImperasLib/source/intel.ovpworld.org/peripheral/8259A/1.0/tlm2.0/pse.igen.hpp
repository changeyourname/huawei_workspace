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
//    Master Port cascade
//    Slave Port io
//    Slave Port PCIackS
//    Slave Port elcr
//    Net input  ir0;
//    Net input  ir1;
//    Net input  ir2;
//    Net input  ir3;
//    Net input  ir4;
//    Net input  ir5;
//    Net input  ir6;
//    Net input  ir7;
//    Net inout  cas;
//    Net output  intp;

#ifndef INTEL_OVPWORLD_ORG_PERIPHERAL__8259A__1_0
#define INTEL_OVPWORLD_ORG_PERIPHERAL__8259A__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class _8259A : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "intel.ovpworld.org", "peripheral", "8259A", "1.0", "pse");
    }

  public:
    icmSlavePort        io;
    icmSlavePort        PCIackS;
    icmSlavePort        elcr;
    icmMasterPort       cascade;
    icmInputNetPort ir0;
    icmInputNetPort ir1;
    icmInputNetPort ir2;
    icmInputNetPort ir3;
    icmInputNetPort ir4;
    icmInputNetPort ir5;
    icmInputNetPort ir6;
    icmInputNetPort ir7;
    icmInoutNetPort cas;
    icmOutputNetPort intp;

    _8259A(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , io(this, "io", 0x2) // static
        , PCIackS(this, "PCIackS", 0x1) // static
        , elcr(this, "elcr", 0x1) // static
        , cascade(this, "cascade", 3)
        , ir0(this, "ir0")
        , ir1(this, "ir1")
        , ir2(this, "ir2")
        , ir3(this, "ir3")
        , ir4(this, "ir4")
        , ir5(this, "ir5")
        , ir6(this, "ir6")
        , ir7(this, "ir7")
        , cas(this, "cas")
        , intp(this, "intp")
    {
    }

    void before_end_of_elaboration() {
        cascade.bindIfNotBound();
    }
}; /* class _8259A */

#endif
