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


#ifndef ICMDEBUGGER_H
#define ICMDEBUGGER_H

#include "icmTypes.h"

/// Clear address breakpoint for the processor.
/// @param processor  Processor on which to clear breakpoint.
/// @param simAddress Address at which break should no longer occur.

void icmClearAddressBreakpoint (
    icmProcessorP processor,
    Addr          simAddress
);

/// Clear instruction count breakpoint for the processor.
/// @param processor Processor handle.

void icmClearICountBreakpoint (
    icmProcessorP processor
);

/// Read a region from the processor address space into native memory, without
/// side effects. When calculating the byte-swap requirements, it uses the
/// processor's DATA endian-ness.
/// @return True if access was successful. False if any part failed.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be read.
/// @param buffer     Pointer to host space to receive the data.
/// @param objectSize Number of bytes in each endian-corrected object.
/// @param objects    Number of objects.
/// @param hostEndian Endian-ness of data in host buffer.

Bool icmDebugReadProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    void*         buffer,
    Uns32         objectSize,
    Uns32         objects,
    icmHostEndian hostEndian
);

/// Add this to the list of processors to attach a debugger (max=1 in OVPsim).
/// @param processor Processor handle.

void icmDebugThisProcessor (
    icmProcessorP processor
);

/// Write a region from native memory into processor address, without
/// side-effects. When calculating the byte-swap requirements, it uses the
/// processor's DATA endian-ness.
/// @return True if access was successful. False if any part failed.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be written.
/// @param buffer     Pointer to host space containing the data.
/// @param objectSize Number of bytes in each endian-corrected object.
/// @param objects    Number of objects.
/// @param hostEndian Endian-ness of data in host buffer.

Bool icmDebugWriteProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    const void*   buffer,
    Uns32         objectSize,
    Uns32         objects,
    icmHostEndian hostEndian
);

/// Delete the passed watchpoint object.
/// @param watchpoint Watchpoint to delete.

void icmDeleteWatchPoint (
    icmWatchPointP watchpoint
);

/// Call the processor-specific register dump.
/// @return Disassembly string. This is a static buffer, so will be
///         overwritten by the next call.
/// @param processor Processor object.
/// @param simAddr   Address of instruction to be disassembled. Must be
///                  correctly instruction-aligned for a meaningful result.

const char* icmDisassemble (
    icmProcessorP processor,
    Addr          simAddr
);

/// Call the processor-specific register dump.
/// @param processor Processor object.

void icmDumpRegisters (
    icmProcessorP processor
);

/// Freeze the processor (frozen processors will not be run by icmSimulate or
/// icmSimulatePlatform).
/// @param processor The processor that was running.

void icmFreeze (
    icmProcessorP processor
);

/// Return fault address associated with the processor state if applicable.
/// @return Whether by-ref fault address is valid.
/// @param processor    Processor object.
/// @param faultAddress Pointer filled with fault address.

Bool icmGetFaultAddress (
    icmProcessorP processor,
    Addr *        faultAddress
);

/// Return the address of the next instruction, allowing for variable length
/// instructions.
/// @return Processor current instruction address.
/// @param processor Processor object.
/// @param thisPC    The address of the current instruction.

Addr icmGetNextInstructionAddress (
    icmProcessorP processor,
    Addr          thisPC
);

/// Return the next triggered watchpoint object that has not been reset.
/// @return Next triggered watchpoint.

icmWatchPointP icmGetNextTriggeredWatchPoint (void);

/// Get the processor program counter.
/// @return Value of the PC. This function is similar to icmReadReg, but does
///         not need to know the name of the PC.
/// @param processor Processor object.

Addr icmGetPC (
    icmProcessorP processor
);

/// For processors without delay slots, or for a non-delay-slot instruction of a
/// processor with delay slots, return the processor program counter and set
/// 'delaySlotOffset' to zero. For a delay slot instruction, return the program
/// counter of the preceding jump instruction and set 'delaySlotOffset' to the
/// offset in bytes of the delay slot instruction.
/// @return Processor program counter.
/// @param processor       Processor object.
/// @param delaySlotOffset Set to offset (in bytes) of the delay slot
///                        instruction.

Addr icmGetPCDS (
    icmProcessorP processor,
    Uns8 *        delaySlotOffset
);

/// Return the number of instructions and halted instructions executed by the
/// processor.
/// @return Number of instructions and halted instructions executed, up to
///         now.
/// @param processor Processor object.

Uns64 icmGetProcessorClocks (
    icmProcessorP processor
);

/// Return the number of instructions executed by the processor.
/// @return Number of instructions executed, up to now.
/// @param processor Processor object.

Uns64 icmGetProcessorICount (
    icmProcessorP processor
);

/// Return current value for the passed register watchpoint (returns NULL for a
/// memory watchpoint).
/// @return Current value pointer.
/// @param watchpoint Watchpoint for which to return current value.

void* icmGetWatchPointCurrentValue (
    icmWatchPointP watchpoint
);

/// Return the high address bound of the passed watchpoint (returns zero for a
/// register watchpoint).
/// @return Watchpoint high address.
/// @param watchpoint Watchpoint for which to return high address.

Addr icmGetWatchPointHighAddress (
    icmWatchPointP watchpoint
);

/// Return the low address bound of the passed watchpoint (returns zero for a
/// register watchpoint).
/// @return Watchpoint low address.
/// @param watchpoint Watchpoint for which to return low address.

Addr icmGetWatchPointLowAddress (
    icmWatchPointP watchpoint
);

/// Return previous value for the passed register watchpoint (returns NULL for a
/// memory watchpoint).
/// @return Previous value pointer.
/// @param watchpoint Watchpoint for which to return previous value.

void* icmGetWatchPointPreviousValue (
    icmWatchPointP watchpoint
);

/// Return register for the passed watchpoint (returns NULL for a memory
/// watchpoint).
/// @return Watchpoint register.
/// @param watchpoint Watchpoint for which to return register.

icmRegInfoP icmGetWatchPointRegister (
    icmWatchPointP watchpoint
);

/// Return processor that triggered a watchpoint.
/// @return The triggering processor.
/// @param watchpoint Watchpoint for which to return processor.

icmProcessorP icmGetWatchPointTriggeredBy (
    icmWatchPointP watchpoint
);

/// Return the type of the passed watchpoint object.
/// @return Watchpoint type.
/// @param watchpoint Watchpoint to query.

icmWatchpointType icmGetWatchPointType (
    icmWatchPointP watchpoint
);

/// Return userData recorded with watchpoint.
/// @return User data pointer.
/// @param watchpoint Watchpoint for which to return userData.

void* icmGetWatchPointUserData (
    icmWatchPointP watchpoint
);

/// This is the only ICM function that is safe to call in a signal handler. It
/// causes any currently-executing simulation thread to stop as soon as possible
/// in a safe state so that other ICM functions can be called. The stop is
/// signalled by a return code stop reason of ICM_SR_INTERRUPT. The thread stops
/// just before the next code block is executed; typically, this will be a few
/// instructions on from the icmInterrupt call. It is safe to use icmInterrupt
/// in non-signal-handler contexts (e.g. memory callbacks) but you may want to
/// consider the use of icmYield in this context.

void icmInterrupt (void);

/// Return control to the mpd console from native code - ICM clients should not
/// use this function.

void icmInterruptRSP (void);

/// Is the processor currently frozen?.
/// @return Whether processor was frozen.
/// @param processor The processor that was running.

Bool icmIsFrozen (
    icmProcessorP processor
);

/// Read a named register of a processor.
/// @return True if the name was recognized.
/// @param processor Processor object.
/// @param name      Name of the register.
/// @param buffer    Space to receive the register contents. Must be large
///                  enough to accept the data.

Bool icmReadReg (
    icmProcessorP processor,
    const char*   name,
    void*         buffer
);

/// Read a processor register.
/// @return True if the register is readable.
/// @param icmProcessor Processor object.
/// @param reg          Register object.
/// @param buffer       Data to be written (must be the correct size).

Bool icmReadRegInfoValue (
    icmProcessorP icmProcessor,
    icmRegInfoP   reg,
    void*         buffer
);

/// Reset the passed watchpoint object so that it is no longer marked as
/// triggered.
/// @param watchpoint Watchpoint to reset.

void icmResetWatchPoint (
    icmWatchPointP watchpoint
);

/// Set address breakpoint for the processor. When breakpoint address is
/// executed, processor stops execution with stopReason ICM_SR_BP_ADDRESS.
/// @param processor  Processor on which to set breakpoint.
/// @param simAddress Address at which to break.

void icmSetAddressBreakpoint (
    icmProcessorP processor,
    Addr          simAddress
);

/// Set access watchpoint on address range low:high in bus. When any processor
/// reads or writes an address in that range, it will stop execution with
/// stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to
/// be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created.
/// @param bus        Memory on which to set watchpoint.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetBusAccessWatchPoint (
    icmBusP          bus,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set read watchpoint on address range low:high in bus. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created.
/// @param bus        Bus on which to set watchpoint.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetBusReadWatchPoint (
    icmBusP          bus,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set write watchpoint on address range low:high in bus. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created.
/// @param bus        Bus on which to set watchpoint.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetBusWriteWatchPoint (
    icmBusP          bus,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Call this before icmInitPlatform. Ask for callbacks for debugger
/// integration.
/// @param notifiers Pointer to structure containing notifiers.

void icmSetDebugNotifiers (
    icmDebugNotifierP notifiers
);

/// Set the stop time (for icmSimulatePlatform) - takes effect at the end of any
/// current time slice. icmSimulatePlatform will not return when this stop time
/// is reached, an attached debugger will get control.
/// @return True if successful.
/// @param newStopTime The new stop time (see icmTime).

Bool icmSetDebugStopTime (
    icmTime newStopTime
);

/// Set exception watchpoint. When the processor takes an exception it will stop
/// execution with stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered
/// watchpoints need to be processed with icmGetNextTriggeredWatchPoint before
/// simulation is resumed.
/// @return Watchpoint object created.
/// @param processor  Processor on which to set watchpoint.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetExceptionWatchPoint (
    icmProcessorP    processor,
    void*            userData,
    icmRegNotifierFn notifierCB
);

/// Set instruction count breakpoint for the processor that will expire after
/// 'delta' instructions. When instruction count has expired, processor stops
/// execution with stopReason ICM_SR_BP_ICOUNT.
/// @param processor Processor on which to set breakpoint.
/// @param delta     Instruction count after which to stop.

void icmSetICountBreakpoint (
    icmProcessorP processor,
    Uns64         delta
);

/// Set access watchpoint on address range low:high in memory. When any
/// processor reads or writes an address in that range, it will stop execution
/// with stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need
/// to be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created.
/// @param memory     Memory on which to set watchpoint.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetMemoryAccessWatchPoint (
    icmMemoryP       memory,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set read watchpoint on address range low:high in memory. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created.
/// @param memory     Memory on which to set watchpoint.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetMemoryReadWatchPoint (
    icmMemoryP       memory,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set write watchpoint on address range low:high in memory. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created.
/// @param memory     Memory on which to set watchpoint.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetMemoryWriteWatchPoint (
    icmMemoryP       memory,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set mode change watchpoint. When the processor mode changes (the value
/// returned by icmGetMode differs) it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created.
/// @param processor  Processor on which to set watchpoint.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetModeWatchPoint (
    icmProcessorP    processor,
    void*            userData,
    icmRegNotifierFn notifierCB
);

/// Set the processor program counter.
/// @param processor Processor object.
/// @param simAddr   Value loaded into the PC. This function is similar to
///                  icmWriteReg, but does not need to know the name of the
///                  PC.

void icmSetPC (
    icmProcessorP processor,
    Addr          simAddr
);

/// Set path to a gdb executable and gdb start-up arguments. This is only
/// required if debugging a PSE.
/// @param processor PSE object.
/// @param path      Path to the GDB executable.
/// @param flags     Any command line flags required by GDB.

void icmSetPSEGdbPath (
    icmPseP     processor,
    const char* path,
    const char* flags
);

/// Set access watchpoint on address range low:high in the processor physical or
/// virtual address space (depending on the setting of 'isPhysical'). When any
/// processor reads or writes an address in that range, it will stop execution
/// with stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need
/// to be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created.
/// @param processor  Processor on which to set watchpoint.
/// @param isPhysical True for physical, False for virtual.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetProcessorAccessWatchPoint (
    icmProcessorP    processor,
    Bool             isPhysical,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Do not use an external GDB for this processor.
/// @param processor Processor to use the basic debug functionality.

void icmSetProcessorGdbBasic (
    icmProcessorP processor
);

/// Set path to a gdb executable and gdb start-up arguments.
/// @param processor Processor to associate with this gdb.
/// @param path      Path to the GDB.
/// @param flags     Optional command line flags.

void icmSetProcessorGdbPath (
    icmProcessorP processor,
    const char*   path,
    const char*   flags
);

/// Set read watchpoint on address range low:high in the processor physical or
/// virtual address space (depending on the setting of 'isPhysical'). When any
/// processor reads an address in that range, it will stop execution with
/// stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to
/// be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created.
/// @param processor  Processor on which to set watchpoint.
/// @param isPhysical True for physical, False for virtual.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetProcessorReadWatchPoint (
    icmProcessorP    processor,
    Bool             isPhysical,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set write watchpoint on address range low:high in the processor physical or
/// virtual address space (depending on the setting of 'isPhysical'). When any
/// processor reads an address in that range, it will stop execution with
/// stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to
/// be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created.
/// @param processor  Processor on which to set watchpoint.
/// @param isPhysical True for physical, False for virtual.
/// @param low        Low bound of watched range.
/// @param high       High bound of watched range.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetProcessorWriteWatchPoint (
    icmProcessorP    processor,
    Bool             isPhysical,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// Set register change watchpoint. When the register value changes in the
/// passed processor, it will stop execution with stopReason ICM_SR_WATCHPOINT.
/// Upon halt, all triggered watchpoints need to be processed with
/// icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created.
/// @param processor  Processor on which to set watchpoint.
/// @param regInfo    Register to watch or null.
/// @param userData   Client-specific data pointer.
/// @param notifierCB Client-specific notifier.

icmWatchPointP icmSetRegisterWatchPoint (
    icmProcessorP    processor,
    icmRegInfoP      regInfo,
    void*            userData,
    icmRegNotifierFn notifierCB
);

/// Ask for a callback when each processor has finished its slice. Deprecated,
/// use icmSetDebugNotifiers.
/// @param startcb  The start simulation function.
/// @param endcb    The end schedule function.
/// @param userData Pass this in the userData argument.

void icmSetSchedFn (
    icmStartSimFn startcb,
    icmEndSchedFn endcb,
    void*         userData
);

/// Unfreeze the processor (frozen processors will not be run by icmSimulate or
/// icmSimulatePlatform).
/// @param processor The processor that was running.

void icmUnfreeze (
    icmProcessorP processor
);

/// Write a named register of a processor.
/// @return True if the name was recognized and the register is readable.
/// @param processor Processor object.
/// @param name      Name of the register.
/// @param buffer    Buffer containing the register contents.

Bool icmWriteReg (
    icmProcessorP processor,
    const char*   name,
    const void*   buffer
);

/// Write to a processor register.
/// @return True if the register is writable.
/// @param icmProcessor Processor object.
/// @param reg          Register object.
/// @param buffer       Space for data to read read (must be the correct
///                     size).

Bool icmWriteRegInfoValue (
    icmProcessorP icmProcessor,
    icmRegInfoP   reg,
    const void*   buffer
);


#endif /* ICMDEBUGGER_H */

