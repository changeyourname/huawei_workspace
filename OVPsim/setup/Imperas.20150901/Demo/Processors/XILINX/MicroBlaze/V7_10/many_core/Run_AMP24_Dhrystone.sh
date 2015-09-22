#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O2-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_10 \
     --numprocessors 24     --parameter endian=big     $@     -argv 800000

