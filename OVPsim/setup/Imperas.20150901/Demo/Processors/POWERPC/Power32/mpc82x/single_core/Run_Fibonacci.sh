#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.POWERPC32-O3-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x \
     --numprocessors 1     --parameter endian=big     $@     -argv 39

