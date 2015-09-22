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


#ifndef ICMRUNTIME_H
#define ICMRUNTIME_H

#include "icmTypes.h"

/// When called in a memory read callback, indicates that the read has been
/// aborted.
/// @param processor The current processor.
/// @param address   The bad address.

void icmAbortRead (
    icmProcessorP processor,
    Addr          address
);

/// When called in a memory write callback, indicates that the write has been
/// aborted.
/// @param processor The current processor or null.
/// @param address   The bad address.

void icmAbortWrite (
    icmProcessorP processor,
    Addr          address
);

/// Install a callback which will occur when a net is written.
/// @param net      The net object.
/// @param cb       Address of function to be called.
/// @param userData User data passed to callback.

void icmAddNetCallback (
    icmNetP  net,
    icmNetFn cb,
    void*    userData
);

/// Ask for notification when a PSE maps an address port.
/// @param pse  The PSE.
/// @param port The PSE port name.
/// @param cb   The callback.
/// @param user User Data.

void icmAddPortMapCB (
    icmPseP         pse,
    const char*     port,
    icmPsePortMapFn cb,
    void*           user
);

/// Advance time processing any pending events due in the period. This will
/// cause PSEs and other timed models to process any pending events or delays.
/// The amount that time is advanced, vs. the number of instructions that each
/// processor executes, sets the effective processor speeds.
/// @return Returns True if simulation must continue, False if finish
///         requested.
/// @param time The new ABSOLUTE time (this is not relative).

Bool icmAdvanceTime (
    icmTime time
);

/// Advance time processing any pending events due in the period. This is the
/// same as icmAdvanceTime(), but takes a double (less precision). This is used
/// by the TLM integration (TLM uses double in MSVC).
/// @return Returns True if simulation must continue, False if finish
///         requested.
/// @param time The new ABSOLUTE time (this is not relative).

Bool icmAdvanceTimeDouble (
    double time
);

/// Create dynamic bridge (not for static platforms).
/// @param slave         Bus with slave port; region which gets addressed.
/// @param master        Bus with master port; region which acts as a bus
///                      master.
/// @param lowAddrSlave  The lower end of the slave region.
/// @param highAddrSlave The higher end of the slave region.
/// @param lowAddrMaster The lower end of the master region.

void icmBridgeBuses (
    icmBusP slave,
    icmBusP master,
    Addr    lowAddrSlave,
    Addr    highAddrSlave,
    Addr    lowAddrMaster
);

/// Call a command that was installed in an Intercept object or model.
/// @return The result string, or null.
/// @param modelInstanceName  Instance name of processor or PSE.
/// @param pluginInstanceName Instance name of plugin (intercept object).
///                           Zero if the command is in the model.
/// @param command            Name of the command.
/// @param argc               Number of args to the command, plus one for the
///                           command name.
/// @param argv               Array of string arguments. The first element
///                           should be the command name.

const char* icmCallCommand (
    const char*  modelInstanceName,
    const char*  pluginInstanceName,
    const char*  command,
    Uns32        argc,
    const char** argv
);

/// Cancel the trigger event (before it triggers).
/// @param event The event.

void icmCancelTrigger (
    icmTriggerEventP event
);

/// Terminate execution of the current processor and return immediately from
/// icmSimulate with icmStopReason ICM_SR_EXIT (typically used within
/// icmMemReadFn or icmMemWriteFn callback).
/// @param processor The processor that was running.

void icmExit (
    icmProcessorP processor
);

/// Terminate execution of the current processor and return immediately from
/// icmSimulate with icmStopReason ICM_SR_FINISH (typically used within
/// icmMemReadFn or icmMemWriteFn callback).
/// @param processor The processor that was running, or null.
/// @param status    Status code.

void icmFinish (
    icmProcessorP processor,
    Int32         status
);

/// Inform the simulator that the memory range lowAddr:highAddr has been
/// modified.
/// @param memory   Memory object.
/// @param lowAddr  Low address of range to flush.
/// @param highAddr High address of range to flush.

void icmFlushMemory (
    icmMemoryP memory,
    Addr       lowAddr,
    Addr       highAddr
);

/// Inform a processor that it's code memory has been updated.
/// @param processor Processor object.
/// @param lowAddr   Lower extent of modified memory.
/// @param highAddr  Upper extent of modified memory.

void icmFlushProcessorMemory (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr
);

/// Get the current simulated time.
/// @return Current simulation time (see icmTime).

icmTime icmGetCurrentTime (void);

/// Return the finish status, if simulation was explicitly finished.
/// @return Status, or zero if simulation was not explicitly finished.

Int32 icmGetStatus (void);

/// Return the stopReason for a specific processor.
/// @return Reason why the simulation stopped (see icmStopReason enumerated
///         type).
/// @param processor Processor object.

icmStopReason icmGetStopReason (
    icmProcessorP processor
);

/// Halt execution of the current processor and return immediately from
/// icmSimulate with icmStopReason ICM_SR_HALT (typically used within
/// icmMemReadFn or icmMemWriteFn callback).
/// @param processor The processor that was running.

void icmHalt (
    icmProcessorP processor
);

/// When called in a memory read callback, indicates whether the current context
/// is a fetch (True) or a load (False) (deprecated - use isFetch argument to
/// icmMemReadFn instead).
/// @return Whether context is a fetch.
/// @param processor The current processor.

Bool icmInFetchContext (
    icmProcessorP processor
);

/// This hook function is called just after each model is loaded - set a
/// breakpoint on this to get control just after each model is loaded (allowing
/// further breakpoints to be set in model code if required).
/// @param modelFile   The name of model file being loaded.
/// @param modelSymbol The entry symbol in the model being loaded.

void icmLoadModelHook (
    const char* modelFile,
    const char* modelSymbol
);

/// Restore the state of the given memory.
/// @return Success or failure.
/// @param memory   The memory to restore.
/// @param cb       The function used to restore data.
/// @param userData User context, passed back in the callback.

icmSaveRestoreStatus icmMemoryRestoreState (
    icmMemoryP   memory,
    icmRestoreFn cb,
    void *       userData
);

/// Restore the state of the given memory from a file in default format.
/// @return Success or failure.
/// @param memory The memory to restore.
/// @param file   File name from which to restore.

icmSaveRestoreStatus icmMemoryRestoreStateFile (
    icmMemoryP   memory,
    const char * file
);

/// Save the state of the given memory.
/// @return Success or failure.
/// @param memory   The memory to save.
/// @param cb       The function used to save data.
/// @param userData User context, passed back in the callback.

icmSaveRestoreStatus icmMemorySaveState (
    icmMemoryP memory,
    icmSaveFn  cb,
    void *     userData
);

/// Save the state of the given memory to a file in default format.
/// @return Success or failure.
/// @param memory The memory to save.
/// @param file   File name to which to save.

icmSaveRestoreStatus icmMemorySaveStateFile (
    icmMemoryP   memory,
    const char * file
);

/// Restore the state of the given processor.
/// @return Success or failure.
/// @param processor The processor to restore as returned by icmNewProcessor.
/// @param cb        The function used to restore data.
/// @param userData  User context, passed back in the callback.

icmSaveRestoreStatus icmProcessorRestoreState (
    icmProcessorP processor,
    icmRestoreFn  cb,
    void *        userData
);

/// Restore the state of the given processor from a file in default format.
/// @return Success or failure.
/// @param processor The processor to restore as returned by icmNewProcessor.
/// @param file      File name from which to restore.

icmSaveRestoreStatus icmProcessorRestoreStateFile (
    icmProcessorP processor,
    const char *  file
);

/// Save the state of the given processor.
/// @return Success or failure.
/// @param processor The processor to save, as returned by icmNewProcessor.
/// @param cb        The function used to save data.
/// @param userData  User context, passed back in the callback.

icmSaveRestoreStatus icmProcessorSaveState (
    icmProcessorP processor,
    icmSaveFn     cb,
    void *        userData
);

/// Save the state of the given processor to a file in default format.
/// @return Success or failure.
/// @param processor The processor to save, as returned by icmNewProcessor.
/// @param file      File name to which to save.

icmSaveRestoreStatus icmProcessorSaveStateFile (
    icmProcessorP processor,
    const char *  file
);

/// Read bytes from a bus into a buffer.
/// @return True if access was successful.
/// @param proc       Processor object or null.
/// @param bus        Bus object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to space the receive the data.
/// @param size       Number of bytes to transfer.

Bool icmReadBus (
    icmProcessorP proc,
    icmBusP       bus,
    Addr          simAddress,
    void*         buffer,
    Uns32         size
);

/// Read bytes from memory into a buffer.
/// @return True if access was successful.
/// @param memory     Memory object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to user's space to receive the data.
/// @param size       Number of bytes to transfer.

Bool icmReadMemory (
    icmMemoryP memory,
    Addr       simAddress,
    void*      buffer,
    Uns32      size
);

/// Read a region from the processor address space into native memory.
/// @return True if access was successful.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be read.
/// @param buffer     Pointer to space to receive the data.
/// @param bytes      Number of bytes to transfer.

Bool icmReadProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    void*         buffer,
    Uns32         bytes
);

/// Set PSE diagnostic level. This sets the return value of the deprecated
/// bhmGetDiagnosticLevel and also causes the PSEs 'setDiagnosticLevel' function
/// to be called if one was installed.
/// @param pse   The PSE.
/// @param level The new diagnostic level. Usually 0-4, but see the
///              peripheral modeling guide.

void icmSetPSEdiagnosticLevel (
    icmPseP pse,
    Uns32   level
);

/// Perform simulation of a specific processor for a number of instructions.
/// @return Why it stopped (see icmStopReason enumerated type).
/// @param processor    The processor object.
/// @param instructions Maximum number of instruction to simulate.

icmStopReason icmSimulate (
    icmProcessorP processor,
    Uns64         instructions
);

/// Simulate the platform using the default scheduling scheme, using time slice
/// and stop time set by icmSetSimulationTimeSlice and icmSetSimulationStopTime.
/// @return The processor that has caused simulation to stop, or null if no
///         processor has caused simulation to stop (e.g. the stop time has
///         been reached). The reason why a processor caused simulation to
///         stop can be found using icmGetStopReason.

icmProcessorP icmSimulatePlatform (void);

/// This can be called just as simulation is about to end, in order to activate
/// PSE end-of-simulation code. It is not required if icmSimulatePlatform() is
/// used.

void icmSimulationEnding (void);

/// This can be called after platform construction and before any processor or
/// PSE is due to run. It is not required if icmSimulatePlatform() or
/// icmSimulateProcessor() is used. It must be called if a platform has no
/// processors (just PSEs) or if PSEs are activated before processors.

void icmSimulationStarting (void);

/// Terminate ICM package - call this at end of simulation.

void icmTerminate (void);

/// Call a function after a given (simulated) time interval.
/// @return An event handle which can be used to cancel the event (before it
///         triggers).
/// @param delay Delay in microseconds.
/// @param cb    Address of function to call.
/// @param user  Data passed to the callback.

icmTriggerEventP icmTriggerAfter (
    icmTime      delay,
    icmTriggerFn cb,
    void*        user
);

/// Remove a dynamic bridge. See icmBridgeBuses().
/// @param bus      Bus with slave port; this generates the addresses.
/// @param lowAddr  The lower end of the slave region.
/// @param highAddr The higher end of the slave region.

void icmUnbridgeBuses (
    icmBusP bus,
    Addr    lowAddr,
    Addr    highAddr
);

/// Write bytes to a bus from a buffer.
/// @return True if access was successful.
/// @param proc       Processor object or null.
/// @param bus        Bus object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to space containing the data.
/// @param size       Number of bytes to transfer.

Bool icmWriteBus (
    icmProcessorP proc,
    icmBusP       bus,
    Addr          simAddress,
    const void*   buffer,
    Uns32         size
);

/// Write bytes to memory from a buffer.
/// @return True if access was successful.
/// @param memory     Memory object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to user's space containing the data.
/// @param size       Number of bytes to transfer.

Bool icmWriteMemory (
    icmMemoryP  memory,
    Addr        simAddress,
    const void* buffer,
    Uns32       size
);

/// Write a value to a net.
/// @return True if the net is connected.
/// @param net      The net object.
/// @param netValue Value to be propagated.

Bool icmWriteNet (
    icmNetP net,
    Uns32   netValue
);

/// Write a value to a netPort.
/// @return True if the port is connected.
/// @param port     The netPort object.
/// @param netValue Value to be propagated.

Bool icmWriteNetPort (
    icmNetPortP port,
    Uns32       netValue
);

/// Write data to a packetnet.
/// @param packetnet Packetnet object.
/// @param data      Data.
/// @param bytes     Number of data bytes to send.

void icmWritePacketnet (
    icmPacketnetP packetnet,
    void*         data,
    Uns32         bytes
);

/// Write a region from native memory into processor address.
/// @return True if access was successful.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be written.
/// @param buffer     Pointer to space containing the data.
/// @param bytes      Number of bytes to transfer.

Bool icmWriteProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    const void*   buffer,
    Uns32         bytes
);

/// Suspend execution of the passed processor (this may be the current
/// processor) and return immediately from icmSimulate with icmStopReason
/// ICM_SR_YIELD (typically used within icmMemReadFn or icmMemWriteFn callback).
/// As with all other ICM functions this should not be called from a signal
/// handler to interrupt simulation (see icmInterrupt for this purpose).
/// @param processor The processor that was running.

void icmYield (
    icmProcessorP processor
);


#endif /* ICMRUNTIME_H */

