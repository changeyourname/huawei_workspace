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
    icmBusP              smbus_b;
    icmBusP              iobus_b;
    icmBusP              dbus_b;
    icmBusP              ibus_b;
    icmProcessorP        cpu_c;
    icmMemoryP           pb_cpu_to_ddr2_bot_m;
    icmMemoryP           tlb_miss_ram_1k_m;
    icmMemoryP           flash_mem_64m_m;
    icmPseP              uart_s1_p;
    icmPseP              sysid_p;
    icmPseP              jtag_uart_p;
    icmPseP              timer_1ms_p;
    icmNetP              irq10_n;
    icmNetP              irq1_n;
    icmNetP              irq11_n;
} handles;
