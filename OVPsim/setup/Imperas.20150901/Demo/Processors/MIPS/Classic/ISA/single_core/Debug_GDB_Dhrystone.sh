#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA \
    --gdbconsole --numprocessors 1     --parameter endian=little    --gdbinit dhrystone.gdb $@ 

