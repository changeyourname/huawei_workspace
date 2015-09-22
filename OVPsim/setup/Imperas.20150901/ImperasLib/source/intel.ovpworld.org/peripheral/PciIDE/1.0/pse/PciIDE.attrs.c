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

#include "drive.h"


static ppmBusPort busPorts[] = {
    {
        .name            = "busPort",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x7LL,
        .mustBeConnected = 1,
        .remappable      = 1,
        .description     = "PCI main bus connection for register access.",
    },
    {
        .name            = "PCIconfig",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x7ffLL,
        .mustBeConnected = 0,
        .remappable      = 1,
        .description     = "PCI configuration bus connection.",
    },
    {
        .name            = "dmaPort",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .mustBeConnected = 0,
        .description     = "PCI DMA bus connection.",
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
        .name            = "intOut0",
        .type            = PPM_OUTPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0
    },
    {
        .name            = "intOut1",
        .type            = PPM_OUTPUT_PORT,
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
        .name        = "PCIslot",
        .type        = ppm_PT_UNS32,
        .description = "Specify which PCI slot the device occupies.",
    },
    {
        .name        = "PCIfunction",
        .type        = ppm_PT_UNS32,
        .description = "Specify which PCI function:code the device implements.",
    },
    {
        .name        = "Drive0Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 0",
    },
    {
        .name        = "Drive0Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 0. This feature is incomplete.",
    },
    {
        .name        = "Drive1Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 1",
    },
    {
        .name        = "Drive1Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 1. This feature is incomplete.",
    },
    {
        .name        = "Drive2Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 2",
    },
    {
        .name        = "Drive2Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 2. This feature is incomplete.",
    },
    {
        .name        = "Drive3Name",
        .type        = ppm_PT_STRING,
        .description = "Virtual disk file for IDE channel 3",
    },
    {
        .name        = "Drive3Delta",
        .type        = ppm_PT_STRING,
        .description = "Delta file for IDE channel 3. This feature is incomplete.",
    },
    {
        .name        = "endian",
        .type        = ppm_PT_STRING,
        .description = "Set the system endian, \"big\" or \"little\"; used for writing boot code.                                           Without this attribute the default is \"little\" endian.",
    },
    {
        .name        = "record",
        .type        = ppm_PT_STRING,
        .description = "Enable record mode",
    },
    {
        .name        = "replay",
        .type        = ppm_PT_STRING,
        .description = "Enable replay mode",
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

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    if(phase==PPM_POST_SAVE_RESTORE) {
        bdrv_restore();
    }
}

ppmModelAttr modelAttrs = {

    .versionString = PPM_VERSION_STRING,
    .type          = PPM_MT_PERIPHERAL,

    .busPortsCB    = nextBusPort,
    .netPortsCB    = nextNetPort,
    .paramSpecCB   = nextParameter,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .vlnv          = {
        .vendor  = "intel.ovpworld.org",
        .library = "peripheral",
        .name    = "PciIDE",
        .version = "1.0"
    },

    .family    = "intel.ovpworld.org",

    .releaseStatus  = PPM_OVP,
    .visibility     = PPM_VISIBLE,

};
