/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "icm/icmCpuManager.h"

// an arbitary limit to terminate infinite loops
#define INSTRUCTION_RUN_LIMIT  80

//
// ISPRAM & DSPRAM memory (when externally implemented)
//
#define ISPRAMSIZE 0x4000
#define DSPRAMSIZE 0x4000
static Uns8 ISPRAM[ISPRAMSIZE];
static Uns8 DSPRAM[DSPRAMSIZE];

//
// ISPRAM read callback
//
static ICM_MEM_READ_FN(readISPRAM) {

    assert(address+bytes < ISPRAMSIZE);

    void *ptr    = &ISPRAM[address];
    Uns32 result = *(Uns32*)ptr;

    if(processor) {
        icmPrintf(
            "readISPRAM  0x%08x %u => 0x%08x\n",
            (Uns32)address, bytes, result
        );
    }

    *(Uns32*)value = result;
}

//
// ISPRAM write callback
//
static ICM_MEM_WRITE_FN(writeISPRAM) {

    assert(address+bytes < ISPRAMSIZE);

    void *ptr    = &ISPRAM[address];
    Uns32 result = *(Uns32*)value;

    if(processor) {
        icmPrintf(
            "writeISPRAM 0x%08x %u <= 0x%08x\n",
            (Uns32)address, bytes, result
        );
    }

    *(Uns32*)ptr = result;
}

//
// DSPRAM read callback
//
static ICM_MEM_READ_FN(readDSPRAM) {

    assert(address+bytes < DSPRAMSIZE);

    void *ptr    = &DSPRAM[address];
    Uns32 result = *(Uns32*)ptr;

    if(processor) {
        icmPrintf(
            "readDSPRAM  0x%08x %u => 0x%08x\n",
            (Uns32)address, bytes, result
        );
    }

    *(Uns32*)value = result;
}

//
// DSPRAM write callback
//
static ICM_MEM_WRITE_FN(writeDSPRAM) {

    assert(address+bytes < DSPRAMSIZE);

    void *ptr    = &DSPRAM[address];
    Uns32 result = *(Uns32*)value;

    if(processor) {
        icmPrintf(
            "writeDSPRAM 0x%08x %u <= 0x%08x\n",
            (Uns32)address, bytes, result
        );
    }

    *(Uns32*)ptr = result;
}

//
// Scheduler loop
//
static Bool simulate(icmProcessorP processor, Uns64 instructions) {

    switch(icmSimulate(processor, instructions)) {

        case ICM_SR_SCHED:
        case ICM_SR_HALT:
            return True;

        default:
            // end simulation
            return False;
    }
}

const char *vendors[] = {"mips.com", "mips.ovpworld.org", 0};
#define NUMBER_VENDORS 2

//
// Select vendor to use for models
//
static const char *selectVendor() {
    Uns32 i, index = 0;

    // Select default model vendor to be used to load model
    char *runtime = getenv("IMPERAS_RUNTIME");
    if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
        index++; // start from next vendor
    } else {
        ;        // leave default index
    }
    for(i=0;i<NUMBER_VENDORS;i++){
        const char *mipsModel    = icmTryVlnvString(NULL, vendors[index], "processor", "mips32", "1.0", "model");
        const char *mipsSemihost = icmTryVlnvString(NULL, vendors[index], "semihosting", "mips32Newlib", "1.0", "model");
        if(mipsModel && mipsSemihost) {
            return vendors[index];
        }
        // Select next in list, if zero back to first
        if (!vendors[++index]) index = 0;
    }

    icmMessage("F", "MODEL", "No Model Available");
    // Will never reach here
    return NULL;
}

#define MIN_ARGS    7
#define MAX_ARGS    9
#define PROC_ARG    4
#define ENDIAN_ARG  5
#define MODE_ARG    6
#define TRACE_ARG   7

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    Bool trace     = False;
    Bool traceRegs = False;
    Bool bigEndian = False;
    Bool external  = False;

    const char *cpuType = NULL;

    if ((argc < MIN_ARGS) || (argc > MAX_ARGS)) {
        icmPrintf("Wrong number of args (%d)\n", argc);
        icmPrintf("usage: %s <application mem init file> <SPRAM file 1> <SPRAM file 2> <processor> <endian> <mode> [<dbglevel>]\n", argv[0]);
        icmPrintf("where: <application file>   : application file loaded\n"
                  "       <SPRAM file 1>       : SPRAM code file 1\n"
                  "       <SPRAM file 2>       : SPRAM code file 2\n"
                  "       <processor variant>  : variant to configure the model e.g. 34Kc\n"
                  "       <endian>             : L or B set Little or Big Endian\n"
                 "        <mode>               : I (internal implement) or X (external implement)\n"
                  "       <dbglevel>           : set bit 1/2 to enable instruction/register trace\n");
        return -1;
    }

    if (argc > PROC_ARG) {
        cpuType = argv[PROC_ARG];
        icmPrintf("\nProcessor %s\n", cpuType);
    }
    if (argc > ENDIAN_ARG) {
        bigEndian = (argv[ENDIAN_ARG][0] == 'B');
    }
    if (argc > MODE_ARG) {
        external = (argv[MODE_ARG][0] == 'X');
    }

    if (argc > TRACE_ARG) {
        trace     = atoi(argv[TRACE_ARG]) & 1;
        traceRegs = atoi(argv[TRACE_ARG]) & 2;
        icmPrintf("Tracing Instructions %s Registers %s\n",
            trace     ? "ON" : "-",
            traceRegs ? "ON" : "-"
        );
    }

    //////////////////////////////////////////////////////////////////////////////
    // Platform Creation Starts here

    //
    // initialize CpuManager
    //
    icmInitPlatform(ICM_VERSION, 0, 0, 0, "platform");

    //
    // Setup the configuration attributes for the simulator
    //
    Uns32 icmAttrs = ICM_ATTR_SIMEX  // the processor model handles simulated exceptions
                     | ICM_ATTR_TRACE_ICOUNT
                     | (trace ? ICM_ATTR_TRACE : 0)
                     | (traceRegs ? ICM_ATTR_TRACE_REGS : 0);

    //
    // Setup the configuration attributes for the MIPS model
    //
    icmAttrListP userAttrs = icmNewAttrList();

    icmAddStringAttr(userAttrs, "endian", bigEndian ? "big" : "little");    // setup endianess

    // Select the processor configuration
    icmAddStringAttr(userAttrs, "variant", cpuType);

    // Enable vectored interrupts
    icmAddStringAttr(userAttrs, "vectoredinterrupt", "enable");

    // Enable MIPS-format trace
    icmAddStringAttr(userAttrs, "MIPS_TRACE", "enable");

    // Enable ISPRAM
    icmAddUns64Attr(userAttrs, "configISP", 1);

    // Enable DSPRAM
    icmAddUns64Attr(userAttrs, "configDSP", 1);

    // Select processor model from library
    const char *vendor    = selectVendor();
    const char *modelFile = icmGetVlnvString(NULL, vendor, "processor", "mips32", "1.0", "model");

    // select semihost file from library
    const char *semihostFile = icmGetVlnvString(NULL, vendor, "semihosting", "mips32Newlib", "1.0", "model");

    //
    // create a processor
    //
    icmProcessorP processor = icmNewProcessor(
        "mips32",       // processor name
        "mips32",       // processor type
        0,              // processor cpuId
        0x10000000,     // enable SPRAM debug
        32,             // address bits
        modelFile,      // model file
        "modelAttrs",   // morpher attributes
        icmAttrs,       // processor attributes
        userAttrs,      // user attribute list
        semihostFile,   // semihosting file name
        "modelAttrs"    // semihosting attribute symbol
    );

    if(!external) {

        icmPrintf("****************************\n");
        icmPrintf("*      INTERNAL SPRAM      *\n");
        icmPrintf("****************************\n");

    } else {

        icmPrintf("****************************\n");
        icmPrintf("*      EXTERNAL SPRAM      *\n");
        icmPrintf("****************************\n");

        // create ISPRAM & DSPRAM busses
        icmBusP ISPRAMBus = icmNewBus("ISPRAMBus", 32);
        icmBusP DSPRAMBus = icmNewBus("DSPRAMBus", 32);

        // map ISPRAM memory using callbacks
        icmMapExternalMemory (
            ISPRAMBus,
            "ISPRAM_Memory",
            ICM_PRIV_RWX,
            0,
            (Uns32)-1,
            readISPRAM,
            writeISPRAM,
            0
        );

        // map DSPRAM memory using callbacks
        icmMapExternalMemory (
            DSPRAMBus,
            "DSPRAM_Memory",
            ICM_PRIV_RWX,
            0,
            (Uns32)-1,
            readDSPRAM,
            writeDSPRAM,
            0
        );

        // external monitor SPRAM
        icmConnectProcessorBusByName(processor, "ISPRAM", ISPRAMBus);
        icmConnectProcessorBusByName(processor, "DSPRAM", DSPRAMBus);
    }

    // load the processor object files at PHYSICAL address (not into SPRAM)
    if (!icmLoadProcessorMemory(processor, argv[1], ICM_LOAD_DEFAULT, False, True)) {
        icmPrintf("Fault loading Programs\n");
        return -1;
    }

    icmSimulationStarting();

    // parameters for SPRAM configuration
    Uns32       index;
    Bool        enable;
    Uns32       size;
    Uns64       base;
    Uns32       offset;
    const char *file;
    Uns32       _unused;

    // configure ISPRAM region 0 (initially enabled, address 0x22000)
    index   = 0;        icmWriteReg(processor, "ISPRAM_INDEX",  &index);
    enable  = True;     icmWriteReg(processor, "ISPRAM_ENABLE", &enable);
    size    = 1;        icmWriteReg(processor, "ISPRAM_SIZE",   &size);
    base    = 0x22000;  icmWriteReg(processor, "ISPRAM_BASE",   &base);
    offset  = 0;        icmWriteReg(processor, "ISPRAM_OFFSET", &offset);
    file    = argv[2];  icmWriteReg(processor, "ISPRAM_FILE",   &file);
    _unused = 0;        icmWriteReg(processor, "ISPRAM_WRITE",  &_unused);

    // configure ISPRAM region 1
    index   = 1;        icmWriteReg(processor, "ISPRAM_INDEX",  &index);
    enable  = False;    icmWriteReg(processor, "ISPRAM_ENABLE", &enable);
    size    = 1;        icmWriteReg(processor, "ISPRAM_SIZE",   &size);
    base    = 0;        icmWriteReg(processor, "ISPRAM_BASE",   &base);
    offset  = 1<<12;    icmWriteReg(processor, "ISPRAM_OFFSET", &offset);
    file    = argv[3];  icmWriteReg(processor, "ISPRAM_FILE",   &file);
    _unused = 0;        icmWriteReg(processor, "ISPRAM_WRITE",  &_unused);

    // configure DSPRAM region 0
    index   = 0;        icmWriteReg(processor, "DSPRAM_INDEX",  &index);
    enable  = False;    icmWriteReg(processor, "DSPRAM_ENABLE", &enable);
    size    = 2;        icmWriteReg(processor, "DSPRAM_SIZE",   &size);
    base    = 0;        icmWriteReg(processor, "DSPRAM_BASE",   &base);
    offset  = 0;        icmWriteReg(processor, "DSPRAM_OFFSET", &offset);
    _unused = 0;        icmWriteReg(processor, "DSPRAM_WRITE",  &_unused);

    // configure DSPRAM region 1
    index   = 1;        icmWriteReg(processor, "DSPRAM_INDEX",  &index);
    enable  = False;    icmWriteReg(processor, "DSPRAM_ENABLE", &enable);
    size    = 2;        icmWriteReg(processor, "DSPRAM_SIZE",   &size);
    base    = 0;        icmWriteReg(processor, "DSPRAM_BASE",   &base);
    offset  = 2<<12;    icmWriteReg(processor, "DSPRAM_OFFSET", &offset);
    _unused = 0;        icmWriteReg(processor, "DSPRAM_WRITE",  &_unused);

    ////////////////////////////////////////////////////////////////////////////
    // DO A SIMULATION RUN
    ////////////////////////////////////////////////////////////////////////////

    simulate(processor, INSTRUCTION_RUN_LIMIT);

    // show final configuration of all ISPRAM regions
    for(index=0; index<2; index++) {

        // select ISPRAM region
        icmWriteReg(processor, "ISPRAM_INDEX", &index);
        icmWriteReg(processor, "ISPRAM_READ",  &_unused);

        // get final configuration of ISPRAM region
        icmReadReg(processor, "ISPRAM_INDEX",  &index);
        icmReadReg(processor, "ISPRAM_ENABLE", &enable);
        icmReadReg(processor, "ISPRAM_SIZE",   &size);
        icmReadReg(processor, "ISPRAM_BASE",   &base);
        icmReadReg(processor, "ISPRAM_OFFSET", &offset);

        // show final configuration of ISPRAM region
        icmPrintf(
            "ISPRAM region %u base=0x%08x size=%u SPRAM_offset=0x%08x enable=%u\n",
            index, (Uns32)base, size, offset, enable
        );
    }

    // show final configuration of all DSPRAM regions
    for(index=0; index<2; index++) {

        // select DSPRAM region
        icmWriteReg(processor, "DSPRAM_INDEX", &index);
        icmWriteReg(processor, "DSPRAM_READ",  &_unused);

        // get final configuration of ISPRAM region
        icmReadReg(processor, "DSPRAM_INDEX",  &index);
        icmReadReg(processor, "DSPRAM_ENABLE", &enable);
        icmReadReg(processor, "DSPRAM_SIZE",   &size);
        icmReadReg(processor, "DSPRAM_BASE",   &base);
        icmReadReg(processor, "DSPRAM_OFFSET", &offset);

        // show final configuration of ISPRAM region
        icmPrintf(
            "DSPRAM region %u base=0x%08x size=%u SPRAM_offset=0x%08x enable=%u\n",
            index, (Uns32)base, size, offset, enable
        );
    }

    icmTerminate();

    return 0;
}
