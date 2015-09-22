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
//    Slave Port CSIEP0
//    Net output  INTCEOF;
//    Net output  INTCEC;
//    Net output  SOE;
//    Net output  SCSE0;
//    Net output  SCSE1;
//    Net output  SCSE2;
//    Net output  SCSE3;
//    Net output  SCSE4;
//    Net output  SCSE5;
//    Net output  SCSE6;
//    Net output  SCSE7;
//    Net input  SIE;
//    Net inout  SCKE;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_CSIE__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_CSIE__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class csie : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "csie", "1.0", "pse");
    }

  public:
    icmSlavePort        CSIEP0;
    icmOutputNetPort INTCEOF;
    icmOutputNetPort INTCEC;
    icmOutputNetPort SOE;
    icmOutputNetPort SCSE0;
    icmOutputNetPort SCSE1;
    icmOutputNetPort SCSE2;
    icmOutputNetPort SCSE3;
    icmOutputNetPort SCSE4;
    icmOutputNetPort SCSE5;
    icmOutputNetPort SCSE6;
    icmOutputNetPort SCSE7;
    icmInputNetPort SIE;
    icmInoutNetPort SCKE;

    csie(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , CSIEP0(this, "CSIEP0", 0x20) // static
        , INTCEOF(this, "INTCEOF")
        , INTCEC(this, "INTCEC")
        , SOE(this, "SOE")
        , SCSE0(this, "SCSE0")
        , SCSE1(this, "SCSE1")
        , SCSE2(this, "SCSE2")
        , SCSE3(this, "SCSE3")
        , SCSE4(this, "SCSE4")
        , SCSE5(this, "SCSE5")
        , SCSE6(this, "SCSE6")
        , SCSE7(this, "SCSE7")
        , SIE(this, "SIE")
        , SCKE(this, "SCKE")
    {
    }

}; /* class csie */

#endif
