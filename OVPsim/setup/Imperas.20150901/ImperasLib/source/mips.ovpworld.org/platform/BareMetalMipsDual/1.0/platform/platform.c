/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "icm/icmCpuManager.h"

#define PLATFORM "BareMetalMipsDual"

static void createPlatform() {

	////////////////////////////////////////////////////////////////////////////////

    icmInitPlatform(ICM_VERSION, ICM_VERBOSE|ICM_STOP_ON_CTRLC, 0, 0, PLATFORM);

    const char *mipsModel    = icmGetVlnvString(NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", "model");
    const char *mipsSemihost = icmGetVlnvString(NULL, "mips.ovpworld.org", "semihosting", "mips32Newlib", "1.0", "model");

    icmAttrListP icmAttr1 = icmNewAttrList();
    icmAddStringAttr(icmAttr1, "endian",        "big");
    icmAddStringAttr(icmAttr1, "variant",       "74Kc");		// default variant

    // create a processor instance
    icmProcessorP processor0 = icmNewProcessor(
        "cpu0",             // CPU name
        0,
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        mipsModel,          // model file
        0,
        ICM_ATTR_DEFAULT,   // attributes
        icmAttr1,           // user-defined attributes
        mipsSemihost,        // semi-hosting file
        0
    );

    // create the processor bus
    icmBusP bus0 = icmNewBus("bus0", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(processor0, bus0, bus0);

    // create memory
    icmMemoryP local0 = icmNewMemory("local0", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(bus0, "mp1", local0, 0x00000000);

    icmAttrListP icmAttr2 = icmNewAttrList();
    icmAddStringAttr(icmAttr2, "endian",        "big");
    icmAddStringAttr(icmAttr2, "variant",       "74Kc");     // default variant

    // create a processor instance
    icmProcessorP processor1 = icmNewProcessor(
        "cpu1",             // CPU name
        0,
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        mipsModel,          // model file
        0,
        ICM_ATTR_DEFAULT,   // attributes
        icmAttr2,           // user-defined attributes
        mipsSemihost,       // semi-hosting file
        0
    );

    // create the processor bus
    icmBusP bus1 = icmNewBus("bus1", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(processor1, bus1, bus1);

    // create memory
    icmMemoryP local1 = icmNewMemory("local", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(bus1, "mp1", local1, 0x00000000);

    // Ignore specific message that compatibility mode causes
    icmIgnoreMessage("ARM_MORPH_BII");

}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);

int main(int argc, const char *argv[])
{

	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", PLATFORM, "Command Line parser error");
		icmExitSimulation(1);
		return 1;
	}

    // the constructor
    createPlatform();

    addPlatformDocumentation();

    // simulate the platform
    icmProcessorP final = icmSimulatePlatform();

    // was simulation interrupted or did it complete
    if(final && (icmGetStopReason(final)==ICM_SR_INTERRUPT)) {
        icmPrintf("*** simulation interrupted\n");
    }

    // finish and clean up
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    char message[1024];
    sprintf(message, "Basic Usage\n"
    		         "  %s --program <elf file>             : load same application onto all processors\n"
    	             "  %s --program <cpu name>=<elf file>  : load specified processor with application\n"
                     "Debug Options\n"
                     "    --port <port number>        : open debug port\n"
                     "    --gbdconsole/--gdbgui       : start and connect remote debugger in console or iGui mode\n"
    		         "    --debugprocessor <instance> : select the processor to attach GDB (OVPsim allows single GDB connection, Imperas allows debug of all)", argv[0], argv[0]);
	icmCLParserUsageMessage(parser, (const char *)message);
    Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", PLATFORM, "Argument '--program' must be specified");
		ok = False;
	}
	return ok;
}

////////////////////////////////////////////////////////////////////////////////

static void addPlatformDocumentation() {

    icmSetPlatformStatus(ICM_OVP,ICM_BAREMETAL,ICM_VISIBLE);

    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "Bare Metal Platform for a MIPS32 Processor (default 74Kc)."
    "The bare metal platform instantiates two MIPS32 processor instances. "
    "The processor operates using big endian data ordering."
    "It creates contiguous memory from 0x00000000 to 0xFFFFFFFF."
    "The ICM platform can be passed any application compiled to a MIPS elf format."
    "The same application executes on each processor. There is no sharing of data."
    "It may also be passed a new variant to be used (default 74Kc)"
    "./platform.OS.exe --program application.CROSS.elf [--variant <model variant>]");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS MIPS32 binary files compiled with CodeSourcery CrossCompiler toolchain.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "None");
    }
}
