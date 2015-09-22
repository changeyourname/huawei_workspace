#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant proAptiv \
     --numprocessors 24     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 800000

