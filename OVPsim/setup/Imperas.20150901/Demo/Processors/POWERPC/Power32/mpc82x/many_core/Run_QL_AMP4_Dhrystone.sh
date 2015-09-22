#!/bin/sh
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x \
    --parallel --numprocessors 4     --parameter endian=big     $@ --parallelmax    -argv 1000000

