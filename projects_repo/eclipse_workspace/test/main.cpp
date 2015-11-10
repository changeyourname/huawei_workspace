/*#include <tlm>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>

class target : public sc_core::sc_module {
public:
	std::vector< tlm_utils::simple_target_socket<target> * > m_tsocket;

	target(sc_core::sc_module_name name) : sc_module(name) {
		m_tsocket.reserve(2);
		m_tsocket.push_back(new tlm_utils::simple_target_socket<target> ("m_tsocket[0]"));
		m_tsocket[0]->register_b_transport(this, &target::b_transport);

		m_tsocket.push_back(new tlm_utils::simple_target_socket<target> ("m_tsocket[1]"));
		m_tsocket[1]->register_b_transport(this, &target::b_transport);
	}

	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay) {

	}
};

class initiator : public sc_core::sc_module {
public:
	tlm_utils::simple_initiator_socket<initiator> m_isocket[2];
	initiator(sc_core::sc_module_name name) : sc_module(name) {

	}
};

int sc_main(int argc, char *argv[]) {
	target t("target");
	initiator i("initiator");

	i.m_isocket[0](*(t.m_tsocket[0]));
	i.m_isocket[1](*(t.m_tsocket[1]));

	sc_core::sc_start();

	return 0;
}*/

#include <stdio.h>
#include <assert.h>
#include <vector>

class abc {
public :
	int a;
	abc() {a=4;}
	abc(int a) : a(a) {}
};

int main(int argc, char *argv[]) {
	std::vector< abc > *test;
	test = new std::vector< abc >[2];

	test[0].reserve(4);
	test[1].reserve(6);

	for (int i=0; i<4; i++) {
		test[0].push_back( abc(i) );
	}

	for (int i=0; i<6; i++) {
		test[1].push_back( abc(i*10) );
	}

	printf("%d\r\n", (test[1])[2].a);


	return 0;
}


