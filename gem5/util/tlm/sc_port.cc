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
//    assert(0);
//    CAUGHT_UP;
//    //SC_REPORT_INFO("transactor", "recvAtomic hasn't been tested much");
//    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

//    /* Prepare the transaction */
//    tlm::tlm_generic_payload * trans = mm.allocate();
//    trans->acquire();
//    packet2payload(packet, *trans);

//    /* Attach the packet pointer to the TLM transaction to keep track */
//    gem5Extension* extension = new gem5Extension(packet);
//    trans->set_auto_extension(extension);
//    
//    iSocket->b_transport(*trans, delay);                    
//        
//    trans->release();        
//    
//    return delay.value();

    owner.recvAtomic(packet);
}

/**
 * Similar to TLM's debug transport
 */
void
sc_transactor::recvFunctional(PacketPtr packet)
{
//    /* Prepare the transaction */
//    tlm::tlm_generic_payload * trans = mm.allocate();
//    trans->acquire();
//    packet2payload(packet, *trans);

//    /* Attach the packet pointer to the TLM transaction to keep track */
//    gem5Extension* extension = new gem5Extension(packet);
//    trans->set_auto_extension(extension);

//    /* Execute Debug Transport: */
//    unsigned int bytes = iSocket->transport_dbg(*trans);
//    if (bytes != trans->get_data_length()) {
//        SC_REPORT_FATAL("transactor","debug transport was not completed");
//    }

//    trans->release();

    owner.recvFunctional(packet);
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
//    CAUGHT_UP;

//    /* We should never get a second request after noting that a retry is
//     * required */
//    sc_assert(!needToSendRequestRetry);

//    // simply drop inhibited packets and clean evictions
//    if (packet->cacheResponding() || packet->cmd == MemCmd::CleanEvict) {
//        return true;
//    }

//    if (blockingResponse) {   
//        needToSendRequestRetry = true;
//        return false;
//    }

//    tlm::tlm_generic_payload * trans = mm.allocate();
//    trans->acquire();
//    packet2payload(packet, *trans);

//    /* Attach the packet pointer to the TLM transaction to keep track */
//    gem5Extension* extension = new gem5Extension(packet);
//    trans->set_auto_extension(extension);

//    /* Starting TLM non-blocking sequence (AT) Refer to IEEE1666-2011 SystemC
//     * Standard Page 507 for a visualisation of the procedure */
//    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
//    tlm::tlm_phase phase = tlm::BEGIN_REQ;
//    
//    iSocket->b_transport(*trans, delay);  
//    //packet->cacheDelay = delay.to_seconds()/1e-12;  

//    payloadEvent< sc_transactor > *pe = new payloadEvent< sc_transactor >
//        (*this, &sc_transactor::pec, "PEQ");    
//    phase = tlm::BEGIN_RESP;
//    pe->notify(*trans, phase, delay);
//    //TODO: somehow avoid this below serialization!!
//    blockingResponse = trans;

//    return true;

    return owner.recvTimingReq(packet);
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
        assert(0);
    }
    else if(phase == tlm::BEGIN_RESP)
    {
        CAUGHT_UP;
        gem5Extension *ext;
        trans.get_extension(ext);
        PacketPtr packet = ext->getPacket();
        if (blockingResponse == &trans) {
            blockingResponse = NULL;
        }

        sc_assert(!blockingResponse);

        bool need_retry;
        if (ext->sendResponseToGem5) {
            need_retry = !iSocket.sendTimingResp(packet);
        } else {
            need_retry = false;
        }

        if (need_retry) {
            blockingResponse = &trans;
        } else {
            trans.release();
        }
    } else if (phase == tlm::END_RESP) {
        assert(0);
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
    
    /* Did another request arrive while blocked, schedule a retry */
    if (needToSendRequestRetry) {
        needToSendRequestRetry = false;
        iSocket.sendRetryReq();
    }    
    
    // Release transaction with all the extensions
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
    SysC_Cache &owner_) :
    tlm::tlm_initiator_socket<>(systemc_name.c_str()),
    SysC_Cache::SPort(name_, owner_),
    iSocket(*this),
    blockingRequest(NULL),
    needToSendRequestRetry(false),
    blockingResponse(NULL)
{
    m_export.bind(*this);
}

class sc_transactorHandler : public SysC_Cache::Handler
{
  public:
    SysC_Cache::SPort *getExternalPort(const std::string &name,
        SysC_Cache &owner,
        const std::string &port_data)
    {
        // This will make a new initiatiator port
        return new sc_transactor(name, port_data, owner);
    }
};

void
registerSCPorts()
{
    SysC_Cache::registerHandler("tlm", new sc_transactorHandler);
}


SysC_Cache *
sc_transactor::getOwner() {
    return &owner;
}


//unsigned long long
//sc_transactor::readReg(unsigned int idx, unsigned int len) {
//    tlm::tlm_generic_payload trans;
//    unsigned char *ptr = new unsigned char[len];
//    
//    trans.set_command(tlm::TLM_READ_COMMAND);
//    trans.set_address(idx);
//    trans.set_data_length(len);
//    trans.set_data_ptr(ptr);
//        
//    iSocket->transport_dbg(trans);
//    sc_dt::uint64 ret = *((sc_dt::uint64 *) ptr);

//    delete ptr;
//    
//    return (unsigned long long) ret;
//}



}
