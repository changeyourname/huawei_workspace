 
  Copyright (c) 2005-2015 Imperas Software Ltd. All Rights Reserved.

  The contents of this file are provided under the Software License
  Agreement that you accepted before downloading this file.

  This source forms part of the Software and can be used for educational,
  training, and demonstration purposes but cannot be used for derivative
  works except in cases where the derivative works require OVP technology
  to run.

  For open source models released under licenses that you can use for
  derivative works, please visit www.ovpworld.org or www.imperas.com
  for the location of the open source models.


FILE:Imperas/Examples/Platforms/systemC/README.txt



INTRODUCTION -------------------------------------------------------

This example shows how to use the CpuManager simulation library 
to control an OR1K processor model from a SystemC design.
It also provides the ability to map external memory to a model
outside the Imperas simulator and it shows how to define and
use a handler for simulator stop conditions.


FILES --------------------------------------------------------------

platform/impMemory.hpp              # The external memory model
platform/impProcessor.hpp           # A simple SystemC wrapper to CpuManager
platform/impSimulation.cpp          # Platform creation and simulation
Makefile                           # Creates the simulation executable
application/application.c          # The application to simulate

The application to simulate copies from a local array 'intIndex' a 
list of index values to a second array 'extIndex'. 
The systemC example is built in such a way that the address space 
that the second array occupies can be within ICM local memory or an 
external systemC memory.
The source file 'application.c' must be compiled using the OR1K GCC
tools into an ELF file called 'application/application.<CROSS>.elf'.


PREPARING THE MAKEFILE --------------------------------------------

Before running the 'make', the Makefile must be customized with the
correct pathname for $SYSTEMC_HOME. Alternatively, this can be done 
on the command line. 

In order to build a simulation to use external memory both the 
'membase' and 'memsize' variables must be set in the Makefile or again 
passed on the command line
How to obtain the values to be used for these variables can be found
below.

COMPILING THE APPLICATION -----------------------------------------

The application is compiled using the normal OR1K tool flow. 
Within the Makefile are encapsulated the command lines that may be
used for the compilation and linking of the application.

This is invoked with 

> make -C application CROSS=<CROSS>

The compilation of the application creates a file 
'application.or1k-buff-address.txt' that contains the address of 
the array in memory. The same information can be created using the
command 

> or32-elf-nm application/application.<CROSS>.elf | grep extIndex

Where this is the OR1K CrossCompiler tools found in 
IMPERAS_HOME/lib/<IMPERAS_ARCH>/CrossCompiler/or32-elf/bin/

The values of address and size should be copied to the Makefile 
prefixing them with the '0x' characters or they can be passed on 
the make command line.

BUILDING THE SIMULATION -------------------------------------------

Using ICM Memory --------------------------------------------------

By default a SystemC simulation that has memory modeled within 
ICM is created.

> make SYSTEMC_HOME=<systemC install director>

Using SystemC Memory ----------------------------------------------

The same application will work if one of the array variables 'extIndex' 
is mapped to be external from ICM. The address of the array and its size 
in the application code must be determined, this is shown above, and 
used to modify the platform. The platform will now have an area of 
memory provided in SystemC located at the address of the 'extIndex' array.

To build the platform, modify the Makefile and use the command

> make EXTMEMORY=1 SYSTEMC_HOME=<systemC install director>

Alternatively, the location of the array and its size can be passed 
on the command line using the command

> make EXTMEMORY=1 membase=0xeffc memsize=0x14 SYSTEMC_HOME=<systemC> 

RUNNING THE EXAMPLE -----------------------------------------------

Ensure the LD_LIBRARY_PATH environment variable is set to include
${IMPERAS_HOME}/bin/${IMPERAS_ARCH} so that the shared object is loaded.

The executable is invoked on the command line 

> impSimulation.exe application/application.<CROSS>.elf

