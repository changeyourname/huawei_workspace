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
/*                  S E M I - H O S T I N G   S U P P O R T                   */
/*                                                                            */
/*                      A T T R I B U T E   T Y P E S                         */
/*                                                                            */
/******************************************************************************/

#ifndef VMIOS_ATTRS_H
#define VMIOS_ATTRS_H

#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// VMIOS CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Model constructor
//
#define VMIOS_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,      \
    vmiosObjectP  object,         \
    void         *parameterValues \
)
typedef VMIOS_CONSTRUCTOR_FN((*vmiosConstructorFn));

//
// Model destructor
//
#define VMIOS_DESTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object        \
)
typedef VMIOS_DESTRUCTOR_FN((*vmiosDestructorFn));


////////////////////////////////////////////////////////////////////////////////
// SAVE / RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type is used to implement model save
//
#define VMIOS_SAVE_STATE_FN(_NAME) void _NAME( \
    vmiosObjectP    object,         \
    vmiSaveContextP cxt             \
)
typedef VMIOS_SAVE_STATE_FN((*vmiosSaveStateFn));

//
// This callback function type is used to implement model restore
//
#define VMIOS_RESTORE_STATE_FN(_NAME) void _NAME( \
    vmiosObjectP       object,      \
    vmiRestoreContextP cxt          \
)
typedef VMIOS_RESTORE_STATE_FN((*vmiosRestoreStateFn));


////////////////////////////////////////////////////////////////////////////////
// TYPES USED TO DEFINE INTERCEPTIONS
////////////////////////////////////////////////////////////////////////////////

//
// This defines the function type called for an intercepted function.
// 'atOpaqueIntercept' is True if the current address is opaquely intercepted
// (not necessarily by this callback) - useful for transparent intercepts that
// decode instructions and therefore need to know whether the current
// instruction is truly going to be executed
//
#define VMIOS_INTERCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,        \
    vmiosObjectP  object,           \
    Addr          thisPC,           \
    const char   *context,          \
    void         *userData,         \
    Bool          atOpaqueIntercept \
)
typedef VMIOS_INTERCEPT_FN((*vmiosInterceptFn));

//
// Intercept attributes (bitmask)
//
typedef enum vmiosInterceptAttrE {
    OSIA_NONE   = 0x0,              // no special attributes
    OSIA_OPAQUE = 0x1,              // opaque intercept (otherwise transparent)
    OSIA_THREAD = 0x2,              // run in thread (otherwise synchronous)
} vmiosInterceptAttr;

//
// Intercept table entry
//
typedef struct vmiosInterceptDescS {
    const char        *name;        // for interception by name
    Addr               simAddress;  // for interception by address
    vmiosInterceptAttr attrs;       // intercepted function attributes
    vmiosInterceptFn   interceptCB; // interception callback
    void              *userData;    // client-specific data pointer
    Bool               skipPrologue;// Use gdb to find the prologue (not implemented yet)
} vmiosInterceptDesc;


////////////////////////////////////////////////////////////////////////////////
// MORPH OVERRIDE CALLBACK
////////////////////////////////////////////////////////////////////////////////

//
// This routine may be used to override the default behavior of the morpher for
// a particular instruction. If the instruction should be overridden, the
// function should return a vmiosInterceptFn function for the required
// interception and set byref arguments 'opaque' (True->opaque, False->
// transparent) 'context' (a user-defined context string) and 'userData'
// (an application-specific argument passed uninterpreted to the intercept
// function); otherwise, it should return NULL.
//
#define VMIOS_MORPH_FN(_NAME) vmiosInterceptFn _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    Addr          thisPC,       \
    Uns8          inDelaySlot,  \
    Bool          firstInBlock, \
    Bool         *opaque,       \
    const char  **context,      \
    void        **userData      \
)
typedef VMIOS_MORPH_FN((*vmiosMorphFn));

//
// This routine may be used to override the default size of an instruction. If
// the size should be overridden, the function should supply the next program
// counter using the 'nextPC' byref argument and return True; otherwise, it
// should return False.
//
#define VMIOS_NEXT_PC_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    Addr          thisPC,       \
    Addr         *nextPC        \
)
typedef VMIOS_NEXT_PC_FN((*vmiosNextPCFn));


////////////////////////////////////////////////////////////////////////////////
// FORMALS
////////////////////////////////////////////////////////////////////////////////

#define VMIOS_PARAM_SPEC_FN(_NAME) vmiParameterP _NAME( \
    vmiosObjectP  object,   \
    vmiParameterP prev      \
)
typedef VMIOS_PARAM_SPEC_FN((*vmiosParamSpecFn));

//
// Type of function called by simulator to get the size of the parameter value
// table
//
#define VMIOS_PARAM_TABLE_SIZE_FN(_NAME) Uns32 _NAME ( \
    vmiosAttrCP plugin  \
)
typedef VMIOS_PARAM_TABLE_SIZE_FN((*vmiosParamValueSizeFn));


////////////////////////////////////////////////////////////////////////////////
// DISASSEMBLE OVERRIDE CALLBACK
////////////////////////////////////////////////////////////////////////////////

//
// Return a string representing the disassembled instruction at the passed
// address
//
#define VMIOS_DISASSEMBLE_FN(_NAME) const char *_NAME( \
    vmiProcessorP  processor,   \
    vmiosObjectP   object,      \
    Addr           thisPC,      \
    vmiDisassAttrs attrs        \
)
typedef VMIOS_DISASSEMBLE_FN((*vmiosDisassFn));


//
// This structure defines attributes for semihosting support
//
typedef struct vmiosAttrS {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    const char           *versionString;    // version string (THIS MUST BE FIRST)
    vmiModelType          modelType;        // type of model (enum)
    const char           *packageName;      // package name
    Uns32                 objectSize;       // size in bytes of VMIOS object

    ////////////////////////////////////////////////////////////////////////
    // MODEL STATUS
    ////////////////////////////////////////////////////////////////////////

    vmiVisibility         visibility;       // model visibility (enum)
    vmiReleaseStatus      releaseStatus;    // model release status (enum)

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosSaveStateFn      saveCB;           // model state save callback
    vmiosRestoreStateFn   restoreCB;        // model state restore callback

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosConstructorFn    constructorCB;    // constructor
    vmiosDestructorFn     destructorCB;     // destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosMorphFn          morphCB;          // morph override callback
    vmiosNextPCFn         nextPCCB;         // get next instruction address
    vmiosDisassFn         disCB;            // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // FORMAL PARAMETERS iterators to find parameters accepted by this model
    ////////////////////////////////////////////////////////////////////////

    vmiosParamSpecFn      paramSpecsCB;     // callback for next formal param
    vmiosParamValueSizeFn paramValueSizeCB; // callback to get size of table

    ////////////////////////////////////////////////////////////////////////
    // Model VLNV
    ////////////////////////////////////////////////////////////////////////

    vmiVlnvInfo           vlnv;              // vendor/library/name/version

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    vmiosInterceptDesc    intercepts[];     // null-terminated intercept list

} vmiosAttr;


#endif

