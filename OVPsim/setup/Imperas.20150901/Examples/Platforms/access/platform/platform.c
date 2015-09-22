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
    icmProcessorP  processor;
} handles;

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, ICM_STOP_ON_CTRLC, 0, 0, "platform");

    // select library components
    const char *model       = icmGetVlnvString(NULL, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(NULL, "ovpworld.org", "modelSupport", "imperasExit", "1.0", "model");

    // create a processor
    handles.processor = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
		MODEL_ATTRS,        // enable tracing or register values
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // No memory or bus connections are created in this platform
    // The simulator assumes and creates a memory connection to the
    // full memory space this processor can access.

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

    Bool done = False;
    while(!done) {

        Uns32 currentPC = (Uns32)icmGetPC(handles.processor);

        // disassemble instruction at current PC
        icmPrintf("** Instruction Disassemble\n");
        icmPrintf(
            "0x%08x : %s\n", currentPC,
            icmDisassemble(handles.processor, currentPC)
        );

        // execute one instruction
        icmPrintf("** Instruction Execution\n");
        done = (icmSimulate(handles.processor, 1) != ICM_SR_SCHED);

        // dump registers
        icmPrintf("** Register Dump\n");
        icmDumpRegisters(handles.processor);
    }

    // print number of instructions executed at end of simulation
    icmPrintf(
        "Simulation finished, "FMT_64u" instructions executed\n",
        icmGetProcessorICount(handles.processor)
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
	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "platform", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
