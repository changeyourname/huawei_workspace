#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.ARM9-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM946E \
     --numprocessors 2 --hishare 0x000fffff --loshare 0x0   --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@ 

