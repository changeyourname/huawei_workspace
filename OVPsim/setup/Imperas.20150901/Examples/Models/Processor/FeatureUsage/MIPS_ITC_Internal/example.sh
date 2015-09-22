#!/bin/sh

# Check Installation supports this demo
if [ -e ../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

CROSS=MIPS32LE
make -C application CROSS=${CROSS}
make -C platform NOVLNV=1

# Run ICM C Platform
if [ -e platform/platform.${IMPERAS_ARCH}.exe ]; then

  echo "Run ITC example"
  platform/platform.${IMPERAS_ARCH}.exe application/main.${CROSS}.elf \
                                        application/genexception.${CROSS}.elf \
                                        34Kc L I 3 

else
  echo "ICM C Platform not built"
fi

