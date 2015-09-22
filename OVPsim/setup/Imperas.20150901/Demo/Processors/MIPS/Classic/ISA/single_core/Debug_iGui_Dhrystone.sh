#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA \
    --gdbgui --numprocessors 1     --parameter endian=little    --gdbinit dhrystone.gdb $@ 

