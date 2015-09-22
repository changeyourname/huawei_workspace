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



////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                          Wed Nov  3 14:26:13 2010
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "icm/icmCpuManager.h"

void createPlatform(char *program) {

////////////////////////////////////////////////////////////////////////////////

    icmInitPlatform(ICM_VERSION, ICM_VERBOSE | ICM_STOP_ON_CTRLC, 0, 0, "BareMetalRisc32");

////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP bus_b = icmNewBus( "bus_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                                Processor cpu
////////////////////////////////////////////////////////////////////////////////

    icmAttrListP cpu_attr = icmNewAttrList();

    icmAddDoubleAttr(cpu_attr, "mips", 100.000000);

    icmProcessorP cpu_c = icmNewProcessor(
        "cpu",          // name
        "risc32",       // type
        0,              // cpuId
        0x0,            // flags
        32,             // address bits
        MORPHER_FILE,   // model
        "modelAttrs",   // symbol
        0x0,            // procAttrs
        cpu_attr,       // attrlist
        0,              // semihost file
        0               // semihost symbol
    );

    icmConnectProcessorBusses( cpu_c, bus_b, bus_b );


////////////////////////////////////////////////////////////////////////////////
//                                 Memory mem
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP mem_m = icmNewMemory("mem_m", 0x7, 0xffffffff);

    icmConnectMemoryToBus(bus_b, "sp1", mem_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Load Memory
////////////////////////////////////////////////////////////////////////////////

    int data, addr;
    char line[256];
    char *pline = line;
    int reset;

    FILE *fp = fopen(program, "r");
    if (fp == NULL) {
        printf("error cannot open testcase.obj");
        exit(1);
    }
    while (fgets(pline, 256, fp)) {
        if(sscanf(pline, "%08x: %08x", &addr, &data) == 2) {
            icmWriteProcessorMemory(cpu_c,  // processor
                                    addr,   // memory address
                                    &data,  // data buffer of data to write
                                    4);     // number of bytes to write

        } else if (sscanf(pline, "_start: %08x", &reset) == 1) {

        } else {
            printf("error cannot parse %s", pline);
            exit(1);
        }

    }

    icmSetPC(cpu_c, reset);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    if (argc!=2) {
        icmPrintf("Usage: %s program.risc32\n", argv[0]);
    }
    // the constructor
    createPlatform(argv[1]);

    // run till the end
    icmSimulatePlatform();

    // finish and clean up
    icmTerminate();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
