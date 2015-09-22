#!/bin/sh

# Check Installation supports this demo
if [ -e ../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

make run
