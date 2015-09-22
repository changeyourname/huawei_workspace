 
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


FILE:Imperas/Examples/Platforms/byteSwapper/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.

The example illustrates the use of an MMC to model a byte swapping
(endian correction) function.
It should be used in conjunction with the user guide but is briefly described 
here.

FILES --------------------------------------------------------------
There are four parts to the example:
1. An application; application/application.c
2. An ICM Platform; platform/platform.c
3. A trivial peripheral model to illustrate the byte swapping; peripheral/main.c
4. A Makefile to build 1, 2 and 3

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=OR1K

RUNNING THE EXAMPLE ------------------------------------------------

> make simulate

If you have Imperas Professional Tools -----------------------------

> make simulateXml


