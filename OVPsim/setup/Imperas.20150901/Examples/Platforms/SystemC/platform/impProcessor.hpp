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



#ifndef _IMP_PROCESSOR
#define _IMP_PROCESSOR

#include "systemc.h"


#include "icm/icmCpuManager.hpp"

#include "impMemory.hpp"

using namespace icmCpuManager;

//
// The handler of the stop reason
//
class stopHandler: public icmHandleSimStop_if
{
public:
   stopHandler() {};
   ~stopHandler() {};

   // implementation of icmHandleSimStop_if
   icmStopReason simStopHandler(icmProcessorObject *p, icmStopReason r) {
      switch(r) {
         case ICM_SR_SCHED: // hit the scheduler limit
         break;

         case ICM_SR_EXIT:  // processor has exited
             cout << "EXIT instructions " << p->getICount() << endl;
             sc_stop();
         break;

         case ICM_SR_FINISH: // simulation must end
             cout << "FINISH instructions " << p->getICount() << endl;
             sc_stop();
         break;

         default:
         break;
      }

      return r;
   }

};


SC_MODULE(impProcessor)
{
   SC_HAS_PROCESS(impProcessor);

   /////
   //
   // Constructor
   //
   impProcessor(sc_module_name instname, sc_clock &ck)
   {
      _init = false;
      _proc = NULL;
      _inclk(ck);

      SC_METHOD(runner);
      sensitive << _inclk.neg();
      dont_initialize();
   }

   /////
   //
   // Destructor
   //
   ~impProcessor()
   {
      if (_init && _proc) {
         delete _proc;
         _proc = NULL;
         _init = false;
      }
   }

   /////
   //
   // Init function
   //
   bool init( const char *procName,
              const char *typeName,
              int         cpuId,
              const char *morpherFile,
              const char *morpherSymbl,
              const char *semiHostFile,
              const char *semiHostSymbl )
   {
      bool retcode = false;

      char busName[64];
      sprintf(busName, "%s_bus", procName);

      _bus  = new icmBusObject(
                     busName,       // bus name
                     32             // address bits
                  );

      _proc = new icmProcessorObject (
                     procName,         // processor name
                     typeName,         // processor type
                     cpuId,            // processor ID
                     0,                // processor model flags
                     32,               // address bits
                     morpherFile,      // processor model file
                     morpherSymbl,     // morpher attributes
                     ICM_ATTR_DEFAULT, // processor attributes
                     0,                // user-defined attributes
                     semiHostFile,     // semi-hosting library file
                     semiHostSymbl     // semi-hosting attributes
                   );

      _proc->connect(*_bus, *_bus);

      if (_proc) {
         // register a handler for the simulator stop conditions
         _proc->icmRegisterSimStopHandler(_shandle);

         retcode = true;
      }

      return retcode;
   }

   /////
   //
   // Load the object file into processor memory
   //
   void objfile(const char *objfile)
   {
      // If processor was successfully created then
      // load the program image into its memory
      if (_proc) {
         // load object file
         (*_proc) << objfile;
      }
   }

   /////
   //
   // The SC_METHOD connected to the clock
   //
   void runner(void)
   {
     // step processor
     (*_proc) << 1;
   }

   /////
   //
   // Maps a memory range to a local memory within the simulator.
   //
   void localMem(const char *name, Addr loaddr, Addr hiaddr)
   {
     icmMemoryObject *mem = new icmMemoryObject(name, ICM_PRIV_RWX, hiaddr-loaddr);
     mem->connect(name, *_bus, loaddr);
   }

   /////
   //
   // Maps a memory range to a memory manager outside the simulator.
   //
   void extMem(Addr loaddr, Addr hiaddr, icmMemReadFn rcb, icmMemWriteFn wcb, impMemory *mem)
   {
      _bus->mapExternalMemory(
        "external",
		ICM_PRIV_RW,
		loaddr,
		hiaddr,
		rcb,
		wcb,
		mem
	);
   }


   bool			        _init;
   sc_in_clk            _inclk;
   unsigned long        _base;
   unsigned long        _size;
   stopHandler          _shandle;
   icmProcessorObject   *_proc;
   icmBusObject         *_bus;
};

#endif // _IMP_PROCESSOR
