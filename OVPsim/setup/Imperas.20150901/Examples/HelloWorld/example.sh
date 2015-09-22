#!/bin/sh

# Check Installation supports this example
if [ -e ../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

# Build Application
make CROSS=OR1K

# Build Platform
make -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.platform SRC=platform.c NOVLNV=1

platform.${IMPERAS_ARCH}.exe --program application.OR1K.elf --processortype or1k

