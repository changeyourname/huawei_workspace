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

#define PLATFORM             "XilinxML505"
#define UART        PLATFORM "/RS232_Uart_1/"

#include "platform.clp.igen.h"

static void overrideError(const char *target, const char *value) {
    icmMessage(
        "E", PLATFORM,
        "Unable to override attribute '%s' with value '%s'", target, value
    );
}

static void overrideBool(const char *target, Bool value) {

    const char *buf = value ? "1" : "0";

    if (!icmOverride(target, buf)) {
        overrideError(target, buf);
    }
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
    icmCLPP parser = icmCLParser("XilinxML505", ICM_AC_ALL);
    icmCLParserUsageMessage(parser, "Basic Usage. <Linux Xilinx ML505 executable> --kernel <kernel image> --uartconsole");
    cmdParserAddUserArgs(parser);

    // insert modifications to the CLP here

    icmCLParseArgs(parser, argc, argv);

    // insert overrides here

    platformConstructor();

    if(options.kernel) {
        if(!icmLoadProcessorMemory(handles.microblaze_0_c, options.kernel, ICM_LOAD_DEFAULT, True, True)) {
            icmMessage("F", PLATFORM, "Failed to load %s", options.kernel);
            icmExitSimulation(1);
            return 1;
        }
    } else {
        icmMessage("F", PLATFORM, "Must specify argument --kernel");
    }

    Bool setUartport = icmCLParseArgUsed (parser,"uartport");
    if (setUartport) {
        overrideBool(UART "console",  1);
    } else if (options.uartport) {
    	overrideUns64x(UART "portnum",  options.uartport);
        icmOverride(UART "diagnosticlevel", "1");
    }


    icmSimulationStarting();
    icmSimulatePlatform();

    // Add post simulation analysis or clean up code here

    icmTerminate();
    icmExitSimulation(0);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
