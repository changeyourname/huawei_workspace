 
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


File:Imperas/Examples/HelloWorld/README.txt

INTRODUCTION -------------------------------------------------------
This example shows a simple Application which will print
	Hello World
to the console
This Application can be cross compiled to any supported processor type
or endian. This example compiled for Big Endian data ordering and includes
a platform that is written to support ARM7, OR1K and MIPS32 processor types.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application.c
2. A CpuManager/OVPsim platform; this is found as platform.c
3. A Makefile to build the application in 1; this is found as Makefile,
   In addition a standard Makefile is used to build the platform.
   This is found at IMPERAS_HOME/ImperasLib/buildutils/Makefile.platform

BUILDING THE SIMULATION --------------------------------------------
> make CROSS=OR1K
This will build the application 'application.OR1K.elf'

> make -f IMPERAS_HOME/ImperasLib/buildutils/Makefile.platform SRC=platform.c NOVLNV=1
This will build the platform 'platform.IMPERAS_ARCH.exe

if the value for 'CROSS' in the call to make the application is replaced with 
either MIPS32 or ARM7, the files which are built will change accordingly. 

These may then be run using the same platform by changing the processor type selected 
on the command line.

RUNNING THE EXAMPLE ------------------------------------------------
> platform.IMPERAS_ARCH.exe --program application.OR1K.elf --processortype or1k

Alternative Processor Vendor
In some releases processor models may be provided by alternative vendors.
If the release being used has a processor model from a vendor not specified 
as the default supplied in the OVPsim installation it may be specified on 
the platform command line, as the final argument

> platform.IMPERAS_ARCH.exe --program application.MIPS32.elf \
                            --processortype mips32 \
                            --alternatevendor mips.com 
