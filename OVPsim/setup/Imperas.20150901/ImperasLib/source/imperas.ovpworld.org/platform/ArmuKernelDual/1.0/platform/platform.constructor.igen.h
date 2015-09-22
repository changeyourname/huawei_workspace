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
    opcDocTextAdd(doc_11_node, "\n        Bare Metal Platform for an ARM Cortex-A9MPx4 to execute the SMP UKernel.\n        This platform instantiates two processor sub-systems.\n        Each sub-system executes the ARM MPCore Boot and Synchronization Example Code");
    optDocNodeP doc_21_node = opcModuleDocSectionAdd(mi, "Limitations");
    opcDocTextAdd(doc_21_node, "BareMetal platform for execution of ARM binary uKernel file");
    optDocNodeP doc_31_node = opcModuleDocSectionAdd(mi, "Reference");
    opcDocTextAdd(doc_31_node, "http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php");


////////////////////////////////////////////////////////////////////////////////
//                            Module Instance sys0
////////////////////////////////////////////////////////////////////////////////

    const char *sys0_path = opcVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "platform",
        "ArmuKernel",
        "1.0",
        OPT_MODULE,
        1   // report errors
    );

    optParamP sys0_param = 0;


    optConnections sys0_conn = {
    };
    opcModuleNew(
        mi,       // parent module
        sys0_path,       // modelfile
        "sys0",   // name
        &sys0_conn,      // conns
        sys0_param        // parameters
    );


////////////////////////////////////////////////////////////////////////////////
//                            Module Instance sys1
////////////////////////////////////////////////////////////////////////////////

    const char *sys1_path = opcVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "platform",
        "ArmuKernel",
        "1.0",
        OPT_MODULE,
        1   // report errors
    );

    optParamP sys1_param = 0;


    optConnections sys1_conn = {
    };
    opcModuleNew(
        mi,       // parent module
        sys1_path,       // modelfile
        "sys1",   // name
        &sys1_conn,      // conns
        sys1_param        // parameters
    );

}


