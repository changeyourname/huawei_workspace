#!/bin/sh
# Debug_iGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS64-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5KEc \
    --gdbgui --numprocessors 1     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org  --gdbinit dhrystone.gdb $@ 

