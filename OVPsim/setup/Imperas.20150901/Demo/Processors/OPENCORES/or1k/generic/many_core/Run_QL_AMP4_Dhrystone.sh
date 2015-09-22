#!/bin/sh
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.OR1K-O3-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --parallel --numprocessors 4          $@     -argv 4000000

