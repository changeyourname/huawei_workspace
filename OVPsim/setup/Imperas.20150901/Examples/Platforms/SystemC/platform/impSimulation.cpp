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


#include "systemc.h"

#include "impMemory.hpp"
#include "impProcessor.hpp"


#ifndef EXTMEM_BASEADDR
#define EXTMEM_BASEADDR 0
#define EXTMEM_SIZE	0
#endif

int sc_main(int argc, char **argv)
{
   bool         retCode      = false;
   impProcessor *proc        = NULL;
   impMemory    *extMemory   = NULL;
   sc_clock     *systemClock = NULL;
   icmPlatform  *platform    = new icmPlatform("test");

   // select library components
   const char *vlnvRoot    = NULL; //When NULL use default library
   const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
   const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");
   const char *application = "application/application.OR1K.elf";

   icmPrintf("Simulation started with the following parameters:\n");
   icmPrintf(
       "MORPHER_FILE:\t%s\n"
       "MORPHER_SYMBOL:\t%s\n"
       "SEMIHOST_FILE:\t%s\n"
       "SEMIHOST_SYMBOL:\t%s\n"
       "APPLICATION_OBJFILE:\t%s\n\n",
	   model,
       "modelAttrs",
       semihosting,
       "modelAttrs",
       application
   );

    // define clock period
    const sc_time clk_period(1, SC_US);

    systemClock = new sc_clock("SYSCLK", clk_period);

    proc = new impProcessor("CPU1", *systemClock);

    retCode = proc->init(
        "CPU1",
        "or1k",
        0,
        model,
        "modelAttrs",
        semihosting,
        "modelAttrs"
    );

    // If PROC was successfully created then attach some external memory to it, if required
    if (retCode && EXTMEM_BASEADDR) {

        // Create a memory object
        extMemory = new impMemory("EXTMEM", *systemClock);
        retCode = extMemory->init(EXTMEM_BASEADDR, EXTMEM_SIZE);

        icmPrintf(
            "SYSTEMC: Creating memory at %08x, size %d bytes\n",
            EXTMEM_BASEADDR, EXTMEM_SIZE
        );

        if (retCode) {
            icmPrintf("SYSTEMC: Callback routines registered\n");
            proc->localMem("local1", 0, EXTMEM_BASEADDR-1);
            proc->localMem("local2", EXTMEM_BASEADDR+EXTMEM_SIZE, 0xffffffff);
            proc->extMem(
                EXTMEM_BASEADDR,
	            (EXTMEM_BASEADDR+EXTMEM_SIZE-1),
	            memReadCB,
	            memWriteCB,
	            extMemory
            );
        }

    } else {

        proc->localMem("local", 0, 0xffffffff);
    }

    // Last thing to do is to load the application to simulate
    if (retCode) {
        proc->objfile(application);
    }

    // Processor and memory ready to simulate
    if (retCode) {
        icmPrintf("\nSYSTEMC: Starting Simulation ... \n");
        sc_start();
    }

    delete platform;

    return (int)retCode;
}

