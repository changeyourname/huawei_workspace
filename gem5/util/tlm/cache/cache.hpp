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
#include "cache_global_defs.hpp"
#include "../global.hh"

class cache : public sc_core::sc_module {
  public:
	enum eviction_policy {LRU, LFU, FIFO, RAND};
	static FILE *common_fid;
    
	// for special requests (e.g back-invalidation) between caches
	class req_extension : public tlm::tlm_extension< req_extension > {
	public:
		enum req_type {NORMAL, M_UPDATE, BACK_INVALIDATE, WB_UPDATE};
		req_type m_type;
		// for memory management
		static std::vector< req_extension * > req_extension_clones;

		virtual tlm_extension_base * clone() const {
			req_extension_clones.push_back(NULL);
			req_extension_clones.back() = new req_extension();
			req_extension_clones.back()->m_type = this->m_type;
			return req_extension_clones.back();
		}

		virtual void copy_from(tlm_extension_base const &ext) {
			m_type = static_cast< req_extension const & >(ext).m_type;
		}
	};
	
	struct cache_specs {
	    uint32_t num_masters;
	    uint32_t size;
	    uint32_t block_size;
	    uint32_t num_ways;
	    bool write_back;
	    bool write_allocate;
	    cache::eviction_policy evict_policy;
	};
		

private:
	struct cache_block {
        // MBS (Modified-but-stale) needed for coherence in inclusive cache hierarchy	
		enum cache_block_state {M, S, I, MBS};						

		cache_block_state state;
		uint64_t tag;
		uint32_t evict_tag;
	};	

    // lt modeling so can afford a single m_trans for the whole object as there are no 
    // outstanding requests..this helps to improve performance as m_trans needs to be 
    // created only once for an object of this class
	tlm::tlm_generic_payload m_trans;	
	req_extension *m_ext;
	uint32_t m_num_upstream_masters;
	uint32_t m_block_size;
	uint32_t m_num_of_sets;
	uint32_t m_num_of_ways;
	bool m_write_back;
	bool m_write_allocate;
	eviction_policy m_evict_policy;
	std::vector< std::vector< cache_block > > m_blocks;
	FILE *m_fid;
	bool m_log;
	uint32_t m_level;
	uint32_t m_current_set;
	uint64_t m_current_tag;
	uint64_t m_current_blockAddr;
	uint32_t m_current_way;
	sc_core::sc_time *m_current_delay;
	uint32_t m_id;
	uint64_t m_cache_regspace_base;	
	uint64_t m_access_register;
	uint64_t m_miss_register;
    sc_core::sc_time m_lookup_delay;
	sc_core::sc_time m_read_delay;
	sc_core::sc_time m_write_delay;

	bool cache_lookup(bool &evict_needed, uint32_t &way_free, bool WB_UPDATE);
	uint32_t find_way_evict();
	void process_hit(tlm::tlm_generic_payload &trans);
	void process_special_request(req_extension::req_type type);
	void process_miss(tlm::tlm_generic_payload &trans, bool evict_needed);
	void do_eviction();
	void send_request(bool downstream, bool new_address=false);
public:
	tlm_utils::simple_initiator_socket< cache > *m_isocket_d;	// in downstream direction
	tlm_utils::simple_initiator_socket< cache > *m_isocket_u;	// in upstream direction
	tlm_utils::simple_target_socket< cache > *m_tsocket_d;		// in downstream direction
	tlm_utils::simple_target_socket< cache > *m_tsocket_u;		// in upstream direction

	cache(	        
            sc_core::sc_module_name name,  
            uint32_t id,
            cache::cache_specs specs, 
            uint32_t level,
            uint64_t regbase,
            const char *logfile = NULL            
	     );
	~cache();	
	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);
	void do_logging();
	void print_cache_set(uint32_t set);
	void set_delays(uint32_t lookup, uint32_t read, uint32_t write);	
};



#endif /* CACHE_HPP_ */












