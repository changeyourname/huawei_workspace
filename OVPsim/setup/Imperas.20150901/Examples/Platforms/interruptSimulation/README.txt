 
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


FILE:Imperas/Examples/Platforms/interruptSimulation/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows a simulation using the ICM platform can be interrupted 
in a number of ways. 
a) by an external source
  i) by installing and using a Linux Control-C handler
  ii) using the internal simulator Control-C handler for Linux and Windows
b) by calling icmInterrupt from the simulation platform

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/application.c
2. An ICM Platform; this is found as platform/platform.c
3. A makefile to build 1 and 2; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the ICM Platform

> make -C platform

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.<IMPERAS_ARCH>.exe --program application/application.<CROSS>.elf

On iteration NUM_VALUES/2 the application writes to a location that is 
covered by a memory watch callback. in the callback routine the icmInterrupt
function is called. 

While the example is running use the keyboard to enter control-C. 

Either of these will cause the simulation to be interrupted and the current
instruction count for the interrupted processor displayed.
