/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */



#ifndef _IMP_MEMORY
#define _IMP_MEMORY

#include <stdlib.h>

#include "systemc.h"
#include "hostapi/impTypes.h"
#include "icm/icmCpuManager.hpp"

SC_MODULE(impMemory)
{
   SC_HAS_PROCESS(impMemory);

   // constructor
   impMemory(sc_module_name instname, sc_clock &ck)
   {
      _init = false;
      _mem  = NULL;

      _inclk(ck);
   }

   // destructor
   ~impMemory()
   {
      if (_init && _mem) {
         delete _mem;
	 _mem = NULL;
	 _init = false;
      }
   }

   // memory initialisation rountine
   bool init( Addr baseAddr, Uns32 size)
   {
      bool retcode = false;

      _mem = new char[size];
      if (_mem) {
         _init 		= true;
         _base 		= (Uns32)baseAddr;
         _size 		= size;
         retcode	= true;
      }

      return retcode;
   }

   // helper function to check address is within memory range
   bool inline inrange(Addr a)
   {
      return ( (a>=_base) && (a<=(_base+_size-1)) ) ? true: false;
   }

   typedef enum { tWrite, tRead } trans_t;

   // memory access routine
   bool transaction(trans_t tr, Addr address, void *value, Uns32 bytes)
   {
      bool retcode = false;

      if (_init) {
         if ( inrange(address) && inrange(address+bytes-1) ) {
            Addr adr = address - _base;
            char *src, *dst;
            switch (tr) {
               case tWrite:
                  src = (char*)value;
                  dst = &(_mem[adr]);
                  break;
               case tRead:
                  src = &(_mem[adr]);
                  dst = (char*)value;
                  break;
               default:
                  assert(0);
                  break;
            }

            memcpy(dst, src, bytes);

            retcode = true;
         }
      }

      return retcode;
   }

   bool             _init;
   sc_in_clk        _inclk;
   unsigned long    _base;
   unsigned long    _size;
   char	*           _mem;

};

using namespace icmCpuManager;

extern "C" {

    //
    //  Callback for memory write
    //
    static ICM_MEM_WRITE_FN(memWriteCB)
    {
        if (processor) {
            impMemory *m = (impMemory*) userData;
            if (m) m->transaction(impMemory::tWrite, address, (void*)value, bytes);
        }
    }

    //
    //  Callback for memory read
    //
    static ICM_MEM_READ_FN(memReadCB)
    {
        if (processor) {
            impMemory *m = (impMemory*) userData;
            if (m) m->transaction(impMemory::tRead, address, value, bytes);
        }
    }

}

#endif // _IMP_MEMORY
