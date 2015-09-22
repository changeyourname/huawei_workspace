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
    icmMemoryP           bootrom_m;
    icmMemoryP           sysram_m;
    icmPseP              mcsm_p;
    icmPseP              dma0_p;
    icmPseP              dmamux0_p;
    icmPseP              dmamux1_p;
    icmPseP              uart0_p;
    icmPseP              uart1_p;
    icmPseP              uart2_p;
    icmPseP              uart3_p;
    icmPseP              iomuxc_p;
    icmPseP              anadig_p;
    icmPseP              ccm_p;
    icmPseP              dma1_p;
    icmPseP              dmamux2_p;
    icmPseP              dmamux3_p;
    icmPseP              ddrmc_p;
    icmNetP              SPI93_n;
    icmNetP              SPI94_n;
    icmNetP              SPI95_n;
    icmNetP              SPI96_n;
} handles;
