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

#define MODEL_FLAGS (ICM_ATTR_DEFAULT)

#define PLATFORM "platform"

static Bool cmdParser(int argc, const char *argv[]);
static Bool simulate(icmProcessorP processor, Uns64 instructions);

// Model query fnctions defined below
static void queryRegisters(icmProcessorP processor);
static void queryExceptions(icmProcessorP processor);
static void queryModes(icmProcessorP processor);

//
// Virtual platform construction and simulation
//
int main(int argc, const char **argv) {

    // Check arguments
    if(!cmdParser(argc, argv)) {
    	icmMessage("E", PLATFORM, "Command Line parser error");
    	return 1;
    }

    // initialize OVPsim
    unsigned int icmAttrs = ICM_STOP_ON_CTRLC | ICM_GDB_CONSOLE;

    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

    const char *modelFile    = "model." IMPERAS_SHRSUF;
    const char *semihostFile = icmGetVlnvString(NULL, "ovpworld.org", "modelSupport", "imperasExit", "1.0", "model");

    // create a processor instance
    icmProcessorP processor = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        modelFile,          // model file
        "modelAttrs",       // morpher attributes
		MODEL_FLAGS,        // attributes
        0,                  // user-defined attributes
        semihostFile,       // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor bus
    icmBusP bus = icmNewBus("bus", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(processor, bus, bus);

    // create memory
    icmMemoryP local = icmNewMemory("local", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(bus, "mp1", local, 0x00000000);

    icmSimulationStarting();

    // query processor registers, execeptions and modes
    queryRegisters(processor);
    queryExceptions(processor);
    queryModes(processor);

    // run processor until done (no instruction limit)
    while(simulate(processor, -1)) {
        // keep going while processor is still running
    }

    // report the total number of instructions executed
    icmPrintf(
        "processor has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor)
    );

    icmTerminate();

    return 0;
}
//
// Simulation main loop
//
static Bool simulate(icmProcessorP processor, Uns64 instructions) {

    icmStopReason stopReason = icmSimulate(processor, instructions);

    switch(stopReason) {

       case ICM_SR_SCHED:
           // hit the scheduler limit
           return True;

       case ICM_SR_EXIT:
           // processor has exited
           return False;

       case ICM_SR_FINISH:
           // simulation must end
           return False;

        case ICM_SR_RD_PRIV:
        case ICM_SR_WR_PRIV:
        case ICM_SR_RD_ALIGN:
        case ICM_SR_WR_ALIGN:
           // unhandled processor exception: simulation must end
           return False;

       default:
           icmPrintf("unimplemented stopReason %u\n", stopReason);
           return False;
    }
}

//
// Query registers and register groups in the passed processor
//
static void queryRegisters(icmProcessorP processor) {

    icmPrintf("%s REGISTERS\n", icmGetProcessorName(processor, "/"));

    icmRegGroupP group = NULL;

    while((group=icmGetNextRegGroup(processor, group))) {

        icmPrintf("  GROUP %s\n", icmGetRegGroupName(group));

        icmRegInfoP reg = NULL;

        while((reg=icmGetNextRegInGroup(processor, group, reg))) {
            icmPrintf("    REGISTER %s\n", icmGetRegInfoName(reg));
        }
    }

    icmPrintf("\n");
}

//
// Query exceptions in the passed processor
//
static void queryExceptions(icmProcessorP processor) {

    const char *name = icmGetProcessorName(processor, "/");

    if(!icmGetNextException(processor, 0)) {

        icmPrintf("%s HAS NO EXCEPTION INFORMATION\n", name);

    } else {

        icmPrintf("%s EXCEPTIONS\n", name);

        icmExceptionInfoP info = NULL;

        while((info=icmGetNextException(processor, info))) {
            icmPrintf(
                "  %s (code %u)\n",
                icmGetExceptionInfoName(info),
                icmGetExceptionInfoCode(info)
            );
        }

        if((info=icmGetException(processor))) {
            icmPrintf(
                "current: %s (code %u)\n",
                icmGetExceptionInfoName(info),
                icmGetExceptionInfoCode(info)
            );
        }
    }

    icmPrintf("\n");
}

//
// Query modes in the passed processor
//
static void queryModes(icmProcessorP processor) {

    const char *name = icmGetProcessorName(processor, "/");

    if(!icmGetNextMode(processor, 0)) {

        icmPrintf("%s HAS NO MODE INFORMATION\n", name);

    } else {

        icmPrintf("%s MODES\n", name);

        icmModeInfoP info = NULL;

        while((info=icmGetNextMode(processor, info))) {
            icmPrintf(
                "  %s (code %u)\n",
                icmGetModeInfoName(info),
                icmGetModeInfoCode(info)
            );
        }

        if((info=icmGetMode(processor))) {
            icmPrintf(
                "current: %s (code %u)\n",
                icmGetModeInfoName(info),
                icmGetModeInfoCode(info)
            );
        }
    }

    icmPrintf("\n");
}
static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    Bool ok = icmCLParseArgs(parser, argc, argv);
	return ok;
}

