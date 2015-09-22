#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC700-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
    --gdbconsole --numprocessors 1         --gdbinit dhrystone.gdb $@ 

