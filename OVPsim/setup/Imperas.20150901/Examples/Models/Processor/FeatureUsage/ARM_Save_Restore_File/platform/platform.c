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

#define PROC_ATTRS ( \
    ICM_ATTR_TRACE        | \
    ICM_ATTR_TRACE_ICOUNT | \
    ICM_ATTR_TRACE_CHANGE | \
    ICM_ATTR_SIMEX          \
)

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

       default:
           icmPrintf("unimplemented stopReason %u\n", stopReason);
           return False;
    }
}

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    Int32       icount    = -1;
    Uns32       doSave    = False;
    Uns32       doRestore = False;
    const char *srFile    = 0;

    // validate number of arguments
    if((argc<2) || (argc>6)) {
        icmPrintf("Usage: %s <application file name> [icount] [sr_file] [do_save] [do_restore]\n", argv[0]);
        exit(-1);
    }

    // get instruction count
    if(argc>=3) {
        sscanf(argv[2], "%d", &icount);
    }

    // get save/restore file
    if(argc>=4) {
        srFile = argv[3];
    }

    // get save/restore booleans
    if(argc>=5) {
        sscanf(argv[4], "%d", &doSave);
    }
    if(argc>=6) {
        sscanf(argv[5], "%d", &doRestore);
    }

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, 0, 0, 0, "platform");

    // create bus
    icmBusP bus = icmNewBus("bus", 32);

    // create physical memory
    icmMemoryP mem  = icmNewMemory("memory", ICM_PRIV_RWX, 0xffffffffULL);
    icmConnectMemoryToBus(bus, "p1", mem, 0);

    // set up processor instance attributes
    icmAttrListP userAttrs = icmNewAttrList();
    icmAddStringAttr(userAttrs, "endian", "little");
    icmAddStringAttr(userAttrs, "variant", "Cortex-A9UP");

    // create a processor and connect to bus
    const char *model    =
        icmTryVlnvString(NULL, "arm.ovpworld.org", "processor",    "arm",         "1.0", "model");
    const char *semihost =
        icmTryVlnvString(NULL, "ovpworld.org",     "modelSupport", "imperasExit", "1.0", "model");
    icmProcessorP processor = icmNewProcessor(
        "cpu1",                             // CPU name
        "arm",                              // CPU type
        0,                                  // CPU cpuId
        0,                                  // CPU model flags
        32,                                 // address bits
        model,                              // model file
        "modelAttrs",                       // morpher attributes
        PROC_ATTRS,                         // processor attributes
        userAttrs,                          // user-defined attributes
        semihost,                           // semi-hosting file
        "modelAttrs"                        // semi-hosting attributes
    );
    icmConnectProcessorBusses(processor, bus, bus);

    // load the processor object file
    icmLoadProcessorMemory(processor, argv[1], ICM_LOAD_DEFAULT, False, True);

    icmPrintf("\nPLATFORM INITIALIZED\n\n");

    // restore from saved state if required
    if(doRestore) {
        char memFile[32];
        char procFile[32];
        sprintf(memFile,  "%s.mem",  srFile);
        sprintf(procFile, "%s.proc", srFile);
        icmPrintf("Restore memory state file %s...\n", memFile);
        icmMemoryRestoreStateFile(mem, memFile);
        icmPrintf("Restore processor state file %s...\n", procFile);
        icmProcessorRestoreStateFile(processor, procFile);
    }

    // run processor
    simulate(processor, icount);

    // save state if required
    if(doSave) {
        char memFile[32];
        char procFile[32];
        sprintf(memFile,  "%s.mem",  srFile);
        sprintf(procFile, "%s.proc", srFile);
        icmPrintf("Save memory state file %s...\n", memFile);
        icmMemorySaveStateFile(mem, memFile);
        icmPrintf("Save processor state file %s...\n", procFile);
        icmProcessorSaveStateFile(processor, procFile);
    }

    icmTerminate();

    return 0;
}

