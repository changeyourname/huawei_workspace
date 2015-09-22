#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.V850-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850ES \
     --numprocessors 2 --hishare 0x0010ffff --loshare 0x00100000        $@ 

