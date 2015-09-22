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
//                              Version 99999999
//                          Tue Mar 11 07:51:25 2014
//
////////////////////////////////////////////////////////////////////////////////


#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif


static ppmBusPort busPorts[] = {
    {
        .name            = "config",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x7LL,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    { 0 }
};

static PPM_BUS_PORT_FN(nextBusPort) {
    if(!busPort) {
        return busPorts;
    } else {
        busPort++;
    }
    return busPort->name ? busPort : 0;
}

static ppmNetPort netPorts[] = {
    {
        .name            = "kbdInterrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "mouseInterrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "reset",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    { 0 }
};

static PPM_NET_PORT_FN(nextNetPort) {
    if(!netPort) {
        return netPorts;
    } else {
        netPort++;
    }
    return netPort->name ? netPort : 0;
}

static ppmParameter parameters[] = {
    {
        .name        = "disableInput",
        .type        = ppm_PT_BOOL,
        .description = "If set, disables mouse and keyboard events.",
    },
    {
        .name        = "pollPeriod",
        .type        = ppm_PT_UNS32,
        .description = "Number of uS between each polling of the keyboard and mouse queues.",
    },
    {
        .name        = "grabDisable",
        .type        = ppm_PT_BOOL,
        .description = "If set, disables grabbing of the mouse by the VGA/input window.",
    },
    {
        .name        = "cursorEnable",
        .type        = ppm_PT_BOOL,
        .description = "If set, shows a basic software cursor in the VGA/input window at the mouse position.",
    },
    {
        .name        = "isMouse",
        .type        = ppm_PT_BOOL,
        .description = "If set, turns on mouse input function.",
    },
    {
        .name        = "isKeyboard",
        .type        = ppm_PT_BOOL,
        .description = "If set, turns on keyboard input function.",
    },
    {
        .name        = "record",
        .type        = ppm_PT_STRING,
        .description = "Specify a record output file",
    },
    {
        .name        = "replay",
        .type        = ppm_PT_STRING,
        .description = "Specify a replay input file",
    },
    { 0 }
};

static PPM_PARAMETER_FN(nextParameter) {
    if(!parameter) {
        return parameters;
    } else {
        parameter++;
    }
    return parameter->name ? parameter : 0;
}

ppmModelAttr modelAttrs = {

    .versionString = PPM_VERSION_STRING,
    .type          = PPM_MT_PERIPHERAL,

    .busPortsCB    = nextBusPort,
    .netPortsCB    = nextNetPort,
    .paramSpecCB   = nextParameter,

    .vlnv          = {
        .vendor  = "intel.ovpworld.org",
        .library = "peripheral",
        .name    = "Ps2Control",
        .version = "1.0"
    },

    .family    = "intel.ovpworld.org",
    .extension = "model",

    .releaseStatus  = PPM_OVP,
    .visibility     = PPM_VISIBLE,

};
