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
////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("ArmCortexMuCOS-II", ICM_AC_ALL);
    cmdParserAddUserArgs(parser);

    icmCLParseArgs(parser, argc, argv);

    platformConstructor();

    if(options.kernel) {
    	icmMessage("I", "ArmCortexMuCOS-II_LOAD", "Loading kernel file %s", options.kernel);
        icmLoadProcessorMemory(handles.cpu1_c, options.kernel, ICM_LOAD_DEFAULT, True, False);
    }

    icmMessage("I", "ArmCortexMuCOS-II", "Running Micrium uC/OS-II Multitasking Kernel");
    icmSimulationStarting();

    icmSimulatePlatform();

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
