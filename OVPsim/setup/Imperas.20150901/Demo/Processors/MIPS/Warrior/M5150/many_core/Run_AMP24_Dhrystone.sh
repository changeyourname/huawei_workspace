#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_UMIPS-O3-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant M5150 \
     --numprocessors 24     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 800000

