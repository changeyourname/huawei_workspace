#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_MIPS32-O1-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 \
     --numprocessors 1 --addressbits 37    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 10

