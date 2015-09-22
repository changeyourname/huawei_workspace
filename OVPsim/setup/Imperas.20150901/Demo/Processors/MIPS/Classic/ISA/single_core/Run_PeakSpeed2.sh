#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.MIPS32LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA \
     --numprocessors 1     --parameter endian=little     $@     -argv 100000000

