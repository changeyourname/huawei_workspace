#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_UMIPS-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant microAptivP \
    --gdbconsole --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  --gdbinit dhrystone.gdb $@ 

