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

#ifndef OPTTYPES_H
#define OPTTYPES_H

#include "hostapi/impTypes.h"
#include "ord/ordObjAttrs.h"
#include "vmi/vmiTypes.h"
#include <stdarg.h>


////////////////////////////////////////////////////////////////////////////////
// Types.
////////////////////////////////////////////////////////////////////////////////

/// Simulator time (in seconds).
typedef long double  optTime;


////////////////////////////////////////////////////////////////////////////////
// Enums.
////////////////////////////////////////////////////////////////////////////////

/// Types of bus port.
typedef enum optBusPortTypeE {
    OPT_UNKNOWN_TYPE , ///< Connection type unknown or not yet set.
    OPT_MASTER , ///< Bus Master (e.g. processor instruction port).
    OPT_SLAVE , ///< Bus Slave (e.g. memory port).
    OPT_MASTERSLAVE   ///< Bus Master and Slave.
} optBusPortType;

/// Types of bus port domain.
typedef enum optDomainTypeE {
    OPT_DATA_DOMAIN , ///< Bus port is connected to a model's data domain.
    OPT_CODE_DOMAIN , ///< Bus port is connected to a model's code domain.
    OPT_OTHER_DOMAIN   ///< Bus port is connected to another type of domain.
} optDomainType;

/// Imagefile endian-ness.
typedef enum optEndianE {
    OPT_ENDIAN_NONE = 0x0, ///< No endian specified.
    OPT_ENDIAN_LITTLE = 0x1, ///< Definitely little.
    OPT_ENDIAN_BIG = 0x2, ///< Definitely big.
    OPT_ENDIAN_EITHER = 0x3  ///< Could be either (not used in this release).
} optEndian;

/// Types of flag accepted by command line parser. See Flag*Fn prototype
/// definitions.
typedef enum optFlagTypeE {
    OPT_FT_NONE , ///< Do not use.
    OPT_FT_BOOLVAL , ///< Argument sets variable of type Boolean.
    OPT_FT_INT32VAL , ///< Argument sets variable of type Int32.
    OPT_FT_UNS32VAL , ///< Argument sets variable of type Uns32.
    OPT_FT_UNS64VAL , ///< Argument sets variable of type Uns64.
    OPT_FT_DOUBLEVAL , ///< Argument sets variable of type Double.
    OPT_FT_STRINGVAL , ///< Argument sets variable of type String.
    OPT_FT_STRINGLIST , ///< One list element for each use of the argument.
    OPT_FT_STRINGSLAST , ///< Flag must be last. One list element for each use of the
           ///  argument.
    OPT_FT_PAIRLIST , ///< One name=value pair for each use of the argument.
    OPT_FT_GLOBSTRING , ///< One list element for each use of the argument. Strings are
           ///  file-glob expanded.
    OPT_FT_FC_BOOLEAN , ///< Function called each time flag is specified.
    OPT_FT_FC_INT32 , ///< Function called each time Int32 argument is specified.
    OPT_FT_FC_UNS32 , ///< Function called each time Uns32 argument is specified.
    OPT_FT_FC_UNS64 , ///< Function called each time Uns64 argument is specified.
    OPT_FT_FC_DOUBLE , ///< Function called each time double argument is specified.
    OPT_FT_FC_STRING , ///< Function called each time string argument is specified.
    OPT_FT_FC_PAIR , ///< Function called each time name=value argument is specified.
    OPT_FT_FC_ARGV , ///< Function called with each list of arguments.
    OPT_FT_FC_ARGVLAST , ///< Flag must be last. Function called with each list of arguments.
    OPT_FT_FC_ARGVPAIR   ///< Function called with each list of name=value pairs.
} optFlagType;

/// Command line parser argument class. Use to select what standard arguments to
/// a parser.
typedef enum optArgClassE {
    OPT_AC_NONE = 0x00, ///< No standard arguments.
    OPT_AC_BASIC = 0x01, ///< Basic arguments.
    OPT_AC_EXT1 = 0x02, ///< Basic demo arguments.
    OPT_AC_EXT2 = 0x04, ///< Extended demo arguments.
    OPT_AC_SIM = 0x08, ///< Simulator arguments.
    OPT_AC_LIB = 0x10, ///< Library management arguments.
    OPT_AC_ENG = 0x20, ///< (do not use).
    OPT_AC_ALL = 0x18  ///< Library and Simulator.
} optArgClass;

/// Types of FIFO port.
typedef enum optFIFOPortTypeE {
    OPT_FIFO_OUTPUT , ///< Output which drives FIFO.
    OPT_FIFO_INPUT   ///< Input which received from a FIFO.
} optFIFOPortType;

/// Control the application loader features.
typedef enum optLoaderControlsE {
    OPT_LDR_DEFAULT = 0x00, ///< No special features.
    OPT_LDR_PHYSICAL = 0x01, ///< Loader will use physical as opposed to logical addresses.
    OPT_LDR_VERBOSE = 0x02, ///< Loader will report sections as they are loaded.
    OPT_LDR_ZERO_BSS = 0x04, ///< Loader will zero the BSS section.
    OPT_LDR_SET_START = 0x08, ///< Loader will set the PC of the target processor (where known) to
           ///  the start address.
    OPT_LDR_SYMBOLS_ONLY = 0x10, ///< Loader will read the symbols but not load the program.
    OPT_LDR_ELF_USE_VMA = 0x20, ///< Loader will load ELF files using VMA addresses rather than LMA.
    OPT_LDR_FAIL_IS_ERROR = 0x40  ///< Failure to load should prevent simulation from running.
} optLoaderControls;

/// Types of model.
typedef enum optModelTypeE {
    OPT_NOT_VALID , ///< Do not use.
    OPT_EXTENSION , ///< Extension (shared object using Extension VMI API).
    OPT_MMC , ///< MMC (shared object using MMC VMI API).
    OPT_MODULE , ///< Module (shared object using OP API).
    OPT_PERIPHERAL , ///< Peripheral (PSE executable using BHM/PPM API).
    OPT_PLATFORM , ///< Platform (shared object using ICM or OP API).
    OPT_PROCESSOR , ///< Processor (shared object using Processor VMI API).
    OPT_XML_PLATFORM   ///< XML Platform (legacy mode).
} optModelType;

/// Types of net port.
typedef enum optNetPortTypeE {
    OPT_NODIR , ///< Direction is not set.
    OPT_INPUT , ///< Input which received from a wire or FIFO.
    OPT_OUTPUT , ///< Output which drives a wire or FIFO.
    OPT_INOUT   ///< Net input and output (bidirectional).
} optNetPortType;

/// Parameter and Formal types.
typedef enum optParamTypeE {
    OPT_PARAM_NONE , ///< dummy type for list head.
    OPT_PARAM_BOOL , ///< boolean.
    OPT_PARAM_INT32 , ///< 32bit signed integer.
    OPT_PARAM_UNS32 , ///< 32bit unsigned integer.
    OPT_PARAM_UNS64 , ///< 64bit unsigned integer.
    OPT_PARAM_DOUBLE , ///< double precision floating point.
    OPT_PARAM_ENDIAN , ///< special enumerated type: big, little or either.
    OPT_PARAM_ENUM , ///< enumerated type.
    OPT_PARAM_PTR , ///< anonymous pointer.
    OPT_PARAM_STRING   ///< text string.
} optParamType;

/// Parameter and Formal classes.
typedef enum optParamClassE {
    OPT_PARAM_SYSTEM = 1, ///< System parameters.
    OPT_PARAM_MODEL = 2, ///< Model-specific parameters.
    OPT_PARAM_ALL = 3  ///< Model-specific parameters.
} optParamClass;

/// Memory access privilege.
typedef enum optPrivE {
    OPT_PRIV_NONE = 0x0, ///< No access permitted.
    OPT_PRIV_R = 0x1, ///< Read permitted.
    OPT_PRIV_W = 0x2, ///< Write permitted.
    OPT_PRIV_RW = 0x3, ///< Read and write permitted.
    OPT_PRIV_X = 0x4, ///< Execute permitted.
    OPT_PRIV_RX = 0x5, ///< Read and execute permitted.
    OPT_PRIV_WX = 0x6, ///< Write and execute permitted.
    OPT_PRIV_RWX = 0x7, ///< Read, write and execute permitted.
    OPT_PRIV_ALIGN = 0x8  ///< Force accesses to be aligned.
} optPriv;

/// Platform Purpose.
typedef enum optPurposeE {
    OPT_BAREMETAL , ///< A processor with memory.
    OPT_FIX , ///< A fixed platform.
    OPT_EPK , ///< Extensible Platform Kit.
    OPT_OEM   ///< For use only by specific OEM. Not for general release.
} optPurpose;

/// CPU Register classification.
typedef enum optRegUsageE {
    OPT_REG_NONE = 0x0, ///< No special usage for this register (GP).
    OPT_REG_PC = 0x1, ///< Register is the program counter.
    OPT_REG_SP = 0x2, ///< Register is the stack pointer.
    OPT_REG_FP = 0x3  ///< Register is the frame pointer.
} optRegUsage;

/// CPU Register access modes.
typedef enum optRegAccessE {
    OPT_RA_NONE = 0x0, ///< No access.
    OPT_RA_R = 0x1, ///< Register is read-only.
    OPT_RA_W = 0x2, ///< Register is write-only.
    OPT_RA_RW = 0x3  ///< Register is read-write.
} optRegAccess;

/// Model release status.
typedef enum optReleaseStatusE {
    OPT_UNSET , ///< Not specified.
    OPT_INTERNAL , ///< For internal use only.
    OPT_RESTRICTED , ///< Restricted release.
    OPT_IMPERAS , ///< Imperas only.
    OPT_OVP   ///< Freely available.
} optReleaseStatus;

/// Simulator and API module phase descriptions.
typedef enum optSimulatorPhaseE {
    OPT_PH_UNKNOWN = 0x00, ///< Unknown phase (invalid module hierarchy).
    OPT_PH_CONSTRUCT = 0x01, ///< Construct a module.
    OPT_PH_PRE_SIMULATE = 0x02, ///< Prepare to simulate. Processor VM constructors are called. All
           ///  simulation objects have been created by now.
    OPT_PH_SIMULATE = 0x04, ///< Simulation in progress. Time is progressing.
    OPT_PH_POST_SIMULATE = 0x08, ///< Post simulation.
    OPT_PH_REPORT = 0x10, ///< Print standard reports.
    OPT_PH_DESTRUCT = 0x20, ///< Destruction of all objects.
    OPT_PHS_QUERY = 0x1F  ///< (Not a phase) Represents all phases except destruction.
} optSimulatorPhase;

/// Stop reason codes returned by oprSimulate functions.
typedef enum optStopReasonE {
    OPT_SR_SCHED = 0x00, ///< Scheduler expired.
    OPT_SR_YIELD = 0x01, ///< Yield encountered.
    OPT_SR_HALT = 0x02, ///< CPU is halted.
    OPT_SR_EXIT = 0x03, ///< CPU has exited.
    OPT_SR_FINISH = 0x04, ///< Simulation finish.
    OPT_SR_RD_PRIV = 0x05, ///< Read privilege exception.
    OPT_SR_WR_PRIV = 0x06, ///< Write privilege exception.
    OPT_SR_RD_ALIGN = 0x07, ///< Read align exception.
    OPT_SR_WR_ALIGN = 0x08, ///< Write align exception.
    OPT_SR_FE_PRIV = 0x09, ///< Fetch privilege exception.
    OPT_SR_ARITH = 0x0a, ///< Arithmetic exception.
    OPT_SR_INTERRUPT = 0x0b, ///< Interrupt simulation.
    OPT_SR_FREEZE = 0x0c, ///< Frozen (by optFreeze).
    OPT_SR_WATCHPOINT = 0x0d, ///< Memory watchpoint is pending.
    OPT_SR_BP_ICOUNT = 0x0e, ///< Instruction count breakpoint is pending.
    OPT_SR_BP_ADDRESS = 0x0f, ///< Address breakpoint is pending.
    OPT_SR_RD_ABORT = 0x10, ///< Read abort exception.
    OPT_SR_WR_ABORT = 0x11, ///< Write abort exception.
    OPT_SR_FE_ABORT = 0x12, ///< Fetch abort exception.
    OPT_SR_INVALID = 0x13  ///< (invalid entry).
} optStopReason;

/// Supplementary information (for time advance callback).
typedef enum optAdvanceTimeInfoE {
    OPT_TA_NONE = 0x00, ///< No supplementary information.
    OPT_TA_SIM = 0x01, ///< Simulator stop time reached.
    OPT_TA_DBG = 0x02, ///< Debug stop time reached.
    OPT_TA_END = 0x04  ///< End of simulation.
} optAdvanceTimeInfo;

/// Types of memory storage.
typedef enum optStorageTypeE {
    OPT_RAM , ///< Read/Write memory.
    OPT_ROM , ///< Read-only memory.
    OPT_TRAP   ///< Unwritable region (for internal use).
} optStorageType;

/// Instruction trace features.
typedef enum optTraceFeaturesE {
    OPT_TRACE_INSTRUCTIONS = 0x01, ///< Basic instruction tracing.
    OPT_TRACE_ICOUNT = 0x02, ///< Include the instruction count in each trace.
    OPT_TRACE_REGS_BEFORE = 0x04, ///< Print the processor registers before each trace.
    OPT_TRACE_REGS_AFTER = 0x08, ///< Print the processor registers after each trace.
    OPT_TRACE_REG_CHANGES = 0x10, ///< Print the changed registers after each trace.
    OPT_TRACE_BUFFER = 0x20, ///< Keep a record of the last 256 instructions (see
           ///  TraceBufferDump).
    OPT_TRACE_NO_ANNUL = 0x40  ///< Do not trace delay slot instructions that were annulled.
} optTraceFeatures;

/// Visibility of platform in debugger, introspection etc.
typedef enum optVisibilityE {
    OPT_VISIBLE , ///< visible in all tools.
    OPT_INVISIBLE   ///< invisible in all tools.
} optVisibility;

/// Types of watchpoint.
typedef enum optWatchpointTypeE {
    OPT_WP_MEM_READ , ///< Memory read watchpoint.
    OPT_WP_MEM_WRITE , ///< Memory write watchpoint.
    OPT_WP_MEM_ACCESS , ///< Memory access watchpoint.
    OPT_WP_REGISTER , ///< Register watchpoint.
    OPT_WP_MODE , ///< Mode change watchpoint.
    OPT_WP_EXCEPTION   ///< Exception watchpoint.
} optWatchpointType;

/// Types of watchpoint.
typedef enum optSaveRestoreStatusE {
    OPT_SAVE_OK , ///< Save or restore was successful.
    OPT_SAVE_ERROR   ///< Save or restore was not successful.
} optSaveRestoreStatus;


////////////////////////////////////////////////////////////////////////////////
// Structure References.
////////////////////////////////////////////////////////////////////////////////

typedef struct optApplicationS          *optApplicationP        , **optApplicationPP;
typedef struct optBridgeS               *optBridgeP             , **optBridgePP;
typedef struct optBusS                  *optBusP                , **optBusPP;
typedef struct optBusCallbackS          *optBusCallbackP        , **optBusCallbackPP;
typedef struct optBusPortS              *optBusPortP            , **optBusPortPP;
typedef struct optBusPortConnS          *optBusPortConnP        , **optBusPortConnPP;
typedef struct optCommandS              *optCommandP            , **optCommandPP;
typedef struct optExtensionS            *optExtensionP          , **optExtensionPP;
typedef struct optExtElabS              *optExtElabP            , **optExtElabPP;
typedef struct optFIFOS                 *optFIFOP               , **optFIFOPP;
typedef struct optFIFOPortS             *optFIFOPortP           , **optFIFOPortPP;
typedef struct optFIFOPortConnS         *optFIFOPortConnP       , **optFIFOPortConnPP;
typedef struct optFormalS               *optFormalP             , **optFormalPP;
typedef struct optFormalEnumS           *optFormalEnumP         , **optFormalEnumPP;
typedef struct optMemoryS               *optMemoryP             , **optMemoryPP;
typedef struct optMMCS                  *optMMCP                , **optMMCPP;
typedef struct optMMRegisterS           *optMMRegisterP         , **optMMRegisterPP;
typedef struct optModuleS               *optModuleP             , **optModulePP;
typedef struct optNetS                  *optNetP                , **optNetPP;
typedef struct optNetCallbackS          *optNetCallbackP        , **optNetCallbackPP;
typedef struct optNetPortS              *optNetPortP            , **optNetPortPP;
typedef struct optNetPortConnS          *optNetPortConnP        , **optNetPortConnPP;
typedef struct optPacketnetS            *optPacketnetP          , **optPacketnetPP;
typedef struct optPacketnetCallbackS    *optPacketnetCallbackP  , **optPacketnetCallbackPP;
typedef struct optPacketnetPortS        *optPacketnetPortP      , **optPacketnetPortPP;
typedef struct optPacketnetPortConnS    *optPacketnetPortConnP  , **optPacketnetPortConnPP;
typedef struct optParamS                *optParamP              , **optParamPP;
typedef struct optPeripheralS           *optPeripheralP         , **optPeripheralPP;
typedef struct optProcessorS            *optProcessorP          , **optProcessorPP;
typedef struct optProcRootS             *optProcRootP           , **optProcRootPP;


////////////////////////////////////////////////////////////////////////////////
// Transparent Union of object types.
////////////////////////////////////////////////////////////////////////////////

#ifndef TRANSPARENT_UNION
    #define TRANSPARENT_UNION __attribute__((transparent_union))
#endif
typedef union {
    optApplicationP      Application;
    optBridgeP           Bridge;
    optBusP              Bus;
    optBusCallbackP      BusCallback;
    optBusPortP          BusPort;
    optBusPortConnP      BusPortConn;
    optCommandP          Command;
    optExtensionP        Extension;
    optExtElabP          ExtElab;
    optFIFOP             FIFO;
    optFIFOPortP         FIFOPort;
    optFIFOPortConnP     FIFOPortConn;
    optFormalP           Formal;
    optFormalEnumP       FormalEnum;
    optMemoryP           Memory;
    optMMCP              MMC;
    optMMRegisterP       MMRegister;
    optModuleP           Module;
    optNetP              Net;
    optNetCallbackP      NetCallback;
    optNetPortP          NetPort;
    optNetPortConnP      NetPortConn;
    optPacketnetP        Packetnet;
    optPacketnetCallbackP PacketnetCallback;
    optPacketnetPortP    PacketnetPort;
    optPacketnetPortConnP PacketnetPortConn;
    optParamP            Param;
    optPeripheralP       Peripheral;
    optProcessorP        Processor;
    optProcRootP         ProcRoot;
} optObjectP TRANSPARENT_UNION;


////////////////////////////////////////////////////////////////////////////////
// Enumeration for each object type.
////////////////////////////////////////////////////////////////////////////////

typedef enum optStrTypeE {
    OPT_NIL_EN            = 0x0,
    OPT_APPLICATION_EN    = 0x1,
    OPT_BRIDGE_EN         = 0x2,
    OPT_BUS_EN            = 0x4,
    OPT_BUSCALLBACK_EN    = 0x8,
    OPT_BUSPORT_EN        = 0x10,
    OPT_BUSPORTCONN_EN    = 0x20,
    OPT_COMMAND_EN        = 0x40,
    OPT_EXTENSION_EN      = 0x80,
    OPT_EXTELAB_EN        = 0x100,
    OPT_FIFO_EN           = 0x200,
    OPT_FIFOPORT_EN       = 0x400,
    OPT_FIFOPORTCONN_EN   = 0x800,
    OPT_FORMAL_EN         = 0x1000,
    OPT_FORMALENUM_EN     = 0x2000,
    OPT_MEMORY_EN         = 0x4000,
    OPT_MMC_EN            = 0x8000,
    OPT_MMREGISTER_EN     = 0x10000,
    OPT_MODULE_EN         = 0x20000,
    OPT_NET_EN            = 0x40000,
    OPT_NETCALLBACK_EN    = 0x80000,
    OPT_NETPORT_EN        = 0x100000,
    OPT_NETPORTCONN_EN    = 0x200000,
    OPT_PACKETNET_EN      = 0x400000,
    OPT_PACKETNETCALLBACK_EN  = 0x800000,
    OPT_PACKETNETPORT_EN  = 0x1000000,
    OPT_PACKETNETPORTCONN_EN  = 0x2000000,
    OPT_PARAM_EN          = 0x4000000,
    OPT_PERIPHERAL_EN     = 0x8000000,
    OPT_PROCESSOR_EN      = 0x10000000,
    OPT_PROCROOT_EN       = 0x20000000,
} optStrType;


////////////////////////////////////////////////////////////////////////////////
// Opaque Structure References.
////////////////////////////////////////////////////////////////////////////////

typedef struct optCmdFlagsS             *optCmdFlagsP           , **optCmdFlagsPP;
typedef struct optCmdParserS            *optCmdParserP          , **optCmdParserPP;
typedef struct optDocNodeS              *optDocNodeP            , **optDocNodePP;
typedef struct optExceptionS            *optExceptionP          , **optExceptionPP;
typedef struct optFlatFIFOS             *optFlatFIFOP           , **optFlatFIFOPP;
typedef struct optFlatNetS              *optFlatNetP            , **optFlatNetPP;
typedef struct optFlatPacketnetS        *optFlatPacketnetP      , **optFlatPacketnetPP;
typedef struct optModeS                 *optModeP               , **optModePP;
typedef struct optModuleObjectS         *optModuleObjectP       , **optModuleObjectPP;
typedef struct optRegGroupS             *optRegGroupP           , **optRegGroupPP;
typedef struct optRegS                  *optRegP                , **optRegPP;
typedef struct optRootModuleDataS       *optRootModuleDataP     , **optRootModuleDataPP;
typedef struct optStringListS           *optStringListP         , **optStringListPP;
typedef struct optTriggerEventS         *optTriggerEventP       , **optTriggerEventPP;
typedef struct optVLNVS                 *optVLNVP               , **optVLNVPP;
typedef struct optWatchpointS           *optWatchpointP         , **optWatchpointPP;


////////////////////////////////////////////////////////////////////////////////
// Public structure forward references.
////////////////////////////////////////////////////////////////////////////////

typedef struct optBusPortInfoS  *optBusPortInfoP, **optBusPortInfoPP;
typedef struct optFIFOPortInfoS  *optFIFOPortInfoP, **optFIFOPortInfoPP;
typedef struct optNetPortInfoS  *optNetPortInfoP, **optNetPortInfoPP;
typedef struct optEnumParamSpecS  *optEnumParamSpecP, **optEnumParamSpecPP;
typedef struct optParamSpecS  *optParamSpecP, **optParamSpecPP;
typedef struct optPacketnetPortInfoS  *optPacketnetPortInfoP, **optPacketnetPortInfoPP;
typedef struct optConnectionsS  *optConnectionsP, **optConnectionsPP;
typedef struct optDebuggerNotifiersS  *optDebuggerNotifiersP, **optDebuggerNotifiersPP;
typedef struct optObjectInfoS  *optObjectInfoP, **optObjectInfoPP;
typedef struct optModuleAttrS  *optModuleAttrP, **optModuleAttrPP;


////////////////////////////////////////////////////////////////////////////////
// Callbacks.
////////////////////////////////////////////////////////////////////////////////

// This function is called before elaboration begins.             Use this call-back to create formal parameters for the module.             Parameters to the formals can change the module's structure.

#define OPT_INTERFACE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_INTERFACE_FN((*optInterfaceFn));

// This function is called during elaboration.              Use this call-back to create structure including model and sub-module instances, interconnect, external ports, permanent (static) bridges and callbacks This call-back will call the elaboration function of each sub-module, in definition order, depth first. This function is called before elaboration begins. Use this call-back to create formal parameters for the module. Parameters to the formals can change the module's structure.

#define OPT_CONSTRUCT_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_CONSTRUCT_FN((*optConstructFn));

// This function is called after the elaboration of this and all other              modules when all structure is guaranteed to exist. Use this call-back to interrogate other modules

#define OPT_POST_CONSTRUCT_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_POST_CONSTRUCT_FN((*optPostConstructFn));

// This function is called immediately before simulation is about to begin for the first time only.              Use this module top set up delayed callbacks

#define OPT_PRE_SIMULATE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_PRE_SIMULATE_FN((*optPreSimulateFn));

// This function is called each time the top-level simulation is started after pre-simulation or at restart after a stop-event.

#define OPT_SIMULATE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_SIMULATE_FN((*optSimulateFn));

// This function is called only once, when simulation has finished, before any destruction. Use this call-back to gather and report simulation statistics.

#define OPT_POST_SIMULATE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_POST_SIMULATE_FN((*optPostSimulateFn));

// This function is called during platform destruction. Use this call-back to free resources unknown to the simulator. It should not rely on existence of other modules.

#define OPT_DESTRUCT_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_DESTRUCT_FN((*optDestructFn));

// (Incomplete feature) This function is called when system save is invoked. Use this call-back to save module data unknown to the simulator

#define OPT_MODULE_SAVE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_MODULE_SAVE_FN((*optModuleSaveFn));

// (Incomplete feature) This function is called when system restore is invoked. Use this call-back to restore module data unknown to the simulator

#define OPT_MODULE_RESTORE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

typedef OPT_MODULE_RESTORE_FN((*optModuleRestoreFn));

// Callback used when a processor accesses

#define OPT_MEM_WATCH_FN(_name) \
void _name ( \
    optProcessorP processor, \
    Addr          addr, \
    Uns32         bytes, \
    const void*   data, \
    void*         userData, \
    Addr          VA)

typedef OPT_MEM_WATCH_FN((*optMemWatchFn));

// Callback for a command definition

#define OPT_COMMAND_FN(_name) \
void _name ( \
    optCommandP command, \
    void*       userData)

typedef OPT_COMMAND_FN((*optCommandFn));

// Command parser callback called for a boolean flag

#define OPT_FLAG_BOOL_FN(_name) \
void _name ( \
    Bool  value, \
    Uns32 userData)

typedef OPT_FLAG_BOOL_FN((*optFlagBoolFn));

// Command parser callback called for an double (floating point) flag

#define OPT_FLAG_DOUBLE_FN(_name) \
void _name ( \
    double value, \
    Uns32  userData)

typedef OPT_FLAG_DOUBLE_FN((*optFlagDoubleFn));

// Command parser callback called for an integer flag

#define OPT_FLAG_INT32_FN(_name) \
void _name ( \
    Int32 value, \
    Uns32 userData)

typedef OPT_FLAG_INT32_FN((*optFlagInt32Fn));

// Command parser callback called for a string flag

#define OPT_FLAG_STRING_FN(_name) \
void _name ( \
    const char * value, \
    Uns32        userData)

typedef OPT_FLAG_STRING_FN((*optFlagStringFn));

// Command parser callback called for a name=value flag

#define OPT_FLAG_PAIR_FN(_name) \
void _name ( \
    const char * name, \
    const char * value, \
    Uns32        userData)

typedef OPT_FLAG_PAIR_FN((*optFlagPairFn));

// Command parser callback called for argv flag

#define OPT_FLAG_ARGV_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argv, \
    Uns32         userData)

typedef OPT_FLAG_ARGV_FN((*optFlagArgvFn));

// Command parser callback called for name=value list flag

#define OPT_FLAG_ARGV_PAIR_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argn, \
    const char ** argv, \
    Uns32         userData)

typedef OPT_FLAG_ARGV_PAIR_FN((*optFlagArgvPairFn));

// Command parser callback called for an unsigned 64 integer flag (also used for an address)

#define OPT_FLAG_UNS64_FN(_name) \
void _name ( \
    Uns64 value, \
    Uns32 userData)

typedef OPT_FLAG_UNS64_FN((*optFlagUns64Fn));

// Called for each VLNV file found

#define OPT_FILE_FN(_name) \
void _name ( \
    const char * path, \
    void*        userData)

typedef OPT_FILE_FN((*optFileFn));

// Notifier function for register changes

#define OPT_REG_NOTIFY_FN(_name) \
Bool _name ( \
    optProcessorP processor, \
    void*         userData)

typedef OPT_REG_NOTIFY_FN((*optRegNotifyFn));

// Memory watchpoint notification callback

#define OPT_MEM_NOTIFY_FN(_name) \
Bool _name ( \
    optWatchpointP watchpoint, \
    optProcessorP  processor, \
    Addr           PA, \
    Addr           VA, \
    Uns32          bytes, \
    void*          userData, \
    void*          value)

typedef OPT_MEM_NOTIFY_FN((*optMemNotifyFn));

// Command parser error handler function

#define OPT_CMD_ERROR_HANDLER_FN(_name) \
void _name ( \
    const char * flag, \
    void*        userData)

typedef OPT_CMD_ERROR_HANDLER_FN((*optCmdErrorHandlerFn));

// Callback for each processor

#define OPT_PROCESSOR_ITERATOR_FN(_name) \
void _name ( \
    optProcessorP processor, \
    void*         userData)

typedef OPT_PROCESSOR_ITERATOR_FN((*optProcessorIteratorFn));

// Callback when opmExit is called

#define OPT_EXIT_FN(_name) \
void _name ( void)

typedef OPT_EXIT_FN((*optExitFn));

// Callback implementing memory read

#define OPT_MEM_READ_FN(_name) \
void _name ( \
    optProcessorP processor, \
    Addr          addr, \
    Uns32         bytes, \
    void*         data, \
    void*         userData, \
    Addr          VA, \
    Bool          isFetch)

typedef OPT_MEM_READ_FN((*optMemReadFn));

// Callback implementing memory write

#define OPT_MEM_WRITE_FN(_name) \
void _name ( \
    optProcessorP processor, \
    Addr          addr, \
    Uns32         bytes, \
    const void*   data, \
    void*         userData, \
    Addr          VA)

typedef OPT_MEM_WRITE_FN((*optMemWriteFn));

// Return each bus port definition

#define OPT_BUS_PORT_FN(_name) \
optBusPortInfoP _name ( \
    optModuleP      module, \
    optBusPortInfoP prev)

typedef OPT_BUS_PORT_FN((*optBusPortFn));

// Return each FIFO port definition

#define OPT_FIFOPORT_FN(_name) \
optFIFOPortInfoP _name ( \
    optModuleP       module, \
    optFIFOPortInfoP prev)

typedef OPT_FIFOPORT_FN((*optFIFOPortFn));

// Return the next net port definition

#define OPT_NET_PORT_FN(_name) \
optNetPortInfoP _name ( \
    optModuleP      module, \
    optNetPortInfoP prev)

typedef OPT_NET_PORT_FN((*optNetPortFn));

// Return the next packetnet port definition

#define OPT_PACKETNET_PORT_FN(_name) \
optPacketnetPortInfoP _name ( \
    optModuleP            module, \
    optPacketnetPortInfoP prev)

typedef OPT_PACKETNET_PORT_FN((*optPacketnetPortFn));

// Return each formal parameter specification

#define OPT_PARAM_SPEC_FN(_name) \
optParamSpecP _name ( \
    optModuleP    module, \
    optParamSpecP prev)

typedef OPT_PARAM_SPEC_FN((*optParamSpecFn));

// Callback for quitting the simulator

#define OPT_QUIT_FN(_name) \
void _name ( \
    Int32 status, \
    void* userData)

typedef OPT_QUIT_FN((*optQuitFn));

// Debugger callback at simulation start

#define OPT_SIMULATE_START_FN(_name) \
void _name ( \
    optModuleP module, \
    void*      userData)

typedef OPT_SIMULATE_START_FN((*optSimulateStartFn));

// Debugger callback after processor execution

#define OPT_SIMULATE_POST_PROCESSOR_FN(_name) \
Bool _name ( \
    optProcessorP processor, \
    void*         userData)

typedef OPT_SIMULATE_POST_PROCESSOR_FN((*optSimulatePostProcessorFn));

// Debugger callback after PSE execution

#define OPT_SIMULATE_POST_PERIPH_FN(_name) \
Bool _name ( \
    optPeripheralP peripheral, \
    void*          userData)

typedef OPT_SIMULATE_POST_PERIPH_FN((*optSimulatePostPeriphFn));

// Debugger callback at end of simulation

#define OPT_SIMULATE_END_FN(_name) \
void _name ( \
    optProcessorP processor, \
    void*         userData)

typedef OPT_SIMULATE_END_FN((*optSimulateEndFn));

// Debugger callback at end of each processor simulation slice

#define OPT_SIMULATE_TIME_ADVANCE_FN(_name) \
Bool _name ( \
    optAdvanceTimeInfo info, \
    void*              userData)

typedef OPT_SIMULATE_TIME_ADVANCE_FN((*optSimulateTimeAdvanceFn));

// Callback for text output (opMessage etc)

#define OPT_TEXT_OUTPUT_FN(_name) \
Uns32 _name ( \
    const char * text, \
    void*        userData)

typedef OPT_TEXT_OUTPUT_FN((*optTextOutputFn));

// Callback for timed trigger

#define OPT_TRIGGER_FN(_name) \
void _name ( \
    optTime    now, \
    optModuleP mi, \
    void*      userData)

typedef OPT_TRIGGER_FN((*optTriggerFn));

// Called when a net is written

#define OPT_NET_WRITE_FN(_name) \
void _name ( \
    void* userData, \
    Uns32 value)

typedef OPT_NET_WRITE_FN((*optNetWriteFn));

// Called when a packetnet is written.

#define OPT_PACKETNET_WRITE_FN(_name) \
void _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

typedef OPT_PACKETNET_WRITE_FN((*optPacketnetWriteFn));

// Called to save a model state

#define OPT_SAVE_FN(_name) \
Bool _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

typedef OPT_SAVE_FN((*optSaveFn));

// Called to restore a model state

#define OPT_RESTORE_FN(_name) \
Bool _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

typedef OPT_RESTORE_FN((*optRestoreFn));

// Called to notify when a dynamic port is mapped or unmapped

#define OPT_PORT_MAP_FN(_name) \
void _name ( \
    void* userData, \
    Addr  addrLo, \
    Addr  addrHi, \
    Bool  map)

typedef OPT_PORT_MAP_FN((*optPortMapFn));



////////////////////////////////////////////////////////////////////////////////
// Public structures.
////////////////////////////////////////////////////////////////////////////////

// Definition of a module bus port

typedef struct optBusPortInfoS {
    const char *             name; // Bus port name
    const char *             description; // Bus port description
    Bool                     mustConnect; // True if this port must be connected
} optBusPortInfo;

// Definition of a module FIFO port

typedef struct optFIFOPortInfoS {
    const char *             name; // FIFO port name
    const char *             description; // FIFO port description
    optBusPortType           type; // input or output
    Bool                     mustConnect; // True if this port must be connected
    Uns32                    width; // Number of bits in a FIFO word
} optFIFOPortInfo;

// Definition of a module net port

typedef struct optNetPortInfoS {
    const char *             name; // Net port name
    const char *             description; // Net port description
    optNetPortType           type; // input, output or inout
    Bool                     mustConnect; // True if this port must be connected
} optNetPortInfo;

// Definition of a module formal parameter enumerated value

typedef struct optEnumParamSpecS {
    const char *             name; // Net port name
    const char *             description; // Net port description
    Uns32                    value; // Value
} optEnumParamSpec;

// Definition of a module formal parameter

typedef struct optParamSpecS {
    const char *             name; // Formal parameter name
    const char *             description; // Formal parameter  description
    optParamType             type; // Formal parameter  type
    union {
        struct {
            Bool                     defaultValue; 
        } boolSpec;

        struct {
            double                   defaultValue; 
            double                   min; 
            double                   max; 
        } doubleSpec;

        struct {
            optEnumParamSpecP        legalValues; 
        } enumSpec;

        struct {
            Int32                    defaultValue; 
            Int32                    min; 
            Int32                    max; 
        } int32Spec;

        struct {
            Uns32                    defaultValue; 
            Uns32                    min; 
            Uns32                    max; 
        } uns32Spec;

        struct {
            Uns64                    defaultValue; 
            Uns64                    min; 
            Uns64                    max; 
        } uns64Spec;

        struct {
            const char *             defaultValue; 
            Uns32                    maxLength; 
        } stringSpec;

    } spec;

} optParamSpec;

// Definition of a module packetnet port

typedef struct optPacketnetPortInfoS {
    const char *             name; // Packetnet port name
    const char *             description; // Packetnet port description
    optNetPortType           type; // input, output or inout
    Bool                     mustConnect; // True if this port must be connected
    Uns32                    bytes; // Maximum number of bytes in a packet
} optPacketnetPortInfo;

// Module connections

typedef struct optConnectionsS {
    optBusPortConnP          busPortConns; // List of bus ports
    optNetPortConnP          netPortConns; // List of net ports
    optPacketnetPortConnP    packetnetPortConns; // List of packetnet ports
    optFIFOPortConnP         fifoPortConns; // List of FIFO ports
} optConnections;

// Callbacks to a debugger

typedef struct optDebuggerNotifiersS {
    optSimulateStartFn       start; // Callback at start of simulation
    optSimulateStartFn       endPeripheralCons; // Callback before PSE constructors have run
    optSimulateStartFn       endPlatformCons; // Callback after platform constructor has run
    optSimulateStartFn       endCons; // Callback after all constructors have run
    optSimulatePostProcessorFn postProcessor; // Callback after processor execution
    optSimulatePostPeriphFn  postPeripheral; // Callback after peripheral execution
    optSimulateTimeAdvanceFn advance; // Callback when time advances
    optSimulateEndFn         end; // Callback at end of simulation
    void*                    userData; // User data
} optDebuggerNotifiers;

// Object file information

typedef struct optObjectInfoS {
    Addr                     entry; // Program entry point
    Addr                     loadAddress; // Program load address
    Addr                     headerOffset; // Offset of program header
    Uns32                    headerEntry; // Program header entry
    Uns32                    headerNumber; // Number of program headers
    const char*              interpreter; // Path to required interpreter if required. String is not persistent
    Uns16                    cpuType; // Processor architecture ELF code, COFF code, etc.
    Uns16                    cpuSupp; // Processor supplementary type (not usd yet).
    optEndian                endian; // Enumerated type; processor endian.
} optObjectInfo;

// 'modelattrs' structure defined in each module

typedef struct optModuleAttrS {
    const char*              versionString; // Version string. Must be OP_VERSION
    optModelType             type; // MUST be set to OPT_MODULE
    const char*              name; // A default name
    Uns32                    objectSize; // Bytes to allocate for each instance
    optVisibility            visibility; // Model instance is invisible
    optReleaseStatus         releaseStatus; // Model release status (enum)
    optPurpose               purpose; // Model purpose
    optConstructFn           constructCB; // see definition above
    optPostConstructFn       postConstructCB; // see definition above
    optPreSimulateFn         preSimulateCB; // see definition above
    optSimulateFn            simulateCB; // see definition above
    optPostSimulateFn        postSimulateCB; // see definition above
    optDestructFn            destructCB; // see definition above
    optSaveFn                saveCB; // see definition above
    optRestoreFn             restoreCB; // see definition above
    optBusPortFn             busPortSpecsCB; // call for each bus port
    optFIFOPortFn            FIFOPortSpecsCB; // call for each FIFO port
    optNetPortFn             netPortSpecsCB; // call for each net port
    optPacketnetPortFn       packetnetPortSpecsCB; // call for each packetnet port
    optParamSpecFn           paramSpecsCB; // call for each parameter
} optModuleAttr;


#endif /* OPTTYPES_H */

