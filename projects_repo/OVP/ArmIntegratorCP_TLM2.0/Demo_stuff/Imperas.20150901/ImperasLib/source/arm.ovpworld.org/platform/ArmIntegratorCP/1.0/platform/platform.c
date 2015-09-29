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

#include "platform.clp.igen.h"
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

#define PLATFORM    "ArmIntegratorCP"
#define UART        "uart1"
#define SMARTLOADER "smartLoader"
#define LCD         "lcd"
#define CPU         "arm1"

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("ArmIntegratorCP", ICM_AC_ALL);
    icmCLParserUsageMessage(parser, "Usage (Linux Kernel)\n"
    		                        "  ArmIntegratorCP --kernel <kernel image> --ramdisk <initial ramdisk>\n"
    		                        "Usage (BareMetal)\n"
    		                        "  ArmIntegratorCP --program <elf file> --semihost <semihost file> --nographics\n");
    cmdParserAddUserArgs(parser);

    icmCLParseArgs(parser, argc, argv);

    // Check to see what UART options are used
    //
    Bool setUartport = icmCLParseArgUsed (parser,"uartport");
    if (options.uartconsole && setUartport) {
    	icmMessage("E", PLATFORM"_CFG", "Can only specify one of --uartport and --uartconsole");
    } else if (setUartport) {
        char buf[32];
        snprintf(buf, sizeof(buf), "0x"FMT_6408x, options.uartport);
        icmOverride(PLATFORM"/"UART"/portnum", buf);			// Override the parameter to cause the UART to open port "portnum"

    } else if (options.uartconsole) {
    	icmOverride(PLATFORM"/"UART"/console", "1");			// Override the parameter to cause the UART to open a console
    }

    if(options.nographics) {
    	icmOverride(PLATFORM"/"LCD"/noGraphics", "1");
    }

    // Check to see if the program argument is loading a non Linux Kernel
    if(icmCLParseArgUsed (parser,"program")) {
		if(icmCLParseArgUsed (parser,"kernel")) {
			icmMessage("E", PLATFORM, "Arguments '--program' and '--kernel' cannot be used together");
		} else {
			icmMessage("I", PLATFORM, "Loading baremetal application, disabling '%s'", SMARTLOADER);
	        icmOverride(PLATFORM"/"SMARTLOADER"/disable", "1");
		}

	} else {
    	if(options.kernel) {
    		icmOverride(PLATFORM"/"SMARTLOADER"/kernel", options.kernel);
    	}
    	if(options.ramdisk) {
    		icmOverride(PLATFORM"/"SMARTLOADER"/initrd", options.ramdisk);
    	}

    }

    platformConstructor();

    if(icmCLParseArgUsed (parser,"program") && (options.semihost)) {
		icmAddInterceptObject (handles.arm1_c, PLATFORM"/"CPU"/semihost",options.semihost, NULL, NULL);
	}

    icmSimulationStarting();
    icmSimulatePlatform();

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
