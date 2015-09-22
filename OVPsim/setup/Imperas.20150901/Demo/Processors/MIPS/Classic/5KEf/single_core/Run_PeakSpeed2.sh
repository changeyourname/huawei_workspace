#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_MIPS64-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5KEf \
     --numprocessors 1     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   $@     -argv 500000000

