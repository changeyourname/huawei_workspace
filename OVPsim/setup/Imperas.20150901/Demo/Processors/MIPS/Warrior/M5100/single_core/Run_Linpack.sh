#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_UMIPS-O0-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant M5100 \
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 11

