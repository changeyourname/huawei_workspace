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
//                          Wed Jun  2 13:21:58 2010
//
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "ovpworld.org/modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.hpp"
#include "ovpworld.org/modelSupport/tlmDecoder/1.0/tlm2.0/tlmDecoder.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"
#include "mips.ovpworld.org/processor/mips32/1.0/tlm2.0/processor.igen.hpp"
#include "mips.ovpworld.org/peripheral/SmartLoaderLinux/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/82371EB/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/PciIDE/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/PciUSB/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/PciPM/1.0/tlm2.0/pse.igen.hpp"
#include "amd.ovpworld.org/peripheral/79C970/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/8259A/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/Ps2Control/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/8253/1.0/tlm2.0/pse.igen.hpp"
#include "motorola.ovpworld.org/peripheral/MC146818/1.0/tlm2.0/pse.igen.hpp"
#include "national.ovpworld.org/peripheral/16550/1.0/tlm2.0/pse.igen.hpp"
#include "mips.ovpworld.org/peripheral/16450C/1.0/tlm2.0/pse.igen.hpp"
#include "intel.ovpworld.org/peripheral/82077AA/1.0/tlm2.0/pse.igen.hpp"
#include "mips.ovpworld.org/peripheral/MaltaFPGA/1.0/tlm2.0/pse.igen.hpp"
#include "marvell.ovpworld.org/peripheral/GT6412x/1.0/tlm2.0/pse.igen.hpp"
#include "ovpworld.org/peripheral/Alpha2x16Display/1.0/tlm2.0/pse.igen.hpp"
#include "ovpworld.org/modelSupport/tlmDummyBus/1.0/tlm2.0/tlmDummyBus.hpp"

////////////////////////////////////////////////////////////////////////////////
//                         MipsMaltaLinux_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class MipsMaltaLinux_TLM2_0 : public sc_core::sc_module {

  public:
    MipsMaltaLinux_TLM2_0 (sc_core::sc_module_name name, bool connect, int port);

    icmTLMPlatform        Platform;
    decoder             <5,24> bus1;
    decoder             <1,7> PCIconfigBus;
    decoder             <1,1> PCIackBus;
    decoder             <1,1> cascadeBus;
    decoder             <3,1> flashBus;
    ram                   Core_Board_SDRAM;
    ram                   Monitor_Flash;
    mips32                mipsle1;
    SmartLoaderLinux      Core_Board_SDRAM_promInit;
    _82371EB              PIIX4;
    PciIDE                PIIX4_IDE;
    PciUSB                PCI_USB;
    PciPM                 PCI_PM;
    _79C970               PCI_NET;
    _8259A                intCtrlMaster;
    _8259A                intCtrlSlave;
    Ps2Control            Ps2;
    _8253                 pit;
    MC146818              rtc;
    _16550                uartTTY0;
    _16550                uartTTY1;
    _16450C               uartCBUS;
    _82077AA              fd0;
    MaltaFPGA             maltaFpga;
    Alpha2x16Display      alphaDisplay;
    GT6412x               sysControl;

    tlmDummyBus           <0,1> _dummy;


    icmAttrListObject *attrsFormipsle1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "24KEf");
        userAttrs->addAttr("vectoredinterrupt", 0);
        userAttrs->addAttr("config1MMUSizeM1", 63);
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForCore_Board_SDRAM_promInit(bool disk) {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("kernel", "vmlinux");
        userAttrs->addAttr("boardid", 0x00000420);
        userAttrs->addAttr("command", "console=ttyS0");
        if (disk) {
            userAttrs->addAttr("root",   "/dev/hda1");
        } else {
            userAttrs->addAttr("initrd",  "initrd.gz");
        }
        return userAttrs;
    }

    icmAttrListObject *attrsForPIIX4() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("PCIslot", 10);
        return userAttrs;
    }

    icmAttrListObject *attrsForPIIX4_IDE() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("PCIslot", 10);
        userAttrs->addAttr("PCIfunction", 1);
        userAttrs->addAttr("Drive0Name", "mipsel_hda");
        userAttrs->addAttr("Drive1Name", "mipsel_hdb");
        userAttrs->addAttr("Drive2Name", "mipsel_cd");
        return userAttrs;
    }

    icmAttrListObject *attrsForPCI_USB() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("PCIslot", 10);
        userAttrs->addAttr("PCIfunction", 2);
        return userAttrs;
    }

    icmAttrListObject *attrsForPCI_PM() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("PCIslot", 10);
        userAttrs->addAttr("PCIfunction", 3);
        return userAttrs;
    }

    icmAttrListObject *attrsForPCI_NET() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("PCIslot", 11);
        userAttrs->addAttr("PCIfunction", 0);
        userAttrs->addAttr("pollDelay", 1000);
        return userAttrs;
    }

    icmAttrListObject *attrsForintCtrlMaster() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("spen", "master");
        return userAttrs;
    }

    icmAttrListObject *attrsForintCtrlSlave() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("spen", "slave");
        return userAttrs;
    }

    icmAttrListObject *attrsForPs2() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("pollPeriod", 50000);
        userAttrs->addAttr("grabDisable", 1);
        return userAttrs;
    }

    icmAttrListObject *attrsForrtc() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        return userAttrs;
    }

    icmAttrListObject *attrsForuartTTY0(bool connect, int port) {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("outfile", "uartTTY0.log");
        if(connect) {
            if(port != -1) {
                userAttrs->addAttr("portnum", port);
            } else {
                userAttrs->addAttr("console", 1);
            }
        }
        userAttrs->addAttr("finishOnDisconnect", 1);
        return userAttrs;
    }

    icmAttrListObject *attrsForuartTTY1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("outfile", "uartTTY1.log");
        return userAttrs;
    }

    icmAttrListObject *attrsForuartCBUS() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        return userAttrs;
    }

    icmAttrListObject *attrsFormaltaFpga() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("stoponsoftreset", 1);
        return userAttrs;
    }
}; /* MipsMaltaLinux_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                      MipsMaltaLinux_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

MipsMaltaLinux_TLM2_0::MipsMaltaLinux_TLM2_0 ( sc_core::sc_module_name name, bool connect, int port)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_VERBOSE | ICM_STOP_ON_CTRLC| ICM_ENABLE_IMPERAS_INTERCEPTS | ICM_WALLCLOCK)
    , bus1("bus1")
    , PCIconfigBus("PCIconfigBus")
    , PCIackBus("PCIackBus")
    , cascadeBus("cascadeBus")
    , flashBus("flashBus")
    , Core_Board_SDRAM ("Core_Board_SDRAM", "sp1", 0x8000000)
    , Monitor_Flash ("Monitor_Flash", "sp1", 0x400000)
    , mipsle1 ( "mipsle1", 0, ICM_ATTR_SIMEX | ICM_ATTR_TRACE_ICOUNT,attrsFormipsle1(), "" )
    , Core_Board_SDRAM_promInit ("Core_Board_SDRAM_promInit", attrsForCore_Board_SDRAM_promInit(0))
    , PIIX4 ("PIIX4", attrsForPIIX4())
    , PIIX4_IDE ("PIIX4_IDE", attrsForPIIX4_IDE())
    , PCI_USB ("PCI_USB", attrsForPCI_USB())
    , PCI_PM ("PCI_PM", attrsForPCI_PM())
    , PCI_NET ("PCI_NET", attrsForPCI_NET())
    , intCtrlMaster ("intCtrlMaster", attrsForintCtrlMaster())
    , intCtrlSlave ("intCtrlSlave", attrsForintCtrlSlave())
    , Ps2 ("Ps2", attrsForPs2())
    , pit ("pit")
    , rtc ("rtc", attrsForrtc())
    , uartTTY0 ("uartTTY0", attrsForuartTTY0(connect, port))
    , uartTTY1 ("uartTTY1", attrsForuartTTY1())
    , uartCBUS ("uartCBUS", attrsForuartCBUS())
    , fd0 ("fd0")
    , maltaFpga ("maltaFpga", attrsFormaltaFpga())
    , alphaDisplay ("alphaDisplay")
    , sysControl ("sysControl")
    , _dummy("_dummy")

{

    // bus1 masters
    mipsle1.INSTRUCTION.socket(bus1.target_socket[0]);
    mipsle1.DATA.socket(bus1.target_socket[1]);
    Core_Board_SDRAM_promInit.mport.socket(bus1.target_socket[2]);
    PIIX4_IDE.dmaPort.socket(bus1.target_socket[3]);
    PCI_NET.dmaPort.socket(bus1.target_socket[4]);

    // bus1 slaves
    bus1.initiator_socket[0](Core_Board_SDRAM_promInit.idport.socket); // Peripheral
    bus1.setDecode(0, 0x1fc00010, 0x1fc00013);

    bus1.initiator_socket[1](PIIX4_IDE.busPort.socket); // Peripheral
    // (remappable)

    bus1.initiator_socket[2](PCI_USB.busPort.socket); // Peripheral
    // (remappable)

    bus1.initiator_socket[3](PCI_PM.busPort.socket); // Peripheral
    // (remappable)

    bus1.initiator_socket[4](PCI_NET.busPort.socket); // Peripheral
    // (remappable)

    bus1.initiator_socket[5](intCtrlMaster.io.socket); // Peripheral
    bus1.setDecode(5, 0x18000020, 0x18000021);

    bus1.initiator_socket[6](intCtrlMaster.elcr.socket); // Peripheral
    bus1.setDecode(6, 0x180004d0, 0x180004d0);

    bus1.initiator_socket[7](intCtrlSlave.io.socket); // Peripheral
    bus1.setDecode(7, 0x180000a0, 0x180000a1);

    bus1.initiator_socket[8](intCtrlSlave.elcr.socket); // Peripheral
    bus1.setDecode(8, 0x180004d1, 0x180004d1);

    bus1.initiator_socket[9](Ps2.config.socket); // Peripheral
    bus1.setDecode(9, 0x18000060, 0x18000067);

    bus1.initiator_socket[10](pit.bport1.socket); // Peripheral
    bus1.setDecode(10, 0x18000040, 0x18000043);

    bus1.initiator_socket[11](rtc.busPort.socket); // Peripheral
    bus1.setDecode(11, 0x18000070, 0x18000071);

    bus1.initiator_socket[12](uartTTY0.bport1.socket); // Peripheral
    bus1.setDecode(12, 0x180003f8, 0x180003ff);

    bus1.initiator_socket[13](uartTTY1.bport1.socket); // Peripheral
    bus1.setDecode(13, 0x180002f8, 0x180002ff);

    bus1.initiator_socket[14](uartCBUS.bport1.socket); // Peripheral
    bus1.setDecode(14, 0x1f000900, 0x1f00093f);

    bus1.initiator_socket[15](fd0.bport1.socket); // Peripheral
    bus1.setDecode(15, 0x180003f0, 0x180003f7);

    bus1.initiator_socket[16](maltaFpga.busPort1.socket); // Peripheral
    bus1.setDecode(16, 0x1f000000, 0x1f0008ff);

    bus1.initiator_socket[17](maltaFpga.busPort2.socket); // Peripheral
    bus1.setDecode(17, 0x1f000a00, 0x1f000fff);

    bus1.initiator_socket[18](alphaDisplay.busPort.socket); // Peripheral
    bus1.setDecode(18, 0x18000100, 0x18000103);

    bus1.initiator_socket[19](sysControl.busPort.socket); // Peripheral
    // (remappable)

    bus1.initiator_socket[20](Core_Board_SDRAM.sp1); // Memory
    bus1.setDecode(20, 0x0, 0x7ffffff);

    bus1.initiator_socket[21](flashBus.target_socket[0]); // Bridge
    bus1.setDecode(21, 0x1e000000, 0x1e3fffff);

    bus1.initiator_socket[22](flashBus.target_socket[1]); // Bridge
    bus1.setDecode(22, 0x1fc00000, 0x1fc0000f);

    bus1.initiator_socket[23](flashBus.target_socket[2]); // Bridge
    bus1.setDecode(23, 0x1fc00014, 0x1fffffff);


    // PCIconfigBus masters
    sysControl.PCIconfigM.socket(PCIconfigBus.target_socket[0]);

    // PCIconfigBus slaves
    PCIconfigBus.initiator_socket[0](PIIX4.PCIconfig.socket); // Peripheral
    // (remappable)

    PCIconfigBus.initiator_socket[1](PIIX4_IDE.PCIconfig.socket); // Peripheral
    // (remappable)

    PCIconfigBus.initiator_socket[2](PCI_USB.PCIconfig.socket); // Peripheral
    // (remappable)

    PCIconfigBus.initiator_socket[3](PCI_PM.PCIconfig.socket); // Peripheral
    // (remappable)

    PCIconfigBus.initiator_socket[4](PCI_NET.PCIconfig.socket); // Peripheral
    // (remappable)

    PCIconfigBus.initiator_socket[5](sysControl.PCIconfig.socket); // Peripheral
    // (remappable)

    PCIconfigBus.initiator_socket[6](sysControl.PCIconfigS.socket); // Peripheral
    // PCIconfigBus.setDecode(6, 0x0, 0xffff);


    // PCIackBus masters
    sysControl.PCIackM.socket(PCIackBus.target_socket[0]);

    // PCIackBus slaves
    PCIackBus.initiator_socket[0](intCtrlMaster.PCIackS.socket); // Peripheral
    PCIackBus.setDecode(0, 0x0, 0x0);


    // cascadeBus masters
    intCtrlMaster.cascade.socket(cascadeBus.target_socket[0]);

    // cascadeBus slaves
    cascadeBus.initiator_socket[0](intCtrlSlave.PCIackS.socket); // Peripheral
    cascadeBus.setDecode(0, 0x2, 0x2);


    // flashBus masters

    // flashBus slaves
    flashBus.initiator_socket[0](Monitor_Flash.sp1); // Memory
    flashBus.setDecode(0, 0x00000000, 0x003fffff);

    intCtrlSlave.cascade.socket(_dummy.target_socket[0]);


    // Net connections
    intCtrlMaster.intp(mipsle1.hwint0);
    PIIX4_IDE.intOut0(intCtrlSlave.ir6);
    PIIX4_IDE.intOut1(intCtrlSlave.ir7);
    PCI_NET.intOut0(intCtrlSlave.ir2);
    Ps2.kbdInterrupt(intCtrlMaster.ir1);
    uartTTY1.intOut(intCtrlMaster.ir3);
    uartTTY0.intOut(intCtrlMaster.ir4);
    intCtrlSlave.intp(intCtrlMaster.ir2);
    rtc.timerInt(intCtrlSlave.ir0);
    Ps2.mouseInterrupt(intCtrlSlave.ir4);
}

int sc_main (int argc, char *argv[] )
{
    sc_set_time_resolution(1,SC_NS);
    icmIgnoreMessage("ICM_NPF");

    bool  timeoutSet = false;
    bool  connect = true;
    int port = -1;
    sc_time stop(0,SC_MS);


    int i;
    for(i=1; i < argc; i++) {
        if (strcmp(argv[i], "t") == 0) {
            stop = sc_time(atoi(argv[++i]), SC_MS);
            timeoutSet = true;
        } else if (strcmp(argv[i], "p") == 0) {
            if (strcmp(argv[++i], "auto") != 0) {
                // set if arg not auto
                port = atoi(argv[i]);
            }
        } else if (strcmp(argv[i], "n") == 0) {
            connect = false;
        } else {
            cout << "Usage: " << argv[0] << " [t <time>] [d <port number>]" << endl;
            cout << "       t = timeout for simulation in milliseconds" << endl;
            cout << "       n = no interactive connection to uart (logging only)" << endl;
            cout << "       p = port number to connect uart (default auto open console)" << endl;
            exit(0);
        }
    }

    cout << "Constructing." << endl;
    MipsMaltaLinux_TLM2_0 top("top", connect, port);           // instantiate example top module

    if (!top.mipsle1.loadLocalMemory("vmlinux", (icmLoaderAttrs)(ICM_LOAD_DEFAULT))) {
        return 1;
    }

    top.uartTTY0.setDiagnosticLevel(1);
    top.uartTTY1.setDiagnosticLevel(1);
    top.uartCBUS.setDiagnosticLevel(1);
    top.Core_Board_SDRAM_promInit.setDiagnosticLevel(1);

    cout << "Starting sc_main." << endl;
    if (timeoutSet) {
        sc_core::sc_start(stop);                  // start the simulation
    } else {
        sc_core::sc_start();                      // start the simulation
    }
    cout << "Finished sc_main." << endl;
    return 0;                              // return okay status
}

