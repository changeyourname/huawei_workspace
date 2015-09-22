#!/bin/sh

# Check Installation supports this demo
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -group quantumleap -p install.pkg --nobanner || exit
fi

ARM_VERSATILE_EXPRESS_PLATFORM=${IMPERAS_VLNV}/arm.ovpworld.org/platform/ArmVersatileExpress-CA9/1.0/platform

${ARM_VERSATILE_EXPRESS_PLATFORM}.${IMPERAS_ARCH}.exe \
       --variant ArmVersatileExpress-CA9/cpu=Cortex-A9MPx4   \
       --zimage zImage --initrd fs.img \
       --boot smpboot.ARM_CORTEX_A9.elf  \
       --quantum 0.00001  \
       --finishtime 40 \
       --verbose  \
       --nographics --uart0port auto --uart1port auto \
       --override ArmVersatileExpress-CA9/smartLoader/append=\"rdinit=/etc/init.d/rcS.bench\"
