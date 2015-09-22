#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


CROSS=OR1K
make -C application CROSS=${CROSS}

make -C platform clean all

platform/platform.${IMPERAS_ARCH}.exe --program application/asmtest.${CROSS}.elf

make -C platform clean all EXCEPTIONS=1

platform/platform.${IMPERAS_ARCH}.exe --program application/asmtest.${CROSS}.elf
