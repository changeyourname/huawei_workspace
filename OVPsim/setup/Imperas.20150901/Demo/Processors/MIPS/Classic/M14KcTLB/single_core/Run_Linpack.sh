#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_UMIPS-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant M14KcTLB \
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 8

