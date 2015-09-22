#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC700-O2-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
     --numprocessors 24          $@     -argv 800000

