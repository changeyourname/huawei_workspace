#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_00 \
    --gdbgui --numprocessors 1     --parameter endian=big    --gdbinit dhrystone_microblaze.gdb $@ 

