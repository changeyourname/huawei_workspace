#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_A-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv7 \
    --gdbgui --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  --gdbinit dhrystone.gdb $@ 

