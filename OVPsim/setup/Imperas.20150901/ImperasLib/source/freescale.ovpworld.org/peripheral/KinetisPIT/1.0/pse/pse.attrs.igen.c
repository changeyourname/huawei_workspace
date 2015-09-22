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
        .addrHi          = 0xfffLL,
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
        .name            = "Reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "irq0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ0 port"
    },
    {
        .name            = "trg0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger0 port"
    },
    {
        .name            = "irq1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ1 port"
    },
    {
        .name            = "trg1",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger1 port"
    },
    {
        .name            = "irq2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ2 port"
    },
    {
        .name            = "trg2",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger2 port"
    },
    {
        .name            = "irq3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "IRQ3 port"
    },
    {
        .name            = "trg3",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = "Trigger3 port"
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

static ppmParameter parameters[] = {
    {
        .name        = "frequency",
        .type        = ppm_PT_UNS64,
        .description = "Frequency of the clock input in Hz (default is 80MHz)",
    },
    { 0 }
};

static PPM_PARAMETER_FN(nextParameter) {
    if(!parameter) {
        parameter = parameters;
    } else {
        parameter++;
    }
    return parameter->name ? parameter : 0;
}

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .busPortsCB       = nextBusPort,  
    .netPortsCB       = nextNetPort,  
    .paramSpecCB      = nextParameter,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .vlnv          = {
        .vendor  = "freescale.ovpworld.org",
        .library = "peripheral",
        .name    = "KinetisPIT",
        .version = "1.0"
    },

    .family    = "freescale.ovpworld.org",

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
