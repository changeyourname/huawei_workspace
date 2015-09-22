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


// Types used by the Platform API.
// This file is included by other API files so should not be included directly.

#ifndef ICMTYPES_H
#define ICMTYPES_H

#include "hostapi/impTypes.h"
#include "ord/ordObjAttrs.h"
#include "vmi/vmiTypes.h"
#include <stdarg.h>


////////////////////////////////////////////////////////////////////////////////
// Types.
////////////////////////////////////////////////////////////////////////////////

/// Simulator time (in seconds).
typedef long double  icmTime;


////////////////////////////////////////////////////////////////////////////////
// Enums.
////////////////////////////////////////////////////////////////////////////////

/// Supplementary information (for time advance callback).
typedef enum icmAdvanceTimeInfoE {
    ICM_TA_NONE = 0x00, ///< No supplementary information.
    ICM_TA_SIM = 0x01, ///< Simulator stop time reached.
    ICM_TA_DBG = 0x02, ///< Debug stop time reached.
    ICM_TA_END = 0x04  ///< End of simulation.
} icmAdvanceTimeInfo;

/// Bus port type.
typedef enum icmBusPortTypeE {
    ICM_BPT_UNSET , ///< Port type is not set.
    ICM_BPT_MASTER , ///< Bus master port.
    ICM_BPT_SLAVE , ///< Bus slave port.
    ICM_BPT_MASTERSLAVE   ///< Bus master and slave port.
} icmBusPortType;

/// Bus domain type.
typedef enum icmDomainTypeE {
    ICM_DOM_CODE , ///< Bus domain used to fetch instructions.
    ICM_DOM_DATA , ///< Bus domain used to read/write data.
    ICM_DOM_OTHER   ///< Bus domain of other uses.
} icmDomainType;

/// Command line parser argument type. See CLPA_*_FN definitions.
typedef enum icmCLPArgTypeE {
    ICM_AT_NONE , ///< Do not use.
    ICM_AT_BOOLVAL , ///< Argument sets variable of type Boolean.
    ICM_AT_INT32VAL , ///< Argument sets variable of type Int32.
    ICM_AT_UNS32VAL , ///< Argument sets variable of type Uns32.
    ICM_AT_UNS64VAL , ///< Argument sets variable of type Uns64.
    ICM_AT_DOUBLEVAL , ///< Argument sets variable of type Double.
    ICM_AT_STRINGVAL , ///< Argument sets variable of type String.
    ICM_AT_STRINGLIST , ///< One list element for each use of the argument.
    ICM_AT_STRINGSLAST , ///< This flag must be last. Builds list of all args following.
    ICM_AT_PAIRLIST , ///< One name=value pair for each use of the argument.
    ICM_AT_GLOB_STRING , ///< One list element for each use of the argument. Strings are
           ///  file-glob expanded.
    ICM_AT_FC_BOOLEAN , ///< Function called each time flag is specified.
    ICM_AT_FC_INT32 , ///< Function called each time Int32 argument is specified.
    ICM_AT_FC_UNS32 , ///< Function called each time Uns32 argument is specified.
    ICM_AT_FC_UNS64 , ///< Function called each time Uns64 argument is specified.
    ICM_AT_FC_DOUBLE , ///< Function called each time double argument is specified.
    ICM_AT_FC_STRING , ///< Function called each time string argument is specified.
    ICM_AT_FC_PAIR , ///< Function called each time name=value is specified.
    ICM_AT_FC_ARGV , ///< Function called with a list of arguments.
    ICM_AT_FC_ARGVLAST , ///< This flag must be last. Function called with a list of all
           ///  following arguments.
    ICM_AT_FC_ARGVPAIR   ///< Function called with each list of name=value arguments.
} icmCLPArgType;

/// Command line parser argument class. Use to select what standard arguments to
/// a parser.
typedef enum icmCLPArgClassE {
    ICM_AC_NONE = 0x00, ///< No standard arguments.
    ICM_AC_BASIC = 0x01, ///< Basic arguments.
    ICM_AC_EXT1 = 0x02, ///< Basic demo arguments.
    ICM_AC_EXT2 = 0x04, ///< Extended demo arguments.
    ICM_AC_SIM = 0x08, ///< Simulator arguments.
    ICM_AC_LIB = 0x10, ///< Library arguments .
    ICM_AC_ENG = 0x20, ///< (do not use).
    ICM_AC_ALL = 0x18  ///< Simulator and Library.
} icmCLPArgClass;

/// Direction.
typedef enum icmDirectionE {
    ICM_ANY = 0x0, ///< For internal use - DO NOT USE.
    ICM_INPUT = 0x1, ///< Slave bus port, input net port or input FIFO port.
    ICM_OUTPUT = 0x2, ///< Master bus port, output net port or output FIFO port.
    ICM_INOUT = 0x3  ///< input net port (not FIFO or bus).
} icmDirection;

/// Imagefile endian-ness.
typedef enum icmEndianE {
    ICM_ENDIAN_NONE = 0x0, ///< No endian specified.
    ICM_ENDIAN_LITTLE = 0x1, ///< Definitely little.
    ICM_ENDIAN_BIG = 0x2, ///< Definitely big.
    ICM_ENDIAN_EITHER = 0x3  ///< Could be either (not used in this release).
} icmEndian;

/// FIFO port type.
typedef enum icmFifoPortTypeE {
    ICM_FPT_NODIR , ///< FIFO Port direction is unset.
    ICM_FPT_INPUT , ///< FIFO Port used for input.
    ICM_FPT_OUTPUT   ///< FIFO Port used for output.
} icmFifoPortType;

/// How data is presented in the host buffer.
typedef enum icmHostEndianE {
    ICM_HOSTENDIAN_HOST = 0x0, ///< Buffer is same endian as host (LE on X86).
    ICM_HOSTENDIAN_TARGET = 0x1, ///< Buffer is same endian as target (ie, not converted).
    ICM_HOSTENDIAN_BIG = 0x2, ///< Buffer is big endian.
    ICM_HOSTENDIAN_LITTLE = 0x3  ///< Buffer is little endian.
} icmHostEndian;

/// Use these values in a bit mask to specify simulation attributes to
/// icmInitPlatform().
typedef enum icmInitAttrsE {
    ICM_INIT_DEFAULT = 0x00000000, ///< Default behavior.
    ICM_ENABLE_IMPERAS_INTERCEPTS = 0x00000001, ///< Enable Imperas intercepts.
    ICM_STOP_ON_CTRLC = 0x00000002, ///< Stop simulation when Ctrl-C.
    ICM_VERBOSE = 0x00000004, ///< Enable verbose reporting.
    ICM_WALLCLOCK = 0x00000008, ///< Sleep if inactive.
    ICM_VERBOSE_DICT = 0x00000010, ///< Enable dictionary statistics.
    ICM_DISASSEMBLE_LABELS = 0x00000020, ///< Deprecated (now always on).
    ICM_PRINT_USER_ATTRIBUTES = 0x00000040, ///< Print user attributes, set or not.
    ICM_TRACE_SHARED_DATA = 0x00000080, ///< Trace activity of vmirtWriteListeners.
    ICM_MPD_EGUI = 0x00000100, ///< Pop up MPD in EGUI.
    ICM_PRINT_COMMANDS = 0x00000200, ///< Print available plugin commands.
    ICM_SUPPRESS_BANNER = 0x00000400, ///< No banner at start-up - only available in CpuManager.
    ICM_NO_RSP_WAIT = 0x00001000, ///< Do not wait for RSP connection - only available in CpuManager.
    ICM_GDB_CONSOLE = 0x00002000, ///< Pop up gdb in console window.
    ICM_GDB_EGUI = 0x00004000, ///< Pop up gdb in EGUI.
    ICM_GDB_GUI = 0x00008000, ///< Pop up gdb in GUI.
    ICM_MPD_CONSOLE = 0x00010000, ///< Pop up MPD in console window.
    ICM_MPD_GUI = 0x00020000, ///< Pop up MPD in GUI.
    ICM_NO_OPTIMIZE = 0x00040000, ///< Turn off aggressive optimization.
    ICM_PRINT_BUSES = 0x00080000, ///< Print a summary of bus connections.
    ICM_DEBUG_CONSTRUCTORS = 0x00100000, ///< Stop for debug before PSE constructors have run.
    ICM_PARALLEL = 0x00200000, ///< Run simulator in limited parallel mode.
    ICM_PARALLEL_MAX = 0x00400000, ///< Run simulator in maximum parallel mode.
    ICM_MEM_STATS = 0x00800000, ///< Show memory statistics.
    ICM_RESERVED = 0x01000000  ///< Reserved for internal use.
} icmInitAttrs;

/// Attributes passed to object file loader.
typedef enum icmLoaderAttrsE {
    ICM_LOAD_DEFAULT = 0x00, ///< Default options.
    ICM_LOAD_PHYSICAL = 0x01, ///< Use physical rather than virtual addresses.
    ICM_LOAD_VERBOSE = 0x02, ///< Report each section loaded.
    ICM_ZERO_BSS = 0x04, ///< Zero the BSS segment.
    ICM_SET_START = 0x08, ///< Set processor start address to entry address.
    ICM_LOAD_SYMBOL_ONLY = 0x10, ///< Read the symbols but do not modify the memory.
    ICM_ELF_USE_VMA = 0x20  ///< Load ELF files using VMA addresses instead of LMA.
} icmLoaderAttrs;

/// Net port type.
typedef enum icmNetPortTypeE {
    ICM_NPT_INPUT , ///< Pin used for input.
    ICM_NPT_OUTPUT , ///< Pin used for output.
    ICM_NPT_INOUT   ///< Pin used for input and output.
} icmNetPortType;

/// Use these values in a bitmask to specify required processor attributes to
/// icmNewProcessor().
typedef enum icmNewProcAttrsE {
    ICM_ATTR_DEFAULT = 0x00000000, ///< Default behavior.
    ICM_ATTR_TRACE = 0x00000001, ///< Enable instruction trace.
    ICM_ATTR_TRACE_ICOUNT = 0x00000002, ///< Print count with trace.
    ICM_ATTR_TRACE_REGS_BEFORE = 0x00000004, ///< Dump registers before trace.
    ICM_ATTR_TRACE_BUFFER = 0x00000008, ///< Enable 256-entry trace buffer.
    ICM_ATTR_DEBUG = 0x00000010, ///< (deprecated).
    ICM_ATTR_SIMEX = 0x00000020, ///< Simulate exceptions.
    ICM_ATTR_RELAXED_SCHED = 0x00000040, ///< (deprecated).
    ICM_ATTR_APPROX_TIMER = 0x00000080, ///< (deprecated).
    ICM_ATTR_FETCH_VALIDATE = 0x00000100, ///< Fetch address validation.
    ICM_ATTR_TRACE_REGS_AFTER = 0x00000200, ///< Dump registers after trace.
    ICM_ATTR_LOAD_PHYSICAL = 0x00000400, ///< Use physical addresses.
    ICM_ATTR_NOTRACE_ANNUL = 0x00000800, ///< Don't trace annulled instructions.
    ICM_ATTR_TRACE_CHANGE = 0x00001000, ///< Dump changed registers.
    ICM_ATTR_RESERVED = 0x00002000, ///< Reserved for internal use.
    ICM_ATTR_DEBUG_BASIC = 0x00004000, ///< Do not use GDB with this processor.
    ICM_ATTR_DEFAULT_SEMIHOST = 0x00008000, ///< Install the default semihost library for this processor.
    ICM_ATTR_SYSTEMC = 0x80000000  ///< Reserved for internal use.
} icmNewProcAttrs;

/// Parameter type.
typedef enum icmParamTypeE {
    ICM_PT_BOOL , ///< Boolean parameter, can be 1,0,t,f,y,n, etc.
    ICM_PT_INT32 , ///< 32bit signed integer parameter.
    ICM_PT_UNS32 , ///< 32bit unsigned integer parameter.
    ICM_PT_UNS64 , ///< 64bit unsigned integer parameter.
    ICM_PT_DOUBLE , ///< Floating point parameter.
    ICM_PT_STRING , ///< String parameter.
    ICM_PT_ENUM , ///< Enumerated type parameter (one of a set of valid strings).
    ICM_PT_ENDIAN , ///< Special enumerated type parameter (big or little).
    ICM_PT_PTR   ///< Pointer parameter.
} icmParamType;

/// Memory access privilege.
typedef enum icmPrivE {
    ICM_PRIV_NONE = 0x0, ///< No access permitted.
    ICM_PRIV_R = 0x1, ///< Read permitted.
    ICM_PRIV_W = 0x2, ///< Write permitted.
    ICM_PRIV_RW = 0x3, ///< Read and write permitted.
    ICM_PRIV_X = 0x4, ///< Execute permitted.
    ICM_PRIV_RX = 0x5, ///< Read and execute permitted.
    ICM_PRIV_WX = 0x6, ///< Write and execute permitted.
    ICM_PRIV_RWX = 0x7, ///< Read, write and execute permitted.
    ICM_PRIV_ALIGN = 0x8  ///< Force accesses to be aligned.
} icmPriv;

/// Platform Purpose.
typedef enum icmPurposeE {
    ICM_BAREMETAL , ///< Processor and memory.
    ICM_FIX , ///< A fixed platform.
    ICM_EPK , ///< Extensible Platform Kit.
    ICM_OEM   ///< For use only by specific OEM. Not for general release.
} icmPurpose;

/// CPU Register classification.
typedef enum icmRegUsageE {
    ICM_REG_NONE = 0x0, ///< No special usage for this register (GP).
    ICM_REG_PC = 0x1, ///< Register is the program counter.
    ICM_REG_SP = 0x2, ///< Register is the stack pointer.
    ICM_REG_FP = 0x3  ///< Register is the frame pointer.
} icmRegUsage;

/// CPU Register read/write accessibility.
typedef enum icmRegAccessE {
    ICM_RA_NONE = 0x0, ///< Register not accessible.
    ICM_RA_R = 0x1, ///< Register is read-only.
    ICM_RA_W = 0x2, ///< Register is write-only.
    ICM_RA_RW = 0x3  ///< Register is read/write.
} icmRegAccess;

/// Model release status.
typedef enum icmReleaseStatusE {
    ICM_UNSET , ///< Not specified.
    ICM_INTERNAL , ///< For internal use only.
    ICM_RESTRICTED , ///< Restricted release.
    ICM_IMPERAS , ///< Imperas only.
    ICM_OVP   ///< Freely available.
} icmReleaseStatus;

/// Return status from save or restore.
typedef enum icmSaveRestoreStatusE {
    ICM_SAVE_OK , ///< Successful save or restore.
    ICM_SAVE_ERROR   ///< Error during save or restore.
} icmSaveRestoreStatus;

/// Stop reason codes on return from icmSimulate.
typedef enum icmStopReasonE {
    ICM_SR_SCHED = 0x00, ///< Scheduler expired.
    ICM_SR_YIELD = 0x01, ///< Yield encountered.
    ICM_SR_HALT = 0x02, ///< CPU is halted.
    ICM_SR_EXIT = 0x03, ///< CPU has exited.
    ICM_SR_FINISH = 0x04, ///< Simulation finish.
    ICM_SR_RD_PRIV = 0x05, ///< Read privilege exception.
    ICM_SR_WR_PRIV = 0x06, ///< Write privilege exception.
    ICM_SR_RD_ALIGN = 0x07, ///< Read align exception.
    ICM_SR_WR_ALIGN = 0x08, ///< Write align exception.
    ICM_SR_FE_PRIV = 0x09, ///< Fetch privilege exception.
    ICM_SR_ARITH = 0x0a, ///< Arithmetic exception.
    ICM_SR_INTERRUPT = 0x0b, ///< Interrupt simulation.
    ICM_SR_FREEZE = 0x0c, ///< Frozen (by icmFreeze).
    ICM_SR_WATCHPOINT = 0x0d, ///< Memory watchpoint is pending.
    ICM_SR_BP_ICOUNT = 0x0e, ///< Instruction count breakpoint is pending.
    ICM_SR_BP_ADDRESS = 0x0f, ///< Address breakpoint is pending.
    ICM_SR_RD_ABORT = 0x10, ///< Read abort exception.
    ICM_SR_WR_ABORT = 0x11, ///< Write abort exception.
    ICM_SR_FE_ABORT = 0x12, ///< Fetch abort exception.
    ICM_SR_INVALID = 0x13  ///< (invalid entry).
} icmStopReason;

/// Visibility of platform in debugger, introspection etc.
typedef enum icmVisibilityE {
    ICM_VISIBLE , ///< visible in all tools.
    ICM_INVISIBLE   ///< invisible in all tools.
} icmVisibility;

/// Watchpoint type.
typedef enum icmWatchpointTypeE {
    ICMWP_MEM_READ , ///< Memory read watchpoint.
    ICMWP_MEM_WRITE , ///< Memory write watchpoint.
    ICMWP_MEM_ACCESS , ///< Memory access watchpoint.
    ICMWP_REGISTER , ///< Register watchpoint.
    ICMWP_MODE , ///< Mode change watchpoint.
    ICMWP_EXCEPTION   ///< Exception watchpoint.
} icmWatchpointType;


////////////////////////////////////////////////////////////////////////////////
// Opaque Structure References.
////////////////////////////////////////////////////////////////////////////////

typedef struct icmProcessorS            *icmProcessorP          , **icmProcessorPP;
typedef struct icmAttrListS             *icmAttrListP           , **icmAttrListPP;
typedef struct icmBusS                  *icmBusP                , **icmBusPP;
typedef struct icmNetS                  *icmNetP                , **icmNetPP;
typedef struct icmNetPortS              *icmNetPortP            , **icmNetPortPP;
typedef struct icmConnS                 *icmConnP               , **icmConnPP;
typedef struct icmMemoryS               *icmMemoryP             , **icmMemoryPP;
typedef struct icmPacketnetS            *icmPacketnetP          , **icmPacketnetPP;
typedef struct icmPacketnetPortS        *icmPacketnetPortP      , **icmPacketnetPortPP;
typedef struct icmPseS                  *icmPseP                , **icmPsePP;
typedef struct icmRegGroupS             *icmRegGroupP           , **icmRegGroupPP;
typedef struct icmRegInfoS              *icmRegInfoP            , **icmRegInfoPP;
typedef struct icmMMRegInfoS            *icmMMRegInfoP          , **icmMMRegInfoPP;
typedef struct icmMmcS                  *icmMmcP                , **icmMmcPP;
typedef struct icmImagefileS            *icmImagefileP          , **icmImagefilePP;
typedef struct icmBusBridgeS            *icmBusBridgeP          , **icmBusBridgePP;
typedef struct icmWatchPointS           *icmWatchPointP         , **icmWatchPointPP;
typedef struct icmInterceptS            *icmInterceptP          , **icmInterceptPP;
typedef struct icmTriggerEventS         *icmTriggerEventP       , **icmTriggerEventPP;
typedef struct icmExceptionInfoS        *icmExceptionInfoP      , **icmExceptionInfoPP;
typedef struct icmNetPortInfoS          *icmNetPortInfoP        , **icmNetPortInfoPP;
typedef struct icmFifoPortInfoS         *icmFifoPortInfoP       , **icmFifoPortInfoPP;
typedef struct icmDocNodeS              *icmDocNodeP            , **icmDocNodePP;
typedef struct icmCLPS                  *icmCLPP                , **icmCLPPP;
typedef struct icmParamInfoS            *icmParamInfoP          , **icmParamInfoPP;
typedef struct icmParamEnumS            *icmParamEnumP          , **icmParamEnumPP;
typedef struct icmBusPortInfoS          *icmBusPortInfoP        , **icmBusPortInfoPP;
typedef struct icmModeInfoS             *icmModeInfoP           , **icmModeInfoPP;


////////////////////////////////////////////////////////////////////////////////
// Public structure forward references.
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Callbacks.
////////////////////////////////////////////////////////////////////////////////

// Prototype of function called when a flag is parsed

#define CLPA_BOOL_FN(_name) \
void _name ( \
    Uns32 userData)

typedef CLPA_BOOL_FN((*icmArgBoolFn));

// Type of function called when an int argument is parsed

#define CLPA_INT32_FN(_name) \
void _name ( \
    Int32 value, \
    Uns32 userData)

typedef CLPA_INT32_FN((*icmArgInt32Fn));

// Type of function called when a 64-bit int argument is parsed

#define CLPA_INT64_FN(_name) \
void _name ( \
    Uns64 value, \
    Uns32 userData)

typedef CLPA_INT64_FN((*icmArgInt64Fn));

// Type of function called when a double argument is parsed

#define CLPA_DOUBLE_FN(_name) \
void _name ( \
    double value, \
    Uns32  userData)

typedef CLPA_DOUBLE_FN((*icmArgDoubleFn));

// Type of function called when a string argument is parsed

#define CLPA_STRING_FN(_name) \
void _name ( \
    const char * value, \
    Uns32        userData)

typedef CLPA_STRING_FN((*icmArgStringFn));

// Type of function called when a name=value argument is parsed

#define CLPA_PAIR_FN(_name) \
void _name ( \
    const char * name, \
    const char * value, \
    Uns32        userData)

typedef CLPA_PAIR_FN((*icmArgStringPairFn));

// Type of function called when a repeated string is parsed

#define CLPA_ARGV_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argv, \
    Uns32         userData)

typedef CLPA_ARGV_FN((*icmArgVFn));

// Type of function called when a repeated name=value is parsed

#define CLPA_ARGV_PAIR_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argn, \
    const char ** argv, \
    Uns32         userData)

typedef CLPA_ARGV_PAIR_FN((*icmArgVPairFn));

// Memory read callback function

#define ICM_MEM_READ_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    Addr          address, \
    Uns32         bytes, \
    void*         value, \
    void*         userData, \
    Addr          VA, \
    Bool          isFetch)

typedef ICM_MEM_READ_FN((*icmMemReadFn));

// Memory write callback function

#define ICM_MEM_WRITE_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    Addr          address, \
    Uns32         bytes, \
    const void*   value, \
    void*         userData, \
    Addr          VA)

typedef ICM_MEM_WRITE_FN((*icmMemWriteFn));

// Memory read/write notification callback

#define ICM_MEM_WATCH_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    Addr          address, \
    Uns32         bytes, \
    const void*   value, \
    void*         userData, \
    Addr          VA)

typedef ICM_MEM_WATCH_FN((*icmMemWatchFn));

// Callback used by icmIterAllUserAttributes

#define USER_ATTR_FN(_name) \
void _name ( \
    const char * owner, \
    const char * name, \
    const char * value, \
    Bool         set, \
    Bool         used, \
    Bool         numeric, \
    void*        userData)

typedef USER_ATTR_FN((*icmAttrFn));

// Callback used for model parameters

#define ICM_PARAM_FN(_name) \
void _name ( \
    const char * owner, \
    const char * name, \
    void*        userData)

typedef ICM_PARAM_FN((*icmParamFn));

// Prototype of on-exit function

#define ICM_EXIT_FN(_name) \
void _name ( void)

typedef ICM_EXIT_FN((*icmExitFn));

// Callback for text output (icmMessage etc)

#define ICM_TEXT_OUTPUT_FN(_name) \
Uns32 _name ( \
    const char * text, \
    void*        userData)

typedef ICM_TEXT_OUTPUT_FN((*icmTextOutputFn));

// Callback  of callback for quitting the simulator

#define ICM_QUIT_FN(_name) \
void _name ( \
    Int32 status, \
    void* userData)

typedef ICM_QUIT_FN((*icmQuitFn));

// Iterator callback function for SMPs

#define ICM_SMP_ITERATOR_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    void*         userData)

typedef ICM_SMP_ITERATOR_FN((*icmSMPIteratorFn));

// Prototype of callback for each installed command

#define ICM_INSTALLED_COMMAND_FN(_name) \
void _name ( \
    const char * platform, \
    const char * model, \
    const char * plugin, \
    const char * command, \
    const char * shortHelp, \
    void*        user)

typedef ICM_INSTALLED_COMMAND_FN((*icmInstalledCommandFn));

// Prototype of callback for vlnv files

#define ICM_VLNV_FOUND_CB(_name) \
void _name ( \
    const char * file, \
    void*        userData)

typedef ICM_VLNV_FOUND_CB((*icmFoundFileFn));

// Prototype of callback used by icmAddNetCallback

#define NET_WRITE_FN(_name) \
void _name ( \
    void* userData, \
    Uns32 value)

typedef NET_WRITE_FN((*icmNetFn));

// Prototype of callback used by icmTriggerAfter

#define TRIGGER_AFTER_FN(_name) \
void _name ( \
    icmTime currentTime, \
    void*   userData)

typedef TRIGGER_AFTER_FN((*icmTriggerFn));

// Prototype of callback when a PSE maps a dynamic port.

#define ICM_PSE_PORT_MAP_FN(_name) \
void _name ( \
    void* userData, \
    Addr  loAddress, \
    Addr  hiAddress, \
    Bool  add)

typedef ICM_PSE_PORT_MAP_FN((*icmPsePortMapFn));

// Callback to save simulation data.

#define ICM_SAVE_FN(_name) \
Bool _name ( \
    const void * buffer, \
    Uns32        bytes, \
    void*        userData)

typedef ICM_SAVE_FN((*icmSaveFn));

// Callback to restore simulation data.

#define ICM_RESTORE_FN(_name) \
Bool _name ( \
    void * buffer, \
    Uns32  bytes, \
    void*  userData)

typedef ICM_RESTORE_FN((*icmRestoreFn));

// Callback when simulation is about to start.

#define ICM_START_SIM_FN(_name) \
void _name ( \
    void* userData)

typedef ICM_START_SIM_FN((*icmStartSimFn));

// Callback when peripheral constructors have finished, when application processors are about to start.

#define ICM_END_CONSTRUCTORS_FN(_name) \
void _name ( \
    void* userData)

typedef ICM_END_CONSTRUCTORS_FN((*icmEndConstructorsFn));

// Callback when platform constructor has finished, before simulation.

#define ICM_END_PLT_CONSTRUCTOR_FN(_name) \
void _name ( \
    void* userData)

typedef ICM_END_PLT_CONSTRUCTOR_FN((*icmEndPltConstructorFn));

// Callback when each processor slice (quantum) has finished. Should return true if simulation is to continue, false if not.

#define ICM_END_SCHED_FN(_name) \
Bool _name ( \
    icmProcessorP processor, \
    void*         userData)

typedef ICM_END_SCHED_FN((*icmEndSchedFn));

// Callback when time advances. Should return true if simulation is to continue, false if not.

#define ICM_TIME_ADVANCE_FN(_name) \
Bool _name ( \
    icmAdvanceTimeInfo info, \
    void*              userData)

typedef ICM_TIME_ADVANCE_FN((*icmTimeAdvanceFn));

// Callback when simulation is finishing.

#define ICM_FINISH_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    void*         userData)

typedef ICM_FINISH_FN((*icmFinishFn));

// Callback when simulation is finishing.

#define ICM_MEM_NOTIFIER_FN(_name) \
Bool _name ( \
    icmProcessorP  processor, \
    icmWatchPointP watchpoint, \
    Addr           PA, \
    Addr           VA, \
    Uns32          bytes, \
    void*          userData, \
    void*          value)

typedef ICM_MEM_NOTIFIER_FN((*icmMemNotifierFn));

// Register watchpoint notification callback.

#define ICM_REG_NOTIFIER_FN(_name) \
Bool _name ( \
    icmWatchPointP watchpoint, \
    icmProcessorP  processor, \
    void*          value)

typedef ICM_REG_NOTIFIER_FN((*icmRegNotifierFn));

// Notification when a packetnet is written.

#define ICM_PACKETNET_NOTIFIER_FN(_name) \
void _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

typedef ICM_PACKETNET_NOTIFIER_FN((*icmPacketnetNotifierFn));

// Called for each loaded region

#define ICM_OBJECT_LIST_REGION_FN(_name) \
void _name ( \
    const char * name, \
    Addr         address, \
    Addr         bytes, \
    Bool         executable, \
    void*        userData)

typedef ICM_OBJECT_LIST_REGION_FN((*icmObjectListRegionFn));



////////////////////////////////////////////////////////////////////////////////
// Public structures.
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Public structures and unions.
////////////////////////////////////////////////////////////////////////////////

// VLNV specification.

typedef struct icmVlnvS {
    const char *           vendor;
    const char *           library;
    const char *           name;
    const char *           version;
} icmVlnv,  *icmVlnvP, **icmVlnvPP;

// Linked list of command line arguments.

typedef struct icmRepeatedArgS {
    struct icmRepeatedArgS *   next;
    const char *           string;
    const char *           name;
} icmRepeatedArg,  *icmRepeatedArgP, **icmRepeatedArgPP;

// Debugger notification callbacks. Each can be NULL if not required.

typedef struct icmDebugNotifierS {
    icmStartSimFn          start;
    icmEndPltConstructorFn   endPSECons;
    icmEndPltConstructorFn   endPltCons;
    icmEndConstructorsFn   endCons;
    icmEndSchedFn          sched;
    icmEndSchedFn          schedPSE;
    icmTimeAdvanceFn       advance;
    icmFinishFn            finish;
    void*                  userData;
} icmDebugNotifier,  *icmDebugNotifierP, **icmDebugNotifierPP;

// Deprecated - use ICM_ATTR_TRACE_REGS_BEFORE or ICM_ATTR_TRACE_REGS_AFTER.


#define ICM_ATTR_TRACE_REGS        ICM_ATTR_TRACE_REGS_AFTER
        
// Initialize ICM package - call this before any other icm functions.


#define icmInit(simAttrs,protocol,dbgPort) \
     icmInitInternal(ICM_VERSION,simAttrs,protocol,dbgPort)
        
// Legacy names.


#define icmGetNextParamInfo    icmGetNextProcessorParamInfo
#define icmGetNextBusPortInfo  icmGetNextProcessorBusPortInfo
#define icmGetNextNetPortInfo  icmGetNextProcessorNetPortInfo
#define icmGetNextFifoPortInfo icmGetNextProcessorFifoPortInfo
        

#endif /* ICMTYPES_H */

