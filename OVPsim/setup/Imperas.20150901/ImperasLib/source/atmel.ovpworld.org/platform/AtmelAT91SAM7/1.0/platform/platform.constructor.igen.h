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

    icmInitAttrs AtmelAT91SAM7_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, AtmelAT91SAM7_attrs, 0, 0, "AtmelAT91SAM7");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc2_node, " Simple platform of Atmel AT91 ARM7TDMI based system\n");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_12_node, "This platform is sufficient to boot Linux");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_22_node, "Rev. 1354D–ATARM–08/02");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc_32_node, "Open Source Apache 2.0");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus mainbus
////////////////////////////////////////////////////////////////////////////////


    handles.mainbus_b = icmNewBus( "mainbus", 32);

////////////////////////////////////////////////////////////////////////////////
//                           Processor ARM7TDMICore
////////////////////////////////////////////////////////////////////////////////


    const char *ARM7TDMICore_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP ARM7TDMICore_attrList = icmNewAttrList();
    icmAddStringAttr(ARM7TDMICore_attrList, "variant", "ARM7TDMI");
    icmAddDoubleAttr(ARM7TDMICore_attrList, "mips", 100.000000);
    icmAddStringAttr(ARM7TDMICore_attrList, "endian", "little");

    const char *loader_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        "intercept"         ,    // library
        "loader"            ,    // name
        0                   ,    // version
        "model"                  // model
    );
    icmNewProcAttrs ARM7TDMICore_attrs = ICM_ATTR_SIMEX;


    handles.ARM7TDMICore_c = icmNewProcessor(
        "ARM7TDMICore"      ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        ARM7TDMICore_path   ,   // model
        0, 
        ARM7TDMICore_attrs  ,   // procAttrs
        ARM7TDMICore_attrList,   // attrlist
        loader_0_path       ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                   PSE AIC
////////////////////////////////////////////////////////////////////////////////


    const char *AIC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "AdvancedInterruptController",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP AIC_attrList = icmNewAttrList();

    handles.AIC_p = icmNewPSE(
        "AIC"               ,   // name
        AIC_path            ,   // model
        AIC_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.AIC_p, handles.mainbus_b, "bp1", 0, 0xfffff000, 0xffffffff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE WD
////////////////////////////////////////////////////////////////////////////////


    const char *WD_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "WatchdogTimer"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP WD_attrList = icmNewAttrList();

    handles.WD_p = icmNewPSE(
        "WD"                ,   // name
        WD_path             ,   // model
        WD_attrList         ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.WD_p, handles.mainbus_b, "bp1", 0, 0xffff8000, 0xffffbfff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE PS
////////////////////////////////////////////////////////////////////////////////


    const char *PS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "PowerSaving"       ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP PS_attrList = icmNewAttrList();

    handles.PS_p = icmNewPSE(
        "PS"                ,   // name
        PS_path             ,   // model
        PS_attrList         ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PS_p, handles.mainbus_b, "bp1", 0, 0xffff4000, 0xffff7fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE PIO
////////////////////////////////////////////////////////////////////////////////


    const char *PIO_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "ParallelIOController",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP PIO_attrList = icmNewAttrList();

    handles.PIO_p = icmNewPSE(
        "PIO"               ,   // name
        PIO_path            ,   // model
        PIO_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PIO_p, handles.mainbus_b, "bp1", 0, 0xffff0000, 0xffff3fff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE TC
////////////////////////////////////////////////////////////////////////////////


    const char *TC_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "TimerCounter"      ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP TC_attrList = icmNewAttrList();

    handles.TC_p = icmNewPSE(
        "TC"                ,   // name
        TC_path             ,   // model
        TC_attrList         ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.TC_p, handles.mainbus_b, "bp1", 0, 0xfffe0000, 0xfffe3fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE USART0
////////////////////////////////////////////////////////////////////////////////


    const char *USART0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "UsartInterface"    ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP USART0_attrList = icmNewAttrList();
    icmAddUns64Attr(USART0_attrList, "finishOnDisconnect", 1LL);

    handles.USART0_p = icmNewPSE(
        "USART0"            ,   // name
        USART0_path         ,   // model
        USART0_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.USART0_p, handles.mainbus_b, "asb", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.USART0_p, handles.mainbus_b, "apb", 0, 0xfffd0000, 0xfffd3fff);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE USART1
////////////////////////////////////////////////////////////////////////////////


    const char *USART1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "UsartInterface"    ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP USART1_attrList = icmNewAttrList();

    handles.USART1_p = icmNewPSE(
        "USART1"            ,   // name
        USART1_path         ,   // model
        USART1_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.USART1_p, handles.mainbus_b, "asb", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.USART1_p, handles.mainbus_b, "apb", 0, 0xfffcc000, 0xfffcffff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE SF
////////////////////////////////////////////////////////////////////////////////


    const char *SF_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "atmel.ovpworld.org",    // vendor
        0                   ,    // library
        "SpecialFunction"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP SF_attrList = icmNewAttrList();

    handles.SF_p = icmNewPSE(
        "SF"                ,   // name
        SF_path             ,   // model
        SF_attrList         ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.SF_p, handles.mainbus_b, "bp1", 0, 0xfff00000, 0xfff03fff);

    icmConnectProcessorBusByName( handles.ARM7TDMICore_c, "INSTRUCTION", handles.mainbus_b );

    icmConnectProcessorBusByName( handles.ARM7TDMICore_c, "DATA", handles.mainbus_b );

////////////////////////////////////////////////////////////////////////////////
//                                Memory extDev
////////////////////////////////////////////////////////////////////////////////

    handles.extDev_m = icmNewMemory("extDev", 0x7, 0xff7fffff);


    icmConnectMemoryToBus( handles.mainbus_b, "sp1", handles.extDev_m, 0x400000);

////////////////////////////////////////////////////////////////////////////////
//                                 Memory ram0
////////////////////////////////////////////////////////////////////////////////

    handles.ram0_m = icmNewMemory("ram0", 0x7, 0xfffff);


    icmConnectMemoryToBus( handles.mainbus_b, "sp1", handles.ram0_m, 0x0);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.NFIQ_n = icmNewNet("NFIQ" );

    icmConnectProcessorNet( handles.ARM7TDMICore_c, handles.NFIQ_n, "fiq", 0);

    icmConnectPSENet( handles.AIC_p, handles.NFIQ_n, "NFIQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.NIRQ_n = icmNewNet("NIRQ" );

    icmConnectProcessorNet( handles.ARM7TDMICore_c, handles.NIRQ_n, "irq", 0);

    icmConnectPSENet( handles.AIC_p, handles.NIRQ_n, "NIRQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.US0IRQ_n = icmNewNet("US0IRQ" );

    icmConnectPSENet( handles.AIC_p, handles.US0IRQ_n, "US0IRQ", 0);

    icmConnectPSENet( handles.USART0_p, handles.US0IRQ_n, "IRQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.US1IRQ_n = icmNewNet("US1IRQ" );

    icmConnectPSENet( handles.AIC_p, handles.US1IRQ_n, "US1IRQ", 0);

    icmConnectPSENet( handles.USART1_p, handles.US1IRQ_n, "IRQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TC0IRQ_n = icmNewNet("TC0IRQ" );

    icmConnectPSENet( handles.AIC_p, handles.TC0IRQ_n, "TC0IRQ", 0);

    icmConnectPSENet( handles.TC_p, handles.TC0IRQ_n, "IRQ0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TC1IRQ_n = icmNewNet("TC1IRQ" );

    icmConnectPSENet( handles.AIC_p, handles.TC1IRQ_n, "TC1IRQ", 0);

    icmConnectPSENet( handles.TC_p, handles.TC1IRQ_n, "IRQ1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.TC2IRQ_n = icmNewNet("TC2IRQ" );

    icmConnectPSENet( handles.AIC_p, handles.TC2IRQ_n, "TC2IRQ", 0);

    icmConnectPSENet( handles.TC_p, handles.TC2IRQ_n, "IRQ2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.WDIRQ_n = icmNewNet("WDIRQ" );

    icmConnectPSENet( handles.AIC_p, handles.WDIRQ_n, "WDIRQ", 0);

    icmConnectPSENet( handles.WD_p, handles.WDIRQ_n, "IRQ", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.PIOIRQ_n = icmNewNet("PIOIRQ" );

    icmConnectPSENet( handles.AIC_p, handles.PIOIRQ_n, "PIOIRQ", 0);

    icmConnectPSENet( handles.PIO_p, handles.PIOIRQ_n, "IRQ", 0);
}
