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

    icmInitAttrs XilinxML505_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, XilinxML505_attrs, 0, 0, "XilinxML505");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc2_node, "Xilinx ML505 Reference Platform");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc_12_node, "Open Source Apache 2.0");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "This platform provides a subset of the full platform functionality. It is provided to boot the Linux operating system.\n           Other software may be used but the operation cannot be guaranteed.");
        icmDocTextAdd(doc_22_node, "Platform capable of booting linux");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "UG347 (v3.1.2) May 16, 2011");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus1
////////////////////////////////////////////////////////////////////////////////


    handles.bus1_b = icmNewBus( "bus1", 32);

////////////////////////////////////////////////////////////////////////////////
//                           Processor microblaze_0
////////////////////////////////////////////////////////////////////////////////


    const char *microblaze_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        "processor"         ,    // library
        "microblaze"        ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP microblaze_0_attrList = icmNewAttrList();
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_MMU", 3LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_MMU_ITLB_SIZE", 2LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_MMU_DTLB_SIZE", 4LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_MMU_TLB_ACCESS", 3LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_MMU_ZONES", 16LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_EXTENDED_FSL_INSTR", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_FSL_EXCEPTION", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_HW_MUL", 2LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_PVR", 2LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_OPCODE_0x0_ILLEGAL", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_FPU_EXCEPTION", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_UNALIGNED_EXCEPTIONS", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_ILL_OPCODE_EXCEPTION", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_DIV_ZERO_EXCEPTION", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_INTERCONNECT", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_BARREL", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_DIV", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_FSL_LINKS", 4LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_DEBUG_ENABLED", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_I_LMB", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_D_LMB", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_FPU", 2LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_MSR_INSTR", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_USE_PCMP_INSTR", 1LL);
    icmAddUns64Attr(microblaze_0_attrList, "C_FAMILY", 12LL);
    icmAddDoubleAttr(microblaze_0_attrList, "mips", 125.000000);
    icmAddStringAttr(microblaze_0_attrList, "endian", "big");
    icmNewProcAttrs microblaze_0_attrs = ICM_ATTR_SIMEX;


    handles.microblaze_0_c = icmNewProcessor(
        "microblaze_0"      ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        microblaze_0_path   ,   // model
        0, 
        microblaze_0_attrs  ,   // procAttrs
        microblaze_0_attrList,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                PSE LEDs_8Bit
////////////////////////////////////////////////////////////////////////////////


    const char *LEDs_8Bit_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-gpio"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP LEDs_8Bit_attrList = icmNewAttrList();

    handles.LEDs_8Bit_p = icmNewPSE(
        "LEDs_8Bit"         ,   // name
        LEDs_8Bit_path      ,   // model
        LEDs_8Bit_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.LEDs_8Bit_p, handles.bus1_b, "plb", 0, 0x81400000, 0x8140ffff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE IIC_EEPROM
////////////////////////////////////////////////////////////////////////////////


    const char *IIC_EEPROM_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-iic"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP IIC_EEPROM_attrList = icmNewAttrList();

    handles.IIC_EEPROM_p = icmNewPSE(
        "IIC_EEPROM"        ,   // name
        IIC_EEPROM_path     ,   // model
        IIC_EEPROM_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.IIC_EEPROM_p, handles.bus1_b, "plb", 0, 0x81600000, 0x8160ffff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE xps_intc_0
////////////////////////////////////////////////////////////////////////////////


    const char *xps_intc_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-intc"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP xps_intc_0_attrList = icmNewAttrList();

    handles.xps_intc_0_p = icmNewPSE(
        "xps_intc_0"        ,   // name
        xps_intc_0_path     ,   // model
        xps_intc_0_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.xps_intc_0_p, handles.bus1_b, "plb", 0, 0x81800000, 0x8180001f);

////////////////////////////////////////////////////////////////////////////////
//                            PSE Hard_Ethernet_MAC
////////////////////////////////////////////////////////////////////////////////


    const char *Hard_Ethernet_MAC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-ll-temac"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP Hard_Ethernet_MAC_attrList = icmNewAttrList();

    handles.Hard_Ethernet_MAC_p = icmNewPSE(
        "Hard_Ethernet_MAC" ,   // name
        Hard_Ethernet_MAC_path,   // model
        Hard_Ethernet_MAC_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.Hard_Ethernet_MAC_p, handles.bus1_b, "plb", 0, 0x81c00000, 0x81c0003f);

////////////////////////////////////////////////////////////////////////////////
//                           PSE SysACE_CompactFlash
////////////////////////////////////////////////////////////////////////////////


    const char *SysACE_CompactFlash_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-sysace"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP SysACE_CompactFlash_attrList = icmNewAttrList();

    handles.SysACE_CompactFlash_p = icmNewPSE(
        "SysACE_CompactFlash",   // name
        SysACE_CompactFlash_path,   // model
        SysACE_CompactFlash_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.SysACE_CompactFlash_p, handles.bus1_b, "plb", 0, 0x83600000, 0x8360ffff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE xps_timer_1
////////////////////////////////////////////////////////////////////////////////


    const char *xps_timer_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-timer"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP xps_timer_1_attrList = icmNewAttrList();

    handles.xps_timer_1_p = icmNewPSE(
        "xps_timer_1"       ,   // name
        xps_timer_1_path    ,   // model
        xps_timer_1_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.xps_timer_1_p, handles.bus1_b, "plb", 0, 0x83c00000, 0x83c0001f);

////////////////////////////////////////////////////////////////////////////////
//                              PSE RS232_Uart_1
////////////////////////////////////////////////////////////////////////////////


    const char *RS232_Uart_1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-uartlite"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP RS232_Uart_1_attrList = icmNewAttrList();
    icmAddStringAttr(RS232_Uart_1_attrList, "outfile", "RS232_Uart_1.log");
    icmAddUns64Attr(RS232_Uart_1_attrList, "finishOnDisconnect", 1LL);

    handles.RS232_Uart_1_p = icmNewPSE(
        "RS232_Uart_1"      ,   // name
        RS232_Uart_1_path   ,   // model
        RS232_Uart_1_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.RS232_Uart_1_p, handles.bus1_b, "plb", 0, 0x84000000, 0x8400000f);

////////////////////////////////////////////////////////////////////////////////
//                              PSE debug_module
////////////////////////////////////////////////////////////////////////////////


    const char *debug_module_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "mdm"               ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP debug_module_attrList = icmNewAttrList();

    handles.debug_module_p = icmNewPSE(
        "debug_module"      ,   // name
        debug_module_path   ,   // model
        debug_module_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.debug_module_p, handles.bus1_b, "plb", 0, 0x84400000, 0x8440ffff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE mpmc
////////////////////////////////////////////////////////////////////////////////


    const char *mpmc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "mpmc"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mpmc_attrList = icmNewAttrList();

    handles.mpmc_p = icmNewPSE(
        "mpmc"              ,   // name
        mpmc_path           ,   // model
        mpmc_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mpmc_p, handles.bus1_b, "plb", 0, 0x84600180, 0x846001ff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE mb_plb
////////////////////////////////////////////////////////////////////////////////


    const char *mb_plb_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        0                   ,    // library
        "xps-mch-emc"       ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mb_plb_attrList = icmNewAttrList();

    handles.mb_plb_p = icmNewPSE(
        "mb_plb"            ,   // name
        mb_plb_path         ,   // model
        mb_plb_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mb_plb_p, handles.bus1_b, "plb", 0, 0xa0000000, 0xa1ffffff);

    icmConnectProcessorBusByName( handles.microblaze_0_c, "INSTRUCTION", handles.bus1_b );

    icmConnectProcessorBusByName( handles.microblaze_0_c, "DATA", handles.bus1_b );

////////////////////////////////////////////////////////////////////////////////
//                               Memory BOOTMEM
////////////////////////////////////////////////////////////////////////////////

    handles.BOOTMEM_m = icmNewMemory("BOOTMEM", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.BOOTMEM_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Memory DDR2_SDRAM
////////////////////////////////////////////////////////////////////////////////

    handles.DDR2_SDRAM_m = icmNewMemory("DDR2_SDRAM", 0x7, 0xfffffff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.DDR2_SDRAM_m, 0x90000000);

////////////////////////////////////////////////////////////////////////////////
//                            Memory UNKNOWN_PERIPH
////////////////////////////////////////////////////////////////////////////////

    handles.UNKNOWN_PERIPH_m = icmNewMemory("UNKNOWN_PERIPH", 0x7, 0xfff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.UNKNOWN_PERIPH_m, 0x8ffff000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.Interrupt_net_n = icmNewNet("Interrupt_net" );

    icmConnectProcessorNet( handles.microblaze_0_c, handles.Interrupt_net_n, "Interrupt", 0);

    icmConnectPSENet( handles.xps_intc_0_p, handles.Interrupt_net_n, "Irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.Interrupt_3_n = icmNewNet("Interrupt_3" );

    icmConnectPSENet( handles.xps_intc_0_p, handles.Interrupt_3_n, "Intr3", 0);

    icmConnectPSENet( handles.xps_timer_1_p, handles.Interrupt_3_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.Interrupt_8_n = icmNewNet("Interrupt_8" );

    icmConnectPSENet( handles.xps_intc_0_p, handles.Interrupt_8_n, "Intr8", 0);

    icmConnectPSENet( handles.RS232_Uart_1_p, handles.Interrupt_8_n, "Interrupt", 0);
}
