#!/bin/sh

# Check Installation supports this example
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

CROSS=OR1K
make -C application CROSS=${CROSS}
make -C platform
make -C loader


echo Run OVPsim
platform/platform.${IMPERAS_ARCH}.exe --program application/hello.${CROSS}.s19

# Run using Imperas Professional (if available)
if [ -e "${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/imperas.exe" ]; then

  echo Run Imperas
  imperas.exe --objectloader loader/loader.${IMPERAS_SHRSUF} -objfile application/hello.${CROSS}.s19 -v

else
  echo "This example requires the Imperas Professional User interface - Not Available in current installation"
fi

if [ -e "${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/libCpuManager.${IMPERAS_SHRSUF}" ]; then

  echo Run CpuManager
  export IMPERAS_RUNTIME=CpuManager
  platform/platform.${IMPERAS_ARCH}.exe --program application/hello.${CROSS}.s19

else
  echo "This example requires the Imperas Professional Simulator - Not Available in current installation"
fi

