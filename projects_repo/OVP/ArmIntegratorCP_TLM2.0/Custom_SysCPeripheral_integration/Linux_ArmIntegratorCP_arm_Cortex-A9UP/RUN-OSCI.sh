#!/bin/sh

# Check Installation supports this demo
if [ -e ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi


ArmIntegratorCP_tlm2.0.${IMPERAS_ARCH}.exe v Cortex-A9UP p auto
  

echo "Do you want to view ttyAMA0 Console log file [y/N] "
read VIEWIT
if [ "${VIEWIT}" = "y" ]; then
  less uart1.log
fi
