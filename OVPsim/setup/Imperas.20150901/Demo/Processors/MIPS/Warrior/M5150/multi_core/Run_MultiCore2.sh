#!/bin/sh
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/multicore2/multicore2.CS_UMIPS-O1-g.elf \
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant M5150 \
     --numprocessors 2 --hishare 0x01ffff --loshare 0x0  --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   $@ 

