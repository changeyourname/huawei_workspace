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
//                          Tue Nov 25 15:20:47 2014
//
////////////////////////////////////////////////////////////////////////////////

// This file declares sc_main and functions to be implemented by the user.
// This file will not be overwritten by subsequent igen runs
// unless --overwrite is specified.
// To conditionally set model attributes, use
// icmOverride("instance-path", "<value>");

#include <fcntl.h>

#include "tlm.h"
#include "ovpworld.org/modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.hpp"
extern "C" {
#include "platform.sc_options.igen.h"
}
#include "platform.sc_constructor.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////
#define PREFIX "CycloneV"

// Platform defaults to 128MB memory
#define MEM_SIZE  0x08000000

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
#define SMARTLOADER "AlteraCycloneV_HPS_TLM2.smartLoader/"
#define UART0       "AlteraCycloneV_HPS_TLM2.uart0/"
#define UART1       "AlteraCycloneV_HPS_TLM2.uart1/"

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
// Check for valid command line arguments specified
//
static Bool postCmdParser(void) {

    Bool ok = True;

    // Check args for errors
    if (!options.ZIMAGE && !options.APP0 && !options.BOOT && !options.IMAGE0) {
        icmPrintf("Error: None of ZIMAGE, APP0, IMAGE0 or BOOT specified. Must specify at least one\n");
        ok = False;
    }

    if (!options.ZIMAGE && (options.INITRD || options.LINUXSYM || options.LINUXCMD)) {
        icmPrintf("Error: Linux-only argument specified with out specifying ZIMAGE\n");
        ok = False;
    }

    if (options.ZIMAGE && options.APP0) {
        icmPrintf("Error: Both IMAGE and APP0 specified. Must be only one or the other\n");
        ok = False;
    }

    if (options.ZIMAGE && options.APP1 && (options.LINUXMEM==0)) {
        icmPrintf("Error: Running Linux with AMP application without LINUXMEM specified to limit Linux memory usage\n");
        ok = False;
    }

    if (!options.IMAGE0 && options.IMAGE0SYM) {
        icmPrintf("Error: IMAGE0SYM specified without IMAGE0\n");
        ok = False;
    }

    if (!options.IMAGE1 && options.IMAGE1SYM) {
        icmPrintf("Error: IMAGE1SYM specified without IMAGE1\n");
        ok = False;
    }

    if (options.IMAGE0 && options.IMAGE0ADDR==-1ULL) {
        icmPrintf("Error: IMAGE0SYM specified without IMAGE0ADDR\n");
        ok = False;
    }

    if (options.IMAGE1 && options.IMAGE1ADDR==-1ULL) {
        icmPrintf("Error: IMAGE1SYM specified without IMAGE1ADDR\n");
        ok = False;
    }

    if (ok) {
        setOverrides();
    }

    return ok;

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

static Bool postPlatformConstruct(AlteraCycloneV_HPS_TLM2 &top) {

    if (options.BOOT) {
        // Use the processor to load memory with the boot file.
        top.cpu.loadLocalMemory(options.BOOT, (icmLoaderAttrs)(ICM_LOAD_VERBOSE));
    }

    // Setup application on each leaf processor
    icmIterAllDescendants(top.cpu.getProcessorP(), setupApplication, NULL);

    return True;

}


#include "platform.sc_clp.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    // Initialize options to default values
    setDefaults();

    if(!cmdParser(argc, (const char **)argv)) {
        return 1;
    }
    if(!postCmdParser())  {
        return 1;
    }
    AlteraCycloneV_HPS_TLM2 AlteraCycloneV_HPS_TLM2 ("AlteraCycloneV_HPS_TLM2");

    if(!postPlatformConstruct(AlteraCycloneV_HPS_TLM2)) {
        return 1;
    }

    sc_core::sc_start();

    return 0;
}
