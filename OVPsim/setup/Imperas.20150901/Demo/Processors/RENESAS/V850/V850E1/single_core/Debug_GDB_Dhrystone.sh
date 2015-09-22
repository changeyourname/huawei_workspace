#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E1 \
    --gdbconsole --numprocessors 1         --gdbinit dhrystone.gdb $@ 

