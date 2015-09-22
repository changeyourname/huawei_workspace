#!/bin/sh
# Run_Linpack.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.AARCH64-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch64 \
     --numprocessors 1     --parameter endian=little     $@     -argv 200
