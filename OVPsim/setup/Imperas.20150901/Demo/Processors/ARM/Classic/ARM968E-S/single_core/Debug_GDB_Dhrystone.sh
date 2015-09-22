#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM9-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM968E-S \
    --gdbconsole --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  --gdbinit dhrystone.gdb $@ 

