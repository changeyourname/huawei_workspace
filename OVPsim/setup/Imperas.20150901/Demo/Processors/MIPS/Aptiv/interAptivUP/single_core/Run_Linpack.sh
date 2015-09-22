#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_MIPS32-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant interAptivUP \
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 11

