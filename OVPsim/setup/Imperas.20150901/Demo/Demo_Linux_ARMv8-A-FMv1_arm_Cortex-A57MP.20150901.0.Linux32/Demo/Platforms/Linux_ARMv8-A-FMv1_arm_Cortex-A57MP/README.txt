Linux_ArmVersatileExpress_arm_Cortex-A57MP

###############################################################################
# 1. Purpose of Demo
###############################################################################
This demo will show the execution of the Linux kernel on an ARM Cortex-A57MP 
on the ARM v8-A Foundation Model v1 platform as described in ARM document
DUI 0677C.

The Platform contains

	   ARM Cortex-A57MP Core (Cortex-A57MPx4 default)
       GIC v2 (implemented in the processor model)
       8GB DRAM
	   System Registers
	   Four UARTs
	   Virtio block device

	   There is a document that describes the details of the platform and its configuration options, memory map, and components in the file:
	   $IMPERAS_HOME\ImperasLib\source\arm.ovpworld.org\platform\ARMv8-A-FMv1\1.0\doc\Imperas_Platform_User_Guide_ARMv8-A-FMv1.pdf
	   
The platform source is found in the VLNV source library in directory:
    $IMPERAS_HOME/ImperasLib/source/arm.ovpworld.org/platform/ARMv8-A-FMv1/1.0/platform
    
The platform executable is found in the VLNV binary library in directory:
    $IMPERAS_VLNV/arm.ovpworld.org/platform/ARMv8-A-FMv1/1.0

NOTE: IMPERAS_HOME and IMPERAS_VLNV are two of the environment variables setup 
      when OVP or Imperas products are installed as detailed in the Imperas 
	  Installation and getting Started Guide.
	
The platform is used to execute a pre-compiled version of the Linux kernel that 
can be interacted with using a virtualized model of the UART connected to a
telnet session running on the host.

The Linux Kernel provided is from linaro.org. Instructions on building it may
be found in the file Makefile.LinuxKernel.

An initial RAM disk (initrd) is provided and this is the disk you see by default
in the simulated Linux. Note that since this is a RAM disk any changes made are 
lost when the simulation ends. See below for information on how to modify the
files on the initrd.

###############################################################################
# 2 Running the simulation harness using a script provided
###############################################################################

Simply launch the executable by double clicking on one of the batch files, for
example 'RUN_VersatileExpress_ARM_Cortex_A57MPx4.bat' or invoking one of the 
shell scripts.

The simulation will now run and Linux will boot to a login prompt. 
to log in, type the username 'root', no password is required.

To finish the simulation, simply close the Terminal windows.

Statistics will be printed upon completion of the simulation.


###############################################################################
# 3. Interpreting results
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
# 4. Build Linux Kernel image
###############################################################################

# Cross Compiler Toolchain:
#   Linaro gcc-linaro-aarch64-linux-gnu-4.8-2013.11_Linux
# Prebuilt binaries may be downloaded from:
#   http://releases.linaro.org/13.11/components/toolchain/binaries

Please examine the provided Makefile 'Makefile.LinuxKernel'

###############################################################################
# 5. Disk Utilities
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
# 6. Additional info
###############################################################################
See ArmV8LinuxNotes.txt for additional info on the platform and running it with
Linux root file systems.

##
