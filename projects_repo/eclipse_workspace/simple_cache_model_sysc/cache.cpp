/*
 * cache.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: uzleo
 */




#include "cache.hpp"

cache::cache(sc_core::sc_module_name name, const char *logfile, uint32_t num_masters, uint32_t size, uint32_t block_size, uint32_t num_ways, bool write_back, bool write_allocate, cache::eviction_policy evict_policy, uint32_t level)
	:	sc_module(name),
		m_trans(),
		m_num_upstream_masters(num_masters),
		m_block_size(block_size),
		m_num_of_sets(size/(block_size*num_ways)),
		m_num_of_ways(num_ways),
		m_write_back(write_back),
		m_write_allocate(write_allocate),
		m_evict_policy(evict_policy),
		m_log(false),
		m_level(level),
		m_isocket_d("m_isocket_d")
{
	// ensuring that set bits <= mem_size_bits.....sort of a corner case but not expected to occur in real cache organizations
	// if this does occur though then cache would be inefficient as it will have slots for memory words which actually dont exist in memory......cache will be bigger than memory!
	assert(log2((double) m_num_of_sets) <= log2((double) MEM_SIZE));

	m_blocks.resize(m_num_of_sets);
	for (uint32_t i=0; i<m_num_of_sets; i++) {
		m_blocks[i].resize(m_num_of_ways);
		for (uint32_t j=0; j<m_num_of_ways; j++) {
			m_blocks[i][j].state = cache_block::I;
		}
	}

	m_tsocket_d = new tlm_utils::simple_target_socket< cache >[m_num_upstream_masters];
	for (uint32_t i=0; i<m_num_upstream_masters; i++) {
		m_tsocket_d[i].register_b_transport(this, &cache::b_transport);
	}

	if (m_level > 1) {		// not first level cache
		m_isocket_u = new tlm_utils::simple_initiator_socket< cache >[m_num_upstream_masters];
	}

	if (m_level < LLC_LEVEL) {			// not last level cache
		m_tsocket_u = new tlm_utils::simple_target_socket< cache >;
		m_tsocket_u->register_b_transport(this, &cache::b_transport);
	}

	m_fid = fopen(logfile, "w+");
	assert(m_fid);
	fprintf(m_fid, "CACHE_CONFIG \r\n");
	fprintf(m_fid, "total_cache_size:%dB", size);
	fprintf(m_fid, "..cache_block_size:%dB", m_block_size);
	fprintf(m_fid, "..num_of_sets:%d", m_num_of_sets);
	fprintf(m_fid, "..num_of_ways:%d", m_num_of_ways);
	fprintf(m_fid, "..num_of_children:%d", m_num_upstream_masters);
	fprintf(m_fid, "..write_back:%d", m_write_back);
	fprintf(m_fid, "..write_allocate:%d", m_write_allocate);
	fprintf(m_fid, "..evict_policy:%d\r\n\r\n", m_evict_policy);
	fflush(m_fid);
}


cache::~cache() {
	delete[] m_tsocket_d;
	if (m_level > 1) {
		delete[] m_isocket_u;
	}
	if (m_level < LLC_LEVEL) {
		delete m_tsocket_u;
	}
}


void cache::do_logging() {
	m_log = true;
}

void cache::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay) {
	uint64_t req_addr = trans.get_address();
	tlm::tlm_command cmd = trans.get_command();
	unsigned char *ptr = trans.get_data_ptr();

	uint64_t block_addr, tag;
	uint32_t set;
	blkAddr_set_tag(req_addr, block_addr, set, tag);

	bool evict_needed;
	uint32_t way_free;

	if (cache_lookup(req_addr, evict_needed, way_free)) {
		// cache hit

		// checking for special request
		if (req_addr==-1 && cmd==tlm::TLM_WRITE_COMMAND) {
			if (*ptr == 0x21) {
				// request from child that it is now caching this block in M state
				if (m_blocks[set][way_free].state==cache_block::M || m_blocks[set][way_free].state==cache_block::S) {
					m_blocks[set][way_free].state = cache_block::MBS;
					// forwarding this special request to further downstream caches if present
					if (m_level < LLC_LEVEL) {
						update_other_cache(true, delay);
					}
				}
			} else if (*ptr == 0x12) {
				// request from parent for back-invalidation
				if (m_blocks[set][way_free].state==cache_block::S || m_block[set][way_free].state==cache_block::MBS) {
					m_blocks[set][way_free].state = cache_block::I;
				} else {
					assert(m_write_back);		// this cache has to be write-back
					// writing-back the data to the cache that initially requested the back-invalidation so that it can write-back to its parent and invalidate its corresponding block

				}
			}
		} else {
			// normal request path
			if (m_log) {
				fprintf(m_fid, "cache hit for 0x%08x", (uint32_t)trans.get_address());
				fprintf(m_fid, "..tag=0x%08x", (uint32_t)tag);
				fprintf(m_fid, "..set=%d\r\n", set);
				fflush(m_fid);			// disable this when not debugging
			}

			if (cmd == tlm::TLM_WRITE_COMMAND) {
				if (m_write_back) {
					if (m_blocks[set][way_free].state == cache_block::S) {
						m_blocks[set][way_free].state = cache_block::M;
						update_other_cache(true, delay);
					}
				} else {
					// writing through downstream
					m_trans.set_write();
					m_trans.set_address(block_addr);
					send_request(true, delay);
				}
			} else {
				// todo: delay
			}
		}
	} else {
		//TODO: assertions if special request doesnt result in a hit!!

		// cache miss
		if (m_log) {
			fprintf(m_fid, "cache miss for 0x%08x", (uint32_t)trans.get_address());
			fprintf(m_fid, "..tag=0x%08x", (uint32_t)tag);
			fprintf(m_fid, "...set=%d\r\n", set);
			fflush(m_fid);			//TODO: disable this after debugging
		}

		if (evict_needed) {
			do_eviction(req_addr, way_free, delay);
		}

		// fetch the block from downstream
		m_trans.set_read();
		m_trans.set_address(block_addr);
		send_request(true, delay);

		// update the state of cache block
		update_block_state(req_addr, cmd, way_free, delay);
	}

	if (m_log) {
		print_cache_set(set);
	}

	trans.set_response_status(tlm::TLM_OK_RESPONSE);
}


void cache::print_cache_set(uint32_t set) {
	for (uint32_t x=0; x<m_num_of_ways; x++) {
		fprintf(m_fid, "way[%d]..", x);
		fprintf(m_fid, "state=%d..", m_blocks[set][x].state);
		fprintf(m_fid, "tag=0x%08x..", (uint32_t)m_blocks[set][x].tag);
		fprintf(m_fid, "lru=%d\r\n", m_blocks[set][x].evict_tag);
	}
	fprintf(m_fid, "------------------\r\n");
	fflush(m_fid);			//TODO: disable this after debugging
}


void cache::update_block_state(uint64_t req_addr, tlm::tlm_command cmd, uint32_t way_free, sc_core::sc_time &delay) {
	uint64_t block_addr, tag;
	uint32_t set;
	blkAddr_set_tag(req_addr, block_addr, set, tag);

	assert(m_blocks[set][way_free].state == cache_block::I);
	m_blocks[set][way_free].tag = tag;
	if (cmd == tlm::TLM_WRITE_COMMAND) {
		if (m_write_back) {
			m_blocks[set][way_free].state = cache_block::M;
			update_other_cache(true, delay);
		} else {
			m_blocks[set][way_free].state = cache_block::S;
			// writing through downstream
			m_trans.set_write();
			m_trans.set_address(block_addr);
			send_request(true, delay);
		}
	} else {
		m_blocks[set][way_free].state = cache_block::S;
	}

	// eviction policy stuff for this newly cached block
	if (m_evict_policy == LRU) {
		for (uint32_t j=0; j<m_num_of_ways; j++) {
			if (way_free!=j && m_blocks[set][j].state!=cache_block::I) {
				m_blocks[set][j].evict_tag++;
			}
			assert(m_blocks[set][way_free].evict_tag <= m_num_of_ways);
		}
		m_blocks[set][way_free].evict_tag = 1;
	} else {
		m_blocks[set][way_free].evict_tag = 0;
	}
}


void cache::update_other_cache(bool parent, sc_core::sc_time &delay) {
	// sends a special write request with all addr bits high and single byte data of 0x12....can also use set_extensions as well
	m_trans.set_write();
	m_trans.set_address(-1);			// special request (64 address bits all set to 1)
	unsigned char *ptr = new unsigned char(parent?0x12:0x21);
	m_trans.set_data_ptr(ptr);

	send_request(parent, delay);
	delete ptr;
}

void cache::blkAddr_set_tag(uint64_t req_addr, uint64_t &block_addr, uint32_t &set, uint64_t &tag) {
	block_addr = (req_addr/m_block_size)*m_block_size;
	set = (block_addr >> (uint32_t)(log2((double)WORD_SIZE) + log2((double)m_block_size/WORD_SIZE))) & ((1 << (uint32_t)log2((double)m_num_of_sets)) - 1);
	tag = (req_addr >> (uint32_t)(log2((double)WORD_SIZE) + log2((double)m_block_size/WORD_SIZE) + log2((double) m_num_of_sets)));
}


bool cache::cache_lookup(uint64_t req_addr, bool &evict_needed, uint32_t &way_free) {
	uint64_t block_addr, tag;
	uint32_t set;
	blkAddr_set_tag(req_addr, block_addr, set, tag);

	evict_needed = true;

	for (uint32_t i=0; i<m_num_of_ways; i++) {
		if (m_blocks[set][i].state != cache_block::I) {
			if (m_blocks[set][i].tag == tag) {
				evict_needed = false;
				way_free = i;
				return true;
			}
		} else {
			evict_needed = false;
			way_free = i;
		}
	}

	if (evict_needed) {
		way_free = find_way_evict(set);
	}

	return false;
}


uint32_t cache::find_way_evict(uint32_t set) {
	int way_free = -1;

	switch(m_evict_policy) {
		case LRU:
		{
			for (uint32_t j=0; j<m_num_of_ways; j++) {
				if (m_blocks[set][j].evict_tag == m_num_of_ways) {
					way_free = j;
				}
			}
			assert(way_free != -1);
			break;
		}
		case LFU:
		{
			uint64_t tmp = m_blocks[set][0].evict_tag;
			way_free = 0;
			for (uint32_t j=1; j<m_num_of_ways; j++) {
				if (tmp > m_blocks[set][j].evict_tag) {
					tmp = m_blocks[set][j].evict_tag;
					way_free = j;
				}
			}
			break;
		}
		case FIFO:
		{
			//TODO
			break;
		}
		case RAND:
		{
			way_free = rand()%4;
			break;
		}
		default:
		{
			assert(0);
		}
	}

	return (uint32_t)way_free;
}


void cache::do_eviction(uint64_t req_addr, uint32_t way_free, sc_core::sc_time &delay) {
	uint64_t block_addr, tag;
	uint32_t set;
	blkAddr_set_tag(req_addr, block_addr, set, tag);

	// BACK INVALIDATION
	if (m_level > 1) {
		update_other_cache(false, delay);
	}

	// incase this block is in 'S' then no writeback is needed
	// incase this block is in 'MBS' then this means that this block is being cached somewhere upstream in 'M' state which would have been written back via the back-invalidation path as above
	if (m_blocks[set][way_free].state==cache_block::M) {
		assert(m_write_back);			// this should be writeback cache
		// writing through downstream..if a cache exists on the downstream path then it can update the status of its block (MBS) to M
		m_trans.set_write();
		m_trans.set_address(block_addr);
		send_request(true, delay);
	}
}


void cache::send_request(bool downstream, sc_core::sc_time &delay) {
	m_trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
	if (downstream) {
		m_isocket_d->b_transport(m_trans, delay);
	} else {
		for (uint32_t i=0; i<m_num_upstream_masters; i++) {
			m_isocket_u[i]->b_transport(m_trans, delay);
		}
	}
	assert(m_trans.get_response_status() == tlm::TLM_OK_RESPONSE);
}






//TODO: use tlm_extension



//TODO: write-allocate
//TODO: fifo eviction policy
//TODO: model timing














