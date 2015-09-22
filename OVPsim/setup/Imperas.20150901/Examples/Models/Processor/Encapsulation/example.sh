#!/bin/sh

# Check Installation supports this example
if [ -e ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)

make all XTHOME=$(pwd)/externalISS

platform.exe testcase.risc32
