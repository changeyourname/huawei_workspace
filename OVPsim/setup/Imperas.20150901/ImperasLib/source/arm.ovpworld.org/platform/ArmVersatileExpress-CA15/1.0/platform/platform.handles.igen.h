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
    icmBusP              nor0bus_b;
    icmBusP              ddr2bus_b;
    icmProcessorP        cpu_c;
    icmMemoryP           nor0_m;
    icmMemoryP           nor1_m;
    icmMemoryP           sram1_m;
    icmMemoryP           vram1_m;
    icmMemoryP           ddr2ram_m;
    icmPseP              eth0_p;
    icmPseP              usb0_p;
    icmPseP              sysRegs_p;
    icmPseP              sysCtrl_p;
    icmPseP              aac1_p;
    icmPseP              mmc1_p;
    icmPseP              kb1_p;
    icmPseP              ms1_p;
    icmPseP              uart0_p;
    icmPseP              uart1_p;
    icmPseP              uart2_p;
    icmPseP              uart3_p;
    icmPseP              wdt1_p;
    icmPseP              timer01_p;
    icmPseP              timer23_p;
    icmPseP              dvi1_p;
    icmPseP              rtc1_p;
    icmPseP              cf1_p;
    icmPseP              uart4_p;
    icmPseP              clcd_p;
    icmPseP              wdt2_p;
    icmPseP              dmc1_p;
    icmPseP              dma0_p;
    icmPseP              smc1_p;
    icmPseP              smartLoader_p;
    icmNetP              ir2_n;
    icmNetP              ir3_n;
    icmNetP              ir4_n;
    icmNetP              ir5_n;
    icmNetP              ir6_n;
    icmNetP              ir7_n;
    icmNetP              ir8_n;
    icmNetP              ir9_n;
    icmNetP              ir10_n;
    icmNetP              ir12_n;
    icmNetP              ir13_n;
    icmNetP              ir14_n;
    icmNetP              ir15_n;
    icmNetP              ir16_n;
    icmNetP              wprot_n;
    icmNetP              cardin_n;
} handles;
