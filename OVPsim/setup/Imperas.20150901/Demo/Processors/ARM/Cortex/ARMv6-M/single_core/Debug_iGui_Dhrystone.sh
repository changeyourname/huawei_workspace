#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M0-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv6-M \
    --gdbgui --numprocessors 1     --parameter UAL=1 --parameter endian=little   --gdbinit dhrystone.gdb $@ 

