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
#include "arc.ovpworld.org/processor/arc/1.0/tlm2.0/processor.igen.hpp"


////////////////////////////////////////////////////////////////////////////////
//                     BareMetalArcManycore24_TLM2_0 Class
////////////////////////////////////////////////////////////////////////////////

class BareMetalArcManycore24_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalArcManycore24_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,2> Bus0;
    decoder             <2,2> Bus1;
    decoder             <2,2> Bus2;
    decoder             <2,2> Bus3;
    decoder             <2,2> Bus4;
    decoder             <2,2> Bus5;
    decoder             <2,2> Bus6;
    decoder             <2,2> Bus7;
    decoder             <2,2> Bus8;
    decoder             <2,2> Bus9;
    decoder             <2,2> Bus10;
    decoder             <2,2> Bus11;
    decoder             <2,2> Bus12;
    decoder             <2,2> Bus13;
    decoder             <2,2> Bus14;
    decoder             <2,2> Bus15;
    decoder             <2,2> Bus16;
    decoder             <2,2> Bus17;
    decoder             <2,2> Bus18;
    decoder             <2,2> Bus19;
    decoder             <2,2> Bus20;
    decoder             <2,2> Bus21;
    decoder             <2,2> Bus22;
    decoder             <2,2> Bus23;
    ram                   Program0;
    ram                   Stack0;
    ram                   Program1;
    ram                   Stack1;
    ram                   Program2;
    ram                   Stack2;
    ram                   Program3;
    ram                   Stack3;
    ram                   Program4;
    ram                   Stack4;
    ram                   Program5;
    ram                   Stack5;
    ram                   Program6;
    ram                   Stack6;
    ram                   Program7;
    ram                   Stack7;
    ram                   Program8;
    ram                   Stack8;
    ram                   Program9;
    ram                   Stack9;
    ram                   Program10;
    ram                   Stack10;
    ram                   Program11;
    ram                   Stack11;
    ram                   Program12;
    ram                   Stack12;
    ram                   Program13;
    ram                   Stack13;
    ram                   Program14;
    ram                   Stack14;
    ram                   Program15;
    ram                   Stack15;
    ram                   Program16;
    ram                   Stack16;
    ram                   Program17;
    ram                   Stack17;
    ram                   Program18;
    ram                   Stack18;
    ram                   Program19;
    ram                   Stack19;
    ram                   Program20;
    ram                   Stack20;
    ram                   Program21;
    ram                   Stack21;
    ram                   Program22;
    ram                   Stack22;
    ram                   Program23;
    ram                   Stack23;
    arc                   cpu0;
    arc                   cpu1;
    arc                   cpu2;
    arc                   cpu3;
    arc                   cpu4;
    arc                   cpu5;
    arc                   cpu6;
    arc                   cpu7;
    arc                   cpu8;
    arc                   cpu9;
    arc                   cpu10;
    arc                   cpu11;
    arc                   cpu12;
    arc                   cpu13;
    arc                   cpu14;
    arc                   cpu15;
    arc                   cpu16;
    arc                   cpu17;
    arc                   cpu18;
    arc                   cpu19;
    arc                   cpu20;
    arc                   cpu21;
    arc                   cpu22;
    arc                   cpu23;


    icmAttrListObject *attrsForcpu0() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu2() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu3() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu4() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu5() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu6() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu7() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu8() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu9() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu10() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu11() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu12() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu13() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu14() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu15() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu16() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu17() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu18() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu19() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu20() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu21() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu22() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }

    icmAttrListObject *attrsForcpu23() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("format", "gdb");
        userAttrs->addAttr("endian", "little");
        return userAttrs;
    }
}; /* BareMetalArcManycore24_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                  BareMetalArcManycore24_TLM2_0 Constructor
////////////////////////////////////////////////////////////////////////////////

BareMetalArcManycore24_TLM2_0::BareMetalArcManycore24_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_INIT_DEFAULT)
    , Bus0("Bus0")
    , Bus1("Bus1")
    , Bus2("Bus2")
    , Bus3("Bus3")
    , Bus4("Bus4")
    , Bus5("Bus5")
    , Bus6("Bus6")
    , Bus7("Bus7")
    , Bus8("Bus8")
    , Bus9("Bus9")
    , Bus10("Bus10")
    , Bus11("Bus11")
    , Bus12("Bus12")
    , Bus13("Bus13")
    , Bus14("Bus14")
    , Bus15("Bus15")
    , Bus16("Bus16")
    , Bus17("Bus17")
    , Bus18("Bus18")
    , Bus19("Bus19")
    , Bus20("Bus20")
    , Bus21("Bus21")
    , Bus22("Bus22")
    , Bus23("Bus23")
    , Program0 ("Program0", "sp1", 0x1fffff)
    , Stack0 ("Stack0", "sp1", 0xfffff)
    , Program1 ("Program1", "sp1", 0x1fffff)
    , Stack1 ("Stack1", "sp1", 0xfffff)
    , Program2 ("Program2", "sp1", 0x1fffff)
    , Stack2 ("Stack2", "sp1", 0xfffff)
    , Program3 ("Program3", "sp1", 0x1fffff)
    , Stack3 ("Stack3", "sp1", 0xfffff)
    , Program4 ("Program4", "sp1", 0x1fffff)
    , Stack4 ("Stack4", "sp1", 0xfffff)
    , Program5 ("Program5", "sp1", 0x1fffff)
    , Stack5 ("Stack5", "sp1", 0xfffff)
    , Program6 ("Program6", "sp1", 0x1fffff)
    , Stack6 ("Stack6", "sp1", 0xfffff)
    , Program7 ("Program7", "sp1", 0x1fffff)
    , Stack7 ("Stack7", "sp1", 0xfffff)
    , Program8 ("Program8", "sp1", 0x1fffff)
    , Stack8 ("Stack8", "sp1", 0xfffff)
    , Program9 ("Program9", "sp1", 0x1fffff)
    , Stack9 ("Stack9", "sp1", 0xfffff)
    , Program10 ("Program10", "sp1", 0x1fffff)
    , Stack10 ("Stack10", "sp1", 0xfffff)
    , Program11 ("Program11", "sp1", 0x1fffff)
    , Stack11 ("Stack11", "sp1", 0xfffff)
    , Program12 ("Program12", "sp1", 0x1fffff)
    , Stack12 ("Stack12", "sp1", 0xfffff)
    , Program13 ("Program13", "sp1", 0x1fffff)
    , Stack13 ("Stack13", "sp1", 0xfffff)
    , Program14 ("Program14", "sp1", 0x1fffff)
    , Stack14 ("Stack14", "sp1", 0xfffff)
    , Program15 ("Program15", "sp1", 0x1fffff)
    , Stack15 ("Stack15", "sp1", 0xfffff)
    , Program16 ("Program16", "sp1", 0x1fffff)
    , Stack16 ("Stack16", "sp1", 0xfffff)
    , Program17 ("Program17", "sp1", 0x1fffff)
    , Stack17 ("Stack17", "sp1", 0xfffff)
    , Program18 ("Program18", "sp1", 0x1fffff)
    , Stack18 ("Stack18", "sp1", 0xfffff)
    , Program19 ("Program19", "sp1", 0x1fffff)
    , Stack19 ("Stack19", "sp1", 0xfffff)
    , Program20 ("Program20", "sp1", 0x1fffff)
    , Stack20 ("Stack20", "sp1", 0xfffff)
    , Program21 ("Program21", "sp1", 0x1fffff)
    , Stack21 ("Stack21", "sp1", 0xfffff)
    , Program22 ("Program22", "sp1", 0x1fffff)
    , Stack22 ("Stack22", "sp1", 0xfffff)
    , Program23 ("Program23", "sp1", 0x1fffff)
    , Stack23 ("Stack23", "sp1", 0xfffff)
    , cpu0 ( "cpu0", 0, ICM_ATTR_DEFAULT, attrsForcpu0(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu1 ( "cpu1", 1, ICM_ATTR_DEFAULT, attrsForcpu1(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu2 ( "cpu2", 2, ICM_ATTR_DEFAULT, attrsForcpu2(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu3 ( "cpu3", 3, ICM_ATTR_DEFAULT, attrsForcpu3(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu4 ( "cpu4", 4, ICM_ATTR_DEFAULT, attrsForcpu4(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu5 ( "cpu5", 5, ICM_ATTR_DEFAULT, attrsForcpu5(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu6 ( "cpu6", 6, ICM_ATTR_DEFAULT, attrsForcpu6(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu7 ( "cpu7", 7, ICM_ATTR_DEFAULT, attrsForcpu7(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu8 ( "cpu8", 8, ICM_ATTR_DEFAULT, attrsForcpu8(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu9 ( "cpu9", 9, ICM_ATTR_DEFAULT, attrsForcpu9(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu10 ( "cpu10", 10, ICM_ATTR_DEFAULT, attrsForcpu10(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu11 ( "cpu11", 11, ICM_ATTR_DEFAULT, attrsForcpu11(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu12 ( "cpu12", 12, ICM_ATTR_DEFAULT, attrsForcpu12(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu13 ( "cpu13", 13, ICM_ATTR_DEFAULT, attrsForcpu13(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu14 ( "cpu14", 14, ICM_ATTR_DEFAULT, attrsForcpu14(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu15 ( "cpu15", 15, ICM_ATTR_DEFAULT, attrsForcpu15(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu16 ( "cpu16", 16, ICM_ATTR_DEFAULT, attrsForcpu16(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu17 ( "cpu17", 17, ICM_ATTR_DEFAULT, attrsForcpu17(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu18 ( "cpu18", 18, ICM_ATTR_DEFAULT, attrsForcpu18(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu19 ( "cpu19", 19, ICM_ATTR_DEFAULT, attrsForcpu19(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu20 ( "cpu20", 20, ICM_ATTR_DEFAULT, attrsForcpu20(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu21 ( "cpu21", 21, ICM_ATTR_DEFAULT, attrsForcpu21(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu22 ( "cpu22", 22, ICM_ATTR_DEFAULT, attrsForcpu22(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
    , cpu23 ( "cpu23", 23, ICM_ATTR_DEFAULT, attrsForcpu23(),  icmGetVlnvString (NULL, "arc.ovpworld.org", "semihosting", "arcNewlib", "1.0", "model") )
{

    // Bus0 masters
    cpu0.INSTRUCTION.socket(Bus0.target_socket[0]);
    cpu0.DATA.socket(Bus0.target_socket[1]);

    // Bus0 slaves
    Bus0.initiator_socket[0](Program0.sp1); // Memory
    Bus0.setDecode(0, 0x0, 0x1fffff);

    Bus0.initiator_socket[1](Stack0.sp1); // Memory
    Bus0.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus1 masters
    cpu1.INSTRUCTION.socket(Bus1.target_socket[0]);
    cpu1.DATA.socket(Bus1.target_socket[1]);

    // Bus1 slaves
    Bus1.initiator_socket[0](Program1.sp1); // Memory
    Bus1.setDecode(0, 0x0, 0x1fffff);

    Bus1.initiator_socket[1](Stack1.sp1); // Memory
    Bus1.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus2 masters
    cpu2.INSTRUCTION.socket(Bus2.target_socket[0]);
    cpu2.DATA.socket(Bus2.target_socket[1]);

    // Bus2 slaves
    Bus2.initiator_socket[0](Program2.sp1); // Memory
    Bus2.setDecode(0, 0x0, 0x1fffff);

    Bus2.initiator_socket[1](Stack2.sp1); // Memory
    Bus2.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus3 masters
    cpu3.INSTRUCTION.socket(Bus3.target_socket[0]);
    cpu3.DATA.socket(Bus3.target_socket[1]);

    // Bus3 slaves
    Bus3.initiator_socket[0](Program3.sp1); // Memory
    Bus3.setDecode(0, 0x0, 0x1fffff);

    Bus3.initiator_socket[1](Stack3.sp1); // Memory
    Bus3.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus4 masters
    cpu4.INSTRUCTION.socket(Bus4.target_socket[0]);
    cpu4.DATA.socket(Bus4.target_socket[1]);

    // Bus4 slaves
    Bus4.initiator_socket[0](Program4.sp1); // Memory
    Bus4.setDecode(0, 0x0, 0x1fffff);

    Bus4.initiator_socket[1](Stack4.sp1); // Memory
    Bus4.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus5 masters
    cpu5.INSTRUCTION.socket(Bus5.target_socket[0]);
    cpu5.DATA.socket(Bus5.target_socket[1]);

    // Bus5 slaves
    Bus5.initiator_socket[0](Program5.sp1); // Memory
    Bus5.setDecode(0, 0x0, 0x1fffff);

    Bus5.initiator_socket[1](Stack5.sp1); // Memory
    Bus5.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus6 masters
    cpu6.INSTRUCTION.socket(Bus6.target_socket[0]);
    cpu6.DATA.socket(Bus6.target_socket[1]);

    // Bus6 slaves
    Bus6.initiator_socket[0](Program6.sp1); // Memory
    Bus6.setDecode(0, 0x0, 0x1fffff);

    Bus6.initiator_socket[1](Stack6.sp1); // Memory
    Bus6.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus7 masters
    cpu7.INSTRUCTION.socket(Bus7.target_socket[0]);
    cpu7.DATA.socket(Bus7.target_socket[1]);

    // Bus7 slaves
    Bus7.initiator_socket[0](Program7.sp1); // Memory
    Bus7.setDecode(0, 0x0, 0x1fffff);

    Bus7.initiator_socket[1](Stack7.sp1); // Memory
    Bus7.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus8 masters
    cpu8.INSTRUCTION.socket(Bus8.target_socket[0]);
    cpu8.DATA.socket(Bus8.target_socket[1]);

    // Bus8 slaves
    Bus8.initiator_socket[0](Program8.sp1); // Memory
    Bus8.setDecode(0, 0x0, 0x1fffff);

    Bus8.initiator_socket[1](Stack8.sp1); // Memory
    Bus8.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus9 masters
    cpu9.INSTRUCTION.socket(Bus9.target_socket[0]);
    cpu9.DATA.socket(Bus9.target_socket[1]);

    // Bus9 slaves
    Bus9.initiator_socket[0](Program9.sp1); // Memory
    Bus9.setDecode(0, 0x0, 0x1fffff);

    Bus9.initiator_socket[1](Stack9.sp1); // Memory
    Bus9.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus10 masters
    cpu10.INSTRUCTION.socket(Bus10.target_socket[0]);
    cpu10.DATA.socket(Bus10.target_socket[1]);

    // Bus10 slaves
    Bus10.initiator_socket[0](Program10.sp1); // Memory
    Bus10.setDecode(0, 0x0, 0x1fffff);

    Bus10.initiator_socket[1](Stack10.sp1); // Memory
    Bus10.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus11 masters
    cpu11.INSTRUCTION.socket(Bus11.target_socket[0]);
    cpu11.DATA.socket(Bus11.target_socket[1]);

    // Bus11 slaves
    Bus11.initiator_socket[0](Program11.sp1); // Memory
    Bus11.setDecode(0, 0x0, 0x1fffff);

    Bus11.initiator_socket[1](Stack11.sp1); // Memory
    Bus11.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus12 masters
    cpu12.INSTRUCTION.socket(Bus12.target_socket[0]);
    cpu12.DATA.socket(Bus12.target_socket[1]);

    // Bus12 slaves
    Bus12.initiator_socket[0](Program12.sp1); // Memory
    Bus12.setDecode(0, 0x0, 0x1fffff);

    Bus12.initiator_socket[1](Stack12.sp1); // Memory
    Bus12.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus13 masters
    cpu13.INSTRUCTION.socket(Bus13.target_socket[0]);
    cpu13.DATA.socket(Bus13.target_socket[1]);

    // Bus13 slaves
    Bus13.initiator_socket[0](Program13.sp1); // Memory
    Bus13.setDecode(0, 0x0, 0x1fffff);

    Bus13.initiator_socket[1](Stack13.sp1); // Memory
    Bus13.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus14 masters
    cpu14.INSTRUCTION.socket(Bus14.target_socket[0]);
    cpu14.DATA.socket(Bus14.target_socket[1]);

    // Bus14 slaves
    Bus14.initiator_socket[0](Program14.sp1); // Memory
    Bus14.setDecode(0, 0x0, 0x1fffff);

    Bus14.initiator_socket[1](Stack14.sp1); // Memory
    Bus14.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus15 masters
    cpu15.INSTRUCTION.socket(Bus15.target_socket[0]);
    cpu15.DATA.socket(Bus15.target_socket[1]);

    // Bus15 slaves
    Bus15.initiator_socket[0](Program15.sp1); // Memory
    Bus15.setDecode(0, 0x0, 0x1fffff);

    Bus15.initiator_socket[1](Stack15.sp1); // Memory
    Bus15.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus16 masters
    cpu16.INSTRUCTION.socket(Bus16.target_socket[0]);
    cpu16.DATA.socket(Bus16.target_socket[1]);

    // Bus16 slaves
    Bus16.initiator_socket[0](Program16.sp1); // Memory
    Bus16.setDecode(0, 0x0, 0x1fffff);

    Bus16.initiator_socket[1](Stack16.sp1); // Memory
    Bus16.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus17 masters
    cpu17.INSTRUCTION.socket(Bus17.target_socket[0]);
    cpu17.DATA.socket(Bus17.target_socket[1]);

    // Bus17 slaves
    Bus17.initiator_socket[0](Program17.sp1); // Memory
    Bus17.setDecode(0, 0x0, 0x1fffff);

    Bus17.initiator_socket[1](Stack17.sp1); // Memory
    Bus17.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus18 masters
    cpu18.INSTRUCTION.socket(Bus18.target_socket[0]);
    cpu18.DATA.socket(Bus18.target_socket[1]);

    // Bus18 slaves
    Bus18.initiator_socket[0](Program18.sp1); // Memory
    Bus18.setDecode(0, 0x0, 0x1fffff);

    Bus18.initiator_socket[1](Stack18.sp1); // Memory
    Bus18.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus19 masters
    cpu19.INSTRUCTION.socket(Bus19.target_socket[0]);
    cpu19.DATA.socket(Bus19.target_socket[1]);

    // Bus19 slaves
    Bus19.initiator_socket[0](Program19.sp1); // Memory
    Bus19.setDecode(0, 0x0, 0x1fffff);

    Bus19.initiator_socket[1](Stack19.sp1); // Memory
    Bus19.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus20 masters
    cpu20.INSTRUCTION.socket(Bus20.target_socket[0]);
    cpu20.DATA.socket(Bus20.target_socket[1]);

    // Bus20 slaves
    Bus20.initiator_socket[0](Program20.sp1); // Memory
    Bus20.setDecode(0, 0x0, 0x1fffff);

    Bus20.initiator_socket[1](Stack20.sp1); // Memory
    Bus20.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus21 masters
    cpu21.INSTRUCTION.socket(Bus21.target_socket[0]);
    cpu21.DATA.socket(Bus21.target_socket[1]);

    // Bus21 slaves
    Bus21.initiator_socket[0](Program21.sp1); // Memory
    Bus21.setDecode(0, 0x0, 0x1fffff);

    Bus21.initiator_socket[1](Stack21.sp1); // Memory
    Bus21.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus22 masters
    cpu22.INSTRUCTION.socket(Bus22.target_socket[0]);
    cpu22.DATA.socket(Bus22.target_socket[1]);

    // Bus22 slaves
    Bus22.initiator_socket[0](Program22.sp1); // Memory
    Bus22.setDecode(0, 0x0, 0x1fffff);

    Bus22.initiator_socket[1](Stack22.sp1); // Memory
    Bus22.setDecode(1, 0x3d000000, 0x3d0fffff);


    // Bus23 masters
    cpu23.INSTRUCTION.socket(Bus23.target_socket[0]);
    cpu23.DATA.socket(Bus23.target_socket[1]);

    // Bus23 slaves
    Bus23.initiator_socket[0](Program23.sp1); // Memory
    Bus23.setDecode(0, 0x0, 0x1fffff);

    Bus23.initiator_socket[1](Stack23.sp1); // Memory
    Bus23.setDecode(1, 0x3d000000, 0x3d0fffff);

}
