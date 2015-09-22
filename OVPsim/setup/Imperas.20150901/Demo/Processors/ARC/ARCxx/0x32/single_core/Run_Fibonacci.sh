#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.ARC600-O3-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 \
     --numprocessors 1          $@     -argv 39

