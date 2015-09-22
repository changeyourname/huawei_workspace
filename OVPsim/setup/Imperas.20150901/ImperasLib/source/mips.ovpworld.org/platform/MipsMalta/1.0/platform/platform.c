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

#ifdef PREFIX
#define PREFIX PREFIX "_PLATFORM_INIT"
#else
#define PREFIX        "PLATFORM_INIT"
#endif

static void overrideError(const char *target, const char *value) {
    icmMessage(
        "E", PREFIX,
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

static void overrideBool(const char *target, Bool value) {

    const char *buf = value ? "1" : "0";

    if (!icmOverride(target, buf)) {
        overrideError(target, buf);
    }
}

static void overrideString(const char *target, const char *value) {

    if (!icmOverride(target, value)) {
        overrideError(target, value);
    }
}


#define PLATFORM    "MipsMalta/"
#define SMARTLOADER PLATFORM "Core_Board_SDRAM_promInit/"
#define NIC         PLATFORM "PCI_NET/"
#define VGA         PLATFORM "vga/"
#define FPGA        PLATFORM "maltaFpga/"
#define IDE         PLATFORM "PIIX4-IDE/"

#include "platform.clp.igen.h"
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("MipsMalta", ICM_AC_ALL);
    icmCLParserUsageMessage(parser, "Basic Usage. Linux MipsMalta executable --kernel <kernel image> --console <Linux boot console> --ramdisk <initial ramdisk> --disk <disk file> --root <root partition to boot from disk");
    cmdParserAddUserArgs(parser);

    icmCLParseArgs(parser, argc, argv);

	if (options.kernel) {
		overrideString(SMARTLOADER "kernel", options.kernel);
	}
	if (options.ramdisk) {
        overrideString(SMARTLOADER "initrd", options.ramdisk);
	}
	if (options.root) {
		overrideString(SMARTLOADER "root", options.root);	// Set the root boot
	}
	if (options.disk) {
		overrideString(IDE "Drive0Name", options.disk);		// Set the file used for the drive
	}
	if (options.finishonhalt) {
		overrideBool(FPGA "stoponsoftreset",  1);
	}
	if (options.redir) {
        overrideString(NIC "redir", "tcp:15901:10.0.2.15:5901,tcp:11001:10.0.2.15:11001");
	}
    if(options.tftproot) {
    	overrideString(NIC "tftpPrefix", options.tftproot);
    }
    if(options.nographics) {
    	overrideBool(VGA "noGraphics", 1);
    }
    if (options.bootimage) {
        overrideString(SMARTLOADER "bootimage", options.bootimage);
    }
    if (options.pagebits) {
        overrideUns64x(SMARTLOADER "pagebits", options.pagebits);
    }
    if (options.console) {
    	char buf[64];
    	snprintf(buf, sizeof(buf), "console=%s", options.console);
        overrideString(SMARTLOADER "command",  buf);
    }

    platformConstructor();

	if (options.kernel) {
		// load the Linux kernel image into memory
		icmLoadProcessorMemory(handles.mipsle1_c, options.kernel, ICM_LOAD_DEFAULT, False, False);
	}

	icmSimulationStarting();
    icmSimulatePlatform();

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
