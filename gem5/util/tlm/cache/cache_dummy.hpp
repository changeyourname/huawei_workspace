/*
 * cache.hpp
 *
 *  Created on: Nov 11, 2015
 *      Author: uzleo
 */

#ifndef CACHE_HPP_
#define CACHE_HPP_

#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <stdint.h>

class cache : public sc_core::sc_module {
  public:
	tlm_utils::simple_target_socket< cache > socket;		// in downstream direction

	cache(sc_core::sc_module_name name);
	~cache();
	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);
};



#endif /* CACHE_HPP_ */












