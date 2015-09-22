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

    icmInitAttrs QuadArmVersatileExpress_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, QuadArmVersatileExpress_attrs, 0, 0, "QuadArmVersatileExpress");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "\nThis platform models the ARM Versatile Express development board with a CoreTile Express A15x2 (V2P-CA15) Daughterboard.\nSee the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0604E_v2p_ca15_tc1_trm.pdf for details of the hardware being modeled. \nNote this platform implements the motherboard's 'Cortex-A Series' memory map.\n\nThe default processor is an ARM Cortex-A15MPx2, which may be changed.\n");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n\nCoreSight software debug and trace ports are not modeled.\n\nRemap option not modeled.\n\nThe CLCD does not work in Linux\n");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_FIX,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus pBus_0
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_0_b = icmNewBus( "pBus_0", 40);

////////////////////////////////////////////////////////////////////////////////
//                                Bus nor0bus_0
////////////////////////////////////////////////////////////////////////////////


    handles.nor0bus_0_b = icmNewBus( "nor0bus_0", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Bus ddr2bus_0
////////////////////////////////////////////////////////////////////////////////


    handles.ddr2bus_0_b = icmNewBus( "ddr2bus_0", 32);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus pBus_1
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_1_b = icmNewBus( "pBus_1", 40);

////////////////////////////////////////////////////////////////////////////////
//                                Bus nor0bus_1
////////////////////////////////////////////////////////////////////////////////


    handles.nor0bus_1_b = icmNewBus( "nor0bus_1", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Bus ddr2bus_1
////////////////////////////////////////////////////////////////////////////////


    handles.ddr2bus_1_b = icmNewBus( "ddr2bus_1", 32);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus pBus_2
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_2_b = icmNewBus( "pBus_2", 40);

////////////////////////////////////////////////////////////////////////////////
//                                Bus nor0bus_2
////////////////////////////////////////////////////////////////////////////////


    handles.nor0bus_2_b = icmNewBus( "nor0bus_2", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Bus ddr2bus_2
////////////////////////////////////////////////////////////////////////////////


    handles.ddr2bus_2_b = icmNewBus( "ddr2bus_2", 32);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus pBus_3
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_3_b = icmNewBus( "pBus_3", 40);

////////////////////////////////////////////////////////////////////////////////
//                                Bus nor0bus_3
////////////////////////////////////////////////////////////////////////////////


    handles.nor0bus_3_b = icmNewBus( "nor0bus_3", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Bus ddr2bus_3
////////////////////////////////////////////////////////////////////////////////


    handles.ddr2bus_3_b = icmNewBus( "ddr2bus_3", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu_0
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_0_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_0_attrList, "variant", "Cortex-A15MPx2");
    icmAddStringAttr(cpu_0_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_0_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_0_attrList, "override_CBAR", 0x2c000000LL);
    icmAddUns64Attr(cpu_0_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddDoubleAttr(cpu_0_attrList, "mips", 1000.000000);
    icmAddStringAttr(cpu_0_attrList, "endian", "little");
    icmNewProcAttrs cpu_0_attrs = ICM_ATTR_SIMEX;


    handles.cpu_0_c = icmNewProcessor(
        "cpu_0"             ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        40                  ,   // address bits
        cpu_0_path          ,   // model
        0, 
        cpu_0_attrs         ,   // procAttrs
        cpu_0_attrList      ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu_1
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_1_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_1_attrList, "variant", "Cortex-A15MPx2");
    icmAddStringAttr(cpu_1_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_1_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_1_attrList, "override_CBAR", 0x2c000000LL);
    icmAddUns64Attr(cpu_1_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddDoubleAttr(cpu_1_attrList, "mips", 1000.000000);
    icmAddStringAttr(cpu_1_attrList, "endian", "little");
    icmNewProcAttrs cpu_1_attrs = ICM_ATTR_SIMEX;


    handles.cpu_1_c = icmNewProcessor(
        "cpu_1"             ,   // name
        0,
        1                   ,   // cpuId
        0x0000              ,  // flags
        40                  ,   // address bits
        cpu_1_path          ,   // model
        0, 
        cpu_1_attrs         ,   // procAttrs
        cpu_1_attrList      ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu_2
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_2_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_2_attrList, "variant", "Cortex-A15MPx2");
    icmAddStringAttr(cpu_2_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_2_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_2_attrList, "override_CBAR", 0x2c000000LL);
    icmAddUns64Attr(cpu_2_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddDoubleAttr(cpu_2_attrList, "mips", 1000.000000);
    icmAddStringAttr(cpu_2_attrList, "endian", "little");
    icmNewProcAttrs cpu_2_attrs = ICM_ATTR_SIMEX;


    handles.cpu_2_c = icmNewProcessor(
        "cpu_2"             ,   // name
        0,
        2                   ,   // cpuId
        0x0000              ,  // flags
        40                  ,   // address bits
        cpu_2_path          ,   // model
        0, 
        cpu_2_attrs         ,   // procAttrs
        cpu_2_attrList      ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu_3
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_3_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_3_attrList, "variant", "Cortex-A15MPx2");
    icmAddStringAttr(cpu_3_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_3_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_3_attrList, "override_CBAR", 0x2c000000LL);
    icmAddUns64Attr(cpu_3_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddDoubleAttr(cpu_3_attrList, "mips", 1000.000000);
    icmAddStringAttr(cpu_3_attrList, "endian", "little");
    icmNewProcAttrs cpu_3_attrs = ICM_ATTR_SIMEX;


    handles.cpu_3_c = icmNewProcessor(
        "cpu_3"             ,   // name
        0,
        3                   ,   // cpuId
        0x0000              ,  // flags
        40                  ,   // address bits
        cpu_3_path          ,   // model
        0, 
        cpu_3_attrs         ,   // procAttrs
        cpu_3_attrList      ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                 PSE eth0_0
////////////////////////////////////////////////////////////////////////////////


    const char *eth0_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "smsc.ovpworld.org" ,    // vendor
        0                   ,    // library
        "LAN9118"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP eth0_0_attrList = icmNewAttrList();

    handles.eth0_0_p = icmNewPSE(
        "eth0_0"            ,   // name
        eth0_0_path         ,   // model
        eth0_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.eth0_0_p, handles.pBus_0_b, "bport1", 0, 0x1a000000, 0x1a000fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE usb0_0
////////////////////////////////////////////////////////////////////////////////


    const char *usb0_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "philips.ovpworld.org",    // vendor
        0                   ,    // library
        "ISP1761"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP usb0_0_attrList = icmNewAttrList();

    handles.usb0_0_p = icmNewPSE(
        "usb0_0"            ,   // name
        usb0_0_path         ,   // model
        usb0_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.usb0_0_p, handles.pBus_0_b, "bport1", 0, 0x1b000000, 0x1b00ffff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysRegs_0
////////////////////////////////////////////////////////////////////////////////


    const char *sysRegs_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "VexpressSysRegs"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysRegs_0_attrList = icmNewAttrList();

    handles.sysRegs_0_p = icmNewPSE(
        "sysRegs_0"         ,   // name
        sysRegs_0_path      ,   // model
        sysRegs_0_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_0_p, handles.pBus_0_b, "bport1", 0, 0x1c010000, 0x1c010fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysCtrl_0
////////////////////////////////////////////////////////////////////////////////


    const char *sysCtrl_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SysCtrlSP810"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysCtrl_0_attrList = icmNewAttrList();

    handles.sysCtrl_0_p = icmNewPSE(
        "sysCtrl_0"         ,   // name
        sysCtrl_0_path      ,   // model
        sysCtrl_0_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysCtrl_0_p, handles.pBus_0_b, "bport1", 0, 0x1c020000, 0x1c020fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE aac1_0
////////////////////////////////////////////////////////////////////////////////


    const char *aac1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "AaciPL041"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP aac1_0_attrList = icmNewAttrList();

    handles.aac1_0_p = icmNewPSE(
        "aac1_0"            ,   // name
        aac1_0_path         ,   // model
        aac1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.aac1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c040000, 0x1c040fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE mmc1_0
////////////////////////////////////////////////////////////////////////////////


    const char *mmc1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mmc1_0_attrList = icmNewAttrList();

    handles.mmc1_0_p = icmNewPSE(
        "mmc1_0"            ,   // name
        mmc1_0_path         ,   // model
        mmc1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mmc1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c050000, 0x1c050fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE kb1_0
////////////////////////////////////////////////////////////////////////////////


    const char *kb1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP kb1_0_attrList = icmNewAttrList();
    icmAddUns64Attr(kb1_0_attrList, "isKeyboard", 1LL);
    icmAddUns64Attr(kb1_0_attrList, "grabDisable", 1LL);

    handles.kb1_0_p = icmNewPSE(
        "kb1_0"             ,   // name
        kb1_0_path          ,   // model
        kb1_0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.kb1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c060000, 0x1c060fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ms1_0
////////////////////////////////////////////////////////////////////////////////


    const char *ms1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ms1_0_attrList = icmNewAttrList();
    icmAddUns64Attr(ms1_0_attrList, "isMouse", 1LL);
    icmAddUns64Attr(ms1_0_attrList, "grabDisable", 1LL);

    handles.ms1_0_p = icmNewPSE(
        "ms1_0"             ,   // name
        ms1_0_path          ,   // model
        ms1_0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ms1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c070000, 0x1c070fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart0_0
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_0_attrList = icmNewAttrList();
    icmAddStringAttr(uart0_0_attrList, "variant", "ARM");
    icmAddStringAttr(uart0_0_attrList, "outfile", "uart0_0.log");
    icmAddUns64Attr(uart0_0_attrList, "finishOnDisconnect", 1LL);

    handles.uart0_0_p = icmNewPSE(
        "uart0_0"           ,   // name
        uart0_0_path        ,   // model
        uart0_0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_0_p, handles.pBus_0_b, "bport1", 0, 0x1c090000, 0x1c090fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart1_0
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_0_attrList = icmNewAttrList();
    icmAddStringAttr(uart1_0_attrList, "variant", "ARM");
    icmAddStringAttr(uart1_0_attrList, "outfile", "uart1_0.log");

    handles.uart1_0_p = icmNewPSE(
        "uart1_0"           ,   // name
        uart1_0_path        ,   // model
        uart1_0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c0a0000, 0x1c0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart2_0
////////////////////////////////////////////////////////////////////////////////


    const char *uart2_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart2_0_attrList = icmNewAttrList();
    icmAddStringAttr(uart2_0_attrList, "variant", "ARM");

    handles.uart2_0_p = icmNewPSE(
        "uart2_0"           ,   // name
        uart2_0_path        ,   // model
        uart2_0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_0_p, handles.pBus_0_b, "bport1", 0, 0x1c0b0000, 0x1c0b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart3_0
////////////////////////////////////////////////////////////////////////////////


    const char *uart3_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart3_0_attrList = icmNewAttrList();
    icmAddStringAttr(uart3_0_attrList, "variant", "ARM");

    handles.uart3_0_p = icmNewPSE(
        "uart3_0"           ,   // name
        uart3_0_path        ,   // model
        uart3_0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_0_p, handles.pBus_0_b, "bport1", 0, 0x1c0c0000, 0x1c0c0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt1_0
////////////////////////////////////////////////////////////////////////////////


    const char *wdt1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt1_0_attrList = icmNewAttrList();

    handles.wdt1_0_p = icmNewPSE(
        "wdt1_0"            ,   // name
        wdt1_0_path         ,   // model
        wdt1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c0f0000, 0x1c0f0fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer01_0
////////////////////////////////////////////////////////////////////////////////


    const char *timer01_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer01_0_attrList = icmNewAttrList();

    handles.timer01_0_p = icmNewPSE(
        "timer01_0"         ,   // name
        timer01_0_path      ,   // model
        timer01_0_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer01_0_p, handles.pBus_0_b, "bport1", 0, 0x1c110000, 0x1c110fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer23_0
////////////////////////////////////////////////////////////////////////////////


    const char *timer23_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer23_0_attrList = icmNewAttrList();

    handles.timer23_0_p = icmNewPSE(
        "timer23_0"         ,   // name
        timer23_0_path      ,   // model
        timer23_0_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer23_0_p, handles.pBus_0_b, "bport1", 0, 0x1c120000, 0x1c120fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dvi1_0
////////////////////////////////////////////////////////////////////////////////


    const char *dvi1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SerBusDviRegs"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dvi1_0_attrList = icmNewAttrList();

    handles.dvi1_0_p = icmNewPSE(
        "dvi1_0"            ,   // name
        dvi1_0_path         ,   // model
        dvi1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dvi1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c160000, 0x1c160fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE rtc1_0
////////////////////////////////////////////////////////////////////////////////


    const char *rtc1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc1_0_attrList = icmNewAttrList();

    handles.rtc1_0_p = icmNewPSE(
        "rtc1_0"            ,   // name
        rtc1_0_path         ,   // model
        rtc1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc1_0_p, handles.pBus_0_b, "bport1", 0, 0x1c170000, 0x1c170fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE cf1_0
////////////////////////////////////////////////////////////////////////////////


    const char *cf1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CompactFlashRegs"  ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cf1_0_attrList = icmNewAttrList();

    handles.cf1_0_p = icmNewPSE(
        "cf1_0"             ,   // name
        cf1_0_path          ,   // model
        cf1_0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cf1_0_p, handles.pBus_0_b, "bport1", 0, 0x1001a000, 0x1001afff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart4_0
////////////////////////////////////////////////////////////////////////////////


    const char *uart4_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart4_0_attrList = icmNewAttrList();
    icmAddStringAttr(uart4_0_attrList, "variant", "ARM");

    handles.uart4_0_p = icmNewPSE(
        "uart4_0"           ,   // name
        uart4_0_path        ,   // model
        uart4_0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart4_0_p, handles.pBus_0_b, "bport1", 0, 0x1c1b0000, 0x1c1b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE clcd_0
////////////////////////////////////////////////////////////////////////////////


    const char *clcd_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP clcd_0_attrList = icmNewAttrList();
    icmAddStringAttr(clcd_0_attrList, "resolution", "xga");
    icmAddUns64Attr(clcd_0_attrList, "noGraphics", 1LL);

    handles.clcd_0_p = icmNewPSE(
        "clcd_0"            ,   // name
        clcd_0_path         ,   // model
        clcd_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.clcd_0_p, handles.pBus_0_b, "bport1", 0, 0x1c1f0000, 0x1c1f0fff);

    icmConnectPSEBus( handles.clcd_0_p, handles.pBus_0_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt2_0
////////////////////////////////////////////////////////////////////////////////


    const char *wdt2_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt2_0_attrList = icmNewAttrList();

    handles.wdt2_0_p = icmNewPSE(
        "wdt2_0"            ,   // name
        wdt2_0_path         ,   // model
        wdt2_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt2_0_p, handles.pBus_0_b, "bport1", 0, 0x2b060000, 0x2b060fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmc1_0
////////////////////////////////////////////////////////////////////////////////


    const char *dmc1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DMemCtrlPL341"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmc1_0_attrList = icmNewAttrList();

    handles.dmc1_0_p = icmNewPSE(
        "dmc1_0"            ,   // name
        dmc1_0_path         ,   // model
        dmc1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmc1_0_p, handles.pBus_0_b, "bport1", 0, 0x2b0a0000, 0x2b0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dma0_0
////////////////////////////////////////////////////////////////////////////////


    const char *dma0_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dma0_0_attrList = icmNewAttrList();

    handles.dma0_0_p = icmNewPSE(
        "dma0_0"            ,   // name
        dma0_0_path         ,   // model
        dma0_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dma0_0_p, handles.pBus_0_b, "bport1", 0, 0x7ffb0000, 0x7ffb0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE smc1_0
////////////////////////////////////////////////////////////////////////////////


    const char *smc1_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SMemCtrlPL354"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc1_0_attrList = icmNewAttrList();

    handles.smc1_0_p = icmNewPSE(
        "smc1_0"            ,   // name
        smc1_0_path         ,   // model
        smc1_0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc1_0_p, handles.pBus_0_b, "bport1", 0, 0x7ffd0000, 0x7ffd0fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE smartLoader_0
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_0_attrList = icmNewAttrList();
    icmAddStringAttr(smartLoader_0_attrList, "command", "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0");
    icmAddUns64Attr(smartLoader_0_attrList, "physicalbase", 0x80000000LL);
    icmAddUns64Attr(smartLoader_0_attrList, "memsize", 0x80000000LL);
    icmAddUns64Attr(smartLoader_0_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_0_p = icmNewPSE(
        "smartLoader_0"     ,   // name
        smartLoader_0_path  ,   // model
        smartLoader_0_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_0_p, handles.pBus_0_b, "mport", 1, 0x0, 0xffffffff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE eth0_1
////////////////////////////////////////////////////////////////////////////////


    const char *eth0_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "smsc.ovpworld.org" ,    // vendor
        0                   ,    // library
        "LAN9118"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP eth0_1_attrList = icmNewAttrList();

    handles.eth0_1_p = icmNewPSE(
        "eth0_1"            ,   // name
        eth0_1_path         ,   // model
        eth0_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.eth0_1_p, handles.pBus_1_b, "bport1", 0, 0x1a000000, 0x1a000fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE usb0_1
////////////////////////////////////////////////////////////////////////////////


    const char *usb0_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "philips.ovpworld.org",    // vendor
        0                   ,    // library
        "ISP1761"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP usb0_1_attrList = icmNewAttrList();

    handles.usb0_1_p = icmNewPSE(
        "usb0_1"            ,   // name
        usb0_1_path         ,   // model
        usb0_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.usb0_1_p, handles.pBus_1_b, "bport1", 0, 0x1b000000, 0x1b00ffff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysRegs_1
////////////////////////////////////////////////////////////////////////////////


    const char *sysRegs_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "VexpressSysRegs"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysRegs_1_attrList = icmNewAttrList();

    handles.sysRegs_1_p = icmNewPSE(
        "sysRegs_1"         ,   // name
        sysRegs_1_path      ,   // model
        sysRegs_1_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_1_p, handles.pBus_1_b, "bport1", 0, 0x1c010000, 0x1c010fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysCtrl_1
////////////////////////////////////////////////////////////////////////////////


    const char *sysCtrl_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SysCtrlSP810"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysCtrl_1_attrList = icmNewAttrList();

    handles.sysCtrl_1_p = icmNewPSE(
        "sysCtrl_1"         ,   // name
        sysCtrl_1_path      ,   // model
        sysCtrl_1_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysCtrl_1_p, handles.pBus_1_b, "bport1", 0, 0x1c020000, 0x1c020fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE aac1_1
////////////////////////////////////////////////////////////////////////////////


    const char *aac1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "AaciPL041"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP aac1_1_attrList = icmNewAttrList();

    handles.aac1_1_p = icmNewPSE(
        "aac1_1"            ,   // name
        aac1_1_path         ,   // model
        aac1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.aac1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c040000, 0x1c040fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE mmc1_1
////////////////////////////////////////////////////////////////////////////////


    const char *mmc1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mmc1_1_attrList = icmNewAttrList();

    handles.mmc1_1_p = icmNewPSE(
        "mmc1_1"            ,   // name
        mmc1_1_path         ,   // model
        mmc1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mmc1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c050000, 0x1c050fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE kb1_1
////////////////////////////////////////////////////////////////////////////////


    const char *kb1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP kb1_1_attrList = icmNewAttrList();
    icmAddUns64Attr(kb1_1_attrList, "isKeyboard", 1LL);
    icmAddUns64Attr(kb1_1_attrList, "grabDisable", 1LL);

    handles.kb1_1_p = icmNewPSE(
        "kb1_1"             ,   // name
        kb1_1_path          ,   // model
        kb1_1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.kb1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c060000, 0x1c060fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ms1_1
////////////////////////////////////////////////////////////////////////////////


    const char *ms1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ms1_1_attrList = icmNewAttrList();
    icmAddUns64Attr(ms1_1_attrList, "isMouse", 1LL);
    icmAddUns64Attr(ms1_1_attrList, "grabDisable", 1LL);

    handles.ms1_1_p = icmNewPSE(
        "ms1_1"             ,   // name
        ms1_1_path          ,   // model
        ms1_1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ms1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c070000, 0x1c070fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart0_1
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_1_attrList = icmNewAttrList();
    icmAddStringAttr(uart0_1_attrList, "variant", "ARM");
    icmAddStringAttr(uart0_1_attrList, "outfile", "uart0_1.log");
    icmAddUns64Attr(uart0_1_attrList, "finishOnDisconnect", 1LL);

    handles.uart0_1_p = icmNewPSE(
        "uart0_1"           ,   // name
        uart0_1_path        ,   // model
        uart0_1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_1_p, handles.pBus_1_b, "bport1", 0, 0x1c090000, 0x1c090fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart1_1
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_1_attrList = icmNewAttrList();
    icmAddStringAttr(uart1_1_attrList, "variant", "ARM");
    icmAddStringAttr(uart1_1_attrList, "outfile", "uart1_1.log");

    handles.uart1_1_p = icmNewPSE(
        "uart1_1"           ,   // name
        uart1_1_path        ,   // model
        uart1_1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c0a0000, 0x1c0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart2_1
////////////////////////////////////////////////////////////////////////////////


    const char *uart2_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart2_1_attrList = icmNewAttrList();
    icmAddStringAttr(uart2_1_attrList, "variant", "ARM");

    handles.uart2_1_p = icmNewPSE(
        "uart2_1"           ,   // name
        uart2_1_path        ,   // model
        uart2_1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_1_p, handles.pBus_1_b, "bport1", 0, 0x1c0b0000, 0x1c0b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart3_1
////////////////////////////////////////////////////////////////////////////////


    const char *uart3_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart3_1_attrList = icmNewAttrList();
    icmAddStringAttr(uart3_1_attrList, "variant", "ARM");

    handles.uart3_1_p = icmNewPSE(
        "uart3_1"           ,   // name
        uart3_1_path        ,   // model
        uart3_1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_1_p, handles.pBus_1_b, "bport1", 0, 0x1c0c0000, 0x1c0c0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt1_1
////////////////////////////////////////////////////////////////////////////////


    const char *wdt1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt1_1_attrList = icmNewAttrList();

    handles.wdt1_1_p = icmNewPSE(
        "wdt1_1"            ,   // name
        wdt1_1_path         ,   // model
        wdt1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c0f0000, 0x1c0f0fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer01_1
////////////////////////////////////////////////////////////////////////////////


    const char *timer01_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer01_1_attrList = icmNewAttrList();

    handles.timer01_1_p = icmNewPSE(
        "timer01_1"         ,   // name
        timer01_1_path      ,   // model
        timer01_1_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer01_1_p, handles.pBus_1_b, "bport1", 0, 0x1c110000, 0x1c110fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer23_1
////////////////////////////////////////////////////////////////////////////////


    const char *timer23_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer23_1_attrList = icmNewAttrList();

    handles.timer23_1_p = icmNewPSE(
        "timer23_1"         ,   // name
        timer23_1_path      ,   // model
        timer23_1_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer23_1_p, handles.pBus_1_b, "bport1", 0, 0x1c120000, 0x1c120fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dvi1_1
////////////////////////////////////////////////////////////////////////////////


    const char *dvi1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SerBusDviRegs"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dvi1_1_attrList = icmNewAttrList();

    handles.dvi1_1_p = icmNewPSE(
        "dvi1_1"            ,   // name
        dvi1_1_path         ,   // model
        dvi1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dvi1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c160000, 0x1c160fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE rtc1_1
////////////////////////////////////////////////////////////////////////////////


    const char *rtc1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc1_1_attrList = icmNewAttrList();

    handles.rtc1_1_p = icmNewPSE(
        "rtc1_1"            ,   // name
        rtc1_1_path         ,   // model
        rtc1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc1_1_p, handles.pBus_1_b, "bport1", 0, 0x1c170000, 0x1c170fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE cf1_1
////////////////////////////////////////////////////////////////////////////////


    const char *cf1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CompactFlashRegs"  ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cf1_1_attrList = icmNewAttrList();

    handles.cf1_1_p = icmNewPSE(
        "cf1_1"             ,   // name
        cf1_1_path          ,   // model
        cf1_1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cf1_1_p, handles.pBus_1_b, "bport1", 0, 0x1001a000, 0x1001afff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart4_1
////////////////////////////////////////////////////////////////////////////////


    const char *uart4_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart4_1_attrList = icmNewAttrList();
    icmAddStringAttr(uart4_1_attrList, "variant", "ARM");

    handles.uart4_1_p = icmNewPSE(
        "uart4_1"           ,   // name
        uart4_1_path        ,   // model
        uart4_1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart4_1_p, handles.pBus_1_b, "bport1", 0, 0x1c1b0000, 0x1c1b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE clcd_1
////////////////////////////////////////////////////////////////////////////////


    const char *clcd_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP clcd_1_attrList = icmNewAttrList();
    icmAddStringAttr(clcd_1_attrList, "resolution", "xga");
    icmAddUns64Attr(clcd_1_attrList, "noGraphics", 1LL);

    handles.clcd_1_p = icmNewPSE(
        "clcd_1"            ,   // name
        clcd_1_path         ,   // model
        clcd_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.clcd_1_p, handles.pBus_1_b, "bport1", 0, 0x1c1f0000, 0x1c1f0fff);

    icmConnectPSEBus( handles.clcd_1_p, handles.pBus_1_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt2_1
////////////////////////////////////////////////////////////////////////////////


    const char *wdt2_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt2_1_attrList = icmNewAttrList();

    handles.wdt2_1_p = icmNewPSE(
        "wdt2_1"            ,   // name
        wdt2_1_path         ,   // model
        wdt2_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt2_1_p, handles.pBus_1_b, "bport1", 0, 0x2b060000, 0x2b060fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmc1_1
////////////////////////////////////////////////////////////////////////////////


    const char *dmc1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DMemCtrlPL341"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmc1_1_attrList = icmNewAttrList();

    handles.dmc1_1_p = icmNewPSE(
        "dmc1_1"            ,   // name
        dmc1_1_path         ,   // model
        dmc1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmc1_1_p, handles.pBus_1_b, "bport1", 0, 0x2b0a0000, 0x2b0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dma0_1
////////////////////////////////////////////////////////////////////////////////


    const char *dma0_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dma0_1_attrList = icmNewAttrList();

    handles.dma0_1_p = icmNewPSE(
        "dma0_1"            ,   // name
        dma0_1_path         ,   // model
        dma0_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dma0_1_p, handles.pBus_1_b, "bport1", 0, 0x7ffb0000, 0x7ffb0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE smc1_1
////////////////////////////////////////////////////////////////////////////////


    const char *smc1_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SMemCtrlPL354"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc1_1_attrList = icmNewAttrList();

    handles.smc1_1_p = icmNewPSE(
        "smc1_1"            ,   // name
        smc1_1_path         ,   // model
        smc1_1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc1_1_p, handles.pBus_1_b, "bport1", 0, 0x7ffd0000, 0x7ffd0fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE smartLoader_1
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_1_attrList = icmNewAttrList();
    icmAddStringAttr(smartLoader_1_attrList, "command", "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0");
    icmAddUns64Attr(smartLoader_1_attrList, "physicalbase", 0x80000000LL);
    icmAddUns64Attr(smartLoader_1_attrList, "memsize", 0x80000000LL);
    icmAddUns64Attr(smartLoader_1_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_1_p = icmNewPSE(
        "smartLoader_1"     ,   // name
        smartLoader_1_path  ,   // model
        smartLoader_1_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_1_p, handles.pBus_1_b, "mport", 1, 0x0, 0xffffffff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE eth0_2
////////////////////////////////////////////////////////////////////////////////


    const char *eth0_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "smsc.ovpworld.org" ,    // vendor
        0                   ,    // library
        "LAN9118"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP eth0_2_attrList = icmNewAttrList();

    handles.eth0_2_p = icmNewPSE(
        "eth0_2"            ,   // name
        eth0_2_path         ,   // model
        eth0_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.eth0_2_p, handles.pBus_2_b, "bport1", 0, 0x1a000000, 0x1a000fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE usb0_2
////////////////////////////////////////////////////////////////////////////////


    const char *usb0_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "philips.ovpworld.org",    // vendor
        0                   ,    // library
        "ISP1761"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP usb0_2_attrList = icmNewAttrList();

    handles.usb0_2_p = icmNewPSE(
        "usb0_2"            ,   // name
        usb0_2_path         ,   // model
        usb0_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.usb0_2_p, handles.pBus_2_b, "bport1", 0, 0x1b000000, 0x1b00ffff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysRegs_2
////////////////////////////////////////////////////////////////////////////////


    const char *sysRegs_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "VexpressSysRegs"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysRegs_2_attrList = icmNewAttrList();

    handles.sysRegs_2_p = icmNewPSE(
        "sysRegs_2"         ,   // name
        sysRegs_2_path      ,   // model
        sysRegs_2_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_2_p, handles.pBus_2_b, "bport1", 0, 0x1c010000, 0x1c010fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysCtrl_2
////////////////////////////////////////////////////////////////////////////////


    const char *sysCtrl_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SysCtrlSP810"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysCtrl_2_attrList = icmNewAttrList();

    handles.sysCtrl_2_p = icmNewPSE(
        "sysCtrl_2"         ,   // name
        sysCtrl_2_path      ,   // model
        sysCtrl_2_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysCtrl_2_p, handles.pBus_2_b, "bport1", 0, 0x1c020000, 0x1c020fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE aac1_2
////////////////////////////////////////////////////////////////////////////////


    const char *aac1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "AaciPL041"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP aac1_2_attrList = icmNewAttrList();

    handles.aac1_2_p = icmNewPSE(
        "aac1_2"            ,   // name
        aac1_2_path         ,   // model
        aac1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.aac1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c040000, 0x1c040fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE mmc1_2
////////////////////////////////////////////////////////////////////////////////


    const char *mmc1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mmc1_2_attrList = icmNewAttrList();

    handles.mmc1_2_p = icmNewPSE(
        "mmc1_2"            ,   // name
        mmc1_2_path         ,   // model
        mmc1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mmc1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c050000, 0x1c050fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE kb1_2
////////////////////////////////////////////////////////////////////////////////


    const char *kb1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP kb1_2_attrList = icmNewAttrList();
    icmAddUns64Attr(kb1_2_attrList, "isKeyboard", 1LL);
    icmAddUns64Attr(kb1_2_attrList, "grabDisable", 1LL);

    handles.kb1_2_p = icmNewPSE(
        "kb1_2"             ,   // name
        kb1_2_path          ,   // model
        kb1_2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.kb1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c060000, 0x1c060fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ms1_2
////////////////////////////////////////////////////////////////////////////////


    const char *ms1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ms1_2_attrList = icmNewAttrList();
    icmAddUns64Attr(ms1_2_attrList, "isMouse", 1LL);
    icmAddUns64Attr(ms1_2_attrList, "grabDisable", 1LL);

    handles.ms1_2_p = icmNewPSE(
        "ms1_2"             ,   // name
        ms1_2_path          ,   // model
        ms1_2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ms1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c070000, 0x1c070fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart0_2
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_2_attrList = icmNewAttrList();
    icmAddStringAttr(uart0_2_attrList, "variant", "ARM");
    icmAddStringAttr(uart0_2_attrList, "outfile", "uart0_2.log");
    icmAddUns64Attr(uart0_2_attrList, "finishOnDisconnect", 1LL);

    handles.uart0_2_p = icmNewPSE(
        "uart0_2"           ,   // name
        uart0_2_path        ,   // model
        uart0_2_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_2_p, handles.pBus_2_b, "bport1", 0, 0x1c090000, 0x1c090fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart1_2
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_2_attrList = icmNewAttrList();
    icmAddStringAttr(uart1_2_attrList, "variant", "ARM");
    icmAddStringAttr(uart1_2_attrList, "outfile", "uart1_2.log");

    handles.uart1_2_p = icmNewPSE(
        "uart1_2"           ,   // name
        uart1_2_path        ,   // model
        uart1_2_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c0a0000, 0x1c0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart2_2
////////////////////////////////////////////////////////////////////////////////


    const char *uart2_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart2_2_attrList = icmNewAttrList();
    icmAddStringAttr(uart2_2_attrList, "variant", "ARM");

    handles.uart2_2_p = icmNewPSE(
        "uart2_2"           ,   // name
        uart2_2_path        ,   // model
        uart2_2_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_2_p, handles.pBus_2_b, "bport1", 0, 0x1c0b0000, 0x1c0b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart3_2
////////////////////////////////////////////////////////////////////////////////


    const char *uart3_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart3_2_attrList = icmNewAttrList();
    icmAddStringAttr(uart3_2_attrList, "variant", "ARM");

    handles.uart3_2_p = icmNewPSE(
        "uart3_2"           ,   // name
        uart3_2_path        ,   // model
        uart3_2_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_2_p, handles.pBus_2_b, "bport1", 0, 0x1c0c0000, 0x1c0c0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt1_2
////////////////////////////////////////////////////////////////////////////////


    const char *wdt1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt1_2_attrList = icmNewAttrList();

    handles.wdt1_2_p = icmNewPSE(
        "wdt1_2"            ,   // name
        wdt1_2_path         ,   // model
        wdt1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c0f0000, 0x1c0f0fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer01_2
////////////////////////////////////////////////////////////////////////////////


    const char *timer01_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer01_2_attrList = icmNewAttrList();

    handles.timer01_2_p = icmNewPSE(
        "timer01_2"         ,   // name
        timer01_2_path      ,   // model
        timer01_2_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer01_2_p, handles.pBus_2_b, "bport1", 0, 0x1c110000, 0x1c110fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer23_2
////////////////////////////////////////////////////////////////////////////////


    const char *timer23_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer23_2_attrList = icmNewAttrList();

    handles.timer23_2_p = icmNewPSE(
        "timer23_2"         ,   // name
        timer23_2_path      ,   // model
        timer23_2_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer23_2_p, handles.pBus_2_b, "bport1", 0, 0x1c120000, 0x1c120fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dvi1_2
////////////////////////////////////////////////////////////////////////////////


    const char *dvi1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SerBusDviRegs"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dvi1_2_attrList = icmNewAttrList();

    handles.dvi1_2_p = icmNewPSE(
        "dvi1_2"            ,   // name
        dvi1_2_path         ,   // model
        dvi1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dvi1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c160000, 0x1c160fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE rtc1_2
////////////////////////////////////////////////////////////////////////////////


    const char *rtc1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc1_2_attrList = icmNewAttrList();

    handles.rtc1_2_p = icmNewPSE(
        "rtc1_2"            ,   // name
        rtc1_2_path         ,   // model
        rtc1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc1_2_p, handles.pBus_2_b, "bport1", 0, 0x1c170000, 0x1c170fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE cf1_2
////////////////////////////////////////////////////////////////////////////////


    const char *cf1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CompactFlashRegs"  ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cf1_2_attrList = icmNewAttrList();

    handles.cf1_2_p = icmNewPSE(
        "cf1_2"             ,   // name
        cf1_2_path          ,   // model
        cf1_2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cf1_2_p, handles.pBus_2_b, "bport1", 0, 0x1001a000, 0x1001afff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart4_2
////////////////////////////////////////////////////////////////////////////////


    const char *uart4_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart4_2_attrList = icmNewAttrList();
    icmAddStringAttr(uart4_2_attrList, "variant", "ARM");

    handles.uart4_2_p = icmNewPSE(
        "uart4_2"           ,   // name
        uart4_2_path        ,   // model
        uart4_2_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart4_2_p, handles.pBus_2_b, "bport1", 0, 0x1c1b0000, 0x1c1b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE clcd_2
////////////////////////////////////////////////////////////////////////////////


    const char *clcd_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP clcd_2_attrList = icmNewAttrList();
    icmAddStringAttr(clcd_2_attrList, "resolution", "xga");
    icmAddUns64Attr(clcd_2_attrList, "noGraphics", 1LL);

    handles.clcd_2_p = icmNewPSE(
        "clcd_2"            ,   // name
        clcd_2_path         ,   // model
        clcd_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.clcd_2_p, handles.pBus_2_b, "bport1", 0, 0x1c1f0000, 0x1c1f0fff);

    icmConnectPSEBus( handles.clcd_2_p, handles.pBus_2_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt2_2
////////////////////////////////////////////////////////////////////////////////


    const char *wdt2_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt2_2_attrList = icmNewAttrList();

    handles.wdt2_2_p = icmNewPSE(
        "wdt2_2"            ,   // name
        wdt2_2_path         ,   // model
        wdt2_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt2_2_p, handles.pBus_2_b, "bport1", 0, 0x2b060000, 0x2b060fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmc1_2
////////////////////////////////////////////////////////////////////////////////


    const char *dmc1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DMemCtrlPL341"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmc1_2_attrList = icmNewAttrList();

    handles.dmc1_2_p = icmNewPSE(
        "dmc1_2"            ,   // name
        dmc1_2_path         ,   // model
        dmc1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmc1_2_p, handles.pBus_2_b, "bport1", 0, 0x2b0a0000, 0x2b0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dma0_2
////////////////////////////////////////////////////////////////////////////////


    const char *dma0_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dma0_2_attrList = icmNewAttrList();

    handles.dma0_2_p = icmNewPSE(
        "dma0_2"            ,   // name
        dma0_2_path         ,   // model
        dma0_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dma0_2_p, handles.pBus_2_b, "bport1", 0, 0x7ffb0000, 0x7ffb0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE smc1_2
////////////////////////////////////////////////////////////////////////////////


    const char *smc1_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SMemCtrlPL354"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc1_2_attrList = icmNewAttrList();

    handles.smc1_2_p = icmNewPSE(
        "smc1_2"            ,   // name
        smc1_2_path         ,   // model
        smc1_2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc1_2_p, handles.pBus_2_b, "bport1", 0, 0x7ffd0000, 0x7ffd0fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE smartLoader_2
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_2_attrList = icmNewAttrList();
    icmAddStringAttr(smartLoader_2_attrList, "command", "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0");
    icmAddUns64Attr(smartLoader_2_attrList, "physicalbase", 0x80000000LL);
    icmAddUns64Attr(smartLoader_2_attrList, "memsize", 0x80000000LL);
    icmAddUns64Attr(smartLoader_2_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_2_p = icmNewPSE(
        "smartLoader_2"     ,   // name
        smartLoader_2_path  ,   // model
        smartLoader_2_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_2_p, handles.pBus_2_b, "mport", 1, 0x0, 0xffffffff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE eth0_3
////////////////////////////////////////////////////////////////////////////////


    const char *eth0_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "smsc.ovpworld.org" ,    // vendor
        0                   ,    // library
        "LAN9118"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP eth0_3_attrList = icmNewAttrList();

    handles.eth0_3_p = icmNewPSE(
        "eth0_3"            ,   // name
        eth0_3_path         ,   // model
        eth0_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.eth0_3_p, handles.pBus_3_b, "bport1", 0, 0x1a000000, 0x1a000fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE usb0_3
////////////////////////////////////////////////////////////////////////////////


    const char *usb0_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "philips.ovpworld.org",    // vendor
        0                   ,    // library
        "ISP1761"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP usb0_3_attrList = icmNewAttrList();

    handles.usb0_3_p = icmNewPSE(
        "usb0_3"            ,   // name
        usb0_3_path         ,   // model
        usb0_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.usb0_3_p, handles.pBus_3_b, "bport1", 0, 0x1b000000, 0x1b00ffff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysRegs_3
////////////////////////////////////////////////////////////////////////////////


    const char *sysRegs_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "VexpressSysRegs"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysRegs_3_attrList = icmNewAttrList();

    handles.sysRegs_3_p = icmNewPSE(
        "sysRegs_3"         ,   // name
        sysRegs_3_path      ,   // model
        sysRegs_3_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysRegs_3_p, handles.pBus_3_b, "bport1", 0, 0x1c010000, 0x1c010fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE sysCtrl_3
////////////////////////////////////////////////////////////////////////////////


    const char *sysCtrl_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SysCtrlSP810"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysCtrl_3_attrList = icmNewAttrList();

    handles.sysCtrl_3_p = icmNewPSE(
        "sysCtrl_3"         ,   // name
        sysCtrl_3_path      ,   // model
        sysCtrl_3_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysCtrl_3_p, handles.pBus_3_b, "bport1", 0, 0x1c020000, 0x1c020fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE aac1_3
////////////////////////////////////////////////////////////////////////////////


    const char *aac1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "AaciPL041"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP aac1_3_attrList = icmNewAttrList();

    handles.aac1_3_p = icmNewPSE(
        "aac1_3"            ,   // name
        aac1_3_path         ,   // model
        aac1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.aac1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c040000, 0x1c040fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE mmc1_3
////////////////////////////////////////////////////////////////////////////////


    const char *mmc1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mmc1_3_attrList = icmNewAttrList();

    handles.mmc1_3_p = icmNewPSE(
        "mmc1_3"            ,   // name
        mmc1_3_path         ,   // model
        mmc1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mmc1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c050000, 0x1c050fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE kb1_3
////////////////////////////////////////////////////////////////////////////////


    const char *kb1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP kb1_3_attrList = icmNewAttrList();
    icmAddUns64Attr(kb1_3_attrList, "isKeyboard", 1LL);
    icmAddUns64Attr(kb1_3_attrList, "grabDisable", 1LL);

    handles.kb1_3_p = icmNewPSE(
        "kb1_3"             ,   // name
        kb1_3_path          ,   // model
        kb1_3_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.kb1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c060000, 0x1c060fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ms1_3
////////////////////////////////////////////////////////////////////////////////


    const char *ms1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ms1_3_attrList = icmNewAttrList();
    icmAddUns64Attr(ms1_3_attrList, "isMouse", 1LL);
    icmAddUns64Attr(ms1_3_attrList, "grabDisable", 1LL);

    handles.ms1_3_p = icmNewPSE(
        "ms1_3"             ,   // name
        ms1_3_path          ,   // model
        ms1_3_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ms1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c070000, 0x1c070fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart0_3
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_3_attrList = icmNewAttrList();
    icmAddStringAttr(uart0_3_attrList, "variant", "ARM");
    icmAddStringAttr(uart0_3_attrList, "outfile", "uart0_3.log");
    icmAddUns64Attr(uart0_3_attrList, "finishOnDisconnect", 1LL);

    handles.uart0_3_p = icmNewPSE(
        "uart0_3"           ,   // name
        uart0_3_path        ,   // model
        uart0_3_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_3_p, handles.pBus_3_b, "bport1", 0, 0x1c090000, 0x1c090fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart1_3
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_3_attrList = icmNewAttrList();
    icmAddStringAttr(uart1_3_attrList, "variant", "ARM");
    icmAddStringAttr(uart1_3_attrList, "outfile", "uart1_3.log");

    handles.uart1_3_p = icmNewPSE(
        "uart1_3"           ,   // name
        uart1_3_path        ,   // model
        uart1_3_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c0a0000, 0x1c0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart2_3
////////////////////////////////////////////////////////////////////////////////


    const char *uart2_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart2_3_attrList = icmNewAttrList();
    icmAddStringAttr(uart2_3_attrList, "variant", "ARM");

    handles.uart2_3_p = icmNewPSE(
        "uart2_3"           ,   // name
        uart2_3_path        ,   // model
        uart2_3_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_3_p, handles.pBus_3_b, "bport1", 0, 0x1c0b0000, 0x1c0b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart3_3
////////////////////////////////////////////////////////////////////////////////


    const char *uart3_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart3_3_attrList = icmNewAttrList();
    icmAddStringAttr(uart3_3_attrList, "variant", "ARM");

    handles.uart3_3_p = icmNewPSE(
        "uart3_3"           ,   // name
        uart3_3_path        ,   // model
        uart3_3_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_3_p, handles.pBus_3_b, "bport1", 0, 0x1c0c0000, 0x1c0c0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt1_3
////////////////////////////////////////////////////////////////////////////////


    const char *wdt1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt1_3_attrList = icmNewAttrList();

    handles.wdt1_3_p = icmNewPSE(
        "wdt1_3"            ,   // name
        wdt1_3_path         ,   // model
        wdt1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c0f0000, 0x1c0f0fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer01_3
////////////////////////////////////////////////////////////////////////////////


    const char *timer01_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer01_3_attrList = icmNewAttrList();

    handles.timer01_3_p = icmNewPSE(
        "timer01_3"         ,   // name
        timer01_3_path      ,   // model
        timer01_3_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer01_3_p, handles.pBus_3_b, "bport1", 0, 0x1c110000, 0x1c110fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer23_3
////////////////////////////////////////////////////////////////////////////////


    const char *timer23_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "TimerSP804"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer23_3_attrList = icmNewAttrList();

    handles.timer23_3_p = icmNewPSE(
        "timer23_3"         ,   // name
        timer23_3_path      ,   // model
        timer23_3_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer23_3_p, handles.pBus_3_b, "bport1", 0, 0x1c120000, 0x1c120fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dvi1_3
////////////////////////////////////////////////////////////////////////////////


    const char *dvi1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SerBusDviRegs"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dvi1_3_attrList = icmNewAttrList();

    handles.dvi1_3_p = icmNewPSE(
        "dvi1_3"            ,   // name
        dvi1_3_path         ,   // model
        dvi1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dvi1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c160000, 0x1c160fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE rtc1_3
////////////////////////////////////////////////////////////////////////////////


    const char *rtc1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc1_3_attrList = icmNewAttrList();

    handles.rtc1_3_p = icmNewPSE(
        "rtc1_3"            ,   // name
        rtc1_3_path         ,   // model
        rtc1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc1_3_p, handles.pBus_3_b, "bport1", 0, 0x1c170000, 0x1c170fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE cf1_3
////////////////////////////////////////////////////////////////////////////////


    const char *cf1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CompactFlashRegs"  ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cf1_3_attrList = icmNewAttrList();

    handles.cf1_3_p = icmNewPSE(
        "cf1_3"             ,   // name
        cf1_3_path          ,   // model
        cf1_3_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cf1_3_p, handles.pBus_3_b, "bport1", 0, 0x1001a000, 0x1001afff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart4_3
////////////////////////////////////////////////////////////////////////////////


    const char *uart4_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart4_3_attrList = icmNewAttrList();
    icmAddStringAttr(uart4_3_attrList, "variant", "ARM");

    handles.uart4_3_p = icmNewPSE(
        "uart4_3"           ,   // name
        uart4_3_path        ,   // model
        uart4_3_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart4_3_p, handles.pBus_3_b, "bport1", 0, 0x1c1b0000, 0x1c1b0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE clcd_3
////////////////////////////////////////////////////////////////////////////////


    const char *clcd_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP clcd_3_attrList = icmNewAttrList();
    icmAddStringAttr(clcd_3_attrList, "resolution", "xga");
    icmAddUns64Attr(clcd_3_attrList, "noGraphics", 1LL);

    handles.clcd_3_p = icmNewPSE(
        "clcd_3"            ,   // name
        clcd_3_path         ,   // model
        clcd_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.clcd_3_p, handles.pBus_3_b, "bport1", 0, 0x1c1f0000, 0x1c1f0fff);

    icmConnectPSEBus( handles.clcd_3_p, handles.pBus_3_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE wdt2_3
////////////////////////////////////////////////////////////////////////////////


    const char *wdt2_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "WdtSP805"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP wdt2_3_attrList = icmNewAttrList();

    handles.wdt2_3_p = icmNewPSE(
        "wdt2_3"            ,   // name
        wdt2_3_path         ,   // model
        wdt2_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.wdt2_3_p, handles.pBus_3_b, "bport1", 0, 0x2b060000, 0x2b060fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmc1_3
////////////////////////////////////////////////////////////////////////////////


    const char *dmc1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DMemCtrlPL341"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmc1_3_attrList = icmNewAttrList();

    handles.dmc1_3_p = icmNewPSE(
        "dmc1_3"            ,   // name
        dmc1_3_path         ,   // model
        dmc1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmc1_3_p, handles.pBus_3_b, "bport1", 0, 0x2b0a0000, 0x2b0a0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dma0_3
////////////////////////////////////////////////////////////////////////////////


    const char *dma0_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dma0_3_attrList = icmNewAttrList();

    handles.dma0_3_p = icmNewPSE(
        "dma0_3"            ,   // name
        dma0_3_path         ,   // model
        dma0_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dma0_3_p, handles.pBus_3_b, "bport1", 0, 0x7ffb0000, 0x7ffb0fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE smc1_3
////////////////////////////////////////////////////////////////////////////////


    const char *smc1_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SMemCtrlPL354"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc1_3_attrList = icmNewAttrList();

    handles.smc1_3_p = icmNewPSE(
        "smc1_3"            ,   // name
        smc1_3_path         ,   // model
        smc1_3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc1_3_p, handles.pBus_3_b, "bport1", 0, 0x7ffd0000, 0x7ffd0fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE smartLoader_3
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_3_attrList = icmNewAttrList();
    icmAddStringAttr(smartLoader_3_attrList, "command", "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0");
    icmAddUns64Attr(smartLoader_3_attrList, "physicalbase", 0x80000000LL);
    icmAddUns64Attr(smartLoader_3_attrList, "memsize", 0x80000000LL);
    icmAddUns64Attr(smartLoader_3_attrList, "boardid", 0x8e0LL);

    handles.smartLoader_3_p = icmNewPSE(
        "smartLoader_3"     ,   // name
        smartLoader_3_path  ,   // model
        smartLoader_3_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_3_p, handles.pBus_3_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectProcessorBusByName( handles.cpu_0_c, "INSTRUCTION", handles.pBus_0_b );

    icmConnectProcessorBusByName( handles.cpu_0_c, "DATA", handles.pBus_0_b );

    icmConnectProcessorBusByName( handles.cpu_1_c, "INSTRUCTION", handles.pBus_1_b );

    icmConnectProcessorBusByName( handles.cpu_1_c, "DATA", handles.pBus_1_b );

    icmConnectProcessorBusByName( handles.cpu_2_c, "INSTRUCTION", handles.pBus_2_b );

    icmConnectProcessorBusByName( handles.cpu_2_c, "DATA", handles.pBus_2_b );

    icmConnectProcessorBusByName( handles.cpu_3_c, "INSTRUCTION", handles.pBus_3_b );

    icmConnectProcessorBusByName( handles.cpu_3_c, "DATA", handles.pBus_3_b );

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor0_0
////////////////////////////////////////////////////////////////////////////////

    handles.nor0_0_m = icmNewMemory("nor0_0", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.nor0bus_0_b, "sp1", handles.nor0_0_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor1_0
////////////////////////////////////////////////////////////////////////////////

    handles.nor1_0_m = icmNewMemory("nor1_0", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_0_b, "sp1", handles.nor1_0_m, 0xc000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory sram1_0
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_0_m = icmNewMemory("sram1_0", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_0_b, "sp1", handles.sram1_0_m, 0x14000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory vram1_0
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_0_m = icmNewMemory("vram1_0", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.pBus_0_b, "sp1", handles.vram1_0_m, 0x18000000);

////////////////////////////////////////////////////////////////////////////////
//                              Memory ddr2ram_0
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_0_m = icmNewMemory("ddr2ram_0", 0x7, 0x7fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_0_b, "sp1", handles.ddr2ram_0_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor0_1
////////////////////////////////////////////////////////////////////////////////

    handles.nor0_1_m = icmNewMemory("nor0_1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.nor0bus_1_b, "sp1", handles.nor0_1_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor1_1
////////////////////////////////////////////////////////////////////////////////

    handles.nor1_1_m = icmNewMemory("nor1_1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_1_b, "sp1", handles.nor1_1_m, 0xc000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory sram1_1
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_1_m = icmNewMemory("sram1_1", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_1_b, "sp1", handles.sram1_1_m, 0x14000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory vram1_1
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_1_m = icmNewMemory("vram1_1", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.pBus_1_b, "sp1", handles.vram1_1_m, 0x18000000);

////////////////////////////////////////////////////////////////////////////////
//                              Memory ddr2ram_1
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_1_m = icmNewMemory("ddr2ram_1", 0x7, 0x7fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_1_b, "sp1", handles.ddr2ram_1_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor0_2
////////////////////////////////////////////////////////////////////////////////

    handles.nor0_2_m = icmNewMemory("nor0_2", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.nor0bus_2_b, "sp1", handles.nor0_2_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor1_2
////////////////////////////////////////////////////////////////////////////////

    handles.nor1_2_m = icmNewMemory("nor1_2", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_2_b, "sp1", handles.nor1_2_m, 0xc000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory sram1_2
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_2_m = icmNewMemory("sram1_2", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_2_b, "sp1", handles.sram1_2_m, 0x14000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory vram1_2
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_2_m = icmNewMemory("vram1_2", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.pBus_2_b, "sp1", handles.vram1_2_m, 0x18000000);

////////////////////////////////////////////////////////////////////////////////
//                              Memory ddr2ram_2
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_2_m = icmNewMemory("ddr2ram_2", 0x7, 0x7fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_2_b, "sp1", handles.ddr2ram_2_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor0_3
////////////////////////////////////////////////////////////////////////////////

    handles.nor0_3_m = icmNewMemory("nor0_3", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.nor0bus_3_b, "sp1", handles.nor0_3_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor1_3
////////////////////////////////////////////////////////////////////////////////

    handles.nor1_3_m = icmNewMemory("nor1_3", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_3_b, "sp1", handles.nor1_3_m, 0xc000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory sram1_3
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_3_m = icmNewMemory("sram1_3", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_3_b, "sp1", handles.sram1_3_m, 0x14000000);

////////////////////////////////////////////////////////////////////////////////
//                               Memory vram1_3
////////////////////////////////////////////////////////////////////////////////

    handles.vram1_3_m = icmNewMemory("vram1_3", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.pBus_3_b, "sp1", handles.vram1_3_m, 0x18000000);

////////////////////////////////////////////////////////////////////////////////
//                              Memory ddr2ram_3
////////////////////////////////////////////////////////////////////////////////

    handles.ddr2ram_3_m = icmNewMemory("ddr2ram_3", 0x7, 0x7fffffff);


    icmConnectMemoryToBus( handles.ddr2bus_3_b, "sp1", handles.ddr2ram_3_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Bridge_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.nor0bus_0_b, "nor0Bridge_0", "sp", "mp", 0x0, 0x3ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Remap_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.nor0bus_0_b, "nor0Remap_0", "sp", "mp", 0x0, 0x3ffffff, 0x8000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Bridge_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.ddr2bus_0_b, "ddr2Bridge_0", "sp", "mp", 0x0, 0x7fffffff, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap1_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.ddr2bus_0_b, "ddr2Remap1_0", "sp", "mp", 0x0, 0x7fffffff, 0x800000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap2_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.ddr2bus_0_b, "ddr2Remap2_0", "sp", "mp", 0x0, 0x7fffffff, 0x880000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap3_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.ddr2bus_0_b, "ddr2Remap3_0", "sp", "mp", 0x0, 0x7fffffff, 0x8000000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap4_0
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_0_b, handles.ddr2bus_0_b, "ddr2Remap4_0", "sp", "mp", 0x0, 0x7fffffff, 0x8080000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Bridge_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.nor0bus_1_b, "nor0Bridge_1", "sp", "mp", 0x0, 0x3ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Remap_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.nor0bus_1_b, "nor0Remap_1", "sp", "mp", 0x0, 0x3ffffff, 0x8000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Bridge_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.ddr2bus_1_b, "ddr2Bridge_1", "sp", "mp", 0x0, 0x7fffffff, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap1_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.ddr2bus_1_b, "ddr2Remap1_1", "sp", "mp", 0x0, 0x7fffffff, 0x800000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap2_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.ddr2bus_1_b, "ddr2Remap2_1", "sp", "mp", 0x0, 0x7fffffff, 0x880000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap3_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.ddr2bus_1_b, "ddr2Remap3_1", "sp", "mp", 0x0, 0x7fffffff, 0x8000000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap4_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_1_b, handles.ddr2bus_1_b, "ddr2Remap4_1", "sp", "mp", 0x0, 0x7fffffff, 0x8080000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Bridge_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.nor0bus_2_b, "nor0Bridge_2", "sp", "mp", 0x0, 0x3ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Remap_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.nor0bus_2_b, "nor0Remap_2", "sp", "mp", 0x0, 0x3ffffff, 0x8000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Bridge_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.ddr2bus_2_b, "ddr2Bridge_2", "sp", "mp", 0x0, 0x7fffffff, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap1_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.ddr2bus_2_b, "ddr2Remap1_2", "sp", "mp", 0x0, 0x7fffffff, 0x800000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap2_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.ddr2bus_2_b, "ddr2Remap2_2", "sp", "mp", 0x0, 0x7fffffff, 0x880000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap3_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.ddr2bus_2_b, "ddr2Remap3_2", "sp", "mp", 0x0, 0x7fffffff, 0x8000000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap4_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_2_b, handles.ddr2bus_2_b, "ddr2Remap4_2", "sp", "mp", 0x0, 0x7fffffff, 0x8080000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Bridge_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.nor0bus_3_b, "nor0Bridge_3", "sp", "mp", 0x0, 0x3ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge nor0Remap_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.nor0bus_3_b, "nor0Remap_3", "sp", "mp", 0x0, 0x3ffffff, 0x8000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Bridge_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.ddr2bus_3_b, "ddr2Bridge_3", "sp", "mp", 0x0, 0x7fffffff, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap1_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.ddr2bus_3_b, "ddr2Remap1_3", "sp", "mp", 0x0, 0x7fffffff, 0x800000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap2_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.ddr2bus_3_b, "ddr2Remap2_3", "sp", "mp", 0x0, 0x7fffffff, 0x880000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap3_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.ddr2bus_3_b, "ddr2Remap3_3", "sp", "mp", 0x0, 0x7fffffff, 0x8000000000ULL);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge ddr2Remap4_3
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.pBus_3_b, handles.ddr2bus_3_b, "ddr2Remap4_3", "sp", "mp", 0x0, 0x7fffffff, 0x8080000000ULL);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.ir2_0_n = icmNewNet("ir2_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir2_0_n, "SPI34", 0);

    icmConnectPSENet( handles.timer01_0_p, handles.ir2_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir3_0_n = icmNewNet("ir3_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir3_0_n, "SPI35", 0);

    icmConnectPSENet( handles.timer23_0_p, handles.ir3_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir4_0_n = icmNewNet("ir4_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir4_0_n, "SPI36", 0);

    icmConnectPSENet( handles.rtc1_0_p, handles.ir4_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir5_0_n = icmNewNet("ir5_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir5_0_n, "SPI37", 0);

    icmConnectPSENet( handles.uart0_0_p, handles.ir5_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir6_0_n = icmNewNet("ir6_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir6_0_n, "SPI38", 0);

    icmConnectPSENet( handles.uart1_0_p, handles.ir6_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir7_0_n = icmNewNet("ir7_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir7_0_n, "SPI39", 0);

    icmConnectPSENet( handles.uart2_0_p, handles.ir7_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir8_0_n = icmNewNet("ir8_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir8_0_n, "SPI40", 0);

    icmConnectPSENet( handles.uart3_0_p, handles.ir8_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir9_0_n = icmNewNet("ir9_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir9_0_n, "SPI41", 0);

    icmConnectPSENet( handles.mmc1_0_p, handles.ir9_0_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir10_0_n = icmNewNet("ir10_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir10_0_n, "SPI42", 0);

    icmConnectPSENet( handles.mmc1_0_p, handles.ir10_0_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir12_0_n = icmNewNet("ir12_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir12_0_n, "SPI44", 0);

    icmConnectPSENet( handles.kb1_0_p, handles.ir12_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir13_0_n = icmNewNet("ir13_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir13_0_n, "SPI45", 0);

    icmConnectPSENet( handles.ms1_0_p, handles.ir13_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir14_0_n = icmNewNet("ir14_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir14_0_n, "SPI46", 0);

    icmConnectPSENet( handles.clcd_0_p, handles.ir14_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir15_0_n = icmNewNet("ir15_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir15_0_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_0_p, handles.ir15_0_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir16_0_n = icmNewNet("ir16_0" );

    icmConnectProcessorNet( handles.cpu_0_c, handles.ir16_0_n, "SPI48", 0);

    icmConnectPSENet( handles.usb0_0_p, handles.ir16_0_n, "hc_irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir2_1_n = icmNewNet("ir2_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir2_1_n, "SPI34", 0);

    icmConnectPSENet( handles.timer01_1_p, handles.ir2_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir3_1_n = icmNewNet("ir3_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir3_1_n, "SPI35", 0);

    icmConnectPSENet( handles.timer23_1_p, handles.ir3_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir4_1_n = icmNewNet("ir4_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir4_1_n, "SPI36", 0);

    icmConnectPSENet( handles.rtc1_1_p, handles.ir4_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir5_1_n = icmNewNet("ir5_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir5_1_n, "SPI37", 0);

    icmConnectPSENet( handles.uart0_1_p, handles.ir5_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir6_1_n = icmNewNet("ir6_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir6_1_n, "SPI38", 0);

    icmConnectPSENet( handles.uart1_1_p, handles.ir6_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir7_1_n = icmNewNet("ir7_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir7_1_n, "SPI39", 0);

    icmConnectPSENet( handles.uart2_1_p, handles.ir7_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir8_1_n = icmNewNet("ir8_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir8_1_n, "SPI40", 0);

    icmConnectPSENet( handles.uart3_1_p, handles.ir8_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir9_1_n = icmNewNet("ir9_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir9_1_n, "SPI41", 0);

    icmConnectPSENet( handles.mmc1_1_p, handles.ir9_1_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir10_1_n = icmNewNet("ir10_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir10_1_n, "SPI42", 0);

    icmConnectPSENet( handles.mmc1_1_p, handles.ir10_1_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir12_1_n = icmNewNet("ir12_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir12_1_n, "SPI44", 0);

    icmConnectPSENet( handles.kb1_1_p, handles.ir12_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir13_1_n = icmNewNet("ir13_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir13_1_n, "SPI45", 0);

    icmConnectPSENet( handles.ms1_1_p, handles.ir13_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir14_1_n = icmNewNet("ir14_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir14_1_n, "SPI46", 0);

    icmConnectPSENet( handles.clcd_1_p, handles.ir14_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir15_1_n = icmNewNet("ir15_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir15_1_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_1_p, handles.ir15_1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir16_1_n = icmNewNet("ir16_1" );

    icmConnectProcessorNet( handles.cpu_1_c, handles.ir16_1_n, "SPI48", 0);

    icmConnectPSENet( handles.usb0_1_p, handles.ir16_1_n, "hc_irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir2_2_n = icmNewNet("ir2_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir2_2_n, "SPI34", 0);

    icmConnectPSENet( handles.timer01_2_p, handles.ir2_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir3_2_n = icmNewNet("ir3_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir3_2_n, "SPI35", 0);

    icmConnectPSENet( handles.timer23_2_p, handles.ir3_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir4_2_n = icmNewNet("ir4_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir4_2_n, "SPI36", 0);

    icmConnectPSENet( handles.rtc1_2_p, handles.ir4_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir5_2_n = icmNewNet("ir5_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir5_2_n, "SPI37", 0);

    icmConnectPSENet( handles.uart0_2_p, handles.ir5_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir6_2_n = icmNewNet("ir6_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir6_2_n, "SPI38", 0);

    icmConnectPSENet( handles.uart1_2_p, handles.ir6_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir7_2_n = icmNewNet("ir7_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir7_2_n, "SPI39", 0);

    icmConnectPSENet( handles.uart2_2_p, handles.ir7_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir8_2_n = icmNewNet("ir8_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir8_2_n, "SPI40", 0);

    icmConnectPSENet( handles.uart3_2_p, handles.ir8_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir9_2_n = icmNewNet("ir9_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir9_2_n, "SPI41", 0);

    icmConnectPSENet( handles.mmc1_2_p, handles.ir9_2_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir10_2_n = icmNewNet("ir10_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir10_2_n, "SPI42", 0);

    icmConnectPSENet( handles.mmc1_2_p, handles.ir10_2_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir12_2_n = icmNewNet("ir12_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir12_2_n, "SPI44", 0);

    icmConnectPSENet( handles.kb1_2_p, handles.ir12_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir13_2_n = icmNewNet("ir13_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir13_2_n, "SPI45", 0);

    icmConnectPSENet( handles.ms1_2_p, handles.ir13_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir14_2_n = icmNewNet("ir14_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir14_2_n, "SPI46", 0);

    icmConnectPSENet( handles.clcd_2_p, handles.ir14_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir15_2_n = icmNewNet("ir15_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir15_2_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_2_p, handles.ir15_2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir16_2_n = icmNewNet("ir16_2" );

    icmConnectProcessorNet( handles.cpu_2_c, handles.ir16_2_n, "SPI48", 0);

    icmConnectPSENet( handles.usb0_2_p, handles.ir16_2_n, "hc_irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir2_3_n = icmNewNet("ir2_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir2_3_n, "SPI34", 0);

    icmConnectPSENet( handles.timer01_3_p, handles.ir2_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir3_3_n = icmNewNet("ir3_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir3_3_n, "SPI35", 0);

    icmConnectPSENet( handles.timer23_3_p, handles.ir3_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir4_3_n = icmNewNet("ir4_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir4_3_n, "SPI36", 0);

    icmConnectPSENet( handles.rtc1_3_p, handles.ir4_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir5_3_n = icmNewNet("ir5_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir5_3_n, "SPI37", 0);

    icmConnectPSENet( handles.uart0_3_p, handles.ir5_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir6_3_n = icmNewNet("ir6_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir6_3_n, "SPI38", 0);

    icmConnectPSENet( handles.uart1_3_p, handles.ir6_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir7_3_n = icmNewNet("ir7_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir7_3_n, "SPI39", 0);

    icmConnectPSENet( handles.uart2_3_p, handles.ir7_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir8_3_n = icmNewNet("ir8_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir8_3_n, "SPI40", 0);

    icmConnectPSENet( handles.uart3_3_p, handles.ir8_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir9_3_n = icmNewNet("ir9_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir9_3_n, "SPI41", 0);

    icmConnectPSENet( handles.mmc1_3_p, handles.ir9_3_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir10_3_n = icmNewNet("ir10_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir10_3_n, "SPI42", 0);

    icmConnectPSENet( handles.mmc1_3_p, handles.ir10_3_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir12_3_n = icmNewNet("ir12_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir12_3_n, "SPI44", 0);

    icmConnectPSENet( handles.kb1_3_p, handles.ir12_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir13_3_n = icmNewNet("ir13_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir13_3_n, "SPI45", 0);

    icmConnectPSENet( handles.ms1_3_p, handles.ir13_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir14_3_n = icmNewNet("ir14_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir14_3_n, "SPI46", 0);

    icmConnectPSENet( handles.clcd_3_p, handles.ir14_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir15_3_n = icmNewNet("ir15_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir15_3_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_3_p, handles.ir15_3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir16_3_n = icmNewNet("ir16_3" );

    icmConnectProcessorNet( handles.cpu_3_c, handles.ir16_3_n, "SPI48", 0);

    icmConnectPSENet( handles.usb0_3_p, handles.ir16_3_n, "hc_irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.wprot_0_n = icmNewNet("wprot_0" );

    icmConnectPSENet( handles.sysRegs_0_p, handles.wprot_0_n, "wprot", 0);

    icmConnectPSENet( handles.mmc1_0_p, handles.wprot_0_n, "wprot", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cardin_0_n = icmNewNet("cardin_0" );

    icmConnectPSENet( handles.sysRegs_0_p, handles.cardin_0_n, "cardin", 0);

    icmConnectPSENet( handles.mmc1_0_p, handles.cardin_0_n, "cardin", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.wprot_1_n = icmNewNet("wprot_1" );

    icmConnectPSENet( handles.sysRegs_1_p, handles.wprot_1_n, "wprot", 0);

    icmConnectPSENet( handles.mmc1_1_p, handles.wprot_1_n, "wprot", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cardin_1_n = icmNewNet("cardin_1" );

    icmConnectPSENet( handles.sysRegs_1_p, handles.cardin_1_n, "cardin", 0);

    icmConnectPSENet( handles.mmc1_1_p, handles.cardin_1_n, "cardin", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.wprot_2_n = icmNewNet("wprot_2" );

    icmConnectPSENet( handles.sysRegs_2_p, handles.wprot_2_n, "wprot", 0);

    icmConnectPSENet( handles.mmc1_2_p, handles.wprot_2_n, "wprot", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cardin_2_n = icmNewNet("cardin_2" );

    icmConnectPSENet( handles.sysRegs_2_p, handles.cardin_2_n, "cardin", 0);

    icmConnectPSENet( handles.mmc1_2_p, handles.cardin_2_n, "cardin", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.wprot_3_n = icmNewNet("wprot_3" );

    icmConnectPSENet( handles.sysRegs_3_p, handles.wprot_3_n, "wprot", 0);

    icmConnectPSENet( handles.mmc1_3_p, handles.wprot_3_n, "wprot", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cardin_3_n = icmNewNet("cardin_3" );

    icmConnectPSENet( handles.sysRegs_3_p, handles.cardin_3_n, "cardin", 0);

    icmConnectPSENet( handles.mmc1_3_p, handles.cardin_3_n, "cardin", 0);
}
