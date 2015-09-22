#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.OR1K-O1-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --gdbconsole --numprocessors 1         --gdbinit dhrystone.gdb $@ 

