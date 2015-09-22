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

#define UART0  "FreescaleKinetis60/uart0/"
#define UART1  "FreescaleKinetis60/uart1/"
#define UART2  "FreescaleKinetis60/uart2/"
#define UART3  "FreescaleKinetis60/uart3/"
#define UART4  "FreescaleKinetis60/uart4/"
#define UART5  "FreescaleKinetis60/uart5/"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
    icmCLPP parser = icmCLParser("FreescaleKinetis60", ICM_AC_ALL);
    cmdParserAddUserArgs(parser);

    icmCLParseArgs(parser, argc, argv);

    if (options.uart0console) {
        icmOverride(UART0"console", "1");
    }
    if (options.uart1console) {
        icmOverride(UART1"console", "1");
    }
    if (options.uart2console) {
        icmOverride(UART2"console", "1");
    }
    if (options.uart3console) {
        icmOverride(UART3"console", "1");
    }
    if (options.uart4console) {
        icmOverride(UART4"console", "1");
    }
    if (options.uart5console) {
        icmOverride(UART5"console", "1");
    }

    platformConstructor();

    // Set simulation time slice to value smaller than
    // character rate for 115000 baud rate (~70 uS per char)
    icmSetSimulationTimeSlice(.0000035);

    icmSimulatePlatform();

    icmTerminate();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
