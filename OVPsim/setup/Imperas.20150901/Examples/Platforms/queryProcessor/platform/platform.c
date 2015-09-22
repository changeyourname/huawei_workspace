/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

/*
 * This example shows how information can be extracted from a processor model.
 * This information can be used to
 *     : create documentation
 *     : build a platform that makes few assumptions about the model.
 *     : build a debugger that adapts to the model.
 *
 * Note that each processor model can return different information, as can
 * different variants of the same model.
 *
 * Note that some functions shown here that return human readable strings have
 * sister functions that return enumerated types. You should not have to compare
 * strings to identify the types of registers, ports, modes etc.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"


// local function definition
//   Instances a processor model
//   Uses the icm query functions to obtain information about it's
//      Buses
//      Nets
//      Registers
//      Exceptions
//      Modes
//      Parameters
//      Description
//      Info
//      Documentation

static void queryProcessor(
	const char *instance,
	const char *vendor,
	const char *name,
    const char *endian,
	const char *variant);

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {

    // Check each model exists before the query
    queryProcessor("i0", "arm.ovpworld.org",  "arm",    "little", "ARM920T"   );
    queryProcessor("i1", "arm.ovpworld.org",  "arm",    "little", "Cortex-A8" );
    queryProcessor("i2", "arm.ovpworld.org",  "arm",    "little",  NULL       );

    queryProcessor("i3", "arm.ovpworld.org",  "armm",   "little", "Cortex-M3" );
    queryProcessor("i4", "arm.ovpworld.org",  "armm",   "little",  NULL       );

    queryProcessor("i5", "mips.ovpworld.org", "mips32", "little", "4Kc"       );
    queryProcessor("i6", "mips.ovpworld.org", "mips32", "little", "24Kf"      );
    queryProcessor("i7", "mips.ovpworld.org", "mips32", "little", "74Kf"      );
    queryProcessor("i8", "mips.ovpworld.org", "mips32", "little",  NULL       );

    queryProcessor("i9", "xilinx.ovpworld.org", "microblaze", "little", NULL  );
    queryProcessor("i10", "ovpworld.org",      "or1k",        NULL,     NULL  );

    return 0;
}


//
// Callback for register query. This gets information about each register and how
// it can be used.
//
static ICM_SMP_ITERATOR_FN(queryRegistersCB) {

    icmPrintf("  REGISTERS\n");

    icmRegGroupP group = NULL;

    // Are the registers in groups
    if(!icmGetNextRegGroup(processor, group)) {

        // no register groups
        icmRegInfoP reg = NULL;

        if(!icmGetNextReg(processor, reg)) {

            icmPrintf("  NO REGISTER INFORMATION\n");

        } else {

            while((reg=icmGetNextReg(processor, reg))) {

                const char *name     = icmGetRegInfoName(reg);
                const char *desc     = icmGetRegInfoDesc(reg);
                Uns32 regbits        = icmGetRegInfoBits(reg);

                // Usage as a string, (see icmGetRegInfoUsage)
                const char *use      = icmGetRegInfoUsageString(reg);

                const char *readonly = icmGetRegInfoReadOnly(reg) ? "readonly" : "readwrite";

                icmPrintf("    REGISTER (%2d bits) %-15s %-25s %-10s", regbits, use, name, readonly);
                if (desc) {
                    icmPrintf(" (%s)", desc);
                }
                icmPrintf("\n");
            }
        }

    } else {
        // iterate over register groups
        while((group=icmGetNextRegGroup(processor, group))) {

            icmPrintf("  GROUP %s\n", icmGetRegGroupName(group));

            icmRegInfoP reg = NULL;

            if(!icmGetNextRegInGroup(processor, group, reg)) {

                icmPrintf("    NO REGISTER INFORMATION\n");

            } else {

                while((reg=icmGetNextRegInGroup(processor, group, reg))) {

                    const char *name     = icmGetRegInfoName(reg);
                    const char *desc     = icmGetRegInfoDesc(reg);
                    Uns32 regbits        = icmGetRegInfoBits(reg);

                    // Usage as a string, (see icmGetRegInfoUsage)
                    const char *use      = icmGetRegInfoUsageString(reg);

                    const char *readonly = icmGetRegInfoReadOnly(reg) ? "readonly" : "readwrite";
                    icmPrintf("    REGISTER (%2d bits) %-15s %-25s %-10s", regbits, use, name, readonly);
                    if (desc) {
                        icmPrintf(" (%s)", desc);
                    }
                    icmPrintf("\n");
                }
            }
        }
    }
    icmPrintf("\n");
}

//
// Query registers and register groups in the passed processor. This information can be used
// by a debugger to get a list of registers, their types, sizes (and values).
//
static void queryRegisters(icmProcessorP processor) {
    queryRegistersCB(processor, 0);
    icmIterAllDescendants(processor, queryRegistersCB, 0);
}

//
// Callback for exception query
//
static ICM_SMP_ITERATOR_FN(queryExceptionsCB) {

    if(!icmGetNextException(processor, 0)) {

        icmPrintf("  NO EXCEPTION INFORMATION\n");

    } else {

        icmPrintf("  EXCEPTIONS\n");

        icmExceptionInfoP info = NULL;
        icmExceptionInfoP current = icmGetException(processor);

        while((info=icmGetNextException(processor, info))) {
            icmPrintf(
                "    %-15s (code %u)%s\n",
                icmGetExceptionInfoName(info),
                icmGetExceptionInfoCode(info),
                (info==current?" [current]" : "")
            );
        }
    }

    icmPrintf("\n");
}

//
// Query exceptions in the passed processor
//
static void queryExceptions(icmProcessorP processor) {
    queryExceptionsCB(processor, 0);
    icmIterAllDescendants(processor, queryExceptionsCB, 0);
}

//
// Callback for mode query
//
static ICM_SMP_ITERATOR_FN(queryModesCB) {

    if(!icmGetNextMode(processor, 0)) {

        icmPrintf("  NO MODE INFORMATION\n");

    } else {

        icmPrintf("  MODES\n");

        icmModeInfoP info = NULL;

        while((info=icmGetNextMode(processor, info))) {
            const char *current = (icmGetMode(processor) == info) ? " [current]" : "";
            const char *name    = icmGetModeInfoName(info);
            Uns32       code    = icmGetModeInfoCode(info);
            const char *desc    = icmGetModeInfoDescription(info);

            icmPrintf("  %-15s (code %u) %s", name,code, current);
            if (desc) {
                icmPrintf(" (%s)", desc);
            }
            icmPrintf("\n");
        }

    }

    icmPrintf("\n");
}

//
// Query modes in the passed processor
//
static void queryModes(icmProcessorP processor) {
    queryModesCB(processor, 0);
    icmIterAllDescendants(processor, queryModesCB, 0);
}

//
// Query parameters (special case for enumerated values)
//
static void enums(icmParamInfoP param) {
    icmPrintf("        ENUMS: ");
    icmParamEnumP e = NULL;
    while((e = icmGetNextParamEnum(param, e))) {
        const char *name = icmGetParamEnumName(e);
        const char *desc = icmGetParamEnumDesc(e);
        Uns32       val  = icmGetParamEnumValue(e);
        icmPrintf("\n           %3d = %s", val, name);
        if (desc) {
            icmPrintf(" (%s)", desc);
        }
    }
    icmPrintf("\n");
}

static void queryParameters(icmProcessorP processor) {

    icmPrintf("  PARAMETERS\n");

    icmParamInfoP param = NULL;
    while( (param = icmGetNextParamInfo(processor, param))) {
        const char  *name = icmGetParamName(param);

        // Usage as a string (see icmGetParamType)
        const char  *type = icmGetParamTypeString(param);

        const char  *desc = icmGetParamDesc(param);


        icmPrintf("    PARAMETER: %-35s %-15s", name, type );
        if (desc) {
            icmPrintf(" (%s)", desc);
        }
        icmPrintf("\n");
        if (icmGetParamType(param) == ICM_PT_ENUM) {
            enums(param);
        }
    }
    icmPrintf("\n");
}

static void queryBuses(icmProcessorP processor) {

    icmPrintf(" BUSES\n");

    icmBusPortInfoP busport = NULL;
    while( (busport = icmGetNextBusPortInfo(processor, busport))) {
        const char  *name = icmGetBusPortName(busport);
        const char  *desc = icmGetBusPortDesc(busport);

        // Usage as a string (see icmGetBusPortType)
        const char  *type = icmGetBusPortTypeString(busport);

        Uns32        minBits = icmGetBusPortAddrBitsMin(busport);
        Uns32        maxBits = icmGetBusPortAddrBitsMax(busport);

        icmPrintf("    BUS %-20s %-20s (%d-%d bits)", type, name, minBits, maxBits);
        if (desc) {
            icmPrintf(" (%s)", desc);
        }
        icmPrintf("\n");
    }
    icmPrintf("\n");
}

static void queryNets(icmProcessorP processor) {

    icmPrintf("  NETS\n");

    icmNetPortInfoP netport = NULL;
    while( (netport = icmGetNextNetPortInfo(processor, netport))) {
        const char  *name = icmGetNetPortName(netport);
        const char  *desc = icmGetNetPortDesc(netport);

        // Usage as a string (see icmGetNetPortType)
        const char  *type = icmGetNetPortTypeString(netport);

        icmPrintf("    NET %-20s %-20s ", type, name);
        if (desc) {
            icmPrintf(" (%s)", desc);
        }
        icmPrintf("\n");
    }
    icmPrintf("\n");
}

static void spaces(Uns32 num) {
    while(num--) {
        icmPrintf(" ");
    }
}

//
// Print the description and name of this processor, then recursively find all children
// Note the the description field is optional and is generally missing from single-core processors.
//
static void queryDescriptionCB(icmProcessorP processor, Uns32 depth) {

    const char *desc = icmGetProcessorDesc(processor);
    const char *name = icmGetProcessorName(processor, "");

    spaces(depth);
    icmPrintf("        %s:%s\n", name, desc ?: "(no description)");

    icmProcessorP ch;
    for (ch= icmGetSMPChild(processor); ch ; ch = icmGetSMPNextSibling(ch)) {
        queryDescriptionCB(ch, depth +4);
    }
}

static void queryDescription(icmProcessorP processor) {
    icmPrintf("    HIERARCHY\n");
    queryDescriptionCB(processor, 0);
    icmPrintf("\n");
}

static void printVLNV(const char *what, icmVlnvP vlnv) {
    if(vlnv) {
        icmPrintf("%s %s/%s/%s/%s\n", what, vlnv->vendor, vlnv->library, vlnv->name, vlnv->version);
    }
}

//
// Get other information embedded in the model
//
static void queryInfo(icmProcessorP processor) {

    // the path to the gdb in the Imperas installation
    // This will select the correct gdb regardless of processor variant, host OS etc..,.
    const char *gdbpath     = icmGetProcessorGdbPath(processor);

    // Any special flags required by the gdb when used in this context.
    const char *gdbflags    = icmGetProcessorGdbFlags(processor);

    // This string is usually vendor-specific.
    // Other processors in this family will have the same string.
    const char *family      = icmGetProcessorFamily(processor);

    // Where the processor is expecting to be stored. This can usually be ignored
    // since you knew where to find the processor in the first place.
    icmVlnvP    model       = icmGetProcessorVlnv(processor);

    // A semihost library to be used with this processor by default.
    icmVlnvP    semihost    = icmGetProcessorDefaultSemihost(processor);

    // Which endian will this processor support? This is NOT the current endian.
    icmEndian   endian      = icmGetProcessorEndian(processor);

    // A list of ELF codes that this processor supports. Used in the case where
    // one or more GNU (or compatible) tool-chains are used to generate code for
    // this processor.
    Bool       defaultElf   = 0;
    Uns32      max          = 10;
    Uns32      elves[max];
    Uns32      actualElves  = icmGetProcessorElfcode(processor, elves, max, &defaultElf);
    if(actualElves > max) {
        // truncate the result - could allocate a larger array if required.
        actualElves = max;
    }

    icmPrintf("  GENERAL INFORMATION\n");
    icmPrintf("    GDB path         : %s\n", gdbpath    ?: "(none)");
    icmPrintf("    GDB flags        : %s\n", gdbflags   ?: "(none)");
    icmPrintf("    Processor family : %s\n", family     ?: "(none)");
    icmPrintf("    Processor endian : %d\n", endian);

    printVLNV("    Model VLNV       :", model);
    printVLNV("    Semihost VLNV    :", semihost);

    icmPrintf("    ELF Code(s)      :");
    Uns32 i;
    for(i=0; i < actualElves; i++) {
        icmPrintf(" %d", elves[i]);
    }
    if(defaultElf) {
        icmPrintf("    (This is the default processor for these ELF codes)\n");
    }
    icmPrintf("\n");
}

//
// A model can supply documentation with arbitrary depth and detail. It is up the
// the consumer to format it as desired. The data is presented in a structure similar
// to the DOM used by some XML documents.
//
static void queryDocumentationNode(icmDocNodeP node, Uns32 depth) {
    while(node) {
        spaces(depth);
        if(icmDocIsText(node)) {
            icmPrintf("  Text : %s\n", icmDocText(node));
        } else {
            icmPrintf("  Title: %s\n", icmDocText(node));
            queryDocumentationNode(icmDocChildNode(node), depth + 4);
        }
        node = icmDocNextNode(node);
    }
}

static void queryDocumentation(icmProcessorP processor) {
    icmPrintf("  DOCUMENTATION:\n");
    icmDocNodeP node = icmGetProcessorDoc(processor);
    queryDocumentationNode(node, 0);
    icmPrintf("\n");
}

//
// Create a new processor instance, given the vendor, name and optional variant.
// If no variant is provided, the default processor is constructed.
// Some of these example processors might be missing from your installation.
//
static icmProcessorP newProcessor(
    const char *instance,
    const char *vendor,
    const char *name,
    const char *endian,
    const char *variant
) {
    // set up instance attributes
    const char *library = "processor";
    const char *version = "1.0";
    icmProcessorP processor = NULL;

    const char *path = icmGetVlnvString(NULL, vendor, library, name, version, "model");
    if(path) {
        icmAttrListP userAttrs = icmNewAttrList();
        if(endian) {
            icmAddStringAttr(userAttrs, "endian", endian);
        }
        if(variant) {
            icmAddStringAttr(userAttrs, "variant", variant);
        }

        // create a processor
        processor = icmNewProcessor(
            instance,           // CPU instance name
            "",                 // (unused)
            0,                  // CPU cpuId
            0x0,                // CPU model flags
            32,                 // address bits
            path,               // model file
            "modelAttrs",       // morpher attributes
            0,                  // processor attributes
            userAttrs,          // user-defined attributes
            0,                  // semi-hosting file
            0                   // semi-hosting attributes
        );
        icmSimulationStarting();
    }
    return processor;
}

static void queryProcessor(
    const char *instance,
    const char *vendor,
    const char *name,
    const char *endian,
    const char *variant
) {
    icmInitPlatform(ICM_VERSION, ICM_INIT_DEFAULT, NULL, 0, "platform");

    if(icmTryVlnvString(NULL, vendor, "processor", name, NULL, "model")) {
        icmProcessorP processor = newProcessor(instance, vendor, name, endian, variant);
        if(processor) {
            icmPrintf("PROCESSOR: Vendor: %s   Name: %s   Variant: %s\n", vendor, name, variant?: "(no variant)");
            queryBuses(processor);
            queryNets(processor);
            queryRegisters(processor);
            queryExceptions(processor);
            queryModes(processor);
            queryParameters(processor);
            queryDescription(processor);
            queryInfo(processor);
            queryDocumentation(processor);
        }
    }
    icmTerminate();
}

