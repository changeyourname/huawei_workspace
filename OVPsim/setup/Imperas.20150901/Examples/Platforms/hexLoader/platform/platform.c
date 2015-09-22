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

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor;
    icmBusP        bus;
} handles;

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager
    icmInitPlatform(ICM_VERSION, ICM_STOP_ON_CTRLC, 0, 0, "platform");

    // select library components
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "modelSupport", "imperasExit", "1.0", "model");

    // create a processor
    handles.processor = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        0,                  // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor bus
    handles.bus = icmNewBus("bus", 32);

    // connect the processor busses
    icmConnectProcessorBusses(handles.processor, handles.bus, handles.bus);

    // create simulated memory from 0x10000000
    // NOTE: Assembler program terminates simulation by invalid read from 0x00000000
    icmMemoryP memory = icmNewMemory("memory", ICM_PRIV_RWX, 0xffffffff-0x00100000);

    // connect memories to handles.bus
    icmConnectMemoryToBus(handles.bus, "mp1", memory, 0x00100000);

}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static int loadHexFile(icmProcessorP processor, const char *fileName, Bool swap);
static Bool cmdParser(int argc, const char *argv[]);

struct optionsS {
    const char*  hexfile;
} options;

int main(int argc, const char *argv[])
{
	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", "platform", "Command Line parser error");
		icmExitSimulation(1);
		return 1;
	}

	// the constructor
	createPlatform();

    // show the bus connections
    icmPrintBusConnections(handles.bus);

    icmSimulationStarting();

    // Load Hex file into Simulator Memory
    if (loadHexFile(handles.processor, options.hexfile, False)) {
        printf("Hex File Load of %s Failed\n", options.hexfile);
        icmExitSimulation(1);
        return 1;
    }

    Bool done = False;

    // Reset the PC to _start
    Uns32 setPC = 0x01000074;
    icmWriteReg(handles.processor, "PC", &setPC);

    while(!done) {

        Uns32 currentPC = (Uns32)icmGetPC(handles.processor);

        // disassemble instruction at current PC
        icmPrintf(
            "0x%08x : %s\n", currentPC,
            icmDisassemble(handles.processor, currentPC)
        );

        // execute one instruction
        done = (icmSimulate(handles.processor, 1) != ICM_SR_SCHED);

        // dump registers
        icmDumpRegisters(handles.processor);
    }

    // free simulation data structures
    icmTerminate();

    icmExitSimulation(0);
    return 0;
}

//
// Load a hex file into simulation memory
//
#define MAX_LINE_LENGTH 64

static int loadHexFile(icmProcessorP processor, const char *fileName, Bool swap) {

    FILE *fp;
    char inBuf[MAX_LINE_LENGTH + 1];
    int address, endAddress, data, dataCheck;

    fp = fopen(fileName, "r");

    if (!fp) {
        printf ("Failed to open Memory Initialization File %s\n", fileName);
        return -1;
    }

    icmPrintf("\nLoading Hex file %s\n", fileName);

    while ( fgets( inBuf,MAX_LINE_LENGTH, fp) != 0 ) {

        if ( inBuf[0] == '#') {
            // ignore header
        } else {
            if ( sscanf(inBuf, "%08x-%08x %08x ;", &address, &endAddress, &data) != 3 ) {
                sscanf(inBuf, "%08x %08x ;", &address, &data);
                endAddress = address;
            }

            if (swap) {  //byte swap
                data = (data & 0x000000ff) << 24 |
                       (data & 0x0000ff00) <<  8 |
                       (data & 0x00ff0000) >>  8 |
                       (data & 0xff000000) >> 24 ;
            }

            do {
                //
                // Access the memory through the processor memory space
                //
                icmWriteProcessorMemory(handles.processor,      // processor
                                        address,        // memory address
                                        &data,          // data buffer of data to write
                                        4);             // number of bytes to write

                icmReadProcessorMemory(handles.processor, address, &dataCheck, 4);

                if(data != dataCheck) {
                    icmPrintf("Failed Data Read Back at 0x%08x\n", (Uns32)address);
                    return -1;
                }

                icmPrintf("  0x%08x <= 0x%08x\n", address, data);
            } while ( address++ < endAddress);
        }
    }

    icmPrintf("Load Complete\n\n");

    if (fclose(fp)!=0) {
        printf ("Failed to close Memory Initialization File\n");
        return -1;
    }

    return 0;
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --hexfile <hex file to load>\n");
	icmCLParserUsageMessage(parser, (const char *)message);

	icmCLParserAdd(parser, "hexfile"  , 0 , 0, "user platform config", ICM_AT_STRINGVAL    , &options.hexfile, "The HEX file to be loaded", 0x0, 0, 0);

	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"hexfile")) {
		icmMessage("E", "hexfile", "Argument '--hexfile' must be used to specify the hex file to load");
		ok = False;
	}
	return ok;
}
