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


// This file declares functions to be implemented by the user.
// Be careful to avoid overwriting any edits should igen be re-run.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"


// Change the name here if required.

#define MODULE_NAME "ArmuKernelDualOP"

#include "platform.options.igen.h"
#include "platform.constructor.igen.h"
#include "platform.clp.igen.h"

typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;

////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

static OPT_PRE_SIMULATE_FN(modulePreSimulate) {
// insert modulePreSimulate code here
}

static OPT_SIMULATE_FN(moduleSimulate) {
// insert moduleSimulate code here
}

static OPT_POST_SIMULATE_FN(modulePostSimulate) {
// insert modulePostSimulate code here
}

static OPT_DESTRUCT_FN(moduleDestruct) {
// insert moduleDestruct code here
}

////////////////////////////////////////////////////////////////////////////////
//                                    ATTRS
////////////////////////////////////////////////////////////////////////////////

#include "platform.attr.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opcInit(OP_VERSION);
    optCmdParserP parser = oppCmdParserNew(MODULE_NAME, OPT_AC_ALL);
    cmdParser(parser);

    char message[1024];
    sprintf(message, "Basic Usage\n  %s\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbgui : start and connect remote debugger in console or iGui mode\n"
			         "UART Console Options\n"
    		         "    Allows the user to open a port on a uart so that manually can connect a socket program, such as a telnet terminal to the uart"
    		         "    Default operation is to automatically open a console and connect to the UART"
    		         "    --uart0port <port number>  : set port number to open for uart1 sub-system 0\n"
                     "    --uart1port <port number>  : set port number to open for uart1 sub-system 1\n", argv[0]);
    oppCmdUsageMessage(parser, (const char *)message);

    oppCmdParseArgs(parser, argc, argv);

    if (oppCmdArgUsed (parser,"uart0port")) {
        char buf[32];
        snprintf(buf, sizeof(buf), "0x"FMT_6408x, options.uart0port);
        opcParamOverrideString(MODULE_NAME "/sys0/uart1/portnum", buf);					// Override the parameter to cause the UART to open port "portnum"
        opcParamOverrideString(MODULE_NAME "/sys0/uart1/diagnosticlevel", "1");
    } else {
        opcParamOverrideString(MODULE_NAME "/sys0/uart1/console", "1");					// Override the parameter to cause the UART to open a console
    }
    opcParamOverrideString(MODULE_NAME "/sys0/uart1/outfile", "uart0_1.log");			// Override the parameter to the UART log file

    if (oppCmdArgUsed (parser,"uart1port")) {
        char buf[32];
        snprintf(buf, sizeof(buf), "0x"FMT_6408x, options.uart1port);
        opcParamOverrideString(MODULE_NAME "/sys1/uart1/portnum", buf);					// Override the parameter to cause the UART to open port "portnum"
        opcParamOverrideString(MODULE_NAME "/sys1/uart1/diagnosticlevel", "1");
    } else {
        opcParamOverrideString(MODULE_NAME "/sys1/uart1/console", "1");					// Override the parameter to cause the UART to open a console
    }
    opcParamOverrideString(MODULE_NAME "/sys1/uart1/outfile", "uart1_1.log");			// Override the parameter to the UART log file

    optModuleP top = opcRootModuleNew(&modelAttrs, MODULE_NAME, 0);
    oprModuleSimulate(top);
    opcTerminate();
    return 0;
}

