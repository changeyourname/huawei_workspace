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
//    Slave Port ADCP0
//    Slave Port ADCP1
//    Net output  INTAD;
//    Net output  ADDMARQ;
//    Net input  INTADEN;
//    Net input  ADTRG;
//    Net input  TS0ADT0;
//    Net input  TS0ADT1;
//    Net input  INTTS0OD;
//    Net input  INTTS0CD;
//    Net input  TS1ADT0;
//    Net input  TS1ADT1;
//    Net input  INTTS1OD;
//    Net input  INTTS1CD;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_ADC__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_ADC__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class adc : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "adc", "1.0", "pse");
    }

  public:
    icmSlavePort        ADCP0;
    icmSlavePort        ADCP1;
    icmOutputNetPort INTAD;
    icmOutputNetPort ADDMARQ;
    icmInputNetPort INTADEN;
    icmInputNetPort ADTRG;
    icmInputNetPort TS0ADT0;
    icmInputNetPort TS0ADT1;
    icmInputNetPort INTTS0OD;
    icmInputNetPort INTTS0CD;
    icmInputNetPort TS1ADT0;
    icmInputNetPort TS1ADT1;
    icmInputNetPort INTTS1OD;
    icmInputNetPort INTTS1CD;

    adc(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , ADCP0(this, "ADCP0", 0x30) // static
        , ADCP1(this, "ADCP1", 0x1) // static
        , INTAD(this, "INTAD")
        , ADDMARQ(this, "ADDMARQ")
        , INTADEN(this, "INTADEN")
        , ADTRG(this, "ADTRG")
        , TS0ADT0(this, "TS0ADT0")
        , TS0ADT1(this, "TS0ADT1")
        , INTTS0OD(this, "INTTS0OD")
        , INTTS0CD(this, "INTTS0CD")
        , TS1ADT0(this, "TS1ADT0")
        , TS1ADT1(this, "TS1ADT1")
        , INTTS1OD(this, "INTTS1OD")
        , INTTS1CD(this, "INTTS1CD")
    {
    }

}; /* class adc */

#endif
