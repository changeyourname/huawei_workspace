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


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// Be careful to avoid overwriting any edits if igen is run a second time.
// Only use -overwrite if you wish to overwrite this file.

#include "platform.options.igen.h"
#include "platform.handles.igen.h"
#include "platform.constructor.igen.h"

#define PLATFORM    "HeteroArmNucleusMIPSLinux"
#define ARMUART1    "armSub1uart1"
#define ARMUART2    "armSub1uart2"
#define MIPSVGA     "mipsMainvga"


#include "platform.clp.igen.h"
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);
    cmdParserAddUserArgs(parser);

    // Insert modifications to the CLP here

    icmCLParseArgs(parser, argc, argv);

    //
    // Check to see what UART options are used
    //
    Bool setUartport = icmCLParseArgUsed (parser,"uartport");
    if (options.uartconsole && setUartport) {
    	icmMessage("E", PLATFORM"_CFG", "Can only specify one of --uartport and --uartconsole");
    } else if (setUartport) {
        char buf[32];
        snprintf(buf, sizeof(buf), "0x"FMT_6408x, options.uartport);
        icmOverride(PLATFORM"/"ARMUART1"/portnum", buf);			// Override the parameter to cause the UART0 to open port "portnum"

    } else if (options.uartconsole) {
    	icmOverride(PLATFORM"/"ARMUART1"/console", "1");			// Override the parameter to cause the UART1 to open a console
    }
    if (options.uartconsole || setUartport) {
        icmOverride(PLATFORM"/"ARMUART1"/finishOnDisconnect", "1");
        icmOverride(PLATFORM"/"ARMUART1"/diagnosticlevel", "1");
    }

    if (options.nographics) {
        icmOverride(PLATFORM"/"MIPSVGA"/disable", "1");
    }

    platformConstructor();

    // Add post construction function here
    icmSimulationStarting();
    icmSimulatePlatform();

    // Add post simulation analysis or clean up code here
    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
