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


#include "icm/icmCpuManager.h"

// Platform components referenced in main()
struct handlesS {
    icmProcessorP  processor;
} handles;

void createPlatform(void) {

/////////////////////////////////////////////////////////////////////////

    icmInitPlatform(ICM_VERSION, 0, 0, 9999, "platform");

    icmSetSimulationTimeSlice(0.001000);


/////////////////////////////////////////////////////////////////////////
//                      Bus   INSTANCES
/////////////////////////////////////////////////////////////////////////

    icmBusP icmBusP_1 = icmNewBus( "mainBus", 32);

    icmBusP icmBusP_2 = icmNewBus( "intermediateBus", 4);

    icmBusP icmBusP_3 = icmNewBus( "peripheralBus", 4);

/////////////////////////////////////////////////////////////////////////
//                Processor   INSTANCE   cpu1
/////////////////////////////////////////////////////////////////////////

    icmAttrListP icmAttrListP_4 = icmNewAttrList();
        icmAddDoubleAttr(icmAttrListP_4, "mips", 100);

    const char * string_5 = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "ovpworld.org",    // vendor
        "processor",    // library
        "or1k",    // name
        "1.0",    // version
        "model"     // model
    );

    const char * string_6 = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "ovpworld.org",    // vendor
        "semihosting",    // library
        "or1kNewlib",    // name
        "1.0",    // version
        "model"     // model
    );

    handles.processor = icmNewProcessor(
        "cpu1",   // name
        "or1k",   // type
        0,   // cpuId
        0x0, // flags
         32,   // address bits
        string_5,   // model
        "modelAttrs",   // symbol
        0x40,   // procAttrs
        icmAttrListP_4,   // attrlist
        string_6,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectProcessorBusses( handles.processor, icmBusP_1, icmBusP_1 );


/////////////////////////////////////////////////////////////////////////
//         Peripheral (PSE)   INSTANCE   Simple32_1
/////////////////////////////////////////////////////////////////////////

    icmAttrListP icmAttrListP_8 = icmNewAttrList();

    const char * string_9 = "peripheral/pse.pse";

    icmPseP icmPseP_10 = icmNewPSE(
        "Simple32_1",   // name
        string_9,   // model
        icmAttrListP_8,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( icmPseP_10, icmBusP_3, "sp1", 0, 0x0, 0xf);


/////////////////////////////////////////////////////////////////////////
//                      MMC   INSTANCE   swap1
/////////////////////////////////////////////////////////////////////////

    icmAttrListP icmAttrListP_11 = icmNewAttrList();

    const char * string_12 = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "ovpworld.org",    // vendor
        "mmc",    // library
        "endianSwap",    // name
        "1.0",    // version
        "model"     // model
    );

    icmMmcP icmMmcP_13 = icmNewMMC(
        "swap1",   // name
        string_12,       // model
        "modelAttrs",   // model
        icmAttrListP_11,       // attrlist
        0,        // handle
        0);

    icmConnectMMCBus(icmMmcP_13, icmBusP_2, "sp1", 0);

    icmConnectMMCBus(icmMmcP_13, icmBusP_3, "mp1", 1);


/////////////////////////////////////////////////////////////////////////
//                   Memory   INSTANCE   prog
/////////////////////////////////////////////////////////////////////////

    icmMemoryP icmMemoryP_14 = icmNewMemory("prog", 0x7, 0xffff);

    icmConnectMemoryToBus( icmBusP_1, "sp1", icmMemoryP_14, 0x0);


/////////////////////////////////////////////////////////////////////////
//                   Memory   INSTANCE   stack
/////////////////////////////////////////////////////////////////////////

    icmMemoryP icmMemoryP_15 = icmNewMemory("stack", 0x7, 0xffff);

    icmConnectMemoryToBus( icmBusP_1, "sp1", icmMemoryP_15, 0xffff0000);


/////////////////////////////////////////////////////////////////////////
//                   Bridge   INSTANCE
/////////////////////////////////////////////////////////////////////////

    icmNewBusBridge(icmBusP_1, icmBusP_2, "bridge1", "decoder_sp1", "decoder_mp1_sp1", 0x0, 0xf, 0x80000000);

}

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//                              M A I N                                //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    // the constructor
    createPlatform();

    // load fixed application
    icmLoadProcessorMemory(handles.processor, "application/application.OR1K.elf", ICM_LOAD_DEFAULT, False, True);

    // run till the end
    icmSimulatePlatform();
    icmTerminate();
    return 0;
}

/////////////////////////////////////////////////////////////////////////
