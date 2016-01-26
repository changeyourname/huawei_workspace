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

class System;

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

    BaseMasterPort &getMasterPort(const std::string &if_name,
                                  PortID idx = InvalidPortID) override;

    BaseSlavePort &getSlavePort(const std::string &if_name,
                                PortID idx = InvalidPortID) override;
                                
/** Derive from this class to create an external port interface */
    class SPort : public SlavePort
    {
      protected:
        SysC_Cache &owner;

      public:
        SPort(const std::string &name_,
            SysC_Cache &owner_) :
            SlavePort(name_, &owner_), owner(owner_)
        { }

        ~SPort() { }

        /** Any or all of recv... can be overloaded to provide the port's
         *  functionality */

        AddrRangeList getAddrRanges() const;   
        virtual unsigned long long readReg(unsigned int idx, unsigned int len) {return 0;}             
    };        
    
    
    /* Handlers are specific to *types* of port not specific port
     * instantiations.  A handler will typically build a bridge to the
     * external port from gem5 and provide gem5 with a SlavePort that can be
     * bound to for each call to Handler::getExternalPort.*/
    class Handler
    {
      public:
        /** Create or find an external port which can be bound.  Returns
         *  NULL on failure */
        virtual SPort *getExternalPort(
            const std::string &name, SysC_Cache &owner,
            const std::string &port_data) = 0;
    };  
    
    /** Register a handler which can provide ports with port_type ==
     *  handler_name */
    static void registerHandler(const std::string &handler_name,
        Handler *handler);         
    
                                    

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
    
    void handleLockErasure(ContextID ctx_id);
    
    unsigned long long readReg(unsigned int idx, unsigned int len);    
    
  protected:
    System *system;
      
    SPort *extPort;  
    /** Name of the bound port.  This will be name() + ".port" */
    std::string portName;

    /** Key to select a port handler */
    std::string portType;

    /** Handler-specific port configuration */
    std::string portData;

    /** The Range of addresses supported by the devices on the external
     *  side of this port */
    AddrRangeList addrRanges;
    
    /** Registered handlers.  Handlers are chosen using the port_type
     *  parameter on ExternalSlaves.  port_types form a global namespace
     *  across the simulation and so handlers are registered into a global
     *  structure */
    static std::map<std::string, Handler *> portHandlers;   
};

#endif //__MEM_COMM_MONITOR_HH__






















