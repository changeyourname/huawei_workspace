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


#ifndef ICMCONSTRUCT_H
#define ICMCONSTRUCT_H

#include "icmTypes.h"

/// Add a Bool attribute to the given attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value Boolean value.

void icmAddBoolAttr (
    icmAttrListP attrs,
    const char*  name,
    Bool         value
);

/// Install a callback on fetch accesses using the bus.
/// @param bus      Bus object.
/// @param scope    If non-null, restrict sensitivity to this processor.
/// @param lowAddr  Lowest address of the region to be sensitized.
/// @param highAddr Highest address of the region to be sensitized.
/// @param writeCB  Function to be called.
/// @param userData Passed to the callback function.

void icmAddBusFetchCallback (
    icmBusP       bus,
    icmProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// Install a callback on read accesses using the bus.
/// @param bus      Bus object.
/// @param scope    If non-null, restrict sensitivity to this processor.
/// @param lowAddr  Lowest address of the region to be sensitized.
/// @param highAddr Highest address of the region to be sensitized.
/// @param readCB   Function to be called.
/// @param userData Passed to the callback function.

void icmAddBusReadCallback (
    icmBusP       bus,
    icmProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn readCB,
    void*         userData
);

/// Install a callback on write accesses using the bus.
/// @param bus      Bus object.
/// @param scope    If non-null, restrict sensitivity to this processor.
/// @param lowAddr  Lowest address of the region to be sensitized.
/// @param highAddr Highest address of the region to be sensitized.
/// @param writeCB  Function to be called.
/// @param userData Passed to the callback function.

void icmAddBusWriteCallback (
    icmBusP       bus,
    icmProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// Add a control file to be read before simulation starts.
/// @param filename The control file.

void icmAddControlFile (
    const char* filename
);

/// Add a double attribute to the attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value Double value.

void icmAddDoubleAttr (
    icmAttrListP attrs,
    const char*  name,
    double       value
);

/// Install a callback activated by fetches on the processor external code bus.
/// @param processor Processor object.
/// @param lowAddr   Lowest address of the region to be sensitized.
/// @param highAddr  Highest address of the region to be sensitized.
/// @param writeCB   Function to be called.
/// @param userData  Passed to the callback function.

void icmAddFetchCallback (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// Add a supplementary intercept shared object for a processor.
/// @return New intercept object.
/// @param processor       Processor to be intercepted.
/// @param instanceName    Unique name for this intercept (will be copied, so
///                        does not need to persist).
/// @param interceptFile   Path to the intercept object file.
/// @param interceptSymbol Not used. Set to null.
/// @param userAttrs       User defined attribute list for the intercept
///                        object (or null).

icmInterceptP icmAddInterceptObject (
    icmProcessorP processor,
    const char*   instanceName,
    const char*   interceptFile,
    const char*   interceptSymbol,
    icmAttrListP  userAttrs
);

/// Add a callback to a packetnet.
/// @param packetnet Packetnet object.
/// @param cb        callback function.
/// @param userData  user data, passed to callback.

void icmAddPacketnetCallback (
    icmPacketnetP          packetnet,
    icmPacketnetNotifierFn cb,
    void*                  userData
);

/// Add a supplementary intercept shared object for a PSE.
/// @return New intercept object.
/// @param pse             PSE to be intercepted.
/// @param instanceName    Unique name for this intercept (will be copied, so
///                        does not need to persist).
/// @param interceptFile   Path to the intercept object file.
/// @param interceptSymbol Not used. Set to null.
/// @param userAttrs       User defined attribute list for the intercept
///                        object (or null).

icmInterceptP icmAddPseInterceptObject (
    icmPseP      pse,
    const char*  instanceName,
    const char*  interceptFile,
    const char*  interceptSymbol,
    icmAttrListP userAttrs
);

/// Add a native host pointer attribute to the given attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value Native host pointer value.

void icmAddPtrAttr (
    icmAttrListP attrs,
    const char*  name,
    void *       value
);

/// Install a callback activated by reads on the processor external data bus.
/// @param processor Processor object.
/// @param lowAddr   Lowest address of the region to be sensitized.
/// @param highAddr  Highest address of the region to be sensitized.
/// @param readCB    Function to be called.
/// @param userData  Passed to the callback function.

void icmAddReadCallback (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn readCB,
    void*         userData
);

/// Add a string attribute to the attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value String value.

void icmAddStringAttr (
    icmAttrListP attrs,
    const char*  name,
    const char*  value
);

/// Add an Uns32 attribute to the given attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value 32-bit integer value.

void icmAddUns32Attr (
    icmAttrListP attrs,
    const char*  name,
    Uns32        value
);

/// Add an Uns64 attribute to the given attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value 64-bit integer value.

void icmAddUns64Attr (
    icmAttrListP attrs,
    const char*  name,
    Uns64        value
);

/// Install a callback activated by writes on the processor external data bus.
/// @param processor Processor object.
/// @param lowAddr   Lowest address of the region to be sensitized.
/// @param highAddr  Highest address of the region to be sensitized.
/// @param writeCB   Function to be called.
/// @param userData  Passed to the callback function.

void icmAddWriteCallback (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// Call the given function on all files matching the VLNV specification.
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT.
/// @param vendor   Vendor directory e.g. yourcompany.com or '*'.
/// @param library  Library directory e.g. processor or '*'.
/// @param name     Name directory e.g. risc32 or '*'.
/// @param version  Version directory e.g. 1.0 or '*'.
/// @param objType  Filename in the version directory or 'pse' or 'model'.
/// @param cb       Callback.
/// @param userData User data passed to cb.

void icmAllVlnvFiles (
    const char*    vlnvroot,
    const char*    vendor,
    const char*    library,
    const char*    name,
    const char*    version,
    const char*    objType,
    icmFoundFileFn cb,
    void*          userData
);

/// Return the object file for a default platform, if one is specified.
/// @return Path to object file if exactly one is specified.

const char * icmCLPDefaultObjectFile (void);

/// Return true if the named argument has been used on the command line.
/// @return Path to object file if exactly one is specified.
/// @param parser Parser.
/// @param name   name of the flag (without the '-').

Bool icmCLParseArgUsed (
    icmCLPP       parser,
    const char  * name
);

/// Parse an argv/argc array.
/// @return True if parsed without errors.
/// @param parser Parser.
/// @param argc   Argument count.
/// @param argv   Argument array.

Bool icmCLParseArgs (
    icmCLPP       parser,
    Uns32         argc,
    const char ** argv
);

/// Parse a control file.
/// @return True if parsed without errors.
/// @param parser Parser.
/// @param path   Path to file.

Bool icmCLParseFile (
    icmCLPP       parser,
    const char  * path
);

/// Parse an argv/argc array using standard arguments. Exits if errors are
/// detected.
/// @param client Name of the client (for error reporting).
/// @param select Select which flags are installed.
/// @param argc   Argument count.
/// @param argv   Argument array.

void icmCLParseStd (
    const char *   client,
    icmCLPArgClass select,
    Uns32          argc,
    const char **  argv
);

/// Create a command line parser.
/// @return Handle to the new parser.
/// @param client    Name of the client (for error reporting).
/// @param argSelect Select which standard flags are installed.

icmCLPP icmCLParser (
    const char *   client,
    icmCLPArgClass argSelect
);

/// Add an argument to be accepted by this parser. The bit mask is used as
/// follows: If the mask is zero , this argument will always be in the parser.
/// If the mask is non-zero, the argument will be installed if the corresponding
/// bit is set in the parse constructor. The flags are allocated as follows: bit
/// 0 : reserved for internal use. bit 1 : for use in the standard product. bits
/// 2-4 : reserved for internal use. bits 5-31: for use by external tools.
/// @param parser      Parser.
/// @param name        Argument name. Must be unique.
/// @param shortname   Optional argument short name. Must be unique.
/// @param argDesc     Optional description of the argument value (e.g.
///                    filename).
/// @param group       Optional argument group.
/// @param type        Argument type.
/// @param ptr         Pointer to data or function.
/// @param description Appears with -help.
/// @param useMask     Use Mask. See function description.
/// @param userData    Passed to function.
/// @param mandatory   This argument must be specified.

void icmCLParserAdd (
    icmCLPP       parser,
    const char *  name,
    const char *  shortname,
    const char *  argDesc,
    const char *  group,
    icmCLPArgType type,
    void*         ptr,
    const char *  description,
    Uns32         useMask,
    Uns32         userData,
    Bool          mandatory
);

/// Destroy the parser.
/// @param parser Parser.

void icmCLParserOld (
    icmCLPP parser
);

/// Print this message with -help or if errors are found.
/// @param parser  Parser.
/// @param message General help message.

void icmCLParserUsageMessage (
    icmCLPP       parser,
    const char  * message
);

/// Connect an MMC bus port to the bus. 'isMaster' specifies whether the port is
/// a bus master (i.e. written by the MMC) or a slave (read by the MMC).
/// @param mmc      The MMC to be connected.
/// @param bus      The bus to be connected.
/// @param portName The name of the port on the MMC.
/// @param isMaster If true, this is a bus master port, if false this is a
///                 slave port.

void icmConnectMMCBus (
    icmMmcP     mmc,
    icmBusP     bus,
    const char* portName,
    Bool        isMaster
);

/// Connect a memory object and a bus, using the named memory port.
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param memory   A memory object already created.
/// @param lowAddr  Base (decoded) address of the connected memory.

void icmConnectMemoryToBus (
    icmBusP     bus,
    const char* portName,
    icmMemoryP  memory,
    Addr        lowAddr
);

/// Connect a PSE bus port to a bus.
/// @param pse      The PSE to be connected.
/// @param bus      The bus to be connected.
/// @param portName Name of the port on the PSE. This must exist in the PSE
///                 model.
/// @param isMaster If True, this is a bus master, otherwise a bus slave.
///                 This must match the semantics of the port in the model.
/// @param lowAddr  Base address on the bus where the port is connected.
/// @param highAddr Highest address on the bus where the port is connected.

void icmConnectPSEBus (
    icmPseP     pse,
    icmBusP     bus,
    const char* portName,
    Bool        isMaster,
    Addr        lowAddr,
    Addr        highAddr
);

/// Connect a PSE bus port to the bus with a range specified by the PSE at
/// run-time.
/// @param pse      The PSE to be connected.
/// @param bus      The bus to be connected.
/// @param portName Name of the port on the PSE. This must exist in the PSE
///                 model.
/// @param isMaster If True, this is a bus master, otherwise a bus slave.
///                 This must match the semantics of the port in the model.

void icmConnectPSEBusDynamic (
    icmPseP     pse,
    icmBusP     bus,
    const char* portName,
    Bool        isMaster
);

/// Connect a PSE instance port to a net.
/// @param pse      The PSE to be connected.
/// @param net      The net to be connected.
/// @param portName Name of the port on the PSE. This must exist in the PSE
///                 model. It must be net port.
/// @param notUsed  Set to zero; this argument is not used.

void icmConnectPSENet (
    icmPseP      pse,
    icmNetP      net,
    const char*  portName,
    icmDirection notUsed
);

/// Connect a PSE to a packetnet.
/// @param pse       PSE object.
/// @param packetnet Packetnet object.
/// @param portName  Name of the packetnet port on the peripheral.

void icmConnectPSEPacketnet (
    icmPseP       pse,
    icmPacketnetP packetnet,
    const char *  portName
);

/// Connect the processor to a bus using the named port.
/// @param processor Processor to connect.
/// @param port      The port name.
/// @param bus       The bus (created with icmNewBus()).

void icmConnectProcessorBusByName (
    icmProcessorP processor,
    const char*   port,
    icmBusP       bus
);

/// Connect the processor to the passed instruction and data buses.
/// @param processor      Processor to connect.
/// @param instructionBus The instruction bus (created with icmNewBus()).
/// @param dataBus        The data bus (created with icmNewBus()).

void icmConnectProcessorBusses (
    icmProcessorP processor,
    icmBusP       instructionBus,
    icmBusP       dataBus
);

/// Connect a processor connection object port.
/// @param icmProcessor Processor to connect.
/// @param conn         The connection object (see icmNewFifo()).
/// @param portName     Name of the port on the processor (see VMI
///                     documentation).
/// @param direction    ICM_INPUT or ICM_OUTPUT.

void icmConnectProcessorConn (
    icmProcessorP icmProcessor,
    icmConnP      conn,
    const char*   portName,
    icmDirection  direction
);

/// Connect a processor net port with the passed name and direction to a net.
/// @param icmProcessor Processor to connect.
/// @param net          The net (created with icmNewNet()).
/// @param portName     Name of the port on the processor (see VMI
///                     documentation).
/// @param notUsed      Set to zero; this argument is not used.

void icmConnectProcessorNet (
    icmProcessorP icmProcessor,
    icmNetP       net,
    const char*   portName,
    icmDirection  notUsed
);

/// Attach a document section to the current platform, or to an existing
/// section.
/// @return Pointer to the new node.
/// @param node        Existing parent node, or null to add to the platform.
/// @param sectionName Name of the new section.

icmDocNodeP icmDocSectionAdd (
    icmDocNodeP  node,
    const char * sectionName
);

/// Attach text to an existing document section.
/// @param node Existing parent node, or null to add to the platform.
/// @param text A paragraph of new text.

void icmDocTextAdd (
    icmDocNodeP  node,
    const char * text
);

/// Synthesize a VLNV path string given the vendor, library, name and version of
/// the library object you wish to load. If models are stored according to
/// Imperas guidelines, this should successfully locate any model. If all
/// arguments are plain strings, constructs a path such as
/// 'vlnvroot/vendor/library/name/version/objtype', otherwise the following
/// rules are used: If vlnvroot is NULL, the default installation path is used.
/// vlnvroot may be a ':' (Linux) or ';' (Windows) separated list of paths. If
/// vendor, library, or name are empty strings (0 is not allowed) or '*', they
/// are treated as wild-cards and all directories are searched. If version is a
/// wild-card, the latest version is taken (note that 1.2.1 is later than 1.2,
/// but FOO is later than both). For success the specification must yield
/// exactly one file. If objType is 'pse', the file pse.pse is used (this is the
/// convention used by Imperas). If objType is 'model' or 'intercept', the file
/// 'model.so' (Linux) or 'model.dll' (Windows) is used. Otherwise, the string
/// is used as is. Note that the name CVS or names that begin with a period are
/// ignored. This function is intended to be used be used by icmNewProcessor,
/// icmNewPSE and icmNewMMC.
/// @return Null (reports an error) if no unique file is found, otherwise a
///         file path.
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT.
/// @param vendor   Vendor directory e.g. yourcompany.com or '*'.
/// @param library  Library directory e.g. processor or '*'.
/// @param name     Name directory e.g. risc32 or '*'.
/// @param version  Version directory e.g. 1.0 or '*'.
/// @param objType  Filename in the version directory or 'pse' or 'model'.

const char* icmGetVlnvString (
    const char* vlnvroot,
    const char* vendor,
    const char* library,
    const char* name,
    const char* version,
    const char* objType
);

/// Initialize ICM package - call this before any other ICM functions. Please
/// use the macro icmInit().
/// @param versionString ICM Version. Checked before ICM is allowed to run.
/// @param simAttrs      Bit mask of simulation switches.
/// @param debugProtocol Specify debug protocol (or null if no debug).
/// @param dbgPort       Optional host port to connect to debug port.

void icmInitInternal (
    const char*  versionString,
    icmInitAttrs simAttrs,
    const char*  debugProtocol,
    Uns32        dbgPort
);

/// Initialize ICM package and create a named platform. Call this before any
/// other ICM functions.
/// @param versionString ICM Version. Checked before ICM is allowed to run.
///                      Use the macro ICM_VERSION.
/// @param simAttrs      Bit mask of simulation switches.
/// @param debugProtocol Specify debug protocol (or null if no debug).
/// @param dbgPort       Optional host port to connect to debug port.
/// @param platformName  Platform name, appearing in hierarchical component
///                      names.

void icmInitPlatform (
    const char*  versionString,
    icmInitAttrs simAttrs,
    const char*  debugProtocol,
    Uns32        dbgPort,
    const char*  platformName
);

/// Map the passed bus address range using the callbacks.
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param priv     Access permission on this memory (see icmPriv).
/// @param lowAddr  Low end of range.
/// @param highAddr High end of range.
/// @param readCB   If specified, will be called for each read.
/// @param writeCB  If specified, will be called for each write.
/// @param userData Passed to each read or write callback.

void icmMapExternalMemory (
    icmBusP       bus,
    const char*   portName,
    icmPriv       priv,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemReadFn  readCB,
    icmMemWriteFn writeCB,
    void*         userData
);

/// Map the passed bus address range using the callbacks or locally allocated
/// memory if a callback is absent.
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param priv     Access permission on this memory (see icmPriv).
/// @param lowAddr  Low end of range.
/// @param highAddr High end of range.
/// @param readCB   If specified, will be called for each read.
/// @param writeCB  If specified, will be called for each write.
/// @param memory   Pointer to space allocated by user (Must be at least as
///                 large as 1+hiAddr-lowAddr).
/// @param userData Passed to each read or write callback.

void icmMapExternalNativeMemory (
    icmBusP       bus,
    const char*   portName,
    icmPriv       priv,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemReadFn  readCB,
    icmMemWriteFn writeCB,
    void*         memory,
    void*         userData
);

/// Map the passed bus address range using a local anonymous memory.
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param priv     Access permission on this memory (see icmPriv).
/// @param lowAddr  Low end of range.
/// @param highAddr High end of range.

void icmMapLocalMemory (
    icmBusP     bus,
    const char* portName,
    icmPriv     priv,
    Addr        lowAddr,
    Addr        highAddr
);

/// Map locally allocated memory to a bus.
/// @param bus     Map the memory onto this bus.
/// @param priv    Access permission on this memory (see icmPriv).
/// @param lowAddr Low extent of the memory.
/// @param hiAddr  High extent of the memory.
/// @param memory  Pointer to space allocated by user (Must be at least as
///                large as 1+hiAddr-lowAddr).

void icmMapNativeMemory (
    icmBusP bus,
    icmPriv priv,
    Addr    lowAddr,
    Addr    hiAddr,
    void*   memory
);

/// Create a new attributes list.
/// @return New user-defined attributes list.

icmAttrListP icmNewAttrList (void);

/// Create a new bus object.
/// @return New bus object.
/// @param name        Unique name for this bus.
/// @param addressBits Width of the bus in bits.

icmBusP icmNewBus (
    const char* name,
    Uns8        addressBits
);

/// Create a bus bridge between the two buses so that the region starting at
/// lowAddrSlave on the slave bus is visible starting at lowAddrMaster in the
/// master bus.
/// @return Handle to new bridge.
/// @param slave          Bus on which the bridge receives an access.
/// @param master         Bus on which the bridge initiates an access.
/// @param bridgeName     Name of the new bridge.
/// @param slavePortName  Name of the new bridge bus slave port.
/// @param masterPortName Name of the new bridge bus master port.
/// @param lowAddrMaster  The lowest address generated by the master port.
/// @param highAddrMaster The highest address generated by the master port.
/// @param lowAddrSlave   The lowest address decoded by the slave port.

icmBusBridgeP icmNewBusBridge (
    icmBusP     slave,
    icmBusP     master,
    const char* bridgeName,
    const char* slavePortName,
    const char* masterPortName,
    Addr        lowAddrMaster,
    Addr        highAddrMaster,
    Addr        lowAddrSlave
);

/// Create a new bus object.
/// @return New bus object.
/// @param name        Unique name for this bus.
/// @param addressBits Width of the bus in bits.
/// @param handle      User-defined handle. The handle can be found later
///                    using icmGetBusHandle().

icmBusP icmNewBusWithHandle (
    const char* name,
    Uns8        addressBits,
    void*       handle
);

/// Create a FIFO object.
/// @return New FIFO object.
/// @param name  Name of the new FIFO object.
/// @param width Width of one input word in bits.
/// @param depth Number of words which can be held before overflow occurs.

icmConnP icmNewFifo (
    const char* name,
    Uns32       width,
    Uns32       depth
);

/// Create a FIFO object.
/// @return New FIFO object.
/// @param name   Name of the new FIFO object.
/// @param width  Width of one input word in bits.
/// @param depth  Number of words which can be held before overflow occurs.
/// @param handle User's handle (which can be found later using
///               icmGetFifoHandle()).

icmConnP icmNewFifoWithHandle (
    const char* name,
    Uns32       width,
    Uns32       depth,
    void*       handle
);

/// Create a new MMC instance running the passed shared object.
/// @return MMC object.
/// @param name         New unique name for this MMC instance.
/// @param modelFile    Path to the MMC model file (see icmGetVlnvString()).
/// @param modelSymbol  Not unused: Set to null.
/// @param initialAttrs List of user defined attributes created using
///                     icmNewAttrList() to be used by this model instance.
/// @param handle       Used by the client.
/// @param transparent  True if this MMC does not affect the bus traffic,
///                     only monitors it.

icmMmcP icmNewMMC (
    const char*  name,
    const char*  modelFile,
    const char*  modelSymbol,
    icmAttrListP initialAttrs,
    void*        handle,
    Bool         transparent
);

/// Create a memory object.
/// @return New memory object.
/// @param name     Unique name for the memory.
/// @param priv     See icmPriv enumeration.
/// @param highAddr Highest byte address (lowest is zero).

icmMemoryP icmNewMemory (
    const char* name,
    icmPriv     priv,
    Addr        highAddr
);

/// Create a memory object, with user-defined handle.
/// @return New memory object.
/// @param name     Unique name for the memory.
/// @param priv     See icmPriv enumeration.
/// @param highAddr Highest byte address (lowest is zero).
/// @param handle   User's handle.

icmMemoryP icmNewMemoryWithHandle (
    const char* name,
    icmPriv     priv,
    Addr        highAddr,
    void*       handle
);

/// Create a net object.
/// @return New net object handle.
/// @param name Name of new net.

icmNetP icmNewNet (
    const char* name
);

/// Create a net object.
/// @return New net object handle.
/// @param name   Name of new net.
/// @param handle User's handle (which can be found later using
///               icmGetNetHandle()).

icmNetP icmNewNetWithHandle (
    const char* name,
    void*       handle
);

/// Create a new PSE instance.
/// @return New PSE object.
/// @param name           New unique name for this PSE instance.
/// @param modelFile      Path to PSE executable file (see
///                       icmGetVlnvString()).
/// @param initialAttrs   List of user-defined attributes for this instance.
///                       In the PSE, routines including bhmStringAttribute
///                       can be used to retrieve the attributes.
/// @param semiHostFile   Path to an extension library for this PSE. This
///                       argument is not normally required; a PSE will load
///                       its own extension if required.
/// @param semiHostSymbol Not used. Set to null.

icmPseP icmNewPSE (
    const char*  name,
    const char*  modelFile,
    icmAttrListP initialAttrs,
    const char*  semiHostFile,
    const char*  semiHostSymbol
);

/// Create a new PSE as above, associating the passed handle with the
/// newly-created PSE.
/// @return New PSE object.
/// @param name           New unique name for this PSE instance.
/// @param modelFile      Path to PSE executable file.
/// @param initialAttrs   List of user-defined attributes for this instance.
///                       In the PSE, routines including bhmStringAttribute
///                       can be used to retrieve the attributes.
/// @param semiHostFile   Path to an extension library for this PSE. This
///                       argument is not normally required; a PSE will load
///                       its own extension if required.
/// @param semiHostSymbol Not used. Set to null.
/// @param handle         The handle which can be found later using
///                       icmGetPSEHandle().

icmPseP icmNewPSEWithHandle (
    const char*  name,
    const char*  modelFile,
    icmAttrListP initialAttrs,
    const char*  semiHostFile,
    const char*  semiHostSymbol,
    void*        handle
);

/// Create a packetnet.
/// @return Handle to the new packetnet.
/// @param name Name of the new packetnet.

icmPacketnetP icmNewPacketnet (
    const char * name
);

/// Create a new processor instance.
/// @return New processor object.
/// @param name           Name of new processor (string will be copied).
/// @param type           Type of new processor (string will be copied).
///                       Corresponds to the N in the VLNV.
/// @param cpuId          A unique number in the platform for this CPU.
/// @param cpuFlags       Debug flags passed to the model.
/// @param addressBits    Width of the address buses (in bits).
/// @param modelFile      Path to the file containing the model's shared
///                       object (see icmGetVlnvString()).
/// @param modelSymbol    Not used. Set to null.
/// @param procAttrs      Bit-mask of values from ICM_ATTR_... macros.
/// @param userAttrs      List of user defined attributes, constructed using
///                       icmNewAttrList() etc.
/// @param semiHostFile   Path to first extension library or null.
/// @param semiHostSymbol Not used. Set to null.

icmProcessorP icmNewProcessor (
    const char*     name,
    const char*     type,
    Uns32           cpuId,
    Uns32           cpuFlags,
    Uns8            addressBits,
    const char*     modelFile,
    const char*     modelSymbol,
    icmNewProcAttrs procAttrs,
    icmAttrListP    userAttrs,
    const char*     semiHostFile,
    const char*     semiHostSymbol
);

/// Create a new processor instance, associating the passed handle with the
/// newly created processor.
/// @return New processor object.
/// @param name           Name of new processor (string will be copied).
/// @param type           Type of new processor (string will be copied).
///                       Corresponds to the N in the VLNV.
/// @param cpuId          A unique number in the platform for this CPU.
/// @param cpuFlags       Debug flags passed to the model.
/// @param addressBits    Width of the address buses (in bits).
/// @param modelFile      Path to the file containing the model's shared
///                       object(see icmGetVlnvString()).
/// @param modelSymbol    Not used. Set to null.
/// @param procAttrs      Bit-mask of values from ICM_ATTR_... macros.
/// @param userAttrs      List of user defined attributes, constructed using
///                       icmNewAttrList() etc.
/// @param semiHostFile   Path to first extension library or null.
/// @param semiHostSymbol Not used. Set to null.
/// @param handle         User's handle which can be retrieved using
///                       icmGetProcessorHandle().

icmProcessorP icmNewProcessorWithHandle (
    const char*     name,
    const char*     type,
    Uns32           cpuId,
    Uns32           cpuFlags,
    Uns8            addressBits,
    const char*     modelFile,
    const char*     modelSymbol,
    icmNewProcAttrs procAttrs,
    icmAttrListP    userAttrs,
    const char*     semiHostFile,
    const char*     semiHostSymbol,
    void*           handle
);

/// Override the value of a model attribute. This function can be called before
/// the platform is constructed.
/// @return True if parsed without errors.
/// @param target Full path to attribute including platform, instance and
///               attribute names.
/// @param value  New value as a string which will be converted to the
///               correct type.

Bool icmOverride (
    const char* target,
    const char* value
);

/// For internal use only.
/// @param features features.

void icmSetFeatures (
    Uns32 features
);

/// This function is deprecated. Please use icmInitPlatform to create a named
/// platform.
/// @param name Name of platform.

void icmSetPlatformName (
    const char* name
);

/// Set the platform status.
/// @param releaseStatus Enumerated type for release status.
/// @param purpose       Enumerated type for packaging.
/// @param visibility    Controls visibility in debugger and introspection
///                      (zero = visible).

void icmSetPlatformStatus (
    icmReleaseStatus releaseStatus,
    icmPurpose       purpose,
    icmVisibility    visibility
);

/// For internal use only.
/// @param p Parameter One.

void icmSetProduct (
    const char* p
);

/// Synthesize a VLNV path string given the vendor, library, name and version of
/// the library object you wish to load. Similar to icmGetVlnvString, but does
/// not report errors.
/// @return Null if no unique file is found, otherwise a file path.
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT.
/// @param vendor   Vendor directory e.g. yourcompany.com or '*'.
/// @param library  Library directory e.g. processor or '*'.
/// @param name     Name directory e.g. risc32 or '*'.
/// @param version  Version directory e.g. 1.0 or '*'.
/// @param objType  Filename in the version directory or 'pse' or 'model'.

const char* icmTryVlnvString (
    const char* vlnvroot,
    const char* vendor,
    const char* library,
    const char* name,
    const char* version,
    const char* objType
);


#endif /* ICMCONSTRUCT_H */

