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

    icmInitAttrs FreescaleVybridVF5_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, FreescaleVybridVF5_attrs, 0, 0, "FreescaleVybridVF5");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "\nFreescale Vybrid VF5 platform\n");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "\nOnly enough functionality modeled to boot MQX. Most peripherals modeled as dummy register ports.\n");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "Development based on document number: VYBRIDRM Rev. 5, 07/2013");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

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
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-A5MPx1");
    icmAddUns64Attr(cpu_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_attrList, "override_CBAR", 0x40002000LL);
    icmAddUns64Attr(cpu_attrList, "override_GICD_TYPER_ITLines", 4LL);
    icmAddUns64Attr(cpu_attrList, "override_timerScaleFactor", 3LL);
    icmAddDoubleAttr(cpu_attrList, "mips", 396.000000);
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
//                                  PSE mcsm
////////////////////////////////////////////////////////////////////////////////


    const char *mcsm_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mcsm_attrList = icmNewAttrList();

    handles.mcsm_p = icmNewPSE(
        "mcsm"              ,   // name
        mcsm_path           ,   // model
        mcsm_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mcsm_p, handles.pBus_b, "bport1", 0, 0x40001000, 0x40001fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE dma0
////////////////////////////////////////////////////////////////////////////////


    const char *dma0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "VybridDMA"         ,    // name
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

    icmConnectPSEBus( handles.dma0_p, handles.pBus_b, "bport1", 0, 0x40018000, 0x40019fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmamux0
////////////////////////////////////////////////////////////////////////////////


    const char *dmamux0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmamux0_attrList = icmNewAttrList();

    handles.dmamux0_p = icmNewPSE(
        "dmamux0"           ,   // name
        dmamux0_path        ,   // model
        dmamux0_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmamux0_p, handles.pBus_b, "bport1", 0, 0x40024000, 0x40024fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmamux1
////////////////////////////////////////////////////////////////////////////////


    const char *dmamux1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmamux1_attrList = icmNewAttrList();

    handles.dmamux1_p = icmNewPSE(
        "dmamux1"           ,   // name
        dmamux1_path        ,   // model
        dmamux1_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmamux1_p, handles.pBus_b, "bport1", 0, 0x40025000, 0x40025fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart0
////////////////////////////////////////////////////////////////////////////////


    const char *uart0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart0_attrList = icmNewAttrList();
    icmAddUns64Attr(uart0_attrList, "fifoSize", 16LL);
    icmAddUns64Attr(uart0_attrList, "moduleClkFreq", 66000000LL);

    handles.uart0_p = icmNewPSE(
        "uart0"             ,   // name
        uart0_path          ,   // model
        uart0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_p, handles.pBus_b, "bport1", 0, 0x40027000, 0x40027fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart1
////////////////////////////////////////////////////////////////////////////////


    const char *uart1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart1_attrList = icmNewAttrList();
    icmAddUns64Attr(uart1_attrList, "fifoSize", 16LL);
    icmAddUns64Attr(uart1_attrList, "moduleClkFreq", 66000000LL);

    handles.uart1_p = icmNewPSE(
        "uart1"             ,   // name
        uart1_path          ,   // model
        uart1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_p, handles.pBus_b, "bport1", 0, 0x40028000, 0x40028fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart2
////////////////////////////////////////////////////////////////////////////////


    const char *uart2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart2_attrList = icmNewAttrList();
    icmAddUns64Attr(uart2_attrList, "fifoSize", 8LL);
    icmAddUns64Attr(uart2_attrList, "moduleClkFreq", 66000000LL);

    handles.uart2_p = icmNewPSE(
        "uart2"             ,   // name
        uart2_path          ,   // model
        uart2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_p, handles.pBus_b, "bport1", 0, 0x40029000, 0x40029fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart3
////////////////////////////////////////////////////////////////////////////////


    const char *uart3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart3_attrList = icmNewAttrList();
    icmAddUns64Attr(uart3_attrList, "fifoSize", 8LL);
    icmAddUns64Attr(uart3_attrList, "moduleClkFreq", 66000000LL);

    handles.uart3_p = icmNewPSE(
        "uart3"             ,   // name
        uart3_path          ,   // model
        uart3_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_p, handles.pBus_b, "bport1", 0, 0x4002a000, 0x4002afff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE iomuxc
////////////////////////////////////////////////////////////////////////////////


    const char *iomuxc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP iomuxc_attrList = icmNewAttrList();

    handles.iomuxc_p = icmNewPSE(
        "iomuxc"            ,   // name
        iomuxc_path         ,   // model
        iomuxc_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.iomuxc_p, handles.pBus_b, "bport1", 0, 0x40048000, 0x40048fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE anadig
////////////////////////////////////////////////////////////////////////////////


    const char *anadig_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "VybridANADIG"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP anadig_attrList = icmNewAttrList();

    handles.anadig_p = icmNewPSE(
        "anadig"            ,   // name
        anadig_path         ,   // model
        anadig_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.anadig_p, handles.pBus_b, "bport1", 0, 0x40050000, 0x40050fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE ccm
////////////////////////////////////////////////////////////////////////////////


    const char *ccm_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "VybridCCM"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ccm_attrList = icmNewAttrList();

    handles.ccm_p = icmNewPSE(
        "ccm"               ,   // name
        ccm_path            ,   // model
        ccm_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ccm_p, handles.pBus_b, "bport1", 0, 0x4006b000, 0x4006bfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE dma1
////////////////////////////////////////////////////////////////////////////////


    const char *dma1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "VybridDMA"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dma1_attrList = icmNewAttrList();

    handles.dma1_p = icmNewPSE(
        "dma1"              ,   // name
        dma1_path           ,   // model
        dma1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dma1_p, handles.pBus_b, "bport1", 0, 0x40098000, 0x40099fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmamux2
////////////////////////////////////////////////////////////////////////////////


    const char *dmamux2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmamux2_attrList = icmNewAttrList();

    handles.dmamux2_p = icmNewPSE(
        "dmamux2"           ,   // name
        dmamux2_path        ,   // model
        dmamux2_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmamux2_p, handles.pBus_b, "bport1", 0, 0x400a1000, 0x400a1fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE dmamux3
////////////////////////////////////////////////////////////////////////////////


    const char *dmamux3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmamux3_attrList = icmNewAttrList();

    handles.dmamux3_p = icmNewPSE(
        "dmamux3"           ,   // name
        dmamux3_path        ,   // model
        dmamux3_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmamux3_p, handles.pBus_b, "bport1", 0, 0x400a2000, 0x400a2fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ddrmc
////////////////////////////////////////////////////////////////////////////////


    const char *ddrmc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP ddrmc_attrList = icmNewAttrList();

    handles.ddrmc_p = icmNewPSE(
        "ddrmc"             ,   // name
        ddrmc_path          ,   // model
        ddrmc_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ddrmc_p, handles.pBus_b, "bport1", 0, 0x400ae000, 0x400aefff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.pBus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.pBus_b );

////////////////////////////////////////////////////////////////////////////////
//                               Memory bootrom
////////////////////////////////////////////////////////////////////////////////

    handles.bootrom_m = icmNewMemory("bootrom", 0x5, 0x17fff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.bootrom_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                Memory sysram
////////////////////////////////////////////////////////////////////////////////

    handles.sysram_m = icmNewMemory("sysram", 0x7, 0xfffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.sysram_m, 0x3f000000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.SPI93_n = icmNewNet("SPI93" );

    icmConnectProcessorNet( handles.cpu_c, handles.SPI93_n, "SPI93", 0);

    icmConnectPSENet( handles.uart0_p, handles.SPI93_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.SPI94_n = icmNewNet("SPI94" );

    icmConnectProcessorNet( handles.cpu_c, handles.SPI94_n, "SPI94", 0);

    icmConnectPSENet( handles.uart1_p, handles.SPI94_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.SPI95_n = icmNewNet("SPI95" );

    icmConnectProcessorNet( handles.cpu_c, handles.SPI95_n, "SPI95", 0);

    icmConnectPSENet( handles.uart2_p, handles.SPI95_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.SPI96_n = icmNewNet("SPI96" );

    icmConnectProcessorNet( handles.cpu_c, handles.SPI96_n, "SPI96", 0);

    icmConnectPSENet( handles.uart3_p, handles.SPI96_n, "Interrupt", 0);
}
