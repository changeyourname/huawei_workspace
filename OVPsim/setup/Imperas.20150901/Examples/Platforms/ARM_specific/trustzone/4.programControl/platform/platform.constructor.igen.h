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

    icmInitAttrs programControl_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, programControl_attrs, 0, 0, "programControl");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc2_node, "\nThis platform implements an Arm Cortex-A9UP processor with some memory and a UART.\n\nAddress bits 40:0 are used in the platform, so TrustZone security information is \nincluded in bus transactions. A DynamicBridge and TrustZone Protection Controller\nare added to allow program control of non-secure accesses to the UART.\n");
    }
    icmSetPlatformStatus(ICM_UNSET,ICM_BAREMETAL,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus tzBus
////////////////////////////////////////////////////////////////////////////////


    handles.tzBus_b = icmNewBus( "tzBus", 41);

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
        41                  ,   // address bits
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

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart0NS
////////////////////////////////////////////////////////////////////////////////


    const char *uart0NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0NS_attrList = icmNewAttrList();
    icmAddUns64Attr(uart0NS_attrList, "mpLoAddress", 0x10000000LL);
    icmAddUns64Attr(uart0NS_attrList, "spLoAddress", 0x10010000000LL);
    icmAddUns64Attr(uart0NS_attrList, "portSize", 0x1000LL);

    handles.uart0NS_p = icmNewPSE(
        "uart0NS"           ,   // name
        uart0NS_path        ,   // model
        uart0NS_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.uart0NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE tzpc
////////////////////////////////////////////////////////////////////////////////


    const char *tzpc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TzpcBP147"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP tzpc_attrList = icmNewAttrList();

    handles.tzpc_p = icmNewPSE(
        "tzpc"              ,   // name
        tzpc_path           ,   // model
        tzpc_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.tzpc_p, handles.pBus_b, "bport1", 0, 0x10001000, 0x10001fff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.tzBus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.tzBus_b );

////////////////////////////////////////////////////////////////////////////////
//                                 Memory ram0
////////////////////////////////////////////////////////////////////////////////

    handles.ram0_m = icmNewMemory("ram0", 0x7, 0x1fffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.ram0_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge secure
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "secure", "sp", "mp", 0x0, 0xffffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge ram0NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "ram0NS", "sp", "mp", 0x0, 0x1fffff, 0x10000000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge tzpcNS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "tzpcNS", "sp", "mp", 0x10001000, 0x10001fff, 0x10010001000ULL);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.tzpcdecprot0_0_n = icmNewNet("tzpcdecprot0_0" );

    icmConnectPSENet( handles.uart0NS_p, handles.tzpcdecprot0_0_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_0_n, "TZPCDECPROT0_0", 0);
}
