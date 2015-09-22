#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS64-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5KEc \
     --numprocessors 24     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   $@     -argv 800000

