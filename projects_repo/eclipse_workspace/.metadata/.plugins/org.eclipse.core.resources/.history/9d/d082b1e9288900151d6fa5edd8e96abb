/*
 * main.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: uzair
 */




#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <stdio.h>
#include "cache.hpp"


#define MEM_SIZE 536870912



struct req_type {
	uint64_t addr;
	tlm::tlm_command cmd;
	unsigned char wr_data[4];
	unsigned char rd_data[4];
};

#define NUM_REQ 3

class req_generator : public sc_core::sc_module {
public:
	tlm_utils::simple_initiator_socket<req_generator> *m_isocket;

	SC_HAS_PROCESS(req_generator);
	req_generator(sc_core::sc_module_name name)
	{
		m_isocket = new tlm_utils::simple_initiator_socket<req_generator>[4];			// dynamic array of isockets
		SC_THREAD(main);
	}

	void main() {
		//unsigned char *mem_no_cache = new unsigned char[MEM_SIZE];
		req_type req_stimuli[NUM_REQ] = {
											{0x00000000, tlm::TLM_READ_COMMAND},
											{0x00000004, tlm::TLM_READ_COMMAND},
											{0x00000008, tlm::TLM_READ_COMMAND}/*,
											{0x10345478, tlm::TLM_READ_COMMAND},
											{0x10345878, tlm::TLM_WRITE_COMMAND, {1,2,3,4}},
											{0x11345078, tlm::TLM_READ_COMMAND},
											{0x11345278, tlm::TLM_READ_COMMAND},
											{0x11345478, tlm::TLM_READ_COMMAND},
											{0x11345a78, tlm::TLM_READ_COMMAND}*/
								  	  	};

		while(1) {
			tlm::tlm_generic_payload trans;

			trans.set_data_length(4);
			for (int i=0; i<NUM_REQ; i++) {
				sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

				trans.set_address(req_stimuli[i].addr);
				if (req_stimuli[i].cmd == tlm::TLM_WRITE_COMMAND) {
					trans.set_command(tlm::TLM_WRITE_COMMAND);
					trans.set_data_ptr((unsigned char *)&req_stimuli[i].wr_data);
				} else {
					trans.set_command(tlm::TLM_READ_COMMAND);
					trans.set_data_ptr((unsigned char *)&req_stimuli[i].rd_data);
				}

				m_isocket[0]->b_transport(trans, delay);

				wait(2, sc_core::SC_NS);
			}

			//assert(0);
			while(1) {
				wait(1, sc_core::SC_MS);
			}
		}
	}
};

#define WORD_SIZE 4

#define L1_TO_L2_CACHEBLOCK_DELAY sc_core::sc_time(20, sc_core::SC_NS)
#define L2_TO_L1_CACHEBLOCK_DELAY sc_core::sc_time(20, sc_core::SC_NS)

#define L2_TO_MEM_CACHEBLOCK_DELAY sc_core::sc_time(40, sc_core::SC_NS)
#define MEM_TO_L2_CACHEBLOCK_DELAY sc_core::sc_time(200, sc_core::SC_NS)

#define L1_LOOKUP_DELAY sc_core::sc_time(1, sc_core::SC_NS)
#define L1_READ_DELAY sc_core::sc_time(5, sc_core::SC_NS)
#define L1_WRITE_DELAY sc_core::sc_time(5, sc_core::SC_NS)

#define L2_LOOKUP_DELAY sc_core::sc_time(2, sc_core::SC_NS)
#define L2_READ_DELAY sc_core::sc_time(10, sc_core::SC_NS)
#define L2_WRITE_DELAY sc_core::sc_time(10, sc_core::SC_NS)

#define L1_TO_CPU_DELAY sc_core::sc_time(10, sc_core::SC_NS)
#define CPU_TO_L1_DELAY sc_core::sc_time(10, sc_core::SC_NS)


class target : public sc_core::sc_module {
private:
	unsigned char *m_mem;
	//std::vector< cache * > m_l1cache_i;
	//std::vector< cache * > m_l1cache_d;
	cache m_l2cache;
	//std::vector< cache * > *child_of_l2;
	cache m_l1cache;

public:
	std::vector< tlm_utils::simple_target_socket_tagged<target> * > m_tsocket;

	target(sc_core::sc_module_name name, unsigned char *mem)
		:	m_mem(mem),
			m_l2cache("m_l2cache", "m_l2cache", 16384, 16, 1, 1),
			m_l1cache("m_l1cache", "m_l1cache", 1024, 4, 1)
	{
		m_tsocket.reserve(4);
		char tmp[20];
		for (uint32_t i=0; i<4; i++) {
			sprintf(tmp, "m_tsocket[%d]", i);
			m_tsocket.push_back(new tlm_utils::simple_target_socket_tagged<target> (tmp));
			m_tsocket[i]->register_b_transport(this, &target::b_transport, i);
		}

		/*m_l1cache_i.reserve(4);
		for (uint32_t i=0; i<4; i++) {
			sprintf(tmp, "m_l1cache_i[%d]", i);
			m_l1cache_i.push_back(new cache(tmp, 1024, 16, 2, false));
			m_l1cache_i[i]->set_parent(&m_l2cache);
			m_l1cache_i[i]->set_children(NULL);
			m_l1cache_i[i]->set_delays((sc_core::sc_time)L2_TO_L1_CACHEBLOCK_DELAY, (sc_core::sc_time)L1_TO_L2_CACHEBLOCK_DELAY, (sc_core::sc_time) L1_LOOKUP_DELAY, (sc_core::sc_time) L1_WRITE_DELAY, (sc_core::sc_time) L1_READ_DELAY);
		}

		m_l1cache_d.reserve(4);
		for (uint32_t i=0; i<4; i++) {
			sprintf(tmp, "m_l1cache_d[%d]", i);
			m_l1cache_d.push_back(new cache(tmp, 1024, 16, 2, false));
			m_l1cache_d[i]->set_parent(&m_l2cache);
			m_l1cache_d[i]->set_children(NULL);
			m_l1cache_d[i]->set_delays((sc_core::sc_time)L2_TO_L1_CACHEBLOCK_DELAY, (sc_core::sc_time)L1_TO_L2_CACHEBLOCK_DELAY, (sc_core::sc_time) L1_LOOKUP_DELAY, (sc_core::sc_time) L1_WRITE_DELAY, (sc_core::sc_time) L1_READ_DELAY);
		}

		m_l2cache.set_parent(NULL);
		child_of_l2 = new std::vector< cache * >;
		child_of_l2->reserve(4*2);
		for (uint32_t i=0; i<4; i++) {
			child_of_l2->push_back(m_l1cache_i[i]);
			child_of_l2->push_back(m_l1cache_d[i]);
		}
		m_l2cache.set_children(child_of_l2);
		m_l2cache.set_delays((sc_core::sc_time)MEM_TO_L2_CACHEBLOCK_DELAY, (sc_core::sc_time)L2_TO_MEM_CACHEBLOCK_DELAY, (sc_core::sc_time) L2_LOOKUP_DELAY, (sc_core::sc_time) L2_WRITE_DELAY, (sc_core::sc_time) L2_READ_DELAY);
		*/
		m_l2cache.set_parent(NULL);
		m_l2cache.set_children(&m_l2cache);
		m_l2cache.do_logging();

		m_l1cache.set_parent(&m_l2cache);
		m_l1cache.do_logging();

	}

	~target() {
		// cleaning up allocated stuff
		/*for (uint32_t i=0; i<4; i++) {
			delete m_l1cache_i[i];
			delete m_l1cache_d[i];
		}
		delete child_of_l2;*/
		for (uint32_t i=0; i<4; i++) {
			delete m_tsocket[i];
		}
	}

	void b_transport(int SocketId, tlm::tlm_generic_payload &payload, sc_core::sc_time &delay) {
		uint64_t addr = (payload.get_address()/WORD_SIZE)*WORD_SIZE;
		tlm::tlm_command cmd = payload.get_command();
		uint32_t len = payload.get_data_length();
		unsigned char *ptr = payload.get_data_ptr();

		assert(addr>=0x00000000 && addr<0x20000000);

		/*static int count = 0;
		count++;*/
		if (payload.get_command() == tlm::TLM_WRITE_COMMAND) {
			delay += CPU_TO_L1_DELAY;
		}
		/*if (addr <= 0x11000000) {
			m_l1cache_d[SocketId]->update(payload, delay);
		} else {
			m_l1cache_i[SocketId]->update(payload, delay);
		}
		if (payload.get_command() == tlm::TLM_READ_COMMAND) {
			delay += L1_TO_CPU_DELAY;
		}*/
		m_l1cache.update(payload, delay);

		if (cmd == tlm::TLM_WRITE_COMMAND) {
			std::memcpy(&m_mem[addr], ptr, (unsigned long) len);
		} else {
			std::memcpy(ptr, &m_mem[addr], (unsigned long) len);
		}
	}

	void print() {
	/*	for (uint32_t i=0; i<4; i++) {
			m_l1cache_d[i]->print_cache_set(7);
			printf("----\r\n");
			m_l1cache_i[i]->print_cache_set(7);
			printf("----\r\n");
		}
		m_l2cache.print_cache_set(7);
		printf("----\r\n");*/
	}
};




int sc_main(int argc, char *argv[]) {
	unsigned char *mem = new unsigned char[MEM_SIZE];

	req_generator m_req("m_req");
	target m_target("m_target", mem);

	for (uint32_t i=0; i<4; i++) {
		m_req.m_isocket[i](*(m_target.m_tsocket[i]));
	}

	sc_core::sc_start(1, sc_core::SC_MS);

	m_target.print();

	return 0;
}
