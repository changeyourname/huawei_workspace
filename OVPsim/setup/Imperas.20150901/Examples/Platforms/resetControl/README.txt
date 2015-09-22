 
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


FILE:Imperas/Examples/Platforms/resetControl/README.txt

INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows that a 'reset' net can be used to hold a processor model 
in its reset state and it will not execute instructions until released.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/application.c
2. An ICM platform; this is found as platform/platform.c
3. A makefile to build 1 and 2; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=OR1K

To build the ICM platform

> make -C platform CROSS=OR1K

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.${IMPERAS_ARCH}.exe application/application.$CROSS.elf

