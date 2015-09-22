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

#define PROCESSOR_COUNT_DEFAULT 24

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform(Uns32 numberProcessors) {

    // Initialize ICM
    // Require Imperas intercepts because the application uses impProcessorId() to get processor id
    icmInitAttrs icmAttrs = ICM_VERBOSE | ICM_ENABLE_IMPERAS_INTERCEPTS | ICM_STOP_ON_CTRLC;
    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, "platform");

    // select library components
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // Variable for sub-system components
    icmProcessorP processor[numberProcessors];
    icmBusP bus[numberProcessors];
    icmMemoryP memory[numberProcessors];
    char name[32];
    Uns32 i;
    for (i=0; i<numberProcessors; i++ ) {
        // create processor cpu<i>
        sprintf(name, "cpu%d", i);
        processor[i] = icmNewProcessor(
            name,               // CPU name
            "or1k",             // CPU type
            i,                  // CPU cpuId
            0,                  // CPU model flags
            32,                 // address bits
            model,              // model file
            "modelAttrs",       // morpher attributes
            MODEL_ATTRS,        // simulation attributes. enable tracing etc
            0,                  // user-defined attributes
            semihosting,        // semi-hosting file
            "modelAttrs"        // semi-hosting attributes
        );

        // create the processor busses
        sprintf(name, "bus%d", i);
        bus[i] = icmNewBus(name, 32);

        // connect the processor busses
        icmConnectProcessorBusses(processor[i], bus[i], bus[i]);

        // create memory
        sprintf(name, "memory%d", i);
        memory[i] = icmNewMemory(name, ICM_PRIV_RWX, 0xffffffff);

        // connect memory
        icmConnectMemoryToBus(bus[i], "mp1", memory[i], 0x00000000);

        // show the bus connections
        icmPrintf("\nBUS[%d] CONNECTIONS\n",i);
        icmPrintBusConnections(bus[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]);

struct optionsS {
    Uns64 number;
} options = {.number=PROCESSOR_COUNT_DEFAULT};

int main(int argc, const char *argv[])
{
	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", "platform", "Command Line parser error");
		icmExitSimulation(1);
		return 1;
	}

	// the constructor
	createPlatform((Uns32)options.number);

	icmSimulationStarting();

    // run simulation
    icmSimulatePlatform();

    // terminate simulation and free simulation data structures
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}
static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file> [--number <processor count>]\n");
	icmCLParserUsageMessage(parser, (const char *)message);

	icmCLParserAdd(parser, "number"  , 0 , 0, "user platform config", ICM_AT_UNS64VAL    , &options.number, "The number of processor instances to create", 0x0, 0, 0);

	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "program", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
