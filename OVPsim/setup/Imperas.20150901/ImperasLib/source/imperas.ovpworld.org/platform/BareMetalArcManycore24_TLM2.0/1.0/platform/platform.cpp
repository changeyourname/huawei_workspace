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
//                                                                            //
//                W R I T T E N   B Y   I M P E R A S   I G E N               //
//                                                                            //
//                          Wed May 19 08:09:56 2010                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "tlm.h"
#include "ovpworld.org/modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.hpp"
#include "ovpworld.org/modelSupport/tlmDecoder/1.0/tlm2.0/tlmDecoder.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"
#include "arc.ovpworld.org/processor/arc/1.0/tlm2.0/arc_700.igen.hpp"

////////////////////////////////////////////////////////////////////////////////
//                     BareMetalArcManycore24_TLM2_0 Class                    //
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
    arc_700               cpu0;
    arc_700               cpu1;
    arc_700               cpu2;
    arc_700               cpu3;
    arc_700               cpu4;
    arc_700               cpu5;
    arc_700               cpu6;
    arc_700               cpu7;
    arc_700               cpu8;
    arc_700               cpu9;
    arc_700               cpu10;
    arc_700               cpu11;
    arc_700               cpu12;
    arc_700               cpu13;
    arc_700               cpu14;
    arc_700               cpu15;
    arc_700               cpu16;
    arc_700               cpu17;
    arc_700               cpu18;
    arc_700               cpu19;
    arc_700               cpu20;
    arc_700               cpu21;
    arc_700               cpu22;
    arc_700               cpu23;

    icmAttrListObject *attrsForcpu() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("endian", "little");
        userAttrs->addAttr("variant",        "700");
        userAttrs->addAttr("format",         "metaware");
        userAttrs->addAttr("end-on-halt",    "1");
        return userAttrs;
    }


}; /* BareMetalArcManycore24_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                  BareMetalArcManycore24_TLM2_0 Constructor                 //
////////////////////////////////////////////////////////////////////////////////

BareMetalArcManycore24_TLM2_0::BareMetalArcManycore24_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_VERBOSE | ICM_STOP_ON_CTRLC| ICM_ENABLE_IMPERAS_INTERCEPTS )
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
    , Program0 ("Program0", "sp1", 0x1FFFFF)
    , Stack0 ("Stack0", "sp1", 0xFFFFF)
    , Program1 ("Program1", "sp1", 0x1FFFFF)
    , Stack1 ("Stack1", "sp1", 0xFFFFF)
    , Program2 ("Program2", "sp1", 0x1FFFFF)
    , Stack2 ("Stack2", "sp1", 0xFFFFF)
    , Program3 ("Program3", "sp1", 0x1FFFFF)
    , Stack3 ("Stack3", "sp1", 0xFFFFF)
    , Program4 ("Program4", "sp1", 0x1FFFFF)
    , Stack4 ("Stack4", "sp1", 0xFFFFF)
    , Program5 ("Program5", "sp1", 0x1FFFFF)
    , Stack5 ("Stack5", "sp1", 0xFFFFF)
    , Program6 ("Program6", "sp1", 0x1FFFFF)
    , Stack6 ("Stack6", "sp1", 0xFFFFF)
    , Program7 ("Program7", "sp1", 0x1FFFFF)
    , Stack7 ("Stack7", "sp1", 0xFFFFF)
    , Program8 ("Program8", "sp1", 0x1FFFFF)
    , Stack8 ("Stack8", "sp1", 0xFFFFF)
    , Program9 ("Program9", "sp1", 0x1FFFFF)
    , Stack9 ("Stack9", "sp1", 0xFFFFF)
    , Program10 ("Program10", "sp1", 0x1FFFFF)
    , Stack10 ("Stack10", "sp1", 0xFFFFF)
    , Program11 ("Program11", "sp1", 0x1FFFFF)
    , Stack11 ("Stack11", "sp1", 0xFFFFF)
    , Program12 ("Program12", "sp1", 0x1FFFFF)
    , Stack12 ("Stack12", "sp1", 0xFFFFF)
    , Program13 ("Program13", "sp1", 0x1FFFFF)
    , Stack13 ("Stack13", "sp1", 0xFFFFF)
    , Program14 ("Program14", "sp1", 0x1FFFFF)
    , Stack14 ("Stack14", "sp1", 0xFFFFF)
    , Program15 ("Program15", "sp1", 0x1FFFFF)
    , Stack15 ("Stack15", "sp1", 0xFFFFF)
    , Program16 ("Program16", "sp1", 0x1FFFFF)
    , Stack16 ("Stack16", "sp1", 0xFFFFF)
    , Program17 ("Program17", "sp1", 0x1FFFFF)
    , Stack17 ("Stack17", "sp1", 0xFFFFF)
    , Program18 ("Program18", "sp1", 0x1FFFFF)
    , Stack18 ("Stack18", "sp1", 0xFFFFF)
    , Program19 ("Program19", "sp1", 0x1FFFFF)
    , Stack19 ("Stack19", "sp1", 0xFFFFF)
    , Program20 ("Program20", "sp1", 0x1FFFFF)
    , Stack20 ("Stack20", "sp1", 0xFFFFF)
    , Program21 ("Program21", "sp1", 0x1FFFFF)
    , Stack21 ("Stack21", "sp1", 0xFFFFF)
    , Program22 ("Program22", "sp1", 0x1FFFFF)
    , Stack22 ("Stack22", "sp1", 0xFFFFF)
    , Program23 ("Program23", "sp1", 0x1FFFFF)
    , Stack23 ("Stack23", "sp1", 0xFFFFF)
    , cpu0 ( "cpu0", 0, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu1 ( "cpu1", 1, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu2 ( "cpu2", 2, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu3 ( "cpu3", 3, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu4 ( "cpu4", 4, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu5 ( "cpu5", 5, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu6 ( "cpu6", 6, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu7 ( "cpu7", 7, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu8 ( "cpu8", 8, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu9 ( "cpu9", 9, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu10 ( "cpu10", 10, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu11 ( "cpu11", 11, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu12 ( "cpu12", 12, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu13 ( "cpu13", 13, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu14 ( "cpu14", 14, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu15 ( "cpu15", 15, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu16 ( "cpu16", 16, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu17 ( "cpu17", 17, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu18 ( "cpu18", 18, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu19 ( "cpu19", 19, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu20 ( "cpu20", 20, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu21 ( "cpu21", 21, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu22 ( "cpu22", 22, ICM_ATTR_DEFAULT, attrsForcpu())
    , cpu23 ( "cpu23", 23, ICM_ATTR_DEFAULT, attrsForcpu())
{

    // Bus0 masters
    cpu0.INSTRUCTION.socket(Bus0.target_socket[0]);
    cpu0.DATA.socket(Bus0.target_socket[1]);

    // Bus0 slaves
    Bus0.initiator_socket[0](Program0.sp1); // Memory
    Bus0.setDecode(0, 0x0, 0x1fffff);

    Bus0.initiator_socket[1](Stack0.sp1); // Memory
    Bus0.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus1 masters
    cpu1.INSTRUCTION.socket(Bus1.target_socket[0]);
    cpu1.DATA.socket(Bus1.target_socket[1]);

    // Bus1 slaves
    Bus1.initiator_socket[0](Program1.sp1); // Memory
    Bus1.setDecode(0, 0x0, 0x1fffff);

    Bus1.initiator_socket[1](Stack1.sp1); // Memory
    Bus1.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus2 masters
    cpu2.INSTRUCTION.socket(Bus2.target_socket[0]);
    cpu2.DATA.socket(Bus2.target_socket[1]);

    // Bus2 slaves
    Bus2.initiator_socket[0](Program2.sp1); // Memory
    Bus2.setDecode(0, 0x0, 0x1fffff);

    Bus2.initiator_socket[1](Stack2.sp1); // Memory
    Bus2.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus3 masters
    cpu3.INSTRUCTION.socket(Bus3.target_socket[0]);
    cpu3.DATA.socket(Bus3.target_socket[1]);

    // Bus3 slaves
    Bus3.initiator_socket[0](Program3.sp1); // Memory
    Bus3.setDecode(0, 0x0, 0x1fffff);

    Bus3.initiator_socket[1](Stack3.sp1); // Memory
    Bus3.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus4 masters
    cpu4.INSTRUCTION.socket(Bus4.target_socket[0]);
    cpu4.DATA.socket(Bus4.target_socket[1]);

    // Bus4 slaves
    Bus4.initiator_socket[0](Program4.sp1); // Memory
    Bus4.setDecode(0, 0x0, 0x1fffff);

    Bus4.initiator_socket[1](Stack4.sp1); // Memory
    Bus4.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus5 masters
    cpu5.INSTRUCTION.socket(Bus5.target_socket[0]);
    cpu5.DATA.socket(Bus5.target_socket[1]);

    // Bus5 slaves
    Bus5.initiator_socket[0](Program5.sp1); // Memory
    Bus5.setDecode(0, 0x0, 0x1fffff);

    Bus5.initiator_socket[1](Stack5.sp1); // Memory
    Bus5.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus6 masters
    cpu6.INSTRUCTION.socket(Bus6.target_socket[0]);
    cpu6.DATA.socket(Bus6.target_socket[1]);

    // Bus6 slaves
    Bus6.initiator_socket[0](Program6.sp1); // Memory
    Bus6.setDecode(0, 0x0, 0x1fffff);

    Bus6.initiator_socket[1](Stack6.sp1); // Memory
    Bus6.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus7 masters
    cpu7.INSTRUCTION.socket(Bus7.target_socket[0]);
    cpu7.DATA.socket(Bus7.target_socket[1]);

    // Bus7 slaves
    Bus7.initiator_socket[0](Program7.sp1); // Memory
    Bus7.setDecode(0, 0x0, 0x1fffff);

    Bus7.initiator_socket[1](Stack7.sp1); // Memory
    Bus7.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus8 masters
    cpu8.INSTRUCTION.socket(Bus8.target_socket[0]);
    cpu8.DATA.socket(Bus8.target_socket[1]);

    // Bus8 slaves
    Bus8.initiator_socket[0](Program8.sp1); // Memory
    Bus8.setDecode(0, 0x0, 0x1fffff);

    Bus8.initiator_socket[1](Stack8.sp1); // Memory
    Bus8.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus9 masters
    cpu9.INSTRUCTION.socket(Bus9.target_socket[0]);
    cpu9.DATA.socket(Bus9.target_socket[1]);

    // Bus9 slaves
    Bus9.initiator_socket[0](Program9.sp1); // Memory
    Bus9.setDecode(0, 0x0, 0x1fffff);

    Bus9.initiator_socket[1](Stack9.sp1); // Memory
    Bus9.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus10 masters
    cpu10.INSTRUCTION.socket(Bus10.target_socket[0]);
    cpu10.DATA.socket(Bus10.target_socket[1]);

    // Bus10 slaves
    Bus10.initiator_socket[0](Program10.sp1); // Memory
    Bus10.setDecode(0, 0x0, 0x1fffff);

    Bus10.initiator_socket[1](Stack10.sp1); // Memory
    Bus10.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus11 masters
    cpu11.INSTRUCTION.socket(Bus11.target_socket[0]);
    cpu11.DATA.socket(Bus11.target_socket[1]);

    // Bus11 slaves
    Bus11.initiator_socket[0](Program11.sp1); // Memory
    Bus11.setDecode(0, 0x0, 0x1fffff);

    Bus11.initiator_socket[1](Stack11.sp1); // Memory
    Bus11.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus12 masters
    cpu12.INSTRUCTION.socket(Bus12.target_socket[0]);
    cpu12.DATA.socket(Bus12.target_socket[1]);

    // Bus12 slaves
    Bus12.initiator_socket[0](Program12.sp1); // Memory
    Bus12.setDecode(0, 0x0, 0x1fffff);

    Bus12.initiator_socket[1](Stack12.sp1); // Memory
    Bus12.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus13 masters
    cpu13.INSTRUCTION.socket(Bus13.target_socket[0]);
    cpu13.DATA.socket(Bus13.target_socket[1]);

    // Bus13 slaves
    Bus13.initiator_socket[0](Program13.sp1); // Memory
    Bus13.setDecode(0, 0x0, 0x1fffff);

    Bus13.initiator_socket[1](Stack13.sp1); // Memory
    Bus13.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus14 masters
    cpu14.INSTRUCTION.socket(Bus14.target_socket[0]);
    cpu14.DATA.socket(Bus14.target_socket[1]);

    // Bus14 slaves
    Bus14.initiator_socket[0](Program14.sp1); // Memory
    Bus14.setDecode(0, 0x0, 0x1fffff);

    Bus14.initiator_socket[1](Stack14.sp1); // Memory
    Bus14.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus15 masters
    cpu15.INSTRUCTION.socket(Bus15.target_socket[0]);
    cpu15.DATA.socket(Bus15.target_socket[1]);

    // Bus15 slaves
    Bus15.initiator_socket[0](Program15.sp1); // Memory
    Bus15.setDecode(0, 0x0, 0x1fffff);

    Bus15.initiator_socket[1](Stack15.sp1); // Memory
    Bus15.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus16 masters
    cpu16.INSTRUCTION.socket(Bus16.target_socket[0]);
    cpu16.DATA.socket(Bus16.target_socket[1]);

    // Bus16 slaves
    Bus16.initiator_socket[0](Program16.sp1); // Memory
    Bus16.setDecode(0, 0x0, 0x1fffff);

    Bus16.initiator_socket[1](Stack16.sp1); // Memory
    Bus16.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus17 masters
    cpu17.INSTRUCTION.socket(Bus17.target_socket[0]);
    cpu17.DATA.socket(Bus17.target_socket[1]);

    // Bus17 slaves
    Bus17.initiator_socket[0](Program17.sp1); // Memory
    Bus17.setDecode(0, 0x0, 0x1fffff);

    Bus17.initiator_socket[1](Stack17.sp1); // Memory
    Bus17.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus18 masters
    cpu18.INSTRUCTION.socket(Bus18.target_socket[0]);
    cpu18.DATA.socket(Bus18.target_socket[1]);

    // Bus18 slaves
    Bus18.initiator_socket[0](Program18.sp1); // Memory
    Bus18.setDecode(0, 0x0, 0x1fffff);

    Bus18.initiator_socket[1](Stack18.sp1); // Memory
    Bus18.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus19 masters
    cpu19.INSTRUCTION.socket(Bus19.target_socket[0]);
    cpu19.DATA.socket(Bus19.target_socket[1]);

    // Bus19 slaves
    Bus19.initiator_socket[0](Program19.sp1); // Memory
    Bus19.setDecode(0, 0x0, 0x1fffff);

    Bus19.initiator_socket[1](Stack19.sp1); // Memory
    Bus19.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus20 masters
    cpu20.INSTRUCTION.socket(Bus20.target_socket[0]);
    cpu20.DATA.socket(Bus20.target_socket[1]);

    // Bus20 slaves
    Bus20.initiator_socket[0](Program20.sp1); // Memory
    Bus20.setDecode(0, 0x0, 0x1fffff);

    Bus20.initiator_socket[1](Stack20.sp1); // Memory
    Bus20.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus21 masters
    cpu21.INSTRUCTION.socket(Bus21.target_socket[0]);
    cpu21.DATA.socket(Bus21.target_socket[1]);

    // Bus21 slaves
    Bus21.initiator_socket[0](Program21.sp1); // Memory
    Bus21.setDecode(0, 0x0, 0x1fffff);

    Bus21.initiator_socket[1](Stack21.sp1); // Memory
    Bus21.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus22 masters
    cpu22.INSTRUCTION.socket(Bus22.target_socket[0]);
    cpu22.DATA.socket(Bus22.target_socket[1]);

    // Bus22 slaves
    Bus22.initiator_socket[0](Program22.sp1); // Memory
    Bus22.setDecode(0, 0x0, 0x1fffff);

    Bus22.initiator_socket[1](Stack22.sp1); // Memory
    Bus22.setDecode(1, 0x3D000000, 0x3D0fffff);


    // Bus23 masters
    cpu23.INSTRUCTION.socket(Bus23.target_socket[0]);
    cpu23.DATA.socket(Bus23.target_socket[1]);

    // Bus23 slaves
    Bus23.initiator_socket[0](Program23.sp1); // Memory
    Bus23.setDecode(0, 0x0, 0x1fffff);

    Bus23.initiator_socket[1](Stack23.sp1); // Memory
    Bus23.setDecode(1, 0x3D000000, 0xffffffff);

}

int sc_main (int argc, char *argv[] )
{

    const char *app = "noAppSupplied";

    if (argc > 1) {
        app = argv[1];
    } else {
        cout << "Please specify application" << endl;
        return 0;
    }

    // Ignore some of the Warning messages
    icmIgnoreMessage ("ICM_NPF");

    BareMetalArcManycore24_TLM2_0 top ("top");

    top.cpu0.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu1.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu2.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu3.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu4.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu5.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu6.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu7.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu8.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu9.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));

    top.cpu10.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu11.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu12.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu13.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu14.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu15.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu16.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu17.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu18.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu19.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));

    top.cpu20.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu21.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu22.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));
    top.cpu23.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));

    sc_core::sc_start();                  // start the simulation
    cout << "Finished sc_main." << endl;
    return 0;                             // return okay status
}

