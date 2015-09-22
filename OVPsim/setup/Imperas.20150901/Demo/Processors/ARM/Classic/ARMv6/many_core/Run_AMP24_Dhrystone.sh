#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM7-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv6 \
     --numprocessors 24     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 500000

