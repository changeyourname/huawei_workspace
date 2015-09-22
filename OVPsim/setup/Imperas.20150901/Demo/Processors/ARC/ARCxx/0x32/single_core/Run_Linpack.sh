#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.ARC600-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 \
     --numprocessors 1          $@     -argv 6

