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
//    Master Port MREAD
//    Master Port MWRITE
//    Slave Port bport1
//    Net input  Reset;
//    Net input  eDMARequest;
//    Net output  eDMADone;
//    Net output  errorInterrupt;
//    Net output  dmaInterrupt_ch0;
//    Net output  dmaInterrupt_ch1;
//    Net output  dmaInterrupt_ch2;
//    Net output  dmaInterrupt_ch3;
//    Net output  dmaInterrupt_ch4;
//    Net output  dmaInterrupt_ch5;
//    Net output  dmaInterrupt_ch6;
//    Net output  dmaInterrupt_ch7;
//    Net output  dmaInterrupt_ch8;
//    Net output  dmaInterrupt_ch9;
//    Net output  dmaInterrupt_ch10;
//    Net output  dmaInterrupt_ch11;
//    Net output  dmaInterrupt_ch12;
//    Net output  dmaInterrupt_ch13;
//    Net output  dmaInterrupt_ch14;
//    Net output  dmaInterrupt_ch15;

#ifndef FREESCALE_OVPWORLD_ORG_PERIPHERAL_VYBRIDDMA__1_0
#define FREESCALE_OVPWORLD_ORG_PERIPHERAL_VYBRIDDMA__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class VybridDMA : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "freescale.ovpworld.org", "peripheral", "VybridDMA", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmMasterPort       MREAD;
    icmMasterPort       MWRITE;
    icmInputNetPort Reset;
    icmInputNetPort eDMARequest;
    icmOutputNetPort eDMADone;
    icmOutputNetPort errorInterrupt;
    icmOutputNetPort dmaInterrupt_ch0;
    icmOutputNetPort dmaInterrupt_ch1;
    icmOutputNetPort dmaInterrupt_ch2;
    icmOutputNetPort dmaInterrupt_ch3;
    icmOutputNetPort dmaInterrupt_ch4;
    icmOutputNetPort dmaInterrupt_ch5;
    icmOutputNetPort dmaInterrupt_ch6;
    icmOutputNetPort dmaInterrupt_ch7;
    icmOutputNetPort dmaInterrupt_ch8;
    icmOutputNetPort dmaInterrupt_ch9;
    icmOutputNetPort dmaInterrupt_ch10;
    icmOutputNetPort dmaInterrupt_ch11;
    icmOutputNetPort dmaInterrupt_ch12;
    icmOutputNetPort dmaInterrupt_ch13;
    icmOutputNetPort dmaInterrupt_ch14;
    icmOutputNetPort dmaInterrupt_ch15;

    VybridDMA(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x2000) // static
        , MREAD(this, "MREAD", 32)
        , MWRITE(this, "MWRITE", 32)
        , Reset(this, "Reset")
        , eDMARequest(this, "eDMARequest")
        , eDMADone(this, "eDMADone")
        , errorInterrupt(this, "errorInterrupt")
        , dmaInterrupt_ch0(this, "dmaInterrupt_ch0")
        , dmaInterrupt_ch1(this, "dmaInterrupt_ch1")
        , dmaInterrupt_ch2(this, "dmaInterrupt_ch2")
        , dmaInterrupt_ch3(this, "dmaInterrupt_ch3")
        , dmaInterrupt_ch4(this, "dmaInterrupt_ch4")
        , dmaInterrupt_ch5(this, "dmaInterrupt_ch5")
        , dmaInterrupt_ch6(this, "dmaInterrupt_ch6")
        , dmaInterrupt_ch7(this, "dmaInterrupt_ch7")
        , dmaInterrupt_ch8(this, "dmaInterrupt_ch8")
        , dmaInterrupt_ch9(this, "dmaInterrupt_ch9")
        , dmaInterrupt_ch10(this, "dmaInterrupt_ch10")
        , dmaInterrupt_ch11(this, "dmaInterrupt_ch11")
        , dmaInterrupt_ch12(this, "dmaInterrupt_ch12")
        , dmaInterrupt_ch13(this, "dmaInterrupt_ch13")
        , dmaInterrupt_ch14(this, "dmaInterrupt_ch14")
        , dmaInterrupt_ch15(this, "dmaInterrupt_ch15")
    {
    }

    void before_end_of_elaboration() {
        MREAD.bindIfNotBound();
        MWRITE.bindIfNotBound();
    }
}; /* class VybridDMA */

#endif
