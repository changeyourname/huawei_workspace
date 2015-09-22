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
/*                      A T T R I B U T E   T Y P E S                         */
/*                                                                            */
/******************************************************************************/

#ifndef VMI_ATTRS_H
#define VMI_ATTRS_H

#include "vmi/simAddrTypes.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiCxt.h"
#include "vmi/vmiCacheAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiPorts.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"
#include "vmi/vmiVersion.h"


////////////////////////////////////////////////////////////////////////////////
// PROCESSOR CONSTRUCTOR & DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Processor constructor
//
#define VMI_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,           \
    Bool           simulateExceptions,  \
    vmiSMPContextP smpContext,          \
    void          *parameterValues      \
)
typedef VMI_CONSTRUCTOR_FN((*vmiConstructorFn));

//
// Processor virtual memory initialization
//
#define VMI_VMINIT_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,            \
    memDomainPP    codeDomains,          \
    memDomainPP    dataDomains           \
)
typedef VMI_VMINIT_FN((*vmiVMInitFn));

//
// Processor destructor
//
#define VMI_DESTRUCTOR_FN(_NAME) void _NAME(vmiProcessorP processor)
typedef VMI_DESTRUCTOR_FN((*vmiDestructorFn));


////////////////////////////////////////////////////////////////////////////////
// SAVE / RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type is used to implement processor save
//
#define VMI_SAVE_STATE_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    vmiSaveContextP     cxt,        \
    vmiSaveRestorePhase phase       \
)
typedef VMI_SAVE_STATE_FN((*vmiSaveStateFn));

//
// This callback function type is used to implement processor restore
//
#define VMI_RESTORE_STATE_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    vmiRestoreContextP  cxt,        \
    vmiSaveRestorePhase phase       \
)
typedef VMI_RESTORE_STATE_FN((*vmiRestoreStateFn));


////////////////////////////////////////////////////////////////////////////////
// SIMULATED PROCESSOR ACTION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type defines functions that are called just before
// a code block translation starts (startBlockCB) and just after a block
// translation completes (endBlockCB). The callbacks may be used to initialize
// and finalize data structures required by the translation function below.
//
#define VMI_START_END_BLOCK_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC,       \
    Uns8          inDelaySlot   \
)
typedef VMI_START_END_BLOCK_FN((*vmiStartEndBlockFn));

//
// This callback function type defines a function used to translate a single
// processor instruction.
//
#define VMI_MORPH_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC,       \
    Uns8          inDelaySlot,  \
    Bool          firstInBlock, \
    Bool          emitTrace     \
)
typedef VMI_MORPH_FN((*vmiMorphFn));

//
// This callback function type defines a function that is called instead of the
// vmiMorphFn above for instructions that have been opaquely intercepted. The
// purpose of the function is to allow processor state to be updated even if
// the instruction implementation is elsewhere.
//
#define VMI_POST_OPAQUE_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC,       \
    Uns8          inDelaySlot   \
)
typedef VMI_POST_OPAQUE_FN((*vmiPostOpaqueFn));

//
// This callback function type defines a routine that is called to snap
// instruction fetch addresses if required
//
#define VMI_FETCH_SNAP_FN(_NAME) Addr _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC        \
)
typedef VMI_FETCH_SNAP_FN((*vmiFetchSnapFn));

//
// Callback to handle misaligned read or write accesses when these should either
// cause the read/write address to be snapped or cause the read/written value to
// be rotated, or both. The return value should be constructed using the
// MEM_SNAP macro defined in vmiTypes.h. A return value of zero indicates no
// address snapping or rotation is required and that the read alignment
// exception handler should be called.
//
#define VMI_RD_WR_SNAP_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    Addr          address,      \
    Uns32         bytes         \
)
typedef VMI_RD_WR_SNAP_FN((*vmiRdWrSnapFn));

//
// Callback to handle memory read privilege exceptions
//
#define VMI_RD_PRIV_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    memDomainP          domain,     \
    Addr                address,    \
    Uns32               bytes,      \
    void               *value,      \
    memAccessAttrs      attrs,      \
    vmiLoadStoreAction *action      \
)
typedef VMI_RD_PRIV_EXCEPT_FN((*vmiRdPrivExceptFn));

//
// Callback to handle memory write privilege exceptions
//
#define VMI_WR_PRIV_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    memDomainP          domain,     \
    Addr                address,    \
    Uns32               bytes,      \
    const void         *value,      \
    memAccessAttrs      attrs,      \
    vmiLoadStoreAction *action      \
)
typedef VMI_WR_PRIV_EXCEPT_FN((*vmiWrPrivExceptFn));

//
// Callback to handle memory read alignment exceptions.
//
#define VMI_RD_ALIGN_EXCEPT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    void         *value         \
)
typedef VMI_RD_ALIGN_EXCEPT_FN((*vmiRdAlignExceptFn));

//
// Callback to handle memory write alignment exceptions.
//
#define VMI_WR_ALIGN_EXCEPT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    const void   *value         \
)
typedef VMI_WR_ALIGN_EXCEPT_FN((*vmiWrAlignExceptFn));

//
// Callback to handle memory read abort exceptions (generated by calls to
// icmAbortRead in memory read callbacks). isFetch is True if this is an
// instruction fetch and False otherwise.
//
#define VMI_RD_ABORT_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          address,      \
    Bool          isFetch       \
)
typedef VMI_RD_ABORT_EXCEPT_FN((*vmiRdAbortExceptFn));

//
// Callback to handle memory write abort exceptions (generated by calls to
// icmAbortWrite in memory read callbacks).
//
#define VMI_WR_ABORT_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          address       \
)
typedef VMI_WR_ABORT_EXCEPT_FN((*vmiWrAbortExceptFn));

//
// Callback to handle illegal device memory read exceptions.
//
#define VMI_RD_DEVICE_EXCEPT_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    void         *value         \
)
typedef VMI_RD_DEVICE_EXCEPT_FN((*vmiRdDeviceExceptFn));

//
// Callback to handle illegal device memory write exceptions.
//
#define VMI_WR_DEVICE_EXCEPT_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    const void   *value         \
)
typedef VMI_WR_DEVICE_EXCEPT_FN((*vmiWrDeviceExceptFn));

//
// Callback for integer exception handler
// Return value indicates how the exception was handled
//
#define VMI_ARITH_EXCEPT_FN(_NAME) vmiIntegerExceptionResult _NAME( \
    vmiProcessorP           processor,          \
    vmiIntegerExceptionType exceptionType,      \
    vmiExceptionContext     exceptionContext    \
)
typedef VMI_ARITH_EXCEPT_FN((*vmiArithExceptFn));

//
// Callback for fetch exception handler for an instruction fetch at the passed
// address. If no exception is pending, return VMI_FETCH_NONE. If an exception
// is pending and the machine state has been modified to handle it, return
// VMI_FETCH_EXCEPTION_COMPLETE.
//
// If it is required that the register dump associated with the instruction
// causing the exception should show the processor state *before* it is updated,
// return VMI_FETCH_EXCEPTION_PENDING (without updating processor state) if
// 'complete' is False. The register dump will then be emitted and the fetch
// exception handler called a second time with the 'complete' argument set to
// True indicating that the machine state should be updated
//
#define VMI_IFETCH_FN(_NAME) vmiFetchAction _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Bool          complete,     \
    Bool          annulled      \
)
typedef VMI_IFETCH_FN((*vmiIFetchFn));

//
// Return the current processor endianness for instruction (if isFetch is True)
// or data (if isFetch is False)
//
#define VMI_ENDIAN_FN(_NAME) memEndian _NAME( \
    vmiProcessorP processor,    \
    Bool          isFetch       \
)
typedef VMI_ENDIAN_FN((*vmiEndianFn));

//
// Return the next instruction address after the current address
//
#define VMI_NEXT_PC_FN(_NAME) Addr _NAME(vmiProcessorP processor, Addr thisPC)
typedef VMI_NEXT_PC_FN((*vmiNextPCFn));

//
// Return a string representing the disassembled instruction at the passed
// address
//
#define VMI_DISASSEMBLE_FN(_NAME) const char *_NAME( \
    vmiProcessorP  processor,   \
    Addr           thisPC,      \
    vmiDisassAttrs attrs        \
)
typedef VMI_DISASSEMBLE_FN((*vmiDisassFn));

//
// This callback is called on a processor context switch. 'state' describes the
// new state.
//
#define VMI_IASSWITCH_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,   \
    vmiIASRunState state        \
)
typedef VMI_IASSWITCH_FN((*vmiIASSwitchFn));

//
// This callback should create code to cause a processor to return from an
// opaque intercept
//
#define VMI_INT_RETURN_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC        \
)
typedef VMI_INT_RETURN_FN((*vmiintReturnFn));

//
// This callback should create code to assign the function result of an
// Imperas intercepted call to the result register of the processor, using the
// standard processor procedure call ABI. The function result type is described
// by the passed format argument, which can be any of the following:
//
//      '4':    4-byte result (e.g. Uns32 type)
//      '8':    8-byte result (e.g. Uns64 type)
//
#define VMI_INT_RESULT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    char          format        \
)
typedef VMI_INT_RESULT_FN((*vmiintResultFn));

//
// This callback should create code to push function parameters before making
// an Imperas intercepted call. The function parameters are presented using the
// standard processor procedure call ABI. The function parameters are described
// by the passed format string. This string can contain a sequence of any of the
// following:
//
//      '4':    push Uns32 function argument using vmimtArgReg(32, ...)
//      '8':    push Uns64 function argument using vmimtArgReg(64, ...)
//      'a':    push address function argument using vmimtArgRegSimAddress(...)
//      'd':    push Flt64 function argument using vmimtArgFlt64(...)
//
// For example, a format string of "84a" requires arguments to be pushed for a
// function that takes an 8-byte argument followed by a 4-byte argument followed
// by an address argument.
//
#define VMI_INT_PAR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    const char   *format        \
)
typedef VMI_INT_PAR_FN((*vmiintParFn));

//
// Invoke encapsulated simulator to simulate for 'count' instructions. Return
// the number of instructions actually executed.
//
#define VMI_ENCAP_SIM_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    Uns32         count         \
)
typedef VMI_ENCAP_SIM_FN((*vmiEncapSimFn));

//
// Get program counter for encapsulated simulator processor
//
#define VMI_ENCAP_GET_PC_FN(_NAME) Addr _NAME( \
    vmiProcessorP processor,    \
    Uns8         *slotD         \
)
typedef VMI_ENCAP_GET_PC_FN((*vmiEncapGetPCFn));

//
// Get instruction count for encapsulated simulator processor
//
#define VMI_ENCAP_ICOUNT_FN(_NAME) Uns64 _NAME(vmiProcessorP processor)
typedef VMI_ENCAP_ICOUNT_FN((*vmiEncapICountFn));

//
// Type of function called by simulator to get the size of the parameter value
// table
//
#define VMI_PROC_PARAM_TABLE_SIZE_FN(_NAME) Uns32 _NAME ( \
    vmiProcessorP processor,    \
    const char   *variant       \
)
typedef VMI_PROC_PARAM_TABLE_SIZE_FN((*vmiParamValueSizeFn));

//
// Type of function called by simulator to get info about the parameters of this
// model
//
#define VMI_PROC_PARAM_SPECS_FN(_NAME) vmiParameterP _NAME ( \
    vmiProcessorP processor,    \
    vmiParameterP prev          \
)
typedef VMI_PROC_PARAM_SPECS_FN((*vmiParamSpecsFn));

//
// This structure describes attributes for instruction-accurate modeling for a
// particular processor
//
typedef struct vmiIASAttrS {

    ////////////////////////////////////////////////////////////////////////
    // VERSION & TYPE
    ////////////////////////////////////////////////////////////////////////

    const char      *versionString;      // version string (THIS MUST BE FIRST)
    vmiModelType     modelType;          // model type (THIS MUST BE SECOND)

    ////////////////////////////////////////////////////////////////////////
    // MODEL STATUS
    ////////////////////////////////////////////////////////////////////////

    vmiVisibility    visibility;         // model instance invisibility (enum)
    vmiReleaseStatus releaseStatus;      // model release status (enum)

    ////////////////////////////////////////////////////////////////////////
    // SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////

    const char    **dictNames;          // null-terminated dictionary name list
    Uns32           cpuSize;            // full size of CPU object

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiSaveStateFn    saveCB;           // processor state save callback
    vmiRestoreStateFn restoreCB;        // processor state restore callback

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiConstructorFn constructorCB;     // constructor
    vmiVMInitFn      vmInitCB;          // virtual memory initialization
    vmiDestructorFn  destructorCB;      // destructor

    ////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiStartEndBlockFn startBlockCB;    // called before block translate
    vmiStartEndBlockFn endBlockCB;      // called after block translate
    vmiMorphFn         morphCB;         // morph callback
    vmiPostOpaqueFn    postOpaqueCB;    // called after opaque intercept
    vmiFetchSnapFn     fetchSnapCB;     // fetch address snap callback
    vmiRdWrSnapFn      rdSnapCB;        // read alignment snap function
    vmiRdWrSnapFn      wrSnapCB;        // write alignment snap function

    ////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiEndianFn    getEndianCB;         // get processor endianness
    vmiNextPCFn    nextPCCB;            // get next instruction address
    vmiDisassFn    disCB;               // disassemble instruction
    vmiIASSwitchFn switchCB;            // call on simulator context switch

    ////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiRdPrivExceptFn   rdPrivExceptCB;     // read privilege exception
    vmiWrPrivExceptFn   wrPrivExceptCB;     // write privilege exception
    vmiRdAlignExceptFn  rdAlignExceptCB;    // read alignment exception
    vmiWrAlignExceptFn  wrAlignExceptCB;    // write alignment exception
    vmiRdAbortExceptFn  rdAbortExceptCB;    // read abort exception
    vmiWrAbortExceptFn  wrAbortExceptCB;    // write abort exception
    vmiRdDeviceExceptFn rdDeviceExceptCB;   // read device exception
    vmiWrDeviceExceptFn wrDeviceExceptCB;   // write device exception
    vmiIFetchFn         ifetchExceptCB;     // execution privilege exception
    vmiArithExceptFn    arithExceptCB;      // arithmetic exception
    vmiICountFn         icountExceptCB;     // instruction count exception

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiRegGroupFn      regGroupCB;      // regGroup callback
    vmiRegInfoFn       regInfoCB;       // regInfo callback
    vmiExceptionInfoFn exceptionInfoCB; // exceptionInfo callback
    vmiModeInfoFn      modeInfoCB;      // modeInfo callback
    vmiGetExceptionFn  getExceptionCB;  // return current processor exception
    vmiGetModeFn       getModeCB;       // return current processor mode
    vmiRegReadFn       regReadCB;       // default regRead callback
    vmiRegWriteFn      regWriteCB;      // default regWrite callback
    vmiTraceFn         traceCB;         // model-specific instruction trace
    vmiDebugFn         debugCB;         // model-specific register dump
    vmiProcDescFn      procDescCB;      // processor description callback

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER SUPPORT ROUTINES iterator to find the parameters
    ////////////////////////////////////////////////////////////////////////

    vmiParamSpecsFn     paramSpecsCB;     // next parameter callback
    vmiParamValueSizeFn paramValueSizeCB; // size of parameter values table

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES iterators to find the bus and net ports
    ////////////////////////////////////////////////////////////////////////

    vmiBusPortSpecsFn   busPortSpecsCB;     // callback for next bus port
    vmiNetPortSpecsFn   netPortSpecsCB;     // callback for next net port
    vmiFifoPortSpecsFn  fifoPortSpecsCB;    // callback for next fifo port

    ////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiintReturnFn intReturnCB;         // morph return from opaque intercept
    vmiintResultFn intResultCB;         // set intercepted function result
    vmiintParFn    intParCB;            // push function arguments

    ////////////////////////////////////////////////////////////////////////
    // ENCAPSULATED EXTERNAL SIMULATOR SUPPORT
    ////////////////////////////////////////////////////////////////////////

    vmiEncapSimFn    encapSimCB;        // simulate for a number of instructions
    vmiEncapGetPCFn  encapGetPCCB;      // get processor program counter
    vmiEncapICountFn encapICountCB;     // get processor instruction count

    ////////////////////////////////////////////////////////////////////////
    // SIMULATOR ENVIRONMENT SUPPORT
    ////////////////////////////////////////////////////////////////////////

    vmiProcessorInfoFn procInfoCB;         // get the procInfo structure

    ////////////////////////////////////////////////////////////////////////////
    // CACHE SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiCacheRegisterFn cacheRegisterCB; // register cache support functions

} vmiIASAttr;

#endif

