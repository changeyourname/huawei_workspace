#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.CS_MIPS32LE-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 4KEm \
     --numprocessors 1     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 39

