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
//    Slave Port LOGICP0
//    Slave Port LOGICP1
//    Slave Port LOGICP2
//    Slave Port LOGICP3
//    Net input  NMIIN;
//    Net input  INTDEDF;
//    Net input  INTDEDR;
//    Net input  INTDEDFR;
//    Net input  INTOSD;
//    Net input  INTP4;
//    Net input  INTUC0R;
//    Net input  INTP5;
//    Net input  INTUC1R;
//    Net input  INTBRG0;
//    Net input  INTBRG1;
//    Net input  INTCB0T;
//    Net input  INTUC2T;
//    Net input  INTCB0R;
//    Net input  INTUC2R;
//    Net input  INTP13;
//    Net input  INTCB0RE;
//    Net input  INTUC2RE;
//    Net input  INTDMA3;
//    Net input  INTFL;
//    Net output  NMIOUT;
//    Net output  INT0;
//    Net output  INT1;
//    Net output  INT6;
//    Net output  INT7;
//    Net output  INT75;
//    Net output  INT99;
//    Net output  INT100;
//    Net output  INT101;
//    Net output  INT116;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_UPD70F3441LOGIC__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_UPD70F3441LOGIC__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class UPD70F3441Logic : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "UPD70F3441Logic", "1.0", "pse");
    }

  public:
    icmSlavePort        LOGICP0;
    icmSlavePort        LOGICP1;
    icmSlavePort        LOGICP2;
    icmSlavePort        LOGICP3;
    icmInputNetPort NMIIN;
    icmInputNetPort INTDEDF;
    icmInputNetPort INTDEDR;
    icmInputNetPort INTDEDFR;
    icmInputNetPort INTOSD;
    icmInputNetPort INTP4;
    icmInputNetPort INTUC0R;
    icmInputNetPort INTP5;
    icmInputNetPort INTUC1R;
    icmInputNetPort INTBRG0;
    icmInputNetPort INTBRG1;
    icmInputNetPort INTCB0T;
    icmInputNetPort INTUC2T;
    icmInputNetPort INTCB0R;
    icmInputNetPort INTUC2R;
    icmInputNetPort INTP13;
    icmInputNetPort INTCB0RE;
    icmInputNetPort INTUC2RE;
    icmInputNetPort INTDMA3;
    icmInputNetPort INTFL;
    icmOutputNetPort NMIOUT;
    icmOutputNetPort INT0;
    icmOutputNetPort INT1;
    icmOutputNetPort INT6;
    icmOutputNetPort INT7;
    icmOutputNetPort INT75;
    icmOutputNetPort INT99;
    icmOutputNetPort INT100;
    icmOutputNetPort INT101;
    icmOutputNetPort INT116;

    UPD70F3441Logic(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , LOGICP0(this, "LOGICP0", 0x4) // static
        , LOGICP1(this, "LOGICP1", 0x76) // static
        , LOGICP2(this, "LOGICP2", 0xc) // static
        , LOGICP3(this, "LOGICP3", 0x1) // static
        , NMIIN(this, "NMIIN")
        , INTDEDF(this, "INTDEDF")
        , INTDEDR(this, "INTDEDR")
        , INTDEDFR(this, "INTDEDFR")
        , INTOSD(this, "INTOSD")
        , INTP4(this, "INTP4")
        , INTUC0R(this, "INTUC0R")
        , INTP5(this, "INTP5")
        , INTUC1R(this, "INTUC1R")
        , INTBRG0(this, "INTBRG0")
        , INTBRG1(this, "INTBRG1")
        , INTCB0T(this, "INTCB0T")
        , INTUC2T(this, "INTUC2T")
        , INTCB0R(this, "INTCB0R")
        , INTUC2R(this, "INTUC2R")
        , INTP13(this, "INTP13")
        , INTCB0RE(this, "INTCB0RE")
        , INTUC2RE(this, "INTUC2RE")
        , INTDMA3(this, "INTDMA3")
        , INTFL(this, "INTFL")
        , NMIOUT(this, "NMIOUT")
        , INT0(this, "INT0")
        , INT1(this, "INT1")
        , INT6(this, "INT6")
        , INT7(this, "INT7")
        , INT75(this, "INT75")
        , INT99(this, "INT99")
        , INT100(this, "INT100")
        , INT101(this, "INT101")
        , INT116(this, "INT116")
    {
    }

}; /* class UPD70F3441Logic */

#endif
