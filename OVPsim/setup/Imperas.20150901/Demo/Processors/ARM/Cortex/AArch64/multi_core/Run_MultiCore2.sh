#!/bin/sh
# Run_MultiCore2.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.AARCH64-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch64 \
     --numprocessors 2 --hishare 0x800FFFFF --loshare 0x80000000   --parameter endian=little     $@ 

