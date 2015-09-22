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

    icmInitAttrs FreescaleKinetis60_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, FreescaleKinetis60_attrs, 0, 0, "FreescaleKinetis60");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "\nFreescale Kinetis K60 Platform\n");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "\nOnly enough functionality modeled to boot MQX. Most peripherals modeled as dummy register ports\n");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "Development based on document number: K60P144M100SF2RM Rev. 6, Nov 2011");
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
        "armm"              ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu_attrList = icmNewAttrList();
    icmAddStringAttr(cpu_attrList, "variant", "Cortex-M4F");
    icmAddUns64Attr(cpu_attrList, "UAL", 1LL);
    icmAddUns64Attr(cpu_attrList, "override_priorityBits", 4LL);
    icmAddUns64Attr(cpu_attrList, "override_numInterrupts", 94LL);
    icmAddDoubleAttr(cpu_attrList, "mips", 120.000000);
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
//                                  PSE dmac
////////////////////////////////////////////////////////////////////////////////


    const char *dmac_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "KinetisDMAC"       ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmac_attrList = icmNewAttrList();

    handles.dmac_p = icmNewPSE(
        "dmac"              ,   // name
        dmac_path           ,   // model
        dmac_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmac_p, handles.pBus_b, "bport1", 0, 0x40008000, 0x40008fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE flexbus
////////////////////////////////////////////////////////////////////////////////


    const char *flexbus_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP flexbus_attrList = icmNewAttrList();

    handles.flexbus_p = icmNewPSE(
        "flexbus"           ,   // name
        flexbus_path        ,   // model
        flexbus_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.flexbus_p, handles.pBus_b, "bport1", 0, 0x4000c000, 0x4000cfff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE mpu
////////////////////////////////////////////////////////////////////////////////


    const char *mpu_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mpu_attrList = icmNewAttrList();

    handles.mpu_p = icmNewPSE(
        "mpu"               ,   // name
        mpu_path            ,   // model
        mpu_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mpu_p, handles.pBus_b, "bport1", 0, 0x4000d000, 0x4000dfff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE fmc
////////////////////////////////////////////////////////////////////////////////


    const char *fmc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP fmc_attrList = icmNewAttrList();

    handles.fmc_p = icmNewPSE(
        "fmc"               ,   // name
        fmc_path            ,   // model
        fmc_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.fmc_p, handles.pBus_b, "bport1", 0, 0x4001f000, 0x4001ffff);

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

    icmConnectPSEBus( handles.dmamux0_p, handles.pBus_b, "bport1", 0, 0x40021000, 0x40021fff);

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

    icmConnectPSEBus( handles.dmamux1_p, handles.pBus_b, "bport1", 0, 0x40022000, 0x40022fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE rtc
////////////////////////////////////////////////////////////////////////////////


    const char *rtc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc_attrList = icmNewAttrList();

    handles.rtc_p = icmNewPSE(
        "rtc"               ,   // name
        rtc_path            ,   // model
        rtc_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc_p, handles.pBus_b, "bport1", 0, 0x4003d000, 0x4003dfff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE simlpl
////////////////////////////////////////////////////////////////////////////////


    const char *simlpl_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP simlpl_attrList = icmNewAttrList();

    handles.simlpl_p = icmNewPSE(
        "simlpl"            ,   // name
        simlpl_path         ,   // model
        simlpl_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.simlpl_p, handles.pBus_b, "bport1", 0, 0x40047000, 0x40047fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE sim
////////////////////////////////////////////////////////////////////////////////


    const char *sim_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP sim_attrList = icmNewAttrList();

    handles.sim_p = icmNewPSE(
        "sim"               ,   // name
        sim_path            ,   // model
        sim_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sim_p, handles.pBus_b, "bport1", 0, 0x40048000, 0x40048fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE amux
////////////////////////////////////////////////////////////////////////////////


    const char *amux_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP amux_attrList = icmNewAttrList();

    handles.amux_p = icmNewPSE(
        "amux"              ,   // name
        amux_path           ,   // model
        amux_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.amux_p, handles.pBus_b, "bport1", 0, 0x40049000, 0x40049fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE bmux
////////////////////////////////////////////////////////////////////////////////


    const char *bmux_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP bmux_attrList = icmNewAttrList();

    handles.bmux_p = icmNewPSE(
        "bmux"              ,   // name
        bmux_path           ,   // model
        bmux_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.bmux_p, handles.pBus_b, "bport1", 0, 0x4004a000, 0x4004afff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE cmux
////////////////////////////////////////////////////////////////////////////////


    const char *cmux_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP cmux_attrList = icmNewAttrList();

    handles.cmux_p = icmNewPSE(
        "cmux"              ,   // name
        cmux_path           ,   // model
        cmux_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.cmux_p, handles.pBus_b, "bport1", 0, 0x4004b000, 0x4004bfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE dmux
////////////////////////////////////////////////////////////////////////////////


    const char *dmux_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP dmux_attrList = icmNewAttrList();

    handles.dmux_p = icmNewPSE(
        "dmux"              ,   // name
        dmux_path           ,   // model
        dmux_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.dmux_p, handles.pBus_b, "bport1", 0, 0x4004c000, 0x4004cfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE emux
////////////////////////////////////////////////////////////////////////////////


    const char *emux_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP emux_attrList = icmNewAttrList();

    handles.emux_p = icmNewPSE(
        "emux"              ,   // name
        emux_path           ,   // model
        emux_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.emux_p, handles.pBus_b, "bport1", 0, 0x4004d000, 0x4004dfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE swwd
////////////////////////////////////////////////////////////////////////////////


    const char *swwd_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP swwd_attrList = icmNewAttrList();

    handles.swwd_p = icmNewPSE(
        "swwd"              ,   // name
        swwd_path           ,   // model
        swwd_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.swwd_p, handles.pBus_b, "bport1", 0, 0x40052000, 0x40052fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE mcg
////////////////////////////////////////////////////////////////////////////////


    const char *mcg_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "KinetisMCG"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP mcg_attrList = icmNewAttrList();

    handles.mcg_p = icmNewPSE(
        "mcg"               ,   // name
        mcg_path            ,   // model
        mcg_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mcg_p, handles.pBus_b, "bport1", 0, 0x40064000, 0x40064fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE osc0
////////////////////////////////////////////////////////////////////////////////


    const char *osc0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP osc0_attrList = icmNewAttrList();

    handles.osc0_p = icmNewPSE(
        "osc0"              ,   // name
        osc0_path           ,   // model
        osc0_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.osc0_p, handles.pBus_b, "bport1", 0, 0x40065000, 0x40065fff);

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
    icmAddUns64Attr(uart0_attrList, "fifoSize", 8LL);
    icmAddUns64Attr(uart0_attrList, "moduleClkFreq", 60000000LL);
    icmAddStringAttr(uart0_attrList, "outfile", "uart0_outfile.txt");

    handles.uart0_p = icmNewPSE(
        "uart0"             ,   // name
        uart0_path          ,   // model
        uart0_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart0_p, handles.pBus_b, "bport1", 0, 0x4006a000, 0x4006afff);

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
    icmAddUns64Attr(uart1_attrList, "fifoSize", 8LL);
    icmAddUns64Attr(uart1_attrList, "moduleClkFreq", 60000000LL);
    icmAddUns64Attr(uart1_attrList, "finishOnDisconnect", 1LL);
    icmAddStringAttr(uart1_attrList, "outfile", "uart1_outfile.txt");

    handles.uart1_p = icmNewPSE(
        "uart1"             ,   // name
        uart1_path          ,   // model
        uart1_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart1_p, handles.pBus_b, "bport1", 0, 0x4006b000, 0x4006bfff);

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
    icmAddUns64Attr(uart2_attrList, "fifoSize", 1LL);
    icmAddUns64Attr(uart2_attrList, "moduleClkFreq", 60000000LL);
    icmAddUns64Attr(uart2_attrList, "finishOnDisconnect", 1LL);
    icmAddStringAttr(uart2_attrList, "outfile", "uart2_outfile.txt");

    handles.uart2_p = icmNewPSE(
        "uart2"             ,   // name
        uart2_path          ,   // model
        uart2_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart2_p, handles.pBus_b, "bport1", 0, 0x4006c000, 0x4006cfff);

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
    icmAddUns64Attr(uart3_attrList, "fifoSize", 1LL);
    icmAddUns64Attr(uart3_attrList, "moduleClkFreq", 60000000LL);
    icmAddUns64Attr(uart3_attrList, "finishOnDisconnect", 1LL);
    icmAddStringAttr(uart3_attrList, "outfile", "uart3_outfile.txt");

    handles.uart3_p = icmNewPSE(
        "uart3"             ,   // name
        uart3_path          ,   // model
        uart3_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart3_p, handles.pBus_b, "bport1", 0, 0x4006d000, 0x4006dfff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE llwu
////////////////////////////////////////////////////////////////////////////////


    const char *llwu_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP llwu_attrList = icmNewAttrList();

    handles.llwu_p = icmNewPSE(
        "llwu"              ,   // name
        llwu_path           ,   // model
        llwu_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.llwu_p, handles.pBus_b, "bport1", 0, 0x4007c000, 0x4007cfff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE pmc
////////////////////////////////////////////////////////////////////////////////


    const char *pmc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP pmc_attrList = icmNewAttrList();

    handles.pmc_p = icmNewPSE(
        "pmc"               ,   // name
        pmc_path            ,   // model
        pmc_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pmc_p, handles.pBus_b, "bport1", 0, 0x4007d000, 0x4007dfff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE smc
////////////////////////////////////////////////////////////////////////////////


    const char *smc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP smc_attrList = icmNewAttrList();

    handles.smc_p = icmNewPSE(
        "smc"               ,   // name
        smc_path            ,   // model
        smc_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.smc_p, handles.pBus_b, "bport1", 0, 0x4007e000, 0x4007efff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE rcm
////////////////////////////////////////////////////////////////////////////////


    const char *rcm_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP rcm_attrList = icmNewAttrList();

    handles.rcm_p = icmNewPSE(
        "rcm"               ,   // name
        rcm_path            ,   // model
        rcm_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rcm_p, handles.pBus_b, "bport1", 0, 0x4007f000, 0x4007ffff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE osc1
////////////////////////////////////////////////////////////////////////////////


    const char *osc1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "dummyPort"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP osc1_attrList = icmNewAttrList();

    handles.osc1_p = icmNewPSE(
        "osc1"              ,   // name
        osc1_path           ,   // model
        osc1_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.osc1_p, handles.pBus_b, "bport1", 0, 0x400e5000, 0x400e5fff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart4
////////////////////////////////////////////////////////////////////////////////


    const char *uart4_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart4_attrList = icmNewAttrList();
    icmAddUns64Attr(uart4_attrList, "fifoSize", 1LL);
    icmAddUns64Attr(uart4_attrList, "moduleClkFreq", 60000000LL);
    icmAddUns64Attr(uart4_attrList, "finishOnDisconnect", 1LL);
    icmAddStringAttr(uart4_attrList, "outfile", "uart4_outfile.txt");

    handles.uart4_p = icmNewPSE(
        "uart4"             ,   // name
        uart4_path          ,   // model
        uart4_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart4_p, handles.pBus_b, "bport1", 0, 0x400ea000, 0x400eafff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart5
////////////////////////////////////////////////////////////////////////////////


    const char *uart5_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "freescale.ovpworld.org",    // vendor
        0                   ,    // library
        "Uart"              ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP uart5_attrList = icmNewAttrList();
    icmAddUns64Attr(uart5_attrList, "fifoSize", 1LL);
    icmAddUns64Attr(uart5_attrList, "moduleClkFreq", 60000000LL);
    icmAddUns64Attr(uart5_attrList, "finishOnDisconnect", 1LL);
    icmAddStringAttr(uart5_attrList, "outfile", "uart5_outfile.txt");

    handles.uart5_p = icmNewPSE(
        "uart5"             ,   // name
        uart5_path          ,   // model
        uart5_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uart5_p, handles.pBus_b, "bport1", 0, 0x400eb000, 0x400ebfff);

    icmConnectProcessorBusByName( handles.cpu_c, "INSTRUCTION", handles.pBus_b );

    icmConnectProcessorBusByName( handles.cpu_c, "DATA", handles.pBus_b );

////////////////////////////////////////////////////////////////////////////////
//                                Memory flash
////////////////////////////////////////////////////////////////////////////////

    handles.flash_m = icmNewMemory("flash", 0x7, 0xfffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.flash_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory sram
////////////////////////////////////////////////////////////////////////////////

    handles.sram_m = icmNewMemory("sram", 0x7, 0x1ffff);


    icmConnectMemoryToBus( handles.pBus_b, "sp1", handles.sram_m, 0x1fff0000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.int45_n = icmNewNet("int45" );

    icmConnectProcessorNet( handles.cpu_c, handles.int45_n, "int45", 0);

    icmConnectPSENet( handles.uart0_p, handles.int45_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.int47_n = icmNewNet("int47" );

    icmConnectProcessorNet( handles.cpu_c, handles.int47_n, "int47", 0);

    icmConnectPSENet( handles.uart1_p, handles.int47_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.int49_n = icmNewNet("int49" );

    icmConnectProcessorNet( handles.cpu_c, handles.int49_n, "int49", 0);

    icmConnectPSENet( handles.uart2_p, handles.int49_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.int51_n = icmNewNet("int51" );

    icmConnectProcessorNet( handles.cpu_c, handles.int51_n, "int51", 0);

    icmConnectPSENet( handles.uart3_p, handles.int51_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.int53_n = icmNewNet("int53" );

    icmConnectProcessorNet( handles.cpu_c, handles.int53_n, "int53", 0);

    icmConnectPSENet( handles.uart4_p, handles.int53_n, "Interrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.int55_n = icmNewNet("int55" );

    icmConnectProcessorNet( handles.cpu_c, handles.int55_n, "int55", 0);

    icmConnectPSENet( handles.uart5_p, handles.int55_n, "Interrupt", 0);
}
