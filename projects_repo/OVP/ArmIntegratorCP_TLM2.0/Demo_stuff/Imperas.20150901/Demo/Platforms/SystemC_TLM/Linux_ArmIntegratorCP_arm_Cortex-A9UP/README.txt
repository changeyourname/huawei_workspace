ArmIntegratorCP_tlm2.0

###############################################################################
# Demo Platform
###############################################################################
This demo will show how to execute linux running on an ARM Cortex-A9UP on the 
ARM Integrator platform

The Platform contains

	Core Module
	   ARM Cortex-A9UP Core
	   Interrupt Controller
	   UART
	   128M Bytes RAM (bridged to separate area)
	Base Board
	   LCD Controller
	   Mouse/Keyboard Interfaces
	   Flash Memory

The platform is used to execute a pre-compiled version of linux that can be 
interacted with using a virtualized model of the LCD and keyboard interfaces.


The simulation harness ArmIntegratorCP_tlm2.0.<OS>.exe was compiled 
using MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# Running the simulation harness
###############################################################################

# Microsoft window manager

Simply launch the executable by double clicking one of the batch files.

# command line

If running a DOS command window, or a mingw / cygwin shell, or a Linux shell 
simply change directory to the demo directory, then type the name of the executable
at the shell prompt with the required arguments, e.g.
cmd > ArmIntegratorCP_tlm2.0.<OS>.exe v Cortex-A9UP
By default it will load zImage, fs.img as linux kernel and filesystem so these files should be present alongwith the platform's exe file


The simulation will now run and Linux will boot to a login prompt. 
to log in, type the username 'root', no password is required
There appears to be a Linux bug which occasionally causes the VGA text
to be skewed across the screen, without the correct CR/LF, if this occurs
simply log out, and log in again.
It is now possible to interact with Linux running on the ARM processor of the 
virtual platform. 

###############################################################################
# Direct FrameBuffer Application
###############################################################################
The ram disk image contains a frameBuffer example that can be run to show the 
true simulation performance. After logging in to run this example type
root> df_andi

###############################################################################
# Stopping the Simulation
###############################################################################

To stop the example executing hit the escape key on the keyboard

To finish the simulation, simply close the VGA window or disconnect from the 
UART, depending upon the Linux kernel configuration being used.

Statistics will be printed upon completion of the simulation.


###############################################################################
# Interpreting results
###############################################################################
At the end of simulation, a number of statistics will be printed.
Amongst the statistical information which is reported, are the number
of 'Simulated instructions' and the 'Simulated MIPS'.
The 'Simulated instructions' will vary depending upon the application being
executed, this count indicates the number of simulated processor
instructions for the processors in the platform.
The 'Simulated MIPS' will be a measure of the number of 'Simulated
instructions' over the host elapsed time. Typically the 'Simulated MIPS' number
should be in the 100's of MIPS range.


###############################################################################
# Disk Utilities
###############################################################################
There are disk utility scripts provided in the 'utilities' directory for this 
demonstration platform. They may be used to add and remove files in the 
provided initrd image. The utilities are:

packImage.sh <host dir> <image file>
    Will take a host directory and turn this into an image file

unPackImage.sh <image file> <host dir>
    Will take an image file and unpack it to a host file system directory 

appendImage.sh <host dir> <input image> <output image>
    Will take a host directory and a previously packed image and create a new
    image by appending the directory contents 
    
###############################################################################
# Compiling User Programs, and adding to disk image
###############################################################################

# 1. Linux

Firstly download the ARM linux toolchain.
The toolchain used in building the Linux kernel and so used to create compatible
applications was obtained from CodeSourcery. Install this toolchain on your host 
machine. 
http://www.codesourcery.com/sgpp/lite/arm/portal/release858

Extract Ramdisk to file system

% utilities/unpackImage.sh fs.img fs

The Benchmark directory on the file system contains several standard benchmarks
and a Makefile. Build the benchmark applications in the following manner.

% make -C fs/benchmarks TOOLDIR=<pathToCompilerInstallation> all

Additional files can be added to the fs directory tree as desired.

Package filesystem back into a ramdisk

% packImage.sh fs fs.img

Rerun the simulator, now the simulated files system will contain any files
that were added and packed.

Note that the file system in this simulated Linux is a ram disk and any changes
made to it are lost when the simulation terminates.


# 2. Windows (MSYS/Mingw)

Firstly download the ARM linux toolchain.
The toolchain used in building the Linux kernel and so used to create compatible
applications was obtained from CodeSourcery. Install this toolchain on your host 
machine. 
http://www.codesourcery.com/sgpp/lite/arm

you will also need a windows version of cpio, this can be found here
http://sourceforge.net/projects/gnuwin32/files/cpio/cpio-2.6-2.exe/download
Install cpio, and ensure it appears on your path in the MSYS shell

Build benchmark applications in the following manner

% make -C benchmarks TOOLDIR=<pathToCompilerInstallation> all

Unfortunately under windows we cannot unpack the image to a filesystem
because windows does not understand symbolic links, which are present on the 
simulated disk, So under Windows we will simply append the files onto the existing
image

% appendImage.sh benchmarks fs.img newfs.img
% mv newfs.img fs.img

Re run the simulator, this time there will be a top level directory called
'benchmarks', which contains the applications build in the previous steps
these can now be executed in the simulated Linux



###############################################################################
# Re-Building
###############################################################################

In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or the Imperas Professional Tools M*DEV 'Imperas_DEV'
or M*SDK 'Imperas_SDK' packages.

The installers are
  'OVPsim'            OVPsim.<major version>.<minor version>.<OS>.exe
  'Imperas_DEV'  Imperas_DEV.<major version>.<minor version>.<OS>.exe
  'Imperas_SDK'  Imperas_SDK.<major version>.<minor version>.<OS>.exe


The simulation platform ArmIntegratorCP_tlm2.0.<OS>.exe was compiled using MinGW/MSYS 
under Windows, and GCC under Linux.

The compilation can be performed using the following command line

>make -f IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform \
         SRC=ArmIntegratorCP_tlm2.0.cpp

The common Makefiles include environment information for the location of the 
SYSTEMC installation.

These must be correctly modified for your installation

    For example:

    # MinGW WINDOWS Configuration
    
    # Set this to your System C installation
    SYSTEMC  = C:\SystemC\Windows\systemc-2.3.0\lib-mingw
    
    # Linux Configuration
    
    # Set this to your SystemC installation
    SYSTEMC  = /home/SystemC/Linux/systemc-2.3.0

    
###############################################################################
# SystemC platform does not support Control-C termination
###############################################################################
The SystemC platform does not allow the simulation to be terminated by the use 
of Control-C. 
The simulation can be terminated by, either:
1. On a Windows host, closing the shell
2. On a Linux host, background the job and then terminate.  

