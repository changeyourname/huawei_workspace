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
//    Slave Port busPortMR
//    Slave Port busPortMDB
//    Slave Port busPortMDH
//    Slave Port busPortMDW
//    Slave Port busPortECC
//    Slave Port busPortGR
//    Slave Port busPortCR
//    Slave Port busPortCRW
//    Net output  INTTRX;
//    Net output  INTREC;
//    Net output  INTERR;
//    Net output  INTWUP;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_CAN__1_1
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_CAN__1_1
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class can : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "can", "1.1", "pse");
    }

  public:
    icmSlavePort        busPortMR;
    icmSlavePort        busPortMDB;
    icmSlavePort        busPortMDH;
    icmSlavePort        busPortMDW;
    icmSlavePort        busPortECC;
    icmSlavePort        busPortGR;
    icmSlavePort        busPortCR;
    icmSlavePort        busPortCRW;
    icmOutputNetPort INTTRX;
    icmOutputNetPort INTREC;
    icmOutputNetPort INTERR;
    icmOutputNetPort INTWUP;

    can(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , busPortMR(this, "busPortMR", 0x300) // static
        , busPortMDB(this, "busPortMDB", 0x1000) // static
        , busPortMDH(this, "busPortMDH", 0x1000) // static
        , busPortMDW(this, "busPortMDW", 0x1000) // static
        , busPortECC(this, "busPortECC", 0x4) // static
        , busPortGR(this, "busPortGR", 0x200) // static
        , busPortCR(this, "busPortCR", 0x200) // static
        , busPortCRW(this, "busPortCRW", 0x100) // static
        , INTTRX(this, "INTTRX")
        , INTREC(this, "INTREC")
        , INTERR(this, "INTERR")
        , INTWUP(this, "INTWUP")
    {
    }

}; /* class can */

#endif
