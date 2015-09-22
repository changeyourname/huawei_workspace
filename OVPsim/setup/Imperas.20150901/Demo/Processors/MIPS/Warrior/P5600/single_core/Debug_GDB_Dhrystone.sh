#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O1-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 \
    --gdbconsole --numprocessors 1 --addressbits 37    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  --gdbinit dhrystone.gdb $@ 

