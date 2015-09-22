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
    icmBusP              busPCI_b;
    icmBusP              busPCIReMap_b;
    icmBusP              PCIconfigBus_b;
    icmBusP              PCIackBus_b;
    icmBusP              cascadeBus_b;
    icmBusP              flashBus_b;
    icmProcessorP        mipsle1_c;
    icmMemoryP           Core_Board_SDRAM_m;
    icmMemoryP           Core_Board_SDRAM2_m;
    icmMemoryP           Monitor_Flash_m;
    icmMemoryP           vgaMemRegion_m;
    icmPseP              pciBrD_p;
    icmPseP              Core_Board_SDRAM_promInit_p;
    icmPseP              sysControl_p;
    icmPseP              PIIX4_p;
    icmPseP              PIIX4_IDE_p;
    icmPseP              PCI_PM_p;
    icmPseP              PCI_NET_p;
    icmPseP              intCtrlMaster_p;
    icmPseP              intCtrlSlave_p;
    icmPseP              _SUPERIO_REG__p;
    icmPseP              vga_p;
    icmPseP              Ps2Control_p;
    icmPseP              pit_p;
    icmPseP              rtc_p;
    icmPseP              uartTTY0_p;
    icmPseP              uartTTY1_p;
    icmPseP              fd0_p;
    icmPseP              uartCBUS_p;
    icmPseP              maltaFpga_p;
    icmPseP              alphaDisplay_p;
    icmNetP              i8259Int_n;
    icmNetP              intCtl_ir14_n;
    icmNetP              intCtl_ir15_n;
    icmNetP              intCtl_ir10_n;
    icmNetP              intCtl_ir1_n;
    icmNetP              intCtl_ir3_n;
    icmNetP              intCtl_ir4_n;
    icmNetP              i8259Cascade_n;
    icmNetP              intCtl_ir8_n;
    icmNetP              intCtl_ir12_n;
} handles;
