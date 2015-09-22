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
/*                  D E B U G G E R   I N T E R F A C E                       */
/*                                                                            */
/******************************************************************************/

#ifndef VMI_DBG_H
#define VMI_DBG_H

#include "vmi/simAddrTypes.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


//
// Type of function called by the debugger to read a register
// Return code indicates whether the read succeeded.
//
// The endianness of the returned data should be that of the host.
//
#define VMI_REG_READ_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    vmiRegInfoCP  reg,          \
    void         *buffer        \
)
typedef VMI_REG_READ_FN((*vmiRegReadFn));

//
// Type of function called by the debugger to write a register
// Return code indicates whether the write succeeded
//
// The endianness of the supplied data should be that of the host.
//
#define VMI_REG_WRITE_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    vmiRegInfoCP  reg,          \
    const void   *buffer        \
)
typedef VMI_REG_WRITE_FN((*vmiRegWriteFn));

//
// Function type used to emit instruction trace for the passed simulated
// address
//
#define VMI_TRACE_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,        \
    Addr          simAddress,       \
    Bool          isException,      \
    Bool          isFirst,          \
    Bool          isRegisterIntro   \
)
typedef VMI_TRACE_FN((*vmiTraceFn));

//
// Function type used to dump processor register state
//
#define VMI_DEBUG_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Bool          isTrace,      \
    Bool          isException,  \
    Bool          isFirst       \
)
typedef VMI_DEBUG_FN((*vmiDebugFn));

//
// Type of function called by the debugger to obtain information about the
// register groups in the simulated processor
//
#define VMI_REG_GROUP_FN(_NAME) vmiRegGroupCP _NAME( \
    vmiProcessorP processor,    \
    vmiRegGroupCP prev          \
)
typedef VMI_REG_GROUP_FN((*vmiRegGroupFn));

//
// Type of function called by the debugger to obtain information about the
// registers in the simulated processor
//
#define VMI_REG_INFO_FN(_NAME) vmiRegInfoCP _NAME( \
    vmiProcessorP processor,    \
    vmiRegInfoCP  prev,         \
    Bool          gdbFrame      \
)
typedef VMI_REG_INFO_FN((*vmiRegInfoFn));

//
// Type of function called by the debugger to obtain information about the
// exceptions in the simulated processor
//
#define VMI_EXCEPTION_INFO_FN(_NAME) vmiExceptionInfoCP _NAME( \
    vmiProcessorP      processor,   \
    vmiExceptionInfoCP prev         \
)
typedef VMI_EXCEPTION_INFO_FN((*vmiExceptionInfoFn));

//
// Type of function called by the debugger to obtain information about the
// current processor exception
//
#define VMI_GET_EXCEPTION_FN(_NAME) vmiExceptionInfoCP _NAME( \
    vmiProcessorP processor \
)
typedef VMI_GET_EXCEPTION_FN((*vmiGetExceptionFn));

//
// Type of function called by the debugger to obtain information about the
// modes in the simulated processor
//
#define VMI_MODE_INFO_FN(_NAME) vmiModeInfoCP _NAME( \
    vmiProcessorP processor,    \
    vmiModeInfoCP prev          \
)
typedef VMI_MODE_INFO_FN((*vmiModeInfoFn));

//
// Type of function called by the debugger to obtain information about the
// current processor mode
//
#define VMI_GET_MODE_FN(_NAME) vmiModeInfoCP _NAME(vmiProcessorP processor)
typedef VMI_GET_MODE_FN((*vmiGetModeFn));

//
// This type is used to indicate the group to which a register belongs (for
// organizational purposes in a debugger)
//
typedef struct vmiRegGroupS {
    const char *name;           // register group name
} vmiRegGroup;

//
// Enumeration of register usage
//
typedef enum {
    vmi_REG_NONE = 0,           // no special usage for this register
    vmi_REG_PC   = 1,           // register is the program counter
    vmi_REG_SP   = 2,           // register is the stack pointer
    vmi_REG_FP   = 3            // register is the frame pointer
} vmiRegUsage;

//
// Enumeration of register access
//
typedef enum {
    vmi_RA_NONE = 0x0,          // no register access
    vmi_RA_R    = 0x1,          // register is read-only
    vmi_RA_W    = 0x2,          // register is write-only
    vmi_RA_RW   = 0x3           // register is read/write
} vmiRegAccess;

//
// Structure used to pass information about the registers in a simulated
// processor to the debugger
//
typedef struct vmiRegInfoS {
    const char   *name;                 // register identification name
    const char   *description;          // description string
    vmiRegGroupCP group;                // group for this register
    Uns32         gdbIndex;             // gdb ordinal index number
    vmiRegUsage   usage         :  2;   // any special usage for this register
    vmiRegAccess  access        :  2;   // allowed access
    Bool          noSaveRestore :  1;   // does not participate in save/restore
    Bool          noTraceChange :  1;   // does not participate in tracing
    Uns32         unused        : 10;   // unused fields
    Uns32         bits          : 16;   // size of register in bits
    vmiRegReadFn  readCB;               // read callback function
    vmiRegWriteFn writeCB;              // write callback function
    vmiReg        raw;                  // raw register value (if no callback)
    void         *userData;             // model-specific data pointer
} vmiRegInfo;

//
// Special readCB and writeCB values specifying that read and write of raw
// register values is allowed (i.e. without callback), requiring that either:
// 1. the 'raw' field is set with the appropriate register; or:
// 2. the userData argument is set to the register offset in the processor
//    structure (deprecated backwards-compatible mode).
// With the introduction of the 'raw' field in the vmiRegInfo structure, these
// special values are not required (specify the 'raw' vmiReg and omit the the
// read/write callback to achieve the same effect).
//
#define VMI_REG_RAW_READ_CB  ((vmiRegReadFn)(-1))
#define VMI_REG_RAW_WRITE_CB ((vmiRegWriteFn)(-1))

//
// Define plain read/write register in processor
//
#define VMI_REG_RAW_RW(_TP, _F) { \
    name   : #_F,                       \
    access : vmi_RA_RW,                 \
    bits   : sizeof(((_TP)0)->_F)*8,    \
    raw    : VMI_CPU_REG(_TP, _F)       \
}

//
// Define plain read-only register in processor
//
#define VMI_REG_RAW_R(_TP, _F) { \
    name   : #_F,                       \
    access : vmi_RA_R,                  \
    bits   : sizeof(((_TP)0)->_F)*8,    \
    raw    : VMI_CPU_REG(_TP, _F)       \
}

//
// Structure used to pass information about an exception to the debugger
//
typedef struct vmiExceptionInfoS {
    const char *name;           // exception name
    Uns32       code;           // model-specific exception code
    const char *description;    // description string
} vmiExceptionInfo;

//
// Structure used to pass information about a processor mode to the debugger
//
typedef struct vmiModeInfoS {
    const char *name;           // mode name
    Uns32       code;           // model-specific mode code
    const char *description;    // description string
} vmiModeInfo;

//
// Function type used to find a processor's type
//
#define VMI_PROC_DESC_FN(_NAME) const char * _NAME( \
    vmiProcessorP processor \
)

typedef VMI_PROC_DESC_FN((*vmiProcDescFn));

#endif
