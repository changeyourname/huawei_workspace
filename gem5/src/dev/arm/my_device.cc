/*
 * Copyright (c) 2010 ARM Limited
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2005 The Regents of The University of Michigan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Uzair
 */

#include "base/trace.hh"
//#include "debug/AMBA.hh"
#include "dev/arm/my_device.hh"
#include "mem/packet.hh"
#include "mem/packet_access.hh"




// right now my_device dummies a cache_monitor peripheral for 32 bit platform
// no write interface...only can read its registers
// each register is 64bit...there are no actual registers but give illusion
// to gem5 that its a peripheral with registers. whenever its register is read
// by gem5, it will internally make call to SystemC cache models and get the 
// required info and send it back to gem5 via passed pkt

// for each cache (i/d) this provides 2 registers
// (1) total accesses         (2) total misses







MyDevice::MyDevice(const Params *p)
    : BasicPioDevice(p, 0xfff),
      reg_size(p->word_width),
      num_regs(2*p->num_caches),
      icache0(p->icache0),
      dcache0(p->dcache0)
{
}

Tick
MyDevice::read(PacketPtr pkt)
{
    assert(pioAddr%reg_size == 0);             // must be correctly aligned
    uint32_t reg = (pkt->getAddr() - pioAddr) / reg_size;
    assert(reg < num_regs);        
    assert(pkt->getSize() == reg_size);     // reg to read should be 8B in gem5

    // TODO: read requested info from systemc cache models
    icache0->uzair();
 
    if (reg == 0) {
        pkt->set<uint32_t>(0x22222222);
    } else if (reg == 1) {
        pkt->set<uint32_t>(0x44444444);
    } else {
        pkt->set<uint32_t>(0);
    }
    
    pkt->makeAtomicResponse();
    return pioDelay;
}

Tick
MyDevice::write(PacketPtr pkt)
{

//    Addr daddr = pkt->getAddr() - pioAddr;

//    if (!params()->ignore_access)
//        panic("Tried to write AmbaFake at offset %#x that doesn't exist\n", daddr);

//    pkt->makeAtomicResponse();
//    return pioDelay;

    assert(0);
}


MyDevice *
MyDeviceParams::create()
{
    return new MyDevice(this);
}
