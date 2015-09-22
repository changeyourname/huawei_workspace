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
    icmBusP              membus_b;
    icmProcessorP        arm1_c;
    icmMemoryP           ram1_m;
    icmMemoryP           ambaDummy_m;
    icmPseP              cm_p;
    icmPseP              pic1_p;
    icmPseP              pic2_p;
    icmPseP              ethlan_p;
    icmPseP              pit_p;
    icmPseP              icp_p;
    icmPseP              ld1_p;
    icmPseP              kb1_p;
    icmPseP              ms1_p;
    icmPseP              rtc_p;
    icmPseP              uart1_p;
    icmPseP              uart2_p;
    icmPseP              mmci_p;
    icmPseP              lcd_p;
    icmPseP              smartLoader_p;
    icmNetP              irq_n;
    icmNetP              fiq_n;
    icmNetP              ir1_n;
    icmNetP              ir2_n;
    icmNetP              ir3_n;
    icmNetP              ir4_n;
    icmNetP              ir5_n;
    icmNetP              ir6_n;
    icmNetP              ir7_n;
    icmNetP              ir8_n;
    icmNetP              ir23_n;
    icmNetP              ir24_n;
} handles;
