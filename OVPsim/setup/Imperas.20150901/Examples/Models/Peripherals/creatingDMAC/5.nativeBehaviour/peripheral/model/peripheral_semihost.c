/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiRt.h"

// model includes
#include "../pse/dmac.igen.h"


//
// Prefix for messages from this module
//
#define PREFIX     "PERIPHERAL_SEMI"
#define CPU_PREFIX PREFIX


typedef struct vmiosObjectS  {

    // return register (standard ABI)
    vmiRegInfoCP result;

    // stack pointer (standard ABI)
    vmiRegInfoCP sp;

    // PSE data domain (passed to read and write callbacks)
    memDomainP pseDomain;

    memDomainP portDomain;

    // diagnostics enabled
    Uns32 diag;

    // alias of internal channel structure of DMAC
    DMACSP_ab32ch0_dataT channel;

    // record position of message sent
    Uns32 msgPtr;

} vmiosObject;

//
// Read a function argument using the standard ABI
//
static void getArg(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index,
    void         *result
) {
    Uns32 argSize   = 4;
    Uns32 argOffset = (index+1)*argSize;
    Uns32 spAddr;

    // get the stack
    vmiosRegRead(processor, object->sp, &spAddr);

    // read argument value
    vmirtReadNByteDomain(
        object->pseDomain, spAddr+argOffset, result, argSize, 0, False
    );
}

const char testString[] = "Native code test string";

static VMIOS_INTERCEPT_FN(transferDataNative) {

    Uns32 addressSrc, addressDest;
    Uns32 bytes;

    getArg(processor, object, 0, &addressSrc);
    getArg(processor, object, 1, &addressDest);
    getArg(processor, object, 2, &bytes);

    if(object->diag) {
        vmiMessage("I", PREFIX, "Send native data 0x%08x to 0x%08x (%d bytes)", addressSrc, addressDest, bytes);
    }
    char tmp[256];

    vmirtReadNByteDomain(object->portDomain, addressSrc, tmp, bytes , 0, False);
    vmirtWriteNByteDomain(object->portDomain, addressDest, tmp, bytes , 0, False);

    // return bytes transferred as result
    vmiosRegWrite(processor, object->result, &bytes);
}


//
// Called to initialise
//
static VMIOS_INTERCEPT_FN(initSemiHost) {

    memDomainP pseDomain = object->pseDomain;

    Uns32 base;

    getArg(processor, object, 0, &base);
    getArg(processor, object, 1, &object->diag);

    DMACSP_ab32ch0_dataTP channel = &object->channel;
    Uns32 top                     = base+sizeof(DMACSP_ab32ch0_dataT)-1;

    // map the memory for the DMAchannel structure
    vmirtMapNativeMemory(pseDomain, base, top, channel);

    const char *portName = "MWRITE";
    Addr lo, hi;    // dummies
    Bool isMaster;
    Bool isDynamic;
    object->portDomain = vmipsePlatformPortAttributes(
        processor,
        portName,
        &lo,
        &hi,
        &isMaster,
        &isDynamic
    );

    vmiMessage("I", "INIT", "'%s', hi " FMT_Ax " lo " FMT_Ax " master %u dynamic %u", portName, lo, hi, isMaster, isDynamic);


    // return channel number as result
    vmiosRegWrite(processor, object->result, &channel);
}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    // return register (standard ABI)
    object->result = vmiosGetRegDesc(processor, "eax");

    // stack pointer (standard ABI)
    object->sp = vmiosGetRegDesc(processor, "esp");

    // store the PSE data domain
    object->pseDomain = vmirtGetProcessorDataDomain(processor);

    // Initialise variables
    object->msgPtr = 0;
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
    if(object->diag) {
        vmiMessage("I" ,PREFIX, "Shutting down");
    }
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,            // version string
    .modelType     = VMI_INTERCEPT_LIBRARY,  // type
    .packageName   = PREFIX,                 // description
    .objectSize    = sizeof(vmiosObject),    // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = constructor,            // object constructor
    .destructorCB  = destructor,             // object destructor

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    =
    // -------------------   ----------- ------ -----------------
    // Name                  Address     Opaque Callback
    // -------------------   ----------- ------ -----------------
    {
        {"transferDataNative",    0,          True,  transferDataNative },
        {"initSemiHost",          0,          True,  initSemiHost },
        {0}
    }
};
