 
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


File:Imperas/Examples/Platforms/SystemC_TLM2.0/README.txt

PREREQUISITES-------------------------------------------------------

It is assumed that you are familiar with SystemC. If you are using a Windows
environment, you will need to obtain and install:

Microsoft Visual C++:
    www.microsoft.com/express/vc (Check licensing conditions).
    
If you are using Linux you will need the gnu tool-chain (g++, ld etc) for
your distribution.

You will need to obtain and install SystemC.
    www.SystemC.org
    
You will need to obtain and install SystemC TLM2.0.
    www.SystemC.org/downloads/standards
    
You will need to obtain and install a toolchain for the processor.

INTRODUCTION -------------------------------------------------------
This example shows the use of OVP technology in a systemC TLM2.0
environment. It is described in detail in the document "OVPsim Using OVP 
Models in SystemC TLM2.0 Platforms" available in the Imperas/doc directory of
this installation.

This example platform contains one processor.

FILES --------------------------------------------------------------
There are two parts to the example
1. The application; code which runs on the OR1K processor model;
   this is in application/main.c

2. The platform; this is in platform/platform.cpp
 

And scripts to build and run
        example.bat       Build and run for Windows
        example.msvc.bat  Build with MSVC and run for Windows
        example.sh        Build and run for Linux 
        

HOW IT WORKS --------------------------------------------------------------
    The example platform (platform.cpp) includes an OR1K processor model, with its own memory
    and a uart peripheral. The test program runs through a loop writing characters to the uart.
    The uart raises an interrupt when each character is sent. The uart logs output characters 
    to a file
    
    The platform is executed using the command line:
        platform/platform.<IMPERAS_ARCH>.exe <application/application.<CROSS>.elf>
                   
The icmCpu Model.    
    $IMPERAS_HOME/ImperasLib/source/ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/processor.cpp
  and
    $IMPERAS_HOME/ImperasLib/source/ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/processor.hpp
    
    This code is instantiated by a processor-specific C++ wrapper which is in the
    tlm2.0 wrapper with the model. In this case, in
    ImperasLib/source/ovpworld.org/processor/or1k/1.0/tlm2.0/processor.igen.hpp
    
    Each processor runs in a systemC thread which runs a certain number of instructions
    (with SystemC time 'frozen') then sleeps for a 'quantum'.
    The ratio of instructions per quantum to quantum duration gives the effective MIPS
    rating of the processor. The quantum itself controls the
    accuracy with which the processor will interact with other systemC models; a shorter
    quantum gives better accuracy, but increases the simulation overhead. Note that
    this wrapper will only work with TLM blocking transactions.

    Interrupts are effected by calling a processor interrupt routine via a SystemC signal.
    The icmCpu wrapper supports this.
    An interrupt will cause the processor to finish the current instruction then branch
    to the interrupt routine as expected. The processor will still execute the correct
    number of instructions in the quantum.
    Note that since a SystemC thread is not normally interrupted, the only source that
    can interrupt a processor during its quantum is something affected by the processor 
    execution e.g. the processor accessing a model which raises the interrupt. An interrupt
    raised by another model or processor will be serviced next time the processor is 
    scheduled.
    
    It is recommended that all processors use the same quantum, and that the MIPS
    rates of processors in a heterogeneous platform are modeled by setting different
    instructions per quantum on each processor.
    
BUILDING THE PLATFORM ----------------------------------------------------------

The installation of OVPsim (www.ovpworld.org) provides this Example directory. 
In addition
  Obtain and install the toolchain for the OR1K.
  Obtain and install Microsoft Visual C++ (MSVC) (www.microsoft.com).
  Obtain SystemC and build it using MSVC (www.systemc.org).

It is required that installations for both SystemC and TLM2.0 are available. 
Environment variable SYSTEMC_HOME is used by the Makefile
 $IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform. These 
should be set to the installation paths for SYSTEMC v2.3 before attempting
to re-compile.

Platform compilation is carried out in the platform_cpp directory.

Windows MinGW shell. This uses the standard Makefile to build
  mingw32-make -f %IMPERAS_HOME%/ImperasLib/buildutils/Makefile.TLM.platform PLATFORM=platform 

Linux shell. This uses the standard Makefile to build
  make -f $IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform PLATFORM=platform 


Windows MSVC. Start a Visual Studio Command Prompt. In this window:
> cd platform_cpp
> call compile.msvc.bat
> cd ..


The application program int.elf is built using a Makefile in the application 
directory. This will also require that the OR1K toolchain is downloaded and installed.

In a MINGW/MSYS shell on Windows or at a Linux prompt go to the application directory
and type
> cd application
> make
> cd ..

RUNNING THE PLATFORM ---------------------------------------------------------------

To run the platform
> platform_cpp/platform.<ARCH>.exe application/int.OR1K.elf

