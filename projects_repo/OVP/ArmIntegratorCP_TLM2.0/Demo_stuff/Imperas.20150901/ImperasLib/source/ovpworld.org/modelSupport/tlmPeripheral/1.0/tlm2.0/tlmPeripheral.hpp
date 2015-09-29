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



#ifndef _TLM_PERIPHERAL_H__
#define _TLM_PERIPHERAL_H__

#include "tlm.h"                              	// TLM headers
#include "tlm_utils/simple_initiator_socket.h"  // equivalent of OVP Bus Master Port
#include "tlm_utils/simple_target_socket.h"  // equivalent of OVP Bus Master Port

#include <icm/icmCpuManager.hpp>

using namespace icmCpuManager;
using namespace std;
using namespace sc_core;

// forward ref to peripheral
class icmPeripheral;

/// Use one of these for each fixed address peripheral slave port.

class icmSlavePort
{
    typedef tlm_utils::simple_target_socket<icmSlavePort> socketType;

private:
    icmBusObject   m_bus;        // OVP address space for this port
    Addr           m_bytes;      // size of port (TODO cannot handle full space
    const char    *m_name;
    icmPeripheral *m_pse;

    // internal
    void         transport( tlm::tlm_generic_payload &payload, void *processor);

    // registered as callbacks on the port
    void         b_transport(tlm::tlm_generic_payload &payload, sc_time &delay);
    unsigned int debug_transport(tlm::tlm_generic_payload &payload);

    Uns32 addrBits(Addr hiAddress) {
        Uns32 i = 0;
        while(hiAddress) {
            hiAddress >>= 1;
            i++;
        }
        return i;
    }

public:

    /// The constructor.
    /// @param pse      Pointer to the peripheral object.
    /// @param name     Name of the slave port in the OVP model.
    /// @param bytes    Number of bytes decoded by this slave port.

    icmSlavePort(icmPeripheral *pse, const char *name, Addr bytes);

    /// Destructor (not usually called explicitly).
    ~icmSlavePort() {}

    /// Target port for incoming data access.
    /// This name (socket) must be used in the platform to bind this port.
    socketType socket;

};

//
// One (of possibly several) mapping through a dynamic slave port
//
class icmDynamicPortMapping {
  private:
    Addr lo;
    Addr hi;
    icmDynamicPortMapping *next;

  public:
    icmDynamicPortMapping(Addr lo_n, Addr hi_n)
        : lo(lo_n), hi(hi_n), next(0){
    }
    void setNext(icmDynamicPortMapping *n) { next = n; }
    icmDynamicPortMapping *getNext()   { return next;  }
    icmDynamicPortMapping **getNextP() { return &next; }

    Bool matches(Addr lo_s, Addr hi_s) {
        return lo == lo_s && hi == hi_s;
    }

    Bool inRegion(Addr a) {
        return a >= lo && a <= hi;
    }
};

/// Use one of these for each dynamic address peripheral slave port.

class icmDynamicSlavePort {
    typedef tlm_utils::simple_target_socket<icmDynamicSlavePort> socketType;

private:
    icmBusObject           m_bus;        // OVP address space for this port
    const char            *m_name;
    icmPeripheral         *m_pse;
    icmDynamicPortMapping *mappings;
    // registered as callbacks on the port
    void         transport(tlm::tlm_generic_payload &payload, void *processor);
    void         b_transport(tlm::tlm_generic_payload &payload, sc_time &delay);
    unsigned int debug_transport(tlm::tlm_generic_payload &payload);
    static void  staticSetPortAddress(void *userData, Addr lo, Addr hi, Bool map);
    void         setPortAddress(Addr lo, Addr hi, Bool map);
public:

    /// The constructor.
    /// @param pse      Pointer to the peripheral object.
    /// @param name     Name of the slave port in the OVP model.
    /// @param addrBits Number of bits accepted by the decoder.

    icmDynamicSlavePort(icmPeripheral *pse, const char *name, Uns32 addrBits);

    /// Destructor (not usually called explicitly).
    ~icmDynamicSlavePort() {}

    /// Target port for incoming data access.
    /// This name (socket) must be used in the platform to bind this port.
    socketType socket;
};

/// Use one of these for each peripheral master port.

class icmMasterPort
{
    typedef tlm_utils::simple_initiator_socket<icmMasterPort> socketType;

private:
    Uns32                    m_addrBits;
    icmBusObject             m_bus;        // OVP address space for this port

    sc_time                  m_zero_delay; // note: is const but cannot be declared as such
    icmMasterPort           *m_dflt;       // alternative port for if this is unbound.
    tlm::tlm_generic_payload m_trans;      // transactions cannot be deferred
                                           // so only one of these is needed.

    // convert response to text
    const char *response();

    // Used by each bus master operation
    void readUpcall (Addr addr,       void *value, Uns32 bytes);
    void writeUpcall(Addr addr, const void *value, Uns32 bytes);

    // Transaction method
    void doTrans( tlm::tlm_generic_payload &trans );

    // Static callback
    static void read(
          Addr          address,
          Uns32         bytes,
          void         *value,
          void         *userData,
          void         *processor
    );

    static void write(
          Addr          address,
          Uns32         bytes,
          const void   *value,
          void         *userData,
          void         *processor
    );

    Addr maxValue(Uns32 bits) { return (bits >= 64) ? 0xFFFFFFFFFFFFFFFFll : ((Addr)1 << bits)-1; }

public:

    /// The constructor.
    /// @param pse      Pointer to PSE.
    /// @param name     Namer of bus port as appears in OVP model.
    /// @param addrBits Number of address bits supported by this port.

    icmMasterPort(icmPeripheral *pse, const char *name, Uns32 addrBits);

    /// Destructor (not usually called explicitly).
    ~icmMasterPort() {}

    /// The TLM initiator socket. This name must be used in the
    /// binding in the platform.
    socketType     socket;

    icmPeripheral *m_pse;

    /// Bind to a dummy port if unbound. This will suppress end-of-elaboration errors
    void bindIfNotBound();
};


/// Use one of these for each peripheral output net port

class icmOutputNetPort : public tlm::tlm_analysis_port<int> {
public:

    /// The constructor.
    /// @param pse       Pointer to PSE.
    /// @param portName  Name of output net port as appears in OVP model.
    icmOutputNetPort(icmPeripheral *pse, const char *portName);

private:
    icmNetObject   m_net;
    icmPeripheral *m_pse;
    const char    *m_name;

    // called by a change on the net
    static void update(void *user, Uns32 value);
};

/// Use one of these for each peripheral input net port.
/// It connects a TLM net to an OVP peripheral net input.

class icmInputNetPort : public tlm::tlm_analysis_if<int>
{
public:
    /// The constructor.
    /// @param name      Name of this object as it appears in the OVP model.
    /// @param pse       Pointer to the PSE object.

    icmInputNetPort(icmPeripheral *pse, sc_module_name name);

private:
    icmNetObject   m_net;
    icmPeripheral *m_pse;
    const char    *m_name;

    virtual void write(const int &value);
};

/// Use one of these for each peripheral inout net port.
/// It connects a TLM net to an OVP peripheral net.

class icmInoutNetPort : public tlm::tlm_analysis_if<int>
{
public:
    /// The constructor.
    /// @param name      Name of this object as it appears in the OVP model.
    /// @param pse       Pointer to the PSE object.

    icmInoutNetPort(icmPeripheral *pse, sc_module_name name);

private:
    icmNetObject   m_net;
    icmPeripheral *m_pse;
    const char    *m_name;

    virtual void write(const int &value);

    // called by a change on the net
    static void update(void *user, Uns32 value);
};

/// This is the generic OVP Peripheral.
/// It instances one OVP Peripheral model.

class icmPeripheral : public sc_module, public icmPseObject
{
public:

    /// The peripheral constructor.
    /// @param name             Instance name. Must be unique in the platform.
    /// @param model            Path to model PSE object file. See icmGetVlnvString().
    /// @param semihostLibrary  Path to intercept object (.dll or .so) if required.
    /// @param initialAttrs     (optional) List of user-defined attributes passed to the model.
    icmPeripheral(
      sc_module_name          name
    , const char             *model
    , const char             *semihostLibrary
    , icmAttrListObject      *initialAttrs = 0
    );

    const char *m_name;

    void traceBuses(bool on)     { m_traceBuses = on;       }
    bool traceBuses(void)        { return m_traceBuses;     }
    void traceBusErrors(bool on) { m_traceBusErrors = on;   }
    bool traceBusErrors(void)    { return m_traceBusErrors; }
    void traceSignals(bool on)   { m_traceSignals = on;     }
    bool traceSignals(void)      { return m_traceSignals;   }

private:
    bool m_traceBuses;
    bool m_traceBusErrors;
    bool m_traceSignals;
};

#endif
