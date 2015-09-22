#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_20 \
    --gdbconsole --numprocessors 1     --parameter endian=big    --gdbinit dhrystone_microblaze.gdb $@ 

