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

    icmInitAttrs RenesasUPD70F3441_attrs = ICM_ENABLE_IMPERAS_INTERCEPTS|ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, RenesasUPD70F3441_attrs, 0, 0, "RenesasUPD70F3441");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "The Renesas uPD70F3441 - V850/PHO3 platform");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "Limitiations of peripheral functionality is documented within the peripheral component.\nUnimplemented Components:\n    System Controller\n    Standby Controller\n    Bus Control Unit\n    Memory Controller\n    CAN Controller\n    FlexRay\n    I/O Ports\n    CPU-CRC\n    DATA-CRC\n    On-chip Debug Unit\n    NBD\nPartially Implemented Components (not complete - only certain modes or features modeled or tested)\n    DMA\n");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                   Bus vfb
////////////////////////////////////////////////////////////////////////////////


    handles.vfb_b = icmNewBus( "vfb", 28);

////////////////////////////////////////////////////////////////////////////////
//                                Processor CPU
////////////////////////////////////////////////////////////////////////////////


    const char *CPU_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "processor"         ,    // library
        "v850"              ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP CPU_attrList = icmNewAttrList();
    icmAddStringAttr(CPU_attrList, "variant", "V850ES");
    icmAddDoubleAttr(CPU_attrList, "mips", 128.000000);
    icmNewProcAttrs CPU_attrs = ICM_ATTR_DEFAULT;


    handles.CPU_c = icmNewProcessor(
        "CPU"               ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        28                  ,   // address bits
        CPU_path            ,   // model
        0, 
        CPU_attrs           ,   // procAttrs
        CPU_attrList        ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                  PSE LOGIC
////////////////////////////////////////////////////////////////////////////////


    const char *LOGIC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "UPD70F3441Logic"   ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP LOGIC_attrList = icmNewAttrList();

    handles.LOGIC_p = icmNewPSE(
        "LOGIC"             ,   // name
        LOGIC_path          ,   // model
        LOGIC_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.LOGIC_p, handles.vfb_b, "LOGICP0", 0, 0xffff6d0, 0xffff6d3);

    icmConnectPSEBus( handles.LOGIC_p, handles.vfb_b, "LOGICP1", 0, 0xffff400, 0xffff475);

    icmConnectPSEBus( handles.LOGIC_p, handles.vfb_b, "LOGICP2", 0, 0xffff888, 0xffff893);

    icmConnectPSEBus( handles.LOGIC_p, handles.vfb_b, "LOGICP3", 0, 0xffff1fc, 0xffff1fc);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE INTC
////////////////////////////////////////////////////////////////////////////////


    const char *INTC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "intc"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP INTC_attrList = icmNewAttrList();

    handles.INTC_p = icmNewPSE(
        "INTC"              ,   // name
        INTC_path           ,   // model
        INTC_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.INTC_p, handles.vfb_b, "INTCP0", 0, 0xffff100, 0xffff1fb);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE CRC
////////////////////////////////////////////////////////////////////////////////


    const char *CRC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "crc"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CRC_attrList = icmNewAttrList();

    handles.CRC_p = icmNewPSE(
        "CRC"               ,   // name
        CRC_path            ,   // model
        CRC_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CRC_p, handles.vfb_b, "CRCP0", 0, 0xfe00000, 0xfe0007f);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE CLKGEN
////////////////////////////////////////////////////////////////////////////////


    const char *CLKGEN_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "clkgen"            ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CLKGEN_attrList = icmNewAttrList();

    handles.CLKGEN_p = icmNewPSE(
        "CLKGEN"            ,   // name
        CLKGEN_path         ,   // model
        CLKGEN_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CLKGEN_p, handles.vfb_b, "CLKGENP0", 0, 0xffff860, 0xffff860);

    icmConnectPSEBus( handles.CLKGEN_p, handles.vfb_b, "CLKGENP1", 0, 0xffffca0, 0xffffca0);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE BCU
////////////////////////////////////////////////////////////////////////////////


    const char *BCU_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "bcu"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP BCU_attrList = icmNewAttrList();

    handles.BCU_p = icmNewPSE(
        "BCU"               ,   // name
        BCU_path            ,   // model
        BCU_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.BCU_p, handles.vfb_b, "BCUP0", 0, 0xffff060, 0xffff06f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE MEMC
////////////////////////////////////////////////////////////////////////////////


    const char *MEMC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "memc"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP MEMC_attrList = icmNewAttrList();

    handles.MEMC_p = icmNewPSE(
        "MEMC"              ,   // name
        MEMC_path           ,   // model
        MEMC_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.MEMC_p, handles.vfb_b, "MEMCP0", 0, 0xffff480, 0xffff48f);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE DMA
////////////////////////////////////////////////////////////////////////////////


    const char *DMA_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "dma"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP DMA_attrList = icmNewAttrList();

    handles.DMA_p = icmNewPSE(
        "DMA"               ,   // name
        DMA_path            ,   // model
        DMA_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.DMA_p, handles.vfb_b, "DMAPM", 1, 0x0, 0xfffffff);

    icmConnectPSEBus( handles.DMA_p, handles.vfb_b, "DMAP0", 0, 0xffffe00, 0xffffe0f);

    icmConnectPSEBus( handles.DMA_p, handles.vfb_b, "DMAP1", 0, 0xffff300, 0xffff3ff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE UARTC0
////////////////////////////////////////////////////////////////////////////////


    const char *UARTC0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "uartc"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP UARTC0_attrList = icmNewAttrList();
    icmAddUns64Attr(UARTC0_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(UARTC0_attrList, "PCLK9", 65536LL);
    icmAddUns64Attr(UARTC0_attrList, "console", 1LL);
    icmAddUns64Attr(UARTC0_attrList, "finishOnDisconnect", 1LL);

    handles.UARTC0_p = icmNewPSE(
        "UARTC0"            ,   // name
        UARTC0_path         ,   // model
        UARTC0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.UARTC0_p, handles.vfb_b, "UARTP0", 0, 0xffffa00, 0xffffa0f);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE UARTC1
////////////////////////////////////////////////////////////////////////////////


    const char *UARTC1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "uartc"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP UARTC1_attrList = icmNewAttrList();
    icmAddUns64Attr(UARTC1_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(UARTC1_attrList, "PCLK9", 65536LL);
    icmAddUns64Attr(UARTC1_attrList, "console", 1LL);
    icmAddUns64Attr(UARTC1_attrList, "finishOnDisconnect", 1LL);

    handles.UARTC1_p = icmNewPSE(
        "UARTC1"            ,   // name
        UARTC1_path         ,   // model
        UARTC1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.UARTC1_p, handles.vfb_b, "UARTP0", 0, 0xffffa20, 0xffffa2f);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE UARTC2
////////////////////////////////////////////////////////////////////////////////


    const char *UARTC2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "uartc"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP UARTC2_attrList = icmNewAttrList();
    icmAddUns64Attr(UARTC2_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(UARTC2_attrList, "PCLK9", 65536LL);
    icmAddUns64Attr(UARTC2_attrList, "console", 1LL);
    icmAddUns64Attr(UARTC2_attrList, "finishOnDisconnect", 1LL);

    handles.UARTC2_p = icmNewPSE(
        "UARTC2"            ,   // name
        UARTC2_path         ,   // model
        UARTC2_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.UARTC2_p, handles.vfb_b, "UARTP0", 0, 0xffffa40, 0xffffa4f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE CSIB0
////////////////////////////////////////////////////////////////////////////////


    const char *CSIB0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "csib"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CSIB0_attrList = icmNewAttrList();
    icmAddUns64Attr(CSIB0_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(CSIB0_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(CSIB0_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(CSIB0_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(CSIB0_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(CSIB0_attrList, "PCLK6", 524288LL);

    handles.CSIB0_p = icmNewPSE(
        "CSIB0"             ,   // name
        CSIB0_path          ,   // model
        CSIB0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CSIB0_p, handles.vfb_b, "CSIBP0", 0, 0xffffd00, 0xffffd07);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE CSIB1
////////////////////////////////////////////////////////////////////////////////


    const char *CSIB1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "csib"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CSIB1_attrList = icmNewAttrList();
    icmAddUns64Attr(CSIB1_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(CSIB1_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(CSIB1_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(CSIB1_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(CSIB1_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(CSIB1_attrList, "PCLK6", 524288LL);

    handles.CSIB1_p = icmNewPSE(
        "CSIB1"             ,   // name
        CSIB1_path          ,   // model
        CSIB1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CSIB1_p, handles.vfb_b, "CSIBP0", 0, 0xffffd20, 0xffffd27);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE CSIE0
////////////////////////////////////////////////////////////////////////////////


    const char *CSIE0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "csie"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CSIE0_attrList = icmNewAttrList();
    icmAddUns64Attr(CSIE0_attrList, "PCLK0", 33554432LL);

    handles.CSIE0_p = icmNewPSE(
        "CSIE0"             ,   // name
        CSIE0_path          ,   // model
        CSIE0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CSIE0_p, handles.vfb_b, "CSIEP0", 0, 0xffffd40, 0xffffd5f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE CSIE1
////////////////////////////////////////////////////////////////////////////////


    const char *CSIE1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "csie"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CSIE1_attrList = icmNewAttrList();
    icmAddUns64Attr(CSIE1_attrList, "PCLK0", 33554432LL);

    handles.CSIE1_p = icmNewPSE(
        "CSIE1"             ,   // name
        CSIE1_path          ,   // model
        CSIE1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CSIE1_p, handles.vfb_b, "CSIEP0", 0, 0xffffd80, 0xffffd9f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE CAN0
////////////////////////////////////////////////////////////////////////////////


    const char *CAN0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "can"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CAN0_attrList = icmNewAttrList();

    handles.CAN0_p = icmNewPSE(
        "CAN0"              ,   // name
        CAN0_path           ,   // model
        CAN0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CAN0_p, handles.vfb_b, "busPortGR", 0, 0x8400000, 0x84000ff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE CAN1
////////////////////////////////////////////////////////////////////////////////


    const char *CAN1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "can"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP CAN1_attrList = icmNewAttrList();

    handles.CAN1_p = icmNewPSE(
        "CAN1"              ,   // name
        CAN1_path           ,   // model
        CAN1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.CAN1_p, handles.vfb_b, "busPortGR", 0, 0x8400600, 0x84006ff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ADC0
////////////////////////////////////////////////////////////////////////////////


    const char *ADC0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "adc"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP ADC0_attrList = icmNewAttrList();
    icmAddUns64Attr(ADC0_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(ADC0_attrList, "sample", 100LL);

    handles.ADC0_p = icmNewPSE(
        "ADC0"              ,   // name
        ADC0_path           ,   // model
        ADC0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ADC0_p, handles.vfb_b, "ADCP0", 0, 0xffff200, 0xffff22f);

    icmConnectPSEBus( handles.ADC0_p, handles.vfb_b, "ADCP1", 0, 0xffff270, 0xffff270);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE ADC1
////////////////////////////////////////////////////////////////////////////////


    const char *ADC1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "adc"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP ADC1_attrList = icmNewAttrList();
    icmAddUns64Attr(ADC1_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(ADC1_attrList, "sample", 100LL);

    handles.ADC1_p = icmNewPSE(
        "ADC1"              ,   // name
        ADC1_path           ,   // model
        ADC1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.ADC1_p, handles.vfb_b, "ADCP0", 0, 0xffff240, 0xffff26f);

    icmConnectPSEBus( handles.ADC1_p, handles.vfb_b, "ADCP1", 0, 0xffff272, 0xffff272);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA0
////////////////////////////////////////////////////////////////////////////////


    const char *TAA0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA0_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA0_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA0_attrList, "PCLK9", 65536LL);

    handles.TAA0_p = icmNewPSE(
        "TAA0"              ,   // name
        TAA0_path           ,   // model
        TAA0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA0_p, handles.vfb_b, "TAAP0", 0, 0xffff600, 0xffff60f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA1
////////////////////////////////////////////////////////////////////////////////


    const char *TAA1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA1_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA1_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA1_attrList, "PCLK9", 65536LL);

    handles.TAA1_p = icmNewPSE(
        "TAA1"              ,   // name
        TAA1_path           ,   // model
        TAA1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA1_p, handles.vfb_b, "TAAP0", 0, 0xffff610, 0xffff61f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA2
////////////////////////////////////////////////////////////////////////////////


    const char *TAA2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA2_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA2_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA2_attrList, "PCLK9", 65536LL);

    handles.TAA2_p = icmNewPSE(
        "TAA2"              ,   // name
        TAA2_path           ,   // model
        TAA2_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA2_p, handles.vfb_b, "TAAP0", 0, 0xffff620, 0xffff62f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA3
////////////////////////////////////////////////////////////////////////////////


    const char *TAA3_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA3_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA3_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA3_attrList, "PCLK9", 65536LL);

    handles.TAA3_p = icmNewPSE(
        "TAA3"              ,   // name
        TAA3_path           ,   // model
        TAA3_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA3_p, handles.vfb_b, "TAAP0", 0, 0xffff630, 0xffff63f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA4
////////////////////////////////////////////////////////////////////////////////


    const char *TAA4_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA4_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA4_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA4_attrList, "PCLK9", 65536LL);

    handles.TAA4_p = icmNewPSE(
        "TAA4"              ,   // name
        TAA4_path           ,   // model
        TAA4_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA4_p, handles.vfb_b, "TAAP0", 0, 0xffff640, 0xffff64f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA5
////////////////////////////////////////////////////////////////////////////////


    const char *TAA5_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA5_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA5_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA5_attrList, "PCLK9", 65536LL);

    handles.TAA5_p = icmNewPSE(
        "TAA5"              ,   // name
        TAA5_path           ,   // model
        TAA5_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA5_p, handles.vfb_b, "TAAP0", 0, 0xffff650, 0xffff65f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA6
////////////////////////////////////////////////////////////////////////////////


    const char *TAA6_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA6_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA6_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA6_attrList, "PCLK9", 65536LL);

    handles.TAA6_p = icmNewPSE(
        "TAA6"              ,   // name
        TAA6_path           ,   // model
        TAA6_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA6_p, handles.vfb_b, "TAAP0", 0, 0xffff660, 0xffff66f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA7
////////////////////////////////////////////////////////////////////////////////


    const char *TAA7_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA7_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA7_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA7_attrList, "PCLK9", 65536LL);

    handles.TAA7_p = icmNewPSE(
        "TAA7"              ,   // name
        TAA7_path           ,   // model
        TAA7_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA7_p, handles.vfb_b, "TAAP0", 0, 0xffff670, 0xffff67f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA8
////////////////////////////////////////////////////////////////////////////////


    const char *TAA8_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA8_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA8_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA8_attrList, "PCLK9", 65536LL);

    handles.TAA8_p = icmNewPSE(
        "TAA8"              ,   // name
        TAA8_path           ,   // model
        TAA8_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA8_p, handles.vfb_b, "TAAP0", 0, 0xffff680, 0xffff68f);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TAA9
////////////////////////////////////////////////////////////////////////////////


    const char *TAA9_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "taa"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TAA9_attrList = icmNewAttrList();
    icmAddUns64Attr(TAA9_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TAA9_attrList, "PCLK9", 65536LL);

    handles.TAA9_p = icmNewPSE(
        "TAA9"              ,   // name
        TAA9_path           ,   // model
        TAA9_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TAA9_p, handles.vfb_b, "TAAP0", 0, 0xffff6b0, 0xffff6bf);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TMS0
////////////////////////////////////////////////////////////////////////////////


    const char *TMS0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "tms"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TMS0_attrList = icmNewAttrList();
    icmAddUns64Attr(TMS0_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TMS0_attrList, "PCLK9", 65536LL);

    handles.TMS0_p = icmNewPSE(
        "TMS0"              ,   // name
        TMS0_path           ,   // model
        TMS0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TMS0_p, handles.vfb_b, "TMSP0", 0, 0xffff580, 0xffff5a9);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TMS1
////////////////////////////////////////////////////////////////////////////////


    const char *TMS1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "tms"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TMS1_attrList = icmNewAttrList();
    icmAddUns64Attr(TMS1_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TMS1_attrList, "PCLK9", 65536LL);

    handles.TMS1_p = icmNewPSE(
        "TMS1"              ,   // name
        TMS1_path           ,   // model
        TMS1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TMS1_p, handles.vfb_b, "TMSP0", 0, 0xffff5c0, 0xffff5e9);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TMT0
////////////////////////////////////////////////////////////////////////////////


    const char *TMT0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "tmt"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TMT0_attrList = icmNewAttrList();
    icmAddUns64Attr(TMT0_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TMT0_attrList, "PCLK9", 65536LL);

    handles.TMT0_p = icmNewPSE(
        "TMT0"              ,   // name
        TMT0_path           ,   // model
        TMT0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TMT0_p, handles.vfb_b, "TMTP0", 0, 0xffff690, 0xffff69f);

    icmConnectPSEBus( handles.TMT0_p, handles.vfb_b, "TMTP1", 0, 0xffff990, 0xffff991);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE TMT1
////////////////////////////////////////////////////////////////////////////////


    const char *TMT1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "tmt"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP TMT1_attrList = icmNewAttrList();
    icmAddUns64Attr(TMT1_attrList, "PCLK0", 33554432LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK1", 16777216LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK2", 8388608LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK3", 4194304LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK4", 2097152LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK5", 1048576LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK7", 262144LL);
    icmAddUns64Attr(TMT1_attrList, "PCLK9", 65536LL);

    handles.TMT1_p = icmNewPSE(
        "TMT1"              ,   // name
        TMT1_path           ,   // model
        TMT1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TMT1_p, handles.vfb_b, "TMTP0", 0, 0xffff6a0, 0xffff6af);

    icmConnectPSEBus( handles.TMT1_p, handles.vfb_b, "TMTP1", 0, 0xffff9a0, 0xffff9a1);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE RNG0
////////////////////////////////////////////////////////////////////////////////


    const char *RNG0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "rng"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP RNG0_attrList = icmNewAttrList();

    handles.RNG0_p = icmNewPSE(
        "RNG0"              ,   // name
        RNG0_path           ,   // model
        RNG0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.RNG0_p, handles.vfb_b, "RNGP0", 0, 0xffff700, 0xffff701);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE BRG0
////////////////////////////////////////////////////////////////////////////////


    const char *BRG0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "brg"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP BRG0_attrList = icmNewAttrList();
    icmAddUns64Attr(BRG0_attrList, "PCLK", 16777216LL);

    handles.BRG0_p = icmNewPSE(
        "BRG0"              ,   // name
        BRG0_path           ,   // model
        BRG0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.BRG0_p, handles.vfb_b, "BRGP0", 0, 0xffffdc0, 0xffffdc1);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE BRG1
////////////////////////////////////////////////////////////////////////////////


    const char *BRG1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "brg"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP BRG1_attrList = icmNewAttrList();
    icmAddUns64Attr(BRG1_attrList, "PCLK", 16777216LL);

    handles.BRG1_p = icmNewPSE(
        "BRG1"              ,   // name
        BRG1_path           ,   // model
        BRG1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.BRG1_p, handles.vfb_b, "BRGP0", 0, 0xffffdd0, 0xffffdd1);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE BRG2
////////////////////////////////////////////////////////////////////////////////


    const char *BRG2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "brg"               ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP BRG2_attrList = icmNewAttrList();
    icmAddUns64Attr(BRG2_attrList, "PCLK", 33554432LL);

    handles.BRG2_p = icmNewPSE(
        "BRG2"              ,   // name
        BRG2_path           ,   // model
        BRG2_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.BRG2_p, handles.vfb_b, "BRGP0", 0, 0xffffde0, 0xffffde1);

    icmConnectProcessorBusByName( handles.CPU_c, "INSTRUCTION", handles.vfb_b );

    icmConnectProcessorBusByName( handles.CPU_c, "DATA", handles.vfb_b );

////////////////////////////////////////////////////////////////////////////////
//                              Memory CodeFlash
////////////////////////////////////////////////////////////////////////////////

    handles.CodeFlash_m = icmNewMemory("CodeFlash", 0x7, 0xf7fff);


    icmConnectMemoryToBus( handles.vfb_b, "sp1", handles.CodeFlash_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              Memory DataFlash
////////////////////////////////////////////////////////////////////////////////

    handles.DataFlash_m = icmNewMemory("DataFlash", 0x7, 0x7fff);


    icmConnectMemoryToBus( handles.vfb_b, "sp1", handles.DataFlash_m, 0x3e00000);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory iRam
////////////////////////////////////////////////////////////////////////////////

    handles.iRam_m = icmNewMemory("iRam", 0x7, 0xefff);


    icmConnectMemoryToBus( handles.vfb_b, "sp1", handles.iRam_m, 0x3ff0000);

////////////////////////////////////////////////////////////////////////////////
//                   Bridge bridge_vfb_0x03FF0000_0x0FFF0000
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.vfb_b, handles.vfb_b, "bridge_vfb_0x03FF0000_0x0FFF0000", "sp", "mp", 0x3ff0000, 0x3ffefff, 0xfff0000);

////////////////////////////////////////////////////////////////////////////////
//                   Bridge bridge_vfb_0x0FFFF58A_0x0FFFFB48
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.vfb_b, handles.vfb_b, "bridge_vfb_0x0FFFF58A_0x0FFFFB48", "sp", "mp", 0xffff58a, 0xffff593, 0xffffb48);

////////////////////////////////////////////////////////////////////////////////
//                   Bridge bridge_vfb_0x0FFFF598_0x0FFFFB56
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.vfb_b, handles.vfb_b, "bridge_vfb_0x0FFFF598_0x0FFFFB56", "sp", "mp", 0xffff598, 0xffff59f, 0xffffb56);

////////////////////////////////////////////////////////////////////////////////
//                   Bridge bridge_vfb_0x0FFFF5CA_0x0FFFFBC8
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.vfb_b, handles.vfb_b, "bridge_vfb_0x0FFFF5CA_0x0FFFFBC8", "sp", "mp", 0xffff5ca, 0xffff5d3, 0xffffbc8);

////////////////////////////////////////////////////////////////////////////////
//                   Bridge bridge_vfb_0x0FFFF5D8_0x0FFFFBD6
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.vfb_b, handles.vfb_b, "bridge_vfb_0x0FFFF5D8_0x0FFFFBD6", "sp", "mp", 0xffff5d8, 0xffff5df, 0xffffbd6);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.INTRESET_n = icmNewNet("INTRESET" );

    icmConnectProcessorNet( handles.CPU_c, handles.INTRESET_n, "reset", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTRESET_n, "RESET", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTNMI_n = icmNewNet("INTNMI" );

    icmConnectProcessorNet( handles.CPU_c, handles.INTNMI_n, "nmi0", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTNMI_n, "NMI0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINTP_n = icmNewNet("INTINTP" );

    icmConnectProcessorNet( handles.CPU_c, handles.INTINTP_n, "intp", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINTP_n, "INTP", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTMIRETI_n = icmNewNet("INTMIRETI" );

    icmConnectProcessorNet( handles.CPU_c, handles.INTMIRETI_n, "mireti", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTMIRETI_n, "MIRETI", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINTACK_n = icmNewNet("INTINTACK" );

    icmConnectProcessorNet( handles.CPU_c, handles.INTINTACK_n, "intack", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINTACK_n, "INTACK", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTNMI0_n = icmNewNet("INTNMI0" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTNMI0_n, "NMIOUT", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTNMI0_n, "NMI_00", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT0_n = icmNewNet("INTINT0" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT0_n, "INT0", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT0_n, "INT_00", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT1_n = icmNewNet("INTINT1" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT1_n, "INT1", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT1_n, "INT_01", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC0R_n = icmNewNet("INTUC0R" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTUC0R_n, "INTUC0R", 0);

    icmConnectPSENet( handles.DMA_p, handles.INTUC0R_n, "INTUC0R", 0);

    icmConnectPSENet( handles.UARTC0_p, handles.INTUC0R_n, "INTUCR", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT6_n = icmNewNet("INTINT6" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT6_n, "INT6", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT6_n, "INT_06", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC1R_n = icmNewNet("INTUC1R" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTUC1R_n, "INTUC1R", 0);

    icmConnectPSENet( handles.DMA_p, handles.INTUC1R_n, "INTUC1R", 0);

    icmConnectPSENet( handles.UARTC1_p, handles.INTUC1R_n, "INTUCR", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT7_n = icmNewNet("INTINT7" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT7_n, "INT7", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT7_n, "INT_07", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTBRG0_n = icmNewNet("INTBRG0" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTBRG0_n, "INTBRG0", 0);

    icmConnectPSENet( handles.BRG0_p, handles.INTBRG0_n, "INTBRG", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTBRG1_n = icmNewNet("INTBRG1" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTBRG1_n, "INTBRG1", 0);

    icmConnectPSENet( handles.BRG1_p, handles.INTBRG1_n, "INTBRG", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT75_n = icmNewNet("INTINT75" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT75_n, "INT75", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT75_n, "INT_75", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTCB0T_n = icmNewNet("INTCB0T" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTCB0T_n, "INTCB0T", 0);

    icmConnectPSENet( handles.CSIB0_p, handles.INTCB0T_n, "INTCBT", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC2T_n = icmNewNet("INTUC2T" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTUC2T_n, "INTUC2T", 0);

    icmConnectPSENet( handles.UARTC2_p, handles.INTUC2T_n, "INTUCT", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT99_n = icmNewNet("INTINT99" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT99_n, "INT99", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT99_n, "INT_99", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTCB0R_n = icmNewNet("INTCB0R" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTCB0R_n, "INTCB0R", 0);

    icmConnectPSENet( handles.CSIB0_p, handles.INTCB0R_n, "INTCBR", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC2R_n = icmNewNet("INTUC2R" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTUC2R_n, "INTUC2R", 0);

    icmConnectPSENet( handles.DMA_p, handles.INTUC2R_n, "INTUC2R", 0);

    icmConnectPSENet( handles.UARTC2_p, handles.INTUC2R_n, "INTUCR", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT100_n = icmNewNet("INTINT100" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT100_n, "INT100", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT100_n, "INT_100", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTCB0RE_n = icmNewNet("INTCB0RE" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTCB0RE_n, "INTCB0RE", 0);

    icmConnectPSENet( handles.CSIB0_p, handles.INTCB0RE_n, "INTCBRE", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC2RE_n = icmNewNet("INTUC2RE" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTUC2RE_n, "INTUC2RE", 0);

    icmConnectPSENet( handles.UARTC2_p, handles.INTUC2RE_n, "INTUCRE", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT101_n = icmNewNet("INTINT101" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT101_n, "INT101", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT101_n, "INT_101", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTINT116_n = icmNewNet("INTINT116" );

    icmConnectPSENet( handles.LOGIC_p, handles.INTINT116_n, "INT116", 0);

    icmConnectPSENet( handles.INTC_p, handles.INTINT116_n, "INT_116", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0OV_n = icmNewNet("INTTS0OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0OV_n, "INT_15", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0OV_n, "INTTSOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CC0_n = icmNewNet("INTTS0CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CC0_n, "INT_16", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CC0_n, "INTTSCC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CC1_n = icmNewNet("INTTS0CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CC1_n, "INT_17", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CC1_n, "INTTSCC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CC2_n = icmNewNet("INTTS0CC2" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CC2_n, "INT_18", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CC2_n, "INTTSCC2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CC3_n = icmNewNet("INTTS0CC3" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CC3_n, "INT_19", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CC3_n, "INTTSCC3", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CC4_n = icmNewNet("INTTS0CC4" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CC4_n, "INT_20", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CC4_n, "INTTSCC4", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CC5_n = icmNewNet("INTTS0CC5" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CC5_n, "INT_21", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CC5_n, "INTTSCC5", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0CD0_n = icmNewNet("INTTS0CD0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0CD0_n, "INT_22", 0);

    icmConnectPSENet( handles.ADC0_p, handles.INTTS0CD0_n, "INTTS0CD", 0);

    icmConnectPSENet( handles.ADC1_p, handles.INTTS0CD0_n, "INTTS0CD", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0CD0_n, "INTTSCD0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0OD_n = icmNewNet("INTTS0OD" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0OD_n, "INT_23", 0);

    icmConnectPSENet( handles.ADC0_p, handles.INTTS0OD_n, "INTTS0OD", 0);

    icmConnectPSENet( handles.ADC1_p, handles.INTTS0OD_n, "INTTS0OD", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0OD_n, "INTTSOD", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0ER_n = icmNewNet("INTTS0ER" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0ER_n, "INT_24", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0ER_n, "INTTSER", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS0WN_n = icmNewNet("INTTS0WN" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS0WN_n, "INT_25", 0);

    icmConnectPSENet( handles.TMS0_p, handles.INTTS0WN_n, "INTTSWN", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1OV_n = icmNewNet("INTTS1OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1OV_n, "INT_26", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1OV_n, "INTTSOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CC0_n = icmNewNet("INTTS1CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CC0_n, "INT_27", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CC0_n, "INTTSCC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CC1_n = icmNewNet("INTTS1CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CC1_n, "INT_28", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CC1_n, "INTTSCC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CC2_n = icmNewNet("INTTS1CC2" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CC2_n, "INT_29", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CC2_n, "INTTSCC2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CC3_n = icmNewNet("INTTS1CC3" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CC3_n, "INT_30", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CC3_n, "INTTSCC3", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CC4_n = icmNewNet("INTTS1CC4" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CC4_n, "INT_31", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CC4_n, "INTTSCC4", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CC5_n = icmNewNet("INTTS1CC5" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CC5_n, "INT_32", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CC5_n, "INTTSCC5", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1CD0_n = icmNewNet("INTTS1CD0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1CD0_n, "INT_33", 0);

    icmConnectPSENet( handles.ADC0_p, handles.INTTS1CD0_n, "INTTS1CD", 0);

    icmConnectPSENet( handles.ADC1_p, handles.INTTS1CD0_n, "INTTS1CD", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1CD0_n, "INTTSCD0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1OD_n = icmNewNet("INTTS1OD" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1OD_n, "INT_34", 0);

    icmConnectPSENet( handles.ADC0_p, handles.INTTS1OD_n, "INTTS1OD", 0);

    icmConnectPSENet( handles.ADC1_p, handles.INTTS1OD_n, "INTTS1OD", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1OD_n, "INTTSOD", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1ER_n = icmNewNet("INTTS1ER" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1ER_n, "INT_35", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1ER_n, "INTTSER", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTS1WN_n = icmNewNet("INTTS1WN" );

    icmConnectPSENet( handles.INTC_p, handles.INTTS1WN_n, "INT_36", 0);

    icmConnectPSENet( handles.TMS1_p, handles.INTTS1WN_n, "INTTSWN", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT0OV_n = icmNewNet("INTTT0OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT0OV_n, "INT_37", 0);

    icmConnectPSENet( handles.TMT0_p, handles.INTTT0OV_n, "INTTTOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT0CC0_n = icmNewNet("INTTT0CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT0CC0_n, "INT_38", 0);

    icmConnectPSENet( handles.TMT0_p, handles.INTTT0CC0_n, "INTTTCC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT0CC1_n = icmNewNet("INTTT0CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT0CC1_n, "INT_39", 0);

    icmConnectPSENet( handles.TMT0_p, handles.INTTT0CC1_n, "INTTTCC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT0EC_n = icmNewNet("INTTT0EC" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT0EC_n, "INT_40", 0);

    icmConnectPSENet( handles.TMT0_p, handles.INTTT0EC_n, "INTTTEC", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT1OV_n = icmNewNet("INTTT1OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT1OV_n, "INT_41", 0);

    icmConnectPSENet( handles.TMT1_p, handles.INTTT1OV_n, "INTTTOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT1CC0_n = icmNewNet("INTTT1CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT1CC0_n, "INT_42", 0);

    icmConnectPSENet( handles.TMT1_p, handles.INTTT1CC0_n, "INTTTCC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT1CC1_n = icmNewNet("INTTT1CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT1CC1_n, "INT_43", 0);

    icmConnectPSENet( handles.TMT1_p, handles.INTTT1CC1_n, "INTTTCC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTT1EC_n = icmNewNet("INTTT1EC" );

    icmConnectPSENet( handles.INTC_p, handles.INTTT1EC_n, "INT_44", 0);

    icmConnectPSENet( handles.TMT1_p, handles.INTTT1EC_n, "INTTTEC", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA0OV_n = icmNewNet("INTTAA0OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA0OV_n, "INT_45", 0);

    icmConnectPSENet( handles.TAA0_p, handles.INTTAA0OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA0CC0_n = icmNewNet("INTTAA0CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA0CC0_n, "INT_46", 0);

    icmConnectPSENet( handles.TAA0_p, handles.INTTAA0CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA0CC1_n = icmNewNet("INTTAA0CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA0CC1_n, "INT_47", 0);

    icmConnectPSENet( handles.TAA0_p, handles.INTTAA0CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA1OV_n = icmNewNet("INTTAA1OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA1OV_n, "INT_48", 0);

    icmConnectPSENet( handles.TAA1_p, handles.INTTAA1OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA1CC0_n = icmNewNet("INTTAA1CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA1CC0_n, "INT_49", 0);

    icmConnectPSENet( handles.TAA1_p, handles.INTTAA1CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA1CC1_n = icmNewNet("INTTAA1CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA1CC1_n, "INT_50", 0);

    icmConnectPSENet( handles.TAA1_p, handles.INTTAA1CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA2OV_n = icmNewNet("INTTAA2OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA2OV_n, "INT_51", 0);

    icmConnectPSENet( handles.TAA2_p, handles.INTTAA2OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA2CC0_n = icmNewNet("INTTAA2CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA2CC0_n, "INT_52", 0);

    icmConnectPSENet( handles.TAA2_p, handles.INTTAA2CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA2CC1_n = icmNewNet("INTTAA2CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA2CC1_n, "INT_53", 0);

    icmConnectPSENet( handles.TAA2_p, handles.INTTAA2CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA3OV_n = icmNewNet("INTTAA3OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA3OV_n, "INT_54", 0);

    icmConnectPSENet( handles.TAA3_p, handles.INTTAA3OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA3CC0_n = icmNewNet("INTTAA3CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA3CC0_n, "INT_55", 0);

    icmConnectPSENet( handles.TAA3_p, handles.INTTAA3CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA3CC1_n = icmNewNet("INTTAA3CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA3CC1_n, "INT_56", 0);

    icmConnectPSENet( handles.TAA3_p, handles.INTTAA3CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA4OV_n = icmNewNet("INTTAA4OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA4OV_n, "INT_57", 0);

    icmConnectPSENet( handles.TAA4_p, handles.INTTAA4OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA4CC0_n = icmNewNet("INTTAA4CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA4CC0_n, "INT_58", 0);

    icmConnectPSENet( handles.TAA4_p, handles.INTTAA4CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA4CC1_n = icmNewNet("INTTAA4CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA4CC1_n, "INT_59", 0);

    icmConnectPSENet( handles.TAA4_p, handles.INTTAA4CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA5OV_n = icmNewNet("INTTAA5OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA5OV_n, "INT_60", 0);

    icmConnectPSENet( handles.TAA5_p, handles.INTTAA5OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA5CC0_n = icmNewNet("INTTAA5CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA5CC0_n, "INT_61", 0);

    icmConnectPSENet( handles.TAA5_p, handles.INTTAA5CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA5CC1_n = icmNewNet("INTTAA5CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA5CC1_n, "INT_62", 0);

    icmConnectPSENet( handles.TAA5_p, handles.INTTAA5CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA6OV_n = icmNewNet("INTTAA6OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA6OV_n, "INT_63", 0);

    icmConnectPSENet( handles.TAA6_p, handles.INTTAA6OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA6CC0_n = icmNewNet("INTTAA6CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA6CC0_n, "INT_64", 0);

    icmConnectPSENet( handles.TAA6_p, handles.INTTAA6CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA6CC1_n = icmNewNet("INTTAA6CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA6CC1_n, "INT_65", 0);

    icmConnectPSENet( handles.TAA6_p, handles.INTTAA6CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA7OV_n = icmNewNet("INTTAA7OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA7OV_n, "INT_66", 0);

    icmConnectPSENet( handles.TAA7_p, handles.INTTAA7OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA7CC0_n = icmNewNet("INTTAA7CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA7CC0_n, "INT_67", 0);

    icmConnectPSENet( handles.TAA7_p, handles.INTTAA7CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA7CC1_n = icmNewNet("INTTAA7CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA7CC1_n, "INT_68", 0);

    icmConnectPSENet( handles.TAA7_p, handles.INTTAA7CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA8OV_n = icmNewNet("INTTAA8OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA8OV_n, "INT_69", 0);

    icmConnectPSENet( handles.TAA8_p, handles.INTTAA8OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA8CC0_n = icmNewNet("INTTAA8CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA8CC0_n, "INT_70", 0);

    icmConnectPSENet( handles.TAA8_p, handles.INTTAA8CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA8CC1_n = icmNewNet("INTTAA8CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA8CC1_n, "INT_71", 0);

    icmConnectPSENet( handles.TAA8_p, handles.INTTAA8CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA9OV_n = icmNewNet("INTTAA9OV" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA9OV_n, "INT_72", 0);

    icmConnectPSENet( handles.TAA9_p, handles.INTTAA9OV_n, "INTTAAOV", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA9CC0_n = icmNewNet("INTTAA9CC0" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA9CC0_n, "INT_73", 0);

    icmConnectPSENet( handles.TAA9_p, handles.INTTAA9CC0_n, "INTTAACC0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTTAA9CC1_n = icmNewNet("INTTAA9CC1" );

    icmConnectPSENet( handles.INTC_p, handles.INTTAA9CC1_n, "INT_74", 0);

    icmConnectPSENet( handles.TAA9_p, handles.INTTAA9CC1_n, "INTTAACC1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTBRG2_n = icmNewNet("INTBRG2" );

    icmConnectPSENet( handles.INTC_p, handles.INTBRG2_n, "INT_76", 0);

    icmConnectPSENet( handles.BRG2_p, handles.INTBRG2_n, "INTBRG", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC0ERR_n = icmNewNet("INTC0ERR" );

    icmConnectPSENet( handles.INTC_p, handles.INTC0ERR_n, "INT_83", 0);

    icmConnectPSENet( handles.CAN0_p, handles.INTC0ERR_n, "INTERR", 0);

    icmConnectPSENet( handles.CAN1_p, handles.INTC0ERR_n, "INTERR", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC0WUPIC_n = icmNewNet("INTC0WUPIC" );

    icmConnectPSENet( handles.INTC_p, handles.INTC0WUPIC_n, "INT_84", 0);

    icmConnectPSENet( handles.CAN0_p, handles.INTC0WUPIC_n, "INTWUP", 0);

    icmConnectPSENet( handles.CAN1_p, handles.INTC0WUPIC_n, "INTWUP", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC0REC_n = icmNewNet("INTC0REC" );

    icmConnectPSENet( handles.INTC_p, handles.INTC0REC_n, "INT_85", 0);

    icmConnectPSENet( handles.CAN0_p, handles.INTC0REC_n, "INTREC", 0);

    icmConnectPSENet( handles.CAN1_p, handles.INTC0REC_n, "INTREC", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC0TRX_n = icmNewNet("INTC0TRX" );

    icmConnectPSENet( handles.INTC_p, handles.INTC0TRX_n, "INT_86", 0);

    icmConnectPSENet( handles.CAN0_p, handles.INTC0TRX_n, "INTTRX", 0);

    icmConnectPSENet( handles.CAN1_p, handles.INTC0TRX_n, "INTTRX", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC1ERR_n = icmNewNet("INTC1ERR" );

    icmConnectPSENet( handles.INTC_p, handles.INTC1ERR_n, "INT_87", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC1WUPIC_n = icmNewNet("INTC1WUPIC" );

    icmConnectPSENet( handles.INTC_p, handles.INTC1WUPIC_n, "INT_88", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC1REC_n = icmNewNet("INTC1REC" );

    icmConnectPSENet( handles.INTC_p, handles.INTC1REC_n, "INT_89", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTC1TRX_n = icmNewNet("INTC1TRX" );

    icmConnectPSENet( handles.INTC_p, handles.INTC1TRX_n, "INT_90", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTCB1T_n = icmNewNet("INTCB1T" );

    icmConnectPSENet( handles.INTC_p, handles.INTCB1T_n, "INT_102", 0);

    icmConnectPSENet( handles.CSIB1_p, handles.INTCB1T_n, "INTCBT", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTCB1R_n = icmNewNet("INTCB1R" );

    icmConnectPSENet( handles.INTC_p, handles.INTCB1R_n, "INT_103", 0);

    icmConnectPSENet( handles.CSIB1_p, handles.INTCB1R_n, "INTCBR", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTCB1RE_n = icmNewNet("INTCB1RE" );

    icmConnectPSENet( handles.INTC_p, handles.INTCB1RE_n, "INT_104", 0);

    icmConnectPSENet( handles.CSIB1_p, handles.INTCB1RE_n, "INTCBRE", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC0RE_n = icmNewNet("INTUC0RE" );

    icmConnectPSENet( handles.INTC_p, handles.INTUC0RE_n, "INT_109", 0);

    icmConnectPSENet( handles.UARTC0_p, handles.INTUC0RE_n, "INTUCRE", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC0T_n = icmNewNet("INTUC0T" );

    icmConnectPSENet( handles.INTC_p, handles.INTUC0T_n, "INT_110", 0);

    icmConnectPSENet( handles.UARTC0_p, handles.INTUC0T_n, "INTUCT", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC1RE_n = icmNewNet("INTUC1RE" );

    icmConnectPSENet( handles.INTC_p, handles.INTUC1RE_n, "INT_111", 0);

    icmConnectPSENet( handles.UARTC1_p, handles.INTUC1RE_n, "INTUCRE", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTUC1T_n = icmNewNet("INTUC1T" );

    icmConnectPSENet( handles.INTC_p, handles.INTUC1T_n, "INT_112", 0);

    icmConnectPSENet( handles.UARTC1_p, handles.INTUC1T_n, "INTUCT", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTAD0_n = icmNewNet("INTAD0" );

    icmConnectPSENet( handles.INTC_p, handles.INTAD0_n, "INT_113", 0);

    icmConnectPSENet( handles.DMA_p, handles.INTAD0_n, "INTDMA0", 0);

    icmConnectPSENet( handles.ADC0_p, handles.INTAD0_n, "INTAD", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.INTAD1_n = icmNewNet("INTAD1" );

    icmConnectPSENet( handles.INTC_p, handles.INTAD1_n, "INT_114", 0);

    icmConnectPSENet( handles.DMA_p, handles.INTAD1_n, "INTDMA1", 0);

    icmConnectPSENet( handles.ADC1_p, handles.INTAD1_n, "INTAD", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.DMA0EN_n = icmNewNet("DMA0EN" );

    icmConnectPSENet( handles.DMA_p, handles.DMA0EN_n, "DMA0EN", 0);

    icmConnectPSENet( handles.ADC0_p, handles.DMA0EN_n, "INTADEN", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.DMA1EN_n = icmNewNet("DMA1EN" );

    icmConnectPSENet( handles.DMA_p, handles.DMA1EN_n, "DMA1EN", 0);

    icmConnectPSENet( handles.ADC1_p, handles.DMA1EN_n, "INTADEN", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ADDMARQ0_n = icmNewNet("ADDMARQ0" );

    icmConnectPSENet( handles.DMA_p, handles.ADDMARQ0_n, "ADDMARQ0", 0);

    icmConnectPSENet( handles.ADC0_p, handles.ADDMARQ0_n, "ADDMARQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.ADDMARQ1_n = icmNewNet("ADDMARQ1" );

    icmConnectPSENet( handles.DMA_p, handles.ADDMARQ1_n, "ADDMARQ1", 0);

    icmConnectPSENet( handles.ADC1_p, handles.ADDMARQ1_n, "ADDMARQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TS0ADTRG0_n = icmNewNet("TS0ADTRG0" );

    icmConnectPSENet( handles.ADC0_p, handles.TS0ADTRG0_n, "TS0ADT0", 0);

    icmConnectPSENet( handles.ADC1_p, handles.TS0ADTRG0_n, "TS0ADT0", 0);

    icmConnectPSENet( handles.TMS0_p, handles.TS0ADTRG0_n, "TSADTRG0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TS0ADTRG1_n = icmNewNet("TS0ADTRG1" );

    icmConnectPSENet( handles.ADC0_p, handles.TS0ADTRG1_n, "TS0ADT1", 0);

    icmConnectPSENet( handles.ADC1_p, handles.TS0ADTRG1_n, "TS0ADT1", 0);

    icmConnectPSENet( handles.TMS0_p, handles.TS0ADTRG1_n, "TSADTRG1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TS1ADTRG0_n = icmNewNet("TS1ADTRG0" );

    icmConnectPSENet( handles.ADC0_p, handles.TS1ADTRG0_n, "TS1ADT0", 0);

    icmConnectPSENet( handles.ADC1_p, handles.TS1ADTRG0_n, "TS1ADT0", 0);

    icmConnectPSENet( handles.TMS1_p, handles.TS1ADTRG0_n, "TSADTRG0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TS1ADTRG1_n = icmNewNet("TS1ADTRG1" );

    icmConnectPSENet( handles.ADC0_p, handles.TS1ADTRG1_n, "TS1ADT1", 0);

    icmConnectPSENet( handles.ADC1_p, handles.TS1ADTRG1_n, "TS1ADT1", 0);

    icmConnectPSENet( handles.TMS1_p, handles.TS1ADTRG1_n, "TSADTRG1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.vcan0_pktn = icmNewPacketnet("vcan0");

    icmConnectPSEPacketnet( handles.CAN0_p, handles.vcan0_pktn, "CAN");

    icmConnectPSEPacketnet( handles.CAN1_p, handles.vcan0_pktn, "CAN");

////////////////////////////////////////////////////////////////////////////////
    handles.vcan1_pktn = icmNewPacketnet("vcan1");
}
