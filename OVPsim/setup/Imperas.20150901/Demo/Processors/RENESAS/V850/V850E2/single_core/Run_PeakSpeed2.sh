#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.V850-O0-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2 \
     --numprocessors 1          $@     -argv 500000000

