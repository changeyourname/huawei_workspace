#!/bin/sh
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O2-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA \
     --numprocessors 4     --parameter endian=little     $@     -argv 1000000

