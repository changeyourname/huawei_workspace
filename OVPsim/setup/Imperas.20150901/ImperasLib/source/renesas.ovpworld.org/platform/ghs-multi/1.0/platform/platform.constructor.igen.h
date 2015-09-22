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

    icmInitAttrs ghs_multi_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, ghs_multi_attrs, 0, 0, "ghs-multi");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc2_node, "Platform Compatible with Greenhills Compiler Output for a V850E1 Processor.\n    The bare metal platform instantiates a single V850 processor instance. \n    The processor operate using big endian data ordering.\n    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.\n    The ICM platform can be passed any application compiled to an V850 elf format.\n    ./platform.<OS>.exe --program application.elf");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc_12_node, "Open Source Apache 2.0");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "BareMetal platform to support images generated with Greenhills Compiler targeting a V850E1 Processor");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_BAREMETAL,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus1
////////////////////////////////////////////////////////////////////////////////


    handles.bus1_b = icmNewBus( "bus1", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu1
////////////////////////////////////////////////////////////////////////////////


    const char *cpu1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "renesas.ovpworld.org",    // vendor
        "processor"         ,    // library
        "v850"              ,    // name
        "1.0"               ,    // version
        "model"                  // model
    );

    icmAttrListP cpu1_attrList = icmNewAttrList();
    icmAddStringAttr(cpu1_attrList, "variant", "V850E1");
    icmAddDoubleAttr(cpu1_attrList, "mips", 100.000000);

    const char *v850Newlib_0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        0                   ,    // vendor
        0                   ,    // library
        "v850Newlib"        ,    // name
        0                   ,    // version
        "model"                  // model
    );
    icmNewProcAttrs cpu1_attrs = ICM_ATTR_DEFAULT;


    handles.cpu1_c = icmNewProcessor(
        "cpu1"              ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        cpu1_path           ,   // model
        0, 
        cpu1_attrs          ,   // procAttrs
        cpu1_attrList       ,   // attrlist
        v850Newlib_0_path   ,   // semihost file
        0
    );


    icmConnectProcessorBusByName( handles.cpu1_c, "INSTRUCTION", handles.bus1_b );

    icmConnectProcessorBusByName( handles.cpu1_c, "DATA", handles.bus1_b );

////////////////////////////////////////////////////////////////////////////////
//                                Memory memory
////////////////////////////////////////////////////////////////////////////////

    handles.memory_m = icmNewMemory("memory", 0x7, 0xffffffff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.memory_m, 0x0);
}
