/*
 * Copyright (c) 2012-2013, 2015 ARM Limited
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
 * Authors: Thomas Grass
 *          Andreas Hansson
 */
 
//TODO: remove extra functions and logic

#include "mem/sysc_cache.hh"
#include "sim/system.hh"
#include "cpu/thread_context.hh"
#include "cpu/base.hh"


std::map<std::string, SysC_Cache::Handler *>
    SysC_Cache::portHandlers;

AddrRangeList
SysC_Cache::SPort::getAddrRanges() const
{
    return owner.addrRanges;
}



SysC_Cache::SysC_Cache(Params* params)
    : MemObject(params),
      memPort(name() + "-memPort", *this),
      extPort(NULL),
      portName(params->name + ".extPort"),
      portType(params->port_type),
      portData(params->port_data),
      addrRanges(params->addr_ranges.begin(), params->addr_ranges.end())
{
}


void
SysC_Cache::registerHandler(const std::string &handler_name, Handler *handler)
{
    portHandlers[handler_name] = handler;
}


SysC_Cache*
SysC_CacheParams::create()
{
    return new SysC_Cache(this);
}

void
SysC_Cache::init()
{
    // make sure both sides of the monitor are connected
    if (!memPort.isConnected()) {
        fatal("SysC_Cache ports not connected on memory sides.\n");
    }
    
    if (!extPort) {
        fatal("SysC_Cache %s: externalPort not set!\n", name());
    } else if (!extPort->isConnected()) {
        fatal("SysC_Cache %s is unconnected\n", name());        
    } else {
        extPort->sendRangeChange();
    }
}


BaseMasterPort &
SysC_Cache::getMasterPort(const std::string &if_name, PortID idx)
{
    if (if_name == "memPort") {
        return memPort;
    } else {
        return MemObject::getMasterPort(if_name, idx);
    }
}

BaseSlavePort &
SysC_Cache::getSlavePort(const std::string &if_name, PortID idx)
{
    if (if_name == "extPort") {
        if (!extPort) {
            auto handlerIter = portHandlers.find(portType);
            
            if (handlerIter == portHandlers.end()) {
                fatal("Can't find port handler type '%s'\n", portType);
            }   
            
            extPort = portHandlers[portType]->getExternalPort(portName, *this, portData);
            
            if (!extPort) {
                fatal("%s: Can't find external port type: %s"
                    " port_data: '%s'\n", portName, portType, portData);
            }
        }
        return *extPort;
    } else {
        return MemObject::getSlavePort(if_name, idx);
    }
}


void
SysC_Cache::recvFunctional(PacketPtr pkt)
{
    memPort.sendFunctional(pkt);
}

void
SysC_Cache::recvFunctionalSnoop(PacketPtr pkt)
{
    extPort->sendFunctionalSnoop(pkt);
}

Tick
SysC_Cache::recvAtomic(PacketPtr pkt)
{
    const Tick delay(memPort.sendAtomic(pkt));
    assert(pkt->isResponse());
    return delay;
}

Tick
SysC_Cache::recvAtomicSnoop(PacketPtr pkt)
{
    return extPort->sendAtomicSnoop(pkt);
}

bool
SysC_Cache::recvTimingReq(PacketPtr pkt)
{
    // should always see a request
    assert(pkt->isRequest());
    return memPort.sendTimingReq(pkt);
}

bool
SysC_Cache::recvTimingResp(PacketPtr pkt)
{
    assert(0);
    return false;
    
//    // should always see responses
//    assert(pkt->isResponse());
//    return extPort.sendTimingResp(pkt);
}

void
SysC_Cache::recvTimingSnoopReq(PacketPtr pkt)
{
    assert(0);
//    extPort.sendTimingSnoopReq(pkt);
}

bool
SysC_Cache::recvTimingSnoopResp(PacketPtr pkt)
{
    return memPort.sendTimingSnoopResp(pkt);
}

void
SysC_Cache::recvRetrySnoopResp()
{
    assert(0);
//    extPort.sendRetrySnoopResp();
}

bool
SysC_Cache::isSnooping() const
{
    // check if the connected master port is snooping
    return extPort->isSnooping();
}

AddrRangeList
SysC_Cache::getAddrRanges() const
{
    // get the address ranges of the connected slave port
    return memPort.getAddrRanges();
}

void
SysC_Cache::recvReqRetry()
{
    assert(0);
//    extPort.sendRetryReq();
}

void
SysC_Cache::recvRespRetry()
{
    memPort.sendRetryResp();
}

void
SysC_Cache::recvRangeChange()
{
    extPort->sendRangeChange();
}




void 
SysC_Cache::handleLockErasure(ContextID ctx_id) 
{
    ThreadContext* ctx = system->getThreadContext(ctx_id);
    ctx->getCpuPtr()->wakeup(ctx->threadId());    
}

unsigned long long
SysC_Cache::readReg(unsigned int idx, unsigned int len) {
    return extPort->readReg(idx, len);
}







