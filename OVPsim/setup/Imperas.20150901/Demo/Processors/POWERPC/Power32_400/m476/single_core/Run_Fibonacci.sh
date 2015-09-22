#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.POWERPC32-O3-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
     --numprocessors 1     --parameter endian=big     $@     -argv 39

