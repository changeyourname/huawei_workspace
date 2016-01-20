/*
 * cache.hpp
 *
 *  Created on: Nov 11, 2015
 *      Author: uzleo
 */

#ifndef _CACHEDUMMY_HPP_
#define _CACHEDUMMY_HPP_

#include <tlm>
#include <tlm_utils/simple_target_socket.h>
#include <stdint.h>

class cache_dum : public sc_core::sc_module {
  public:
	tlm_utils::simple_target_socket< cache_dum > socket;		// in downstream direction

	cache_dum(sc_core::sc_module_name name);
	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);
	unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
	
	sc_dt::uint64 regs[2];
};



#endif /* _CACHEDUMMY_HPP_ */












