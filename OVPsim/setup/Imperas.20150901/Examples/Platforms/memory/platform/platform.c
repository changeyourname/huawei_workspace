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

//
// Callback for memory reads from defined external area
//
static ICM_MEM_READ_FN(extMemReadCB) {

    Int32 data = 0xcefaedfe;
    *(Int32 *)value = data;

    icmPrintf(
        "EXTERNAL MEMORY: Reading  0x%08x from 0x%08x\n",
        data, (Int32)address
    );
}

//
// Callback for memory writes to defined external area
//
static ICM_MEM_WRITE_FN(extMemWriteCB) {

    icmPrintf(
        "EXTERNAL MEMORY: Writing 0x%08x to 0x%08x\n",
        *(Int32 *)value, (Int32)address
    );
}

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor;
    icmBusP        bus;
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
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "modelSupport", "imperasExit", "1.0", "model");

    // create a processor
    handles.processor = icmNewProcessor(
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

    // create the processor bus
    handles.bus = icmNewBus("bus", 32);

    // connect the processor busses
    icmConnectProcessorBusses(handles.processor, handles.bus, handles.bus);

    // create two simulated memories for low and high regions
    icmMemoryP memory1 = icmNewMemory("mem1", ICM_PRIV_RWX, 0x003fffff);
    icmMemoryP memory2 = icmNewMemory("mem2", ICM_PRIV_RWX, 0xffffffff-0x00401000);

    // map the address range 0x00400000:0x00400fff externally to the processor,
    // read only
    icmMapExternalMemory(
        handles.bus, "external", ICM_PRIV_R, 0x00400000, 0x00400fff,
        extMemReadCB, extMemWriteCB, 0
    );

    // connect memories to bus
    icmConnectMemoryToBus(handles.bus, "mp1", memory1, 0);
    icmConnectMemoryToBus(handles.bus, "mp2", memory2, 0x00401000);
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
    icmPrintBusConnections(handles.bus);

    Bool done = False;

    while(!done) {

        Uns32 currentPC = (Uns32)icmGetPC(handles.processor);

        // disassemble instruction at current PC
        icmPrintf(
            "0x%08x : %s\n", currentPC,
            icmDisassemble(handles.processor, currentPC)
        );

        // execute one instruction
        done = (icmSimulate(handles.processor, 1) != ICM_SR_SCHED);

        // dump registers
        icmDumpRegisters(handles.processor);
    }

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
		icmMessage("E", "program", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
