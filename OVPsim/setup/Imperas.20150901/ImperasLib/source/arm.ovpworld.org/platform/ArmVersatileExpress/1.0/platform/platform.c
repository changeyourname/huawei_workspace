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

#define PLATFORM    "ArmVersatileExpress"
#define UART0       "uart0"
#define UART1       "uart1"
#define SMARTLOADER "smartLoader"
#define MMC         "mmc1"
#define LCD         "lcd1"

ICM_SMP_ITERATOR_FN(setStartAddress);

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("ArmVersatileExpress", ICM_AC_ALL);
    icmCLParserUsageMessage(parser, "Basic Usage. Linux ArmVersatileExpress executable --kernel <kernel image> --ramdisk <initial ramdisk>");
    cmdParserAddUserArgs(parser);

    // insert modifications to the CLP here

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
        icmOverride(PLATFORM"/"UART0"/portnum", buf);			// Override the parameter to cause the UART0 to open port "portnum"
        snprintf(buf, sizeof(buf), "0x"FMT_6408x, options.uartport + 1 );
        icmOverride(PLATFORM"/"UART1"/portnum", buf);			// Override the parameter to cause the UART1 to open port "portnum+1"

    } else if (options.uartconsole) {
    	icmOverride(PLATFORM"/"UART0"/console", "1");			// Override the parameter to cause the UART0 to open a console
    	icmOverride(PLATFORM"/"UART1"/console", "1");			// Override the parameter to cause the UART1 to open a console
    }
    if (options.uartconsole || setUartport) {
        icmOverride(PLATFORM"/"UART0"/finishOnDisconnect", "1");
        icmOverride(PLATFORM"/"UART0"/diagnosticlevel", "1");
        icmOverride(PLATFORM"/"UART1"/finishOnDisconnect", "1");
        icmOverride(PLATFORM"/"UART1"/diagnosticlevel", "1");
    }

    if(options.nographics) {
    	icmOverride(PLATFORM"/"LCD"/noGraphics", "1");
    }

    //
    // Setup the Linux command line
    //
    char command[256] = "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0";
    if(icmCLParseArgUsed (parser,"command")) {
    	// Android boot requires "androidboot.console=ttyAMA0 vga=771", specified on command line
    	strcat(command, " ");
    	strcat(command, options.command);
    }
	icmOverride(PLATFORM"/"SMARTLOADER"/command", command);

	//
    // Setup the SmartLoader for the Linux Kernel and ramdisk
	//
	if(options.kernel) {
		icmOverride(PLATFORM"/"SMARTLOADER"/kernel", options.kernel);
	}
	if(options.ramdisk) {
		icmOverride(PLATFORM"/"SMARTLOADER"/initrd", options.ramdisk);
	}

    if(icmCLParseArgUsed (parser,"sdcard")) {
    	icmOverride(PLATFORM"/"MMC"/SD_DRIVE", options.sdcard);
    }

    platformConstructor();

    if(icmCLParseArgUsed (parser,"bootcode")) {
		icmImagefileP image = icmLoadBus(handles.smbus_b, options.bootcode, ICM_LOAD_VERBOSE, True);
		if (image) {
			char buf[32];
			snprintf(buf, sizeof(buf), "0x"FMT_6408x, icmGetImagefileEntry(image));
			icmOverride(PLATFORM"/"SMARTLOADER"/bootaddr", buf);
		} else {
			icmMessage("E", PLATFORM, "Failed to load '%s'", options.bootcode);
		}
	}

	icmIterAllChildren(handles.cpu_c, setStartAddress, 0);

    icmSimulationStarting();
    icmSimulatePlatform();

    // Add post simulation analysis or clean up code here

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

ICM_SMP_ITERATOR_FN(setStartAddress) {

    Uns32 start = 0x60000000;
    icmMessage("I", PLATFORM"_STARTUP", "Set start address for %s to 0x%08x", icmGetProcessorName(processor, ""), start);
    icmSetPC(processor, start);
}
