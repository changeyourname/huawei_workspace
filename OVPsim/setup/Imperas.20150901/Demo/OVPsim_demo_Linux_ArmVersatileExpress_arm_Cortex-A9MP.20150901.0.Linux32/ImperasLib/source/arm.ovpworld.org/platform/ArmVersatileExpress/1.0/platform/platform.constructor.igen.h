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

    icmInitAttrs ArmVersatileExpress_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, ArmVersatileExpress_attrs, 0, 0, "ArmVersatileExpress");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "This platform models the ARM Versatile Express development board with the Legacy memory map.\nIt provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nThe main processor is an ARM Cortex-A9UP.\nThis platform is deprecated in favor of the ArmVersatileExpress-CA9 platform which models additional behavior, including TrustZone.");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "No known limitations for executing Linux operating system.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus smbus
////////////////////////////////////////////////////////////////////////////////


    handles.smbus_b = icmNewBus( "smbus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus ddr2bus
////////////////////////////////////////////////////////////////////////////////


    handles.ddr2bus_b = icmNewBus( "ddr2bus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Processor cpu
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-A9MPx1");
    icmAddStringAttr(cpu_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_attrList, "showHiddenRegs", 0LL);
    icmAddUns64Attr(cpu_attrList, "override_CBAR", 0x1e000000LL);
    icmAddDoubleAttr(cpu_attrList, "mips", 448.000000);
    icmAddStringAttr(cpu_attrList, "endian", "little");
    icmNewProcAttrs cpu_attrs = ICM_ATTR_SIMEX;


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
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                 PSE sysRegs
////////////////////////////////////////////////////////////////////////////////


    const char *sysRegs_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "VexpressSysRegs"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysRegs_attrList = icmNewAttrList();

    handles.sysRegs_p = icmNewPSE(
        "sysRegs"           ,   // name
        sysRegs_path        ,   // model
        sysRegs_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_p, handles.smbus_b, "bport1", 0, 0x10000000, 0x10000fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE sysCtrl
////////////////////////////////////////////////////////////////////////////////


    const char *sysCtrl_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SysCtrlSP810"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysCtrl_attrList = icmNewAttrList();

    handles.sysCtrl_p = icmNewPSE(
        "sysCtrl"           ,   // name
        sysCtrl_path        ,   // model
        sysCtrl_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysCtrl_p, handles.smbus_b, "bport1", 0, 0x10001000, 0x10001fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE aac1
////////////////////////////////////////////////////////////////////////////////


    const char *aac1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "AaciPL041"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP aac1_attrList = icmNewAttrList();

    handles.aac1_p = icmNewPSE(
        "aac1"              ,   // name
        aac1_path           ,   // model
        aac1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.aac1_p, handles.smbus_b, "bport1", 0, 0x10004000, 0x10004fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE mmc1
////////////////////////////////////////////////////////////////////////////////


    const char *mmc1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mmc1_attrList = icmNewAttrList();

    handles.mmc1_p = icmNewPSE(
        "mmc1"              ,   // name
        mmc1_path           ,   // model
        mmc1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mmc1_p, handles.smbus_b, "bport1", 0, 0x10005000, 0x10005fff);

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
    icmAddUns64Attr(kb1_attrList, "isKeyboard", 1LL);
    icmAddUns64Attr(kb1_attrList, "grabDisable", 1LL);

    handles.kb1_p = icmNewPSE(
        "kb1"               ,   // name
        kb1_path            ,   // model
        kb1_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.kb1_p, handles.smbus_b, "bport1", 0, 0x10006000, 0x10006fff);

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

    icmConnectPSEBus( handles.ms1_p, handles.smbus_b, "bport1", 0, 0x10007000, 0x10007fff);

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
    icmAddStringAttr(uart0_attrList, "variant", "ARM");
    icmAddStringAttr(uart0_attrList, "outfile", "uart0.log");
    icmAddUns64Attr(uart0_attrList, "finishOnDisconnect", 1LL);

    handles.uart0_p = icmNewPSE(
        "uart0"             ,   // name
        uart0_path          ,   // model
        uart0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_p, handles.smbus_b, "bport1", 0, 0x10009000, 0x10009fff);

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

    icmConnectPSEBus( handles.uart1_p, handles.smbus_b, "bport1", 0, 0x1000a000, 0x1000afff);

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

    handles.uart2_p = icmNewPSE(
        "uart2"             ,   // name
        uart2_path          ,   // model
        uart2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_p, handles.smbus_b, "bport1", 0, 0x1000b000, 0x1000bfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart3
////////////////////////////////////////////////////////////////////////////////


    const char *uart3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart3_attrList = icmNewAttrList();
    icmAddStringAttr(uart3_attrList, "variant", "ARM");

    handles.uart3_p = icmNewPSE(
        "uart3"             ,   // name
        uart3_path          ,   // model
        uart3_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_p, handles.smbus_b, "bport1", 0, 0x1000c000, 0x1000cfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE wdt1
////////////////////////////////////////////////////////////////////////////////


    const char *wdt1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt1_attrList = icmNewAttrList();

    handles.wdt1_p = icmNewPSE(
        "wdt1"              ,   // name
        wdt1_path           ,   // model
        wdt1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt1_p, handles.smbus_b, "bport1", 0, 0x1000f000, 0x1000ffff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer01
////////////////////////////////////////////////////////////////////////////////


    const char *timer01_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer01_attrList = icmNewAttrList();

    handles.timer01_p = icmNewPSE(
        "timer01"           ,   // name
        timer01_path        ,   // model
        timer01_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer01_p, handles.smbus_b, "bport1", 0, 0x10011000, 0x10011fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer23
////////////////////////////////////////////////////////////////////////////////


    const char *timer23_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer23_attrList = icmNewAttrList();

    handles.timer23_p = icmNewPSE(
        "timer23"           ,   // name
        timer23_path        ,   // model
        timer23_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer23_p, handles.smbus_b, "bport1", 0, 0x10012000, 0x10012fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE dvi1
////////////////////////////////////////////////////////////////////////////////


    const char *dvi1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SerBusDviRegs"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dvi1_attrList = icmNewAttrList();

    handles.dvi1_p = icmNewPSE(
        "dvi1"              ,   // name
        dvi1_path           ,   // model
        dvi1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dvi1_p, handles.smbus_b, "bport1", 0, 0x10016000, 0x10016fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE rtc1
////////////////////////////////////////////////////////////////////////////////


    const char *rtc1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc1_attrList = icmNewAttrList();

    handles.rtc1_p = icmNewPSE(
        "rtc1"              ,   // name
        rtc1_path           ,   // model
        rtc1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc1_p, handles.smbus_b, "bport1", 0, 0x10017000, 0x10017fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE cf1
////////////////////////////////////////////////////////////////////////////////


    const char *cf1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CompactFlashRegs"  ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cf1_attrList = icmNewAttrList();

    handles.cf1_p = icmNewPSE(
        "cf1"               ,   // name
        cf1_path            ,   // model
        cf1_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cf1_p, handles.smbus_b, "bport1", 0, 0x1001a000, 0x1001afff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE lcd1
////////////////////////////////////////////////////////////////////////////////


    const char *lcd1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP lcd1_attrList = icmNewAttrList();
    icmAddStringAttr(lcd1_attrList, "resolution", "xga");

    handles.lcd1_p = icmNewPSE(
        "lcd1"              ,   // name
        lcd1_path           ,   // model
        lcd1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.lcd1_p, handles.smbus_b, "bport1", 0, 0x10020000, 0x10020fff);

    icmConnectPSEBus( handles.lcd1_p, handles.smbus_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE dmc1
////////////////////////////////////////////////////////////////////////////////


    const char *dmc1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DMemCtrlPL341"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmc1_attrList = icmNewAttrList();

    handles.dmc1_p = icmNewPSE(
        "dmc1"              ,   // name
        dmc1_path           ,   // model
        dmc1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmc1_p, handles.smbus_b, "bport1", 0, 0x100e0000, 0x100e0fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE smc1
////////////////////////////////////////////////////////////////////////////////


    const char *smc1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SMemCtrlPL354"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc1_attrList = icmNewAttrList();

    handles.smc1_p = icmNewPSE(
        "smc1"              ,   // name
        smc1_path           ,   // model
        smc1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc1_p, handles.smbus_b, "bport1", 0, 0x100e1000, 0x100e1fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer45
////////////////////////////////////////////////////////////////////////////////


    const char *timer45_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer45_attrList = icmNewAttrList();

    handles.timer45_p = icmNewPSE(
        "timer45"           ,   // name
        timer45_path        ,   // model
        timer45_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer45_p, handles.smbus_b, "bport1", 0, 0x100e4000, 0x100e4fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE gpio0
////////////////////////////////////////////////////////////////////////////////


    const char *gpio0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP gpio0_attrList = icmNewAttrList();

    handles.gpio0_p = icmNewPSE(
        "gpio0"             ,   // name
        gpio0_path          ,   // model
        gpio0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.gpio0_p, handles.smbus_b, "bport1", 0, 0x100e8000, 0x100e8fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE l2regs
////////////////////////////////////////////////////////////////////////////////


    const char *l2regs_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "L2CachePL310"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP l2regs_attrList = icmNewAttrList();

    handles.l2regs_p = icmNewPSE(
        "l2regs"            ,   // name
        l2regs_path         ,   // model
        l2regs_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.l2regs_p, handles.smbus_b, "bport1", 0, 0x1e00a000, 0x1e00afff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE eth0
////////////////////////////////////////////////////////////////////////////////


    const char *eth0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "smsc.ovpworld.org" ,    // vendor
        0                   ,    // library
        "LAN9118"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP eth0_attrList = icmNewAttrList();

    handles.eth0_p = icmNewPSE(
        "eth0"              ,   // name
        eth0_path           ,   // model
        eth0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.eth0_p, handles.smbus_b, "bport1", 0, 0x4e000000, 0x4e000fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE usb0
////////////////////////////////////////////////////////////////////////////////


    const char *usb0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "philips.ovpworld.org",    // vendor
        0                   ,    // library
        "ISP1761"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP usb0_attrList = icmNewAttrList();

    handles.usb0_p = icmNewPSE(
        "usb0"              ,   // name
        usb0_path           ,   // model
        usb0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.usb0_p, handles.smbus_b, "bport1", 0, 0x4f000000, 0x4f00ffff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE smartLoader
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_attrList = icmNewAttrList();
    icmAddStringAttr(smartLoader_attrList, "command", "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0");
    icmAddUns64Attr(smartLoader_attrList, "physicalbase", 0x60000000LL);
    icmAddUns64Attr(smartLoader_attrList, "memsize", 0x10000000LL);
    icmAddUns64Attr(smartLoader_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_p = icmNewPSE(
        "smartLoader"       ,   // name
        smartLoader_path    ,   // model
        smartLoader_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_p, handles.smbus_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.smbus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.smbus_b );

////////////////////////////////////////////////////////////////////////////////
//                                 Memory lcd2
////////////////////////////////////////////////////////////////////////////////

    handles.lcd2_m = icmNewMemory("lcd2", 0x7, 0xfff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.lcd2_m, 0x1001f000);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory nor0
////////////////////////////////////////////////////////////////////////////////

    handles.nor0_m = icmNewMemory("nor0", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.nor0_m, 0x40000000);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory nor1
////////////////////////////////////////////////////////////////////////////////

    handles.nor1_m = icmNewMemory("nor1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.nor1_m, 0x44000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory sram1
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_m = icmNewMemory("sram1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.sram1_m, 0x48000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory vram1
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_m = icmNewMemory("vram1", 0x7, 0x7fffff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.vram1_m, 0x4c000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory ddr2ram
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_m = icmNewMemory("ddr2ram", 0x7, 0x3fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_b, "sp1", handles.ddr2ram_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                            Bridge ddr2RamBridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.smbus_b, handles.ddr2bus_b, "ddr2RamBridge", "sp", "mp", 0x0, 0x3fffffff, 0x60000000);

////////////////////////////////////////////////////////////////////////////////
//                           Bridge ddr2RemapBridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.smbus_b, handles.ddr2bus_b, "ddr2RemapBridge", "sp1", "mp", 0x20000000, 0x23ffffff, 0x0);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.ir2_n = icmNewNet("ir2" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir2_n, "SPI34", 0);

    icmConnectPSENet( handles.timer01_p, handles.ir2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir3_n = icmNewNet("ir3" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir3_n, "SPI35", 0);

    icmConnectPSENet( handles.timer23_p, handles.ir3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir4_n = icmNewNet("ir4" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir4_n, "SPI36", 0);

    icmConnectPSENet( handles.rtc1_p, handles.ir4_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir5_n = icmNewNet("ir5" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir5_n, "SPI37", 0);

    icmConnectPSENet( handles.uart0_p, handles.ir5_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir6_n = icmNewNet("ir6" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir6_n, "SPI38", 0);

    icmConnectPSENet( handles.uart1_p, handles.ir6_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir7_n = icmNewNet("ir7" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir7_n, "SPI39", 0);

    icmConnectPSENet( handles.uart2_p, handles.ir7_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir8_n = icmNewNet("ir8" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir8_n, "SPI40", 0);

    icmConnectPSENet( handles.uart3_p, handles.ir8_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir9_n = icmNewNet("ir9" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir9_n, "SPI41", 0);

    icmConnectPSENet( handles.mmc1_p, handles.ir9_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir10_n = icmNewNet("ir10" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir10_n, "SPI42", 0);

    icmConnectPSENet( handles.mmc1_p, handles.ir10_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir12_n = icmNewNet("ir12" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir12_n, "SPI44", 0);

    icmConnectPSENet( handles.kb1_p, handles.ir12_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir13_n = icmNewNet("ir13" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir13_n, "SPI45", 0);

    icmConnectPSENet( handles.ms1_p, handles.ir13_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir15_n = icmNewNet("ir15" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir15_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_p, handles.ir15_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir16_n = icmNewNet("ir16" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir16_n, "SPI48", 0);

    icmConnectPSENet( handles.usb0_p, handles.ir16_n, "hc_irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir44_n = icmNewNet("ir44" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir44_n, "SPI76", 0);

    icmConnectPSENet( handles.lcd1_p, handles.ir44_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir48_n = icmNewNet("ir48" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir48_n, "SPI80", 0);

    icmConnectPSENet( handles.timer45_p, handles.ir48_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cardin_n = icmNewNet("cardin" );

    icmConnectPSENet( handles.sysRegs_p, handles.cardin_n, "cardin", 0);

    icmConnectPSENet( handles.mmc1_p, handles.cardin_n, "cardin", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.wprot_n = icmNewNet("wprot" );

    icmConnectPSENet( handles.sysRegs_p, handles.wprot_n, "wprot", 0);

    icmConnectPSENet( handles.mmc1_p, handles.wprot_n, "wprot", 0);
}
