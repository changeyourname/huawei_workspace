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

#define SIM_ATTRS (ICM_ATTR_DEFAULT)

#define PLATFORM "BareMetalArmx1Mips32x3"

// create an array of pointers to processor instances
static icmProcessorP processor[4];


void createPlatform() {

    // initialize OVPsim, enabling verbose mode to get statistics at end of execution
    unsigned int icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC | ICM_ENABLE_IMPERAS_INTERCEPTS;

    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

    // create processors
    const char *armModel    = icmGetVlnvString(NULL, "arm.ovpworld.org", "processor", "arm", "1.0", "model");
    const char *armSemihost = icmGetVlnvString(NULL, "arm.ovpworld.org", "semihosting", "armNewlib", "1.0", "model");

    icmAttrListP armUserAttr = icmNewAttrList();
    icmAddStringAttr(armUserAttr, "variant", "Cortex-A9UP");
    icmAddStringAttr(armUserAttr, "compatibility", "nopSVC");   // ignore the svc trap instructions

    processor[0] = icmNewProcessor(
        "CPU0_ARM",          // CPU name
        "arm",               // CPU type
        0,                   // CPU cpuId
        0,                   // CPU model flags
        32,                  // address bits
        armModel,            // model file
        "modelAttrs",        // morpher attributes
        SIM_ATTRS,           // attributes
        armUserAttr,         // user-defined attributes
        armSemihost,         // semi-hosting file
        "modelAttrs"         // semi-hosting attributes
    );

    // Processors in the platform exchanging data must use the same endian
    // By default the MIPS processor is big endian and the ARM processor is
    // little endian.
    // Use attributes to change the endian used by the MIPS processor.

    const char *mips32Model    = icmGetVlnvString(NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", "model");
    const char *mips32Semihost = icmGetVlnvString(NULL, "mips.ovpworld.org", "semihosting", "mips32Newlib", "1.0", "model");

    icmAttrListP mipsUserAttr1 = icmNewAttrList();
    icmAddStringAttr(mipsUserAttr1, "endian", "little");
    icmAddStringAttr(mipsUserAttr1, "variant", "24KEc");

    processor[1] = icmNewProcessor(
        "CPU1_MIPS",         // CPU name
        "mips32",            // CPU type
        1,                   // CPU cpuId
        0,                   // CPU model flags
        32,                  // address bits
        mips32Model,         // model file
        "modelAttrs",        // morpher attributes
        SIM_ATTRS,           // attributes
        mipsUserAttr1,       // user-defined attributes
        mips32Semihost,      // semi-hosting file
        "modelAttrs"         // semi-hosting attributes
    );

    icmAttrListP mipsUserAttr2 = icmNewAttrList();
    icmAddStringAttr(mipsUserAttr2, "endian", "little");
    icmAddStringAttr(mipsUserAttr2, "variant", "24KEc");

    processor[2] = icmNewProcessor(
        "CPU2_MIPS",         // CPU name
        "mips32",            // CPU type
        2,                   // CPU cpuId
        0,                   // CPU model flags
        32,                  // address bits
        mips32Model,         // model file
        "modelAttrs",        // morpher attributes
        SIM_ATTRS,           // attributes
        mipsUserAttr2,       // user-defined attributes
        mips32Semihost,      // semi-hosting file
        "modelAttrs"         // semi-hosting attributes
    );

    icmAttrListP mipsUserAttr3 = icmNewAttrList();
    icmAddStringAttr(mipsUserAttr3, "endian", "little");
    icmAddStringAttr(mipsUserAttr3, "variant", "24KEc");

    processor[3] = icmNewProcessor(
        "CPU3_MIPS",         // CPU name
        "mips32",            // CPU type
        3,                   // CPU cpuId
        0,                   // CPU model flags
        32,                  // address bits
        mips32Model,         // model file
        "modelAttrs",        // morpher attributes
        SIM_ATTRS,           // attributes
        mipsUserAttr3,       // user-defined attributes
        mips32Semihost,      // semi-hosting file
        "modelAttrs"         // semi-hosting attributes
    );

    // create the processor busses
    // NOTE: One bus for each processor instantiation
    icmBusP bus1 = icmNewBus("bus1", 32);
    icmBusP bus2 = icmNewBus("bus2", 32);
    icmBusP bus3 = icmNewBus("bus3", 32);
    icmBusP bus4 = icmNewBus("bus4", 32);
    icmBusP busS = icmNewBus( "busShare", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(processor[0], bus1, bus1);
    icmConnectProcessorBusses(processor[1], bus2, bus2);
    icmConnectProcessorBusses(processor[2], bus3, bus3);
    icmConnectProcessorBusses(processor[3], bus4, bus4);

    // create memories
    icmMemoryP local0 = icmNewMemory("local0", ICM_PRIV_RWX, 0x01ffffff);
    icmMemoryP local1 = icmNewMemory("local1", ICM_PRIV_RWX, 0x01ffffff);
    icmMemoryP local2 = icmNewMemory("local2", ICM_PRIV_RWX, 0x01ffffff);
    icmMemoryP local3 = icmNewMemory("local3", ICM_PRIV_RWX, 0x01ffffff);

    icmMemoryP shared = icmNewMemory("shared", ICM_PRIV_RWX, 0x01ffffff);

    // connect the memories onto the busses
    // connect local memories onto individual processor buses
    icmConnectMemoryToBus(bus1, "mp1", local0, 0x00000000);
    icmConnectMemoryToBus(bus2, "mp1", local1, 0x00000000);
    icmConnectMemoryToBus(bus3, "mp1", local2, 0x00000000);
    icmConnectMemoryToBus(bus4, "mp1", local3, 0x00000000);

    // connect the memory to the bus and bridge onto all the local buses
    // this makes it available to all processors at the specified address
    // NOTE: in this case the shared memory appears at the same address for all
    // processors but it could be at any address in each processors address map
    icmConnectMemoryToBus(busS, "mp1", shared, 0x02000000);
    icmNewBusBridge(bus1, busS, "br1", "sp1", "mp1", 0x2000000, 0x2ffffff, 0x2000000);
    icmNewBusBridge(bus2, busS, "br2", "sp1", "mp1", 0x2000000, 0x2ffffff, 0x2000000);
    icmNewBusBridge(bus3, busS, "br3", "sp1", "mp1", 0x2000000, 0x2ffffff, 0x2000000);
    icmNewBusBridge(bus4, busS, "br4", "sp1", "mp1", 0x2000000, 0x2ffffff, 0x2000000);

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

    // Ignore some of the Info messages
    icmIgnoreMessage ("MIPS32_IAS_COP0_READ");
    icmIgnoreMessage ("MIPS32_IAS_COP0_WRITE");

    // load the processor object files
    const char *appArm="writer.ARM_CORTEX_A9.elf";
    const char *appMips1="reader1.CS_MIPS32LE.elf";
    const char *appMips2="reader2.CS_MIPS32LE.elf";
    const char *appMips3="reader3.CS_MIPS32LE.elf";
    icmImagefileP load1 = icmLoadProcessorMemory(processor[0], appArm,   ICM_LOAD_DEFAULT, False, True);
    icmImagefileP load2 = icmLoadProcessorMemory(processor[1], appMips1, ICM_LOAD_DEFAULT, False, True);
    icmImagefileP load3 = icmLoadProcessorMemory(processor[2], appMips2, ICM_LOAD_DEFAULT, False, True);
    icmImagefileP load4 = icmLoadProcessorMemory(processor[3], appMips3, ICM_LOAD_DEFAULT, False, True);

    if (!load1 || !load2 || !load3 || !load4) {
    	icmMessage("E", PLATFORM"_LOAD", "Failed to load one or more application onto processor");
    }

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
	sprintf(message, "Basic Usage\n  %s  : loads fixed applications onto each processor and starts execution\n"
					 "Debug Options\n"
					 "    --gbdconsole/--gdbgui       : start and connect remote debugger in console or iGui mode\n"
					 "    --debugprocessor <instance> : processor to attach GDB\n", argv[0]);
	icmCLParserUsageMessage(parser, (const char *)message);
	Bool ok = icmCLParseArgs(parser, argc, argv);

	return ok;
}

static void addPlatformDocumentation() {
	icmSetPlatformStatus(ICM_OVP,ICM_BAREMETAL,ICM_VISIBLE);

	icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
	{
		icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
		icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
		icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
		icmDocTextAdd(doc_12_node, "Bare Metal Platform for MIPS32 Processors.");
		icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
		icmDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS32 binary files compiled with CodeSourcery MIPS32 CrossCompiler toolchain.");
		icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
		icmDocTextAdd(doc_32_node, "None, BareMetal platform definition");
	}
}
