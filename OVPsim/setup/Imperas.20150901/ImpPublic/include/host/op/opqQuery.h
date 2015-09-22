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


#ifndef OPQQUERY_H
#define OPQQUERY_H

#include "optTypes.h"

/// Get the next bridge instance in a module.
/// @return The next bridge.
/// @param module Module containing the bus.
/// @param bridge Current bridge or null.

optBridgeP opqBridgeNext (
    optModuleP module,
    optBridgeP bridge
);

/// Get the number of address bits used on this bus.
/// @return The number of bits used to represent an address.
/// @param bus The bus instance.

Uns32 opqBusAddrBits (
    optBusP bus
);

/// Get the next application loaded onto this bus.
/// @return The list of applications.
/// @param bus The bus instance.
/// @param app Current application or null.

optApplicationP opqBusApplicationNext (
    optBusP         bus,
    optApplicationP app
);

/// Find a bus by its name.
/// @return The bus instance.
/// @param module Module containing the bus.
/// @param name   Name of the bus to find.

optBusP opqBusByName (
    optModuleP   module,
    const char * name
);

/// Get the pseudo port name of a callback.
/// @return The bus callback upper bound.
/// @param callback Current callback object.

Addr opqBusCallbackAddrHi (
    optBusCallbackP callback
);

/// Get the pseudo port name of a callback.
/// @return The bus callback lower bounds.
/// @param callback Current callback object.

Addr opqBusCallbackAddrLo (
    optBusCallbackP callback
);

/// Get the next callback installed on this bus.
/// @return The bus callback object.
/// @param bus      The bus.
/// @param callback Current callback object.

optBusCallbackP opqBusCallbackNext (
    optBusP         bus,
    optBusCallbackP callback
);

/// Return the next bus in this module.
/// @return Bus.
/// @param module Module instance.
/// @param bus    The current bus instance or null.

optBusP opqBusNext (
    optModuleP module,
    optBusP    bus
);

/// Return the upper address bound from a bus port connection.
/// @return Upper bound.
/// @param busPortConn The bus port connection.

Addr opqBusPortConnAddrHi (
    optBusPortConnP busPortConn
);

/// Return the lower address bound from a bus port connection.
/// @return Lower bound.
/// @param list The bus port connection.

Addr opqBusPortConnAddrLo (
    optBusPortConnP list
);

/// Return the connected bus.
/// @return The bus connected to this BPC.
/// @param busPortConn Bus port connection.

optBusP opqBusPortConnBus (
    optBusPortConnP busPortConn
);

/// Return the next Bus port connection for this bus.
/// @return The next Bus port connection.
/// @param bus         Bus.
/// @param busPortConn Current port connection or null.

optBusPortConnP opqBusPortConnNext (
    optBusP         bus,
    optBusPortConnP busPortConn
);

/// Return the next memory mapped register (slave port only).
/// @return Next register or null.
/// @param busPort The bus port descriptor.
/// @param prev    The previous register descriptor or null.

optMMRegisterP opqBusPortMMRegisterNext (
    optBusPortP    busPort,
    optMMRegisterP prev
);

/// Display bus connections.
/// @param bus Bus to show.

void opqBusShow (
    optBusP bus
);

/// Display all model commands.
/// @param module Root of hierarchy to show, or null for all.

void opqCommandsShow (
    optModuleP module
);

/// Find name FIFO instance by name.
/// @return The FIFO instance or null.
/// @param module Module instance.
/// @param name   Name of the FIFO instance to find.

optFIFOP opqFIFOByName (
    optModuleP  module,
    const char* name
);

/// Get the depth of a FIFO (in words).
/// @return The name.
/// @param fifo FIFO instance.

Uns32 opqFIFODepth (
    optFIFOP fifo
);

/// Return the next FIFO instance.
/// @return FIFO list.
/// @param module Module instance.
/// @param fifo   The current FIFO or null.

optFIFOP opqFIFONext (
    optModuleP module,
    optFIFOP   fifo
);

/// Return the next FIFO port connection from this FIFO.
/// @return The next FIFO port connection.
/// @param fifo         FIFO.
/// @param fifoPortConn Current port connection or null.

optFIFOPortConnP opqFIFOPortConnNext (
    optFIFOP         fifo,
    optFIFOPortConnP fifoPortConn
);

/// Return the width of the FIFO port connection.
/// @return The width of one word in bits.
/// @param fifoPortConn Current FIFO port connection.

Uns32 opqFIFOPortConnWidth (
    optFIFOPortConnP fifoPortConn
);

/// Display all elaborated formal parameters (overrides).
/// @param module Root of hierarchy to show, or null for all.
/// @param class  Choose to show system, model or all.

void opqFormalsShow (
    optModuleP    module,
    optParamClass class
);

/// Return an MMC instance.
/// @return MMC or null.
/// @param module Module instance.
/// @param name   MMC name.

optMMCP opqMMCByName (
    optModuleP   module,
    const char * name
);

/// Return next MMC instance.
/// @return Next MMC instance in this module.
/// @param module Module instance.
/// @param mmc    The current MMC instance or null.

optMMCP opqMMCNext (
    optModuleP module,
    optMMCP    mmc
);

/// Return the memory mapped register width in bits.
/// @return Width of register in bits.
/// @param mmr The register descriptor.

Uns32 opqMMRegisterBits (
    optMMRegisterP mmr
);

/// Return the memory mapped register description.
/// @return Description of register.
/// @param mmr The register descriptor.

const char * opqMMRegisterDescription (
    optMMRegisterP mmr
);

/// Return the memory mapped register name.
/// @return Name of register.
/// @param mmr The register descriptor.

const char * opqMMRegisterName (
    optMMRegisterP mmr
);

/// Return the memory mapped register offset.
/// @return Offset of register in bytes from the base of the bus port.
/// @param mmr The register descriptor.

Addr opqMMRegisterOffset (
    optMMRegisterP mmr
);

/// Return next application loaded onto this bus.
/// @return The next application or null.
/// @param memory Memory instance.
/// @param app    Current application or null.

optApplicationP opqMemoryApplicationNext (
    optMemoryP      memory,
    optApplicationP app
);

/// Return the next memory instance.
/// @return The next instance or null.
/// @param memory Module instance.
/// @param name   memory name.

optMemoryP opqMemoryByName (
    optModuleP   memory,
    const char * name
);

/// Return the memory's maximum (byte) address.
/// @return The maximum address of this memory instance.
/// @param memory Memory.

Addr opqMemoryMaxAddress (
    optMemoryP memory
);

/// Return the next memory instance.
/// @return The next instance or null.
/// @param module Module instance.
/// @param memory The current memory instance or null.

optMemoryP opqMemoryNext (
    optModuleP module,
    optMemoryP memory
);

/// Display all bus connections in a module.
/// @param module Module containing buses.

void opqModuleBusShow (
    optModuleP module
);

/// Return a module instance by name.
/// @return The module.
/// @param module Module instance.
/// @param name   Module name.

optModuleP opqModuleByName (
    optModuleP   module,
    const char * name
);

/// Return the next module documentation node.
/// @return The next documentation node.
/// @param module  Module instance.
/// @param docNode The current node or null.

optDocNodeP opqModuleDocNodeNext (
    optModuleP  module,
    optDocNodeP docNode
);

/// Return the next module extension.
/// @return Next extension.
/// @param module    Module instance.
/// @param extension The current extension or null.

optExtensionP opqModuleExtensionNext (
    optModuleP    module,
    optExtensionP extension
);

/// Return the next child module instance in this parent module.
/// @return Module list.
/// @param parent Parent module instance.
/// @param module Current child module instance or null.

optModuleP opqModuleNext (
    optModuleP parent,
    optModuleP module
);

/// Return the module object (persistent data).
/// @return The object.
/// @param module Module.

optModuleObjectP opqModuleObject (
    optModuleP module
);

/// Find any object by hierarchical name.
/// @return Platform object of any type.
/// @param module Root of search.
/// @param name   Hierarchical name.
/// @param mask   Mask of types to find.

optObjectP opqModuleObjectByHierName (
    optModuleP  module,
    const char* name,
    optStrType  mask
);

/// Return the path to file implementing this module.
/// @return Cannonical path to module object.
/// @param module Module.

const char * opqModulePath (
    optModuleP module
);

/// Return the purpose of this module.
/// @return Purpose (this may be used by packaging tools).
/// @param module Module.

optPurpose opqModulePurpose (
    optModuleP module
);

/// Display all modules.
/// @param module Root of hierarchy to show, or null for all.

void opqModuleShow (
    optModuleP module
);

/// Find a net instance by name.
/// @return The net instance or null.
/// @param module Module instance.
/// @param name   Name of the net to find.

optNetP opqNetByName (
    optModuleP  module,
    const char* name
);

/// Return the next net in this module.
/// @return The next net or null.
/// @param module Module instance.
/// @param net    The current net or null.

optNetP opqNetNext (
    optModuleP module,
    optNetP    net
);

/// Return the net connected to a net port connection.
/// @return The net.
/// @param netPort The current net port connection.

optNetP opqNetPortConnNet (
    optNetPortConnP netPort
);

/// Return the next net port connection on this net.
/// @return The next net port connection, or null.
/// @param net         The net.
/// @param netPortConn The current net port connection or null.

optNetPortConnP opqNetPortConnNext (
    optNetP         net,
    optNetPortConnP netPortConn
);

/// Print information about this net.
/// @param net The current net.

void opqNetShow (
    optNetP net
);

/// Find a bus port descriptor by name.
/// @return The next bus port descriptor or null.
/// @param processor Processor instance.
/// @param name      The bus port name.

optBusPortP opqObjectBusPortByName (
    optProcessorP processor,
    const char *  name
);

/// Get next bus port connection.
/// @return The the next bus port connection or null.
/// @param object Any structural object in a platform.
/// @param name   Bus port connnection name.

optBusPortConnP opqObjectBusPortConnByName (
    optObjectP   object,
    const char * name
);

/// Get next bus port connection.
/// @return The the next bus port connection or null.
/// @param object      Any structural object in a platform.
/// @param busPortConn Current bus port connnection or null.

optBusPortConnP opqObjectBusPortConnNext (
    optObjectP      object,
    optBusPortConnP busPortConn
);

/// Get the next bus port definition.
/// @return The next bus port definition or null.
/// @param object  Any structural object in a platform.
/// @param busPort Current bus port or null.

optBusPortP opqObjectBusPortNext (
    optObjectP  object,
    optBusPortP busPort
);

/// Find a command by name (in a processor or extension).
/// @return The command object or null.
/// @param object Object holding the command.
/// @param name   Command name.

optCommandP opqObjectCommandByName (
    optObjectP   object,
    const char * name
);

/// Return an extension elaborated instance by name.
/// @return The elaborated extension or null.
/// @param object Object that can contain an elaborated extension.
/// @param name   Extension name.

optExtElabP opqObjectExtElabByName (
    optObjectP   object,
    const char * name
);

/// Return an extension instance by name.
/// @return The extension instance.
/// @param object Instance containing an extension library definition.
/// @param name   extension name.

optExtensionP opqObjectExtensionByName (
    optObjectP   object,
    const char * name
);

/// Find a FIFO port definition by name.
/// @return The required FIFO port definition or null.
/// @param object Any structural object in a platform.
/// @param name   Name of the required FIFO port definition.

optFIFOPortP opqObjectFIFOPortByName (
    optObjectP   object,
    const char * name
);

/// Find a FIFO port connection by name.
/// @return The required FIFO port connection or null.
/// @param object Any structural object in a platform.
/// @param name   Name of the required FIFO port connection.

optFIFOPortConnP opqObjectFIFOPortConnByName (
    optObjectP   object,
    const char * name
);

/// Get the next FIFO port connection.
/// @return The next FIFO port connection or null.
/// @param object       Any structural object in a platform.
/// @param FIFOPortConn Current FIFO port connnection or null.

optFIFOPortConnP opqObjectFIFOPortConnNext (
    optObjectP       object,
    optFIFOPortConnP FIFOPortConn
);

/// Get the next FIFO port definition.
/// @return The next FIFO port definition or null.
/// @param object   Any structural object in a platform.
/// @param FIFOPort Current FIFO port or null.

optFIFOPortP opqObjectFIFOPortNext (
    optObjectP   object,
    optFIFOPortP FIFOPort
);

/// find a formal formal parameter by name.
/// @return The required formal parameter or null.
/// @param object Any structural object in a platform.
/// @param name   Name of the required formal parameter.

optFormalP opqObjectFormalByName (
    optObjectP   object,
    const char * name
);

/// Get the next formal parameter.
/// @return The next formal parameter or null.
/// @param object Any structural object in a platform.
/// @param formal Current formal parameter or null.
/// @param clss   Class: system, model or all.

optFormalP opqObjectFormalNext (
    optObjectP    object,
    optFormalP    formal,
    optParamClass clss
);

/// Get the hierarchical name of any platform object.
/// @return The hierarchical name, if one can be created. The string is
///         volatile.
/// @param object A platform object.

const char* opqObjectHierName (
    optObjectP object
);

/// Get the module immediately containing this object.
/// @return The parent module.
/// @param object Any structural object in a platform.

optModuleP opqObjectModule (
    optObjectP object
);

/// Get the local name of any platform object.
/// @return The, if one can be created. The string is static.
/// @param object A platform object.

const char* opqObjectName (
    optObjectP object
);

/// Find a net port definition by name.
/// @return The required net port definition or null.
/// @param object Any structural object in a platform.
/// @param name   Name of the required net port definition.

optNetPortP opqObjectNetPortByName (
    optObjectP   object,
    const char * name
);

/// Find a net port connection by name.
/// @return The required net port connection or null.
/// @param object Any structural object in a platform.
/// @param name   Name of the required net port connection.

optNetPortConnP opqObjectNetPortConnByName (
    optObjectP   object,
    const char * name
);

/// Get the next net port connection.
/// @return The next net port connection or null.
/// @param object      Any structural object in a platform.
/// @param netPortConn Current net port connnection or null.

optNetPortConnP opqObjectNetPortConnNext (
    optObjectP      object,
    optNetPortConnP netPortConn
);

/// Get the next net port definition.
/// @return The next net port definition or null.
/// @param object  Any structural object in a platform.
/// @param netPort Current net port definition or null.

optNetPortP opqObjectNetPortNext (
    optObjectP  object,
    optNetPortP netPort
);

/// Find a packetnet port connection by name.
/// @return The required packetnet port connection or null.
/// @param object Any structural object in a platform.
/// @param name   Name of the required packetnet port connection.

optPacketnetPortConnP opqObjectPacketnetPortConnByName (
    optObjectP   object,
    const char * name
);

/// Get the next packetnet port connection.
/// @return The next packetnet port connection or null.
/// @param object            Peripheral or module.
/// @param packetnetPortConn Current packetnet port connnection or null.

optPacketnetPortConnP opqObjectPacketnetPortConnNext (
    optObjectP            object,
    optPacketnetPortConnP packetnetPortConn
);

/// Return the next bus port description.
/// @return Pointer to net port info.
/// @param object  Object handle (peripheral or module).
/// @param netPort Handle to previous packetnet port or null.

optPacketnetPortP opqObjectPacketnetPortNext (
    optObjectP        object,
    optPacketnetPortP netPort
);

/// Get a parameter value as a boolean.
/// @return Value.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

Bool opqObjectParamBoolValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Find a parameter by name.
/// @return The required parameter or null.
/// @param object Any structural object in a platform.
/// @param name   Name of required parameter.

optParamP opqObjectParamByName (
    optObjectP  object,
    const char* name
);

/// Get an parameter value as a double precision float (will attempt a
/// conversion).
/// @return The value.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

double opqObjectParamDoubleValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get the value of an endian parameter.
/// @return The endian enumeration.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

optEndian opqObjectParamEndianValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get an parameter value as an enum (non-zero integer, will attempt a
/// conversion).
/// @return The enum value as an Uns32.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

Uns32 opqObjectParamEnumValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get an parameter value as an Int32 (will attempt a conversion).
/// @return The value as an Int32.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

Int32 opqObjectParamInt32Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get the next parameter.
/// @return The next parameter or null.
/// @param object Any structural object in a platform.
/// @param param  Current parameter or null.

optParamP opqObjectParamNext (
    optObjectP object,
    optParamP  param
);

/// Get an parameter value as a pointer.
/// @return The value.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

void* opqObjectParamPtrValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get an parameter value as a string (will convert when possible).
/// @return The value as a string (the string must be used or copied).
/// @param object The object with the parameter.
/// @param name   The parameter name.

const char * opqObjectParamStringValue (
    optObjectP   object,
    const char * name
);

/// Get an parameter value as an Uns32 (will attempt a conversion).
/// @return The value as an Uns32.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

Uns32 opqObjectParamUns32Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get an parameter value as an Uns64 (will attempt a conversion).
/// @return The value as an Uns64.
/// @param object The object with the parameter.
/// @param name   The parameter name.
/// @param set    Set if the parameter is valid.

Uns64 opqObjectParamUns64Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Get the parent of the given object.
/// @return The parent object.
/// @param object The current object.

optObjectP opqObjectParent (
    optObjectP object
);

/// Return the release status of the given object.
/// @return Current release status (may be used by packaging and
///         documentation tools).
/// @param object Object handle (peripheral or module).

optReleaseStatus opqObjectReleaseStatus (
    optObjectP object
);

/// Get the root module containing this object.
/// @return The root module.
/// @param object Any structural object in a platform.

optModuleP opqObjectRootModule (
    optObjectP object
);

/// Return true if this object supports save/restore.
/// @return true if this model supports save/restore, False if not or if this
///         is not applicable.
/// @param object An object.

Bool opqObjectSaveRestoreSupported (
    optObjectP object
);

/// Get the current simulator phase of this object.
/// @return The current phase of the platform.
/// @param object Any structural object in a platform.

optSimulatorPhase opqObjectSimulatorPhase (
    optObjectP object
);

/// Get the current simulator phase of this object as a string.
/// @return The current phase of the platform.
/// @param object Any structural object in a platform.

const char* opqObjectSimulatorPhaseString (
    optObjectP object
);

/// Get the type of an unknown object.
/// @return The type of an unknown object.
/// @param object Any structural object in a platform.

optStrType opqObjectType (
    optObjectP object
);

/// Return the visibility of this object. Objects that do not support this
/// feature will be reported as visible.
/// @return The visibility (enum).
/// @param object An object.

optVisibility opqObjectVisibility (
    optObjectP object
);

/// Get the max bytes supported by a packetnet.
/// @return Maximum number of bytes or zero.
/// @param packetnet A packetnet handle.

Uns32 opqPacketnetMaxBytes (
    optPacketnetP packetnet
);

/// Get the packetnet connected to a packetnet port connection.
/// @return The packetnet or null.
/// @param packetnetPortConn Current packetnet port connnection or null.

optPacketnetP opqPacketnetPortConnPacketnet (
    optPacketnetPortConnP packetnetPortConn
);

/// Get the description of a packetnet port definition.
/// @return Short text description.
/// @param packetnet A packetnet port handle.

const char * opqPacketnetPortDescription (
    optPacketnetPortP packetnet
);

/// Get the description of a packetnet port definition.
/// @return True if this packetnet port must be connected.
/// @param packetnet A packetnet port handle.

Bool opqPacketnetPortMustBeConnected (
    optPacketnetPortP packetnet
);

/// Get the name of a packetnet port.
/// @return Name of the packetnet port.
/// @param packetnet A packetnet port handle.

const char * opqPacketnetPortName (
    optPacketnetPortP packetnet
);

/// Get an parameter value as a pointer.
/// @return The value.
/// @param param The parameter.

void* opqParamPtrValue (
    optParamP param
);

/// Return the parameter type from the actual parameter.
/// @return The type.
/// @param param The actual parameter.

optParamType opqParamTypeEnum (
    optParamP param
);

/// Return the formal parameter type from the descriptor as a string.
/// @return The type.
/// @param param The actual parameter.

const char* opqParamTypeString (
    optParamP param
);

/// Return a peripheral instance by name.
/// @return The instance.
/// @param module Module instance.
/// @param name   Processor name.

optPeripheralP opqPeripheralByName (
    optModuleP   module,
    const char * name
);

/// Return next extension instance.
/// @return The next extension.
/// @param peripheral peripheral instance.
/// @param extension  extension.

optExtensionP opqPeripheralExtensionNext (
    optPeripheralP peripheral,
    optExtensionP  extension
);

/// Return the next peripheral instance.
/// @return The instance or null.
/// @param module  Module instance.
/// @param current The current peripheral instance or null.

optPeripheralP opqPeripheralNext (
    optModuleP     module,
    optPeripheralP current
);

/// Return the next processor application.
/// @return Next application.
/// @param processor Processor instance.
/// @param app       The current application or null.

optApplicationP opqProcessorApplicationNext (
    optProcessorP   processor,
    optApplicationP app
);

/// Return a processor instance by name.
/// @return The name.
/// @param module Module instance.
/// @param name   Processor name.

optProcessorP opqProcessorByName (
    optModuleP   module,
    const char * name
);

/// Get the next extension from a processor instance.
/// @return The next extension or null.
/// @param processor Processor instance.
/// @param extension The current extension or null.

optExtensionP opqProcessorExtensionNext (
    optProcessorP processor,
    optExtensionP extension
);

/// find a FIFO port by name on a processor instance.
/// @return The next FIFO port.
/// @param processor Processor instance.
/// @param name      The current extension or null.

optFIFOPortP opqProcessorFIFOPortByName (
    optProcessorP processor,
    const char *  name
);

/// Get the next FIFO port from a processor instance.
/// @return The next FIFO port.
/// @param processor Processor instance.
/// @param fifo      The current extension or null.

optFIFOPortP opqProcessorFIFOPortNext (
    optProcessorP processor,
    optFIFOPortP  fifo
);

/// Return the next processor instance.
/// @return The next processor.
/// @param module    Module instance.
/// @param processor Current processor or null.

optProcessorP opqProcessorNext (
    optModuleP    module,
    optProcessorP processor
);

/// Get the dummy root module instance.
/// @return The dummy root module.

optModuleP opqRoot (void);


#endif /* OPQQUERY_H */

