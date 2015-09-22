#!/bin/sh
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32LE-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 4KEc \
     --numprocessors 1     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@     -argv 10000000

