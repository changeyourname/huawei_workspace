/*
 * cache.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: uzair
 */




#include "cache.hpp"
#include <math.h>
#include <algorithm>

cache::cache(sc_core::sc_module_name name, uint32_t total_cache_size, uint32_t cache_line_size, uint32_t num_of_ways, bool write_back, bool write_allocate, cache::eviction_policy evict_pol)
	:	sc_module(name),
		m_total_cache_size(total_cache_size),
		m_cache_line_size(cache_line_size),
		m_num_of_sets(total_cache_size/(cache_line_size*num_of_ways)),
		m_num_of_ways(num_of_ways),
		m_write_back(write_back),
		m_write_allocate(write_allocate),
		m_evict(evict_pol)
{
	m_cache_lines.resize(m_num_of_sets);
	for (uint32_t i=0; i<m_num_of_sets; i++) {
		m_cache_lines[i].resize(m_num_of_ways);
		for (uint32_t j=0; j<m_num_of_ways; j++) {
			m_cache_lines[i][j].valid = false;
		}
	}

	// ensuring that set bits <= mem_size_bits.....sort of a corner case but not expected to occur in real cache organizations
	// if this does occur though then cache would be inefficient as it will have slots for memory words which actually dont exist in memory......cache will be bigger than memory!
	assert(log2((double) m_num_of_sets) <= log2((double) MEM_SIZE));


	printf("CACHE_CONFIG \r\n");
	std::cout << name;
	printf("..total_cache_size:%dB", m_total_cache_size);
	printf("..cache_block_size:%dB", m_cache_line_size);
	printf("..num_of_sets:%d", m_num_of_sets);
	printf("..num_of_ways:%d", m_num_of_ways);
	printf("..write_back:%d", m_write_back);
	printf("..write_allocate:%d", m_write_allocate);
	printf("..evict_policy:%d\r\n\r\n", m_evict);

}

void cache::update(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay) {

	addr_t addr = (payload.get_address()/m_cache_line_size)*m_cache_line_size;			// rounded to cache-block address
	tlm::tlm_command cmd = payload.get_command();

	int way_free = -1;

	// finding out the cache set for this address for lookup
	uint32_t set = (addr >> (uint32_t) (log2((double) WORD_SIZE) + log2((double) m_cache_line_size/WORD_SIZE))) & ((1 << (uint32_t) log2((double)m_num_of_sets)) - 1);
	// as well as the tag
	addr_t tag = (addr >> (uint32_t) (log2((double) WORD_SIZE) + log2((double) m_cache_line_size/WORD_SIZE) + log2((double) m_num_of_sets)));

	delay += m_lookup_delay;
	// cache lookup for the found tag
	for (uint32_t i=0; i<m_num_of_ways; i++) {
		if (m_cache_lines[set][i].valid == true) {
			if (m_cache_lines[set][i].tag == tag) {
				printf("(%s)..", name());
				printf("cache hit for 0x%08x", payload.get_address());
				printf("..tag=0x%08x", tag);
				printf("...set=%d\r\n", set);

				if (cmd == tlm::TLM_WRITE_COMMAND) {	// write hit
					if (!m_child) {
						if (m_write_back) {
							// for the lowest level cache, marking this block as dirty incase of write hit and write-back policy being used
							m_cache_lines[set][i].dirty = true;
							delay += m_write_cache_delay;
						} else {
							//delay += m_downstream_cacheblock_delay;
							// for write-through policy, we assume that there are write buffers b/w cache and higher level cache/memory module so as to hide the write word delay to this cache
							// hence delay not updated here
						}
					} else {
						// write miss in l1 cache but hit in higher level cache hierarchy so transferring this block to l1 and canceling dirtyness as l1 has the most updated data now
						delay += m_read_cache_delay;
						m_cache_lines[set][i].dirty = false;
					}
				} else if (cmd == tlm::TLM_READ_COMMAND) {	// read hit
					delay += m_read_cache_delay;
				}

				// for eviction policy management
				switch(m_evict) {
					case LRU:
						for (uint32_t j=0; j<m_num_of_ways; j++) {
							if (i!=j && m_cache_lines[set][j].valid==true && m_cache_lines[set][j].evict_tag<=m_cache_lines[set][i].evict_tag) {
								m_cache_lines[set][j].evict_tag++;
							}
							assert(m_cache_lines[set][j].evict_tag <= m_num_of_ways);
						}
						m_cache_lines[set][i].evict_tag = 1;
						break;
					case LFU:
						m_cache_lines[set][i].evict_tag++;
						break;
					case RAND:
						break;
					default:
						assert(0);
				}

				return;
			}
		} else {
			way_free = i;
		}
	}
	printf("(%s)..", name());
	printf("cache miss for 0x%08x", payload.get_address());
	printf("..tag=0x%08x", tag);
	printf("...set=%d\r\n", set);

	if (cmd == tlm::TLM_WRITE_COMMAND && !m_write_allocate) {
		// if write miss and write-no-allocate policy being selected then not updating anything in cache for this case...just modeling delay for writing the word into downstream memory module

		delay += m_downstream_cacheblock_delay;
	} else {
		if (way_free == -1) {
			// there is no free way available for caching new block so have to evict one
			// finding the way to be evicted based on eviction policy
			uint64_t tmp = 0;
			switch(m_evict) {
				case LRU:
					for (uint32_t j=0; j<m_num_of_ways; j++) {
						if (m_cache_lines[set][j].evict_tag == m_num_of_ways) {
							way_free = j;
						}
					}
					break;
				case LFU:
					tmp = m_cache_lines[set][0].evict_tag;
					way_free = 0;
					for (uint32_t j=1; j<m_num_of_ways; j++) {
						if (tmp > m_cache_lines[set][j].evict_tag) {
							tmp = m_cache_lines[set][j].evict_tag;
							way_free = j;
						}
					}
					break;
				case RAND:
					way_free = rand()%4;
					break;
				default:
					assert(0);
			}

			// evicting the cache-block in way_free (found above)
			// if the block is dirty then writing back to higher level cache/memory module (any block cached in lower level cache must be in its parent caches by inclusion)
			if (m_write_back && m_cache_lines[set][way_free].dirty) {
				delay += m_downstream_cacheblock_delay;

				// notify the parent cache so that it can mark its block dirty with new written data
				if (m_parent) {
					m_parent->handle_writeback(payload.get_address());
					delay += WRITEBACK_NOTIFICATION_DELAY;
				}

				// notifying every child cache that this block is going to be evicted so invalidation of this block is required in case if they are being cached
				if (m_child) {
					for (uint32_t i=0; i<m_child->size(); i++) {
						(*m_child)[i]->handle_invalidation_request(payload.get_address(), delay);
					}
				}
			}
		}

		// requesting cache block from higher level cache/memory module
		if (m_parent) {
			// for lower level caches, requesting the block from next higher cache in hierarchy
			m_parent->update(payload, delay);
		}
		delay += m_upstream_cacheblock_delay;

		// caching this new block
		m_cache_lines[set][way_free].valid = true;
		m_cache_lines[set][way_free].dirty = false;
		m_cache_lines[set][way_free].tag = tag;
		if (m_evict == LRU) {
			for (uint32_t j=0; j<m_num_of_ways; j++) {
				if ((uint32_t)way_free!=j && m_cache_lines[set][j].valid==true) {
					m_cache_lines[set][j].evict_tag++;
				}
				assert(m_cache_lines[set][j].evict_tag <= m_num_of_ways);
			}
			m_cache_lines[set][way_free].evict_tag = 1;
		} else {
			m_cache_lines[set][way_free].evict_tag = 0;
		}
		if (cmd == tlm::TLM_WRITE_COMMAND) {					// write miss
			// only the lowest level cache would update this block and mark it as dirty
			if (!m_child) {
				if (m_write_back) {
					m_cache_lines[set][way_free].dirty = true;
					delay += m_write_cache_delay;
				} else {
					//delay += m_downstream_cacheblock_delay;
					// for write-through policy, we assume that there are write buffers b/w cache and higher level cache/memory module so as to hide the write word delay to this cache
					// hence delay not updated here
				}
			} else {
				delay += m_read_cache_delay;
			}
		} else if (cmd == tlm::TLM_READ_COMMAND) {			// read miss
			delay += m_read_cache_delay;
		}
	}
}




void cache::set_parent(cache *parent) {
	m_parent = parent;
}

void cache::set_children(std::vector< cache * > *child) {
	m_child = child;
}

void cache::set_delays(sc_core::sc_time upstream, sc_core::sc_time downstream, sc_core::sc_time lookup, sc_core::sc_time write, sc_core::sc_time read) {
	m_lookup_delay = lookup;
	m_write_cache_delay = write;
	m_read_cache_delay = read;
	m_upstream_cacheblock_delay = upstream;
	m_downstream_cacheblock_delay = downstream;
}

void cache::handle_invalidation_request(addr_t req_addr, sc_core::sc_time &delay) {
	delay += INVALIDATION_NOTIFICATION_DELAY;
	// request from the parent to invalidate this cache block if it is being cached here(inclusion property)..this will be called when the parent is going to evict this block

	addr_t addr = (req_addr/m_cache_line_size)*m_cache_line_size;			// rounded to cache-block address
	// finding out the cache set for this address for lookup
	uint32_t set = (addr >> (uint32_t) (log2((double) WORD_SIZE) + log2((double) m_cache_line_size/WORD_SIZE))) & ((1 << (uint32_t) log2((double)m_num_of_sets)) - 1);
	// as well as the tag
	addr_t tag = (addr >> (uint32_t) (log2((double) WORD_SIZE) + log2((double) m_cache_line_size/WORD_SIZE) + log2((double) m_num_of_sets)));

	for (uint32_t i=0; i<m_num_of_ways; i++) {
		if (m_cache_lines[set][i].valid && m_cache_lines[set][i].tag==tag) {
			m_cache_lines[set][i].valid = false;
			// lru stuff!!
			if (m_evict == LRU) {
				for (uint32_t j=0; j<m_num_of_ways; j++) {
					if ((uint32_t)i!=j && m_cache_lines[set][j].valid==true && m_cache_lines[set][j].evict_tag>m_cache_lines[set][i].evict_tag) {
						m_cache_lines[set][j].evict_tag--;
					}
					assert(m_cache_lines[set][j].evict_tag <= m_num_of_ways);
				}
				m_cache_lines[set][i].evict_tag = m_num_of_ways;
			}
			break;
		}
	}

	// notifying about invalidating this block in lower level caches as well
	if (m_child) {
		for (uint32_t i=0; i<m_child->size(); i++) {
			(*m_child)[i]->handle_invalidation_request(req_addr, delay);
		}
	}
}


void cache::handle_writeback(addr_t req_addr) {
	// writeback request from the child...marking this block dirty now in this cache

	addr_t addr = (req_addr/m_cache_line_size)*m_cache_line_size;			// rounded to cache-block address
	// finding out the cache set for this address for lookup
	uint32_t set = (addr >> (uint32_t) (log2((double) WORD_SIZE) + log2((double) m_cache_line_size/WORD_SIZE))) & ((1 << (uint32_t) log2((double)m_num_of_sets)) - 1);
	// as well as the tag
	addr_t tag = (addr >> (uint32_t) (log2((double) WORD_SIZE) + log2((double) m_cache_line_size/WORD_SIZE) + log2((double) m_num_of_sets)));

	for (uint32_t i=0; i<m_num_of_ways; i++) {
		if (m_cache_lines[set][i].valid && m_cache_lines[set][i].tag==tag) {
			assert(m_cache_lines[set][i].dirty == false);
			m_cache_lines[set][i].dirty = true;
			break;
		}
	}
}





