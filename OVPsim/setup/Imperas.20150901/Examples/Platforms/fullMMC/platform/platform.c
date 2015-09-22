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

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, ICM_STOP_ON_CTRLC, 0, 0, "platform");

    // select library components
    const char *vlnvRoot = 0; // when null use default library
    const char *model = icmGetVlnvString(
        vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model"
    );
    const char *semihosting = icmGetVlnvString(
        vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model"
    );
    const char *mmc_model = icmGetVlnvString(
        vlnvRoot, "ovpworld.org", "mmc", "wb_1way_32byteline_2048tags", "1.0",
        "model"
    );

    // create a processor
    icmProcessorP cpu1h = icmNewProcessor(
        "cpu1",             // CPU name
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

    // create full MMCs
    icmMmcP mmci = icmNewMMC("mmci", mmc_model, "modelAttrs", 0, 0, False);
    icmMmcP mmcd = icmNewMMC("mmcd", mmc_model, "modelAttrs", 0, 0, False);

    // create the processor instruction bus and data bus
    icmBusP ibus = icmNewBus("ibus", 32);
    icmBusP dbus = icmNewBus("dbus", 32);

    // create the processor main bus
    icmBusP mbus = icmNewBus("mbus", 32);

    // connect processor ports to their buses
    icmConnectProcessorBusses(cpu1h, ibus, dbus);

    // connect MMCs to buses
    icmConnectMMCBus(mmci, ibus, "sp1", False);
    icmConnectMMCBus(mmcd, dbus, "sp1", False);

    // connect master ports of MMC to main bus
    icmConnectMMCBus(mmci, mbus, "mp1", True);
    icmConnectMMCBus(mmcd, mbus, "mp1", True);

    // create two simulated memories for low and high regions
    icmMemoryP memory1 = icmNewMemory("mem1", ICM_PRIV_RWX, 0x003fffff);
    icmMemoryP memory2 = icmNewMemory("mem2", ICM_PRIV_RWX, 0xffffffff-0x00401000);

    // connect memories to main bus
    icmConnectMemoryToBus(mbus, "mp1", memory1, 0);
    icmConnectMemoryToBus(mbus, "mp2", memory2, 0x00401000);
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

    icmPrintf("2x Full MMC\n");

	// the constructor
	createPlatform();

    icmSimulationStarting();

    // run until exit
    icmSimulatePlatform();

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
