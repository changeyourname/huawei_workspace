#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O3-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S \
     --numprocessors 4     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    $@     -argv 4000000

