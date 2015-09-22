#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32LE-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 24Kf \
     --numprocessors 24     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 800000

