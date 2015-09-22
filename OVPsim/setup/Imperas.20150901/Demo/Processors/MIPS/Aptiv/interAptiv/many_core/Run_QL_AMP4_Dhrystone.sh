#!/bin/sh
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant interAptiv \
    --parallel --numprocessors 4     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@ --parallelmax    -argv 4000000

