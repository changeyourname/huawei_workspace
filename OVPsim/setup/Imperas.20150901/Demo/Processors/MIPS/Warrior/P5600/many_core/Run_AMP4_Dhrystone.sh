#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O0-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 \
     --numprocessors 4 --addressbits 37    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 300000

