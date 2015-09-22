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
        .name            = "DirectWrite",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "DirectRead",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "Interrupt",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "Reset",
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
        .name        = "fifoSize",
        .type        = ppm_PT_UNS32,
        .description = "Size of fifos (default 128)",
    },
    {
        .name        = "moduleClkFreq",
        .type        = ppm_PT_UNS32,
        .description = "Frequency (in hertz) of module clock used in baud rate calculation (default=10.2 MHz)",
    },
    {
        .name        = "console",
        .type        = ppm_PT_BOOL,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference: \n            Automatic console",
    },
    {
        .name        = "portnum",
        .type        = ppm_PT_UNS32,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference:  \n             Specify port to open for a connection. \n             A value of zero causes the OS to select the next available port.",
    },
    {
        .name        = "infile",
        .type        = ppm_PT_STRING,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference: \n             UART takes input from this serial input source file",
    },
    {
        .name        = "outfile",
        .type        = ppm_PT_STRING,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference: \n             Serial output file",
    },
    {
        .name        = "portFile",
        .type        = ppm_PT_STRING,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference: \n             When portnum is set to zero, write the assigned port number to this file",
    },
    {
        .name        = "log",
        .type        = ppm_PT_BOOL,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference: \n             Report serial output in the simulator log",
    },
    {
        .name        = "finishOnDisconnect",
        .type        = ppm_PT_BOOL,
        .description = "Standard Serial Socket Parameter: See OVP BHM and PPM API Function Reference: \n             When defined the simulation will be terminated if the port is disconnected",
    },
    {
        .name        = "record",
        .type        = ppm_PT_STRING,
        .description = 0,
    },
    {
        .name        = "replay",
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
        .vendor  = "freescale.ovpworld.org",
        .library = "peripheral",
        .name    = "Uart",
        .version = "1.0"
    },

    .family    = "freescale.ovpworld.org",

    .releaseStatus = PPM_OVP,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
