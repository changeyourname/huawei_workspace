#!/bin/sh

# Check Installation supports this demo
#if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
#  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
#fi

PLATFORM=ARMv8-A-FMv1
PLATFORMVLNV=${IMPERAS_VLNV}/arm.ovpworld.org/platform/${PLATFORM}/1.0/platform.${IMPERAS_ARCH}.exe

${PLATFORMVLNV} --output imperas.log --verbose \
 \
 --startaddress 0x80000000 \
 \
 --override ${PLATFORM}/smartLoader/kernel=Image \
 --override ${PLATFORM}/smartLoader/initrd=initrd.arm64.img \
 --override ${PLATFORM}/smartLoader/dtb=foundation-v8.dtb \
 \
 --override ${PLATFORM}/uart0/console=1 \
 --override ${PLATFORM}/uart1/console=1
 

