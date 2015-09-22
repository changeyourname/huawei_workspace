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
//    Slave Port TMTP0
//    Slave Port TMTP1
//    Net output  TOT0;
//    Net output  TOT1;
//    Net output  TTTTO0;
//    Net output  TTTT01;
//    Net output  TTTICC0;
//    Net output  TTTICC1;
//    Net output  TTTEQC0;
//    Net output  TTTEQC1;
//    Net output  INTTTCC0;
//    Net output  INTTTCC1;
//    Net output  INTTTOV;
//    Net output  INTTTEC;
//    Net input  TIT0;
//    Net input  TIT1;
//    Net input  TEVTT;
//    Net input  TTRGT;
//    Net input  TENCT0;
//    Net input  TENCT1;
//    Net input  TECRT;
//    Net input  TTTTI0;
//    Net input  TTTTI1;
//    Net input  TTTENC0;
//    Net input  TTTENC1;
//    Net input  TTTTRG;
//    Net input  TTTEVT;
//    Net input  TTTECR;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_TMT__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_TMT__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class tmt : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "tmt", "1.0", "pse");
    }

  public:
    icmSlavePort        TMTP0;
    icmSlavePort        TMTP1;
    icmOutputNetPort TOT0;
    icmOutputNetPort TOT1;
    icmOutputNetPort TTTTO0;
    icmOutputNetPort TTTT01;
    icmOutputNetPort TTTICC0;
    icmOutputNetPort TTTICC1;
    icmOutputNetPort TTTEQC0;
    icmOutputNetPort TTTEQC1;
    icmOutputNetPort INTTTCC0;
    icmOutputNetPort INTTTCC1;
    icmOutputNetPort INTTTOV;
    icmOutputNetPort INTTTEC;
    icmInputNetPort TIT0;
    icmInputNetPort TIT1;
    icmInputNetPort TEVTT;
    icmInputNetPort TTRGT;
    icmInputNetPort TENCT0;
    icmInputNetPort TENCT1;
    icmInputNetPort TECRT;
    icmInputNetPort TTTTI0;
    icmInputNetPort TTTTI1;
    icmInputNetPort TTTENC0;
    icmInputNetPort TTTENC1;
    icmInputNetPort TTTTRG;
    icmInputNetPort TTTEVT;
    icmInputNetPort TTTECR;

    tmt(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , TMTP0(this, "TMTP0", 0x10) // static
        , TMTP1(this, "TMTP1", 0x2) // static
        , TOT0(this, "TOT0")
        , TOT1(this, "TOT1")
        , TTTTO0(this, "TTTTO0")
        , TTTT01(this, "TTTT01")
        , TTTICC0(this, "TTTICC0")
        , TTTICC1(this, "TTTICC1")
        , TTTEQC0(this, "TTTEQC0")
        , TTTEQC1(this, "TTTEQC1")
        , INTTTCC0(this, "INTTTCC0")
        , INTTTCC1(this, "INTTTCC1")
        , INTTTOV(this, "INTTTOV")
        , INTTTEC(this, "INTTTEC")
        , TIT0(this, "TIT0")
        , TIT1(this, "TIT1")
        , TEVTT(this, "TEVTT")
        , TTRGT(this, "TTRGT")
        , TENCT0(this, "TENCT0")
        , TENCT1(this, "TENCT1")
        , TECRT(this, "TECRT")
        , TTTTI0(this, "TTTTI0")
        , TTTTI1(this, "TTTTI1")
        , TTTENC0(this, "TTTENC0")
        , TTTENC1(this, "TTTENC1")
        , TTTTRG(this, "TTTTRG")
        , TTTEVT(this, "TTTEVT")
        , TTTECR(this, "TTTECR")
    {
    }

}; /* class tmt */

#endif
