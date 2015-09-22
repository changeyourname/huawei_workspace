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

    icmInitAttrs ARMv8_A_FMv1_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, ARMv8_A_FMv1_attrs, 0, 0, "ARMv8-A-FMv1");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "\nThis platform implements the ARM v8-A Foundation Model v1 memory map described in ARM DUI 0677C.\n\nThe default processor is an ARM Cortex-A57MPx4.\n\nThe processor mips rate is modeled as 500MIPS by default. \n\nThe timerScaleFactor and processor MIPS rate default to values to model a 100MHz timer and CNTFREQ is automatically set accordingly. \nThis matches the clock frequency in the default Linux device tree. These should be adjusted if that is changed.\n");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "ARM DUI 0677C");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus pBus
////////////////////////////////////////////////////////////////////////////////


    handles.pBus_b = icmNewBus( "pBus", 40);

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
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-A57MPx4");
    icmAddStringAttr(cpu_attrList, "compatibility", "ISA");
    icmAddUns64Attr(cpu_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_attrList, "override_CBAR", 0x2c000000LL);
    icmAddUns64Attr(cpu_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddUns64Attr(cpu_attrList, "override_timerScaleFactor", 5LL);
    icmAddDoubleAttr(cpu_attrList, "mips", 500.000000);
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
        "LAN91C111"         ,    // name
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
//                                  PSE vbd0
////////////////////////////////////////////////////////////////////////////////


    const char *vbd0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "VirtioBlkMMIO"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP vbd0_attrList = icmNewAttrList();

    handles.vbd0_p = icmNewPSE(
        "vbd0"              ,   // name
        vbd0_path           ,   // model
        vbd0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.vbd0_p, handles.pBus_b, "dma", 1, 0x0, 0xffffffffffULL);

    icmConnectPSEBus( handles.vbd0_p, handles.pBus_b, "bport1", 0, 0x1c130000, 0x1c1301ff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE smartLoader
////////////////////////////////////////////////////////////////////////////////


    const char *smartLoader_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArm64Linux",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smartLoader_attrList = icmNewAttrList();
    icmAddUns64Attr(smartLoader_attrList, "physicalbase", 0x80000000LL);
    icmAddStringAttr(smartLoader_attrList, "command", "console=ttyAMA0 earlyprintk=pl011,0x1c090000 nokaslr");

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
//                                 Memory RAM0
////////////////////////////////////////////////////////////////////////////////

    handles.RAM0_m = icmNewMemory("RAM0", 0x7, 0x3ffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.RAM0_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory RAM1
////////////////////////////////////////////////////////////////////////////////

    handles.RAM1_m = icmNewMemory("RAM1", 0x7, 0x3ffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.RAM1_m, 0x4000000);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory RAM2
////////////////////////////////////////////////////////////////////////////////

    handles.RAM2_m = icmNewMemory("RAM2", 0x7, 0x1ffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.RAM2_m, 0x6000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory DRAM0
////////////////////////////////////////////////////////////////////////////////

    handles.DRAM0_m = icmNewMemory("DRAM0", 0x7, 0x7fffffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.DRAM0_m, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory DRAM1
////////////////////////////////////////////////////////////////////////////////

    handles.DRAM1_m = icmNewMemory("DRAM1", 0x7, 0x17fffffffULL);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.DRAM1_m, 0x880000000ULL);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
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
    handles.ir15_n = icmNewNet("ir15" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir15_n, "SPI47", 0);

    icmConnectPSENet( handles.eth0_p, handles.ir15_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ir42_n = icmNewNet("ir42" );

    icmConnectProcessorNet( handles.cpu_c, handles.ir42_n, "SPI74", 0);

    icmConnectPSENet( handles.vbd0_p, handles.ir42_n, "Interrupt", 0);
}
