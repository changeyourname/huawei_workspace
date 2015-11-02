/*
 * cache.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: uzair
 */


// implementation of simple cache model that is designed to be integrated with the processor model or any other mem access request generating agent

#ifndef CACHE_HPP_
#define CACHE_HPP_

#include <tlm>
#include <stdint.h>

#define WORD_SIZE 4			// in bytes
#define MEM_SIZE 536870912	// in bytes
#define MEM_ADDRESSING 32	// or 64

#if MEM_ADDRESSING == 32
	typedef uint32_t addr_t;
#elif MEM_ADDRESSING == 64
	typedef uint64_t addr_t;
//#elif ...	and so on for other mem_addressing modes if need be
#endif

// cache timings
//#define CACHE_LOOKUP_DELAY sc_core::sc_time(1, sc_core::SC_NS)
//#define WR_CACHE_DELAY sc_core::sc_time(5, sc_core::SC_NS)
//#define RD_CACHE_DELAY sc_core::sc_time(5, sc_core::SC_NS)
//#define MEM2CACHE_LINE_DELAY sc_core::sc_time(200, sc_core::SC_NS)
//#define CACHE2MEM_LINE_DELAY sc_core::sc_time(20, sc_core::SC_NS)
#define WRITEBACK_NOTIFICATION_DELAY sc_core::sc_time(10, sc_core::SC_NS);
#define INVALIDATION_NOTIFICATION_DELAY sc_core::sc_time(10, sc_core::SC_NS);


struct cache_line {
	bool valid;
	bool dirty;
	addr_t tag;
	uint64_t evict_tag;
};


class cache : public sc_core::sc_module {
public:
	enum eviction_policy {LRU, LFU, RAND};

	cache(sc_core::sc_module_name name, uint32_t total_cache_size=65536, uint32_t cache_line_size=8, uint32_t num_of_ways=2, bool write_back=true, bool write_allocate=true, cache::eviction_policy evict_pol=LRU);
	void update(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay);
	void set_parent(cache *parent);
	void set_children(std::vector< cache * > *child);
	void set_delays(sc_core::sc_time upstream, sc_core::sc_time downstream, sc_core::sc_time lookup, sc_core::sc_time write, sc_core::sc_time read);
private:
	uint32_t m_total_cache_size;
	uint32_t m_cache_line_size;
	uint32_t m_num_of_sets;
	uint32_t m_num_of_ways;
	bool     m_write_back;
	bool     m_write_allocate;
	eviction_policy m_evict;
	std::vector< std::vector<cache_line> > m_cache_lines;
	cache *m_parent;
	std::vector < cache * > *m_child;
	sc_core::sc_time m_lookup_delay;
	sc_core::sc_time m_read_cache_delay;
	sc_core::sc_time m_write_cache_delay;
	sc_core::sc_time m_upstream_cacheblock_delay;
	sc_core::sc_time m_downstream_cacheblock_delay;

	void handle_invalidation_request(addr_t req_addr, sc_core::sc_time &delay);
	void handle_writeback(addr_t req_addr);
};








// NOTES:
// support for cache write-back or write-through; write-allocate or write-no-allocate
// support for LRU, LFU, random eviction policy












#endif /* CACHE_HPP_ */

