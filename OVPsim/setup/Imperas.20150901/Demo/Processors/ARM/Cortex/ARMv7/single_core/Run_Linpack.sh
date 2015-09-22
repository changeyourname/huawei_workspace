#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.ARM_CORTEX_A-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv7 \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 8

