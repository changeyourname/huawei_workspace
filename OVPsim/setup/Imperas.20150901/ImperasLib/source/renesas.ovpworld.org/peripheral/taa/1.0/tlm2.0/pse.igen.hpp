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
//    Slave Port TAAP0
//    Net output  TOAA0;
//    Net output  TOAA1;
//    Net output  INTTAAOV;
//    Net output  INTTAACC0;
//    Net output  INTTAACC1;
//    Net input  TIAA0;
//    Net input  TIAA1;
//    Net input  TTRGAA;
//    Net input  TEVTAA;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_TAA__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_TAA__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class taa : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "taa", "1.0", "pse");
    }

  public:
    icmSlavePort        TAAP0;
    icmOutputNetPort TOAA0;
    icmOutputNetPort TOAA1;
    icmOutputNetPort INTTAAOV;
    icmOutputNetPort INTTAACC0;
    icmOutputNetPort INTTAACC1;
    icmInputNetPort TIAA0;
    icmInputNetPort TIAA1;
    icmInputNetPort TTRGAA;
    icmInputNetPort TEVTAA;

    taa(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , TAAP0(this, "TAAP0", 0x10) // static
        , TOAA0(this, "TOAA0")
        , TOAA1(this, "TOAA1")
        , INTTAAOV(this, "INTTAAOV")
        , INTTAACC0(this, "INTTAACC0")
        , INTTAACC1(this, "INTTAACC1")
        , TIAA0(this, "TIAA0")
        , TIAA1(this, "TIAA1")
        , TTRGAA(this, "TTRGAA")
        , TEVTAA(this, "TEVTAA")
    {
    }

}; /* class taa */

#endif
