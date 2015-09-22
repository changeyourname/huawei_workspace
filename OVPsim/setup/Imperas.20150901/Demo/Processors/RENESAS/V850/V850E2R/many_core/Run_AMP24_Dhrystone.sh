#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2R \
     --numprocessors 24          $@     -argv 500000

