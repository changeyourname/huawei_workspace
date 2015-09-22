#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.ARM_CORTEX_A-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv7 \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 39

