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
//                          Thu Oct 30 11:11:11 2014
//
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "ovpworld.org/modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.hpp"
#include "ovpworld.org/modelSupport/tlmDecoder/1.0/tlm2.0/tlmDecoder.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"
#include "arm.ovpworld.org/processor/arm/1.0/tlm2.0/arm_Cortex-A57MPx1.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                       BareMetalArmAArch64Single_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalArmAArch64Single_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalArmAArch64Single_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,2> bus1;
    ram                   ram1;
    ram                   ram2;
    arm_Cortex_A57MPx1    cpu0;

    const char *semihostForcpu0() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "semihosting", "armAngel", "1.0", "model");
    }

    icmAttrListObject *attrsForcpu0() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("endian", "little");
        userAttrs->addAttr("variant", "Cortex-A57MPx1");
        return userAttrs;
    }
}; /* BareMetalArmAArch64Single_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                    BareMetalArmAArch64Single_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalArmAArch64Single_TLM2_0::BareMetalArmAArch64Single_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_VERBOSE | ICM_STOP_ON_CTRLC| ICM_ENABLE_IMPERAS_INTERCEPTS )
    , bus1("bus1")
    , ram1 ("ram1", "sp1", 0x000fffff)
    , ram2 ("ram2", "sp1", 0x000fffff)
    , cpu0 ( "cpu0", 0, ICM_ATTR_DEFAULT, attrsForcpu0(), semihostForcpu0())
{
    // bus1 masters
    cpu0.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu0.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](ram1.sp1); // Memory
    bus1.setDecode(0, 0x80000000, 0x800fffff);

    bus1.initiator_socket[1](ram2.sp1); // Memory
    bus1.setDecode(1, 0xefff0000, 0xefffffff);

}


////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {

    const char *app = "noAppSupplied";

    sc_time stop(0,SC_MS);

    if (argc > 1 && argc <= 3) {
        app = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <application> [stop time]" << endl;
        cout << "     :   stop time is in milliseconds" << endl;
        return 0;
    }

    // Ignore some of the Warning messages
    icmIgnoreMessage ("ICM_NPF");
    // Ignore specific message that compatibility mode causes
    icmIgnoreMessage("ARM_MORPH_BII");

    BareMetalArmAArch64Single_TLM2_0 top("top");             // instantiate example top module

    // Use the processor to load memory with the program.
    top.cpu0.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE  | ICM_SET_START));

    if (argc > 3) {
        stop = sc_time(atoi(argv[3]), SC_MS);

        sc_core::sc_start(stop);                  // start the simulation
    } else {
        sc_core::sc_start();                      // start the simulation
    }

    cout << "Finished sc_main." << endl;
    return 0;                             // return okay status
}

