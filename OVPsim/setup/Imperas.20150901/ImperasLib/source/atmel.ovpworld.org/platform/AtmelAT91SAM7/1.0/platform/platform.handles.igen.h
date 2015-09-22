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
    icmBusP              mainbus_b;
    icmProcessorP        ARM7TDMICore_c;
    icmMemoryP           extDev_m;
    icmMemoryP           ram0_m;
    icmPseP              AIC_p;
    icmPseP              WD_p;
    icmPseP              PS_p;
    icmPseP              PIO_p;
    icmPseP              TC_p;
    icmPseP              USART0_p;
    icmPseP              USART1_p;
    icmPseP              SF_p;
    icmNetP              NFIQ_n;
    icmNetP              NIRQ_n;
    icmNetP              US0IRQ_n;
    icmNetP              US1IRQ_n;
    icmNetP              TC0IRQ_n;
    icmNetP              TC1IRQ_n;
    icmNetP              TC2IRQ_n;
    icmNetP              WDIRQ_n;
    icmNetP              PIOIRQ_n;
} handles;
