/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

/******************************************************************************/
/*                                                                            */
/*            V I R T U A L   M A C H I N E   I N T E R F A C E               */
/*                                                                            */
/*                          P A R A M E T E R S                               */
/*                                                                            */
/******************************************************************************/

#ifndef VMI_MODEL_INFO_H
#define VMI_MODEL_INFO_H

#include "vmi/vmiTyperefs.h"
#include "vmi/vmiTypes.h"
#include "hostapi/impTypes.h"

#if (IMPERAS_WINDOWS==1)
#    define VMI_EXE_SUFFIX ".exe"
#else
#    define VMI_EXE_SUFFIX ""
#endif

typedef struct vmiVlnvInfoS {
    const char  *vendor;
    const char  *library;
    const char  *name;
    const char  *version;
} vmiVlnvInfo, *vmiVlnvInfoP;

//
// Data needed by a simulator for processor model.
//
typedef struct vmiProcessorInfoS {

    // Location of this model
    vmiVlnvInfo  vlnv;

    // semihost library used by default with this model.
    vmiVlnvInfo  semihost;

    // Path to the gdb used to debug this model.
    // Remember to use the VMI_EXE_SUFFIX so this works on Windows
    const char  *gdbPath;

    // Flags (if any) required by this GDB for this processor
    const char  *gdbFlags;

    // Startup commands (if any) sent to this GDB for this processor
    // Separate and terminate each command with newline (\n)
    // e.g. "command one\ncommand two\n"
    const char  *gdbInitCommands;

    // CPU Helper used by this model
    vmiVlnvInfo  helper;

    // If endianFixed is true, this is it, otherwise ignore it.
    memEndian    endian;

    // This model supports one endian
    Bool         endianFixed;

    // By default, choose this model to execute a program with the following
    // elf code. Only one model in your library should have this set.
    Bool         defaultModel;

    // When reading executables for this model, the loader should use
    // physical addresses, not virtual.
    // (This is a legacy feature; unlikely to be required).
    Bool         loadPhysical;

    // True if this model can run in QuantumLeap mode
    Bool         QLQualified;

    // standard ELF code used by this processors
    Uns32        elfCode;

    // Alternative ELF codes used by this processor
    const Uns32 *alternativeElfCodes;

    // Deprecated field
    const char  *variant;

    // Processor family string
    const char  *family;

    // Processor group strings
    const char  *groupH;
    const char  *groupL;

    // If the gdb associated with this processor sets the lower address bits
    // to indicate the processor mode, use this field to clear the bits prior
    // to setting a breakpoint.
    //  =0 or 1 if no snap required
    //  =2 to snap to 2-byte short
    //  =4 to snap to 4-byte word
    //  =8 to snap to 8-byte long word

    Uns32        debugSnapAddress;

} vmiProcessorInfo;

//
// Type of function called by simulator to get general info about this model
//
#define VMI_PROC_INFO_FN(_NAME) vmiProcessorInfoCP _NAME ( \
    vmiProcessorP processor \
)

typedef VMI_PROC_INFO_FN((*vmiProcessorInfoFn));

#endif

