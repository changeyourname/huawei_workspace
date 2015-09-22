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

#include "icm/icmCpuManager.h"

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor0, processor1;
    icmBusP        bus0, bus1;
} handles;

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager - require Imperas intercepts because the
    // application uses impProcessorId() to get processor id
    icmInitAttrs icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC | ICM_ENABLE_IMPERAS_INTERCEPTS;
    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, "platform");


    // select library components
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // create processor cpu0
    handles.processor0 = icmNewProcessor(
        "cpu0",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        MODEL_ATTRS,        // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create processor cpu1
    handles.processor1 = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
        1,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        MODEL_ATTRS,        // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor busses
    handles.bus0 = icmNewBus("bus0", 32);
    handles.bus1 = icmNewBus("bus1", 32);

    // connect the processor busses
    icmConnectProcessorBusses(handles.processor0, handles.bus0, handles.bus0);
    icmConnectProcessorBusses(handles.processor1, handles.bus1, handles.bus1);

    // create memories
    icmMemoryP local1 = icmNewMemory("local1", ICM_PRIV_RWX, 0x0fffffff);
    icmMemoryP local2 = icmNewMemory("local2", ICM_PRIV_RWX, 0x0fffffff);
    icmMemoryP shared = icmNewMemory("shared", ICM_PRIV_RWX, 0xefffffff);

    // connect memories
    icmConnectMemoryToBus(handles.bus0, "mp1", shared, 0x00000000);
    icmConnectMemoryToBus(handles.bus1, "mp2", shared, 0x00000000);
    icmConnectMemoryToBus(handles.bus0, "mp1", local1, 0xf0000000);
    icmConnectMemoryToBus(handles.bus1, "mp1", local2, 0xf0000000);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

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


    // show the bus connections
    icmPrintf("\nbus0 CONNECTIONS\n");
    icmPrintBusConnections(handles.bus0);
    icmPrintf("\nbus1 CONNECTIONS\n");
    icmPrintBusConnections(handles.bus1);
    icmPrintf("\n");

    icmSimulationStarting();

    // limit performance to no more than 2x nominal speed
    icmSetWallClockFactor(2);

    // run simulation
    icmSimulatePlatform();

    // report the total number of instructions executed
    icmPrintf(
        "processor0 has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(handles.processor0)
    );
    icmPrintf(
        "processor1 has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(handles.processor1)
    );

    // free simulation data structures
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file>\n");
	icmCLParserUsageMessage(parser, (const char *)message);

	Bool ok = False;
	ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "program", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
