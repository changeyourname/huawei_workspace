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
        .name            = "LOGICP0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x3LL,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "LOGICP1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x75LL,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "LOGICP2",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0xbLL,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "LOGICP3",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x0LL,
        .mustBeConnected = 0,
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
        .name            = "NMIIN",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTDEDF",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTDEDR",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTDEDFR",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTOSD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTP4",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTUC0R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTP5",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTUC1R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTBRG0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTBRG1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTCB0T",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTUC2T",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTCB0R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTUC2R",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTP13",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTCB0RE",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTUC2RE",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTDMA3",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTFL",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "NMIOUT",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT6",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT7",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT75",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT99",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT100",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT101",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INT116",
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
        .vendor  = "renesas.ovpworld.org",
        .library = "peripheral",
        .name    = "UPD70F3441Logic",
        .version = "1.0"
    },

    .family    = "renesas.ovpworld.org",

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
