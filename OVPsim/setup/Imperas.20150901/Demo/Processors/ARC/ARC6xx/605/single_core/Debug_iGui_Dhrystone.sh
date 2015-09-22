#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 605 \
    --gdbgui --numprocessors 1         --gdbinit dhrystone.gdb $@ 

