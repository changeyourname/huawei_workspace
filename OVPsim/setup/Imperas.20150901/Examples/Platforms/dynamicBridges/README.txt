 
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


FILE:Imperas/Examples/Platforms/dynamicBridges/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and 
CpuManager User guide.
It should be used in conjunction with the user guide but is briefly 
described here.

This example shows how several busses can be created and then the 
mapping between them be dynamically altered.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/asmtest.S
2. An ICM Platform; this is found as platform/platform.c
3. A Makefile to build 1 and 2; this is found as Makefile

DESCRIPTION --------------------------------------------------------
The platform has three busses, 'busLocal', 'busMapped' and 
'busExternal' that are connected using dynamic bus bridges.
    'busLocal'    has master connections to the processor
    'busMapped'   contains a memory instance
    'busExternal' contains an external memory callback

The mapping initially allows a program to load into the memory of 
the bus 'busMapped'. As the program executes the platform will use 
the Program Counter (PC) address to dynamically change the mapping 
between 'busLocal' and the other two busses and so change the mapping 
seen by the application executing on the processor.  

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the ICM Platform

> make -C platform

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.<IMPERAS_ARCH>.exe --program application/asmtest.<CROSS>.elf

