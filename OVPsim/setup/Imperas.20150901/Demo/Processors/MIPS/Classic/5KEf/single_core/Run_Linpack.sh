#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_MIPS64-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5KEf \
     --numprocessors 1     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   $@     -argv 11

