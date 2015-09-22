#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.CS_UMIPS-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant microAptivCF \
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 39

