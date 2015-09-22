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
        .name            = "mport",
        .type            = PPM_MASTER_PORT,
        .addrBits        = 32,
        .mustBeConnected = 1,
        .description     = "Master port - connect to same bus connected to Linux processor's data port",
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
        .name        = "kernel",
        .type        = ppm_PT_STRING,
        .description = "Name of the the Linux kernel image file (e.g. zImage) to load. (required)",
    },
    {
        .name        = "kerneladdr",
        .type        = ppm_PT_UNS32,
        .description = "Address to load the Linux kernel image file (default: physicalbase+0x00010000)",
    },
    {
        .name        = "initrd",
        .type        = ppm_PT_STRING,
        .description = "Name of the initial ram disk file to load. (optional)",
    },
    {
        .name        = "initrdaddr",
        .type        = ppm_PT_UNS32,
        .description = "Address to load the initial ram disk file (default: physicalbase+0x00d00000)",
    },
    {
        .name        = "atagsaddr",
        .type        = ppm_PT_UNS32,
        .description = "Address to write Linux ATAGS data (default: physicalbase+0x100)",
    },
    {
        .name        = "physicalbase",
        .type        = ppm_PT_UNS32,
        .description = "The physical address of the base of memory. (default: 0)",
    },
    {
        .name        = "memsize",
        .type        = ppm_PT_UNS32,
        .description = "The size of memory in bytes. (default: 128M)",
    },
    {
        .name        = "command",
        .type        = ppm_PT_STRING,
        .description = "Command string passed to the kernel.",
    },
    {
        .name        = "boardid",
        .type        = ppm_PT_UNS32,
        .description = "The boardid passed to the kernel. (default: ArmIntegrator value = 0x113)",
    },
    {
        .name        = "stackpointer",
        .type        = ppm_PT_UNS32,
        .description = "The stackpointer passed to the kernel. (default: memsize+physicalbase)",
    },
    {
        .name        = "bootaddr",
        .type        = ppm_PT_UNS32,
        .description = "Address to call from smart Loader's tiny startup code (default: kerneladdr)",
    },
    {
        .name        = "bootcode",
        .type        = ppm_PT_STRING,
        .description = "Path to boot code",
    },
    {
        .name        = "disable",
        .type        = ppm_PT_BOOL,
        .description = "Set to True to disable the smart loader",
    },
    {
        .name        = "append",
        .type        = ppm_PT_STRING,
        .description = "Append this string to the command line",
    },
    {
        .name        = "nbcpus",
        .type        = ppm_PT_UNS64,
        .description = "Number of CPUs",
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
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "SmartLoaderArmLinux",
        .version = "1.0"
    },

    .family    = "arm.ovpworld.org",

    .releaseStatus  = PPM_OVP,
    .visibility     = PPM_VISIBLE,

};
