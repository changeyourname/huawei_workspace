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
#include "arc.ovpworld.org/processor/arc/1.0/tlm2.0/arc_700.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                       BareMetalArcSingle_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalArcSingle_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalArcSingle_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,2> bus1;
    ram                   ram1;
    ram                   ram2;
    arc_700               cpu1;


    icmAttrListObject *attrsForcpu1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("variant", (int)700);
        userAttrs->addAttr("endian", "big");
        return userAttrs;
    }
}; /* BareMetalArcSingle_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                    BareMetalArcSingle_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalArcSingle_TLM2_0::BareMetalArcSingle_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , bus1("bus1")
    , ram1 ("ram1", "sp1", 0x1fffff)
    , ram2 ("ram2", "sp1", 0xffffff)
    , cpu1 ( "cpu1", 0, ICM_ATTR_DEFAULT, attrsForcpu1() )
{

    // bus1 masters
    cpu1.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu1.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](ram1.sp1); // Memory
    bus1.setDecode(0, 0x0, 0x1fffff);

    bus1.initiator_socket[1](ram2.sp1); // Memory
    bus1.setDecode(1, 0x3d000000, 0x3dffffff);

}
