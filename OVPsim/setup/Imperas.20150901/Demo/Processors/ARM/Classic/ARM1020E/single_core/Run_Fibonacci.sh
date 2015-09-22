#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.ARM9-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM1020E \
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   $@     -argv 39

