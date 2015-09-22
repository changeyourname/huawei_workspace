#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x \
     --numprocessors 1     --parameter endian=big     $@     -argv 8

