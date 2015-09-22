#!/bin/sh

# Check Installation supports this example
if [ -e ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -group imperas -p install.pkg --nobanner || exit
fi

make all

if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/libCpuManager.${IMPERAS_SHRSUF} ] && [ "${IMPERAS_RUNTIME}" = "CpuManager" ]; then 

platform/platform.${IMPERAS_ARCH}.exe --program application/asmtest.OR1K.elf --idebug
  
else
  echo "This example requires the Imperas Professional Tools - Not Available in current installation"
fi


