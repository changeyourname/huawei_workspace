/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include "tlm.h"
#include "ovpworld.org/modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.hpp"
#include "ovpworld.org/modelSupport/tlmDecoder/1.0/tlm2.0/tlmDecoder.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"
#include "ovpworld.org/processor/or1k/1.0/tlm2.0/processor.igen.hpp"

////////////////////////////////////////////////////////////////////////////////
//                      Platform_TLM2_0 Class                      //
////////////////////////////////////////////////////////////////////////////////

class Platform_TLM2_0 : public sc_core::sc_module {

  public:
    Platform_TLM2_0 (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,2> bus1;
    ram                   ram1;
    ram                   ram2;
    or1k                  cpu1;

    icmAttrListObject *attrsForcpu1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        return userAttrs;
    }
}; /* Platform_TLM2_0 */

////////////////////////////////////////////////////////////////////////////////
//                   Platform_TLM2_0 Constructor                   //
////////////////////////////////////////////////////////////////////////////////

Platform_TLM2_0::Platform_TLM2_0 ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_VERBOSE | ICM_STOP_ON_CTRLC | ICM_GDB_CONSOLE, "rsp", 0 )
    , bus1("bus1")
    , ram1 ("ram1", "sp1", 0xFFFFF)
    , ram2 ("ram2", "sp1", 0xFFFF)
    , cpu1 ( "cpu1", 0, ICM_ATTR_DEFAULT, attrsForcpu1())
{

    // bus1 masters
    cpu1.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu1.DATA.socket(bus1.target_socket[1]);

    // bus1 slaves
    bus1.initiator_socket[0](ram1.sp1); // Memory
    bus1.setDecode(0, 0x0, 0xfffff);

    bus1.initiator_socket[1](ram2.sp1); // Memory
    bus1.setDecode(1, 0xffff0000, 0xffffffff);

}

int sc_main (int argc, char *argv[] )
{
    const char *app = "application.elf";

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

    Platform_TLM2_0 top("top");             // instantiate example top module

    // Use the TLM code memory. It needs to be loaded with the program.
    top.cpu1.loadLocalMemory(app, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));

    // Specify the debug processor.
    top.cpu1.debugThisProcessor();

    if (argc > 2) {
        stop = sc_time(atoi(argv[2]), SC_MS);

        sc_core::sc_start(stop);                  // start the simulation
    } else {
        sc_core::sc_start();                      // start the simulation
    }

    cout << "Finished sc_main." << endl;
    return 0;                             // return okay status
}
