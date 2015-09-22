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
//    Net input  resetNet;
//    Net output  TZPCR0SIZE;
//    Net output  TZPCDECPROT0_0;
//    Net output  TZPCDECPROT0_1;
//    Net output  TZPCDECPROT0_2;
//    Net output  TZPCDECPROT0_3;
//    Net output  TZPCDECPROT0_4;
//    Net output  TZPCDECPROT0_5;
//    Net output  TZPCDECPROT0_6;
//    Net output  TZPCDECPROT0_7;
//    Net output  TZPCDECPROT0_8;
//    Net output  TZPCDECPROT0_9;
//    Net output  TZPCDECPROT0_10;
//    Net output  TZPCDECPROT0_11;
//    Net output  TZPCDECPROT0_12;
//    Net output  TZPCDECPROT0_13;
//    Net output  TZPCDECPROT0_14;
//    Net output  TZPCDECPROT0_15;
//    Net output  TZPCDECPROT1_0;
//    Net output  TZPCDECPROT1_1;
//    Net output  TZPCDECPROT1_2;
//    Net output  TZPCDECPROT1_3;
//    Net output  TZPCDECPROT1_4;
//    Net output  TZPCDECPROT1_5;
//    Net output  TZPCDECPROT1_6;
//    Net output  TZPCDECPROT1_7;
//    Net output  TZPCDECPROT1_8;
//    Net output  TZPCDECPROT1_9;
//    Net output  TZPCDECPROT1_10;
//    Net output  TZPCDECPROT1_11;
//    Net output  TZPCDECPROT1_12;
//    Net output  TZPCDECPROT1_13;
//    Net output  TZPCDECPROT1_14;
//    Net output  TZPCDECPROT1_15;
//    Net output  TZPCDECPROT2_0;
//    Net output  TZPCDECPROT2_1;
//    Net output  TZPCDECPROT2_2;
//    Net output  TZPCDECPROT2_3;
//    Net output  TZPCDECPROT2_4;
//    Net output  TZPCDECPROT2_5;
//    Net output  TZPCDECPROT2_6;
//    Net output  TZPCDECPROT2_7;
//    Net output  TZPCDECPROT2_8;
//    Net output  TZPCDECPROT2_9;
//    Net output  TZPCDECPROT2_10;
//    Net output  TZPCDECPROT2_11;
//    Net output  TZPCDECPROT2_12;
//    Net output  TZPCDECPROT2_13;
//    Net output  TZPCDECPROT2_14;
//    Net output  TZPCDECPROT2_15;

#ifndef ARM_OVPWORLD_ORG_PERIPHERAL_TZPCBP147__1_0
#define ARM_OVPWORLD_ORG_PERIPHERAL_TZPCBP147__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class TzpcBP147 : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "peripheral", "TzpcBP147", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmInputNetPort resetNet;
    icmOutputNetPort TZPCR0SIZE;
    icmOutputNetPort TZPCDECPROT0_0;
    icmOutputNetPort TZPCDECPROT0_1;
    icmOutputNetPort TZPCDECPROT0_2;
    icmOutputNetPort TZPCDECPROT0_3;
    icmOutputNetPort TZPCDECPROT0_4;
    icmOutputNetPort TZPCDECPROT0_5;
    icmOutputNetPort TZPCDECPROT0_6;
    icmOutputNetPort TZPCDECPROT0_7;
    icmOutputNetPort TZPCDECPROT0_8;
    icmOutputNetPort TZPCDECPROT0_9;
    icmOutputNetPort TZPCDECPROT0_10;
    icmOutputNetPort TZPCDECPROT0_11;
    icmOutputNetPort TZPCDECPROT0_12;
    icmOutputNetPort TZPCDECPROT0_13;
    icmOutputNetPort TZPCDECPROT0_14;
    icmOutputNetPort TZPCDECPROT0_15;
    icmOutputNetPort TZPCDECPROT1_0;
    icmOutputNetPort TZPCDECPROT1_1;
    icmOutputNetPort TZPCDECPROT1_2;
    icmOutputNetPort TZPCDECPROT1_3;
    icmOutputNetPort TZPCDECPROT1_4;
    icmOutputNetPort TZPCDECPROT1_5;
    icmOutputNetPort TZPCDECPROT1_6;
    icmOutputNetPort TZPCDECPROT1_7;
    icmOutputNetPort TZPCDECPROT1_8;
    icmOutputNetPort TZPCDECPROT1_9;
    icmOutputNetPort TZPCDECPROT1_10;
    icmOutputNetPort TZPCDECPROT1_11;
    icmOutputNetPort TZPCDECPROT1_12;
    icmOutputNetPort TZPCDECPROT1_13;
    icmOutputNetPort TZPCDECPROT1_14;
    icmOutputNetPort TZPCDECPROT1_15;
    icmOutputNetPort TZPCDECPROT2_0;
    icmOutputNetPort TZPCDECPROT2_1;
    icmOutputNetPort TZPCDECPROT2_2;
    icmOutputNetPort TZPCDECPROT2_3;
    icmOutputNetPort TZPCDECPROT2_4;
    icmOutputNetPort TZPCDECPROT2_5;
    icmOutputNetPort TZPCDECPROT2_6;
    icmOutputNetPort TZPCDECPROT2_7;
    icmOutputNetPort TZPCDECPROT2_8;
    icmOutputNetPort TZPCDECPROT2_9;
    icmOutputNetPort TZPCDECPROT2_10;
    icmOutputNetPort TZPCDECPROT2_11;
    icmOutputNetPort TZPCDECPROT2_12;
    icmOutputNetPort TZPCDECPROT2_13;
    icmOutputNetPort TZPCDECPROT2_14;
    icmOutputNetPort TZPCDECPROT2_15;

    TzpcBP147(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x1000) // static
        , resetNet(this, "resetNet")
        , TZPCR0SIZE(this, "TZPCR0SIZE")
        , TZPCDECPROT0_0(this, "TZPCDECPROT0_0")
        , TZPCDECPROT0_1(this, "TZPCDECPROT0_1")
        , TZPCDECPROT0_2(this, "TZPCDECPROT0_2")
        , TZPCDECPROT0_3(this, "TZPCDECPROT0_3")
        , TZPCDECPROT0_4(this, "TZPCDECPROT0_4")
        , TZPCDECPROT0_5(this, "TZPCDECPROT0_5")
        , TZPCDECPROT0_6(this, "TZPCDECPROT0_6")
        , TZPCDECPROT0_7(this, "TZPCDECPROT0_7")
        , TZPCDECPROT0_8(this, "TZPCDECPROT0_8")
        , TZPCDECPROT0_9(this, "TZPCDECPROT0_9")
        , TZPCDECPROT0_10(this, "TZPCDECPROT0_10")
        , TZPCDECPROT0_11(this, "TZPCDECPROT0_11")
        , TZPCDECPROT0_12(this, "TZPCDECPROT0_12")
        , TZPCDECPROT0_13(this, "TZPCDECPROT0_13")
        , TZPCDECPROT0_14(this, "TZPCDECPROT0_14")
        , TZPCDECPROT0_15(this, "TZPCDECPROT0_15")
        , TZPCDECPROT1_0(this, "TZPCDECPROT1_0")
        , TZPCDECPROT1_1(this, "TZPCDECPROT1_1")
        , TZPCDECPROT1_2(this, "TZPCDECPROT1_2")
        , TZPCDECPROT1_3(this, "TZPCDECPROT1_3")
        , TZPCDECPROT1_4(this, "TZPCDECPROT1_4")
        , TZPCDECPROT1_5(this, "TZPCDECPROT1_5")
        , TZPCDECPROT1_6(this, "TZPCDECPROT1_6")
        , TZPCDECPROT1_7(this, "TZPCDECPROT1_7")
        , TZPCDECPROT1_8(this, "TZPCDECPROT1_8")
        , TZPCDECPROT1_9(this, "TZPCDECPROT1_9")
        , TZPCDECPROT1_10(this, "TZPCDECPROT1_10")
        , TZPCDECPROT1_11(this, "TZPCDECPROT1_11")
        , TZPCDECPROT1_12(this, "TZPCDECPROT1_12")
        , TZPCDECPROT1_13(this, "TZPCDECPROT1_13")
        , TZPCDECPROT1_14(this, "TZPCDECPROT1_14")
        , TZPCDECPROT1_15(this, "TZPCDECPROT1_15")
        , TZPCDECPROT2_0(this, "TZPCDECPROT2_0")
        , TZPCDECPROT2_1(this, "TZPCDECPROT2_1")
        , TZPCDECPROT2_2(this, "TZPCDECPROT2_2")
        , TZPCDECPROT2_3(this, "TZPCDECPROT2_3")
        , TZPCDECPROT2_4(this, "TZPCDECPROT2_4")
        , TZPCDECPROT2_5(this, "TZPCDECPROT2_5")
        , TZPCDECPROT2_6(this, "TZPCDECPROT2_6")
        , TZPCDECPROT2_7(this, "TZPCDECPROT2_7")
        , TZPCDECPROT2_8(this, "TZPCDECPROT2_8")
        , TZPCDECPROT2_9(this, "TZPCDECPROT2_9")
        , TZPCDECPROT2_10(this, "TZPCDECPROT2_10")
        , TZPCDECPROT2_11(this, "TZPCDECPROT2_11")
        , TZPCDECPROT2_12(this, "TZPCDECPROT2_12")
        , TZPCDECPROT2_13(this, "TZPCDECPROT2_13")
        , TZPCDECPROT2_14(this, "TZPCDECPROT2_14")
        , TZPCDECPROT2_15(this, "TZPCDECPROT2_15")
    {
    }

}; /* class TzpcBP147 */

#endif
