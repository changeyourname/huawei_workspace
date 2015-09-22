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
//    Net output  eDMARequest;
//    Net input  dmaSrc0;
//    Net input  dmaSrc1;
//    Net input  dmaSrc2;
//    Net input  dmaSrc3;
//    Net input  dmaSrc4;
//    Net input  dmaSrc5;
//    Net input  dmaSrc6;
//    Net input  dmaSrc7;
//    Net input  dmaSrc8;
//    Net input  dmaSrc9;
//    Net input  dmaSrc10;
//    Net input  dmaSrc11;
//    Net input  dmaSrc12;
//    Net input  dmaSrc13;
//    Net input  dmaSrc14;
//    Net input  dmaSrc15;
//    Net input  dmaSrc16;
//    Net input  dmaSrc17;
//    Net input  dmaSrc18;
//    Net input  dmaSrc19;
//    Net input  dmaSrc20;
//    Net input  dmaSrc21;
//    Net input  dmaSrc22;
//    Net input  dmaSrc23;
//    Net input  dmaSrc24;
//    Net input  dmaSrc25;
//    Net input  dmaSrc26;
//    Net input  dmaSrc27;
//    Net input  dmaSrc28;
//    Net input  dmaSrc29;
//    Net input  dmaSrc30;
//    Net input  dmaSrc31;
//    Net input  dmaSrc32;
//    Net input  dmaSrc33;
//    Net input  dmaSrc34;
//    Net input  dmaSrc35;
//    Net input  dmaSrc36;
//    Net input  dmaSrc37;
//    Net input  dmaSrc38;
//    Net input  dmaSrc39;
//    Net input  dmaSrc40;
//    Net input  dmaSrc41;
//    Net input  dmaSrc42;
//    Net input  dmaSrc43;
//    Net input  dmaSrc44;
//    Net input  dmaSrc45;
//    Net input  dmaSrc46;
//    Net input  dmaSrc47;
//    Net input  dmaSrc48;
//    Net input  dmaSrc49;
//    Net input  dmaSrc50;
//    Net input  dmaSrc51;
//    Net input  dmaSrc52;
//    Net input  dmaSrc53;
//    Net input  dmaSrc54;
//    Net input  dmaSrc55;
//    Net input  dmaSrc56;
//    Net input  dmaSrc57;
//    Net input  dmaSrc58;
//    Net input  dmaSrc59;
//    Net input  dmaSrc60;
//    Net input  dmaSrc61;
//    Net input  dmaSrc62;
//    Net input  dmaSrc63;
//    Net input  trg1;
//    Net input  trg2;
//    Net input  trg3;
//    Net input  trg4;

#ifndef FREESCALE_OVPWORLD_ORG_PERIPHERAL_KINETISDMAMUX__1_0
#define FREESCALE_OVPWORLD_ORG_PERIPHERAL_KINETISDMAMUX__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class KinetisDMAMUX : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "freescale.ovpworld.org", "peripheral", "KinetisDMAMUX", "1.0", "pse");
    }

  public:
    icmSlavePort        bport1;
    icmInputNetPort Reset;
    icmOutputNetPort eDMARequest;
    icmInputNetPort dmaSrc0;
    icmInputNetPort dmaSrc1;
    icmInputNetPort dmaSrc2;
    icmInputNetPort dmaSrc3;
    icmInputNetPort dmaSrc4;
    icmInputNetPort dmaSrc5;
    icmInputNetPort dmaSrc6;
    icmInputNetPort dmaSrc7;
    icmInputNetPort dmaSrc8;
    icmInputNetPort dmaSrc9;
    icmInputNetPort dmaSrc10;
    icmInputNetPort dmaSrc11;
    icmInputNetPort dmaSrc12;
    icmInputNetPort dmaSrc13;
    icmInputNetPort dmaSrc14;
    icmInputNetPort dmaSrc15;
    icmInputNetPort dmaSrc16;
    icmInputNetPort dmaSrc17;
    icmInputNetPort dmaSrc18;
    icmInputNetPort dmaSrc19;
    icmInputNetPort dmaSrc20;
    icmInputNetPort dmaSrc21;
    icmInputNetPort dmaSrc22;
    icmInputNetPort dmaSrc23;
    icmInputNetPort dmaSrc24;
    icmInputNetPort dmaSrc25;
    icmInputNetPort dmaSrc26;
    icmInputNetPort dmaSrc27;
    icmInputNetPort dmaSrc28;
    icmInputNetPort dmaSrc29;
    icmInputNetPort dmaSrc30;
    icmInputNetPort dmaSrc31;
    icmInputNetPort dmaSrc32;
    icmInputNetPort dmaSrc33;
    icmInputNetPort dmaSrc34;
    icmInputNetPort dmaSrc35;
    icmInputNetPort dmaSrc36;
    icmInputNetPort dmaSrc37;
    icmInputNetPort dmaSrc38;
    icmInputNetPort dmaSrc39;
    icmInputNetPort dmaSrc40;
    icmInputNetPort dmaSrc41;
    icmInputNetPort dmaSrc42;
    icmInputNetPort dmaSrc43;
    icmInputNetPort dmaSrc44;
    icmInputNetPort dmaSrc45;
    icmInputNetPort dmaSrc46;
    icmInputNetPort dmaSrc47;
    icmInputNetPort dmaSrc48;
    icmInputNetPort dmaSrc49;
    icmInputNetPort dmaSrc50;
    icmInputNetPort dmaSrc51;
    icmInputNetPort dmaSrc52;
    icmInputNetPort dmaSrc53;
    icmInputNetPort dmaSrc54;
    icmInputNetPort dmaSrc55;
    icmInputNetPort dmaSrc56;
    icmInputNetPort dmaSrc57;
    icmInputNetPort dmaSrc58;
    icmInputNetPort dmaSrc59;
    icmInputNetPort dmaSrc60;
    icmInputNetPort dmaSrc61;
    icmInputNetPort dmaSrc62;
    icmInputNetPort dmaSrc63;
    icmInputNetPort trg1;
    icmInputNetPort trg2;
    icmInputNetPort trg3;
    icmInputNetPort trg4;

    KinetisDMAMUX(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , bport1(this, "bport1", 0x1000) // static
        , Reset(this, "Reset")
        , eDMARequest(this, "eDMARequest")
        , dmaSrc0(this, "dmaSrc0")
        , dmaSrc1(this, "dmaSrc1")
        , dmaSrc2(this, "dmaSrc2")
        , dmaSrc3(this, "dmaSrc3")
        , dmaSrc4(this, "dmaSrc4")
        , dmaSrc5(this, "dmaSrc5")
        , dmaSrc6(this, "dmaSrc6")
        , dmaSrc7(this, "dmaSrc7")
        , dmaSrc8(this, "dmaSrc8")
        , dmaSrc9(this, "dmaSrc9")
        , dmaSrc10(this, "dmaSrc10")
        , dmaSrc11(this, "dmaSrc11")
        , dmaSrc12(this, "dmaSrc12")
        , dmaSrc13(this, "dmaSrc13")
        , dmaSrc14(this, "dmaSrc14")
        , dmaSrc15(this, "dmaSrc15")
        , dmaSrc16(this, "dmaSrc16")
        , dmaSrc17(this, "dmaSrc17")
        , dmaSrc18(this, "dmaSrc18")
        , dmaSrc19(this, "dmaSrc19")
        , dmaSrc20(this, "dmaSrc20")
        , dmaSrc21(this, "dmaSrc21")
        , dmaSrc22(this, "dmaSrc22")
        , dmaSrc23(this, "dmaSrc23")
        , dmaSrc24(this, "dmaSrc24")
        , dmaSrc25(this, "dmaSrc25")
        , dmaSrc26(this, "dmaSrc26")
        , dmaSrc27(this, "dmaSrc27")
        , dmaSrc28(this, "dmaSrc28")
        , dmaSrc29(this, "dmaSrc29")
        , dmaSrc30(this, "dmaSrc30")
        , dmaSrc31(this, "dmaSrc31")
        , dmaSrc32(this, "dmaSrc32")
        , dmaSrc33(this, "dmaSrc33")
        , dmaSrc34(this, "dmaSrc34")
        , dmaSrc35(this, "dmaSrc35")
        , dmaSrc36(this, "dmaSrc36")
        , dmaSrc37(this, "dmaSrc37")
        , dmaSrc38(this, "dmaSrc38")
        , dmaSrc39(this, "dmaSrc39")
        , dmaSrc40(this, "dmaSrc40")
        , dmaSrc41(this, "dmaSrc41")
        , dmaSrc42(this, "dmaSrc42")
        , dmaSrc43(this, "dmaSrc43")
        , dmaSrc44(this, "dmaSrc44")
        , dmaSrc45(this, "dmaSrc45")
        , dmaSrc46(this, "dmaSrc46")
        , dmaSrc47(this, "dmaSrc47")
        , dmaSrc48(this, "dmaSrc48")
        , dmaSrc49(this, "dmaSrc49")
        , dmaSrc50(this, "dmaSrc50")
        , dmaSrc51(this, "dmaSrc51")
        , dmaSrc52(this, "dmaSrc52")
        , dmaSrc53(this, "dmaSrc53")
        , dmaSrc54(this, "dmaSrc54")
        , dmaSrc55(this, "dmaSrc55")
        , dmaSrc56(this, "dmaSrc56")
        , dmaSrc57(this, "dmaSrc57")
        , dmaSrc58(this, "dmaSrc58")
        , dmaSrc59(this, "dmaSrc59")
        , dmaSrc60(this, "dmaSrc60")
        , dmaSrc61(this, "dmaSrc61")
        , dmaSrc62(this, "dmaSrc62")
        , dmaSrc63(this, "dmaSrc63")
        , trg1(this, "trg1")
        , trg2(this, "trg2")
        , trg3(this, "trg3")
        , trg4(this, "trg4")
    {
    }

}; /* class KinetisDMAMUX */

#endif
