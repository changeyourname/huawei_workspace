#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.ARM_CORTEX_A-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A9MPx1 \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 300000000

