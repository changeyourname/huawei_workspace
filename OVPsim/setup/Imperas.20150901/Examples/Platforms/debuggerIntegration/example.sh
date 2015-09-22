#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


CROSS=OR1K

make -C application CROSS=${CROSS}
make -C platform SRC=platform1.c
make -C platform SRC=platform2.c

# Run using Imperas Professional Simulator (if available)
if [ -e "${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/libCpuManager.${IMPERAS_SHRSUF}" ]; then 

  export IMPERAS_RUNTIME=CpuManager
  
  platform/platform1.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf
  platform/platform2.${IMPERAS_ARCH}.exe --program application/asmtest.${CROSS}.elf

else
  echo "This example requires the Imperas Professional Simulator - Not Available in current installation"
fi
