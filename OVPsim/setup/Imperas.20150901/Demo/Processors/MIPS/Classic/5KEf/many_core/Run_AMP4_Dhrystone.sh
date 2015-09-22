#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS64-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5KEf \
     --numprocessors 4     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   $@     -argv 4000000

