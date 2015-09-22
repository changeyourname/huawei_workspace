#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O1-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
    --gdbconsole --numprocessors 1     --parameter endian=big    --gdbinit dhrystone.gdb $@ 

