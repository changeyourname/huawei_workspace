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
    icmBusP              bus1_b;
    icmProcessorP        microblaze_0_c;
    icmMemoryP           BOOTMEM_m;
    icmMemoryP           DDR2_SDRAM_m;
    icmMemoryP           UNKNOWN_PERIPH_m;
    icmPseP              LEDs_8Bit_p;
    icmPseP              IIC_EEPROM_p;
    icmPseP              xps_intc_0_p;
    icmPseP              Hard_Ethernet_MAC_p;
    icmPseP              SysACE_CompactFlash_p;
    icmPseP              xps_timer_1_p;
    icmPseP              RS232_Uart_1_p;
    icmPseP              debug_module_p;
    icmPseP              mpmc_p;
    icmPseP              mb_plb_p;
    icmNetP              Interrupt_net_n;
    icmNetP              Interrupt_3_n;
    icmNetP              Interrupt_8_n;
} handles;
