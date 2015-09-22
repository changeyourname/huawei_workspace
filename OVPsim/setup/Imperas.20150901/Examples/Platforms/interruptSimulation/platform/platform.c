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

// By default use the internal handler for Control-C when ICM is initialised with ICM_STOP_ON_CTRLC
// This is valid for both Linux and Windows Hosts

// Alternatively, on Linux only, use this define to use this included Linux control-C handler
//#define EXTERNALHANDLER
// or build platform with make -C platform CFLAGS="-D EXTERNALHANDLER"

// This is a custom handler that is only valid when compiled for a Linux host system
#ifdef EXTERNALHANDLER

#include <signal.h>

//
// LINUX signal handler to interrupt the running simulation
//
static void ctrlCHandler(Int32 nativeSigNum, siginfo_t *sigInfo, void *context) {
    // On Linux the API call may be used directly as the simulator is frozen on a signal
    // On Windows the simulator must be suspended before issuing this call

    printf("External Users Ctrl-C Handler Triggered\n");
    icmInterrupt();
}

//
// Install a LINUX signal handler to trap any CtrlC
//
static void installCtrlCHandler(void) {

    struct sigaction sa = {{0}};
    sa.sa_sigaction = ctrlCHandler;
    sa.sa_flags     = SA_SIGINFO;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}

#define ICM_INIT (ICM_VERBOSE|ICM_ENABLE_IMPERAS_INTERCEPTS)

#else

#define ICM_INIT (ICM_VERBOSE|ICM_ENABLE_IMPERAS_INTERCEPTS|ICM_STOP_ON_CTRLC)

#endif

//
// Callback for memory writes to defined external area
// this will cause the icmYield() function to interrupt the simulation
// after the instruction of the processor causing the access completes
//
static ICM_MEM_WRITE_FN(watchWriteCB) {

    icmPrintf(
        "WATCHCALLBACK '%s': Writing to 0x%08x : Interrupt\n",
        (Uns8 *)userData,
        (Int32)address
    );

    // Calling this API function will interrupt the simulator
    icmYield(processor);
}

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor0;
    icmProcessorP  processor1;
    icmBusP        bus0;
    icmBusP        bus1;
} handles;

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform() {

    // initialize ICM - require Imperas intercepts because the
    // application uses impProcessorId() to get processor id
    icmInitPlatform(ICM_VERSION, ICM_INIT, 0, 0, "platform");

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
    icmMemoryP shared = icmNewMemory("shared", ICM_PRIV_RWX, 0xefffffff);
    icmMemoryP local1 = icmNewMemory("local1", ICM_PRIV_RWX, 0x0fffffff);
    icmMemoryP local2 = icmNewMemory("local2", ICM_PRIV_RWX, 0x0fffffff);

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

#ifdef EXTERNALHANDLER

    // install a signal handler to trap any CtrlC
    installCtrlCHandler();

#endif

	// the constructor
	createPlatform();

    icmSimulationStarting();

    //
    // Create a watchpoint
    // Invoke callback on write accesses to the address 0xeffffff0-0xeffffff3
    //
    icmAddBusWriteCallback(
        handles.bus0,               // bus
        handles.processor0,         // processor
        0xeffffff0,         // low address
        0xeffffff3,         // high address
        watchWriteCB,       // callback to invoke
        "cpu0"              // user data passed to callback
    );
    icmAddBusWriteCallback(
        handles.bus1,               // bus
        handles.processor1,         // processor
        0xeffffff0,         // low address
        0xeffffff3,         // high address
        watchWriteCB,       // callback to invoke
        "cpu1"              // user data passed to callback
    );

    // show the bus connections
    icmPrintf("\nbus0 CONNECTIONS\n");
    icmPrintBusConnections(handles.bus0);
    icmPrintf("\nbus1 CONNECTIONS\n");
    icmPrintBusConnections(handles.bus1);
    icmPrintf("\n");

    // run simulation
    icmProcessorP stoppedProcessor;

    // simulate until done, yield or ctrl-C
    Bool continueExecution = True;
    while(continueExecution && (stoppedProcessor=icmSimulatePlatform())) {
        icmStopReason stopReason = icmGetStopReason(stoppedProcessor);
        switch(stopReason) {
               case ICM_SR_INTERRUPT:
               case ICM_SR_YIELD:
                   icmPrintf(
                       "%s: interrupt after " FMT_64u " instructions...\n",
                       icmGetProcessorName(stoppedProcessor, "/"),
                       icmGetProcessorICount(stoppedProcessor));
                   break;
               default:
                   // some other stop reason encountered
                   continueExecution = False;
                   break;
    	}
    }

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

	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "program", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}

