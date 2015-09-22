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
//   Loads the Linux Kernel, device tree blob and optional initrd.
//
//   For a description of some of what the heck is going on here see the file:
//      Documentation/arm64/booting.txt
//   in the Linux source tree.
//
//   This peripheral takes the place of the Boot monitor and U-Boot functions
//
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pse.igen.h"
#include "libfdt.h"

#define PREFIX "SMARTLOADER_LINUX"

#define FNSIZE 256

struct arm_boot_info {
    Addr  memBase;           // address of start of memory
    Addr  kernelAddr;        // address in simulated memory of kernel
    Addr  fdtAddr;           // address in simulated memory of flattened device tree
    Addr  initrdAddr;        // address in simulated memory of initrd
    Uns32 initrdSize;        // size of initrd file in bytes
    Addr  releaseAddr;       // cpu release address for device tree spin-table enable-method
    char  kernelFn[FNSIZE];  // Name of kernel file to load
    char  dtbFn[FNSIZE];     // Name of device tree blob file to load
    char  initrdFn[FNSIZE];  // name of initrd file to load (optional)
};

// Structure to hold configuration info, initialized with defaults
static struct arm_boot_info config = {
    .kernelAddr = 0x80000ULL,   // default is this + memBase setting
    .kernelFn   = "Image",
    .dtbFn      = "",
    .initrdFn   = "",
};

//
// The tiny bootloader.  Set registers to values expected by Linux then jump to kernel.
// (assumes it is being run in EL3)
//
static Uns32 bootloader[] = {
    //
    // ARM V8 Linux Boot code
    // Compatible only with:
    //    spin-table CPU enable method
    //    gic V2 at 0x2c000000
    //
    0x58000440, // ldr x0, dtb
    0x58000461, // ldr x1, kernel

    // for core0 start core in EL2 at address in X1
    0xd53800a3, // mrs x3, mpidr_el1
    0xf2401c7f, // tst x3, #0xff
    0x540000a0, // b.eq start_core

    // for cores other than 0, wait for cpu-release-addr to be set
    // then start the core in EL2 at that address
    // 1:
    0xd503205f, // wfe
    0x58000401, // ldr  x1, <release>
    0xf100003f, // cmp x1, #0x0
    0x54ffffa0, // b.eq 1B

    // start_core:

    // set HCE, NS and RW bits in scr_el3
    0xd53e1103, // mrs x3, scr_el3
    0xd280a024, // mov x4, #0x501
    0xaa040063, // orr x3, x3, x4
    0xd51e1103, // msr scr_el3, x3

    // seed spsr_el3 with mode EL2
    0xd53e4003, // mrs x3, spsr_el3
    0x927be863, // bic x3, x3, #0x1f
    0xb27d0063, // orr x3, x3, #0x8
    0xd51e4003, // msr spsr_el3, x3

    // seed elr_el3 with target address
    0xd51e4021, // msr elr_el3, x1

    // Set GICC_PMR to 0x80 to allow non-secure access to it
    0xd2a58004, // movz        x4, #0x2c00, LSL 16
    0x52801005, // movz        w5, #0x80
    0xb9200485, // str         w5, [x4, #0x2004]

    // Write all 1's to GICD_IGROUPRxx to allow access from NS EL1
    0xb9500485, // ldr w5, [x4,#0x1004] // GICD_TYPER
    0x120010a5, // and w5, w5, #0x1f    // GICD_TYPER.ITLines
    0x531e74a5, // lsl w5, w5, #2       // GICD_TYPER.ITLines*4
    0xf2821004, // movk    x4, #0x1080  // GICD_IGROUPR00
    0x8b0400a5, // add x5, x5, x4       // GICD_IGROUPRNN+1
    0x2a3f03e3, // mvn w3, wzr
    0xb8004483, // str w3, [x4],#4
    0xeb05009f, // cmp x4, x5
    0x54ffffcb, // b.lt    68 <start_core+0x40>

    // clear x1-x3
    0xaa1f03e1, // mov x1, xzr
    0xaa1f03e2, // mov x2, xzr
    0xaa1f03e3, // mov x3, xzr

    // switch mode to EL2
    0xd69f03e0, // eret

    // Note: Must be aligned to 8 bytes

    // dtb:     .quad 0  //  Fill with PA of dtb
    0x0, 0x0,
    // kernel:  .quad 0  //  Fill with PA of kernel entry
    0x0, 0x0,
    // release: .quad 0  //  spin-table cpu-release-addr - to be set by kernel
    0x0, 0x0
};

// Indexes for the address entries to be filled in
#define BOOT_ENTRIES (sizeof(bootloader)/sizeof(bootloader[0]))
#define ENTRIES_PER_UNS64 (sizeof(Uns64)/sizeof(bootloader[0]))
#define BOOT_FDT     (BOOT_ENTRIES - (3*ENTRIES_PER_UNS64))
#define BOOT_KERNEL  (BOOT_ENTRIES - (2*ENTRIES_PER_UNS64))
#define BOOT_RELEASE (BOOT_ENTRIES - (1*ENTRIES_PER_UNS64))

// Diagnostics
#define DIAG_1  (diagnosticLevel >= 1)
#define DIAG_2  (diagnosticLevel >= 2)
#define DIAG_3  (diagnosticLevel >= 3)

// ***************************************************************

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

//
// Write to simulated memory
//
static Bool writeSimMemory(
    const char *name,
    Addr        addr,
    Uns32       size,
    void       *data
) {

    if (DIAG_2) {
        bhmMessage(
            "I", PREFIX,
            "Writing %s (%d bytes at 0x%08llx)",
            name, size, addr
        );
    }

    if (!ppmWriteAddressSpace(handles.mport, addr, size, data)) {

        bhmMessage(
            "E", PREFIX,
            "Failed trying to write %s (%d bytes at 0x%08llx)",
            name, size, addr
        );
        return False;

    }

    return True;

}

//
// Return the size of a file given its file descriptor
// (resets file pointer to the beginning of the file)
//
static Uns32 fileSize(Int32 fd) {

    // Get the size of the file
    size_t size = lseek(fd, 0, SEEK_END);

    // Seek back to the beginning
    lseek(fd, 0, SEEK_SET);

    return size;
}

//
// Load the file to the indicated simulated memory address
// Returns number of bytes loaded or 0 if an error
//
static Uns32 loadImage(char *name, const char *filename, Addr addr) {

    Int32 fd = open(filename, O_RDONLY | O_BINARY);

    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open %s image file '%s'", name, filename);
        return 0;
    }

    // Get the size of the file
    Uns32 size = fileSize(fd);

    // Copy the file to simulated memory
    Uns32 bytes = size;
    Addr  dest  = addr;
    char buff[BYTES_PER_ACCESS];
    while (bytes) {

        size_t thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;

        thisAccess = read(fd, buff, thisAccess);

        if (!ppmWriteAddressSpace(handles.mport, dest, thisAccess, buff)) {

            bhmMessage(
                "E", PREFIX,
                "Unable to write %s image file '%s' to simulated memory: failed at 0x%08llx",
                name, filename, dest
            );

            close(fd);
            return 0;

        }

        dest += thisAccess;
        bytes -= thisAccess;

    }

    close(fd);

    if (DIAG_1) {
        bhmMessage(
            "I", PREFIX,
            "%s image file '%s' loaded (%d bytes at 0x%08llx)",
            name, filename, size, addr
        );
    }

    return size;
}

static Bool setUns64Attribute(char *name, Uns64 *val) {

    Uns64 attrVal;

    if (bhmUns64Attribute(name, &attrVal)) {
        *val = attrVal;
        if (DIAG_1) {
            bhmMessage("I", PREFIX, "%s: set to %lld", name, *val);
        }
        return True;
    } else if (DIAG_1) {
        bhmMessage("I", PREFIX, "%s: using default value %lld", name, *val);
    }
    return False;
}

static Bool setAddrAttribute(char *name, Addr *val) {

    Addr attrVal;

    if (bhmUns64Attribute(name, &attrVal)) {
        *val = attrVal;
        if (DIAG_1) {
            bhmMessage("I", PREFIX, "%s: set to 0x%08llx", name, *val);
        }
        return True;
    } else if (DIAG_1) {
        bhmMessage("I", PREFIX, "%s: using default value 0x%08llx", name, *val);
    }
    return False;
}

static Bool setStringAttribute(char *name, char *str, Uns32 size) {

    if (bhmStringAttribute(name, str, size)) {
        if (DIAG_1) {
            bhmMessage("I", PREFIX, "%s: set to '%s'", name, str);
        }
        return True;
    }
    return False;
}

//
// Align pointer to the indicate byte boundary
//
static inline Addr alignPointer(Addr ptr, Uns32 align) {
    Addr mask = align - 1;
    return (ptr + mask) & ~mask;
}

#define FDT_CHECK(code) \
    { \
        err = (code); \
        if (err) { \
            bhmMessage( \
                "E", PREFIX"_FDTERR", \
                #code ": %s", \
                fdt_strerror(err) \
            ); \
        } \
    }

static void fdtShowHeader(const void *fdt) {
    bhmMessage("I", PREFIX"_FDT", "Header magic 0x%x", fdt_magic(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header off_dt_struct 0x%x", fdt_off_dt_struct(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header off_dt_strings 0x%x", fdt_off_dt_strings(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header off_mem_rsvmap 0x%x", fdt_off_mem_rsvmap(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header version 0x%x", fdt_version(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header last_comp_version 0x%x", fdt_last_comp_version(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header size_dt_strings 0x%x", fdt_size_dt_strings(fdt));
    bhmMessage("I", PREFIX"_FDT", "Header size_dt_struct 0x%x", fdt_size_dt_struct(fdt));
}

static void fdtShowNode(const void *fdt, int nodeOffset) {

    int err;
    int offset;
    char path[256];

    FDT_CHECK(fdt_get_path(fdt, nodeOffset, path, sizeof(path)));

    if (!err) {

        bhmMessage("I", PREFIX"_FDT", "Path: %s", path);

        // List properties
        for (offset=fdt_first_property_offset(fdt, nodeOffset);
             offset >= 0;
             offset=fdt_next_property_offset(fdt, offset)) {

            const void *prop;
            const char *propName;
            int         propLen;

            prop = fdt_getprop_by_offset(fdt, offset, &propName, &propLen);
            if (prop) {
                bhmMessage(
                    "I", PREFIX"_FDT",
                    "  prop: '%s', len=%d",
                    propName, propLen
                );
            }
        }

        // list subnodes
        for (offset=fdt_first_subnode(fdt, nodeOffset);
             offset >= 0;
             offset=fdt_next_subnode(fdt, offset)) {

            fdtShowNode(fdt, offset);

        }
    }
}

//
// Print the Memory Reserve table in the fdt
//
static void fdtShowMemRsv(const void *fdt) {

    Uns64 addr;
    Uns64 size;
    int i;

    for (i = 0, size = -1ULL; size != 0; i++) {
        fdt_get_mem_rsv(fdt, i, &addr, &size);
        if (size) {
            // TODO: work around bug with 64 bit arguments in bhmMessage
            union { Uns64 u64; Uns32 u32[2]; } addrX={.u64=addr}, sizeX={.u64=size};
            bhmMessage(
                "I", PREFIX"_FDT",
                "MemRsv: At: 0x%08x%08x Size: 0x%08x%08x",
                addrX.u32[1], addrX.u32[0], sizeX.u32[1], sizeX.u32[0]
            );
        }
    }
}

//
// Print the dtb that has been loaded into memory
//
static void fdtPrint(const void *fdt) {
    fdtShowHeader(fdt);
    fdtShowNode(fdt, 0);
    fdtShowMemRsv(fdt);
}

//
// Find or add the indicated subnode at the indicate path
//
static Int32 fdtFindAddNode(void *fdt, const char *path, const char *node) {

    Int32 parentOffset = fdt_path_offset(fdt, path);
    Int32 offset;

    if (parentOffset < 0) {

        // Error finding parent node
        offset = parentOffset;

    }  else {

        offset = fdt_subnode_offset(fdt, parentOffset, node);
        if (offset == -FDT_ERR_NOTFOUND) {
            // Must add the node
            offset = fdt_add_subnode(fdt, parentOffset, node);
        }

    }

    if (offset < 0) {
        bhmMessage(
            "E", PREFIX"_ECN",
            "Error creating FDT node '%s%s%s': %s",
            path,
            (*path && path[strlen(path)-1] == '/') ? "" : "/",
            node,
            fdt_strerror(offset)
        );
    }

    return offset;
}

//
// Add memory reserve entries to fdt
//
static void fdtReserveMemory(void *fdt, Addr start, Uns32 size) {

    Int32 err;

    FDT_CHECK(fdt_add_mem_rsv(fdt, start, size));

}

//
// Set the initrd data in the fdt (info must already be set in config)
//
static void fdtSetInitrd(void *fdt, Addr initrdStart, Uns32 initrdSize) {

    if (config.initrdSize) {

        Int32 chosenOffset = fdtFindAddNode(fdt, "/", "chosen");
        if (chosenOffset >= 0) {

            Addr initrdEnd   = initrdStart + initrdSize;

            fdt_setprop_u64(fdt, chosenOffset, "linux,initrd-start", initrdStart);
            fdt_setprop_u64(fdt, chosenOffset, "linux,initrd-end",   initrdEnd);

            fdtReserveMemory(fdt, initrdStart, initrdSize);

        }
    }
}

//
// Set the enable-method
// The only enable-method we support is spin-table - force it to that
//
static void fdtSetEnableMethod(void *fdt) {

    int err;

    Int32 cpusOffset = fdt_path_offset(fdt, "/cpus");
    if (cpusOffset < 0) {

        bhmMessage(
            "E", PREFIX"_UFC",
            "Unable to find node '/cpus' in dtb: %s",
            fdt_strerror(cpusOffset)
        );

    } else {

        // Get address of release address location in the bootloader code
        Addr releaseAddr = config.memBase + (BOOT_RELEASE * sizeof(bootloader[0]));
        int cpuOffset;

        for (cpuOffset=fdt_first_subnode(fdt, cpusOffset);
             cpuOffset >= 0;
             cpuOffset=fdt_next_subnode(fdt, cpuOffset)) {

            FDT_CHECK(fdt_setprop_string(fdt, cpuOffset, "enable-method", "spin-table"));
            FDT_CHECK(fdt_setprop_u64   (fdt, cpuOffset, "cpu-release-addr", releaseAddr));

        }
    }
}

//
// Set the command line data in the fdt
//
static void fdtSetCommandLine(void *fdt) {

    char cmdLine[512] = "";
    char append[512]  = "";
    int  err;

    setStringAttribute("command", cmdLine, sizeof(cmdLine));
    setStringAttribute("append",  append, sizeof(append));

    if (*append) {
        snprintf(cmdLine, sizeof(cmdLine), "%s %s", cmdLine, append);
    }

    if (*cmdLine) {

        Int32 chosenOffset = fdtFindAddNode(fdt, "/", "chosen");

        if (chosenOffset >= 0) {

            FDT_CHECK(fdt_setprop_string(fdt, chosenOffset, "bootargs", cmdLine));

            if (DIAG_1) {
                bhmMessage(
                    "I", PREFIX"_LCL",
                    "Linux kernel command line set to: '%s'",
                    cmdLine
                );
            }
        }
    }
}

//
// TODO: Can we set the freq for the timer according to the timer scale factor?
//
static void fdtSetTimerScale(void *fdt) {

    Uns64 scale = 1;

    setUns64Attribute("override_timerScaleFactor", &scale);

}

//
// Read the device tree blob into memory
// If any problems issue error or fatal messages so that simulation will not proceed
//
static void *readDTB(char *fn) {

    Int32 fd = open(fn, O_RDONLY | O_BINARY);
    if (fd < 0) {
        bhmMessage("E", PREFIX"_UOD", "Unable to open dtb file '%s'", fn);
        return NULL;
    }

    // Allocate a buffer to hold the dtb file + room for adding some data
    Uns32 origDTBsize = fileSize(fd);
    Uns32 DTBsize     = origDTBsize + 1024;
    void *dtb         = malloc(DTBsize);
    if (!dtb) {
        bhmMessage("F", PREFIX"_UAD", "Unable to allocate %d bytes for dtb", DTBsize);
        return NULL;   // Not reached
    }

    // load the dtb into the allocated buffer
    Int32 rc = read(fd, dtb, origDTBsize);
    close(fd);
    if (rc != origDTBsize) {
        bhmMessage("E", PREFIX"_URD", "Unable to read dtb file '%s'", fn);
        free(dtb);
        return NULL;
    }

    // Let fdt know about the extra space available
    fdt_set_totalsize(dtb, DTBsize);

    // Check that dtb file just loaded is valid
    rc = fdt_check_header(dtb);
    if (rc != 0) {
        bhmMessage("E", PREFIX"_DFI", "dtb file '%s' invalid: %s", fn, fdt_strerror(rc));
        return NULL;
    }

    if (DIAG_1) {
        bhmMessage("I", PREFIX"_DFL", "dtb file '%s' loaded (%d bytes)", fn, origDTBsize);
    }

    return dtb;

}

//
// Access all attributes to inhibit unused warning messages
//
static void touchAttributes() {

    Uns64 dummy;
    char dummyStr[4];

    bhmUns64Attribute ("override_timerScaleFactor", &dummy);
    bhmUns64Attribute ("kerneladdr", &dummy);
    bhmUns64Attribute ("kerneladdr", &dummy);
    bhmStringAttribute("kernel",      dummyStr, sizeof(dummyStr));
    bhmStringAttribute("command",     dummyStr, sizeof(dummyStr));
    bhmStringAttribute("append",      dummyStr, sizeof(dummyStr));
    bhmStringAttribute("initrd",      dummyStr, sizeof(dummyStr));
    bhmStringAttribute("dtb",         dummyStr, sizeof(dummyStr));

}

PPM_CONSTRUCTOR_CB(constructor) {

    bhmEventHandle finished = bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION);
    Addr           writePointer;

    periphConstructor();

    if (bhmBoolAttribute("disable")) {

        bhmMessage("W", PREFIX"_SLD", "Linux Smart Loader Disabled");
        touchAttributes();

    } else {

        //
        // Override defaults with any attributes set from platform
        //
        setAddrAttribute("physicalbase", &config.memBase);
        config.kernelAddr += config.memBase;
        setAddrAttribute("kerneladdr",   &config.kernelAddr);

        //
        // Write kernel image to memory
        //
        if (!setStringAttribute("kernel", config.kernelFn, sizeof(config.kernelFn))) {
            bhmMessage(
                "I", PREFIX,
                "kernel: using default value '%s'",
                config.kernelFn
            );
        }
        writePointer  = config.kernelAddr;
        writePointer += loadImage("kernel", config.kernelFn, writePointer);

        // Align write pointer to next 16MB page, to make sure it is past kernel's BSS
        writePointer  = alignPointer(writePointer, 16*1024*1024);

        //
        // if an initrd image file was specified,
        // copy it into simulated memory (Aligned to 4096 bytes)
        //
        setStringAttribute("initrd", config.initrdFn, sizeof(config.initrdFn));
        if (*config.initrdFn != '\0') {
            writePointer      = alignPointer(writePointer, 4096);
            config.initrdAddr = writePointer;
            config.initrdSize = loadImage("initrd", config.initrdFn, config.initrdAddr);
            writePointer      += config.initrdSize;
        }

        //
        // Read dtb file into host memory and add any additional settings to the fdt
        // Copy the fdt to simulated memory immediately following the bootloader (aligned to 8 bytes)
        // (Note: Must be done after initrd has been read)
        //
        if (!setStringAttribute("dtb", config.dtbFn, sizeof(config.dtbFn))) {

            bhmMessage("E", PREFIX"_MDF", "dtb file name must be specified using the dtb parameter");

        } else {

            void *fdt = readDTB(config.dtbFn);

            if (fdt) {

                // Set initrd info in fdt
                fdtSetInitrd(fdt, config.initrdAddr, config.initrdSize);

                // Set enable-method in fdt
                fdtSetEnableMethod(fdt);

                // set command line info in fdt
                fdtSetCommandLine(fdt);

                // set the timer scale factor
                fdtSetTimerScale(fdt);

                if (DIAG_3) {
                    fdtPrint(fdt);
                }

                // Get size of the fdt in config
                Uns32 fdtSize = fdt_totalsize(fdt);

                config.fdtAddr = alignPointer(config.memBase + sizeof(bootloader), 8);
                if (config.fdtAddr + fdtSize >= config.kernelAddr) {
                    bhmMessage("F", PREFIX"_DTB", "Device tree too big: %d bytes", fdtSize);
                }

                // Copy fdt to simulated memory
                writeSimMemory("dtb", config.fdtAddr, fdtSize, fdt);

            }
        }

        // Place fdtAddr and kernelAddr in boot code
        *(Uns64 *)(bootloader+BOOT_FDT)     = config.fdtAddr;
        *(Uns64 *)(bootloader+BOOT_KERNEL)  = config.kernelAddr;
        *(Uns64 *)(bootloader+BOOT_RELEASE) = 0ULL; // will be set by kernel

        // Write bootloader to beginning of simulated memory
        writeSimMemory("bootloader", config.memBase, sizeof(bootloader), bootloader);

    }

    // No longer used so close it
    ppmCloseAddressSpace(handles.mport);

    // now sit and wait for end of simulation
    bhmWaitEvent(finished);

}

//
// PSE newlib memmove() function does not work!
//
void *memmove_local(void *dest, const void *src, int len) {

    const char *s = src;
    char       *d = dest;

    if ((d == s) || (len == 0)) {
        // No copy needed
    } else if ((s < d) && (d < (s + len))) {
        // Have to copy backwards
        s += len;
        d += len;
        while (len-- > 0) {
            *(--d) = *(--s);
        }
    } else {
        while (len-- > 0) {
            *(d++) = *(s++);
        }
    }

    return dest;
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

