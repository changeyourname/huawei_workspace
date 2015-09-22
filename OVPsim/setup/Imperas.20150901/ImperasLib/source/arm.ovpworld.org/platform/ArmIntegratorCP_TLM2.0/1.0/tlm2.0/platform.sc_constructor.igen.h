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
#include "arm.ovpworld.org/processor/arm/1.0/tlm2.0/arm_ARM926EJ-S.igen.hpp"
#include "arm.ovpworld.org/peripheral/CoreModule9x6/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/IntICP/1.01/tlm2.0/pse.igen.hpp"
#include "smsc.ovpworld.org/peripheral/LAN9118/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/IcpCounterTimer/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/IcpControl/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/DebugLedAndDipSwitch/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/KbPL050/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/RtcPL031/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/UartPL011/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/MmciPL181/1.0/tlm2.0/pse.igen.hpp"
#include "arm.ovpworld.org/peripheral/SmartLoaderArmLinux/1.0/tlm2.0/pse.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                        ArmIntegratorCP_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class ArmIntegratorCP_TLM2_0 : public sc_core::sc_module {

  public:
    ArmIntegratorCP_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <4,17> bus1;
    ram                   ram1;
    ram                   ambaDummy;
    ram                   lcdDummy;
    arm_ARM926EJ_S        arm1;
    CoreModule9x6         cm;
    IntICP                pic1;
    IntICP                pic2;
    LAN9118               ethlan;
    IcpCounterTimer       pit;
    IcpControl            icp;
    DebugLedAndDipSwitch  ld1;
    KbPL050               kb1;
    KbPL050               ms1;
    RtcPL031              rtc;
    UartPL011             uart1;
    UartPL011             uart2;
    MmciPL181             mmci;
    SmartLoaderArmLinux   smartLoader;


    icmAttrListObject *attrsForarm1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "ARM926EJ-S");
        userAttrs->addAttr("compatibility", "ISA");
        userAttrs->addAttr("showHiddenRegs", (int)0);
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForkb1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("isMouse", (int)0);
        userAttrs->addAttr("grabDisable", (int)0);
        return userAttrs;
    }

    icmAttrListObject *attrsForms1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("isMouse", (int)1);
        userAttrs->addAttr("grabDisable", (int)1);
        return userAttrs;
    }

    icmAttrListObject *attrsForuart1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "ARM");
        return userAttrs;
    }

    icmAttrListObject *attrsForuart2() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "ARM");
        return userAttrs;
    }

    icmAttrListObject *attrsForsmartLoader() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        return userAttrs;
    }
}; /* ArmIntegratorCP_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                     ArmIntegratorCP_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

ArmIntegratorCP_TLM2_0::ArmIntegratorCP_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , bus1("bus1")
    , ram1 ("ram1", "sp1", 0x7ffffff)
    , ambaDummy ("ambaDummy", "sp1", 0xfff)
    , lcdDummy ("lcdDummy", "sp1", 0xffffff)
    , arm1 ( "arm1", 0, ICM_ATTR_SIMEX, attrsForarm1() )
    , cm ("cm")
    , pic1 ("pic1")
    , pic2 ("pic2")
    , ethlan ("ethlan")
    , pit ("pit")
    , icp ("icp")
    , ld1 ("ld1")
    , kb1 ("kb1", attrsForkb1())
    , ms1 ("ms1", attrsForms1())
    , rtc ("rtc")
    , uart1 ("uart1", attrsForuart1())
    , uart2 ("uart2", attrsForuart2())
    , mmci ("mmci")
    , smartLoader ("smartLoader", attrsForsmartLoader())
{

    // bus1 masters
    arm1.INSTRUCTION.socket(bus1.target_socket[0]);
    arm1.DATA.socket(bus1.target_socket[1]);
    smartLoader.mport.socket(bus1.target_socket[2]);

    // bus1 slaves
    bus1.initiator_socket[0](cm.bport1.socket); // Peripheral
    bus1.setDecode(0, 0x10000000, 0x10000fff);

    bus1.initiator_socket[1](pic1.bport1.socket); // Peripheral
    bus1.setDecode(1, 0x14000000, 0x14000fff);

    bus1.initiator_socket[2](pic2.bport1.socket); // Peripheral
    bus1.setDecode(2, 0xca000000, 0xca000fff);

    bus1.initiator_socket[3](ethlan.bport1.socket); // Peripheral
    bus1.setDecode(3, 0xc8000000, 0xc8000fff);

    bus1.initiator_socket[4](pit.bport1.socket); // Peripheral
    bus1.setDecode(4, 0x13000000, 0x13000fff);

    bus1.initiator_socket[5](icp.bport1.socket); // Peripheral
    bus1.setDecode(5, 0xcb000000, 0xcb00000f);

    bus1.initiator_socket[6](ld1.bport1.socket); // Peripheral
    bus1.setDecode(6, 0x1a000000, 0x1a000fff);

    bus1.initiator_socket[7](kb1.bport1.socket); // Peripheral
    bus1.setDecode(7, 0x18000000, 0x18000fff);

    bus1.initiator_socket[8](ms1.bport1.socket); // Peripheral
    bus1.setDecode(8, 0x19000000, 0x19000fff);

    bus1.initiator_socket[9](rtc.bport1.socket); // Peripheral
    bus1.setDecode(9, 0x15000000, 0x15000fff);

    bus1.initiator_socket[10](uart1.bport1.socket); // Peripheral
    bus1.setDecode(10, 0x16000000, 0x16000fff);

    bus1.initiator_socket[11](uart2.bport1.socket); // Peripheral
    bus1.setDecode(11, 0x17000000, 0x17000fff);

    bus1.initiator_socket[12](mmci.bport1.socket); // Peripheral
    bus1.setDecode(12, 0x1c000000, 0x1c000fff);

    bus1.initiator_socket[13](ram1.sp1); // Memory
    bus1.setDecode(13, 0x0, 0x7ffffff);

    bus1.initiator_socket[14](ambaDummy.sp1); // Memory
    bus1.setDecode(14, 0x1d000000, 0x1d000fff);

    bus1.initiator_socket[15](lcdDummy.sp1); // Memory
    bus1.setDecode(15, 0xc0000000, 0xc0ffffff);

    bus1.initiator_socket[16](bus1.target_socket[3]); // Bridge
    bus1.setDecode(16, 0x80000000, 0x87ffffff);


    // Net connections
    pic1.irq(arm1.irq);
    pic1.fiq(arm1.fiq);
    uart1.irq(pic1.ir1);
    uart2.irq(pic1.ir2);
    kb1.irq(pic1.ir3);
    ms1.irq(pic1.ir4);
    pit.irq0(pic1.ir5);
    pit.irq1(pic1.ir6);
    pit.irq2(pic1.ir7);
    rtc.irq(pic1.ir8);
    mmci.irq0(pic1.ir23);
    mmci.irq1(pic1.ir24);
}
