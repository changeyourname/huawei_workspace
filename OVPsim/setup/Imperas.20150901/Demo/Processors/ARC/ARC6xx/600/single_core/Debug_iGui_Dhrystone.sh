#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 \
    --gdbgui --numprocessors 1     --parameter opt-rf16=0    --gdbinit dhrystone.gdb $@ 

