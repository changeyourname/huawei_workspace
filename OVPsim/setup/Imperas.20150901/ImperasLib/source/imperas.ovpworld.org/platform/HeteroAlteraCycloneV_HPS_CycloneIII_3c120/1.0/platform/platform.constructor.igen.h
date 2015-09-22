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

    icmInitAttrs HeteroAlteraCycloneV_HPS_CycloneIII_3c120_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, HeteroAlteraCycloneV_HPS_CycloneIII_3c120_attrs, 0, 0, "HeteroAlteraCycloneV_HPS_CycloneIII_3c120");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "This platform merges the Altera Cyclone V (ARM) and Cyclone III (Nios_II) processor systems");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux.");
    }
    icmSetPlatformStatus(ICM_IMPERAS,ICM_FIX,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                Bus smbus_HPS
////////////////////////////////////////////////////////////////////////////////


    handles.smbus_HPS_b = icmNewBus( "smbus_HPS", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Bus smbus_3c120
////////////////////////////////////////////////////////////////////////////////


    handles.smbus_3c120_b = icmNewBus( "smbus_3c120", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Bus iobus_3c120
////////////////////////////////////////////////////////////////////////////////


    handles.iobus_3c120_b = icmNewBus( "iobus_3c120", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Bus dbus_3c120
////////////////////////////////////////////////////////////////////////////////


    handles.dbus_3c120_b = icmNewBus( "dbus_3c120", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Bus ibus_3c120
////////////////////////////////////////////////////////////////////////////////


    handles.ibus_3c120_b = icmNewBus( "ibus_3c120", 32);

////////////////////////////////////////////////////////////////////////////////
//                            Processor cpu_A9MPx2
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_A9MPx2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_A9MPx2_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_A9MPx2_attrList, "variant", "Cortex-A9MPx2");
    icmAddStringAttr(cpu_A9MPx2_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_A9MPx2_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_A9MPx2_attrList, "showHiddenRegs", 0LL);
    icmAddUns64Attr(cpu_A9MPx2_attrList, "override_CBAR", 0xfffec000LL);
    icmAddUns64Attr(cpu_A9MPx2_attrList, "override_GICD_TYPER_ITLines", 6LL);
    icmAddDoubleAttr(cpu_A9MPx2_attrList, "mips", 100.000000);
    icmAddStringAttr(cpu_A9MPx2_attrList, "endian", "little");
    icmNewProcAttrs cpu_A9MPx2_attrs = ICM_ATTR_SIMEX;


    handles.cpu_A9MPx2_c = icmNewProcessor(
        "cpu_A9MPx2"        ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        cpu_A9MPx2_path     ,   // model
        0, 
        cpu_A9MPx2_attrs    ,   // procAttrs
        cpu_A9MPx2_attrList ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                            Processor cpu_Nios_II
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_Nios_II_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "nios_ii"           ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_Nios_II_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_Nios_II_attrList, "variant", "Nios_II_F");
    icmAddUns64Attr(cpu_Nios_II_attrList, "BREAK_VECTOR", 0xc7fff820LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "EXCEPTION_VECTOR", 0xd0000020LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "RESET_VECTOR", 0xc2800000LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "FAST_TLB_MISS_EXCEPTION_VECTOR", 0xc7fff400LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "HW_DIVIDE", 1LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "HW_MULTIPLY", 1LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "HW_MULX", 0LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "INCLUDE_MMU", 1LL);
    icmAddStringAttr(cpu_Nios_II_attrList, "MMU_TLB_SET_ASSOCIATIVITY", "16");
    icmAddStringAttr(cpu_Nios_II_attrList, "MMU_TLB_ENTRIES", "128");
    icmAddUns64Attr(cpu_Nios_II_attrList, "MMU_PID_BITS", 8LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "DATA_ADDR_WIDTH", 29LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "INST_ADDR_WIDTH", 29LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "TEST_HALT_EXIT", 1LL);
    icmAddUns64Attr(cpu_Nios_II_attrList, "EXCEPTION_EXTRA_INFORMATION", 1LL);
    icmAddDoubleAttr(cpu_Nios_II_attrList, "mips", 125.000000);
    icmAddStringAttr(cpu_Nios_II_attrList, "endian", "little");
    icmNewProcAttrs cpu_Nios_II_attrs = ICM_ATTR_SIMEX;


    handles.cpu_Nios_II_c = icmNewProcessor(
        "cpu_Nios_II"       ,   // name
        0,
        1                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        cpu_Nios_II_path    ,   // model
        0, 
        cpu_Nios_II_attrs   ,   // procAttrs
        cpu_Nios_II_attrList,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                   PSE L2
////////////////////////////////////////////////////////////////////////////////


    const char *L2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "L2CachePL310"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP L2_attrList = icmNewAttrList();

    handles.L2_p = icmNewPSE(
        "L2"                ,   // name
        L2_path             ,   // model
        L2_attrList         ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.L2_p, handles.smbus_HPS_b, "bport1", 0, 0xfffef000, 0xfffeffff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer0
////////////////////////////////////////////////////////////////////////////////


    const char *timer0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "dw-apb-timer"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer0_attrList = icmNewAttrList();

    handles.timer0_p = icmNewPSE(
        "timer0"            ,   // name
        timer0_path         ,   // model
        timer0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer0_p, handles.smbus_HPS_b, "bport1", 0, 0xffc08000, 0xffc08fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer1
////////////////////////////////////////////////////////////////////////////////


    const char *timer1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "dw-apb-timer"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer1_attrList = icmNewAttrList();

    handles.timer1_p = icmNewPSE(
        "timer1"            ,   // name
        timer1_path         ,   // model
        timer1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer1_p, handles.smbus_HPS_b, "bport1", 0, 0xffc09000, 0xffc09fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer2
////////////////////////////////////////////////////////////////////////////////


    const char *timer2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "dw-apb-timer"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer2_attrList = icmNewAttrList();

    handles.timer2_p = icmNewPSE(
        "timer2"            ,   // name
        timer2_path         ,   // model
        timer2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer2_p, handles.smbus_HPS_b, "bport1", 0, 0xffd00000, 0xffd00fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer3
////////////////////////////////////////////////////////////////////////////////


    const char *timer3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "dw-apb-timer"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer3_attrList = icmNewAttrList();

    handles.timer3_p = icmNewPSE(
        "timer3"            ,   // name
        timer3_path         ,   // model
        timer3_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer3_p, handles.smbus_HPS_b, "bport1", 0, 0xffd01000, 0xffd01fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart0
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "dw-apb-uart"       ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_attrList = icmNewAttrList();
    icmAddStringAttr(uart0_attrList, "outfile", "uart0.log");
    icmAddUns64Attr(uart0_attrList, "console", 1LL);
    icmAddUns64Attr(uart0_attrList, "finishOnDisconnect", 1LL);

    handles.uart0_p = icmNewPSE(
        "uart0"             ,   // name
        uart0_path          ,   // model
        uart0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_p, handles.smbus_HPS_b, "bport1", 0, 0xffc02000, 0xffc02fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart1
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "dw-apb-uart"       ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_attrList = icmNewAttrList();
    icmAddStringAttr(uart1_attrList, "outfile", "uart1.log");
    icmAddUns64Attr(uart1_attrList, "console", 1LL);

    handles.uart1_p = icmNewPSE(
        "uart1"             ,   // name
        uart1_path          ,   // model
        uart1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_p, handles.smbus_HPS_b, "bport1", 0, 0xffc03000, 0xffc03fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE RSTMGR0
////////////////////////////////////////////////////////////////////////////////


    const char *RSTMGR0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "RSTMGR"            ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP RSTMGR0_attrList = icmNewAttrList();

    handles.RSTMGR0_p = icmNewPSE(
        "RSTMGR0"           ,   // name
        RSTMGR0_path        ,   // model
        RSTMGR0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.RSTMGR0_p, handles.smbus_HPS_b, "bport1", 0, 0xffd05000, 0xffd05fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE SYSMGR0
////////////////////////////////////////////////////////////////////////////////


    const char *SYSMGR0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP SYSMGR0_attrList = icmNewAttrList();

    handles.SYSMGR0_p = icmNewPSE(
        "SYSMGR0"           ,   // name
        SYSMGR0_path        ,   // model
        SYSMGR0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.SYSMGR0_p, handles.smbus_HPS_b, "bport1", 0, 0xffd08000, 0xffd08fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE CLKMGR0
////////////////////////////////////////////////////////////////////////////////


    const char *CLKMGR0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP CLKMGR0_attrList = icmNewAttrList();

    handles.CLKMGR0_p = icmNewPSE(
        "CLKMGR0"           ,   // name
        CLKMGR0_path        ,   // model
        CLKMGR0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CLKMGR0_p, handles.smbus_HPS_b, "bport1", 0, 0xffd04000, 0xffd04fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE pdma0
////////////////////////////////////////////////////////////////////////////////


    const char *pdma0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP pdma0_attrList = icmNewAttrList();

    handles.pdma0_p = icmNewPSE(
        "pdma0"             ,   // name
        pdma0_path          ,   // model
        pdma0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pdma0_p, handles.smbus_HPS_b, "bport1", 0, 0xffe01000, 0xffe01fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE gmac0
////////////////////////////////////////////////////////////////////////////////


    const char *gmac0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP gmac0_attrList = icmNewAttrList();

    handles.gmac0_p = icmNewPSE(
        "gmac0"             ,   // name
        gmac0_path          ,   // model
        gmac0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.gmac0_p, handles.smbus_HPS_b, "bport1", 0, 0xff700000, 0xff700fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE emac0_dma
////////////////////////////////////////////////////////////////////////////////


    const char *emac0_dma_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP emac0_dma_attrList = icmNewAttrList();

    handles.emac0_dma_p = icmNewPSE(
        "emac0_dma"         ,   // name
        emac0_dma_path      ,   // model
        emac0_dma_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.emac0_dma_p, handles.smbus_HPS_b, "bport1", 0, 0xff701000, 0xff701fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE gmac1
////////////////////////////////////////////////////////////////////////////////


    const char *gmac1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP gmac1_attrList = icmNewAttrList();

    handles.gmac1_p = icmNewPSE(
        "gmac1"             ,   // name
        gmac1_path          ,   // model
        gmac1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.gmac1_p, handles.smbus_HPS_b, "bport1", 0, 0xff702000, 0xff702fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE emac1_dma
////////////////////////////////////////////////////////////////////////////////


    const char *emac1_dma_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP emac1_dma_attrList = icmNewAttrList();

    handles.emac1_dma_p = icmNewPSE(
        "emac1_dma"         ,   // name
        emac1_dma_path      ,   // model
        emac1_dma_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.emac1_dma_p, handles.smbus_HPS_b, "bport1", 0, 0xff703000, 0xff703fff);

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
    icmAddUns64Attr(smartLoader_attrList, "boardid", 0xffffffffLL);
    icmAddStringAttr(smartLoader_attrList, "kernel", "zImage");
    icmAddStringAttr(smartLoader_attrList, "initrd", "fs.img");
    icmAddStringAttr(smartLoader_attrList, "command", "mem=1024M console=ttyS0");
    icmAddUns64Attr(smartLoader_attrList, "physicalbase", 0x0LL);
    icmAddUns64Attr(smartLoader_attrList, "memsize", 0x40000000LL);
    icmAddUns64Attr(smartLoader_attrList, "disable", 0LL);

    handles.smartLoader_p = icmNewPSE(
        "smartLoader"       ,   // name
        smartLoader_path    ,   // model
        smartLoader_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smartLoader_p, handles.smbus_HPS_b, "mport", 1, 0x0, 0xffffffff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE uart_s1
////////////////////////////////////////////////////////////////////////////////


    const char *uart_s1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart_s1_attrList = icmNewAttrList();

    handles.uart_s1_p = icmNewPSE(
        "uart_s1"           ,   // name
        uart_s1_path        ,   // model
        uart_s1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart_s1_p, handles.iobus_3c120_b, "sp1", 0, 0x4c80, 0x4c9f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE sysid
////////////////////////////////////////////////////////////////////////////////


    const char *sysid_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "SystemIDCore"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sysid_attrList = icmNewAttrList();

    handles.sysid_p = icmNewPSE(
        "sysid"             ,   // name
        sysid_path          ,   // model
        sysid_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysid_p, handles.iobus_3c120_b, "sp1", 0, 0x4d40, 0x4d47);

////////////////////////////////////////////////////////////////////////////////
//                                PSE jtag_uart
////////////////////////////////////////////////////////////////////////////////


    const char *jtag_uart_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "JtagUart"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP jtag_uart_attrList = icmNewAttrList();
    icmAddUns64Attr(jtag_uart_attrList, "writeIRQThreshold", 8LL);
    icmAddUns64Attr(jtag_uart_attrList, "readIRQThreshold", 8LL);
    icmAddUns64Attr(jtag_uart_attrList, "writeBufferDepth", 64LL);
    icmAddUns64Attr(jtag_uart_attrList, "readBufferDepth", 64LL);
    icmAddUns64Attr(jtag_uart_attrList, "console", 1LL);
    icmAddStringAttr(jtag_uart_attrList, "outfile", "jtag_uart.log");
    icmAddUns64Attr(jtag_uart_attrList, "finishOnDisconnect", 1LL);

    handles.jtag_uart_p = icmNewPSE(
        "jtag_uart"         ,   // name
        jtag_uart_path      ,   // model
        jtag_uart_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.jtag_uart_p, handles.iobus_3c120_b, "sp1", 0, 0x4d50, 0x4d57);

////////////////////////////////////////////////////////////////////////////////
//                                PSE timer_1ms
////////////////////////////////////////////////////////////////////////////////


    const char *timer_1ms_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "IntervalTimer32Core",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP timer_1ms_attrList = icmNewAttrList();

    handles.timer_1ms_p = icmNewPSE(
        "timer_1ms"         ,   // name
        timer_1ms_path      ,   // model
        timer_1ms_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.timer_1ms_p, handles.iobus_3c120_b, "sp1", 0, 0x400000, 0x400017);

    icmConnectProcessorBusByName( handles.cpu_A9MPx2_c, "INSTRUCTION", handles.smbus_HPS_b );

    icmConnectProcessorBusByName( handles.cpu_A9MPx2_c, "DATA", handles.smbus_HPS_b );

    icmConnectProcessorBusByName( handles.cpu_Nios_II_c, "INSTRUCTION", handles.ibus_3c120_b );

    icmConnectProcessorBusByName( handles.cpu_Nios_II_c, "DATA", handles.dbus_3c120_b );

////////////////////////////////////////////////////////////////////////////////
//                                Memory sram1
////////////////////////////////////////////////////////////////////////////////

    handles.sram1_m = icmNewMemory("sram1", 0x7, 0x3fffffff);


    icmConnectMemoryToBus( handles.smbus_HPS_b, "sp1", handles.sram1_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                          Memory pb_cpu_to_ddr2_bot
////////////////////////////////////////////////////////////////////////////////

    handles.pb_cpu_to_ddr2_bot_m = icmNewMemory("pb_cpu_to_ddr2_bot", 0x7, 0x7ffffff);


    icmConnectMemoryToBus( handles.smbus_3c120_b, "sp1", handles.pb_cpu_to_ddr2_bot_m, 0x10000000);

////////////////////////////////////////////////////////////////////////////////
//                           Memory tlb_miss_ram_1k
////////////////////////////////////////////////////////////////////////////////

    handles.tlb_miss_ram_1k_m = icmNewMemory("tlb_miss_ram_1k", 0x7, 0x3ff);


    icmConnectMemoryToBus( handles.smbus_3c120_b, "sp1", handles.tlb_miss_ram_1k_m, 0x7fff400);

////////////////////////////////////////////////////////////////////////////////
//                            Memory flash_mem_64m
////////////////////////////////////////////////////////////////////////////////

    handles.flash_mem_64m_m = icmNewMemory("flash_mem_64m", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.smbus_3c120_b, "sp1", handles.flash_mem_64m_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                        Bridge pb_ibus_to_smbus_3c120
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.ibus_3c120_b, handles.smbus_3c120_b, "pb_ibus_to_smbus_3c120", "sp1", "mp1", 0x0, 0xffffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                       Bridge pb_dbus_to_smbus_3c120_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.dbus_3c120_b, handles.smbus_3c120_b, "pb_dbus_to_smbus_3c120_1", "sp1", "mp1", 0x0, 0x7ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                       Bridge pb_dbus_to_smbus_3c120_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.dbus_3c120_b, handles.smbus_3c120_b, "pb_dbus_to_smbus_3c120_2", "sp1", "mp1", 0x8800000, 0xffffffff, 0x8800000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge pb_cpu_to_io
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.dbus_3c120_b, handles.iobus_3c120_b, "pb_cpu_to_io", "sp1", "mp1", 0x0, 0x7fffff, 0x8000000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.ir199_n = icmNewNet("ir199" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.ir199_n, "SPI199", 0);

    icmConnectPSENet( handles.timer0_p, handles.ir199_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir200_n = icmNewNet("ir200" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.ir200_n, "SPI200", 0);

    icmConnectPSENet( handles.timer1_p, handles.ir200_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir201_n = icmNewNet("ir201" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.ir201_n, "SPI201", 0);

    icmConnectPSENet( handles.timer2_p, handles.ir201_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir202_n = icmNewNet("ir202" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.ir202_n, "SPI202", 0);

    icmConnectPSENet( handles.timer3_p, handles.ir202_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir194_n = icmNewNet("ir194" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.ir194_n, "SPI194", 0);

    icmConnectPSENet( handles.uart0_p, handles.ir194_n, "intOut", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir195_n = icmNewNet("ir195" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.ir195_n, "SPI195", 0);

    icmConnectPSENet( handles.uart1_p, handles.ir195_n, "intOut", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cpu0Reset_n = icmNewNet("cpu0Reset" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.cpu0Reset_n, "reset_CPU0", 0);

    icmConnectPSENet( handles.RSTMGR0_p, handles.cpu0Reset_n, "cpu0Reset", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.cpu1Reset_n = icmNewNet("cpu1Reset" );

    icmConnectProcessorNet( handles.cpu_A9MPx2_c, handles.cpu1Reset_n, "reset_CPU1", 0);

    icmConnectPSENet( handles.RSTMGR0_p, handles.cpu1Reset_n, "cpu1Reset", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.irq10_n = icmNewNet("irq10" );

    icmConnectProcessorNet( handles.cpu_Nios_II_c, handles.irq10_n, "d_irq10", 0);

    icmConnectPSENet( handles.uart_s1_p, handles.irq10_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.irq1_n = icmNewNet("irq1" );

    icmConnectProcessorNet( handles.cpu_Nios_II_c, handles.irq1_n, "d_irq1", 0);

    icmConnectPSENet( handles.jtag_uart_p, handles.irq1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.irq11_n = icmNewNet("irq11" );

    icmConnectProcessorNet( handles.cpu_Nios_II_c, handles.irq11_n, "d_irq11", 0);

    icmConnectPSENet( handles.timer_1ms_p, handles.irq11_n, "irq", 0);
}
