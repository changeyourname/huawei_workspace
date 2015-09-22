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

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "icm/icmCpuManager.h"

// Be careful to avoid overwriting any edits if igen is run a second time.
// Only use -overwrite if you wish to overwrite this file.

#define PREFIX "QuadArmVersatileExpress"

#include "platform.options.igen.h"
#include "platform.handles.igen.h"
#include "platform.constructor.igen.h"

// Physical address of base of RAM - use as start address
#define PHYS_BASE 0x80000000

//
// Return the entry address in the Boot file, if one is specified.
// Cache the result so we don't read the file over and over
//
static Addr getBootElfEntry() {

    static Addr bootElfEntry = -1ULL;

    if (bootElfEntry != -1ULL) {

        // Already set - no action

    } else if (options.boot) {

        if (!icmReadObjectFileHeader(options.boot, NULL, NULL, &bootElfEntry)) {
            icmMessage("F", PREFIX"_URB", "Unable to load Boot code file '%s'", options.boot);
        }

    }

    return bootElfEntry;

}

//
// Set non-zero default configuration values - may be overridden from command line
//
static void setDefaults() {

    // Allows detecting when not set, since 0 is a valid value
    options.image0addr = -1ULL;
    options.image1addr = -1ULL;
    options.zimageaddr = -1ULL;
    options.initrdaddr = -1ULL;
    options.boardid    = -1;

}

static void overrideError(const char *target, const char *value) {
    icmMessage(
        "W", PREFIX"_OE",
        "Unable to override attribute '%s' with value '%s'", target, value
    );
}

static void overrideUns32x(const char *target, Uns32 value) {

    char buf[32];

    snprintf(buf, sizeof(buf), "0x%x", value);

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

#define SMARTLOADER_0 PREFIX"/smartLoader_0/"
#define UART0_0       PREFIX"/uart0_0/"
#define UART1_0       PREFIX"/uart1_0/"
#define CLCD_0        PREFIX"/clcd_0/"

#define SMARTLOADER_1 PREFIX"/smartLoader_1/"
#define UART0_1       PREFIX"/uart0_1/"
#define UART1_1       PREFIX"/uart1_1/"
#define CLCD_1        PREFIX"/clcd_1/"

#define SMARTLOADER_2 PREFIX"/smartLoader_2/"
#define UART0_2       PREFIX"/uart0_2/"
#define UART1_2       PREFIX"/uart1_2/"
#define CLCD_2        PREFIX"/clcd_2/"

#define SMARTLOADER_3 PREFIX"/smartLoader_3/"
#define UART0_3       PREFIX"/uart0_3/"
#define UART1_3       PREFIX"/uart1_3/"
#define CLCD_3        PREFIX"/clcd_3/"
//
// Set overrides for attributes affected by command line options
//
static void setOverrides() {

    if (options.zimage) {

        overrideString(SMARTLOADER_0"kernel", options.zimage);
        overrideString(SMARTLOADER_1"kernel", options.zimage);
        overrideString(SMARTLOADER_2"kernel", options.zimage);
        overrideString(SMARTLOADER_3"kernel", options.zimage);

        if (options.linuxcmd) {
            overrideString(SMARTLOADER_0"command", options.linuxcmd);
            overrideString(SMARTLOADER_1"command", options.linuxcmd);
            overrideString(SMARTLOADER_2"command", options.linuxcmd);
            overrideString(SMARTLOADER_3"command", options.linuxcmd);
        }

        if (options.boardid != -1) {
            overrideUns32x(SMARTLOADER_0"boardid", options.boardid);
            overrideUns32x(SMARTLOADER_1"boardid", options.boardid);
            overrideUns32x(SMARTLOADER_2"boardid", options.boardid);
            overrideUns32x(SMARTLOADER_3"boardid", options.boardid);
        }

        if (options.linuxmem) {
            overrideUns64x(SMARTLOADER_0"memsize", options.linuxmem);
            overrideUns64x(SMARTLOADER_1"memsize", options.linuxmem);
            overrideUns64x(SMARTLOADER_2"memsize", options.linuxmem);
            overrideUns64x(SMARTLOADER_3"memsize", options.linuxmem);
        }

        if (options.zimageaddr != -1ULL) {
            overrideUns64x(SMARTLOADER_0"kerneladdr", options.zimageaddr);
            overrideUns64x(SMARTLOADER_1"kerneladdr", options.zimageaddr);
            overrideUns64x(SMARTLOADER_2"kerneladdr", options.zimageaddr);
            overrideUns64x(SMARTLOADER_3"kerneladdr", options.zimageaddr);
        }

        if (options.boot) {
            overrideUns64x(SMARTLOADER_0"bootaddr", getBootElfEntry() );
            overrideUns64x(SMARTLOADER_1"bootaddr", getBootElfEntry() );
            overrideUns64x(SMARTLOADER_2"bootaddr", getBootElfEntry() );
            overrideUns64x(SMARTLOADER_3"bootaddr", getBootElfEntry() );
        }

        if (options.initrd) {
            overrideString(SMARTLOADER_0"initrd",     options.initrd);
            overrideString(SMARTLOADER_1"initrd",     options.initrd);
            overrideString(SMARTLOADER_2"initrd",     options.initrd);
            overrideString(SMARTLOADER_3"initrd",     options.initrd);
        }

        if (options.initrdaddr != -1ULL) {
            overrideUns64x(SMARTLOADER_0"initrdaddr", options.initrdaddr);
            overrideUns64x(SMARTLOADER_1"initrdaddr", options.initrdaddr);
            overrideUns64x(SMARTLOADER_2"initrdaddr", options.initrdaddr);
            overrideUns64x(SMARTLOADER_3"initrdaddr", options.initrdaddr);
        }

    } else {

        // Disable smart loader if LINUX is not used
        overrideString(SMARTLOADER_0"disable", "1");
        overrideString(SMARTLOADER_1"disable", "1");
        overrideString(SMARTLOADER_2"disable", "1");
        overrideString(SMARTLOADER_3"disable", "1");

    }

    if (options.uart0port) {
        Uns32 portNum;
        if (strcmp(options.uart0port, "auto") == 0) {
            overrideString(UART0_0"console", "1");
            overrideString(UART0_1"console", "1");
            overrideString(UART0_2"console", "1");
            overrideString(UART0_3"console", "1");
        } else if (sscanf(options.uart0port, "%i", &portNum) == 1) {
            overrideString(UART0_0"portnum", options.uart0port);
            overrideString(UART0_1"portnum", options.uart0port);
            overrideString(UART0_2"portnum", options.uart0port);
            overrideString(UART0_3"portnum", options.uart0port);
        } else {
            icmMessage(
                "W", PREFIX"_IO",
                "Invalid argument for uart0port: '%s'. Must be 'auto' or a number.",
                options.uart0port
            );
        }
    }

    if (options.uart1port) {
        Uns32 portNum;
        if (strcmp(options.uart1port, "auto") == 0) {
            overrideString(UART1_0"console", "1");
            overrideString(UART1_1"console", "1");
            overrideString(UART1_2"console", "1");
            overrideString(UART1_3"console", "1");
        } else if (sscanf(options.uart1port, "%i", &portNum) == 1) {
            overrideString(UART1_0"portnum", options.uart1port);
            overrideString(UART1_1"portnum", options.uart1port);
            overrideString(UART1_2"portnum", options.uart1port);
            overrideString(UART1_3"portnum", options.uart1port);
        } else {
            icmMessage(
                "W", PREFIX"_IO",
                "Invalid argument for uart1port: '%s'. Must be 'auto' or a number.",
                options.uart1port
            );
        }
    }

    if (options.nographics) {
        overrideBool(CLCD_0"noGraphics", options.nographics);
        overrideBool(CLCD_1"noGraphics", options.nographics);
        overrideBool(CLCD_2"noGraphics", options.nographics);
        overrideBool(CLCD_3"noGraphics", options.nographics);
    }

}


#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

//
// Load the binary image file at the indicated address
// Returns number of bytes loaded or 0 if an error
//
static Uns32 loadImage(icmProcessorP processor, const char *filename, Uns32 addr) {

	Int32 fd = open(filename, O_RDONLY | O_BINARY);

	if (fd < 0) {
		icmMessage("E", PREFIX, "Cannot open image file %s", filename);
		return 0;
	}

	// Get the size of the file
	Int32 size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	// Copy the file to simulated memory
	Uns32 bytes = size;
	Uns32 dest  = addr;
	char  buff[BYTES_PER_ACCESS];
	while (bytes) {

		Uns32 thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;

		thisAccess = read(fd, buff, thisAccess);

		if (!icmWriteProcessorMemory(processor, dest, buff, thisAccess)) {

			icmMessage(
				"E", PREFIX"_UWI",
				"Unable to write image file %s to simulated memory: failed at 0x%08x",
				filename, dest
			);

			close(fd);
			return 0;

		}

		dest  += thisAccess;
		bytes -= thisAccess;

	}

	close(fd);

	icmMessage(
			"I", PREFIX"_IFL",
			"Image file %s loaded (%u bytes) on %s",
			filename, size, icmGetProcessorName(processor, 0)
	);

	return size;
}

//
// Load a symbol file on a processor
//
static void loadSymbols(icmProcessorP processor, const char *symFile) {
icmLoadSymbols(processor, symFile, False);
icmMessage(
    "I", PREFIX"_SFL",
    "Symbols file %s loaded on %s",
    symFile, icmGetProcessorName(processor, 0)
);
}

//
// Do application setup for each leaf processor
//
static ICM_SMP_ITERATOR_FN(setupApplication) {

	if (icmSMPIsLeaf(processor)) {

		Uns32 smpIndex = icmGetSMPIndex(processor);

		const char *appName = NULL;
		const char *imgName = smpIndex==0 ? options.image0     : options.image1;
		const char *imgSyms = smpIndex==0 ? options.image0sym  : options.image1sym;
		Uns32       imgAddr = smpIndex==0 ? options.image0addr : options.image1addr;
		Addr        start   = 0;

		// Is this processor running Linux?
		// (Linux runs on both processors if no application for cpu1 specified)
		if (options.zimage && (smpIndex==0 || !imgName)) {

			// Running Linux on this processor
			appName = "Linux";

			// Linux image file is loaded by smartLoader peripheral
			// so just load a symbol file here, if one was specified,
			if (options.linuxsym) loadSymbols(processor, options.linuxsym);

			// Set start address to physical base, where smartLoader writes the boot code
			start = PHYS_BASE;

		}

		// Load image file if indicated
		if (imgName) {

			Uns32 imageSize = loadImage(processor, imgName, imgAddr);

			if (imageSize) {
				if (imgSyms) {
					loadSymbols(processor, imgSyms);
				}
			}
			if (!appName) appName = imgName;
			start = options.boot ? getBootElfEntry() : imgAddr;
		}

		// Set processor's starting address
		icmSetPC(processor, start);

		icmMessage(
			"I", PREFIX"_LAF",
			"%s loaded on %s (start address set to 0x"FMT_A08x")",
			appName ? appName : "nothing", icmGetProcessorName(processor, 0), start
		);

	}
}

#include "platform.clp.igen.h"
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    // Initialize options to default values
    setDefaults();

    icmCLPP parser = icmCLParser("QuadArmVersatileExpress", ICM_AC_ALL);
    cmdParserAddUserArgs(parser);

    icmCLParseArgs(parser, argc, argv);

    Bool ok = True;

    // Check args for errors
    if (!options.zimage && !options.boot && !options.image0) {
        icmMessage("W", PREFIX, "None of zimage, image0 or boot specified. Must specify executable some other way");
    }

    if (!options.zimage && (options.initrd || options.linuxsym || options.linuxcmd || options.linuxmem)) {
    	icmMessage("E", PREFIX, "Linux-only argument specified with out specifying zimage\n");
        ok = False;
    }

    if (!options.image0 && options.image0sym) {
    	icmMessage("E", PREFIX, "image0sym specified without image0");
        ok = False;
    }

    if (!options.image1 && options.image1sym) {
    	icmMessage("E", PREFIX, "image1sym specified without image1");
        ok = False;
    }

    if (options.image0 && options.image0addr==-1ULL) {
    	icmMessage("E", PREFIX, "image0sym specified without image0addr");
    }

    if (options.image1 && options.image1addr==-1ULL) {
    	icmMessage("E", PREFIX, "image1sym specified without image1addr");
    }

    if (ok) {
        setOverrides();
    }

    platformConstructor();

    if (options.boot) {
        // Load the boot file
    	icmLoadBus(handles.pBus_0_b, options.boot, ICM_LOAD_VERBOSE, True);
        icmLoadBus(handles.pBus_1_b, options.boot, ICM_LOAD_VERBOSE, True);
        icmLoadBus(handles.pBus_2_b, options.boot, ICM_LOAD_VERBOSE, True);
        icmLoadBus(handles.pBus_3_b, options.boot, ICM_LOAD_VERBOSE, True);
    }

    // Setup application on each leaf processor
    icmIterAllDescendants(handles.cpu_0_c, setupApplication, NULL);
    icmIterAllDescendants(handles.cpu_1_c, setupApplication, NULL);
    icmIterAllDescendants(handles.cpu_2_c, setupApplication, NULL);
    icmIterAllDescendants(handles.cpu_3_c, setupApplication, NULL);

    icmSimulationStarting();
    icmSimulatePlatform();

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
