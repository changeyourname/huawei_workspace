#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O3-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 605 \
     --numprocessors 4          $@     -argv 300000

