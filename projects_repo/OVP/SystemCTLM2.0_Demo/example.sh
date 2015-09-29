#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


CROSS=OR1K

make -C application CROSS=${CROSS}

cd platform_cpp
    make -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.TLM.platform SRC=platform.cpp
cd ..

platform_cpp/platform.${IMPERAS_ARCH}.exe application/int.${CROSS}.elf
