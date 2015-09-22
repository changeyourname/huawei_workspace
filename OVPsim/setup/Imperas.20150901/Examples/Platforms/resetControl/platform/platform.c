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
#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor[2];
    icmNetP        reset0,reset1;
} handles;

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_TRACE_ICOUNT)

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, ICM_VERBOSE|ICM_STOP_ON_CTRLC|ICM_ENABLE_IMPERAS_INTERCEPTS,0 , 0, "platform");

    // select library components
    const char *vlnvRoot = 0; // when null use default library
    const char *model = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // create a processor
    handles.processor[0]= icmNewProcessor (
        "cpu0",             // CPU name
        0,
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        0,
        MODEL_ATTRS,        // enable tracing etc
        NULL,               // user-defined attributes
        semihosting,        // semi-hosting file
        0
    );
    // create a processor
    handles.processor[1] = icmNewProcessor (
        "cpu1",             // CPU name
        0,
        1,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        0,
        MODEL_ATTRS,        // enable tracing etc
        NULL,               // user-defined attributes
        semihosting,        // semi-hosting file
        0
    );


    icmBusP bus0 = icmNewBus("bus0", 32);
    icmBusP bus1 = icmNewBus("bus1", 32);

    icmConnectProcessorBusses(handles.processor[0], bus0, bus0);
    icmConnectProcessorBusses(handles.processor[1], bus1, bus1);

    icmMemoryP memLow0 = icmNewMemory("memLow0", ICM_PRIV_RWX, 0x0fffffff);
    icmConnectMemoryToBus(bus0,"sp1",memLow0, 0x00000000);
    icmMemoryP memLow1 = icmNewMemory("memLow1", ICM_PRIV_RWX, 0x0fffffff);
    icmConnectMemoryToBus(bus1,"sp1",memLow1, 0x00000000);

    icmMemoryP memHigh0 = icmNewMemory("memHigh0", ICM_PRIV_RWX, 0xdfffffff);
    icmConnectMemoryToBus(bus0,"sp1",memHigh0, 0x20000000);
    icmMemoryP memHigh1 = icmNewMemory("memHigh1", ICM_PRIV_RWX, 0xdfffffff);
    icmConnectMemoryToBus(bus1,"sp1",memHigh1, 0x20000000);

    handles.reset0 = icmNewNet("reset0");
    handles.reset1 = icmNewNet("reset1");

    icmConnectProcessorNet(handles.processor[0], handles.reset0, "reset", ICM_INPUT);
    icmConnectProcessorNet(handles.processor[1], handles.reset1, "reset", ICM_INPUT);
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

    icmWriteNet(handles.reset0, 0);
    icmWriteNet(handles.reset1, 1);

    // run simulation

    // Set to stop at 0.001 seconds simulation time
    icmSetSimulationStopTime(0.01);

    icmSimulatePlatform();

    icmPrintf("Simulation time: %f\n",(float)icmGetCurrentTime());

    icmWriteNet(handles.reset1, 0);

    // Set to stop at 0.002 seconds simulation time
    icmSetSimulationStopTime(0.02);

    icmSimulatePlatform();

    icmPrintf("Simulation time: %f\n",(float)icmGetCurrentTime());

    // terminate simulation
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file>\n");
	icmCLParserUsageMessage(parser, (const char *)message);

	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "program", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
