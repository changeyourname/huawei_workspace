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

#define PLATFORM "BareMetalArm7Single"

void createPlatform() {

    // initialize OVPsim, enabling verbose mode to get statistics at end of execution
    unsigned int icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

    const char *arm7Model    = icmGetVlnvString(NULL, "arm.ovpworld.org", "processor", "arm", "1.0", "model");
    const char *arm7Semihost = icmGetVlnvString(NULL, "arm.ovpworld.org", "semihosting", "armNewlib", "1.0", "model");

    icmAttrListP icmAttr = icmNewAttrList();
    icmAddStringAttr(icmAttr, "variant", "ARM7TDMI");   // set the variant
    icmAddStringAttr(icmAttr, "endian", "little");      // set endian ordering
    icmAddStringAttr(icmAttr, "compatibility", "gdb");  // set register reset compatible with GDB
    icmAddStringAttr(icmAttr, "UAL", "1");              // set disassembly output UAL syntax

#define SIM_ATTRS (ICM_ATTR_DEFAULT)

    // create a processor instance
    icmProcessorP processor = icmNewProcessor(
        "cpu1",             // CPU name
        "arm",              // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        arm7Model,          // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // attributes
        icmAttr,            // user-defined attributes
        arm7Semihost,       // semi-hosting file
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
		icmDocTextAdd(doc_12_node, "Bare Metal Platform for an ARM7 Processor.");
		icmDocTextAdd(doc_12_node, "The bare metal platform instantiates a single ARM7 processor instance.");
		icmDocTextAdd(doc_12_node, "The processor operates using little endian data ordering.");
		icmDocTextAdd(doc_12_node, "It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.");
		icmDocTextAdd(doc_12_node, "The ICM platform can be passed any application compiled to an ARM elf format as the first argument.");
		icmDocTextAdd(doc_12_node, "./platform.<OS>.exe --program application.elf");
		icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
		icmDocTextAdd(doc_22_node, "BareMetal platform for execution of ARM binary files compiled with Linaro 32-bit CrossCompiler toolchain.");
		icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
		icmDocTextAdd(doc_32_node, "None");
	}
}
