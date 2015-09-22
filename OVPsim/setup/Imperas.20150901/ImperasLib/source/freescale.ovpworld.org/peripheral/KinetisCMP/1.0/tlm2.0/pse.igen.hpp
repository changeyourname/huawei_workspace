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
//    Net input  ExtSample;
//    Net input  Vin1;
//    Net input  Vin2;
//    Net input  Input0;
//    Net input  Input1;
//    Net input  Input2;
//    Net input  Input3;
//    Net input  Input4;
//    Net input  Input5;
//    Net input  Input6;
//    Net input  Input7;
//    Net output  DacOutput;
//    Net output  CoutSoc;
//    Net output  Interrupt;
//    Net output  DmaReq;
//    Net output  CmpOPad;

#ifndef FREESCALE_OVPWORLD_ORG_PERIPHERAL_KINETISCMP__1_0
#define FREESCALE_OVPWORLD_ORG_PERIPHERAL_KINETISCMP__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class KinetisCMP : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "freescale.ovpworld.org", "peripheral", "KinetisCMP", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmInputNetPort Reset;
    icmInputNetPort ExtSample;
    icmInputNetPort Vin1;
    icmInputNetPort Vin2;
    icmInputNetPort Input0;
    icmInputNetPort Input1;
    icmInputNetPort Input2;
    icmInputNetPort Input3;
    icmInputNetPort Input4;
    icmInputNetPort Input5;
    icmInputNetPort Input6;
    icmInputNetPort Input7;
    icmOutputNetPort DacOutput;
    icmOutputNetPort CoutSoc;
    icmOutputNetPort Interrupt;
    icmOutputNetPort DmaReq;
    icmOutputNetPort CmpOPad;

    KinetisCMP(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x8) // static
        , Reset(this, "Reset")
        , ExtSample(this, "ExtSample")
        , Vin1(this, "Vin1")
        , Vin2(this, "Vin2")
        , Input0(this, "Input0")
        , Input1(this, "Input1")
        , Input2(this, "Input2")
        , Input3(this, "Input3")
        , Input4(this, "Input4")
        , Input5(this, "Input5")
        , Input6(this, "Input6")
        , Input7(this, "Input7")
        , DacOutput(this, "DacOutput")
        , CoutSoc(this, "CoutSoc")
        , Interrupt(this, "Interrupt")
        , DmaReq(this, "DmaReq")
        , CmpOPad(this, "CmpOPad")
    {
    }

}; /* class KinetisCMP */

#endif
