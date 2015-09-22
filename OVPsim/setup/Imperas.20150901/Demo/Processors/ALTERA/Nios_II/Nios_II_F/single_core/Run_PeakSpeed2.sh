#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_NIOS2-O0-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F \
     --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    $@     -argv 100000000

