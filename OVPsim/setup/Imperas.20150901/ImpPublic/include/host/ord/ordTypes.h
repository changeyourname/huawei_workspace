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

#ifndef ORD_TYPES_H
#define ORD_TYPES_H

//
// Endian enumeration
//
typedef enum ordCpuEndianE {
    CPU_END_ILLEGAL,    // never be this value
    CPU_END_LITTLE,     // little endian
    CPU_END_BIG,        // big endian
    CPU_END_EITHER,     // could be either (applies to a CPU, not to an object file)
    CPU_END_UNSPEC      // does not specify big or little (applies only to an object file)
} ordCpuEndian;

//
// Attributes passed to object file loader.
//
typedef enum ordLoaderAttrsE {
    ORD_LOAD_DEFAULT     = 0x000,    // Default options.
    ORD_LOAD_PHYSICAL    = 0x001,    // Use physical rather than virtual addresses.
    ORD_LOAD_VERBOSE     = 0x002,    // Report each section loaded.
    ORD_ZERO_BSS         = 0x004,    // Zero the BSS segment.
    ORD_SET_START        = 0x008,    // Set processor start address to entry address.
    ORD_LOAD_SYMBOL_ONLY = 0x010,    // Read the symbols but do not modify the memory.
    ORD_READ_FRAMES      = 0x020,    // Load ELF files using VMA addresses instead of LMA.
    ORD_ELF_USE_VMA      = 0x040,    // Load ELF files using VMA addresses instead of LMA.
    ORD_LOAD_SECTIONS    = 0x080,    // Load ELF sections rather than program headers.
    ORD_FAIL_IS_ERROR    = 0x100     // If it fails to load, make this an error.
} ordLoaderAttrs;

//
// Type of a symbol from a target processor object file
//
typedef enum ordSymbolTypeE {
    ORD_SYMBOL_TYPE_SECTION,
    ORD_SYMBOL_TYPE_NONE,
    ORD_SYMBOL_TYPE_OBJECT,
    ORD_SYMBOL_TYPE_FUNC,
    ORD_SYMBOL_TYPE_FILE
} ordSymbolType;

//
// Binding of a symbol from a target processor object file
// in order from weakest to strongest
//
typedef enum ordSymbolBindingE {
    ORD_SYMBOL_BIND_LOCAL,
    ORD_SYMBOL_BIND_WEAK,
    ORD_SYMBOL_BIND_GLOBAL
} ordSymbolBinding;

#endif

