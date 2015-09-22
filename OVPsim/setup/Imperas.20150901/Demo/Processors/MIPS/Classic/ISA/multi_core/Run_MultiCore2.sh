#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.MIPS32LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA \
     --numprocessors 2 --hishare 0x9fffffff  --loshare 0x80000000   --parameter endian=little     $@ 

