#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.CS_NIOS2-O0-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F \
     --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    $@     -argv 11

