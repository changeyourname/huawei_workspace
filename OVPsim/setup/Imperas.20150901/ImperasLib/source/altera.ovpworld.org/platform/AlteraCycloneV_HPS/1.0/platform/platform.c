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

#include "platform.options.igen.h"
#include "platform.handles.igen.h"
#include "platform.constructor.igen.h"

#define PREFIX "CycloneV"

// Platform defaults to 1GB memory
#define MEM_SIZE  0x40000000

// Default Linux Command line
#define CMD_LINE "console=ttyS0"

//
// Return the entry address in the Boot file, if one is specified.
// Cache the result so we don't read the file over and over
//
static Addr getBootElfEntry() {

    static Addr bootElfEntry = -1ULL;

    if (bootElfEntry != -1ULL) {

        // Already set - no action

    } else if (options.BOOT) {

        if (!icmReadObjectFileHeader(options.BOOT, NULL, NULL, &bootElfEntry)) {
            icmMessage("F", PREFIX"_URB", "Unable to load Boot code file '%s'", options.BOOT);
        }

    }

    return bootElfEntry;

}

//
// Set non-zero default configuration values - may be overridden from command line
//
static void setDefaults() {

    options.IMAGE0ADDR = -1ULL;   // Allows detecting when not set
    options.IMAGE1ADDR = -1ULL;
    options.ZIMAGEADDR = -1ULL;
    options.INITRDADDR = -1ULL;
    options.BOARDID    = -1;

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

static void overrideString(const char *target, const char *value) {

    if (!icmOverride(target, value)) {
        overrideError(target, value);
    }
}
#define SMARTLOADER "AlteraCycloneV_HPS/smartLoader/"
#define UART0       "AlteraCycloneV_HPS/uart0/"
#define UART1       "AlteraCycloneV_HPS/uart1/"

//
// Set overrides for attributes affected by command line options
//
static void setOverrides() {

    if (options.ZIMAGE) {

        // Linux is being used - override any Linux command line options
        Addr memsize = options.LINUXMEM ? options.LINUXMEM : MEM_SIZE;

        overrideString(SMARTLOADER"kernel", options.ZIMAGE);

        if (options.LINUXCMD || options.LINUXMEM) {

            if(!options.LINUXCMD || (strstr(options.LINUXCMD, "mem=")==NULL)) {
                // Add configured memory size to command string
                char commandstr[1024];
                snprintf (
                    commandstr, sizeof(commandstr),
                    "mem="FMT_Au"M %s",
                    memsize>>20,
                    options.LINUXCMD ? options.LINUXCMD : CMD_LINE
                );
                overrideString(SMARTLOADER"command", commandstr);
            } else {
                overrideString(SMARTLOADER"command", options.LINUXCMD);
            }

        }

        if (options.BOARDID != -1) {
            overrideUns32x(SMARTLOADER"boardid", options.BOARDID);
        }

        if (options.LINUXMEM) {
            overrideUns64x(SMARTLOADER"memsize", memsize);
        }

        if (options.ZIMAGEADDR != -1ULL) {
            overrideUns64x(SMARTLOADER"kerneladdr", options.ZIMAGEADDR);
        }

        if (options.BOOT) {
            overrideUns64x(SMARTLOADER"bootaddr", getBootElfEntry() );
        }

        if (options.INITRD) {
            overrideString(SMARTLOADER"initrd",     options.INITRD);
        }
        if (options.INITRDADDR != -1ULL) {
            overrideUns64x(SMARTLOADER"initrdaddr", options.INITRDADDR);
        }

    } else {

        // Disable smart loader if LINUX is not used
        overrideString(SMARTLOADER"disable", "1");

    }

    if (options.UART0PORT) {
        Uns32 portNum;
        if (strcmp(options.UART0PORT, "auto") == 0) {
            overrideString(UART0"console", "1");
        } else if (sscanf(options.UART0PORT, "%i", &portNum) == 1) {
            overrideString(UART0"portnum", options.UART0PORT);
        } else {
            icmMessage(
                "W", PREFIX"_IO",
                "Invalid argument for uart0port: '%s'. Must be 'auto' or a number.",
                options.UART0PORT
            );
        }
    }

    if (options.UART1PORT) {
        Uns32 portNum;
        if (strcmp(options.UART1PORT, "auto") == 0) {
            overrideString(UART1"console", "1");
        } else if (sscanf(options.UART1PORT, "%i", &portNum) == 1) {
            overrideString(UART1"portnum", options.UART1PORT);
        } else {
            icmMessage(
                "W", PREFIX"_IO",
                "Invalid argument for uart1port: '%s'. Must be 'auto' or a number.",
                options.UART1PORT
            );
        }
    }

}

//
// Load an ELF file on the processor
//
static icmImagefileP loadElf(icmProcessorP processor, const char *appName) {

    icmImagefileP image;

    image = icmLoadProcessorMemory(processor, appName, ICM_LOAD_VERBOSE, True, False);

    if (!image) {
        icmMessage(
            "F", PREFIX"_ULF",
            "unable to load file %s on %s",
            appName, icmGetProcessorName(processor, "/")
        );
    }

    return image;

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
            filename, size, icmGetProcessorName(processor, "/")
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
        symFile, icmGetProcessorName(processor, "/")
    );
}

//
// Do application setup for each leaf processor
//
static ICM_SMP_ITERATOR_FN(setupApplication) {

    if (icmSMPIsLeaf(processor)) {

        Uns32 smpIndex = icmGetSMPIndex(processor);

        if (smpIndex > 1) {

            icmMessage(
                "E", PREFIX"_TMP",
                "%s: Only 2 processor cores supported on this platform",
                icmGetProcessorName(processor, "/")
            );

        } else {

            const char *appName = smpIndex==0 ? options.APP0       : options.APP1;
            const char *imgName = smpIndex==0 ? options.IMAGE0     : options.IMAGE1;
            const char *imgSyms = smpIndex==0 ? options.IMAGE0SYM  : options.IMAGE1SYM;
            Uns32       imgAddr = smpIndex==0 ? options.IMAGE0ADDR : options.IMAGE1ADDR;
            Addr        start   = 0;

            // Is this processor running Linux?
            // (Linux runs on both processors if no application for cpu1 specified)
            if (options.ZIMAGE && (smpIndex==0 || (!appName && !imgName))) {

                // Running Linux on this processor
                appName = "Linux";

                // Linux image file is loaded by smartLoader peripheral
                // so just load a symbol file here, if one was specified,
                if (options.LINUXSYM) loadSymbols(processor, options.LINUXSYM);

            } else if (appName) {

                // Load application file on the processor
                icmImagefileP image = loadElf(processor, appName);

                // Get start address from ELF file if not using boot code
                start = options.BOOT ? getBootElfEntry() : icmGetImagefileEntry(image);

            }

            // Load image file if indicated
            if (imgName) {

                Uns32 imageSize = loadImage(processor, imgName, imgAddr);

                if (imageSize) {
                    if (imgSyms) {
                        loadSymbols(processor, imgSyms);
                    }
                    if (!appName) {
                        appName = imgName;
                        start = options.BOOT ? getBootElfEntry() : imgAddr;
                    }
                }
            }

            // Set processor's starting address
            icmSetPC(processor, start);

            icmMessage(
                "I", PREFIX"_LAF",
                "%s loaded on %s (start address set to 0x"FMT_A08x")",
                appName ? appName : "nothing", icmGetProcessorName(processor, "/"), start
            );

        }
    }
}



#include "platform.clp.igen.h"
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    // Initialize options to default values
    setDefaults();

    icmCLPP parser = icmCLParser("AlteraCycloneV_HPS", ICM_AC_ALL);
    cmdParserAddUserArgs(parser);

    // insert modifications to the CLP here

    icmCLParseArgs(parser, argc, argv);

    Bool ok = True;

    // Check args for errors
    if (!options.ZIMAGE && !options.APP0 && !options.BOOT && !options.IMAGE0) {
        icmMessage("E", PREFIX, "None of ZIMAGE, APP0, IMAGE0 or BOOT specified. Must specify at least one\n");
        ok = False;
    }

    if (!options.ZIMAGE && (options.INITRD || options.LINUXSYM || options.LINUXCMD)) {
        icmMessage("E", PREFIX, "Linux-only argument specified with out specifying ZIMAGE\n");
        ok = False;
    }

    if (options.ZIMAGE && options.APP0) {
        icmMessage("E", PREFIX, "Both IMAGE and APP0 specified. Must be only one or the other\n");
        ok = False;
    }

    if (options.ZIMAGE && options.APP1 && (options.LINUXMEM==0)) {
        icmMessage("E", PREFIX, "Running Linux with AMP application without LINUXMEM specified to limit Linux memory usage\n");
        ok = False;
    }

    if (!options.IMAGE0 && options.IMAGE0SYM) {
        icmMessage("E", PREFIX, "IMAGE0SYM specified without IMAGE0\n");
        ok = False;
    }

    if (!options.IMAGE1 && options.IMAGE1SYM) {
        icmMessage("E", PREFIX, "IMAGE1SYM specified without IMAGE1\n");
        ok = False;
    }

    if (options.IMAGE0 && options.IMAGE0ADDR==-1ULL) {
        icmMessage("E", PREFIX, "IMAGE0SYM specified without IMAGE0ADDR\n");
        ok = False;
    }

    if (options.IMAGE1 && options.IMAGE1ADDR==-1ULL) {
        icmMessage("E", PREFIX, "IMAGE1SYM specified without IMAGE1ADDR\n");
        ok = False;
    }

    if (ok) {
        setOverrides();
    }

    platformConstructor();

    if (options.BOOT) {
        // Load the boot file
        icmLoadBus(handles.smbus_b, options.BOOT, ICM_LOAD_VERBOSE, True);
    }

    // Setup application on each leaf processor
    icmIterAllDescendants(handles.cpu_c, setupApplication, NULL);

    icmSimulationStarting();
    icmSimulatePlatform();

    // Add post simulation analysis or clean up code here

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
