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

// This file declares handles to platform objects.
// Access to these are required by parts of the ICM API.
// This file should NOT need to be edited.

struct handlesS {
    icmBusP              pBus_b;
    icmProcessorP        cpu_c;
    icmMemoryP           flash_m;
    icmMemoryP           sram_m;
    icmPseP              dmac_p;
    icmPseP              flexbus_p;
    icmPseP              mpu_p;
    icmPseP              fmc_p;
    icmPseP              dmamux0_p;
    icmPseP              dmamux1_p;
    icmPseP              rtc_p;
    icmPseP              simlpl_p;
    icmPseP              sim_p;
    icmPseP              amux_p;
    icmPseP              bmux_p;
    icmPseP              cmux_p;
    icmPseP              dmux_p;
    icmPseP              emux_p;
    icmPseP              swwd_p;
    icmPseP              mcg_p;
    icmPseP              osc0_p;
    icmPseP              uart0_p;
    icmPseP              uart1_p;
    icmPseP              uart2_p;
    icmPseP              uart3_p;
    icmPseP              llwu_p;
    icmPseP              pmc_p;
    icmPseP              smc_p;
    icmPseP              rcm_p;
    icmPseP              osc1_p;
    icmPseP              uart4_p;
    icmPseP              uart5_p;
    icmNetP              int45_n;
    icmNetP              int47_n;
    icmNetP              int49_n;
    icmNetP              int51_n;
    icmNetP              int53_n;
    icmNetP              int55_n;
} handles;
