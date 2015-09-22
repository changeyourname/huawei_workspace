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

    icmInitAttrs AlteraCycloneIII_3c120_attrs = ICM_STOP_ON_CTRLC|ICM_VERBOSE;

    icmInitPlatform(ICM_VERSION, AlteraCycloneIII_3c120_attrs, 0, 0, "AlteraCycloneIII_3c120");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "This platform models the Altera Cyclone III 3c120.\n\nThe processor is an Altera Nios_II procesor, Nios_II_F.");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "Altera Cyclone III 3c120 Reference Guide");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus smbus
////////////////////////////////////////////////////////////////////////////////


    handles.smbus_b = icmNewBus( "smbus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus iobus
////////////////////////////////////////////////////////////////////////////////


    handles.iobus_b = icmNewBus( "iobus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus dbus
////////////////////////////////////////////////////////////////////////////////


    handles.dbus_b = icmNewBus( "dbus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus ibus
////////////////////////////////////////////////////////////////////////////////


    handles.ibus_b = icmNewBus( "ibus", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Processor cpu
////////////////////////////////////////////////////////////////////////////////


    const char *cpu_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "altera.ovpworld.org",    // vendor
        0                   ,    // library
        "nios_ii"           ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_attrList, "variant", "Nios_II_F");
    icmAddUns64Attr(cpu_attrList, "BREAK_VECTOR", 0xc7fff820LL);
    icmAddUns64Attr(cpu_attrList, "EXCEPTION_VECTOR", 0xd0000020LL);
    icmAddUns64Attr(cpu_attrList, "RESET_VECTOR", 0xc2800000LL);
    icmAddUns64Attr(cpu_attrList, "FAST_TLB_MISS_EXCEPTION_VECTOR", 0xc7fff400LL);
    icmAddUns64Attr(cpu_attrList, "HW_DIVIDE", 1LL);
    icmAddUns64Attr(cpu_attrList, "HW_MULTIPLY", 1LL);
    icmAddUns64Attr(cpu_attrList, "HW_MULX", 0LL);
    icmAddUns64Attr(cpu_attrList, "INCLUDE_MMU", 1LL);
    icmAddStringAttr(cpu_attrList, "MMU_TLB_SET_ASSOCIATIVITY", "16");
    icmAddStringAttr(cpu_attrList, "MMU_TLB_ENTRIES", "128");
    icmAddUns64Attr(cpu_attrList, "MMU_PID_BITS", 8LL);
    icmAddUns64Attr(cpu_attrList, "DATA_ADDR_WIDTH", 29LL);
    icmAddUns64Attr(cpu_attrList, "INST_ADDR_WIDTH", 29LL);
    icmAddUns64Attr(cpu_attrList, "TEST_HALT_EXIT", 1LL);
    icmAddUns64Attr(cpu_attrList, "EXCEPTION_EXTRA_INFORMATION", 1LL);
    icmAddDoubleAttr(cpu_attrList, "mips", 125.000000);
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

    icmConnectPSEBus( handles.uart_s1_p, handles.iobus_b, "sp1", 0, 0x4c80, 0x4c9f);

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

    icmConnectPSEBus( handles.sysid_p, handles.iobus_b, "sp1", 0, 0x4d40, 0x4d47);

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
    icmAddUns64Attr(jtag_uart_attrList, "finishOnDisconnect", 1LL);

    handles.jtag_uart_p = icmNewPSE(
        "jtag_uart"         ,   // name
        jtag_uart_path      ,   // model
        jtag_uart_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.jtag_uart_p, handles.iobus_b, "sp1", 0, 0x4d50, 0x4d57);

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

    icmConnectPSEBus( handles.timer_1ms_p, handles.iobus_b, "sp1", 0, 0x400000, 0x400017);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.ibus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.dbus_b );

////////////////////////////////////////////////////////////////////////////////
//                          Memory pb_cpu_to_ddr2_bot
////////////////////////////////////////////////////////////////////////////////

    handles.pb_cpu_to_ddr2_bot_m = icmNewMemory("pb_cpu_to_ddr2_bot", 0x7, 0x7ffffff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.pb_cpu_to_ddr2_bot_m, 0x10000000);

////////////////////////////////////////////////////////////////////////////////
//                           Memory tlb_miss_ram_1k
////////////////////////////////////////////////////////////////////////////////

    handles.tlb_miss_ram_1k_m = icmNewMemory("tlb_miss_ram_1k", 0x7, 0x3ff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.tlb_miss_ram_1k_m, 0x7fff400);

////////////////////////////////////////////////////////////////////////////////
//                            Memory flash_mem_64m
////////////////////////////////////////////////////////////////////////////////

    handles.flash_mem_64m_m = icmNewMemory("flash_mem_64m", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.smbus_b, "sp1", handles.flash_mem_64m_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                           Bridge pb_ibus_to_smbus
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.ibus_b, handles.smbus_b, "pb_ibus_to_smbus", "sp1", "mp1", 0x0, 0xffffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                          Bridge pb_dbus_to_smbus_1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.dbus_b, handles.smbus_b, "pb_dbus_to_smbus_1", "sp1", "mp1", 0x0, 0x7ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                          Bridge pb_dbus_to_smbus_2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.dbus_b, handles.smbus_b, "pb_dbus_to_smbus_2", "sp1", "mp1", 0x8800000, 0xffffffff, 0x8800000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge pb_cpu_to_io
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.dbus_b, handles.iobus_b, "pb_cpu_to_io", "sp1", "mp1", 0x0, 0x7fffff, 0x8000000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.irq10_n = icmNewNet("irq10" );

    icmConnectProcessorNet( handles.cpu_c, handles.irq10_n, "d_irq10", 0);

    icmConnectPSENet( handles.uart_s1_p, handles.irq10_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.irq1_n = icmNewNet("irq1" );

    icmConnectProcessorNet( handles.cpu_c, handles.irq1_n, "d_irq1", 0);

    icmConnectPSENet( handles.jtag_uart_p, handles.irq1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.irq11_n = icmNewNet("irq11" );

    icmConnectProcessorNet( handles.cpu_c, handles.irq11_n, "d_irq11", 0);

    icmConnectPSENet( handles.timer_1ms_p, handles.irq11_n, "irq", 0);
}
