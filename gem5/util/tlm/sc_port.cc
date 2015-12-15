/*
 * Copyright (c) 2015, University of Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Matthias Jung
 *          Abdul Mutaal Ahmad
 */

#include <cctype>
#include <iomanip>
#include <sstream>

#include "debug/ExternalPort.hh"
#include "sc_ext.hh"
#include "sc_mm.hh"
#include "sc_port.hh"
#include "cpu/thread_context.hh"
#include "sim/system.hh"

namespace Gem5SystemC
{

/**
 * Instantiate a tlm memory manager that takes care about all the
 * tlm transactions in the system
 */
MemoryManager mm;

/**
 * Convert a gem5 packet to a TLM payload by copying all the relevant
 * information to a previously allocated tlm payload
 */
void
packet2payload(PacketPtr packet, tlm::tlm_generic_payload &trans)
{
    trans.set_address(packet->getAddr());

    /* Check if this transaction was allocated by mm */
    sc_assert(trans.has_mm());

    unsigned int size = packet->getSize();
    unsigned char *data = packet->getPtr<unsigned char>();

    trans.set_data_length(size);
    trans.set_streaming_width(size);
    trans.set_data_ptr(data);

    if (packet->isRead()) {
        trans.set_command(tlm::TLM_READ_COMMAND);
    }
    else if (packet->isInvalidate()) {
        /* Do nothing */
    } else if (packet->isWrite()) {
        trans.set_command(tlm::TLM_WRITE_COMMAND);
    } else {
        SC_REPORT_FATAL("transactor", "No R/W packet");
    }
}

/**
 * Similar to TLM's blocking transport (LT)
 */
Tick
sc_transactor::recvAtomic(PacketPtr packet)
{
    CAUGHT_UP;
    //SC_REPORT_INFO("transactor", "recvAtomic hasn't been tested much");       

    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;   
    /* Prepare the transaction */
    tlm::tlm_generic_payload * trans = mm.allocate();
    trans->acquire();
    packet2payload(packet, *trans);

    /* Attach the packet pointer to the TLM transaction to keep track */
    gem5Extension* extension = new gem5Extension(packet);
    trans->set_auto_extension(extension);

    /* Execute b_transport: */
    if (packet->memInhibitAsserted() || packet->cmd == MemCmd::CleanEvict || packet->cmd == MemCmd::WritebackClean) {
        return delay.value();
    } else {
        if (packet->cmd == MemCmd::SwapReq) {
            SC_REPORT_FATAL("transactor", "SwapReq not supported");
        } else if (packet->isRead()) {
            if (packet->isLLSC()) {
                trackLoadLocked(packet);
            }
            iSocket->b_transport(*trans, delay);
        } else if (packet->isInvalidate()) {
            // do nothing
        } else if (packet->isWrite()) {
            Request *req = packet->req;
            if (lockedAddrList.empty()) {
                bool isLLSC = packet->isLLSC();
                if (isLLSC) {
                    req->setExtraData(0);
                    return true;
                }
            } else {
                if (!checkLockedAddrList(packet)) {
                    return true;
                }
            }
            
            iSocket->b_transport(*trans, delay);
        } else {
            SC_REPORT_FATAL("transactor", "Typo of request not supported");
        }   
    }

    if (packet->needsResponse()) {
        packet->makeResponse();
    }

    trans->release();

    return delay.value();
}

/**
 * Similar to TLM's debug transport
 */
void
sc_transactor::recvFunctional(PacketPtr packet)
{
    /* Prepare the transaction */
    tlm::tlm_generic_payload * trans = mm.allocate();
    trans->acquire();
    packet2payload(packet, *trans);

    /* Attach the packet pointer to the TLM transaction to keep track */
    gem5Extension* extension = new gem5Extension(packet);
    trans->set_auto_extension(extension);

    /* Execute Debug Transport: */
    unsigned int bytes = iSocket->transport_dbg(*trans);
    if (bytes != trans->get_data_length()) {
        SC_REPORT_FATAL("transactor","debug transport was not completed");
    }

    trans->release();
}

bool
sc_transactor::recvTimingSnoopResp(PacketPtr packet)
{
    /* Snooping should be implemented with tlm_dbg_transport */
    SC_REPORT_FATAL("transactor","unimplemented func.: recvTimingSnoopResp");
    return false;
}

void
sc_transactor::recvFunctionalSnoop(PacketPtr packet)
{
    /* Snooping should be implemented with tlm_dbg_transport */
    SC_REPORT_FATAL("transactor","unimplemented func.: recvFunctionalSnoop");
}

/**
 *  Similar to TLM's non-blocking transport (AT)
 */
bool
sc_transactor::recvTimingReq(PacketPtr packet)
{
    CAUGHT_UP;

    /* We should never get a second request after noting that a retry is
     * required */
    sc_assert(!needToSendRequestRetry);

    // simply drop inhibited packets and clean evictions
    if (packet->memInhibitAsserted()) {
        return true;
    }
    if (packet->cmd == MemCmd::CleanEvict || packet->cmd == MemCmd::WritebackClean) {
        return true;
    }           
    
    //assert(AddrRange(packet->getAddr(), packet->getAddr() + (packet->getSize() - 1)).isSubset(range)); 
        
    /* Remember if a request comes in while we're blocked so that a retry
     * can be sent to gem5 */
    /*if (blockingRequest) {
        needToSendRequestRetry = true;
        return false;
    }*/
    

    /*  NOTE: normal tlm is blocking here. But in our case we return false
     *  and tell gem5 when a retry can be done. This is the main difference
     *  in the protocol:
     *  if(requestInProgress)
     *  {
     *      wait(endRequestEvent);
     *  }
     *  requestInProgress = trans;
    */
    
    
    if (packet->cmd == MemCmd::SwapReq) {
        assert(0);
    } else if (packet->isRead()) {
        assert(!packet->isWrite());
        if (packet->isLLSC()) {
            trackLoadLocked(packet);
        }
        // forward this request to SysC memory        
    } else if (packet->isInvalidate()) {
        return true;
    } else if (packet->isWrite()) {
        Request *req = packet->req;
        if (lockedAddrList.empty()) {
            // no locked addrs: nothing to check, sotre_conditional fails
            bool isLLSC = packet->isLLSC();
            if (isLLSC) {
                req->setExtraData(0);
                return true;
            }
        } else {
            if (!checkLockedAddrList(packet)) {
                return true;
            }
        }
    }


    // if the previous transaction's response has not been sent Ok then
    // we shouldn't forward any new request to memory
    if (blockingResponse) {
        needToSendRequestRetry = true;

        // send retry request so as to retry the previous transaction                
        return false;
    }
    
    // forwarding the request to SysC memory module  
    

    /* Prepare the transaction */
    tlm::tlm_generic_payload * trans = mm.allocate();
    trans->acquire();
    packet2payload(packet, *trans);

    /* Attach the packet pointer to the TLM transaction to keep track */
    gem5Extension* extension = new gem5Extension(packet);
    trans->set_auto_extension(extension);

    /* Starting TLM non-blocking sequence (AT) Refer to IEEE1666-2011 SystemC
     * Standard Page 507 for a visualisation of the procedure */
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    tlm::tlm_phase phase = tlm::BEGIN_REQ;
    tlm::tlm_sync_enum status;    
    
    status = iSocket->nb_transport_fw(*trans, phase, delay);
    
    //assert(status == tlm::TLM_COMPLETED);
    
    /* Check returned value: */
    if(status == tlm::TLM_ACCEPTED) {
        sc_assert(phase == tlm::BEGIN_REQ);
        /* Accepted but is now blocking until END_REQ (exclusion rule)*/
        blockingRequest = trans;    
    } else if(status == tlm::TLM_UPDATED) {
        /* The Timing annotation must be honored: */
        sc_assert(phase == tlm::END_REQ || phase == tlm::BEGIN_RESP);

        payloadEvent<sc_transactor> * pe;
        pe = new payloadEvent<sc_transactor>(*this,
            &sc_transactor::pec, "PEQ");
        pe->notify(*trans, phase, delay);
    } else if(status == tlm::TLM_COMPLETED) {
        /* Transaction is over nothing has do be done. */
        sc_assert(phase == tlm::END_RESP);
        
        payloadEvent<sc_transactor> * pe;
        pe = new payloadEvent<sc_transactor>(*this,
            &sc_transactor::pec, "PEQ");
        pe->notify(*trans, phase, delay);
    }

    return true;
}


// Called on *writes* only... both regular stores and
// store-conditional operations.  Check for conventional stores which
// conflict with locked addresses, and for success/failure of store
// conditionals.
bool
sc_transactor::checkLockedAddrList(PacketPtr pkt)
{
    Request *req = pkt->req;
    Addr paddr = LockedAddr::mask(req->getPaddr());
    bool isLLSC = pkt->isLLSC();
    
    bool allowStore = !isLLSC;

    // Iterate over list.  Note that there could be multiple matching records,
    // as more than one context could have done a load locked to this location.
    // Only remove records when we succeed in finding a record for (xc, addr);
    // then, remove all records with this address.  Failed store-conditionals do
    // not blow unrelated reservations.
    std::list<LockedAddr>::iterator i = lockedAddrList.begin();

    if (isLLSC) {
        while (i != lockedAddrList.end()) {
            if (i->addr == paddr && i->matchesContext(req)) {
                // it's a store conditional, and as far as the memory system can
                // tell, the requesting context's lock is still valid.
                /*DPRINTF(LLSC, "StCond success: context %d addr %#x\n",
                        req->contextId(), paddr);*/
                allowStore = true;
                break;
            }
            // If we didn't find a match, keep searching!  Someone else may well
            // have a reservation on this line here but we may find ours in just
            // a little while.
            i++;
        }
        req->setExtraData(allowStore ? 1 : 0);
    }

    // LLSCs that succeeded AND non-LLSC stores both fall into here:
    if (allowStore) {
        // We write address paddr.  However, there may be several entries with a
        // reservation on this address (for other contextIds) and they must all
        // be removed.
        i = lockedAddrList.begin();
        while (i != lockedAddrList.end()) {
            if (i->addr == paddr) {
                /*DPRINTF(LLSC, "Erasing lock record: context %d addr %#x\n",
                        i->contextId, paddr);*/
                        
                // For ARM, a spinlock would typically include a Wait
                // For Event (WFE) to conserve energy. The ARMv8
                // architecture specifies that an event is
                // automatically generated when clearing the exclusive
                // monitor to wake up the processor in WFE.          
                // ThreadContext* ctx = owner.getSystem()->getThreadContext(i->contextId);
                // ctx->getCpuPtr()->wakeup(ctx->threadId());                  
                
                // FIXME: enable above!!
                // right now not getting the true system instance in owner.getSystem()
                // can explore why we are not getting the true system instance even though 
                // its address is similar to the one that is actually created               

                // i think we are fairly OK with non-LLSC if we ignore this as this would have
                // been handled in locked_mem.hh as without caches, each SMP-core request 
                // is being snooped by all others before issuing it to the memory
                
                // But for LLSC succeeding stores, is waking up that CPU necessary??
                // can we also do this in locked_mem.hh???
                
                i = lockedAddrList.erase(i);
            } else {
                i++;
            }
        }
    }

    return allowStore;
}


// Add load-locked to tracking list.  Should only be called if the
// operation is a load and the LLSC flag is set.
void
sc_transactor::trackLoadLocked(PacketPtr pkt)
{
    Request *req = pkt->req;
    Addr paddr = LockedAddr::mask(req->getPaddr());

    // first we check if we already have a locked addr for this
    // xc.  Since each xc only gets one, we just update the
    // existing record with the new address.
    std::list<LockedAddr>::iterator i;

    for (i = lockedAddrList.begin(); i != lockedAddrList.end(); ++i) {
        if (i->matchesContext(req)) {
            /*DPRINTF(LLSC, "Modifying lock record: context %d addr %#x\n",
                    req->contextId(), paddr);*/
            i->addr = paddr;
            return;
        }
    }

    // no record for this xc: need to allocate a new one
    /*DPRINTF(LLSC, "Adding lock record: context %d addr %#x\n",
            req->contextId(), paddr);*/
    lockedAddrList.push_front(LockedAddr(req));
}



void
sc_transactor::pec(
    sc_transactor::payloadEvent<sc_transactor> * pe,
    tlm::tlm_generic_payload& trans,
    const tlm::tlm_phase& phase)
{
    sc_time delay;
    
    if(phase == tlm::END_REQ ||
            &trans == blockingRequest && phase == tlm::BEGIN_RESP) {
        sc_assert(&trans == blockingRequest);
        blockingRequest = NULL;

        /* Did another request arrive while blocked, schedule a retry */
        if (needToSendRequestRetry) {
            needToSendRequestRetry = false;
           iSocket.sendRetryReq();
        }
    }
    else if(phase == tlm::BEGIN_RESP)
    {                    
        CAUGHT_UP;        
        PacketPtr packet = gem5Extension::getExtension(trans).getPacket();

        sc_assert(!blockingResponse);

        bool need_retry;
        if (packet->needsResponse()) {
            packet->makeResponse();
            need_retry = !iSocket.sendTimingResp(packet);
        } else {
            need_retry = false;
        }

        if (need_retry) {
            blockingResponse = &trans;
        } else {
            if (phase == tlm::BEGIN_RESP) {
                /* Send END_RESP and we're finished: */
                tlm::tlm_phase fw_phase = tlm::END_RESP;
                sc_time delay = SC_ZERO_TIME;
                iSocket->nb_transport_fw(trans, fw_phase, delay);
                /* Release the transaction with all the extensions */
                trans.release();
            }
        }
    } else if (phase == tlm::END_RESP) {
        CAUGHT_UP;       
        PacketPtr packet = gem5Extension::getExtension(trans).getPacket();
         
        sc_assert(!blockingResponse);        

        bool need_retry;
        if (packet->needsResponse()) {
            packet->makeResponse();
            need_retry = !iSocket.sendTimingResp(packet);
        } else {
            need_retry = false;
        }
        
        if (need_retry) {
            blockingResponse = &trans;
        } else {                                  
            trans.release();        
        }
    } else {
        SC_REPORT_FATAL("transactor", "Invalid protocol phase in pec");
    }
    delete pe;
}

void
sc_transactor::recvRespRetry()
{
    CAUGHT_UP;

    /* Retry a response */
    sc_assert(blockingResponse);

    tlm::tlm_generic_payload *trans = blockingResponse;
    blockingResponse = NULL;

    PacketPtr packet = gem5Extension::getExtension(trans).getPacket();

    bool need_retry = !iSocket.sendTimingResp(packet);

    sc_assert(!need_retry);

    /*sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    tlm::tlm_phase phase = tlm::END_RESP;
    iSocket->nb_transport_fw(*trans, phase, delay);*/
    // Release transaction with all the extensions
    
    if (needToSendRequestRetry) {
        needToSendRequestRetry = false;
        iSocket.sendRetryReq();
    }    
    
    
    trans->release();
}

tlm::tlm_sync_enum
sc_transactor::nb_transport_bw(tlm::tlm_generic_payload& trans,
    tlm::tlm_phase& phase,
    sc_core::sc_time& delay)
{
    payloadEvent<sc_transactor> * pe;
    pe = new payloadEvent<sc_transactor>(*this, &sc_transactor::pec, "PE");
    pe->notify(trans, phase, delay);
    return tlm::TLM_ACCEPTED;
}

void
sc_transactor::invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
     sc_dt::uint64 end_range)
{
    SC_REPORT_FATAL("transactor", "unimpl. func: invalidate_direct_mem_ptr");
}

sc_transactor::sc_transactor(const std::string &name_,
    const std::string &systemc_name,
    ExternalSlave &owner_) :
    tlm::tlm_initiator_socket<>(systemc_name.c_str()),
    ExternalSlave::Port(name_, owner_),
    iSocket(*this),
    blockingRequest(NULL),
    needToSendRequestRetry(false),
    blockingResponse(NULL)
{
    m_export.bind(*this);
}

class sc_transactorHandler : public ExternalSlave::Handler
{
  public:
    ExternalSlave::Port *getExternalPort(const std::string &name,
        ExternalSlave &owner,
        const std::string &port_data)
    {
        // This will make a new initiatiator port
        return new sc_transactor(name, port_data, owner);
    }
};

void
registerSCPorts()
{
    ExternalSlave::registerHandler("tlm", new sc_transactorHandler);
}

}
