#!/bin/sh
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.ARM9-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM926EJ-S \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 500000000

