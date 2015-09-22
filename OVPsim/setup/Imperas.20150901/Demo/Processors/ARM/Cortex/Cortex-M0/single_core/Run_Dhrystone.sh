#!/bin/sh
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M0-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M0 \
     --numprocessors 1     --parameter UAL=1 --parameter endian=little    $@     -argv 600000

