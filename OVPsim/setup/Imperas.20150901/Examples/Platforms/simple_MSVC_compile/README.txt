 
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


File:Imperas/Examples/Platforms/simple_MSVC_compile/README.txt

PREREQUISITES-------------------------------------------------------

If you are using a Windows environment, you will need to obtain and install:

Microsoft Visual C++:
    www.microsoft.com/express/vc (Check licensing conditions).
    
If you are using Linux you will need the gnu tool-chain (g++, ld etc) for
your distribution.

You will need to obtain and install a toolchain for the processor.

INTRODUCTION -------------------------------------------------------
This example shows the use of OVP technology with the Microsoft MSVC
toolchain to compile the host virtual platform. 

This example platform contains one processor

FILES --------------------------------------------------------------
There are two parts to the example
1. The application; code which runs on the OR1K processor model;
   this is in application/main.c

2. The platform; this is in platform/platform.c
 

with scripts to build and run
        example.bat       Build and run for Windows
        example.msvc.bat  Build with MSVC and run for Windows
        example.sh        Build and run for Linux 
        
    
BUILDING THE PLATFORM ----------------------------------------------------------

The installation of OVPsim (www.ovpworld.org) provides this Example directory.
In addition
  Obtain and install the toolchain for the OR1K.
  Obtain and install Microsoft Visual C++ (MSVC) (www.microsoft.com).

Platform compilation is carried out in the platform_cpp directory.

Windows MinGW shell. This uses the standard Makefile to build
  mingw32-make -f %IMPERAS_HOME%/ImperasLib/buildutils/Makefile.TLM.platform PLATFORM=platform 

Linux shell. This uses the standard Makefile to build
  make -f $IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform PLATFORM=platform 

Windows MSVC. Start a Visual Studio Command Prompt so that the correct MSVC environment is available.
In this window:
> cd platform_cpp
> call compile.msvc.bat
> cd ..

this invokes nmake on the Makefile nmakefile to build the platform.


The application program is built using a Makefile in the application 
directory. This will also require that the OR1K toolchain is downloaded and installed.

In a MINGW/MSYS shell on Windows or at a Linux prompt go to the application directory
and type
> cd application
> make
> cd ..

RUNNING THE PLATFORM ---------------------------------------------------------------

To run the platform
> platform/platform.<ARCH>.exe application/asmTest.OR1K.elf

