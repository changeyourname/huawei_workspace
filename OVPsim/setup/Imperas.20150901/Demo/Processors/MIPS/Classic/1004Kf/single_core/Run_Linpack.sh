#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_MIPS32LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 1004Kf \
     --numprocessors 1     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 11

