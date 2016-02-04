/*
 * Copyright (c) 2015, University of Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Matthias Jung
 */

/**
 * @file
 *
 *  Example top level file for SystemC-TLM integration with C++-only
 *  instantiation.
 *
 */

#include <tlm_utils/simple_target_socket.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <systemc>
#include <tlm>
#include <typeinfo>
#include <vector>
#include <string>

#include "base/statistics.hh"
#include "base/str.hh"
#include "base/trace.hh"
#include "cpu/base.hh"
#include "sc_logger.hh"
#include "sc_module.hh"
#include "sc_port.hh"
#include "sc_target.hh"
#include "cache/cache.hpp"
#include "sim/cxx_config_ini.hh"
#include "sim/cxx_manager.hh"
#include "sim/init_signals.hh"
#include "sim/serialize.hh"
#include "sim/simulate.hh"
#include "sim/stat_control.hh"
#include "sim/system.hh"
#include "stats.hh"
#include "global.hh"


void usage(const std::string &prog_name)
{
    std::cerr << "Usage: " << prog_name << (
        " <config_file.ini> [ <option> ]\n\n"
        "OPTIONS:\n"

        "    -o <offset>                  -- set memory offset\n"
        "    -p <object> <param> <value>  -- set a parameter\n"
        "    -v <object> <param> <values> -- set a vector parameter from a\n"
        "                                    comma separated values string\n"
        "    -d <flag>                    -- set a debug flag\n"
        "                                    (-<flag> clear a flag)\n"
        "    -D                           -- debug on\n"
        "    -e <ticks>                   -- end of simulation after a \n"
        "                                    given number of ticks\n"
        "    -mem                         -- enable SystemC memory as main memory\n"
        "    -n_cpu <value>               -- set number of gem5 smp cores\n"
        "\n"
        );
    std::exit(EXIT_FAILURE);
}

class SimControl : public Gem5SystemC::Module
{
    protected:
    int argc;
    char **argv;
    CxxConfigManager *config_manager;
    Gem5SystemC::Logger logger;

    Tick sim_end;
    bool debug;
    unsigned int offset;

    public:
    SC_HAS_PROCESS(SimControl);

    bool enable_SystemC_mem;
    unsigned int num_gem5_smp_cores;

    SimControl(sc_core::sc_module_name name, int argc_, char **argv_);
    void before_end_of_elaboration();
    bool getDebugFlag() { return debug; }
    unsigned int getOffset() { return offset; }
    void run();        
};

SimControl::SimControl(sc_core::sc_module_name name,
                       int argc_,
                       char **argv_) : Gem5SystemC::Module(name),
                                       argc(argc_),
                                       argv(argv_)
{
    SC_THREAD(run);

    std::string prog_name(argv[0]);
    unsigned int arg_ptr = 1;

    if (argc == 1) {
        usage(prog_name);
    }

    cxxConfigInit();
    Gem5SystemC::registerSCPorts();

    Trace::setDebugLogger(&logger);

    Gem5SystemC::setTickFrequency();
    sc_core::sc_set_time_resolution(1, sc_core::SC_PS);

    Gem5SystemC::Module::setupEventQueues(*this);
    initSignals();

    Stats::initSimStats();
    Stats::registerHandlers(CxxConfig::statsReset, CxxConfig::statsDump);

    Trace::enable();

    sim_end = 0;
    debug = false;
    offset = 0;
    enable_SystemC_mem = false;
    num_gem5_smp_cores = 0;

    const std::string config_file(argv[arg_ptr]);

    CxxConfigFileBase *conf = new CxxIniFile();

    if (!conf->load(config_file.c_str())) {
        std::cerr << "Can't open config file: " << config_file << '\n';
        std::exit(EXIT_FAILURE);
    }
    arg_ptr++;

    config_manager = new CxxConfigManager(*conf);

    try {
        while (arg_ptr < argc) {
            std::string option(argv[arg_ptr]);
            arg_ptr++;
            unsigned num_args = argc - arg_ptr;

            if (option == "-p") {
                if (num_args < 3) {
                    usage(prog_name);
                }

                config_manager->setParam(argv[arg_ptr], argv[arg_ptr + 1],
                argv[arg_ptr + 2]);
                arg_ptr += 3;
            } else if (option == "-v") {
                std::vector<std::string> values;

                if (num_args < 3) {
                    usage(prog_name);
                }
                tokenize(values, argv[2], ',');
                config_manager->setParamVector(argv[arg_ptr],
                                               argv[arg_ptr],
                                               values);
                arg_ptr += 3;
            } else if (option == "-d") {
                if (num_args < 1) {
                    usage(prog_name);
                }
                if (argv[arg_ptr][0] == '-') {
                    clearDebugFlag(argv[arg_ptr] + 1);
                } else {
                    setDebugFlag(argv[arg_ptr]);
                }
                arg_ptr++;
            } else if (option == "-e") {
                if (num_args < 1) {
                    usage(prog_name);
                }
                std::istringstream(argv[arg_ptr]) >> sim_end;
                arg_ptr++;
            } else if (option == "-D") {
                debug = true;
            } else if (option == "-o") {
                if (num_args < 1) {
                    usage(prog_name);
                }
                std::istringstream(argv[arg_ptr]) >> offset;
                arg_ptr++;
                /* code */
            } else if (option == "-mem") {
                enable_SystemC_mem = true;
            } else if (option == "-n_cpu") {
                if (num_args < 1) {
                    usage(prog_name);
                }
                std::istringstream(argv[arg_ptr]) >> num_gem5_smp_cores;
                arg_ptr++;
            } else {
                usage(prog_name);
            }
        }
    } catch (CxxConfigManager::Exception &e) {
        std::cerr << e.name << ": " << e.message << "\n";
        std::exit(EXIT_FAILURE);
    }

    CxxConfig::statsEnable();
    getEventQueue(0)->dump();

    try {
        config_manager->instantiate();
    } catch (CxxConfigManager::Exception &e) {
        std::cerr << "Config problem in sim object "
                  << e.name << ": " << e.message << "\n";
        std::exit(EXIT_FAILURE);
    }
}

void
SimControl::before_end_of_elaboration()
{
    try {
        config_manager->initState();
        config_manager->startup();
    } catch (CxxConfigManager::Exception &e) {
        std::cerr << "Config problem in sim object "
            << e.name << ": " << e.message << "\n";
        std::exit(EXIT_FAILURE);
    }
}

void
SimControl::run()
{
    GlobalSimLoopExitEvent *exit_event = NULL;

    if(sim_end == 0) {
        exit_event = simulate();
    } else {
        exit_event = simulate(sim_end);
    }

    std::cerr << "Exit at tick " << curTick()
              << ", cause: " << exit_event->getCause() << '\n';

    getEventQueue(0)->dump();

#if TRY_CLEAN_DELETE
    config_manager->deleteObjects();
#endif
}


void
reportHandler(const sc_core::sc_report &report,
              const sc_core::sc_actions &actions)
{
    uint64_t systemc_time = report.get_time().value();
    uint64_t gem5_time = curTick();

    std::cerr << report.get_time();

    if (gem5_time < systemc_time) {
        std::cerr << " (<) ";
    } else if (gem5_time > systemc_time) {
        std::cerr << " (!) ";
    } else {
        std::cerr << " (=) ";
    }

    std::cerr << ": " << report.get_msg_type()
              << ' ' << report.get_msg() << '\n';
}


int
sc_main(int argc, char **argv)
{
    sc_core::sc_report_handler::set_handler(reportHandler);

    SimControl sim_control("gem5", argc, argv);
    unsigned long long int size = 512*1024*1024ULL;
    unsigned char *mem = new unsigned char[size];    
    
    if (sim_control.enable_SystemC_mem) {
        // if gem5 system uses SystemC memory
        Target *membus;    
        Gem5SystemC::sc_transactor 
                *membus_port = dynamic_cast<Gem5SystemC::sc_transactor *> (   
                                    sc_core::sc_find_object("gem5.membus_port")
                                );          
        if (membus_port) {
            SC_REPORT_INFO("sc_main", "gem5.membus_port Found");
            membus = new Target("membus",
                                sim_control.getDebugFlag(),
                                size,
                                sim_control.getOffset(),
                                mem,
                                membus_port->getOwner());
            membus->socket.bind(*membus_port);
        } else {
            SC_REPORT_FATAL("sc_main", "gem5.membus_port Not Found");
            std::exit(EXIT_FAILURE);
        }
    }  



//    std::vector< Gem5SystemC::sc_transactor * > smp_cache_ports;
//    std::vector< cache_dum * > smp_caches;
//    std::string temp;
//    
//    for (int i=0; i<sim_control.num_gem5_smp_cores*2; i++) {
//        // icache hooks
//        temp = (i%2==0) ? "gem5.icache_" + std::to_string(i/2) : 
//                          "gem5.dcache_" + std::to_string(i/2) ;
//        smp_cache_ports.push_back( 
//            dynamic_cast<Gem5SystemC::sc_transactor *> (
//                sc_core::sc_find_object(temp.c_str())
//            )
//        );
//        if (smp_cache_ports[i]) {
//            temp = temp + " found";
//            SC_REPORT_INFO("sc_main", temp.c_str());
//            
//            temp = (i%2==0) ? "icache_" + std::to_string(i/2) :
//                              "dcache_" + std::to_string(i/2) ;
//            smp_caches.push_back(new cache_dum(temp.c_str()));
//            smp_caches[i]->socket.bind(*smp_cache_ports[i]);
//        } else {
//            temp = temp + " not found!";
//            SC_REPORT_FATAL("sc_main", temp.c_str());
//            std::exit(EXIT_FAILURE);
//        }        
//    }










    //TODO: automate following based on num of cpus!!
    cache::cache_specs specs;
    specs.num_masters = 1;
    specs.size = 65536;
    specs.block_size = 4*WORD_SIZE;
    specs.num_ways = 4;
    specs.write_back = true;
    specs.write_allocate = true;
    specs.evict_policy = cache::LRU;       

    cache *icache_0;
    Gem5SystemC::sc_transactor *gem5_icache_0 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.icache_0"));
    if (gem5_icache_0) {     
        icache_0 = new cache("icache_0", 
                             0, 
                             specs, 
                             1, 
                             0xD000D000
                             #ifdef CACHE_DEBUG
                             , "log/icache_0.log"
                             #endif
                            );
        icache_0->set_delays(1, 1, 1);                             
        icache_0->do_logging();        
                             
        icache_0->m_tsocket_d[0].bind(*gem5_icache_0);
    } else {
        SC_REPORT_FATAL("sc_main", "gem5.icache_0 not found");
        std::exit(EXIT_FAILURE);
    }         

    cache *dcache_0;                                                
    Gem5SystemC::sc_transactor *gem5_dcache_0 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.dcache_0")); 
    if (gem5_dcache_0) {                                        
        dcache_0 = new cache("dcache_0", 
                             1, 
                             specs, 
                             1, 
                             0xD000E000
                             #ifdef CACHE_DEBUG
                             , "log/dcache_0.log"
                             #endif
                            );
        dcache_0->set_delays(1, 1, 1);                             
        dcache_0->do_logging();
                             
        dcache_0->m_tsocket_d[0].bind(*gem5_dcache_0);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.dcache_0 not found");
        std::exit(EXIT_FAILURE);        
    }
    
    
    #if 1
    cache *icache_1;                                                
    Gem5SystemC::sc_transactor *gem5_icache_1 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.icache_1")); 
    if (gem5_icache_1) {                                        
        icache_1 = new cache("icache_1", 
                             2, 
                             specs, 
                             1, 
                             0xD000F000
                             #ifdef CACHE_DEBUG
                             , "log/icache_1.log"
                             #endif
                            );
        icache_1->set_delays(1, 1, 1);                             
        icache_1->do_logging();
                             
        icache_1->m_tsocket_d[0].bind(*gem5_icache_1);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.icache_1 not found");
        std::exit(EXIT_FAILURE);        
    } 
    
    cache *dcache_1;                                                
    Gem5SystemC::sc_transactor *gem5_dcache_1 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.dcache_1")); 
    if (gem5_dcache_1) {                                        
        dcache_1 = new cache("dcache_1", 
                             3, 
                             specs, 
                             1, 
                             0xD0010000
                             #ifdef CACHE_DEBUG
                             , "log/dcache_1.log"
                             #endif
                            );
        dcache_1->set_delays(1, 1, 1);                             
        dcache_1->do_logging();
                             
        dcache_1->m_tsocket_d[0].bind(*gem5_dcache_1);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.dcache_1 not found");
        std::exit(EXIT_FAILURE);        
    }
    
    cache *icache_2;                                                
    Gem5SystemC::sc_transactor *gem5_icache_2 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.icache_2")); 
    if (gem5_icache_2) {                                        
        icache_2 = new cache("icache_2", 
                             4, 
                             specs, 
                             1, 
                             0xD0011000
                             #ifdef CACHE_DEBUG
                             , "log/icache_2.log"
                             #endif
                            );
        icache_2->set_delays(1, 1, 1);                             
        icache_2->do_logging();
                             
        icache_2->m_tsocket_d[0].bind(*gem5_icache_2);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.icache_2 not found");
        std::exit(EXIT_FAILURE);        
    } 
    
    cache *dcache_2;                                                
    Gem5SystemC::sc_transactor *gem5_dcache_2 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.dcache_2")); 
    if (gem5_dcache_2) {                                        
        dcache_2 = new cache("dcache_2", 
                             5, 
                             specs, 
                             1, 
                             0xD0012000
                             #ifdef CACHE_DEBUG
                             , "log/dcache_2.log"
                             #endif
                            );
        dcache_2->set_delays(1, 1, 1);                             
        dcache_2->do_logging();
                             
        dcache_2->m_tsocket_d[0].bind(*gem5_dcache_2);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.dcache_2 not found");
        std::exit(EXIT_FAILURE);        
    }        
    
    cache *icache_3;                                                
    Gem5SystemC::sc_transactor *gem5_icache_3 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.icache_3")); 
    if (gem5_icache_3) {                                        
        icache_3 = new cache("icache_3", 
                             6, 
                             specs, 
                             1, 
                             0xD0013000
                             #ifdef CACHE_DEBUG
                             , "log/icache_3.log"
                             #endif
                            );
        icache_3->set_delays(1, 1, 1);                             
        icache_3->do_logging();
                             
        icache_3->m_tsocket_d[0].bind(*gem5_icache_3);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.icache_3 not found");
        std::exit(EXIT_FAILURE);        
    } 
    
    cache *dcache_3;                                                
    Gem5SystemC::sc_transactor *gem5_dcache_3 = dynamic_cast<Gem5SystemC::sc_transactor *>
                                                (sc_core::sc_find_object("gem5.dcache_3")); 
    if (gem5_dcache_3) {                                        
        dcache_3 = new cache("dcache_3", 
                             7, 
                             specs, 
                             1, 
                             0xD0014000
                             #ifdef CACHE_DEBUG
                             , "log/dcache_3.log"
                             #endif
                            );
        dcache_3->set_delays(1, 1, 1);                             
        dcache_3->do_logging();
                             
        dcache_3->m_tsocket_d[0].bind(*gem5_dcache_3);  
    } else {        
        SC_REPORT_FATAL("sc_main", "gem5.dcache_3 not found");
        std::exit(EXIT_FAILURE);        
    }    
    #endif
 
 
 
 
 
 
    
    
    
    
    
    specs.num_masters = 8;
    specs.size = 2*1024*1024;
    specs.block_size = 4*WORD_SIZE;
    specs.num_ways = 16;    
    cache *l2cache;
    l2cache = new cache("l2cache", 
                         8, 
                         specs, 
                         2, 
                         0xD0015000
                         #ifdef CACHE_DEBUG
                         , "log/l2cache.log"
                         #endif
                       );
    l2cache->set_delays(5, 10, 10);
    l2cache->do_logging();
    
    l2cache->m_tsocket_d[0].bind(*(icache_0->m_isocket_d));
    l2cache->m_tsocket_d[1].bind(*(dcache_0->m_isocket_d));
    l2cache->m_tsocket_d[2].bind(*(icache_1->m_isocket_d));
    l2cache->m_tsocket_d[3].bind(*(dcache_1->m_isocket_d));
    l2cache->m_tsocket_d[4].bind(*(icache_2->m_isocket_d));
    l2cache->m_tsocket_d[5].bind(*(dcache_2->m_isocket_d));
    l2cache->m_tsocket_d[6].bind(*(icache_3->m_isocket_d));
    l2cache->m_tsocket_d[7].bind(*(dcache_3->m_isocket_d));
    l2cache->m_isocket_u[0].bind(*(icache_0->m_tsocket_u));
    l2cache->m_isocket_u[1].bind(*(dcache_0->m_tsocket_u));
    l2cache->m_isocket_u[2].bind(*(icache_1->m_tsocket_u));
    l2cache->m_isocket_u[3].bind(*(dcache_1->m_tsocket_u));
    l2cache->m_isocket_u[4].bind(*(icache_2->m_tsocket_u));
    l2cache->m_isocket_u[5].bind(*(dcache_2->m_tsocket_u));
    l2cache->m_isocket_u[6].bind(*(icache_3->m_tsocket_u));
    l2cache->m_isocket_u[7].bind(*(dcache_3->m_tsocket_u));    
    
    
    
   
   
   
   
 
   
   
                                                                                       

    sc_core::sc_start();

    SC_REPORT_INFO("sc_main", "End of Simulation");
    

    // cleaning  up heap-allocated stuff!!
    if (gem5_icache_0) {
        delete icache_0;
    }
    if (gem5_dcache_0) {
        delete dcache_0;
    }
    
    #if 1
    if (gem5_icache_1) {
        delete icache_1;
    }
    if (gem5_dcache_1) {
        delete dcache_1;
    }
    if (gem5_icache_2) {
        delete icache_2;
    }
    if (gem5_dcache_2) {
        delete dcache_2;
    }
    if (gem5_icache_3) {
        delete icache_3;
    }
    if (gem5_dcache_3) {
        delete dcache_3;
    }
    #endif
    
    delete l2cache;    
        
    
    //TODO: clean up allocated global stuff from cache module!!  
    
    

    return EXIT_SUCCESS;
}



