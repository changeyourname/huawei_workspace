#!/bin/sh
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O2-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_10 \
    --parallel --numprocessors 4     --parameter endian=big     $@     -argv 4000000

