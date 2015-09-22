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

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

// VGA module
#include "sdlInput.c.h"

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

#define DIAG_LOW(_obj)    ((_obj->diagLevel & 3) >= 1)
#define DIAG_MEDIUM(_obj) ((_obj->diagLevel & 3) >= 2)
#define DIAG_HIGH(_obj)   ((_obj->diagLevel & 3) == 3)

typedef struct vmiosObjectS  {

    // return register (standard ABI)
    vmiRegInfoCP result;
    // stack pointer (standard ABI)
    vmiRegInfoCP sp;
    Uns32  diagLevel;

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
// Called to start the keyboard service.
//
static VMIOS_INTERCEPT_FN(inputInit)
{
    Uns32 diag;
    Uns32 grabDisable;
    Uns32 enableCursor;
    getArg(processor, object, 0, &diag);
    getArg(processor, object, 1, &grabDisable);
    getArg(processor, object, 2, &enableCursor);
    sdlInputInit(diag, grabDisable, enableCursor);
    object->diagLevel = diag;
}

//
// Called to end the keyboard service.
//
static VMIOS_INTERCEPT_FN(inputCleanUp)
{
    sdlInputCleanUp();
}

//
// Called to fetch the next event
//
static VMIOS_INTERCEPT_FN(inputPoll)
{
    Uns32 statep;
    Uns32 useMouse;

    getArg(processor, object, 0, &statep);
    getArg(processor, object, 1, &useMouse);
    static InputState native;

    Bool result = sdlInputPoll(&native,useMouse);

    if (result) {
        memDomainP domain = vmirtGetProcessorDataDomain(processor);
        vmirtWriteNByteDomain(domain, statep, &native, sizeof(native), 0, True);
    }
    vmiosRegWrite(processor, object->result, &result);
}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
    // What am I ?
    const char *procType = vmirtProcessorType(processor);
    if (strcmp(procType, "pse") != 0) {
        vmiMessage("F", "SDL_IN", "Processor must be a PSE\n");
    }
    memEndian  endian    = vmirtGetProcessorDataEndian(processor);
    if(endian != ENDIAN_NATIVE) {
        vmiMessage("F", "SDL_IN", "Host processor must be same endian as a PSE (little endian)\n");
    }

    // return register (standard ABI)
    object->result = vmiosGetRegDesc(processor, "eax");

    // stack pointer (standard ABI)
    object->sp = vmiosGetRegDesc(processor, "esp");

}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
    sdlInputCleanUp();
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
    .packageName    = "sdlInput_semihost",        // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "ovpworld.org",
        .library = "modelSupport",
        .name    = "sdlInput",
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
        {"kbControlCleanUp",    0,       True,   inputCleanUp },
        {"kbControlInit",       0,       True,   inputInit    },
        {"kbControlPoll",       0,       True,   inputPoll    },
        {0}
    }
};
