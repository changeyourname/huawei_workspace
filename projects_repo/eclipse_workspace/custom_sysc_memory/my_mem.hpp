// instantiates the OVP ram module

#ifndef __MY_MEM_H__
#define __MY_MEM_H__

#include <tlm>

#include "tlm_wrapper_bridge.hpp"
#include "ovpworld.org/memory/ram/1.0/tlm2.0/tlmMemory.hpp"

class my_mem : public sc_core::sc_module, virtual public tlm::tlm_fw_transport_if< > {
public:
	tlm::tlm_target_socket< > m_tsocket;

	my_mem(sc_core::sc_module_name, const char *memory_socket, sc_dt::uint64 high_address, unsigned int memory_width = 4);

private:
	ram m_ram;
	tlm_wrapper_bridge m_bridge;

	// have to supply these functions for hierarchical connectivity..they dont do anything in this module
	// avoiding this would result in compilation error like: 'cannot declare field 'Executive::queue' to be of abstract'
	tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase& phase, sc_core::sc_time& t);
	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);
	bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);
	unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
};

#endif
