#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_MIPS32LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 1004Kc \
     --numprocessors 1     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 500000000

