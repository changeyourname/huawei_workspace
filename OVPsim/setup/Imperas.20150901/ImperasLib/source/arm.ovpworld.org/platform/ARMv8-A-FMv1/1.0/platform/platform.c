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
//                              Version 99999999
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// Be careful to avoid overwriting any edits if igen is run a second time.
// Only use -overwrite if you wish to overwrite this file.

#include "platform.options.igen.h"
#include "platform.handles.igen.h"
#include "platform.constructor.igen.h"

#include "platform.clp.igen.h"

// Startup iterator function
ICM_SMP_ITERATOR_FN(setStartAddress);

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("ARMv8-A-FMv1", ICM_AC_ALL);
    cmdParserAddUserArgs(parser);

    // insert modifications to the CLP here

    icmCLParseArgs(parser, argc, argv);

    // insert overrides here

    platformConstructor();

    // Set start address on each leaf processor
    // TODO: get this from override for smartLoader physicalbase attribute
    Addr startAddress = 0x80000000;
    icmIterAllDescendants(handles.cpu_c, setStartAddress, &startAddress);

    // Set default simulation time slice to optimize performance
    icmSetSimulationTimeSlice(0.0001);

    icmSimulationStarting();
    icmSimulatePlatform();

    // Add post simulation analysis or clean up code here

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

ICM_SMP_ITERATOR_FN(setStartAddress) {
    Addr start = *(Addr *)userData;
    icmMessage(
        "I", "STARTUP",
        "Set start address for %s to 0x"FMT_A0Nx,
        icmGetProcessorName(processor, "/"),
        start
    );
    icmSetPC(processor, start);
}
