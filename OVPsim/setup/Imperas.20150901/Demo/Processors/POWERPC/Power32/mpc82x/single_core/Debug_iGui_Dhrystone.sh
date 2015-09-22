#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O1-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x \
    --gdbgui --numprocessors 1     --parameter endian=big    --gdbinit dhrystone.gdb $@ 

