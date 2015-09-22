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
        .name            = "ADCP0",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x2fLL,
        .mustBeConnected = 0,
        .remappable      = 0,
        .description     = 0,
    },
    {
        .name            = "ADCP1",
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
        .name            = "INTAD",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "ADDMARQ",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTADEN",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "ADTRG",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "TS0ADT0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "TS0ADT1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTTS0OD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTTS0CD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "TS1ADT0",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "TS1ADT1",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTTS1OD",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "INTTS1CD",
        .type            = PPM_INPUT_PORT,
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

static ppmParameter parameters[] = {
    {
        .name        = "stimfile0",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile1",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile2",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile3",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile4",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile5",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile6",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile7",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile8",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "stimfile9",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "PCLK1",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "sample",
        .type        = ppm_PT_UNS32,
        .description = 0,
    },
    {
        .name        = "plantmode0",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode1",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode2",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode3",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode4",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode5",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode6",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode7",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode8",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "plantmode9",
        .type        = ppm_PT_STRING,
        .description = 0,
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
        .vendor  = "renesas.ovpworld.org",
        .library = "peripheral",
        .name    = "adc",
        .version = "1.0"
    },

    .family    = "renesas.ovpworld.org",

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
