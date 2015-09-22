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

#define UNUSED   __attribute__((unused))

static OPT_CONSTRUCT_FN(moduleConstruct) {

    optDocNodeP doc1_node = opcModuleDocSectionAdd(mi, "Licensing");
    opcDocTextAdd(doc1_node, "Open Source Apache 2.0");
    optDocNodeP doc_11_node = opcModuleDocSectionAdd(mi, "Description");
    opcDocTextAdd(doc_11_node, "\n    Bare Metal Platform for an ARM Cortex-A9MPx4 to execute the SMP UKernel.\n    This platform  executes the ARM MPCore Boot and Synchronization Example Code");
    optDocNodeP doc_21_node = opcModuleDocSectionAdd(mi, "Limitations");
    opcDocTextAdd(doc_21_node, "BareMetal platform for execution of ARM binary uKernel file");
    optDocNodeP doc_31_node = opcModuleDocSectionAdd(mi, "Reference");
    opcDocTextAdd(doc_31_node, "http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php");


////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus1
////////////////////////////////////////////////////////////////////////////////

    optBusP bus1_b = opcBusNew(mi, "bus1", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu1
////////////////////////////////////////////////////////////////////////////////

    const char *cpu1_path = opcVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        "1.0",
        OPT_PROCESSOR,
        1   // report errors
    );

    optParamP cpu1_param = 0;

    cpu1_param = opcParamStringSet(cpu1_param, "variant", "Cortex-A9MPx4");
    cpu1_param = opcParamBoolSet(cpu1_param, "UAL", 1);
    cpu1_param = opcParamUns32Set(cpu1_param, "override_CBAR", 0x1f000000);
    cpu1_param = opcParamBoolSet(cpu1_param, "simulateexceptions", 0x1);
    cpu1_param = opcParamDoubleSet(cpu1_param, "mips", 100.000000);
    cpu1_param = opcParamEndianSet(cpu1_param, "endian", OPT_ENDIAN_LITTLE);
    optProcessorP cpu1_c = opcProcessorNew(mi, cpu1_path, "cpu1", cpu1_param);

    opcProcessorBusConnect(cpu1_c, bus1_b, "INSTRUCTION");
    opcProcessorBusConnect(cpu1_c, bus1_b, "DATA");

    const char *armNewlib_0_expath = opcVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "armNewlib",
        0,
        OPT_EXTENSION,
        1   // report errors
    );

    opcProcessorExtensionNew(cpu1_c, armNewlib_0_expath, "armNewlib_0", 0);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart1
////////////////////////////////////////////////////////////////////////////////

    const char *uart1_path = opcVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "UartPL011",
        0,
        OPT_PERIPHERAL,
        1   // report errors
    );

    optParamP uart1_param = 0;

    uart1_param = opcParamStringSet(uart1_param, "variant", "ARM");
    uart1_param = opcParamStringSet(uart1_param, "outfile", "uart1.log");
    uart1_param = opcParamBoolSet(uart1_param, "console", 1);
    uart1_param = opcParamBoolSet(uart1_param, "finishOnDisconnect", 1);

    optPeripheralP uart1_p = opcPeripheralNew(mi, uart1_path, "uart1", uart1_param);

    opcPeripheralBusConnectSlave(uart1_p, bus1_b, "bport1", 0x10009000, 0x10009fff);

    oprPeripheralDiagnosticLevelSet(uart1_p, 1);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP irq_n = opcNetNew(mi, "irq", 0, 0);

////////////////////////////////////////////////////////////////////////////////
//                               Memory memory1
////////////////////////////////////////////////////////////////////////////////

    optMemoryP memory1_m = opcMemoryNew(mi, "memory1", OPT_PRIV_RWX, 0xfffffff, 0);

    opcMemoryBusConnect(memory1_m, bus1_b, "sp1", 0x0, 0xfffffff);


////////////////////////////////////////////////////////////////////////////////
//                             Memory deviceDummy1
////////////////////////////////////////////////////////////////////////////////

    optMemoryP deviceDummy1_m = opcMemoryNew(mi, "deviceDummy1", OPT_PRIV_RWX, 0x8fff, 0);

    opcMemoryBusConnect(deviceDummy1_m, bus1_b, "sp1", 0x10000000, 0x10008fff);


////////////////////////////////////////////////////////////////////////////////
//                             Memory deviceDummy2
////////////////////////////////////////////////////////////////////////////////

    optMemoryP deviceDummy2_m = opcMemoryNew(mi, "deviceDummy2", OPT_PRIV_RWX, 0xefff5fff, 0);

    opcMemoryBusConnect(deviceDummy2_m, bus1_b, "sp1", 0x1000a000, 0xffffffff);

////////////////////////////////////////////////////////////////////////////////
//                               Program loading
////////////////////////////////////////////////////////////////////////////////

    if(!opcProcessorApplicationLoad(cpu1_c, "cli.axf", OPT_LDR_DEFAULT|OPT_LDR_SET_START, 0)){
        opmPrintf("%s", opmLastMessage());
        opcTerminate();
        opmExit(1);
    }

    opcProcessorNetConnect(cpu1_c, irq_n, "SPI36");
    opcPeripheralNetConnect(uart1_p, irq_n, "irq");
}


