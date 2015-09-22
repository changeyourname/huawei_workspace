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

    icmInitAttrs ArmVersatileExpress_CA9_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, ArmVersatileExpress_CA9_attrs, 0, 0, "ArmVersatileExpress-CA9");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "\nThis platform models the ARM Versatile Express development board with a CoreTile Express A9x4 (V2P-CA9) Daughterboard.\nSee the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0448G_v2p_ca9_trm.pdf for details of the hardware being modeled. \nNote this platform implements the motherboard's 'Legacy' memory map.\n\nThe default processor is an ARM Cortex-A9MPx4, which may be changed.");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n\nThe TrustZone Protection Controller (TZPC) is modeled, the TrustZone Address Space Controller (TZASPC) is not modeled.\n\nCoreSight software debug and trace ports are not modeled.\n");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A9x4");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus tzBus
////////////////////////////////////////////////////////////////////////////////


    handles.tzBus_b = icmNewBus( "tzBus", 41);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus pBus
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_b = icmNewBus( "pBus", 32);

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
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-A9MPx4");
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
        41                  ,   // address bits
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
    icmAddUns64Attr(sysRegs_attrList, "SYS_PROCID0", 0x0c000191LL);

    handles.sysRegs_p = icmNewPSE(
        "sysRegs"           ,   // name
        sysRegs_path        ,   // model
        sysRegs_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_p, handles.pBus_b, "bport1", 0, 0x10000000, 0x10000fff);

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

    icmConnectPSEBus( handles.sysCtrl_p, handles.pBus_b, "bport1", 0, 0x10001000, 0x10001fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE sbpci0
////////////////////////////////////////////////////////////////////////////////


    const char *sbpci0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sbpci0_attrList = icmNewAttrList();

    handles.sbpci0_p = icmNewPSE(
        "sbpci0"            ,   // name
        sbpci0_path         ,   // model
        sbpci0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sbpci0_p, handles.pBus_b, "bport1", 0, 0x10002000, 0x10002fff);

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

    icmConnectPSEBus( handles.aac1_p, handles.pBus_b, "bport1", 0, 0x10004000, 0x10004fff);

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

    icmConnectPSEBus( handles.mmc1_p, handles.pBus_b, "bport1", 0, 0x10005000, 0x10005fff);

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

    icmConnectPSEBus( handles.kb1_p, handles.pBus_b, "bport1", 0, 0x10006000, 0x10006fff);

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

    icmConnectPSEBus( handles.ms1_p, handles.pBus_b, "bport1", 0, 0x10007000, 0x10007fff);

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

    icmConnectPSEBus( handles.uart0_p, handles.pBus_b, "bport1", 0, 0x10009000, 0x10009fff);

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

    icmConnectPSEBus( handles.uart1_p, handles.pBus_b, "bport1", 0, 0x1000a000, 0x1000afff);

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

    icmConnectPSEBus( handles.uart2_p, handles.pBus_b, "bport1", 0, 0x1000b000, 0x1000bfff);

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

    icmConnectPSEBus( handles.uart3_p, handles.pBus_b, "bport1", 0, 0x1000c000, 0x1000cfff);

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

    icmConnectPSEBus( handles.wdt1_p, handles.pBus_b, "bport1", 0, 0x1000f000, 0x1000ffff);

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

    icmConnectPSEBus( handles.timer01_p, handles.pBus_b, "bport1", 0, 0x10011000, 0x10011fff);

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

    icmConnectPSEBus( handles.timer23_p, handles.pBus_b, "bport1", 0, 0x10012000, 0x10012fff);

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

    icmConnectPSEBus( handles.dvi1_p, handles.pBus_b, "bport1", 0, 0x10016000, 0x10016fff);

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

    icmConnectPSEBus( handles.rtc1_p, handles.pBus_b, "bport1", 0, 0x10017000, 0x10017fff);

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

    icmConnectPSEBus( handles.clcd_p, handles.pBus_b, "bport1", 0, 0x1001f000, 0x1001ffff);

    icmConnectPSEBus( handles.clcd_p, handles.pBus_b, "memory", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.lcd1_p, handles.pBus_b, "bport1", 0, 0x10020000, 0x10020fff);

    icmConnectPSEBus( handles.lcd1_p, handles.pBus_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE lcd1NS
////////////////////////////////////////////////////////////////////////////////


    const char *lcd1NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP lcd1NS_attrList = icmNewAttrList();
    icmAddUns64Attr(lcd1NS_attrList, "mpLoAddress", 0x10020000LL);
    icmAddUns64Attr(lcd1NS_attrList, "spLoAddress", 1099780194304LL);
    icmAddUns64Attr(lcd1NS_attrList, "portSize", 0x1000LL);

    handles.lcd1NS_p = icmNewPSE(
        "lcd1NS"            ,   // name
        lcd1NS_path         ,   // model
        lcd1NS_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.lcd1NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.lcd1NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.dmc1_p, handles.pBus_b, "bport1", 0, 0x100e0000, 0x100e0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmc1NS
////////////////////////////////////////////////////////////////////////////////


    const char *dmc1NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmc1NS_attrList = icmNewAttrList();
    icmAddUns64Attr(dmc1NS_attrList, "mpLoAddress", 0x100e0000LL);
    icmAddUns64Attr(dmc1NS_attrList, "spLoAddress", 1099780980736LL);
    icmAddUns64Attr(dmc1NS_attrList, "portSize", 0x1000LL);

    handles.dmc1NS_p = icmNewPSE(
        "dmc1NS"            ,   // name
        dmc1NS_path         ,   // model
        dmc1NS_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmc1NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.dmc1NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.smc1_p, handles.pBus_b, "bport1", 0, 0x100e1000, 0x100e1fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE smc1NS
////////////////////////////////////////////////////////////////////////////////


    const char *smc1NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc1NS_attrList = icmNewAttrList();
    icmAddUns64Attr(smc1NS_attrList, "mpLoAddress", 0x100e1000LL);
    icmAddUns64Attr(smc1NS_attrList, "spLoAddress", 1099780984832LL);
    icmAddUns64Attr(smc1NS_attrList, "portSize", 0x1000LL);

    handles.smc1NS_p = icmNewPSE(
        "smc1NS"            ,   // name
        smc1NS_path         ,   // model
        smc1NS_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc1NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.smc1NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE scc1
////////////////////////////////////////////////////////////////////////////////


    const char *scc1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP scc1_attrList = icmNewAttrList();

    handles.scc1_p = icmNewPSE(
        "scc1"              ,   // name
        scc1_path           ,   // model
        scc1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.scc1_p, handles.pBus_b, "bport1", 0, 0x100e2000, 0x100e2fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE scc1NS
////////////////////////////////////////////////////////////////////////////////


    const char *scc1NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP scc1NS_attrList = icmNewAttrList();
    icmAddUns64Attr(scc1NS_attrList, "mpLoAddress", 0x100e2000LL);
    icmAddUns64Attr(scc1NS_attrList, "spLoAddress", 1099780988928LL);
    icmAddUns64Attr(scc1NS_attrList, "portSize", 0x1000LL);

    handles.scc1NS_p = icmNewPSE(
        "scc1NS"            ,   // name
        scc1NS_path         ,   // model
        scc1NS_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.scc1NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.scc1NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.timer45_p, handles.pBus_b, "bport1", 0, 0x100e4000, 0x100e4fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer45NS
////////////////////////////////////////////////////////////////////////////////


    const char *timer45NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer45NS_attrList = icmNewAttrList();
    icmAddUns64Attr(timer45NS_attrList, "mpLoAddress", 0x100e4000LL);
    icmAddUns64Attr(timer45NS_attrList, "spLoAddress", 1099780997120LL);
    icmAddUns64Attr(timer45NS_attrList, "portSize", 0x1000LL);

    handles.timer45NS_p = icmNewPSE(
        "timer45NS"         ,   // name
        timer45NS_path      ,   // model
        timer45NS_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer45NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.timer45NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.wdt2_p, handles.pBus_b, "bport1", 0, 0x100e5000, 0x100e5fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt2NS
////////////////////////////////////////////////////////////////////////////////


    const char *wdt2NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt2NS_attrList = icmNewAttrList();
    icmAddUns64Attr(wdt2NS_attrList, "mpLoAddress", 0x100e5000LL);
    icmAddUns64Attr(wdt2NS_attrList, "spLoAddress", 1099781001216LL);
    icmAddUns64Attr(wdt2NS_attrList, "portSize", 0x1000LL);

    handles.wdt2NS_p = icmNewPSE(
        "wdt2NS"            ,   // name
        wdt2NS_path         ,   // model
        wdt2NS_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt2NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.wdt2NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.tzpc_p, handles.pBus_b, "bport1", 0, 0x100e6000, 0x100e6fff);

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

    icmConnectPSEBus( handles.gpio0_p, handles.pBus_b, "bport1", 0, 0x100e8000, 0x100e8fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE faxi1
////////////////////////////////////////////////////////////////////////////////


    const char *faxi1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP faxi1_attrList = icmNewAttrList();

    handles.faxi1_p = icmNewPSE(
        "faxi1"             ,   // name
        faxi1_path          ,   // model
        faxi1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.faxi1_p, handles.pBus_b, "bport1", 0, 0x100e9000, 0x100e9fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE faxi1NS
////////////////////////////////////////////////////////////////////////////////


    const char *faxi1NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP faxi1NS_attrList = icmNewAttrList();
    icmAddUns64Attr(faxi1NS_attrList, "mpLoAddress", 0x100e9000LL);
    icmAddUns64Attr(faxi1NS_attrList, "spLoAddress", 1099781017600LL);
    icmAddUns64Attr(faxi1NS_attrList, "portSize", 0x1000LL);

    handles.faxi1NS_p = icmNewPSE(
        "faxi1NS"           ,   // name
        faxi1NS_path        ,   // model
        faxi1NS_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.faxi1NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.faxi1NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE saxi1
////////////////////////////////////////////////////////////////////////////////


    const char *saxi1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP saxi1_attrList = icmNewAttrList();

    handles.saxi1_p = icmNewPSE(
        "saxi1"             ,   // name
        saxi1_path          ,   // model
        saxi1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.saxi1_p, handles.pBus_b, "bport1", 0, 0x100ea000, 0x100eafff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE saxi1NS
////////////////////////////////////////////////////////////////////////////////


    const char *saxi1NS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP saxi1NS_attrList = icmNewAttrList();
    icmAddUns64Attr(saxi1NS_attrList, "mpLoAddress", 0x100ea000LL);
    icmAddUns64Attr(saxi1NS_attrList, "spLoAddress", 1099781021696LL);
    icmAddUns64Attr(saxi1NS_attrList, "portSize", 0x1000LL);

    handles.saxi1NS_p = icmNewPSE(
        "saxi1NS"           ,   // name
        saxi1NS_path        ,   // model
        saxi1NS_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.saxi1NS_p, handles.pBus_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.saxi1NS_p, handles.tzBus_b, "sp", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.l2regs_p, handles.pBus_b, "bport1", 0, 0x1e00a000, 0x1e00afff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE nor0
////////////////////////////////////////////////////////////////////////////////


    const char *nor0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        0                   ,    // library
        "NorFlash48F4400"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP nor0_attrList = icmNewAttrList();

    handles.nor0_p = icmNewPSE(
        "nor0"              ,   // name
        nor0_path           ,   // model
        nor0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.nor0_p, handles.pBus_b, "flash", 0, 0x40000000, 0x43ffffff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE nor1
////////////////////////////////////////////////////////////////////////////////


    const char *nor1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        0                   ,    // library
        "NorFlash48F4400"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP nor1_attrList = icmNewAttrList();

    handles.nor1_p = icmNewPSE(
        "nor1"              ,   // name
        nor1_path           ,   // model
        nor1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.nor1_p, handles.pBus_b, "flash", 0, 0x44000000, 0x47ffffff);

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

    icmConnectPSEBus( handles.eth0_p, handles.pBus_b, "bport1", 0, 0x4e000000, 0x4e000fff);

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

    icmConnectPSEBus( handles.usb0_p, handles.pBus_b, "bport1", 0, 0x4f000000, 0x4f00ffff);

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
    icmAddUns64Attr(smartLoader_attrList, "memsize", 0x40000000LL);
    icmAddUns64Attr(smartLoader_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_p = icmNewPSE(
        "smartLoader"       ,   // name
        smartLoader_path    ,   // model
        smartLoader_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_p, handles.pBus_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.tzBus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.tzBus_b );

////////////////////////////////////////////////////////////////////////////////
//                                Memory sram1
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_m = icmNewMemory("sram1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.sram1_m, 0x48000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory vram1
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_m = icmNewMemory("vram1", 0x7, 0x7fffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.vram1_m, 0x4c000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory ddr2ram
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_m = icmNewMemory("ddr2ram", 0x7, 0x3fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_b, "sp1", handles.ddr2ram_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge secure
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "secure", "sp", "mp", 0x0, 0xffffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge sysRegsNS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "sysRegsNS", "sp", "mp", 0x10000000, 0x10000fff, 0x10010000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge sysCtrlNS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "sysCtrlNS", "sp", "mp", 0x10001000, 0x10001fff, 0x10010001000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge aac1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "aac1NS", "sp", "mp", 0x10004000, 0x10004fff, 0x10010004000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge mmc1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "mmc1NS", "sp", "mp", 0x10005000, 0x10005fff, 0x10010005000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge kb1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "kb1NS", "sp", "mp", 0x10006000, 0x10006fff, 0x10010006000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge ms1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "ms1NS", "sp", "mp", 0x10007000, 0x10007fff, 0x10010007000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge uart0NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "uart0NS", "sp", "mp", 0x10009000, 0x10009fff, 0x10010009000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge uart1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "uart1NS", "sp", "mp", 0x1000a000, 0x1000afff, 0x1001000a000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge uart2NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "uart2NS", "sp", "mp", 0x1000b000, 0x1000bfff, 0x1001000b000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge uart3NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "uart3NS", "sp", "mp", 0x1000c000, 0x1000cfff, 0x1001000c000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge wdt1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "wdt1NS", "sp", "mp", 0x1000f000, 0x1000ffff, 0x1001000f000ULL);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge timer01NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "timer01NS", "sp", "mp", 0x10011000, 0x10011fff, 0x10010011000ULL);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge timer02NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "timer02NS", "sp", "mp", 0x10012000, 0x10012fff, 0x10010012000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge dvi1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "dvi1NS", "sp", "mp", 0x10016000, 0x10016fff, 0x10010016000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge rtc1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "rtc1NS", "sp", "mp", 0x10017000, 0x10017fff, 0x10010017000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge cf1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "cf1NS", "sp", "mp", 0x1001a000, 0x1001afff, 0x1001001a000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge lcd2NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "lcd2NS", "sp", "mp", 0x1001f000, 0x1001ffff, 0x1001001f000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge l2regsNS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "l2regsNS", "sp", "mp", 0x1e00a000, 0x1e00afff, 0x1001e00a000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge nor0NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "nor0NS", "sp", "mp", 0x40000000, 0x43ffffff, 0x10040000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge nor1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "nor1NS", "sp", "mp", 0x44000000, 0x47ffffff, 0x10044000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge sram1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "sram1NS", "sp", "mp", 0x48000000, 0x4bffffff, 0x10048000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge vram1NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "vram1NS", "sp", "mp", 0x4c000000, 0x4c7fffff, 0x1004c000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge eth0NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "eth0NS", "sp", "mp", 0x4e000000, 0x4e000fff, 0x1004e000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge usb0NS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "usb0NS", "sp", "mp", 0x4f000000, 0x4f00ffff, 0x1004f000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                            Bridge ddr2RamBridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2RamBridge", "sp", "mp", 0x0, 0x3fffffff, 0x60000000);

////////////////////////////////////////////////////////////////////////////////
//                              Bridge ddr2ramNS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "ddr2ramNS", "sp", "mp", 0x60000000, 0x9fffffff, 0x10060000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                           Bridge ddr2RemapBridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_b, handles.ddr2bus_b, "ddr2RemapBridge", "sp1", "mp", 0x20000000, 0x23ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                          Bridge ddr2RemapBridgeNS
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.tzBus_b, handles.pBus_b, "ddr2RemapBridgeNS", "sp", "mp", 0x0, 0x3ffffff, 0x10000000000ULL);


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

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot1_4_n = icmNewNet("tzpcdecprot1_4" );

    icmConnectPSENet( handles.lcd1NS_p, handles.tzpcdecprot1_4_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot1_4_n, "TZPCDECPROT1_4", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_0_n = icmNewNet("tzpcdecprot0_0" );

    icmConnectPSENet( handles.dmc1NS_p, handles.tzpcdecprot0_0_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_0_n, "TZPCDECPROT0_0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_1_n = icmNewNet("tzpcdecprot0_1" );

    icmConnectPSENet( handles.smc1NS_p, handles.tzpcdecprot0_1_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_1_n, "TZPCDECPROT0_1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_2_n = icmNewNet("tzpcdecprot0_2" );

    icmConnectPSENet( handles.scc1NS_p, handles.tzpcdecprot0_2_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_2_n, "TZPCDECPROT0_2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_4_n = icmNewNet("tzpcdecprot0_4" );

    icmConnectPSENet( handles.timer45NS_p, handles.tzpcdecprot0_4_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_4_n, "TZPCDECPROT0_4", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_5_n = icmNewNet("tzpcdecprot0_5" );

    icmConnectPSENet( handles.wdt2NS_p, handles.tzpcdecprot0_5_n, "enable", 0);

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_5_n, "TZPCDECPROT0_5", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_9_n = icmNewNet("tzpcdecprot0_9" );

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_9_n, "TZPCDECPROT0_9", 0);

    icmConnectPSENet( handles.faxi1NS_p, handles.tzpcdecprot0_9_n, "enable", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.tzpcdecprot0_10_n = icmNewNet("tzpcdecprot0_10" );

    icmConnectPSENet( handles.tzpc_p, handles.tzpcdecprot0_10_n, "TZPCDECPROT0_10", 0);

    icmConnectPSENet( handles.saxi1NS_p, handles.tzpcdecprot0_10_n, "enable", 0);
}
