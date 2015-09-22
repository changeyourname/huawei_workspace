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


#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#include "pse.igen.h"

static ppmBusPort busPorts[] = {
    {
        .name            = "bport1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x1fffLL,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "MREAD",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .mustBeConnected = 0,
        .description     = "DMA Master Read of address space",
    },
    {
        .name            = "MWRITE",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .mustBeConnected = 0,
        .description     = "DMA Master Write of address space",
    },
    { 0 }
};

static PPM_BUS_PORT_FN(nextBusPort) {
    if(!busPort) {
        busPort = busPorts;
    } else {
        busPort++;
    }
    return busPort->name ? busPort : 0;
}

static ppmNetPort netPorts[] = {
    {
        .name            = "Reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "eDMARequest",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "eDMADone",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "errorInterrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Error Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 0 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 1 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 2 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 3 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch4",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 4 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch5",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 5 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 6 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 7 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch8",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 8 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch9",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 9 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch10",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 10 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch11",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 11 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch12",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 12 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch13",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 13 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch14",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 14 Interrupt port"
    },
    {
        .name            = "dmaInterrupt_ch15",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "DMA Done for channel 15 Interrupt port"
    },
    { 0 }
};

static PPM_NET_PORT_FN(nextNetPort) {
    if(!netPort) {
         netPort = netPorts;
    } else {
        netPort++;
    }
    return netPort->name ? netPort : 0;
}

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .busPortsCB       = nextBusPort,  
    .netPortsCB       = nextNetPort,  

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .vlnv          = {
        .vendor  = "freescale.ovpworld.org",
        .library = "peripheral",
        .name    = "VybridDMA",
        .version = "1.0"
    },

    .family    = "freescale.ovpworld.org",

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
