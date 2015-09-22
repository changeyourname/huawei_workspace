#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


CROSS=OR1K

make -C application CROSS=${CROSS}
make -C peripheral  NOVLNV=1
make -C platform    NOVLNV=1


platform/platform.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf
