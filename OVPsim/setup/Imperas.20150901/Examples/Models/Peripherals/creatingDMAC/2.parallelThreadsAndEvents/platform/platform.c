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
#include <ctype.h>

#include "icm/icmCpuManager.h"

#define SIM_ATTRS (ICM_ATTR_DEFAULT)

//
// Perform platform creation
//
void createPlatform() {

    // initialize OVPsim, enabling verbose mode to get statistics at end
    // of execution
    icmInitPlatform(ICM_VERSION, ICM_VERBOSE|ICM_STOP_ON_CTRLC, 0, 0, "platform");

	// select library components
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // create the processor bus
    icmBusP bus = icmNewBus("busMain", 32);

    ////////////////////////////////////////////////////////////////////////////
    // Memory
    ////////////////////////////////////////////////////////////////////////////

    // create two memory regions mapping all memory except the DMAC registers
    icmMemoryP mem1 = icmNewMemory("mem1", ICM_PRIV_RWX, 0x3fffffff);
    icmMemoryP mem2 = icmNewMemory("mem2", ICM_PRIV_RWX, 0x7fffffff);

    // connect memories to the bus
    icmConnectMemoryToBus(bus, "sp", mem1, 0xc0000000);
    icmConnectMemoryToBus(bus, "sp", mem2, 0x00000000);

    ////////////////////////////////////////////////////////////////////////////
    // Processor
    ////////////////////////////////////////////////////////////////////////////

    // create a processor instance
    icmProcessorP processor = icmNewProcessor(
        "CPU1",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // connect the processor instruction and data busses to the bus
    icmConnectProcessorBusses(processor, bus, bus);

    ////////////////////////////////////////////////////////////////////////////
    // DMAC Peripheral
    ////////////////////////////////////////////////////////////////////////////

    // instantiate the peripheral
    icmPseP dmac = icmNewPSE("dmac", "pse.pse", NULL, NULL, NULL);

    // connect the DMAC slave port on the bus and define the address range it occupies
    icmConnectPSEBus(dmac, bus, "DMACSP", False, 0x80000000, 0x8000013f);

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

	// simulate the platform
    icmProcessorP final = icmSimulatePlatform();

    // was simulation interrupted or did it complete
    if(final && (icmGetStopReason(final)==ICM_SR_INTERRUPT)) {
        icmPrintf("*** simulation interrupted\n");
    }

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
