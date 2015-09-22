#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC700-O2-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
     --numprocessors 4          $@     -argv 300000

