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

    icmInitAttrs ArmVersatileExpress_CA15_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, ArmVersatileExpress_CA15_attrs, 0, 0, "ArmVersatileExpress-CA15");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "\nThis platform models the ARM Versatile Express development board with a CoreTile Express A15x2 (V2P-CA15) Daughterboard.\nSee the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0604E_v2p_ca15_tc1_trm.pdf for details of the hardware being modeled. \nNote this platform implements the motherboard's 'Cortex-A Series' memory map.\n\nThe default processor is an ARM Cortex-A15MPx2, which may be changed.\n");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n\nCoreSight software debug and trace ports are not modeled.\n\nRemap option not modeled.\n\nThe CLCD does not work in Linux\n");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus pBus
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_b = icmNewBus( "pBus", 40);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus nor0bus
////////////////////////////////////////////////////////////////////////////////


    handles.nor0bus_b = icmNewBus( "nor0bus", 32);

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
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-A15MPx2");
    icmAddStringAttr(cpu_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_attrList, "override_CBAR", 0x2c000000LL);
    icmAddUns64Attr(cpu_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddDoubleAttr(cpu_attrList, "mips", 1000.000000);
    icmAddStringAttr(cpu_attrList, "endian", "little");
    icmNewProcAttrs cpu_attrs = ICM_ATTR_SIMEX;


    handles.cpu_c = icmNewProcessor(
        "cpu"               ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        40                  ,   // address bits
        cpu_path            ,   // model
        0, 
        cpu_attrs           ,   // procAttrs
        cpu_attrList        ,   // attrlist
        0                   ,   // semihost file
        0
    );


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

    icmConnectPSEBus( handles.eth0_p, handles.pBus_b, "bport1", 0, 0x1a000000, 0x1a000fff);

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

    icmConnectPSEBus( handles.usb0_p, handles.pBus_b, "bport1", 0, 0x1b000000, 0x1b00ffff);

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
    icmAddUns64Attr(sysRegs_attrList, "SYS_PROCID0", 0x14000237LL);

    handles.sysRegs_p = icmNewPSE(
        "sysRegs"           ,   // name
        sysRegs_path        ,   // model
        sysRegs_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_p, handles.pBus_b, "bport1", 0, 0x1c010000, 0x1c010fff);

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

    icmConnectPSEBus( handles.sysCtrl_p, handles.pBus_b, "bport1", 0, 0x1c020000, 0x1c020fff);

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

    icmConnectPSEBus( handles.aac1_p, handles.pBus_b, "bport1", 0, 0x1c040000, 0x1c040fff);

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

    icmConnectPSEBus( handles.mmc1_p, handles.pBus_b, "bport1", 0, 0x1c050000, 0x1c050fff);

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

    icmConnectPSEBus( handles.kb1_p, handles.pBus_b, "bport1", 0, 0x1c060000, 0x1c060fff);

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

    icmConnectPSEBus( handles.ms1_p, handles.pBus_b, "bport1", 0, 0x1c070000, 0x1c070fff);

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

    icmConnectPSEBus( handles.uart0_p, handles.pBus_b, "bport1", 0, 0x1c090000, 0x1c090fff);

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

    handles.uart1_p = icmNewPSE(
        "uart1"             ,   // name
        uart1_path          ,   // model
        uart1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_p, handles.pBus_b, "bport1", 0, 0x1c0a0000, 0x1c0a0fff);

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

    icmConnectPSEBus( handles.uart2_p, handles.pBus_b, "bport1", 0, 0x1c0b0000, 0x1c0b0fff);

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

    icmConnectPSEBus( handles.uart3_p, handles.pBus_b, "bport1", 0, 0x1c0c0000, 0x1c0c0fff);

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

    icmConnectPSEBus( handles.wdt1_p, handles.pBus_b, "bport1", 0, 0x1c0f0000, 0x1c0f0fff);

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

    icmConnectPSEBus( handles.timer01_p, handles.pBus_b, "bport1", 0, 0x1c110000, 0x1c110fff);

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

    icmConnectPSEBus( handles.timer23_p, handles.pBus_b, "bport1", 0, 0x1c120000, 0x1c120fff);

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

    icmConnectPSEBus( handles.dvi1_p, handles.pBus_b, "bport1", 0, 0x1c160000, 0x1c160fff);

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

    icmConnectPSEBus( handles.rtc1_p, handles.pBus_b, "bport1", 0, 0x1c170000, 0x1c170fff);

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

    icmConnectPSEBus( handles.cf1_p, handles.pBus_b, "bport1", 0, 0x1001a000, 0x1001afff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart4
////////////////////////////////////////////////////////////////////////////////


    const char *uart4_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart4_attrList = icmNewAttrList();
    icmAddStringAttr(uart4_attrList, "variant", "ARM");

    handles.uart4_p = icmNewPSE(
        "uart4"             ,   // name
        uart4_path          ,   // model
        uart4_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart4_p, handles.pBus_b, "bport1", 0, 0x1c1b0000, 0x1c1b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE clcd
////////////////////////////////////////////////////////////////////////////////


    const char *clcd_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP clcd_attrList = icmNewAttrList();
    icmAddStringAttr(clcd_attrList, "resolution", "xga");
    icmAddUns64Attr(clcd_attrList, "noGraphics", 1LL);

    handles.clcd_p = icmNewPSE(
        "clcd"              ,   // name
        clcd_path           ,   // model
        clcd_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.clcd_p, handles.pBus_b, "bport1", 0, 0x1c1f0000, 0x1c1f0fff);

    icmConnectPSEBus( handles.clcd_p, handles.pBus_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE wdt2
////////////////////////////////////////////////////////////////////////////////


    const char *wdt2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt2_attrList = icmNewAttrList();

    handles.wdt2_p = icmNewPSE(
        "wdt2"              ,   // name
        wdt2_path           ,   // model
        wdt2_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt2_p, handles.pBus_b, "bport1", 0, 0x2b060000, 0x2b060fff);

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

    icmConnectPSEBus( handles.dmc1_p, handles.pBus_b, "bport1", 0, 0x2b0a0000, 0x2b0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE dma0
////////////////////////////////////////////////////////////////////////////////


    const char *dma0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dma0_attrList = icmNewAttrList();

    handles.dma0_p = icmNewPSE(
        "dma0"              ,   // name
        dma0_path           ,   // model
        dma0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dma0_p, handles.pBus_b, "bport1", 0, 0x7ffb0000, 0x7ffb0fff);

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

    icmConnectPSEBus( handles.smc1_p, handles.pBus_b, "bport1", 0, 0x7ffd0000, 0x7ffd0fff);

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
    icmAddStringAttr(smartLoader_attrList, "command", "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0");
    icmAddUns64Attr(smartLoader_attrList, "physicalbase", 0x80000000LL);
    icmAddUns64Attr(smartLoader_attrList, "memsize", 0x80000000LL);
    icmAddUns64Attr(smartLoader_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_p = icmNewPSE(
        "smartLoader"       ,   // name
        smartLoader_path    ,   // model
        smartLoader_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_p, handles.pBus_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.pBus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.pBus_b );

////////////////////////////////////////////////////////////////////////////////
//                                 Memory nor0
////////////////////////////////////////////////////////////////////////////////

    handles.nor0_m = icmNewMemory("nor0", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.nor0bus_b, "sp1", handles.nor0_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory nor1
////////////////////////////////////////////////////////////////////////////////

    handles.nor1_m = icmNewMemory("nor1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.nor1_m, 0xc000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory sram1
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_m = icmNewMemory("sram1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.sram1_m, 0x14000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory vram1
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_m = icmNewMemory("vram1", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.vram1_m, 0x18000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory ddr2ram
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_m = icmNewMemory("ddr2ram", 0x7, 0x7fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_b, "sp1", handles.ddr2ram_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge nor0Bridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.nor0bus_b, "nor0Bridge", "sp", "mp", 0x0, 0x3ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge nor0Remap
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.nor0bus_b, "nor0Remap", "sp", "mp", 0x0, 0x3ffffff, 0x8000000);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ddr2Bridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2Bridge", "sp", "mp", 0x0, 0x7fffffff, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ddr2Remap1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2Remap1", "sp", "mp", 0x0, 0x7fffffff, 0x800000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ddr2Remap2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2Remap2", "sp", "mp", 0x0, 0x7fffffff, 0x880000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ddr2Remap3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2Remap3", "sp", "mp", 0x0, 0x7fffffff, 0x8000000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ddr2Remap4
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2Remap4", "sp", "mp", 0x0, 0x7fffffff, 0x8080000000ULL);


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
    handles.ir14_n = icmNewNet("ir14" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir14_n, "SPI46", 0);

    icmConnectPSENet( handles.clcd_p, handles.ir14_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir15_n = icmNewNet("ir15" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir15_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_p, handles.ir15_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir16_n = icmNewNet("ir16" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir16_n, "SPI48", 0);

    icmConnectPSENet( handles.usb0_p, handles.ir16_n, "hc_irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.wprot_n = icmNewNet("wprot" );

    icmConnectPSENet( handles.sysRegs_p, handles.wprot_n, "wprot", 0);

    icmConnectPSENet( handles.mmc1_p, handles.wprot_n, "wprot", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cardin_n = icmNewNet("cardin" );

    icmConnectPSENet( handles.sysRegs_p, handles.cardin_n, "cardin", 0);

    icmConnectPSENet( handles.mmc1_p, handles.cardin_n, "cardin", 0);
}
