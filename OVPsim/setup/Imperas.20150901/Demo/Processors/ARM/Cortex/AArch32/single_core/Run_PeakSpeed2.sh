#!/bin/sh
# Run_PeakSpeed2.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.AARCH32-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch32 \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 300000000

