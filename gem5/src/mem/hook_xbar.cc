/*
 * Copyright (c) 2011-2015 ARM Limited
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
 * Copyright (c) 2006 The Regents of The University of Michigan
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
 * Authors: Ali Saidi
 *          Andreas Hansson
 *          William Wang
 */

/**
 * @file
 * Definition of a hook crossbar object.
 */

#include "base/misc.hh"
#include "base/trace.hh"
#include "debug/HookXBar.hh"
#include "debug/XBar.hh"
#include "mem/hook_xbar.hh"

HookXBar::HookXBar(const HookXBarParams *p)
    : BaseXBar(p)
{
    // create the ports based on the size of the master and slave
    // vector ports, and the presence of the default port, the ports
    // are enumerated starting from zero
    for (int i = 0; i < p->port_master_connection_count; ++i) {
        std::string portName = csprintf("%s.master[%d]", name(), i);
        MasterPort* bp = new HookXBarMasterPort(portName, *this, i);
        masterPorts.push_back(bp);
        reqLayers.push_back(new ReqLayer(*bp, *this,
                                         csprintf(".reqLayer%d", i)));
    }   

    // see if we have a default slave device connected and if so add
    // our corresponding master port
    if (p->port_default_connection_count) {
        defaultPortID = masterPorts.size();              
        std::string portName = name() + ".default";
        MasterPort* bp = new HookXBarMasterPort(portName, *this,
                                                      defaultPortID);
        masterPorts.push_back(bp);
        reqLayers.push_back(new ReqLayer(*bp, *this, csprintf(".reqLayer%d",
                                                              defaultPortID)));
    }
    
    std::string portName = name() + ".hook";
    HookPort = new HookXBarMasterPort(portName, *this, masterPorts.size());
    masterPorts.push_back(HookPort);
    //reqLayers.push_back(new ReqLayer(HookPort, *this, csprintf(".reqLayer%d", 
    //                                 masterPorts.size())));
    
    
    // create the slave ports, once again starting at zero
    for (int i = 0; i < p->port_slave_connection_count; ++i) {
        std::string portName = csprintf("%s.slave[%d]", name(), i);
        QueuedSlavePort* bp = new HookXBarSlavePort(portName, *this, i);
        slavePorts.push_back(bp);
        respLayers.push_back(new RespLayer(*bp, *this,
                                           csprintf(".respLayer%d", i)));
    }

    clearPortCache();
}

HookXBar::~HookXBar()
{
    for (auto l: reqLayers)
        delete l;
    for (auto l: respLayers)
        delete l;
}

bool
HookXBar::recvTimingReq(PacketPtr pkt, PortID slave_port_id)
{
    // not supported
    assert(0);
    return false;
}

bool
HookXBar::recvTimingResp(PacketPtr pkt, PortID master_port_id)
{
    // not supported
    assert(0);
    return false;
}

void
HookXBar::recvReqRetry(PortID master_port_id)
{
    // not supported
    assert(0);
}

Tick
HookXBar::recvAtomic(PacketPtr pkt, PortID slave_port_id)
{
    DPRINTF(HookXBar, "recvAtomic: packet src %s addr 0x%x cmd %s\n",
            slavePorts[slave_port_id]->name(), pkt->getAddr(),
            pkt->cmdString());

    // determine the destination port
    PortID master_port_id = findPort(pkt->getAddr());          

    Tick response_latency;  
         
    // forward the request to hook port so as to maybe pick it up in SystemC world    
    response_latency = HookPort->sendAtomic(pkt);  
      
    // forward the request to the appropriate destination (actual master)
    response_latency = masterPorts[master_port_id]->sendAtomic(pkt);    

    // @todo: Not setting first-word time
    pkt->payloadDelay = response_latency;
    return response_latency;
}

void
HookXBar::recvFunctional(PacketPtr pkt, PortID slave_port_id)
{
    if (!pkt->isPrint()) {
        // don't do DPRINTFs on PrintReq as it clutters up the output
        DPRINTF(HookXBar,
                "recvFunctional: packet src %s addr 0x%x cmd %s\n",
                slavePorts[slave_port_id]->name(), pkt->getAddr(),
                pkt->cmdString());
    }

    // since our slave ports are queued ports we need to check them as well
    for (const auto& p : slavePorts) {
        // if we find a response that has the data, then the
        // downstream caches/memories may be out of date, so simply stop
        // here
        if (p->checkFunctional(pkt)) {
            if (pkt->needsResponse())
                pkt->makeResponse();
            return;
        }
    }

    // determine the destination port
    PortID dest_id = findPort(pkt->getAddr());

    // forward the request to the appropriate destination
    masterPorts[dest_id]->sendFunctional(pkt);
}

HookXBar*
HookXBarParams::create()
{
    return new HookXBar(this);
}












