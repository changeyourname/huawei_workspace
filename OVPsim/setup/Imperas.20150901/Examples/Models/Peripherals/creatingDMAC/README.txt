 
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


FILE:Imperas/Examples/Models/Peripherals/creatingDmac/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains examples to be used in conjunction with the 
OVP Peripheral Modeling Guide.

This directory contains an example which shows how to construct and use
a peripheral model using the Imperas tools. The example demonstrates a
processor interacting with a model of a DMAC peripheral.

The example progresses over a series of steps:

Step 1 "registers" creates a simple peripheral with memory-mapped registers.

Step 2 "parallelThreadsAndEvents" adds bodies to the register callbacks,
       and execution threads for each DMA channel.

Step 3 "memAccess" introduces functions from the ppm library to allow access
       to the address spaces of buses connected to the peripheral.  

Step 4 "interrupt" completes the example by adding interrupt outputs and a reset input.

Step 5 "nativeBehaviour" shows how a peripheral model can use native code.

FILES --------------------------------------------------------------
Peripheral Model:

dmacModel.tcl
   Contains the TCL script that generates the peripheral template. Generated files
   have .igen. in their names.
   
dmac.c (generated as dmac.igen.stubs)
   This file contains callbacks to be expanded by the user. All but the 1st example,
   does not use the file created by igen, but a modified version.

dmac.attrs.igen.c
   Contains code to describe the simulation interface of the model which is
   interrogated by the simulator.

dmac.igen.c
   Contains the initialization of the peripheral, the connection of ports 
   and the installation of registers and their callbacks.
   
dmac.igen.h
   To be included by C files.
   
dmac.macros.igen.h
   Macros defining register and bit offsets in the model. Might be useful in application
   code that uses this model.

dmaTest.c, dmacRegisters.h
   Source files for the test program running on the processor.

platform.c
   The OVP virtual platform description.

Makefiles
   Makefiles are present for building:
   1. Peripheral (root): Compiles the C files implementing the peripheral model 
      to produce executable code for the Peripheral Simulation Environment (PSE).
   2. Application: Cross compiles the C files for the test application to create a 
      loadable elf file.
   3. Platform: Compiles the C file of the OVP ICM platform description that creates 
      the platform executable that loads, processor and peripheral model components.
   
RUNNING THE EXAMPLES -----------------------------------------------

Building Executables
    A Makefile is included that use the imperas cross compiler installation.
    These build the application, the OVP virtual platform and the peripheral
    pse executable. To build all parts of the example use the commands

> make -C application     
> make -C platform         NOVLNV=1

> make -C peripheral/pse   NOVLNV=1 
> make -C peripheral/model NOVLNV=1 

    
Running the example
    The example is run from the command line using the following
    
> platform/platform.${IMPERAS_ARCH}.exe --program application/dmaTest.elf


    
    
