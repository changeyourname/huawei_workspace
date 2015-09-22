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
#include "mips.ovpworld.org/processor/mips32/1.0/tlm2.0/mips32_M14K.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                      BareMetalM14KSingle_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalM14KSingle_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalM14KSingle_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,6> bus1;
    ram                   program1;
    ram                   stack1;
    ram                   stack2;
    ram                   stack3;
    ram                   high_mem1;
    ram                   high_mem2;
    mips32_M14K           cpu1;


    icmAttrListObject *attrsForcpu1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", "M14K");
        userAttrs->addAttr("endian", "big");
        return userAttrs;
    }
}; /* BareMetalM14KSingle_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                   BareMetalM14KSingle_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalM14KSingle_TLM2_0::BareMetalM14KSingle_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , bus1("bus1")
    , program1 ("program1", "sp1", 0xfffff)
    , stack1 ("stack1", "sp1", 0xfffff)
    , stack2 ("stack2", "sp1", 0xfffff)
    , stack3 ("stack3", "sp1", 0xffff)
    , high_mem1 ("high_mem1", "sp1", 0xfffff)
    , high_mem2 ("high_mem2", "sp1", 0x17ffff)
    , cpu1 ( "cpu1", 0, ICM_ATTR_DEFAULT, attrsForcpu1() )
{

    // bus1 masters
    cpu1.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu1.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](program1.sp1); // Memory
    bus1.setDecode(0, 0x0, 0xfffff);

    bus1.initiator_socket[1](stack1.sp1); // Memory
    bus1.setDecode(1, 0x100000, 0x1fffff);

    bus1.initiator_socket[2](stack2.sp1); // Memory
    bus1.setDecode(2, 0x500000, 0x5fffff);

    bus1.initiator_socket[3](stack3.sp1); // Memory
    bus1.setDecode(3, 0x7fff0000, 0x7fffffff);

    bus1.initiator_socket[4](high_mem1.sp1); // Memory
    bus1.setDecode(4, 0x40000000, 0x400fffff);

    bus1.initiator_socket[5](high_mem2.sp1); // Memory
    bus1.setDecode(5, 0x80000000, 0x8017ffff);

}
