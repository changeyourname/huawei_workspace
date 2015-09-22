#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 \
     --numprocessors 4          $@     -argv 1000000

