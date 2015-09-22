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
#include "arm.ovpworld.org/processor/arm/1.0/tlm2.0/arm_Cortex-A57MPx1.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                   BareMetalArmAArch64Single_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalArmAArch64Single_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalArmAArch64Single_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,3> bus1;
    ram                   local1;
    ram                   local2;
    ram                   local3;
    arm_Cortex_A57MPx1    cpu0;


    icmAttrListObject *attrsForcpu0() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "Cortex-A57MPx1");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }
}; /* BareMetalArmAArch64Single_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                BareMetalArmAArch64Single_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalArmAArch64Single_TLM2_0::BareMetalArmAArch64Single_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , bus1("bus1")
    , local1 ("local1", "sp1", 0xffff)
    , local2 ("local2", "sp1", 0x4fff)
    , local3 ("local3", "sp1", 0xffff)
    , cpu0 ( "cpu0", 0, ICM_ATTR_DEFAULT, attrsForcpu0(),  icmGetVlnvString (NULL, "arm.ovpworld.org", "semihosting", "armAngel", "1.0", "model") )
{

    // bus1 masters
    cpu0.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu0.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](local1.sp1); // Memory
    bus1.setDecode(0, 0x80000000, 0x8000ffff);

    bus1.initiator_socket[1](local2.sp1); // Memory
    bus1.setDecode(1, 0x80027000, 0x8002bfff);

    bus1.initiator_socket[2](local3.sp1); // Memory
    bus1.setDecode(2, 0xefff0000, 0xefffffff);

}
