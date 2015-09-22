#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_MIPS32-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant proAptiv \
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 300000000

