#!/bin/sh

# Check Installation supports this demo
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

#rem ask user what size of disk he wants
echo "First create an empty disk to Install Linux"
echo "Enter the size in GigaBytes you wish to create"
echo -n "Disk Size in GB (Default 2GB): "
read SIZE

if [ "$SIZE" = "" ]; then
  SIZE=2
fi

#rem build a disk image
create-image.${IMPERAS_ARCH}.exe armhf_hda ${SIZE}G

#fail if a disk image was not created
if [ ! -f armhf_hda ]; then echo "valid disk image 'armhf_hda' was not created"; fi

ARM_VERSATILE_EXPRESS_PLATFORM=${IMPERAS_VLNV}/arm.ovpworld.org/platform/ArmVersatileExpress-CA9/1.0/platform
  
${ARM_VERSATILE_EXPRESS_PLATFORM}.${IMPERAS_ARCH}.exe \
    --variant ArmVersatileExpress-CA9/cpu=Cortex-A9MPx4 \
    --zimage vmlinuz --initrd initrd.gz \
    --boot smpboot.ARM_CORTEX_A9.elf \
    --linuxcmd "mem=1024M root=/dev/ram" \
    --override ArmVersatileExpress-CA9/mmc1/SD_DRIVE=armhf_hda \
    --wallclock
