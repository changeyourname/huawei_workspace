 
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


FILE:Imperas/Examples/Platforms/objectReader/README.txt

INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.
The features described are not available in OVPsim

This example shows how to write your own object code reader and use it
with CpuManager or the Imperas Simulator.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/hello.c
2. The example loader; this is found as loader/loader.c
3. The ICM platform; this is found as platform/platform.c

BUILDING THE COMPONENTS --------------------------------------------

To build the application
> make -C application

To build the loader
> make -C loader

To build the platform
> make -C platform


RUNNING THE EXAMPLE ------------------------------------------------

to Run in the simulator
> make imperas
or
> imperas.exe --objectloader loader/loader.<IMPERAS_SHRSUF> -objfile application/hello.<CROSS>.s19 -v

to run the standalone platform
> make standalone
or
> IMPERAS_RUNTIME=CpuManager platform/platform.<IMPERAS_ARCH>.exe --program application/hello.<CROSS>.s19


