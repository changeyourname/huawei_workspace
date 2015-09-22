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
#include "mips.ovpworld.org/processor/mips32/1.0/tlm2.0/processor.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                   BareMetalMips32Multicore2_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalMips32Multicore2_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalMips32Multicore2_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,3> bus1;
    decoder             <2,3> bus2;
    decoder             <2,1> bus_sh;
    ram                   m_ram_10;
    ram                   m_ram_11;
    ram                   m_ram_20;
    ram                   m_ram_21;
    ram                   m_ram_sh;
    mips32                cpu_1;
    mips32                cpu_2;

}; /* BareMetalMips32Multicore2_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                BareMetalMips32Multicore2_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalMips32Multicore2_TLM2_0::BareMetalMips32Multicore2_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , bus1("bus1")
    , bus2("bus2")
    , bus_sh("bus_sh")
    , m_ram_10 ("m_ram_10", "sp1", 0xffff)
    , m_ram_11 ("m_ram_11", "sp1", 0xfffff)
    , m_ram_20 ("m_ram_20", "sp1", 0xffff)
    , m_ram_21 ("m_ram_21", "sp1", 0xfffff)
    , m_ram_sh ("m_ram_sh", "sp1", 0xfff)
    , cpu_1 ( "cpu_1", 0, ICM_ATTR_DEFAULT )
    , cpu_2 ( "cpu_2", 1, ICM_ATTR_DEFAULT )
{

    // bus1 masters
    cpu_1.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu_1.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](m_ram_10.sp1); // Memory
    bus1.setDecode(0, 0x7fff0000, 0x7fffffff);

    bus1.initiator_socket[1](m_ram_11.sp1); // Memory
    bus1.setDecode(1, 0x80080000, 0x8017ffff);

    bus1.initiator_socket[2](bus_sh.target_socket[0]); // Bridge
    bus1.setDecode(2, 0x11000000, 0x11000fff);


    // bus2 masters
    cpu_2.INSTRUCTION.socket(bus2.target_socket[0]);
    cpu_2.DATA.socket(bus2.target_socket[1]);

    // bus2 slaves
    bus2.initiator_socket[0](m_ram_20.sp1); // Memory
    bus2.setDecode(0, 0x7fff0000, 0x7fffffff);

    bus2.initiator_socket[1](m_ram_21.sp1); // Memory
    bus2.setDecode(1, 0x80080000, 0x8017ffff);

    bus2.initiator_socket[2](bus_sh.target_socket[1]); // Bridge
    bus2.setDecode(2, 0x11000000, 0x11000fff);


    // bus_sh masters

    // bus_sh slaves
    bus_sh.initiator_socket[0](m_ram_sh.sp1); // Memory
    bus_sh.setDecode(0, 0x0, 0xfff);

}
