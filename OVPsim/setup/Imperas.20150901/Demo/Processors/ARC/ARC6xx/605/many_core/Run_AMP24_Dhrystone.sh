#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 605 \
     --numprocessors 24          $@     -argv 500000

