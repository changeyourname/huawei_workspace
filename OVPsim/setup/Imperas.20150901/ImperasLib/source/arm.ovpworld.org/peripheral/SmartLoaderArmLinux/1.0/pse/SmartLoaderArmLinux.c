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

//
// Smart loader peripheral model for Linux:
//   Provides pre-boot memory initialization for loading an ARM zImage compressed kernel file.
//   For a description of some of what the heck is going on here see:
//    http://www.linux-arm.org/pub/LinuxPlatform/RealViewLink/Booting_ARM_Linux_SMP_on_MPCore.doc
//   This peripheral takes the place of the Boot monitor and U-Boot functions
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "peripheral/impTypes.h"
#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

#define PREFIX "SMARTLOADER_LINUX"

#define ADDRRESS_SPACE_PORT     "mport"

ppmAddressSpaceHandle addressSpaceHandle;

#define BUFSIZE 256

// Use ArmIntegrator board ID as default
#define DEFAULT_BOARDID 0x113

// Use 128MB as default memory size
#define DEFAULT_MEMSIZE (128*1024*1024)

struct arm_boot_info {
    Uns32 stackPointer;                 // stack pointer to pass to Linux
    Uns32 boardId;                      // ID of board to pass to Linux
    Uns32 memBase;                      // address of start of memory
    Uns32 memSize;                      // size of memory
    Uns32 atagsAddr;                    // address to load ATAGS data (should be in first 16K)
    Uns32 bootAddr;                     // address to load boot code
    Uns32 kernelAddr;                   // address to load kernel file
    Uns32 initrdAddr;                   // address to load initrd file
    char  kernelFn[BUFSIZE];            // Name of kernel file to load (required)
    char  initrdFn[BUFSIZE];            // name of initrd file to load (optional)
    char  linuxCmdline[BUFSIZE];        // Linux command line
};

// Structure to hold configuration info, initialized with defaults
static struct arm_boot_info configInfo = {
        .stackPointer    = 0,           // default is memBase+memSize
        .boardId         = DEFAULT_BOARDID,
        .memBase         = 0,
        .memSize         = DEFAULT_MEMSIZE,
        .bootAddr        = 0,           // default is this + memBase setting
        .atagsAddr       = 0x00000100,  // default is this + memBase setting
        .kernelAddr      = 0x00010000,  // default is this + memBase setting
        .initrdAddr      = 0x00d00000,  // default is this + memBase setting
        .kernelFn        = "",
        .initrdFn        = "",
        .linuxCmdline    = ""
};

/* The worlds second smallest bootloader.  Set registers to values expected by Linux then jump to kernel.  */
static Uns32 bootloader[] = {
  0xe3a00000, // mov     r0, #0
  0xe59fd00c, // ldr     sp, [pc, #12]
  0xe59f100c, // ldr     r1, [pc, #12]
  0xe59f200c, // ldr     r2, [pc, #12]
  0xe59f300c, // ldr     r3, [pc, #12]
  0xe59ff00c, // ldr     pc, [pc, #12]
  // The following are filled in based on the attributes passed in
  0,          // pointer to stack area
  0,          // boardid
  0,          // Address of kernel args
  0,          // Address of kernel image
  0,          // Address to jump to
};

// ATAG Constants (from arch/arm/include/uapi/asm/setup.h)
#define ATAG_NONE    0x00000000
#define ATAG_CORE    0x54410001
#define ATAG_MEM     0x54410002
#define ATAG_INITRD2 0x54420005
#define ATAG_CMDLINE 0x54410009

// Diagnostics
Uns32 diagnosticLevel;
#define DIAG_1  (diagnosticLevel >= 1)
#define DIAG_2  (diagnosticLevel >= 2)
#define DIAG_3  (diagnosticLevel >= 3)
static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

// ***************************************************************

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

//
// Write to simulated memory
//
static Bool writeSimMemory(const char *name, Uns32 addr, Uns32 size, Uns32 *data) {

    if (DIAG_2) {
        bhmMessage(
            "I", PREFIX,
            "Writing %s to 0x%08x, size %d",
            name, addr, size);
    }

    if (!ppmWriteAddressSpace(addressSpaceHandle, addr, size, data)) {

        bhmMessage(
            "E", PREFIX,
            "Failed trying to write %s to 0x%08x, size %d",
            name, addr, size
        );
        return False;

    }

    return True;

}

//
// Load the file at the indicated address
// Returns number of bytes loaded or 0 if an error
//
static Uns32 load_image(char *name, const char *filename, Uns32 addr) {

    Int32 fd = open(filename, O_RDONLY | O_BINARY);

    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open %s image file %s", name, filename);
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

        if (!ppmWriteAddressSpace(addressSpaceHandle, dest, thisAccess, buff)){

            bhmMessage(
                "E", PREFIX,
                "Unable to write %s image file %s to simulated memory: failed at 0x%08x",
                name, filename, dest
            );

            close(fd);
            return 0;

        }

        dest  += thisAccess;
        bytes -= thisAccess;

    }

    close(fd);

    if(DIAG_1) {
        bhmMessage("I", PREFIX, "%s image file %s loaded (%u bytes)", name, filename, size);
    }

    return size;
}

//
// write a value to the ATAG Memory, incrementing the pointer
//
static inline void writeATAG(Uns32 **p, Uns32 val) {
    *((*p)++) = val;
}

//
// write an ATAG entry:
//  <size>
//  <ATAG>
//  <data> (size-2 bytes of data)
//
static void writeATAGEntry(Uns32 **p, Uns32 id, Uns32 *data, Uns32 numEntries) {

    // ATAG_NONE requires size 0, all others the total number of bytes taken by the tag
    Uns32 tagSize = id==ATAG_NONE ? 0 : numEntries+2;

    writeATAG(p, tagSize);
    writeATAG(p, id);

    Uns32 i;
    for (i = 0; i < numEntries; i++) {
        writeATAG(p, data[i]);
    }

}

#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

//
// Write ATAGS data to the buffer
//
static Uns32 getATAGS(Uns32 *buf, Uns32 size, Uns32 initrdSize) {

    Uns32 *p = buf;

    // Write ATAG_CORE Entry
    Uns32 coreData[] = {
        1,                    // flags (read-only)
        0x1000,               // pagesize
        0                     // rootdev
    };
    writeATAGEntry(&p, ATAG_CORE, coreData, NUM_MEMBERS(coreData));

    // Write ATAG_MEM Entry
    Uns32 memData[] = {
        configInfo.memSize,   // size
        configInfo.memBase,   // start
    };
    writeATAGEntry(&p, ATAG_MEM, memData, NUM_MEMBERS(memData));

    // Write ATAG_INITRD2 Entry if specified
    if (initrdSize) {
        Uns32 initrdData[] = {
            configInfo.initrdAddr,  // start
            initrdSize,             // size
        };
        writeATAGEntry(&p, ATAG_INITRD2, initrdData, NUM_MEMBERS(initrdData));
    }

    // Write ATAG_CMDLINE Entry, if specified
    if (configInfo.linuxCmdline && *configInfo.linuxCmdline) {

        // Make string into array of Uns32
        Uns32 cmdlineLen  = strlen(configInfo.linuxCmdline);
        Uns32 cmdlineSize = (cmdlineLen >> 2) + 1;
        Uns32 cmdlineData[cmdlineSize];

        // Make sure last word is initialized
        cmdlineData[cmdlineSize-1] = 0;

        // Copy from string to Uns32 array
        strcpy((char *)cmdlineData, configInfo.linuxCmdline);

        writeATAGEntry(&p, ATAG_CMDLINE, cmdlineData,  NUM_MEMBERS(cmdlineData));

    }

    // Write ATAG_NONE Entry
    writeATAGEntry(&p, ATAG_NONE, NULL, 0);

    Uns32 used = (p - buf) * sizeof(Uns32);

    if (used > size) {
        bhmMessage("F", PREFIX, "ATAGS buffer overflow");
        bhmFinish();
    }

    return used;

}

static Bool setIntegerAttribute(char *name, Uns32 *val) {

    Uns32 attrVal;

    if (bhmIntegerAttribute(name, &attrVal)) {
        *val = attrVal;
        if(DIAG_1) {
            bhmMessage("I", PREFIX, "%s: set to %d (0x%08x)", name, *val, *val);
        }
        return True;
    } else if (DIAG_1) {
        bhmMessage("I", PREFIX, "%s: using default value %d (0x%08x)", name, *val, *val);
    }
    return False;
}

static Bool setStringAttribute(char *name, char *str, Uns32 size) {

    if (bhmStringAttribute(name, str, size)) {
        if(DIAG_1) {
            bhmMessage("I", PREFIX, "%s: set to %s", name, str);
        }
        return True;
    }
    return False;
}

//
// Issue error message if address is outside of physical memory range
//
static void checkRange(char *name, Uns32 address) {
    Uns32 low  = configInfo.memBase;
    Uns32 high = low + configInfo.memSize - 1;

    if (address < low || address > high) {

        bhmMessage(
            "E", PREFIX,
            "%s value 0x%08x is outside of memory range 0x%08x:0x%08x",
            name, address, low, high);

    }
}

//
// Access all attributes to inhibit unused warning messages
//
static void touchAttributes() {

    Uns32 dummy;
    char dummyStr[4];

    bhmIntegerAttribute("boardid",      &dummy);
    bhmIntegerAttribute("memsize",      &dummy);
    bhmIntegerAttribute("physicalbase", &dummy);
    bhmIntegerAttribute("kerneladdr",   &dummy);
    bhmIntegerAttribute("initrdaddr",   &dummy);
    bhmIntegerAttribute("atagsaddr",    &dummy);
    bhmIntegerAttribute("bootaddr",     &dummy);
    bhmStringAttribute ("kernel",        dummyStr, sizeof(dummyStr));
    bhmStringAttribute ("command",       dummyStr, sizeof(dummyStr));
    bhmStringAttribute ("append",        dummyStr, sizeof(dummyStr));
    bhmStringAttribute ("initrd",        dummyStr, sizeof(dummyStr));

}

static void addDoc() {
    ppmDocNodeP docRoot = ppmDocAddSection(0, "Root");

    ppmDocNodeP docDesc = ppmDocAddSection(docRoot, "Description");
    ppmDocAddText(docDesc, "Psuedo-peripheral to perform memory initialisation for an ARM based Linux kernel boot:");
    ppmDocAddText(docDesc, "Loads Linux kernel image file and (optional) initial ram disk image into memory.");
    ppmDocAddText(docDesc, "Writes ATAG data into memory.");
    ppmDocAddText(docDesc, "Writes tiny boot code at physical memory base that configures the registers as expected by Linux Kernel and then jumps to boot address (image load address by default).");

    ppmDocNodeP docLicense = ppmDocAddSection(docRoot, "Licensing");
    ppmDocAddText(docLicense, "Open Source Apache 2.0");

    ppmDocNodeP docLimits = ppmDocAddSection(docRoot, "Limitations");
    ppmDocAddText(docLimits, "Only supports little endian");

    ppmDocNodeP docRef = ppmDocAddSection(docRoot, "Reference");
    ppmDocAddText(docRef, "See ARM Linux boot requirements in Linux source tree at documentation/arm/Booting");
}

int main(int argc, char **argv)
{
    diagnosticLevel = 0;
    addDoc();
    bhmInstallDiagCB(setDiagLevel);

    bhmEventHandle finished = bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION);

    if (!(addressSpaceHandle = ppmOpenAddressSpace(ADDRRESS_SPACE_PORT))) {

        bhmMessage("E", PREFIX, "Failed to open port %s\n", ADDRRESS_SPACE_PORT);

    } else if(bhmBoolAttribute("disable")) {

        bhmMessage("W", PREFIX, "Platform Initialization Disabled");
        touchAttributes();

    } else  {

        // Override defaults with any attributes set from platform
        setIntegerAttribute("boardid",      &configInfo.boardId);
        setIntegerAttribute("memsize",      &configInfo.memSize);
        setIntegerAttribute("physicalbase", &configInfo.memBase);

        // Adjust these default values for membase value
        configInfo.stackPointer = configInfo.memBase + configInfo.memSize;
        configInfo.kernelAddr  += configInfo.memBase;
        configInfo.initrdAddr  += configInfo.memBase;
        configInfo.atagsAddr   += configInfo.memBase;

        // Override defaults with any attributes set from platform
        setIntegerAttribute("stackpointer", &configInfo.stackPointer);
        setIntegerAttribute("kerneladdr",   &configInfo.kernelAddr);
        setIntegerAttribute("initrdaddr",   &configInfo.initrdAddr);
        setIntegerAttribute("atagsaddr",    &configInfo.atagsAddr);

        // Set bootAddr - default depends on kernelAddr setting
        configInfo.bootAddr = configInfo.kernelAddr;
        setIntegerAttribute("bootaddr", &configInfo.bootAddr);

        // Validate that all Linux addresses specified are in suitable range
        checkRange("atagsaddr",    configInfo.atagsAddr);
        checkRange("kerneladdr",   configInfo.kernelAddr);
        checkRange("initrdaddr",   configInfo.initrdAddr);

        if (!setStringAttribute("kernel", configInfo.kernelFn, sizeof(configInfo.kernelFn))) {
            bhmMessage("E", PREFIX, "Failed to specify the Kernel image to load into platform using 'kernel' attribute");
            configInfo.kernelFn[0] = 0;
        }

        // Set the command line
        char cmdLine[512] = "";
        char append[512]  = "";
        setStringAttribute("command", cmdLine, sizeof(cmdLine));

        if (setStringAttribute("append",  append, sizeof(append))) {
            snprintf(configInfo.linuxCmdline, sizeof(configInfo.linuxCmdline), "%s %s", cmdLine, append);
        } else {
            snprintf(configInfo.linuxCmdline, sizeof(configInfo.linuxCmdline), "%s", cmdLine);
        }

        if (DIAG_1) {
            bhmMessage(
                "I", PREFIX,
                "Linux kernel command line set to: '%s'",
                configInfo.linuxCmdline
            );
        }

        setStringAttribute("initrd", configInfo.initrdFn, sizeof(configInfo.initrdFn));

        // Place stackpointer, board id, ATAGS, boot and kernel entry addresses in bootloader
        bootloader[6] = configInfo.stackPointer;
        bootloader[7] = configInfo.boardId;
        bootloader[8] = configInfo.atagsAddr;
        bootloader[9] = configInfo.kernelAddr;
        bootloader[10]= configInfo.bootAddr;

        // Write bootloader to beginning of memory
        writeSimMemory("bootloader", configInfo.memBase, sizeof(bootloader), bootloader);

        // Write kernel image to memory
        if(*configInfo.kernelFn) {
            load_image("kernel", configInfo.kernelFn, configInfo.kernelAddr);
        }

        // Write initrd image to memory if an initrd image file was specified
        Uns32 initrdSize = 0;
        if (configInfo.initrdFn[0]) {
            initrdSize = load_image("initrd", configInfo.initrdFn, configInfo.initrdAddr);
        }

        // Build ATAGS array
        Uns32 atags[1024];
        Uns32 atagsSize = getATAGS(atags, sizeof(atags), initrdSize);

        // Write ATAGS to memory
        writeSimMemory("atags", configInfo.atagsAddr, atagsSize, atags);

    }

    if(addressSpaceHandle) {
        ppmCloseAddressSpace(addressSpaceHandle);
    }

    // now sit and wait for end of simulation
    bhmWaitEvent(finished);

    return 0;
}
