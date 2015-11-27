# -*- coding: utf-8 -*-
# Copyright (c) 2015 Jason Power
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors: Jason Power

# import the m5 (gem5) library created when gem5 is built
import m5
# import all of the SimObjects
from m5.objects import *

# Add the common scripts to our path
m5.util.addToPath('../../common')

# import the SimpleOpts module
import SimpleOpts

# Set the usage message to display
SimpleOpts.set_usage("usage: %prog [options] <binary to execute>")

# Finalize the arguments and grab the opts so we can pass it on to our objects
(opts, args) = SimpleOpts.parse_args()

# get ISA for the default binary to run. This is mostly for simple testing
isa = str(m5.defines.buildEnv['TARGET_ISA']).lower()

# Default to running 'hello', use the compiled ISA to find the binary
binary = 'tests/test-progs/hello/bin/' + isa + '/linux/hello'

# Check if there was a binary passed in via the command line and error if
# there are too many arguments
if len(args) == 1:
    binary = args[0]
elif len(args) > 1:
    SimpleOpts.print_help()
    m5.fatal("Expected a binary to execute as positional argument")

# create the system we are going to simulate
system = System()

# Set the clock fequency of the system (and all of its children)
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

# Set up the system
system.mem_mode = 'timing'               # Use timing accesses
system.mem_ranges = [AddrRange('512MB')] # Create an address range

# Create a simple CPU
system.cpu = TimingSimpleCPU()

# Create dummy L1 i/d caches
system.cpu.icache = CommMonitor()
system.cpu.dcache = CommMonitor()

# external ports for hooking to SystemC world
system.physmem = SimpleMemory() # This must be instanciated, even if not needed
system.tlm_1 = ExternalSlave()
system.tlm_1.addr_ranges = [AddrRange('512MB')]
system.tlm_1.port_type = "tlm"
system.tlm_1.port_data = "icache_port"

system.tlm_2 = ExternalSlave()
system.tlm_2.addr_ranges = [AddrRange('512MB')]
system.tlm_2.port_type = "tlm"
system.tlm_2.port_data = "dcache_port"

system.tlm_3 = ExternalSlave()
system.tlm_3.addr_ranges = [AddrRange('512MB')]
system.tlm_3.port_type = "tlm"
system.tlm_3.port_data = "system_port"

# Connect the instruction and data caches to the CPU
system.cpu.icache.slave = system.cpu.icache_port
system.cpu.dcache.slave = system.cpu.dcache_port
# Hook the caches to external world
system.cpu.icache.master = system.tlm_1.port
system.cpu.dcache.master = system.tlm_2.port
# hook the system_port to external world
system.system_port = system.tlm_3.port

# create the interrupt controller for the CPU
system.cpu.createInterruptController()

# For x86 only, make sure the interrupts are connected to the memory
# Note: these are directly connected to the memory bus and are not cached
if m5.defines.buildEnv['TARGET_ISA'] == "x86":
    print "x86 not supported"
    sys.exit(1);

# Create a process for a simple "Hello World" application
process = LiveProcess()
# Set the command
# cmd is a list which begins with the executable (like argv)
process.cmd = [binary]
# Set the cpu to use the process as its workload and create thread contexts
system.cpu.workload = process
system.cpu.createThreads()

# set up the root SimObject and start the simulation
root = Root(full_system = False, system = system)
# instantiate all of the objects we've created above
m5.instantiate()

print "Beginning simulation!"
exit_event = m5.simulate()
print 'Exiting @ tick %i because %s' % (m5.curTick(), exit_event.getCause())
