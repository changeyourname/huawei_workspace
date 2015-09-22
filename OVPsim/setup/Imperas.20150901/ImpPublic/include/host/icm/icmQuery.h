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


#ifndef ICMQUERY_H
#define ICMQUERY_H

#include "icmTypes.h"

/// Get the child of this node.
/// @return Pointer to child document node, or null.
/// @param node Current document node, or null to get the root.

icmDocNodeP icmDocChildNode (
    icmDocNodeP node
);

/// Is this content or a title?.
/// @return True if this is content, False it it's a title.
/// @param node Document node.

Bool icmDocIsText (
    icmDocNodeP node
);

/// Get the next node.
/// @return Pointer to next document node, or null.
/// @param node Current document node.

icmDocNodeP icmDocNextNode (
    icmDocNodeP node
);

/// Get title or content text from this node (use icmDocIsText to find which it
/// is).
/// @return Pointer to text.
/// @param node Document node.

const char * icmDocText (
    icmDocNodeP node
);

/// Find intercept shared object on a processor.
/// @return The intercept object.
/// @param processor    Processor holding the object.
/// @param instanceName Unique name for this intercept.

icmInterceptP icmFindInterceptObject (
    icmProcessorP processor,
    const char*   instanceName
);

/// Get the handle of an MMC instance from its name.
/// @return Handle of the MMC.
/// @param name The name of the MMC.

icmMmcP icmFindMMCByName (
    const char* name
);

/// Find intercept shared object on a PSE.
/// @return New intercept object.
/// @param processor    PSE holding the object.
/// @param instanceName Unique name for this intercept.

icmInterceptP icmFindPSEInterceptObject (
    icmPseP     processor,
    const char* instanceName
);

/// Get handle to an existing processor object from the current platform.
/// @return Processor object.
/// @param name hierarchical name of processor instance.

icmProcessorP icmFindProcessorByName (
    const char* name
);

/// Find a double attribute by name.
/// @return If found, the pointer is set and True returned.
/// @param attrList Processor object.
/// @param name     The attribute name.
/// @param valp     Pointer to attribute value.

Bool icmFindProcessorDoubleAttribute (
    icmProcessorP attrList,
    const char*   name,
    double*       valp
);

/// Find a net port by name. This can then be written.
/// @return Net Port object.
/// @param processor Processor to search.
/// @param name      Name of net port.

icmNetPortP icmFindProcessorNetPort (
    icmProcessorP processor,
    const char*   name
);

/// Find a string attribute by name.
/// @return The value of the attribute (or null).
/// @param attrList Processor object.
/// @param name     The attribute name.

const char* icmFindProcessorStringAttribute (
    icmProcessorP attrList,
    const char*   name
);

/// Search for an existing PSE by name in the current platform.
/// @return PSE object.
/// @param name Instance name of PSE.

icmPseP icmFindPseByName (
    const char* name
);

/// Find a net port by name. This can then be written.
/// @return Net Port object.
/// @param pse  PSE to search.
/// @param name Name of net port.

icmNetPortP icmFindPseNetPort (
    icmPseP     pse,
    const char* name
);

/// Request a callback for each command in each processor and each plugin.
/// @param commandCB The callback.
/// @param userData  User data to be returned in callback.

void icmGetAllPlatformCommands (
    icmInstalledCommandFn commandCB,
    void*                 userData
);

/// Request a callback for each command in the given processor and each plugin.
/// @param processor Processor handle.
/// @param commandCB The callback.
/// @param userData  User data to be returned in callback.

void icmGetAllProcessorCommands (
    icmProcessorP         processor,
    icmInstalledCommandFn commandCB,
    void*                 userData
);

/// Return the application-specific handle associated with the bus.
/// @return The user's handle.
/// @param bus The bus object.

void* icmGetBusHandle (
    icmBusP bus
);

/// Return the bus port number of address bits.
/// @return Number of address bits.
/// @param busPort Handle to bus port descriptor.

Uns32 icmGetBusPortAddrBits (
    icmBusPortInfoP busPort
);

/// Return the maximum supported number of address bits.
/// @return Maximum number of address bits.
/// @param busPort Handle to bus port descriptor.

Uns32 icmGetBusPortAddrBitsMax (
    icmBusPortInfoP busPort
);

/// Return the minimum supported number of address bits.
/// @return Minimum number of address bits.
/// @param busPort Handle to bus port descriptor.

Uns32 icmGetBusPortAddrBitsMin (
    icmBusPortInfoP busPort
);

/// Return the number of bytes addressed (less one) by the port (if a slave
/// port) or zero (if a master port).
/// @return One less than the number of bytes addressed.
/// @param busPort Handle to bus port descriptor.

Addr icmGetBusPortBytes (
    icmBusPortInfoP busPort
);

/// Return the bus port description descriptor.
/// @return A short description.
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortDesc (
    icmBusPortInfoP busPort
);

/// Return the bus port domain type from the descriptor.
/// @return The type.
/// @param busPort Handle to bus port descriptor.

icmDomainType icmGetBusPortDomainType (
    icmBusPortInfoP busPort
);

/// Return the bus port domain type from the descriptor as a string.
/// @return The type.
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortDomainTypeString (
    icmBusPortInfoP busPort
);

/// Return if this port cannot be left unconnected.
/// @return True if this bus port cannot be left unconnected.
/// @param busPort Handle to bus port descriptor.

Bool icmGetBusPortMustBeConnected (
    icmBusPortInfoP busPort
);

/// Return the bus port name from the descriptor.
/// @return The bus port name (note that this string does not persist).
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortName (
    icmBusPortInfoP busPort
);

/// Return the bus port type from the descriptor.
/// @return The type.
/// @param busPort Handle to bus port descriptor.

icmBusPortType icmGetBusPortType (
    icmBusPortInfoP busPort
);

/// Return the bus port type from the descriptor as a string.
/// @return The type.
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortTypeString (
    icmBusPortInfoP busPort
);

/// Returns the current processor exception description (NULL if the model does
/// not implement or expose exceptions).
/// @return Exception description.
/// @param processor Processor object.

icmExceptionInfoP icmGetException (
    icmProcessorP processor
);

/// Return the model-specific exception code from the descriptor.
/// @return Exception code.
/// @param exceptionInfo Handle to exception object.

Uns32 icmGetExceptionInfoCode (
    icmExceptionInfoP exceptionInfo
);

/// Return the description of the exception from the descriptor.
/// @return Exception description.
/// @param exceptionInfo Handle to exception object.

const char* icmGetExceptionInfoDescription (
    icmExceptionInfoP exceptionInfo
);

/// Return the name of the exception from the descriptor.
/// @return Exception name (note that this string does not persist).
/// @param exceptionInfo Handle to exception object.

const char* icmGetExceptionInfoName (
    icmExceptionInfoP exceptionInfo
);

/// Return application-specific handle associated with the FIFO.
/// @return The user's handle.
/// @param fifo The FIFO object.

void* icmGetFifoHandle (
    icmConnP fifo
);

/// Return the FIFO port's description.
/// @return Brief description.
/// @param fifoPort Handle to FIFO port descriptor.

const char* icmGetFifoPortDesc (
    icmFifoPortInfoP fifoPort
);

/// Return the FIFO port name from the descriptor.
/// @return The FIFO port name (note that this string does not persist).
/// @param fifoPort Handle to FIFO port descriptor.

const char* icmGetFifoPortName (
    icmFifoPortInfoP fifoPort
);

/// Return the FIFO port type (input or output) from the descriptor.
/// @return The FIFO port type (direction of use).
/// @param fifoPort Handle to FIFO port descriptor.

icmFifoPortType icmGetFifoPortType (
    icmFifoPortInfoP fifoPort
);

/// Return the FIFO port type (input or output) from the descriptor.
/// @return The FIFO port type (direction of use) as a string.
/// @param fifoPort Handle to FIFO port descriptor.

const char* icmGetFifoPortTypeString (
    icmFifoPortInfoP fifoPort
);

/// Return the FIFO port width (in bits) from the descriptor.
/// @return The FIFO port Width, in bits.
/// @param fifoPort Handle to FIFO port descriptor.

Uns32 icmGetFifoPortWidth (
    icmFifoPortInfoP fifoPort
);

/// Get the name of an intercept shared object.
/// @return Name of intercept object (note that this string does not
///         persist).
/// @param intercept Intercept object handle.

const char* icmGetInterceptObjectName (
    icmInterceptP intercept
);

/// Return the current release status of this intercept shared object.
/// @return Release status (enumerated type).
/// @param intercept intercept object.

icmReleaseStatus icmGetInterceptObjectReleaseStatus (
    icmInterceptP intercept
);

/// Return the current visibility of this intercept shared object.
/// @return Current visibility.
/// @param intercept intercept object.

icmVisibility icmGetInterceptObjectVisibility (
    icmInterceptP intercept
);

/// Get the VLNV spec of this intercept object.
/// @return Pointer to VLNV structure.
/// @param intercept Intercept object handle.

icmVlnvP icmGetInterceptVlnv (
    icmInterceptP intercept
);

/// Get the instance name of this MMC.
/// @return The hierarchical name.
/// @param mmc MMC object.

const char * icmGetMMCName (
    icmMmcP mmc
);

/// Return the current release status of this MMC.
/// @return Release status (enumerated type).
/// @param mmc MMC object.

icmReleaseStatus icmGetMMCReleaseStatus (
    icmMmcP mmc
);

/// Return the visibility of the model.
/// @return instance visibility.
/// @param mmc MMC object.

icmVisibility icmGetMMCVisibility (
    icmMmcP mmc
);

/// Get the VLNV spec of this MMC.
/// @return Pointer to VLNV structure.
/// @param mmc MMC object.

icmVlnvP icmGetMMCVlnv (
    icmMmcP mmc
);

/// Return the user's handle associated with the memory.
/// @return User's handle.
/// @param memory Return application-specific handle associated with the
///               memory.

void* icmGetMemoryHandle (
    icmMemoryP memory
);

/// Returns the current processor mode description (NULL if the model does not
/// implement or expose modes).
/// @return Mode description.
/// @param processor Processor object.

icmModeInfoP icmGetMode (
    icmProcessorP processor
);

/// Return the model-specific mode code from the descriptor.
/// @return Mode code.
/// @param modeInfo Handle to mode object.

Uns32 icmGetModeInfoCode (
    icmModeInfoP modeInfo
);

/// Return the description of the mode from the descriptor.
/// @return Mode description.
/// @param modeInfo Handle to mode object.

const char* icmGetModeInfoDescription (
    icmModeInfoP modeInfo
);

/// Return the name of the mode from the descriptor.
/// @return Mode name (note that this string does not persist).
/// @param modeInfo Handle to mode object.

const char* icmGetModeInfoName (
    icmModeInfoP modeInfo
);

/// Return application-specific handle associated with the net.
/// @return The user's handle.
/// @param net The net object.

void* icmGetNetHandle (
    icmNetP net
);

/// Return the net port description.
/// @return A short description.
/// @param netPort Handle to net port descriptor.

const char* icmGetNetPortDesc (
    icmNetPortInfoP netPort
);

/// Returns true if this netport must be connected for the model to function.
/// @return True if must be connected.
/// @param netPort Handle to net port descriptor.

Bool icmGetNetPortMustBeConnected (
    icmNetPortInfoP netPort
);

/// Return the net port name from the descriptor.
/// @return The net port name (note that this string does not persist).
/// @param netPort Handle to net port descriptor.

const char* icmGetNetPortName (
    icmNetPortInfoP netPort
);

/// Return the net port type from the descriptor.
/// @return The type.
/// @param netPort Handle to net port descriptor.

icmNetPortType icmGetNetPortType (
    icmNetPortInfoP netPort
);

/// Return the net port type from the descriptor, as a string.
/// @return The type.
/// @param netPort Handle to net port descriptor.

const char* icmGetNetPortTypeString (
    icmNetPortInfoP netPort
);

/// Returns the next processor exception description, given the previous
/// description. Pass NULL to get the first description.
/// @return Next exception description.
/// @param processor Processor object.
/// @param previous  Previous exception description, or null to start off.

icmExceptionInfoP icmGetNextException (
    icmProcessorP     processor,
    icmExceptionInfoP previous
);

/// Return the next parameter description.
/// @return Pointer to parameter info.
/// @param intercept Intercept object handle.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextInterceptParamInfo (
    icmInterceptP intercept,
    icmParamInfoP paramInfo
);

/// Return the next bus port description.
/// @return Pointer to bus port info.
/// @param mmc     MMC object.
/// @param busPort Handle to previous bus port descriptor or null to start.

icmBusPortInfoP icmGetNextMMCBusPortInfo (
    icmMmcP         mmc,
    icmBusPortInfoP busPort
);

/// Return the next parameter description.
/// @return Pointer to parameter info.
/// @param mmc       MMC object.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextMMCParamInfo (
    icmMmcP       mmc,
    icmParamInfoP paramInfo
);

/// Returns the next processor mode description, given the previous description.
/// Pass NULL to get the first description.
/// @return Next mode description.
/// @param processor Processor object.
/// @param previous  Previous mode description, or null to start off.

icmModeInfoP icmGetNextMode (
    icmProcessorP processor,
    icmModeInfoP  previous
);

/// Return the next bus port description.
/// @return Pointer to bus port info.
/// @param pse     PSE object.
/// @param busPort Handle to previous bus port descriptor or null to start.

icmBusPortInfoP icmGetNextPSEBusPortInfo (
    icmPseP         pse,
    icmBusPortInfoP busPort
);

/// Return the next bus port description.
/// @return Pointer to net port info.
/// @param pse     PSE object.
/// @param netPort Handle to previous net port descriptor or null to start.

icmNetPortInfoP icmGetNextPSENetPortInfo (
    icmPseP         pse,
    icmNetPortInfoP netPort
);

/// Return the next bus port description.
/// @return Pointer to net port info.
/// @param pse     PSE object.
/// @param netPort Handle to previous packetnet port or null to start.

icmPacketnetPortP icmGetNextPSEPacketnetPort (
    icmPseP           pse,
    icmPacketnetPortP netPort
);

/// Return the next parameter description.
/// @return Pointer to parameter info.
/// @param pse       PSE object.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextPSEParamInfo (
    icmPseP       pse,
    icmParamInfoP paramInfo
);

/// Return the next enum value of a parameter descriptor.
/// @return The enum.
/// @param paramInfo Handle to parameter.
/// @param e         Handle to current enum, or null to begin.

icmParamEnumP icmGetNextParamEnum (
    icmParamInfoP paramInfo,
    icmParamEnumP e
);

/// Return the next bus port description.
/// @return The next bus port descriptor.
/// @param processor Processor object.
/// @param busPort   Handle to previous bus port descriptor or null to start.

icmBusPortInfoP icmGetNextProcessorBusPortInfo (
    icmProcessorP   processor,
    icmBusPortInfoP busPort
);

/// Return the next FIFO port description.
/// @return The next FIFO port descriptor.
/// @param processor Processor object.
/// @param fifoPort  Handle to previous FIFO port descriptor or null to
///                  begin.

icmFifoPortInfoP icmGetNextProcessorFifoPortInfo (
    icmProcessorP    processor,
    icmFifoPortInfoP fifoPort
);

/// Return the next net port description.
/// @return The next net port descriptor.
/// @param processor Processor object.
/// @param netPort   Handle to previous net port descriptor or null to begin.

icmNetPortInfoP icmGetNextProcessorNetPortInfo (
    icmProcessorP   processor,
    icmNetPortInfoP netPort
);

/// Return the next parameter description.
/// @return The next parameter.
/// @param processor Processor object.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextProcessorParamInfo (
    icmProcessorP processor,
    icmParamInfoP paramInfo
);

/// Returns the next processor register description, given the previous
/// description. Pass NULL to get the first register description.
/// @return Next register object.
/// @param processor Processor object.
/// @param previous  Previous register object, or null to start off.

icmRegInfoP icmGetNextReg (
    icmProcessorP processor,
    icmRegInfoP   previous
);

/// Returns the next processor register group description, given the previous
/// description. Pass NULL to get the first register description.
/// @return Next register group object.
/// @param processor Processor object.
/// @param previous  Previous register group object, or null to start off.

icmRegGroupP icmGetNextRegGroup (
    icmProcessorP processor,
    icmRegGroupP  previous
);

/// Returns the next processor register description in the passed group, given
/// the previous description. Pass NULL to get the first register description.
/// @return Next register object.
/// @param processor Processor object.
/// @param group     Group object.
/// @param previous  Previous register object, or null to start off.

icmRegInfoP icmGetNextRegInGroup (
    icmProcessorP processor,
    icmRegGroupP  group,
    icmRegInfoP   previous
);

/// Return the documentation for this PSE.
/// @return The root documentation node.
/// @param pse PSE object.

icmDocNodeP icmGetPSEDoc (
    icmPseP pse
);

/// Return application-specific handle associated with the PSE.
/// @return The user's handle.
/// @param pse PSE object.

void* icmGetPSEHandle (
    icmPseP pse
);

/// Return the name of the PSE.
/// @return The PSE name (note that this string does not persist).
/// @param pse PSE object.

const char* icmGetPSEName (
    icmPseP pse
);

/// Return the current release status of this PSE.
/// @return Release status (enumerated type).
/// @param pse PSE object.

icmReleaseStatus icmGetPSEReleaseStatus (
    icmPseP pse
);

/// Return true if this model reports that it supports save/restore.
/// @return True if supported.
/// @param pse PSE object.

Bool icmGetPSESaveRestoreSupported (
    icmPseP pse
);

/// Is the PSE visible (models can choose to hide themselves).
/// @return PSE visibility.
/// @param pse PSE object.

icmVisibility icmGetPSEVisibility (
    icmPseP pse
);

/// Get the VLNV spec of this PSE.
/// @return Pointer to VLNV Structure.
/// @param pse PSE object.

icmVlnvP icmGetPSEVlnv (
    icmPseP pse
);

/// Return the minimum number of bytes allowed on a packetnet.
/// @return The name of the packetnet.
/// @param packetnet The packetnet object.

Uns32 icmGetPacketnetMaxBytes (
    icmPacketnetP packetnet
);

/// Return the name of a packetnet.
/// @return The name of the packetnet.
/// @param packetnet The packetnet object.

const char* icmGetPacketnetName (
    icmPacketnetP packetnet
);

/// Return the description of a packetnet port, if it exists.
/// @return Description string.
/// @param netPort Handle to packetnet port.

const char * icmGetPacketnetPortDesc (
    icmPacketnetPortP netPort
);

/// Return true if the model reports that this packetnetport must be connected
/// for the model to function.
/// @return True if must be connected, false if optional.
/// @param netPort Handle to packetnet port.

Bool icmGetPacketnetPortMustBeConnected (
    icmPacketnetPortP netPort
);

/// Return the name of a packetnet port.
/// @return Name string.
/// @param netPort Handle to packetnet port.

const char * icmGetPacketnetPortName (
    icmPacketnetPortP netPort
);

/// Return the net connected to this port.
/// @return The connected net or null.
/// @param netPort Handle to packetnet port.

icmPacketnetP icmGetPacketnetPortNet (
    icmPacketnetPortP netPort
);

/// Return the parameter description from the descriptor.
/// @return A short description.
/// @param paramInfo Handle to parameter.

const char* icmGetParamDesc (
    icmParamInfoP paramInfo
);

/// Return the enum description.
/// @return The enumeration description.
/// @param e Handle to current enum.

const char* icmGetParamEnumDesc (
    icmParamEnumP e
);

/// Return the enum name.
/// @return The name of enumeration.
/// @param e Handle to current enum.

const char* icmGetParamEnumName (
    icmParamEnumP e
);

/// Return the enum value.
/// @return The enumeration value.
/// @param e Handle to current enum.

Uns32 icmGetParamEnumValue (
    icmParamEnumP e
);

/// Return the parameter name from the descriptor.
/// @return The parameter name.
/// @param paramInfo Handle to parameter.

const char* icmGetParamName (
    icmParamInfoP paramInfo
);

/// Return the parameter type from the descriptor.
/// @return The type.
/// @param paramInfo Handle to parameter.

icmParamType icmGetParamType (
    icmParamInfoP paramInfo
);

/// Return the parameter type from the descriptor as a string.
/// @return The type.
/// @param paramInfo Handle to parameter.

const char* icmGetParamTypeString (
    icmParamInfoP paramInfo
);

/// Return the current platform name.
/// @return Name of platform.

const char* icmGetPlatformName (void);

/// Return the purpose of this platform.
/// @return Platform purpose (enumerated type).

icmPurpose icmGetPlatformPurpose (void);

/// Return the current release status of this platform.
/// @return Release status (enumerated type).

icmReleaseStatus icmGetPlatformReleaseStatus (void);

/// Find the data bus connected to this processor.
/// @return The data bus.
/// @param processor The bus object.

icmBusP icmGetProcessorDataBus (
    icmProcessorP processor
);

/// Get the semihost library to be used by default with this processor.
/// @return Pointer to semihost library VLNV structure.
/// @param processor Processor handle.

icmVlnvP icmGetProcessorDefaultSemihost (
    icmProcessorP processor
);

/// Return a description of this processor in the CPU model.
/// @return Single name indicating this processor's function in the model.
///         e.g. TC, VPE, CPU, CMP.
/// @param processor Handle to this processor.

const char* icmGetProcessorDesc (
    icmProcessorP processor
);

/// Get the root document node of this processor.
/// @return Pointer to root document node.
/// @param processor Processor handle.

icmDocNodeP icmGetProcessorDoc (
    icmProcessorP processor
);

/// Get the ELF codes supported by this processor.
/// @return Number of elf codes supported by this processor.
/// @param processor  Processor handle.
/// @param codes      Array of codes to be filled in by this call.
/// @param maxCodes   Size of the array to be filled.
/// @param defaultElf This is the default processor for this ELF code (no
///                   longer used).

Uns32 icmGetProcessorElfcode (
    icmProcessorP processor,
    Uns32*        codes,
    Uns32         maxCodes,
    Bool*         defaultElf
);

/// Get the endian supported by this processor.
/// @return Endian supported by this processor.
/// @param processor Processor handle.

icmEndian icmGetProcessorEndian (
    icmProcessorP processor
);

/// Get the Family name of this processor.
/// @return Family name of this processor or null if not defined.
/// @param processor Processor handle.

const char * icmGetProcessorFamily (
    icmProcessorP processor
);

/// Get any flags required for this GDB.
/// @return GDB Flags.
/// @param processor Processor handle.

const char* icmGetProcessorGdbFlags (
    icmProcessorP processor
);

/// Get the GDB to be used with this processor.
/// @return Path to GDB.
/// @param processor Processor handle.

const char* icmGetProcessorGdbPath (
    icmProcessorP processor
);

/// Get the group name of this processor.
/// @return Group name (more significant) of this processor or null if not
///         defined.
/// @param processor Processor handle.

const char * icmGetProcessorGroupH (
    icmProcessorP processor
);

/// Get the group name of this processor.
/// @return Group name (less significant) of this processor or null if not
///         defined.
/// @param processor Processor handle.

const char * icmGetProcessorGroupL (
    icmProcessorP processor
);

/// Return application-specific handle associated with the processor.
/// @return The user-supplied handle.
/// @param processor The processor return by icmNewProcessorWithHandle().

void* icmGetProcessorHandle (
    icmProcessorP processor
);

/// Get the CPU Helper library to be used by the VAP tools with this processor.
/// @return Pointer to helper VLNV structure.
/// @param processor Processor handle.

icmVlnvP icmGetProcessorHelper (
    icmProcessorP processor
);

/// Find the instruction bus connected to this processor.
/// @return The instruction bus.
/// @param processor The bus object.

icmBusP icmGetProcessorInstructionBus (
    icmProcessorP processor
);

/// Does this processor always require the use of physical addresses?.
/// @return True if physical addresses required (legacy feature).
/// @param processor Processor handle.

Bool icmGetProcessorLoadPhysical (
    icmProcessorP processor
);

/// Return the processor name.
/// @return Processor name (note that this string does not persist).
/// @param processor Processor object.
/// @param delimiter Use this string to delimit platform hierarchy. The '/'
///                  forward slash is default.

const char* icmGetProcessorName (
    icmProcessorP processor,
    const char*   delimiter
);

/// Is this processor qualified to run in QL mode?.
/// @return Processor supports QL Mode.
/// @param processor Processor handle.

Bool icmGetProcessorQLQualified (
    icmProcessorP processor
);

/// Return the current release status of this processor.
/// @return Release status (enumerated type).
/// @param processor Processor object.

icmReleaseStatus icmGetProcessorReleaseStatus (
    icmProcessorP processor
);

/// Get the current variant of this processor instance.
/// @return Current variant of this processor or null if not defined.
/// @param processor Processor handle.

const char * icmGetProcessorVariant (
    icmProcessorP processor
);

/// Is the processor visible (models can choose to hide themselves).
/// @return Processor visibility.
/// @param processor Processor object.

icmVisibility icmGetProcessorVisibility (
    icmProcessorP processor
);

/// Get the VLNV spec of this processor.
/// @return Pointer to VLNV structure.
/// @param processor Processor handle.

icmVlnvP icmGetProcessorVlnv (
    icmProcessorP processor
);

/// Search for a register by its index.
/// @return The register object.
/// @param processor Processor object.
/// @param index     Register index (see VMI API).

icmRegInfoP icmGetRegByIndex (
    icmProcessorP processor,
    Uns32         index
);

/// Search for a register by its name.
/// @return The register object.
/// @param processor Processor object.
/// @param name      Register name.

icmRegInfoP icmGetRegByName (
    icmProcessorP processor,
    const char*   name
);

/// Search for a register by its usage.
/// @return The register object.
/// @param processor Processor object.
/// @param usage     Register usage.

icmRegInfoP icmGetRegByUsage (
    icmProcessorP processor,
    icmRegUsage   usage
);

/// Search for a register group by its name.
/// @return The register group object.
/// @param processor Processor object.
/// @param name      Register name.

icmRegGroupP icmGetRegGroupByName (
    icmProcessorP processor,
    const char*   name
);

/// Return the name of the register group from the descriptor.
/// @return Register name (note that this string does not persist).
/// @param group Handle to register group object.

const char* icmGetRegGroupName (
    icmRegGroupP group
);

/// Return the read/write accessibility of the register from the descriptor.
/// @return Register accessibility enumerated type.
/// @param regInfo Handle to register object.

icmRegAccess icmGetRegInfoAccess (
    icmRegInfoP regInfo
);

/// Return the size of the register from the descriptor.
/// @return Register size in bits.
/// @param regInfo Handle to register object.

Uns32 icmGetRegInfoBits (
    icmRegInfoP regInfo
);

/// Return the register description.
/// @return Short description.
/// @param regInfo Handle to register object.

const char * icmGetRegInfoDesc (
    icmRegInfoP regInfo
);

/// Return the register GDB index.
/// @return Index number.
/// @param regInfo Handle to register object.

Uns32 icmGetRegInfoGdbIndex (
    icmRegInfoP regInfo
);

/// Return the register group for the register.
/// @return Register group.
/// @param regInfo Handle to register object.

icmRegGroupP icmGetRegInfoGroup (
    icmRegInfoP regInfo
);

/// Return the name of the register from the descriptor.
/// @return Register name (note that this string does not persist).
/// @param regInfo Handle to register object.

const char* icmGetRegInfoName (
    icmRegInfoP regInfo
);

/// Return if the register is read-only (deprecated: use icmGetRegInfoAccess).
/// @return Is read-only.
/// @param regInfo Handle to register object.

Bool icmGetRegInfoReadOnly (
    icmRegInfoP regInfo
);

/// Return the type of the register from the descriptor.
/// @return Register usage enumerated type.
/// @param regInfo Handle to register object.

icmRegUsage icmGetRegInfoUsage (
    icmRegInfoP regInfo
);

/// Return the type of the register, as a string, from the descriptor.
/// @return Register usage enumerated type.
/// @param regInfo Handle to register object.

const char* icmGetRegInfoUsageString (
    icmRegInfoP regInfo
);

/// Return the first child of the passed SMP processor.
/// @return SMP first child.
/// @param processor The processor object.

icmProcessorP icmGetSMPChild (
    icmProcessorP processor
);

/// Return a pointer to processor data. Use instead of casting the
/// vmiProcessorP.
/// @return Return a pointer to the processor data (beginning with
///         registers).
/// @param processor The processor object.

void* icmGetSMPData (
    icmProcessorP processor
);

/// Return the index number of the passed SMP processor.
/// @return Unique (within this processor cluster) index number.
/// @param processor The processor object.

Uns32 icmGetSMPIndex (
    icmProcessorP processor
);

/// Return the next sibling of the passed SMP processor.
/// @return SMP next sibling.
/// @param processor The processor object.

icmProcessorP icmGetSMPNextSibling (
    icmProcessorP processor
);

/// Return the parent of the passed SMP processor.
/// @return SMP parent.
/// @param processor The processor object.

icmProcessorP icmGetSMPParent (
    icmProcessorP processor
);

/// Return the previous sibling of the passed SMP processor.
/// @return SMP previous sibling.
/// @param processor The processor object.

icmProcessorP icmGetSMPPrevSibling (
    icmProcessorP processor
);

/// Apply the callback to all children of the processor object.
/// @param processor The processor object.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void icmIterAllChildren (
    icmProcessorP    processor,
    icmSMPIteratorFn iterCB,
    void*            userData
);

/// Apply the callback to all descendants of the processor object.
/// @param processor The processor object.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void icmIterAllDescendants (
    icmProcessorP    processor,
    icmSMPIteratorFn iterCB,
    void*            userData
);

/// Call for all parameters of models using in the platform.
/// @param fn   Function to be called with each attribute.
/// @param user Data passed to function.

void icmIterAllModelParameters (
    icmParamFn fn,
    void*      user
);

/// Apply the callback to the processor and all its descendants.
/// @param processor The processor object.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void icmIterAllProcessors (
    icmProcessorP    processor,
    icmSMPIteratorFn iterCB,
    void*            userData
);

/// Call for all user defined attributes in the platform.
/// @param fn   Function to be called with each attribute.
/// @param user Data passed to function.

void icmIterAllUserAttributes (
    icmAttrFn fn,
    void*     user
);

/// Returns the number of bits in a memory mapped register.
/// @return Number of bits in the register (will be a multiple of 8).
/// @param info Register info.

Uns32 icmMMRegBits (
    icmMMRegInfoP info
);

/// Returns the memory mapped register short description.
/// @return A short description of the memory mapped register.
/// @param info Register info.

const char * icmMMRegDescription (
    icmMMRegInfoP info
);

/// Returns the memory mapped register name.
/// @return Memory mapped register name.
/// @param info Register info.

const char * icmMMRegName (
    icmMMRegInfoP info
);

/// Returns the offset in bytes from the base of the bus port.
/// @return Offset in bytes from the base of the bus port.
/// @param info Register info.

Addr icmMMRegOffset (
    icmMMRegInfoP info
);

/// Return netPort direction.
/// @return Direction.
/// @param netPort The net port.

icmDirection icmNetPortDirection (
    icmNetPortP netPort
);

/// Return netPort name.
/// @return Name of net port (note that this string does not persist).
/// @param netPort The net port.

const char* icmNetPortName (
    icmNetPortP netPort
);

/// Returns the next memory mapped register information given the previous. Pass
/// NULL to get the first register from a bus port.
/// @return Next register object.
/// @param busPort  Bus Port.
/// @param previous Previous register object, or null to start.

icmMMRegInfoP icmNextBusPortMMRegInfo (
    icmBusPortInfoP busPort,
    icmMMRegInfoP   previous
);

/// Get the next intercept shared object on a processor.
/// @return Next intercept object.
/// @param processor Processor holding the object.
/// @param previous  Previous intercept or null.

icmInterceptP icmNextInterceptObject (
    icmProcessorP processor,
    icmInterceptP previous
);

/// Iterate each of the MMCs in a platform.
/// @return Next MMC or null to begin.
/// @param mmc The current MMC or null if starting.

icmMmcP icmNextMmc (
    icmMmcP mmc
);

/// Iterate each of the processors in a platform.
/// @return Next processor or null to begin.
/// @param processor The current processor or null if starting.

icmProcessorP icmNextProcessor (
    icmProcessorP processor
);

/// Get next netPort of a processor.
/// @return Next port or null if last one.
/// @param processor The processor.
/// @param current   Current port or null if starting.

icmNetPortP icmNextProcessorNetPort (
    icmProcessorP processor,
    icmNetPortP   current
);

/// Iterate each of the PSEs in a platform.
/// @return The next PSE (or null if no more).
/// @param pse The current PSE or null if starting.

icmPseP icmNextPse (
    icmPseP pse
);

/// Get next netPort of a PSE.
/// @return Next port or null if last one.
/// @param pse     The PSE.
/// @param current Current port or null if starting.

icmNetPortP icmNextPseNetPort (
    icmPseP     pse,
    icmNetPortP current
);

/// Print the master and slave connections on a bus.

void icmPrintAllBusConnections (void);

/// Print the connections on all packetnets.

void icmPrintAllPacketnetConnections (void);

/// Print the master and slave connections on a bus.
/// @param bus The bus object.

void icmPrintBusConnections (
    icmBusP bus
);

/// Print a summary of nets and their connections.

void icmPrintNetConnections (void);

/// Return true if this processor can run code.
/// @return True if can run code.
/// @param processor The processor object.

Bool icmSMPIsLeaf (
    icmProcessorP processor
);


#endif /* ICMQUERY_H */

