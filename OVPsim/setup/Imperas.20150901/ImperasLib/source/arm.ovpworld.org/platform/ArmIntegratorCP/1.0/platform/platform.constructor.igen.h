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
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////


// This file constructs the platform according to TCL script.
// This file should NOT need to be edited.

////////////////////////////////////////////////////////////////////////////////

void platformConstructor(void) {

    icmInitAttrs ArmIntegratorCP_attrs = ICM_ENABLE_IMPERAS_INTERCEPTS|ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, ArmIntegratorCP_attrs, 0, 0, "ArmIntegratorCP");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "This platform models the ARM INTEGRATOR CP development board.\nIt provides the peripherals required to boot and run Operating Systems such as Linux or Nucleus.\nThe main processor is an ARM, by default this is an ARM926EJ-S (Linux) but can be overriden; for example ARM920T (Nucleus).");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "No known limitations for executing Linux and Nucleus operating systems.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "ARM Development Boards Integrator CP BaseBoard and Integrator Core Modules ARM9x6");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus1
////////////////////////////////////////////////////////////////////////////////


    handles.bus1_b = icmNewBus( "bus1", 32);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus membus
////////////////////////////////////////////////////////////////////////////////


    handles.membus_b = icmNewBus( "membus", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Processor arm1
////////////////////////////////////////////////////////////////////////////////


    const char *arm1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP arm1_attrList = icmNewAttrList();
    icmAddStringAttr(arm1_attrList, "variant", "ARM926EJ-S");
    icmAddStringAttr(arm1_attrList, "compatibility", "ISA");
    icmAddUns64Attr(arm1_attrList, "showHiddenRegs", 0LL);
    icmAddDoubleAttr(arm1_attrList, "mips", 200.000000);
    icmAddStringAttr(arm1_attrList, "endian", "little");
    icmNewProcAttrs arm1_attrs = ICM_ATTR_SIMEX;


    handles.arm1_c = icmNewProcessor(
        "arm1"              ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        arm1_path           ,   // model
        0, 
        arm1_attrs          ,   // procAttrs
        arm1_attrList       ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                   PSE cm
////////////////////////////////////////////////////////////////////////////////


    const char *cm_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CoreModule9x6"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cm_attrList = icmNewAttrList();

    handles.cm_p = icmNewPSE(
        "cm"                ,   // name
        cm_path             ,   // model
        cm_attrList         ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cm_p, handles.bus1_b, "bport1", 0, 0x10000000, 0x10000fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE pic1
////////////////////////////////////////////////////////////////////////////////


    const char *pic1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IntICP"            ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP pic1_attrList = icmNewAttrList();

    handles.pic1_p = icmNewPSE(
        "pic1"              ,   // name
        pic1_path           ,   // model
        pic1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pic1_p, handles.bus1_b, "bport1", 0, 0x14000000, 0x14000fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE pic2
////////////////////////////////////////////////////////////////////////////////


    const char *pic2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IntICP"            ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP pic2_attrList = icmNewAttrList();

    handles.pic2_p = icmNewPSE(
        "pic2"              ,   // name
        pic2_path           ,   // model
        pic2_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pic2_p, handles.bus1_b, "bport1", 0, 0xca000000, 0xca000fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE ethlan
////////////////////////////////////////////////////////////////////////////////


    const char *ethlan_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "smsc.ovpworld.org" ,    // vendor
        0                   ,    // library
        "LAN9118"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ethlan_attrList = icmNewAttrList();

    handles.ethlan_p = icmNewPSE(
        "ethlan"            ,   // name
        ethlan_path         ,   // model
        ethlan_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ethlan_p, handles.bus1_b, "bport1", 0, 0xc8000000, 0xc8000fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE pit
////////////////////////////////////////////////////////////////////////////////


    const char *pit_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IcpCounterTimer"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP pit_attrList = icmNewAttrList();

    handles.pit_p = icmNewPSE(
        "pit"               ,   // name
        pit_path            ,   // model
        pit_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pit_p, handles.bus1_b, "bport1", 0, 0x13000000, 0x13000fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE icp
////////////////////////////////////////////////////////////////////////////////


    const char *icp_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IcpControl"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP icp_attrList = icmNewAttrList();

    handles.icp_p = icmNewPSE(
        "icp"               ,   // name
        icp_path            ,   // model
        icp_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.icp_p, handles.bus1_b, "bport1", 0, 0xcb000000, 0xcb00000f);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE ld1
////////////////////////////////////////////////////////////////////////////////


    const char *ld1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DebugLedAndDipSwitch",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ld1_attrList = icmNewAttrList();

    handles.ld1_p = icmNewPSE(
        "ld1"               ,   // name
        ld1_path            ,   // model
        ld1_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ld1_p, handles.bus1_b, "bport1", 0, 0x1a000000, 0x1a000fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE kb1
////////////////////////////////////////////////////////////////////////////////


    const char *kb1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP kb1_attrList = icmNewAttrList();
    icmAddUns64Attr(kb1_attrList, "isMouse", 0LL);
    icmAddUns64Attr(kb1_attrList, "grabDisable", 0LL);

    handles.kb1_p = icmNewPSE(
        "kb1"               ,   // name
        kb1_path            ,   // model
        kb1_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.kb1_p, handles.bus1_b, "bport1", 0, 0x18000000, 0x18000fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE ms1
////////////////////////////////////////////////////////////////////////////////


    const char *ms1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ms1_attrList = icmNewAttrList();
    icmAddUns64Attr(ms1_attrList, "isMouse", 1LL);
    icmAddUns64Attr(ms1_attrList, "grabDisable", 1LL);

    handles.ms1_p = icmNewPSE(
        "ms1"               ,   // name
        ms1_path            ,   // model
        ms1_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ms1_p, handles.bus1_b, "bport1", 0, 0x19000000, 0x19000fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE rtc
////////////////////////////////////////////////////////////////////////////////


    const char *rtc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc_attrList = icmNewAttrList();

    handles.rtc_p = icmNewPSE(
        "rtc"               ,   // name
        rtc_path            ,   // model
        rtc_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc_p, handles.bus1_b, "bport1", 0, 0x15000000, 0x15000fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart1
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_attrList = icmNewAttrList();
    icmAddStringAttr(uart1_attrList, "variant", "ARM");
    icmAddStringAttr(uart1_attrList, "outfile", "uart1.log");
    icmAddUns64Attr(uart1_attrList, "finishOnDisconnect", 1LL);

    handles.uart1_p = icmNewPSE(
        "uart1"             ,   // name
        uart1_path          ,   // model
        uart1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_p, handles.bus1_b, "bport1", 0, 0x16000000, 0x16000fff);
    icmSetPSEdiagnosticLevel(handles.uart1_p, 1);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart2
////////////////////////////////////////////////////////////////////////////////


    const char *uart2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart2_attrList = icmNewAttrList();
    icmAddStringAttr(uart2_attrList, "variant", "ARM");
    icmAddStringAttr(uart2_attrList, "outfile", "uart2.log");
    icmAddUns64Attr(uart2_attrList, "finishOnDisconnect", 1LL);

    handles.uart2_p = icmNewPSE(
        "uart2"             ,   // name
        uart2_path          ,   // model
        uart2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_p, handles.bus1_b, "bport1", 0, 0x17000000, 0x17000fff);
    icmSetPSEdiagnosticLevel(handles.uart2_p, 1);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE mmci
////////////////////////////////////////////////////////////////////////////////


    const char *mmci_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mmci_attrList = icmNewAttrList();

    handles.mmci_p = icmNewPSE(
        "mmci"              ,   // name
        mmci_path           ,   // model
        mmci_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mmci_p, handles.bus1_b, "bport1", 0, 0x1c000000, 0x1c000fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE lcd
////////////////////////////////////////////////////////////////////////////////


    const char *lcd_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP lcd_attrList = icmNewAttrList();
    icmAddUns64Attr(lcd_attrList, "busOffset", 0x80000000LL);
    icmAddUns64Attr(lcd_attrList, "scanDelay", 50000LL);

    handles.lcd_p = icmNewPSE(
        "lcd"               ,   // name
        lcd_path            ,   // model
        lcd_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.lcd_p, handles.bus1_b, "bport1", 0, 0xc0000000, 0xc0000fff);

    icmConnectPSEBus( handles.lcd_p, handles.membus_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                               PSE smartLoader
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_attrList = icmNewAttrList();

    handles.smartLoader_p = icmNewPSE(
        "smartLoader"       ,   // name
        smartLoader_path    ,   // model
        smartLoader_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_p, handles.bus1_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectProcessorBusByName( handles.arm1_c, "INSTRUCTION", handles.bus1_b );

    icmConnectProcessorBusByName( handles.arm1_c, "DATA", handles.bus1_b );

////////////////////////////////////////////////////////////////////////////////
//                                 Memory ram1
////////////////////////////////////////////////////////////////////////////////

    handles.ram1_m = icmNewMemory("ram1", 0x7, 0x7ffffff);


    icmConnectMemoryToBus( handles.membus_b, "sp1", handles.ram1_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Memory ambaDummy
////////////////////////////////////////////////////////////////////////////////

    handles.ambaDummy_m = icmNewMemory("ambaDummy", 0x7, 0xfff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.ambaDummy_m, 0x1d000000);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ram1Bridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.membus_b, "ram1Bridge", "sp", "mp", 0x0, 0x7ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ram2Bridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.membus_b, "ram2Bridge", "sp1", "mp", 0x0, 0x7ffffff, 0x80000000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.irq_n = icmNewNet("irq" );

    icmConnectProcessorNet( handles.arm1_c, handles.irq_n, "irq", 0);

    icmConnectPSENet( handles.pic1_p, handles.irq_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.fiq_n = icmNewNet("fiq" );

    icmConnectProcessorNet( handles.arm1_c, handles.fiq_n, "fiq", 0);

    icmConnectPSENet( handles.pic1_p, handles.fiq_n, "fiq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir1_n = icmNewNet("ir1" );

    icmConnectPSENet( handles.pic1_p, handles.ir1_n, "ir1", 0);

    icmConnectPSENet( handles.uart1_p, handles.ir1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir2_n = icmNewNet("ir2" );

    icmConnectPSENet( handles.pic1_p, handles.ir2_n, "ir2", 0);

    icmConnectPSENet( handles.uart2_p, handles.ir2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir3_n = icmNewNet("ir3" );

    icmConnectPSENet( handles.pic1_p, handles.ir3_n, "ir3", 0);

    icmConnectPSENet( handles.kb1_p, handles.ir3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir4_n = icmNewNet("ir4" );

    icmConnectPSENet( handles.pic1_p, handles.ir4_n, "ir4", 0);

    icmConnectPSENet( handles.ms1_p, handles.ir4_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir5_n = icmNewNet("ir5" );

    icmConnectPSENet( handles.pic1_p, handles.ir5_n, "ir5", 0);

    icmConnectPSENet( handles.pit_p, handles.ir5_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir6_n = icmNewNet("ir6" );

    icmConnectPSENet( handles.pic1_p, handles.ir6_n, "ir6", 0);

    icmConnectPSENet( handles.pit_p, handles.ir6_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir7_n = icmNewNet("ir7" );

    icmConnectPSENet( handles.pic1_p, handles.ir7_n, "ir7", 0);

    icmConnectPSENet( handles.pit_p, handles.ir7_n, "irq2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir8_n = icmNewNet("ir8" );

    icmConnectPSENet( handles.pic1_p, handles.ir8_n, "ir8", 0);

    icmConnectPSENet( handles.rtc_p, handles.ir8_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir23_n = icmNewNet("ir23" );

    icmConnectPSENet( handles.pic1_p, handles.ir23_n, "ir23", 0);

    icmConnectPSENet( handles.mmci_p, handles.ir23_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir24_n = icmNewNet("ir24" );

    icmConnectPSENet( handles.pic1_p, handles.ir24_n, "ir24", 0);

    icmConnectPSENet( handles.mmci_p, handles.ir24_n, "irq1", 0);
}
