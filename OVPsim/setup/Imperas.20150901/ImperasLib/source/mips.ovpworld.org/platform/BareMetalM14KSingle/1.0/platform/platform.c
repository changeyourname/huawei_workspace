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
#include <stdlib.h>
#include <string.h>

#include "icm/icmCpuManager.h"

#define PLATFORM "BareMetalM14KSingle"

// Function Prototypes early declaration
static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);
static const char *selectVendor(void);

// vendor options for processor model
const char *vendor[] = {"mips.ovpworld.org", "mips.com", 0};
#define NUMBER_VENDORS 2

// Set of valid model variants
const char *modelVariantList[] = { "M14K", "M14KcFMM", "M14KcTLB", "microAptivC", "microAptivP",   0};

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

    // initialize OVPsim, enabling verbose mode to get statistics at end of execution
    unsigned int icmAttrs = ICM_VERBOSE | ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, icmAttrs, 0, 0, PLATFORM);

    addPlatformDocumentation();

    // Select components from library
    const char *vendorP = selectVendor();
    const char *mipsModel    = icmGetVlnvString(NULL, vendorP, "processor", "mips32", "1.0", "model");
    const char *mipsSemihost = icmGetVlnvString(NULL, vendorP, "semihosting", "mips32Newlib", "1.0", "model");

    Uns32 simAttrs = ICM_ATTR_DEFAULT;

    // Setup the configuration attributes for the MIPS model
    icmAttrListP userAttrs = icmNewAttrList();
    icmAddStringAttr(userAttrs, "endian", "big" );       // setup endianess
    icmAddStringAttr(userAttrs, "variant", "M14K");      // Select the processor configuration

    // The complete configuration of the Processor Model uses the configuration parameters
    // defined for the processor.
    // The attributes available to further configure a processor model are detailed
    // in the library listing in the README.txt or XML file.
    // Further attributes should be added to the userAttrs list.

    icmProcessorP processor = icmNewProcessor(
        "M14K_1",           // CPU name
        "microMIPS",        // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        mipsModel,          // model file
        "modelAttrs",       // morpher attributes
        simAttrs,           // attributes
        userAttrs,          // user-defined attributes
        mipsSemihost,       // semi-hosting file
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

    // Ignore specific Info messages
    icmIgnoreMessage ("MIPS32_IAS_COP0_READ");
    icmIgnoreMessage ("MIPS32_IAS_COP0_WRITE");

    // simulate the platform
    icmProcessorP final = icmSimulatePlatform();

    // was simulation interrupted or did it complete
    if(final && (icmGetStopReason(final)==ICM_SR_INTERRUPT)) {
        icmPrintf("*** simulation interrupted\n");
    }

    // Finish simulating
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}




struct optionsS {
    const char    *vendor;
} options;

static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    char message[1024];
    sprintf(message, "Basic Usage\n  %s --program <elf file>\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbgui : start and connect remote debugger in console or iGui mode\n"
                     "Configuration Options\n"
                     "    --vendor <vendor>     : set the vendor for model loading e.g mips.ovpworld.org, mips.com \n"
                     "    --variant <variant>   : set the processor variant configuration (", argv[0]);
    int i;
    for(i=0;modelVariantList[i];i++) {
    	char tmp[32];
    	sprintf(tmp, " %s", modelVariantList[i]);
		strcat(message, tmp);
	}
    strcat(message, " )\n");
                     
	icmCLParserUsageMessage(parser, (const char *)message);
    icmCLParserAdd(parser, "vendor"  , 0 , "string", "user configuration", ICM_AT_STRINGVAL, &options.vendor, "set the vendor for model loading e.g mips.ovpworld.org, mips.com ", 0x0, 0, 0);
    Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", PLATFORM, "Argument '--program' must be specified");
		ok = False;
	}
	return ok;
}

//
// Select vendor to use for models
//
static const char *selectVendor() {
    Uns32 i, index = 0;

	if(options.vendor) {
		return options.vendor;
	} else {
		// Select default model vendor to be used to load model
		char *runtime = getenv("IMPERAS_RUNTIME");
		if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
			;        // leave default index
		} else {
			index++; // start from next vendor
		}
		for(i=0;i<NUMBER_VENDORS;i++){
			const char *mipsModel    = icmTryVlnvString(NULL, vendor[index], "processor", "mips32", "1.0", "model");
			const char *mipsSemihost = icmTryVlnvString(NULL, vendor[index], "semihosting", "mips32Newlib", "1.0", "model");
			if(mipsModel && mipsSemihost) {
				return vendor[index];
			}
			// Select next in list, if zero back to first
			if (!vendor[++index]) index = 0;
		}

		icmMessage("F", "MODEL", "No Model Available");
		// Will never reach here
		return NULL;
    }
}

static void addPlatformDocumentation() {
    icmSetPlatformStatus(ICM_OVP,ICM_BAREMETAL,ICM_VISIBLE);

    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "Bare Metal Platform for a MIPS M14K Processor."
                "The bare metal platform instantiates a single M14K processor instance, using little endian data ordering."
                ""
                "The ICM platform can be passed any application compiled to a MIPS elf format as the argument"
                "It will also allow a port number to be specified to allow the connection of a remote GDB debugger."
                ""
                "platform.OS.exe --program application.CROSS.elf [--port <gdb port>]"
                ""
                "Where OS is Linux or Windows");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS M14K binary files compiled with CodeSourcery CrossCompiler toolchain.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "None");
    }
}
