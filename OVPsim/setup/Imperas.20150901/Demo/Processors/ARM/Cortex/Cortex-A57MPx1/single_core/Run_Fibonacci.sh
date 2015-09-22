#!/bin/sh
# Run_Fibonacci.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.AARCH64-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A57MPx1 \
     --numprocessors 1     --parameter endian=little     $@     -argv 39
