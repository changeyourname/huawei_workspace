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

// Define processor performance and time information
#define INSTRUCTIONS_PER_SECOND 100000000
#define TIME_SLICE	0.01
#define INSTRUCTIONS_PER_TIME_SLICE (INSTRUCTIONS_PER_SECOND*TIME_SLICE)

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
    const char *vlnvRoot = 0; // when null use default library
    const char *model = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // create a processor
    handles.processor = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
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

    icmBusP bus = icmNewBus("bus", 32);

    icmConnectProcessorBusses(handles.processor, bus, bus);

    icmMemoryP memLow = icmNewMemory("memLow", ICM_PRIV_RWX, 0x0fffffff);
    icmConnectMemoryToBus(bus,"sp1",memLow, 0x00000000);

    icmMemoryP memHigh = icmNewMemory("memHigh", ICM_PRIV_RWX, 0xdfffffff);
    icmConnectMemoryToBus(bus,"sp1",memHigh, 0x20000000);

    const char *uartPse = icmGetVlnvString(
        vlnvRoot, "national.ovpworld.org", "peripheral", "16550", "1.0", "pse"
    );

    {
        icmAttrListP uarttty0Attrs = icmNewAttrList();
        icmAddStringAttr(uarttty0Attrs, "outfile", "uartTTY0.out");
        icmPseP uartTTY0 = icmNewPSE("uartTTY0", uartPse, uarttty0Attrs, NULL, NULL);
        icmConnectPSEBus(uartTTY0, bus, "bport1", False, 0x100003f8, 0x100003ff);
        icmSetPSEdiagnosticLevel(uartTTY0, 0x3);
    }

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

    // run simulation with default scheduling
    //icmSimulatePlatform();

    // run simulation with custom scheduling
    icmTime myTime;
    icmStopReason rtnVal = ICM_SR_SCHED;
    for(myTime=TIME_SLICE;rtnVal==ICM_SR_SCHED || rtnVal==ICM_SR_HALT;myTime+=TIME_SLICE){
	    rtnVal= icmSimulate(handles.processor, INSTRUCTIONS_PER_TIME_SLICE);
	    icmAdvanceTime(myTime);
    }

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
