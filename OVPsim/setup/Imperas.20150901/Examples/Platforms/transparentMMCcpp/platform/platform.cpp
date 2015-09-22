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

#include "icm/icmCpuManager.hpp"


using namespace icmCpuManager;

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    // check for the application program name argument
    if(argc!=2) {
        icmPrintf("usage: %s <application name>\n", argv[0]);
        return -1;
    }

    const char *app = argv[1];

    icmPlatform platform(NULL);
    icmPrintf("1x transparent MMC using %s\n", argv[1]);

    // select library components
	const char *vlnvRoot    = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");
    const char *mmc_model   = icmGetVlnvString(vlnvRoot, "ovpworld.org", "mmc", "wb_1way_32byteline_2048tags", "1.0", "model");

    // create a processor
    icmProcessorObject cpu1(
            "cpu1",             // CPU name
            "or1k",             // CPU type
            0,                  // CPU cpuId
            0,                  // CPU model flags
            32,                 // address bits
            model,              // model file
            "modelAttrs",       // morpher attributes
            ICM_ATTR_DEFAULT,   // simulation attributes
            0,                  // user-defined attributes
            semihosting,        // semi-hosting file
            "modelAttrs"        // semi-hosting attributes
        );

    // create transparent MMC
    icmMmcObject mmc1("mmc1", mmc_model, "modelAttrs", 0, True);

    // create busses
    icmBusObject pbus("pbus", 32);
    icmBusObject mbus("mbus", 32);

    // connect processor busses
    cpu1.connect(pbus, pbus);

    // insert MMC between processor and memory
    mmc1.connect(mbus, "mp1", True);
    mmc1.connect(pbus, "sp1", False);

    // create two simulated memories for low and high regions
    icmMemoryObject memory1("mem1", ICM_PRIV_RWX, 0x003fffff);
    icmMemoryObject memory2("mem2", ICM_PRIV_RWX, 0xffffffff-0x00401000);

    // connect memories to bus
    memory1.connect("mp1", mbus, 0x00000000);
    memory2.connect("mp2", mbus, 0x00401000);

    // load the processor object file
    cpu1 << app;

    // run until exit
    platform.simulate();

    return 0;
}
