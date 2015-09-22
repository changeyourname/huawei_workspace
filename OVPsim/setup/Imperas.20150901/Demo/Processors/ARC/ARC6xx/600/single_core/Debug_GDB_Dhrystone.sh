#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 \
    --gdbconsole --numprocessors 1     --parameter opt-rf16=0    --gdbinit dhrystone.gdb $@ 

