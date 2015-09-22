#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_UMIPS-O0-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant M5100 \
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 300000000

