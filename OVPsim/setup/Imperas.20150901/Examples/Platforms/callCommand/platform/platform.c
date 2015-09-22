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

#include <stdlib.h>
#include <stdio.h>

#include "icm/icmCpuManager.h"

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor;
} handles;

// enable tracing etc
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, 0, 0, 0, "platform");

    // select library components
	const char *vlnvRoot = 0;   // when null use default library
    const char *model = icmGetVlnvString(
        vlnvRoot, "mips.ovpworld.org", "processor", "mips32", "1.0", "model"
    );
    const char *semihosting = icmGetVlnvString(
        vlnvRoot, "mips.ovpworld.org", "semihosting", "mips32SDE", "1.0", "model"
    );

    // create a processor
    handles.processor = icmNewProcessor(
        "cpu1",             // CPU name
        "mips32",           // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        MODEL_ATTRS,        // enable tracing etc
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );
}
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static void queryCommands(void);
static Bool cmdParser(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", "platform", "Command Line parser error");
		icmExitSimulation(1);
		return 1;
	}

	// the constructor
	createPlatform();

	icmSimulationStarting();

    // Run the processor for 100 instructions
    icmSimulate(handles.processor, 100);

    // Call a command that had been created in a processor model
    // Pointer to the call command result string. This could be any string
    const char *result;

    icmPrintf("\nCall Model Commands\n\n");

    // Setup calling arguments to read COP0 'Config' register
    const char *cmd1Argv[] = {"mipsCOP0", "16", "0"};

    result = icmCallCommand("platform/cpu1",
                            NULL,
                            cmd1Argv[0],
                            3,
                            &cmd1Argv[0]);

    icmPrintf("\nCall Command result '%s'\n", result);

    // Setup calling arguments to read COP0 'PrId' register
    const char *cmd2Argv[] = {"mipsCOP0", "15", "0"};

    result = icmCallCommand("platform/cpu1",
                            NULL,
                            cmd2Argv[0],
                            3,
                            &cmd2Argv[0]);

    icmPrintf("\nCall Command result '%s'\n", result);

    icmPrintf("\nDiscover installed commands\n");
    queryCommands();

    icmPrintf("\nComplete Simulation\n\n");

    // run simulation to completion
    icmSimulate(handles.processor, -1);

    // terminate simulation
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

//
// This is the callback, called once per installed command
//
static ICM_INSTALLED_COMMAND_FN(printCommand) {
    printf("CB:");
    if (platform) {
        printf(" Plt:%s", platform);
    }
    if (model) {
        printf(" Mdl:%s", model);
    }
    if (plugin) {
        printf(" Plg:%s", plugin);
    }
    if (command) {
        printf(" Cmd:%s", command);
    }
    if (shortHelp) {
        printf(" (Help found)");
    }
    printf("\n");
}

//
// Discover what commands are installed, first for the platform, then for
// one particular processor (with the same effect in this simple platform).
//
static void queryCommands(void) {
    printf("AllCommands\n");
    // iterates over all commands on all processor instances
    icmGetAllPlatformCommands(printCommand, 0);

    const char *procName = "cpu1";
    printf("Commands for %s\n", procName);
    icmProcessorP proc = icmFindProcessorByName(procName);

    // iterates over all commands on this processor instance
    icmGetAllProcessorCommands(proc, printCommand, (void*)1);
    printf("Done\n");
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file>\n");
	icmCLParserUsageMessage(parser, (const char *)message);
	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "platform", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
