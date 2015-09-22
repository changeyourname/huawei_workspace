#!/bin/sh
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O3-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x \
     --numprocessors 1     --parameter endian=big     $@     -argv 2000000

