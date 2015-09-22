#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O1-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S \
    --gdbgui --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   --gdbinit dhrystone.gdb $@ 

