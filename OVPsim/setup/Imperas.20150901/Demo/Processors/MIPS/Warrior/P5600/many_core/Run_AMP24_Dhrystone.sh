#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O0-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 \
     --numprocessors 24 --addressbits 37    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 500000

