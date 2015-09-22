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

// This file constructs the platform.
// This file should NOT need to be edited.

#include "ovpworld.org/modelSupport/tlmDecoder/1.0/tlm2.0/tlmDecoder.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"
#include "arm.ovpworld.org/processor/arm/1.0/tlm2.0/arm_Cortex-A9MPx2.igen.hpp"
#include "arm.ovpworld.org/peripheral/L2CachePL310/1.0/tlm2.0/pse.igen.hpp"
#include "altera.ovpworld.org/peripheral/dw-apb-timer/1.0/tlm2.0/pse.igen.hpp"
#include "altera.ovpworld.org/peripheral/dw-apb-uart/1.0/tlm2.0/pse.igen.hpp"
#include "altera.ovpworld.org/peripheral/RSTMGR/1.0/tlm2.0/pse.igen.hpp"
#include "ovpworld.org/peripheral/dummyPort/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/SmartLoaderArmLinux/1.0/tlm2.0/pse.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                        AlteraCycloneV_HPS_TLM2 Class
////////////////////////////////////////////////////////////////////////////////

class AlteraCycloneV_HPS_TLM2 : public sc_core::sc_module {

  public:
    AlteraCycloneV_HPS_TLM2 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <3,16> smbus;
    ram                   sram1;
    arm_Cortex_A9MPx2     cpu;
    L2CachePL310          L2;
    dw_apb_timer          timer0;
    dw_apb_timer          timer1;
    dw_apb_timer          timer2;
    dw_apb_timer          timer3;
    dw_apb_uart           uart0;
    dw_apb_uart           uart1;
    RSTMGR                RSTMGR0;
    dummyPort             SYSMGR0;
    dummyPort             CLKMGR0;
    dummyPort             pdma0;
    dummyPort             gmac0;
    dummyPort             emac0_dma;
    dummyPort             gmac1;
    dummyPort             emac1_dma;
    SmartLoaderArmLinux   smartLoader;


    icmAttrListObject *attrsForcpu() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "Cortex-A9MPx2");
        userAttrs->addAttr("compatibility", "ISA");
        userAttrs->addAttr("UAL", (int)1);
        userAttrs->addAttr("showHiddenRegs", (int)0);
        userAttrs->addAttr("override_CBAR", (int)0xfffec000);
        userAttrs->addAttr("override_GICD_TYPER_ITLines", (int)6);
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForuart0() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("outfile", "uart0.log");
        userAttrs->addAttr("console", (int)1);
        userAttrs->addAttr("finishOnDisconnect", (int)1);
        return userAttrs;
    }

    icmAttrListObject *attrsForuart1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("outfile", "uart1.log");
        userAttrs->addAttr("console", (int)1);
        return userAttrs;
    }

    icmAttrListObject *attrsForsmartLoader() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("boardid", (int)0xffffffff);
        userAttrs->addAttr("kernel", "zImage");
        userAttrs->addAttr("initrd", "fs.img");
        userAttrs->addAttr("command", "mem=128M console=ttyS0");
        userAttrs->addAttr("physicalbase", (int)0x0);
        userAttrs->addAttr("memsize", (int)0x08000000);
        userAttrs->addAttr("disable", (int)0);
        return userAttrs;
    }
}; /* AlteraCycloneV_HPS_TLM2 */

////////////////////////////////////////////////////////////////////////////////
//                     AlteraCycloneV_HPS_TLM2 Constructor
////////////////////////////////////////////////////////////////////////////////

AlteraCycloneV_HPS_TLM2::AlteraCycloneV_HPS_TLM2 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , smbus("smbus")
    , sram1 ("sram1", "sp1", 0x7ffffff)
    , cpu ( "cpu", 0, ICM_ATTR_SIMEX, attrsForcpu() )
    , L2 ("L2")
    , timer0 ("timer0")
    , timer1 ("timer1")
    , timer2 ("timer2")
    , timer3 ("timer3")
    , uart0 ("uart0", attrsForuart0())
    , uart1 ("uart1", attrsForuart1())
    , RSTMGR0 ("RSTMGR0")
    , SYSMGR0 ("SYSMGR0")
    , CLKMGR0 ("CLKMGR0")
    , pdma0 ("pdma0")
    , gmac0 ("gmac0")
    , emac0_dma ("emac0_dma")
    , gmac1 ("gmac1")
    , emac1_dma ("emac1_dma")
    , smartLoader ("smartLoader", attrsForsmartLoader())
{

    // smbus masters
    cpu.INSTRUCTION.socket(smbus.target_socket[0]);
    cpu.DATA.socket(smbus.target_socket[1]);
    smartLoader.mport.socket(smbus.target_socket[2]);

    // smbus slaves
    smbus.initiator_socket[0](L2.bport1.socket); // Peripheral
    smbus.setDecode(0, 0xfffef000, 0xfffeffff);

    smbus.initiator_socket[1](timer0.bport1.socket); // Peripheral
    smbus.setDecode(1, 0xffc08000, 0xffc08fff);

    smbus.initiator_socket[2](timer1.bport1.socket); // Peripheral
    smbus.setDecode(2, 0xffc09000, 0xffc09fff);

    smbus.initiator_socket[3](timer2.bport1.socket); // Peripheral
    smbus.setDecode(3, 0xffd00000, 0xffd00fff);

    smbus.initiator_socket[4](timer3.bport1.socket); // Peripheral
    smbus.setDecode(4, 0xffd01000, 0xffd01fff);

    smbus.initiator_socket[5](uart0.bport1.socket); // Peripheral
    smbus.setDecode(5, 0xffc02000, 0xffc02fff);

    smbus.initiator_socket[6](uart1.bport1.socket); // Peripheral
    smbus.setDecode(6, 0xffc03000, 0xffc03fff);

    smbus.initiator_socket[7](RSTMGR0.bport1.socket); // Peripheral
    smbus.setDecode(7, 0xffd05000, 0xffd05fff);

    smbus.initiator_socket[8](SYSMGR0.bport1.socket); // Peripheral
    smbus.setDecode(8, 0xffd08000, 0xffd08fff);

    smbus.initiator_socket[9](CLKMGR0.bport1.socket); // Peripheral
    smbus.setDecode(9, 0xffd04000, 0xffd04fff);

    smbus.initiator_socket[10](pdma0.bport1.socket); // Peripheral
    smbus.setDecode(10, 0xffe01000, 0xffe01fff);

    smbus.initiator_socket[11](gmac0.bport1.socket); // Peripheral
    smbus.setDecode(11, 0xff700000, 0xff700fff);

    smbus.initiator_socket[12](emac0_dma.bport1.socket); // Peripheral
    smbus.setDecode(12, 0xff701000, 0xff701fff);

    smbus.initiator_socket[13](gmac1.bport1.socket); // Peripheral
    smbus.setDecode(13, 0xff702000, 0xff702fff);

    smbus.initiator_socket[14](emac1_dma.bport1.socket); // Peripheral
    smbus.setDecode(14, 0xff703000, 0xff703fff);

    smbus.initiator_socket[15](sram1.sp1); // Memory
    smbus.setDecode(15, 0x0, 0x7ffffff);


    // Net connections
    timer0.irq(cpu.SPI199);
    timer1.irq(cpu.SPI200);
    timer2.irq(cpu.SPI201);
    timer3.irq(cpu.SPI202);
    uart0.intOut(cpu.SPI194);
    uart1.intOut(cpu.SPI195);
    RSTMGR0.cpu0Reset(cpu.reset_CPU0);
    RSTMGR0.cpu1Reset(cpu.reset_CPU1);
}
