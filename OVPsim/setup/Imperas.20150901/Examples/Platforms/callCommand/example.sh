#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


CROSS=MIPS32

make -C application CROSS=${CROSS}
make -C platform

# Run using Imperas Professional Simulator (if available)
if [ -e "${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/libCpuManager.${IMPERAS_SHRSUF}" ]; then 

  export IMPERAS_RUNTIME=CpuManager

  platform/platform.${IMPERAS_ARCH}.exe --program application/application.${CROSS}.elf

else
  echo "This example requires the Imperas Professional Simulator - Not Available in current installation"
fi
