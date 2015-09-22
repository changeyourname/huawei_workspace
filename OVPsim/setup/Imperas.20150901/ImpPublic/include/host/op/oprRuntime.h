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


#ifndef OPRRUNTIME_H
#define OPRRUNTIME_H

#include "optTypes.h"

/// Get the control features specified for this application.
/// @return Bit-mask of control features.
/// @param application Application.

optLoaderControls oprApplicationControls (
    optApplicationP application
);

/// Get the elf code of a loaded program.
/// @return The ELF code.
/// @param app The application.

Uns32 oprApplicationElfCode (
    optApplicationP app
);

/// Get the endian of a loaded program.
/// @return The ELF code.
/// @param app The application.

optEndian oprApplicationEndian (
    optApplicationP app
);

/// Get the entry address of a loaded program.
/// @return The entry point.
/// @param app The application.

Addr oprApplicationEntry (
    optApplicationP app
);

/// Get the path to a loaded program.
/// @return The cannonical path to the program object file.
/// @param app The application.

const char * oprApplicationPath (
    optApplicationP app
);

/// Add a fetch callback on a bus region.
/// @param bus       Bus.
/// @param processor optional processor pointer.
/// @param loAddr    Lower bound.
/// @param hiAddr    Upper bound.
/// @param wcb       Callback.
/// @param userData  User data returned in the callback.

void oprBusFetchCallback (
    optBusP       bus,
    optProcessorP processor,
    Addr          loAddr,
    Addr          hiAddr,
    optMemWatchFn wcb,
    void*         userData
);

/// Return the bus port maximum number of address bits.
/// @return Number of address bits.
/// @param busPort The bus port descriptor.

Uns32 oprBusPortAddrBitsMax (
    optBusPortP busPort
);

/// Return the bus port minimum number of address bits.
/// @return Number of address bits.
/// @param busPort The bus port descriptor.

Uns32 oprBusPortAddrBitsMin (
    optBusPortP busPort
);

/// Return the bus port maximum address (slave port only).
/// @return Maximum address in this window.
/// @param busPort The bus port descriptor.

Addr oprBusPortAddrHi (
    optBusPortP busPort
);

/// Return true if the connected bus port slave decode can change at run-time.
/// @return True if dynamic decode.
/// @param list The bus port connection.

Bool oprBusPortConnIsDynamic (
    optBusPortConnP list
);

/// Install callback for when a port mapping changes.
/// @return Success.
/// @param busPort  Bus to read.
/// @param cb       Callback.
/// @param userData User data.

Bool oprBusPortConnMapNotify (
    optBusPortConnP busPort,
    optPortMapFn    cb,
    void*           userData
);

/// Return the bus port connection type.
/// @return type.
/// @param list The bus port connection.

optBusPortType oprBusPortConnType (
    optBusPortConnP list
);

/// Return the bus port connection type.
/// @return type as a string.
/// @param list The bus port connection.

const char * oprBusPortConnTypeString (
    optBusPortConnP list
);

/// Return the bus port descriptor.
/// @return A description.
/// @param busPort The bus port descriptor.

const char* oprBusPortDescription (
    optBusPortP busPort
);

/// Return the bus port domain type from the descriptor.
/// @return The type of domain (code or data).
/// @param busPort The bus port descriptor.

optDomainType oprBusPortDomainType (
    optBusPortP busPort
);

/// Return the bus port domain type from the descriptor as a string.
/// @return The type of domain.
/// @param busPort The bus port descriptor.

const char* oprBusPortDomainTypeString (
    optBusPortP busPort
);

/// Return true if this port cannot be left unconnected.
/// @return True if this bus port must be connected.
/// @param busPort The bus port descriptor.

Bool oprBusPortMustBeConnected (
    optBusPortP busPort
);

/// Return the bus port type from the descriptor.
/// @return The type.
/// @param busPort The bus port descriptor.

optBusPortType oprBusPortTypeEnum (
    optBusPortP busPort
);

/// Return the bus port type from the descriptor as a string.
/// @return The type of port.
/// @param busPort The bus port descriptor.

const char* oprBusPortTypeString (
    optBusPortP busPort
);

/// Add a read callback on a bus region.
/// @param bus       Bus.
/// @param processor optional processor pointer.
/// @param loAddr    Lower bound.
/// @param hiAddr    Upper bound.
/// @param rcb       Callback.
/// @param userData  User data returned in the callback.

void oprBusReadCallback (
    optBusP       bus,
    optProcessorP processor,
    Addr          loAddr,
    Addr          hiAddr,
    optMemWatchFn rcb,
    void*         userData
);

/// Set a watchpoint on a bus access.
/// @return New watchpoint.
/// @param bus        Bus.
/// @param addrLo     lower bound.
/// @param addrHi     upper bound.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprBusWatchpointAccessSet (
    optBusP        bus,
    Addr           addrLo,
    Addr           addrHi,
    void*          userData,
    optMemNotifyFn notifierCB
);

/// Set a watchpoint on a bus read access.
/// @return New watchpoint.
/// @param bus        Bus.
/// @param addrLo     lower bound.
/// @param addrHi     upper bound.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprBusWatchpointReadSet (
    optBusP        bus,
    Addr           addrLo,
    Addr           addrHi,
    void*          userData,
    optMemNotifyFn notifierCB
);

/// Set a watchpoint on a bus write access.
/// @return New watchpoint.
/// @param bus        Bus.
/// @param addrLo     lower bound.
/// @param addrHi     upper bound.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprBusWatchpointWriteSet (
    optBusP        bus,
    Addr           addrLo,
    Addr           addrHi,
    void*          userData,
    optMemNotifyFn notifierCB
);

/// Add a write callback on a bus region.
/// @param bus       Bus.
/// @param processor optional processor pointer.
/// @param loAddr    Lower bound.
/// @param hiAddr    Upper bound.
/// @param wcb       Callback.
/// @param userData  User data returned in the callback.

void oprBusWriteCallback (
    optBusP       bus,
    optProcessorP processor,
    Addr          loAddr,
    Addr          hiAddr,
    optMemWatchFn wcb,
    void*         userData
);

/// Call a command.
/// @return String returned by the command.
/// @param command Command Object.
/// @param argc    Number of arguments.
/// @param argv    List of arguments.

const char * oprCommandCall (
    optCommandP   command,
    Uns32         argc,
    const char ** argv
);

/// Get the help string associated with a command.
/// @return Help string from the command.
/// @param command Command.

const char * oprCommandHelp (
    optCommandP command
);

/// Issue the callback on all commands in this module.
/// @param module   The module.
/// @param cb       Command callback.
/// @param userData User data passed to callback.

void oprCommandIterAll (
    optModuleP   module,
    optCommandFn cb,
    void*        userData
);

/// Call a command.
/// @return String returned by the command, or null if command failed.
/// @param root    Root module.
/// @param command Hierarchical name of the command, including globbing.
/// @param argc    Number of arguments.
/// @param argv    List of arguments.

const char * oprCommandStringCall (
    optModuleP    root,
    const char *  command,
    Uns32         argc,
    const char ** argv
);

/// Get the next child of this node.
/// @return Pointer to child document node, or null.
/// @param parent Current document node.
/// @param child  Current document node or null.

optDocNodeP oprDocChildNext (
    optDocNodeP parent,
    optDocNodeP child
);

/// Is this content or a title?.
/// @return True if this is content, False it it's a title.
/// @param node Document node.

Bool oprDocIsTitle (
    optDocNodeP node
);

/// Get title or content text from this node (use icmDocIsText to find which it
/// is).
/// @return Pointer to text.
/// @param node Document node.

const char * oprDocText (
    optDocNodeP node
);

/// Create dynamic bridge between two buses.
/// @return True if the bridge was created.
/// @param slave        The initiating bus.
/// @param master       The responding bus.
/// @param loAddrSlave  The lowest address of the decoded region on the
///                     initiating bus.
/// @param hiAddrSlave  The highest address of the decoded region on the
///                     initiating bus.
/// @param loAddrMaster The lowest address of the region where accesses are
///                     initiated on the responding bus.

Bool oprDynamicBridge (
    optBusP slave,
    optBusP master,
    Addr    loAddrSlave,
    Addr    hiAddrSlave,
    Addr    loAddrMaster
);

/// Map native memory onto a bus at run-time. The memory must be pre-allocated
/// by the user.
/// @return True if the mapping was accepted.
/// @param bus          Bus on which the bridge receives an access.
/// @param loAddr       The lowest address on the bus.
/// @param hiAddr       The highest address on the bus.
/// @param nativeMemory The native memory to be mapped.
/// @param priv         privilege for new mapping.

Bool oprDynamicNativeMemory (
    optBusP bus,
    Addr    loAddr,
    Addr    hiAddr,
    void*   nativeMemory,
    optPriv priv
);

/// Remove dynamic bridge between two buses.
/// @return True if the bridge was removed.
/// @param slave        The initiating bus.
/// @param loAddrMaster The lowest address on the initiating bus.
/// @param hiAddrMaster The highest address on the initiating bus.

Bool oprDynamicUnbridge (
    optBusP slave,
    Addr    loAddrMaster,
    Addr    hiAddrMaster
);

/// Return the enum description.
/// @return The enumeration description.
/// @param e The current enum.

const char* oprEnumDescription (
    optFormalEnumP e
);

/// Return the enum value.
/// @return The enumeration value.
/// @param e The current enum.

Uns32 oprEnumValue (
    optFormalEnumP e
);

/// Return the model-specific exception code.
/// @return Exception code.
/// @param exception Handle to exception descriptor.

Uns32 oprExceptionCode (
    optExceptionP exception
);

/// Return a description of the exception.
/// @return Exception description.
/// @param exception Handle to exception descriptor.

const char* oprExceptionDescription (
    optExceptionP exception
);

/// Return the name of the exception from the descriptor.
/// @return Exception name (note that this string does not persist).
/// @param exception Handle to exception descriptor.

const char* oprExceptionName (
    optExceptionP exception
);

/// Next extension command.
/// @return Command descriptor.
/// @param processor Parent extension.
/// @param current   Current command or null.

optCommandP oprExtensionCommandNext (
    optExtensionP processor,
    optCommandP   current
);

/// Return the FIFO port's description.
/// @return Description of the FIFO port.
/// @param fifoPort Handle to FIFO port descriptor.

const char* oprFIFOPortDescription (
    optFIFOPortP fifoPort
);

/// Return the FIFO port type (input or output) from the descriptor.
/// @return The FIFO port type (direction of use).
/// @param fifoPort Handle to FIFO port descriptor.

optFIFOPortType oprFIFOPortTypeEnum (
    optFIFOPortP fifoPort
);

/// Return the FIFO port type (input or output) from the descriptor.
/// @return The FIFO port type (direction of use) as a string.
/// @param fifoPort Handle to FIFO port descriptor.

const char* oprFIFOPortTypeString (
    optFIFOPortP fifoPort
);

/// Return the FIFO port width (in bits) from the descriptor.
/// @return The FIFO port width, in bits.
/// @param fifoPort Handle to FIFO port descriptor.

Uns32 oprFIFOPortWidth (
    optFIFOPortP fifoPort
);

/// Return the formal parameter description from the descriptor.
/// @return A description.
/// @param formal Handle to parameter.

const char* oprFormalDescription (
    optFormalP formal
);

/// Return the next enum value from a formal parameter descriptor.
/// @return The enum.
/// @param paramInfo The formal parameter.
/// @param e         The current enum or null.

optFormalEnumP oprFormalEnumNext (
    optFormalP     paramInfo,
    optFormalEnumP e
);

/// Return the formal parameter name from the descriptor.
/// @return The parameter name.
/// @param formal The formal parameter.

const char* oprFormalName (
    optFormalP formal
);

/// Return the formal parameter type from the descriptor.
/// @return The type.
/// @param formal The formal parameter.

optParamType oprFormalType (
    optFormalP formal
);

/// Return the formal parameter type from the descriptor as a string.
/// @return The type.
/// @param formal The formal parameter.

const char* oprFormalTypeString (
    optFormalP formal
);

/// When called in a memory read callback, indicates whether the current context
/// is a fetch or a load.
/// @return True if in a fetch context.
/// @param processor Processing element.

Bool oprInFetchContext (
    optProcessorP processor
);

/// Called when the simulator is running but thread safe, causes it to
/// prematurely return optStopReason OPT_SR_INTERRUPT.

void oprInterrupt (void);

/// Called when the simulator is running but thread safe, Return control to the
/// mpd console.

void oprInterruptRSP (void);

/// Signal that code memory has been changed and that any processors using the
/// address range should invalidate cached JIT translations.
/// @param memory Memory to flush.
/// @param addrLo Lower bound.
/// @param addrHi Upper bound.

void oprMemoryFlush (
    optMemoryP memory,
    Addr       addrLo,
    Addr       addrHi
);

/// Read data from a memory.
/// @return True if success.
/// @param memory  Memory to read.
/// @param address Memory address.
/// @param buffer  Native buffer.
/// @param bytes   Number of bytes.
/// @param debug   True if this should not perturb the platform state.

Bool oprMemoryRead (
    optMemoryP memory,
    Addr       address,
    void*      buffer,
    Uns32      bytes,
    Bool       debug
);

/// Restore the state of the given memory.
/// @return Success or failure.
/// @param memory   The memory to restore.
/// @param cb       The function used to restore data.
/// @param userData User context, passed back in the callback.

optSaveRestoreStatus oprMemoryStateRestore (
    optMemoryP   memory,
    optRestoreFn cb,
    void *       userData
);

/// Restore the state of the given memory.
/// @return Success or failure.
/// @param memory The memory to save.
/// @param file   The file.

optSaveRestoreStatus oprMemoryStateRestoreFile (
    optMemoryP   memory,
    const char * file
);

/// Save the state of the given memory using a callback.
/// @return Success or failure.
/// @param memory   The memory to save.
/// @param cb       The function used to save data.
/// @param userData User context, passed back in the callback.

optSaveRestoreStatus oprMemoryStateSave (
    optMemoryP memory,
    optSaveFn  cb,
    void *     userData
);

/// Save the state of the given memory to a file.
/// @return Success or failure.
/// @param memory The memory to save.
/// @param file   The file.

optSaveRestoreStatus oprMemoryStateSaveFile (
    optMemoryP   memory,
    const char * file
);

/// Write data to a memory.
/// @return Success.
/// @param memory  Memory to write.
/// @param address Memory address.
/// @param buffer  Native buffer.
/// @param bytes   Number of bytes.
/// @param debug   True if this should not perturb the platform state (other
///                than the memory location).

Bool oprMemoryWrite (
    optMemoryP  memory,
    Addr        address,
    const void* buffer,
    Uns32       bytes,
    Bool        debug
);

/// Return the model-specific mode code from the descriptor.
/// @return Mode code.
/// @param mode Processor mode descriptor.

Uns32 oprModeCode (
    optModeP mode
);

/// Return the description of the mode from the descriptor.
/// @return Mode description.
/// @param mode Processor mode descriptor.

const char* oprModeDescription (
    optModeP mode
);

/// Return the name of the mode from the descriptor.
/// @return Mode name (note that this string does not persist).
/// @param mode Processor mode descriptor.

const char* oprModeName (
    optModeP mode
);

/// Get the current time.
/// @return The current time.
/// @param module (root) module instance.

optTime oprModuleCurrentTime (
    optModuleP module
);

/// Report the domains in a module.
/// @param module The root module.

void oprModuleDomainDebug (
    optModuleP module
);

/// Signal that this module wants to terminate the session.
/// @param module Current module instance.
/// @param status Return status.

void oprModuleFinish (
    optModuleP module,
    Int32      status
);

/// Get the finish status of this root module.
/// @return The finish status.
/// @param module Current module instance.

Int32 oprModuleFinishStatus (
    optModuleP module
);

/// Perform actions after elaboration but before simulation.
/// @param module The root module.

void oprModulePostElaborate (
    optModuleP module
);

/// Perform end-of-simulation actions without destroying the platform.
/// @param module The root module to finish.

void oprModulePostSimulate (
    optModuleP module
);

/// Prepare for and run start-of-simulation actions without running any code.
/// @param module The root module to prepare.

void oprModulePreSimulate (
    optModuleP module
);

/// Set the debug stop time (for optModuleSimulate) - takes effect at the end of
/// any current time slice. icmSimulatePlatform will return when this stop time
/// is reached.
/// @return True if successful.
/// @param module      Parent module.
/// @param newStopTime The new stop time (see optTime).

Bool oprModuleSetDebugStopTime (
    optModuleP module,
    optTime    newStopTime
);

/// Set a seed for randomizing the order in which processors are processed a
/// time slice. The default is no randomization (seed=0).
/// @param module   Parent module.
/// @param lfsrSeed New seed.

void oprModuleSetSimulationRandomSeed (
    optModuleP module,
    Uns32      lfsrSeed
);

/// Set the simulation stop time (for icmSimulatePlatform) - takes effect at the
/// end of any current time slice. icmSimulatePlatform will return when this
/// stop time is reached.
/// @return True if successful.
/// @param module      Parent module.
/// @param newStopTime The new stop time (see optTime).

Bool oprModuleSetSimulationStopTime (
    optModuleP module,
    optTime    newStopTime
);

/// Set the simulation time precision - all event times are rounded to this. Use
/// this if calling from MSVC.
/// @return True if successful.
/// @param module    Parent module.
/// @param precision The precision (see optTime).

Bool oprModuleSetSimulationTimePrecision (
    optModuleP module,
    optTime    precision
);

/// Set the simulation time slice size (for optModuleSimulate) - takes effect at
/// the end of the current time slice.
/// @return True if successful.
/// @param module       Parent module.
/// @param newSliceSize The new slice duration (see optTime).

Bool oprModuleSetSimulationTimeSlice (
    optModuleP module,
    optTime    newSliceSize
);

/// When running in wallclock mode (_wallClock specified), this gives the
/// maximum multiple of real time at which the simulation should run. The
/// default is 1.0, implying no faster than real time. An value of 2.0 implies
/// no faster than twice real time; a value of 0.5 implies no faster than half.
/// @param module Parent module.
/// @param factor Wallclock factor to apply.

void oprModuleSetWallClockFactor (
    optModuleP module,
    double     factor
);

/// Simulate a platform until a reason to stop occurs.
/// @return The processor that was running when the simulation stopped.
/// @param module The complete platform instance.

optProcessorP oprModuleSimulate (
    optModuleP module
);

/// Move time forward for this platform, processing any pending events due in
/// the period.
/// @return Returns true if successful.
/// @param module       Parent module.
/// @param absoluteTime New time.

Bool oprModuleTimeAdvance (
    optModuleP module,
    optTime    absoluteTime
);

/// Call a function this far into the future.
/// @return Trigger object (use this to delete the trigger before it occurs).
/// @param module       Parent module.
/// @param relativeTime Time into the future.
/// @param cb           Triggered callback.
/// @param userData     Data to be passed to the callback.

optTriggerEventP oprModuleTriggerAdd (
    optModuleP   module,
    optTime      relativeTime,
    optTriggerFn cb,
    void*        userData
);

/// Delete a trigger event.
/// @param module Parent module.
/// @param event  The trigger event to delete.

void oprModuleTriggerDelete (
    optModuleP       module,
    optTriggerEventP event
);

/// Return the next triggered watchpoint.
/// @return The next triggered watchpoint.
/// @param module The root module.

optWatchpointP oprModuleWatchpointNext (
    optModuleP module
);

/// Add a callback to a net.
/// @param net      Net.
/// @param cb       Function to be called when the net is written.
/// @param userData User data.

void oprNetCallbackAdd (
    optNetP       net,
    optNetWriteFn cb,
    void*         userData
);

/// Return the net port type from the descriptor.
/// @return The type of port.
/// @param netPort Handle to net port connection.

optNetPortType oprNetPortConnType (
    optNetPortConnP netPort
);

/// Return the net port description.
/// @return A description of the net port.
/// @param netPort Handle to net port descriptor.

const char* oprNetPortDescription (
    optNetPortP netPort
);

/// Return true if this port cannot be left unconnected.
/// @return True if this bus port must be connected.
/// @param netPort The net port descriptor.

Bool oprNetPortMustBeConnected (
    optNetPortP netPort
);

/// Return the net port type from the descriptor.
/// @return The type of port.
/// @param netPort Handle to net port descriptor.

optNetPortType oprNetPortType (
    optNetPortP netPort
);

/// Return the net port type from the descriptor, as a string.
/// @return The type.
/// @param netPort Handle to net port descriptor.

const char* oprNetPortTypeString (
    optNetPortP netPort
);

/// Read a net's current value .
/// @return Returns the net value.
/// @param net Net.

Uns32 oprNetValue (
    optNetP net
);

/// Read a net's previous value .
/// @return Returns the net value prior to the most recent write.
/// @param net Net.

Uns32 oprNetValuePrevious (
    optNetP net
);

/// Write a value to a net.
/// @return Returns True if anything was triggered by the write.
/// @param net   Net.
/// @param value New value.

Bool oprNetWrite (
    optNetP net,
    Uns32   value
);

/// Get the VLNV spec of this object.
/// @return Pointer to VLNV structure.
/// @param object Object(processor, peripheral, mmc, extension).

optVLNVP oprObjectVLNV (
    optObjectP object
);

/// Write data to a packetnet.
/// @param packetnet Packetnet object.
/// @param data      Data.
/// @param bytes     Number of data bytes to send.

void oprPacketnetWrite (
    optPacketnetP packetnet,
    void*         data,
    Uns32         bytes
);

/// Set the diagnostic level on a peripheral.
/// @param peripheral Peripheral.
/// @param level      New level.

void oprPeripheralDiagnosticLevelSet (
    optPeripheralP peripheral,
    Uns32          level
);

/// Get the next document node from this peripheral.
/// @return Pointer to a document node or null.
/// @param proc Peripheral instance.
/// @param node The current document node or null.

optDocNodeP oprPeripheralDocNodeNext (
    optPeripheralP proc,
    optDocNodeP    node
);

/// Add an application symbol-address mapping to a processor.
/// @param processor Processor instance.
/// @param name      Symbol name.
/// @param value     Symbol address value.
/// @param size      Symbol address size in bytes.
/// @param type      Symbol type (TODO - be more specific).
/// @param binding   Symbol binding (TODO - be more specific).

void oprProcessorApplicationSymbolAdd (
    optProcessorP processor,
    const char *  name,
    Addr          value,
    Addr          size,
    Uns32         type,
    Uns32         binding
);

/// Clear a breakpoint.
/// @param processor Processor element.
/// @param addr      Bus address.

void oprProcessorBreakpointAddrClear (
    optProcessorP processor,
    Addr          addr
);

/// Set a breakpoint.
/// @param processor Processor element.
/// @param addr      Bus address.

void oprProcessorBreakpointAddrSet (
    optProcessorP processor,
    Addr          addr
);

/// Clear an ICount breakpoint.
/// @param processor Processor element.

void oprProcessorBreakpointICountClear (
    optProcessorP processor
);

/// Stop this processor after this many more instructions. Only one ICount
/// breakpoint is allowed.
/// @param processor Processor element.
/// @param delta     After this many instructions from now.

void oprProcessorBreakpointICountSet (
    optProcessorP processor,
    Uns64         delta
);

/// Read data from a bus in the context of a processor.
/// @return True if success.
/// @param processor Processor context.
/// @param bus       Bus to read.
/// @param address   Bus address.
/// @param buffer    Native buffer.
/// @param bytes     Number of bytes.
/// @param debug     True if this should not perturb the platform state.

Bool oprProcessorBusRead (
    optProcessorP processor,
    optBusP       bus,
    Addr          address,
    void*         buffer,
    Uns32         bytes,
    Bool          debug
);

/// Write data to a bus in the context of a processor.
/// @return Success.
/// @param processor Processor context.
/// @param bus       Bus to write.
/// @param address   Bus address.
/// @param buffer    Native buffer.
/// @param bytes     Number of bytes.
/// @param debug     True if this should not perturb the platform state
///                  (other than the memory location).

Bool oprProcessorBusWrite (
    optProcessorP processor,
    optBusP       bus,
    Addr          address,
    const void*   buffer,
    Uns32         bytes,
    Bool          debug
);

/// Return the first child of the passed SMP processor.
/// @return first child.
/// @param processor current processor.

optProcessorP oprProcessorChild (
    optProcessorP processor
);

/// Get the number of instructions and halted instructions executed by the given
/// processor.
/// @return Number of instructions.
/// @param processor Processor element.

Uns64 oprProcessorClocks (
    optProcessorP processor
);

/// Issue the callback on all commands attached to this processor (includes
/// those on extensions).
/// @param processor The processor.
/// @param cb        Command callback.
/// @param userData  User data passed to callback.

void oprProcessorCommandIterAll (
    optProcessorP processor,
    optCommandFn  cb,
    void*         userData
);

/// Next processor command.
/// @return Command descriptor.
/// @param processor Parent processor.
/// @param current   Current command or null.

optCommandP oprProcessorCommandNext (
    optProcessorP processor,
    optCommandP   current
);

/// Return the raw processor data.
/// @return pointer to raw processor data (usually beginning with processor
///         registers).
/// @param processor Processor element.

void * oprProcessorData (
    optProcessorP processor
);

/// Get the semihost library to be used by default with this processor.
/// @return Pointer to semihost library VLNV structure.
/// @param processor Processor instance.

optVLNVP oprProcessorDefaultSemihost (
    optProcessorP processor
);

/// Return a description of this processor.
/// @return Single name indicating this processor's function in the model.
///         e.g. TC, VPE, CPU, CMP.
/// @param processor Handle to this processor.

const char* oprProcessorDescription (
    optProcessorP processor
);

/// Disassemble the instruction at this address, using the given processor
/// model.
/// @return Disassembly string. This must be used before this function is
///         called again.
/// @param processor Processor element.
/// @param addr      Address.

const char * oprProcessorDisassemble (
    optProcessorP processor,
    Addr          addr
);

/// Get the next document node of this processor element.
/// @return Pointer to a document node or null.
/// @param proc Processor instance.
/// @param node The current document node or null.

optDocNodeP oprProcessorDocNodeNext (
    optProcessorP proc,
    optDocNodeP   node
);

/// Get the ELF codes supported by this processor.
/// @return Zero-terminated list of ELF codes supported by this processor.
/// @param processor  Processor instance.
/// @param codes      Array of codes to be filled in by this call.
/// @param maxCodes   Size of the array to be filled.
/// @param defaultElf This is the default processor for this ELF code (no
///                   longer used).

Uns32 oprProcessorElfCodes (
    optProcessorP processor,
    Uns32*        codes,
    Uns32         maxCodes,
    Bool*         defaultElf
);

/// Get the endian supported by this processor.
/// @return Endian supported by this processor.
/// @param processor Processor instance.
/// @param data      Return data endian if true, code endian if false.

optEndian oprProcessorEndian (
    optProcessorP processor,
    Bool          data
);

/// Returns the current processor exception descriptor null if the model does
/// not implement or expose exceptions).
/// @return Exception description.
/// @param processor Processor object.

optExceptionP oprProcessorException (
    optProcessorP processor
);

/// Returns the next processor exception descriptor.
/// @return The next exception.
/// @param processor Processor object.
/// @param exception Previous exception or null to get the first.

optExceptionP oprProcessorExceptionNext (
    optProcessorP processor,
    optExceptionP exception
);

/// Set watchpoint on a processor exception event.
/// @return New watchpoint.
/// @param processor  Processor element.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprProcessorExceptionWatchpointSet (
    optProcessorP  processor,
    void*          userData,
    optRegNotifyFn notifierCB
);

/// Terminate execution of the current processor and return immediately from
/// oprXxxSimulate with optStopReason OPT_SR_EXIT (typically used within read or
/// write callback).
/// @param processor Processor element.

void oprProcessorExit (
    optProcessorP processor
);

/// Get the Family name of this processor.
/// @return Family name of this processor or null if not defined.
/// @param processor Processor instance.

const char * oprProcessorFamily (
    optProcessorP processor
);

/// Get the fault address of the given processor.
/// @return True if there was a fault.
/// @param processor Processing element.
/// @param address   Ptr to address to be updated.

Bool oprProcessorFaultAddress (
    optProcessorP processor,
    Addr*         address
);

/// Add a fetch callback on a processor.
/// @param processor processor.
/// @param loAddr    Lower bound.
/// @param hiAddr    Upper bound.
/// @param rcb       Callback.
/// @param userData  User data returned in the callback.

void oprProcessorFetchCallback (
    optProcessorP processor,
    Addr          loAddr,
    Addr          hiAddr,
    optMemWatchFn rcb,
    void*         userData
);

/// Terminate execution of the current processor and return immediately from
/// oprXxxSimulate with optStopReason OPT_SR_FINISH. Typically used within read
/// or write callback. If there's no current processor, call iExit. The ICM exit
/// handler will tidy up.
/// @param processor Processor element.
/// @param status    Return status.

void oprProcessorFinish (
    optProcessorP processor,
    Int32         status
);

/// Signal that code memory has been changed and that the processor should
/// invalidate cached JIT translations.
/// @param processor processor to flush.
/// @param addrLo    Lower bound.
/// @param addrHi    Upper bound.

void oprProcessorFlush (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi
);

/// This processor will not be scheduled to run any instructions until Unfreeze
/// is called. oprProcessorSimulate will return OPT_SR_FREEZE.
/// @param processor Processor instance.

void oprProcessorFreeze (
    optProcessorP processor
);

/// Indicate if this processor is frozen.
/// @return True if this processor is frozen.
/// @param processor Processor instance.

Bool oprProcessorFrozen (
    optProcessorP processor
);

/// Get any flags required for this GDB.
/// @return GDB Flags.
/// @param processor Processor instance.

const char* oprProcessorGdbFlags (
    optProcessorP processor
);

/// Get the GDB to be used with this processor.
/// @return Path to GDB.
/// @param processor Processor instance.

const char* oprProcessorGdbPath (
    optProcessorP processor
);

/// Get the group name of this processor.
/// @return Group name (more significant) of this processor or null if not
///         defined.
/// @param processor Processor instance.

const char * oprProcessorGroupH (
    optProcessorP processor
);

/// Get the group name of this processor.
/// @return Group name (less significant) of this processor or null if not
///         defined.
/// @param processor Processor instance.

const char * oprProcessorGroupL (
    optProcessorP processor
);

/// Halt execution of the current processor and return immediately from
/// oprXxxxSimulate with icmStopReason SR_HALT (typically used within read or
/// write callback).
/// @param processor Processor element.

void oprProcessorHalt (
    optProcessorP processor
);

/// Get the VLNV spec of the helper for this processor.
/// @return VLNV of processor helper plugin.
/// @param processor Processor instance.

optVLNVP oprProcessorHelper (
    optProcessorP processor
);

/// Get the number of instructions executed by the given processor.
/// @return Number of instructions.
/// @param processor Processor element.

Uns64 oprProcessorICount (
    optProcessorP processor
);

/// Return the index number of the passed SMP processor.
/// @return Unique (within this processor cluster) index number.
/// @param processor current processor.

Uns32 oprProcessorIndex (
    optProcessorP processor
);

/// Get the address of the next whole instruction.
/// @return The next whole instruction.
/// @param processor Processing element.
/// @param pc        The current PC value.

Addr oprProcessorInstructionNext (
    optProcessorP processor,
    Addr          pc
);

/// Return true if the SMP processor is a leaf (it can execute code).
/// @return True if is a leaf.
/// @param processor current processor.

Bool oprProcessorIsLeaf (
    optProcessorP processor
);

/// Apply the callback to the processor and all its descendants.
/// @param processor Processor instance.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void oprProcessorIterAll (
    optProcessorP          processor,
    optProcessorIteratorFn iterCB,
    void*                  userData
);

/// Apply the callback to all children of the processor object.
/// @param processor Processor instance.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void oprProcessorIterChildren (
    optProcessorP          processor,
    optProcessorIteratorFn iterCB,
    void*                  userData
);

/// Apply the callback to all descendants of the processor object.
/// @param processor Processor instance.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void oprProcessorIterDescendants (
    optProcessorP          processor,
    optProcessorIteratorFn iterCB,
    void*                  userData
);

/// Does this processor always require the use of physical addresses?.
/// @return True if physical addresses required (legacy feature).
/// @param processor Processor instance.

Bool oprProcessorLoadPhysical (
    optProcessorP processor
);

/// Returns the current processor mode description (or zero if the model does
/// not implement or expose modes).
/// @return Current mode.
/// @param processor Processing element.

optModeP oprProcessorMode (
    optProcessorP processor
);

/// Returns the next processor mode descriptor.
/// @return Next mode description.
/// @param processor Processor object.
/// @param mode      Previous mode description, or null to get the first.

optModeP oprProcessorModeNext (
    optProcessorP processor,
    optModeP      mode
);

/// Set watchpoint on a processor mode change.
/// @return New watchpoint.
/// @param processor  Processor element.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprProcessorModeWatchpointSet (
    optProcessorP  processor,
    void*          userData,
    optRegNotifyFn notifierCB
);

/// Return the name of the processor.
/// @return Name of the processor (which can change).
/// @param processor The processor.

const char * oprProcessorName (
    optProcessorP processor
);

/// Get the current PC of a processor.
/// @return The current PC.
/// @param processor Processing element.

Addr oprProcessorPC (
    optProcessorP processor
);

/// Get the current PC and the delay slot offset.
/// @return Current PC value.
/// @param processor Processing element.
/// @param delay     Pointer to delay slot offset.

Addr oprProcessorPCDS (
    optProcessorP processor,
    Uns8*         delay
);

/// Is the current PC in a delay slot?.
/// @return True if in a delay slot.
/// @param processor Processing element.

Bool oprProcessorPCInDS (
    optProcessorP processor
);

/// Set the current PC of a processor.
/// @param processor Processing element.
/// @param addr      New PC value.

void oprProcessorPCSet (
    optProcessorP processor,
    Addr          addr
);

/// Return the parent of the passed SMP processor.
/// @return SMP parent.
/// @param processor The processor object.

optProcessorP oprProcessorParent (
    optProcessorP processor
);

/// Return the previous sibling of the passed SMP processor.
/// @return previous siblin.
/// @param processor Processor instance.

optProcessorP oprProcessorPrev (
    optProcessorP processor
);

/// Does this processor support QuantumLeap mode?.
/// @return True if this processor supports QuantumLeap.
/// @param processor Processor instance.

Bool oprProcessorQLQualified (
    optProcessorP processor
);

/// Read memory (through the processor's TLB).
/// @return True if successful.
/// @param processor   Processor element.
/// @param simAddress  Processor virtual address.
/// @param buffer      Pointer to location of data.
/// @param bytes       Number of bytes to read.
/// @param debugAccess True if artifact access.

Bool oprProcessorRead (
    optProcessorP processor,
    Addr          simAddress,
    void*         buffer,
    Uns32         bytes,
    Bool          debugAccess
);

/// Abort the current read access. Used in memory read callback.
/// @param processor Processing element, or null if no current processor.
/// @param addr      The address that failed.

void oprProcessorReadAbort (
    optProcessorP processor,
    Addr          addr
);

/// Add a read callback on a processor.
/// @param processor processor.
/// @param loAddr    Lower bound.
/// @param hiAddr    Upper bound.
/// @param rcb       Callback.
/// @param userData  User data returned in the callback.

void oprProcessorReadCallback (
    optProcessorP processor,
    Addr          loAddr,
    Addr          hiAddr,
    optMemWatchFn rcb,
    void*         userData
);

/// Find a register from a processor by index.
/// @return Processor register.
/// @param processor Processing element.
/// @param index     The required index.

optRegP oprProcessorRegByIndex (
    optProcessorP processor,
    Uns32         index
);

/// Find a register from a processor by name.
/// @return Processor register.
/// @param processor Processing element.
/// @param name      The required name.

optRegP oprProcessorRegByName (
    optProcessorP processor,
    const char *  name
);

/// Find a register from a processor by usage.
/// @return Processor register.
/// @param processor Processing element.
/// @param usage     The required usage.

optRegP oprProcessorRegByUsage (
    optProcessorP processor,
    optRegUsage   usage
);

/// Find a processor register group by name.
/// @return Register group or null.
/// @param processor Processing element.
/// @param name      The group name.

optRegGroupP oprProcessorRegGroupByName (
    optProcessorP processor,
    const char*   name
);

/// Get the next group of processor registers from a processor.
/// @return Next register group or null.
/// @param processor Processing element.
/// @param group     current group or null.

optRegGroupP oprProcessorRegGroupNext (
    optProcessorP processor,
    optRegGroupP  group
);

/// Get the next register from a processor.
/// @return Processor register.
/// @param processor Processing element.
/// @param reg       The current register or null.

optRegP oprProcessorRegNext (
    optProcessorP processor,
    optRegP       reg
);

/// Read a register.
/// @return True if read was successful.
/// @param processor Processing element.
/// @param name      Name of register.
/// @param buffer    Data.

Bool oprProcessorRegRead (
    optProcessorP processor,
    const char *  name,
    void *        buffer
);

/// Dump all the registers of the processor to the text output stream.
/// @return New watchpoint.
/// @param processor  Processing element.
/// @param reg        The register.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprProcessorRegWatchpointSet (
    optProcessorP  processor,
    optRegP        reg,
    void*          userData,
    optRegNotifyFn notifierCB
);

/// Write a register.
/// @return True if write was successful.
/// @param processor Processing element.
/// @param name      Name of register.
/// @param buffer    Data.

Bool oprProcessorRegWrite (
    optProcessorP processor,
    const char *  name,
    const void *  buffer
);

/// Dump all the registers of the processor to the text output stream.
/// @param processor Processing element.

void oprProcessorRegisterDump (
    optProcessorP processor
);

/// Return the next sibling of the passed SMP processor.
/// @return next sibling.
/// @param processor current processor.

optProcessorP oprProcessorSiblingNext (
    optProcessorP processor
);

/// Simulate a number of instructions on a processor. Depending on the type of
/// processor, one of more of the processors might be advanced by this command.
/// @return The reason for stopping.
/// @param processor    Processor instance.
/// @param instructions Number of instructions.

optStopReason oprProcessorSimulate (
    optProcessorP processor,
    Uns64         instructions
);

/// Restore the state of the given processor.
/// @return Success or failure.
/// @param processor The processor to restore.
/// @param cb        The function used to restore data.
/// @param userData  User context, passed back in the callback.

optSaveRestoreStatus oprProcessorStateRestore (
    optProcessorP processor,
    optRestoreFn  cb,
    void *        userData
);

/// Restore the state of the given processor from a file.
/// @return Success or failure.
/// @param processor The processor to restore.
/// @param file      The file.

optSaveRestoreStatus oprProcessorStateRestoreFile (
    optProcessorP processor,
    const char *  file
);

/// Save the state of the given processor.
/// @return Success or failure.
/// @param processor The processor to save.
/// @param cb        The function used to save data.
/// @param userData  User context, passed back in the callback.

optSaveRestoreStatus oprProcessorStateSave (
    optProcessorP processor,
    optSaveFn     cb,
    void *        userData
);

/// Save the state of the given processor to a file.
/// @return Success or failure.
/// @param processor The processor to save.
/// @param file      The file.

optSaveRestoreStatus oprProcessorStateSaveFile (
    optProcessorP processor,
    const char *  file
);

/// Get the stop reason for the given processor.
/// @return Stop reason.
/// @param processor Processor element.

optStopReason oprProcessorStopReason (
    optProcessorP processor
);

/// Disable the processor trace buffer.
/// @param processor processor instance.

void oprProcessorTraceBufferDisable (
    optProcessorP processor
);

/// Dump the processor trace buffer to the text output stream (if it was
/// enabled).
/// @param processor processor instance.

void oprProcessorTraceBufferDump (
    optProcessorP processor
);

/// Enable the processor trace buffer.
/// @param processor processor instance.

void oprProcessorTraceBufferEnable (
    optProcessorP processor
);

/// Turn off processor tracing.
/// @param processor processor instance.
/// @param delta     The action happens after this many more instructions.

void oprProcessorTraceOffAfter (
    optProcessorP processor,
    Uns64         delta
);

/// Turn on processor tracing.
/// @param processor processor instance.
/// @param delta     The action happens after this many more instructions.

void oprProcessorTraceOnAfter (
    optProcessorP processor,
    Uns64         delta
);

/// This processor will be scheduled normally.
/// @param processor Processor instance.

void oprProcessorUnfreeze (
    optProcessorP processor
);

/// Get the current variant.
/// @return Variant name of this processor or null if not defined.
/// @param processor Processor instance.

const char * oprProcessorVariant (
    optProcessorP processor
);

/// Set a watchpoint on a processor access.
/// @return New watchpoint.
/// @param processor  Processor element.
/// @param physical   Use physical addresses.
/// @param addrLo     lower bound.
/// @param addrHi     upper bound.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprProcessorWatchpointAccessSet (
    optProcessorP  processor,
    Bool           physical,
    Addr           addrLo,
    Addr           addrHi,
    void*          userData,
    optMemNotifyFn notifierCB
);

/// Set a watchpoint on a processor read access.
/// @return New watchpoint.
/// @param processor  Processor element.
/// @param physical   Use physical addresses.
/// @param addrLo     lower bound.
/// @param addrHi     upper bound.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprProcessorWatchpointReadSet (
    optProcessorP  processor,
    Bool           physical,
    Addr           addrLo,
    Addr           addrHi,
    void*          userData,
    optMemNotifyFn notifierCB
);

/// Set a watchpoint on a processor write access.
/// @return New watchpoint.
/// @param processor  Processor element.
/// @param physical   Use physical addresses.
/// @param addrLo     lower bound.
/// @param addrHi     upper bound.
/// @param userData   Pointer available in the watchpoint.
/// @param notifierCB Notifier function.

optWatchpointP oprProcessorWatchpointWriteSet (
    optProcessorP  processor,
    Bool           physical,
    Addr           addrLo,
    Addr           addrHi,
    void*          userData,
    optMemNotifyFn notifierCB
);

/// Write memory (through the processor's TLB).
/// @return True if successful.
/// @param processor   Processor element.
/// @param simAddress  Processor virtual address.
/// @param buffer      Pointer to location of data.
/// @param bytes       Number of bytes to write.
/// @param debugAccess True if artifact access.

Bool oprProcessorWrite (
    optProcessorP processor,
    Addr          simAddress,
    const void*   buffer,
    Uns32         bytes,
    Bool          debugAccess
);

/// Abort the current write access. Used in memory write callback.
/// @param processor Processing element, or null if no current processor.
/// @param addr      The address that failed.

void oprProcessorWriteAbort (
    optProcessorP processor,
    Addr          addr
);

/// Add a write callback on a processor.
/// @param processor processor.
/// @param loAddr    Lower bound.
/// @param hiAddr    Upper bound.
/// @param rcb       Callback.
/// @param userData  User data returned in the callback.

void oprProcessorWriteCallback (
    optProcessorP processor,
    Addr          loAddr,
    Addr          hiAddr,
    optMemWatchFn rcb,
    void*         userData
);

/// Suspend execution of the current processor and return immediately from
/// oprXxxSimulate with optStopReason OPT_SR_YIELD (typically used within read
/// or write callback).
/// @param processor Processor element.

void oprProcessorYield (
    optProcessorP processor
);

/// Get the access mode enumeration of a processor register.
/// @return Access mode of the processor register.
/// @param reg Processor register.

optRegAccess oprRegAccessEnum (
    optRegP reg
);

/// Get the access mode of a processor register as a string.
/// @return Usage of the processor register.
/// @param reg Processor register.

const char * oprRegAccessString (
    optRegP reg
);

/// Get the number of bits in a processor register.
/// @return Bit-width of the processor register.
/// @param reg Processor register.

Uns32 oprRegBits (
    optRegP reg
);

/// Get a description of the processor register.
/// @return Description of the processor register.
/// @param reg Processor register.

const char * oprRegDescription (
    optRegP reg
);

/// Get the GDB index of the processor register.
/// @return The GDB index.
/// @param reg Processor register.

Uns32 oprRegGdbIndex (
    optRegP reg
);

/// Get the group that contains the processor register.
/// @return Processor register group.
/// @param reg Processor register.

optRegGroupP oprRegGroup (
    optRegP reg
);

/// Get name of a processor register group.
/// @return Name of register group.
/// @param group Processor register group.

const char * oprRegGroupName (
    optRegGroupP group
);

/// Find the next processor register in this group.
/// @return Processor register.
/// @param processor Processing element.
/// @param group     Processor register group.
/// @param reg       The current processor register.

optRegP oprRegGroupRegNext (
    optProcessorP processor,
    optRegGroupP  group,
    optRegP       reg
);

/// Get name of a processor register.
/// @return The name of the register.
/// @param reg Processor register.

const char * oprRegName (
    optRegP reg
);

/// Read a processor register.
/// @return True if read was successful.
/// @param processor Processing element.
/// @param reg       Processor register.
/// @param buffer    Data.

Bool oprRegRead (
    optProcessorP processor,
    optRegP       reg,
    void *        buffer
);

/// Is this processor register read-only.
/// @return True if processor register is read-only.
/// @param reg Processor register.

Bool oprRegReadOnly (
    optRegP reg
);

/// Get the usage enumeration of a processor register.
/// @return Usage of the processor register.
/// @param reg Processor register.

optRegUsage oprRegUsageEnum (
    optRegP reg
);

/// Get the usage of a processor register as a string.
/// @return Access mode of the processor register.
/// @param reg Processor register.

const char * oprRegUsageString (
    optRegP reg
);

/// Write a processor register.
/// @return True if write was successful.
/// @param processor Processing element.
/// @param reg       Processor register.
/// @param buffer    Data.

Bool oprRegWrite (
    optProcessorP processor,
    optRegP       reg,
    const void *  buffer
);

/// Copy an complete design (during simulation).
/// @return The new copied module hierarchy, ready to simulate.
/// @param module Parent module.

optModuleP oprRootModuleSimulationCopy (
    optModuleP module
);

/// Get the stop reason for the given processor.
/// @return The stop reason as a string.
/// @param stopReason Stop Reason as a code.

const char * oprStopReasonString (
    optStopReason stopReason
);

/// Return the 'library' part of the VLNV.
/// @return Pointer to text.
/// @param vlnv Document node.

const char * oprVLNVLibrary (
    optVLNVP vlnv
);

/// Return the 'name' part of the VLNV.
/// @return Pointer to text.
/// @param vlnv Document node.

const char * oprVLNVName (
    optVLNVP vlnv
);

/// Return the 'vendor' part of the VLNV.
/// @return Pointer to text.
/// @param vlnv Document node.

const char * oprVLNVVendor (
    optVLNVP vlnv
);

/// Return the 'version' part of the VLNV.
/// @return Pointer to text.
/// @param vlnv Document node.

const char * oprVLNVVersion (
    optVLNVP vlnv
);

/// Return the upper bound of a watchpoint region.
/// @return Upper bound of a watchpoint region.
/// @param watchpoint The watchpoint.

Addr oprWatchpointAddressHi (
    optWatchpointP watchpoint
);

/// Return the lower bound of a watchpoint region.
/// @return Lower bound of a watchpoint region.
/// @param watchpoint The watchpoint.

Addr oprWatchpointAddressLo (
    optWatchpointP watchpoint
);

/// Return a pointer to the register's current value.
/// @return Pointer to previous value data.
/// @param watchpoint The current watchpoint.

void* oprWatchpointCurrentValue (
    optWatchpointP watchpoint
);

/// Delete a watchpoint.
/// @param watchpoint The watchpoint.

void oprWatchpointDelete (
    optWatchpointP watchpoint
);

/// Return a pointer to the register's previous value.
/// @return Pointer to previous value data.
/// @param watchpoint The current watchpoint.

void* oprWatchpointPreviousValue (
    optWatchpointP watchpoint
);

/// Return the register that changed.
/// @return The register that changed.
/// @param watchpoint The current watchpoint.

optRegP oprWatchpointRegister (
    optWatchpointP watchpoint
);

/// Reset a watchpoint.
/// @param watchpoint The current watchpoint.

void oprWatchpointReset (
    optWatchpointP watchpoint
);

/// Find which processor triggered this watchpoint (i.e. was executing at the
/// time).
/// @return The processor element that triggered the watchpoint.
/// @param watchpoint The current watchpoint.

optProcessorP oprWatchpointTriggeredBy (
    optWatchpointP watchpoint
);

/// Find the type of this watchpoint.
/// @return The type of the watchpoint.
/// @param watchpoint The current watchpoint.

optWatchpointType oprWatchpointTypeEnum (
    optWatchpointP watchpoint
);

/// Return the user data of this watchpoint.
/// @return User data passed when the watchpoint was created.
/// @param watchpoint The current watchpoint.

void* oprWatchpointUserData (
    optWatchpointP watchpoint
);


#endif /* OPRRUNTIME_H */

