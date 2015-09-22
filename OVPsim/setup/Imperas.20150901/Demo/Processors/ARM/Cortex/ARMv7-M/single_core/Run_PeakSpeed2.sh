#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.ARM_CORTEX_M3-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv7-M \
     --numprocessors 1     --parameter UAL=1 --parameter endian=little    $@     -argv 500000000

