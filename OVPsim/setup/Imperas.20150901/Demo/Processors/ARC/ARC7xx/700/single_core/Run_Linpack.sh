#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.ARC700-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
     --numprocessors 1          $@     -argv 11

