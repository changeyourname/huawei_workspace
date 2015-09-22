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
//                          Tue May 18 14:13:15 2010                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PLATFORM_CPP
#define PLATFORM_CPP
#include "tlm.h"
#include "ovpworld.org/modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.hpp"
#include "ovpworld.org/modelSupport/tlmDecoder/1.0/tlm2.0/tlmDecoder.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"
#include "mips.processor.igen.hpp"
#include "ovp.processor.igen.hpp"

////////////////////////////////////////////////////////////////////////////////
//                     BareMetalMips32Single_TLM2_0 Class                     //
////////////////////////////////////////////////////////////////////////////////

class BareMetalMips32Single_TLM2_0 : public sc_core::sc_module {

  public:
    BareMetalMips32Single_TLM2_0 (sc_core::sc_module_name name, bool *defaultVendor, const char *variant);
    ~BareMetalMips32Single_TLM2_0 ();

    icmTLMPlatform        Platform;
    decoder             <2,6> bus1;
    ram                   program1;
    ram                   stack1;
    ram                   stack2;
    ram                   stack3;
    ram                   high_mem1;
    ram                   high_mem2;
    ovp_mips32           *ovp_cpu1;
    mips_mips32          *mips_cpu1;

    const char *semihostForovp_cpu1() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "semihosting", "mips32Newlib", 0, "model");
    }
    const char *semihostFormips_cpu1() {
            return icmGetVlnvString (NULL, "mips.com", "semihosting", "mips32Newlib", 0, "model");
    }

    icmAttrListObject *attrsForcpu1(const char *variant) {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("endian", "little");
        userAttrs->addAttr("variant", variant);
        return userAttrs;
    }

}; /* BareMetalMips32Single_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                  BareMetalMips32Single_TLM2_0 Constructor                  //
////////////////////////////////////////////////////////////////////////////////

BareMetalMips32Single_TLM2_0::BareMetalMips32Single_TLM2_0 ( sc_core::sc_module_name name, bool *defaultVendor, const char *variant)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_VERBOSE| ICM_STOP_ON_CTRLC| ICM_ENABLE_IMPERAS_INTERCEPTS )
    , bus1("bus1")
    , program1 ("program1", "sp1", 0x0FFFFF)
    , stack1 ("stack1", "sp1", 0x0FFFFF)
    , stack2 ("stack2", "sp1", 0x0FFFFF)
    , stack3 ("stack3", "sp1", 0x0FFFF)
    , high_mem1 ("high_mem1", "sp1",  0x0FFFFF)
    , high_mem2 ("high_mem2", "sp1",  0x17FFFF)
{
    // select model to load based upon simulator
    char *runtime = getenv("IMPERAS_RUNTIME");
    // Are we running OVPsim or Imperas? If so use mips.ovpworld.org
    if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
        ;   // use default vendor
        const char *model = icmTryVlnvString (NULL, "mips.ovpworld.org", "processor", "mips32", 0, "model");
        // Check model exists, otherwise revert to other
        if(!model) *defaultVendor = false;
        else *defaultVendor = true;
    } else {
        const char *model = icmTryVlnvString (NULL, "mips.com", "processor", "mips32", 0, "model");
        // Check model exists, otherwise revert to other
        if(model) *defaultVendor = false;
        else *defaultVendor = true;
    }

    if (*defaultVendor) {
        ovp_cpu1  = new ovp_mips32 ( "cpu1", 0, ICM_ATTR_DEFAULT, attrsForcpu1(variant), semihostForovp_cpu1());
        mips_cpu1 = 0;
    } else {
        mips_cpu1 = new mips_mips32 ( "cpu1", 0, ICM_ATTR_DEFAULT, attrsForcpu1(variant), semihostFormips_cpu1());
        ovp_cpu1  = 0;
    }

    // bus1 masters
    if (*defaultVendor) {
        ovp_cpu1->INSTRUCTION.socket(bus1.target_socket[0]);
        ovp_cpu1->DATA.socket(bus1.target_socket[1]);
    } else {
        mips_cpu1->INSTRUCTION.socket(bus1.target_socket[0]);
        mips_cpu1->DATA.socket(bus1.target_socket[1]);
    }

    // bus1 slaves
    bus1.initiator_socket[0](program1.sp1); // Memory
    bus1.setDecode(0, 0x0, 0xfffff);

    bus1.initiator_socket[1](stack1.sp1); // Memory
    bus1.setDecode(1, 0x500000, 0x5fffff);

    bus1.initiator_socket[2](stack2.sp1); // Memory
    bus1.setDecode(2, 0x100000, 0x1fffff);

    bus1.initiator_socket[3](stack3.sp1); // Memory
    bus1.setDecode(3, 0x1fff0000, 0x1fffffff);

    bus1.initiator_socket[4](high_mem1.sp1); // Memory
    bus1.setDecode(4, 0x10000000, 0x100fffff);

    bus1.initiator_socket[5](high_mem2.sp1); // Memory
    bus1.setDecode(5, 0x80000000, 0x8017ffff);

}

BareMetalMips32Single_TLM2_0::~BareMetalMips64Single_TLM2_0() {
    if(ovp_cpu1 ) delete ovp_cpu1;
    if(mips_cpu1) delete mips_cpu1;
}

#endif

int sc_main (int argc, char *argv[] )
{

    const char *app = "noAppSupplied";
    const char *variant = "4KEc";           // default variant
    bool defaultVendor = true;

    if (argc > 1) {
        app = argv[1];
        if (argc > 2) {
            variant = argv[2];
        }
    } else {
        cout << "Please specify application" << endl;
        return 0;
    }

    // Ignore some of the Warning messages
    icmIgnoreMessage ("ICM_NPF");

    BareMetalMips32Single_TLM2_0 top("top", &defaultVendor, variant);             // instantiate example top module
    if(!(defaultVendor ? top.ovp_cpu1->loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START)) :
                         top.mips_cpu1->loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START)))) {
        return 1;
    }

    sc_core::sc_start();                  // start the simulation
    cout << "Finished sc_main." << endl;
    return 0;                             // return okay status
}
