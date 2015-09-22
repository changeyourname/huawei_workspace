#!/bin/sh

# Check Installation supports this example
if [ -e ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


make clean all
platform/platform.${IMPERAS_ARCH}.exe --program application/asmtest.OR1K.elf

make clean all MODAL=1
platform/platform.${IMPERAS_ARCH}.exe --program application/asmtest.OR1K.elf
