#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.ARM_CORTEX_M3-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv7-M \
     --numprocessors 1     --parameter UAL=1 --parameter endian=little    $@     -argv 39

