#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.ARM_CORTEX_M0-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv6-M \
     --numprocessors 2 --hishare 0x000fffff --loshare 0x0   --parameter UAL=1 --parameter endian=little    $@ 

