#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.V850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2M \
     --numprocessors 1          $@     -argv 11

