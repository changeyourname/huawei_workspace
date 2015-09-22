/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 * icmPlatform contains the ICM platform object and other mechanisms
 * need to interface TLM2.0 to ICM.
 */

/*
 * This the the mechanism for getting systemC kernel to tell us when time is advancing.
 * Thanks to Robert Guenzel  (robert.guenzel@greensocs.com) for advice on how to do this.
 */

#ifndef __TLM_PLATFORM_H__
#define __TLM_PLATFORM_H__

#include <cstdio>
#include "sysc/tracing/sc_trace.h"
#include "sysc/kernel/sc_simcontext.h"

#include "icm/icmCpuManager.hpp"
#include "tlm.h"

using namespace sc_core;
using namespace icmCpuManager;

class time_advance : public sc_trace_file
{

protected:

    // These are all virtual functions in sc_trace_file. They need to be defined here.

     void trace(const bool& object, const std::string& name) {}
     virtual void trace( const sc_dt::sc_bit& object,  const std::string& name) {}
     void trace(const sc_dt::sc_logic& object, const std::string& name) {}
     void trace(const unsigned char& object, const std::string& name, int width) {}
     void trace(const unsigned short& object, const std::string& name, int width) {}
     void trace(const unsigned int& object, const std::string& name, int width) {}
     void trace(const unsigned long& object, const std::string& name, int width) {}
     void trace(const char& object, const std::string& name, int width) {}
     void trace(const short& object, const std::string& name, int width) {}
     void trace(const int& object, const std::string& name, int width) {}
     void trace(const long& object, const std::string& name, int width) {}
     void trace(const sc_dt::int64& object, const std::string& name, int width) {}
     void trace(const sc_dt::uint64& object, const std::string& name, int width) {}
     void trace(const float& object, const std::string& name) {}
     void trace(const double& object, const std::string& name) {}
     void trace (const sc_dt::sc_uint_base& object, const std::string& name) {}
     void trace (const sc_dt::sc_int_base& object, const std::string& name) {}
     void trace (const sc_dt::sc_unsigned& object, const std::string& name) {}
     void trace (const sc_dt::sc_signed& object, const std::string& name) {}
     void trace( const sc_dt::sc_fxval& object, const std::string& name ) {}
     void trace( const sc_dt::sc_fxval_fast& object, const std::string& name ) {}
     void trace( const sc_dt::sc_fxnum& object, const std::string& name ) {}
     void trace( const sc_dt::sc_fxnum_fast& object, const std::string& name )  {}
     virtual void trace(const sc_dt::sc_bv_base& object, const std::string& name) {}
     virtual void trace(const sc_dt::sc_lv_base& object, const std::string& name) {}
     void trace(const unsigned& object, const std::string& name, const char** enum_literals) {}

     void write_comment(const std::string& comment) {}
     void delta_cycles(bool flag) {  }

     // this is the only virtual function we actually need !!
     void cycle(bool delta_cycle);

private:
     typedef bool (*timeFn)(long double time, void *user);
     timeFn  m_advanceFn;
     void   *m_user;

public:
    // constructor and destructor
    time_advance()  {}
    ~time_advance() {}

    void set_time_unit( int exponent10_seconds ) {}
    void set_time_unit( double v, sc_time_unit tu) {}

    // call a static function when time changes, with no dependence on its class.
    void setCallback(timeFn fn, void *user) { m_advanceFn = fn; m_user = user; }
};

/// The Platform object.
/// Instantiating this is optional; the underlying constructors
/// are called anyway by calls to other constructors.
/// If you wish to set global simulation attributes you should construct
/// one of these before all other OVP objects.

class icmTLMPlatform : public sc_module, public icmPlatform {

private:

    // registers the time advance callback.
    time_advance  m_timeAdvance;

    // period of one quantum for all processors
    sc_time       m_quantum;

    static Bool advance(icmTime t, void *user) {
        icmTLMPlatform *p = (icmTLMPlatform*) user;
        double dt = t;

        // use the double, not the long double. This introduces a rounding error bug
        // in the windows cross-compiler
        return p->advanceTime(dt);
    }

    // pointer to the (static) platform
    static icmTLMPlatform *m_singleton;

    // defining this virtual fn from sc_module causes our startup to be called
    // before simulation starts
    void start_of_simulation(void);

    // defining this virtual fn from sc_module causes our shutdown to be called
    // before SystemC starts calling destructors.
    void end_of_simulation(void);

public:

    /// The constructor. Ensure this is called before any other ICM constructors.
    /// It must be called only once.
    /// @param module_name     A unique name for the platform.
    /// @param simAttrs        (optional) global simulation attributes.
    /// @param dbgProtocol     (optional) Protocol used by debugger.
    /// @param dbgPort         (optional) Debugger port number.

    icmTLMPlatform(
        sc_module_name module_name,
        icmInitAttrs   simAttrs    = ICM_INIT_DEFAULT,
        const char    *dbgProtocol = NULL,
        Uns32          dbgPort     = 0
    );

    /// Destructor (not usually called explicitly).

    ~icmTLMPlatform() { }

    /// Override the default global quantum (length of each time-slice).
    /// Should be called from the platform constructor (not during simulation).

    void    quantum(sc_time q) { m_quantum = q; }

    /// Return the current global quantum.
    /// @return current quantum.

    sc_time quantum() { return m_quantum; }

    /// Return the ICM platform object.

    static icmTLMPlatform *Instance() { return m_singleton; }
};

#endif
