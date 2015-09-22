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
        .name            = "bp1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3fffLL,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
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
        .name            = "P0",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P1",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P2",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P3",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P4",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P5",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P6",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P7",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P8",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P9",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P10",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P11",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P12",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P13",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P14",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P15",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P16",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P17",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P18",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P19",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P20",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P21",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P22",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P23",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P24",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P25",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P26",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P27",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P28",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P29",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P30",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "P31",
        .type            = PPM_INOUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "IRQ",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
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
        .vendor  = "atmel.ovpworld.org",
        .library = "peripheral",
        .name    = "ParallelIOController",
        .version = "1.0"
    },

    .family    = "atmel.ovpworld.org",

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
