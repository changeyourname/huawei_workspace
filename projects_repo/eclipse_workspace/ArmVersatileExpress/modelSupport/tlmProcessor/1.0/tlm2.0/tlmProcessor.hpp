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



#ifndef __TLM_PROCESSOR_H__
#define __TLM_PROCESSOR_H__

#include "tlm.h"                                // TLM headers
#include "tlm_utils/simple_initiator_socket.h"  // equivalent of OVP Bus Master Port
#include "tlm_utils/simple_target_socket.h"     // equivalent of OVP Bus Master Port
#include "icm/icmCpuManager.hpp"

using namespace icmCpuManager;
using namespace std;
using namespace sc_core;

class icmCpu;
class icmInitiatorExtension;

/*
 * READ THIS BEFORE TRYING TO CHANGE THE BASE TYPES USED BY OVP/TLM
 *
 * It would be nice NOT to use tlm_analysis_if for interrupts, but this class has the
 * advantage that it propagates values from drivers to receivers without using the
 * scheduler. sc_signal seems to insist on doing just that, which delays the interrupt
 * response of a processor to the end of the quantum - not satisfactory.
 *
 * The worst case is:
 * processor thread
 *     processor
 *          TLM transaction
 *              TLM BUS
 *                  TLM Slave
 *                      Slave produces interrupt.
 * (interrupt does not happen till next quantum begins).
 *
 * The objection to using tlm_analysis_if is that other models use sc_signal so need
 * converters to connect up  to TLM models.
 *
 */

//
// Use this to connect a SystemC sc_in to an OVP processor interrupt.
//
class icmCpuInterrupt: public tlm::tlm_analysis_if<int>
{

public:
    /// icmCpuInterrupt Constructor.
    /// @param name      sc_module_name (must be unique within this processor model).
    /// @param processor pointer to icmProcessorObject.
    icmCpuInterrupt(const char *name, icmCpu *cpu);

    virtual void write(const int &value);

private:
    icmNetObject  m_net;
    icmCpu       *m_cpu;
    const char   *m_name;
};

//
// Use one of these for each output net port
//
class icmCpuOutputNetPort : public tlm::tlm_analysis_port<int>
{
public:

    /// The constructor.
    /// @param cpu       Pointer to processor.
    /// @param portName  Name of output net port as appears in OVP model.
    icmCpuOutputNetPort(const char *portName, icmCpu *cpu);

private:
    icmNetObject m_net;
    icmCpu      *m_cpu;
    const char  *m_name;

    // called by a change on the net
    static void update(void *user, Uns32 value);
};

//
////////////////////////////////////// MASTER PORT ////////////////////////////
//
class icmCpuMasterPort
{
public:
	enum identifier {INSTRUCTION, DATA, GICRegisters};				// identifier to distinguish individual Ports in instance
	static int last_smp_found;										// class variable to keep track of last cpu found via INSTRUCTION port so that other ports can use this info
private:
    Uns32                    m_addrBits;      // number of address bits
    const char              *m_name;
    icmBusObject             m_bus;           // OVP address space for this port
    sc_time                  m_zero_delay;    // note: is const but cannot be declared as such
    bool                     m_warn_data_ptr; // have warned that ptr was modified
    icmCpu                  *m_cpu;
    Uns32                    m_maxBytes;      // max bytes per transaction
    icmCpuMasterPort        *m_dflt;          // alternative port for if this is unbound.
    icmInitiatorExtension   *m_initiator;
    tlm::tlm_generic_payload m_trans;         // transactions cannot be deferred so only one of these is needed.
    Uns32                    m_num_smp_cores;
    unsigned int 			*m_ICount_hist;
    identifier               m_ID;

    icmMemCallback *cbTryDMI;
    icmMemCallback *cbNoDMI;
    icmMemCallback *cbRdDMI;
    icmMemCallback *cbWrDMI;
    icmMemCallback *cbRWDMI;

    // text conversion function
    const char *response();

    // Used by each bus master operation
    void readUpcall (Addr addr,       unsigned char *value, Uns32 bytes, void* simulate, bool &first, bool tryDMI);
    void writeUpcall(Addr addr, const unsigned char *value, Uns32 bytes, void* simulate, bool &first, bool tryDMI);

    // convert bits to mask
    Addr maxValue(Uns32 bits) { return (bits >= 64) ? 0xFFFFFFFFFFFFFFFFll : ((Addr)1 << bits)-1; }

    // Static callback
    static void readTryDMI(
          Addr          address,
          Uns32         bytes,
          void         *value,
          void         *userData,
          void*         simulate
    );

    static void writeTryDMI(
          Addr          address,
          Uns32         bytes,
          const void   *value,
          void         *userData,
          void*         simulate
    );

    static void readNoDMI(
          Addr          address,
          Uns32         bytes,
          void         *value,
          void         *userData,
          void         *processor
    );

    static void writeNoDMI(
          Addr          address,
          Uns32         bytes,
          const void   *value,
          void         *userData,
          void*         simulate
    );

    // see if DMI is available and use it to map the memory if possible.
    void tryDmi(Addr addr, Bool read);

    /// Invalidate this DMI region
    /// @param low       Lower extent of the region.
    /// @param high      Upper extent of the region.
    void invalidate_direct_mem_ptr(int SocketId, sc_dt::uint64 start_range, sc_dt::uint64 end_range);

    icmProcessorP getFirstLeafProc(icmProcessorP parent);				// recursively find the first leaf node from passed parent node
    bool ICount_hist_lookup(icmProcessorP proc);						// for the passed proc, returns true if its ICount has increased else false
    unsigned int findSMPCPU();						// this will iterate over all the leaf cores in the platform CPU and see if the current leaf core issued the instruction fetch request using its Instruction Count and past history of counts

public:
    /// The constructor.
    /// @param pse      Pointer to PSE.
    /// @param name     Namer of bus port as appears in OVP model.
    /// @param addrBits Number of address bits supported by this port.

    icmCpuMasterPort(icmCpu *cpu, const char *name, Uns32 addrBits, Uns32 num_smp_cores, icmCpuMasterPort::identifier ID);

    /// Destructor (not usually called explicitly).
    ~icmCpuMasterPort() {}

    /*/// The TLM initiator socket. This name  must be used in the
    /// binding in the platform.
    socketType socket;*/

    // Modifying the TLM sockets to correspond to each of individual SMP core inside the Processor rather than only one socket/bus for the processor
    std::vector< tlm_utils::simple_initiator_socket_tagged<icmCpuMasterPort> * > m_isocket;


    /// Memory mapping function. Note that any region within the processor's address
    /// space not mapped by one of these functions will default to TLM memory.
    /// Map this region to local OVP memory.
    /// @param name      A unique name for this memory region.
    /// @param low       Lower extent of the region.
    /// @param high      Upper extent of the region.

    void mapLocalMemory(Addr low, Addr high, icmBusObject* &localBus);

    /// Map this region to native memory.
    /// @param name      A unique name for this memory region.
    /// @param ptr       Pointer to the native memory.
    /// @param low       Lower extent of the region.
    /// @param high      Upper extent of the region.
    /// @param priv      Read, write and alignment Privileges
    void mapNativeMemory(unsigned char *ptr, Addr low, Addr high, icmPriv priv);

    /// Un-map this region (back to callbacks)
    /// @param low       Lower extent of the region.
    /// @param high      Upper extent of the region.
    void unmapNativeMemory(Addr low, Addr high);

    /// Bind to a dummy port if unbound
    /// This will suppress end-of-elaboration errors if the port is unbound
    void bindIfNotBound();
    void bindIfNotBound(icmCpuMasterPort *dflt);

    /// Invalidate the whole DMI region
    void invalidateDMI(void);
};

/// Generic TLM/OVP processor.
/// It instances one OVP Processor model which can be connected to a TLM initiator socket.
/// The memory map of the processor can be set using the mapXxxMemory methods.
/// Note that this model connects both the INSTRUCTION and DATA memory spaces
/// of the OVP model to a single TLM2.0 bus.

class icmCpu : public sc_module, public icmProcessorObject
{

public:

    /// icmCpu constructor
    /// Constructs an instance of an OVP CPU model.
    /// @param name            Unique instance name.
    /// @param ID              Unique processor identifier.
    /// @param type            The type of the processor. Should match the 'N'
    ///                        in the VLNV.
    /// @param model           Path to the model files (dll or shared object).
    /// @param attrTable       Name of the attributes table in the model file.
    ///                        Note that some processor model files can contain
    ///                        more than one table, each supporting a different model.
    /// @param semihostLibrary (optional) Path to semihost library (dll or shared object).
    /// @param initialAttrs    (optional) list of user-defined attributes.
    ///                        Used to configure options in the model.
    /// @param procAttrs       (optional) processor simulator attributes.
    ///                        Used to control how the simulator treats this model.
    /// @param addressBits     Number of bits used by code and data address buses.
    /// @param dmi             (defaults to true) Control initial state of DMI.
    ///                        DMI uses memory mapping to bypass TLM where possible.
    ///
    ///                        Use instance.dmi(true) or instance.dmi(false)
    ///                        to turn on and off during simulation
    icmCpu(
    sc_module_name     name
  , const unsigned int ID
  , const char        *type
  , const char        *model
  , const char        *attrTable
  , const char        *semihostLibrary
  , icmNewProcAttrs   procAttrs     = ICM_ATTR_DEFAULT
  , icmAttrListObject *initialAttrs = 0
  , Uns32             addressBits   = 32
  , bool              dmi           = true
  , Uns32             cpuFlags      = 0
  );

private:
    static bool         m_finished;          // set if any cpu finishes.
    Uns64               m_instPerSecond;     // instructions to execute per second
    bool                m_traceQuanta;
    bool                m_traceBuses;
    bool                m_traceBusErrors;
    bool                m_traceSignals;
    const char *        m_name;

protected:
    virtual void        icmCpuThread (void);

public:

    // current state of DMI
    bool                m_dmi;

    // Use this to map local memory on each bus master port
    icmBusObject* m_localBus;

    /// Override the number of instructions to run per second.
    /// @param ips       Instructions per second.
    void setIPS    (Uns64 ips)   { m_instPerSecond = ips; }

    /// Install one interrupt.
    /// @param intr      Pointer to interrupt object.
    /// @param name      Name of interrupt object as it appears in the OVP model.
    void connectInterrupt(icmCpuInterrupt **intr, const char *name);


    /// Control tracing of each quantum.
    /// @param on         On/Off.
    void traceQuanta(bool on) { m_traceQuanta = on; }

    /// Control tracing of each quantum.
    /// @return           On/Off.
    bool traceQuanta(void) { return m_traceQuanta; }


    /// Control tracing of each bus cycle.
    /// @param on         On/Off.
    void traceBuses(bool on) { m_traceBuses = on; }

    /// Fetch tracing of each bus cycle.
    /// @return           On/Off.
    bool traceBuses() { return m_traceBuses; }


    /// Fetch tracing of each bus cycle.
    /// @param on         On/Off.
    void traceBusErrors(bool on) { m_traceBusErrors = on; }

    /// Fetch tracing of each bus cycle.
    /// @return           On/Off.
    bool traceBusErrors() { return m_traceBusErrors; }


    /// Control tracing of signals (interrupts).
    /// @param on        On/Off.
    void traceSignals(bool on) { m_traceSignals = on; }

    /// Fetch tracing of signals.
    /// @return           On/Off.
    bool traceSignals() { return m_traceSignals; }


    /// Fetch model name
    /// @return           name.
    const char *name(void) { return m_name; }

    /// Fetch DMI mode.
    /// @return           On/Off.
    bool dmi() { return m_dmi; }

    /// Set DMI mode.
    /// @param dmi        New state
    virtual void dmi(bool on) = 0;
};









#endif
