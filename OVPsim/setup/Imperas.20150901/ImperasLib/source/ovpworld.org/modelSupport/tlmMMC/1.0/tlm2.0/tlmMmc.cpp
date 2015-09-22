/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include "ovpworld.org/modelSupport/tlmMMC/1.0/tlm2.0/tlmMmc.hpp"
#include "ovpworld.org/modelSupport/tlmInitiatorExtension/1.0/tlm2.0/tlmInitiatorExtension.hpp"

#define CONCAT2(s1,s2) ((string) s1 + "_" + (string) s2).c_str()

//
//////////////////////////////// SLAVE PORT ///////////////////////////////////
//
icmMMCSlavePort::icmMMCSlavePort(icmMMC *mmc, const char *name, Addr bytes)
  : socket   (name)
  , m_bus    ("sp_bus", CONCAT2(mmc->m_name, name), addrBits(bytes-1))
  , m_name   (name)
  , m_bytes  (bytes)
  , m_mmc    (mmc)
  , m_forceDebug(getenv("IMPERAS_TLM_MMC_DEBUG") != 0)
{
    socket.register_b_transport  (this, &icmMMCSlavePort::b_transport);
    socket.register_transport_dbg(this, &icmMMCSlavePort::debug_transport);
    mmc->icmCpuManager::icmMmcObject::connect(m_bus, name, false);
}

// target regular method
void icmMMCSlavePort::transport( tlm::tlm_generic_payload &payload, void *processor)
{
    Addr              addr     = payload.get_address();     // memory address
    tlm::tlm_command  command  = payload.get_command();     // memory command
    unsigned char    *data     = payload.get_data_ptr();    // data pointer
    unsigned int      bytes    = payload.get_data_length(); // data length
    bool              ok       = true;

    if (m_forceDebug) {
        processor = 0;
    }

    if ((addr + bytes) > m_bytes) {
        ok = false;
    } else {
        switch(command) {
            case tlm::TLM_WRITE_COMMAND:
                if (m_mmc->traceSlaves()) {
                	icmPrintf("TLM: %s.%s %s write %d bytes to 0x" FMT_Ax "\n",
                		m_mmc->m_name,
                		m_name,
                		processor ? " sim" : " dbg",
                		bytes,
                		addr
                	);
                }
                m_bus.write(addr, (void*)data, bytes, processor);
                break;
            case tlm::TLM_READ_COMMAND:
                if (m_mmc->traceSlaves()) {
                	icmPrintf("TLM: %s.%s %s read %d bytes from 0x" FMT_Ax "\n",
                		m_mmc->m_name,
                		m_name,
                		processor ? " sim" : " dbg",
                		bytes,
                		addr
                	);
                }
                m_bus.read(addr, (void*)data, bytes, processor);
                break;
            default:
                ok = false;
        }
    }
    payload.set_response_status(ok ? tlm::TLM_OK_RESPONSE : tlm::TLM_ADDRESS_ERROR_RESPONSE);
}

void icmMMCSlavePort::b_transport( tlm::tlm_generic_payload &payload, sc_time &delay)
{
    icmInitiatorExtension *ext;
    payload.get_extension(ext);
    transport(payload, ext->m_initiator);
}

// target debug method
unsigned int icmMMCSlavePort::debug_transport(tlm::tlm_generic_payload &payload)
{
    transport(payload, 0);
    return payload.get_data_length();
}

//
//////////////////////////////// MASTER PORT //////////////////////////////////
//
icmMMCMasterPort::icmMMCMasterPort(icmMMC *mmc, const char *name, Uns32 addrBits)
    : m_addrBits  (addrBits)
    , m_name      (name)
    , m_bus       ("m_bus",   CONCAT2(mmc->m_name, name), m_addrBits)
    , m_tlmBus    ("tlm_bus", CONCAT2(mmc->m_name, name), m_addrBits)
    , m_zero_delay(SC_ZERO_TIME)
    , m_mmc       (mmc)
    , socket      (name)
{
    m_initiator = new icmInitiatorExtension();
    m_trans.set_extension(m_initiator);

    icmMemCallback *cb = new icmMemCallback(
        (icmMemCallback::readCallback)&icmMMCMasterPort::read,
        (icmMemCallback::writeCallback)&icmMMCMasterPort::write,
        (void*)this // this master port
    );
    m_tlmBus.mapExternalMemory("callback", ICM_PRIV_RWX, 0, maxValue(m_addrBits), cb);
    mmc->icmCpuManager::icmMmcObject::connect(m_bus, name, true);

    // all address space mapped to TLM
    m_bus.bridge(m_tlmBus, 0, maxValue(m_addrBits), 0);
}

void icmMMCMasterPort::read(
    Addr   address,
    Uns32  bytes,
    void  *value,
    void  *userData,
    void  *processor
) {
    icmMMCMasterPort *classPtr = (icmMMCMasterPort*)userData;
    classPtr->readUpcall(address, value, bytes, processor);
}

// static write callback
void icmMMCMasterPort::write(
    Addr        address,
    Uns32       bytes,
    const void *value,
    void       *userData,
    void       *processor
) {
    icmMMCMasterPort *classPtr = (icmMMCMasterPort*)userData;
    classPtr->writeUpcall(address, value, bytes, processor);
}

//! This is the entry point used by ::staticReadUpcall(). Constructs a
//! Generic transactional payload for the read, then passes it to the target.

//! @param addr     The address for the write
//! @param simulate If true, this access should be simulated, if not it should be a back-door access

void icmMMCMasterPort::readUpcall(Addr addr, void *value, Uns32 bytes, void *processor)
{
    // set initiator for this transaction
    m_initiator->m_initiator = processor;

    m_trans.set_read();
    m_trans.set_address(addr);
    m_trans.set_data_length(bytes);
    m_trans.set_data_ptr( (unsigned char *)value );
    m_trans.set_streaming_width(bytes);
    m_trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    m_trans.set_dmi_allowed(false);

    if (m_mmc->traceMasters()) {
        icmPrintf("TLM: %s.%s %s read %d bytes from 0x" FMT_Ax "\n",
            m_mmc->m_name,
            m_name,
            processor ? " sim" : " dbg",
            bytes,
            addr
        );
    }
    if (processor) {
        socket->b_transport(m_trans, m_zero_delay);
    } else {
        socket->transport_dbg(m_trans);
    }
}


// This is the entry point used by icmMMC::write.
//  Constructs a generic transactional payload for the write, then passes the target.

//! @param addr     The address for the write
//! @param mask     The byte enable mask for the write
//! @param wdata    The data to be written (matching the mask)
//! @param simulate If true, this access should be simulated, if not it should be a back-door access

void icmMMCMasterPort::writeUpcall(Addr addr, const void *value, Uns32 bytes, void *processor)
{
    // set initiator for this transaction
    m_initiator->m_initiator = processor;

    m_trans.set_write();
    m_trans.set_address(addr);
    m_trans.set_data_length(bytes);
    m_trans.set_data_ptr( (unsigned char *)value);
    m_trans.set_streaming_width(bytes);  // who's to say the max width?
    m_trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    m_trans.set_dmi_allowed(false);

    if (m_mmc->traceMasters()) {
        icmPrintf("TLM: %s.%s %s write %d bytes to 0x" FMT_Ax "\n",
            m_mmc->m_name,
            m_name,
            processor ? " sim" : " dbg",
            bytes,
            addr
        );
    }
    if (processor) {
        socket->b_transport(m_trans, m_zero_delay);
    } else {
        socket->transport_dbg(m_trans);
    }
}

//
/////////////////////////////////////// MMC ///////////////////////////////////
//

icmMMC::icmMMC(
      sc_module_name          name
    , const char             *model
    , const char             *attrTable
    , icmAttrListObject      *initialAttrs
)
: sc_module (name)          /// instance name
, icmMmcObject(sc_object::name(), model, attrTable, initialAttrs, false)
, m_traceMasters(0)
, m_traceSlaves(0)
, m_name(name)
{
    if(getenv("IMPERAS_TLM_MMC_TRACE")) {
    	icmPrintf("TLM: %s Tracing ON\n", m_name);
        m_traceMasters = 1;
        m_traceSlaves  = 1;
    }
}
