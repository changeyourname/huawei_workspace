/*
 * cache.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: uzleo
 */




#include "cache_dummy.hpp"

// constructor
cache::cache(sc_core::sc_module_name name)
	:	sc_module(name),
		socket("socket")												// initiator socket to downstream slave
{
    socket.register_b_transport(this, &cache::b_transport);
}


// deleting allocated stuff to avoid memory leaks
cache::~cache() {

}


// port interface method
void cache::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay) {

}

