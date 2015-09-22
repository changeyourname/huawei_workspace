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
//    Net output  irq;
//    Net output  fiq;
//    Net input  ir0;
//    Net input  ir1;
//    Net input  ir2;
//    Net input  ir3;
//    Net input  ir4;
//    Net input  ir5;
//    Net input  ir6;
//    Net input  ir7;
//    Net input  ir8;
//    Net input  ir9;
//    Net input  ir10;
//    Net input  ir11;
//    Net input  ir12;
//    Net input  ir13;
//    Net input  ir14;
//    Net input  ir15;
//    Net input  ir16;
//    Net input  ir17;
//    Net input  ir18;
//    Net input  ir19;
//    Net input  ir20;
//    Net input  ir21;
//    Net input  ir22;
//    Net input  ir23;
//    Net input  ir24;
//    Net input  ir25;
//    Net input  ir26;
//    Net input  ir27;
//    Net input  ir28;
//    Net input  ir29;
//    Net input  ir30;
//    Net input  ir31;

#ifndef ARM_OVPWORLD_ORG_PERIPHERAL_INTICP__1_0
#define ARM_OVPWORLD_ORG_PERIPHERAL_INTICP__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class IntICP : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "peripheral", "IntICP", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmOutputNetPort irq;
    icmOutputNetPort fiq;
    icmInputNetPort ir0;
    icmInputNetPort ir1;
    icmInputNetPort ir2;
    icmInputNetPort ir3;
    icmInputNetPort ir4;
    icmInputNetPort ir5;
    icmInputNetPort ir6;
    icmInputNetPort ir7;
    icmInputNetPort ir8;
    icmInputNetPort ir9;
    icmInputNetPort ir10;
    icmInputNetPort ir11;
    icmInputNetPort ir12;
    icmInputNetPort ir13;
    icmInputNetPort ir14;
    icmInputNetPort ir15;
    icmInputNetPort ir16;
    icmInputNetPort ir17;
    icmInputNetPort ir18;
    icmInputNetPort ir19;
    icmInputNetPort ir20;
    icmInputNetPort ir21;
    icmInputNetPort ir22;
    icmInputNetPort ir23;
    icmInputNetPort ir24;
    icmInputNetPort ir25;
    icmInputNetPort ir26;
    icmInputNetPort ir27;
    icmInputNetPort ir28;
    icmInputNetPort ir29;
    icmInputNetPort ir30;
    icmInputNetPort ir31;

    IntICP(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x1000) // static
        , irq(this, "irq")
        , fiq(this, "fiq")
        , ir0(this, "ir0")
        , ir1(this, "ir1")
        , ir2(this, "ir2")
        , ir3(this, "ir3")
        , ir4(this, "ir4")
        , ir5(this, "ir5")
        , ir6(this, "ir6")
        , ir7(this, "ir7")
        , ir8(this, "ir8")
        , ir9(this, "ir9")
        , ir10(this, "ir10")
        , ir11(this, "ir11")
        , ir12(this, "ir12")
        , ir13(this, "ir13")
        , ir14(this, "ir14")
        , ir15(this, "ir15")
        , ir16(this, "ir16")
        , ir17(this, "ir17")
        , ir18(this, "ir18")
        , ir19(this, "ir19")
        , ir20(this, "ir20")
        , ir21(this, "ir21")
        , ir22(this, "ir22")
        , ir23(this, "ir23")
        , ir24(this, "ir24")
        , ir25(this, "ir25")
        , ir26(this, "ir26")
        , ir27(this, "ir27")
        , ir28(this, "ir28")
        , ir29(this, "ir29")
        , ir30(this, "ir30")
        , ir31(this, "ir31")
    {
    }

}; /* class IntICP */

#endif
