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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                              Version 99999999
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// Be careful to avoid overwriting any edits if igen is run a second time.
// Only use -overwrite if you wish to overwrite this file.

#include "platform.options.igen.h"
#include "platform.handles.igen.h"
#include "platform.constructor.igen.h"

#define PLATFORM      "AtmelAT91SAM7"
#define USART0        PLATFORM "/USART0/"

#include "platform.clp.igen.h"

static void overrideError(const char *target, const char *value) {
    icmMessage(
        "E", PLATFORM,
        "Unable to override attribute '%s' with value '%s'", target, value
    );
}

static void overrideUns64x(const char *target, Uns64 value) {

    char buf[32];

    snprintf(buf, sizeof(buf), "0x"FMT_6408x, value);

    if (!icmOverride(target, buf)) {
        overrideError(target, buf);
    }
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("AtmelAT91SAM7", ICM_AC_ALL);
    icmCLParserUsageMessage(parser, "Basic Usage. <Atmel AT91SAM7 executable> --kernel <uCLinux kernel image>");
    cmdParserAddUserArgs(parser);

    icmCLParseArgs(parser, argc, argv);

    Bool setUartport = icmCLParseArgUsed (parser,"uartport");
    if (setUartport) {
    	overrideUns64x(USART0 "portnum",  options.uartport);
        icmOverride(USART0 "diagnosticlevel", "1");
    } else {
        icmOverride(USART0 "console", "1");
    }

    platformConstructor();

    if(!options.kernel) {
    	options.kernel="linux";
    }
	icmMessage("I", PLATFORM, "Loading Kernel file %s", options.kernel);
	if(!icmLoadProcessorMemory(handles.ARM7TDMICore_c, options.kernel, ICM_LOAD_DEFAULT, True, True)) {
		icmMessage("E", PLATFORM, "Failed to load %s", options.kernel);
		icmExitSimulation(1);
		return 1;
    }

    icmSimulationStarting();
    icmSimulatePlatform();

    // Add post simulation analysis or clean up code here

    icmTerminate();
    icmExitSimulation(0);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
