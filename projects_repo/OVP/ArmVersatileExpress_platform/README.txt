OVPsim_Linux_ArmVersatileExpress_arm_Cortex-A9MP

###############################################################################
# 1. Purpose of Demo
###############################################################################
This demo will show the execution of the Linux kernel on an ARM Cortex-A9MP
on the ARM Versatile Express platform

The Platform contains

   ARM Cortex-A9MPx4 Core (default)
       GIC v1 Interrupt tController (implemented in processor model)
       1 GB DRAM
       128MB Flash Memory
       64MB SRAM
       8MB Video RAM
       Mouse/Keyboard Interfaces
       Four UARTs
       Three Timer SP804
       RTC PL031 Real Time Clock
       CLCD PL111 LCD Controller
       TZPC BP147 TrustZone Controller (Secure)
   MMCI PL181 MultiMedia Card Interface
       LAN9118 Ethernet Controller
       ISP1761 USB Controller

The platform source is found in the VLNV library in directory:
  $IMPERAS_HOME/ImperasLib/source/arm.ovpworld.org/platform/ArmVersatileExpress-CA9/1.0/platform

The platform executable is found in the VLNV library in directory:
  $IMPERAS_VLNV/arm.ovpworld.org/platform/ArmVersatileExpress-CA9/1.0

The platform is used to execute a pre-compiled version of the Linux kernel that 
can be interacted with using a virtualized model of the LCD and keyboard 
interfaces and/or a UART model connected to a telnet session running on the host.

The Linux Kernel provided is from kernel.org. Instructions on building it may
be found below.

An initial RAM disk (initrd) is provided and this is the disk you see in the 
simulated Linux when using the provided scripts to run it. Note that since 
this is a RAM disk any changes made are lost when the simulation ends. See 
below for information on how to modify the files on the initrd.

###############################################################################
# 2. Running the simulation harness using a script provided
###############################################################################

Simply launch the executable by double clicking on one of the batch files, for
example 'RUN_VersatileExpress_ARM_Cortex_A9MPx4.bat'

The simulation will now run and Linux will boot to a login prompt. 
to log in, type the username 'root', no password is required.

It is now possible to interact with Linux running on the ARM processor of the 
virtual platform. 

To finish the simulation, simply close the VGA or UART windows.

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

The Linux Kernel provided is the 3.7.1 version downloaded from www.kernel.org:
   wget http://www.kernel.org/pub/linux/kernel/v3.0/linux-3.7.1.tar.bz2
   tar xf linux-3.7.1.tar.bz2
   cd linux-3.7.1
  
The Kernel must be built with appended device tree support
The config file: 
   arch/arm/configs/vexpress_defconfig
must be modified by appending the following to it:
   CONFIG_ARM_APPENDED_DTB=y
   CONFIG_ARM_ATAG_DTB_COMPAT=y
   CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER=y

The Cross Compiler Toolchain used was:
   CodeSourcery 2011.03-41 version of Sourcery_G++_Lite arm-none-linux-gnueabi
After installing the bin directory must be added to path. 

A variety of Linux utilities must be installed to compile the kernel.
These are not listed here, but may be found on Linux information sites.

To make the .config, zImage and dtb:
   make ARCH=arm vexpress_defconfig
   
   make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- CONFIG_DEBUG_INFO=1 zImage
   scripts/dtc/dtc -I dts -O dtb -o vexpress-v2p-ca9.dtb arch/arm/boot/dts/vexpress-v2p-ca9.dts

Append the device tree blob to the kernel:
   cat arch/arm/boot/zImage vexpress-v2p-ca9.dtb > zImage

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
# 6.a Benchmark Programs
###############################################################################
The provided initrd contains a set of benchmarks programs you can run in
the simulated Linux. They are in the directory /benchmarks.

The provided initrd does not include a compiler but programs that are cross-
compiled on the host may be added to the initrd by following the directions 
below, for either Windows or Linux. 

###############################################################################
# 6.b Compiling User Programs, and adding to disk image - Linux
###############################################################################
Firstly download an ARM GNU/Linux toolchain, e.g. from CodeSourcery
   http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition/
and install this toolchain on your disk.

To re-build the provided benchmarks, first extract the contents of the initrd:
  ./utilities/unpackImage.sh fs.img fs
  
Build benchmark applications in the following manner
  make -C fs/benchmarks -f Makefile.cortex-a9 TOOLDIR=<pathToCompilerInstallation> all

This will create several executables, now we want to add this to our ramdisk
  ./utilities/packImage.sh fs fs.img

When a new simulation is run the re-compiled benchmarks will be seen on the disk


###############################################################################
# 6.c Compiling User Programs, and adding to disk image - Windows (MSYS/Mingw)
###############################################################################
Windows does not support the utilities necessary for packing and unpacking the 
initrd image so you must use a Linux host to do this.

###############################################################################
# 7. Command Line Execution Options
###############################################################################

Additional command line options may be used when running the platform. These may
be added to the .bat or .sh scripts provided.

'--variant cpu=<new variant>'  to modify the processor type modeled. 
                  If this is modified from the default ARM Cortex-A9MPx4 the 
                  operation of the platform may change.
          
'--nographics'    may be used to disable the LCD screen. This should only be 
                  used if a different application that utilities the UARTs for
                  communication is being run.  

'--uart<n>port <port>|<auto>' 
                  configures uart <n> to wither open the indicated port
                  and wait for a connection or to automatically open
                  a telnet window connected to the uart.

'--boot <boot code>'   
                  specify a boot image to be loaded and executed prior to
                  the kernel. A sample is provided that handles booting
                  the secondary processors in the file smpboot.s.
                  
'--wallclock'     this is used to reduce the simulation speed to a maximum of
                  'real' time. By default the simulator will run as 'fast as possible'

###############################################################################
# 8. Starting network interface and running Applications
###############################################################################

The Platform contains a model of the Network interface card. In order to allow
network traffic to be transferred to and from the host machine, please do
the following

1.1 start and configure eth0
ifconfig eth0 10.0.2.7 netmask 255.255.255.0 up

1.2 add default GW
route add default gw 10.0.2.2

1.3 set up DNS
echo "nameserver 10.0.2.3" > /etc/resolv.conf

1.4 Application example - browse google
lynx http://www.google.com/

any other utilities should now work such as telnet, rlogin etc

###############################################################################
# 9. Installing Debian Linux
###############################################################################
1. Firstly download the Debian installation files
DISTRO=wheezy
wget ftp://ftp.debian.org/debian/dists/${DISTRO}/main/installer-armhf/current/images/vexpress/netboot/{vmlinuz*,initrd*}
mv vmlinuz-* vmlinuz

2. Create an installation disk
create-image.${IMPERAS_ARCH}.exe armhf_hda 2G

3. Run simulator and follow installation guide
Install_Debian_VersatileExpress_ARM_Cortex_A9MPx4.sh


