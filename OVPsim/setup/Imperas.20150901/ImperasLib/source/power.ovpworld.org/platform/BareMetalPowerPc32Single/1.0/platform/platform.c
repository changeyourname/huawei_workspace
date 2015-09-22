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

#define PLATFORM "BareMetalPowerPc32Single"

void createPlatform() {

////////////////////////////////////////////////////////////////////////////////

    // initialize OVPsim, enabling verbose mode to get statistics at end of execution
    unsigned int icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

	////////////////////////////////////////////////////////////////////////////////
	//                                 Bus bus1_b                                 //
	////////////////////////////////////////////////////////////////////////////////

    icmBusP bus1_b = icmNewBus( "bus1_b", 32);


	////////////////////////////////////////////////////////////////////////////////
	//                               Processor cpu1                               //
	////////////////////////////////////////////////////////////////////////////////
#define SIM_ATTRS (ICM_ATTR_DEFAULT)

    icmAttrListP cpu1_attr = icmNewAttrList();

    icmAddStringAttr(cpu1_attr, "endian",        "big");
    icmAddDoubleAttr(cpu1_attr, "mips", 100.000000);

    const char *powerpc32Model    = icmGetVlnvString(NULL, "power.ovpworld.org", "processor",   "powerpc32",       "1.0", "model");
    const char *powerpc32Semihost = icmGetVlnvString(NULL, "power.ovpworld.org", "semihosting", "powerpc32Newlib", "1.0", "model");

    icmProcessorP cpu1_c = icmNewProcessor(
        "cpu1",   // name
        "powerpc32",   // type
        0,   // cpuId
        0x0, // flags
         32,   // address bits
        powerpc32Model,   // model
        "modelAttrs",   // symbol
        SIM_ATTRS,   // procAttrs
        cpu1_attr,   // attrlist
        powerpc32Semihost,   // semihost file
        "modelAttrs"  // semihost symbol
    );

    icmConnectProcessorBusses( cpu1_c, bus1_b, bus1_b );


	////////////////////////////////////////////////////////////////////////////////
	//                                Memory memory                               //
	////////////////////////////////////////////////////////////////////////////////

    icmMemoryP memory_m = icmNewMemory("memory_m", 0x7, 0xffffffff);

    icmConnectMemoryToBus( bus1_b, "sp1", memory_m, 0x0);

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
    sprintf(message, "Basic Usage\n  %s --program <elf file>\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbgui : start and connect remote debugger in console or iGui mode\n", argv[0]);
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
		icmDocTextAdd(doc_12_node, "Bare Metal Platform for an PowerPc32 Processor."
			"The bare metal platform instantiates a single PowerPc32 processor instance."
			"It creates contiguous memory from 0x00000000 to 0xFFFFFFFF."
			"The ICM platform can be passed any application compiled to an M16C elf format as the first argument."
			"./platform.<OS>.exe --program application.elf");
		icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
		icmDocTextAdd(doc_22_node, "BareMetal platform for execution of PowerPc32 binary files.");
		icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
		icmDocTextAdd(doc_32_node, "None, baremetal platform definition");
	}
}
