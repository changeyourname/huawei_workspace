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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hostapi/hostMacros.h"

// socket I/F
#if (IMPERAS_LINUX==1)
#include <arpa/inet.h>
#include <sys/select.h>
#endif

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

// slirp
#include "slirp.h"
#include "libslirp.h"

#include "semihost.h"

#define PREFIX "NET_SEMI"
#define MAX_TFTP_PATH 256

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

#define DIAG_LEVEL (object->diagLevel)

#define DIAG_LOW     ((DIAG_LEVEL & 3) >= 1)
#define DIAG_MEDIUM  ((DIAG_LEVEL & 3) >= 2)
#define DIAG_HIGH    ((DIAG_LEVEL & 3) >= 3)




typedef struct vmiosObjectS  {

    // return register (standard ABI)
    vmiRegInfoCP result;

    // stack pointer (standard ABI)
    vmiRegInfoCP sp;

    char tftpPath[MAX_TFTP_PATH];

    Uns32       packets;      // ptr to shared space
    Uns32       count;        // number of packets filled
    memDomainP  domain;       // PSE domain
    Uns32       diagLevel;    // for this instance
    Uns64       pollCount;

    Slirp      *slirp;

} vmiosObject;

//
// Read a function adument using the standard ABI
//
static void getArg(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index,
    void         *result
) {
    memDomainP domain    = vmirtGetProcessorDataDomain(processor);
    Uns32      argSize   = 4;
    Uns32      argOffset = (index+1)*argSize;
    Uns32      spAddr;

    // get the stack
    vmiosRegRead(processor, object->sp, &spAddr);

    // read argument value
    vmirtReadNByteDomain(domain, spAddr+argOffset, result, argSize, 0, True);
}

//
// Called to create the network connection.
//
static VMIOS_INTERCEPT_FN(netInit)
{
    object->domain = vmirtGetProcessorDataDomain(processor);

    Uns32 prefixStringAddr;
    Uns32 localNetAddr;

    getArg(processor, object, 0, &object->diagLevel);
    getArg(processor, object, 1, &object->packets);
    getArg(processor, object, 2, &prefixStringAddr);
    getArg(processor, object, 3, &localNetAddr);
    object->pollCount = 0;

    const char *tftp_path = NULL;
    if(prefixStringAddr) {
         tftp_path = vmirtGetString(object->domain, prefixStringAddr);

         if(DIAG_LOW) {
             vmiMessage("I", PREFIX,
                 "local tftp server is active. Root directory is '%s'",
                 object->tftpPath
             );
         }
    }
    const char *localNet = localNetAddr
        ?  vmirtGetString(object->domain, localNetAddr)
        : "10.0.2.0";


    char vhostname[256];
    vhostname[0] = 0;

    //gethostname(vhostname, sizeof(vhostname));
    const char *bootfile    = NULL;
    const char *vnetmask    = NULL;
    const char *vdhcp_start = NULL;
    const char *vnameserver = NULL;
    const char *vhost       = NULL;
    Bool  restricted        = False;

    object->slirp = net_slirp_init(
        restricted,
        localNet,
        vnetmask,
        vhost,
        vhostname,
        tftp_path,
        bootfile,
        vdhcp_start,
        vnameserver,
        object
    );
    if (!object->slirp) {
        vmiMessage("F", PREFIX, "Unable to start networking");
    }
}

static VMIOS_INTERCEPT_FN(netTxPacket)
{
    Uns32 addr, bytes;
    getArg(processor, object, 0, &addr);
    getArg(processor, object, 1, &bytes);

    // copy data from PSE to host memory space.
    Uns8 packet[bytes];
    vmirtReadNByteDomain(object->domain, addr, packet, bytes, NULL, False);

    if(DIAG_HIGH) vmiMessage("I", PREFIX, "netTxPacket bytes:%d", bytes);

    // send to slirp
    slirp_input(object->slirp, packet, bytes);
}

static VMIOS_INTERCEPT_FN(netPoll)
{
    u_int timeMS;
    getArg(processor, object, 0, &timeMS);

    if(DIAG_HIGH) {
        vmiMessage("I", PREFIX, "netPoll #" FMT_64d " at %d ***********", object->pollCount, timeMS);
    }

    object->pollCount++;

    int nfds = -1;

    Slirp *slirp = object->slirp;

    FD_ZERO(&slirp->rfds);
    FD_ZERO(&slirp->wfds);
    FD_ZERO(&slirp->xfds);

    slirp_select_fill(slirp, &nfds, &slirp->rfds, &slirp->wfds, &slirp->xfds);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    int r = recSelectSocket(nfds + 1, &slirp->rfds, &slirp->wfds, &slirp->xfds, &tv);
    slirp_select_poll(slirp, &slirp->rfds, &slirp->wfds, &slirp->xfds, timeMS, r >= 0);
}

static VMIOS_INTERCEPT_FN(netStats)
{
    slirp_connection_info(object->slirp);
}

static VMIOS_INTERCEPT_FN(netClearQueue)
{
    object->count = 0;
}

static void redirStringError(const char *what)
{
    vmiMessage("F", PREFIX,  "Error parsing redirection : %s", what);
}

static int get_str_sep(char *buf, int buf_size, const char **pp, int sep)
{
    const char *p, *p1;
    int len;
    p = *pp;
    p1 = strchr(p, sep);
    if (!p1)
        return -1;
    len = p1 - p;
    p1++;
    if (buf_size > 0) {
        if (len > buf_size - 1)
            len = buf_size - 1;
        memcpy(buf, p, len);
        buf[len] = '\0';
    }
    *pp = p1;
    return 0;
}

static void redirPort(Slirp *slirp, const char *p, const char *procName)
{
    do {
        Bool udp = False;
        char buf[256], *r;
        struct in_addr host_addr;
        struct in_addr guest_addr;
        int host_port, guest_port;

        memset(&host_addr, 0, sizeof(host_addr));
        host_addr.s_addr = INADDR_ANY;

        if (get_str_sep(buf, sizeof(buf), &p, ':') < 0)
            redirStringError("expected tcp: or udp:");

        if (!strcmp(buf, "tcp")) {
            udp = 0;
        } else if (!strcmp(buf, "udp")) {
            udp = 1;
        } else {
            vmiMessage("F", PREFIX,  "expected tcp: or udp:");
        }

        if (get_str_sep(buf, sizeof(buf), &p, ':') < 0)
            redirStringError("expected host port number");

        host_port = strtol(buf, &r, 0);
        if (r == buf)
            redirStringError("expected host port number");

        if (get_str_sep(buf, sizeof(buf), &p, ':') < 0)
            redirStringError("expected guest ip address");

        if (buf[0] == '\0') {
            strcpy(buf, "10.0.2.15");
        } else {
            if (!inet_aton(buf, &guest_addr))
                redirStringError("expected guest ip address");
        }
        guest_port = strtol(p, &r, 0);
        if (r == p)
            redirStringError("expected guest port number");

        Uns32 actualHostPort = 0;

        int res = slirp_add_hostfwd(
            slirp,
            udp,
            host_addr,
            host_port,
            guest_addr,
            guest_port,
            &actualHostPort
        );

        if (res >= 0) {
            vmiMessage("I", PREFIX,
                "%s Listening on host %s port:%d. Redirecting to guest port:%d",
                procName,
                udp ? "udp" : "tcp",
                // host_port,
                actualHostPort,
                guest_port
            );
        } else {
            vmiMessage("W", PREFIX,  "Failed to set up redirection on port %d", guest_port);
        }
        p = r;
        if(*p != ',')
            break;
        p++;
    } while (1);
}

static VMIOS_INTERCEPT_FN(netAddRedir)
{
    Uns32 strAddr;
    getArg(processor, object, 0, &strAddr);
    if(strAddr) {
        const char *proc = vmirtProcessorName(processor);
        const char *str = vmirtGetString(object->domain, strAddr);
        redirPort(object->slirp, str, proc);
    }
}

// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
    if(DIAG_LOW)
        vmiMessage("I", PREFIX, "Starting SLIRP");

    // What am I ?
    const char *procType = vmirtProcessorType(processor);
    if (strcmp(procType, "pse") != 0) {
        vmiMessage("F", PREFIX, "Processor must be a PSE");
    }
    memEndian  endian    = vmirtGetProcessorDataEndian(processor);
    if(endian != ENDIAN_NATIVE) {
        vmiMessage("F", PREFIX, "Host processor must have same endianity as a PSE");
    }

    // return register (standard ABI)
    object->result = vmiosGetRegDesc(processor, "eax");

    // stack pointer (standard ABI)
    object->sp = vmiosGetRegDesc(processor, "esp");

    object->count = 0;
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
    if(DIAG_LOW)
        vmiMessage("I" ,PREFIX, "Shutting down SLIRP");
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "network",                  // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "amd.ovpworld.org",
        .library = "peripheral",
        .name    = "79C970",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                          // morph callback
    .nextPCCB       = 0,                          // get next instruction address
    .disCB          = 0,                          // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////
    // -------------------   ----------- ------ -----------------
    // Name                  Address     Opaque Callback
    // -------------------   ----------- ------ -----------------
    .intercepts = {
        {"netInit",            0,         True,   netInit       },
        {"netTxPacket",        0,         True,   netTxPacket   },
        {"netPoll",            0,         True,   netPoll       },
        {"netStats",           0,         True,   netStats      },
        {"netClearQueue",      0,         True,   netClearQueue },
        {"netAddRedir",        0,         True,   netAddRedir   },
        {0}
    }
};

//
// Called from slirp to put a packet in the ethernet device receive queue.
// Copies it into the next free buffer.
#define MAX_LENGTH 1600

typedef struct packetS {
    Uns32     length;
    Uns8      data[MAX_LENGTH];
} packet, *packetP;

void netRxPacket(void *opaque, const void *buf, Uns32 len)
{
    vmiosObjectP object = opaque;

    if(object->count >= 32) {
        vmiMessage("F", PREFIX, "Too many packets queued in one poll period. Dropped");
        return;
    }
    if(len >= MAX_LENGTH) {
        vmiMessage("E", PREFIX,
            "rxBuffer is too small for packet (needed:%d, space:%d). Dropped",
            len,
            MAX_LENGTH
        );
        return;
    }
    Uns32 packetAddr =object->packets + (sizeof(packet) * object->count);
    vmirtWriteNByteDomain(object->domain, packetAddr,   &len, 4,   NULL, 0);
    vmirtWriteNByteDomain(object->domain, packetAddr+4, buf,  len, NULL, 0);
    object->count++;
}

void printBuf(const char *what, const void *buf, Uns32 len) {
#if 0
    vmiPrintf("Buf (%s)", what);
    const unsigned char *p = buf;
    Uns32 i = 0;
    while(len--) {
        vmiPrintf(" %02x", *p++);
        if ((++i & 3) == 0) {
            vmiPrintf("  ");
        }
    }
    vmiPrintf("\n");
#endif
}
