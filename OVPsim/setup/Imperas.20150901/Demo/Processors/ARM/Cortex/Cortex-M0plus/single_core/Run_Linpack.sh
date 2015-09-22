#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.ARM_CORTEX_M0-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M0plus \
     --numprocessors 1     --parameter UAL=1 --parameter endian=little    $@     -argv 8

