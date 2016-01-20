/*
 * cache.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: uzleo
 */




#include "cache_dummy.hpp"

// constructor
cache_dum::cache_dum(sc_core::sc_module_name name)
	:	sc_module(name),
		socket("socket")												// initiator socket to downstream slave
{
    socket.register_b_transport(this, &cache_dum::b_transport);
    socket.register_transport_dbg(this, &cache_dum::transport_dbg);
    
    regs[0] = 0x0;
    regs[1] = 0x0;
}



// port interface method
void cache_dum::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay) {
    delay += sc_core::sc_time(2, sc_core::SC_NS);
}


unsigned int 
cache_dum::transport_dbg(tlm::tlm_generic_payload &trans) 
{
    // specifically use only for reading cache misses or access registers!!!    
        
    // intentionally putting dummy values in regs
    regs[0] = 0x1111;
    regs[1] = 0x2222;
        
    tlm::tlm_command cmd = trans.get_command();
    assert(cmd == tlm::TLM_READ_COMMAND);
    unsigned int idx = trans.get_address();
    unsigned char *ptr = trans.get_data_ptr();
    assert(ptr);
    unsigned int len = trans.get_data_length();
    assert(len==4 || len==8);
    
    memcpy(ptr, &regs[idx], len);
    return len;    
}


















