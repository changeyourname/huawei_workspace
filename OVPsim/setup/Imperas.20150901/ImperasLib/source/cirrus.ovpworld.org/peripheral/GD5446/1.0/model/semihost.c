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
#include "vmi/vmiPSE.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"


// VGA modules
#include "vga_display.h"
#include "vga_state.h"
#include "cirrus_vga.h"
#include "sdl.h"

// Measure time between wakeups
// #define VGA_TIMING

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

//
// Use this type to pass pointers between PSE and native code in a fashion that
// works on both 32-bit and 64-bit hosts
//
typedef union {
    void *pointer;
    Uns64 u64;
    Uns32 u32[2];
} handle;

typedef struct vmiosObjectS  {

    // return registers (standard ABI)
    vmiRegInfoCP resultLSW;
    vmiRegInfoCP resultMSW;

    // stack pointer (standard ABI)
    vmiRegInfoCP sp;

    // count events
    Uns32        updates;
    Uns32        registerWrites;
    Uns32        screenRamWrites;

    // the VGA RAM mapped region
    memDomainP   domain;
    Addr         sizeM1;

    CirrusVGAStateP vgaState;

} vmiosObject;

//
// FWD references
//
VMI_MEM_READ_FN(vgaDisplayRead);
VMI_MEM_WRITE_FN(vgaDisplayWrite);

//
// Read a function argument using the standard ABI
//
static void getArg(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32        *argOffset,
    void         *result,
    Uns32         argSize
) {
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    Uns32      spAddr;

    // get the current PSE stack pointer
    vmiosRegRead(processor, object->sp, &spAddr);

    // read argument value (looking past 4-byte return address)
    vmirtReadNByteDomain(domain, spAddr+*argOffset+4, result, argSize, 0, True);

    // update argOffset for next argument
    *argOffset += argSize;
}

//
// Macro wrapper for getArg ensuring arguments of correct size are fetched
//
#define GET_ARG(_PROCESSOR, _OBJECT, _ARGOFFSET, _ARG) \
    getArg(_PROCESSOR, _OBJECT, &_ARGOFFSET, &_ARG, sizeof(_ARG))

//
// Convert native pointer to handle and assign this to the PSE result (note that
// handles are 64 bits to ensure portability)
//
inline static void pointerResult(
    vmiProcessorP processor,
    vmiosObjectP  object,
    void         *result
) {
    handle h  = {u64:0};
    h.pointer = result;

    vmiosRegWrite(processor, object->resultLSW, &h.u32[0]);
    vmiosRegWrite(processor, object->resultMSW, &h.u32[1]);
}

//
// Write data passed by reference on the stack
//
static void putData(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index,
    Uns32         size,
    void         *result
) {
    memDomainP domain    = vmirtGetProcessorDataDomain(processor);
    Uns32      argSize   = size;
    Uns32      argOffset = 0;
    Uns32      address;

    GET_ARG(processor, object, argOffset, address);

    // read argument value
    vmirtWriteNByteDomain(domain, address, result, argSize, 0, True);
}

//
// Called to create a display. Returns the displayState object, which is opaque.
//
static VMIOS_INTERCEPT_FN(displayInit)
{
    char  title[32] = "CL GD54xx";
    char *titleP    = title;
    Uns32 argOffset = 0;
    Uns32 titleAddr;

    GET_ARG(processor, object, argOffset, titleAddr);

    if(titleAddr) {

        memDomainP domain = vmirtGetProcessorDataDomain(processor);

        // read argument value
        vmirtReadNByteDomain(domain, titleAddr, &title, sizeof(title), 0, True);
    }

    void *display = sdl_display_init(processor, 0,0, titleP, 640, 480, 32);

    if (!display) {
        vmiMessage("E", "VGA_UIS", "Unable to initialize SDL display");
    } else {
        pointerResult(processor, object, display);
    }
}

//
// Called to create the VGA model state.
// Allocates space for the video ram then maps this directly into simulated
// ram according to the VGA model's port connection.
//
static VMIOS_INTERCEPT_FN(cirrusInit)
{
    Uns32 argOffset = 0;
    Uns32 vgaRamSize;
    Uns32 port_nameAddr;
    Uns32 id;

    GET_ARG(processor, object, argOffset, vgaRamSize);
    GET_ARG(processor, object, argOffset, port_nameAddr);
    GET_ARG(processor, object, argOffset, id);

    // get file name from data domain
    memDomainP  domain      = vmirtGetProcessorDataDomain(processor);
    const char *portName    = vmirtGetString(domain, port_nameAddr);
    void       *vgaRamBase  = malloc(vgaRamSize);
    if (!vgaRamBase) {
        vmiMessage("F", "VGA_NP", "Failed to allocate VGA ram");
    }

    // create a local domain and map native memory to it
    memDomainP      localDomain = vmirtNewDomain("tmp", 32);
    CirrusVGAStateP vgaState    = pci_cirrus_vga_init(vgaRamSize, vgaRamBase, id);

    Addr lo, hi;    // dummies
    Bool isMaster;
    Bool isDynamic;
    memDomainP portDomain = vmipsePlatformPortAttributes(
        processor,
        portName,
        &lo,
        &hi,
        &isMaster,
        &isDynamic
    );

    if (!portDomain || isMaster || !isDynamic) {
        vmiMessage("F", "VGA_NP", "Failed to find remappable slave port '%s'", portName);
    }

    pointerResult(processor, object, vgaState);

    vgaState->memDomain   = portDomain;
    vgaState->localDomain = localDomain;

    //
    // Setup callbacks for Display Memory
    //
    object->vgaState = vgaState;
    vmirtMapCallbacks(
            localDomain,
            0,
            vgaRamSize-1,
            vgaDisplayRead,
            vgaDisplayWrite,
            (void*)object
    );
}

//
// Map the VGA ram at the PCI requested address
//
static VMIOS_INTERCEPT_FN(mapDisplay)
{
    Uns32  argOffset = 0;
    handle vgaStateHandle;
    Uns32  base;

    GET_ARG(processor, object, argOffset, vgaStateHandle);
    GET_ARG(processor, object, argOffset, base);

    CirrusVGAStateP vgaState = vgaStateHandle.pointer;
    Uns32           bytes    = vgaState->vram_size;

    if(vgaState->base != 0xFFFFFFFF) {
        // unmap the old region first
    }
    vgaState->base = base;
    if(base) {

        Addr lowAddr  = base;
        Addr highAddr = base + bytes - 1;

        object->sizeM1   = bytes-1;
        object->domain   = vgaState->localDomain;

        vmipseAliasMemory(
            vgaState->localDomain,
            "memory",
            lowAddr,
            highAddr
        );
    }
    // Here we should really map the other 6 apertures:
    // base+1 = LFB with byte swap
    // base+2 = LFB with byte swap
    // base+3 = LFB with byte swap
    // base+4 = bitblt ram
    // base+5 = bitblt ram
    // base+6 = bitblt ram
    // base+7 = empty
}

//
// Returns true if more than 50mS (wallclock) since it was last called.
// Used to limit the refresh rate on a fast computer,
// given that there's no point in updating the screen faster than 20Hz.
// USING THIS FUNCTION AFFECTS REPEATABILITY
//

//
// Called to update the display
// Arg0: pointer to vga state structure.
// Arg1: pointer to display state structure.
//
static VMIOS_INTERCEPT_FN(vgaDisplay)
{
    Uns32  argOffset = 0;
    handle vgaStateHandle;
    handle displayStateHandle;

    GET_ARG(processor, object, argOffset, vgaStateHandle);
    GET_ARG(processor, object, argOffset, displayStateHandle);

    VGAStateP vgaState     = vgaStateHandle.pointer;
    void     *displayState = displayStateHandle.pointer;

    if ((object->screenRamWrites || object->registerWrites) && sdl_needs_update(displayState)) {
        object->updates++;
        #ifdef DISPLAY_OPTIMISATION_STATS
            vmiPrintf("Update:%6d",          object->updates);
            vmiPrintf("    ram:%6d",         object->screenRamWrites);
            vmiPrintf("    reg:%6d",         object->registerWrites);
        #endif
        object->screenRamWrites = 0;
        object->registerWrites  = 0;

        vga_update_display(vgaState, displayState);
    }
}

static VMIOS_INTERCEPT_FN(ioportRead)
{
    Uns32  argOffset = 0;
    handle vgaStateHandle;
    Uns32  address;
    Uns32  diag;

    GET_ARG(processor, object, argOffset, vgaStateHandle);
    GET_ARG(processor, object, argOffset, address);
    GET_ARG(processor, object, argOffset, diag);

    CirrusVGAStateP vgaState = vgaStateHandle.pointer;

    Uns32 result = cirrus_vga_ioport_read(vgaState, address, diag);

    vmiosRegWrite(processor, object->resultLSW, &result);
}

static VMIOS_INTERCEPT_FN(ioportWrite)
{
    Uns32  argOffset = 0;
    handle vgaStateHandle;
    Uns32  address;
    Uns32  data;
    Uns32  diag;

    object->registerWrites++;

    GET_ARG(processor, object, argOffset, vgaStateHandle);
    GET_ARG(processor, object, argOffset, address);
    GET_ARG(processor, object, argOffset, data);
    GET_ARG(processor, object, argOffset, diag);

    CirrusVGAStateP vgaState = vgaStateHandle.pointer;

    cirrus_vga_ioport_write(vgaState, address, data, diag);
}

VMI_MEM_READ_FN(vgaDisplayRead) {
//    vmiMessage("F", __func__, "Address=0x%08x, Data=0x%08x, Bytes=%d", (Uns32)address, *(Uns32*)value, bytes);
    vmiosObjectP object = (vmiosObjectP) userData;
    CirrusVGAStateP vgaState = object->vgaState;

    switch (bytes) {
    case 1: {
        *(Uns8*)value = cirrus_linear_readb(vgaState, address);
        break;
    }
    case 2: {
        *(Uns32*)value = cirrus_linear_readw(vgaState, address);

        break;
    }
    case 4: {
        *(Uns32*)value = cirrus_linear_readl(vgaState, address);
        break;
    }
    case 8: {
        ((Uns32*)value)[0] = cirrus_linear_readl(vgaState, address);
        ((Uns32*)value)[1] = cirrus_linear_readl(vgaState, address + 4);
        break;
    }
    default:
        vmiMessage("F", __func__, "Cannot read %d bytes", bytes);
        break;
    }
}

void badwritecompare(Uns32 a, Uns32 b) {
    vmiPrintf("a=%x b=%x\n", a, b);
}

VMI_MEM_WRITE_FN(vgaDisplayWrite) {
//    vmiMessage("I", __func__, "Address=0x%08x, Data=0x%08x, Bytes=%d", (Uns32)address, *(Uns32*)value, bytes);

    vmiosObjectP object = (vmiosObjectP) userData;
    CirrusVGAStateP vgaState = object->vgaState;
    object->screenRamWrites++;

    // test the local write value

    switch (bytes) {
    case 1: {
        cirrus_linear_writeb(vgaState, address, *(Uns8*)value);
        break;
    }
    case 2: {
        cirrus_linear_writew(vgaState, address, *(Uns16*)value);
        break;
    }
    case 4: {
        cirrus_linear_writel(vgaState, address, *(Uns32*)value);
        break;
    }
    case 8: {
        cirrus_linear_writel(vgaState, address, ((Uns32*)value)[0]);
        cirrus_linear_writel(vgaState, address + 4, ((Uns32*)value)[1]);
        break;
    }
    default:
        vmiMessage("F", __func__, "Cannot write %d bytes", bytes);
        break;
    }

}

static VMIOS_INTERCEPT_FN(ImperasTestModeTimeout)
{
    char * testEnv     = getenv("IMPERAS_TESTMODE_TIMEOUT");
    double testTimeout = 0;
    Uns32  result      = 0;

    if(testEnv) {
        testTimeout = atof(testEnv);
        vmiMessage("W", "VGA_SDL_TEST", "Imperas Test Mode Detected. Timeout %f", testTimeout);
        result = 1;
    }

    putData(processor, object, 0, sizeof(double), &testTimeout);

    vmiosRegWrite(processor, object->resultLSW, &result);
}


// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
    // What am I ?
    const char *procType = vmirtProcessorType(processor);
    memEndian   endian   = vmirtGetProcessorDataEndian(processor);

    if (strcmp(procType, "pse") != 0) {
        vmiMessage("F", "VGA_BP", "Processor must be a PSE\n");
    }

    if(endian != ENDIAN_NATIVE) {
        vmiMessage("F", "VGA_BE", "Host processor must same endianity as a PSE\n");
    }

    // return registers (standard ABI)
    object->resultLSW = vmiosGetRegDesc(processor, "eax");
    object->resultMSW = vmiosGetRegDesc(processor, "edx");

    // stack pointer (standard ABI)
    object->sp = vmiosGetRegDesc(processor, "esp");

    init_expand_tables();
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
    //vmiMessage("I" ,"VGA_DN", "Shutting down");
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
    .packageName    = "vga",                      // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "cirrus.ovpworld.org",
        .library = "peripheral",
        .name    = "GD5446",
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
    // -------------------          -------- ------  -----------------
    // Name                         Address  Opaque  Callback
    // -------------------          -------- ------  -----------------
    .intercepts = {
        {"displayInit",             0,       True,   displayInit            },
        {"cirrusInit",              0,       True,   cirrusInit             },
        {"vgaDisplay",              0,       True,   vgaDisplay             },
        {"mapDisplay",              0,       True,   mapDisplay             },
        {"ioportRead",              0,       True,   ioportRead             },
        {"ioportWrite",             0,       True,   ioportWrite            },
        {"ImperasTestModeTimeout",  0,       True,   ImperasTestModeTimeout },
        {0}
    }
};
