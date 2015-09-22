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


#ifndef ICMOBJECTFILES_H
#define ICMOBJECTFILES_H

#include "icmTypes.h"

/// Add one symbol for address-symbol lookup.
/// @param processor Load into this processor's code address space.
/// @param symbol    The symbol.
/// @param value     Symbol address.
/// @param size      Symbol size in bytes (set to 1 if not known).
/// @param type      Symbol type: 2=function,1=object,0=other.
/// @param binding   Symbol binding: 2=weak,1=global,0=local.

void icmAddSymbol (
    icmProcessorP processor,
    const char*   symbol,
    Addr          value,
    Addr          size,
    int           type,
    int           binding
);

/// Return the ELF code of a loaded file.
/// @return Returns the ELF processor architecture code.
/// @param file Handle of loaded object file.

Uns32 icmGetImagefileElfcode (
    icmImagefileP file
);

/// Return the endianness of a loaded file.
/// @return See icmEndian enumerated type.
/// @param file Handle of loaded object file.

icmEndian icmGetImagefileEndian (
    icmImagefileP file
);

/// Return the start address in the object file.
/// @return Return the start-address (entry point) of a loaded file.
/// @param file Handle of loaded object file.

Addr icmGetImagefileEntry (
    icmImagefileP file
);

/// Install a new object file reader.
/// @return Returns non-zero if successful, zero otherwise.
/// @param filename Name of the loader file.

int icmInstallObjectReader (
    const char* filename
);

/// Load an object directly onto a bus (actually, the memory on the bus).
/// @return A Handle to the objectFile.
/// @param bus        Bus object.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param attrs      Attributes to control how a file is loaded.
/// @param verbose    Output information about the loaded object and its
///                   sections.

icmImagefileP icmLoadBus (
    icmBusP        bus,
    const char*    objectFile,
    icmLoaderAttrs attrs,
    Bool           verbose
);

/// Load the processor memory with an object file.
/// @return A Handle to the objectFile.
/// @param processor  Load into this processor's code address space.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param attrs      Attributes to control how a file is loaded.
/// @param verbose    Output information about the loaded object and its
///                   sections.
/// @param useEntry   Sets the PC of the related processor to the start
///                   address in the object file.

icmImagefileP icmLoadProcessorMemory (
    icmProcessorP  processor,
    const char*    objectFile,
    icmLoaderAttrs attrs,
    Bool           verbose,
    Bool           useEntry
);

/// Load with offset the processor memory with an object file.
/// @return A Handle to the objectFile.
/// @param processor  Load into this processor's code address space.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param attrs      Attributes to control how a file is loaded.
/// @param offset     Offset applied to all addresses.

icmImagefileP icmLoadProcessorMemoryOffset (
    icmProcessorP  processor,
    const char*    objectFile,
    icmLoaderAttrs attrs,
    Addr           offset
);

/// Load the symbols from an object file.
/// @return True if successful.
/// @param processor    Load into this processor's code address space.
/// @param objectFile   Path to the object file (must be a recognized
///                     format).
/// @param loadPhysical If true, physical addresses from the ELF file are
///                     used; otherwise, virtual.

Bool icmLoadSymbols (
    icmProcessorP processor,
    const char*   objectFile,
    Bool          loadPhysical
);

/// Read the header of an object file and find the architecture, endian-ness and
/// entry point.
/// @return True if it was able to read it.
/// @param filename Name of file to load.
/// @param cpuType  Type code (ELF or COFF).
/// @param endianp  Endian code.
/// @param reset    Entry address.

Bool icmReadObjectFileHeader (
    const char * filename,
    Uns16*       cpuType,
    icmEndian*   endianp,
    Addr*        reset
);

/// Read the header of an object file, returning comprehensive information.
/// @return True if able to read it.
/// @param filename Name of file to load.
/// @param info     Pointer to structure filled by this function and defined
///                 in ord/ordObjAttrs.h.

Bool icmReadObjectFileHeaderInfo (
    const char *   filename,
    ordObjectInfoP info
);

/// Read an object file, making callbacks for each region.
/// @return True if successful.
/// @param processor  Processor.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param notifierCB Region callback.
/// @param offset     Load offset.
/// @param userData   User data.

Bool icmReadObjectFileInfo (
    icmProcessorP processor,
    const char*   objectFile,
    ordSectionFn  notifierCB,
    Addr          offset,
    void*         userData
);


#endif /* ICMOBJECTFILES_H */

