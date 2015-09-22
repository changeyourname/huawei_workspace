#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2M \
     --numprocessors 4          $@     -argv 1000000

