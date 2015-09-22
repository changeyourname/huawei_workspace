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
//    Master Port DMAPM
//    Slave Port DMAP0
//    Slave Port DMAP1
//    Net output  INTDMA0;
//    Net output  INTDMA1;
//    Net output  INTDMA2;
//    Net output  INTDMA3;
//    Net output  INTDMA4;
//    Net output  INTDMA5;
//    Net output  INTDMA6;
//    Net output  INTDMA7;
//    Net output  INTDMA8;
//    Net output  INTDMA9;
//    Net output  DMA0EN;
//    Net output  DMA1EN;
//    Net input  ADDMARQ0;
//    Net input  ADDMARQ1;
//    Net input  INTTS0CD;
//    Net input  INTTS1CD;
//    Net input  INTCE0C;
//    Net input  INTCE1C;
//    Net input  INTBE0R;
//    Net input  INTBE1R;
//    Net input  INTUC0R;
//    Net input  INTUC1R;
//    Net input  INTUC2R;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_DMA__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_DMA__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class dma : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "dma", "1.0", "pse");
    }

  public:
    icmSlavePort        DMAP0;
    icmSlavePort        DMAP1;
    icmMasterPort       DMAPM;
    icmOutputNetPort INTDMA0;
    icmOutputNetPort INTDMA1;
    icmOutputNetPort INTDMA2;
    icmOutputNetPort INTDMA3;
    icmOutputNetPort INTDMA4;
    icmOutputNetPort INTDMA5;
    icmOutputNetPort INTDMA6;
    icmOutputNetPort INTDMA7;
    icmOutputNetPort INTDMA8;
    icmOutputNetPort INTDMA9;
    icmOutputNetPort DMA0EN;
    icmOutputNetPort DMA1EN;
    icmInputNetPort ADDMARQ0;
    icmInputNetPort ADDMARQ1;
    icmInputNetPort INTTS0CD;
    icmInputNetPort INTTS1CD;
    icmInputNetPort INTCE0C;
    icmInputNetPort INTCE1C;
    icmInputNetPort INTBE0R;
    icmInputNetPort INTBE1R;
    icmInputNetPort INTUC0R;
    icmInputNetPort INTUC1R;
    icmInputNetPort INTUC2R;

    dma(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , DMAP0(this, "DMAP0", 0x10) // static
        , DMAP1(this, "DMAP1", 0x100) // static
        , DMAPM(this, "DMAPM", 28)
        , INTDMA0(this, "INTDMA0")
        , INTDMA1(this, "INTDMA1")
        , INTDMA2(this, "INTDMA2")
        , INTDMA3(this, "INTDMA3")
        , INTDMA4(this, "INTDMA4")
        , INTDMA5(this, "INTDMA5")
        , INTDMA6(this, "INTDMA6")
        , INTDMA7(this, "INTDMA7")
        , INTDMA8(this, "INTDMA8")
        , INTDMA9(this, "INTDMA9")
        , DMA0EN(this, "DMA0EN")
        , DMA1EN(this, "DMA1EN")
        , ADDMARQ0(this, "ADDMARQ0")
        , ADDMARQ1(this, "ADDMARQ1")
        , INTTS0CD(this, "INTTS0CD")
        , INTTS1CD(this, "INTTS1CD")
        , INTCE0C(this, "INTCE0C")
        , INTCE1C(this, "INTCE1C")
        , INTBE0R(this, "INTBE0R")
        , INTBE1R(this, "INTBE1R")
        , INTUC0R(this, "INTUC0R")
        , INTUC1R(this, "INTUC1R")
        , INTUC2R(this, "INTUC2R")
    {
    }

    void before_end_of_elaboration() {
        DMAPM.bindIfNotBound();
    }
}; /* class dma */

#endif
