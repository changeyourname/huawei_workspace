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
//    Slave Port bp1
//    Net inout  P0;
//    Net inout  P1;
//    Net inout  P2;
//    Net inout  P3;
//    Net inout  P4;
//    Net inout  P5;
//    Net inout  P6;
//    Net inout  P7;
//    Net inout  P8;
//    Net inout  P9;
//    Net inout  P10;
//    Net inout  P11;
//    Net inout  P12;
//    Net inout  P13;
//    Net inout  P14;
//    Net inout  P15;
//    Net inout  P16;
//    Net inout  P17;
//    Net inout  P18;
//    Net inout  P19;
//    Net inout  P20;
//    Net inout  P21;
//    Net inout  P22;
//    Net inout  P23;
//    Net inout  P24;
//    Net inout  P25;
//    Net inout  P26;
//    Net inout  P27;
//    Net inout  P28;
//    Net inout  P29;
//    Net inout  P30;
//    Net inout  P31;
//    Net output  IRQ;

#ifndef ATMEL_OVPWORLD_ORG_PERIPHERAL_PARALLELIOCONTROLLER__1_0
#define ATMEL_OVPWORLD_ORG_PERIPHERAL_PARALLELIOCONTROLLER__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class ParallelIOController : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "atmel.ovpworld.org", "peripheral", "ParallelIOController", "1.0", "pse");
    }

  public:
    icmSlavePort        bp1;
    icmInoutNetPort P0;
    icmInoutNetPort P1;
    icmInoutNetPort P2;
    icmInoutNetPort P3;
    icmInoutNetPort P4;
    icmInoutNetPort P5;
    icmInoutNetPort P6;
    icmInoutNetPort P7;
    icmInoutNetPort P8;
    icmInoutNetPort P9;
    icmInoutNetPort P10;
    icmInoutNetPort P11;
    icmInoutNetPort P12;
    icmInoutNetPort P13;
    icmInoutNetPort P14;
    icmInoutNetPort P15;
    icmInoutNetPort P16;
    icmInoutNetPort P17;
    icmInoutNetPort P18;
    icmInoutNetPort P19;
    icmInoutNetPort P20;
    icmInoutNetPort P21;
    icmInoutNetPort P22;
    icmInoutNetPort P23;
    icmInoutNetPort P24;
    icmInoutNetPort P25;
    icmInoutNetPort P26;
    icmInoutNetPort P27;
    icmInoutNetPort P28;
    icmInoutNetPort P29;
    icmInoutNetPort P30;
    icmInoutNetPort P31;
    icmOutputNetPort IRQ;

    ParallelIOController(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bp1(this, "bp1", 0x4000) // static
        , P0(this, "P0")
        , P1(this, "P1")
        , P2(this, "P2")
        , P3(this, "P3")
        , P4(this, "P4")
        , P5(this, "P5")
        , P6(this, "P6")
        , P7(this, "P7")
        , P8(this, "P8")
        , P9(this, "P9")
        , P10(this, "P10")
        , P11(this, "P11")
        , P12(this, "P12")
        , P13(this, "P13")
        , P14(this, "P14")
        , P15(this, "P15")
        , P16(this, "P16")
        , P17(this, "P17")
        , P18(this, "P18")
        , P19(this, "P19")
        , P20(this, "P20")
        , P21(this, "P21")
        , P22(this, "P22")
        , P23(this, "P23")
        , P24(this, "P24")
        , P25(this, "P25")
        , P26(this, "P26")
        , P27(this, "P27")
        , P28(this, "P28")
        , P29(this, "P29")
        , P30(this, "P30")
        , P31(this, "P31")
        , IRQ(this, "IRQ")
    {
    }

}; /* class ParallelIOController */

#endif
