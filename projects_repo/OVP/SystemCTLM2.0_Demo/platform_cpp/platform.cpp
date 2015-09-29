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
#include "national.ovpworld.org/peripheral/16550/1.0/tlm2.0/pse.igen.hpp"

////////////////////////////////////////////////////////////////////////////////
//                                simple Class
////////////////////////////////////////////////////////////////////////////////

class simple : public sc_core::sc_module {

  public:
    simple (sc_core::sc_module_name name);

    icmTLMPlatform        Platform;
    decoder             <2,3> bus1;
    ram                   ram1;
    ram                   ram2;
    or1k                  cpu1;
    _16550                uart1;


    icmAttrListObject *attrsForuart1() {
        icmAttrListObject *userAttrs = new icmAttrListObject;
        userAttrs->addAttr("outfile", "uart1.log");
        return userAttrs;
    }
}; /* simple */

////////////////////////////////////////////////////////////////////////////////
//                             simple Constructor
////////////////////////////////////////////////////////////////////////////////

simple::simple ( sc_core::sc_module_name name)
    : sc_core::sc_module (name)
    , Platform ("icm", ICM_VERBOSE | ICM_STOP_ON_CTRLC| ICM_ENABLE_IMPERAS_INTERCEPTS )
    , bus1("bus1")
    , ram1 ("ram1", "sp1", 0xFFFFF)
    , ram2 ("ram2", "sp1", 0xFFFF)
    , cpu1 ( "cpu1", 0    )
    , uart1 ("uart1", attrsForuart1())
{

    // bus1 master
    cpu1.INSTRUCTION.socket(bus1.target_socket[0]);
    cpu1.DATA.socket(bus1.target_socket[1]);

    // bus1 slave
    bus1.initiator_socket[0](uart1.bport1.socket); // Peripheral
    bus1.setDecode(0, 0x90000000, 0x90000007);

    // Connect and configure the bus decoder
    bus1.initiator_socket[1](ram1.sp1); // Memory
    bus1.setDecode(1, 0x0, 0xfffff);

    bus1.initiator_socket[2](ram2.sp1); // Memory
    bus1.setDecode(2, 0xffff0000, 0xffffffff);

    // Net connections
    uart1.intOut(cpu1.intr0);
    // reverse binding for sc_signal cpu1.intr0(uart1.intOut);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[] )
{
    const char *exe;

    if (argc == 2) {
        exe = argv[1];
    } else {
        cout << "Usage: platform.exe <application>" << endl;
        cout << "       Please specify application" << endl;
        return 0;
    }

    cout << "Constructing." << endl;
    simple top("top");
    top.cpu1.setIPS(100000);       // 1000KHz

    top.uart1.setDiagnosticLevel(1);  // Set diagnostic level for Uart

    cout << "Using SystemC TLM2.0 Memory with DMI" << endl;

    top.cpu1.loadLocalMemory(exe, (icmLoaderAttrs)(ICM_LOAD_VERBOSE | ICM_SET_START));

    cout << "Starting sc_main (reset asserted)." << endl;
    top.cpu1.reset.write(1);
    sc_core::sc_start(1, SC_US);         // Run the simulation for 1 uS with reset asserted

    cout << "*** De-assert reset. ***\n" << endl;
    top.cpu1.reset.write(0);
    sc_core::sc_start();                 // Run to end of simulation with reset de-asserted

    cout << "Finished sc_main." << endl;
    return 0;                            // return okay status
}

