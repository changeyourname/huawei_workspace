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
//                              Version 99999999
//
////////////////////////////////////////////////////////////////////////////////


// This file constructs the platform according to TCL script.
// This file should NOT need to be edited.

////////////////////////////////////////////////////////////////////////////////

void platformConstructor(void) {

    icmInitAttrs ignoreTrustZone_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, ignoreTrustZone_attrs, 0, 0, "ignoreTrustZone");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc2_node, "\nThis platform implements an Arm Cortex-A9UP processor with some memory and a UART.\n\nOnly address bits 31:0 are used in the platform, so no TrustZone security \ninformation is included in bus transactions and all addresses are accessible in \nboth secure and non-secure modes.\n");
    }
    icmSetPlatformStatus(ICM_UNSET,ICM_BAREMETAL,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus pBus
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_b = icmNewBus( "pBus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Processor cpu
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-A9UP");
    icmAddStringAttr(cpu_attrList, "compatibility", "nopSVC");
    icmAddDoubleAttr(cpu_attrList, "mips", 100.000000);
    icmAddStringAttr(cpu_attrList, "endian", "little");

    const char *armNewlib_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "armNewlib"         ,    // name
        0                   ,    // version
        "model"                  // model
    );
    icmNewProcAttrs cpu_attrs = ICM_ATTR_DEFAULT;


    handles.cpu_c = icmNewProcessor(
        "cpu"               ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        cpu_path            ,   // model
        0, 
        cpu_attrs           ,   // procAttrs
        cpu_attrList        ,   // attrlist
        armNewlib_0_path    ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart0
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_attrList = icmNewAttrList();
    icmAddStringAttr(uart0_attrList, "outfile", "uart0.log");

    handles.uart0_p = icmNewPSE(
        "uart0"             ,   // name
        uart0_path          ,   // model
        uart0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_p, handles.pBus_b, "bport1", 0, 0x10000000, 0x10000fff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.pBus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.pBus_b );

////////////////////////////////////////////////////////////////////////////////
//                                 Memory ram0
////////////////////////////////////////////////////////////////////////////////

    handles.ram0_m = icmNewMemory("ram0", 0x7, 0x1fffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.ram0_m, 0x0);
}
