#!/bin/sh
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O2-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA \
     --numprocessors 24     --parameter endian=little     $@     -argv 800000

