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
        .description = "Set the PCI slot at which the Ethernet card is installed",
    },
    {
        .name        = "PCIfunction",
        .type        = ppm_PT_UNS32,
        .description = "Set the PCI function of the device. The default of 0 is correct for this device.",
    },
    {
        .name        = "ethereal",
        .type        = ppm_PT_STRING,
        .description = "Set a log file name and turn on packet logging using ethereal format. Every packet passing trough the device will be added to the file. Use the freely available 'ethereal' program to analyze the output. Example: /home/my_user/my_ethereal_log_file.txt",
    },
    {
        .name        = "maxEtherLength",
        .type        = ppm_PT_UNS32,
        .description = "Only used when ethereal attribute set. Specify the max length for each packet logged.",
    },
    {
        .name        = "pollDelay",
        .type        = ppm_PT_UNS32,
        .description = "Allows the rate the network is checked for packets to transfer to be altered .",
    },
    {
        .name        = "MAC",
        .type        = ppm_PT_UNS64,
        .description = "Set the MAC address of the NIC, as read from the PCI bus. Note that the interface to the host's network is at the TCP/UPD level so it is not possible to affect the actual MAC address. Example: ab:cd:ef:01:23:45",
    },
    {
        .name        = "redir",
        .type        = ppm_PT_STRING,
        .description = "Specify a list of ports to open on the host and redirect to the guest. Format: redirect{,redirect}  redirect        := protocol:host_port:guest_ip:guest_port protocol        := udp|tcp host_port       := integer guest_ip        := integer.integer.integer.integer guest_port      := integer  Example: tcp:10080:10.0.2.15:80,tcp:10021:10.0.2.15:21  This opens ports 10080 and 10021 on the host and redirects them to the guest's http and ftp ports. This could be used if http and ftp servers are running on the guest.  The default sub-net of the network interface is 10.0.2.0;  This can be changed (see below), but there is rarely any need; each network card is on a private network invisible to all other devices (even another network card in the same platform). TCP and UDP packets are routed to the real network using N.A.T. (like in a SOHO router).  In this example, the guest Linux configures the network IP as 10.0.2.15, which is correct for the 10.0.2.0 virtual subnet it is connected to.",
    },
    {
        .name        = "tftpPrefix",
        .type        = ppm_PT_STRING,
        .description = "Enable the TFTP server emulation and set the tftp root directory. tftp is a trivial FTP protocol (port 69) used usually to boot diskless computers on a LAN. When this feature is enabled, the network card intercepts all TFTP 'get' requests, regardless of their destination, and searches the supplied directory for the requested file. Thus, a TFTP client running on the guest platform can fetch files without a server on the host. Note that there is no 'put' feature. Example: /home/my_user/my_tftp_directory",
    },
    {
        .name        = "localNet",
        .type        = ppm_PT_STRING,
        .description = "Change the local network address from its default of 10.0.2.0 (rarely required, see above). Example: 192.168.0.0",
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

PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

ppmModelAttr modelAttrs = {

    .versionString = PPM_VERSION_STRING,
    .type          = PPM_MT_PERIPHERAL,

    .busPortsCB    = nextBusPort,
    .netPortsCB    = nextNetPort,
    .paramSpecCB   = nextParameter,

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .vlnv          = {
        .vendor  = "amd.ovpworld.org",
        .library = "peripheral",
        .name    = "79C970",
        .version = "1.0"
    },

    .family    = "amd.ovpworld.org",
    .extension = "model"

};
