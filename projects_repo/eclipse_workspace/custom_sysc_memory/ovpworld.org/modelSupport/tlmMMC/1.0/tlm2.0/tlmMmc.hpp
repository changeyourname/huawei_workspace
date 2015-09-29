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



#ifndef __TLM_MMC_H__
#define __TLM_MMC_H__

#include "tlm.h"                              	// TLM headers
#include "tlm_utils/simple_initiator_socket.h"  // equivalent of OVP Bus Master Port
#include "tlm_utils/simple_target_socket.h"     // equivalent of OVP Bus Slave Port

#include "icm/icmCpuManager.hpp"

using namespace icmCpuManager;
using namespace std;
using namespace sc_core;

class icmMMC;
class icmInitiatorExtension;

//
/////////////////////////////////// SLAVE PORT ////////////////////////////////
//
// The slave port receives a TLM transaction from an initiator.
//
class icmMMCSlavePort
{
    typedef tlm_utils::simple_target_socket<icmMMCSlavePort> socketType;

  public:

    /// The constructor.
    /// @param pse      Pointer to the peripheral object.
    /// @param name     Name of the slave port in the OVP model.
    /// @param bytes    Number of bytes decoded by this slave port.
    icmMMCSlavePort(icmMMC *mmc, const char *name, Addr bytes);

    /// Destructor (not usually called explicitly).
    ~icmMMCSlavePort() {}

    /// Target port for incoming data access.
    /// This name (socket) must be used in the platform to bind this port.
    socketType socket;

  private:
    sc_time       m_zero_delay; // note: is const but cannot be declared as such
    icmBusObject  m_bus;        // OVP address space for this port
    const char   *m_name;
    Addr          m_bytes;
    icmMMC       *m_mmc;
    bool          m_forceDebug;

    void transport( tlm::tlm_generic_payload &payload, void *processor);

    // registered as callbacks on the port
    void          b_transport    (tlm::tlm_generic_payload &payload, sc_time &delay);
    unsigned int  debug_transport(tlm::tlm_generic_payload &payload);

    Uns32 addrBits(Addr hiAddress) {
        Uns32 i = 0;
        while(hiAddress) {
            hiAddress >>= 1;
            i++;
        }
        return i;
    }
};


//
////////////////////////////////////// MASTER PORT ////////////////////////////
//
// The master port initiates TLM transaction.
//

class icmMMCMasterPort
{
    typedef tlm_utils::simple_initiator_socket<icmMMCMasterPort> socketType;

  private:
    Uns32                    m_addrBits;   // number of address bits
    const char              *m_name;
    icmBusObject             m_bus;        // OVP address space for this port
    icmBusObject             m_tlmBus;     // Region mapped to TLM
    sc_time                  m_zero_delay; // note: is const but cannot be declared as such
    icmMMC                  *m_mmc;
    icmInitiatorExtension   *m_initiator;
    tlm::tlm_generic_payload m_trans;      // transactions cannot be deferred
                                           // so only one of these is needed.

    // Used by each bus master operation
    void readUpcall (Addr addr,       void *value, Uns32 bytes, void *processor);
    void writeUpcall(Addr addr, const void *value, Uns32 bytes, void *processor);

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
    icmMMCMasterPort(icmMMC *mmc, const char *name, Uns32 addrBits);

    /// Destructor (not usually called explicitly).
    ~icmMMCMasterPort() {}

    /// The TLM initiator socket. This name  must be used in the
    /// binding in the platform.
    socketType socket;
};

/// Generic TLM/OVP MMC.
/// It instances one OVP MMC model which can be connected to TLM initiator and
/// acceptor sockets.

class icmMMC : public sc_module, public icmMmcObject
{

private:
    bool  m_traceMasters;
    bool  m_traceSlaves;

public:
    /// icmMMC constructor
    /// Constructs an instance of an OVP MMC model.
    /// @param name            Unique instance name.
    /// @param model           Path to the model files (dll or shared object).
    /// @param attrTable       Name of the attributes table in the model file.
    /// @param initialAttrs    (optional) list of user-defined attributes.
    ///                        Used to configure options in the model.

  icmMMC(
    sc_module_name     name
  , const char        *model
  , const char        *attrTable
  , icmAttrListObject *initialAttrs = 0
  );

  const char* m_name;

  bool traceMasters(void)    { return m_traceMasters; }
  void traceMasters(bool on) { m_traceMasters = on;   }
  bool traceSlaves(void)     { return m_traceSlaves;  }
  void traceSlaves(bool on)  { m_traceSlaves = on;    }

};

#endif
