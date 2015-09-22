#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM9-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM1026EJ-S \
     --numprocessors 4     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 300000

