#!/bin/sh
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS64-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5Kc \
     --numprocessors 1     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   $@     -argv 600000

