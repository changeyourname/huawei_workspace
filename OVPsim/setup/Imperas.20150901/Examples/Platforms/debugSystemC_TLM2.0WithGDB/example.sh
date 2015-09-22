#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

make -C application application.OR1K.elf

cd platform
    make -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.TLM.platform \
        SRC=platform.cpp
cd ..

platform/platform.${IMPERAS_ARCH}.exe application/application.OR1K.elf
