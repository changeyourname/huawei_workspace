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
 */

#include "sc_target.hh"
#include "sc_port.hh"
#include "sc_ext.hh"

using namespace sc_core;
using namespace std;

uint64_t Target::prev_req_cnt = 0;

Target::Target(sc_core::sc_module_name name,
    bool debug,
    unsigned long long int size,
    unsigned int offset, unsigned char *mem,
    SysC_Cache *gem5_master) :
    socket("socket"),
    transaction_in_progress(0),
    response_in_progress(false),
    next_response_pending(0),
    end_req_pending(0),
    m_peq(this, &Target::peq_cb),
    debug(debug),
    size(size),
    offset(offset),
    m_mem(mem),
    gem5_master(gem5_master),
    req_count(0)
{
    /* Register tlm transport functions */
    socket.register_b_transport(this, &Target::b_transport);
    socket.register_transport_dbg(this, &Target::transport_dbg);
    socket.register_nb_transport_fw(this, &Target::nb_transport_fw);


    SC_METHOD(execute_transaction_process);
    sensitive << target_done_event;
    dont_initialize();
}



// Add load-locked to tracking list.  Should only be called if the
// operation is a load and the LLSC flag is set.
void
Target::trackLoadLocked(PacketPtr pkt)
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



// Called on *writes* only... both regular stores and
// store-conditional operations.  Check for conventional stores which
// conflict with locked addresses, and for success/failure of store
// conditionals.
bool
Target::checkLockedAddrList(PacketPtr pkt)
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
                         
//                gem5_master->handleLockErasure(i->contextId);
                
                i = lockedAddrList.erase(i);
            } else {
                i++;
            }
        }
    }

    return allowStore;
}



void
Target::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
    //cout << sc_time_stamp() << ": " << name() << ": addr=0x" << hex <<trans.get_address() << dec << endl;
       
    gem5Extension *ext;
    trans.get_extension(ext);
    PacketPtr packet = ext->getPacket();
/*    
    if ((prev_req_cnt >= packet->req_count) && (packet->req_count!=0)) {
        assert(0);
    }
    prev_req_cnt = packet->req_count;*/

    
    /* Execute the read or write commands */
    if (packet->cacheResponding() || packet->cmd==MemCmd::CleanEvict
        || packet->cmd==MemCmd::WritebackClean) {
        return;
    } else {
        if (packet->cmd == MemCmd::SwapReq) {
            SC_REPORT_FATAL("transactor", "SwapReq not supported");
        } else if (packet->isRead()) {
            if (packet->isLLSC()) {
                trackLoadLocked(packet);
            }
        } else if (packet->isInvalidate()) {
            // do nothing
            assert(0);
        } else if (packet->isWrite()) {
            Request *req = packet->req;
            if (lockedAddrList.empty()) {
                bool isLLSC = packet->isLLSC();
                if (isLLSC) {
                    req->setExtraData(0);
                    return;
                }
            } else {
                if (!checkLockedAddrList(packet)) {
                    return;
                }
            }            
        } else {
            SC_REPORT_FATAL("transactor", "Typo of request not supported");
        }
    }

    execute_transaction(trans);
    
    if (packet->needsResponse()) {
        packet->makeResponse();
        ext->sendResponseToGem5 = true;
    }    
    delay += sc_core::sc_time(500, sc_core::SC_PS);        
}

unsigned int
Target::transport_dbg(tlm::tlm_generic_payload& trans)
{
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() - offset;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();

    unsigned char *mem_array_ptr = m_mem + adr;

    /* Load / Store the access: */
    if ( cmd == tlm::TLM_READ_COMMAND ) {
        if(debug) {
            SC_REPORT_INFO("target", "tlm::TLM_READ_COMMAND");
        }
        std::memcpy(ptr, mem_array_ptr, len);
    } else if ( cmd == tlm::TLM_WRITE_COMMAND ) {
        if(debug) {
            SC_REPORT_INFO("target", "tlm::TLM_WRITE_COMMAND");
        }
        std::memcpy(mem_array_ptr, ptr, len);
    }

    return len;
}


/* TLM-2 non-blocking transport method */
tlm::tlm_sync_enum Target::nb_transport_fw(tlm::tlm_generic_payload& trans,
                                           tlm::tlm_phase& phase,
                                           sc_time& delay)
{
    /* Queue the transaction until the annotated time has elapsed */
    m_peq.notify(trans, phase, delay);
    return tlm::TLM_ACCEPTED;
}

void
Target::peq_cb(tlm::tlm_generic_payload& trans,
               const tlm::tlm_phase& phase)
{
    sc_time delay;

    if(phase == tlm::BEGIN_REQ) {
        if(debug) SC_REPORT_INFO("target", "tlm::BEGIN_REQ");

        /* Increment the transaction reference count */
        trans.acquire();

        if ( !transaction_in_progress ) {
            send_end_req(trans);
        } else {
            /* Put back-pressure on initiator by deferring END_REQ until
             * pipeline is clear */
            end_req_pending = &trans;
        }
    } else if (phase == tlm::END_RESP) {
        /* On receiving END_RESP, the target can release the transaction and
         * allow other pending transactions to proceed */
        if (!response_in_progress) {
            SC_REPORT_FATAL("TLM-2", "Illegal transaction phase END_RESP"
                            "received by target");
        }

        transaction_in_progress = 0;

        /* Target itself is now clear to issue the next BEGIN_RESP */
        response_in_progress = false;
        if (next_response_pending) {
            send_response( *next_response_pending );
            next_response_pending = 0;
        }

        /* ... and to unblock the initiator by issuing END_REQ */
        if (end_req_pending) {
            send_end_req( *end_req_pending );
            end_req_pending = 0;
        }

    } else /* tlm::END_REQ or tlm::BEGIN_RESP */ {
            SC_REPORT_FATAL("TLM-2", "Illegal transaction phase received by"
                            "target");
    }
}

void
Target::send_end_req(tlm::tlm_generic_payload& trans)
{
    tlm::tlm_phase bw_phase;
    sc_time delay;

    /* Queue the acceptance and the response with the appropriate latency */
    bw_phase = tlm::END_REQ;

    delay = sc_time(10, SC_NS); // Accept delay
// for 1 phase protocol
// delay = sc_core::SC_ZERO_TIME;

    tlm::tlm_sync_enum status;
    status = socket->nb_transport_bw(trans, bw_phase, delay);

    /* Ignore return value;
     * initiator cannot terminate transaction at this point
     * Queue internal event to mark beginning of response: */

    delay = delay + sc_time(40, SC_NS); // Latency
// for 1 phase protocol, comment above

    target_done_event.notify(delay);

    assert(transaction_in_progress == 0);
    transaction_in_progress = &trans;
}

void
Target::execute_transaction_process()
{
    /* Execute the read or write commands */
    execute_transaction( *transaction_in_progress );

    /* Target must honor BEGIN_RESP/END_RESP exclusion rule; i.e. must not
     * send BEGIN_RESP until receiving previous END_RESP or BEGIN_REQ */
    if (response_in_progress) {
        /* Target allows only two transactions in-flight */
        if (next_response_pending) {
            SC_REPORT_FATAL("TLM-2", "Attempt to have two pending responses"
                            "in target");
        }
        next_response_pending = transaction_in_progress;
    } else {
        send_response( *transaction_in_progress );
    }
}

void
Target::execute_transaction(tlm::tlm_generic_payload& trans)
{
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() - offset;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    if ( byt != 0 ) {
        cout << "Byte Error" << endl;
        trans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
        return;
    }

    //if ( len > 4 || wid < len ) {
    //    cout << "Burst Error len=" << len << " wid=" << wid << endl;
    //    trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
    //    return;
    //}

    unsigned char *mem_array_ptr = m_mem + adr;

    /* Load / Store the access: */
    if ( cmd == tlm::TLM_READ_COMMAND ) {
        if(debug) {
            SC_REPORT_INFO("target", "tlm::TLM_READ_COMMAND");
        }
        std::memcpy(ptr, mem_array_ptr, len);
    } else if ( cmd == tlm::TLM_WRITE_COMMAND ) {
        if(debug) {
            SC_REPORT_INFO("target", "tlm::TLM_WRITE_COMMAND");
        }
        std::memcpy(mem_array_ptr, ptr, len);
    }

    trans.set_response_status( tlm::TLM_OK_RESPONSE );    
}

void
Target::send_response(tlm::tlm_generic_payload& trans)
{
    tlm::tlm_sync_enum status;
    tlm::tlm_phase bw_phase;
    sc_time delay;

    response_in_progress = true;
    bw_phase = tlm::BEGIN_RESP;
    delay = sc_time(10, SC_NS);
// for 1-phase protocol
    delay = sc_core::SC_ZERO_TIME;
    status = socket->nb_transport_bw( trans, bw_phase, delay );

    if (status == tlm::TLM_UPDATED) {
        /* The timing annotation must be honored */
        m_peq.notify(trans, bw_phase, delay);
    } else if (status == tlm::TLM_COMPLETED) {
        /* The initiator has terminated the transaction */
        transaction_in_progress = 0;
        response_in_progress = false;
    }
    trans.release();
}



unsigned int Target::get_reqCount() {
    return req_count;
}

