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


#ifndef OPCCONSTRUCT_H
#define OPCCONSTRUCT_H

#include "optTypes.h"

/// Use installed readers to parse the header of an application file.
/// @return True if read successfully.
/// @param file Program object.
/// @param info pointer to info structure, filled in by this call.

Bool opcApplicationHeaderRead (
    const char*    file,
    ordObjectInfoP info
);

/// Install a reader for application programs.
/// @return True if installed successfully.
/// @param file Program object.

Bool opcApplicationReaderInstall (
    const char* file
);

/// Connect a bridge to a bus.
/// @return The new connection.
/// @param bridge   Bridge.
/// @param bus      Bus.
/// @param portName Name of port.
/// @param isMaster True if the connection is a master, false if a slave.
/// @param addrLo   Lower address bound.
/// @param addrHi   Upper address bound.

optBusPortConnP opcBridgeBusConnect (
    optBridgeP   bridge,
    optBusP      bus,
    const char * portName,
    Bool         isMaster,
    Addr         addrLo,
    Addr         addrHi
);

/// Create a bridge for connecting two buses.
/// @return The new bridge instance.
/// @param module Parent processor.
/// @param name   New instance name.

optBridgeP opcBridgeNew (
    optModuleP  module,
    const char* name
);

/// Load application code onto a bus.
/// @return The new application object.
/// @param bus        Bus instance.
/// @param path       Application object file.
/// @param controls   Control loader behaviour.
/// @param loadOffset Add this to all load addresses.

optApplicationP opcBusApplicationLoad (
    optBusP           bus,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset
);

/// Connect a bus to a module instance.
/// @return The new connection.
/// @param list     Previous connection to add to the list.
/// @param portName Name of the bus port in the instanced object.
/// @param bus      Bus instance.

optBusPortConnP opcBusConnect (
    optBusPortConnP list,
    const char*     portName,
    optBusP         bus
);

/// Create a bus.
/// @return The new bus.
/// @param module   Parent module.
/// @param name     New bus name.
/// @param addrBits Number of address bits.
/// @param portName Export the bus using this port name.
/// @param params   List of parameters for the instance.

optBusP opcBusNew (
    optModuleP  module,
    const char* name,
    Uns32       addrBits,
    const char* portName,
    optParamP   params
);

/// Implement an address region as callbacks.
/// @return True if successful.
/// @param bus          Bus.
/// @param name         Name for the region.
/// @param proc         Optional processor context. If valid, only this
///                     processor will trigger the callback.
/// @param privilege    Set the access privilege.
/// @param addrLo       Low address.
/// @param addrHi       High address.
/// @param rcb          Function called to implement bus reads.
/// @param wcb          Function called to implement bus writes.
/// @param nativeMemory User data.
/// @param userData     User data.

Bool opcBusRegionAsCallbacks (
    optBusP       bus,
    const char *  name,
    optProcessorP proc,
    optPriv       privilege,
    Addr          addrLo,
    Addr          addrHi,
    optMemReadFn  rcb,
    optMemWriteFn wcb,
    void*         nativeMemory,
    void*         userData
);

/// Read this control file.
/// @param file Path to control file.

void opcControlFileRead (
    const char* file
);

/// Install callbacks for debug integration.
/// @param root      Applies to this root module only.
/// @param notifiers Callback structure.

void opcDebuggerNotifiersAdd (
    optModuleP            root,
    optDebuggerNotifiersP notifiers
);

/// Create a documentation section.
/// @return The new documentation node.
/// @param parent Parent node.
/// @param name   Section name.

optDocNodeP opcDocSectionAdd (
    optDocNodeP parent,
    const char* name
);

/// Add text to a document.
/// @return The new documentation node.
/// @param parent Parent node.
/// @param text   Document text.

optDocNodeP opcDocTextAdd (
    optDocNodeP parent,
    const char* text
);

/// Create an extension instance on a module (not yet supported).
/// @return The new extension instance.
/// @param module Parent module.
/// @param path   Path to extension library.
/// @param name   New instance name.
/// @param params Parameters to configure this instance.

optExtensionP opcExtensionNew (
    optModuleP  module,
    const char* path,
    const char* name,
    optParamP   params
);

/// Connect a FIFO to a module instance.
/// @return The new connection.
/// @param list     An existing module.
/// @param portName Name of FIFO port.
/// @param fifo     FIFO.

optFIFOPortConnP opcFIFOConnect (
    optFIFOPortConnP list,
    const char *     portName,
    optFIFOP         fifo
);

/// Add a FIFO to a module.
/// @return The new FIFO instance.
/// @param module   Parent module.
/// @param name     New FIFO name.
/// @param depth    Number of words.
/// @param portName Export the FIFO using this port name.
/// @param params   Parameters to configure this instance.

optFIFOP opcFIFONew (
    optModuleP  module,
    const char* name,
    Uns32       depth,
    const char* portName,
    optParamP   params
);

/// (for internal use only).
/// @param module   (for internal use only).
/// @param features (for internal use only).

void opcFeaturesSet (
    optModuleP module,
    Uns32      features
);

/// Special modes. Use for legacy code.
/// @param module Parent module.

void opcICMModeSet (
    optModuleP module
);

/// Start a session.
/// @param version Version string (from macro OP_VERSION).

void opcInit (
    const char* version
);

/// Set the product personality (for internal use only).
/// @param personality Personality string.

void opcLicPersonalitySet (
    const char* personality
);

/// Connect an MMC to a bus.
/// @return The new connection.
/// @param mmc      MMC.
/// @param bus      Bus.
/// @param portName Name of MMC port.

optBusPortConnP opcMMCBusConnect (
    optMMCP      mmc,
    optBusP      bus,
    const char * portName
);

/// Create an MMC instance from a shared object.
/// @return The new MMC instance.
/// @param module Parent module.
/// @param path   Path to MMC model.
/// @param name   New instance name.
/// @param params Parameters to configure this instance.

optMMCP opcMMCNew (
    optModuleP  module,
    const char* path,
    const char* name,
    optParamP   params
);

/// Load application code into a memory.
/// @return The new application object.
/// @param memory     Memory instance.
/// @param path       Application object file.
/// @param controls   Control loader behaviour.
/// @param loadOffset Add this to all load addresses.

optApplicationP opcMemoryApplicationLoad (
    optMemoryP        memory,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset
);

/// Connect a memory bus port by name.
/// @return The new connection.
/// @param memory   Memory instance.
/// @param bus      Net.
/// @param portName Name of port.
/// @param addrLo   Lower address bound.
/// @param addrHi   Upper address bound.

optBusPortConnP opcMemoryBusConnect (
    optMemoryP   memory,
    optBusP      bus,
    const char * portName,
    Addr         addrLo,
    Addr         addrHi
);

/// Create a memory instance representing native memory.
/// @return The new memory instance.
/// @param module       Parent module.
/// @param name         New instance name.
/// @param priv         Permitted access.
/// @param maxAddress   Maximum address (size-1).
/// @param nativeMemory Pre-allocated memory.
/// @param params       Parameters to configure this instance.

optMemoryP opcMemoryNativeNew (
    optModuleP  module,
    const char* name,
    optPriv     priv,
    Addr        maxAddress,
    void*       nativeMemory,
    optParamP   params
);

/// Create a memory instance.
/// @return The new memory instance.
/// @param module     Parent module.
/// @param name       New instance name.
/// @param priv       Permitted access.
/// @param maxAddress Maximum address (size-1).
/// @param params     Parameters to configure this instance.

optMemoryP opcMemoryNew (
    optModuleP  module,
    const char* name,
    optPriv     priv,
    Addr        maxAddress,
    optParamP   params
);

/// Add documentation section to a module.
/// @return The new (root) document node.
/// @param module The module being documented.
/// @param name   The name of the new section.

optDocNodeP opcModuleDocSectionAdd (
    optModuleP   module,
    const char * name
);

/// Change the name of a module. Do not use this function.
/// @param module Parent module.
/// @param name   New name.

void opcModuleNameChange (
    optModuleP  module,
    const char* name
);

/// Create an module instance from a module file.
/// @return The new module instance.
/// @param module      Parent module.
/// @param path        Path to module.
/// @param name        New instance name or null.
/// @param connections Lists of connections.
/// @param params      List of parameters for the instance.

optModuleP opcModuleNew (
    optModuleP      module,
    const char*     path,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// Create an module instance from a module modelAttrs structure.
/// @return The new module instance.
/// @param module      Parent module.
/// @param attrs       Attributes table.
/// @param name        New instance name or null.
/// @param connections Lists of connections.
/// @param params      List of parameters for the instance.

optModuleP opcModuleNewFromAttrs (
    optModuleP      module,
    optModuleAttrP  attrs,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// Connect a net to a module instance.
/// @return The new connection.
/// @param list     Previous connection to add to the list.
/// @param portName Name of net port on the module instance.
/// @param net      Net instance.

optNetPortConnP opcNetConnect (
    optNetPortConnP list,
    const char *    portName,
    optNetP         net
);

/// Create a new net.
/// @return The new net.
/// @param module   Parent module.
/// @param name     Name of the new net.
/// @param portName Export the net using this port name.
/// @param params   Parameters to configure this instance.

optNetP opcNetNew (
    optModuleP  module,
    const char* name,
    const char* portName,
    optParamP   params
);

/// Add a callback to a packetnet.
/// @param packetnet Packetnet object.
/// @param cb        callback function.
/// @param userData  user data, passed to callback.

void opcPacketnetCallbackAdd (
    optPacketnetP       packetnet,
    optPacketnetWriteFn cb,
    void*               userData
);

/// Connect a packetnet to a module instance.
/// @return The new connection.
/// @param list      Previous connection to add to the list.
/// @param portName  Name of packetnet port on the module instance.
/// @param packetnet Packetnet instance.

optPacketnetPortConnP opcPacketnetConnect (
    optPacketnetPortConnP list,
    const char *          portName,
    optPacketnetP         packetnet
);

/// Create a packetnet.
/// @return The new packetnet.
/// @param module   Parent module.
/// @param name     Name of the new packetnet.
/// @param portName Export the packetnet using this port name.
/// @param params   Parameters to configure this packetnet.

optPacketnetP opcPacketnetNew (
    optModuleP   module,
    const char * name,
    const char*  portName,
    optParamP    params
);

/// Create a Bool parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamBoolSet (
    optParamP   list,
    const char* name,
    Bool        value
);

/// Create a double precision parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamDoubleSet (
    optParamP   list,
    const char* name,
    double      value
);

/// Create an endian parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Endian value (enumerated type).

optParamP opcParamEndianSet (
    optParamP   list,
    const char* name,
    optEndian   value
);

/// Create an enum parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamEnumSet (
    optParamP   list,
    const char* name,
    const char* value
);

/// Create an Int32 parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamInt32Set (
    optParamP   list,
    const char* name,
    Int32       value
);

/// Override an existing parameter by hierarchical name.
/// @return True if successful.
/// @param name  Hierarchical name of the parameter.
/// @param value New parameter value. Will be converted to the correct type.

Bool opcParamOverrideString (
    const char* name,
    const char* value
);

/// Create an pointer parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamPtrSet (
    optParamP   list,
    const char* name,
    void*       value
);

/// Create a string parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamStringSet (
    optParamP   list,
    const char* name,
    const char* value
);

/// Create an Uns32 parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamUns32Set (
    optParamP   list,
    const char* name,
    Uns32       value
);

/// Create an Uns64 parameter in this list.
/// @return The head of the parameter list.
/// @param list  The list or null.
/// @param name  New parameter name.
/// @param value Value.

optParamP opcParamUns64Set (
    optParamP   list,
    const char* name,
    Uns64       value
);

/// Create a cursor parameter to begin a new list (This is not now required, the
/// simulator will add it automatically).
/// @return The head of the parameter list.
/// @param module The parent module.

optParamP opcParamVoid (
    optModuleP module
);

/// Connect a peripheral to a bus.
/// @return The new connection.
/// @param peripheral Peripheral instance.
/// @param bus        Bus.
/// @param portName   Name of peripheral port.
/// @param addrLo     Lower address bound.
/// @param addrHi     Upper address bound.

optBusPortConnP opcPeripheralBusConnectMaster (
    optPeripheralP peripheral,
    optBusP        bus,
    const char *   portName,
    Addr           addrLo,
    Addr           addrHi
);

/// Connect a peripheral to a bus.
/// @return The new connection.
/// @param peripheral Peripheral instance.
/// @param bus        Bus.
/// @param portName   Name of peripheral port.
/// @param addrLo     Lower address bound.
/// @param addrHi     Upper address bound.

optBusPortConnP opcPeripheralBusConnectSlave (
    optPeripheralP peripheral,
    optBusP        bus,
    const char *   portName,
    Addr           addrLo,
    Addr           addrHi
);

/// Connect a peripheral to a bus with a dynamic slave port.
/// @return The new connection.
/// @param peripheral Peripheral instance.
/// @param bus        Bus.
/// @param portName   Name of peripheral port.

optBusPortConnP opcPeripheralBusConnectSlaveDynamic (
    optPeripheralP peripheral,
    optBusP        bus,
    const char *   portName
);

/// Create an extension instance on a peripheral.
/// @return The new extension instance.
/// @param peripheral Parent peripheral.
/// @param path       Path to extension file.
/// @param name       New instance name.
/// @param params     Parameters to configure this instance.

optExtensionP opcPeripheralExtensionNew (
    optPeripheralP peripheral,
    const char*    path,
    const char*    name,
    optParamP      params
);

/// Connect a peripheral port by name.
/// @return The new connection.
/// @param peripheral Peripheral instance.
/// @param net        Net.
/// @param portName   Name of peripheral port.

optNetPortConnP opcPeripheralNetConnect (
    optPeripheralP peripheral,
    optNetP        net,
    const char *   portName
);

/// Create a peripheral instance from a peripheral program.
/// @return The new peripheral instance.
/// @param module Parent module.
/// @param path   Path to peripheral.
/// @param name   New instance name.
/// @param params Parameters to configure this instance.

optPeripheralP opcPeripheralNew (
    optModuleP  module,
    const char* path,
    const char* name,
    optParamP   params
);

/// Connect a Peripheral to a packetnet.
/// @return The new connection.
/// @param peripheral Peripheral object.
/// @param packetnet  Packetnet object.
/// @param portName   Name of the packetnet port on the peripheral.

optPacketnetPortConnP opcPeripheralPacketnetConnect (
    optPeripheralP peripheral,
    optPacketnetP  packetnet,
    const char *   portName
);

/// Load application code onto a processor.
/// @return The new application object.
/// @param processor  Processor instance.
/// @param path       Application object file.
/// @param controls   Control loader behaviour.
/// @param loadOffset Offset added to program.

optApplicationP opcProcessorApplicationLoad (
    optProcessorP     processor,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset
);

/// Read application code, making a callback for each region.
/// @return The new application object.
/// @param processor  Processor instance.
/// @param path       Application object file.
/// @param controls   Control loader behaviour.
/// @param loadOffset Offset added to program.
/// @param cbs        Callback table.
/// @param userData   User data.

optApplicationP opcProcessorApplicationRead (
    optProcessorP     processor,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset,
    ordCallbacksP     cbs,
    void*             userData
);

/// Connect a processor bus port by name.
/// @return The new connection.
/// @param processor Processor instance.
/// @param bus       Bus.
/// @param portName  Name of port.

optBusPortConnP opcProcessorBusConnect (
    optProcessorP processor,
    optBusP       bus,
    const char *  portName
);

/// Mark this processor to be attached to the next debugger (when using GDB).
/// @param processor Processor to be debugged.

void opcProcessorDebug (
    optProcessorP processor
);

/// Create an extension instance on a processor.
/// @return The new extension instance.
/// @param processor Parent processor.
/// @param path      Extension master.
/// @param name      New instance name.
/// @param params    Parameters to configure this instance.

optExtensionP opcProcessorExtensionNew (
    optProcessorP processor,
    const char*   path,
    const char*   name,
    optParamP     params
);

/// Connect a processor bus port by name.
/// @return The new connection.
/// @param processor Processor instance.
/// @param fifo      FIFO.
/// @param portName  Name of port.

optFIFOPortConnP opcProcessorFIFOConnect (
    optProcessorP processor,
    optFIFOP      fifo,
    const char *  portName
);

/// Connect a processor net port by name.
/// @return The new connection.
/// @param processor Processor instance.
/// @param net       Net.
/// @param portName  Name of port.

optNetPortConnP opcProcessorNetConnect (
    optProcessorP processor,
    optNetP       net,
    const char *  portName
);

/// Create a processor instance from a shared object.
/// @return The new processor instance.
/// @param module Parent module.
/// @param path   Path to processor model.
/// @param name   New instance name.
/// @param params Parameters to configure this instance.

optProcessorP opcProcessorNew (
    optModuleP  module,
    const char* path,
    const char* name,
    optParamP   params
);

/// Create a processor instance from a modelAttrs structure.
/// @return The new processor instance.
/// @param module   Parent module.
/// @param iasAttrs Processor attribute table.
/// @param stubs    Processor stub functions table.
/// @param name     New instance name.
/// @param params   Parameters to configure this instance.

optProcessorP opcProcessorNewFromAttrs (
    optModuleP  module,
    void *      iasAttrs,
    void *      stubs,
    const char* name,
    optParamP   params
);

/// Create a processor instance with semihosting installed (for ICM
/// compatibility).
/// @return The new processor instance.
/// @param module   Parent module.
/// @param path     Path to processor model.
/// @param name     New instance name.
/// @param params   Parameters to configure this instance.
/// @param semihost Path to semihost library.

optProcessorP opcProcessorNewWithSemihost (
    optModuleP  module,
    const char* path,
    const char* name,
    optParamP   params,
    const char* semihost
);

/// (for internal use only).
/// @param name (for internal use only).

void opcProductSet (
    const char* name
);

/// Copy an complete design (pre simulation).
/// @return The new copied module hierarchy.
/// @param module Parent module.

optModuleP opcRootModuleCopy (
    optModuleP module
);

/// Create a root module instance. Use this when constructing a test harness.
/// @return The new root module instance.
/// @param attrs  Attribute table. Registers callbacks for each phase.
/// @param name   Name of root module (optional).
/// @param params Simulator control parameters.

optModuleP opcRootModuleNew (
    optModuleAttrP attrs,
    const char*    name,
    optParamP      params
);

/// Destroy a root module instance.
/// @param mi Root module instance.

void opcRootModuleOld (
    optModuleP mi
);

/// Create a temporary formatted string. Note that there are a limited number of
/// buffers so do not rely on the data persisting beyond the next use of this
/// function.
/// @return A temporary string containing the formatted text.
/// @param fmt format string.
/// @param ... varargs.

const char* opcSprintf (
    const char * fmt,
                 ...
);

/// End a session.

void opcTerminate (void);

/// Call the given function on all files that match the given VLNV.
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT.
/// @param vendor   Vendor directory e.g. yourcompany.com.
/// @param library  Library directory e.g. processor.
/// @param name     Name directory e.g. risc32.
/// @param version  Version directory e.g. 1.0.
/// @param type     Type of model.
/// @param cb       Callback.
/// @param userData User data passed to callback.

void opcVLNVIter (
    const char*  vlnvroot,
    const char*  vendor,
    const char*  library,
    const char*  name,
    const char*  version,
    optModelType type,
    optFileFn    cb,
    void*        userData
);

/// Synthesize a VLNV path string given the vendor, library, name and version of
/// the library object you wish to load. If models are stored according to
/// Imperas guidelines, this should successfully locate any model. If all
/// arguments are plain strings, constructs a path such as
/// 'vlnvroot/vendor/library/name/version/objtype', otherwise the following
/// rules are used: If vlnvroot is null, the default installation path is used.
/// vlnvroot may be a ':' (Linux) or ';' (Windows) separated list of paths.
/// @return Null if no file is found, otherwise a file path.
/// @param vlnvroot     Path or list of paths to root of directory(s)
///                     containing modelsT.
/// @param vendor       Vendor directory e.g. yourcompany.com.
/// @param library      Library directory e.g. processor.
/// @param name         Name directory e.g. risc32.
/// @param version      Version directory e.g. 1.0.
/// @param type         Type of model.
/// @param reportErrors Print errors and ambiguities, otherwise quietly
///                     return null if fails.

const char* opcVLNVString (
    const char*  vlnvroot,
    const char*  vendor,
    const char*  library,
    const char*  name,
    const char*  version,
    optModelType type,
    Bool         reportErrors
);


#endif /* OPCCONSTRUCT_H */

