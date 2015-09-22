#!/bin/sh
# Run_AMP24_Dhrystone.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.AARCH64-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch64 \
     --numprocessors 24     --parameter endian=little     $@     -argv 800000

