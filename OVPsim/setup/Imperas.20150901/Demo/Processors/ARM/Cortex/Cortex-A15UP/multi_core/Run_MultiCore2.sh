#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.ARM_CORTEX_A-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A15UP \
     --numprocessors 2 --hishare 0x000fffff --loshare 0x0   --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@ 

