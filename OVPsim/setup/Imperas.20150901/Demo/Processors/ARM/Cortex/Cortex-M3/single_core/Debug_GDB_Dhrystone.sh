#!/bin/sh
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M3-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M3 \
    --gdbconsole --numprocessors 1     --parameter UAL=1 --parameter endian=little   --gdbinit dhrystone.gdb $@ 

