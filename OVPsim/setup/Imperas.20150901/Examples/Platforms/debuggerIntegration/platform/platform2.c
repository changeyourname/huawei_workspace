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
} handles;

// enable tracing etc. on processor model
#define MODEL_ATTRS (ICM_ATTR_TRACE)

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

    // create processor cpu0
    handles.processor = icmNewProcessor(
        "cpu0",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        MODEL_ATTRS,          // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static void applyBreakpoints(icmProcessorP processor);
static void clearBreakpoints(icmProcessorP processor);
static Uns32 getWatchpointId(icmWatchPointP watchpoint);
static void applyModeWatchpoints(icmProcessorP processor);
static void applyExceptionWatchpoints(icmProcessorP processor);
static void handleWatchpoints(void);
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

    // Do not print information about missing register callbacks
    icmIgnoreMessage("PC_NRI");

    // apply mode change watchpoints
    applyModeWatchpoints(handles.processor);

    // apply exception watchpoints
    applyExceptionWatchpoints(handles.processor);

    // this is set to step for one instruction
    Bool          stepOver      = False;
    Bool          finished      = False;
    icmProcessorP stopProcessor = NULL;

    while(!finished) {

        // simulate the platform using the default scheduler
        if(stepOver) {
            icmSetICountBreakpoint(stopProcessor, 1);
            stopProcessor = icmSimulatePlatform();
            stepOver = False;
        } else {
            applyBreakpoints(handles.processor);
            stopProcessor = icmSimulatePlatform();
            clearBreakpoints(handles.processor);
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

    // dump the final register contents
    icmDumpRegisters(handles.processor);

    // report the total number of instructions executed
    icmPrintf(
        "processor has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(handles.processor)
    );

    icmTerminate();

    return 0;
}
static UnsPS id;

//
// List of breakpoint addresses
//
const static Uns32 breakpoints[] = {
    0               // terminator
};

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
// Set mode watchpoints the passed processor
//
static void applyModeWatchpoints(icmProcessorP processor) {
    icmWatchPointP mwp = icmSetModeWatchPoint(processor, (void *)(id++), 0);
    icmPrintf("MODE watchpoint 1 is %u\n", getWatchpointId(mwp));
}

//
// Set exception watchpoints the passed processor
//
static void applyExceptionWatchpoints(icmProcessorP processor) {
    icmWatchPointP ewp = icmSetExceptionWatchPoint(processor, (void *)(id++), 0);
    icmPrintf("EXCEPTION watchpoint 1 is %u\n", getWatchpointId(ewp));
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

            case ICMWP_MODE: {

                // a mode switch watchpoint was triggered
                icmModeInfoP *oldValueP = icmGetWatchPointPreviousValue(wp);
                icmModeInfoP *newValueP = icmGetWatchPointCurrentValue(wp);
                icmModeInfoP  oldValue  = *oldValueP;
                icmModeInfoP  newValue  = *newValueP;

                icmPrintf(
                    "  watchpoint %u (processor %s:mode) triggered %s->%s\n",
                    id,
                    icmGetProcessorName(processor, "/"),
                    icmGetModeInfoName(oldValue),
                    icmGetModeInfoName(newValue)
                );

                icmResetWatchPoint(wp);

                break;
            }

            case ICMWP_EXCEPTION: {

                icmExceptionInfoP exception = icmGetException(processor);

                // an exception watchpoint was triggered
                icmPrintf(
                    "  watchpoint %u (processor %s:exception) triggered ->%s\n",
                    id,
                    icmGetProcessorName(processor, "/"),
                    icmGetExceptionInfoName(exception)
                );

                icmResetWatchPoint(wp);

                break;
            }

            default:
                icmPrintf(
                    "  unknown watchpoint type triggered by processor %s\n",
                    icmGetProcessorName(processor, "/")
                );
                break;
        }
    }
}

static Bool cmdParser(int argc, const char *argv[]) {
	icmCLPP parser = icmCLParser("platform", ICM_AC_ALL);
	char message[1024];
	sprintf(message, "Basic Usage\n  platform.IMPERAS_ARCH.exe --program <elf file>\n");
	icmCLParserUsageMessage(parser, (const char *)message);
	Bool ok = icmCLParseArgs(parser, argc, argv);

	if (!icmCLParseArgUsed (parser,"program")) {
		icmMessage("E", "platform", "Argument '--program' must be used to specify application elf file to load");
		ok = False;
	}
	return ok;
}
