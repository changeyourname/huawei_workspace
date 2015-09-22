 
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


FILE:Imperas/Examples/Platforms/exceptions/README.txt

INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows the use of the ICM attribute ICM_ATTR_SIMEX that can be 
passed to the simulator to allow the simulation of exceptions by the processor
model rather than being trapped by the simulator.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/asmtest.S
2. An ICM Platform; this is found as platform/platform.c
3. A makefile to build 1 and 2; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the ICM Platform
  Allowing exceptions to be handled by the simulator
  
> make -C platform

  To include the ICM_ATTR_SIMEX attribute and simulate exceptions in 
  the model
  
> make -C platform EXCEPTIONS=1

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.<IMPERAS_ARCH>.exe --program application/asmtest.<CROSS>.elf

