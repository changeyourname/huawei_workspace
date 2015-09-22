#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.CS_MIPS64-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5Kc \
     --numprocessors 2 --hishare 0x0001ffff --loshare 0x00000000   --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   $@ 

