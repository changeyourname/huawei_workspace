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

#include <stdio.h>
#include <string.h>

#include "icm/icmCpuManager.h"

#define SIM_ATTRS (ICM_ATTR_DEFAULT)
#define PLATFORM "BareMetalMips32Single"


void createPlatform() {

    // initialize OVPsim, enabling verbose mode to get statistics at end
    // of execution
    icmInitPlatform(ICM_VERSION, ICM_VERBOSE|ICM_STOP_ON_CTRLC, 0, 0, PLATFORM);

    icmAttrListP userAttrs = icmNewAttrList();
    icmAddStringAttr(userAttrs, "endian",  "big");      // set endian
    icmAddStringAttr(userAttrs, "variant", "4Km");      // set model variant (default 4Km)
                                                        // CrossCompiler CROSS=MIPS32 from installer mips32.toolchain
                                                        // only supports non TLB variants 4Km/4Kp
                                                        // change to use CROSS=CS_MIPS32, Semihost mips32Newlib
                                                        // and CodeSourcery toolchain for others

    const char *mips32Model    = icmGetVlnvString(NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", "model");
    const char *mips32Semihost = icmGetVlnvString(NULL, "mips.ovpworld.org", "semihosting", "mips32SDE", "1.0", "model");

    // create a processor instance
    icmProcessorP processor = icmNewProcessor(
        "cpu0",             // CPU name
        "mips32",           // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        mips32Model,        // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // attributes
        userAttrs,          // user-defined attributes
        mips32Semihost,     // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor busses
    icmBusP bus = icmNewBus("bus", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(processor, bus, bus);

    // create memory
    icmMemoryP local = icmNewMemory("local", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(bus, "mp1", local, 0x00000000);

}



// Function Prototypes declaration
static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);

//
// Main routine
//
int main(int argc, const char **argv) {

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

    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    char message[1024];
    sprintf(message, "Basic Usage\n  %s --program <elf file>\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbgui : start and connect remote debugger in console or iGui mode\n"
                     "Configuration Options\n"
                     "    --variant <variant>   : set the processor variant configuration\n", argv[0]);
	icmCLParserUsageMessage(parser, (const char *)message);
    Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", PLATFORM, "Argument '--program' must be specified");
		ok = False;
	}
	return ok;
}

static void addPlatformDocumentation() {

	icmSetPlatformStatus(ICM_OVP,ICM_BAREMETAL,ICM_VISIBLE);

	icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
	{
		icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
		icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
		icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
		icmDocTextAdd(doc_12_node, "Bare Metal Platform for an MIPS32 Processor (variant 4Km)."
									"The bare metal platform instantiates a single MIPS32 processor instance. "
									"The processor operate using big endian data ordering."
									"It creates contiguous memory from 0x00000000 to 0xFFFFFFFF."
									"The ICM platform can be passed any application compiled to an MIPS32 elf format as the first argument."
									"./platform.<OS>.exe --program application.elf");
		icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
		icmDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS MIPS32 binary files compiled with MIPS SDE CrossCompiler toolchain");
		icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
		icmDocTextAdd(doc_32_node, "None");
	}
}
