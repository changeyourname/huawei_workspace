/*
 * cache_controller.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: uzair
 */

#include "cache_controller.hpp"

cache_controller::cache_controller(sc_core::sc_module_name name, int num_smp_cores)
	:	sc_core::sc_module(name), m_num_smp_cores(num_smp_cores), m_Ibus_isocket("m_Ibus_isocket"), m_Dbus_isocket("m_Dbus_isocket")
{
	m_tsocket.reserve(m_num_smp_cores*3);					// 3 groups: INSTRUCTION, DATA, GICREGISTERS
	for (int i=0; i<m_num_smp_cores*3; i++) {
		char socket_name[20];
		sprintf(socket_name, "m_tsocket[%d]", i);
		m_tsocket.push_back(new tlm_utils::simple_target_socket_tagged<cache_controller>(socket_name));
		m_tsocket[i]->register_b_transport(this, &cache_controller::b_transport, i);
		m_tsocket[i]->register_transport_dbg(this, &cache_controller::transport_dbg, i);
	}

	//TODO: dmi stuff for initiator sockets
}


void cache_controller::b_transport(int SocketId, tlm::tlm_generic_payload &payload, sc_core::sc_time &delay) {
	if (SocketId<4) {			// request from INSTRUCTION BUS
		assert(SocketId == 0);
		m_Ibus_isocket->b_transport(payload, delay);
	}

	if (SocketId>=4 && SocketId<8) {		// request from DATA BUS
		assert(SocketId == 4);
		m_Dbus_isocket->b_transport(payload, delay);
	}
}


unsigned int cache_controller::transport_dbg(int SocketId, tlm::tlm_generic_payload &payload) {
	if (SocketId<4) {			// request from INSTRUCTION BUS
		assert(SocketId == 0);
		return m_Ibus_isocket->transport_dbg(payload);
	}

	if (SocketId>=4 && SocketId<8) {		// request from DATA BUS
		assert(SocketId == 4);
		return m_Dbus_isocket->transport_dbg(payload);
	}
}

