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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "icm/icmCpuManager.h"

void createPlatform(const char* processorType, const char* alternateVendor) {

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, ICM_VERBOSE | ICM_STOP_ON_CTRLC, 0, 0, "platform");

    // select library components
    const char *vlnvRoot = NULL; //When NULL use default library

    // set default
	const char *model       = icmGetVlnvString(vlnvRoot, alternateVendor ? alternateVendor : "ovpworld.org",
                                                                  "processor",   "or1k",       "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot,  "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    if (strcmp(processorType, "mips32") == 0) {
        model       = icmGetVlnvString(vlnvRoot, alternateVendor ? alternateVendor : "mips.ovpworld.org",
                                                                      "processor",   "mips32",    "1.0", "model");
        semihosting = icmGetVlnvString(vlnvRoot, "mips.ovpworld.org", "semihosting", "mips32SDE", "1.0", "model");

    } else if (strcmp(processorType, "arm") == 0) {
        model       = icmGetVlnvString(vlnvRoot,alternateVendor ? alternateVendor : "arm.ovpworld.org",
                                                                     "processor",   "arm",       "1.0", "model");
        semihosting = icmGetVlnvString(vlnvRoot, "arm.ovpworld.org", "semihosting", "armNewlib", "1.0", "model");

    } else {
        icmMessage("W", "PROC", "Processor type %s not recognized. Using default. Please try or1k, mips32 or arm", processorType);
    }

    if (!model || !semihosting) {
        icmMessage("F", "LIBRARY", "Failed to find library components for specified %s processor type (or vendor %s)", processorType, alternateVendor);
    }

    // create a processor
    icmNewProcessor(
        "cpu1",             // CPU name
        processorType,      // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        0,                  // enable tracing or register values
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]);

struct optionsS {
    const char*     processortype;
    const char*     alternatevendor;
} options = {.processortype="or1k"};

int main(int argc, const char *argv[])
{

	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", "platform", "Command Line parser error");
		icmExitSimulation(1);
		return 1;
	}

	// the constructor
	createPlatform(options.processortype, options.alternatevendor);

	// simulate the platform
	icmSimulatePlatform();

	// finish and clean up
	icmTerminate();

	icmExitSimulation(0);
	return 0;
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file> --processortype <or1k|mips32|arm7> [--alternatevendor <vendor>]\n");
	icmCLParserUsageMessage(parser, (const char *)message);
    icmCLParserAdd(parser, "processortype"  , 0 , 0, "user platform config", ICM_AT_STRINGVAL    , &options.processortype, "Specify the processor type to use. or1k, mips32 or arm", 0x0, 0, 0);
    icmCLParserAdd(parser, "alternatevendor", 0 , 0, "user platform config", ICM_AT_STRINGVAL    , &options.alternatevendor, "Specify an alternative vendor for processor model", 0x0, 0, 0);
	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "platform", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
