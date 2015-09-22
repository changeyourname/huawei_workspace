#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.ARC700-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
     --numprocessors 1          $@     -argv 500000000

