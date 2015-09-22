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

#define PLATFORM "BareMetalArmCortexASingleAngelTrap"

void createPlatform() {

    // initialize OVPsim, enabling verbose mode to get statistics at end of execution
    unsigned int icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus bus1_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP bus1_b = icmNewBus( "bus1_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu1
////////////////////////////////////////////////////////////////////////////////

    const char *cpu1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "arm.ovpworld.org",    // vendor
        0,    // library
        "arm",    // name
        0,    // version
        "model"     // model
    );

    icmAttrListP cpu1_attr = icmNewAttrList();

    icmAddStringAttr(cpu1_attr, "variant", "Cortex-A9UP");	// default variant
    icmAddStringAttr(cpu1_attr, "UAL", "1");
    icmAddDoubleAttr(cpu1_attr, "mips", 100.000000);
    icmAddStringAttr(cpu1_attr, "endian", "little");
    const char *armAngel_0_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "arm.ovpworld.org",    // vendor
        0,    // library
        "armAngel",    // name
        0,    // version
        "model"     // model
    );

#define SIM_ATTRS (ICM_ATTR_DEFAULT)

    icmProcessorP cpu1_c = icmNewProcessor(
        "cpu1",   // name
        "arm",   // type
        0,   // cpuId
        0x0, // flags
         32,   // address bits
        cpu1_path,   // model
        "modelAttrs",   // symbol
        0x0,   // procAttrs
        cpu1_attr,   // attrlist
        armAngel_0_path,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectProcessorBusses( cpu1_c, bus1_b, bus1_b );


////////////////////////////////////////////////////////////////////////////////
//                                Memory memory
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
    icmSimulatePlatform();

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
        icmDocTextAdd(doc_12_node, "Bare Metal Platform for an ARM Cortex-A series Processor (default Cortex-A9UP) that uses the ARM Angel Trap for semihosting.");
        icmDocTextAdd(doc_12_node, "The bare metal platform instantiates a single ARM Cortex-A9UP processor instance.");
        icmDocTextAdd(doc_12_node, "The processor operates using little endian data ordering.");
        icmDocTextAdd(doc_12_node, "It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.");
        icmDocTextAdd(doc_12_node, "The ICM platform can be passed any application compiled to an ARM elf (axf) format, that uses ARM Angel traps for semihosting, as the first argument.");
        icmDocTextAdd(doc_12_node, "It may also be passed a new variant to be used (default Cortex-A9UP)");
        icmDocTextAdd(doc_12_node, "./platform.OS.exe application.CROSS.elf [model variant]");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "BareMetal platform for execution of ARM binary files compiled with Linaro 32-bit CrossCompiler toolchain for Cortex-A.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "None");
    }
}
