#!/bin/sh
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_A-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A8 \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 2000000

