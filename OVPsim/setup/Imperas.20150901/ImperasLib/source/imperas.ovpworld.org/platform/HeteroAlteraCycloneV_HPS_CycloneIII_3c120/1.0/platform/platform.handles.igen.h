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
    icmBusP              smbus_HPS_b;
    icmBusP              smbus_3c120_b;
    icmBusP              iobus_3c120_b;
    icmBusP              dbus_3c120_b;
    icmBusP              ibus_3c120_b;
    icmProcessorP        cpu_A9MPx2_c;
    icmProcessorP        cpu_Nios_II_c;
    icmMemoryP           sram1_m;
    icmMemoryP           pb_cpu_to_ddr2_bot_m;
    icmMemoryP           tlb_miss_ram_1k_m;
    icmMemoryP           flash_mem_64m_m;
    icmPseP              L2_p;
    icmPseP              timer0_p;
    icmPseP              timer1_p;
    icmPseP              timer2_p;
    icmPseP              timer3_p;
    icmPseP              uart0_p;
    icmPseP              uart1_p;
    icmPseP              RSTMGR0_p;
    icmPseP              SYSMGR0_p;
    icmPseP              CLKMGR0_p;
    icmPseP              pdma0_p;
    icmPseP              gmac0_p;
    icmPseP              emac0_dma_p;
    icmPseP              gmac1_p;
    icmPseP              emac1_dma_p;
    icmPseP              smartLoader_p;
    icmPseP              uart_s1_p;
    icmPseP              sysid_p;
    icmPseP              jtag_uart_p;
    icmPseP              timer_1ms_p;
    icmNetP              ir199_n;
    icmNetP              ir200_n;
    icmNetP              ir201_n;
    icmNetP              ir202_n;
    icmNetP              ir194_n;
    icmNetP              ir195_n;
    icmNetP              cpu0Reset_n;
    icmNetP              cpu1Reset_n;
    icmNetP              irq10_n;
    icmNetP              irq1_n;
    icmNetP              irq11_n;
} handles;
