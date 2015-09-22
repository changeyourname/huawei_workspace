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
    icmBusP              pBus_0_b;
    icmBusP              nor0bus_0_b;
    icmBusP              ddr2bus_0_b;
    icmBusP              pBus_1_b;
    icmBusP              nor0bus_1_b;
    icmBusP              ddr2bus_1_b;
    icmBusP              pBus_2_b;
    icmBusP              nor0bus_2_b;
    icmBusP              ddr2bus_2_b;
    icmBusP              pBus_3_b;
    icmBusP              nor0bus_3_b;
    icmBusP              ddr2bus_3_b;
    icmProcessorP        cpu_0_c;
    icmProcessorP        cpu_1_c;
    icmProcessorP        cpu_2_c;
    icmProcessorP        cpu_3_c;
    icmMemoryP           nor0_0_m;
    icmMemoryP           nor1_0_m;
    icmMemoryP           sram1_0_m;
    icmMemoryP           vram1_0_m;
    icmMemoryP           ddr2ram_0_m;
    icmMemoryP           nor0_1_m;
    icmMemoryP           nor1_1_m;
    icmMemoryP           sram1_1_m;
    icmMemoryP           vram1_1_m;
    icmMemoryP           ddr2ram_1_m;
    icmMemoryP           nor0_2_m;
    icmMemoryP           nor1_2_m;
    icmMemoryP           sram1_2_m;
    icmMemoryP           vram1_2_m;
    icmMemoryP           ddr2ram_2_m;
    icmMemoryP           nor0_3_m;
    icmMemoryP           nor1_3_m;
    icmMemoryP           sram1_3_m;
    icmMemoryP           vram1_3_m;
    icmMemoryP           ddr2ram_3_m;
    icmPseP              eth0_0_p;
    icmPseP              usb0_0_p;
    icmPseP              sysRegs_0_p;
    icmPseP              sysCtrl_0_p;
    icmPseP              aac1_0_p;
    icmPseP              mmc1_0_p;
    icmPseP              kb1_0_p;
    icmPseP              ms1_0_p;
    icmPseP              uart0_0_p;
    icmPseP              uart1_0_p;
    icmPseP              uart2_0_p;
    icmPseP              uart3_0_p;
    icmPseP              wdt1_0_p;
    icmPseP              timer01_0_p;
    icmPseP              timer23_0_p;
    icmPseP              dvi1_0_p;
    icmPseP              rtc1_0_p;
    icmPseP              cf1_0_p;
    icmPseP              uart4_0_p;
    icmPseP              clcd_0_p;
    icmPseP              wdt2_0_p;
    icmPseP              dmc1_0_p;
    icmPseP              dma0_0_p;
    icmPseP              smc1_0_p;
    icmPseP              smartLoader_0_p;
    icmPseP              eth0_1_p;
    icmPseP              usb0_1_p;
    icmPseP              sysRegs_1_p;
    icmPseP              sysCtrl_1_p;
    icmPseP              aac1_1_p;
    icmPseP              mmc1_1_p;
    icmPseP              kb1_1_p;
    icmPseP              ms1_1_p;
    icmPseP              uart0_1_p;
    icmPseP              uart1_1_p;
    icmPseP              uart2_1_p;
    icmPseP              uart3_1_p;
    icmPseP              wdt1_1_p;
    icmPseP              timer01_1_p;
    icmPseP              timer23_1_p;
    icmPseP              dvi1_1_p;
    icmPseP              rtc1_1_p;
    icmPseP              cf1_1_p;
    icmPseP              uart4_1_p;
    icmPseP              clcd_1_p;
    icmPseP              wdt2_1_p;
    icmPseP              dmc1_1_p;
    icmPseP              dma0_1_p;
    icmPseP              smc1_1_p;
    icmPseP              smartLoader_1_p;
    icmPseP              eth0_2_p;
    icmPseP              usb0_2_p;
    icmPseP              sysRegs_2_p;
    icmPseP              sysCtrl_2_p;
    icmPseP              aac1_2_p;
    icmPseP              mmc1_2_p;
    icmPseP              kb1_2_p;
    icmPseP              ms1_2_p;
    icmPseP              uart0_2_p;
    icmPseP              uart1_2_p;
    icmPseP              uart2_2_p;
    icmPseP              uart3_2_p;
    icmPseP              wdt1_2_p;
    icmPseP              timer01_2_p;
    icmPseP              timer23_2_p;
    icmPseP              dvi1_2_p;
    icmPseP              rtc1_2_p;
    icmPseP              cf1_2_p;
    icmPseP              uart4_2_p;
    icmPseP              clcd_2_p;
    icmPseP              wdt2_2_p;
    icmPseP              dmc1_2_p;
    icmPseP              dma0_2_p;
    icmPseP              smc1_2_p;
    icmPseP              smartLoader_2_p;
    icmPseP              eth0_3_p;
    icmPseP              usb0_3_p;
    icmPseP              sysRegs_3_p;
    icmPseP              sysCtrl_3_p;
    icmPseP              aac1_3_p;
    icmPseP              mmc1_3_p;
    icmPseP              kb1_3_p;
    icmPseP              ms1_3_p;
    icmPseP              uart0_3_p;
    icmPseP              uart1_3_p;
    icmPseP              uart2_3_p;
    icmPseP              uart3_3_p;
    icmPseP              wdt1_3_p;
    icmPseP              timer01_3_p;
    icmPseP              timer23_3_p;
    icmPseP              dvi1_3_p;
    icmPseP              rtc1_3_p;
    icmPseP              cf1_3_p;
    icmPseP              uart4_3_p;
    icmPseP              clcd_3_p;
    icmPseP              wdt2_3_p;
    icmPseP              dmc1_3_p;
    icmPseP              dma0_3_p;
    icmPseP              smc1_3_p;
    icmPseP              smartLoader_3_p;
    icmNetP              ir2_0_n;
    icmNetP              ir3_0_n;
    icmNetP              ir4_0_n;
    icmNetP              ir5_0_n;
    icmNetP              ir6_0_n;
    icmNetP              ir7_0_n;
    icmNetP              ir8_0_n;
    icmNetP              ir9_0_n;
    icmNetP              ir10_0_n;
    icmNetP              ir12_0_n;
    icmNetP              ir13_0_n;
    icmNetP              ir14_0_n;
    icmNetP              ir15_0_n;
    icmNetP              ir16_0_n;
    icmNetP              ir2_1_n;
    icmNetP              ir3_1_n;
    icmNetP              ir4_1_n;
    icmNetP              ir5_1_n;
    icmNetP              ir6_1_n;
    icmNetP              ir7_1_n;
    icmNetP              ir8_1_n;
    icmNetP              ir9_1_n;
    icmNetP              ir10_1_n;
    icmNetP              ir12_1_n;
    icmNetP              ir13_1_n;
    icmNetP              ir14_1_n;
    icmNetP              ir15_1_n;
    icmNetP              ir16_1_n;
    icmNetP              ir2_2_n;
    icmNetP              ir3_2_n;
    icmNetP              ir4_2_n;
    icmNetP              ir5_2_n;
    icmNetP              ir6_2_n;
    icmNetP              ir7_2_n;
    icmNetP              ir8_2_n;
    icmNetP              ir9_2_n;
    icmNetP              ir10_2_n;
    icmNetP              ir12_2_n;
    icmNetP              ir13_2_n;
    icmNetP              ir14_2_n;
    icmNetP              ir15_2_n;
    icmNetP              ir16_2_n;
    icmNetP              ir2_3_n;
    icmNetP              ir3_3_n;
    icmNetP              ir4_3_n;
    icmNetP              ir5_3_n;
    icmNetP              ir6_3_n;
    icmNetP              ir7_3_n;
    icmNetP              ir8_3_n;
    icmNetP              ir9_3_n;
    icmNetP              ir10_3_n;
    icmNetP              ir12_3_n;
    icmNetP              ir13_3_n;
    icmNetP              ir14_3_n;
    icmNetP              ir15_3_n;
    icmNetP              ir16_3_n;
    icmNetP              wprot_0_n;
    icmNetP              cardin_0_n;
    icmNetP              wprot_1_n;
    icmNetP              cardin_1_n;
    icmNetP              wprot_2_n;
    icmNetP              cardin_2_n;
    icmNetP              wprot_3_n;
    icmNetP              cardin_3_n;
} handles;
