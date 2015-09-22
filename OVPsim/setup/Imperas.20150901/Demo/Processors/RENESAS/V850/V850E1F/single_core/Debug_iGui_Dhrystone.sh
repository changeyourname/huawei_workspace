#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E1F \
    --gdbgui --numprocessors 1         --gdbinit dhrystone.gdb $@ 

