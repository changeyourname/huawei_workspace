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


// VMI header files
#include "vmi/vmiAttrs.h"

// model header files
#include "or1kStructure.h"
#include "or1kFunctions.h"

static const char *dictNames[] = {"NORMAL", 0};

//
// Configuration block for instruction-accurate modelling
//
const vmiIASAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION & SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,
    .modelType     = VMI_PROCESSOR_MODEL,
    .dictNames     = dictNames,
    .cpuSize       = sizeof(or1k),

    ////////////////////////////////////////////////////////////////////////
    // CREATE/DELETE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = or1kConstructor,
    .destructorCB  = or1kDestructor,

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB = or1kMorphInstruction,

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .getEndianCB = or1kGetEndian,
    .nextPCCB    = or1kNextInstruction,
    .disCB       = or1kDisassemble,

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .rdPrivExceptCB  = or1kRdPrivExceptionCB,
    .wrPrivExceptCB  = or1kWrPrivExceptionCB,
    .rdAlignExceptCB = or1kRdAlignExceptionCB,
    .wrAlignExceptCB = or1kWrAlignExceptionCB,
    .arithExceptCB   = or1kArithExceptionCB,

    ////////////////////////////////////////////////////////////////////////
    // REGISTER ACCESS SUPPORT ROUTINES (DEBUGGER & SEMIHOSTING)
    ////////////////////////////////////////////////////////////////////////

    .debugCB = or1kDumpRegisters,

    ////////////////////////////////////////////////////////////////////////
    // PORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB     = or1kGetBusPortSpec,

    ////////////////////////////////////////////////////////////////////////
    // PROCESSOR INFO ROUTINE
    ////////////////////////////////////////////////////////////////////////

    .procInfoCB  = or1kProcInfo

};
