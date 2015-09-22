#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O1-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F \
    --gdbconsole --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   --gdbinit dhrystone.gdb $@ 

