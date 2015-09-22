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

#define PLATFORM "BareMetalALteraNiosII"

static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);

//
// Virtual platform construction
//
void createPlatform(void)
{

////////////////////////////////////////////////////////////////////////////////

    // initialize OVPsim, enabling verbose mode to get statistics at end of execution
    unsigned int icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC;

    // initialize OVPsim, enabling verbose mode to get statistics at end
    // of execution
    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

    addPlatformDocumentation();

#define SIM_ATTRS (ICM_ATTR_DEFAULT)

    const char *nios_iiModel =
        icmGetVlnvString(NULL, "altera.ovpworld.org", "processor", "nios_ii",
                               "1.0", "model");
    const char *nios_iiSemihost =
        icmGetVlnvString(NULL, "altera.ovpworld.org", "semihosting",
                               "nios_iiNewlib", "1.0", "model");

    icmAttrListP userAttrs = icmNewAttrList();
    icmAddStringAttr(userAttrs, "variant", "Nios_II_S");
    icmAddUns64Attr(userAttrs,  "HW_DIVIDE", 1);
    icmAddUns64Attr(userAttrs,  "HW_MULTIPLY", 1);

    // create a processor instance
    icmProcessorP processor = icmNewProcessor(
            "cpu0",           // CPU name
            "nios_ii",        // CPU type
            0,                // CPU cpuId
            0,                // CPU model flags
            32,               // address bits
            nios_iiModel,     // model file
            "modelAttrs",     // morpher attributes
            SIM_ATTRS,        // attributes
            userAttrs,        // user-defined attributes
            nios_iiSemihost,  // semi-hosting file
            "modelAttrs"      // semi-hosting attributes
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

int
main(int argc, const char *argv[])
{

	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", PLATFORM, "Command Line parser error");
		icmExitSimulation(1);
		return 1;
	}

    // the constructor
    createPlatform();

    // run till the end
    icmSimulatePlatform();

    // finish and clean up
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    char message[1024];
    sprintf(message, "Basic Usage\n  %s --program <elf file>\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbgui : start and connect remote debugger in console or iGui mode\n"
                     "The NIOS II processor is highly configurable, for all configuration options\n"
                     "    --showoverrides       : show override of configuration options\n", argv[0]);
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
		icmDocTextAdd(doc_12_node, "Bare Metal Platform for an ALtera Nios II Processor.");
		icmDocTextAdd(doc_12_node, "The bare metal platform instantiates a single processor instance, default Nios_II_S");
		icmDocTextAdd(doc_12_node, "It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.");
		icmDocTextAdd(doc_12_node, "The ICM platform can be passed any application compiled to the Nios II elf format.");
		icmDocTextAdd(doc_12_node, "It may also be passed a new variant to be used");
		icmDocTextAdd(doc_12_node, "./platform.OS.exe --program application.CROSS.elf [--variant <model variant>]");
		icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
		icmDocTextAdd(doc_32_node, "None");
	}
}
