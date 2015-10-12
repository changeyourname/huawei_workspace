/**********************************************************************
  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2008 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.
 *********************************************************************/

/* Derived from SimpleBusLT by Imperas Software Ltd. */

#ifndef __TLM_DECODER_H__
#define __TLM_DECODER_H__

#include <assert.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

#define DMI_DEBUG 0
//
// One (of possibly several) mapping through a dynamic slave port
//
class icmPortMapping {
private:
    Addr lo;
    Addr hi;
    icmPortMapping *next;

public:
    icmPortMapping(Addr lo_n, Addr hi_n)
        : lo(lo_n), hi(hi_n), next(0){
    }
    void setNext(icmPortMapping *n) { next = n; }
    icmPortMapping *getNext()   { return next;  }

    void getRegion(Addr& l, Addr&h) { l = lo; h = hi; }

    Bool matches(Addr lo_s, Addr hi_s) {
        return lo == lo_s && hi == hi_s;
    }

    Bool inRegion(Addr a) {
        return a >= lo && a <= hi;
    }

    Addr offsetInto(Addr a) {
        return a - lo;
    }
    Addr offsetOutOf(Addr a) {
        return a + lo;
    }
};


template <int NR_OF_INITIATORS, int NR_OF_TARGETS>
class decoder : public sc_core::sc_module
{

private:
    icmPortMapping *decodes[NR_OF_TARGETS];
    bool m_trace;

public:
	typedef tlm::tlm_generic_payload                           transaction_type;
	typedef tlm_utils::simple_target_socket_tagged<decoder>    target_socket_type;
	typedef tlm_utils::simple_initiator_socket_tagged<decoder> initiator_socket_type;

	target_socket_type target_socket[NR_OF_INITIATORS];
	initiator_socket_type initiator_socket[NR_OF_TARGETS];

public:
	decoder(sc_core::sc_module_name name)
	: sc_core::sc_module(name)
	, m_trace(false)
	{
		for (int i = 0; i < NR_OF_INITIATORS; ++i) {
		  target_socket[i].register_b_transport(this, &decoder::initiatorBTransport, i);
		  target_socket[i].register_transport_dbg(this, &decoder::transportDebug, i);
		  target_socket[i].register_get_direct_mem_ptr(this, &decoder::getDMIPointer, i);
		}
		for (int i = 0; i < NR_OF_TARGETS; ++i) {
		  initiator_socket[i].register_invalidate_direct_mem_ptr(this, &decoder::invalidateDMIPointers, i);
		  decodes[i] = 0;
		}
	    if (getenv("IMPERAS_TLM_DECODE_TRACE")) {
	        m_trace = true;
	    }
	}

	void setDecode(int portId, Addr lo, Addr hi) {
	    if (portId >= NR_OF_TARGETS) {
	        icmPrintf(
	            "Error configuring TLM decoder %s: portId (%d) cannot be greater than the number of targets (%d)\n",
	            name(),
	            portId,
	            NR_OF_TARGETS
	        );
	        return;
	        abort();
	    }
	    if (lo > hi) {
	        icmPrintf(
	            "Error configuring TLM decoder %s: lo (0x" FMT_Ax ") cannot be greater than hi (0x" FMT_Ax ")\n",
                name(),
	            lo,
	            hi
	        );
	        return;
	    }
		icmPortMapping *decode = new icmPortMapping(lo, hi);
		decode->setNext(decodes[portId]);
		decodes[portId] = decode;
	}

    void trace(bool on) { m_trace = on; }

private:
    icmPortMapping *getMapping(int port, Addr address) {
        icmPortMapping *decode;
        for (decode = decodes[port]; decode; decode = decode->getNext()) {
            if (decode->inRegion(address)) {
                return decode;
            }
        }
        return 0;
    }

	int getPortId(const Addr address, Addr& offset)
	{
		int i;
		for(i = 0; i < NR_OF_TARGETS; i++) {
		  icmPortMapping *decode = getMapping(i, address);
		  if (decode) {
			  offset = decode->offsetInto(address);
			  return i;
		  }
		}
		return -1;
	}

	//
	// LT protocol
	// - forward each call to the target/initiator
	//
    void initiatorBTransport(int SocketId,
                             transaction_type& trans,
                             sc_core::sc_time& t) {
        Addr orig        = trans.get_address();
        Addr offset;
        int  portId      = getPortId(orig, offset);
        if(portId >= 0) {
            if(m_trace) {
                icmPrintf("TLM: %s decode:0x" FMT_64x " -> initiator_socket[%d]\n",
                        name(), orig, portId);
            }
            // It is a static port ?
            initiator_socket_type *decodeSocket     = &initiator_socket[portId];
            trans.set_address(offset);
            (*decodeSocket)->b_transport(trans, t);
        } else {
            // might be a dynamic port, so try each un-set port till one responds
            int i;
            for(i = 0; i < NR_OF_TARGETS; i++) {
                if (!decodes[i]) {
                    initiator_socket_type *decodeSocket = &initiator_socket[i];
                    (*decodeSocket)->b_transport(trans, t);
                    if (trans.get_response_status() == tlm::TLM_OK_RESPONSE) {
                        if(m_trace) {
                            icmPrintf("TLM: %s dynamic:0x" FMT_64x " -> initiator_socket[%d]\n",
                                    name(), orig, i);
                        }
                        break;
                    }
                }
            }
        }
    }

    unsigned int transportDebug(int SocketId, transaction_type& trans)
    {
        Addr orig        = trans.get_address();
        Addr offset;
        int  portId      = getPortId(orig, offset);
        if(portId >= 0) {
            if(m_trace) {
                icmPrintf("TLM: %s dbg decode:0x" FMT_64x " -> initiator_socket[%d]\n",
                        name(), orig, portId);
            }
            // It is a static port ?
            initiator_socket_type *decodeSocket = &initiator_socket[portId];
            trans.set_address(offset);
            return (*decodeSocket)->transport_dbg(trans);
        } else {
            for(int i = 0; i < NR_OF_TARGETS; i++) {
                if (!decodes[i]) {
                    initiator_socket_type *decodeSocket = &initiator_socket[i];
                    int r = (*decodeSocket)->transport_dbg(trans);
                    if (r) {
                        if(m_trace) {
                            icmPrintf("TLM: %s dbg dynamic:0x" FMT_64x " -> initiator_socket[%d]\n",
                                    name(), orig, i);
                        }
                        return r;
                    }
                }
            }
            return 0;
        }
    }

    void adjustRange(int portId, Addr orig, Addr& low, Addr& high)
    {
        if(DMI_DEBUG) {
            icmPrintf("TLM: %s adjustRange port %d input lo:" FMT_64x " hi:" FMT_64x "\n", name(), portId, low, high);
        }
        icmPortMapping *map = getMapping(portId, orig);
        Addr portLo, portHi;

        map->getRegion(portLo, portHi);

        if(DMI_DEBUG) {
            icmPrintf("TLM: %s adjustRange region addr:" FMT_64x " (lo:" FMT_64x " hi:" FMT_64x ")\n", name(), orig, portLo, portHi);
        }

        // low is always correct
        low  += portLo;

        // if high > decoder, it's the special case of the device not knowing it's size
        // or just being larger than the decoder
        Addr maxDecode = portHi - portLo;
        if(high > maxDecode) {
            high = portLo + maxDecode;
        } else {
            high += portLo;
        }

        if(DMI_DEBUG) {
            icmPrintf("TLM: %s adjustRange changed: lo:" FMT_64x " hi:" FMT_64x "\n\n", name(), low, high);
        }

        assert(high >= low);
        assert(high - low <= maxDecode);

    }

    //
    // Cannot use DMI through plug & play devices. This is probably OK for present.
    //
    bool getDMIPointer(int SocketId, transaction_type& trans, tlm::tlm_dmi&  dmi_data)
    {
        Addr address = trans.get_address();
        Addr offset;
        int  portId = getPortId(address, offset);
        Bool result = false;

        if(portId >= 0) {
            initiator_socket_type* decodeSocket = &initiator_socket[portId];

            // send on the transaction with the new address, adjusted for the decoder offset
            trans.set_address(offset);
            result = (*decodeSocket)->get_direct_mem_ptr(trans, dmi_data);

            // put the address back how it was
            trans.set_address(address);

            // Should always succeed
            Addr start = dmi_data.get_start_address();
            Addr end   = dmi_data.get_end_address();

            if (result) {
                // Range must contain address
                assert(start <= offset);
                assert(end   >= offset);
            }

            adjustRange(portId, address, start, end);

            dmi_data.set_start_address(start);
            dmi_data.set_end_address(end);
        }

        return result;
    }

    void invalidateDMIPointers(int port_id,  sc_dt::uint64 start_range,  sc_dt::uint64 end_range)
    {
        // For each decode on this port, adjust the range for the decode and pass the call on.
        icmPortMapping *decode;
        for (decode = decodes[port_id]; decode; decode = decode->getNext()) {
            sc_dt::uint64 start = decode->offsetOutOf(start_range);
            sc_dt::uint64 end   = decode->offsetOutOf(end_range);
            for (int i = 0; i < NR_OF_INITIATORS; ++i) {
                (target_socket[i])->invalidate_direct_mem_ptr(start, end);
            }
        }
    }

};

#endif
