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

#include "base/trace.hh"
#include "mem/sysc_cache.hh"

SysC_Cache::SysC_Cache(Params* params)
    : MemObject(params),
      memPort(name() + "-memPort", *this),
      extPort(name() + "-extPort", *this)
{
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
    if (!extPort.isConnected() || !memPort.isConnected())
        fatal("SysC_Cache ports not connected on both sides.\n");
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
        return extPort;
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
    extPort.sendFunctionalSnoop(pkt);
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
    return extPort.sendAtomicSnoop(pkt);
}

bool
SysC_Cache::recvTimingReq(PacketPtr pkt)
{
    assert(0);
    return false;
    
//    // should always see a request
//    assert(pkt->isRequest());

//    // Store relevant fields of packet, because packet may be modified
//    // or even deleted when sendTiming() is called.
//    const ProbePoints::PacketInfo pkt_info(pkt);

//    const bool is_read = pkt->isRead();
//    const bool is_write = pkt->isWrite();
//    const bool expects_response(
//        pkt->needsResponse() && !pkt->cacheResponding());

//    // If a cache miss is served by a cache, a monitor near the memory
//    // would see a request which needs a response, but this response
//    // would not come back from the memory. Therefore we additionally
//    // have to check the cacheResponding flag
//    if (expects_response && !stats.disableLatencyHists) {
//        pkt->pushSenderState(new CommMonitorSenderState(curTick()));
//    }

//    // Attempt to send the packet
//    bool successful = masterPort.sendTimingReq(pkt);

//    // If not successful, restore the sender state
//    if (!successful && expects_response && !stats.disableLatencyHists) {
//        delete pkt->popSenderState();
//    }

//    if (successful) {
//        ppPktReq->notify(pkt_info);
//    }

//    if (successful && is_read) {
//        DPRINTF(CommMonitor, "Forwarded read request\n");

//        // Increment number of observed read transactions
//        if (!stats.disableTransactionHists) {
//            ++stats.readTrans;
//        }

//        // Get sample of burst length
//        if (!stats.disableBurstLengthHists) {
//            stats.readBurstLengthHist.sample(pkt_info.size);
//        }

//        // Sample the masked address
//        if (!stats.disableAddrDists) {
//            stats.readAddrDist.sample(pkt_info.addr & readAddrMask);
//        }

//        // If it needs a response increment number of outstanding read
//        // requests
//        if (!stats.disableOutstandingHists && expects_response) {
//            ++stats.outstandingReadReqs;
//        }

//        if (!stats.disableITTDists) {
//            // Sample value of read-read inter transaction time
//            if (stats.timeOfLastRead != 0) {
//                stats.ittReadRead.sample(curTick() - stats.timeOfLastRead);
//            }
//            stats.timeOfLastRead = curTick();

//            // Sample value of req-req inter transaction time
//            if (stats.timeOfLastReq != 0) {
//                stats.ittReqReq.sample(curTick() - stats.timeOfLastReq);
//            }
//            stats.timeOfLastReq = curTick();
//        }
//    } else if (successful && is_write) {
//        DPRINTF(CommMonitor, "Forwarded write request\n");

//        // Same as for reads
//        if (!stats.disableTransactionHists) {
//            ++stats.writeTrans;
//        }

//        if (!stats.disableBurstLengthHists) {
//            stats.writeBurstLengthHist.sample(pkt_info.size);
//        }

//        // Update the bandwidth stats on the request
//        if (!stats.disableBandwidthHists) {
//            stats.writtenBytes += pkt_info.size;
//            stats.totalWrittenBytes += pkt_info.size;
//        }

//        // Sample the masked write address
//        if (!stats.disableAddrDists) {
//            stats.writeAddrDist.sample(pkt_info.addr & writeAddrMask);
//        }

//        if (!stats.disableOutstandingHists && expects_response) {
//            ++stats.outstandingWriteReqs;
//        }

//        if (!stats.disableITTDists) {
//            // Sample value of write-to-write inter transaction time
//            if (stats.timeOfLastWrite != 0) {
//                stats.ittWriteWrite.sample(curTick() - stats.timeOfLastWrite);
//            }
//            stats.timeOfLastWrite = curTick();

//            // Sample value of req-to-req inter transaction time
//            if (stats.timeOfLastReq != 0) {
//                stats.ittReqReq.sample(curTick() - stats.timeOfLastReq);
//            }
//            stats.timeOfLastReq = curTick();
//        }
//    } else if (successful) {
//        DPRINTF(CommMonitor, "Forwarded non read/write request\n");
//    }

//    return successful;
}

bool
SysC_Cache::recvTimingResp(PacketPtr pkt)
{
    assert(0);
    return false;
//    
//    // should always see responses
//    assert(pkt->isResponse());

//    // Store relevant fields of packet, because packet may be modified
//    // or even deleted when sendTiming() is called.
//    const ProbePoints::PacketInfo pkt_info(pkt);

//    bool is_read = pkt->isRead();
//    bool is_write = pkt->isWrite();
//    Tick latency = 0;
//    CommMonitorSenderState* received_state =
//        dynamic_cast<CommMonitorSenderState*>(pkt->senderState);

//    if (!stats.disableLatencyHists) {
//        // Restore initial sender state
//        if (received_state == NULL)
//            panic("Monitor got a response without monitor sender state\n");

//        // Restore the sate
//        pkt->senderState = received_state->predecessor;
//    }

//    // Attempt to send the packet
//    bool successful = slavePort.sendTimingResp(pkt);

//    if (!stats.disableLatencyHists) {
//        // If packet successfully send, sample value of latency,
//        // afterwards delete sender state, otherwise restore state
//        if (successful) {
//            latency = curTick() - received_state->transmitTime;
//            DPRINTF(CommMonitor, "Latency: %d\n", latency);
//            delete received_state;
//        } else {
//            // Don't delete anything and let the packet look like we
//            // did not touch it
//            pkt->senderState = received_state;
//        }
//    }

//    if (successful) {
//        ppPktResp->notify(pkt_info);
//    }

//    if (successful && is_read) {
//        // Decrement number of outstanding read requests
//        DPRINTF(CommMonitor, "Received read response\n");
//        if (!stats.disableOutstandingHists) {
//            assert(stats.outstandingReadReqs != 0);
//            --stats.outstandingReadReqs;
//        }

//        if (!stats.disableLatencyHists) {
//            stats.readLatencyHist.sample(latency);
//        }

//        // Update the bandwidth stats based on responses for reads
//        if (!stats.disableBandwidthHists) {
//            stats.readBytes += pkt_info.size;
//            stats.totalReadBytes += pkt_info.size;
//        }

//    } else if (successful && is_write) {
//        // Decrement number of outstanding write requests
//        DPRINTF(CommMonitor, "Received write response\n");
//        if (!stats.disableOutstandingHists) {
//            assert(stats.outstandingWriteReqs != 0);
//            --stats.outstandingWriteReqs;
//        }

//        if (!stats.disableLatencyHists) {
//            stats.writeLatencyHist.sample(latency);
//        }
//    } else if (successful) {
//        DPRINTF(CommMonitor, "Received non read/write response\n");
//    }
//    return successful;
}

void
SysC_Cache::recvTimingSnoopReq(PacketPtr pkt)
{
    assert(0);
//    slavePort.sendTimingSnoopReq(pkt);
}

bool
SysC_Cache::recvTimingSnoopResp(PacketPtr pkt)
{
    assert(0);
    return false;
    
//    return masterPort.sendTimingSnoopResp(pkt);
}

void
SysC_Cache::recvRetrySnoopResp()
{
    extPort.sendRetrySnoopResp();
}

bool
SysC_Cache::isSnooping() const
{
    // check if the connected master port is snooping
    return extPort.isSnooping();
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
    extPort.sendRetryReq();
}

void
SysC_Cache::recvRespRetry()
{
    memPort.sendRetryResp();
}

void
SysC_Cache::recvRangeChange()
{
    extPort.sendRangeChange();
}








