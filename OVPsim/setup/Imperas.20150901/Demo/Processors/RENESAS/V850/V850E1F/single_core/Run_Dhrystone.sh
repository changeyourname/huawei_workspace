#!/bin/sh
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E1F \
     --numprocessors 1          $@     -argv 2000000

