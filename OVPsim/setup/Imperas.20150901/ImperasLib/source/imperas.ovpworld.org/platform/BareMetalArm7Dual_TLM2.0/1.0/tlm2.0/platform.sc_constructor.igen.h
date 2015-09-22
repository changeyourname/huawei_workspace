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
#include "arm.ovpworld.org/processor/arm/1.0/tlm2.0/arm_ARM7TDMI.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                       BareMetalArm7Dual_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalArm7Dual_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalArm7Dual_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,2> bus1;
    decoder             <2,2> bus2;
    ram                   ram10;
    ram                   ram11;
    ram                   ram20;
    ram                   ram21;
    arm_ARM7TDMI          cpu1;
    arm_ARM7TDMI          cpu2;


    icmAttrListObject *attrsForcpu1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "ARM7TDMI");
        userAttrs->addAttr("endian", "big");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu2() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "ARM7TDMI");
        userAttrs->addAttr("endian", "big");
        return userAttrs;
    }
}; /* BareMetalArm7Dual_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                    BareMetalArm7Dual_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalArm7Dual_TLM2_0::BareMetalArm7Dual_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , bus1("bus1")
    , bus2("bus2")
    , ram10 ("ram10", "sp10", 0xffffff)
    , ram11 ("ram11", "sp1", 0xffff)
    , ram20 ("ram20", "sp1", 0xffffff)
    , ram21 ("ram21", "sp1", 0xffff)
    , cpu1 ( "cpu1", 0, ICM_ATTR_DEFAULT, attrsForcpu1() )
    , cpu2 ( "cpu2", 1, ICM_ATTR_DEFAULT, attrsForcpu2() )
{

    // bus1 masters
    cpu1.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu1.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](ram10.sp10); // Memory
    bus1.setDecode(0, 0x0, 0xffffff);

    bus1.initiator_socket[1](ram11.sp1); // Memory
    bus1.setDecode(1, 0xffff0000, 0xffffffff);


    // bus2 masters
    cpu2.INSTRUCTION.socket(bus2.target_socket[0]);
    cpu2.DATA.socket(bus2.target_socket[1]);

    // bus2 slaves
    bus2.initiator_socket[0](ram20.sp1); // Memory
    bus2.setDecode(0, 0x0, 0xffffff);

    bus2.initiator_socket[1](ram21.sp1); // Memory
    bus2.setDecode(1, 0xffff0000, 0xffffffff);

}
