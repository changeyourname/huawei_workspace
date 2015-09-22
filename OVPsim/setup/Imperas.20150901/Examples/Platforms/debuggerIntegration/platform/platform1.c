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
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_DEFAULT)

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor0;	// processor instance
    icmProcessorP  processor1;  // processor instance
    icmMemoryP     shared;      // shared memory instance
} handles;

//
// Create platform
//
void createPlatform() {

    // initialize CpuManager - require Imperas intercepts because the
    // application uses impProcessorId() to get processor id
    icmInitPlatform(ICM_VERSION, ICM_ENABLE_IMPERAS_INTERCEPTS, 0, 0, "platform");

    // select library components
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // create processor cpu0
    handles.processor0 = icmNewProcessor(
        "cpu0",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        MODEL_ATTRS,        // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create processor cpu0
    handles.processor1 = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
        1,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        MODEL_ATTRS,        // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor busses
    icmBusP bus1 = icmNewBus("bus1", 32);
    icmBusP bus2 = icmNewBus("bus2", 32);

    // connect the processor busses
    icmConnectProcessorBusses(handles.processor0, bus1, bus1);
    icmConnectProcessorBusses(handles.processor1, bus2, bus2);

    // create memories
    icmMemoryP local1 = icmNewMemory("local1", ICM_PRIV_RWX, 0x0fffffff);
    icmMemoryP local2 = icmNewMemory("local2", ICM_PRIV_RWX, 0x0fffffff);
    handles.shared = icmNewMemory("shared", ICM_PRIV_RWX, 0xefffffff);

    // connect memories
    icmConnectMemoryToBus(bus1, "mp1", handles.shared, 0x00000000);
    icmConnectMemoryToBus(bus2, "mp2", handles.shared, 0x00000000);
    icmConnectMemoryToBus(bus1, "mp1",         local1, 0xf0000000);
    icmConnectMemoryToBus(bus2, "mp1",         local2, 0xf0000000);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static void applyBreakpoints(icmProcessorP processor);
static void clearBreakpoints(icmProcessorP processor);
static Uns32 getWatchpointId(icmWatchPointP watchpoint);
static void applyWatchpoints(icmMemoryP memory);
static void applyRegWatchpoints(icmProcessorP processor);
static void handleWatchpoints(void);
static void queryRegisters(icmProcessorP processor);
static Bool cmdParser(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
	// Check arguments and ensure application to load specified
	if(!cmdParser(argc, argv)) {
		icmMessage("E", "platform", "Command Line parser error");
		return 1;
	}

	// the constructor
	createPlatform();

    icmSimulationStarting();

    // apply watchpoints in shared memory
    applyWatchpoints(handles.shared);

    // set register watchpoints for processor0 only
    applyRegWatchpoints(handles.processor0);

    // this is set to step for one instruction
    Bool          stepOver      = False;
    Bool          finished      = False;
    icmProcessorP stopProcessor = NULL;

    // query registers and register groups in processor0
    queryRegisters(handles.processor0);

    while(!finished) {

        // simulate the platform using the default scheduler
        if(stepOver) {
            icmSetICountBreakpoint(stopProcessor, 1);
            stopProcessor = icmSimulatePlatform();
            stepOver = False;
        } else {
            applyBreakpoints(handles.processor0);
            applyBreakpoints(handles.processor1);
            stopProcessor = icmSimulatePlatform();
            clearBreakpoints(handles.processor0);
            clearBreakpoints(handles.processor1);
        }

        switch(icmGetStopReason(stopProcessor)) {

            case ICM_SR_EXIT:
                finished = True;
                break;

            case ICM_SR_FINISH:
                finished = True;
                break;

            case ICM_SR_BP_ICOUNT:
                icmPrintf(
                    "Processor %s icount %u stopped at icount\n",
                     icmGetProcessorName(stopProcessor, "/"),
                    (Uns32)icmGetProcessorICount(stopProcessor)
                );
                break;

            case ICM_SR_BP_ADDRESS:
                icmPrintf(
                    "Processor %s icount %u stopped at address 0x%08x\n",
                    icmGetProcessorName(stopProcessor, "/"),
                    (Uns32)icmGetProcessorICount(stopProcessor),
                    (Uns32)icmGetPC(stopProcessor)
                );
                stepOver = True;
                break;

            case ICM_SR_WATCHPOINT:
                icmPrintf(
                    "Processor %s icount %u stopped at watchpoint\n",
                     icmGetProcessorName(stopProcessor, "/"),
                    (Uns32)icmGetProcessorICount(stopProcessor)
                );
                handleWatchpoints();
                break;

            default:
                icmPrintf(
                    "Processor %s icount %u stopped for reason %u\n",
                    icmGetProcessorName(stopProcessor, "/"),
                    (Uns32)icmGetProcessorICount(stopProcessor),
                    icmGetStopReason(stopProcessor)
                );
                break;
        }
    }

    icmTerminate();

    return 0;
}


//
// Type defining a watchpoint
//
typedef struct watchpointS {
    Uns32 address;
    Uns32 size;
} watchpoint;

//
// List of breakpoint addresses
//
const static Uns32 breakpoints[] = {
    0x0fdc,         // munge
    0x1330,         // main
    0x108c,         // writer
    0x1204,         // reader
    0               // terminator
};

const static watchpoint watchpoints[] = {
    {0xe404, 4},    // fibres
    {0}
};

//
// Static data for register watchpoint invocation count and watchpoint id
//
static Uns32 regWatchPointCount;
static UnsPS id;

//
// Apply all breakpoints for the passed processor
//
static void applyBreakpoints(icmProcessorP processor) {

    Uns32 i;

    for(i=0; breakpoints[i]; i++) {
        icmSetAddressBreakpoint(processor, breakpoints[i]);
    }
}

//
// Clear all breakpoints for the passed processor
//
static void clearBreakpoints(icmProcessorP processor) {

    Uns32 i;

    for(i=0; breakpoints[i]; i++) {
        icmClearAddressBreakpoint(processor, breakpoints[i]);
    }
}

//
// Return watchpoint id
//
static Uns32 getWatchpointId(icmWatchPointP watchpoint) {
    return (UnsPS)icmGetWatchPointUserData(watchpoint);
}

//
// Apply memory watchpoints
//
static void applyWatchpoints(icmMemoryP memory) {

    Uns32 address;
    Uns32 i;

    for(i=0; (address=watchpoints[i].address); i++) {

        // create read watchpoint
        icmWatchPointP rwp = icmSetMemoryReadWatchPoint(
            memory, address, address+watchpoints[i].size-1, (void *)(id++), 0
        );

        // create write watchpoint
        icmWatchPointP wwp = icmSetMemoryWriteWatchPoint(
            memory, address, address+watchpoints[i].size-1, (void *)(id++), 0
        );

        icmPrintf("READ watchpoint is %u\n", getWatchpointId(rwp));
        icmPrintf("WRITE watchpoint is %u\n", getWatchpointId(wwp));
    }
}

//
// Set register watchpoints for registers r3, r9 and the stack pointer in the
// passed processor
//
static void applyRegWatchpoints(icmProcessorP processor) {

    icmWatchPointP rwp1 = icmSetRegisterWatchPoint(
        processor, icmGetRegByName(processor, "r3"), (void *)(id++), 0
    );

    icmWatchPointP rwp2 = icmSetRegisterWatchPoint(
        processor, icmGetRegByName(processor, "r9"), (void *)(id++), 0
    );

    icmWatchPointP rwp3 = icmSetRegisterWatchPoint(
        processor, icmGetRegByUsage(processor, ICM_REG_SP), (void *)(id++), 0
    );

    icmPrintf("REGISTER watchpoint 1 is %u\n", getWatchpointId(rwp1));
    icmPrintf("REGISTER watchpoint 2 is %u\n", getWatchpointId(rwp2));
    icmPrintf("REGISTER watchpoint 3 is %u\n", getWatchpointId(rwp3));
}

//
// Handle all active watchpoints
//
static void handleWatchpoints(void) {

    icmWatchPointP wp;

    while((wp=icmGetNextTriggeredWatchPoint())) {

        Uns32         id        = getWatchpointId(wp);
        icmProcessorP processor = icmGetWatchPointTriggeredBy(wp);

        switch(icmGetWatchPointType(wp)) {

            case ICMWP_REGISTER: {

                // a register watchpoint was triggered
                icmRegInfoP reg       = icmGetWatchPointRegister(wp);
                Uns32      *newValueP = (Uns32 *)icmGetWatchPointCurrentValue(wp);
                Uns32      *oldValueP = (Uns32 *)icmGetWatchPointPreviousValue(wp);

                // indicate old and new value of the affected register
                icmPrintf(
                    "  watchpoint %u (processor %s:%s) triggered 0x%08x->0x%08x\n",
                    id,
                    icmGetProcessorName(processor, "/"),
                    icmGetRegInfoName(reg),
                    *oldValueP,
                    *newValueP
                );

                // delete watchpoint after 100 triggerings
                if(regWatchPointCount++>100) {
                    icmDeleteWatchPoint(wp);
                } else {
                    icmResetWatchPoint(wp);
                }

                break;
            }

            case ICMWP_MEM_READ:
            case ICMWP_MEM_WRITE:
            case ICMWP_MEM_ACCESS:

                // a memory watchpoint was triggered
                icmPrintf(
                    "  watchpoint %u (range 0x%08x:0x%08x) triggered by processor %s\n",
                    id,
                    (Uns32)icmGetWatchPointLowAddress(wp),
                    (Uns32)icmGetWatchPointHighAddress(wp),
                    icmGetProcessorName(processor, "/")
                );

                icmResetWatchPoint(wp);

                break;

            default:
                icmPrintf(
                    "  unknown watchpoint type triggered by processor %s\n",
                    icmGetProcessorName(processor, "/")
                );
                break;
        }
    }
}

//
// Query registers and register groups in the passed processor
//
static void queryRegisters(icmProcessorP processor) {

    icmPrintf("%s REGISTERS\n", icmGetProcessorName(processor, "/"));

    icmRegGroupP group = NULL;

    while((group=icmGetNextRegGroup(processor, group))) {

        icmPrintf("  GROUP %s\n", icmGetRegGroupName(group));

        icmRegInfoP reg = NULL;

        while((reg=icmGetNextRegInGroup(processor, group, reg))) {
            icmPrintf("    REGISTER %s\n", icmGetRegInfoName(reg));
        }
    }
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file for both processors>\n");
	icmCLParserUsageMessage(parser, (const char *)message);
	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "platform", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
