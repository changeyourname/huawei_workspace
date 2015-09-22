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

#define MODEL_FLAGS  (ICM_ATTR_SIMEX)

#define PLATFORM "platform"

static Bool cmdParser(int argc, const char *argv[]);

static icmAttrListP attrsForB(void) {
    icmAttrListP userAttrs = icmNewAttrList();
    icmAddUns64Attr (userAttrs, "verbose", 1);
    icmAddUns64Attr (userAttrs, "extinterrupts", 2);
    icmAddStringAttr(userAttrs, "extintlogfile", "test.log");
    return userAttrs;
}

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
    icmProcessorP procA = icmNewProcessor(
        "procA",            // CPU name
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
    icmBusP busA = icmNewBus("busA", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(procA, busA, busA);

    // create memory
    icmMemoryP localA = icmNewMemory("localA", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(busA, "mp1", localA, 0x00000000);


    // create a processor instance
    icmProcessorP procB = icmNewProcessor(
        "procB",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        modelFile,          // model file
        "modelAttrs",       // morpher attributes
		MODEL_FLAGS,        // attributes
        attrsForB(),        // user-defined attributes
        semihostFile,       // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor bus
    icmBusP busB = icmNewBus("busB", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(procB, busB, busB);

    // create memory
    icmMemoryP localB = icmNewMemory("localB", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(busB, "mp1", localB, 0x00000000);

    icmNetP n1 = icmNewNet("n1");
    icmNetP n2 = icmNewNet("n2");
    icmNetP n3 = icmNewNet("n3");

    icmConnectProcessorNet(procA, n1, "intr0", ICM_INPUT);
    icmConnectProcessorNet(procB, n2, "intr0", ICM_INPUT);
    icmConnectProcessorNet(procB, n3, "intr1", ICM_INPUT);

    // advance the processors, then interrupt
    icmSimulate(procA, 9);
    icmSimulate(procB, 9);
    icmPrintf("Interrupting A & B\n");
    icmWriteNet(n1, 1);
    icmWriteNet(n3, 1);
    icmSimulate(procA, 1);
    icmSimulate(procB, 1);
    icmWriteNet(n1, 0);
    icmWriteNet(n3, 0);
    icmSimulate(procA, 9);
    icmSimulate(procB, 9);

    icmPrintf("Interrupting B\n");
    icmWriteNet(n2, 1);
    icmSimulate(procA, 1);
    icmSimulate(procB, 1);
    icmWriteNet(n2, 0);
    icmSimulate(procA, 10);
    icmSimulate(procB, 10);

    // report the total number of instructions executed
    icmPrintf(
        "processor A has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(procA)
    );
    icmPrintf(
        "processor B has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(procB)
    );

    icmTerminate();

    return 0;
}

static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    Bool ok = icmCLParseArgs(parser, argc, argv);
	return ok;
}

