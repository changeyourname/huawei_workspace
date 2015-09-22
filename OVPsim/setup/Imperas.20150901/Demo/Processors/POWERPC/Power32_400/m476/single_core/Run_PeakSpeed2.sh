#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
     --numprocessors 1     --parameter endian=big     $@     -argv 500000000

