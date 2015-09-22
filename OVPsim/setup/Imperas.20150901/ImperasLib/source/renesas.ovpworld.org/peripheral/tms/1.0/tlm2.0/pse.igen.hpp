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
//    Slave Port TMSP0
//    Net output  TOS0;
//    Net output  TOS1;
//    Net output  TOS2;
//    Net output  TOS3;
//    Net output  TOS4;
//    Net output  TOS5;
//    Net output  TOS6;
//    Net output  TOS7;
//    Net output  TSADTRG0;
//    Net output  TSADTRG1;
//    Net output  TSAEDO;
//    Net output  TSESG;
//    Net output  TSTSF;
//    Net output  INTTSCC0;
//    Net output  INTTSCC1;
//    Net output  INTTSCC2;
//    Net output  INTTSCC3;
//    Net output  INTTSCC4;
//    Net output  INTTSCC5;
//    Net output  INTTSCD0;
//    Net output  INTTSOD;
//    Net output  INTTSOV;
//    Net output  INTTSER;
//    Net output  INTTSWN;
//    Net input  TTRGS;
//    Net input  TEVTS;
//    Net input  TAPTS0;
//    Net input  TAPTS1;
//    Net input  TAPTS2;
//    Net input  ESO;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_TMS__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_TMS__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class tms : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "tms", "1.0", "pse");
    }

  public:
    icmSlavePort        TMSP0;
    icmOutputNetPort TOS0;
    icmOutputNetPort TOS1;
    icmOutputNetPort TOS2;
    icmOutputNetPort TOS3;
    icmOutputNetPort TOS4;
    icmOutputNetPort TOS5;
    icmOutputNetPort TOS6;
    icmOutputNetPort TOS7;
    icmOutputNetPort TSADTRG0;
    icmOutputNetPort TSADTRG1;
    icmOutputNetPort TSAEDO;
    icmOutputNetPort TSESG;
    icmOutputNetPort TSTSF;
    icmOutputNetPort INTTSCC0;
    icmOutputNetPort INTTSCC1;
    icmOutputNetPort INTTSCC2;
    icmOutputNetPort INTTSCC3;
    icmOutputNetPort INTTSCC4;
    icmOutputNetPort INTTSCC5;
    icmOutputNetPort INTTSCD0;
    icmOutputNetPort INTTSOD;
    icmOutputNetPort INTTSOV;
    icmOutputNetPort INTTSER;
    icmOutputNetPort INTTSWN;
    icmInputNetPort TTRGS;
    icmInputNetPort TEVTS;
    icmInputNetPort TAPTS0;
    icmInputNetPort TAPTS1;
    icmInputNetPort TAPTS2;
    icmInputNetPort ESO;

    tms(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , TMSP0(this, "TMSP0", 0x2a) // static
        , TOS0(this, "TOS0")
        , TOS1(this, "TOS1")
        , TOS2(this, "TOS2")
        , TOS3(this, "TOS3")
        , TOS4(this, "TOS4")
        , TOS5(this, "TOS5")
        , TOS6(this, "TOS6")
        , TOS7(this, "TOS7")
        , TSADTRG0(this, "TSADTRG0")
        , TSADTRG1(this, "TSADTRG1")
        , TSAEDO(this, "TSAEDO")
        , TSESG(this, "TSESG")
        , TSTSF(this, "TSTSF")
        , INTTSCC0(this, "INTTSCC0")
        , INTTSCC1(this, "INTTSCC1")
        , INTTSCC2(this, "INTTSCC2")
        , INTTSCC3(this, "INTTSCC3")
        , INTTSCC4(this, "INTTSCC4")
        , INTTSCC5(this, "INTTSCC5")
        , INTTSCD0(this, "INTTSCD0")
        , INTTSOD(this, "INTTSOD")
        , INTTSOV(this, "INTTSOV")
        , INTTSER(this, "INTTSER")
        , INTTSWN(this, "INTTSWN")
        , TTRGS(this, "TTRGS")
        , TEVTS(this, "TEVTS")
        , TAPTS0(this, "TAPTS0")
        , TAPTS1(this, "TAPTS1")
        , TAPTS2(this, "TAPTS2")
        , ESO(this, "ESO")
    {
    }

}; /* class tms */

#endif
