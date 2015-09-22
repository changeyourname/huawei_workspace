###############################################################################
    Date : 20150825                        Version : 20150901.0
###############################################################################

Welcome to the README for Imperas and Open Virtual Platforms installations.

**
If you have installed the OVP or Imperas products 
Please go to -> doc/index.html with a web browser for full documentation.

If you have installed stand-alone demos then the documentation will not be available
in this installation. Please visit www.ovpworld.org->documentation 
**

Linux Installation from Self Extracting Packages:
to Install under Linux, run the self extracting packages this should be in a 
directory containing files of the form
    <Package>.<Release Major>.<Release Minor>.<Host Architecture>.exe

<Release Major> is the major release number of the product
<Release Minor> is the minor release number of the product
<Package> is the name of a package to install.
<Host Architecture> is either Linux32 or Linux64, host architecture dependent.

NOTE: A Linux32 product may be installed and execute on a 'Linux64' host if 
      32-bit compatibility libraries are available on the host machine.

For Example, 
    imperas.20150901.0.Linux32.exe
    mips32.model.20150901.0.Linux64.exe
    mips32.toolchain.20150901.0.Linux32.exe

Releases with the same <Release Major> version support compatible versions of the public APIs.

It may be required to make the packages executable, this can be done using the command

  % chmod +x <Package>.<Release Major>.<Release Minor>.<Host Architecture>.exe

When you run the self extracting packages, depending upon the licensing 
restrictions of the packages, you may be prompted to agree to the terms 
and conditions, failure to do so will result in a failure to extract the 
package.

Linux Installation:
Imperas or OVP are installed into a directory of the form 

	/home/user1/Imperas.<Release Major>

where <Release Major> is the Major release number of the product

It is required that the following environment variables are set: 
  IMPERAS_HOME is the root of the Imperas installation
  IMPERAS_ARCH should be set to Linux32 or Linux64 (host architecture dependent)
  IMPERAS_UNAME should be set to Linux
  IMPERAS_SHRSUF should be set to so
  IMPERAS_VLNV is the root of the component model library
  IMPERAS_RUNTIME this is the runtime library selected by the simulator
  PATH updated
  LD_LIBRARY_PATH is set to the runtime library directory
  LM_LICENSE_FILE is set to point at the license file or server port

This can be done by sourcing a script, which is supplied, in bash shell 
and executing a function as follows

  % source <install directory>/Imperas.20150901.0/bin/setup.sh
  % setupImperas <install directory>/Imperas.20150901.0

This should set the following variables
  export IMPERAS_HOME=<install directory>/Imperas.20150901.0
  export IMPERAS_ARCH=Linux32 (or Linux64)
  export IMPERAS_UNAME=Linux
  export IMPERAS_UNAME=so
  export IMPERAS_VLNV=$IMPERAS_HOME/lib/$IMPERAS_ARCH/ImperasLib
  export IMPERAS_RUNTIME=CpuManager
  export PATH=$PATH:$IMPERAS_HOME/bin/$IMPERAS_ARCH
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMPERAS_HOME/bin/$IMPERAS_ARCH:$IMPERAS_HOME/lib/$IMPERAS_ARCH/External/lib
  export LM_LICENSE_FILE=$LM_LICENSE_FILE:/path/to/license/file.lic

It may be required to set the environment variable IMPERAS_PERSONALITY when using 
the Imperas Developer products or other specific products. For example, when the Imperas_DEV 
package is installed, there are three options available; Controller, Standard and Multi. These have
specific feature sets available to them 
  export IMPERAS_PERSONALITY=CPUMAN_STANDARD 


It is possible to run a Linux32 product installation on a 'Linux64' host if 32-bit 
compatibility libraries are available on the host machine. To setup the environment 
in the current shell the setupImperas function may be used as follows

  % setupImperas <install directory>/Imperas.20150901.0 -m32

  
This document describes the installations you have performed on this machine.
It describes the directory and file structure for a full download.
If you have not downloaded everything, then you may not have all the files present.

You can install the Imperas products and OVP in the same place and they are designed to co-exist.

For OVP please go to www.ovpworld.org/download.php, register, login, and download what you need.
Any questions - please ask in the ovpworld forums, or email us at info@ovpworld.org.

For Imperas products, please contact Imperas info@imperas.com for product information.


Obtaining a License to run the OVPsim Simulator
-----------------------------------------------
A free demonstration/evaluation license to run the OVPsim simulator may be obtained from 
the downloads page of the OVPworld website, under the heading 'Obtaining a license key'
Once you have your license key you should, either
1. Place it on your machine and point to it using the environment variable IMPERASD_LICENSE_FILE (or add to LM_LICENSE_FILE), or
2. Place the license data in the default file found, for example, at Imperas.20150901.0/OVPsim.lic

CAUTION: If using the default location in the Imperas installation this will be overwritten if a 
new installation is carried out or deleted if an installation is uninstalled. 


Model Source Code
-----------------------------------------------
The model source code is provided in the source library provided as part of a FULL OVP or Imperas product installation. It 
is not provided with demo example installation packages.

The library is found at IMPERAS_HOME/ImperasLib/source
The library (source and binary) is structured as Vendor/Library/Name/Version (VLNV)  
Rebuilding of individual components or the complete library is carried out using the build 
system, files for which are found in IMPERAS_HOME/ImperasLib/source/buildutils

The source model consists of a model directory containing the source and a tlm2.0 directory 
containing the TLM2.0 interface.

For further information please consult the Installation and Getting Started guide 

OVP Fast Processor Model Variant Documentation
-----------------------------------------------
An OVP Fast Processor Model will normally support several variants. For example, the 'arm' model supports
ARM7TDMI, Cortex-A9MPx4 etc, the 'mips32' model supports 74Kc, 1004Kf, M14K etc. 
Each variant has a document to provide it's specific configuration. These are found with the processor 
model source in a doc directory parallel to the model source directory within the VLNV.

Licenses
    IMPERAS_LICENSE
    OVP_IMPERAS_LICENSE
    OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0
-----------------------------------------------
The software and contents of this directory tree are covered by one or more Software License Agreements. 
For OVP you will have accepted OVP click through license to have unpacked these files. The SLA is 
contained in the file: OVP_IMPERAS_LICENSE, available in txt, rtf and pdf formats.
For the Imperas Professional products you will have a signed license agreement that covers your usage 
of the Imperas commercial products, that is contained in IMPERAS_LICENSE, available in txt, rtf and
pdf formats.
The model source code is provided under a modified Apache 2.0 license contained in the 
file OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf

Demo (installed as part of the demo installers)
-----------------------------------------------
This is where the self contained demos live. 
For example you will find directories, such as: OVPsim_single_or1k
If you go into these directories, you will find a README.txt which explains what 
is in that directory and how to run it. There will be source files of applications 
and platform, executables, and a .jpg showing the structure of the demo platform etc.

doc (installed as part of OVPsim, and Imperas)
-----------------------------------------------
There is an index.html file that is the starting point of our Browser based documentation.
Click your browser on doc/index.html to look at the documentation.
There are .pdf user and reference guides, and .html API documentation created from the .h 
files using Doxygen.

Examples
-----------------------------------------------
This is where the OVP and Imperas examples live. You will find examples of simple 
platforms, simple benchmarks / applications and Makefiles etc to build them.
For Imperas installations you will also find here examples of debugging with the 
Imperas Multicore Debugger and also the Imperas Verification/Analysis/Profiling tools.

Examples\Debugger - examples of using the integrated Imperas Multicore Debugger
Examples\HelloWorld - the simplest example, with all source files, etc to re-build it...
Examples\Platforms - a directory for each example of building platforms using ICM
Examples\Models\Processors - a directory for each example of building a processor with VMI
Examples\Models\Peripherals - a directory for each walked through peripheral model using BMH/PPM
Examples\Verification\

ImperasLib (for Imperas created source)
-----------------------------------------------
For library components shipped as source (created by Imperas):
ImperasLib\source\imperas.com\peripheral
ImperasLib\source\imperas.com\processor (empty until open source released)

lib (for binaries)
-----------------------------------------------
For library components shipped as binaries (created by Imperas):
lib\<Host Architecture>\ImperasLib\imperas.com\peripheral\
lib\<Host Architecture>\ImperasLib\imperas.com\processor\
lib\<Host Architecture>\ImperasLib\imperas.com\semihosting\

For Cross Compiler components to build applications etc:
lib\<Host Architecture>\CrossCompiler
lib\<Host Architecture>\TargetLibraries\

bin
-----------------------------------------------
This is where the binaries of the simulator and its libraries live.
Other utility programs are also put here.

bin/<Host Architecture>/imperasOVP_versionCheck.exe
-----------------------------------------------
This release includes a feature which will access the OVPworld website to see if
a newer version of the simulator is available. Your accessing of the OVPworld 
website is recorded. If you wish to disable this feature, after installation 
please delete the executable from the installation Directory, the executable
 to remove is called :-
    "imperasOVP_versionCheck.exe"

cfg
-----------------------------------------------
used during build/release process - ignore

CHANGELOG.Imperas.txt / CHANGELOG.CpuManager.txt / CHANGELOG.OVP.txt
-----------------------------------------------
These documents detail the recent changes made to the Imperas / OVP products
since the last release. This document is accessible through the html browser interface
from doc/index.html. The contents of the files cover:
  CHANGELOG.SDK.txt        : Imperas Professional Product M*SDK
  CHANGELOG.iGen.txt       : Imperas Model Framework Generator
  CHANGELOG.CpuManager.txt : Imperas Professional Simulator M*SIM
  CHANGELOG.OVP.txt        : OVP Products


ICM Platform Run Time Simulator Selection
-----------------------------------------------
At runtime the simulator dynamic link library is loaded into the platform. By default
the OVPsim simulator is loaded from libOVPsim.so. 
It is possible to select an alternative simulator such as CpuManager provided with the 
Imperas Professional Tools by setting an environment variable IMPERAS_RUNTIME. 
This can be done in an MSYS shell, for example
> export IMPERAS_RUNTIME=CpuManager

Product Testing
-----------------------------------------------
Testing is carried out on 
  Linux32 Fedora Core version 12 (2.6.31.5-127.fc12.i686 #1 SMP Sat Nov 7 21:41:45 EST 2009 i686 i686 i386 GNU/Linux)
  Linux64 Fedora Core version 18 (3.8.5-201.fc18.x86_64 #1 SMP Thu Mar 28 21:01:19 UTC 2013 x86_64 x86_64 x86_64 GNU/Linux)

(README.Linux.txt v1.9)
##

