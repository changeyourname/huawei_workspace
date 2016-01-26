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

#ifndef __SYSC_CACHE_HH__
#define __SYSC_CACHE_HH__

#include "mem/mem_object.hh"
#include "params/SysC_Cache.hh"


// TODO: documentation!!

class SysC_Cache : public MemObject
{

  public: // Construction & SimObject interfaces

    /** Parameters of communication monitor */
    typedef SysC_CacheParams Params;
    const Params* params() const
    { return reinterpret_cast<const Params*>(_params); }

    /**
     * Constructor based on the Python params
     *
     * @param params Python parameters
     */
    SysC_Cache(Params* params);

    void init() override;

  public: // MemObject interfaces
    BaseMasterPort &getMasterPort(const std::string &if_name,
                                  PortID idx = InvalidPortID) override;

    BaseSlavePort &getSlavePort(const std::string &if_name,
                                PortID idx = InvalidPortID) override;

  private:

    /**
     * Sender state class for the monitor so that we can annotate
     * packets with a transmit time and receive time.
     */
    class SysC_CacheSenderState : public Packet::SenderState
    {

      public:

        /**
         * Construct a new sender state and store the time so we can
         * calculate round-trip latency.
         *
         * @param _transmitTime Time of packet transmission
         */
        SysC_CacheSenderState(Tick _transmitTime)
            : transmitTime(_transmitTime)
        { }

        /** Destructor */
        ~SysC_CacheSenderState() { }

        /** Tick when request is transmitted */
        Tick transmitTime;

    };

    /**
     * This is the master port of the communication monitor. All recv
     * functions call a function in CommMonitor, where the
     * send function of the slave port is called. Besides this, these
     * functions can also perform actions for capturing statistics.
     */
    class MPort : public MasterPort
    {

      public:

        MPort(const std::string &_name, SysC_Cache &_owner)
            : MasterPort(_name, &_owner), owner(_owner)
        { }

      protected:

        void recvFunctionalSnoop(PacketPtr pkt)
        {
            owner.recvFunctionalSnoop(pkt);
        }

        Tick recvAtomicSnoop(PacketPtr pkt)
        {
            return owner.recvAtomicSnoop(pkt);
        }

        bool recvTimingResp(PacketPtr pkt)
        {
            return owner.recvTimingResp(pkt);
        }

        void recvTimingSnoopReq(PacketPtr pkt)
        {
            owner.recvTimingSnoopReq(pkt);
        }

        void recvRangeChange()
        {
            owner.recvRangeChange();
        }

        bool isSnooping() const
        {
            return owner.isSnooping();
        }

        void recvReqRetry()
        {
            owner.recvReqRetry();
        }

        void recvRetrySnoopResp()
        {
            owner.recvRetrySnoopResp();
        }

      private:

        SysC_Cache &owner;

    };

    /** Instance of master port, facing the memory side */
    MPort memPort;

    /**
     * This is the slave port of the communication monitor. All recv
     * functions call a function in CommMonitor, where the
     * send function of the master port is called. Besides this, these
     * functions can also perform actions for capturing statistics.
     */
    class SPort : public SlavePort
    {

      public:

        SPort(const std::string &_name, SysC_Cache &_owner)
            : SlavePort(_name, &_owner), owner(_owner)
        { }

      protected:

        void recvFunctional(PacketPtr pkt)
        {
            owner.recvFunctional(pkt);
        }

        Tick recvAtomic(PacketPtr pkt)
        {
            return owner.recvAtomic(pkt);
        }

        bool recvTimingReq(PacketPtr pkt)
        {
            return owner.recvTimingReq(pkt);
        }

        bool recvTimingSnoopResp(PacketPtr pkt)
        {
            return owner.recvTimingSnoopResp(pkt);
        }

        AddrRangeList getAddrRanges() const
        {
            return owner.getAddrRanges();
        }

        void recvRespRetry()
        {
            owner.recvRespRetry();
        }

      private:

        SysC_Cache &owner;

    };

    /** Instance of slave port, i.e. on the CPU side */
    SPort extPort;

    void recvFunctional(PacketPtr pkt);

    void recvFunctionalSnoop(PacketPtr pkt);

    Tick recvAtomic(PacketPtr pkt);

    Tick recvAtomicSnoop(PacketPtr pkt);

    bool recvTimingReq(PacketPtr pkt);

    bool recvTimingResp(PacketPtr pkt);

    void recvTimingSnoopReq(PacketPtr pkt);

    bool recvTimingSnoopResp(PacketPtr pkt);

    void recvRetrySnoopResp();

    AddrRangeList getAddrRanges() const;

    bool isSnooping() const;

    void recvReqRetry();

    void recvRespRetry();

    void recvRangeChange();
};

#endif //__MEM_COMM_MONITOR_HH__
