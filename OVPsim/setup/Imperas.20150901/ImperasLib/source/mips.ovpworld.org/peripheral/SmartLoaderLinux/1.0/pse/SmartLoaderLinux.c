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


// smart loader model for Linux provides memory initialization for running a linux kernel

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "peripheral/impTypes.h"
#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

#include "elfreader.h"

#define DIAG_HIGH   ((diag & 3) >  2)
#define DIAG_MEDIUM ((diag & 3) >  1)
#define DIAG_LOW    ((diag & 3) >  0)

#define BUFFERLENGTH 16
#define DEBUG 0
#define PREFIX "SMARTLOADER_LINUX"

// Calculate number of entries in an array
#define NUM_ENTRIES(_A) (sizeof(_A)/sizeof(*_A))

// Need to define the TLB page size used in the target processor
// this is used to align the loaded initrd onto the next page boundary
#define TARGET_PAGE_BITS_DEFAULT 12
Uns32 targetPageBits = TARGET_PAGE_BITS_DEFAULT;
#define TARGET_PAGE_SIZE (1 << targetPageBits)
#define TARGET_PAGE_MASK ~(TARGET_PAGE_SIZE - 1)
#define TARGET_PAGE_ALIGN(addr) (((addr) + TARGET_PAGE_SIZE - 1) & TARGET_PAGE_MASK)

// The environment for the Linux kernel consists of
// 1. Command line arguments
// 2. environment variables
// environment variables are structured as paired entries ie name and value in separate entries
// and follow after the command line
#define VIRTUAL_BASE             0x80000000
#define ENVP_BASE                0x2000

#define ENVP_ADDR                ENVP_BASE
#define ENVP_NB_ENTRIES          16
#define ENVP_ENTRY_SIZE          256

#define MALTACORELVID             0x00000420

// Always two command line parameters passed
// 1 = kernel name (eg vmlinux)
// 2 = other command line arguments
#define KERNEL_COMMAND_LINE_ARGS  2
#define DEFAULT_MEMSIZE          (128*1024*1024)

#define WINDOW_KERNELARGS        ENVP_NB_ENTRIES*(4+ENVP_ENTRY_SIZE)

#define ADDRRESS_SPACE_PORT     "mport"
//#define WRITE_BOOT_VECTOR
#define BOOT_VECTOR              0x1fc00000
#define BOOT_MAPPING             0x1e000000
#define BOOT_MAX_SIZE           (1*1024*1024)

typedef struct tableS {
    Uns32 index[ENVP_NB_ENTRIES];
    char strings[ENVP_NB_ENTRIES][ENVP_ENTRY_SIZE];
} tableSS, *tableP;

union {
    char bytes[WINDOW_KERNELARGS];
    tableSS table;
} window_kernelargs;

Uns32 envpaddress = ENVP_ADDR;

ppmAddressSpaceHandle addressSpaceHandle;

// ***********************************************************

char window_bootrom[BOOT_MAX_SIZE];

// ***********************************************************

Uns32 diag = 0;

/*************************************************************
 * Byte Swapping Functions
 *************************************************************/

Bool byteSwap = False;

//
// convert a word for endian
//
static inline Uns32 BSWAP_UNS32(Uns32 p)
{
    if (byteSwap)
        return (((p & 0x000000ff) << 24) |
                ((p & 0x0000ff00) << 8) |
                ((p & 0x00ff0000) >> 8) |
                ((p & 0xff000000) >> 24));
    else
        return p;
}

#define PHYS_TO_VIRT(x) ((x) | ~(Uns32)0x7fffffff)
#define VIRT_TO_PHYS(x) ((x) &  (Uns32)0x7fffffff)

static void write_bootloader_goldfish (Uns32 kernel_entry, Uns32 kernel_args,
                              Uns32 envvp, Uns32 rams)
{
    Uns32 envva = PHYS_TO_VIRT(envvp);

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32(0x0bf00160);                                      /* j 0x1fc00580 */
    *p++ = BSWAP_UNS32(0x00000000);                                      /* nop */


    p = (Uns32 *)&window_bootrom[0x580];
    *p++ =  BSWAP_UNS32(0x3c040000 | ((envva >> 16) & 0xffff));         /* lui a0, high(ENVP_ADDR) */
    *p++ =  BSWAP_UNS32(0x34840000 | (envva & 0xffff));                 /* ori a0, a0, low(ENVP_ADDR) */
    *p++ =  BSWAP_UNS32(0x3c050000 | (rams >> 16));                     /* lui a1, high(ram_size) */
    *p++ =  BSWAP_UNS32(0x34a50000 | (rams & 0xffff));                  /* ori a1, a1, low(ram_size) */

    /* Jump to kernel code */
    *p++ =  BSWAP_UNS32(0x3c1f0000 | ((kernel_entry >> 16) & 0xffff));    /* lui ra, high(kernel_entry) */
    *p++ =  BSWAP_UNS32(0x37ff0000 | (kernel_entry & 0xffff));            /* ori ra, ra, low(kernel_entry) */
    *p++ =  BSWAP_UNS32(0x03e00009);                                      /* jalr $0,ra (in R6: jr ra) */
    *p++ =  BSWAP_UNS32(0x00000000);                                      /* nop */

}

//
// Copy code to setup gprs and BAR registers for calling the Linux kernel
// p is a pointer to an Uns32[] with sufficient space for the code
// Returns pointer to first entry in p past the loaded code
//
static Uns32 *copy_bootloader_linux_start(Uns32 *p , Uns32 kernel_entry, Uns32 kernel_args, Uns32 envva, Uns32 rams) {

    *p++ = BSWAP_UNS32(0x24040000 | kernel_args);                       /* addiu a0, zero, kernel_args*/
    *p++ = BSWAP_UNS32(0x3c1d0000 | (((envva - 64) >> 16) & 0xffff));   /* lui sp, high(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x37bd0000 | ((envva - 64) & 0xffff));           /* ori sp, sp, low(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x3c050000 | ((envva >> 16) & 0xffff));          /* lui a1, high(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x34a50000 | (envva & 0xffff));                  /* ori a1, a1, low(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x3c060000 | (((envva + (kernel_args*4)) >> 16) & 0xffff));  /* lui a2, high(ENVP_ADDR + kernel_args*4) */
    *p++ = BSWAP_UNS32(0x34c60000 | ((envva + (kernel_args*4)) & 0xffff));          /* ori a2, a2, low(ENVP_ADDR + kernel_args*4) */
    *p++ = BSWAP_UNS32(0x3c070000 | (rams >> 16));                      /* lui a3, high(ram_size) */
    *p++ = BSWAP_UNS32(0x34e70000 | (rams & 0xffff));                   /* ori a3, a3, low(ram_size) */

    /* Load BAR registers as done by YAMON */
    *p++ = BSWAP_UNS32(0x3c09b400);                                     /* lui t1, 0xb400 */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c08df00)                           /* lui t0, 0xdf00 */
                    : 0x340800df;                                       /* ori t0, r0, 0x00df */
    *p++ = BSWAP_UNS32(0xad280068);                                     /* sw t0, 0x0068(t1) */

    *p++ = BSWAP_UNS32(0x3c09bbe0);                                     /* lui t1, 0xbbe0 */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c08c000)                           /* lui t0, 0xc000 */
                    : 0x340800c0;                                       /* ori t0, r0, 0x00c0 */
    *p++ = BSWAP_UNS32(0xad280048);                                     /* sw t0, 0x0048(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c084000)                           /* lui t0, 0x4000 */
                    : 0x34080040;                                       /* ori t0, r0, 0x0040 */
    *p++ = BSWAP_UNS32(0xad280050);                                     /* sw t0, 0x0050(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c088000)                           /* lui t0, 0x8000 */
                    : 0x34080080;                                       /* ori t0, r0, 0x0080 */
    *p++ = BSWAP_UNS32(0xad280058);                                     /* sw t0, 0x0058(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c083f00)                           /* lui t0, 0x3f00 */
                    : 0x3408003f;                                       /* ori t0, r0, 0x003f */
    *p++ = BSWAP_UNS32(0xad280060);                                     /* sw t0, 0x0060(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c08c100)                           /* lui t0, 0xc100 */
                    : 0x340800c1;                                       /* ori t0, r0, 0x00c1 */
    *p++ = BSWAP_UNS32(0xad280080);                                     /* sw t0, 0x0080(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c085e00)                           /* lui t0, 0x5e00 */
                    : 0x3408005e;                                       /* ori t0, r0, 0x005e */
    *p++ = BSWAP_UNS32(0xad280088);                                     /* sw t0, 0x0088(t1) */

    /* Jump to kernel code */
    *p++ = BSWAP_UNS32(0x3c1f0000 | ((kernel_entry >> 16) & 0xffff));   /* lui ra, high(kernel_entry) */
    *p++ = BSWAP_UNS32(0x37ff0000 | (kernel_entry & 0xffff));           /* ori ra, ra, low(kernel_entry) */
    *p++ = BSWAP_UNS32(0x03e00009);                                     /* jalr $0,ra (in R6: jr ra)*/
    *p++ = BSWAP_UNS32(0x00000000);                                     /* nop */

    return p;

}

static void write_bootloader (Uns32 kernel_entry, Uns32 kernel_args,
							  Uns32 envpa, Uns32 rams)
{
    Uns32 envva = PHYS_TO_VIRT(envpa);

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32(0x0bf00160);                                      /* j 0x1fc00580 */
    *p++ = BSWAP_UNS32(0x00000000);                                      /* nop */

    /* YAMON service vector */
    p = (Uns32 *)&window_bootrom[0x500];
    *p++ =  BSWAP_UNS32(0xbfc00580);      /* start: */
    *p++ =  BSWAP_UNS32(0xbfc0083c);      /* print_count: */
    *p++ =  BSWAP_UNS32(0xbfc00580);      /* start: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* flush_cache: */
    *p++ =  BSWAP_UNS32(0xbfc00808);      /* print: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_cpu_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unred_cpu_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_ic_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unred_ic_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_esr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unreg_esr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* getchar: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* syscon_read: */

	p = (Uns32 *)&window_bootrom[0x580];
	p = copy_bootloader_linux_start(p , kernel_entry, kernel_args, envva, rams);

    /* YAMON subroutines */
    p = (Uns32 *)&window_bootrom[0x800];
    *p++ =  BSWAP_UNS32(0x03e00009);                                     /* jalr $0,ra (in R6: jr ra)*/
    *p++ =  BSWAP_UNS32(0x24020000);                                     /* li v0,0 */
   /* 808 YAMON print */
    *p++ =  BSWAP_UNS32(0x03e06821);                                     /* move t5,ra */
    *p++ =  BSWAP_UNS32(0x00805821);                                     /* move t3,a0 */
    *p++ =  BSWAP_UNS32(0x00a05021);                                     /* move t2,a1 */
    *p++ =  BSWAP_UNS32(0x91440000);                                     /* lbu a0,0(t2) */
    *p++ =  BSWAP_UNS32(0x254a0001);                                     /* addiu t2,t2,1 */
    *p++ =  BSWAP_UNS32(0x10800005);                                     /* beqz a0,834 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x0ff0021c);                                     /* jal 870 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x08000205);                                     /* j 814 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x01a00009);                                     /* jalr $0,t5 (in R6: jr t5)*/
    *p++ =  BSWAP_UNS32(0x01602021);                                     /* move a0,t3 */
    /* 0x83c YAMON print_count */
    *p++ =  BSWAP_UNS32(0x03e06821);                                     /* move t5,ra */
    *p++ =  BSWAP_UNS32(0x00805821);                                     /* move t3,a0 */
    *p++ =  BSWAP_UNS32(0x00a05021);                                     /* move t2,a1 */
    *p++ =  BSWAP_UNS32(0x00c06021);                                     /* move t4,a2 */
    *p++ =  BSWAP_UNS32(0x91440000);                                     /* lbu a0,0(t2) */
    *p++ =  BSWAP_UNS32(0x0ff0021c);                                     /* jal 870 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x254a0001);                                     /* addiu t2,t2,1 */
    *p++ =  BSWAP_UNS32(0x258cffff);                                     /* addiu t4,t4,-1 */
    *p++ =  BSWAP_UNS32(0x1580fffa);                                     /* bnez t4,84c */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x01a00009);                                     /* jalr $0,t5 (in R6: jr t5)*/
    *p++ =  BSWAP_UNS32(0x01602021);                                     /* move a0,t3 */
    /* 0x870 */
    *p++ =  BSWAP_UNS32(0x3c08b800);                                     /* lui t0,0xb400 */
    *p++ =  BSWAP_UNS32(0x350803f8);                                     /* ori t0,t0,0x3f8 */
    *p++ =  BSWAP_UNS32(0x91090005);                                     /* lbu t1,5(t0) */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x31290040);                                     /* andi t1,t1,0x40 */
    *p++ =  BSWAP_UNS32(0x1120fffc);                                     /* beqz t1,878 <outch+0x8> */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x03e00009);                                     /* jalr $0,ra (in R6: jr ra)*/
    *p++ =  BSWAP_UNS32(0xa1040000);                                     /* sb a0,0(t0) */

    if ((char *)p > &window_bootrom[NUM_ENTRIES(window_bootrom)]) {
        bhmMessage("F", PREFIX, "overflow of window_bootrom buffer");
    }
}

static void write_bootimage (char *imageFile)
{
    FILE *fileout= fopen(imageFile, "w");
    // fail if we cannot open file
    if(!fileout) {
        bhmMessage("E", PREFIX, "Could not write fl file '%s'", imageFile);
    }

    if(DIAG_LOW)
        bhmMessage("I", PREFIX, "Started boot image output to '%s'", imageFile);

    int idx;
    int address = -1;
    Uns32 *p = (Uns32 *)window_bootrom;
    for (idx=0; idx < BOOT_MAX_SIZE; idx++) {
        //printf("idx=%08x address=%08x *p=%08x\n", idx, address, *p);
        // Skip all zero address fields
        if (p[idx] != 0) {
            // if this address is not contiguous - output the address
            if (address++ != idx) {
                fprintf(fileout, "@%08x\n", idx*4);
                address = idx;
            }
            fprintf(fileout, "%08x\n", p[idx]);
        }
    }
    if(DIAG_LOW)
        bhmMessage("I", PREFIX, "Completed boot image output to '%s'", imageFile);

    fclose(fileout);
}

static void read_bootimage (char *bootimage)
{
    FILE *bootimageFile;

    char *pline, line[256];
    int match;
    int byteAddress;
    int dataField;
    Uns32 *p;

    if(!(bootimageFile = fopen(bootimage, "r"))){
        bhmMessage("E", PREFIX, "Error opening bootimage file '%s' for reading", bootimage);
    }

    p = (Uns32 *)window_bootrom;

    while(fgets(line, 256, bootimageFile) != NULL) {

        pline = line;

        // Invalid chars for parsing so skip
        if (*pline=='#' || *pline=='!' || *pline=='>') {
            continue;
        }

        // Is this an address, or data
        if (*pline=='@') {
            pline++;
            match = sscanf(pline, "%8x", &byteAddress);
            if(DIAG_HIGH)
                bhmMessage("I", PREFIX, "    load set 0x%08x", byteAddress);
            if (match == 1) {
                p = (Uns32 *)&window_bootrom[byteAddress & 0x3fffff];
            }
            continue;
        } else {
            match = sscanf(pline, "%8x", &dataField);
            *p++ = dataField;
            byteAddress+=4;
        }
    }
    fclose(bootimageFile);

}

static void prom_set(int index, const char *string, ...)
{
    va_list ap;
    Uns32 table_addr;

    if (index >= ENVP_NB_ENTRIES)
        return;

    if (string == NULL) {
        window_kernelargs.table.index[index] = 0;
        return;
    }

    table_addr = PHYS_TO_VIRT(envpaddress) + (4 * ENVP_NB_ENTRIES) + (index * ENVP_ENTRY_SIZE);

    window_kernelargs.table.index[index] = BSWAP_UNS32(table_addr);

    va_start(ap, string);
    vsnprintf (&window_kernelargs.table.strings[index][0], ENVP_ENTRY_SIZE, string, ap);
    va_end(ap);

    if(DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Kernel Command String, index %d, string '%s' table.index[%d]=%08x, table.strings[%d][]='%s' (%d)",
                                index, string,
                                index, window_kernelargs.table.index[index],
                                index, &window_kernelargs.table.strings[index][0],
                                (int)strlen((const char *)&window_kernelargs.table.strings[index][0])
                                );
}


/* return the size or -1 if error */
int getImageSize(const char *filename)
{
    int fd, size;
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open Image '%s'", filename);
    }
    size = lseek(fd, 0, SEEK_END);
    close(fd);

    if(DIAG_HIGH)
        bhmMessage("I", PREFIX, "Get Image Size: size %d of filename '%s'", size, filename);

    return size;
}

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

/* return the size or -1 if error */
int load_image(const char *filename, Uns32 addr)
{
    Uns32 bytes;
    Uns32 dest = addr;
    char buff[BYTES_PER_ACCESS];
    Int32 fd, size;

    fd = open(filename, O_RDONLY | O_BINARY);
    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open Image %s", filename);
        return 0;
    }
    size = lseek(fd, 0, SEEK_END);
    if(DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Load Image: filename %s %u bytes to load to 0x%08x", filename, size, dest);
    lseek(fd, 0, SEEK_SET);

    bytes = size;
    while (bytes) {
        Uns32 thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;
        thisAccess = read(fd, buff, thisAccess);
        if(!ppmWriteAddressSpace(addressSpaceHandle, (Int64)(Int32)dest, thisAccess, buff)){
            bhmMessage("E", PREFIX, "Load Image: Failed to write %u bytes to 0x%08x", thisAccess, dest);
            return 0;
        }
        dest  += thisAccess;
        bytes -= thisAccess;
    }
    close(fd);
    if(DIAG_LOW)
        bhmMessage("I", PREFIX, "Load Image: filename %s completed (%u bytes loaded)", filename, size);
    return size;
}

Uns32 idWindow = 0;

static void setBoardId(ppmLocalBusHandle idPortHandle) {
	Uns32 boardID;

	if(bhmIntegerAttribute("boardid", &boardID)) {
	    idWindow = BSWAP_UNS32(boardID);
	} else {
	    idWindow = BSWAP_UNS32(MALTACORELVID);
	}

    if(DIAG_LOW) {
        bhmMessage("I", PREFIX, "Set Malta Board Id 0x%x", idWindow);
    }
}

//
// write linux startup code to the indicated address
//
static void write_bootloader_linux_start(Uns32 fixupAddress, Uns32 kernel_entry, Uns32 kernel_args, Uns32 envvp, Uns32 rams) {

    Uns32 envva = PHYS_TO_VIRT(envvp);
    Uns32 kernelStartUp[32*4];

    // Get linux startup code
    Uns32 *p = copy_bootloader_linux_start(kernelStartUp, kernel_entry, kernel_args, envva, rams);

    if (p > &kernelStartUp[NUM_ENTRIES(kernelStartUp)]) {
        bhmMessage("F", PREFIX, "overflow of kernelStartUp buffer");
    }

    // Write linux startup code to indicated memory location
    if(!ppmWriteAddressSpace(addressSpaceHandle, VIRT_TO_PHYS(fixupAddress), sizeof(kernelStartUp), kernelStartUp)){
        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(kernelStartUp),VIRT_TO_PHYS(fixupAddress));
    }

}

static Uns32 createKernelInitialisation(char * kernelfile, Uns32 kernel_entry, Uns32 kernel_low, Uns32 kernel_high, Bool goldfish){

	char initrdfile[BHM_MAX_PATH];
    char rootHDA[128];
    char memsizeString[32];
    Uns32 memsize = DEFAULT_MEMSIZE;	// default is 128MBytes
    Uns32 useInitRD = 0;
    Uns32 useHDABoot = 0;
    Uns32 index = 0;

	// read the base address for ENVP
	if(!bhmUns32Attribute("envpaddress", &envpaddress)){
		if(DIAG_MEDIUM) {
			bhmMessage("W", PREFIX, "Default ENVP Address being used 0x%08x", envpaddress);
		}
	}
    if(DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "ENVP Address 0x%08x", envpaddress);
    }

	if(!bhmUns32Attribute("memsize", &memsize)){
		if(DIAG_MEDIUM) {
			bhmMessage("W", PREFIX, "Default Memory size being used %u", memsize);
		}
	}
    if(DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Memory size %u (0x%08x)", memsize, memsize);
    }
	sprintf(memsizeString, "%u", memsize);

    /* Override page size if requested */
    if(!bhmUns32Attribute("pagebits", &targetPageBits)){
        if(DIAG_MEDIUM) {
            bhmMessage("W", PREFIX, "Default page bits being used %u", targetPageBits);
        }
    }
    if(DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Page bits %d (page size %dKB)", targetPageBits, TARGET_PAGE_SIZE/1024);
    }

	// check for an initrd file
	useInitRD = bhmStringAttribute("initrd", initrdfile, sizeof(initrdfile));
	if(useInitRD && !(*initrdfile)) {
        bhmMessage("W", PREFIX, "Boot Method 'initrd' set to Null");
	    useInitRD = False;
	}

	// check for boot from root on disk
	useHDABoot = bhmStringAttribute("root", rootHDA, sizeof(rootHDA));
    if(useHDABoot && !(*rootHDA)) {
        bhmMessage("W", PREFIX, "Boot Method 'root' set to Null");
        useHDABoot = False;
    }

	if(!(useHDABoot ^ useInitRD)) {
		bhmMessage("E", PREFIX, "Error in boot method specified. "
                                "Must specify one of 'initrd' or 'root' attribute. "
                                "initrd '%s' root '%s'",
                                useInitRD ? initrdfile : "not specified",
                                useHDABoot ? rootHDA : "not specified");
		return 0;
	}

    /***** Create the Kernel Command String */
    if(DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Create kernel Command String");
    }

    char commandString[ENVP_ENTRY_SIZE] = "";

    /* Add any user defined commands */
    bhmStringAttribute("command", commandString, sizeof(commandString));

    /* Build up boot command line */
    if(useHDABoot) {
        sprintf(commandString, "%s root=%s", commandString, rootHDA);
    }

    if (useInitRD) {
        Uns32 size;
        Uns32 initrd_offset;

        initrd_offset = TARGET_PAGE_ALIGN(kernel_high);

        size = load_image(initrdfile, initrd_offset-VIRTUAL_BASE);

        sprintf(commandString, "%s rd_start=0x%08x rd_size=%u", commandString, initrd_offset, size);
    }

    if (!goldfish) {
         /* Store command line.  */
        prom_set(index++, kernelfile);

        prom_set(index++, commandString);

        /* Setup minimum environment variables */
        prom_set(index++, "memsize");
        prom_set(index++, memsizeString);
        prom_set(index++, "modetty0");
        prom_set(index++, "38400n8r");

        /* Terminate kernel command line*/
        prom_set(index, NULL);			// always last

        if(DIAG_MEDIUM) {
            bhmMessage("I", PREFIX, "Kernel Command String Arguments %u", index);
        }

        // copy out to memory
        if(!ppmWriteAddressSpace(addressSpaceHandle, envpaddress, sizeof(window_kernelargs), (char *)&window_kernelargs.bytes)) {
            bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_kernelargs), envpaddress);
            return 0;
        }
    } else {
        if(DIAG_MEDIUM) {
            bhmMessage("I", PREFIX, "Kernel Command String '%s'", commandString);
        }

        // copy out to memory
        if (!ppmWriteAddressSpace(addressSpaceHandle, envpaddress, sizeof(commandString), (char *)&commandString)) {
            bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(commandString), envpaddress);
            return 0;
        }

    }
    if(DIAG_LOW)
        bhmMessage("I", PREFIX, "Initialized Kernel Arguments");
    return memsize;
}


static void getEndian() {
    char endianString[8];
    // check for an endian
    Bool setEndian = bhmStringAttribute("endian", endianString, sizeof(endianString));
    if(setEndian){
        if(!strcmp(endianString, "big")){
            byteSwap = True;
        }
        if(BHM_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX, "Endian attribute found : Set Endian %s", byteSwap ? "BIG" : "LITTLE");
        }
    }
}

int main(int argc, char **argv)
{
	// Model Documentation
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Smart peripheral creates memory initialization for a MIPS32 based Linux kernel boot.");
        ppmDocAddText(doc2_node, "Performs the generation of boot code at the reset vector (virtual address 0xbfc00000) of the MIPS32 processor.");
        ppmDocAddText(doc2_node, "Loads both the Linux kernel and initial ramdisk into memory and patches the boot code to jump to the kernel start.  Initializes the MIPS32 registers and Linux command line");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "None");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "MIPS Malta User Manual. MIPS Boot code reference");
    }
    diag                    = bhmGetDiagnosticLevel();
    bhmEventHandle finished = bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION);

    char kernelfile[BHM_MAX_PATH];
    Uns32 memsize = DEFAULT_MEMSIZE;

    addressSpaceHandle = ppmOpenAddressSpace(ADDRRESS_SPACE_PORT);

    ppmLocalBusHandle idPortHandle = ppmOpenSlaveBusPort(
        "idport",
        &idWindow,
        sizeof(idWindow)
    );

    if(bhmBoolAttribute("disable")){
        bhmMessage("W", PREFIX, "Platform Initialization Disabled");
    } else {

        getEndian();

        if(DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Opening port %s", ADDRRESS_SPACE_PORT);
        }

        if(!addressSpaceHandle) {
            bhmMessage("F", PREFIX, "Failed to open port %s\n", ADDRRESS_SPACE_PORT);
        }

        Bool bootGenerationDisabled = bhmBoolAttribute("disablebootgen");
        if(bootGenerationDisabled){
            bhmMessage("I", PREFIX, "Boot loader code generation disabled");
        }

        // Check to see if we are modelling the goldfish platform
        Bool goldfish = bhmBoolAttribute("goldfish");

        // Always read the boot loader file, if specified
        char bootimage[256];
        char *bootimageP = NULL;
        if (bhmStringAttribute("bootimage", bootimage, sizeof(bootimage))) {
            if(DIAG_LOW) {
                bhmMessage("I", PREFIX, "Loading 'bootimage %s", bootimage);
            }
            read_bootimage(bootimage);
            bootimageP = bootimage;

            // copy out to memory (mapped space)
            if(!ppmWriteAddressSpace(addressSpaceHandle, goldfish ? BOOT_VECTOR : BOOT_MAPPING, sizeof(window_bootrom), window_bootrom)){
                bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_MAPPING);
            }
#ifdef WRITE_BOOT_VECTOR
            if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
            }
#endif
        }


        // Check to see if we are running Linux or want to load a standalone application
        // if stand alone we only need to generate the boot loader
        Bool noLinux = bhmBoolAttribute("nonelinux");

        if(!noLinux) {

            // check for kernel (or if none linux the executable)
            bhmStringAttribute("kernel", kernelfile, sizeof(kernelfile));

            if(DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Opening kernel file '%s'", kernelfile);
            }

            int fd = open(kernelfile, O_RDONLY);
            if (fd < 0) {
                bhmMessage("E", PREFIX, "Could not open kernel file '%s' for reading", kernelfile);
                return 0;
            }

            Uns32 kernel_entry, kernel_low, kernel_high;
            if (read_elf(fd, &kernel_entry, &kernel_low, &kernel_high) < 0) {
                bhmMessage("E", PREFIX, "Failed to extract required data from kernel file %s", kernelfile);
                return 0;
            }
            close(fd);

            if(DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, "Information from kernel '%s': entry 0x%08x, low 0x%08x, high 0x%08x", kernelfile, kernel_entry, kernel_low-VIRTUAL_BASE, kernel_high-VIRTUAL_BASE);
            }

            if(!(memsize = createKernelInitialisation(kernelfile, kernel_entry, kernel_low, kernel_high, goldfish))) {
                return 0;
            }

            if(goldfish){
                write_bootloader_goldfish (kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                    bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
                    return 0;
                }
            } else {
                // no boot loader specified, so write
                if(!bootimageP && !bootGenerationDisabled) {
                    write_bootloader(kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                    // copy out to memory (mapped space)
                    if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_MAPPING, sizeof(window_bootrom), window_bootrom)){
                        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_MAPPING);
                        return 0;
                    }
#ifdef WRITE_BOOT_VECTOR
                    if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
                        return 0;
                    }
#endif
                }

                Uns32 fixupStart = 0;
                if(bhmUns32Attribute("fixuplinuxstart", &fixupStart)) {
                    // this overwrites parts of the ROM image loaded above
                    write_bootloader_linux_start(fixupStart, kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                }

            }

        }

        char bootFL[BHM_MAX_PATH];
        if (bhmStringAttribute("writebootimage", bootFL, sizeof(bootFL))) {
            if(DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Creating boot fl file '%s'", bootFL);
            }
            write_bootimage(bootFL);
        }

    }// disabled

    setBoardId(idPortHandle);// This will write the board ID into the window_bootrom

    if(addressSpaceHandle) {
        ppmCloseAddressSpace(addressSpaceHandle);
    }

    /****************************************************************************/


    // now sit and wait for end of simulation
    bhmWaitEvent(finished);
    return 0;
}
