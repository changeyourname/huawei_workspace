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


#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
#include "ovpworld.org/modelSupport/tlmDummySlavePort/1.0/tlm2.0/tlmDummySlavePort.hpp"
#include "ovpworld.org/modelSupport/tlmInitiatorExtension/1.0/tlm2.0/tlmInitiatorExtension.hpp"

#define CONCAT(s1,s2) ((string) s1 + "_" + (string) s2).c_str()

//
// Local utility
//
static void printBytes(Uns8 *ptr, Uns32 bytes) {
    icmPrintf("{");
    Uns32 i;
    for(i = 0; i < bytes; i++, ptr++) {
        if(i == 0) {
            icmPrintf("%02x", *ptr);
        } else {
            icmPrintf(",%02x", *ptr);
        }
    }
    icmPrintf("}");
}

//
////////////////////////// Slave port implementation //////////////////////////
//
icmSlavePort::icmSlavePort(
    icmPeripheral *pse,
    const char    *name,
    Addr           bytes)
: m_bus    ("sp_bus", CONCAT(pse->m_name, name), addrBits(bytes-1))
, m_bytes  (bytes)
, m_name   (name)
, m_pse    (pse)
, socket   (name)
{
    socket.register_b_transport  (this, &icmSlavePort::b_transport);
    socket.register_transport_dbg(this, &icmSlavePort::debug_transport);
    pse->icmCpuManager::icmPseObject::connect(m_bus, name, false, 0, bytes-1);
}

// target regular method
void icmSlavePort::transport( tlm::tlm_generic_payload &payload, void *processor)
{
    Addr              address  = payload.get_address();     // memory address
    tlm::tlm_command  command  = payload.get_command();     // memory command
    unsigned char    *data     = payload.get_data_ptr();    // data pointer
    unsigned  int     length   = payload.get_data_length(); // data length
    bool              ok       = true;

    if (address + length > m_bytes) {
        ok = false;
    }
    if (length > 4) {
        ok = false;   // perhaps we can handle more?
    }
    switch(command) {
        case tlm::TLM_WRITE_COMMAND:
            if (m_pse->traceBuses()) {
                icmPrintf("TLM: %s.%s write %d bytes [" FMT_Ax "] ", m_pse->m_name, m_name, length, address);
                printBytes(data, length);
                icmPrintf("\n");
            }
            m_bus.write(address, (void*)data, length, processor);
        break;

        case tlm::TLM_READ_COMMAND:
            m_bus.read(address, (void*)data, length, processor);
            if (m_pse->traceBuses()) {
                icmPrintf("TLM: %s.%s read  %d bytes [" FMT_Ax "] ", m_pse->m_name, m_name, length, address);
                printBytes(data, length);
                icmPrintf("\n");
            }
            break;

        default:
            ok = false;
    }
    payload.set_response_status(ok ? tlm::TLM_OK_RESPONSE : tlm::TLM_ADDRESS_ERROR_RESPONSE);
}

// target regular method
void icmSlavePort::b_transport( tlm::tlm_generic_payload &payload, sc_time &delay)
{
    icmInitiatorExtension *ext;
    payload.get_extension(ext);
    transport(payload, ext->m_initiator);
}

// target debug method
unsigned int icmSlavePort::debug_transport(tlm::tlm_generic_payload &payload)
{
    transport(payload, 0);
    return 1;
}

//
////////////////////////// Dynamic Slave port implementation //////////////////////////
//
icmDynamicSlavePort::icmDynamicSlavePort(
    icmPeripheral *pse,
    const char    *name,
    Uns32 addrBits)
: m_bus    ("sp_bus", CONCAT(pse->m_name, name), addrBits)
, m_name   (name)
, m_pse    (pse)
, mappings (0)
, socket   (name)
{
    socket.register_b_transport  (this, &icmDynamicSlavePort::b_transport);
    socket.register_transport_dbg(this, &icmDynamicSlavePort::debug_transport);
    pse->icmCpuManager::icmPseObject::connect(m_bus, name, false);
    pse->addPortMapCB(name, staticSetPortAddress, (void*)this);
}

void icmDynamicSlavePort::transport( tlm::tlm_generic_payload &payload, void *processor)
{
    Addr              address  = payload.get_address();     // memory address
    tlm::tlm_command  command  = payload.get_command();     // memory command
    unsigned char    *data     = payload.get_data_ptr();    // data pointer
    unsigned  int     length   = payload.get_data_length(); // data length
    bool              ok       = true;

    icmDynamicPortMapping *mapping;
    for (mapping = mappings; mapping; mapping = mapping->getNext()) {
        if (mapping->inRegion(address)) {
            switch(command) {
                case tlm::TLM_WRITE_COMMAND:
                    if (m_pse->traceBuses()) {
                        icmPrintf("TLM: %s.%s write [" FMT_Ax "] ", m_pse->m_name, m_name, address);
                        printBytes(data, length);
                        icmPrintf("\n");
                    }
                    m_bus.write(address, (void*)data, length, processor);
                    break;
                case tlm::TLM_READ_COMMAND:
                    m_bus.read(address, (void*)data, length, processor);
                    if (m_pse->traceBuses()) {
                        icmPrintf("TLM: %s.%s read  %d bytes [" FMT_Ax "] ", m_pse->m_name, m_name, length, address);
                        printBytes(data, length);
                        icmPrintf("\n");
                    }
                    break;
                default:
                    ok = false;
            }
            if (ok) {
                payload.set_response_status(tlm::TLM_OK_RESPONSE);
            }
            break;
        }
    }
}

// target regular method
void icmDynamicSlavePort::b_transport( tlm::tlm_generic_payload &payload, sc_time &delay)
{
    icmInitiatorExtension *ext;
    payload.get_extension(ext);
    transport(payload, ext->m_initiator);
}

// target debug method
unsigned int icmDynamicSlavePort::debug_transport(tlm::tlm_generic_payload &payload)
{
    transport(payload, 0);
    return 1;
}

void icmDynamicSlavePort::staticSetPortAddress(void *userData, Addr lo, Addr hi, Bool map) {
    icmDynamicSlavePort *ptr = (icmDynamicSlavePort*)userData;
    ptr->setPortAddress(lo, hi, map);
}

void icmDynamicSlavePort::setPortAddress(Addr lo, Addr hi, Bool map) {
    if (m_pse->traceBuses()) {
    	const char *what = map ? "mapping" : "unmapping";
   	    icmPrintf("TLM: %s.%s %s [" FMT_Ax ":" FMT_Ax "]\n", m_pse->m_name, m_name, what, lo, hi);
    }
    if(map) {
        icmDynamicPortMapping *mapping = new icmDynamicPortMapping(lo,hi);
        mapping->setNext(mappings);
        mappings = mapping;
    } else {
        icmDynamicPortMapping **old = &mappings;
        while(*old) {
            if ((*old)->matches(lo, hi)) {
                *old = (*old)->getNext();
                break;
            }
            old = (*old)->getNextP();
        }
    }
}

//
/////////////////////////// Master port implementation ////////////////////////
//
#define CASE_STRING(_n)   case tlm::_n : s = # _n;          break;

const char *icmMasterPort::response() {
    const char *s = "???";
    switch (m_trans.get_response_status()) {
        CASE_STRING(TLM_OK_RESPONSE);
        CASE_STRING(TLM_INCOMPLETE_RESPONSE);
        CASE_STRING(TLM_GENERIC_ERROR_RESPONSE);
        CASE_STRING(TLM_ADDRESS_ERROR_RESPONSE);
        CASE_STRING(TLM_COMMAND_ERROR_RESPONSE);
        CASE_STRING(TLM_BURST_ERROR_RESPONSE);
        CASE_STRING(TLM_BYTE_ENABLE_ERROR_RESPONSE);
    }
    return s;
}


icmMasterPort::icmMasterPort(icmPeripheral *pse, const char *name, Uns32 addrBits)
: m_addrBits(addrBits)
, m_bus("m_bus", CONCAT(pse->m_name,name), m_addrBits)
, m_zero_delay(SC_ZERO_TIME)
, m_pse(pse)
{
    icmInitiatorExtension *initiator = new icmInitiatorExtension();
    initiator->m_initiator = pse->getPseP();
    m_trans.set_extension(initiator);

    icmMemCallback *cb = new icmMemCallback(
         (icmMemCallback::readCallback)&icmMasterPort::read,
         (icmMemCallback::writeCallback)&icmMasterPort::write,
         (void*)this // this master port
     );
    m_bus.mapExternalMemory("callback", ICM_PRIV_RW, 0, maxValue(addrBits), cb);
    pse->icmPseObject::connect(m_bus, name, true, 0, maxValue(addrBits));
}

// Read and write methods construct a TLM transaction for each memory access.
// Note that OVP processor does not model byte lanes and byte lane enables.

// static read callback
void icmMasterPort::read(
      Addr          address,
      Uns32         bytes,
      void         *value,
      void         *userData,
      void         *processor
) {
    icmMasterPort *classPtr = (icmMasterPort*)userData;
    classPtr->readUpcall(address, value, bytes);
}

// static write callback
void icmMasterPort::write(
      Addr          address,
      Uns32         bytes,
      const void   *value,
      void         *userData,
      void         *processor
) {
    icmMasterPort *classPtr = (icmMasterPort*)userData;
    classPtr->writeUpcall(address, value, bytes);
}

void icmMasterPort::readUpcall(Addr addr, void *value, Uns32 bytes)
{
    m_trans.set_read();
    m_trans.set_address(addr);
    m_trans.set_data_length(bytes);
    m_trans.set_data_ptr((unsigned char *)value);
    m_trans.set_streaming_width(bytes);
    m_trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    if (m_pse->traceBuses()) {
    	icmPrintf("TLM: %s read  %d bytes [" FMT_Ax "]\n", m_pse->m_name, bytes, addr);
    }
    socket->b_transport( m_trans, m_zero_delay );
    if (m_pse->traceBusErrors() && m_trans.get_response_status() != tlm::TLM_OK_RESPONSE) {
    	icmPrintf("TLM: %s read [" FMT_Ax "] %s\n",
    		m_pse->m_name,
    		addr,
    		response()
    	);
    }
    if (m_pse->traceBuses()) {
        icmPrintf("TLM: %s %s [" FMT_Ax "] ", m_pse->m_name, response(), addr);
        if(m_trans.get_response_status() == tlm::TLM_OK_RESPONSE) {
            printBytes(m_trans.get_data_ptr(), bytes);
        }
        icmPrintf("\n");
    }
}

void icmMasterPort::writeUpcall(Addr addr, const void *value, Uns32 bytes)
{
    m_trans.set_write();
    m_trans.set_address(addr);
    m_trans.set_data_length(bytes);
    m_trans.set_data_ptr((unsigned char *)value);
    m_trans.set_streaming_width(bytes);
    m_trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    if (m_pse->traceBuses()) {
    	icmPrintf("TLM: %s write %d bytes [" FMT_Ax "] ", m_pse->m_name, bytes, addr);
    	printBytes(m_trans.get_data_ptr(), bytes);
        icmPrintf("\n");
    }
    socket->b_transport( m_trans, m_zero_delay );
    if (m_pse->traceBusErrors() && m_trans.get_response_status() != tlm::TLM_OK_RESPONSE) {
    	icmPrintf(
    		"TLM: %s write address [" FMT_Ax "] %s\n",
    		m_pse->m_name,
    		addr,
    		response()
    	);
    }
    if (m_pse->traceBuses()) {
        icmPrintf("TLM: %s write %s\n", m_pse->m_name, response());
    }
}

//
//////////////////////////////// Output net port //////////////////////////////
//

icmOutputNetPort::icmOutputNetPort(icmPeripheral *pse,  const char *portName)
: m_net(CONCAT(pse->m_name,portName))
, m_pse(pse)
, m_name(portName)
{
    pse->icmPseObject::connect(m_net, portName, ICM_OUTPUT);
    m_net.addCallback(icmOutputNetPort::update, this);
}

void icmOutputNetPort::update(void *user, Uns32 value)
{
    icmOutputNetPort *thisPtr = (icmOutputNetPort*)user;
    int t = value;;
    if (thisPtr->m_pse->traceSignals()) {
    	icmPrintf("TLM: %s.%s = %d\n", thisPtr->m_pse->m_name, thisPtr->m_name, value);
    }
    thisPtr->write(t); // SystemC net write
}

//
/////////////////////////// Input net port //////////////////////////////
//
icmInputNetPort::icmInputNetPort(icmPeripheral *pse, sc_module_name name)
: m_net(CONCAT(pse->getName(), name))
, m_pse(pse)
, m_name(name)
{
  pse->icmPseObject::connect(m_net, (const char*)name, ICM_INPUT);
}

void icmInputNetPort::write(const int &value) {
    if (m_pse->traceSignals()) {
    	icmPrintf("TLM: %s.%s = %d\n", m_pse->m_name, m_name, value);
    }
    m_net.write(value);
}

//
/////////////////////////// Inout net port //////////////////////////////
//
icmInoutNetPort::icmInoutNetPort(icmPeripheral *pse, sc_module_name name)
: m_net(CONCAT(pse->getName(), name))
, m_pse(pse)
, m_name(name)
{
    pse->icmPseObject::connect(m_net, (const char*)name, ICM_INOUT);
    m_net.addCallback(icmInoutNetPort::update, this);
}

void icmInoutNetPort::write(const int &value) {
	if (m_pse->traceSignals()) {
		icmPrintf("TLM: %s.%s = %d\n", m_pse->m_name, m_name, value);
	}
    m_net.write(value);
}

void icmInoutNetPort::update(void *user, Uns32 value)
{
    icmInoutNetPort *thisPtr = (icmInoutNetPort*)user;
    int t = value;;
    if (thisPtr->m_pse->traceSignals()) {
    	icmPrintf("TLM: %s.%s = %d\n", thisPtr->m_pse->m_name, thisPtr->m_name, value);
    }
    thisPtr->write(t); // SystemC net write
}
//
// Use this when there is no default master port
//
void icmMasterPort::bindIfNotBound() {
    if (socket.size() == 0) {
        icmDummySlavePort *dummy=new icmDummySlavePort();
        socket(dummy->socket);
    }
}

//
/////////////////////////////////// Peripheral ////////////////////////////////
//
icmPeripheral::icmPeripheral(
  sc_module_name          name
, const char             *model
, const char             *semihostLibrary
, icmAttrListObject      *initialAttrs
)
: sc_module   (name)   // instance name
, icmPseObject(sc_object::name(), model, initialAttrs, semihostLibrary, semihostLibrary ? "modelAttrs" : 0)
, m_name          (name)
, m_traceBuses    (false)
, m_traceBusErrors(false)
, m_traceSignals  (false)
{
    if(getenv("IMPERAS_TLM_PSE_TRACE")) {
    	icmPrintf("TLM: %s Tracing ON (addresses [] and data {} in Hexadecimal)\n", m_name);
        m_traceBuses     = true;
        m_traceBusErrors = true;
        m_traceSignals   = true;
    }
}


