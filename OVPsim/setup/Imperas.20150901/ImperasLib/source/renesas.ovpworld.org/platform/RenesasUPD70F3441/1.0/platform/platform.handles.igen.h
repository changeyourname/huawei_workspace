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
    icmBusP              vfb_b;
    icmProcessorP        CPU_c;
    icmMemoryP           CodeFlash_m;
    icmMemoryP           DataFlash_m;
    icmMemoryP           iRam_m;
    icmPseP              LOGIC_p;
    icmPseP              INTC_p;
    icmPseP              CRC_p;
    icmPseP              CLKGEN_p;
    icmPseP              BCU_p;
    icmPseP              MEMC_p;
    icmPseP              DMA_p;
    icmPseP              UARTC0_p;
    icmPseP              UARTC1_p;
    icmPseP              UARTC2_p;
    icmPseP              CSIB0_p;
    icmPseP              CSIB1_p;
    icmPseP              CSIE0_p;
    icmPseP              CSIE1_p;
    icmPseP              CAN0_p;
    icmPseP              CAN1_p;
    icmPseP              ADC0_p;
    icmPseP              ADC1_p;
    icmPseP              TAA0_p;
    icmPseP              TAA1_p;
    icmPseP              TAA2_p;
    icmPseP              TAA3_p;
    icmPseP              TAA4_p;
    icmPseP              TAA5_p;
    icmPseP              TAA6_p;
    icmPseP              TAA7_p;
    icmPseP              TAA8_p;
    icmPseP              TAA9_p;
    icmPseP              TMS0_p;
    icmPseP              TMS1_p;
    icmPseP              TMT0_p;
    icmPseP              TMT1_p;
    icmPseP              RNG0_p;
    icmPseP              BRG0_p;
    icmPseP              BRG1_p;
    icmPseP              BRG2_p;
    icmNetP              INTRESET_n;
    icmNetP              INTNMI_n;
    icmNetP              INTINTP_n;
    icmNetP              INTMIRETI_n;
    icmNetP              INTINTACK_n;
    icmNetP              INTNMI0_n;
    icmNetP              INTINT0_n;
    icmNetP              INTINT1_n;
    icmNetP              INTUC0R_n;
    icmNetP              INTINT6_n;
    icmNetP              INTUC1R_n;
    icmNetP              INTINT7_n;
    icmNetP              INTBRG0_n;
    icmNetP              INTBRG1_n;
    icmNetP              INTINT75_n;
    icmNetP              INTCB0T_n;
    icmNetP              INTUC2T_n;
    icmNetP              INTINT99_n;
    icmNetP              INTCB0R_n;
    icmNetP              INTUC2R_n;
    icmNetP              INTINT100_n;
    icmNetP              INTCB0RE_n;
    icmNetP              INTUC2RE_n;
    icmNetP              INTINT101_n;
    icmNetP              INTINT116_n;
    icmNetP              INTTS0OV_n;
    icmNetP              INTTS0CC0_n;
    icmNetP              INTTS0CC1_n;
    icmNetP              INTTS0CC2_n;
    icmNetP              INTTS0CC3_n;
    icmNetP              INTTS0CC4_n;
    icmNetP              INTTS0CC5_n;
    icmNetP              INTTS0CD0_n;
    icmNetP              INTTS0OD_n;
    icmNetP              INTTS0ER_n;
    icmNetP              INTTS0WN_n;
    icmNetP              INTTS1OV_n;
    icmNetP              INTTS1CC0_n;
    icmNetP              INTTS1CC1_n;
    icmNetP              INTTS1CC2_n;
    icmNetP              INTTS1CC3_n;
    icmNetP              INTTS1CC4_n;
    icmNetP              INTTS1CC5_n;
    icmNetP              INTTS1CD0_n;
    icmNetP              INTTS1OD_n;
    icmNetP              INTTS1ER_n;
    icmNetP              INTTS1WN_n;
    icmNetP              INTTT0OV_n;
    icmNetP              INTTT0CC0_n;
    icmNetP              INTTT0CC1_n;
    icmNetP              INTTT0EC_n;
    icmNetP              INTTT1OV_n;
    icmNetP              INTTT1CC0_n;
    icmNetP              INTTT1CC1_n;
    icmNetP              INTTT1EC_n;
    icmNetP              INTTAA0OV_n;
    icmNetP              INTTAA0CC0_n;
    icmNetP              INTTAA0CC1_n;
    icmNetP              INTTAA1OV_n;
    icmNetP              INTTAA1CC0_n;
    icmNetP              INTTAA1CC1_n;
    icmNetP              INTTAA2OV_n;
    icmNetP              INTTAA2CC0_n;
    icmNetP              INTTAA2CC1_n;
    icmNetP              INTTAA3OV_n;
    icmNetP              INTTAA3CC0_n;
    icmNetP              INTTAA3CC1_n;
    icmNetP              INTTAA4OV_n;
    icmNetP              INTTAA4CC0_n;
    icmNetP              INTTAA4CC1_n;
    icmNetP              INTTAA5OV_n;
    icmNetP              INTTAA5CC0_n;
    icmNetP              INTTAA5CC1_n;
    icmNetP              INTTAA6OV_n;
    icmNetP              INTTAA6CC0_n;
    icmNetP              INTTAA6CC1_n;
    icmNetP              INTTAA7OV_n;
    icmNetP              INTTAA7CC0_n;
    icmNetP              INTTAA7CC1_n;
    icmNetP              INTTAA8OV_n;
    icmNetP              INTTAA8CC0_n;
    icmNetP              INTTAA8CC1_n;
    icmNetP              INTTAA9OV_n;
    icmNetP              INTTAA9CC0_n;
    icmNetP              INTTAA9CC1_n;
    icmNetP              INTBRG2_n;
    icmNetP              INTC0ERR_n;
    icmNetP              INTC0WUPIC_n;
    icmNetP              INTC0REC_n;
    icmNetP              INTC0TRX_n;
    icmNetP              INTC1ERR_n;
    icmNetP              INTC1WUPIC_n;
    icmNetP              INTC1REC_n;
    icmNetP              INTC1TRX_n;
    icmNetP              INTCB1T_n;
    icmNetP              INTCB1R_n;
    icmNetP              INTCB1RE_n;
    icmNetP              INTUC0RE_n;
    icmNetP              INTUC0T_n;
    icmNetP              INTUC1RE_n;
    icmNetP              INTUC1T_n;
    icmNetP              INTAD0_n;
    icmNetP              INTAD1_n;
    icmNetP              DMA0EN_n;
    icmNetP              DMA1EN_n;
    icmNetP              ADDMARQ0_n;
    icmNetP              ADDMARQ1_n;
    icmNetP              TS0ADTRG0_n;
    icmNetP              TS0ADTRG1_n;
    icmNetP              TS1ADTRG0_n;
    icmNetP              TS1ADTRG1_n;
    icmPacketnetP        vcan0_pktn;
    icmPacketnetP        vcan1_pktn;
} handles;
