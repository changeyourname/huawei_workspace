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

#define MODEL_FLAGS  (ICM_ATTR_TRACE|ICM_ATTR_TRACE_ICOUNT)

#define PLATFORM "platform"

static Bool cmdParser(int argc, const char *argv[]);
static Bool simulate(icmProcessorP processor, Uns64 instructions);

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
    unsigned int icmAttrs = ICM_STOP_ON_CTRLC;

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

    // create intr0 and intr1 nets and connect them to the processor
    icmNetP intr0Net = icmNewNet("intr0Net");
    icmNetP intr1Net = icmNewNet("intr1Net");
    icmConnectProcessorNet(processor, intr0Net, "intr0", ICM_INPUT);
    icmConnectProcessorNet(processor, intr1Net, "intr1", ICM_INPUT);

    // run processor for 9 instructions
    simulate(processor, 9);

    // raise intr0 for one instruction
    icmWriteNet(intr0Net, 1);
    simulate(processor, 1);
    icmWriteNet(intr0Net, 0);

    // run processor for 9 instructions
    simulate(processor, 9);

    // raise intr1 for one instruction
    icmWriteNet(intr1Net, 1);
    simulate(processor, 1);
    icmWriteNet(intr1Net, 0);

    // run processor until done (no instruction limit)
    while(simulate(processor, -1)) {
        // keep going while processor is still running
    }

    // dump the final register contents
    icmDumpRegisters(processor);

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
static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    Bool ok = icmCLParseArgs(parser, argc, argv);
	return ok;
}

